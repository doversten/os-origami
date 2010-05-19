#ifndef __API__
#define __API__

#include "syscall.h"
#include "types.h"
#include "message.h"

int og_print_string(const char* text);
int og_print_int(int i);
int og_read_line(char*text, int max);

int og_display_int(int n);
int og_display_string(const char* text);

int og_spawn(void (*code)(), uint32_t argument, uint32_t priority);
int og_kill(uint32_t pid);
int og_exit(uint32_t exit_code);

int og_sleep(int ticks);

int og_set_priority(uint32_t pid, uint32_t priority);

int og_read_msg(char type, message_t *spot, int timeout);
int og_send_msg(uint32_t receiver, char type, uint32_t data);

uint32_t og_get_pid();

uint32_t og_random(uint32_t min, uint32_t max);
int og_random_seed(uint32_t seed);

uint32_t og_system_clock();

//Supervise systemcalls
int og_supervise(uint32_t pid);
int og_unsupervise(uint32_t pid);
int og_wait(message_t *spot, int timeout);

#endif
