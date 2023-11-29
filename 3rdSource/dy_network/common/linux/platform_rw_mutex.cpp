#include "platform_rw_mutex.h"


PlatformRwMutex::PlatformRwMutex()
{
    pthread_rwlock_init(&_rw_lock, NULL);
}

PlatformRwMutex::~PlatformRwMutex()
{
	pthread_rwlock_destroy(&_rw_lock);
}

void PlatformRwMutex::read_lock()
{
    pthread_rwlock_rdlock(&_rw_lock);
}

void PlatformRwMutex::write_lock()
{
    pthread_rwlock_wrlock(&_rw_lock);
}

void PlatformRwMutex::read_unlock()
{
    pthread_rwlock_unlock(&_rw_lock);
}

void PlatformRwMutex::write_unlock()
{
    pthread_rwlock_unlock(&_rw_lock);
}


