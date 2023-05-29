#include "Basics.h"

#if defined(__WINDOWS__)

class MiniLock
{
	CRITICAL_SECTION	m_Lock;

public:
	BOOL	mStatus;
	MiniLock()
	{
		InitializeCriticalSection(&m_Lock);
		mStatus = FALSE;
	}
	~MiniLock()
	{
		DeleteCriticalSection(&m_Lock);
	}
	void Lock()
	{
		EnterCriticalSection(&m_Lock);
		mStatus = TRUE;
	}
	void Unlock()
	{
		LeaveCriticalSection(&m_Lock);
		mStatus = FALSE;
	}
};

#elif defined(__LINUX__)

class	MiniLock
{
	pthread_mutex_t m_Mutex;
public:
	BOOL	mStatus;

	MiniLock()
	{
		pthread_mutex_init(&m_Mutex, NULL);
		mStatus = FALSE;
	}
	~MiniLock()
	{
		pthread_mutex_destroy(&m_Mutex);
	}
	void Lock()
	{
		pthread_mutex_lock(&m_Mutex);
		mStatus = TRUE;
	}
	void Unlock()
	{
		pthread_mutex_unlock(&m_Mutex);
		mStatus = FALSE;
	}
};

#endif


template<typename Mutex>
class minilock_guard
{
private:
	Mutex			&m;
	explicit		minilock_guard(minilock_guard &);
	minilock_guard &operator	=(minilock_guard &);
public:
	explicit minilock_guard(Mutex &m_) :
	m(m_)
	{
		m.Lock();
	}
	~minilock_guard(void)
	{
		m.Unlock();
	}
};
