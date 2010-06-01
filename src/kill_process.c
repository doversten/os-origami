#include "api.h"
#include "og_stdlib.h"

void kill_process() {

	uint32_t pid;
	char buffer[16];

	buffer[0] = '\0';
	while(og_parse_int(buffer, &pid) || pid < 0) {
		og_print_string("PID of the process: ");
		og_read_line(buffer, 16);
	}

	if(og_kill(pid)) {
		og_print_string("[No such process]\n");
	}

	og_exit(0);
}
