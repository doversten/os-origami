#include "api.h"
#include "og_stdlib.h"

void kill_process(){

	uint32_t pid, prio;
	char buffer[16];

	buffer[0] = '\0';
	while(og_parse_int(buffer, &pid) || pid < 0) {
		og_print_string("PID of the process: ");
		og_read_line(buffer, 16);
	}

	og_kill(pid);

	og_exit(0);
}
