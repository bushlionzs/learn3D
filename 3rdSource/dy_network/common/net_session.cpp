#include <platform_common.h>
#include <platform_log.h>
#include <platform_util.h>

#include <server_interface.h>
#include <recv_buffer.h>
#include <server_def.h>
#include "net_session.h"


NetSession::NetSession(IServerInterface* server, bool need_split)
{
    _server = server;
    _need_split = need_split;
}

void NetSession::OnAccept(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = 0;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    
    _server->post_network_message(NetMsg_Accept, h, (const uint8_t *)&sit, sizeof(sit));
}

void NetSession::OnConnected(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = 1;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
	sit.param = data.m_param;
    
    _server->post_network_message(NetMsg_Connected, h, (const uint8_t *)&sit, sizeof(sit));
}

void NetSession::OnClose(NetHandle h, const SessionData& data)
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

void NetSession::on_release(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = data.m_is_client;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    sit.param = data.m_param;

    _server->post_network_message(NetMsg_Session_Release, h, (const uint8_t *)&sit, sizeof(sit), data);
}

INetBuffer* NetSession::create_recv_buffer(const SessionData& oSessionInfo)
{
    if (!_need_split)
    {
        return new RecvBuffer(_server, _server->get_client_recv_buffer_size(), false);
    }
    
    uint32_t capacity = 0;
    if (oSessionInfo.m_is_client == 0)
    {
        capacity = _server->get_recv_buffer_size();
    }
    else
    {
        capacity = _server->get_client_recv_buffer_size();
    }

	INetBuffer* pNetBuffer = new RecvBuffer(_server, capacity);
	return pNetBuffer;
}

uint32_t NetSession::get_send_buffer_size(const SessionData& oSessionInfo)
{
    if (oSessionInfo.m_is_client == 0)
    {
        return _server->get_send_buffer_size();
    }

    return _server->get_client_send_buffer_size();
}
