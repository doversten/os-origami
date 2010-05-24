#ifndef __PROGRAMS__
#define __PROGRAMS__

#include "types.h"

#define NUMBER_OF_PROGRAMS 13

//User programs
void malta_scroller();
void malta_scroller_loop(int ask);
void shell();
void fib();
void inc();
void dining_philosophers();
void waiter(int cycles);
void philosopher();
void ring();
void ring_actor();
void folding();
void top();
void change_priority();

//Meta-programs counters 
void programs_init();
void *programs_get_program(char *programID);


#endif
