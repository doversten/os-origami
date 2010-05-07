#include "../include/types.h"

void fib(uint32_t max_fib_number) {
	int i = 0;
	uint32_t last = 0;
	uint32_t current = 1;

	for (; i<=max_fib_number; i++){
		og_print_int(current);		
		current = current + last;
		last = current - last;
		og_print_string("\n");
	}
}
