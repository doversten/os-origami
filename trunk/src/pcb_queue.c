#include "pcb_queue.h"
#include "pcb.h"
#include "types.h"
#include "console.h"



int pcb_queue_add(pcb_queue_t queue, pcb_t *element) {
	uint32_t i = 0;

	element->next = NULL;
	element->prev = NULL;


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
			if (!queue[i]->next){
				element->next = queue[i];
				element->prev = queue[i];
				queue[i]->next = element;
				queue[i]->prev = element;
			}else {
				element->next = queue[i]->next;
				element->prev = queue[i];
				queue[i]->next = element;
				element->next->prev = element;
			}
			break;
		}
	}

	return 1;

}

int pcb_queue_remove(pcb_queue_t queue, uint32_t pid) {

	uint32_t i = 0;


	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		if(queue[i] && queue[i]->pid == pid){		//är pcb och den pcb vi letar efter
			if(queue[i]->next){							//om det inte är den enda med denna prioritet
				if(queue[i]->prev == queue[i]->next){ // precis två pcbs linkade
					queue[i]->prev->next = queue[i]->next->prev = NULL;
				}else{
					queue[i]->prev->next = queue[i]->next;
					queue[i]->next->prev = queue[i]->prev;
				}
			}
		}
	}

	return 1;

}

void pcb_queue_print(pcb_queue_t queue) {

	uint32_t i = 0;


	for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
		console_print_string("\n-----");
		if(queue[i]) {
			console_print_string("array_index=");
			console_print_int(i);
			console_print_string("\npid=");
			console_print_int(queue[i]->pid);
			console_print_string("\nnext=");
			console_print_int((uint32_t)queue[i]->next);
			console_print_string("\nprev=");
			console_print_int((uint32_t)queue[i]->prev);
		} else {
			console_print_string("array_index=");
			console_print_int(i);
			console_print_string("\nIngen PCB");
		}
		console_print_string("\n-----");
	}

}


/*

void scheduler_add_to_ready(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(readyQueue[i] == NULL){
      readyQueue[i] = &pcbArray[pid];
      break;
    }

    i++;
  }
  return;

}
void scheduler_add_to_block(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(blockQueue[i] == NULL){
      blockQueue[i] = &pcbArray[pid];
      break;
    }

    i++;
  }
  return;

}
void scheduler_remove_from_ready(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(readyQueue[i] != NULL && readyQueue[i]-> pid == pid){
      readyQueue[i] = NULL;
    }

    i++;
  }
  return;

}
void scheduler_remove_from_block(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(blockQueue[i] != NULL && blockQueue[i]-> pid == pid){
      blockQueue[i] = NULL;
    }

    i++;
  }
  return;
}
*/
