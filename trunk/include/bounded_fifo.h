#ifndef __BOUNDED_FIFO__
#define __BOUNDED_FIFO__

#include "types.h"

#define FIFO_SIZE 256

/* A simple FIFO queue of bounded size. */
typedef 
struct bounded_fifo_t {
  uint8_t  buf[FIFO_SIZE];
  uint32_t length;
} bounded_fifo_t;

void bfifo_put(struct bounded_fifo_t* bfifo, uint8_t ch);
uint8_t bfifo_get(struct bounded_fifo_t* bfifo);

#endif
