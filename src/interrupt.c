#include "console.h"
#include "ns16550.h"
#include "registers.h"
#include "asm.h"
#include "mips4kc.h"
#include "scheduler.h"
#include "syscall.h"

static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;

void kexception()
{

	cause_reg_t cause;
	registers_t* reg;

	/* Make sure that we are here because of a timer interrupt. */
	cause.reg = kget_cause();
	
	if (cause.field.ip & 0x80) { //Timer interrupt
		/* Reload timer for another 1/5 ms (simulated time) */
		kload_timer(timer_msec/5);
		scheduler_handle_interrupt();


	} else if(cause.field.ip & 4) { //Console interrupt
		console_handle_interrupt();
	} else if(cause.field.exc == 8) {
		reg = kget_registers();
		// Handle the system call (see syscall.S) and save return value
		reg->v_reg[0] = syscall_handle_interrupt(reg);

		/* Return from exception to instruction following syscall. */
		reg->epc_reg += 4;

	} else {
		console_print_string("-----------------\n");
		console_print_string("Unknown Interrupt\n");
		console_print_string("-----------------\n");
		console_print_string("Interrupt Pending: ");
		console_print_int(cause.field.ip);
		console_print_string("\n");
		console_print_string("Exception Code: ");
		console_print_int(cause.field.exc);
		console_print_string("\n");
		console_print_string("-----------------\n");
	}

}
