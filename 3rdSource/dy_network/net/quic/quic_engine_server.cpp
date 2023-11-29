#include "quic_engine_server.h"
#include "quic_socket.h"


////////////////////////////////////////////////////////////
struct server_cert
{
    char                *ce_sni;
    struct ssl_ctx_st   *ce_ssl_ctx;
    struct lsquic_hash_elem ce_hash_el;
};

static char s_alpn[0x100];

static int
select_alpn (SSL *ssl, const unsigned char **out, unsigned char *outlen,
                    const unsigned char *in, unsigned int inlen, void *arg)
{
    int r;

    r = SSL_select_next_proto((unsigned char **) out, outlen, in, inlen,
                                    (unsigned char *) s_alpn, strlen(s_alpn));
    if (r == OPENSSL_NPN_NEGOTIATED)
        return SSL_TLSEXT_ERR_OK;
    else
    {
        QUIC_WARNING_LOG(0, "no supported protocol can be selected from %.*s",
                                                    (int) inlen, (char *) in);
        return SSL_TLSEXT_ERR_ALERT_FATAL;
    }
}

int
load_cert (struct lsquic_hash *certs, const char* cert_file, const char* key_file, const char* sni = nullptr)
{
    int rv = -1;
    struct server_cert *cert = nullptr;
    EVP_PKEY *pkey = nullptr;
    FILE *f = nullptr;

    if (!cert_file || !key_file || (0 == strlen(cert_file)) || (0 == strlen(key_file)))
    {
        QUIC_WARNING_LOG(0, "cert:%s or key:%s is empty", cert_file, key_file);
        return rv;
    }

    cert = (struct server_cert *)calloc(1, sizeof(*cert));
    if (sni)
        cert->ce_sni = strdup(sni);

    cert->ce_ssl_ctx = SSL_CTX_new(TLS_method());
    if (!cert->ce_ssl_ctx)
    {
        QUIC_WARNING_LOG(0, "SSL_CTX_new failed");
        if (sni)
            free(cert->ce_sni);
        free(cert);
        return rv;
    }
    SSL_CTX_set_min_proto_version(cert->ce_ssl_ctx, TLS1_3_VERSION);
    SSL_CTX_set_max_proto_version(cert->ce_ssl_ctx, TLS1_3_VERSION);
    SSL_CTX_set_default_verify_paths(cert->ce_ssl_ctx);
    SSL_CTX_set_alpn_select_cb(cert->ce_ssl_ctx, select_alpn, NULL);
    SSL_CTX_set_early_data_enabled(cert->ce_ssl_ctx, 1);    /* XXX */
    if (1 != SSL_CTX_use_certificate_chain_file(cert->ce_ssl_ctx, cert_file))
    {
        QUIC_WARNING_LOG(0, "SSL_CTX_use_certificate_chain_file failed: %s", cert_file);
        if (sni)
            free(cert->ce_sni);
        free(cert);
        return rv;
    }

    if (strstr(key_file, ".pkcs8"))
    {
        f = fopen(key_file, "r");
        if (!f)
        {
            QUIC_WARNING_LOG(0, "fopen(%s) failed: %s", cert_file, strerror(errno));
            if (sni)
                free(cert->ce_sni);
            free(cert);
            return rv;
        }
        pkey = d2i_PrivateKey_fp(f, NULL);
        fclose(f);
        f = NULL;
        if (!pkey)
        {
            QUIC_WARNING_LOG(0, "Reading private key from %s failed", key_file);
            if (sni)
                free(cert->ce_sni);
            free(cert);
            return rv;
        }
        if (!SSL_CTX_use_PrivateKey(cert->ce_ssl_ctx, pkey))
        {
            QUIC_WARNING_LOG(0, "SSL_CTX_use_PrivateKey failed");
            if (sni)
                free(cert->ce_sni);
            free(cert);
            return rv;
        }
    }
    else if (1 != SSL_CTX_use_PrivateKey_file(cert->ce_ssl_ctx, key_file,
                                                            SSL_FILETYPE_PEM))
    {
        QUIC_WARNING_LOG(0, "SSL_CTX_use_PrivateKey_file failed");
        if (sni)
            free(cert->ce_sni);
        free(cert);
        return rv;
    }

    const int was = SSL_CTX_set_session_cache_mode(cert->ce_ssl_ctx, 1);
    QUIC_DEBUG_LOG(0, "set SSL session cache mode to 1 (was: %d)", was);

    lsquic_hash_elem *el = nullptr;
    if (sni)
    {
        el = lsquic_hash_insert(certs, cert->ce_sni, strlen(cert->ce_sni), cert, &cert->ce_hash_el);
    }
    else
    {
        el = lsquic_hash_insert(certs, nullptr, 0, cert, &cert->ce_hash_el);
    }

    if (el)
    {
        rv = 0;
    }
    else
    {
        QUIC_WARNING_LOG(0, "cannot insert cert for %s into hash table", cert->ce_sni);
        if (sni)
            free(cert->ce_sni);
        free(cert);        
    }

    return rv;
}

struct ssl_ctx_st *
lookup_cert (void *cert_lu_ctx, const struct sockaddr *sa_UNUSED,
             const char *sni)
{
    QUIC_DEBUG_LOG(0, "lookup cert. cert_lu_ctx:%p, sni:%s", cert_lu_ctx, sni);

    struct lsquic_hash_elem *el;
    struct server_cert *server_cert;

    if (!cert_lu_ctx)
        return NULL;

    el = lsquic_hash_first((struct lsquic_hash *)cert_lu_ctx);
    if (el)
    {
        server_cert = (struct server_cert *)lsquic_hashelem_getdata(el);
        if (server_cert)
            return server_cert->ce_ssl_ctx;
    }

    return NULL;
}


void
delete_certs (struct lsquic_hash *certs)
{
    struct lsquic_hash_elem *el;
    struct server_cert *cert;

    for (el = lsquic_hash_first(certs); el; el = lsquic_hash_next(certs))
    {
        cert = (struct server_cert *)lsquic_hashelem_getdata(el);
        SSL_CTX_free(cert->ce_ssl_ctx);
        free(cert->ce_sni);
        free(cert);
    }
    lsquic_hash_destroy(certs);
}

static SSL_CTX *
get_ssl_ctx (void *peer_ctx)
{
    QUIC_DEBUG_LOG(0, "get ssl ctx, peer_ctx:%p", peer_ctx);

    QuicEngineServer* qe = static_cast<QuicEngineServer*>(peer_ctx);
    return qe->_prog_ssl_ctx;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
QuicEngineServer::QuicEngineServer(uint32_t recv_buffer_size, 
                                    const std::shared_ptr<QuicConfig>& quic_cfg, 
                                    const std::string& local_ip, 
                                    uint16_t local_port)
    : QuicEngineBase(recv_buffer_size, quic_cfg)
    , _prog_ssl_ctx(nullptr)
    , _prog_certs(nullptr)
    , _local_ip(local_ip)
    , _local_port(local_port)
{
}

QuicEngineServer::~QuicEngineServer()
{
    _lsquic_stream_set.clear();

    if (_prog_ssl_ctx)
    {
        SSL_CTX_free(_prog_ssl_ctx);
        _prog_ssl_ctx = nullptr;
    }

    if (_prog_certs)
    {
        lsquic_hash_destroy(_prog_certs);
        _prog_certs = nullptr;
    }

    if (_lsquic_engine)
    {
        lsquic_engine_destroy(_lsquic_engine);
        _lsquic_engine = nullptr;
    }

    QUIC_FLOW_LOG(0, "delete QuicEngineServer, this:%p", this);
}

bool QuicEngineServer::start()
{
    memset(&_lsquic_setting, 0, sizeof(_lsquic_setting));
    lsquic_engine_init_settings(&_lsquic_setting, QuicEngineServerMode);
    _lsquic_setting.es_cc_algo = _quic_cfg->_congestion_ctrl_algo;
    constexpr char lsquic_ua[32] = "dyp2p/lsquic server agent";
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
    if (0 != lsquic_engine_check_settings(&_lsquic_setting, QuicEngineServerMode, err_buf, sizeof(err_buf)))
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
    _lsquic_api.ea_get_ssl_ctx = get_ssl_ctx;

    _prog_certs = lsquic_hash_create();
    if (0 != load_cert(_prog_certs, 
                _quic_cfg->_crt_file.c_str(), 
                _quic_cfg->_key_file.c_str(), 
                _quic_cfg->_sni.c_str()))
    {
        QUIC_FATAL_LOG(-1, 0, "load_cert failed");
        return false;   
    }

    _lsquic_api.ea_lookup_cert = lookup_cert;
    _lsquic_api.ea_cert_lu_ctx = _prog_certs;

    _lsquic_engine = lsquic_engine_new(QuicEngineServerMode, &_lsquic_api);
    if (!_lsquic_engine)
    {
        QUIC_FATAL_LOG(-1, 0, "lsquic_engine_new failed");
        return false;
    }

    unsigned char ticket_keys[48];
    _prog_ssl_ctx = SSL_CTX_new(TLS_method());
    if (_prog_ssl_ctx)
    {
        SSL_CTX_set_min_proto_version(_prog_ssl_ctx, TLS1_3_VERSION);
        SSL_CTX_set_max_proto_version(_prog_ssl_ctx, TLS1_3_VERSION);
        SSL_CTX_set_default_verify_paths(_prog_ssl_ctx);

        /* This is obviously test code: the key is just an array of NUL bytes */
        memset(ticket_keys, 0, sizeof(ticket_keys));
        if (1 != SSL_CTX_set_tlsext_ticket_keys(_prog_ssl_ctx,
                                            ticket_keys, sizeof(ticket_keys)))
        {
            QUIC_WARNING_LOG(0, "SSL_CTX_set_tlsext_ticket_keys failed");
            return false;
        }
    }
    else
        QUIC_WARNING_LOG(0, "cannot create SSL context");    

    memset(&_addr_local, 0, sizeof(_addr_local));
    _addr_local.sin_family = AF_INET;
    dy_network::SocketAddress local(_local_ip, _local_port);
    _addr_local.sin_addr = local.ipaddr().ipv4_address();
    _addr_local.sin_port = ntohs(local.port());

    if (0 != lsquic_global_init(LSQUIC_GLOBAL_SERVER))
    {
        QUIC_FATAL_LOG(-1, 0, "quic engine server global init failed");
        return false;
    }

    QUIC_FLOW_LOG(0, "new QuicEngineServer ok, this:%p, _lsquic_engine:%p", this, _lsquic_engine);
    return true;
}

bool QuicEngineServer::send(lsquic_stream_t* quic_stream)
{
    add_ref();
    bool ret = post_task([=](){
                if (_lsquic_stream_set.end() == _lsquic_stream_set.find(quic_stream))
                {
                    QUIC_DEBUG_LOG(0, "stream:%p not found to send data", quic_stream);
                    return;
                }

                lsquic_stream_ctx_t* stream_ctx = lsquic_stream_get_ctx(quic_stream);
                if (!stream_ctx)
                {
                    QUIC_WARNING_LOG(stream_ctx->_handle, "stream_ctx is null for stream:%p to send", 
                                        quic_stream);
                    return;
                }

                lsquic_stream_wantwrite(quic_stream, 1);
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

// static
void QuicEngineServer::qe_on_hsk_done(lsquic_conn_t *c, enum lsquic_hsk_status s)
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
lsquic_conn_ctx_t* QuicEngineServer::qe_on_new_conn(void *stream_if_ctx, lsquic_conn_t *conn)
{
    int lv = lsquic_conn_quic_version(conn);
    char cid_str[64] = {0};
    lsquic_cid2str2(lsquic_conn_id(conn), cid_str, sizeof(cid_str));

    lsquic_conn_ctx_t* conn_ctx = lsquic_conn_get_ctx(conn);
    if (conn_ctx)
    {
        QUIC_WARNING_LOG(0, "conn_ctx:%p, conn:%p existed already", conn_ctx, conn);
        return conn_ctx;
    }

    conn_ctx = new lsquic_conn_ctx_t;
    QUIC_FLOW_LOG(0, "on new conn. version:%d, cid:%s, conn:%p, conn_ctx:%p", lv, cid_str, conn, conn_ctx);
    return conn_ctx;
}

// static
void QuicEngineServer::qe_on_new_token(lsquic_conn_t *c, const unsigned char *token, size_t token_size)
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
void QuicEngineServer::qe_on_zero_rtt_info(lsquic_conn_t *c, const unsigned char * rtt_info, size_t rtt_size)
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
void QuicEngineServer::qe_on_goaway_received(lsquic_conn_t *conn)
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
void QuicEngineServer::qe_on_conn_closed(lsquic_conn_t *conn)
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
lsquic_stream_ctx_t* QuicEngineServer::qe_on_new_stream(void* stream_if_ctx, lsquic_stream_t* stream)
{
    if (!stream_if_ctx || !stream)
    {
        QUIC_WARNING_LOG(0, "stream_if_ctx:%p or stream:%p is null", stream_if_ctx, stream);
        return nullptr;
    }

    QuicEngineServer* quic_engine = reinterpret_cast<QuicEngineServer*>(stream_if_ctx);
    if(!quic_engine)
    {
        QUIC_WARNING_LOG(0, "quic_engine is null. stream_if_ctx:%p, stream:%p", stream_if_ctx, stream);
        return nullptr;
    }

    return quic_engine->do_new_stream(stream);
}

lsquic_stream_ctx_t* QuicEngineServer::do_new_stream(lsquic_stream_t* stream)
{
    if (_lsquic_stream_set.end() != _lsquic_stream_set.find(stream))
    {
        QUIC_WARNING_LOG(0, "stream:%p is existed", stream);
        return nullptr;
    }

    lsquic_stream_ctx* stream_ctx = new lsquic_stream_ctx();
    if (!stream_ctx)
    {
        QUIC_WARNING_LOG(0, "new stream_ctx error for stream:%p", stream);
        return nullptr;   
    }

    lsquic_conn_t* conn = lsquic_stream_conn(stream);
    if (!conn)
    {
        QUIC_WARNING_LOG(0, "conn is null for stream:%p stream_ctx:%p", stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }

    lsquic_conn_ctx_t* conn_ctx = lsquic_conn_get_ctx(conn);
    if (!conn_ctx)
    {
        QUIC_WARNING_LOG(0, "conn_ctx no existed for conn:%p stream:%p stream_ctx:%p", conn, stream, stream_ctx);
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

    stream_ctx->_quic_engine = this;

    QuicServerSocket* quic_server_socket 
                    = dynamic_cast<QuicServerSocket*>(NetManager::GetInstance()->RefHandle(_handle));
    if (!quic_server_socket)
    {
        QUIC_WARNING_LOG(_handle, "quic server socket refhandle error for stream:%p stream_ctx:%p", stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }

    QuicSocket* ps = quic_server_socket->on_new_stream_socket(stream);
    NetManager::GetInstance()->UnrefHandle(_handle);

    NetHandle handle = ps->GetNetHandle();
    if (ps != NetManager::GetInstance()->RefHandle(handle))
    {
        QUIC_WARNING_LOG(_handle, "refhandle error for "
                            "platform_socket:%p stream:%p stream_ctx:%p", 
                            ps, stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }
    stream_ctx->_handle = handle;

    ps->UpdateIpInfo(remote_ip, remote_port, local_ip, local_port);
    if (!ps->OnAccept())
    {
        QUIC_WARNING_LOG(stream_ctx->_handle, "platformsocket OnAccept error for "
                            "platform_socket:%p stream:%p stream_ctx:%p", 
                            ps, stream, stream_ctx);
        delete stream_ctx;
        return nullptr;
    }
    NetManager::GetInstance()->UnrefHandle(handle);

    stream_ctx->_peer_ip = remote_ip;
    stream_ctx->_peer_port = remote_port;

    lsquic_stream_wantread(stream, 1);
    conn_ctx->_stream_num++;
    _lsquic_stream_set.insert(stream);
    add_stream_cnt();
    
    QUIC_FLOW_LOG(stream_ctx->_handle, "new stream_ctx:%p for lsquic_stream:%p stream_id:%" PRIu64 
            " conn:%p stream_num:%d stream_info:%s. local:[%s:%u]",
            stream_ctx, stream, lsquic_stream_id(stream), 
            conn, conn_ctx->_stream_num, stream_ctx->to_string().c_str(),
            local_ip.c_str(), local_port);
    return stream_ctx;
}

// static
void QuicEngineServer::qe_on_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
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

void QuicEngineServer::do_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    NetHandle handle = stream_ctx->_handle;
    lsquic_conn_t* conn = lsquic_stream_conn(stream);
    if (!conn)
    {
        QUIC_FLOW_LOG(handle, "conn is null for stream close. "
                "stream:%p, stream_ctx:%p, stream_info:%s", 
                stream, stream_ctx, stream_ctx->to_string().c_str());
        return;
    }
    lsquic_conn_ctx_t* conn_ctx = lsquic_conn_get_ctx(conn);
    if (!conn_ctx)
    {
        QUIC_NOTICE_LOG(handle, "conn_ctx no existed for conn:%p stream:%p stream_ctx:%p", 
                    conn, stream, stream_ctx);
        return;
    }

    auto it = _lsquic_stream_set.find(stream);
    if (_lsquic_stream_set.end() == it)
    {
        QUIC_WARNING_LOG(handle, 
                        "conn:%p stream:%p stream_ctx:%p stream_info:%s not found to close", 
                        conn, stream, stream_ctx, stream_ctx->to_string().c_str());
        return;
    }
    _lsquic_stream_set.erase(it);

    QUIC_FLOW_LOG(handle, 
            "close stream only. conn:%p, stream:%p, stream_ctx:%p, stream_info:%s", 
            conn, stream, stream_ctx, stream_ctx->to_string().c_str());

    conn_ctx->_stream_num--;

    PlatformSocket* ps = NetManager::GetInstance()->RefHandle(handle);
    if (!ps)
    {
        QUIC_DEBUG_LOG(handle, "platform socket is null for stream:%p to destroy", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }
    ps->DestroySocket(1001);
    NetManager::GetInstance()->UnrefHandle(handle);

    delete stream_ctx;
    return;
}

// static
void QuicEngineServer::qe_on_stream_read(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!stream_ctx)
    {
        QUIC_WARNING_LOG(0, "stream_ctx is null for stream:%p to read", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    NetHandle handle = stream_ctx->_handle;
    PlatformSocket* ps = NetManager::GetInstance()->RefHandle(handle);
    if (!ps)
    {
        QUIC_DEBUG_LOG(handle, "platform socket is null for stream:%p to read", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    QuicEngineBase* quic_engine = stream_ctx->_quic_engine;
    quic_engine->do_stream_read(ps, stream, stream_ctx);
    NetManager::GetInstance()->UnrefHandle(handle);

    return;
}

// static
void QuicEngineServer::qe_on_stream_write(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx)
{
    if (!stream_ctx)
    {
        QUIC_WARNING_LOG(0, "stream_ctx is null for stream:%p to write", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    NetHandle handle = stream_ctx->_handle;
    QuicSocket* ps = dynamic_cast<QuicSocket*>(NetManager::GetInstance()->RefHandle(handle));
    if (!ps)
    {
        QUIC_DEBUG_LOG(handle, "platform socket is null for stream:%p to write", stream);
        lsquic_stream_shutdown(stream, 2);
        return;
    }

    QuicEngineBase* quic_engine = stream_ctx->_quic_engine;
    quic_engine->do_stream_write(ps, stream, stream_ctx);
    NetManager::GetInstance()->UnrefHandle(handle);

    return;
}

// static
int QuicEngineServer::send_packets_out(void *packets_out_ctx, const struct lsquic_out_spec *specs, unsigned count)
{
    QuicEngineServer* qc_engine = static_cast<QuicEngineServer*>(packets_out_ctx);
    if (!qc_engine)
    {
        QUIC_WARNING_LOG(0, "qc_engine is null");
        return -1;
    }

    uint32_t n = 0;
    for (; n < count; ++n)
    {
        PlatformSocket* ps = static_cast<PlatformSocket*>(specs[n].peer_ctx);
        if (!ps)
        {
            QUIC_WARNING_LOG(0, "ctx null for send_packets_out");
            break;
        }

        QUIC_DEBUG_LOG(ps->GetNetHandle(), "ps:%p", specs[n].peer_ctx);
        if (NetlibError_None != qc_engine->do_send_packets_out(ps, specs, n))
        {
            break;
        }
    }

    if (n != count)
    {
        QUIC_WARNING_LOG(0, "not completely. need_iovlen:%d, sent_iovlen:%d", count, n);
    }

    if (n > 0)
    {
        QUIC_DEBUG_LOG(0, "send_packets_out ok. send_iov_count:%d total_iovcount:%d", n, count);
    }
    return n;
}