#include "api.h"
#include "og_stdlib.h"

void change_priority(){

	uint32_t pid, prio;
	char buffer[16];


	buffer[0] = '\0';
	while(og_parse_int(buffer, &pid) || pid < 0) {
		og_print_string("PID of the process: ");
		og_read_line(buffer, 16);
	}

	buffer[0] = 0;
	while(og_parse_int(buffer, &prio) || prio < 0) {
		og_print_string("Priority to change to:  ");
		og_read_line(buffer, 16);
	}

	if(og_set_priority(pid, prio)) {
		og_print_string("[No such process]\n");
	}

	og_exit(0);
}
