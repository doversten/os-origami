#ifndef __API__
#define __API__

#include "syscall.h"
#include "types.h"
#include "message.h"
#include "pids.h"

// Console
int og_print_string(const char* text);
int og_print_int(int i);
int og_read_line(char*text, int max);

// Malta display
int og_display_int(int n);
int og_display_string(const char* text);

// Process creation and termination
int og_spawn(void (*code)(), uint32_t argument, uint32_t priority);
int og_kill(uint32_t pid);
int og_exit(uint32_t exit_code);

// Sleeping
int og_sleep(int ticks);

// Priority change
int og_set_priority(uint32_t pid, uint32_t priority);

// Messages
int og_read_msg(char type, message_t *spot, int timeout);
int og_send_msg(uint32_t receiver, char type, uint32_t data);

// Random functions
uint32_t og_random(uint32_t min, uint32_t max);
int og_random_seed(uint32_t seed);

// System Clock
uint32_t og_system_clock();

// Supervise systemcalls
int og_supervise(uint32_t pid);
int og_unsupervise(uint32_t pid);
int og_wait(message_t *spot, int timeout);

// Process information
uint32_t og_get_pid();
int og_get_pids(pids_t *pids);
int og_get_process_name(uint32_t pid, char* name, int nameSize);
int og_get_priority(uint32_t pid);
int og_get_scheduler_state(uint32_t pid);

#endif
