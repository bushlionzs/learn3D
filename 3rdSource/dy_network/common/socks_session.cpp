#include "socks_session.h"
#include "socks_buffer.h"
#include "server_interface.h"

SocksSession::SocksSession(IServerInterface* server)
{
	_server = server;
}

void SocksSession::OnClose(NetHandle h, const SessionData&)
{

}

void SocksSession::on_release(NetHandle, const SessionData&)
{

}

INetBuffer* SocksSession::create_recv_buffer(const SessionData&)
{
	auto capacity = _server->get_recv_buffer_size();
	INetBuffer* pBuffer = new SocksBuffer(_server, capacity);
	return pBuffer;
}

uint32_t SocksSession::get_send_buffer_size(const SessionData&)
{
	return _server->get_send_buffer_size();
}