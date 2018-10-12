#ifndef SYINCHRONIZATION_H
#define SYINCHRONIZATION_H

#include <mutex>
#include <thread>

#define INFINITE -1
typedef std::timed_mutex * MT_Mutex_t;

inline void MT_Delay(int t)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

inline  MT_Mutex_t MT_CreateMutex(bool xxx)
{
	return new std::timed_mutex();
}

inline  void MT_CloseMutex(MT_Mutex_t mtx)
{
	delete mtx;
}

inline bool MT_WaitMutex(MT_Mutex_t mtx, int delay)
{
	if(delay == INFINITE)
	{
		mtx->lock();
		return true;
	}
	else
	{
		return mtx->try_lock_for(std::chrono::milliseconds(delay));
	}
}
inline bool MT_ReleaseMutex(MT_Mutex_t mtx)
{
	mtx->unlock();
	return true;
}
#endif

