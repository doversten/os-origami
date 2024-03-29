#include "pcb.h"
#include "types.h"
#include "stack.h"
#include "message_pool.h"
#include "pids.h"

static volatile pcb_t pcbArray[NUMBER_OF_PROCESSES];
static volatile stack_t stackArray[NUMBER_OF_PROCESSES];

int pcb_get_priority(uint32_t pid){
	if(pid >= NUMBER_OF_PROCESSES) {
		return -1;
	}
	if(pcbArray[pid].status.field.empty) {
		return -2;
	}

	return pcbArray[pid].priority;
}

int pcb_get_name(uint32_t pid, char *name, int nameSize) {
	int i = 0;
	if(pid >= NUMBER_OF_PROCESSES) {
		return -1;
	}
	if(pcbArray[pid].status.field.empty) {
		return -2;
	}
	while(i < nameSize-1) {
		if(pcbArray[pid].name[i]) {
			name[i] = pcbArray[pid].name[i];
			i++;
		} else {
			name[i] = '\0';
			break;
		}
	}
	return 0;
}

int pcb_get_pids(pids_t *pids) {
	int i;
	pids->length = 0;
	for(i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if(pcbArray[i].status.field.empty) {
			continue;
		} else {
			pids->elements[pids->length] = pcbArray[i].pid;
			pids->length++;
		}
	}
	return 0;
}

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
		pcbArray[i].status.field.supervised = 0;
		pcbArray[i].stack_start = (uint32_t) &stackArray[i].memory[PROGRAM_STACK_START];
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
