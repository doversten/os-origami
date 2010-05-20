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
int scheduler_create_process(void (*code)(), uint32_t argument, uint32_t priority);

// Kill a process with specified pid and speciefied exit code.
int scheduler_kill(uint32_t pid, uint32_t exit_code);

// Kill the current process with exit code	
int scheduler_exit(uint32_t exit_code);

//Scheduler that makes stuff.
void scheduler_schedule();

// Interupt handler that makes contex switch and decrease of sleep.							.
void scheduler_handle_interrupt();

// Get current process' pcb/pid
pcb_t *scheduler_get_current_pcb();
uint32_t scheduler_get_current_pid();

// (Un)block processes
int scheduler_block(uint32_t pid);
int scheduler_unblock(uint32_t pid);

// Sleep processes
int scheduler_sleep(int ticks);

void scheduler_decrease_sleep();

// Set priority
int scheduler_set_priority(uint32_t pid, uint32_t priority);

// System clock
uint32_t scheduler_system_clock();

// Process information
uint32_t *scheduler_get_pids();

// Debug
void scheduler_debug();

#endif
