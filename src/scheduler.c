#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"
#include "pcb_queue.h"
#include "scheduler.h"
#include "message_pool.h"
#include "programs.h"
#include "malta_display.h"

static uint32_t system_clock = 0;
static pcb_t *current = NULL;
static pcb_queue_t pcb_ready;
static pcb_queue_t pcb_block;

uint32_t scheduler_system_clock() {
	return system_clock;
}

pcb_t *scheduler_get_current_pcb() {
	return current;
}

uint32_t scheduler_get_current_pid() {
	return current->pid;
}
int scheduler_get_state(uint32_t pid) {
	if (pcb_queue_contains(&pcb_ready, pid))
		return 0;
	else if (pcb_queue_contains(&pcb_block, pid))
		return 1;
	else
		return -1;
}

int scheduler_set_priority(uint32_t pid, uint32_t priority) {

	if (pid >= NUMBER_OF_PROCESSES) {
		return -1;		//Failcode
	}

	pcb_t	*pcb = pcb_get_with_pid(pid);

	if (!pcb || pcb->status.field.empty) {
		return -1;
	}

	// Remove, change prio and add to keep elements correctly linked
	if (pcb_queue_contains(&pcb_ready, pid)) {
		pcb_queue_remove(&pcb_ready, pid);
		pcb->priority = priority;
		pcb_queue_add(&pcb_ready, pcb);
		// New active process?
		if (priority < current->priority || pcb == current) {
			current = NULL;
			scheduler_schedule();
		}
	} else if (pcb_queue_contains(&pcb_block, pid)) {
		pcb_queue_remove(&pcb_block, pid);
		pcb->priority = priority;
		pcb_queue_add(&pcb_block, pcb);
	} else {
		// Shouldn't happen, running process not in any queue
		console_print_string("\nERROR>>>>Trying to set priority of process not in ready or block queue.\n");
		return -1;
	}

	return 0;
}

int scheduler_kill(uint32_t pid, uint32_t exit_code) {

	pcb_t *pot_supervisor;

	if (pid >= NUMBER_OF_PROCESSES) {
		return -1;		//Failcode
	}

	// Get pcb
	pcb_t *zombie_pcb = pcb_get_with_pid(pid);

	if (!zombie_pcb) {
		return -1;		// Failcode
	}

	if (zombie_pcb->status.field.empty) {
		return -1;		// Failcode
	}

	// Remove pcb from scheduler
	pcb_queue_remove(&pcb_ready, pid);
	pcb_queue_remove(&pcb_block, pid);

	// Set ready and empty bits.
	zombie_pcb->status.field.ready = 0;
	zombie_pcb->status.field.empty = 1;

	// Send a message to potensial supervisor. 
	if (zombie_pcb->status.field.supervised) {
		pot_supervisor = pcb_get_with_pid(zombie_pcb->supervisor);
		if (pot_supervisor  && !pot_supervisor->status.field.empty ) {
			message_pool_send_from(pid, zombie_pcb->supervisor, 't', exit_code);
		}
	} 

	//Remove supervsed
	zombie_pcb->status.field.supervised = 0;

	// Currently process was running, chose a new one.
	if (zombie_pcb == current) {
		if(current->next == current) {
			// If current process is the only one with it's priority, reset currently.
			current = NULL;
		}else {
			// Set currently process to next process in 'chain'
			current = current->next;
		}
		scheduler_schedule();
	}

	return 0; 		// Success code
}

int scheduler_exit(uint32_t exit_code) {
	return scheduler_kill(current->pid, exit_code);
}

int scheduler_create_process(void (*code)(), uint32_t argument, uint32_t priority) { //const *void code

	//uint32_t pid = 0;
	pcb_t *new_pcb = pcb_get();

	if(!new_pcb) {
		return -1; //failcode
	}

	// Set Empty bit to false
	new_pcb->status.field.empty = 0;

	// Set priority
	new_pcb->priority = priority;

	// Set exception program counter to start of program 
	new_pcb->regs.epc_reg = (uint32_t) code;

	// Set stackpointer to highest adress of program stack
	new_pcb->regs.sp_reg = new_pcb->stack_start;

	// Set the argument of the procces
	new_pcb->regs.a_reg[0] = argument;

	// Set process to be ready to execute
	new_pcb->status.field.ready = 1;

	// Set process pid active
	new_pcb->name = programs_get_name(code);

	// Add the process to the ready queue
	pcb_queue_add(&pcb_ready, new_pcb);

	// RESET STUFF, OH WHY DIDN'T WE DO THIS AT ONCE
	new_pcb->sleep = 0;
	new_pcb->status.field.supervised = 0;
	new_pcb->supervisor = 0;
	message_pool_reset(new_pcb->pid);
	// New process higher priority?
	if (!current || priority < current->priority) {
		current = NULL;
		scheduler_schedule();
	}

	return new_pcb->pid; //successcode
}


int scheduler_block(uint32_t pid) {

	pcb_t *pcb =pcb_get_with_pid(pid);

	if (!pcb || pcb->status.field.empty) {
		return -1;
	} 

	pcb_queue_remove(&pcb_ready, pcb->pid);
	pcb_queue_add(&pcb_block, pcb);

	if (current == pcb) {
		current = NULL;
		scheduler_schedule();		
	}

	return 0;

}

int scheduler_unblock(uint32_t pid) {

	pcb_t *pcb = pcb_get_with_pid(pid);

	if (!pcb || pcb->status.field.empty) {
		return -1;
	} 

	pcb_queue_remove(&pcb_block, pcb->pid);
	pcb_queue_add(&pcb_ready, pcb);

	if (pcb->priority < current->priority) {
		current = NULL;
		scheduler_schedule();		
	}

	return 0;

}

int scheduler_sleep(int ticks) {
	if (ticks <= 0) {
		return -1;
	}

	current->sleep = ticks;
	return scheduler_block(current->pid);

}

void scheduler_decrease_sleep(){

	pcb_t *pcb;
	pcb_queue_reset(&pcb_block);
	pcb = pcb_queue_next(&pcb_block);
	while(pcb) {
		if (pcb->sleep > 0) {
			pcb->sleep--;
			if ((pcb->sleep) == 0) {
				scheduler_unblock(pcb->pid);
			}
		}
		pcb = pcb_queue_next(&pcb_block);
	}

}

void scheduler_schedule() {


	// If there is no current running process choose the highest priority from the ready queue
	if(!current){
		current = pcb_queue_get_highest_priority(&pcb_ready);
	} 
	if(!current) {
		// No process to schedule, why did you kill folding?
		malta_display_string("ErrNoPrc");
		while(1){}
	}else {
	// If there is a current process, choose the next process in the 'chain'.
		current = current->next;
		kset_registers(&current->regs);
	}
}

void scheduler_handle_interrupt() {
	system_clock++;
	scheduler_decrease_sleep();
	scheduler_schedule();

}
