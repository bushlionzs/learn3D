#include "platform_rw_mutex.h"


PlatformRwMutex::PlatformRwMutex()
{
    InitializeSRWLock(&_srw);
}

PlatformRwMutex::~PlatformRwMutex()
{
}

void PlatformRwMutex::read_lock()
{
    AcquireSRWLockShared(&_srw);
}

void PlatformRwMutex::write_lock()
{
    AcquireSRWLockExclusive(&_srw);
}

void PlatformRwMutex::read_unlock()
{
    ReleaseSRWLockShared(&_srw);
}

void PlatformRwMutex::write_unlock()
{
    ReleaseSRWLockExclusive(&_srw);
}


