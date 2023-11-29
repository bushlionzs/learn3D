#pragma once

#include "quic_engine_base.h"


//////////////////////////////////////////////////
class QuicServerSocket;
class QuicEngineServer : public QuicEngineBase
{
public:
    QuicEngineServer(uint32_t recv_buffer_size, 
                    const std::shared_ptr<QuicConfig>& quic_cfg, 
                    const std::string& local_ip, 
                    uint16_t local_port);
    virtual ~QuicEngineServer();

    virtual bool start();
    virtual bool send(lsquic_stream_t* quic_stream);

    virtual lsquic_stream_ctx_t* do_new_stream(lsquic_stream_t* stream);
    virtual void do_stream_read(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx) {};
    virtual void do_stream_write(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx) {}
    virtual void do_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx);

private:
    static void qe_on_hsk_done(lsquic_conn_t *c, enum lsquic_hsk_status s);
    static lsquic_conn_ctx_t* qe_on_new_conn(void *stream_if_ctx, lsquic_conn_t *conn);
    static void qe_on_new_token(lsquic_conn_t *c, const unsigned char *token, size_t token_size);
    static void qe_on_zero_rtt_info(lsquic_conn_t *c, const unsigned char *, size_t);
    static void qe_on_goaway_received(lsquic_conn_t *conn);
    static void qe_on_conn_closed(lsquic_conn_t *conn);
    static lsquic_stream_ctx_t* qe_on_new_stream(void* stream_if_ctx, lsquic_stream_t* s);
    static void qe_on_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx);
    static void qe_on_stream_read(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx);
    static void qe_on_stream_write(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx);
    static int send_packets_out(void *ctx, const struct lsquic_out_spec *specs, unsigned n_specs);

public:
    struct ssl_ctx_st* _prog_ssl_ctx;

private:
    std::unordered_set<lsquic_stream_t*> _lsquic_stream_set;
    struct lsquic_hash* _prog_certs;

    std::string _local_ip;
    uint16_t _local_port;
};