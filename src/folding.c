#include "programs.h"
#include "api.h"
#include "og_stdlib.h"

void folding() {

	og_print_string("                   _____ ______  _____  _____   ___  ___  ___ _____ \n");
	og_print_string("                  |  _  || ___ \\|_   _||  __ \\ / _ \\ |  \\/  ||_   _|\n");
	og_print_string("                  | | | || |_/ /  | |  | |  \\// /_\\ \\|      |  | |  \n");
	og_print_string("                  | | | ||    /   | |  | | __ |  _  || |\\/| |  | |  \n");
	og_print_string("                  \\ \\_/ /| |\\ \\  _| |_ | |_\\ \\| | | || |  | | _| |_ \n");
	og_print_string("                   \\___/ \\_| \\_| \\___/  \\____/\\_| |_/\\_|  |_/ \\___/ \n");
                                               
	og_print_string("Startup\n");

	og_spawn(malta_scroller_loop, 1, 1);

	og_spawn(programs_get_program("shell"), 0, 2);

	while(1) {}

}


