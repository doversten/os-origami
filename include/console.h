#ifndef __CONSOLE__
#define __CONSOLE__

#include "types.h"

void console_putc(char c);
void console_print_string(const char* text);
void console_print_int(uint32_t number);
void console_handle_interrupt();

#endif
