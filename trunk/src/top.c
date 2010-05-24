#include "api.h"
#include "og_stdlib.h"

void top() {

	int i, prio;
	char name[128];
	char buffer[256], numbers[32];
	uint32_t pid;
	pids_t pids;
	og_get_pids(&pids);

	//og_print_string("NUMBER_OF_PROCESSES=");
	//og_print_int(pids[0]);
	//og_print_string("\n");

	og_print_string("PID  Name                Priority    State\n");
  
	for(i = 0; i < pids.length; i++) {
		buffer[0] = '\0';
		og_get_process_name(pids.elements[i], name, 128);
		pid = pids.elements[i];



		/*og_print_int(pid);
		og_print_string(" - ");
		og_print_string(name);
		og_print_string("\n");*/

		og_uint_to_string(numbers, pid);
		og_fill_string(numbers, 5, ' ');
		og_string_concat(buffer, buffer, numbers);

		og_fill_string(name, 20, ' ');
		og_string_concat(buffer, buffer, name);

		prio = og_get_priority(pid);
		og_uint_to_string(numbers, prio);
		og_fill_string(numbers, 12, ' ');
		og_string_concat(buffer, buffer, numbers);

		if (og_get_scheduler_state(pid) == 1) {
			og_string_concat(buffer, buffer, "blocked");
		} else if (og_get_scheduler_state(pid) == 0) {
			og_string_concat(buffer, buffer, "ready");
		} else {
			og_string_concat(buffer, buffer, "error");
				}

		og_string_concat(buffer, buffer, "\n");
		og_print_string(buffer);
		
	}
	
	og_exit(0);

}
