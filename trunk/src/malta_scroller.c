#include "api.h"

void malta_scroller_init() {

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

void malta_scroller_text(char *string) {
	char buffer[256];
	int i = 0;
	char *blank = "        ";
	og_string_concat(buffer, blank, string);

	while (1) {

		og_display_string(buffer + i);
	
		if (!buffer[i]) {
			i = 0;
		}

		i++;
		if(og_sleep(1000)) {
			og_print_string("\nSLEEP FAILED\n");
			og_exit(-1);
		}
	}
}

void malta_scroller() {
	char input[256];
	og_print_string("What do you like to print: ");
	og_read_line(input, 256-8);
	malta_scroller_text(input);
}
