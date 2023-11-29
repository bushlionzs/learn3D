#pragma once


#ifdef _WIN32
#include <winsock2.h>
namespace dy
{
namespace common
{

    using pid_t = DWORD;

    inline pid_t getpid()
    {
        return GetCurrentProcessId();
    }
    inline DWORD gettid()
    {
        return GetCurrentThreadId();
    }

	inline int platform_get_nprocs()
	{
		return 0;
	}

    inline void closepid(pid_t id)
    {
        HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
        ::TerminateProcess(h, 0);
        ::CloseHandle(h);
    }

    inline void closeself()
    {
        HANDLE h = ::GetCurrentProcess();
        ::TerminateProcess(h, 0);
    }
}
}
#else
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>

#ifdef __APPLE__
#include <pthread.h>
#else
#include <sys/sysinfo.h>
#endif

namespace dy
{
namespace common
{
#ifdef __APPLE__
typedef unsigned int pid_t;
#else
typedef __pid_t pid_t;
#endif
    
inline pid_t getpid()
{
	return ::getpid();
}
    // getpid
inline pid_t gettid() {
#ifdef __APPLE__
    return pthread_mach_thread_np(pthread_self());
#else
    return syscall(__NR_gettid);
#endif
}

inline int platform_get_nprocs()
{
#ifdef __APPLE__
    return 1;
#else
#if defined(__ANDROID__)
    return 1; //return get_nprocs();
#else
    return get_nprocs();
#endif
#endif
}

inline void closepid(pid_t id)
{
    kill(id, SIGTERM);
}

inline void closeself()
{
    exit(0);
}

}  
}
#endif
