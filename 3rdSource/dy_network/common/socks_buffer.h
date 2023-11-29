#pragma once

#include <stdint.h>

#include <inet_session.h>
#include <net_define.h>
class IServerInterface;
class SocksBuffer :public INetBuffer
{
public:
	SocksBuffer(IServerInterface* server, uint32_t capacity);
	~SocksBuffer();
public:
	virtual bool  process_data(const SessionData& sd);
};



