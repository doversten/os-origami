#include "api.h"

void stupid(){
	uint32_t pid = og_get_pid();
	while(1){
		og_send_msg(pid,1,0);
		og_sleep(1000);
	}
}
void supervisor(){
	message_t msg;
	int prio = og_get_priority(og_get_pid());
	uint32_t pid = og_spawn(stupid,0,prio+1);
	while(1){
		og_supervise(pid);
		og_wait(&msg, 100000000);
		og_print_string("Mitt barn dog, skapar nytt\n");
		pid = og_spawn(stupid,0,prio+1);
	}
}


int supervisor_test(){

	int prio = og_get_priority(og_get_pid());
	return og_spawn(supervisor,0,prio);
}
