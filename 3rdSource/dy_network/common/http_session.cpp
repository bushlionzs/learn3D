#include <platform_common.h>
#include <platform_log.h>
#include <platform_util.h>
#include <server_interface.h>
#include <http_client_buffer.h>
#include <http_buffer.h>
#include <websocket_buffer.h>
#include "http_session.h"
#include "http_agent_buffer.h"


HttpSession::HttpSession(IServerInterface* server, bool ssl, bool ws, bool hc, bool reuse_port)
{
    _server = server;
    _is_ssl = ssl;
    _is_ws  = ws;
    _is_hc  = hc;
    _reuse_port = reuse_port;
}

void HttpSession::OnAccept(NetHandle h, const SessionData& data)
{
	session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = data.m_is_client;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    
    _server->post_network_message(NetMsg_Accept, h, (const uint8_t *)&sit, sizeof(sit), data);
}

void HttpSession::OnConnected(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = data.m_is_client;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    sit.param = data.m_param;
    
    _server->post_network_message(NetMsg_Connected, h, (const uint8_t *)&sit, sizeof(sit), data);
}

void HttpSession::OnClose(NetHandle h, const SessionData& data)
{
    session_info_t sit;
    memset(&sit, 0, sizeof(sit));
    sit.is_client = data.m_is_client;
    strncpy(sit.peer_ip, data.m_PeerIP.c_str(), sizeof(sit.peer_ip));
    sit.peer_port = data.m_PeerPort;
    strncpy(sit.local_ip, data.m_LocalIP.c_str(), sizeof(sit.local_ip));
    sit.local_port = data.m_LocalPort;
    sit.param = data.m_param;
    
    _server->post_network_message(NetMsg_Close, h, (const uint8_t *)&sit, sizeof(sit), data);
}

void HttpSession::on_release(NetHandle h, const SessionData& data)
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

INetBuffer* HttpSession::create_recv_buffer(const SessionData&)
{
    INetBuffer* pNetBuffer = NULL;
    if (_is_ws)
    {
        pNetBuffer = new WebsocketBuffer(_server, _server->get_http_recv_buffer_size());
    }
    else
    {
        if (_is_hc)
        {
            pNetBuffer = new HttpClientBuffer(_server, _server->get_http_recv_buffer_size(), _server->is_http_continue_data());
        }
        else
        {
            if (_server->is_agent())
            {
                pNetBuffer = new HttpAgentBuffer(_server, _server->get_http_recv_buffer_size());
            }
            else
            {
                pNetBuffer = new HttpBuffer(_server, _server->get_http_recv_buffer_size());
            }
            
        }
    }
	return pNetBuffer;
}

uint32_t HttpSession::get_send_buffer_size(const SessionData&)
{
	return _server->get_send_buffer_size();
}
