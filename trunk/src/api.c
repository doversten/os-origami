#include "syscall.h"
#include "api.h"
#include "console.h"
#include "scheduler.h"
#include "types.h"
#include "malta_display.h"
#include "message_pool.h"
#include "message.h"
#include "random.h"
#include "supervision.h"
#include "pids.h"

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

int og_spawn(void (*code)(), uint32_t argument, uint32_t priority) {
	return og_syscall((uint32_t) scheduler_create_process, (uint32_t) code, argument, priority);
}

int og_kill(uint32_t pid) {
	return og_syscall((uint32_t) scheduler_kill, pid, -1, 0);
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


uint32_t og_get_pid(){
	return og_syscall((uint32_t) scheduler_get_current_pid, 0, 0, 0);
}


// Pseudo-random functions
uint32_t og_random(uint32_t min, uint32_t max) {
	return og_syscall((uint32_t) random, min, max, 0);
}

int og_random_seed(uint32_t seed) {
	return og_syscall((uint32_t) random_seed, seed, 0, 0);
}

// Time functions
uint32_t og_system_clock() {
	return og_syscall((uint32_t) scheduler_system_clock, 0, 0, 0);
}

// Supervision functions
int og_supervise(uint32_t pid) {
	return og_syscall((uint32_t) supervise, pid, 0, 0);
}

int og_unsupervise(uint32_t pid) {
	return og_syscall((uint32_t) unsupervise, pid, 0, 0);
}

int og_wait(message_t *spot, int timeout) {
	return og_syscall((uint32_t) message_pool_read, (uint32_t) 't', (uint32_t) spot,(uint32_t) timeout);
}

// Process information
int og_get_pids(pids_t *pids) {
	return og_syscall((uint32_t) pcb_get_pids, (uint32_t) pids, 0, 0);
}

int og_get_process_name(uint32_t pid, char* name, int nameSize) {
	return og_syscall((uint32_t) pcb_get_name, pid, (uint32_t) name, (uint32_t) nameSize);
}

int og_get_priority(uint32_t pid){
	return og_syscall((uint32_t) pcb_get_priority, (uint32_t) pid, 0, 0);
}

int og_get_scheduler_state(uint32_t pid){
	return og_syscall((uint32_t) scheduler_get_state, (uint32_t) pid, 0, 0);
}
