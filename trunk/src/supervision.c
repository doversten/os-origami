#include "pcb.h"
#include "scheduler.h"
#include "supervision.h"

int supervise(uint32_t pid) {
	pcb_t *pcb = pcb_get_with_pid(pid);
	if (!pcb) {
		return -1;
	}
	if (pcb->status.field.empty) {
		return -2;
	}
	if (pcb->status.field.supervised) {
		return -3;
	}
	pcb->status.field.supervised = 1;
	pcb->supervisor = scheduler_get_current_pid();
	return 0;
}

int unsupervise(uint32_t pid) {
	pcb_t *pcb = pcb_get_with_pid(pid);
	if (!pcb) {
		return -1;
	}
	if (pcb->status.field.empty) {
		return -2;
	}
	if (!pcb->status.field.supervised) {
		return -3;
	}	
	if (pcb->supervisor != scheduler_get_current_pid()) {
		return -4;
	}
	pcb->status.field.supervised = 0;
	return 0;
}
