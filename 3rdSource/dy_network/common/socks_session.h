#pragma once

#include "net_lib.h"

class IServerInterface;
class SocksSession : public INetSession
{
public:
	SocksSession(IServerInterface* server);
	virtual void OnClose(NetHandle h, const SessionData&);
	virtual void on_release(NetHandle, const SessionData&);
	virtual INetBuffer* create_recv_buffer(const SessionData&);

	virtual uint32_t get_send_buffer_size(const SessionData&);
private:
	IServerInterface* _server;
};

