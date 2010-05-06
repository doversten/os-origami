#ifndef __PCB_QUEUE__
#define __PCB_QUEUE__

#include "pcb.h"

typedef pcb_t *pcb_queue_t[NUMBER_OF_PROCESSES];

// Add a pcb with pid to the queue
int pcb_queue_add(pcb_queue_t queue, pcb_t *element);	
// Remove pcb with pid from the queue
int pcb_queue_remove(pcb_queue_t queue, uint32_t pid);
// Get the pcb with the highest priority in the queue
pcb_t *pcb_queue_get_highest_priority(pcb_queue_t queue);

#endif
