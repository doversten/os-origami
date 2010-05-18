#include "console.h"
#include "scheduler.h"
#include "pcb.h"
#include "api.h"
#include "programs.h"

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
		pid[i] = og_spawn(child, 10);
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

void reader() {

	char buffer[128];
	og_print_string("Readin'\n");

	while (1) {
		og_print_string("\n>");
		while(og_read_line(&buffer[0], 128)) {
			og_print_string("input in progress\n");
		};
		og_print_string("Read'\n");
		og_print_string(buffer);
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

   //og_spawn(parent, 15);
	og_spawn(reader, 15);

	while(1) {}

}


