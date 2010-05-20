#ifndef __OG_STDLIB__
#define __OG_STDLIB__

int og_parse_int(char* text, int* n);
int og_string_equals(char* a, char* b);

void og_string_concat(char *buffer, char *a, char *b);
void og_int_to_string(char *buffer, int i);

#endif
