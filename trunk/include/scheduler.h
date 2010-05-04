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
void scheduler_handle_interrupt();
void scheduler_kill(uint32_t pid, uint32_t exit_code);
void scheduler_exit(uint32_t exit_code);

#endif
