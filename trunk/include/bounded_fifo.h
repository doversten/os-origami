#ifndef __NS16550__
#define __NS16550__

#include "types.h"

#define FIFO_SIZE 8

/* A simple FIFO queue of bounded size. */
struct bounded_fifo {
  uint8_t  buf[FIFO_SIZE];
  uint32_t length;
};

static void bfifo_put(struct bounded_fifo* bfifo, uint8_t ch);
static uint8_t bfifo_get(struct bounded_fifo* bfifo);

#endif
