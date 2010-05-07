#include "malta_display.h"

static volatile malta_display_t* const malta = (malta_display_t*) 0xbf000400;

void malta_display_init() {

	malta->ledbar.reg = 0xFF;

}

int malta_display_c(char c, int pos) {

	if (c) {
		malta->asciipos[pos].value = c;	
	} else {
		malta->asciipos[pos].value = ' ';	
	}

	return 0;

}

int malta_display_int(int n) {

	int i, negative = 0;

	if(n < 0) {
		negative = 1;
		n *= -1;
	}

	for (i = 7; i >= 0; i--) {
		if(negative && !n) {
			negative = 0;
			malta_display_c('-', i);
		} else if (!n) {
			malta_display_c(' ', i);
		} else {
			malta_display_c('0' + n % 10, i);
		}
		n /= 10;
	}

	return 0;
}

int malta_display_string(const char* text) {
	
	int i, ended = 0;

	for (i = 0; i < 8; i++) {
		if (text[i] && !ended) {
			malta_display_c(text[i], i);
		} else {
			ended = 1;
			malta_display_c(' ', i);
		}
	}

	return 0;
}
