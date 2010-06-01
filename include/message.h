#ifndef __MESSAGE__
#define __MESSAGE__

#include "types.h"

// Type for messages

typedef struct message_t {
	uint32_t sender;
	uint32_t receiver;
	char type; //0 for empty, 't' reserved for supervisor messages.
	uint32_t message;
} message_t;

#endif
