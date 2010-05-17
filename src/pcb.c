#include "pcb.h"
#include "types.h"
#include "stack.h"
#include "message_pool.h"

static volatile pcb_t pcbArray[NUMBER_OF_PROCESSES];
static volatile stack_t stackArray[NUMBER_OF_PROCESSES];


pcb_t *pcb_get_with_pid(uint32_t pid) {

	if(pid >= NUMBER_OF_PROCESSES)
		return NULL;
	return (pcb_t*) &pcbArray[pid];
}

void pcb_init() {

	uint32_t i;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		pcbArray[i].pid = i;
		pcbArray[i].status.field.empty = 1;
		pcbArray[i].stack_start = (uint32_t) &stackArray[i].memory[PROGRAM_STACK_START];
		//pcbArray[i].messages = &poolArray[i]; //Not really necessary since we don't use it
	}
}

pcb_t *pcb_get() {

	uint32_t i;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if (pcbArray[i].status.field.empty) {
			return (pcb_t*) &pcbArray[i];
		}
	}

	return NULL;
}


void pcb_free(pcb_t *pcb) {

	pcb->status.field.empty = 1;
}
