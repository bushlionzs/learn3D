#include "platform_mutex.h"
#include <stdio.h>

void PlatformMutex::lock()
{
	_mutex.lock();
}

void PlatformMutex::unlock()
{
	_mutex.unlock();
}
