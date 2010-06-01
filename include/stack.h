#ifndef __STACK__
#define __STACK__

#include "types.h"

// Process stack type

#define PROGRAM_STACK_SIZE 0x1000
#define PROGRAM_STACK_START 0x0FFF

typedef struct
{
  uint32_t memory[PROGRAM_STACK_SIZE];
} stack_t;

#endif
