#ifndef __PIDS__
#define __PIDS__

#include "types.h"

typedef struct pids_t
{
	int length;
	uint32_t elements[NUMBER_OF_PROCESSES];
} pids_t;

#endif
