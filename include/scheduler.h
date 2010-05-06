#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"
#include "pcb_queue.h"

// Initialization of the scheduler.
void scheduler_init();

// Create a process with specied function and priority.							
int scheduler_create_process(void (*code)(),uint32_t priority);

// Kill a process with specified pid and speciefied exit code.
int scheduler_kill(uint32_t pid, uint32_t exit_code);

// Kill the current process with exit code	
int scheduler_exit(uint32_t exit_code);

// Interupt handler that makes contex switch.									.
void scheduler_handle_interrupt();

// Get current process' pcb/pid
pcb_t *scheduler_get_current_pcb();
uint32_t scheduler_get_current_pid();

// (Un)block processes
int scheduler_block(uint32_t pid);
int scheduler_unblock(uint32_t pid);

#endif
