#include "pcb.h"
#include "stack.h"
#include "console.h"
#include "asm.h"
#include "types.h"

#define NUMBER_OF_PROCESSES 16
#define NULL 0

pcb_t pcbArray[NUMBER_OF_PROCESSES];
static pcb_t *readyQueue[NUMBER_OF_PROCESSES];
static pcb_t *blockQueue[NUMBER_OF_PROCESSES];
stack_t stackArray[NUMBER_OF_PROCESSES];

void scheduler_foo() {

  console_print_string("Loopin'");

  while(1) {};

}

void scheduler_next() {
}


void scheduler_add_to_ready(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(readyQueue[i] == NULL){
      readyQueue[i] = &pcbArray[pid];
      break;
    }

    i++;
  }
  return;

}
void scheduler_add_to_block(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(blockQueue[i] == NULL){
      blockQueue[i] = &pcbArray[pid];
      break;
    }

    i++;
  }
  return;

}
void scheduler_remove_from_ready(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(readyQueue[i] != NULL && readyQueue[i]-> pid == pid){
      readyQueue[i] = NULL;
    }

    i++;
  }
  return;

}
void scheduler_remove_from_block(uint32_t pid) {
  uint32_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(blockQueue[i] != NULL && blockQueue[i]-> pid == pid){
      blockQueue[i] = NULL;
    }

    i++;
  }
  return;
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

void scheduler_create_process(void (*code)()) { //const *void code

  uint32_t pid = 0;
  console_print_string("scheduler_create_process()\n");
  while (pid < NUMBER_OF_PROCESSES) {
    if (pcbArray[pid].status.field.empty) {
      break;
    }
    pid++;
  }
  console_print_string("pid=");
  console_print_int(pid);
  console_print_string("\n");

  pcbArray[pid].status.field.empty = 0;

  pcbArray[pid].status.field.ready = 1; //is this safe?

  pcbArray[pid].priority = 1;

  //void (*function_pointer)();
  //function_pointer = scheduler_foo;

  console_print_int(0);
  console_print_string("\n");
  console_print_int(scheduler_foo);
  console_print_string("\n");

  pcbArray[pid].regs.epc_reg = (uint32_t) code;//scheduler_foo;

  pcbArray[pid].regs.sp_reg = (uint32_t) &stackArray[pid].memory[PROGRAM_STACK_START];

  console_print_string("stack=");
  console_print_int(pcbArray[pid].regs.sp_reg);
  console_print_string("\n");

  //scheduler_add_to_ready(pid);
  //test
  kset_registers(&pcbArray[pid].regs);

}

void scheduler_handle_interrupt() {

  
  //kset_registers()

}
