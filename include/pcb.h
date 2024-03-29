#ifndef __PCB__
#define __PCB__

#include "types.h"
#include "registers.h"
#include "stack.h"
#include "message_pool.h"
#include "pids.h"

// PCB type

typedef struct pcb_t
{
	uint32_t pid;
	//The lower the value is the higher the priority is, priority >= 0	
	uint32_t priority;
	union {
			uint8_t value;
			struct {
				//Ready bit, 1 if process is ready to be executed 0 if it's blocked or pending some event.
				uint8_t ready : 1;
				//Valid bit, 0 if PCB contains an active process, 1 otherwise.
				uint8_t empty : 1;
				//Have Supervisor
				uint8_t supervised : 1;
			} field;
	} status;
	// The current value of the registers for this process.
	registers_t regs;
	// The next process to run in the 'chain' with process with the same priority.		
	struct pcb_t *next;
	// The previus process that runed in the 'chain' with process with the same priority.
	struct pcb_t *prev;
	// Pointer to the process stack.		
	uint32_t stack_start;
	// Ticks to sleep the process
	int sleep;
	// Process supervisor to notify on exit
	uint32_t supervisor;
	// Program name
	char* name;

} pcb_t;

//Initialization of the pcb.
void pcb_init();
// Get the first free pcb.
pcb_t *pcb_get();
// Free the pcb with specied pid.						
void pcb_free(pcb_t *pcb);
// Get the pcb that contains a process with speciefied pid.	
pcb_t *pcb_get_with_pid(uint32_t pid);
// Process information
int pcb_get_pids(pids_t *pids);
int pcb_get_name(uint32_t pid, char *name, int nameSize);
int pcb_get_priority(uint32_t pid);

#endif
