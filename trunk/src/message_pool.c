#include "message.h"
#include "message_pool.h"
#include "pcb.h"
#include "scheduler.h"

static volatile message_pool_t poolArray[NUMBER_OF_PROCESSES];

int message_pool_send(uint32_t receiver, char type, uint32_t message) {
	uint32_t sender = scheduler_get_current_pid();
	message_pool_t *pool = (message_pool_t*) &poolArray[receiver]; 
	pcb_t *pcb = pcb_get_with_pid(receiver);
	int i;

	if(pool->waiting_for_type == type) {
		//Copy the message to the save spot.
		if(!pool->save_spot) {
			console_print_string("\n>>>ERROR: og_read called with NULL message pointer.\n");
			return -1;
		}
		pool->save_spot->sender = sender;
		pool->save_spot->receiver = receiver;
		pool->save_spot->type = type;
		pool->save_spot->message = message;
		pool->waiting_for_type = 0;
		pool->save_spot = NULL;
		

		pcb->regs.v_reg[0] = 0; // setting return value for the waiting process.

		scheduler_unblock(receiver);

		return 0;
	} 

	for(i = 0; i < NUMBER_OF_MESSAGES; i++){
		if(!pool->messages[i].type){
			pool->messages[i].sender = sender;
			pool->messages[i].receiver = receiver;
			pool->messages[i].type = type;
			pool->messages[i].message = message;
			break;
		}
	}
	if (i == NUMBER_OF_MESSAGES) 
		return -1;

	return 0;
}

int message_pool_read(char type, message_t *spot, int timeout) {
	uint32_t receiver = scheduler_get_current_pid();
	message_pool_t *pool = (message_pool_t*) &poolArray[receiver];  
	int i;
	
	for(i = 0; i < NUMBER_OF_MESSAGES; i++){
		if (pool->messages[i].type == type) {
			//Copy the message to the save spot.
			spot->sender = pool->messages[i].sender;
			spot->receiver = pool->messages[i].receiver;
			spot->type = pool->messages[i].type;
			spot->message = pool->messages[i].message;
			//Delete the read message.
			pool->messages[i].type = 0;
			return 0;
		}

	}
	pool->waiting_for_type = type;
	pool->save_spot = spot;
	scheduler_sleep(timeout);

	return -1;

}
