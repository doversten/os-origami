#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"
#include "pcb_queue.h"

int scheduler_create_process(void (*code)(),uint32_t priority);
void scheduler_init();
#endif
