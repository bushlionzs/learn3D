#pragma once
#include "inet_session.h"

class IServerInterface;

class PipeSession : public INetSession
{
public:
	PipeSession(IServerInterface* server, uint32_t recv_buffer_size = 1024, uint32_t send_buffer_size = 1024);
	~PipeSession();

	virtual void OnClose(NetHandle, const SessionData&);
	virtual void OnConnected(NetHandle, const SessionData&);
	virtual INetBuffer* create_recv_buffer(const SessionData&);
	virtual uint32_t get_send_buffer_size(const SessionData&);
private:
	IServerInterface* _server;
	uint32_t _recv_buffer_size;
	uint32_t _send_buffer_size;
	
};