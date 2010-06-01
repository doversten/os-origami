#include "pcb_queue.h"
#include "pcb.h"
#include "types.h"
#include "console.h"

int pcb_queue_contains(pcb_queue_t *queue, uint32_t pid) {

	int i;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if (queue->elements[i] && queue->elements[i]->pid == pid) {
			return 1;
		}
	}

	return 0;
}

void pcb_queue_reset(pcb_queue_t *queue) {
	queue->current = 0;
}

pcb_t *pcb_queue_next(pcb_queue_t *queue) {

	while(queue->current < NUMBER_OF_PROCESSES) {
		queue->current++;
		if (queue->elements[queue->current-1]) {
			return queue->elements[queue->current-1];
		}
	}

	return 0;

}

int pcb_queue_remove(pcb_queue_t *queue, uint32_t pid) {

	uint32_t i = 0;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		//check if it is a PCB and the PCB we looking for.
		if(queue->elements[i] && queue->elements[i]->pid == pid) {
			// Link together the previus and next element in the 'chain'
			queue->elements[i]->prev->next = queue->elements[i]->next;
			queue->elements[i]->next->prev = queue->elements[i]->prev;
			queue->elements[i] = NULL;
		}
	}

	return 0;

}

int pcb_queue_add(pcb_queue_t *queue, pcb_t *element) {

	uint32_t i = 0;

	pcb_queue_remove(queue, element->pid);  //take away any copy of the elemnt in the queue.
	
	element->next = element;
	element->prev = element;


	if (!queue) { return 0; }

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if(queue->elements[i] == NULL){
			queue->elements[i] = element;
			break;
		}
	}

	if (i == NUMBER_OF_PROCESSES) { return 0; }

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		// Is PCB stored at this index? Is it the added PCB?
		if(!queue->elements[i] || queue->elements[i] == element) { continue; }
		if (queue->elements[i]->priority == element->priority) {
			element->next = queue->elements[i]->next;
			element->prev = queue->elements[i];
			queue->elements[i]->next = element;
			element->next->prev = element;
			break;
		}
	}

	return 0;

}

pcb_t *pcb_queue_get_highest_priority(pcb_queue_t *queue) {

	uint32_t i;
	pcb_t *current_highest = NULL;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		//Check if space in array is not-empty
		if (queue->elements[i]) {
			//Check if we have a higher priotity or if current i lower then the highest
			if ( !current_highest || current_highest->priority > queue->elements[i]->priority) {
				current_highest = queue->elements[i];
			}
		}
	}
	return current_highest;
}
