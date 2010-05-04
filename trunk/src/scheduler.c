#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"
#include "pcb_queue.h"
#include "scheduler.h"

static pcb_t *current = NULL;
static pcb_queue_t pcb_ready;
static pcb_queue_t pcb_block;

void scheduler_kill(uint32_t pid, uint32_t exit_code) {

	// Get pcb
	pcb_t *zombie_pcb = pcb_get_with_pid(pid);

	// Remove pcb from scheduler
	pcb_queue_remove(pcb_ready, pid);
	pcb_queue_remove(pcb_block, pid);

	// Set ready and zombie bits.
	zombie_pcb->status.field.ready = 0;
	zombie_pcb->status.field.zombie = 1;

	// Save exit code in zombie pcb
	zombie_pcb->exit_code = exit_code;

	// Currently process was running, chose a new one.
	if (zombie_pcb == current) {
		if(current->next == current) {
			// If current process is the only one with it's priority, reset currently.
			current = NULL;
		}else {
			// Set currently process to next process in 'chain'
			current = current->next;
		}
		scheduler_handle_interrupt();
	}
}

void scheduler_exit(uint32_t exit_code) {
	scheduler_kill(current->pid, exit_code);
}

int scheduler_create_process(void (*code)(),uint32_t priority) { //const *void code

	//uint32_t pid = 0;
	pcb_t *new_pcb = pcb_get();

	if(!new_pcb) {
		return 0; //failcode
	}

	// Set Empty bit to false
	new_pcb->status.field.empty = 0;

	// Set priority
	new_pcb->priority = priority;

	// Set exception program counter to start of program 
	new_pcb->regs.epc_reg = (uint32_t) code;

	// Set stackpointer to highest adress of program stack
	new_pcb->regs.sp_reg = new_pcb->stack_start;

	// Set process is not zombie
	new_pcb->status.field.zombie = 0;

	// Set process to be ready to execute
	new_pcb->status.field.ready = 1;

	// Add the process to the ready queue
	pcb_queue_add(pcb_ready, new_pcb);

	return 1; //successcode

}

void scheduler_handle_interrupt() {
	if(!current){
		current = pcb_queue_get_highest_priority(pcb_ready);
	} 
	if(!current) {
	}else {
		current = current->next;
		kset_registers(&current->regs);
	}
}
