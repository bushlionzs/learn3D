#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>

#include <net_define.h>
#include <platform_socket.h>
#include <platform_io.h>
#include <platform_log.h>
#include <net_stat.h>
#include <inet_session.h>
#include <netlib_error.h>
#include <platform.h>


extern struct NetLibParam g_param;

bool PlatformSocket::PlatformSocketInit()
{
	return true;
}

PlatformSocket::PlatformSocket( INetSession* session, NetProtocol protocol, const SessionData& sessionData)
{
	_session			  = session;
	this->m_socketFd         = -1;
	this->m_protocol          = protocol;
	_sessionData       = sessionData;
	this->m_IsListeningSocket = false;
	this->bufferDataLen       = 0;
	_handle			  = INVALID_NET_HANDLE;
    
#ifndef DY_NETWORK_DISNABLE_SSL
    _is_ssl = session->is_ssl();
#endif
    
    _ssl_connection = NULL;
    
    m_is_connected = false;
	
	_magic = -1;
	_send_bytes = 0;
	_recv_bytes = 0;
}


PlatformSocket::~PlatformSocket()
{
	DestroySocket(1);
	if (_ssl_connection != NULL)
	{
		destroy_ssl_connection(_ssl_connection);
		_ssl_connection = NULL;
	}
	_session->on_release(_handle, _sessionData);
}

int PlatformSocket::GetSocketType(NetProtocol protocol)
{
	switch( protocol )
	{
	case NETPROTOCOL_TCP:
		return SOCK_STREAM;
	case NETPROTOCOL_UDP:
	case NETPROTOCOL_QUIC:
		return SOCK_DGRAM;
	default://NETPROTOCOL_RAWIP
		return SOCK_RAW;
	}
}

int PlatformSocket::GetSocketProtocol(NetProtocol protocol)
{
	switch( protocol )
	{
	case NETPROTOCOL_TCP:
		return IPPROTO_TCP;
	case NETPROTOCOL_UDP:
	case NETPROTOCOL_QUIC:
		return IPPROTO_UDP;
	default://NETPROTOCOL_RAWIP
		return IPPROTO_UDP|IPPROTO_ICMP|IPPROTO_IP;
	}
}

bool PlatformSocket::CreateSocketOnly(void* socketHandle)
{
	if (m_protocol == NETPROTOCOL_INVALID)
	{
		return false;
	}
    
    if (NULL == socketHandle)
    {
        int sockettype     = GetSocketType(m_protocol);
        int socketprotocol = GetSocketProtocol(m_protocol);

        _sessionData.check_inet_family();
		m_socketFd = socket(_sessionData.m_family, sockettype, socketprotocol);


        if (-1 == m_socketFd)
        {
            FATAL_LOG("[err:%d,sockettype:%d]socket error", errno, sockettype);
            return false;
        }
		
		NOTICE_LOG("create socket:%d, protocol:%d", m_socketFd, m_protocol);
    }
    else
    {
        int* socketHandleToSet =  (int*)socketHandle;
        m_socketFd = *socketHandleToSet;
    }
	return true;
}

bool PlatformSocket::MakeSocketNonBlocking()
{
	int flags = fcntl(this->m_socketFd, F_GETFL, 0);

	if (flags == -1)
	{
		return false;
	}

	flags |= O_NONBLOCK;
	int setResult = fcntl(this->m_socketFd, F_SETFL, flags);
	if (setResult == -1)
	{
		return false;
	}

	return true;
}

bool PlatformSocket::UpdateIpInfo()
{
    dy_network::SockaddrStorage local;
    socklen_t len = sizeof(local);
    int nRet = getsockname(m_socketFd, local.addr(), &len);
    if (nRet == 0)
    {
        if (local.get_ip_string(_sessionData.m_LocalIP)
            && local.get_port(_sessionData.m_LocalPort))
        {
            return true;
        }
    }

    return false;
}

bool PlatformSocket::UpdateRawIpInfo()
{
	return true;
}

bool PlatformSocket::CreateSocket( )
{
	if (false == CreateSocketOnly(NULL))
	{
		return false;
	}

	int sockettype = GetSocketType(m_protocol);
	
	
	if (false == UpdateRawIpInfo())
	{
		return false;
	}

	if (_sessionData.m_LocalIP.empty() == false || _sessionData.m_LocalPort != 0)
	{
        dy_network::SockaddrStorage local;
        if (!local.init(_sessionData.get_local_ip(), _sessionData.m_LocalPort))
        {
            DestroySocket(2);
            return false;
        }

        unsigned value = 1;
        setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

        if ((SOCK_STREAM == sockettype) && ((_sessionData.m_PeerIP.empty() == true || _sessionData.m_PeerPort == 0)) 
            && (_session->is_server_reuse_port()))
        {
            setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value));
        }

        if (_sessionData.m_reuse_port)
        {
            setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value));
        }

        int ipv6_only = _sessionData.m_ipv6_only ? 1 : 0;
        setsockopt(m_socketFd,
            IPPROTO_IPV6,
            IPV6_V6ONLY,
            reinterpret_cast<const char *>(&ipv6_only),
            sizeof(int)
        );

		int nRet = bind( m_socketFd , local.addr(), local.size());
		if (-1 == nRet)
		{
            WARNING_LOG("[err:%d]bind error, port[%u]", errno, _sessionData.m_LocalPort);
			DestroySocket(3);
			return false;
		}
	}
	
	if (SOCK_STREAM == sockettype)
	{
		if (_sessionData.m_PeerIP.empty() == true || _sessionData.m_PeerPort == 0)
		{
			if (false == MakeSocketNonBlocking())
			{
                WARNING_LOG("[err:%d]MakeSocketNonBlocking error", errno);
				DestroySocket(4);
				return false;
			}

			int nRet = listen(m_socketFd, g_param._max_queuing_connection_number);

			if (-1 == nRet)
			{
                WARNING_LOG("[err:%d]listen error", errno);
				DestroySocket(5);
				return false;
			}
			this->m_IsListeningSocket = true;

            this->UpdateIpInfo();
		}
		else
		{
            dy_network::SockaddrStorage peer;
            if (!peer.init(_sessionData.m_PeerIP.c_str(), _sessionData.m_PeerPort))
            {
                WARNING_LOG("[err:%d]inet_addr error", errno);
                DestroySocket(6);
                return false;
            }
			
			if (false == SetSocketOption())
			{
                WARNING_LOG("[err:%d]SetSocketOption error", errno);
				DestroySocket(7);
				return false;
			}

			int nRet             = connect(m_socketFd,  peer.addr(), peer.size());

			if (-1 == nRet)
			{
				int err = errno;
				if (err != EINPROGRESS)
				{
                    WARNING_LOG("[err:%d]connect error", errno);
                    DestroySocket(8);
					return false;
				}
			}


			if (false == UpdateIpInfo())
			{
                WARNING_LOG("[err:%d]UpdateIpInfo error", errno);
				DestroySocket(9);
				return false;
			}
            
            if (_is_ssl)
            {
                if (NULL == _ssl_connection)
                {
                    _ssl_connection = create_ssl_connection(m_socketFd, true);
                }
            }
		}
	}
	else
	{
		if (false == SetSocketOption())
		{
            WARNING_LOG("[err:%d]SetSocketOption error", errno);
			DestroySocket(10);
			return false;
		}
		this->UpdateIpInfo();
	}

	return true;
}

bool PlatformSocket::OnConnected()
{
	if (m_socketFd < 0)
	{
		return false;
	}

    if (_is_ssl) 
    {
        if (0 == _ssl_connection->handshaked)
        {
            int ret = ngx_ssl_handshake(_ssl_connection);
            if (ret != 0 && ret != EAGAIN)
            {
                return false;
            }
            
            if (ret == EAGAIN)
            {
                return false;
            }
            
            if (1 == _sessionData.m_is_client)
            {
                _session->OnConnected(_handle, _sessionData);
            }
        }
    }
    return true;
}

bool PlatformSocket::set_tcp_keepalive(const TcpKeepAliveOption *options)
{
    int keepalive = options ? 1 : 0;
    int ret = setsockopt(m_socketFd, SOL_SOCKET, SO_KEEPALIVE, (void*)&keepalive, sizeof(keepalive));
    if (ret < 0)
    {
        WARNING_LOG("[fd:%zu,ret:%d,err:%d]setsockopt SO_KEEPALIVE", m_socketFd, ret, errno);
        return false;
    }

    if (!options)
    {
        NOTICE_LOG("[fd:%zu] disenable tcp keepalive", m_socketFd);
        return true;
    }

    if (options->idle_sec > 0)
    {
        ret = setsockopt(m_socketFd, IPPROTO_TCP, TCP_KEEPALIVE, (void*)&options->idle_sec, sizeof(options->idle_sec));
        if (ret < 0)
        {
            WARNING_LOG("[fd:%zu,ret:%d,err:%d]setsockopt TCP_KEEPIDLE", m_socketFd, ret, errno);
            return false;
        }
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

bool PlatformSocket::AcceptSocket(PlatformSocket* client)
{
    dy_network::SockaddrStorage clientAddress;
	socklen_t   clientAddressLen = sizeof(clientAddress);
	

	int fd = accept(this->m_socketFd, clientAddress.addr(), &clientAddressLen);
    
	if (fd >= 0)
	{
        clientAddress.get_ip_string(client->_sessionData.m_PeerIP);
        clientAddress.get_port(client->_sessionData.m_PeerPort);
        client->_sessionData.m_LocalPort = _sessionData.m_LocalPort;

		client->m_socketFd = fd;
		client->SetSocketOption();
        client->UpdateIpInfo();
        
        if (client->_is_ssl)
        {
            if (NULL == client->_ssl_connection)
            {
                client->_ssl_connection = create_ssl_connection(fd);
            }
        }
	} 
	else
	{
        if (errno != EAGAIN)
        {
            FATAL_LOG("AcceptSocket error: %d", errno);
        }
        
		return false;
	}
	return true;
}

bool PlatformSocket::DestroySocket(int magic)
{
    if (m_socketFd >= 0)
    {
        ScopedLock<PlatformMutex> lock(_recv_mutex);
        if (m_socketFd >= 0)
        {
            NOTICE_LOG("nethandle:%lu, m_protocol:%d, DestroySocket, magic:%d, err:%d", 
                        _handle, m_protocol, magic, errno);
            PlatformIO::GetInstance()->UnBindSocket(this);
            shutdown(m_socketFd, SHUT_WR);
            close(m_socketFd);
            m_socketFd = -1;
			_magic = magic;
            
            OnClose();
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
	if (m_socketFd >= 0)
	{
		ref();
		IOEvent ev;
		ev._event = EVENT_DELAY_CLOSE;
		ev._self = this;
		PlatformIO::GetInstance()->PostEvent(_handle, ev);
	}
	return true;
}

bool PlatformSocket::DelaySendData()
{
	if (m_socketFd >= 0)
	{
		ref();
		IOEvent ev;
		ev._event = EVENT_DELAY_SEND;
		ev._self = this;
		PlatformIO::GetInstance()->PostEvent(_handle, ev);
	}
	return true;
}

bool PlatformSocket::DelayRecvData()
{
	if (m_socketFd >= 0)
	{
		ref();
		IOEvent ev;
		ev._event = EVENT_DELAY_RECV;
		ev._self = this;
		PlatformIO::GetInstance()->PostEvent(_handle, ev);
	}
	return true;
}

bool PlatformSocket::SetSocketOption()
{		
	return MakeSocketNonBlocking();
}

void PlatformSocket::OnSend(uint32_t)
{
}

bool PlatformSocket::OnAccept()
{
    return false;
}

void PlatformSocket::OnClose()
{
	_session->OnClose(_handle, _sessionData);
}


void PlatformSocket::get_stat_info(net_lib_stat_t& info)
{
	info._recv_bytes = _recv_bytes;
	info._send_bytes = _send_bytes;
}

int32_t PlatformSocket::Send(const uint8_t*, uint32_t, SndData*)
{
	return NetlibError_SocketError;
}



bool PlatformSocket::recreate_udpsocket()
{
    if (m_socketFd >= 0)
	{
		close(m_socketFd);
	}
	
    m_socketFd = socket(_sessionData.m_family, SOCK_DGRAM, IPPROTO_UDP);
	
	if (m_socketFd == -1)
	{
		WARNING_LOG("[err:%d]recreate_udpsocket failed", errno);
		return false;
	}
	
    if (false == SetSocketOption())
    {
		WARNING_LOG("[err:%d,socket:%d]SetSocketOption error", errno, m_socketFd);
		DestroySocket(71);
		return false;
	}
    
    UpdateIpInfo();
	
	PlatformIO::GetInstance()->BindSocket(this);
	NOTICE_LOG("[socket:%d,ip:%s,port:%d]recreate udp socket", 
                m_socketFd, _sessionData.m_LocalIP.c_str(), _sessionData.m_LocalPort);
	
	return true;
}

int PlatformSocket::SendUdp(const uint8_t* data, uint32_t size, const sockaddr *addr, int addrlen)
{
	if (this->m_socketFd < 0 )
	{
		return -1;
	}

	int times = 0;
	for (;;)
    {
		int sendResult = sendto(this->m_socketFd, data, size, 0, addr, addrlen);

		if (sendResult > 0)
        {
            if (sendResult != size)
            {
                WARNING_LOG("sendto() incomplete");
                return -1;
            }

            return sendResult;
        }

        int errorCode = errno;
        if(errorCode == EWOULDBLOCK)
        {
            return 0;
        }

        if (errorCode == EINTR)
        {
            continue;
        }
		
		if (errorCode == EPIPE)
		{
			if (recreate_udpsocket())
			{
				times++;
				if (times >= 3)
				{
					return -1;
				}
				continue;
			}
		}
		NOTICE_LOG("sendto failed, fd:%d, err:%d, handle:%" PRIu64 "", m_socketFd, errorCode, _handle);
        return -1;
	}
}


int PlatformSocket::SendTcp(const uint8_t* data , uint32_t size)
{
	if (m_socketFd < 0)
	{
		return NetlibError_SocketError;
	}
    
    if (_is_ssl)
    {
        int n = SSL_write(_ssl_connection->connection, data, size);
        if (n > 0)
        {
            return n;
        }
        else
        {
            int sslerr = SSL_get_error(_ssl_connection->connection, n);
            
            if (sslerr == SSL_ERROR_WANT_WRITE)
            {
                return 0;
            }
            DestroySocket(12);
            return -1;
        }
    }
    else
    {
        int sendResult = send(this->m_socketFd, data, size, 0);

        if (sendResult > 0)
        {
            return sendResult;
        }
        else
        {
            int errorCode = errno;

            if( errorCode == EWOULDBLOCK ||
                errorCode == EINTR)
            {
                return 0;
            }

            FATAL_LOG("[handle:%llu]send err: %d", _handle, errorCode);

            DestroySocket(13);
            return -1;
        }
    }
}

bool PlatformSocket::RecvUdp(struct IOThredData* io_thread_data, INetBuffer* recv_buf)
{
	if (m_socketFd < 0)
	{
		return false;
	}
	
	net_buf_pos_t* net_pos = recv_buf->get_recv_buf(io_thread_data);
            
	if (NULL == net_pos)
	{
		WARNING_LOG("[net_handle:%lu]recv buffer flow", _handle);
		DestroySocket(14);
		return false;
	}
	ScopedLock<PlatformMutex> lock(_recv_mutex);
	while( true )
	{
        dy_network::SockaddrStorage peerAddr;
        socklen_t   peerAddrLen = sizeof(peerAddr);

		int recvResult = recvfrom(this->m_socketFd, net_pos->_buf, net_pos->_size, 0, peerAddr.addr(),&peerAddrLen);

		/*These calls return the number of bytes received, or -1 if an error
		occurred.  The return value will be 0 when the peer has performed an
		orderly shutdown.*/

		switch (recvResult)
		{
		case -1:
		{
			if( errno != EAGAIN )
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		break;
		case 0:
			{
				return false;
			}
			break;
		default:
			{
                peerAddr.get_ip_string(_sessionData.m_PeerIP);
                peerAddr.get_port(_sessionData.m_PeerPort);

				OnRecvUdp(net_pos->_buf, recvResult, peerAddr.addr(), peerAddrLen);
				
			}
			break;
		}
	
	}

	return true;
}


bool PlatformSocket::RecvTcp(struct IOThredData* io_thread_data, INetBuffer* recv_buf, uint32_t limit)
{
	if (m_socketFd < 0)
	{
		return false;
	}
    
    
    if (_is_ssl)
    {   
        if (0 == _ssl_connection->handshaked)
        {
            int ret = ngx_ssl_handshake(_ssl_connection);
           
            if (ret != 0 && ret != EAGAIN)
            {
                return false;
            }
            
            if (ret == EAGAIN)
            {
                return true;
            }
            
            if (1 == _sessionData.m_is_client)
            {
                _session->OnConnected(_handle, _sessionData);
            }
        }
        ScopedLock<PlatformMutex> lock(_recv_mutex);
        while (true)
        {
            net_buf_pos_t* net_pos = recv_buf->get_recv_buf(io_thread_data);
            
            if (NULL == net_pos)
            {
                WARNING_LOG("[net_handle:%lu]recv buffer flow", _handle);
                DestroySocket(15);
                return false;
            }
            int recvResult = SSL_read(_ssl_connection->connection, net_pos->_buf, net_pos->_size);
                        
            switch (recvResult)
            {
            case -1:
            {
                if (errno != EAGAIN)
                {
                    DestroySocket(16);
                    return false;
                }
                else
                {
                    return true;
                }
            }
            break;
            case 0:
                {
                    DestroySocket(17);
                    return false;
                }
                break;
            default:
                {
                    this->bufferDataLen = recvResult;
                    if (false == recv_buf->recv_data(net_pos->_buf, recvResult, _sessionData))
					{
						DestroySocket(18);
					}
                }
            }
        }

    }
    else
    {
        ScopedLock<PlatformMutex> lock(_recv_mutex);
        while (true)
        {
            net_buf_pos_t* net_pos = recv_buf->get_recv_buf(io_thread_data);
            
            if (NULL == net_pos)
            {
                DestroySocket(19);
                return false;
            }
            
            int recvResult = recv(this->m_socketFd, net_pos->_buf, net_pos->_size, 0);
            
            switch (recvResult)
            {
            case -1:
            {
                if (errno != EAGAIN)
                {
                    DestroySocket(20);
                    return false;
                }
                else
                {
                    return true;
                }
            }
            break;
            case 0:
                {
                    DestroySocket(21);
                    return false;
                }
                break;
            default:
                {
                    this->bufferDataLen = recvResult;
					_recv_bytes += recvResult;
                    if (false == recv_buf->recv_data(net_pos->_buf, recvResult, _sessionData))
					{
						DestroySocket(22);
					}
					
					limit -= recvResult;
					if(0 == limit)
					{
						return 2;
					}
                }
            }
        }
    }

	return true;
}

bool PlatformSocket::IsValid() const
{
    if (m_socketFd < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


int32_t PlatformSocket::WriteSome(const void* buf, uint32_t size)
{
    if (size <= 0)
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
        int ret = write(m_socketFd, buf, size);
        if (ret <= 0)
        {
            int err = errno;
            if (EINTR == err)
            {
                return DY_NET_INTR;
            }

            if (EAGAIN == err)
            {
                return DY_NET_AGAIN;
            }
            return DY_NET_ERROR;
        }
        return ret;
    }

}

int32_t PlatformSocket::WriteV(const iovec* io_vec, uint32_t size)
{
    if (0 == size)
    {
        return DY_NET_OK;
    }

    if (_is_ssl)
    {
        int ret = DY_NET_OK;
        int done = 0;
        int i = 0;
        for (; i < size; ++i)
        {
            ret = WriteSome(io_vec[i].iov_base, io_vec[i].iov_len);
            if (ret > 0)
            {
                done += ret;
            }
            else if (ret == DY_NET_AGAIN || ret == DY_NET_INTR)
            {
                break;
            }
            else
            {
                return ret;
            }
        }
        if (done == 0)
        {
            //EAGAIN || EINTR
            return ret;
        }
        else
        {
            return done;
        }
    }
    else
    {
        int ret = writev(m_socketFd, io_vec, size);
        if (ret <= 0)
        {
            int err = errno;
            if (err == EAGAIN)
            {
                return DY_NET_AGAIN;
            }
            if (err == EINTR)
            {
                return DY_NET_INTR;
            }
            return DY_NET_ERROR;
        }
        return ret;
    }
}
