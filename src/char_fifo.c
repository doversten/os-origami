#include <char_fifo.h>
#include <types.h>

/* Inserts a character at the end of the queue. */
int char_fifo_put(char_fifo_t* fifo, uint8_t c)
{
	
	if(!fifo) {
		return -1;
	}

	if(fifo->length < FIFO_SIZE) {
		fifo->elements[(fifo->current + fifo->length) % FIFO_SIZE] = c;
		fifo->length++;
	} else {
		return -1;
	}

	return 0;

}

/* Removes and returns a character at the start of the queue. */
char char_fifo_get(char_fifo_t* fifo) {

	char c;

	if(!fifo) {
		while(1) {
		}
	}

	if(fifo->length > 0) {
		c = fifo->elements[fifo->current];
		fifo->length--;
		fifo->current = (fifo->current + 1) % FIFO_SIZE;
		return c;
	}

	while(1) {
	}

}
