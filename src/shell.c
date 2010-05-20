#include "api.h"
#include "programs.h"
#include "og_stdlib.h"
#define SHELL_PRIO 20
#define SHELL_WAIT 1000000
#define PROG_PRIO 30

void shell();

/*#include "fibonacci.c"
#include "increment.c"*/

/*int compare(char* a, char* b){
	int i = 0;
	while(a[i]&&b[i]){
		if (a[i]!=b[i]){
			return 0;	// The current characters are not equal
		}
		i++;
	}
	
	if (a[i] || b[i]) {		// One of the string is longer then the other
		return 0;
	}

	return 1;
}*/

/*int parser_int (char* a){
	int i = 0;
	int ack = 0;
	
	while(a[i]) {
		ack = ack * 10 + (a[i] - '0');
		i++;
	}
	return ack;
}*/

void parser (char* input){

	uint32_t pid;
	message_t msg;

	if (programs_get_program(input)) {
		pid = og_spawn(programs_get_program(input), 0, PROG_PRIO);
		og_supervise(pid);
		while(og_wait(&msg, SHELL_WAIT)) {}
	}

	shell();

	/*if (compare(input, "inc")) {
		og_print_string("Print the number you want to increment to: ");
		char text[8];
		og_read_line(text, 8);
		int number = parser_int(text);
		inc(number);
		
	} else if (compare(input, "fib")) {
		og_print_string("Print the number of fibonacci you want to calculate: ");
		char text[8];
		og_read_line(text, 8);
		int number = parser_int(text);
		fib(number);
	} else if (compare(input, "exit") || compare(input, "EXIT")) {
		og_print_string("Bye bye! Thank you for folding...\n");
		og_exit(0);
	} else if (compare(input, "thotin")) {
		thotin();
	} else {
		og_print_string(input);
		og_print_string(": not found\n");
	}*/
	
}

void shell(){
	char input[256];
	og_print_string("thotin > ");
	og_read_line(input, 256);
	parser(input);
}

void thotin(){
	og_set_priority(og_get_pid(), SHELL_PRIO);
	og_print_string("Welcome to thotin, write 'EXIT' to exit the shell!\n\n");
	shell();
}





