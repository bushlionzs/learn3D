#ifndef __PLATFORM_THREAD_H__
#define __PLATFORM_THREAD_H__

#include <stdint.h>
#include <string.h>
#include <thread>
#include <memory>

struct ThreadData
{
	void (*threadfunc)(void*);
	void* _param;
	uint32_t _module;
    char _name[16];
    ThreadData()
    {
        memset(_name, 0, sizeof(_name));
		_param = 0;
		_name[0] = 0;
		_module = 0;
    }
};

// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=55917
#if defined(__GNUC__) && __GNUC__ < 8
#include <pthread.h>
#include <system_error>

class Thread
{
public:
    Thread(void *(*start_routine)(void *), void *arg)
        : Thread()
    {
        int err = pthread_create(&_handle, nullptr, start_routine, arg);
        if (0 != err)
        {
            throw_system_error(err, "pthread_create");
        }
    }

    ~Thread()
    {
        if (joinable())
        {
            std::terminate();
        }
    }

    Thread() noexcept = default;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    Thread(Thread&& other) noexcept 
        : _handle(other._handle)
    {
        other._handle = 0;
    }

    Thread& operator=(Thread&& other) noexcept
    {
        if (this != &other)
        {
            this->~Thread();
            _handle = other._handle;
            other._handle = 0;
        }

        return *this;
    }

    using native_handle_type = pthread_t;
    native_handle_type native_handle() { return _handle; }

    void detach()
    {
        int err = EINVAL;

        if (joinable())
        {
            err = pthread_detach(_handle);
        }

        if (0 != err)
        {
            throw_system_error(err, "pthread_detach");
        }

        _handle = 0;
    }

    void join()
    {
        int err = EINVAL;

        if (joinable())
        {
            err = pthread_join(_handle, nullptr);
        }

        if (0 != err)
        {
            throw_system_error(err, "pthread_join");
        }

        _handle = 0;
    }

    bool joinable() const noexcept
    {
        return 0 != _handle;
    }

    static unsigned int hardware_concurrency() noexcept
    {
        return std::thread::hardware_concurrency();
    }
private:
    void throw_system_error(int err, const char *what)
    {
        throw std::system_error(err, std::system_category(), what);
    }

    pthread_t _handle = 0;
};
#else
class Thread : private std::thread
{
public:
    using std::thread::native_handle_type;

    using std::thread::thread;
    using std::thread::native_handle;
    using std::thread::detach;
    using std::thread::join;
    using std::thread::joinable;
    using std::thread::hardware_concurrency;
};
#endif

std::shared_ptr<Thread> PlatformRunThread(const ThreadData& data);

#endif //__PLATFORM_THREAD_H__
