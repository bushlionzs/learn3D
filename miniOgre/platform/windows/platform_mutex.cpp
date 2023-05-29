#define THIS_MODULE MODULE_NETWORK
#include "platform_mutex.h"


PlatformMutex::PlatformMutex()
{
	InitializeCriticalSection( &m_cs );
}

PlatformMutex::~PlatformMutex()
{
	DeleteCriticalSection( &m_cs );
}

void PlatformMutex::lock()
{
	EnterCriticalSection( &m_cs);
}

bool PlatformMutex::tryLock()
{
	return TryEnterCriticalSection( &m_cs) != 0;
}

void PlatformMutex::unlock()
{
	LeaveCriticalSection( &m_cs);
}


