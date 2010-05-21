#ifndef __PROGRAMS__
#define __PROGRAMS__

#include "types.h"

#define NUMBER_OF_PROGRAMS 12

//User programs
void malta_scroller();
void malta_scroller_loop(int ask);
void thotin();
void fib();
void inc();
void dining_philosophers();
void waiter(int cycles);
void philosopher();
void ring();
void ring_actor();
void folding();
void top();

//Meta-programs counters 
void programs_init();
void *programs_get_program(char *programID);


#endif
