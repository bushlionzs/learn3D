#ifndef __PLATFORM_SIGNAL_H__
#define __PLATFORM_SIGNAL_H__

#include <stdint.h>
#include <mutex>
#include <condition_variable>
class PlatformCond
{
public:
	PlatformCond();

	~PlatformCond();

public:
    void wait(std::unique_lock<std::mutex>& lock);
	void signal();
private:
    std::condition_variable  _cond;
};
#endif //__PLATFORM_SIGNAL_H__