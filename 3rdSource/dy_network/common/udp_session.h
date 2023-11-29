#ifndef __UDP_SESSION_H__
#define __UDP_SESSION_H__

#include "net_lib.h"

class IServerInterface;
class UdpSession : public INetSession
{
public:
	UdpSession(IServerInterface* server);
	virtual void OnClose(NetHandle h, const SessionData&);
    virtual void on_release(NetHandle, const SessionData&);
	virtual INetBuffer* create_recv_buffer(const SessionData&);

	virtual uint32_t get_send_buffer_size(const SessionData&);
private:
	IServerInterface* _server;
};

#endif //__UDP_SESSION_H__
