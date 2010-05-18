#include "api.h"
#include "og_stdlib.h"
#define NUMBER_OF_PHILOSOPHERS 7
static int forks_and_knives[NUMBER_OF_PHILOSOPHERS][2];
static uint32_t pids[NUMBER_OF_PHILOSOPHERS];

void dining_init () {
	int i;
	int n_processes = NUMBER_OF_PHILOSOPHERS;
	char iterations[12];	
	int n_iterations;

	og_print_string("How many iterations do you want to execute: ");
	og_read_line(iterations, 12);
	while(og_parse_int(iterations, &n_iterations || n_iterations < 1) {
		og_print_string("The number of iterations must be a positive integer\n");
		og_print_string("How many iterations do you want to execute: ");
		og_read_line(iterations, 12);
	}

	for(i=0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		pids[i] = og_spawn(thomas, i, 5);
		forks_and_knives[i][0] = 1;
		forks_and_knives[i][1] = 1;
	}
	
}

void thomas (uint32_t number) {
	uint32_t supervisor_pid;
	message_t message;
	og_read_msg('i', &message, 1000);
	supervisor_pid = message.message;

	int n = number % 2;
	int r = og_random(0, 100);
	og_sleep(r);

	while() {
		if (n) {
			og_send_msg(supervisor_pid, 'i', 1);
		} else {
			og_send_msg(supervisor_pid, 'i', 2);
		}
	
		r = og_random(0, 100);
		og_sleep(r);
	}

}
