#include "api.h"
#include "og_stdlib.h"
#define NUMBER_OF_PHILOSOPHERS 17

void say(int n, char *text) {
	char buffer[256];
	char number[64];
	og_int_to_string(number, n);

	og_string_concat(buffer, "Philosopher", " ");
	og_string_concat(buffer, buffer, number);
	og_string_concat(buffer, buffer, " ");
	og_string_concat(buffer, buffer, text);
	og_string_concat(buffer, buffer, "\n");

	og_print_string(buffer);
}

void philosopher(int arg) {
	int n = arg;
	int cycles;
	message_t answer;
	uint32_t waiter;
	
	say(n, "seated himself");

	og_read_msg('c', &answer, 100000);
	cycles = answer.message;
	og_read_msg('p', &answer, 100000);
	waiter = answer.message;

	while(cycles > 0) {

		say(n, "starts thinking");
		og_sleep(og_random(3000, 5000));

		say(n, "gets hungry");

		// Left
		//say(n, "asks for left fork");
		og_send_msg(waiter, 'l', n);
		og_read_msg('l', &answer, 10000);
		while(!answer.message) {
			//say(n, "asks for left fork");
			og_sleep(1000);
			og_send_msg(waiter, 'l', n);
			og_read_msg('l', &answer, 10000);
		}
		//say(n, "picks up his left fork");

		// Right
		//say(n, "asks for right fork");
		og_send_msg(waiter, 'r', n);
		og_read_msg('r', &answer, 10000);
		while(!answer.message) {
			//say(n, "asks for right fork");
			og_sleep(1000);
			og_send_msg(waiter, 'r', n);
			og_read_msg('r', &answer, 10000);
		}
		//say(n, "picks up his right fork");
		say(n, "+++STARTS+++ eating");
		og_sleep(og_random(3000, 5000));
		say(n, "---STOPS--- eating");
		og_send_msg(waiter, 'd', n);
		//say(n, "dropped his forks");

		cycles--;
	}

	say(n, "is done for today");
	og_send_msg(waiter, 'x', n);

	og_exit(0);
}

void waiter(int cycles) {

	int forks[NUMBER_OF_PHILOSOPHERS];
	uint32_t pids[NUMBER_OF_PHILOSOPHERS];
	int done = 0;
	message_t request;
	int i;
	int forks_on_table = NUMBER_OF_PHILOSOPHERS;
	
	// Seed random generator
	og_random_seed(og_system_clock());

	// Set priority to make sure higher than children
	og_set_priority(og_get_pid(), 10);

	// Init forks
	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		forks[i] = 1;
	}

	// Spawn children
	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		pids[i] = og_spawn(philosopher, i, 20);
		if (pids[i] == -1) {
			say(i, "failed to be created, could not start a new process");
			done++;
		} else {
			og_send_msg(pids[i], 'c', cycles);
			og_send_msg(pids[i], 'p', og_get_pid());
		}
	}

	while(done < NUMBER_OF_PHILOSOPHERS) {
		if (og_read_msg('*', &request, 10000)) {
			continue;
		}
		if (request.type == 'l') {
			i = request.message;
			if(forks_on_table > 1) {
				if(forks[i]) {
					//say(i, "got his left fork --Waiter");
					forks_on_table--;
					forks[i] = 0;
					og_send_msg(pids[i], 'l', 1);
				} else {
					//say(i, "'s left fork is busy --Waiter");
					og_send_msg(pids[i], 'l', 0);
				}
			} else {
				//say(i, "didn't get left, only one free  --Waiter");
				og_send_msg(pids[i], 'l', 0);
			}
		} else if (request.type == 'r') {
			i = request.message;
			if(forks[(i+1) % NUMBER_OF_PHILOSOPHERS]) {		
				//say(i, "got his right fork --Waiter");	
				forks_on_table--;
				forks[(i+1) % NUMBER_OF_PHILOSOPHERS] = 0;
				og_send_msg(pids[i], 'r', 1);
			} else {
				//say(i, "'s right fork is busy --Waiter");
				og_send_msg(pids[i], 'r', 0);
			}
		} else if (request.type == 'd') {
			i = request.message;
			//say(i, "returned his forks --Waiter");
			forks[i] = 1;
			forks[(i+1) % NUMBER_OF_PHILOSOPHERS] = 1;
			forks_on_table += 2;
		} else if (request.type == 'x') {
			//og_print_string("Waiter says goodbye to a philosopher\n");
			done++;
		}
	}

	og_print_string("All philosophers have finished for today\n");

	og_exit(0);

}

void dining_philosophers() {

	char buffer[12];
	int cycles;

	// Get number of cycles
	buffer[0] = 0;
	while(og_parse_int(buffer, &cycles) || cycles < 1) {
		og_print_string("The number of cycles must be a positive integer\n");
		og_print_string("How many cycles do you want to execute: ");
		og_read_line(buffer, 12);
	}

	og_spawn(waiter, cycles, 10);
	og_exit(0);
}
