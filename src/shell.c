#include "../include/shell.h"
#include "fibonacci.c"
#include "increment.c"

void thotin(){
	og_print_string("Welcome to thotin, write 'EXIT' to exit the shell!\n\n");
	shell();
}

int compare(char* a, char* b){
	int i = 0;
	while(a[i]&&b[i]){
		if (a[i]!=b[i]){
			return 0;
		}
		i++;
	}
	
	if (a[i] || b[i]) {
		return 0;
	}

	return 1;
}

void shell(){
	char input[256];
	og_print_string("thotin > ");
	og_read_line(input, 256);
	parser(input);
}

int parser_int (char* a){
	int i = 0;
	int ack = 0;
	
	while(a[i]) {
		ack = ack * 10 + (a[i] - '0');
		i++;
	}
	return ack;
}

void parser (char* input){

	if (compare(input, "inc")) {
		og_print_string("Print the number you want to increment to: ");
		char text[8];
		og_read_line(text, 8);
		int number = parser_int(text);
		inc(number);
		
	} else if (compare(input, "fib")) {
		og_print_string("Print the number of fibonacci you want to calculate: ");
		char text[8];
		og_read_line(text, 8);
		int number = parser_int(text);
		fib(number);
	} else if (compare(input, "exit") || compare(input, "EXIT")) {
		og_print_string("Bye bye! Thank you for folding...\n");
		og_exit(0);
	}  else if (compare(input, "thotin")) {
		thotin();
	} else {
		og_print_string(input);
		og_print_string(": not found\n");
	}
	

	shell();
}







