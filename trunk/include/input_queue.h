#ifndef __INPUT_QUEUE__
#define __INPUT_QUEUE__

#include "types.h"

typedef struct input_req_t
{
	uint32_t requester;
	char *save_spot;
	int index;
	int length;
} input_req_t;

typedef struct input_queue_t
{
	int length;
	int current;
	input_req_t elements[NUMBER_OF_PROCESSES];
} input_queue_t;

int input_queue_put(input_queue_t *queue, uint32_t pid, char *save_spot, int length);
int input_queue_get(input_queue_t *queue, input_req_t *req);
void input_queue_print(input_queue_t *queue);

#endif
