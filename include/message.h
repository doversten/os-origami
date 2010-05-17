#ifndef __MESSAGE__
#define __MESSAGE__

#include "types.h"

typedef struct message_t {
	uint32_t sender;
	uint32_t receiver;
	char type; //'i' int, 'c' char, 'f' float, 'd' double, 0 for empty
	uint32_t message;
} message_t;

#endif
