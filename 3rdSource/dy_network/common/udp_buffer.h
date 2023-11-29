#ifndef __UDP_BUFFER_H__
#define __UDP_BUFFER_H__
#include <stdint.h>

#include <inet_session.h>
#include <net_define.h>
class IServerInterface;
class UdpBuffer :public INetBuffer
{
public:
	UdpBuffer(IServerInterface* server, uint32_t capacity);
	~UdpBuffer();
public:
	virtual void recv_udp_data(const char* data, uint32_t size, const sockaddr *addr, int addrlen);
	virtual bool  process_data(const SessionData& sd);
};
#endif //__UDP_BUFFER_H__