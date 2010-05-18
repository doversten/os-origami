#ifndef __OG_STDLIB__
#define __OG_STDLIB__

uint32_t og_random();
void og_seed(uint32_t seed);
int og_parse_int(char* text, int* n);
int og_string_equals(char* a, char* b);

#endif
