#ifndef __PROGRAMS__
#define __PROGRAMS__

#include "types.h"

#define NUMBER_OF_PROGRAMS 6

//User programs
void malta_scroller();
void thotin();
void fib();
void inc();
void waiter();
void folding();

//Meta-programs counters 
void programs_init();
void *programs_get_program(char *programID);


#endif
