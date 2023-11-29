#include "http_client.h"
#include <stdio.h>
#include <sstream>
#include <random>
#include <inttypes.h>
#include <netlib_error.h>
#include <net_factory.h>
#include <server_interface.h>
#include <http_session.h>
#include <server_def.h>
#include <http_util.h>
#include <platform_util.h>
#include <string_util.h>
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <platform_common.h>
#include <platform_log.h>
#include <http_defines.h>
#include <url.h>
#include <dy_dns.h>
#include <time_util.h>
#include "net_manager.h"
#include "net_helper.h"
#include "random_engine.h"
#include "sock_base.h"
#include "base64.h"

#define REDIRECT_STATUS_CODE 302
static IPlatformModule* _http_client_module = NULL;
static bool _http_client_flag = false;
static PlatformMutex _http_client_mutex;
static uint32_t _http_client_thread_count = 1;
void post_http_client_module_message(uint32_t messageid, uint64_t sender, uint64_t param, const void* message, uint32_t size);
typedef struct
{
    std::vector<std::string> _dns_ip_list;
    uint32_t _dns_ip_ix;
    uint64_t _last_dns_time;
}dns_cache_info_t;

typedef struct
{
    std::string _http_host;
    std::string _http_ip;
    std::string _http_location;
    std::string _http_body;
    std::string _http_content;
    std::string _http_method;
    std::string _http_useragent;
    uint16_t    _http_port;
    uint32_t    _http_timeout;
    bool        _ssl;
}http_request_info_t;

typedef struct
{
    int _dns_error;
    std::string _domain_name;
    std::vector<std::string> _ip_list;
}http_dns_result_t;

enum
{
    http_client_msg_release_client = 0,
    http_client_msg_timeout,
    http_client_dns_result,
    http_client_net_message,
    http_client_request
};

IHttpClient::IHttpClient()
{
}

IHttpClient::~IHttpClient()
{
}

int32_t IHttpClient::http_get(
    const std::string& url, 
    uint32_t timeout, 
    std::map<std::string, std::string>* http_header,
    const std::string *body)
{
    return 0;
}

int32_t IHttpClient::http_post(
    const std::string& url, 
    const char* data,
    uint32_t size,
    uint32_t timeout, 
    std::map<std::string, std::string>* http_header)
{
    return 0;
}

static int32_t http_client_timer_callback(platform_timer_t, void* timer_self, void* timer_param);

enum eHttpClientState
{
    HttpClientState_Normal = 0,
    HttpClientState_Dnsing = 1,
    HttpClientState_Requesting = 2,
    HttpClientState_Request = 3,
    HttpClientState_Response_Continue = 4,
    HttpClientState_Response = 5,
    HttpClientState_Reset = 6,
    HttpClientState_Close = 7,
    HttpClientState_Release = 8,
};

class CHttpClient: public IHttpClient, IServerInterface
{

public:
CHttpClient(
    const HTTPClientConfig& config,
    HTTPClientHandler* handler)
    : _config(config)
{
    _http_handler = handler;
    _http_handle = INVALID_NET_HANDLE;
    _http_timer_handle = INVALID_TIMER_ID;
    _http_ref = 1;
    _http_client_state = HttpClientState_Normal;
    _need_delete = false;
    _http_redirect_times = 0;
    _http_state_code = 0;
    _http_response_time = 0;

    _http_session = new HttpSession(this, false, false, true);
    _http_ssl_session = new HttpSession(this, true, false, true);
    _http_client_identity = 0;
    _http_client_hash_value = dy_network::RandomGenerator::create_id();

    _proxy_ip = config.proxy_ip;
    _proxy_port = config.proxy_port;
    _proxy_usrname = config.proxy_username;
    _proxy_passwd = config.proxy_passwd;

    DEBUG_LOG("[this:%p,session:%p,state:%d,identity:%d]CHttpClient create", this, _http_session, _http_client_state, _http_client_identity);
}

~CHttpClient()
{
    DEBUG_LOG("[this:%p,session:%p,state:%d,identity:%d]CHttpClient release", this, _http_session, _http_client_state, _http_client_identity);
    if (_http_session != NULL)
    {
        delete _http_session;
    }

    if (_http_ssl_session != NULL)
    {
        delete _http_ssl_session;
    }

    _http_handler->on_http_release(this);
}

uint32_t get_http_client_hash_value()
{
    return _http_client_hash_value;
}

bool is_http_continue_data()
{
    return _config.continue_data;
}
void set_user_data(void *ud)
{
    _user_data = ud;
}

void *get_user_data()
{
    return _user_data;
}

const void *get_user_data() const
{
    return _user_data;
}

virtual INetSession* get_changed_session()
{
    return nullptr;
}

static void http_dns_callback(dy_dns_t* result)
{
    http_dns_result_t* tmp = new http_dns_result_t;
    tmp->_dns_error = result->_dns_error;
    tmp->_ip_list = result->_ip_list;
    tmp->_domain_name = result->_domain_name;
    post_http_client_module_message(http_client_dns_result, (uint64_t)result->_user_data, (uint64_t)tmp, 0, 0);
}

void update_dns_cache(http_dns_result_t* result)
{
    std::map<std::string, dns_cache_info_t>::iterator itor = _dns_cache_map.find(result->_domain_name);
    if (itor != _dns_cache_map.end())
    {
        itor->second._dns_ip_ix = 0;
        itor->second._dns_ip_list = result->_ip_list;
        itor->second._last_dns_time = get_tick_count();
    }
    else
    {
        dns_cache_info_t tmp;
        tmp._dns_ip_ix = 0;
        tmp._dns_ip_list = result->_ip_list;
        tmp._last_dns_time = get_tick_count();
        _dns_cache_map[result->_domain_name] = tmp;
    }
}

bool get_dns_cache(const std::string& domain_name, std::string& ip)
{
    std::map<std::string, dns_cache_info_t>::iterator itor = _dns_cache_map.find(domain_name);

    if (itor == _dns_cache_map.end())
    {
        return false;
    }

    dns_cache_info_t& tmp = itor->second;

    uint64_t current = get_tick_count();

    if (current - tmp._last_dns_time > _config.dns_cache_time)
    {
        return false;
    }

    if (tmp._dns_ip_list.empty())
    {
        return false;
    }

    if (_config.dns_ip_rool)
    {
        ip = tmp._dns_ip_list[++tmp._dns_ip_ix % tmp._dns_ip_list.size()];
    }
    else
    {
        uint32_t rdm = dy_network::RandomGenerator::create_id() % tmp._dns_ip_list.size();
        ip = tmp._dns_ip_list[rdm];
    }
    return true;
}

void process_dns_result(http_dns_result_t* result)
{
    if (_need_delete)
    {
        return;
    }
    if (0 == result->_dns_error)
    {
        if (!result->_ip_list.empty())
        {
            update_dns_cache(result);
            uint32_t rdm = dy_network::RandomGenerator::create_id() % result->_ip_list.size();
            _http_request_param._http_ip = result->_ip_list[rdm];
            DEBUG_LOG("[http host:%s,http ip:%s,this:%p,session:%p,state:%d,_http_ref:%d]get dns ip from network",
                    _http_request_param._http_host.c_str(), _http_request_param._http_ip.c_str(), this,_http_session, _http_client_state, _http_ref);
            if (_http_client_state == HttpClientState_Close)
            {
                return;
            }

            int ret = prepare_request(&_http_request_param);
            if (ret != 0)
            {
                invoke_http_event_callback(HTTP_SEND_FAIL);
            }
            else
            {
                set_http_client_state(HttpClientState_Requesting);
            }
        }
        else
        {
            invoke_http_event_callback(HTTP_DNS_ERROR);
        }
    }
    else
    {
        WARNING_LOG("[hostname:%s, err:%d, this:%p,session:%p,state:%d]http client dns error", result->_domain_name.c_str(), result->_dns_error, this,_http_session, _http_client_state);
        invoke_http_event_callback(HTTP_DNS_ERROR);
    }
}

bool check_and_set_http_state()
{
    ScopedLock<PlatformMutex> lock(_http_mutex);
    if (
        _http_client_state == HttpClientState_Normal ||
        _http_client_state == HttpClientState_Response ||
        _http_client_state == HttpClientState_Close ||
        _http_client_state == HttpClientState_Release)
    {
        //_http_client_state = HttpClientState_Requesting;
        return true;
    }

    return false;
}

bool check_http_client_state(eHttpClientState hcs)
{
    ScopedLock<PlatformMutex> lock(_http_mutex);
    return _http_client_state == hcs;
}

void set_http_client_state(eHttpClientState hcs)
{
    ScopedLock<PlatformMutex> lock(_http_mutex);
    _http_client_state = hcs;
}

void make_http_ctx_ctx(HTTPClientCtx& ctx)
{
    ctx.hnet = _http_handle;
    ctx.client_identity = _http_client_identity;
    ctx.conn_create_ms = _conn_create_time;
    ctx.request_send_ms = _request_send_time;
    ctx.request_connected_ms = _request_connected_time;
    ctx.server_host = _last_http_request_param._http_host;
    ctx.server_ip = _last_http_request_param._http_ip;
    ctx.server_port = _last_http_request_param._http_port;
    ctx.uri = _last_http_request_param._http_location;
    ctx.agent = _last_http_request_param._http_useragent;
    ctx.ssl = _last_http_request_param._ssl;
    ctx.response_status_code = _http_state_code;
    ctx.proxy_status_code = _proxy_state_code;
}

void invoke_http_event_callback(eHttpEvent event)
{
    HTTPClientCtx ctx;
    make_http_ctx_ctx(ctx);
    _http_handler->on_http_event(this, ctx, event);
}

void invoke_http_data_callback(const char* data, uint32_t size)
{
    HTTPClientCtx ctx;
    make_http_ctx_ctx(ctx);
    _http_handler->on_http_data(this, ctx, data, size);
}

void invoke_http_status_line_callback(const HTTPStatusLine &status_line)
{
    HTTPClientCtx ctx;
    make_http_ctx_ctx(ctx);
    _http_handler->on_http_status(this, ctx, status_line);
}

void invoke_http_headers_callback(const HTTPHeaders &headers)
{
    HTTPClientCtx ctx;
    make_http_ctx_ctx(ctx);
    _http_handler->on_http_headers(this, ctx, headers);
}

void build_http_content(const std::string& host, const char* http_method, const char* location, const std::string* body, http_request_info_t* info)
{
    std::ostringstream ss;
    ss << http_method << " /" << location << " HTTP/1.1\r\n";
    bool has_host = false;
    if (!_user_http_headers.empty())
    {
        auto itor = _user_http_headers.begin();
        for (; itor != _user_http_headers.end(); itor++)
        {
            if (itor->first == "Host")
            {
                has_host = true;
                break;
            }
        }
    }

    if (!has_host)
    {
        int family = dy_network::ip_family_from_string(host.c_str());
        if (AF_INET6 == family)
        {
            ss << "Host: [" << host << ']';
        }
        else
        {
            ss << "Host: " << host;
        }

        uint16_t default_port = info->_ssl ? 443 : 80;
        if (info->_http_port != default_port)
        {
            ss << ':' << info->_http_port;
        }

        ss << "\r\n";
    }

    ss << "Content-Length: " << (int32_t)info->_http_body.size() << "\r\n";

    if (!_user_http_headers.empty())
    {
        auto itor = _user_http_headers.begin();
        for (; itor != _user_http_headers.end(); itor++)
        {
            ss << itor->first << ": " << itor->second << "\r\n";
            if (itor->first == "Host")
            {
                has_host = true;
            }
            else if (itor->first == "User-Agent")
            {
                info->_http_useragent = itor->second;
            }
        }
    }

    ss << "\r\n";

    if (body && !body->empty())
    {
        ss << *body;
    }

    info->_http_content = ss.str();
}

int32_t process_http_request()
{
    if (_http_handle != INVALID_NET_HANDLE)
    {
        if (
            _http_request_param._http_host != _last_http_request_param._http_host ||
            _http_request_param._ssl != _last_http_request_param._ssl ||
            _http_request_param._http_port != _last_http_request_param._http_port)
        {
            _http_client_state = HttpClientState_Reset;
            close();
            return NetlibError_None;
        }
    }

	if (check_http_client_state(HttpClientState_Close))
	{
		set_http_client_state(HttpClientState_Reset);
		return 0;
	}
    return visit_http(&_http_request_param);
}

bool interval_parse_http_info(const std::string& url, http_request_info_t* info)
{
    if (!parse_http_url(url, info->_http_host, info->_http_port, info->_http_location, info->_ssl))
    {
        return false;
    }
#ifdef DY_NETWORK_DISNABLE_SSL
    if (info->_ssl)
    {
        WARNING_LOG("[this:%p,session:%p,state:%d,identity:%d,url:%s] https not supported", this, _http_session, _http_client_state, _http_client_identity, url.c_str());
        return false;
    }
#endif

    build_http_content(info->_http_host, info->_http_method.c_str(), info->_http_location.c_str(), &info->_http_body, info);

    if (!_proxy_ip.empty())
    {
        info->_ssl = false;
    }

    return true;
}

int32_t http_request(
    const std::string& url, 
    const char* data,
    uint32_t size,
    uint32_t timeout, 
    const std::map<std::string, std::string>* http_header,
    const char* method)
{
    DEBUG_LOG("[url:%s,identity:%d,this:%p,state:%d]http_request", url.c_str(), _http_client_identity, this, _http_client_state);
    if (!check_and_set_http_state())
    {
        return NetlibError_Try_Later;
    }

    if (http_header)
    {
        _user_http_headers = *http_header;
    }
    else
    {
        _user_http_headers.clear();
    }

    _http_request_param._http_method = method;
    _http_request_param._http_timeout = timeout;
    if (data)
    {
        _http_request_param._http_body.assign(data, size);
    }

    if (!interval_parse_http_info(url, &_http_request_param))
    {
        return NetlibError_InvalidUrl;
    }

    Ref(); // post msg ref
    post_http_client_module_message(http_client_request, (uint64_t)this, 0, 0, 0);
    return NetlibError_None;
}
int32_t http_get(const std::string& url, uint32_t timeout, std::map<std::string, std::string>*http_header, const std::string *body)
{
    const char* data = nullptr;
    uint32_t size = 0;
    if (body)
    {
        data = body->data();
        size = body->size();
    }
    return http_request(url, data, size, timeout, http_header, "GET");
}

int32_t http_post(
    const std::string& url, 
    const char* data,
    uint32_t size,
    uint32_t timeout, 
    std::map<std::string, std::string>* http_header) override
{
    return http_request(url, data, size, timeout, http_header, "POST");
}



void generate_connect_message(std::string& msg, http_request_info_t* info)
{
    std::string tmp = _proxy_usrname + ":" + _proxy_passwd;
    Base64Encrypt encrypt(tmp.c_str(), tmp.size());
    tmp = encrypt.GetString();
    msg = dy::str_format("CONNECT %s:%d HTTP/1.0\r\nProxy-Authorization: Basic %s\r\n\r\n", 
        info->_http_host.c_str(), info->_http_port, tmp.c_str());
}

int prepare_request(http_request_info_t* info)
{
    INetSession* net_session = NULL;

    if (info->_ssl)
    {
        net_session = _http_ssl_session;
    }
    else
    {
        net_session = _http_session;
    }

    _last_http_request_param = *info;

    if (_http_handle == INVALID_NET_HANDLE)
    {
	    _conn_create_time = get_tick_count();
        SessionData sessiondata;
        sessiondata.m_PeerIP = info->_http_ip;
        sessiondata.m_PeerPort = info->_http_port;
        sessiondata.m_param = (void*)(uintptr_t)(_http_client_identity + 1);

        if (!_proxy_ip.empty())
        {
            sessiondata.m_PeerPort = _proxy_port;
            net_session = _http_session;
        }

		Ref();
        _http_handle = NetFactory::GetInstance()->CreateTcpConnection(net_session, sessiondata);

        if (_http_handle == INVALID_NET_HANDLE)
        {
            WARNING_LOG("CreateTcpConnection failed");
            return NetlibError_ConnectionError;
        }

        _http_handle_bak = _http_handle;

        if (_config.tcp_keepalive)
        {
            TcpKeepAliveOption options;
            options.idle_sec = _config.tcp_keepalive_idle_sec;
            options.intvl_sec = _config.tcp_keepalive_intvl_sec;
            options.probes = _config.tcp_keepalive_probes;

            NetManager::GetInstance()->set_tcp_keepalive(_http_handle, &options);
        }

        _http_client_identity++;


        if (!_proxy_ip.empty())
        {
            return send_proxy_connect(info);
        }
    }

    return send_http_message(info);
}

int send_proxy_connect(http_request_info_t* info)
{
    close_timer();

    if (info->_http_timeout > 0)
    {
        Ref();
        _http_timer_handle = platform_create_timer(info->_http_timeout, http_client_timer_callback, nullptr, this);
        if (_http_timer_handle == INVALID_TIMER_ID)
        {
            Unref();
            WARNING_LOG("[ip:%s:%d,timeout:%d,ssl:%d]create timer failed in send_proxy_connect", info->_http_ip.c_str(), info->_http_port, info->_http_timeout, info->_ssl);
            return NetlibError_Try_Later;
        }
    }

    //send connect message
    std::string connect_msg;
    generate_connect_message(connect_msg, info);

    int ret = NetFactory::GetInstance()->SendData(_http_handle, (const uint8_t*)connect_msg.c_str(), (uint32_t)connect_msg.size());

    _proxy_connect = true;
    return ret;
}

int send_http_message(http_request_info_t* info)
{
    close_timer();


    _request_send_time = get_tick_count();
    _http_response_time = _request_send_time;

    if (info->_http_timeout > 0)
    {
        Ref();
        _http_timer_handle = platform_create_timer(info->_http_timeout, http_client_timer_callback, nullptr, this);
        if (_http_timer_handle == INVALID_TIMER_ID)
        {
            Unref();
            WARNING_LOG("[ip:%s:%d,timeout:%d,ssl:%d]create timer failed in send_http_message", info->_http_ip.c_str(), info->_http_port, info->_http_timeout, info->_ssl);
            return NetlibError_Try_Later;
        }
    }

    int ret = NetFactory::GetInstance()->SendData(_http_handle, (const uint8_t*)info->_http_content.c_str(), (uint32_t)info->_http_content.size());

    return ret;
}

int visit_http(http_request_info_t* info)
{
    std::string* host = &info->_http_host;
    if (!_proxy_ip.empty())
    {
        host = &_proxy_ip;
    }
    if (AF_UNSPEC == dy_network::ip_family_from_string(host->c_str()))
    {
        if (!get_dns_cache(*host, info->_http_ip))
        {
            Ref();
            DnsHandle dh = dns_resolve(*host, http_dns_callback, this);
            if (dh < 0)
            {
                Unref();
                return dh;
            }

            return 0;
        }

        DEBUG_LOG("[http host:%s,url:%s,http ip:%s,identity:%d,this:%p,state:%d]get dns ip from cache",
			info->_http_host.c_str(), info->_http_location.c_str(), info->_http_ip.c_str(), _http_client_identity,this,_http_client_state);
    }
    else
    {
        info->_http_ip = *host;
    }

	set_http_client_state(HttpClientState_Requesting);

    if (_http_handle != INVALID_NET_HANDLE)
    {
        if (_http_request_param._http_ip != _last_http_request_param._http_ip)
        {
            _http_client_state = HttpClientState_Reset;
            close();
            return NetlibError_None;
        }
    }

    return prepare_request(info);
}

int redirect(const std::string& http_location)
{
    DEBUG_LOG("[location:%s,this:%p,session:%p,state:%d,_http_ref:%d]redirect", http_location.c_str(), this,_http_session, _http_client_state, _http_ref);
    _http_redirect_times++;

    if (_http_redirect_times >= _config.redirect_times)
    {
        return NetlibError_Redirect_Error;
    }
    std::string host;
    std::string location;

    if (!interval_parse_http_info(http_location, &_http_request_param))
    {
        invoke_http_event_callback(HTTP_302_ERROR);
        return NetlibError_302_Error;
    }

    return visit_http(&_http_request_param);
}

int close_timer()
{
    if (INVALID_TIMER_ID != _http_timer_handle)
    {
        platform_timer_t tmp = _http_timer_handle;
        _http_timer_handle = INVALID_TIMER_ID;
        if (platform_delete_timer(tmp))
        {
            Unref();
        }
    }
    return 0;
}

int close_net_handle()
{
    if (INVALID_NET_HANDLE != _http_handle)
    {
        _http_handle = INVALID_NET_HANDLE;
        DEBUG_LOG("[this:%p,session:%p,identity:%d,handle:%" PRIu64 ",state:%d,_http_ref:%d]prepare close http handle", 
            this, _http_session, _http_client_identity, _http_handle_bak, _http_client_state, _http_ref);
        if (!check_http_client_state(HttpClientState_Reset))
		{
		    set_http_client_state(HttpClientState_Close);
		}

        NetFactory::GetInstance()->CloseNetHandle(_http_handle_bak);
    }
    return 0;
}

int process_network_message(uint32_t msg_id, const uint8_t* data, uint32_t size)
{
    switch (msg_id)
    {
    case NetMsg_HttpReponse_StatusLine:
        {
            process_status_line(data, size);
        }
        break;
    case NetMsg_HttpReponse_Headers:
        {
            process_response_header(data, size);
        }
        break;
    case NetMsg_HttpDataResponse:

        if (!_config.dont_redirect && REDIRECT_STATUS_CODE == _http_state_code)
        {
            return close();
        }
        _http_redirect_times = 0;

        DEBUG_LOG("[handle:%" PRIu64 ", size:%d]recv http client data", _http_handle, size);
        if (_config.continue_data)
        {
            if (0 == size)
            {
                close_timer();
                set_http_client_state(HttpClientState_Response);
            }
            else
            {

                set_http_client_state(HttpClientState_Response_Continue);
            }
        }
        else
        {
            close_timer();
            set_http_client_state(HttpClientState_Response);
        }
        _http_response_time = get_tick_count();
        invoke_http_data_callback((const char*)data, size);

        break;
    case NetMsg_Close:

        DEBUG_LOG("[handle:%" PRIu64 ",identity:%d,this:%p,session:%p,state:%d,_http_ref:%d]NetMsg_Close", 
            _http_handle_bak, _http_client_identity, this, _http_session, _http_client_state, _http_ref);
        internal_close();
        break;
    case NetMsg_Session_Release:
        internal_release(data, size);
        break;
    case NetMsg_Connected:
    {
        session_info_t* info = (session_info_t*)data;
        DEBUG_LOG("[handle:%llu,local_port:%d,peer_ip:%s, http_session:%p,this:%p,identity:%d,state:%d,_http_ref:%d]NetMsg_Connected",
            _http_handle, info->local_port, info->peer_ip, _http_session, this, _http_client_identity, _http_client_state, _http_ref);
        _request_connected_time = get_tick_count();
        invoke_http_event_callback(HTTP_EVENT_CONNECTED);
    }

        break;
    default:
        break;
    }

    return 0;
}

int process_status_line(const uint8_t* data, uint32_t size)
{
    const HTTPStatusLine* status_line = *(HTTPStatusLine**)data;
    if (status_line)
    {
        
        if (!_proxy_connect)
        {
            _http_state_code = status_line->status_code;
            invoke_http_status_line_callback(*status_line);
        }
        else
        {
            _proxy_state_code = status_line->status_code;

            if (status_line->status_code == 200)
            {
                SockBase* sock = NetManager::GetInstance()->RefHandle(_http_handle);

                if (sock)
                {
                    sock->change_session(_http_ssl_session);

                    NetManager::GetInstance()->UnrefHandle(_http_handle);
                    this->send_http_message(&_http_request_param);
                }
                else
                {
                    WARNING_LOG("[handle:%llu,this:%p]RefHandle exception", _http_handle, this);
                    close();
                }
            }
            else
            {
                close();
            }
            
        }
        delete status_line;
    }

    _proxy_connect = false;

    return 0;
}

int process_response_header(const uint8_t* data, uint32_t size)
{
    const HTTPHeaders* http_headers = *(HTTPHeaders**)data;
    if (http_headers)
    {
        invoke_http_headers_callback(*http_headers);

        if (_http_state_code == REDIRECT_STATUS_CODE)
        {
            HTTPHeaders::const_iterator itor = http_headers->find("location");
            if (itor != http_headers->end())
            {
                _http_location = itor->second;
            }
            else
            {
                _http_location.clear();
            }
        }
        else
        {
            _http_location.clear();
        }
        delete http_headers;
    }
    return 0;
}

int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size)
{
    Ref(); // post msg ref
    post_http_client_module_message(http_client_net_message, (uint64_t)this, (uint64_t)msg_id, data, size);

    return 0;
}

uint32_t get_http_recv_buffer_size()
{
    return _config.recv_buffer_size;
}

uint32_t get_send_buffer_size()
{
    return _config.send_buffer_size;
}

void internal_close()
{
    close_timer();
    if (INVALID_NET_HANDLE == _http_handle && !_need_delete)
    {
        if (_http_client_state == HttpClientState_Reset)
        {
            return;
        }

        /*if (!_config.dont_redirect && _http_state_code == REDIRECT_STATUS_CODE)
        {
            return;
        }*/
    }

    if (_http_handle != INVALID_NET_HANDLE)
    {
        close_net_handle();
    }

    invoke_http_event_callback(HTTP_EVENT_CLOSE);
    _http_state_code = 0;
    _http_redirect_times = 0;
    set_http_client_state(HttpClientState_Close);
}

void internal_release(const uint8_t* data, uint32_t size)
{
	const session_info_t* info = (const session_info_t*)data;
	uint32_t identity = (uint32_t)(uint64_t)info->param;
    DEBUG_LOG("NetMsg_Session_Release:%p,session:%p,identity:%d, _http_client_identity:%d, state:%d,_http_ref:%d\n", this, _http_session, identity, _http_client_identity, _http_client_state, _http_ref);

    if (Unref())
    {
        return;
    }

    if (_http_client_state == HttpClientState_Reset)
    {
        visit_http(&_http_request_param);
        return;
    }

    set_http_client_state(HttpClientState_Release);

    if (!_config.dont_redirect && _http_state_code == REDIRECT_STATUS_CODE)
    {
        int ret = redirect(_http_location);
        if (ret == 0)
        {
            return;
        }
    }

}

void external_close()
{
    _http_state_code = 0;
    _http_redirect_times = 0;
    _need_delete = true;
    DEBUG_LOG("[this:%p,http_session:%p,state:%d,identity:%d,_http_ref:%d]external_close", this, _http_session, _http_client_state, _http_client_identity, _http_ref);
    close();
    Unref();
}

void timeout()
{
    if (!_config.is_absolute_timeout)
    {
        uint64_t current = get_tick_count();
        if (current > _http_response_time)
        {
            if (current - _http_response_time < _last_http_request_param._http_timeout)
            {
                return;
            }
        }
        else
        {
            return;
        }
    }


    DEBUG_LOG("[handle:%" PRIu64 ",timeout:%d,this:%p,session:%p,identity:%d,_http_ref:%d]http client timeout",
		_http_handle, _last_http_request_param._http_timeout, this, _http_session, _http_client_identity, _http_ref);
    invoke_http_event_callback(HTTP_EVENT_TIMEOUT);
    close();
}

bool close()
{
    close_net_handle();
    close_timer();
    return true;
}

void Ref()
{
    ScopedLock<PlatformMutex> lock(_http_mutex);
    ++_http_ref;
}

bool Unref()
{
    bool del = false;
    {
        ScopedLock<PlatformMutex> lock(_http_mutex);
        --_http_ref;
        if (_http_ref <= 0)
        {
            del = true;
        }
    }
    if (del)
    {
        delete this;
    }

    return del;
}

private:
    INetSession* _http_session;
    INetSession* _http_ssl_session;
    NetHandle _http_handle;
    NetHandle _http_handle_bak = INVALID_NET_HANDLE;
    HTTPClientHandler* _http_handler = nullptr;

    platform_timer_t _http_timer_handle;
    std::map<std::string, std::string> _user_http_headers;
    PlatformMutex _http_mutex;
    int32_t      _http_ref;
    void *_user_data;

    eHttpClientState _http_client_state;
    const HTTPClientConfig _config;
    bool _need_delete;

    uint16_t _http_state_code;
    uint16_t _proxy_state_code;
    std::string _http_location;
    uint32_t _http_redirect_times;

    http_request_info_t _http_request_param;
    http_request_info_t _last_http_request_param;
    std::map<std::string, dns_cache_info_t> _dns_cache_map;

    uint64_t _http_response_time;
    uint64_t _request_send_time = 0;
    uint64_t _request_connected_time = 0;
    uint64_t _conn_create_time = 0;

    uint32_t _http_client_identity;

    uint32_t _http_client_hash_value;

    std::string _proxy_ip;
    uint32_t _proxy_port;
    std::string _proxy_usrname;
    std::string _proxy_passwd;

    bool _proxy_connect = false;
};

static int32_t http_client_timer_callback(platform_timer_t, void* timer_self, void* timer_param)
{
    CHttpClient* p = (CHttpClient*)timer_param;

    p->Ref(); // post msg addref
    post_http_client_module_message(http_client_msg_timeout, (uint64_t)timer_param, 0, 0, 0);

    return 0;
}

static void http_client_init()
{
}

const char* get_http_event_string(eHttpEvent event)
{
    if (event == HTTP_EVENT_CONNECTED)
    {
        return "http_connected";
    }
    else if (event == HTTP_EVENT_CLOSE)
    {
        return "http_close";
    }
    else if (event == HTTP_EVENT_TIMEOUT)
    {
        return "http_timeout";
    }
    else if (event == HTTP_DNS_ERROR)
    {
        return "dns_error";
    }
    else
    {
        return "invalid http event";
    }
}

static uint32_t http_client_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg , uint32_t msg_size, void* pNetThreadData)
{
    if (msg_id == http_client_net_message)
    {
        CHttpClient* tmp = (CHttpClient*)sender;
        uint32_t msg_id = (uint32_t)(uint64_t)param;
        tmp->process_network_message(msg_id, (const uint8_t*)msg, msg_size);
        tmp->Unref(); // post msg unref
    }
    else if (msg_id == http_client_request)
    {
        CHttpClient* tmp = (CHttpClient*)sender;
        tmp->process_http_request();
        tmp->Unref(); // post msg unref
    }
    else if (msg_id == http_client_msg_timeout)
    {
        CHttpClient* tmp = (CHttpClient*)sender;
        tmp->timeout();
        tmp->Unref(); // post msg unref
    }
    else if (msg_id == http_client_msg_release_client)
    {
        CHttpClient* tmp = (CHttpClient*)sender;
        tmp->external_close();
    }
    else if (msg_id == http_client_dns_result)
    {
        CHttpClient* tmp = (CHttpClient*)sender;
        http_dns_result_t* result = (http_dns_result_t*)param;
        tmp->process_dns_result(result);
        tmp->Unref();  // post msg unref
        delete result;
    }
    return 0;
}

IHttpClient* create_http_client(
    const HTTPClientConfig& config,
    HTTPClientHandler* handler)
{
    if (!_http_client_flag)
    {
        ScopedLock<PlatformMutex> lock(_http_client_mutex);
        if (!_http_client_flag)
        {
            extern struct NetLibParam g_param;
            _http_client_thread_count = g_param._http_client_thread_count;

            if (_http_client_thread_count > 4)
            {
                _http_client_thread_count = 4;
            }

            if (_http_client_thread_count == 0)
            {
                _http_client_thread_count = 1;
            }
            INIT_LOG("[thread count:%d]http client thread create sucessfully", _http_client_thread_count);
            _http_client_module = create_platform_module(_http_client_thread_count, "http_client");
            _http_client_flag = true;
            for (int i = 0; i < _http_client_thread_count; i++)
            {
                _http_client_module->attach_module(i, http_client_init, http_client_entry, NULL);
            }

            _http_client_module->run_module();
        }
    }
    CHttpClient* httpclient = new CHttpClient(config, handler);
    return httpclient;
}

void post_http_client_module_message(uint32_t messageid, uint64_t sender, uint64_t param, const void* message, uint32_t size)
{
	if (_http_client_module)
	{
		CHttpClient* client = (CHttpClient*)sender;
		uint32_t hash_value = client->get_http_client_hash_value();
		uint32_t index = hash_value % _http_client_thread_count;
		_http_client_module->post_module_message(index, messageid, sender, param, message, size);
	}
}

void release_http_client(IHttpClient* http_client)
{
    post_http_client_module_message(http_client_msg_release_client, (uint64_t)http_client, 0, 0, 0);
}
void destory_http_client()
{
    if (_http_client_module)
    {
        destory_platform_module(_http_client_module);
        _http_client_module = nullptr;
    }
}
