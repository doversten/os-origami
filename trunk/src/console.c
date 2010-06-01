#include "console.h"
#include "ns16550.h"
#include "char_fifo.h"
#include "scheduler.h"
#include "input_queue.h"

static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;
static input_queue_t input_queue;
static input_req_t input_req;
static char_fifo_t output_buffer;
static int input_in_progress = 0;

int console_put_c(char c) { 

	if (output_buffer.length >= FIFO_SIZE) {
		return -1; // Fail code, unable to buffer char
	}

	if(c=='\r') { 
		char_fifo_put(&output_buffer, '\n');
	}

	char_fifo_put(&output_buffer, c);

	if(c=='\n') { 
		char_fifo_put(&output_buffer, '\r');
	}

	if(c==8) { //if c = backspace
		char_fifo_put(&output_buffer, ' ');
		char_fifo_put(&output_buffer, c);
	}

	if (output_buffer.length > 0) { 
		console->ier.field.etbei = 1;
	}

	return 0;		// Success code

}

int console_print_string(const char* text) {

	while (text[0] != '\0') {
		if(console_put_c(text[0])) {
			return -1; // Fail code, could not print enitre string
		}
		++text;
	}
	
	return 0;		// Success code
}

int console_print_int(int number) {

	if (number < 0) {
		console_put_c('-');
		number *= -1;
	}
	if (number < 10) {
		console_put_c('0' + number);
	}else{
		console_print_int(number/10);
		console_put_c('0' + number % 10);
	}

	return 0; // Success code
}

int console_store_c(char c){

	if ( c == 8 && input_req.index > 0) {
		// Backspace 
		input_req.index--;
		console_put_c(c);
	} else if  (c == '\r'){
		// Return
		input_req.save_spot[input_req.index] = '\0';
		console_put_c(c);
		return 1;
	} else if (input_req.index < input_req.length && c != 8){
		// Normal chars
		input_req.save_spot[input_req.index] = c;
		input_req.index++;
		console_put_c(c);
	} else {
		// Do nothing, no space left to store in
	}

	return 0;
}

int console_read_line(char* text, int max) {

	uint32_t pid = scheduler_get_current_pid();

	input_queue_put(&input_queue, pid, text, max-1);

	if(!input_in_progress) {
		input_in_progress = 1;
		input_queue_get(&input_queue, &input_req);
	}

	scheduler_block(pid);	

	return 0;

}

void console_handle_interrupt() {

	char c;

	// Key pressed
	if (console->lsr.field.dr) {
		c = console->rbr;
		if (input_in_progress) {
			if (console_store_c(c)) {
				scheduler_unblock(input_req.requester);
				if (input_queue_get(&input_queue, &input_req)) {
					input_in_progress = 0;
				}
			}
		}
	}

	// Buffered char to send to console
	if (output_buffer.length > 0 && console->lsr.field.thre) {
		console->thr = char_fifo_get(&output_buffer);
		if (output_buffer.length == 0) {
			console->ier.field.etbei = 0;
		}
	}

}
