#pragma once
#include <atomic>
class ReferenceObject
{
public:
	ReferenceObject()
	{
		_ref = 1;
	}

	virtual ~ReferenceObject() {}
	int32_t ref()
	{
		return ++_ref;
	}
	int32_t unref()
	{
        int32_t ref = --_ref;

        if (ref == 0)
        {
			OnUnref();
            delete this;
        }

        return ref;
	}

	virtual void OnUnref() {}
private:
	std::atomic<int32_t> _ref;
};