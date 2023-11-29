#include "quic_engine_base.h"
#include "quic_socket.h"


//////////////////////////////////////////////////
void lsquic_cid2str2(const lsquic_cid_t *cid, char *out, uint32_t out_len)
{
    if ((cid->len*2 + 1) >= out_len)
    {
        QUIC_WARNING_LOG(0, "cid len:%d invalid", cid->len);
        return;
    }

    static const char hex[] = "0123456789ABCDEF";
    int i;

    for (i = 0; i < (int) cid->len; ++i)
    {
        *out++ = hex[ cid->idbuf[i] >> 4 ];
        *out++ = hex[ cid->idbuf[i] & 0xF ];
    }
    *out = '\0';
}

int keylog_log_line(void *ctx, const char *buf, size_t len)
{
    FILE *fr = (FILE*)ctx;
    if (fr)
    {
        fputs(buf, fr);
    }
    else
    {
        QUIC_FLOW_LOG(0, "[lsquic_log]%s", buf);
    }
    return 0;
}

//////////////////////////////////////////////////
QuicEngineBase::QuicEngineBase(uint32_t recv_buffer_size, const std::shared_ptr<QuicConfig>& quic_cfg)
    : _quic_cfg(quic_cfg)
{
    _quic_stack_buf = new QuicBuffer(recv_buffer_size);

    _executor = dy_network::IExecutor::create(1, "QuicEngine");
    if (!_executor)
    {
        QUIC_FATAL_LOG(-1, 0, "lsquic server executor create failed");
        return;
    }

    add_ref(); // for timer
    _trigger_timer = platform_create_timer(10, engine_trigger_timer_callback, this);
    if (_trigger_timer == INVALID_TIMER_ID)
    {
        QUIC_FATAL_LOG(-1, 0, "create trigger timer failed");
        return;
    }

    QUIC_DEBUG_LOG(0, "new QuicEngineBase:%p", this);
}

QuicEngineBase::~QuicEngineBase()
{
    if (_quic_stack_buf)
    {
        delete(_quic_stack_buf);
        _quic_stack_buf = nullptr;
    }

    QUIC_DEBUG_LOG(0, "delete QuicEngineBase:%p", this);
}

void QuicEngineBase::close()
{
    bool expect = false;
    if (!_is_closed.compare_exchange_strong(expect, true))
    {
        return;
    }

    QUIC_FLOW_LOG(0, "quic engine base:%p close", this);

    if (INVALID_TIMER_ID != _trigger_timer)
    {
        platform_timer_t tmp = _trigger_timer;
        _trigger_timer = INVALID_TIMER_ID;
        if (!platform_delete_timer(tmp))
        {
            QUIC_WARNING_LOG(0, "delete timer error");
        }
    }

    _release_timer = platform_create_timer(1000, engine_release_timer_callback, this);
    if (_release_timer == INVALID_TIMER_ID)
    {
        QUIC_WARNING_LOG(0, "create release timer failed");
        return;
    }
}

int QuicEngineBase::recv_udp_message(PlatformSocket* ps, 
                                    const char* buf, 
                                    uint32_t size, 
                                    const sockaddr *addr_remote, 
                                    int addrlen)
{
    char* tmp = (char*)malloc(size);
    memcpy(tmp, buf, size);

    sockaddr addr_remote_tmp;
    memcpy((void*)&addr_remote_tmp, (void*)addr_remote, sizeof(addr_remote_tmp));

    add_ref();
    bool ret = post_task([=](){
                auto ar = reinterpret_cast<const dy_network::SockaddrStorage *>(&addr_remote_tmp);
                std::string ar_ip = ar->get_ip_string();
                uint32_t ar_port = ar->get_port();

                auto al = reinterpret_cast<const dy_network::SockaddrStorage *>((struct sockaddr*)&_addr_local);
                std::string al_ip = al->get_ip_string();
                uint32_t al_port = al->get_port();

                QUIC_DEBUG_LOG(0, 
                            "%s lsquic_engine:%p local:[%s:%d] remote:[%s:%d] msg_size:%d platform_socket:%p", 
                            __FUNCTION__, _lsquic_engine,
                            al_ip.c_str(), al_port, ar_ip.c_str(), ar_port, size, ps);
                int ret = lsquic_engine_packet_in(_lsquic_engine, (const unsigned char*)tmp, size, 
                                                    (struct sockaddr*)&_addr_local, &addr_remote_tmp, 
                                                    (void*)ps, 0);

                if (0 == ret)
                {
                    process_quic_engine();
                }
                else
                {
                    switch (ret) {
                    case -1:
                        QUIC_WARNING_LOG(0, 
                                        "lsquic_in_error -1 if lsquic_engine_error. local:[%s:%d], remote:[%s:%d]", 
                                        al_ip.c_str(), al_port, ar_ip.c_str(), ar_port);
                        break;
                    case 1:
                        QUIC_NOTICE_LOG(0, 
                                        "lsquic_in_error 1 if the packet was processed, but not by a connection."
                                        " local:[%s:%d], remote:[%s:%d]",
                                        al_ip.c_str(), al_port, ar_ip.c_str(), ar_port);
                        break;
                    default:
                        QUIC_WARNING_LOG(0, 
                                        "lsquic_in_error unknow lsquic_engine_error. local:[%s:%d], remote:[%s:%d]",
                                        al_ip.c_str(), al_port, ar_ip.c_str(), ar_port);
                        break;
                    }
                }
                free(tmp);
                release();
            });

    if (!ret)
    {
        free(tmp);
        release();
        return -1;
    }

    return 0;
}

void QuicEngineBase::do_stream_read(PlatformSocket* ps, lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!ps)
    {
        QUIC_WARNING_LOG(0, "platform_socket is null for stream:%p", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    if (!ps->get_recv_buffer())
    {
        QUIC_WARNING_LOG(ps->GetNetHandle(), "platform_socket recv buffer is null for stream:%p", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    if (!ps->get_recv_buffer()->get_recv_buf(nullptr))
    {
        QUIC_WARNING_LOG(ps->GetNetHandle(), "platform_socket recv buffer get error for stream:%p", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    net_buf_pos_t* net_pos = ps->get_recv_buffer()->get_recv_buf(nullptr);
    if (!net_pos || !net_pos->_buf)
    {
        QUIC_WARNING_LOG(ps->GetNetHandle(), "no buf to recv. stream:%p, stream_ctx:%p", stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    int nreads = 0;
    nreads = lsquic_stream_read(stream, net_pos->_buf, net_pos->_size);
    if (0 == nreads) // EOS(end of stream) has been reached
    {
        QUIC_FLOW_LOG(ps->GetNetHandle(), "stream:%p stream_ctx:%p lsquic_stream_read return 0", 
                stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }
    else if (nreads < 0)
    {
        int errorCode = errno;
        if(errorCode != EWOULDBLOCK && errorCode != EINTR)
        {
            QUIC_FLOW_LOG(ps->GetNetHandle(), "stream:%p stream_ctx:%p read error. nreads:%d errno:%d", 
                        stream, stream_ctx, nreads, errorCode);
            lsquic_stream_shutdown(stream, 2);
            return;
        }
    }
    QUIC_DEBUG_LOG(ps->GetNetHandle(), "lsquic_stream_read ok. buf:%p, buf_size:%d read_size:%d", 
                    net_pos->_buf, net_pos->_size, nreads);

    if (!ps->get_recv_buffer()->recv_data(net_pos->_buf, nreads, ps->GetSessionData()))
    {
        QUIC_NOTICE_LOG(ps->GetNetHandle(), "stream:%p stream_ctx:%p recv data error. ",
                stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }
    stream_ctx->on_read(nreads);
    return;
}

void QuicEngineBase::do_stream_write(QuicSocket* ps, lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!ps)
    {
        QUIC_WARNING_LOG(0, "platform_socket is null for stream:%p", stream);
        return;
    }

    if (!stream || !stream_ctx)
    {
        QUIC_WARNING_LOG(ps->GetNetHandle(), "unexpect lsquic_stream[%p] lsquic_stream_ctx[%p] on_write()", 
                        stream, stream_ctx);
        return;
    }

    int ret = ps->write_to_quic_buffer([=](const uint8_t* buf, uint32_t size) -> int {
        int ret = lsquic_stream_write(stream, buf, size);
        if (ret < 0)
        {
            QUIC_WARNING_LOG(ps->GetNetHandle(), 
                            "lsquic_stream_write error and shutdown. stream:%p, stream_ctx:%p, need_size:%d, ret:%d", 
                            stream, stream_ctx, size, ret);
            lsquic_stream_shutdown(stream, 2);
        }
        else
        {
            QUIC_DEBUG_LOG(ps->GetNetHandle(), 
                            "lsquic_stream_write ok. stream:%p, stream_ctx:%p, need_size:%d, write_size:%d", 
                            stream, stream_ctx, size, ret);
            stream_ctx->on_write(ret);
        }
        return ret;
    });

    if (NetlibError_None != ret)
    {
        QUIC_WARNING_LOG(ps->GetNetHandle(), 
                        "write to quic buffer error and shutdown. stream:%p, stream_ctx:%p", 
                        stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }
    
    if (0 == ps->GetLeftData())
    {
        lsquic_stream_wantwrite(stream, 0);
    }

    lsquic_stream_flush(stream);
    return;
}

bool QuicEngineBase::wait_drive_lsquic_engine(int32_t delay_ms)
{
    add_ref();
    bool ret = post_task([=](){
        process_quic_engine();
        release();
    });

    if (!ret)
    {
        release();
        return false;
    }

    return true;
}

bool QuicEngineBase::process_quic_engine(void)
{
    uint32_t nb_process = 0;

    // QUIC_DEBUG_LOG(0, "lsquic_engine:%p", _lsquic_engine);
    if (_lsquic_engine)
    {
        lsquic_engine_send_unsent_packets(_lsquic_engine);
        lsquic_engine_process_conns(_lsquic_engine);

        while(true)
        {
            if (nb_process++ >= 4000)
            {
                QUIC_WARNING_LOG(0, "process conns cnt:%d exec too much once", nb_process);
                break;
            }

            int diff = 0;
            if (lsquic_engine_earliest_adv_tick(_lsquic_engine, &diff))
            {
                if (diff < 0)
                {
                    QUIC_DEBUG_LOG(0, "diff:%d. exec now", diff);

                    lsquic_engine_send_unsent_packets(_lsquic_engine);
                    lsquic_engine_process_conns(_lsquic_engine);
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    return true;
}

int QuicEngineBase::do_send_packets_out(PlatformSocket* ps, const struct lsquic_out_spec *specs, unsigned n)
{
    const struct sockaddr_in *dest_sa = (struct sockaddr_in *)specs[n].dest_sa;
    dy_network::SocketAddress peer(dest_sa->sin_addr.s_addr, ntohs(dest_sa->sin_port));

    uint32_t total_iov_len = 0;
    uint32_t iovlen = specs[n].iovlen;
    if (iovlen > 1)
    {
        for (int iovidx = 0; iovidx < iovlen; iovidx++)
        {
            total_iov_len += specs[n].iov[iovidx].iov_len;
        }
        QUIC_NOTICE_LOG(ps->GetNetHandle(), "send to %s:%u iovlen:%u total_iov_len:%d", 
                        peer.ipstr().c_str(), peer.port(), iovlen, total_iov_len);
    }

    SndData sd;
    peer.to_send_data(sd);
    int ret = ps->SendQuic(specs[n].iov, iovlen, &sd);
    if (NetlibError_None != ret)
    {
        if (NetlibError_BufferOver == ret)
        {
            errno = EAGAIN;
            QUIC_NOTICE_LOG(ps->GetNetHandle(), "send to %s:%u iovlen:%zu error:%d", 
                        peer.ipstr().c_str(), peer.port(), specs[n].iovlen, ret);
        }
        else
        {
            errno = 1;
            QUIC_WARNING_LOG(ps->GetNetHandle(), "send to %s:%u iovlen:%zu error:%d", 
                            peer.ipstr().c_str(), peer.port(), specs[n].iovlen, ret);
        }
    }
    QUIC_DEBUG_LOG(0, "send to %s:%u iovlen:%u total_iov_len:%d", 
                    peer.ipstr().c_str(), peer.port(), iovlen, total_iov_len);
    return ret;
}