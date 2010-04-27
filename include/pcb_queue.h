#ifndef __PCB_QUEUE__
#define __PCB_QUEUE__

#include "pcb.h"

#define NUMBER_OF_PROCESSES 16
#define NULL 0

typedef pcb_t *pcb_queue[NUMBER_OF_PROCESSES];

int pcb_queue_add(pcb_queue queue, pcb *element);
int pcb_queue_remove(pcb_queue queue, uint32_t pid);

#endif
