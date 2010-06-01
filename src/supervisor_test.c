#include "api.h"

void stupid(){
	uint32_t pid = og_get_pid();
	while(1){
		og_send_msg(pid,1,0);
		og_sleep(og_random(500,1500));
	}
}
void supervisor(){
	message_t msg;
	int prio = og_get_priority(og_get_pid());
	int i = 0;
	uint32_t pid;
	for(i = 0;i < 3; i++){
		pid = og_spawn(stupid,0,prio+1);
		og_supervise(pid);
	}
	while(1){
		og_wait(&msg, 100000000);
		og_print_string("A child died, spawning a new\n");
		pid = og_spawn(stupid,0,prio+1);
		og_supervise(pid);
	}
}


void supervisor_test(){

	int prio = og_get_priority(og_get_pid());
	og_spawn(supervisor,0,prio);
	og_exit(0);
}
