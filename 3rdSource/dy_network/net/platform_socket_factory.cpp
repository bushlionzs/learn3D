#include <platform_socket_factory.h>
#include <cross_platform_socket.h>
#include "platform_io.h"
#include "platform_pipe.h"
#ifdef QUIC_ENABLE
#include "quic/quic_socket.h"
#endif

PlatformSocketFactory::PlatformSocketFactory()
{
}

PlatformSocketFactory::~PlatformSocketFactory()
{

}

PlatformSocket* PlatformSocketFactory::CreatePlatformSocket( INetSession* session , 
                                                                NetProtocol protocol,
                                                                const SessionData& sessionData )
{
	PlatformSocket* platformSocket = NULL;

	bool isTcpServer =false;

	switch (protocol)
	{
	case NETPROTOCOL_TCP:
		if( sessionData.m_PeerPort == 0 )
		{
			isTcpServer = true;
			platformSocket = new ServerSocket(session, protocol, sessionData);
		}
		else
		{
			platformSocket = new TcpClientSocket(session, protocol, sessionData);
		}
		break;
	case NETPROTOCOL_UDP:
	{
		platformSocket = new UdpSocket(session, protocol, sessionData);
	}
	break;
#ifdef QUIC_ENABLE
    case NETPROTOCOL_QUIC:
    {
        if( sessionData.m_PeerPort == 0 )
        {
            platformSocket = new QuicServerSocket(session, protocol, sessionData);
        }
        else
        {
            platformSocket = new QuicClientSocket(session, protocol, sessionData);
        }
    }
    break;
#endif
	default:
		{
			return NULL;
		}
		break;
	}

	if( NULL != platformSocket )
	{
		bool ret = platformSocket->CreateSocket();

		if( false == ret )
		{
			delete platformSocket;
			return NULL;
		}
#ifdef _WIN32
	if (true == isTcpServer)
	{
		PlatformIO::GetInstance()->BindSocket(platformSocket);
		platformSocket->Recv(NULL);
	}
	else if(NETPROTOCOL_UDP == protocol)
	{

	}
#else
	if (true == isTcpServer)
	{
		PlatformIO::GetInstance()->BindSocket(platformSocket);
	}
#endif
	}

	return platformSocket;
}

SockBase* PlatformSocketFactory::CreatePlatformPipe(INetSession* session, const std::string& name, bool client)
{
	SockBase* sock = new PlatformPipe(session, name, client);
	return sock;
}