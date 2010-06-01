#include "api.h"
#include "og_stdlib.h"

void inc_calc(int n) {
	int i = 0;
	for (; i<=n; i++){
		og_print_int(i);
		og_print_string("\n");
	}
	og_exit(0);
}

void inc() {
	char input[12];
	int max;

	input[0] = 0;
	while(og_parse_int(input, &max) || max < 1) {
		og_print_string("The max must be positive integer\n");
		og_print_string("Count to: ");
		og_read_line(input, 12);
	}
	inc_calc(max);
}
