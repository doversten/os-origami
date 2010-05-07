#include "../include/types.h"

void inc(uint32_t n) {
	int i = 0;
	for (; i<=n; i++){
		og_print_int(i);
		og_print_string("\n");
	}
}
