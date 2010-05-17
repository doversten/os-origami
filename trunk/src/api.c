#include "syscall.h"
#include "api.h"
#include "console.h"
#include "scheduler.h"
#include "types.h"
#include "malta_display.h"
#include "message_pool.h"
#include "message.h"

int og_print_string(const char* text) {
	return og_syscall((uint32_t) console_print_string, (uint32_t) text, 0, 0);
}

int og_print_int(int i) {
	return og_syscall((uint32_t) console_print_int, (uint32_t) i, 0, 0);
}

int og_read_line(char* text, int max) {
	return og_syscall((uint32_t) console_read_line, (uint32_t) text, (uint32_t) max, 0);
}

int og_display_string(const char* text) {
	return og_syscall((uint32_t) malta_display_string, (uint32_t) text, 0, 0); 
}

int og_display_int(int n) {
	return og_syscall((uint32_t) malta_display_int, (uint32_t) n, 0, 0); 
}

int og_spawn(void (*code)(), uint32_t priority) {
	return og_syscall((uint32_t) scheduler_create_process, (uint32_t) code, priority, 0);
}

int og_kill(uint32_t pid, uint32_t exit_code) {
	return og_syscall((uint32_t) scheduler_kill, pid, exit_code, 0);
}

int og_exit(uint32_t exit_code) {
	return og_syscall((uint32_t) scheduler_exit, exit_code, 0, 0);
}

int og_sleep(int ticks) {
	return og_syscall((uint32_t) scheduler_sleep, (uint32_t) ticks, 0, 0);
}

int og_set_priority(uint32_t pid, uint32_t priority) {
	return og_syscall((uint32_t) scheduler_set_priority, pid, priority, 0);
}





/*
	pre: spot is empty
 */
int og_read_msg(char type, message_t *spot, int timeout) {
	return og_syscall((uint32_t) message_pool_read, (uint32_t) type, (uint32_t) spot,(uint32_t) timeout);
}

int og_send_msg(uint32_t receiver, char type, uint32_t data) {
	return og_syscall((uint32_t) message_pool_send, receiver, (uint32_t) type, data);
}

