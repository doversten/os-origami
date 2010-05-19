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
	int i;
	int sum = 0;

	og_random_seed(seed);

	for (i = 0; i < 10000; i++) {
		sum += og_random(1,101);
	}	

	og_print_string("Seed = ");
	og_print_int(seed);
	og_print_string("\n");	

	og_print_int(sum/10000);
	og_print_string("\n");		
	og_exit(0);
}


void slave(int arg) {
	
	int sleep_time = og_random(1,10000);
	
	og_sleep(sleep_time);
	og_print_string("I'm slave #");
	og_print_int(arg);
	og_print_string(" and I'm going to get eaten. T.T \n");
	og_exit(0);


}

void big_boss() {

	int i;
	uint32_t pid[5];	
	message_t message;

	og_random_seed(og_system_clock());

	og_print_string("Spawning my slaves! MUHAHA!\n");
	
	for (i = 0; i < 5; i++) {
		pid[i] = og_spawn(slave, pid, 25);
		og_supervise(pid[i]);
		og_print_string("slave created: ");
		og_print_int(pid[i]);
		og_print_string("\n");
	}

	og_print_string("Eating my slaves! MUHAHA!\n");
	for (i = 0; i < 5; i++) {
		og_wait(&message, 10000);
		og_print_string("slave #");
		og_print_int(message.sender);
		og_print_string(" have been eated!\n");
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

	og_spawn(programs_get_program("malta_scroller"), 0, 1);

   //og_spawn(parent, 0, 15);

	//og_spawn(argumenter, 42, 1);

	//og_spawn(reader, 0, 15);

	/*while(1) {
		og_spawn(randomer, og_system_clock(), 1);
	}*/

	og_spawn(big_boss, 0, 20);

	while(1) {}

}


