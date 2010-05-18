#include "types.h"

static uint32_t current_random;

uint32_t og_random(uint32_t min, uint32_t max) {
	current_random = (current_random*current_random) % (7877*5087); //Two randomly selected primes :/
	return (current_random % (max-min+1)) + min;
}

void og_seed(uint32_t seed) {
	current_random = seed;
}

int og_parse_int(char* text, int* n) {
	int i = 0;
	int ack = 0;

	if (!((text[0] >= '0' && text[0] <= '9') || text[0] == '-')) {
		return -1;
	}

	if (text[0] == '-') {
		i++;
	}

	while(text[i]) {
		if (text[i] >= '0' && text[i] <= '9') {
			ack = ack * 10 + (text[i] - '0');
			i++;
		} else {
			return -1;
		}
	}

	if (text[0] == '-') {
		ack *= -1;
		// This is reALLY A LOT MORE INTUATIVE
		//ack = ack + (2147483647 - (ack-1)) + (2147483647 - (ack-1));
	}

	*n = ack;
	return 0;

}

int og_string_equals(char* a, char* b) {
	
	int i = 0;
	while(a[i] && b[i]){
		if (a[i] != b[i]){
			return 0;	// The current characters are not equal
		}
		i++;
	}
	
	if (a[i] || b[i]) {		// One of the string is longer then the other
		return 0;
	}

	return 1;
}
