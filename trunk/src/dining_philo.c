#include "api.h"
#include "og_stdlib.h"
#define NUMBER_OF_PHILOSOPHERS 7
static int forks[NUMBER_OF_PHILOSOPHERS];
static uint32_t pids[NUMBER_OF_PHILOSOPHERS];
static int n_iterations_left[NUMBER_OF_PHILOSOPHERS];

void philosopher(uint32_t number) {
	uint32_t supervisor_pid;
	message_t message;
	og_read_msg('i', &message, 2000);
	supervisor_pid = message.sender;
	int even = number % 2;

	while(1) {
		og_print_string("Philosofer ");
		og_print_int(number);
		og_print_string(" is thinking\n");
		int r = og_random(500, 1500);
		og_print_string("\n");
		if(og_sleep(r)){
		og_print_string("Philosofer ");
		og_print_int(number);
		og_print_string(" couldent sleep\n");
		}
		og_print_string("Philosofer ");
		og_print_int(number);
		og_print_string(" got hungry\n");
		if (even) {
			og_send_msg(supervisor_pid, 'l', 0); // request left fork
		} else {
			og_send_msg(supervisor_pid, 'r', 0); // request right fork
		}
		while(og_read_msg('i',&message,500)){
			og_print_string("Philosofer ");
			og_print_int(number);
			og_print_string(" is waiting for the first fork\n");
		
		}
		
		if (!even) {
			og_send_msg(supervisor_pid, 'l', 0); // request left fork
		} else {
			og_send_msg(supervisor_pid, 'r', 0); // request right fork
		}
		while(og_read_msg('i',&message,500)){
			og_print_string("Philosofer ");
			og_print_int(number);
			og_print_string(" is waiting for the second fork\n");
		}
		
	
		og_print_string("Philosofer ");
		og_print_int(number);
		og_print_string(" is eating\n");
		r = og_random(500, 2500);
		og_print_string("\n");

		if(og_sleep(r)){
		og_print_string("Philosofer ");
		og_print_int(number);
		og_print_string(" couldent sleep\n");
		}
		og_send_msg(supervisor_pid, 'd', 0); // drops forks
		og_print_string("Philosofer ");
		og_print_int(number);
		og_print_string(" finished eating\n");
	}

}

void dining_init () {
	int i;
	char iterations[12];
	int i_iterations;	
	og_random_seed(og_system_clock());
	og_print_string("How many iterations do you want to execute: ");
	og_read_line(iterations, 12);
	while(og_parse_int(iterations, &i_iterations) || i_iterations < 1) {
		og_print_string("The number of iterations must be a positive integer\n");
		og_print_string("How many iterations do you want to execute: ");
		og_read_line(iterations, 12);
	}

	for(i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
		pids[i] = og_spawn(philosopher, i, 25);
		og_send_msg(pids[i],'i',0);
		n_iterations_left[i] = i_iterations;
		if(i < NUMBER_OF_PHILOSOPHERS){
			forks[i] = 1;
		}
	}
}

void dining_ph(){
	int i;
	message_t message;
	dining_init();
	while(1){
		og_read_msg('*',&message,10000);
		for(i = 0; i < NUMBER_OF_PHILOSOPHERS; i++){
			if(message.sender == pids[i])
				break;
		}
		if(message.type == 'r'){
			if(forks[(i + 1) % NUMBER_OF_PHILOSOPHERS]){
				og_send_msg(pids[i],'i',0);
				forks[(i + 1) % NUMBER_OF_PHILOSOPHERS] = 0;
			}
		}else if(message.type == 'l'){
			if(forks[i]){
				og_send_msg(pids[i],'i',0);
				forks[i] = 0;
			}
		}else if(message.type == 'd'){
			forks[i] = forks[(i + 1) % NUMBER_OF_PHILOSOPHERS] = 1;
			n_iterations_left[i]--;
			if(!n_iterations_left[i]){
				og_kill(pids[i]);
				for(i = 0; i < NUMBER_OF_PHILOSOPHERS; i++){
					if(n_iterations_left[i])
						break;
				}
				if (i == NUMBER_OF_PHILOSOPHERS){
					og_print_string("All philosophers are finished eating\n");
					og_exit(0);
				}
			}
		}
	}
}
