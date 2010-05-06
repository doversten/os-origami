#ifndef __SYSCALL__
#define __SYSCALL__

#include "registers.h"
#include "types.h"

int og_syscall(uint32_t code, uint32_t arg1, uint32_t arg2, uint32_t arg3);		// Syscall function for the OS.

/* Declaration of system call handler (defined in 'syscall.S'). */
int syscall_handle_interrupt(registers_t* reg);

#endif
