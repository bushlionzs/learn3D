#ifndef __SCOPEDLOCK_H__
#define __SCOPEDLOCK_H__
#include <platform_log.h>
#include <pid.h>

#define SCOPE_LOCK_MACRO(mutex) \
    ScopedLock<PlatformMutex> lock(mutex);

template <class M>
class ScopedLock
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex (and optionally
	/// a timeout value in milliseconds) and locks it.
	/// The destructor unlocks the mutex.
{
public:
    explicit ScopedLock(M& mutex) : _mutex(mutex)
    {
        _mutex.lock();
    }

    explicit ScopedLock(M& mutex, const char* file, int line) : _mutex(mutex)
    {
        _str_pos.append("[thread:");
        _str_pos.append(std::to_string(dy::common::gettid()));
        _str_pos.append("]");
        _str_pos.append(file);
        _str_pos.append(":");
        _str_pos.append(std::to_string(line));
        NOTICE_LOG("lock mutex from %s, ptr is %p", _str_pos.c_str(), &_mutex);
        _mutex.lock();
    }
	
	~ScopedLock()
	{
        if (!_str_pos.empty())
        {
            NOTICE_LOG("unlock mutex from %s, ptr is %p", _str_pos.c_str(), &_mutex);
        }
        
		_mutex.unlock();//lint !e1551
	}
private:
	ScopedLock& operator = ( const ScopedLock& obj )
	{
		return *this;
	}

	M& _mutex;
    std::string _str_pos;
};

template <class M>
class SharedLock
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex (and optionally
	/// a timeout value in milliseconds) and locks it.
	/// The destructor unlocks the mutex.
{
public:
	explicit SharedLock(M& mutex): _mutex(mutex)
	{
		_mutex.read_lock();
	}
	
	~SharedLock()
	{
		_mutex.read_unlock();//lint !e1551
	}
private:
	SharedLock& operator = ( const SharedLock& obj )
	{
		return *this;
	}

	M& _mutex;
};

template <class M>
class UniqueLock
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex (and optionally
	/// a timeout value in milliseconds) and locks it.
	/// The destructor unlocks the mutex.
{
public:
	explicit UniqueLock(M& mutex): _mutex(mutex)
	{
		_mutex.write_lock();
	}
	
	~UniqueLock()
	{
		_mutex.write_unlock();//lint !e1551
	}
private:
	UniqueLock& operator = ( const UniqueLock& obj )
	{
		return *this;
	}

	M& _mutex;
};

#endif //__SCOPEDLOCK_H__
