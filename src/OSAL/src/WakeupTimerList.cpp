//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2018
//---------------------------------------------------------------------------

#include <iterator>
#include <algorithm>
#include "WakeupTimerList.h"

WakeupTimerList::WakeupTimerList() {

}

WakeupTimerList::~WakeupTimerList() {
	std::unique_lock<std::mutex> lk(mMutex);
	m_pList.clear();
}

void WakeupTimerList::Queue(CTimeoutRealmS * timer) {
	if(timer == NULL) {
		return;
	}

	{
		std::unique_lock<std::mutex> lk(mMutex);
		std::vector<CTimeoutRealmS *>::iterator it;
		it = std::find(m_pList.begin(), m_pList.end(), timer);
		if (it == m_pList.end()) {
			m_pList.push_back(timer);
		}
	}
}

void WakeupTimerList::Dequeue(CTimeoutRealmS * timer) {
	if(timer == NULL) {
		return;
	}

	{
		std::unique_lock<std::mutex> lk(mMutex);
		std::vector<CTimeoutRealmS *>::iterator it;
		it = std::find(m_pList.begin(), m_pList.end(), timer);
		if(it != m_pList.end()) {
			m_pList.erase(it);
		}
	}
}

uint32_t WakeupTimerList::GetNextWakeupTime(void) {
	uint32_t wakeup_time = 0;

	{
		std::unique_lock<std::mutex> lk(mMutex);
		std::vector<CTimeoutRealmS *>::iterator it = m_pList.begin();
		while(it != m_pList.end()) {
			CTimeoutRealmS * pTimer = *it;
			uint32_t reset_time = pTimer->GetRestTime();

			if(reset_time > 0) {
				if(wakeup_time == 0) {
					wakeup_time = reset_time;
				} else if(wakeup_time > reset_time) {
					wakeup_time = reset_time;
				}
			}

			it++;
		}
	}

	return wakeup_time;
}
