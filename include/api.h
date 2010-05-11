#ifndef __API__
#define __API__

#include "syscall.h"
#include "types.h"

int og_print_string(const char* text);
int og_print_int(int i);
int og_read_line(char*text, int max);
int og_display_int(int n);
int og_display_string(const char* text);
int og_spawn(void (*code)(), uint32_t priority);
int og_kill(uint32_t pid, uint32_t exit_code);
int og_exit(uint32_t exit_code);
int og_sleep(int ticks);
int og_set_priority(uint32_t pid, uint32_t priority);

#endif
