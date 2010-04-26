#include "pcb.h"

#define NUMBER_OF_PROCESSES 16

static pcb_t[NUMBER_OF_PROCESSES] pcbArray;
static pcb_t[NUMBER_OF_PROCESSES] *readyQueue;
static pcb_t[NUMBER_OF_PROCESSES] *blockQueue;
static uint8_t readyQueueN = 0;
static uint8_t blockQueueN = 0;


void scheduler_handle_interrupt() {
}

void scheduler_block(int pid) {
  uint8_t i = 0;
  while (i < NUMBER_OF_PROCESSES){
    if(readyQueue[i] != 0) {
      if (readyQueue[i]->pid == pid)
        readyQueue[i] = 0;
    }
  }
}

void scheduler_unblock(int pid) {
}

void scheduler_next() {
}
