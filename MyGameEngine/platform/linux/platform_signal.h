#ifndef __PLATFORM_SIGNAL_H__
#define __PLATFORM_SIGNAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <condition_variable>
#include <platform_mutex.h>

class PlatformCond
{
public:
	void wait(std::unique_lock<std::mutex>& lock);
	void signal();
private:
	std::condition_variable  _cond;
};
#endif //__PLATFORM_SIGNAL_H__
