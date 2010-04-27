#include <stdio.h>
#include "pcb_queue.h"






void print_queue_unix(pcb_queue queue) {
	int pid, next, prev;
	int i;
	
	for (i=0; i < NUMBER_OF_PROCESS, i++) {
		if (queue[i]){ 
			printf("NULL, ")
			continue;
		}
		pid = queue[i]->pid;
		if (!queue[i]->next) {
			printf("Pid:%d (NULL), ", pid); 
		} else {
			next = queue[i]->next;
			prev = queue[i]->prev;
			printf("Pid:%d, (next:%d, prev:%d), ", pid, next, prev)
		} 
	}
}

int main () {



}