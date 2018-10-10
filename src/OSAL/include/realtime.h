/*
 * realtime.h
 *
 *  Created on: Jun 7, 2016
 *      Author: honeywell
 */

#ifndef SRC_REALTIME_H_
#define SRC_REALTIME_H_

#define PRIORITY_SLEEP_THREAD		99

#define PRIORITY_SIGNALING_THREAD  40
#define PRIORITY_POWERMANAGER_THREAD  39

#define PRIORITY_TRIGGER_MODE_MANAGER_THREAD  35
#define PRIORITY_KEY_LISTENER_THREAD  30

#define PRIORITY_BTSTACK_THREAD 27

#define PRIORITY_CAPTURE_THREAD    20
#define PRIORITY_BARCODE_PROCESS_MANAGER_THREAD  18
#define PRIORITY_FRAMERATE_EVT_MANAGER_THREAD	15
#define PRIORITY_FLDIQ_DECODER_THREAD  10
#define PRIORITY_USB_DEVICE_STS_THREAD  50

int set_sched_fifo(int priority);
int set_sched_other(int priority);
int get_sched_priority(int *priority);
int set_sched_idle(int priority);

void set_thread_name(const char *name);
const char * get_thread_name();

#endif /* SRC_REALTIME_H_ */
