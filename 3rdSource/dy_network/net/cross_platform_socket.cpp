#include "cross_platform_socket.h"
#include <assert.h>
#include <net_lib.h>
#include <net_manager.h>
#include <net_buffer.h>
#include <platform.h>
#include <netlib_error.h>
#include <inet_session.h>
#include <platform_io.h>
#include <platform_log.h>
#include <math_util.h>
#include <rate_limiter.h>
#include <net_stat.h>


///////////////////////////////////////////////////////////

#ifdef _WIN32
#pragma warning(disable:4127)
#endif

extern struct NetLibParam g_param;


#define DEFAULT_BUFFER_SIZE 1024 * 32

ServerSocket::ServerSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
:PlatformSocket(session, protocol, sessionData)
{
    _tmp = NULL;
}

ServerSocket::~ServerSocket()
{

}

PlatformSocket* ServerSocket::CreateAcceptSocket(void* socket)
{
	PlatformSocket* obj = NULL;
	
	obj = new ServerTcpClientSocket(_session, m_protocol, _sessionData);

#ifdef _WIN32
	if (false == obj->CreateSocketOnly(socket))
	{
		delete obj;
		obj = NULL;
	}

	if (NULL != obj)
	{
		if (false == obj->SetSocketOption())
		{
			delete obj;
			obj = NULL;
		}
	}
#endif //WIN32
	
	return obj;
}


bool ServerSocket::Recv(struct IOThredData* io_thread_data)
{
#ifdef _WIN32

	if (NULL == _tmp)
	{
		_tmp = CreateAcceptSocket(NULL);
	}

	if (!AcceptSocket(_tmp))
	{
		return false;
	}
	else
	{
		_tmp = NULL;
		return true;
	}
	
#else
	while (true)
	{
		if (NULL == _tmp)
		{
			_tmp = CreateAcceptSocket(NULL);
		}

		if (!AcceptSocket(_tmp))
		{
			break;
		}
		else
		{
			if (!_tmp->OnAccept())
			{
				WARNING_LOG("OnAccept err, maybe no Handle left:%d", 0);
				delete _tmp;
			}
			_tmp = NULL;

		}
	}
#endif
    
    
    return true;
}



ServerTcpClientSocket::ServerTcpClientSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
:TcpSocket(session ,protocol , sessionData)
{
    _sessionData.m_is_client = 0;
    m_is_connected = true;
}

ServerTcpClientSocket::~ServerTcpClientSocket()
{
}

bool ServerTcpClientSocket::OnAccept()
{
	if (_handle == INVALID_NET_HANDLE)
	{
		NetManager::GetInstance()->allocNetHandle(this);

        
        if (_handle == INVALID_NET_HANDLE)
        {
            return false;
        }
	}
	else
	{
		assert(false);
        return false;
	}
	TcpSocket::OnAccept();
    if (!m_recvBuffer->OnHandle(_handle, _sessionData))
    {
        return false;
    }
	DEBUG_LOG("[handle:%llu]accept tcp client", _handle);
	_session->OnAccept(_handle, _sessionData);

    return true;
}


TcpClientSocket::TcpClientSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
:TcpSocket(session, protocol, sessionData)
{
    _sessionData.m_is_client = 1;
	m_is_connected = false;
}

TcpClientSocket::~TcpClientSocket()
{
}

int32_t TcpClientSocket::Send()
{
#ifndef _WIN32
    if (false == m_is_connected)
    {
        ScopedLock<PlatformMutex> lock(m_mutex);
        if (PlatformSocket::OnConnected())
        {
            m_is_connected = true;    
        }
        else
        {
            return NetlibError_None;
        }
        if (!_is_ssl)
        {
            _session->OnConnected(_handle, _sessionData);
        }
    }
#endif
	return TcpSocket::Send();
}


bool TcpClientSocket::OnInit()
{
    if (!m_recvBuffer->OnHandle(_handle, _sessionData))
    {
        return false;
    }
	return true;
}

///////////////////////////////////////////////////////////
TcpSocket::TcpSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
:PlatformSocket(session, protocol, sessionData)
, m_sendBuffer(NULL)
, m_recvBuffer(NULL)
{
    m_is_connected = false;

    uint32_t recv_buffer_size = _session->get_send_buffer_size(_sessionData);

    recv_buffer_size = next_pow_of_2(recv_buffer_size);

    bool delete_flag = false;
    
    m_sendBuffer = new(std::nothrow) CBuffer(recv_buffer_size);
#ifdef _WIN32
    if (_is_ssl)
    {
        m_sslBuffer = new(std::nothrow) CBuffer(recv_buffer_size);
    }
    else
    {
        m_sslBuffer = NULL;
    }
#endif
    m_recvBuffer = _session->create_recv_buffer(_sessionData);
   
}

TcpSocket::~TcpSocket()
{
#ifdef _WIN32
    if (m_sslBuffer)
    {
        delete m_sslBuffer;
        m_sslBuffer = NULL;
    }
#endif

	if (m_sendBuffer)
	{
		delete m_sendBuffer;
		m_sendBuffer = NULL;
	}

	if (m_recvBuffer)
	{
		delete m_recvBuffer;
		m_recvBuffer = NULL;
	}
}

void TcpSocket::OnSend(uint32_t ioSize)
{
    ScopedLock<PlatformMutex> lock(m_mutex);
#ifdef _WIN32
    _send_bytes += ioSize;
    incr_send_data_size(ioSize);
    if (_is_ssl)
    {
        if (ioSize > 0)
        {
            m_sslBuffer->ReleaseTcpBuffer(ioSize);
        }
		
        SendNolock();
	}
	else
	{
        if (ioSize > 0)
        {
            m_sendBuffer->ReleaseTcpBuffer(ioSize);
            SendNolock();
        }
	}
#else
    if (m_sendBuffer)
    {
        m_sendBuffer->ReleaseTcpBuffer(ioSize);
    }
#endif
}

int32_t TcpSocket::Send(const uint8_t* data, uint32_t size, SndData* params)
{
#ifndef _WIN32
    {
        ScopedLock<PlatformMutex> lock(m_mutex);
        bool isEmpty = m_sendBuffer->IsEmpty();
        if (m_socketFd == -1)
        {
            return NetlibError_SocketError;
        }

        if (!m_sendBuffer->AddTcpBuffer(data, size))
        {
            return NetlibError_BufferError;
        }

        if (!m_is_connected)
        {
            return NetlibError_None;
        }
        if (isEmpty)
        {
            DelaySendData();
        }
    }

    return NetlibError_None;
#else

    ScopedLock<PlatformMutex> lock(m_mutex);
    bool isEmpty = m_sendBuffer->IsEmpty();

    if (!m_sendBuffer->AddTcpBuffer(data, size))
    {
        return NetlibError_BufferError;
    }

    if (!m_is_connected)
    {
        return NetlibError_None;
    }

    if (_is_ssl)
    {
        isEmpty = m_sslBuffer->IsEmpty();
        if (isEmpty)
        {
            DelaySendData();
        }
        return NetlibError_None;
    }
    else
    {
        if (isEmpty)
        {
            DelaySendData();
        }
        return NetlibError_None;
    }

#endif
}



int32_t TcpSocket::Send()
{
    ScopedLock<PlatformMutex> lock(m_mutex);
    return SendNolock();
}

int32_t limiter_sender_callback(platform_timer_t, void* timer_self, void* timer_param)
{
    PlatformSocket* ps = (PlatformSocket*)timer_param;
    ps->DelaySendData();
    ps->unref();
    return -1;
}

int32_t limiter_recv_callback(platform_timer_t, void* timer_self, void* timer_param)
{
    PlatformSocket* ps = (PlatformSocket*)timer_param;
    ps->DelayRecvData();
    ps->unref();
    return -1;
}

int32_t TcpSocket::SendNolock()
{
#ifndef _WIN32
    while (m_sendBuffer)
	{
		const uint8_t* buf = m_sendBuffer->GetTcpBuffer();
		uint32_t size = m_sendBuffer->GetTcpLength();
		if( size == 0 )
        {
            return NetlibError_None;
        }

        if (_limiter)
        {
            uint64_t tokens = _limiter->get_tokens();
            if (tokens == 0)
            {
                ref();
                platform_timer_t id = platform_create_timer(100, limiter_sender_callback, nullptr, this);
                if (id == INVALID_TIMER_ID)
                {
                    unref();
                    WARNING_LOG("platform_create_timer failed");
                }
                return NetlibError_None;
            }
            else
            {
                uint32_t current = std::min(size, (uint32_t)tokens);

                _limiter->release_tokens(current);
                int ret = PlatformSocket::SendTcp(buf, current);
                if (ret < 0)
                {
                    return NetlibError_SocketError;
                }
                m_sendBuffer->ReleaseTcpBuffer(ret);
            }
        }
        else
        {
            int ret = PlatformSocket::SendTcp(buf, size);
            if (ret == 0)
            {
                break;
            }
            if (ret < 0)
            {
                return NetlibError_SocketError;
            }
            m_sendBuffer->ReleaseTcpBuffer(ret);
        }
			
		
        if (m_sendBuffer->IsEmpty())
        {
			if (IsValid())
			{
				_session->on_send_bytes(_handle, _sessionData, _send_bytes);
			}
            
        }
	}

	return NetlibError_None;
#else
	if (_is_ssl)
	{
		ssl_transfer();
		const uint8_t* buf = m_sslBuffer->GetTcpBuffer();
		uint32_t size = m_sslBuffer->GetTcpLength();
		if (size > 0)
		{
			int ret = PlatformSocket::SendTcp(buf, size);
			if (ret < 0)
			{
				return NetlibError_SocketError;
			}
		}
        else
        {
            _session->on_send_bytes(_handle, _sessionData, _send_bytes);
        }
	}
	else
	{
        const uint8_t* buf = m_sendBuffer->GetTcpBuffer();
        uint32_t size = m_sendBuffer->GetTcpLength();
        if (size > 0)
        {
            if (_limiter)
            {
                uint64_t tokens = _limiter->get_tokens();
                if (tokens == 0)
                {
                    ref();
                    platform_timer_t id = platform_create_timer(100, limiter_sender_callback, nullptr, this);
                    if (id == INVALID_TIMER_ID)
                    {
                        unref();
                        WARNING_LOG("platform_create_timer failed");
                    }
                }
                else
                {
                    uint32_t current = std::min(size, (uint32_t)tokens);

                    _limiter->release_tokens(current);
                    int ret = PlatformSocket::SendTcp(buf, current);
                    if (ret < 0)
                    {
                        return NetlibError_SocketError;
                    }
                }
            }
            else
            {
                int ret = PlatformSocket::SendTcp(buf, size);
                if (ret < 0)
                {
                    return NetlibError_SocketError;
                }
            }
            
        }
        else
        {
            _session->on_send_bytes(_handle, _sessionData, _send_bytes);
        }
	}
	return NetlibError_None;
#endif
}

bool TcpSocket::Recv(struct IOThredData* io_thread_data)
{
    uint32_t limit = 0xffffffff;
    if (_limiter)
    {
        limit = _limiter->get_tokens();
        if (limit < 50)
        {
            ref();
            platform_timer_t id = platform_create_timer(70, limiter_recv_callback, nullptr, this);
            if (id == INVALID_TIMER_ID)
            {
                unref();
                WARNING_LOG("platform_create_timer failed");
            }
            return true;
        }
    }
	int32_t ret = PlatformSocket::RecvTcp(io_thread_data, m_recvBuffer, limit);

    if (2 == ret)
    {
        //only for linux

        ref();
        platform_timer_t id = platform_create_timer(70, limiter_recv_callback, nullptr, this);
        if (id == INVALID_TIMER_ID)
        {
            unref();
            WARNING_LOG("platform_create_timer failed");
        }
        return true;
    }

    return ret;
}

bool TcpSocket::conn_reusing()
{
    if(m_recvBuffer)
    {
        m_recvBuffer->conn_reusing();
        return true;
    }
    return false;
}

uint32_t TcpSocket::GetLeftData()
{
	ScopedLock<PlatformMutex> lock(m_mutex);
	if( m_sendBuffer )
	{
		return m_sendBuffer->GetLeftData();
	}
	else
	{
		return 0;
	}
}

bool TcpSocket::OnAccept()
{
	return true;
}

void TcpSocket::OnRecv(const char* buf, uint32_t size)
{
#ifdef _WIN32
    if (_limiter)
    {
        _limiter->release_tokens(size);
    }
	m_recvBuffer->recv_data(buf, size, _sessionData);
    _recv_bytes += size;
    incr_recv_data_size(size);
#endif
}

void TcpSocket::OnEvent(struct IOThredData* io_thread_data, uint32_t event, void* param)
{
    if (event == EVENT_DELAY_CLOSE)
    {
        DestroySocket(31);
    }
    else if (event == EVENT_DELAY_RECV)
    {
        Recv(io_thread_data);
    }
    else if (event == EVENT_DELAY_SEND)
    {
        Send();
    }
#ifdef _WIN32
    else if (event == EVENT_DELAY_SSL)
    {
        if (nullptr == m_sslBuffer)
        {
            uint32_t recv_buffer_size = _session->get_send_buffer_size(_sessionData);

            recv_buffer_size = next_pow_of_2(recv_buffer_size);
            m_sslBuffer = new(std::nothrow) CBuffer(recv_buffer_size);
        }
        m_recvBuffer->reset();
        ssl_connect(io_thread_data, false);
    }
#endif
}


/////////////////////////////////////////////////
UdpSocket::UdpSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
	:PlatformSocket(session, protocol, sessionData)
{
	m_sendBuffer = new CUdpSendBuffer(session->get_send_buffer_size(sessionData));
	m_recvBuffer = session->create_recv_buffer(sessionData);
}

UdpSocket::~UdpSocket()
{
	if (m_sendBuffer)
	{
		delete m_sendBuffer;
		m_sendBuffer = NULL;
	}
    if (m_recvBuffer)
    {
        delete m_recvBuffer;
        m_recvBuffer = NULL;
    }
}

void UdpSocket::OnSend(uint32_t ioSize)
{
	ScopedLock<PlatformMutex> lock(m_mutex);
    m_sendBuffer->release_udp_buffer();
    _sending = false;
    _send_buffer_msg_count--;
    send_nolock();
}

void UdpSocket::OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen)
{
	m_recvBuffer->recv_udp_data(buf, size, addr, addrlen);
}


int32_t UdpSocket::Send(const uint8_t* data, uint32_t size, SndData* param)
{
    if (NULL == param)
    {
        return NetlibError_SendError;
    }

	ScopedLock<PlatformMutex> lock(m_mutex);
	if (!m_sendBuffer->add_udp_buffer(*param, data, size))
    {
		return NetlibError_BufferError;
    }

    _send_buffer_msg_count++;

	if (!_sending)
	{
		if (send_nolock() < 0)
		{
			return NetlibError_SendError;
		}
	}

	return NetlibError_None;
}


int32_t UdpSocket::Send()
{
	ScopedLock<PlatformMutex> lock(m_mutex);
    _sending = false;
    return send_nolock();
}

int32_t UdpSocket::send_nolock()
{
    while (m_sendBuffer)
    {
        auto udp_chunk = m_sendBuffer->get_udp_buffer();
        if (!udp_chunk)
        {
            return NetlibError_None;
        }

        dy_network::SockaddrStorage dst;
        const uint8_t *data = nullptr;
        uint32_t len = 0;
        if (!udp_chunk->get_send_param(dst, data, len))
        {
            return NetlibError_SendError;
        }

        int ret = PlatformSocket::SendUdp(data, len, dst.addr(), static_cast<int>(dst.size()));
        if (ret == 0)
        {
            _sending = true;
            break;
        }

#ifndef _WIN32
		m_sendBuffer->release_udp_buffer(udp_chunk);
#endif

        if (ret < 0)
        {
#ifdef _WIN32
            m_sendBuffer->release_udp_buffer(udp_chunk);
#endif
            return NetlibError_SocketError;
        }

        _send_buffer_msg_count--;
    }

    return NetlibError_None;
}

bool UdpSocket::Recv(struct IOThredData* io_thread_data)
{
	return PlatformSocket::RecvUdp(io_thread_data, m_recvBuffer);
}

bool UdpSocket::OnInit()
{
    m_recvBuffer->OnHandle(_handle, _sessionData);
#ifdef _WIN32
	PlatformSocket::RecvUdp(NULL, m_recvBuffer);
#endif
	return true;
}

uint64_t UdpSocket::udp_send_buffer_msg_count() const
{
    return _send_buffer_msg_count;
}
