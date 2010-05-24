#include "programs.h"
#include "og_stdlib.h"

void *programs[NUMBER_OF_PROGRAMS][2];
void *unknown = "<unknown>";

void programs_init () {

	int n = 0;

	// TODO DEBUG THESE Should be golobaly declared, not on the stack, danger danger

	programs[n][0] = (void*)"malta_scroller_loop";
	programs[n][1] = (void*) malta_scroller_loop;
	n++;
	programs[n][0] = (void*)"malta_scroller";
	programs[n][1] = (void*) malta_scroller;
	n++;
	programs[n][0] = (void*)"shell";
	programs[n][1] = (void*) shell;
	n++;
	programs[n][0] = (void*)"fib";
	programs[n][1] = (void*) fib;
	n++;
	programs[n][0] = (void*)"inc";
	programs[n][1] = (void*) inc;
	n++;
	programs[n][0] = (void*)"dining_philosophers";
	programs[n][1] = (void*) dining_philosophers;
	n++;
	programs[n][0] = (void*)"waiter";
	programs[n][1] = (void*) waiter;
	n++;
	programs[n][0] = (void*)"philosopher";
	programs[n][1] = (void*) philosopher;
	n++;
	programs[n][0] = (void*)"folding";
	programs[n][1] = (void*) folding;
	n++;
	programs[n][0] = (void*)"top";
	programs[n][1] = (void*) top;
	n++;
	programs[n][0] = (void*)"ring";
	programs[n][1] = (void*) ring;
	n++;
	programs[n][0] = (void*)"ring_actor";
	programs[n][1] = (void*) ring_actor;
	n++;
	programs[n][0] = (void*)"change_priority";
	programs[n][1] = (void*) change_priority;
	n++;
	programs[n][0] = (void*)"supervisor_test";
	programs[n][1] = (void*) supervisor_test;
	n++;
	programs[n][0] = (void*)"supervisor";
	programs[n][1] = (void*) supervisor;
	n++;
	programs[n][0] = (void*)"stupid";
	programs[n][1] = (void*) stupid;
	n++;


}

void *programs_get_program(char *programID){
	
	int i = 0;
	
	for(i =0; i < NUMBER_OF_PROGRAMS; i++) {
		if (og_string_equals(programID, (char*) programs[i][0])) {
			return programs[i][1];
		}
	}

	return 0; //TODO:fix to return NULL

}

char *programs_get_name(void (*code) ()) {

	int i = 0;
	
	for(i =0; i < NUMBER_OF_PROGRAMS; i++) {
		if(code == programs[i][1]) {
			return programs[i][0];
		}
	}

	console_print_string(">>>ERROR: Couldn't find process name\n");
	return unknown; //TODO:fix to return NULL?

}
