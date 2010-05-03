#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"
#include "pcb_queue.h"

static pcb_t *current;

int scheduler_create_process(void (*code)()) { //const *void code

  uint32_t pid = 0;
  while (pid < NUMBER_OF_PROCESSES) {
    if (pcbArray[pid].status.field.empty) {
      break;
    }
    pid++;
  }
  if(pid == NUMBER_OF_PROCESSES) {
    return 0; //failcode
  }

  pcbArray[pid].status.field.empty = 0;  //Set Empty bit to false
  pcbArray[pid].priority = 1;		 //Set priority
  pcbArray[pid].regs.epc_reg = (uint32_t) code; //Set exception program counter to start of program 
  pcbArray[pid].regs.sp_reg = (uint32_t) &stackArray[pid].memory[PROGRAM_STACK_START]; //Set stackpointer to highest adress of program stack
  pcbArray[pid].status.field.ready = 1; //Set process to be ready to execute
  //scheduler_add_to_ready(pid);  // Add the process to the ready queue

  //rest code:
  //kset_registers(&pcbArray[pid].regs);

  return 1;

}

void scheduler_handle_interrupt() {

//kset_registers(current->regs)

}
