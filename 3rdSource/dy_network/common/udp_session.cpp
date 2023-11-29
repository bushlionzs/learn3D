#include "udp_session.h"
#include "udp_buffer.h"
#include "server_interface.h"
#include "server_def.h"

UdpSession::UdpSession(IServerInterface* server)
{
	_server = server;
}

void UdpSession::OnClose(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = data.m_is_client;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    sit.param = data.m_param;

    _server->post_network_message(NetMsg_Close, h, (const uint8_t *)&sit, sizeof(sit));
}

void UdpSession::on_release(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = data.m_is_client;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    sit.param = data.m_param;

    _server->post_network_message(NetMsg_Session_Release, h, (const uint8_t *)&sit, sizeof(sit));
}

INetBuffer* UdpSession::create_recv_buffer(const SessionData&)
{
	return new UdpBuffer(_server, 1024 * 5);
}

uint32_t UdpSession::get_send_buffer_size(const SessionData&)
{
	return 1500 * 300;
}