#ifndef __SYSCALL__
#define __SYSCALL__

#include "registers.h"
#include "types.h"

void og_syscall(uint32_t code, uint32_t arg1, uint32_t arg2, uint32_t arg3);

/* Declaration of system call handler (defined in 'syscall.S'). */
void syscall_handle_interrupt(registers_t* reg);

#endif
