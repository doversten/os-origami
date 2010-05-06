#ifndef __API__
#define __API__

#include "syscall.h"
#include "types.h"

int og_print_string(const char* text);
int og_read_line(char* text, int max);
int og_kill(uint32_t pid, uint32_t exit_code);
int og_exit(uint32_t exit_code);

#endif
