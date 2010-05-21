#ifndef __CHAR_FIFO__
#define __CHAR_FIFO__

#include "types.h"

#define FIFO_SIZE 128

/* A simple FIFO queue of bounded size. */
typedef 
struct char_fifo_t {
	uint8_t  elements[FIFO_SIZE];
	int length;
	int current;
} char_fifo_t;

int char_fifo_put(char_fifo_t* fifo, uint8_t c);		// Put an element in the queue
char char_fifo_get(char_fifo_t* fifo);					// remove an element from the queue

#endif
