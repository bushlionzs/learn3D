#include "quic_engine_client.h"
#include "quic_socket.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
QuicEngineClient::QuicEngineClient(uint32_t recv_buffer_size, 
                                    const std::shared_ptr<QuicConfig>& quic_cfg, 
                                    const std::string& peer_ip, 
                                    uint16_t peer_port)
    : QuicEngineBase(recv_buffer_size, quic_cfg)
    , _conn_ctx(nullptr)
    , _stream(nullptr)
    , _peer_ip(peer_ip)
    , _peer_port(peer_port)
{
}

QuicEngineClient::~QuicEngineClient()
{
    QUIC_DEBUG_LOG(0, "delete QuicEngineClient:%p", this);

    if (_lsquic_engine)
    {
        lsquic_engine_destroy(_lsquic_engine);
        _lsquic_engine = nullptr;
    }
}

bool QuicEngineClient::start()
{
    memset(&_lsquic_setting, 0, sizeof(_lsquic_setting));
    lsquic_engine_init_settings(&_lsquic_setting, QuicEngineClientMode);
    _lsquic_setting.es_cc_algo = _quic_cfg->_congestion_ctrl_algo;
    constexpr char lsquic_ua[32] = "dyp2p/lsquic client agent";
    _lsquic_setting.es_ua = lsquic_ua;
    _lsquic_setting.es_idle_conn_to = _quic_cfg->_idle_conn_timeout * 1000 * 1000;
    _lsquic_setting.es_idle_timeout = _quic_cfg->_idle_conn_timeout;
    _lsquic_setting.es_sfcw = _quic_cfg->_flow_control_window;
    _lsquic_setting.es_cfcw = 1.5 * _quic_cfg->_flow_control_window;
    _lsquic_setting.es_max_sfcw = _quic_cfg->_max_flow_control_window;
    _lsquic_setting.es_max_cfcw = 1.5 * _quic_cfg->_max_flow_control_window;

    lsquic_log_to_fstream(stderr, LLTS_HHMMSSMS);
    if (!_quic_cfg->_log.empty())
    {
        FILE *fr = fopen(_quic_cfg->_log.c_str(), "w");
        lsquic_logger_init((lsquic_logger_if*)&keylog_if, (void*)fr, LLTS_YYYYMMDD_HHMMSSMS);
    }
    else
    {
        lsquic_logger_init((lsquic_logger_if*)&keylog_if, nullptr, LLTS_YYYYMMDD_HHMMSSMS);
    }
    lsquic_set_log_level(_quic_cfg->_log_level.c_str());

    char err_buf[100];
    if (0 != lsquic_engine_check_settings(&_lsquic_setting, QuicEngineClientMode, err_buf, sizeof(err_buf)))
    {
        QUIC_FATAL_LOG(-1, 0, "Error in settings: %s", err_buf);
        return false;
    }

    memset(&_lsquic_server_if, 0, sizeof(_lsquic_server_if));
    _lsquic_server_if.on_hsk_done = qe_on_hsk_done;
    _lsquic_server_if.on_new_conn = qe_on_new_conn;
    _lsquic_server_if.on_new_token = qe_on_new_token;
    _lsquic_server_if.on_zero_rtt_info = qe_on_zero_rtt_info;
    _lsquic_server_if.on_goaway_received = qe_on_goaway_received;
    _lsquic_server_if.on_conn_closed = qe_on_conn_closed;
    _lsquic_server_if.on_new_stream = qe_on_new_stream;
    _lsquic_server_if.on_read = qe_on_stream_read;
    _lsquic_server_if.on_write = qe_on_stream_write;
    _lsquic_server_if.on_close = qe_on_stream_close;

    memset(&_lsquic_api, 0, sizeof(_lsquic_api));
    _lsquic_api.ea_settings = &_lsquic_setting;
    _lsquic_api.ea_stream_if = &_lsquic_server_if;
    _lsquic_api.ea_stream_if_ctx = (void*)(&(*this));
    _lsquic_api.ea_packets_out = send_packets_out;
    _lsquic_api.ea_packets_out_ctx = this;

    _lsquic_engine = lsquic_engine_new(QuicEngineClientMode, &_lsquic_api);
    if (!_lsquic_engine)
    {
        QUIC_FATAL_LOG(-1, 0, "lsquic_engine_new failed");
        return false;
    }

    memset(&_addr_local, 0, sizeof(_addr_local));
    _addr_local.sin_family = AF_INET;
    dy_network::SocketAddress local("0.0.0.0", 0);
    _addr_local.sin_addr = local.ipaddr().ipv4_address();
    _addr_local.sin_port = ntohs(local.port());

    memset(&_addr_remote, 0, sizeof(_addr_remote));
    _addr_remote.sin_family = AF_INET;
    dy_network::SocketAddress remote(_peer_ip, _peer_port);
    _addr_remote.sin_addr = remote.ipaddr().ipv4_address();
    _addr_remote.sin_port = ntohs(remote.port());

    if (0 != lsquic_global_init(LSQUIC_GLOBAL_CLIENT))
    {
        QUIC_FATAL_LOG(-1, 0, "quic engine client global init failed");
        return false;
    }

    QUIC_FLOW_LOG(0, "new QuicEngineClient:%p, _lsquic_engine:%p", this, _lsquic_engine);

    return true;
}

bool QuicEngineClient::send(lsquic_stream_t* )
{
    if (_is_closed)
    {
        return false;
    }

    add_ref();
    bool ret = post_task([=](){
                if (!_stream)
                {
                    QUIC_WARNING_LOG(_handle, "stream is null to send");
                    return;
                }

                lsquic_stream_wantwrite(_stream, 1);
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

bool QuicEngineClient::connect_to()
{
    add_ref();
    bool ret = post_task([&](){
        _conn_ctx = new lsquic_conn_ctx_t;

        // connect to remote server
        if (NULL == lsquic_engine_connect(_lsquic_engine,
            LSQVER_039, //(lsquic_version)ver     /*LSQVER_039,N_LSQVER*/,
            (struct sockaddr *) &_addr_local,
            (struct sockaddr *) &_addr_remote,
            nullptr,    /* void *peer_ctx */
            _conn_ctx,           /* lsquic_conn_ctx_t *conn_ctx */
            "*.com",                     /* const char *hostname */
            0,                      /* unsigned short max_udp_payload_size */
            nullptr,                   /* const unsigned char *zero_rtt */
            0,                      /* size_t zero_rtt_len */
            nullptr,                   /* const unsigned char *token */
            0))                     /* size_t token_sz */
        {
            QUIC_WARNING_LOG(_handle, "lsquic_engine_connect error");
        }

        release();
        return;
    });

    if (!ret)
    {
        release();
        QUIC_WARNING_LOG(_handle, "post to lsquic_engine_connect error");
        return false;
    }

    return true;
}

// static
void QuicEngineClient::qe_on_hsk_done(lsquic_conn_t *c, enum lsquic_hsk_status s)
{
    lsquic_conn_ctx_t *conn_ctx = lsquic_conn_get_ctx(c);
    if (conn_ctx)
    {
        QUIC_DEBUG_LOG(0, "%s recv hsk status: %d", conn_ctx->to_string().c_str(), s);
    }
    else
    {
        QUIC_WARNING_LOG(0, "unknow recv hsk status: %d", s);
    }
    return;
}

// static
lsquic_conn_ctx_t* QuicEngineClient::qe_on_new_conn(void *stream_if_ctx, lsquic_conn_t *conn)
{
    QuicEngineClient* qc_engine = static_cast<QuicEngineClient*>(stream_if_ctx);

    return qc_engine->do_new_conn(stream_if_ctx, conn);
}

lsquic_conn_ctx_t* QuicEngineClient::do_new_conn(void *stream_if_ctx, lsquic_conn_t *conn)
{
    int lv = lsquic_conn_quic_version(conn);
    char cid_str[64] = {0};
    lsquic_cid2str2(lsquic_conn_id(conn), cid_str, sizeof(cid_str));

    if (!_conn_ctx)
    {
        QUIC_WARNING_LOG(_handle, "conn_ctx is null for conn:%p", conn);
        return nullptr;
    }

    lsquic_conn_make_stream(conn);
    QUIC_FLOW_LOG(_handle, "on new conn. version:%d, cid:%s, conn:%p, conn_ctx:%p", 
                    lv, cid_str, conn, _conn_ctx);
    return _conn_ctx;
}

// static
void QuicEngineClient::qe_on_new_token(lsquic_conn_t *c, const unsigned char *token, size_t token_size)
{
    lsquic_conn_ctx_t *conn_ctx = lsquic_conn_get_ctx(c);
    if (conn_ctx)
    {
        QUIC_DEBUG_LOG(0, "%s recv new_token size %zu", conn_ctx->to_string().c_str(), token_size);
    }
    else
    {
        QUIC_WARNING_LOG(0, "unknow recv new_token size %zu", token_size);
    }
    return;
}

// static
void QuicEngineClient::qe_on_zero_rtt_info(lsquic_conn_t *c, const unsigned char * rtt_info, size_t rtt_size)
{
    lsquic_conn_ctx_t *conn_ctx = lsquic_conn_get_ctx(c);
    if (conn_ctx)
    {
        QUIC_DEBUG_LOG(0, "%s recv zero_rtt_info size %zu", conn_ctx->to_string().c_str(), rtt_size);
    }
    else
    {
        QUIC_WARNING_LOG(0, "unknow recv zero_rtt_info size %zu", rtt_size);
    }
    return;
}

// static
void QuicEngineClient::qe_on_goaway_received(lsquic_conn_t *conn)
{
    lsquic_conn_ctx_t *conn_ctx = lsquic_conn_get_ctx(conn);
    if (conn_ctx)
    {
        QUIC_DEBUG_LOG(0, "%s recv goaway_received", conn_ctx->to_string().c_str());
    }
    else
    {
        QUIC_WARNING_LOG(0, "unknow recv goaway_received");
    }
    return;
}

// static
void QuicEngineClient::qe_on_conn_closed(lsquic_conn_t *conn)
{
    lsquic_conn_ctx_t* conn_ctx = lsquic_conn_get_ctx(conn);
    if (!conn_ctx)
    {
        QUIC_NOTICE_LOG(0, "%s conn:%p no existed", __FUNCTION__, conn);
        return;
    }

    QUIC_FLOW_LOG(0, "on close conn. conn:%p, conn_ctx:%p, conn_info:%s", 
                    conn, conn_ctx, conn_ctx->to_string().c_str());
    delete conn_ctx;
    return;
}

// static
lsquic_stream_ctx_t* QuicEngineClient::qe_on_new_stream(void* stream_if_ctx, lsquic_stream_t* stream)
{
    if (!stream_if_ctx || !stream)
    {
        QUIC_WARNING_LOG(0, "stream_if_ctx:%p or stream:%p is null", stream_if_ctx, stream);
        return nullptr;
    }

    QuicEngineClient* quic_engine = reinterpret_cast<QuicEngineClient*>(stream_if_ctx);
    if(!quic_engine)
    {
        QUIC_WARNING_LOG(0, "quic_engine is null. stream_if_ctx:%p, stream:%p", stream_if_ctx, stream);
        return nullptr;
    }

    return quic_engine->do_new_stream(stream);
}

lsquic_stream_ctx_t* QuicEngineClient::do_new_stream(lsquic_stream_t* stream)
{
    lsquic_stream_ctx* stream_ctx = new lsquic_stream_ctx();
    if (!stream_ctx)
    {
        QUIC_WARNING_LOG(_handle, "new stream_ctx error for stream:%p", stream);
        return nullptr;   
    }

    lsquic_conn_t* conn = lsquic_stream_conn(stream);
    if (!conn)
    {
        QUIC_WARNING_LOG(_handle, "conn is null for stream:%p stream_ctx:%p", stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }

    lsquic_conn_ctx_t* conn_ctx = lsquic_conn_get_ctx(conn);
    if (!conn_ctx)
    {
        QUIC_WARNING_LOG(_handle, "conn_ctx no existed for conn:%p stream:%p stream_ctx:%p", 
                        conn, stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }

    struct sockaddr *local;
    struct sockaddr *peer;
    lsquic_conn_get_sockaddr(conn, (const struct sockaddr **)&local, (const struct sockaddr **)&peer);
    struct sockaddr_in* addr_local = (struct sockaddr_in*)(local);
    struct sockaddr_in* addr_peer = (struct sockaddr_in*)(peer);

    std::string local_ip(inet_ntoa(addr_local->sin_addr));
    uint16_t local_port = ntohs(addr_local->sin_port);
    std::string remote_ip(inet_ntoa(addr_peer->sin_addr));
    uint16_t remote_port = ntohs(addr_peer->sin_port);

    _stream = stream;
    stream_ctx->_quic_engine = this;

    QuicClientSocket* ps = dynamic_cast<QuicClientSocket*>(NetManager::GetInstance()->RefHandle(_handle));
    if (!ps)
    {
        QUIC_WARNING_LOG(_handle, "refhandle error for platform_socket:%p stream:%p stream_ctx:%p", 
                            ps, stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }

    ps->UpdateIpInfo(remote_ip, remote_port, local_ip, local_port);
    if (!ps->on_connected())
    {
        QUIC_WARNING_LOG(_handle, "on_connected error for platform_socket:%p stream:%p stream_ctx:%p", 
                            ps, stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }
    NetManager::GetInstance()->UnrefHandle(_handle);

    stream_ctx->_peer_ip = remote_ip;
    stream_ctx->_peer_port = remote_port;

    lsquic_stream_wantread(stream, 0);
    lsquic_stream_wantwrite(stream, 1);
    conn_ctx->_stream_num++;
    add_stream_cnt();
    
    QUIC_FLOW_LOG(_handle, "new stream_ctx:%p for lsquic_stream:%p stream_id:%" PRIu64 
            " conn:%p stream_num:%d stream_info:%s. local:[%s:%u] remote:[%s:%u]",
            stream_ctx, stream, lsquic_stream_id(stream), 
            conn, conn_ctx->_stream_num, stream_ctx->to_string().c_str(),
            local_ip.c_str(), local_port, remote_ip.c_str(), remote_port);
    return stream_ctx;
}

// static
void QuicEngineClient::qe_on_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!stream || !stream_ctx)
    {
        QUIC_WARNING_LOG(0, "stream:%p or stream_ctx:%p is null", stream, stream_ctx);
        return;
    }

    QuicEngineBase* quic_engine = stream_ctx->_quic_engine;
    quic_engine->do_stream_close(stream, stream_ctx);
    return;
}

void QuicEngineClient::do_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    lsquic_conn_t* conn = lsquic_stream_conn(stream);
    if (!conn)
    {
        QUIC_FLOW_LOG(_handle, "conn is null for stream close. "
                "stream:%p, stream_ctx:%p, stream_info:%s", 
                stream, stream_ctx, stream_ctx->to_string().c_str());
        return;
    }
    lsquic_conn_ctx_t* conn_ctx = lsquic_conn_get_ctx(conn);
    if (!conn_ctx)
    {
        QUIC_NOTICE_LOG(_handle, "conn_ctx no existed for conn:%p stream:%p stream_ctx:%p", 
                        conn, stream, stream_ctx);
        return;
    }

    QUIC_FLOW_LOG(_handle, 
        "close stream only. conn:%p, stream:%p, stream_ctx:%p, stream_info:%s", 
        conn, stream, stream_ctx, stream_ctx->to_string().c_str());

    conn_ctx->_stream_num--;

    QuicClientSocket* ps = dynamic_cast<QuicClientSocket*>(NetManager::GetInstance()->RefHandle(_handle));
    if (!ps)
    {
        QUIC_DEBUG_LOG(_handle, "refhandle error for stream:%p stream_ctx:%p to destroy", 
                            stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }
    ps->DestroySocket(1100);
    NetManager::GetInstance()->UnrefHandle(_handle);
        
    delete stream_ctx;
    return;
}

// static
void QuicEngineClient::qe_on_stream_read(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!stream || !stream_ctx)
    {
        QUIC_WARNING_LOG(0, "stream:%p or stream_ctx:%p is null", stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    QuicEngineBase* quic_engine = stream_ctx->_quic_engine;
    quic_engine->do_stream_read(stream, stream_ctx);
    return;
}

void QuicEngineClient::do_stream_read(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    QuicClientSocket* ps = dynamic_cast<QuicClientSocket*>(NetManager::GetInstance()->RefHandle(_handle));
    if (!ps)
    {
        QUIC_DEBUG_LOG(_handle, "refhandle error for stream:%p stream_ctx:%p to read", 
                            stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    QuicEngineBase::do_stream_read(ps, stream, stream_ctx);
    NetManager::GetInstance()->UnrefHandle(_handle);
    return;
}

// static
void QuicEngineClient::qe_on_stream_write(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!stream || !stream_ctx)
    {
        QUIC_WARNING_LOG(0, "stream:%p or stream_ctx:%p is null", stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    QuicEngineBase* quic_engine = stream_ctx->_quic_engine;
    quic_engine->do_stream_write(stream, stream_ctx);
    return;
}

void QuicEngineClient::do_stream_write(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    QuicClientSocket* ps = dynamic_cast<QuicClientSocket*>(NetManager::GetInstance()->RefHandle(_handle));
    if (!ps)
    {
        QUIC_DEBUG_LOG(_handle, "refhandle error for stream:%p stream_ctx:%p to write", 
                            stream, stream_ctx);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    QuicEngineBase::do_stream_write(ps, stream, stream_ctx);
    NetManager::GetInstance()->UnrefHandle(_handle);

    lsquic_stream_wantread(stream, 1);
    return;
}

// static
int QuicEngineClient::send_packets_out(void *packets_out_ctx, const struct lsquic_out_spec *specs, unsigned count)
{
    QuicEngineClient* qc_engine = static_cast<QuicEngineClient*>(packets_out_ctx);
    if (!qc_engine)
    {
        QUIC_WARNING_LOG(0, "packets_out_ctx is null for send_packets_out");
        return -1;
    }

    return qc_engine->send_packets_out(specs, count);
}


int QuicEngineClient::send_packets_out(const struct lsquic_out_spec *specs, unsigned count)
{
    QuicClientSocket* ps = dynamic_cast<QuicClientSocket*>(NetManager::GetInstance()->RefHandle(_handle));
    if (!ps)
    {
        QUIC_WARNING_LOG(_handle, "refhandle error to send packet out");
        return -1;
    }

    uint32_t n = 0;
    for (; n < count; ++n)
    {
        QUIC_DEBUG_LOG(_handle, "ps:%p", ps);
        if (NetlibError_None != do_send_packets_out(ps, specs, n))
        {
            break;
        }
    }
    NetManager::GetInstance()->UnrefHandle(_handle);

    if (n != count)
    {
        QUIC_WARNING_LOG(_handle, "not completely. need_iovlen:%d, sent_iovlen:%d", count, n);
    }

    if (n > 0)
    {
        QUIC_DEBUG_LOG(_handle, "send_packets_out ok. send_iov_count:%d total_iovcount:%d", n, count);
    }
    return n;
}