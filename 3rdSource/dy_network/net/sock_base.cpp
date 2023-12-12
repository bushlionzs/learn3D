#include "sock_base.h"
#include "platform_log.h"

SockBase::SockBase()
{
    _ref = 1;
}

int32_t SockBase::ref()
{
    return ++_ref;
}
int32_t SockBase::unref()
{
    int32_t ref = --_ref;

    if (ref == 0)
    {
        deleleSelf();
    }
    else if (ref < 0)
    {
        WARNING_LOG("PlatformSocket(%p) unref(%d)", this, ref);
        //assert(false);
    }

    return ref;
}

void SockBase::change_session(INetSession* session)
{
    _session = session;

    OnSessionChanged();
}