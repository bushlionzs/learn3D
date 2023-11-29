#pragma once

#include <WinSock2.h>
#include <windows.h>

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
    SRWLOCK _srw;
};
