#include "api.h"

void malta_scroller() {

	int i = 0;
	char *string = "        ORIGAMI OPERATING SYSTEM";

	while (1) {

		og_display_string(string + i);
	
		if (!string[i]) {
			i = 0;
		}

		i++;
		if(og_sleep(1000)) {
			og_print_string("\nSLEEP FAILED\n");
			og_exit(-1);
		}
	}
}
