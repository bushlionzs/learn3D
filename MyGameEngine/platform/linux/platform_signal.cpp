#include "platform_signal.h"

void PlatformCond::wait(std::unique_lock<std::mutex>& lock)
{	
	_cond.wait(lock);
}

void PlatformCond::signal()
{
	_cond.notify_one();
}
