/*
 * htime.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: honeywell
 */

#include <time.h>
#include "htime.h"

uint64_t get_time_us(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	uint64_t t = ts.tv_sec * 1000000LL + ts.tv_nsec / 1000LL;
	return t;
}

/**
 * @return current monotonic time in ms
 */
uint64_t get_time_ms(ClockType_t type)
{
	struct timespec spec;
	clockid_t id = CLOCK_MONOTONIC;
	if(type == BOOTTIME)
		id = CLOCK_BOOTTIME;
	clock_gettime(id, &spec);
	uint64_t ms = spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
	return ms;
}

