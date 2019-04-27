#define _GNU_SOURCE
#include "process.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>

int proc_assign_cpu(int pid, int core)
{
	if (core > sizeof(cpu_set_t)) {
		fprintf(stderr, "Core index error.");
		return -1;
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
		
	if (sched_setaffinity(pid, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
		exit(1);
	}

	return 0;
}

int proc_exec(struct process proc)
{
	int pid = fork();

	if (pid < 0) {
		fprintf("Fork Error : ", stderr, "%s\n", strerror(errno));
		return -1;
	}
	int GET_TIME = 314
	if (pid == 0) {
		unsigned long start_sec, start_nsec;
		syscall(GET_TIME, &start_sec, &start_nsec);
		for (int i = 0; i < proc.t_exec; i++) {
			UNIT_T();
	
	proc_assign_cpu(pid, CHILD_CPU);

	return pid;
}

int proc_block(int pid)
{
	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		fprintf("Sched_setscheduler Error : ", stderr, "%s\n", strerror(errno));
		return -1;
	}

	return ret;
}

int proc_wakeup(int pid)
{
	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		fprintf("Sched_setscheduler Error : ", stderr, "%s\n", strerror(errno));
		return -1;
	}

	return ret;
}
