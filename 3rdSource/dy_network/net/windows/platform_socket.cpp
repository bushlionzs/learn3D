#include <stdio.h>
#include <map>
#include <algorithm>
#include <winsock2.h>
#include <mstcpip.h>
#include <assert.h>
#include  <Mswsock.h>
#include <net_define.h>
#include <windows/platform_socket.h>
#include <windows/platform_io.h>
#include <iclient_connection.h>
#include <inet_session.h>
#include <net_manager.h>
#include <netlib_error.h>
#include <platform.h>
#include <platform_log.h>
#include <net_buffer.h>
#include "platform_io.h"

#pragma warning(disable:4127)
#pragma comment(lib ,"Mswsock.lib")
#pragma comment(lib ,"Ws2_32.lib")

#ifndef DY_NETWORK_DISNABLE_SSL
static bool ssl_is_fatal_error(int ssl_error)
{
    switch (ssl_error)
    {
    case SSL_ERROR_NONE:
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
    case SSL_ERROR_WANT_CONNECT:
    case SSL_ERROR_WANT_ACCEPT:
        return false;
    }
    return true;
}
#else
static bool ssl_is_fatal_error(int ssl_error)
{
    return true;
}
#endif

bool PlatformSocket::PlatformSocketInit()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );

	if( err != 0 )
	{
        INIT_LOG("WSAStartup failed:%d", err);
		//print something
		return false;
	}

	return true;
}


PlatformSocket::PlatformSocket( INetSession* session , NetProtocol protocol , const SessionData& sessionData)
{
    //printf("PlatformSocket construct: %p\n", this);

	_session = session;
	m_socketFd				 = INVALID_SOCKET;
	m_olConnect.m_ioType	 = IOConnect;
    m_olConnect.m_param = 0;
	if (protocol == NETPROTOCOL_UDP)
	{
		m_olConnect.m_ioType = IOUdpConnect;
		m_olConnect.m_param =  (uint64_t)this;
	}
	ZeroMemory(&m_olConnect.m_ol, sizeof(m_olConnect.m_ol));

	m_olEventClose.m_Ov.m_ioType = IOEvent;
	m_olEventClose.m_Owner = this;
	m_olEventClose.m_event = EVENT_DELAY_CLOSE;
	m_olEventRecv.m_Ov.m_ioType = IOEvent;
	m_olEventRecv.m_Owner = this;
	m_olEventRecv.m_event = EVENT_DELAY_RECV;
	m_olEventSend.m_Ov.m_ioType = IOEvent;
	m_olEventSend.m_Owner = this;
	m_olEventSend.m_event = EVENT_DELAY_SEND;

	m_olEventSSL.m_Ov.m_ioType = IOEvent;
	m_olEventSSL.m_Owner = this;
	m_olEventSSL.m_event = EVENT_DELAY_SSL;

	
	m_olSend.m_ioType        = IOSend;
	m_olRecv.m_ioType        = IORecv;
	m_olRecv.m_remoteAddrLen = sizeof(m_olRecv.m_remoteAddr);
	m_olAccept.m_Ov.m_ioType = IOAccept;
	m_protocol               = protocol;
	_sessionData = sessionData;
	_handle = INVALID_NET_HANDLE;

#ifndef DY_NETWORK_DISNABLE_SSL
	_is_ssl = session->is_ssl();
#endif

	_ssl_connection = NULL;

	m_is_connected = false;
    _send_bytes = 0;
	_recv_bytes = 0;
}


PlatformSocket::~PlatformSocket()
{
    if (_ssl_connection != NULL)
    {
        delete _ssl_connection;
    }
    DestroySocket(120);
	_session->on_release(_handle, _sessionData);
}



int PlatformSocket::GetSocketType( NetProtocol protocol )
{
	switch( protocol )
	{
	case NETPROTOCOL_TCP:
		return SOCK_STREAM;
	default://NETPROTOCOL_UDP
		return SOCK_DGRAM;
	}
}


int PlatformSocket::GetSocketProtocol( NetProtocol protocol )
{
	switch( protocol )
	{
	case NETPROTOCOL_TCP:
		return IPPROTO_TCP;
	default://NETPROTOCOL_UDP
		return IPPROTO_UDP;
	}
}

bool PlatformSocket::MakeSocketNonBlocking()
{
	int nRet = 0;

	unsigned long ul = 1;

	nRet = ioctlsocket(m_socketFd, FIONBIO, &ul);

	if (SOCKET_ERROR == nRet)
	{
		return false;
	}

	return true;
}

bool PlatformSocket::CreateSocketOnly(void* s)
{
	if( NULL == s )
	{
		if( m_protocol == NETPROTOCOL_INVALID )
			return false;

		_sessionData.check_inet_family();

		int sockettype = GetSocketType( m_protocol );
		int socketprotocol = GetSocketProtocol( m_protocol );

		m_socketFd = WSASocket(_sessionData.m_family, sockettype, socketprotocol, NULL, 0, WSA_FLAG_OVERLAPPED);
		if( INVALID_SOCKET == m_socketFd)
		{
			return false;
		}

		setsockopt(m_socketFd, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, NULL, 0);

		return true;
	}
	else
	{
		m_socketFd = *( (SOCKET*)s );
		return true;
	}
}

bool PlatformSocket::SetSocketOption()
{
	if( false == MakeSocketNonBlocking() )
	{
		return false;
	}

	if( m_protocol == NETPROTOCOL_UDP )
	{
		DWORD dwBytesReturned = 0;
		BOOL bNewBehavior = FALSE;
		int status;

		// disable  new behavior using
		// IOCTL: SIO_UDP_CONNRESET
		status = WSAIoctl(m_socketFd, SIO_UDP_CONNRESET,
		&bNewBehavior, sizeof(bNewBehavior),
						   NULL, 0, &dwBytesReturned,
						   NULL, NULL);

		if (SOCKET_ERROR == status)
		{
			int dwErr = WSAGetLastError();
			if (WSAEWOULDBLOCK == dwErr)
			{
				return(false);
			}
		}	
	}
	return true;
}

bool PlatformSocket::set_tcp_keepalive(const TcpKeepAliveOption *options)
{
    BOOL keepalive = options ? TRUE : FALSE;
    int ret = setsockopt(m_socketFd, SOL_SOCKET, SO_KEEPALIVE, (const char*)&keepalive, sizeof(keepalive));
    if (SOCKET_ERROR == ret)
    {
        WARNING_LOG("[fd:%zu,ret:%d,err:%d]setsockopt  SO_KEEPALIVE", m_socketFd, ret, WSAGetLastError());
        return false;
    }

    if (!options || options->idle_sec < 0 || options->intvl_sec < 0)
    {
        NOTICE_LOG("[fd:%zu] set tcp keepalive to %d", m_socketFd, keepalive);
        return true;
    }

    tcp_keepalive in;
    in.onoff = TRUE;
    in.keepalivetime = options->idle_sec * 1000;
    in.keepaliveinterval = options->intvl_sec * 1000;
 
    DWORD ul = 0;
    ret = WSAIoctl(
        m_socketFd, 
        SIO_KEEPALIVE_VALS,
        &in,
        sizeof(in), 
        NULL,
        0,
        &ul,
        NULL, 
        NULL
    );

    if (SOCKET_ERROR == ret)
    {
        WARNING_LOG("[fd:%zu,ret:%d,err:%d]WSAIoctl keepalive failed", m_socketFd, ret, WSAGetLastError());
        return false;
    }

    NOTICE_LOG(
        "[fd:%zu] enable tcp keepalive,cnt=%d,idle=%d,intvl=%d", 
        m_socketFd, 
        options->probes,
        options->idle_sec,
        options->intvl_sec
    );

    return true;
}
bool PlatformSocket::CreateSocket( )
{
	if( false == CreateSocketOnly(NULL ) )
	{
		return false;
	}

	int sockettype = GetSocketType( m_protocol );


	//if( m_protocol != NETPROTOCOL_RAWIP )
	{
		dy_network::SockaddrStorage local;
        if (!local.init(_sessionData.get_local_ip(), _sessionData.m_LocalPort))
        {
            DestroySocket(1);
            return false;
        }

        if (_sessionData.m_reuse_port)
        {
            int on = 1;
            setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
        }
        else
        {
            int on = 1;
            setsockopt(m_socketFd, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (const char*)&on, sizeof(on));
        }

        int ipv6_only = _sessionData.m_ipv6_only ? 1 : 0;
        setsockopt(m_socketFd,
            IPPROTO_IPV6,
            IPV6_V6ONLY,
            reinterpret_cast<const char *>(&ipv6_only),
            sizeof(int)
        );

		int nRet = ::bind(m_socketFd, local.addr(), local.size());
		if( SOCKET_ERROR == nRet )
		{
			DestroySocket(2);
			return false;
		}

        int len = sizeof(local);
        nRet = ::getsockname(m_socketFd, local.addr(), &len);
        if (nRet == 0)
        {
            local.get_ip_string(_sessionData.m_LocalIP);
			_sessionData.m_LocalPort = local.get_port();
        }
        else
        {
            DestroySocket(8);
            return false;
        }
	}

	if( false == SetSocketOption() )
	{
		DestroySocket(3);
		return false;
	}


	if( SOCK_STREAM == sockettype )
	{
		if(_sessionData.m_PeerIP.empty() == true || _sessionData.m_PeerPort == 0 )
		{
			int nRet = listen(m_socketFd,  5);

            m_IsListeningSocket = true;

			if( SOCKET_ERROR == nRet )
			{
				DestroySocket(4);
				return false;
			}
		}
	}


	return true;
}

bool PlatformSocket::AcceptSocket( PlatformSocket* client )
{
	int AddrLen = sizeof(sockaddr_in6)+16;

	DWORD dwBytes = 0;
	memset( &m_olAccept.m_Ov.m_ol , 0 , sizeof( m_olAccept.m_Ov.m_ol ) );
	m_olAccept.m_Owner = client;


	BOOL ret = AcceptEx(m_socketFd, client->m_socketFd, m_olAccept.m_netBuffer, 0,
        AddrLen, AddrLen, &dwBytes , &m_olAccept.m_Ov.m_ol );

	if( FALSE == ret )
	{
		int err = ::WSAGetLastError();
		if( err != WSA_IO_PENDING )
		{
			return false;
		}
	}

	if (client->_is_ssl)
	{
		if (NULL == client->_ssl_connection)
		{
			client->_ssl_connection = create_ssl_connection((int)client->m_socketFd);
		}
	}
	
	return true;
}

void PlatformSocket::update_socket_addrs(void *buffer)
{
    DWORD addr_filled_len = sizeof(sockaddr_in6) + 16;
    dy_network::SockaddrStorage *local_addr = nullptr;
    dy_network::SockaddrStorage *remote_addr = nullptr;
    INT local_addr_len = 0;
    INT remote_addr_len = 0;

    GetAcceptExSockaddrs(
        buffer,
        0,
        addr_filled_len,
        addr_filled_len,
        (sockaddr **)&local_addr,
        &local_addr_len,
        (sockaddr **)&remote_addr,
        &remote_addr_len
    );

    if (remote_addr_len > 0 && remote_addr)
    {
		_sessionData.m_PeerIP = remote_addr->get_ip_string();
		_sessionData.m_PeerPort = remote_addr->get_port();
    }
}

bool PlatformSocket::DestroySocket(int magic)
{
	if (m_socketFd != INVALID_SOCKET)
	{
		ScopedLock<PlatformMutex> lock(m_mutex);
        if (m_socketFd != INVALID_SOCKET)
        {
            SOCKET tmp = m_socketFd;
            m_socketFd = INVALID_SOCKET;
            NOTICE_LOG("nethandle:%llu, session:%p, DestroySocket, magic:%d, err:%d,this:%p\n", 
				_handle, _session, magic, errno, this);
            OnClose();
            closesocket(tmp);

            return true;
        }
        else
        {
            return false;
        }
	}
	else
	{
		return false;
	}
}



bool PlatformSocket::DelayCloseSocket()
{
	if (m_socketFd != INVALID_SOCKET)
	{
		ref();
		PlatformIO::GetInstance()->PostEvent(_handle, (OVERLAPPED*)&m_olEventClose);
	}
	return true;
}

void PlatformSocket::deleleSelf()
{
	delete this;
}

bool PlatformSocket::DelaySendData()
{
	if (m_socketFd != INVALID_SOCKET)
	{
		ref();
		PlatformIO::GetInstance()->PostEvent(_handle, (OVERLAPPED*)&m_olEventSend);
	}
	return true;
}

bool PlatformSocket::DelayRecvData()
{
	if (m_socketFd != INVALID_SOCKET)
	{
		ref();
		PlatformIO::GetInstance()->PostEvent(_handle, (OVERLAPPED*)&m_olEventRecv);
	}
	return true;
}

bool PlatformSocket::DelaySSL()
{
	if (m_socketFd != INVALID_SOCKET)
	{
		ref();
		PlatformIO::GetInstance()->PostEvent(_handle, (OVERLAPPED*)&m_olEventSSL);
	}
	return true;
}

bool PlatformSocket::is_socket_valid()
{
    return m_socketFd != INVALID_SOCKET;
}

bool PlatformSocket::OnConnected(struct IOThredData* io_thread_data)
{
    ScopedLock<PlatformMutex> lock(m_mutex);
	if (!m_is_connected)
	{
		if (_is_ssl)
		{
			return ssl_connect(io_thread_data, true);
		}
		else
		{
            if (m_socketFd == INVALID_SOCKET)
            {
                return false;
            }
			_session->OnConnected(_handle, _sessionData);
            if (!Recv(io_thread_data)) {
                return false;
            }
            m_is_connected = true;
            Send();
			return true;
        }
    }
    return true;
}

bool PlatformSocket::ssl_connect(struct IOThredData* io_thread_data, bool recv)
{
	if (0 == _ssl_connection->handshaked)
	{
		int bytes = SSL_read(_ssl_connection->connection, io_thread_data->_recv_buffer, io_thread_data->_recv_buffer_size);
		int ssl_error = SSL_get_error(_ssl_connection->connection, bytes);

		SSL_is_init_finished(_ssl_connection->connection);
		if (ssl_is_fatal_error(ssl_error))
		{
			DestroySocket(9);
			return false;
		}
		bytes = BIO_read(_ssl_connection->bio_out, io_thread_data->_recv_buffer, io_thread_data->_recv_buffer_size);

		if (bytes > 0)
		{
			CBuffer* send_buf = get_ssl_buffer();

			SendDirect(send_buf, io_thread_data->_recv_buffer, bytes);

			if(recv)
			  Recv(io_thread_data);

			return true;

		}
		else
		{
			DestroySocket(10);
			return false;
		}
	}

	return true;
}

bool PlatformSocket::OnIOBinded()
{
    if (NETPROTOCOL_TCP != m_protocol)
    {
        return true;
    }

    if (_sessionData.m_PeerIP.empty() || 0 == _sessionData.m_PeerPort)
    {
        return true;
    }

    dy_network::SockaddrStorage peer;
    if (!peer.init(_sessionData.m_PeerIP.c_str(), _sessionData.m_PeerPort))
	{
		DestroySocket(5);
		return false;
	}

	LPFN_CONNECTEX m_lpfnConnectEx = NULL;
	GUID GuidConnectEx = WSAID_CONNECTEX;
	DWORD dwBytes = 0;

	if (SOCKET_ERROR == WSAIoctl(m_socketFd, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidConnectEx, sizeof(GuidConnectEx),
		&m_lpfnConnectEx, sizeof(m_lpfnConnectEx), &dwBytes, 0, 0))
	{
		DestroySocket(6);
		return false;
	}

	if (_is_ssl)
	{
		if (NULL == _ssl_connection)
		{
			_ssl_connection = create_ssl_connection((int)m_socketFd, true);
		}
	}

    ref();
	BOOL bResult = m_lpfnConnectEx(m_socketFd, peer.addr(), peer.size(), NULL, 0, 0, &m_olConnect.m_ol);
	if (!bResult)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
            unref();
			DestroySocket(7);
			return false;
		}
	}

	return true;
}


bool PlatformSocket::OnAccept()
{
	return false;
}

void PlatformSocket::OnClose()
{
	_session->OnClose(_handle, _sessionData);
}

void PlatformSocket::OnSessionChanged()
{
	bool ssl = _session->is_ssl();
	if (ssl)
	{
		if (nullptr == _ssl_connection)
		{
			m_is_connected = false;

			_ssl_connection = create_ssl_connection((int)m_socketFd, true);
		}
		
		_is_ssl = ssl;
		
		DelaySSL();
	}
}

void PlatformSocket::get_stat_info(net_lib_stat_t& info)
{
	info._recv_bytes = _recv_bytes;
	info._send_bytes = _send_bytes;
}


int PlatformSocket::SendUdp(const uint8_t* data, uint32_t size, const sockaddr *addr, int addrlen)
{
    if (m_socketFd == INVALID_SOCKET)
    {
        return NetlibError_SocketError;
    }

	int ret;
	DWORD sendbyte = 0;
	m_olSend.m_wsaBuffer.buf = (CHAR*)data;
	m_olSend.m_wsaBuffer.len = size;

	memset( &m_olSend.m_ol , 0 , sizeof(m_olSend.m_ol) );
    ref();
	ret = WSASendTo(m_socketFd, &m_olSend.m_wsaBuffer, 1, &sendbyte, 0,  addr, addrlen, &m_olSend.m_ol, NULL);
	if(ret == 0)
	{
		return 0;
	}
	else
	{
		int err = WSAGetLastError();

		if( err == WSA_IO_PENDING )
		{
			return 0;
		}
        unref();

        auto ss = reinterpret_cast<const dy_network::SockaddrStorage *>(addr);

        uint16_t port = ss->get_port();

        char ip[INET6_ADDRSTRLEN];
        ss->get_ip_string(ip);

		WARNING_LOG("[err:%d,dstaddr:%s, dstport:%u]WSASendTo error", errno, ip, (uint32_t)port);
		return -1;
	}
}

int PlatformSocket::SendTcp(const uint8_t* data, uint32_t size)
{
	if (m_socketFd == INVALID_SOCKET)
	{
		return NetlibError_SocketError;
	}


	int ret;
	m_sendbyte = 0;

	memset(&m_olSend.m_ol, 0, sizeof(m_olSend.m_ol));
	m_olSend.m_wsaBuffer.buf = (CHAR*)data;
	m_olSend.m_wsaBuffer.len = size;
    ref();
	ret = WSASend(m_socketFd, &m_olSend.m_wsaBuffer, 1, &m_sendbyte, 0, &m_olSend.m_ol, NULL);
	if (ret == 0)
	{
		return 0;
	}
	else
	{
		int err = WSAGetLastError();

		if (err == WSA_IO_PENDING)
		{
			return 0;
		}
        unref();
		DestroySocket(12);
		return -1;
	}

}



bool PlatformSocket::RecvUdp(struct IOThredData* io_thread_data, INetBuffer* recv_buf)
{
    if (m_socketFd == INVALID_SOCKET)
    {
        return false;
    }

	net_buf_pos_t* net_pos = recv_buf->get_recv_buf(io_thread_data);

	if (NULL == net_pos)
	{
		DestroySocket(13);
		return false;
	}

	DWORD sendbyte = 0;
	m_olRecv.m_wsaBuffer.buf = (char*)net_pos->_buf;
	m_olRecv.m_wsaBuffer.len = net_pos->_size;
	memset(&m_olRecv.m_ol, 0, sizeof(m_olRecv.m_ol));

	DWORD flags = 0;
    ref();
	int ret = WSARecvFrom(m_socketFd, &m_olRecv.m_wsaBuffer, 1, &sendbyte, &flags, m_olRecv.m_remoteAddr.addr(), &m_olRecv.m_remoteAddrLen, &m_olRecv.m_ol, NULL);
	if (ret == 0)
	{
		return true;
	}
	else
	{
		int err = WSAGetLastError();

		if (err == WSA_IO_PENDING)
		{

			return true;
		}
        unref();
		return false;
	}
}

int32_t PlatformSocket::RecvTcp(struct IOThredData* io_thread_data, INetBuffer* recv_buf, uint32_t limit)
{
	if (m_socketFd == INVALID_SOCKET)
	{
		return 0;
	}


	if (_is_ssl)
	{
		DWORD recvbyte = 0;
		m_olRecv.m_wsaBuffer.buf = _ssl_connection->ssl_recv_buf;
		m_olRecv.m_wsaBuffer.len = std::min((uint32_t)_ssl_connection->ssl_recv_buf_size, limit);
		memset(&m_olRecv.m_ol, 0, sizeof(m_olRecv.m_ol));

		DWORD flags = 0;
        ref();
		int ret = WSARecv(m_socketFd, &m_olRecv.m_wsaBuffer, 1, &recvbyte, &flags, &m_olRecv.m_ol, NULL);
		if (ret == 0)
		{
			return 1;
		}
		else
		{
			int err = WSAGetLastError();

			if (err == WSA_IO_PENDING)
			{
				return 1;
			}
            unref();
			DestroySocket(15);
			return 0;
		}
	}
	else
	{
		net_buf_pos_t* net_pos = recv_buf->get_recv_buf(io_thread_data);

		if (NULL == net_pos)
		{
			DestroySocket(16);
			return 0;
		}

		DWORD recvbyte = 0;
		m_olRecv.m_wsaBuffer.buf = (char*)net_pos->_buf;
		m_olRecv.m_wsaBuffer.len = std::min(net_pos->_size, limit);
		memset(&m_olRecv.m_ol, 0, sizeof(m_olRecv.m_ol));

		DWORD flags = 0;
        ref();
		int ret = WSARecv(m_socketFd, &m_olRecv.m_wsaBuffer, 1, &recvbyte, &flags, &m_olRecv.m_ol, NULL);
		if (ret == 0)
		{
			return 1;
		}
		else
		{
			int err = WSAGetLastError();

			if (err == WSA_IO_PENDING)
			{
				return 1;
			}

            unref();
			DestroySocket(17);
			return 0;
		}
	}
}

int PlatformSocket::GetSockError(WSAOVERLAPPED* pWSAOVERLAPPED)
{
	DWORD dwTrans;
	DWORD dwFlags;
	if (FALSE == WSAGetOverlappedResult(m_socketFd, pWSAOVERLAPPED, &dwTrans, FALSE, &dwFlags))
	{
		return WSAGetLastError();
	}
	else
	{
		return NetlibError_None;
	}

}

int32_t PlatformSocket::SendDirect(CBuffer* send_buf, const char* buf, uint32_t size)
{
	ScopedLock<PlatformMutex> lock(m_mutex);
	if (false == send_buf->AddTcpBuffer((const uint8_t*)buf, size))
	{
		return NetlibError_BufferError;
	}

	const uint8_t* data = send_buf->GetTcpBuffer();
	uint32_t data_size = send_buf->GetTcpLength();

	int ret;
	m_sendbyte = 0;

	memset(&m_olSend.m_ol, 0, sizeof(m_olSend.m_ol));
	m_olSend.m_wsaBuffer.buf = (CHAR*)data;
	m_olSend.m_wsaBuffer.len = data_size;
    ref();
	ret = WSASend(m_socketFd, &m_olSend.m_wsaBuffer, 1, &m_sendbyte, 0, &m_olSend.m_ol, NULL);

	if (ret == 0)
	{
		return 0;
	}
	else
	{
		int err = WSAGetLastError();

		if (err == WSA_IO_PENDING)
		{
			return 0;
		}

        unref();
		DestroySocket(18);
		return NetlibError_SocketError;
	}
	return NetlibError_None;
}


int32_t PlatformSocket::ssl_transfer()
{
	if (_is_ssl)
	{
		if (0 == _ssl_connection->handshaked)
		{
			return NetlibError_None;
		}
		CBuffer* ssl_buffer = get_ssl_buffer();
		CBuffer* send_buffer = get_send_buffer();

		const uint8_t* buf = send_buffer->GetTcpBuffer();
		uint32_t size = send_buffer->GetTcpLength();

		if (0 == size)
		{
			return NetlibError_None;
		}

		int bytes = SSL_write(_ssl_connection->connection, buf, size);

		if (bytes <= 0)
		{
			int sslerr = SSL_get_error(_ssl_connection->connection, bytes);
			if (ssl_is_fatal_error(sslerr))
			{
				return 0;
			}
			DestroySocket(19);
			return NetlibError_SSL_Error;
		}

		send_buffer->ReleaseTcpBuffer(bytes);

		char tmp_buffer[1024 * 10];
		while (BIO_pending(_ssl_connection->bio_out))
		{
			int bytes = BIO_read(_ssl_connection->bio_out, tmp_buffer, sizeof(tmp_buffer));
			if (bytes > 0)
			{
				ScopedLock<PlatformMutex> lock(m_mutex);
				if (false == ssl_buffer->AddTcpBuffer((const uint8_t*)tmp_buffer, bytes))
				{
					return NetlibError_BufferError;
				}
			}
			else
			{
				int ssl_error = SSL_get_error(_ssl_connection->connection, bytes);
				if (ssl_is_fatal_error(ssl_error))
				{
					DestroySocket(20);
					return NetlibError_SSL_Error;
				}
			}
		}
	}

	return NetlibError_None;
}

bool PlatformSocket::RecvData(struct IOThredData* io_thread_data, OVERLAPPEDPLUS* olrecv, uint32_t size)
{
    if (this->m_socketFd == INVALID_SOCKET)
    {
        return false;
    }
    ScopedLock<PlatformMutex> lock(m_mutex);
	const char* buf = olrecv->m_wsaBuffer.buf;
	if (_is_ssl)
	{
        //printf("ssl recv data:size:%d\n", size);
		int bytes = BIO_write(_ssl_connection->bio_in, buf, size);
		if (bytes != size)
		{
			int ssl_error = SSL_get_error(_ssl_connection->connection, bytes);
			printf("ssl_error:%d\n", ssl_error);
		}

		INetBuffer* recv_buf = get_recv_buffer();

		bool connect_event = false;
		bool have_send = false;
		for (;;)
		{
            net_buf_pos_t* net_pos = recv_buf->get_recv_buf(io_thread_data);

            if (NULL == net_pos)
            {
                WARNING_LOG("[net_handle:%llu]recv buffer flow", _handle);
                DestroySocket(21);
                return false;
            }

			int sslbytes = SSL_read(_ssl_connection->connection, net_pos->_buf, net_pos->_size);
 
			if (0 == _ssl_connection->handshaked)
			{
				if (SSL_is_init_finished(_ssl_connection->connection))
				{
					_ssl_connection->handshaked = 1;
					m_is_connected = true;

					connect_event = true;
				}
			}

			
			if (sslbytes > 0)
			{
				OnRecv(net_pos->_buf, sslbytes);
			}
			else
			{
				int sslerr = SSL_get_error(_ssl_connection->connection, sslbytes);

				if (ssl_is_fatal_error(sslerr))
				{
					DestroySocket(22);
					return false;
				}

				if (BIO_pending(_ssl_connection->bio_out))
				{
					int bytes = BIO_read(_ssl_connection->bio_out, io_thread_data->_recv_buffer, io_thread_data->_recv_buffer_size);
					int ssl_error = SSL_get_error(_ssl_connection->connection, bytes);
					if (bytes > 0)
					{
						CBuffer* ssl_buffer = get_ssl_buffer();
						SendDirect(ssl_buffer, io_thread_data->_recv_buffer, bytes);
						have_send = true;
					}
					else if (ssl_is_fatal_error(ssl_error))
					{
						DestroySocket(23);
						return false;
					}
				}
				else
				{
					break;
				}
			}

		}
		bool ret = Recv(io_thread_data);

        if (!ret)
        {
            return false;
        }
		if (connect_event)
		{
			_session->OnConnected(_handle, _sessionData);

			if(!have_send)
				Send();
		}
		return true;
	}
	else
	{
		if (m_protocol == NETPROTOCOL_UDP)
		{
			OnRecvUdp(buf, size, olrecv->m_remoteAddr.addr(), olrecv->m_remoteAddrLen);
		}
		else
		{
			OnRecv(buf, size);
		}
		return Recv(io_thread_data);
	}
}

int32_t PlatformSocket::WriteSome(const void* buf, uint32_t size)
{
	/*if (size <= 0)
	{
		return DY_NET_OK;
	}

	if (_is_ssl)
	{
		int n = SSL_write(_ssl_connection->connection, buf, size);
		if (n > 0)
		{
			return n;
		}
		else
		{
			int sslerr = SSL_get_error(_ssl_connection->connection, n);
			if (sslerr == SSL_ERROR_WANT_WRITE)
			{
				return DY_NET_AGAIN;
			}
			return DY_NET_ERROR;
		}
	}
	else
	{
		int ret;
		m_sendbyte = 0;

		memset(&m_olSend.m_ol, 0, sizeof(m_olSend.m_ol));
		m_olSend.m_wsaBuffer.buf = (CHAR*)buf;
		m_olSend.m_wsaBuffer.len = size;
		ret = WSASend(m_socketFd, &m_olSend.m_wsaBuffer, 1, &m_sendbyte, 0, &m_olSend.m_ol, NULL);

		if (ret == 0)
		{
			return 0;
		}
		else
		{
			int err = WSAGetLastError();

			if (err == WSA_IO_PENDING)
			{
				return 0;
			}
			DestroySocket(23);
			return -1;
		}
	}
    */
    return 0;
}

