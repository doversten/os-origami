#ifndef __PCB__
#define __PCB__

#include "types.h"
#include "registers.h"

typedef struct
{
  uint32_t pid;
  uint32_t priority;
  uint8_t status;
  registers_t regs;

} pcb_t;

#endif
