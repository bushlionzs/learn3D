#pragma once

#include <mutex>
#include <algorithm>

#include "singleton.h"

namespace dy_network
{

class FreeList
{
public:
    void *get()
    {
        void *p = _head;
        if (p)
        {
            _head = next(_head);
        }

        return p;
    }

    void put(void *ptr)
    {
        next(ptr) = _head;
        _head = ptr;
    }
private:
    static void *&next(void *ptr)
    {
        return *static_cast<void **>(ptr);
    }

    void *_head = nullptr;
};

class MemoryPool
{
public:
    ~MemoryPool()
    {
        free_all();
    }

    void *alloc(size_t size)
    {
        void *p = _freelist.get();
        if (p)
        {
            return p;
        }

        return malloc((std::max)(size, sizeof(void *)));
    }

    void dealloc(void *ptr)
    {
        _seq++;
        if (_seq % 20 == 0 || !_is_receiver)
        {
            free(ptr);
        }
        else
        {
            _freelist.put(ptr);
        }
    }

    void set_receiver() { _is_receiver = true; }
private:
    void free_all()
    {
        void *p = nullptr;
        while (NULL != (p = _freelist.get()))
        {
            free(p);
        }
    }

    FreeList _freelist;
    uint32_t _seq = 0;
    bool _is_receiver = false;
};


// T as tag
template<typename T>
class UseGlobalMemoryPool
{
public:
    void *operator new(size_t n)
    {
        return Inner::get_mutable_instance().alloc(n);
    }

    void operator delete(void *ptr)
    {
        Inner::get_mutable_instance().dealloc(ptr);
    }

private:
    class Inner : public Singleton<Inner>
    {
    public:
        Inner()
        {
            _inner.set_receiver();
        }

        void *alloc(size_t size)
        {
            std::lock_guard<std::mutex> guard(_mu);
            return _inner.alloc(size);
        }

        void dealloc(void *ptr)
        {
            std::lock_guard<std::mutex> guard(_mu);
            return _inner.dealloc(ptr);
        }
    private:
        std::mutex _mu;
        MemoryPool _inner;
    };
};

// T as tag
template<typename T>
class UseThreadLocalMemoryPool
{
public:
    void *operator new(size_t n)
    {
        inner().set_receiver();
        return inner().alloc(n);
    }

    void operator delete(void *ptr)
    {
        inner().dealloc(ptr);
    }
private: 
    static MemoryPool& inner()
    {
#if (defined (__i386__) || defined (__x86_64__)) && (defined(__APPLE__))
        static  MemoryPool _inner;
        return _inner;
#else
        static thread_local MemoryPool _inner;
        return _inner;
#endif
    }
};

}

