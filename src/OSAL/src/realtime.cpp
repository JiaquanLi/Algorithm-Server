/*
 * realtime.c
 *
 *  Created on: Jun 7, 2016
 *      Author: honeywell
 */

#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/resource.h>

#include "logging.h"
#include "realtime.h"

#define LOG_TAG "realtime"

/*
 * Raise the soft priority limit up to prio, if that is less than or equal
 * to the hard limit
 * if a call fails, return the error
 * if successful return 0
 * if fails, return -1
 */
static int raise_soft_prio(int policy, const struct sched_param *param)
{
	int err;
	int policy_max;	/* max for scheduling policy such as SCHED_FIFO */
	int soft_max;
	int hard_max;
	int prio;
	struct rlimit rlim;

	prio = param->sched_priority;

	policy_max = sched_get_priority_max(policy);
	if (policy_max == -1) {
		err = errno;
		log_print(LOG_ERR,LOG_TAG, "sched_get_priority_max #%d: %s\n", err, strerror(err));
		return err;
	}

	err = getrlimit(RLIMIT_RTPRIO, &rlim);
	if (err) {
		err = errno;
		log_print(LOG_ERR,LOG_TAG, "getrlimit #%d: %s\n", err, strerror(err));
		return err;
	}

	soft_max = (rlim.rlim_cur == RLIM_INFINITY) ? policy_max : rlim.rlim_cur;
	hard_max = (rlim.rlim_max == RLIM_INFINITY) ? policy_max : rlim.rlim_max;

	if (prio > soft_max && prio <= hard_max) {
		rlim.rlim_cur = prio;
		err = setrlimit(RLIMIT_RTPRIO, &rlim);
		if (err) {
			err = errno;
			log_print(LOG_ERR,LOG_TAG, "setrlimit #%d: %s\n", err, strerror(err));
			/* return err; */
		}
	} else {
		err = -1;
	}

	return err;
}

/*
 * Check the error status of sched_setscheduler
 * If an error can be corrected by raising the soft limit priority to
 * a priority less than or equal to the hard limit, then do so.
 */
static int setscheduler(pid_t pid, int policy, const struct sched_param *param)
{
	int err = 0;

	try_again:
	err = sched_setscheduler(pid, policy, param);
	if (err) {
		err = errno;
		log_print(LOG_ERR,LOG_TAG, "sched_setscheduler #%d: %s\n", err, strerror(err));
		if (err == EPERM) {
			int err1;
			err1 = raise_soft_prio(policy, param);
			if (!err1) goto try_again;
		}
	}

	return err;
}

int set_sched_fifo(int priority)
{
	struct sched_param schedp;

	memset(&schedp, 0, sizeof(schedp));
	schedp.sched_priority = priority;

	return setscheduler(0, SCHED_FIFO, &schedp);
}

int set_sched_other(int priority)
{
	struct sched_param schedp;

	memset(&schedp, 0, sizeof(schedp));
	schedp.sched_priority = priority;

	return sched_setscheduler(0, SCHED_OTHER, &schedp);
}

int get_sched_priority(int *priority)
{
	int ret;
	struct sched_param schedp;
	ret = sched_getparam(0, &schedp);
	*priority = schedp.sched_priority;
	return ret;
}

static thread_local char thread_name[81];

void set_thread_name(const char *name)
{
	char shortname[16];
	const char *threadname;

	if(strlen(name) < 16) {
		threadname = name;
	} else {
		//Thread name length shall be smaller than 16
		memcpy(shortname, name, 15);
		shortname[15] = 0;
		threadname = shortname;
	}

	int res = pthread_setname_np(pthread_self(), threadname);
	if(res) {
		log_print(LOG_ERR,LOG_TAG, "set_thread_name failure:  %s (%d)\n", strerror(res), res);
	}

	strncpy(thread_name, name, sizeof(thread_name));
	thread_name[sizeof(thread_name)-1] = '\0';
}

const char * get_thread_name()
{
	return thread_name;
}

int set_sched_idle(int priority)
{
	struct sched_param schedp;

	memset(&schedp, 0, sizeof(schedp));
	schedp.sched_priority = priority;

	return sched_setscheduler(0, SCHED_IDLE, &schedp);
}
