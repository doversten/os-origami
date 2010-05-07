#include "console.h"
#include "scheduler.h"
#include "pcb.h"
#include "api.h"

void prog1() {

	char test[16];

	while (1) {

		og_print_string("Origami1> ");
		while(og_read_line(test, 16)){}
		og_print_string("Fagel 1 viskar: ");
		og_print_string(test);
		og_print_string("\n");
	}

}

void prog2() {

og_print_int(42);

og_exit(0);

}

void prog3() {

	while (1) {
		og_print_string("FUUUUUUU\n");
	}

}

void folding() {

	og_print_string("                   _____ ______  _____  _____   ___  ___  ___ _____ \n");
	og_print_string("                  |  _  || ___ \\|_   _||  __ \\ / _ \\ |  \\/  ||_   _|\n");
	og_print_string("                  | | | || |_/ /  | |  | |  \\// /_\\ \\|      |  | |  \n");
	og_print_string("                  | | | ||    /   | |  | | __ |  _  || |\\/| |  | |  \n");
	og_print_string("                  \\ \\_/ /| |\\ \\  _| |_ | |_\\ \\| | | || |  | | _| |_ \n");
	og_print_string("                   \\___/ \\_| \\_| \\___/  \\____/\\_| |_/\\_|  |_/ \\___/ \n");
                                               
	og_print_string("Startup\n");

	//og_display_int(-678);
	//og_display_int(12345);
	og_display_string("Origami");
	//og_display_string("LOL O ! ");

	while(1) {}

}


