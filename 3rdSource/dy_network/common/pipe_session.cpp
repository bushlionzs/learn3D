#include "pipe_session.h"
#include "server_def.h"
#include "server_interface.h"
#include "recv_buffer.h"

PipeSession::PipeSession(IServerInterface* server, uint32_t recv_buffer_size, uint32_t send_buffer_size)
{
	_server = server;
	_recv_buffer_size = recv_buffer_size;
	_send_buffer_size = send_buffer_size;
}

PipeSession::~PipeSession()
{

}

void PipeSession::OnClose(NetHandle h, const SessionData& sd)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.param = sd.m_param;

    _server->post_network_message(NetMsg_Close, h, (const uint8_t*)&sit, sizeof(sit), sd);
}


void PipeSession::OnConnected(NetHandle h, const SessionData& sd)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));

    sit.param = sd.m_param;

    _server->post_network_message(NetMsg_Connected, h, (const uint8_t*)&sit, sizeof(sit), sd);
}

INetBuffer* PipeSession::create_recv_buffer(const SessionData&)
{
    return new RecvBuffer(_server, _recv_buffer_size, true);
}

uint32_t PipeSession::get_send_buffer_size(const SessionData&)
{
    return _send_buffer_size;
}

