#ifndef __CONSOLE__
#define __CONSOLE__

#include "types.h"

// Prints a character to the console.
int console_putc(char c);
// Prints a string to the console.
int console_print_string(const char* text);
// Prints an int to the console.
int console_print_int(int number);
// Handle interupt for console i.e. handles input and output.
void console_handle_interrupt();

#endif
