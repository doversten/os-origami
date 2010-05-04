#ifndef __API__
#define __API__

#include "syscall.h"
#include "types.h"

void og_print(const char* text);
void og_kill(uint32_t pid, uint32_t exit_code);
void og_exit(uint32_t exit_code);

#endif
