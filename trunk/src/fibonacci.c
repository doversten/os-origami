#include "api.h"
#include "og_stdlib.h"

void fib_calc(int max_fib_number) {
	int i = 0;
	uint32_t last = 0;
	uint32_t current = 1;

	for (; i<=max_fib_number; i++){
		og_print_int(current);		
		current = current + last;
		last = current - last;
		og_print_string("\n");
	}

	og_exit(0);

}

void fib() {
	char input[12];
	int max;

	input[0] = 0;
	while(og_parse_int(input, &max) || max < 1) {
		og_print_string("The max must be positive integer\n");
		og_print_string("Calc to fibonacci number: ");
		og_read_line(input, 12);
	}
	fib_calc(max);
}
