#include "programs.h"
#include "og_stdlib.h"

void *programs[NUMBER_OF_PROGRAMS][2];

void programs_init () {

	int n = 0;

	programs[n][0] = (void*)"malta_scroller";
	programs[n][1] = (void*) malta_scroller;
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
