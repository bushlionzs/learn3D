#ifndef __PLATFORMMUTEX_H__
#define __PLATFORMMUTEX_H__

#include <mutex>

class  PlatformMutex
{
public:
	void lock();
	void unlock();
	std::recursive_mutex& get_mutex()
    {
        return _mutex;
    }
private:
	std::recursive_mutex _mutex;
};

#endif //__PLATFORMMUTEX_H__
