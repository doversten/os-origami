#include "api.h"
#include "og_stdlib.h"

void top() {

	int i;
	char name[128];
	char buffer[256];
	uint32_t pid;
	pids_t pids;
	og_get_pids(&pids);

	//og_print_string("NUMBER_OF_PROCESSES=");
	//og_print_int(pids[0]);
	//og_print_string("\n");
	for(i = 0; i < pids.length; i++) {
		og_get_process_name(pids.elements[i], name, 128);
		pid = pids.elements[i];


		/*og_print_int(pid);
		og_print_string(" - ");
		og_print_string(name);
		og_print_string("\n");*/

		og_int_to_string(buffer, pid);
		og_string_concat(buffer, buffer, " - ");
		og_string_concat(buffer, buffer, name);
		og_string_concat(buffer, buffer, "\n");
		og_print_string(buffer);
	}
	
	og_exit(0);

}
