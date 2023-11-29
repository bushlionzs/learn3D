#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include <string>
#include <vector>
#include <utility>
#include <stdint.h>
#include <map>
#include <net_lib.h>

#include "http_defines.h"
#include "string_view.h"

class IHttpClient
{
protected:
    IHttpClient();
    ~IHttpClient();
public:
    virtual void set_user_data(void *ud) = 0;
    virtual void *get_user_data() = 0;
    virtual const void *get_user_data() const = 0;
    virtual bool close() = 0;
    virtual int32_t http_get(
        const std::string& url, 
        uint32_t timeout,
        std::map<std::string, std::string>* http_header = nullptr,
        const std::string *body = nullptr);
    virtual int32_t http_post(
        const std::string& url, 
        const char* data,
        uint32_t size,
        uint32_t timeout, 
        std::map<std::string, std::string>* http_header = nullptr);
};

struct HTTPClientCtx
{
    NetHandle hnet = 0;
    uint64_t conn_create_ms = 0;
    uint64_t request_send_ms = 0;
    uint64_t request_connected_ms = 0;
    uint32_t client_identity = 0;
    string_view uri;
    string_view agent;
    string_view server_host;
    string_view server_ip;
    uint16_t server_port = 0;
    bool ssl = false;
    bool quic = false;
    int response_status_code = 0;
    int proxy_status_code = 0;
};

enum eHttpEvent
{
    HTTP_EVENT_CONNECTED    = 0,
    HTTP_EVENT_CLOSE        = 1,
    HTTP_EVENT_TIMEOUT      = 2,
    HTTP_DNS_ERROR          = 3,
    HTTP_302_ERROR          = 4,
    HTTP_SEND_FAIL          = 5,
};


const char* get_http_event_string(eHttpEvent event);


struct HTTPClientConfig
{
    uint32_t recv_buffer_size = (1024 * 512);
    uint32_t send_buffer_size = (1024 * 512);    
    uint32_t dns_cache_time = (60 * 5 * 1000);
    uint32_t redirect_times = 4;
    bool     dns_ip_rool = false;
    bool     continue_data = false;
    bool     is_absolute_timeout = false;
    bool     http2_over_quic = false;
    bool     dont_redirect = false;
    bool     tcp_keepalive = false;
    int      tcp_keepalive_idle_sec = -1;
    int      tcp_keepalive_intvl_sec = -1;          // not support on MAC
    int      tcp_keepalive_probes = -1;             // not support on MAC or windows

    std::string proxy_ip;
    uint32_t proxy_port;
    std::string proxy_username;
    std::string proxy_passwd;

    HTTPClientConfig(){}
};



class HTTPClientHandler
{
protected:
    virtual ~HTTPClientHandler() = default;
public:

    virtual int32_t on_http_event(IHttpClient*, const HTTPClientCtx& ctx, eHttpEvent event) { return 0; }
    virtual int32_t on_http_data(IHttpClient*, const HTTPClientCtx& ctx, const char* data, uint32_t size) { return 0; }
    virtual int32_t on_http_status(IHttpClient*, const HTTPClientCtx& ctx, const HTTPStatusLine&) { return 0; }
    virtual int32_t on_http_headers(IHttpClient*, const HTTPClientCtx& ctx, const HTTPHeaders&) { return 0; }
    virtual void on_http_release(IHttpClient*) {}
};

IHttpClient* create_http_client(
    const HTTPClientConfig& config,
    HTTPClientHandler* handler);


void release_http_client(IHttpClient* http_client);

void destory_http_client();





#endif //__HTTP_CLIENT_H__
