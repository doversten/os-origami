#include "pcb_queue.h"
#include "pcb.h"
#include "types.h"
#include "console.h"

int pcb_queue_remove(pcb_queue_t queue, uint32_t pid) {

	uint32_t i = 0;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		//check if it is a PCB and the PCB we looking for.
		if(queue[i] && queue[i]->pid == pid) {
			// Link together the previus and next element in the 'chain'
			queue[i]->prev->next = queue[i]->next;
			queue[i]->next->prev = queue[i]->prev;
			queue[i] = NULL;
		}
	}

	return 0;

}

int pcb_queue_add(pcb_queue_t queue, pcb_t *element) {

	uint32_t i = 0;

	pcb_queue_remove(queue, element->pid);  //take away any copy of the elemnt in the queue.
	
	element->next = element;
	element->prev = element;


	if (!queue) { return 0; }

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if(queue[i] == NULL){
			queue[i] = element;
			break;
		}
	}

	if (i == NUMBER_OF_PROCESSES) { return 0; }

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if(!queue[i] || queue[i] == element) { continue; }
		if (queue[i]->priority == element->priority) {
			element->next = queue[i]->next;
			element->prev = queue[i];
			queue[i]->next = element;
			element->next->prev = element;
			break;
		}
	}

	return 0;

}

pcb_t *pcb_queue_get_highest_priority(pcb_queue_t queue) {

	uint32_t i;
	pcb_t *current_highest = NULL;

	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		//Check if space in array is not-empty
		if (queue[i]) {
			//Check if we have a higher priotity or if current i lower then the highest
			if ( !current_highest || current_highest->priority > queue[i]->priority) {
				current_highest = queue[i];
			}
		}
	}
	return current_highest;
}


/* TEST CODE*/
void pcb_queue_print(pcb_queue_t queue) {

	uint32_t i = 0;


	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		console_print_string("\n-----");
		if(queue[i]) {
			console_print_string("\narray_index=");
			console_print_int(i);
			console_print_string("\npid=");
			console_print_int(queue[i]->pid);
			if(queue[i]->next) {
				console_print_string("\nnext=");
				console_print_int((uint32_t)queue[i]->next->pid);
				console_print_string("\nprev=");
				console_print_int((uint32_t)queue[i]->prev->pid);
			}
		} else {
			console_print_string("\narray_index=");
			console_print_int(i);
			console_print_string("\nIngen PCB");
		}
		console_print_string("\n-----");
	}

}




void pcb_queue_test() {

	pcb_queue_t q;
	pcb_t pcb0;
	pcb_t pcb1;
	pcb_t pcb2;
	pcb_t pcb3;
	pcb_t pcb4;
	pcb_t pcb5;

	pcb0.pid = 0;
	pcb1.pid = 10;
	pcb2.pid = 20;
	pcb3.pid = 30;
	pcb4.pid = 40;
	pcb5.pid = 50;


	pcb0.priority = 1;
	pcb1.priority = 1;
	pcb2.priority = 2;
	pcb3.priority = 3;
	pcb4.priority = 1;
	pcb5.priority = 2;

	pcb_queue_add(q, &pcb0);
	pcb_queue_add(q, &pcb1);
	pcb_queue_add(q, &pcb2);
	pcb_queue_add(q, &pcb3);
	pcb_queue_add(q, &pcb4);
	pcb_queue_add(q, &pcb5);

	pcb_queue_print(q);

   console_print_string("\nstartar dequeueing\n");

	pcb_queue_remove(q, 10);
	pcb_queue_remove(q, 20);
	pcb_queue_remove(q, 30);

	pcb_queue_print(q);

   console_print_string("\nstartar dequeueing\n");

	pcb2.priority = 2;

	pcb_queue_add(q, &pcb2);


	pcb_queue_print(q);

	console_print_string("Highest:\n");
	console_print_int(pcb_queue_get_highest_priority(q)->pid);
	console_print_string("\n");
	console_print_int(pcb_queue_get_highest_priority(q)->priority);

}
