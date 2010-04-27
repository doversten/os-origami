#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"

#define NUMBER_OF_PROCESSES 16
#define NULL 0

static pcb_t pcbArray[NUMBER_OF_PROCESSES];
//static pcb_t *readyQueue[NUMBER_OF_PROCESSES];
//static pcb_t *blockQueue[NUMBER_OF_PROCESSES];
static stack_t stackArray[NUMBER_OF_PROCESSES];

void scheduler_foo() {

  console_print_string("Loopin'");

  while(1) {};

}

void scheduler_next() {
}


void scheduler_block(uint32_t pid) {
  if (pid >= NUMBER_OF_PROCESSES) return;
  scheduler_remove_from_ready(pid);
  scheduler_add_to_block(pid);
  return;
}

void scheduler_unblock(uint32_t pid) {
  if (pid >= NUMBER_OF_PROCESSES) return;
  scheduler_remove_from_block(pid);
  scheduler_add_to_ready(pid);
  return;
}

void scheduler_remove(uint32_t pid) {
  scheduler_remove_from_block(pid);
  scheduler_remove_from_ready(pid);
  return;
}

void scheduler_init() {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    pcbArray[i].pid = i;
    pcbArray[i].status.field.empty = 1;
    i++;
  }
  
}

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
  scheduler_add_to_ready(pid);  // Add the process to the ready queue

  //rest code:
  //kset_registers(&pcbArray[pid].regs);

  return 1;

}

void scheduler_handle_interrupt() {

  
  //kset_registers()

}
