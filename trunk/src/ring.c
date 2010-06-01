#include "api.h"
#include "og_stdlib.h"


void ring_actor(int number){
	message_t message;
	uint32_t send_to_pid;
	og_read_msg('*', &message, 10000);
	if(message.type == 'k'){
		og_exit(1);
	}
	send_to_pid = message.message;
	while(1){
		if(og_read_msg('*',&message,10000)) {
			og_print_string("Hello, im proccess number ");
			og_print_int(number);
			og_print_string(" in the ring and i have not recived a message in a looooong time and will therefore die of loneliness\n");
			og_exit(1);
		}
		if(message.type == 'k'){
			og_print_string("Oh no, they killed proccess number ");
			og_print_int(number);
			og_print_string(" they bastards\n");
			og_send_msg(send_to_pid, 'k', 0);
			og_exit(1);
		}

		og_print_string("Hello, im proccess number ");
		og_print_int(number);
		og_print_string(" in the ring and i have just recived a message\n");
		og_sleep(1000);
		og_send_msg(send_to_pid, 's', 0);
	}
}

void ring(){
	char c_num[12];
	int num, first_pid, current_pid, prev_pid, i;

	og_print_string("Set the number of proccesses in the ring: ");
	og_read_line(c_num, 12);
	while(og_parse_int(c_num,&num) || num < 1){
		og_print_string("The number of proccesses in the ring must be a positive integer\n");
		og_print_string("Set the number of proccesses in the ring: ");
		og_read_line(c_num, 12);
	}

	first_pid = og_spawn(ring_actor,num,31);
	if(first_pid == -1){
		og_print_string("Unable to create proccess number 1, exiting program\n");
		og_exit(1);
	}

	prev_pid = first_pid;
	for(i = 1; i < num; i++){
		current_pid = og_spawn(ring_actor, num - i,31);
		if(current_pid == -1){
			og_print_string("Unable to create proccess number ");
			og_print_int(i+1);
			og_print_string(", exiting program\n");
			og_send_msg(prev_pid,'k',0);
			og_exit(1);
		}

		og_send_msg(current_pid,'i',prev_pid);
		prev_pid = current_pid;
	}

	og_send_msg(first_pid,'i',current_pid);
	og_send_msg(current_pid,'s',0);
	og_exit(0);
}
