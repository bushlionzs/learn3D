#pragma once

#include <pthread.h>

class  PlatformRwMutex
{
public:
    PlatformRwMutex();
	~PlatformRwMutex();
	void read_lock();
    void write_lock();
	void read_unlock();
    void write_unlock();
private:
    pthread_rwlock_t _rw_lock;
};
