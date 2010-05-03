#include "pcb.h"
#include "types.h"
#include "stack.h"


void pcb_init() {

	uint32_t i;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		pcbArray[i].pid = i;
		pcbArray[i].status.field.empty = 1;
		pcbArray[i].stack = &stackArray[i].memory[PROGRAM_STACK_START];
	}

}

pcb_t *pcb_get() {

	uint32_t i;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if (pcbArray[i].field.empty) {
			return &pcbArray[i];
		}
	}

	return NULL;

}


void pcb_free(pcb_t *pcb) {

	pcb->status.field.empty = 1;

}
