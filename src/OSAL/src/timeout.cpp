/*
 * timeout.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: honeywell
 */

#include "WakeupTimerList.h"

void CTimeoutRealmS::SetWakeupHandler(WakeupTimerList * handler) {
	wakeup_handler = handler;
}

WakeupTimerList * CTimeoutRealmS::wakeup_handler = NULL;


void CTimeoutRealmS::setwakeup (bool enable)
{
	if(enable) {
		if(wakeup_handler) {
			wakeup_handler->Queue(this);
		}
	} else {
		if(wakeup_handler) {
			wakeup_handler->Dequeue(this);
		}
	}
}
