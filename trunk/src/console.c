#include "console.h"
#include "ns16550.h"
#include "bounded_fifo.h"
#include "scheduler.h"

#define PRINT_BUFFER_NORMAL 0
#define PRINT_BUFFER_INPUT 1

static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;
static bounded_fifo_t bfifo[2];
static int input_in_progress;
static char* input_string;
static int input_index;
static int input_index_max;
static uint32_t input_pid;

int console_put_c(char c, int buffer) { 

	if (bfifo[buffer].length >= FIFO_SIZE) {
		return -1; // Fail code, unable to buffer char
	}

	if(c=='\r') { 
		bfifo_put(&bfifo[buffer], '\n');
	}

	bfifo_put(&bfifo[buffer], c);

	if(c=='\n') { 
		bfifo_put(&bfifo[buffer], '\r');
	}

	if(c==8) { //if c = backspace
		bfifo_put(&bfifo[buffer], 32);
		bfifo_put(&bfifo[buffer], c);
	}

	if (!(buffer == PRINT_BUFFER_NORMAL && input_in_progress)) { 
		console->ier.field.etbei = 1;
	}

	return 0;		// Success code

}

int console_print_string(const char* text) {

	while (text[0] != '\0') {
		if(console_put_c(text[0], PRINT_BUFFER_NORMAL)) {
			return -1; // Fail code, could not print enitre string
		}
		++text;
	}
	
	return 0;		// Success code
}

int console_print_int(int number) {

	if (number < 0) {
		console_put_c('-', PRINT_BUFFER_NORMAL);
		number *= -1;
	}
	if (number < 10) {
		console_put_c('0' + number, PRINT_BUFFER_NORMAL);
	}else{
		console_print_int(number/10);
		console_put_c('0' + number % 10, PRINT_BUFFER_NORMAL);
	}

	return 0; // Success code
}

int console_store_c(char c){

	if ( c == 8 && input_index > 0) {
		// Backspace 
			input_index--;
			console_put_c(c, PRINT_BUFFER_INPUT);
	} else if  (c == '\r'){
		// Return
		input_string[input_index] = NULL;
		console_put_c(c, PRINT_BUFFER_INPUT);
		return 1;
	} else if (input_index <= input_index_max && c != 8){
		// Normal chars
		input_string[input_index] = c;
		input_index++;
		console_put_c(c, PRINT_BUFFER_INPUT);
	}
	
	return 0;
}


void console_handle_interrupt() {

	char c;

	// Key pressed
	if (console->lsr.field.dr) {
		c = console->rbr;
		if (input_in_progress) {
			if (console_store_c(c)) {
				input_in_progress = 0;
				scheduler_unblock(input_pid);
			}
		}
	}
	// Buffered char to send to console
	/*if (bfifo[print_buffer_active].length > 0 && console->lsr.field.thre) {
		console->thr = bfifo_get(&bfifo[print_buffer_active]);
		if (bfifo[print_buffer_active].length == 0) {
			console->ier.field.etbei = 0;
		}
	}*/

	if (bfifo[PRINT_BUFFER_INPUT].length > 0 && console->lsr.field.thre) {
		console->thr = bfifo_get(&bfifo[PRINT_BUFFER_INPUT]);
		if (bfifo[PRINT_BUFFER_INPUT].length == 0 && input_in_progress) {
			console->ier.field.etbei = 0;
		}
	} else if (!input_in_progress && bfifo[PRINT_BUFFER_NORMAL].length > 0 && console->lsr.field.thre) {
		console->thr = bfifo_get(&bfifo[PRINT_BUFFER_NORMAL]);
	}

	if (bfifo[PRINT_BUFFER_INPUT].length == 0 && bfifo[PRINT_BUFFER_NORMAL].length == 0) {
		console->ier.field.etbei = 0;
	}

	//console->ier.field.etbei = 0;
	//kset_cause(~0x1000, 0);
}

int console_read_line(char* text, int max) {

	if(input_in_progress) {
		return -1;
	}

	input_index_max = max-2;
	input_in_progress = 1;
	input_index = 0;
	input_string = text;
	input_pid = scheduler_get_current_pid();
	
	scheduler_block(input_pid);

	return 0;

}


