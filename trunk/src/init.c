#include "console.h"
#include "ns16550.h"
#include "registers.h"
#include "asm.h"
#include "mips4kc.h"
#include "scheduler.h"
#include "malta_display.h"
#include "folding.h" //Idle process
#include "programs.h"

static registers_t regs;
static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;

void kinit()
{

	//'Meta'-Programs init
	programs_init();

	// Init malta display
	malta_display_init();

	// Init scheduler stuff
	pcb_init();

	// Mother of all process
	scheduler_create_process(folding, 0, 0xFFFFFFFF);

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

	// Wait for scheduler to start
	while (1) {};
}
