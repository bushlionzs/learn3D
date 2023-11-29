#pragma once

#include <memory>
#include <list>
#include <functional>
#include <unordered_set>
#include <sstream>
#include <future>

#include <platform_socket.h>
#include "adapter/executor_interface.h"
#include "utility/singleton.h"
#include "platform_util.h"
#include "inet_session.h"
#include "net_buffer.h"
#include <platform_log.h>
#include "time_util.h"
#include "socket_address.h"
#include "net_manager.h"

#include "lsquic.h"

#if defined (__cplusplus)
extern "C" {
#endif

#include "lsquic_hash.h"
#include "lsquic_logger.h"

#if defined (__cplusplus)
}
#endif


//////////////////////////////////////////////////
#ifndef LSENG_CLIENT
#define LSENG_CLIENT 0
#endif

typedef enum {
    QuicEngineClientMode = LSENG_CLIENT,
    QuicEngineServerMode = LSENG_SERVER,
} QuicEngineMode;


#define QUIC_FATAL_LOG(error_code, handle, fmt, ...)                                               \
    do                                                                                              \
    {                                                                                               \
        FATAL_LOG(" [%s] [err:%d] [%d#%d#%" PRIu64 "]: " fmt, __FUNCTION__, error_code,             \
        dy::common::getpid(), dy::common::gettid(), (uint64_t)handle, ##__VA_ARGS__)                \
    }                                                                                               \
    while (false)

#define QUIC_WARNING_LOG(handle, fmt, ...)                                                       \
    do                                                                                          \
    {                                                                                           \
        WARNING_LOG(" [%s] [%d#%d#%" PRIu64 "]: " fmt, __FUNCTION__,                            \
        dy::common::getpid(),  dy::common::gettid(), (uint64_t)handle, ##__VA_ARGS__)           \
    }                                                                                           \
    while (false)

#define QUIC_NOTICE_LOG(handle, fmt, ...)                                                       \
    do                                                                                          \
    {                                                                                           \
        NOTICE_LOG(" [%s] [%d#%d#%" PRIu64 "]: " fmt, __FUNCTION__,                             \
        dy::common::getpid(),  dy::common::gettid(), (uint64_t)handle, ##__VA_ARGS__)           \
    }                                                                                           \
    while (false)

#define QUIC_TRACE_LOG(handle, fmt, ...)                                                     \
    do                                                                                          \
    {                                                                                           \
        TRACE_LOG(" [%s] [%d#%d#%" PRIu64 "]: " fmt, __FUNCTION__,                              \
        dy::common::getpid(),  dy::common::gettid(), (uint64_t)handle, ##__VA_ARGS__)           \
    }                                                                                           \
    while (false)

#define QUIC_DEBUG_LOG(handle, fmt, ...)                                                       \
    do                                                                                          \
    {                                                                                           \
        DEBUG_LOG(" [%s] [%d#%d#%" PRIu64 "]: " fmt, __FUNCTION__,                              \
        dy::common::getpid(),  dy::common::gettid(), (uint64_t)handle, ##__VA_ARGS__)           \
    }                                                                                           \
    while (false)


#define QUIC_FLOW_LOG(handle, fmt, ...)                                                        \
    do                                                                                          \
    {                                                                                           \
        FLOW_LOG(" [%s] [%d#%d#%" PRIu64 "]: " fmt, __FUNCTION__,                               \
        dy::common::getpid(), dy::common::gettid(), (uint64_t)handle, ##__VA_ARGS__)            \
    }                                                                                           \
    while (false)


//////////////////////////////////////////////////
void lsquic_cid2str2(const lsquic_cid_t *cid, char *out, uint32_t out_len);

int keylog_log_line(void *ctx, const char *buf, size_t len);

const lsquic_logger_if keylog_if = { keylog_log_line };

struct lsquic_conn_ctx
{
    uint32_t _stream_num = 0;

    std::string to_string()
    {
        std::stringstream ss;
        ss << "[this:" << this
            << ",stream_num:" << _stream_num
            << "]";
        return ss.str();
    }
};

class QuicEngineBase;
struct lsquic_stream_ctx
{
    std::string to_string()
    {
        uint32_t now = get_seconds();
        std::stringstream ss;
        ss << "[this:" << this
            << ",new:" << _new
            << ",read_active:" << _read_active
            << ",write_active:" << _write_active
            << ",online:" << now - _new
            << ",read_size:" << _read_size
            << ",write_size:" << _write_size
            << ",peer_ip:" << _peer_ip
            << ",peer_port:" << _peer_port
            << "]";
        return ss.str();
    }

    void on_read(uint32_t size)
    {
        _read_size += size;
        _read_active = get_seconds();
        _active = _read_active;
    }
    void on_write(uint32_t size)
    {
        _write_size += size;
        _write_active = get_seconds();
        _active = _write_active;
    }

    struct lsquic_conn_ctx* conn_ctx = nullptr;
    QuicEngineBase* _quic_engine = nullptr;
	uint32_t _new = get_seconds();
    uint32_t _online = 0;
	uint32_t _active = _new;
	uint32_t _read_active = 0;
	uint32_t _write_active = 0;
    uint64_t _read_size = 0;
    uint64_t _write_size = 0;
    uint16_t _peer_port = 0;
    std::string _peer_ip;
    NetHandle _handle = INVALID_NET_HANDLE;
};


//////////////////////////////////////////////////
class QuicBuffer : public INetBuffer
{
public:
    QuicBuffer(uint32_t capacity)
        : INetBuffer(nullptr, capacity)
    {}

    bool process_data(const SessionData& sd) override
    {
        return true;
    }

private:
};


//////////////////////////////////////////////////
class QuicSocket;
class QuicEngineBase : public RefCountBase
{
public:
    QuicEngineBase(uint32_t recv_buffer_size, const std::shared_ptr<QuicConfig>& quic_cfg);
    virtual ~QuicEngineBase();

    virtual bool start() = 0;
    virtual void stop() { return; }

    virtual bool send(lsquic_stream_t* quic_stream) = 0;
    virtual bool connect_to() { return true; };

    virtual lsquic_stream_ctx_t* do_new_stream(lsquic_stream_t* stream) = 0;
    virtual void do_stream_read(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx) = 0;
    virtual void do_stream_write(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx) = 0;
    virtual void do_stream_close(lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx) = 0;

    void on_handle(NetHandle handle)
    {
        _handle = handle;
    }

    INetBuffer* get_quic_stack_buf() { return _quic_stack_buf; };

    void close();

    virtual int recv_udp_message(PlatformSocket* ps,
                            const char* buf, 
                            uint32_t size, 
                            const sockaddr *addr_remote, 
                            int addrlen);

    void do_stream_read(PlatformSocket* ps, lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx);
    void do_stream_write(QuicSocket* ps, lsquic_stream_t* stream, lsquic_stream_ctx_t* stream_ctx);

    template<typename F>
    bool post_task(F&& f, uint32_t delay_ms = 0)
    {
        if (!_executor)
        {
            return false;
        }
        return _executor->post([=] { f(); }, 0, delay_ms);
    }

    bool wait_drive_lsquic_engine(int32_t delay_ms = 10);

protected:
    bool process_quic_engine();

    void add_stream_cnt() { _stream_cnt++; }
    void del_stream_cnt() { _stream_cnt--; }

    int do_send_packets_out(PlatformSocket* ps, const struct lsquic_out_spec *specs, unsigned n);

protected:
    std::shared_ptr<dy_network::IExecutor> _executor = nullptr;
    QuicBuffer* _quic_stack_buf = nullptr;

    lsquic_engine_api _lsquic_api = { 0 };
    lsquic_stream_if _lsquic_server_if = { 0 };
    lsquic_engine_t* _lsquic_engine = { nullptr };
    lsquic_engine_settings _lsquic_setting;
    struct sockaddr_in _addr_local;
    struct sockaddr_in _addr_remote;

    uint64_t _stream_cnt = 0;

    std::atomic<NetHandle> _handle = {INVALID_NET_HANDLE};

    platform_timer_t _trigger_timer;
    platform_timer_t _release_timer;

    std::atomic_bool _is_closed { false };

    std::shared_ptr<QuicConfig> _quic_cfg;
};


//////////////////////////////////////////////////
static int32_t engine_trigger_timer_callback(void* param)
{
    QuicEngineBase* p = (QuicEngineBase*)param;
    p->wait_drive_lsquic_engine();

    return 0;
}

static int32_t engine_release_timer_callback(void* param)
{
    QuicEngineBase* p = (QuicEngineBase*)param;
    p->release();

    return 1;
}