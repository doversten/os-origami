#include "console.h"
#include "ns16550.h"
#include "registers.h"
#include "asm.h"
#include "mips4kc.h"
#include "scheduler.h"

static registers_t regs;
static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;

void kinit()
{

	// Init scheduler stuff
	scheduler_init();

	// Init
	status_reg_t and, or;

	/* Setup storage-area for saving registers on exception. */
	kset_registers(&regs);

	/* Initialise timer to interrupt in 100 ms (simulated time). */
	kload_timer(100 * timer_msec);

	/* Update the status register to enable timer interrupts. */
	//kset_sr(0xFFBF00E8, 0x10008001);
	
	// Enable I/O Interrupt
	/* Below is an alternative way of setting the status register,
	 * using the 'status_reg_t' type defined in 'mips4kc.h'.
	 */
	and.reg = 0xFFFFFFFF;
	and.field.exl = 0; 	// Normal level (not exception)
	and.field.erl = 0;	// Error level
	and.field.um	= 0; 	// Kernel mode
	and.field.im	= 0x84; // Disable all except HW interrupt 0 and timer
	and.field.bev = 0; 	// Use normal exception vector (not bootsptrap)

	or.reg	= 0;
	or.field.ie	 = 1;	 	// Enable interrupts
	or.field.im	 = 0x84;	// Enable HW interrupt 0 and timer 84
	or.field.cu0	= 1;	 	// Coprocessor 0 usable

	kset_sr(and.reg, or.reg);

	/* Generate interrupts when data is received by UART. */
	console->ier.field.erbfi = 1;

	/* Some obscure bit that need to be set for UART interrupts to work. */
	console->mcr.field.out2 = 1;

}


//testkod

void interrupt_foo() {

	console_print_string("Loopin2'");

	while(1) {};

}


void kexception()
{
	//static int i = 0;
	cause_reg_t cause;

	/* Make sure that we are here because of a timer interrupt. */
	cause.reg = kget_cause();
	//kdebug_assert(cause.field.exc == 0);		/* External interrupt */
	//kdebug_assert(cause.field.ip & 0x80);	 /* Timer interrupt */
	
	if (cause.field.ip & 0x80) { //Timer interrupt
	/* Reload timer for another 100 ms (simulated time) */
		kload_timer(100 * timer_msec);
		console_print_string("Timer interrupt!\n");

		//test
		scheduler_create_process(interrupt_foo);



	} else if(cause.field.ip & 4) { //Console interrupt
		console_handle_interrupt();
	} else {
		console_print_string("Unknown Interrupt: ");
		console_print_int(cause.field.ip);
		console_putc('\n');
		console_print_int(cause.field.exc);
		console_putc('\n');
	}

}
