#ifndef __PLATFORMMUTEX_H__
#define __PLATFORMMUTEX_H__

#include <WinSock2.h>
#include <windows.h>

class  PlatformMutex
{
public:
	PlatformMutex();
	~PlatformMutex();
	void lock();
	bool tryLock();
	void unlock();
	CRITICAL_SECTION * get_cs()
	{
		return &m_cs;
	}
private:
	CRITICAL_SECTION m_cs;
};

#endif //__PLATFORMMUTEX_H__