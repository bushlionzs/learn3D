#include <platform_thread.h>
#include <platform.h>
#ifdef _WIN32
#include <process.h>
#include <windows.h>
#else

#ifdef __APPLE__
//#include <sys/prctl.h>
#else
#include <sys/prctl.h>
#endif
#endif
struct ThreadPriData
{
	ThreadData		m_PriData;
};
#ifdef _WIN32
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // must be 0x1000
	LPCSTR szName; // pointer to name (in user addr space)
	DWORD dwThreadID; // thread ID (-1=caller thread)
	DWORD dwFlags; // reserved for future use, must be zero
} THREADNAME_INFO;

void SetThreadName(DWORD thread_id, const char* name)
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = name;
	info.dwThreadID = thread_id;
	info.dwFlags = 0;

	__try
	{
		RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), reinterpret_cast<DWORD_PTR*>(&info));
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}
#endif
static void* WindowsThreadFunc(void* obj)
{
	ThreadPriData* data = (ThreadPriData*)obj;
#ifdef _WIN32
	if (data->m_PriData._name[0] != 0)
	{
		SetThreadName(-1, data->m_PriData._name);
	}
#elif __APPLE__
    
#else
    if (data->m_PriData._name[0] != 0)
    {
        prctl(PR_SET_NAME, data->m_PriData._name);
    }
#endif

	data->m_PriData.threadfunc(data->m_PriData._param);

	delete data;
	return 0;
}


std::shared_ptr<Thread> PlatformRunThread(const ThreadData& data)
{
    ThreadPriData* newdata = new ThreadPriData();
    newdata->m_PriData = data;
    std::shared_ptr<Thread> dummy = std::make_shared<Thread>(WindowsThreadFunc, newdata);
    return dummy;
}
