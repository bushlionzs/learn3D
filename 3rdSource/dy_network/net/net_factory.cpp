
#include <inet_session.h>
#include <iclient_connection.h>
#include <iserver_connection.h>
#include <net_factory.h>
#include <net_manager.h>
#include <udp_session.h>
#include "platform_io.h"
#include <platform_log.h>
#include <dy_network_containter.h>
extern DyNetworkContaintor *g_dy_network_containtor;

bool NetFactory::is_client_handle(NetHandle h)
{
    if (h & NET_HANDLE_CLIENT_FLAG)
    {
        return true;
    }
    return false;
}

NetFactory* NetFactory::GetInstance()
{
    return g_dy_network_containtor->get_net_factory();
}

NetFactory::NetFactory()
{

}

NetFactory::~NetFactory()
{

}

NetHandle NetFactory::CreateUdpConnection(UdpSession* session , const SessionData& sessionData )
{
	NetHandle handle = NetManager::GetInstance()->createClientConnection(session, NETPROTOCOL_UDP, sessionData);

	if( INVALID_NET_HANDLE == handle )
	{
        FATAL_LOG("create udp endpoint failed!");
		return INVALID_NET_HANDLE;
	}

	if ( false == NetManager::GetInstance()->InitializeConnection( handle ) )
	{
        FATAL_LOG("initialize udp connection failed!");
		return INVALID_NET_HANDLE;
	}

	return handle;
}

NetHandle NetFactory::CreateTcpConnection(INetSession* session , const SessionData& sessionData)
{
	NetHandle handle = NetManager::GetInstance()->createClientConnection( session , NETPROTOCOL_TCP , sessionData );

	if( INVALID_NET_HANDLE == handle )
	{
		return INVALID_NET_HANDLE;
	}

	if ( false == NetManager::GetInstance()->InitializeConnection( handle ) )
	{
		return INVALID_NET_HANDLE;
	}

	return handle;
}

NetHandle NetFactory::CreateQuicConnection(INetSession* session, const SessionData& sessionData)
{
	SessionData tmp = sessionData;
    tmp.m_is_quic = true;
    NetHandle handle = NetManager::GetInstance()->createClientConnection(session, NETPROTOCOL_QUIC, tmp);
    if (INVALID_NET_HANDLE == handle)
    {
        WARNING_LOG("create quic endpoint failed!");
        return INVALID_NET_HANDLE;
    }

    if (false == NetManager::GetInstance()->InitializeQuicConnection(handle))
    {
        WARNING_LOG("create quic endpoint failed!");
        return INVALID_NET_HANDLE;
    }

    return handle;
}

NetHandle NetFactory::CreateQuicServer(INetSession* session, 
                                    const std::string& ip, 
                                    uint16_t port, 
                                    const std::shared_ptr<QuicConfig>& quic_cfg)
{
    SessionData sessionData;
    sessionData.m_LocalIP   = ip;
    sessionData.m_LocalPort = port;
    sessionData.m_reuse_port = session->is_server_reuse_port();
    sessionData.m_is_quic = true;
    sessionData.m_quic_cfg = quic_cfg;

    NetHandle handle = NetManager::GetInstance()->createServerQuicConnection(session, 
                                                                                NETPROTOCOL_QUIC, 
                                                                                sessionData);
    if (INVALID_NET_HANDLE == handle)
    {
        FATAL_LOG("create quic endpoint failed!");
        return INVALID_NET_HANDLE;
    }

    if (false == NetManager::GetInstance()->InitializeConnection(handle))
    {
        FATAL_LOG("init quic endpoint failed!");
        return INVALID_NET_HANDLE;
    }
    return handle;
}

void NetFactory::DisconnectHandle(const NetHandle& handle)
{
    NetManager::GetInstance()->AccordClose(handle);
}


NetHandle NetFactory::CreateTcpServer( INetSession* session , const std::string& ip , uint16_t port )
{
	SessionData sessionData;
	sessionData.m_LocalIP   = ip;
	sessionData.m_LocalPort = port;

	NetHandle handle = NetManager::GetInstance()->createServerConnection(session, NETPROTOCOL_TCP, sessionData);
	return handle;
}

int32_t NetFactory::SendData(const NetHandle& handle, const uint8_t* data,  uint32_t size, SndData* param)
{
	return NetManager::GetInstance()->SendData( handle , data , size , param );
}
NetHandle NetFactory::CreateTcpServer( INetSession* session , const SessionData& sessionData)
{
    return NetManager::GetInstance()->createServerConnection(session, NETPROTOCOL_TCP, sessionData);
}



NetHandle NetFactory::CreatePipe(INetSession* session, const std::string& name, bool client)
{
    NetHandle handle =  NetManager::GetInstance()->CreatePipe(session, name, client);

    if (INVALID_NET_HANDLE == handle)
    {
        FATAL_LOG("[name:%s, client:%d]CreatePipe failed!", name.c_str(), client);
        return INVALID_NET_HANDLE;
    }

    if (false == NetManager::GetInstance()->InitializeConnection(handle))
    {
        FATAL_LOG("[name:%s, client:%d]initialize CreatePipe failed!", name.c_str(), client);
        return INVALID_NET_HANDLE;
    }

    return handle;
}




