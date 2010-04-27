#ifndef __PCB_QUEUE__
#define __PCB_QUEUE__

#include "pcb.h"

#define NUMBER_OF_PROCESSES 16
#define NULL 0

typedef pcb_t *pcb_queue_t[NUMBER_OF_PROCESSES];

int pcb_queue_add(pcb_queue_t queue, pcb_t *element);
int pcb_queue_remove(pcb_queue_t queue, uint32_t pid);
pcb_t *pcb_queue_get_highest_priority(pcb_queue_t queue);

#endif
