#include "syscall.h"
#include "api.h"
#include "console.h"
#include "scheduler.h"
#include "types.h"

int og_print_string(const char* text) {
	return og_syscall((uint32_t) console_print_string, (uint32_t) text, 0, 0);
}

int og_read_line(char* text, int max) {
	return og_syscall((uint32_t) console_read_line, (uint32_t) text, (uint32_t) max, 0);
}

int og_kill(uint32_t pid, uint32_t exit_code) {
	return og_syscall((uint32_t) scheduler_kill, pid, exit_code, 0);
}

int og_exit(uint32_t exit_code) {
	return og_syscall((uint32_t) scheduler_exit, exit_code, 0, 0);
}
