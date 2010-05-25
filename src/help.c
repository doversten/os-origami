#include "programs.h"
#include "api.h"

void help() {

	int i;

	og_print_string("Available programs:\n");
	og_print_string("-------------------\n");

	for(i = 0; i < NUMBER_OF_PROGRAMS; i++) {
		if(programs[i][2]) {
			og_print_string(programs[i][0]);
			og_print_string("\n");
		}
	}
	og_exit(0);

}
