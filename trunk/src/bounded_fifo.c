#include <bounded_fifo.h>

/* bfifo_put: Inserts a character at the end of the queue. */
static void bfifo_put(struct bounded_fifo* bfifo, uint8_t ch)
{
  /* Make sure the 'bfifo' pointer is not 0. */
  //kdebug_assert(bfifo != 0);

  if (bfifo->length < FIFO_SIZE) {
    bfifo->buf[(bfifo->length)++] = ch;
  }
}

/* bfifo_get: Returns a character removed from the front of the queue. */
static uint8_t bfifo_get(struct bounded_fifo* bfifo)
{
  int i;
  uint8_t ch;

  /* Make sure the 'bfifo' pointer is not 0, and that queue is not empty. */
  //kdebug_assert(bfifo != 0);
  //kdebug_assert(bfifo->length > 0);

  bfifo->length--;
  ch = bfifo->buf[0];
  for (i = 0; i < bfifo->length; i++) {
    bfifo->buf[i] = bfifo->buf[i+1];
  }
  return ch;
}
