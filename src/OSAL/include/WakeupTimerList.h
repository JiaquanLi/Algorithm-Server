//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2018
//---------------------------------------------------------------------------

#ifndef SRC_OSAL_SRC_WAKEUPTIMERLIST_H_
#define SRC_OSAL_SRC_WAKEUPTIMERLIST_H_

#include <vector>
#include <mutex>
#include "timeout.h"

class WakeupTimerList {
public:
	WakeupTimerList();
	virtual ~WakeupTimerList();

	void Queue(CTimeoutRealmS * timer);
	void Dequeue(CTimeoutRealmS * timer);

	uint32_t GetNextWakeupTime(void);

private:
	std::mutex mMutex;
	std::vector<CTimeoutRealmS *> m_pList;
};

#endif /* SRC_OSAL_SRC_WAKEUPTIMERLIST_H_ */
