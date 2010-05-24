#include "api.h"
#include "og_stdlib.h"

void malta_scroller_loop(int ask) {
	char display[128];
	char *standard = "Welcome to the Origami Operating System";
	char *blank = "        ";
	int i = 0;

	message_t update;
	uint32_t pid;

	og_string_concat(display, blank, standard);

	while (1) {

		// Receive new strings via messages
		// Empty the message
		update.type = 0;
		if(!og_read_msg('s', &update, 1000)) {
			//og_print_string("Receiving new string\n");
			// Reset display string
			i = 8;
			og_string_concat(display, blank, "\0");
			// Empty the message
			update.type = 0;
			while(!og_read_msg('c', &update, 1000)) {
				//og_print_string("Got another char\n");
				display[i] = (char) update.message;
				i++;
				// Might not be able to handle all messages if this got lower prio than sender and we get spammed
			}
			display[i] = '\0';
			i = 0;
		}

		og_display_string(display + i);
	
		if (!display[i]) {
			i = 0;
		}

		i++;
	}

}

void malta_scroller() {

	pids_t pids;
	uint32_t pid;
	char name[256];
	char input[256];
	int i = 0;

	og_get_pids(&pids);
	for(i = 0; i < pids.length; i++) {
		pid = pids.elements[i];
		og_get_process_name(pid, name, 256);
		if(og_string_equals(name, "malta_scroller_loop")) {	
			break;
		}
	}

	if(i == pids.length) {
		og_print_string("[Could not find malta scroller loop process; starting new scroller]\n");
		pid = og_spawn(malta_scroller_loop, 0, 1);
	}

	og_print_string("Enter text to scroll: ");
	og_read_line(input, 256);

	og_send_msg(pid, 's', 0);
	i = 0;
	while(input[i]) {
		og_send_msg(pid, 'c', input[i]);
		i++;
	}

	og_exit(0);

}
