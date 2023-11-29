#include "quic_socket.h"
#include "quic_engine_client.h"
#include "quic_engine_server.h"
#include <memory>
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
#include <multi_send_buffer.h>
#include "media_message.h"

extern struct NetLibParam g_param;

//////////////////////////////////////////////////////////////////////
QuicServerSocket::QuicServerSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
    : PlatformSocket(session, protocol, sessionData)
{
    uint32_t send_buf_size = m_sessionData.m_quic_cfg->_udp_send_buffer_size;
    m_sendBuffer = new CUdpSendBuffer(send_buf_size);

    _qc_engine = m_sessionData.m_quic_cfg->_quic_engine;
}

QuicServerSocket::~QuicServerSocket()
{
    if (m_sendBuffer)
    {
        delete m_sendBuffer;
        m_sendBuffer = NULL;
    }

    if (_qc_engine)
    {
        _qc_engine->close();
        _qc_engine->release();
        _qc_engine = nullptr;
    }
}

bool QuicServerSocket::OnIOBinded()
{
    _qc_engine->on_handle(m_handle);
    return PlatformSocket::OnIOBinded();
}

void QuicServerSocket::OnSend(uint32_t ioSize)
{
	ScopedLock<PlatformMutex> lock(m_mutex);
    m_sendBuffer->release_udp_buffer();
    _sending = false;
    send_nolock();
}

bool QuicServerSocket::Recv(struct IOThredData* io_thread_data)
{
    return PlatformSocket::RecvUdp(io_thread_data, _qc_engine->get_quic_stack_buf());
}

void QuicServerSocket::OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen)
{
    _qc_engine->recv_udp_message(this, buf, size, addr, addrlen);
}

int32_t QuicServerSocket::Send(const uint8_t* data, uint32_t size, SndData* param)
{
    iovec msg;
    msg.iov_base = const_cast<uint8_t *>(data);
    msg.iov_len = size;
    return SendQuic(&msg, 1, param);
}

int32_t QuicServerSocket::SendQuic(const iovec *msgs, size_t nmsgs, SndData *params)
{
    if (NULL == params)
    {
        return NetlibError_SendError;
    }

    uint32_t size = 0;
    for (size_t i = 0; i < nmsgs; ++i)
    {
        size += msgs[i].iov_len;
    }

    ScopedLock<PlatformMutex> lock(m_mutex);
    if (!m_sendBuffer->check(size))
    {
        return NetlibError_BufferOver;
    }

    for (size_t i = 0; i < nmsgs; ++i)
    {
        auto&& msg = msgs[i];
        if (!m_sendBuffer->add_udp_buffer(*params, 
                                            static_cast<const uint8_t*>(msg.iov_base), 
                                            static_cast<uint32_t>(msg.iov_len)))
        {
            return NetlibError_BufferError;
        }
    }

    if (!_sending)
    {
        if (send_nolock() < 0)
        {
            return NetlibError_SendError;
        }
    }

	return NetlibError_None;
}

int32_t QuicServerSocket::Send()
{
	ScopedLock<PlatformMutex> lock(m_mutex);
    _sending = false;
    return send_nolock();
}

int32_t QuicServerSocket::send_nolock()
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
    }

    return NetlibError_None;
}

QuicSocket* QuicServerSocket::on_new_stream_socket(lsquic_stream_t* quic_stream)
{
    QuicSocket* ps = new ServerQuicClientSocket(m_session, m_protocol, m_sessionData, _qc_engine, quic_stream);

    if (ps->GetNetHandle() == INVALID_NET_HANDLE)
    {
        NetManager::GetInstance()->AddPlatformSocket(ps);
        if (ps->GetNetHandle() == INVALID_NET_HANDLE)
        {
            return nullptr;
        }
    }
    else
    {
        assert(false);
        return nullptr;
    }

    return ps;
}


///////////////////////////////////////////////////////////
QuicSocket::QuicSocket(INetSession* session, 
                        NetProtocol protocol, 
                        const SessionData& sessionData, 
                        QuicEngineBase* qc_engine,
                        lsquic_stream_t* quic_stream)
    : PlatformSocket(session, protocol, sessionData)
    , m_sendBuffer(NULL)
    , m_recvBuffer(NULL)
    , _qc_engine(qc_engine)
    , _quic_stream(quic_stream)
{
    m_is_connected = false;
    _is_ssl = false;

    m_recvBuffer = m_session->create_recv_buffer(m_sessionData);

    if (m_sessionData.m_quic_cfg && m_sessionData.m_quic_cfg->_chunk_slice)
    {
        _pkt_chunk_slice = m_sessionData.m_quic_cfg->_chunk_slice;
    }

    if (!_pkt_chunk_slice)
    {
        uint32_t send_buffer_size = m_session->get_send_buffer_size(m_sessionData);
        send_buffer_size = next_pow_of_2(send_buffer_size);
        m_sendBuffer = new(std::nothrow) CBuffer(send_buffer_size);
    }

    _create_time = get_seconds();

    DEBUG_LOG("new QuicSocket:%p", this);
}

QuicSocket::~QuicSocket()
{
    DEBUG_LOG("[handle:%" PRIu64 "]delete QuicSocket:%p", m_handle, this);

    if (m_sendBuffer)
    {
        delete m_sendBuffer;
        m_sendBuffer = nullptr;
    }

    if (m_recvBuffer)
    {
        delete m_recvBuffer;
        m_recvBuffer = nullptr;
    }

    if (!_pkt_list.empty())
    {
        for (auto it = _pkt_list.begin(); it != _pkt_list.end(); ++it)
        {
            (*it)->release();
        }
        _pkt_list.clear();
    }
}

bool QuicSocket::OnInit()
{
    if (!m_recvBuffer->OnHandle(m_handle, m_sessionData))
    {
        return false;
    }
    return true;
}

int32_t QuicSocket::multi_send(IMultiSendPacket* pkt)
{
    if (!_pkt_chunk_slice)
    {
        WARNING_LOG("[handle:%" PRIu64 "]quic pkt chunk slice is null", m_handle);
        return NetlibError_BufferError;
    }

    ScopedLock<PlatformMutex> lock(m_mutex);
    if (_pkt_list_size > get_max_pkt_list_size())
    {
        DEBUG_LOG("[handle:%" PRIu64 "]quic pkt_list_size is full. drop pkt. "
                    "pkt_list_size:%d", 
                    m_handle, _pkt_list_size);
        return NetlibError_BufferOver;
    }
    
    pkt->add_ref();
    _pkt_list.emplace_back(pkt);
    _pkt_list_size++;
    
    if (!_qc_engine->send(_quic_stream))
    {
        return NetlibError_SocketError;
    }

    DEBUG_LOG("[handle:%" PRIu64 "]quic multi_send pkt_list_size:%d", m_handle, _pkt_list_size);
    return NetlibError_None;
}

int32_t QuicSocket::Send(const uint8_t* data, uint32_t size, SndData* params)
{
    iovec msg;
    msg.iov_base = const_cast<uint8_t *>(data);
    msg.iov_len = size;
    return sendv(&msg, 1, params);
}

int32_t QuicSocket::sendv(const iovec *msgs, size_t nmsgs, SndData *params)
{
    if (!m_sendBuffer)
    {
        WARNING_LOG("[handle:%" PRIu64 "]quic m_sendBuffer is null", m_handle);
        return NetlibError_BufferError;
    }

    size_t total_len = 0;
    for (size_t idx = 0; idx < nmsgs; idx++)
    {
        total_len += msgs[idx].iov_len;
    }

    ScopedLock<PlatformMutex> lock(m_mutex);
    if (total_len > m_sendBuffer->GetLeftCapacity())
    {
        DEBUG_LOG("[handle:%" PRIu64 "]quic buffer overflow while sendv length=%zu left_cap=%d", 
                    m_handle, total_len, m_sendBuffer->GetLeftCapacity());
        return NetlibError_BufferOver;
    }

    if (!m_sendBuffer->add_buffers(msgs, nmsgs, params))
    {
        WARNING_LOG("[handle:%" PRIu64 "]quic add buffers error while sendv length %zu bytes", m_handle, total_len);
        return NetlibError_BufferError;
    }

    if (!m_is_connected)
    {
        return NetlibError_None;
    }

    if (!_qc_engine->send(_quic_stream))
    {
        return NetlibError_SocketError;
    }

    return NetlibError_None;
}

uint32_t QuicSocket::GetLeftData()
{
    ScopedLock<PlatformMutex> lock(m_mutex);
    if (m_sendBuffer)
    {
        return m_sendBuffer->GetLeftData();
    }
    else
    {
        return _pkt_list_size;
    }
}

int32_t QuicSocket::write_to_quic_buffer(FunctionView<int(const uint8_t*, uint32_t)> f)
{
    int ret = 0;
    ScopedLock<PlatformMutex> lock(m_mutex);

    if (m_sendBuffer)
    {
        while (m_sendBuffer)
        {
            const uint8_t* buf = m_sendBuffer->GetTcpBuffer();
            uint32_t size = m_sendBuffer->GetTcpLength();
            if( size == 0 )
            {
                break;
            }

            ret = f(buf, size);
            if (ret == 0)
            {
                break;
            }

            if( ret < 0 )
            {
                return NetlibError_SocketError;
            }

            _send_bytes += ret;
            m_sendBuffer->ReleaseTcpBuffer(ret);
            if (m_sendBuffer->IsEmpty())
            {
                if (IsValid())
                {
                    m_session->on_send_bytes(m_handle, m_sessionData, _send_bytes);
                }
            }
        }
    }
    else
    {
        int nb = 0;
        for (auto it = _pkt_list.begin(); it != _pkt_list.end(); )
        {
            if (0 == _pkt_chunk_slice->nb_chunk())
            {
                IMultiSendPacket* pkt = *it;
                ret = _pkt_chunk_slice->chunk_slice(pkt);
                if (ret <= 0)
                {
                    WARNING_LOG("[handle:%" PRIu64 "]quic pkt chunk slice error ret:%d", m_handle, ret);
                    (*it)->release();
                    _pkt_list.erase(it++);
                    _pkt_list_size--;
                    continue;
                }
            }

            uint32_t nb_chunk = _pkt_chunk_slice->nb_chunk();
            for (int i = 0; i < nb_chunk; ++i)
            {
                uint8_t* buf = nullptr;
                uint32_t size = 0;
                if (!_pkt_chunk_slice->get_send_buffer(&buf, size))
                {
                    WARNING_LOG("[handle:%" PRIu64 "]quic get_send_buffer error", m_handle);
                    return NetlibError_SocketError;
                }

                ret = f(buf, size);
                if (ret < 0)
                {
                    WARNING_LOG("[handle:%" PRIu64 "]quic write cb ret:%d", m_handle, ret);
                    return NetlibError_SocketError;
                }
                else if (ret == 0)
                {
                    return NetlibError_None;
                }

                if (!_pkt_chunk_slice->on_send(ret))
                {
                    WARNING_LOG("[handle:%" PRIu64 "]quic on_send error", m_handle);
                    return NetlibError_SocketError;
                }
            }

            if (_pkt_chunk_slice->is_last_chunk_send_ok())
            {
                (*it)->release();
                _pkt_list.erase(it++);
                _pkt_list_size--;
                ++nb;
            }

        }
        DEBUG_LOG("[handle:%" PRIu64 "]quic send packet cnt:%d pkt_list_size:%d", m_handle, nb, _pkt_list_size);
    }

    return NetlibError_None;
}

bool QuicSocket::UpdateIpInfo(const std::string& remote_ip, 
                                uint16_t remote_port,
                                const std::string& local_ip, 
                                uint16_t local_port)
{
    m_sessionData.m_PeerIP = remote_ip;
    m_sessionData.m_PeerPort = remote_port;
    m_sessionData.m_LocalIP = local_ip;
    m_sessionData.m_LocalPort = local_port;

    return true;
}

uint32_t QuicSocket::get_max_pkt_list_size()
{
    uint32_t max_pkt_list_size = m_sessionData.m_quic_cfg->_max_pkt_list_size;
    if (_is_fresh)
    {
        if (get_seconds() - _create_time < 30)
        {
            max_pkt_list_size = 3 * max_pkt_list_size;
        }
        else
        {
            _is_fresh = false;
        }
    }

    return max_pkt_list_size;
}

bool QuicSocket::DestroySocket(int magic)
{
    if (_quic_stream)
    {
        ScopedLock<PlatformMutex> guard(m_mutex);
        if (_quic_stream)
        {
            NOTICE_LOG("[handle:%" PRIu64 "]session:%p, quic DestroySocket, magic:%d, err:%d,this:%p\n", 
                        m_handle, m_session, magic, errno, this);
            PlatformIO::GetInstance()->UnBindSocket(this);
            OnClose();
            _quic_stream = nullptr;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////
ServerQuicClientSocket::ServerQuicClientSocket(INetSession* session, 
                                                NetProtocol protocol, 
                                                const SessionData& sessionData,
                                                QuicEngineBase* qc_engine,
                                                lsquic_stream_t* quic_stream)
    : QuicSocket(session ,protocol , sessionData, qc_engine, quic_stream)
{
    m_is_connected = true;
}

ServerQuicClientSocket::~ServerQuicClientSocket()
{
}

bool ServerQuicClientSocket::OnAccept()
{
	QuicSocket::OnAccept();
    if (!m_recvBuffer->OnHandle(m_handle, m_sessionData))
    {
        return false;
    }
    DEBUG_LOG("[handle:%" PRIu64 "]accept quic client", m_handle);
    m_session->OnAccept(m_handle, m_sessionData);

    return true;
}

///////////////////////////////////////////////////////////
QuicClientSocket::QuicClientSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
    : QuicSocket(session, protocol, sessionData, nullptr, nullptr)
{
    _qc_engine = sessionData.m_quic_cfg->_quic_engine;

    m_quic_send_buffer = new CUdpSendBuffer(m_session->get_send_buffer_size(m_sessionData));
    DEBUG_LOG("new QuicClientSocket:%p", this);
}

QuicClientSocket::~QuicClientSocket()
{
    DEBUG_LOG("[handle:%" PRIu64 "] delete QuicClientSocket:%p", m_handle, this);

    if (m_quic_send_buffer)
    {
        delete m_quic_send_buffer;
        m_quic_send_buffer = nullptr;
    }

    if (_qc_engine)
    {
        _qc_engine->close();
        _qc_engine->release();
        _qc_engine = nullptr;
    }
}

bool QuicClientSocket::OnIOBinded()
{
    _qc_engine->on_handle(m_handle);
    return _qc_engine->connect_to();
}

void QuicClientSocket::OnSend(uint32_t ioSize)
{
	ScopedLock<PlatformMutex> lock(m_mutex);
    m_quic_send_buffer->release_udp_buffer();
    _sending = false;
    send_nolock();
}

bool QuicClientSocket::Recv(struct IOThredData* io_thread_data)
{
    return PlatformSocket::RecvUdp(io_thread_data, _qc_engine->get_quic_stack_buf());
}

void QuicClientSocket::OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen)
{
    _qc_engine->recv_udp_message(this, buf, size, addr, addrlen);
}

int32_t QuicClientSocket::SendQuic(const iovec *msgs, size_t nmsgs, SndData *params)
{
    if (NULL == params)
    {
        return NetlibError_SendError;
    }

    uint32_t size = 0;
    for (size_t i = 0; i < nmsgs; ++i)
    {
        size += msgs[i].iov_len;
    }

    ScopedLock<PlatformMutex> lock(m_mutex);
    if (!m_quic_send_buffer->check(size))
    {
        return NetlibError_BufferOver;
    }

    for (size_t i = 0; i < nmsgs; ++i)
    {
        auto&& msg = msgs[i];
        if (!m_quic_send_buffer->add_udp_buffer(*params, 
                                            static_cast<const uint8_t*>(msg.iov_base), 
                                            static_cast<uint32_t>(msg.iov_len)))
        {
            return NetlibError_BufferError;
        }
    }

    if (!_sending)
    {
        if (send_nolock() < 0)
        {
            return NetlibError_SendError;
        }
    }

    return NetlibError_None;
}

int32_t QuicClientSocket::Send()
{
    ScopedLock<PlatformMutex> lock(m_mutex);
    _sending = false;
    return send_nolock();
}

bool QuicClientSocket::on_connected()
{
    if (false == m_is_connected)
    {
        ScopedLock<PlatformMutex> lock(m_mutex);
        m_is_connected = true;
        m_session->OnConnected(m_handle, m_sessionData);
    }

    return true;
}

int32_t QuicClientSocket::send_nolock()
{
    while (m_quic_send_buffer)
    {
        auto udp_chunk = m_quic_send_buffer->get_udp_buffer();
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
        m_quic_send_buffer->release_udp_buffer(udp_chunk);
#endif

        if (ret < 0)
        {
#ifdef _WIN32
            m_quic_send_buffer->release_udp_buffer(udp_chunk);
#endif
            return NetlibError_SocketError;
        }
    }

    return NetlibError_None;
}