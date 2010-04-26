#include <console.h>
#include <ns16550.h>
#include <bounded_fifo.h>

static volatile ns16550_t* const console = (ns16550_t*) 0xb80003f8;
static bounded_fifo_t bfifo;
static char reading = 0;
void console_putc(char c) {

  //FULDEBUG
  while(bfifo.length >= FIFO_SIZE) {};

  if(c=='\r') { 
    bfifo_put(&bfifo, '\n');
  }

  bfifo_put(&bfifo, c);

  if(c=='\n') { 
    bfifo_put(&bfifo, '\r');
  }

  if(c==8) { //if c = backspace
    bfifo_put(&bfifo, 32);
    bfifo_put(&bfifo, c);
  }

  console->ier.field.etbei = 1;
	  
}

void console_print_string(const char* text) {
  while (text[0] != '\0') {
    console_putc(text[0]);
    ++text;
  }
}

void console_print_int(uint32_t number) {
  if (number < 10) {
    console_putc('0' + number);
  }else{
    console_print_int(number/10);
    console_putc('0' + number % 10);
  }
}

void console_handle_interrupt() {

  char c;

  //console_print_string("Console interrupt!\n");
  if (console->lsr.field.dr) {
    c = console->rbr;
    console_putc(c);
  }
  if (bfifo.length > 0 && console->lsr.field.thre) {
	console->thr = bfifo_get(&bfifo);
	if (bfifo.length == 0) {
          console->ier.field.etbei = 0;
        }
  }



  //console->ier.field.etbei = 0;
  //kset_cause(~0x1000, 0);

}

void console_read_line(char* text) {
  int i = 0;
  reading = 1;
  while(1) {
    	
  }	

}
