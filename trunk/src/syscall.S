
#include <regdef.h>
#include <cp0_regdef.h>
#include "asm_regs.h"

	.text
	.globl og_syscall
	.globl syscall_handle_interrupt


	# og_syscall:
	#   A user mode interface to the kernel mode function
	#   'kmy_system_call'.
	#
og_syscall:
	#la v0,a0		# Load adress of syscall implementation in v0.
	addi v0, a0, 0
	syscall		# Enter kernel mode by 'syscall' exception.
	jr ra			# Back in user mode, return to caller

	# syscall_handler:
	#   Enables argument passing for up
	#   to four parameters of a system call.
	#
	# Input:
	#   a0 - Pointer to saved registers.
	#
syscall_handle_interrupt:
	addi	v0, a0, 0	# Move a0 into v0.
	lw	a0, REG_A1(v0)	# Load saved a1 (argument 1) into a0.
	lw	a1, REG_A2(v0)	# Load saved a2 (argument 2) into a1.
	lw	a2, REG_A3(v0)	# Load saved a3 (argument 3) into a2.	lw	v0, REG_V0(v0)	# Load saved v0 (implementation) into v0.

	jr	v0		# Jump to system call implementation.
