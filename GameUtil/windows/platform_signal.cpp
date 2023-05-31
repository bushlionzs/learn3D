#include "platform_signal.h"

PlatformCond::PlatformCond()
{

}


PlatformCond::~PlatformCond()
{
	
}


void PlatformCond::wait(std::unique_lock<std::mutex>& lock)
{
    _cond.wait(lock);
}

void PlatformCond::signal()
{
    _cond.notify_one();
}