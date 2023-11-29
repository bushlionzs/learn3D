#ifndef _REF_COUNT_OBJECT_H_INCLUDED
#define _REF_COUNT_OBJECT_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#include <atomic>
#include <utility>

class IRefCountObject
{
protected:
    virtual ~IRefCountObject() {}
public:
    typedef int32_t RefCountType;

    virtual RefCountType add_ref() = 0;
    virtual void release() = 0;
    virtual RefCountType ref_count() const = 0;
};

template<typename T>
class ReleaseAtExit
{
public:
    explicit ReleaseAtExit(T *refc, int opc = 0) : _refc(refc), _opc(opc) {}

    ~ReleaseAtExit()
    {
        if (_refc)
        {
            while (_opc-- > 0)
            {
                _refc->release();
            }
        }
    }

    void add_ref()
    {
        if (_refc)
        {
            _refc->add_ref();
            _opc++;
        }
    }

    void detach()
    {
        _refc = NULL;
        _opc = 0;
    }

private:
    T *_refc;
    int _opc; 
};

template<typename T>
struct Void0
{
    typedef void type;
};

template<typename T, typename = void>
struct RefCountType
{
    typedef int64_t type;
};

template<typename T>
struct RefCountType<T, typename Void0<typename T::RefCountType>::type>
{
    typedef typename T::RefCountType type;
};

template<typename Base, typename RefCount = typename RefCountType<Base>::type, RefCount INIT = 0>
class RefCountObject : public Base
{
public:
    template<typename ... Args>
    RefCountObject(Args&& ... args)
        : Base(std::forward<Args>(args)...)
        , _ref_count(INIT) {}

    RefCount add_ref() { return ++_ref_count; }

    void release()
    {
        if (0 == --_ref_count)
        {
            delete this;
        }
    }

    RefCount ref_count() const { return _ref_count; }
protected:
    std::atomic<RefCount> _ref_count;
};

using RefCountBase = RefCountObject<IRefCountObject, IRefCountObject::RefCountType, 1>;

template<typename T>
class RefCountPtr
{
public:
    RefCountPtr() : _px(NULL) {}

    RefCountPtr(T *p, bool add_ref = true) : _px(p)
    {
        if (_px && add_ref)
        {
            _px->add_ref();
        }
    }

    RefCountPtr(const RefCountPtr& rhs) : _px(rhs.get())
    {
        if (_px)
        {
            _px->add_ref();
        }
    }

    template<typename U>
    RefCountPtr(const RefCountPtr<U>& rhs) : _px(rhs.get())
    {
        if (_px)
        {
            _px->add_ref();
        }
    }

    ~RefCountPtr()
    {
        if (_px)
        {
            _px->release();
            _px = NULL;
        }
    }

    RefCountPtr& operator =(const RefCountPtr& rhs)
    {
        RefCountPtr(rhs).swap(*this);
        return *this;
    }

    template<typename U>
    RefCountPtr& operator =(const RefCountPtr<U>& rhs)
    {
        RefCountPtr(rhs).swap(*this);
        return *this;
    }

    template<typename U>
    RefCountPtr& operator =(U *p)
    {
        RefCountPtr(p).swap(*this);
        return *this;
    }

    void reset(T *p = NULL, bool add_ref = true)
    {
        RefCountPtr(p, add_ref).swap(*this);
    }

    T *get() const { return _px; }

    T *detach()
    {
        T *px = _px;
        _px = NULL;
        return px;
    }

    T& operator *() const { return *_px; }

    T *operator->() const { return _px; }

    operator bool() const { return NULL != _px; }

    template<typename U>
    void swap(RefCountPtr<U>& rhs)
    {
        T *px = _px;
        _px = rhs._px;
        rhs._px = px;
    }
private:
    T * _px;
};

template<typename T, typename ... Args>
RefCountPtr<T> make_refc_ptr(Args&& ... args)
{
    return new RefCountObject<T>(std::forward<Args>(args)...);
}

#endif // !_REF_COUNT_OBJECT_H_INCLUDED
