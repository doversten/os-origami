#ifndef __MESSAGE_POOL__
#define __MESSAGE_POOL__

#include "message.h"

// A pool containing NUMBER_OF_MESSAGES messages

#define NUMBER_OF_MESSAGES 16

typedef struct messagese_pool_t{
	message_t *save_spot;
	char waiting_for_type;
	message_t messages[NUMBER_OF_MESSAGES];

} message_pool_t;

int message_pool_read(char type, message_t *spot, int timeout);
int message_pool_send(uint32_t receiver, char type, uint32_t message);
int message_pool_send_from(uint32_t sender, uint32_t receiver, char type, uint32_t message);
int message_pool_reset(uint32_t pid);

#endif
