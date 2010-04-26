#ifndef __PCB__
#define __PCB__

#include "types.h"
#include "registers.h"

typedef struct
{
  uint32_t pid;
  uint32_t priority;
  union {
      uint8_t ;
      struct {
          uint8_t ready : 1;  //Ready bit, 1 if process is ready to be executed 0 if it's blocked or pending some event.
	  uint8_t valid : 1   //Valid bit, 1 if PCB contains a ective process, 0 otherwise.
      } field;
  } status;
  registers_t regs;

} pcb_t;

#endif
