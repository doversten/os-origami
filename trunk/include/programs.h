#ifndef __PROGRAMS__
#define __PROGRAMS__

#include "types.h"

#define NUMBER_OF_PROGRAMS 1

//User programs
void malta_scroller();

//Meta-programs counters 
void programs_init();
void *programs_get_program(char *programID);


#endif
