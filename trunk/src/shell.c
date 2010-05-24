#include "api.h"
#include "programs.h"
#include "og_stdlib.h"
#define SHELL_PRIO 2
#define SHELL_WAIT 1000000
#define PROG_PRIO 30

void shell();


void parser (char* input){

	uint32_t pid;
	message_t msg;

	if (programs_get_program(input)) {
		pid = og_spawn(programs_get_program(input), 0, PROG_PRIO);
		og_supervise(pid);
		while(og_wait(&msg, SHELL_WAIT)) {}
	}

	shell_loop();
	
}

void shell_loop(){
	char input[256];
	og_print_string("crane> ");
	og_read_line(input, 256);
	parser(input);
}

void shell(){
	og_set_priority(og_get_pid(), SHELL_PRIO);
	og_print_string("Welcome to 'the shell', write 'EXIT' to exit the shell!\n\n");
	shell_loop();
}





