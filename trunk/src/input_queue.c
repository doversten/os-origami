#include <input_queue.h>
#include <types.h>
int input_queue_put(input_queue_t *queue, uint32_t pid, char *save_spot, int length) {
	if(!queue) {
		return -1;
	}

	if (queue->length < NUMBER_OF_PROCESSES) {
		queue->elements[(queue->current + queue->length) % NUMBER_OF_PROCESSES].requester = pid;
		queue->elements[(queue->current + queue->length) % NUMBER_OF_PROCESSES].save_spot = save_spot;
		queue->elements[(queue->current + queue->length) % NUMBER_OF_PROCESSES].length = length;
		queue->elements[(queue->current + queue->length) % NUMBER_OF_PROCESSES].index = 0;
		queue->length++;
	} else {
		return -1;
	}

	return 0;

}

int input_queue_get(input_queue_t *queue, input_req_t *req) {

	if(!queue || !req) {
		return -1;
	}

	if(queue->length > 0) {
		req->requester = queue->elements[queue->current].requester;
		req->save_spot = queue->elements[queue->current].save_spot;
		req->length = queue->elements[queue->current].length;
		req->index = queue->elements[queue->current].index;
		queue->length--;
		queue->current = (queue->current + 1) % NUMBER_OF_PROCESSES;
	} else {
		return -2;
	}

	return 0;

}
