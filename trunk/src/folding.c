#include "console.h"
#include "scheduler.h"
#include "pcb.h"
#include "api.h"
#include "programs.h"

#include "types.h"

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

	while(1) {

		og_print_string("a");
		if (og_sleep(10000)) {
			og_print_string("I'm not sleepy :(");
		}

	}

}

static uint32_t pid1;
static uint32_t pid2;
static uint32_t prio = 2;

void prio2() {

	while (1) {
		og_print_string("2");
		og_set_priority(pid2, ++prio);
	}

}

void prio1() {

	og_sleep(10000);

	pid2 = og_spawn(prio2, ++prio);

	/*og_print_string("pid1 ");
	og_print_int(pid1);
	og_print_string("\n");
	og_print_string("pid2 ");
	og_print_int(pid2);
	og_print_string("\n");*/

	while (1) {
		og_print_string("1");
		og_set_priority(pid1, ++prio);
		/*og_print_string("prio ");
		og_print_int(prio);
		og_print_string("\n");
		og_print_string("set_prio code ");
		og_print_int(og_set_priority(pid1, ++prio));
		og_print_string("\n");*/
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
	//og_display_string("Origami");
	//og_display_string("LOL O ! ");

	og_spawn(malta_scroller, 1);

   pid1 = og_spawn(prio1, prio);
	og_print_string("folding pid1 ");
	og_print_int(pid1);
	og_print_string("\n");

	while(1) {}

}


