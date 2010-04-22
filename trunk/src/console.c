#include <console.h>
#include <ns16550.h>

static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;

void console_putc(char c) {
  // Poll until ready to transmit.
  while (!console->lsr.field.thre) {}		

  // Write character to Transmitter Holding Register
  console->thr = c;

  if(c=='\n') {     while (!console->lsr.field.thre) {}
    console->thr = '\r';
  }	    
	  
}

void console_print_string(const char* text) {
  while (text[0] != '\0') {
    console_putc(text[0]);
    ++text;
  }
}
