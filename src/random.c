#include "types.h"
#include "scheduler.h"

static uint32_t current_random;

// Semi-pesudeo-somewhat-random function
uint32_t random(uint32_t min, uint32_t max) {
	int next_random = (current_random*current_random) % (7877*5087);  //Two randomly selected primes :)
	if (next_random == current_random) {
		next_random += 42;
	}
	current_random = next_random;
	return (current_random % (max-min+1)) + min;
}

int random_seed(uint32_t seed) {
	current_random = seed;
	return 0;
}
