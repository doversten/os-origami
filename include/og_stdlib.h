#ifndef __OG_STDLIB__
#define __OG_STDLIB__

// Some useful functions for user programs.

// String operaions
int og_parse_int(char* text, int* n);	// Makes a string representaion of a number in to an int
int og_string_equals(char* a, char* b); // Compares two strings and check if they are equal
void og_string_concat(char *buffer, char *a, char *b);	// Concatenate two strings into one
void og_int_to_string(char *buffer, int i);	// Turns an int into a string representation
void og_uint_to_string(char *buffer, uint32_t i);	// Turns an unsigned int into a string representation 
void og_fill_string(char *buffer, int max, char c);	// Fills a string to a size with a special char

#endif
