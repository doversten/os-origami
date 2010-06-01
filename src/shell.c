#include "api.h"
#include "programs.h"
#include "og_stdlib.h"
#define SHELL_PRIO 2
#define SHELL_WAIT 1000000
#define PROG_PRIO 30

void shell_loop (){

	uint32_t pid;
	message_t msg;
	char input[256];

	while (1) {

		og_print_string("crane> ");
		og_read_line(input, 256);

		if(og_string_equals(input, "quit")) {
			og_print_string("[shell terminated]\n");
			og_exit(0);	
		}

		if (programs_get_program(input)) {
			pid = og_spawn(programs_get_program(input), 0, PROG_PRIO);
			if(pid != -1) {
				og_supervise(pid);
				while(og_wait(&msg, SHELL_WAIT)) {}
			} else {
				og_print_string("[Could not create new process]\n");
			}
		} else {
			og_print_string("[No such program exists]\n");
		}

	}
	
}

void shell(){
	og_set_priority(og_get_pid(), SHELL_PRIO);
	og_print_string("Welcome! Write 'quit' to exit the shell.\n\n");
	shell_loop();
}
