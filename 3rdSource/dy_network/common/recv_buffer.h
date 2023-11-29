#ifndef __CHANNEL_BUFFER_H__
#define __CHANNEL_BUFFER_H__

#include <stdint.h>

#include <inet_session.h>
#include <net_define.h>
class IServerInterface;
class RecvBuffer:public INetBuffer
{
public:
	RecvBuffer(IServerInterface* server, uint32_t capacity, bool need_split = true);
	~RecvBuffer();
public:
    virtual bool  process_data(const SessionData& sd);
};

#endif //__CHANNEL_BUFFER_H__


