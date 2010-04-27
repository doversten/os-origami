#ifndef __PCB__
#define __PCB__

#include "types.h"
#include "registers.h"

typedef struct pcb_t
{
  uint32_t pid;
  uint32_t priority;
  union {
      uint8_t value;
      struct {
        uint8_t ready : 1;  //Ready bit, 1 if process is ready to be executed 0 if it's blocked or pending some event.
        uint8_t empty : 1;  //Valid bit, 0 if PCB contains an active process, 1 otherwise.
      } field;
  } status;
  registers_t regs;
  struct pcb_t *next;
  struct pcb_t *prev;

} pcb_t;

#endif
