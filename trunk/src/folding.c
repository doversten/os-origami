#include "console.h"
#include "scheduler.h"
#include "pcb.h"
#include "api.h"
#include "programs.h"

#include "og_stdlib.h"

void child() {
	message_t brev;
	if (og_read_msg('i', &brev, 1000000)) {
		og_print_string("fail");
		og_print_string("\n");
	} else {
		og_print_int(brev.message);
		og_print_string("\n");
	}

	og_exit(0);

}

void parent() {
	int i;
	uint32_t pid[5];
	for(i = 0; i < 5; i++) {
		pid[i] = og_spawn(child, 0, 10);
	}

	og_print_string("Lilla barnen skapade\n");

	for(i = 0; i < 5; i++) {
		og_set_priority(pid[i], 20);
	}

		og_print_string("Smiskat ner barnen till lagre prio\n");

	for(i = 0; i < 5; i++) {
		og_send_msg(pid[i], 'i', pid[i]);
	}

	og_print_string("Medelanden skickade\n");
	og_exit(0);

}

void intreader() {

	int n = -1;
	char buffer[128];
	og_print_string("Readin'\n");

	while (1) {
		
		buffer[0] = 0;
		while(og_parse_int(buffer, &n)) {
			og_print_string("Enter an integer: ");
			og_read_line(&buffer[0], 128);
		}

		og_print_string("Read: ");
		og_print_int(n);
		og_print_string("\n");
	}

}

void reader() {

	char buffer1[128];
	char buffer2[128];
	og_print_string("Readin'\n");

	while (1) {

		og_print_string("String1: ");
		og_read_line(buffer1, 128);
		og_print_string("String2: ");
		og_read_line(buffer2, 128);

		if (!og_string_equals(buffer1, buffer2)) {
			og_print_string("o");
		}
		og_print_string("lika!\n");
	}

}


void argumenter(int i) {
	og_print_string("\n");
	og_print_string("Argumenter: ");
	og_print_int(i);
	og_print_string("\n");
	og_exit(0);
}

void randomer(uint32_t seed) {
	og_seed(seed);
	int i;
	for (i = 0; i < 100; i++) {
		og_print_int(og_random(1,10));
		og_print_string("\n");
	}	
	og_exit(0);
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

	og_spawn(programs_get_program("malta_scroller"), 0, 1);

   //og_spawn(parent, 15);

//	og_spawn(argumenter, 42, 1);

//	og_spawn(reader, 0, 15);

	og_spawn(randomer, 1337, 1);
	og_spawn(randomer, 2*1337, 1);
	og_spawn(randomer, 3*1337, 1);
	og_spawn(randomer, 4*1337, 1);

	while(1) {}

}


