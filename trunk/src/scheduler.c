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


int scheduler_create_process(void (*code)(),uint32_t priority) { //const *void code

	
	
	uint32_t pid = 0;
	while (pid < NUMBER_OF_PROCESSES) {
		if (pcbArray[pid].status.field.empty) {
			break;
		}
		pid++;
	}
	if(pid == NUMBER_OF_PROCESSES) {
		return 0; //failcode
	}

	pcbArray[pid].status.field.empty = 0;		// Set Empty bit to false
	pcbArray[pid].priority = priority;		// Set priority
	pcbArray[pid].regs.epc_reg = (uint32_t) code; 	// Set exception program counter to start of program 
	pcbArray[pid].regs.sp_reg = (uint32_t) &stackArray[pid].memory[PROGRAM_STACK_START]; // Set stackpointer to highest adress of program stack
	pcbArray[pid].status.field.ready = 1;		// Set process to be ready to execute
	pcb_queue_add(pcb_ready, &pcbArray[pid]);	// Add the process to the ready queue

	pcb_queue_print(pcb_ready);

	//rest code:
	//kset_registers(&pcbArray[pid].regs);

	return 1;

}

void scheduler_handle_interrupt() {
	if(!current){
		current = pcb_queue_get_highest_priority(pcb_ready);
	}if(!current){
	}else{
		current = current->next;
		kset_registers(&current->regs);
	}
}
