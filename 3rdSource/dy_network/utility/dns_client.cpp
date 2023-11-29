#include "utility/dns_client.h"
#include "netlib_error.h"
#include "scoped_lock.h"
#include "time_util.h"
#include "server_def.h"

namespace dy_network
{
struct TimerParam
{
    uint16_t dns_id = 0;
    DNSClient *client = nullptr;
};

constexpr bool is_A_qtype_request(DNSReqPolicy req_policy)
{
    return DNSReqPolicy::A == req_policy || DNSReqPolicy::BOTH == req_policy;
}

constexpr bool is_AAAA_qtype_request(DNSReqPolicy req_policy)
{
    return DNSReqPolicy::AAAA == req_policy || DNSReqPolicy::BOTH == req_policy;
}

bool DNSIPList::empty() const
{
    return this->ip4.empty() && this->ip6.empty();
}

void DNSResult::from_answers(const std::vector<DNSAnswer>& answers)
{
    for (auto&& answer : answers)
    {
        if (answer._type == TYPE_A)
        {
            this->list.ip4.push_back(answer._data);
        }
        else if (answer._type == TYPE_AAAA)
        {
            this->list.ip6.push_back(answer._data);
        }
        else
        {
            continue;
        }

        if (answer._ttl < this->ttl)
        {
            this->ttl = answer._ttl;
        }
    }
}

bool HostCacheEntry::copy_to(uint64_t now, std::vector<std::string>& result) const
{
    if (now >= this->deadline_ms)
    {
        return false;
    }

    copy_to(result);

    return true;
}

void HostCacheEntry::copy_to(std::vector<std::string>& result) const
{
    size_t index = this->start_index++ % this->ip_list.size();
    for (size_t i = index; i < this->ip_list.size(); ++i)
    {
        result.emplace_back(this->ip_list[i]);
    }

    for (size_t i = 0; i < index; ++i)
    {
        result.emplace_back(this->ip_list[i]);
    }
}

DNSCtx::~DNSCtx()
{
    if (_dns_callback)
    {
        fix_error();
        _dns_callback(this);
    }
}

bool DNSCtx::all_resp_received() const
{
    return this->stat.ip4.all_resp_received() && this->stat.ip6.all_resp_received();
}

void DNSCtx::check_ip_list()
{
    if (_ip_list.empty())
    {
        if (!this->list.ip4.empty())
        {
            _ip_list = std::move(this->list.ip4);
        }

        if (!this->list.ip6.empty())
        {
            _ip_list = std::move(this->list.ip6);
        }
    }
}

void DNSCtx::fix_error()
{
    if (_ip_list.empty())
    {
        if (NetlibError_None == _dns_error)
        {
            _dns_error = NetlibError_Dns_Error;
        }
    }
    else
    {
        _dns_error = NetlibError_None;
    }
}

DNSClient::DNSClient(const DNSConfig& config)
    : _config(config)
    , _domain_cache{ HostCache(config.cache_limit_size), HostCache(config.cache_limit_size) }
{
}

int DNSClient::init()
{
    _module = create_platform_module(1, "dns_client");
    if (!_module)
    {
        FATAL_LOG("dns client create_platform_module failed");
        return -1;
    }

    if (!_module->attach_module(0, [] {}, thread_entry, nullptr))
    {
        FATAL_LOG("dns client attach_module failed");
        return -1;
    }

    if (!_module->run_module())
    {
        FATAL_LOG("dns client run_module failed");
        return -1;
    }

    do_load_name_server_conf();
    do_load_hosts_conf();

    _session.reset(new UdpSession(this));
    if (_config.use_ip4)
    {
        _udp_handle.ip4 = create_net_handle(AF_INET);
    }
    if (_config.use_ip6)
    {
        _udp_handle.ip6 = create_net_handle(AF_INET6);
    }

    if (INVALID_NET_HANDLE == _udp_handle.ip4 && INVALID_NET_HANDLE == _udp_handle.ip6)
    {
        FATAL_LOG("create dns udp socket failed, port:%" PRIu16, _config.local_port);
        return -1;
    }

    FLOW_LOG(
        "create dns port sucessfully!port:%" PRIu16 ", udp_handle:%" PRIu64 ",udp6_handle:%" PRIu64,
        _config.local_port,
        _udp_handle.ip4,
        _udp_handle.ip6
    );

    return 0;
}

NetHandle DNSClient::create_net_handle(uint16_t net_family)
{
    if (net_family != AF_INET && net_family != AF_INET)
    {
        return INVALID_NET_HANDLE;
    }
    SessionData sessiondata;
    sessiondata.m_LocalPort = _config.local_port;
    sessiondata.m_family = net_family;
    return NetFactory::GetInstance()->CreateUdpConnection(_session.get(), sessiondata);
}

int32_t DNSClient::resolve(const std::string& domain_name,
                           dns_callback dc,
                           void* user_data,
                           const DNSResolveConfig& config)
{
    int32_t ret = create_ctx(domain_name, dc, user_data, config);
    if (ret < 0)
    {
        return ret;
    }

    uint16_t dns_id = static_cast<uint16_t>(ret);
    bool ok = post_task([dns_id](DNSClient& client) {
        client.do_resolve(static_cast<uint16_t>(dns_id));
    });

    if (ok)
    {
        return ret;
    }

    WARNING_LOG("dns resolve failed,post task err,dns_id=%" PRIu16, dns_id);
    auto ctx = remove_ctx(dns_id);
    if (ctx)
    {
        ctx->_dns_callback = nullptr;
    }

    return -1;
}

void DNSClient::cancel(uint16_t dns_id)
{
    auto ctx = remove_ctx(dns_id);
    if (ctx)
    {
        ctx->_dns_error = NetlibError_Dns_Close;
    }
}

void DNSClient::load_name_server_conf()
{
    post_task([](DNSClient& client) {
        client.do_load_name_server_conf();
    });
}

void DNSClient::load_hosts_conf()
{
    post_task([](DNSClient& client) {
        client.do_load_hosts_conf();
    });
}

bool DNSClient::add_name_server(const std::string& ip)
{
    return post_task([ip](DNSClient& client) {
        client.do_add_name_server(ip);
    });
}

void DNSClient::add_local_host(const std::string&ip, const std::string& domain_name)
{
    post_task([ip, domain_name](DNSClient& client) {
        client.do_add_local_host(ip, domain_name);
    });
}

void DNSClient::using_syshost(bool use)
{
    post_task([use](DNSClient& client) {
        client.do_using_syshost(use);
    });
}

void DNSClient::using_cache(bool use)
{
    post_task([use](DNSClient& client) {
        client.do_using_cache(use);
    });
}

void DNSClient::set_timeout(uint32_t timeout)
{
    post_task([timeout](DNSClient& client) {
        client.do_set_timeout(timeout);
    });
}
int DNSClient::ip_stack() const
{
    return _ip_stack_checker.ip_stack;
}

bool DNSClient::post_task(DNSTask task)
{
    return _module->post_module_message(
        0,
        NetMsg_Custom,
        reinterpret_cast<uint64_t>(this),
        reinterpret_cast<uint64_t>(new DNSTask(std::move(task))),
        nullptr,
        0
    );
}

int DNSClient::post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size)
{
    if (!_module)
    {
        return -1;
    }

    auto ok = _module->post_module_message(0, msg_id, reinterpret_cast<uint64_t>(this), param, data, size);
    if (!ok)
    {
        FATAL_LOG("dns client post_module_message failed");
    }

    return 0;
}

// static
uint32_t DNSClient::thread_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pNetThreadData)
{
    auto client = reinterpret_cast<DNSClient *>(sender);

    switch (msg_id)
    {
    case NetMsg_UdpData:
    {
        FreeUniquePtr<UdpData> udp_data(reinterpret_cast<UdpData*>(param));
        client->process_dns_response(udp_data.get());
        break;
    }
    case NetMsg_Session_Release:
    {
        auto sit = reinterpret_cast<const session_info_t*>(msg);
        FLOW_LOG("dns client release, local[%s:%u], peer[%s:%u], h: %" PRIu64 "",
            sit->local_ip, sit->local_port, sit->peer_ip, sit->peer_port, param);
        client->process_session_release();
        break;
    }
    case NetMsg_Custom:
    {
        std::unique_ptr<DNSTask> task(reinterpret_cast<DNSTask *>(param));
        (*task)(*client);
        break;
    }
    }

    return 0;
}

//static
int32_t DNSClient::timer_entry(platform_timer_t, void* timer_self, void* timer_param)
{
    std::unique_ptr<TimerParam> tp(reinterpret_cast<TimerParam *>(timer_param));
    uint16_t dns_id = tp->dns_id;
    tp->client->post_task([dns_id] (DNSClient& client) {
        client.process_dns_timeout(dns_id);
    });

    return -1;
}

void DNSClient::do_resolve(uint16_t dns_id)
{
    auto ctx = resolve_ctx(dns_id);
    if (!ctx)
    {
        std::unique_ptr<TimerParam> tp(new TimerParam);
        tp->client = this;
        tp->dns_id = dns_id;

        auto timer = platform_create_timer(_config.timeout, timer_entry, nullptr, tp.get());
        if (INVALID_TIMER_ID != timer)
        {
            tp.release();
            return;
        }

        FATAL_LOG("dns client create timer failed,dns_id:%" PRIu16, dns_id);

        ctx = remove_ctx(dns_id);
    }

    if (ctx)
    {
        finish_dns_result(*ctx, ctx->_dns_error);
    }
}

void DNSClient::do_load_name_server_conf()
{
    _name_servers = _user_name_servers;

#if !defined(__ANDROID__) && !defined(__APPLE__)
    DNSUtil::parse_sys_name_server(_name_servers);
#endif

    // add default name servers if empty
    if (_name_servers.ip4.empty())
    {
        _name_servers.add("119.29.29.29");
        //_name_servers.add("114.114.114.114");//deprecated
        _name_servers.add("223.5.5.5");
    }

    if (_name_servers.ip6.empty())
    {
        // ali
        _name_servers.add("2400:3200::1");
        _name_servers.add("2400:3200:baba::1");

        // Yeti DNS Project 
        _name_servers.add("240C::6666");
        _name_servers.add("240C::6644");
    }
}

void DNSClient::do_load_hosts_conf()
{
    _domain_syshost_map.clear();

#if !defined(__ANDROID__) && !defined(__APPLE__)
    DNSUtil::parse_sys_hosts_file(_domain_syshost_map, !_config.use_ip6);
#endif
}

bool DNSClient::do_add_name_server(const std::string& ip)
{
#if defined(__ANDROID__) || defined(__APPLE__)
    if (_user_name_servers.empty())
    {
        _name_servers.clear();
    }
#endif

    return _name_servers.add(ip, true) && _user_name_servers.add(ip, true);
}

void DNSClient::do_add_local_host(const std::string&ip, const std::string& domain_name)
{
    _domain_userspec_map[domain_name].push_back(ip);
}

void DNSClient::do_using_syshost(bool use)
{
    _config.using_syshost = use;
}

void DNSClient::do_using_cache(bool use)
{
    _config.using_dnscache = use;
}

void DNSClient::do_set_timeout(uint32_t timeout)
{
    _config.timeout = timeout;
}

bool DNSClient::resolve_domain(uint16_t dns_id, DNSCtx& ctx)
{
    if (get_userspec_host_ip(ctx._domain_name, ctx._ip_list))
    {
        return true;
    }

    if (ctx.config.using_syshost && get_syshost_host_ip(ctx._domain_name, ctx._ip_list))
    {
        return true;
    }

    if (!ctx.ip_stack_checker)
    {
        ctx.ip_stack_checker = &_ip_stack_checker;
    }

    if (ctx.config.using_dnscache)
    {
        auto result = get_dns_from_cache(ctx.ip_stack_checker->ip_stack, ctx._domain_name);
        if (result && result->copy_to(ctx.start_ms, ctx._ip_list))
        {
            return true;
        }
    }

    ctx._dns_error = process_dns_request(dns_id, ctx);

    return NetlibError_None != ctx._dns_error;
}

int32_t DNSClient::process_dns_request(uint16_t dns_id, DNSCtx& ctx)
{
    auto ip_stack_checker = ctx.ip_stack_checker;
    if(_config.use_ip4
        && (!ip_stack_checker || AF_INET6 != ip_stack_checker->ip_stack))
    {
        send_ip4_request(dns_id, ctx.config.ip4_req_policy, ctx);
    }

    if(_config.use_ip6
        && (!ip_stack_checker || AF_INET != ip_stack_checker->ip_stack))
    {
        send_ip6_request(dns_id, ctx.config.ip6_req_policy, ctx);
    }

    if (0 == ctx.stat.ip4.query_cnt && 0 == ctx.stat.ip6.query_cnt)
    {
        WARNING_LOG("send dns request failed, dns_id:%d", dns_id);
        return NetlibError_Dns_Error;
    }

    return NetlibError_None;
}

DNSSendResult DNSClient::send_request(uint16_t id,
                             const std::string& domain_name,
                             uint16_t qtype,
                             NetHandle hnet,
                             const PriorityNameServers& name_servers,
                             uint16_t dport,
                             DNSStat& stat)
{
    std::string content;
    if (!DNSUtil::build_dns_request(id, domain_name, qtype, content))
    {
        return DNS_BUILD_FAILED;
    }

    SndData param;
    param._dst_port = dport;

    for (int i = 0; i < _config.req_once_cnt; i++)
    {
        for (auto&& ns : name_servers)
        {
            ns.addr.to_send_data(param);

            const uint8_t* data = (const uint8_t*)content.c_str();
            int32_t ret = NetFactory::GetInstance()->SendData(
                hnet,
                reinterpret_cast<const uint8_t*>(data),
                static_cast<uint32_t>(content.size()),
                &param
            );

            if (ret != 0)
            {
                char buf[INET_ADDRSTRLEN];
                WARNING_LOG(
                    "fail to send dns message,ip:%s,ret:%d,errno: %u",
                    ns.addr.to_string(buf),
                    ret,
                    errno);
                if (ret == NetlibError_HandleError)
                {
                    return DNS_HANDLE_ERROR;
                }
            }
            else
            {
                stat.query_cnt++;
            }
        }
    }

    return DNS_SEND_SUCCESSFUL;
}

DNSSendResult DNSClient::send_request(uint16_t id,
                             const std::string& domain_name,
                             DNSReqPolicy req_policy,
                             NetHandle hnet,
                             const PriorityNameServers& name_servers,
                             uint16_t dport,
                             DNSStat& stat)
{
    DNSSendResult ret1 = DNS_SEND_SUCCESSFUL;
    DNSSendResult ret2 = DNS_SEND_SUCCESSFUL;

    if (is_A_qtype_request(req_policy))
    {
        ret1 = send_request(id, domain_name, TYPE_A, hnet, name_servers, dport, stat);
    }

    if (is_AAAA_qtype_request(req_policy))
    {
        ret2 = send_request(id, domain_name, TYPE_AAAA, hnet, name_servers, dport, stat);
    }

    return (ret1 != DNS_SEND_SUCCESSFUL) ? ret1 : ret2;
}

bool DNSClient::send_ip4_request(uint16_t id, DNSReqPolicy req_policy, DNSCtx& ctx)
{
    if (_udp_handle.ip4 == INVALID_NET_HANDLE)
    {
        _udp_handle.ip4 = create_net_handle(AF_INET);
    }
    auto rv = send_request(
        id,
        ctx._domain_name,
        req_policy,
        _udp_handle.ip4,
        _name_servers.ip4,
        _config.server_port,
        ctx.stat.ip4
    );
    if (rv == DNS_HANDLE_ERROR)
    {
        NetFactory::GetInstance()->CloseNetHandle(_udp_handle.ip4);
        _udp_handle.ip4 = INVALID_NET_HANDLE;
    }
    return (rv == DNS_SEND_SUCCESSFUL);
}

bool DNSClient::send_ip6_request(uint16_t id, DNSReqPolicy req_policy, DNSCtx& ctx)
{
    if (_udp_handle.ip6 == INVALID_NET_HANDLE)
    {
        _udp_handle.ip6 = create_net_handle(AF_INET6);
    }
    auto rv = send_request(
        id,
        ctx._domain_name,
        req_policy,
        _udp_handle.ip6,
        _name_servers.ip6,
        _config.server_port,
        ctx.stat.ip6
    );
    if (rv == DNS_HANDLE_ERROR)
    {
        NetFactory::GetInstance()->CloseNetHandle(_udp_handle.ip6);
        _udp_handle.ip6 = INVALID_NET_HANDLE;
    }
    return (rv == DNS_SEND_SUCCESSFUL);
}

int32_t DNSClient::process_dns_response(const UdpData* udp_data)
{
    dy_network::IPAddress peer_addr;
    if (!peer_addr.from_udp_data(*udp_data))
    {
        WARNING_LOG("dns client recv response with bad addr");
        return -1;
    }

    char ipstr[INET6_ADDRSTRLEN];
    auto ns = _name_servers.find(peer_addr);
    if (!ns)
    {
        WARNING_LOG(
            "dns client recv response ns not found,ns:%s",
            peer_addr.to_string(ipstr)
        );
        return -1;
    }

    uint16_t dns_id = 0;
    std::string qname;
    std::vector<DNSAnswer> answers;
    int ret = DNSUtil::parse_dns_response(
        reinterpret_cast<const uint8_t *>(udp_data->_data),
        udp_data->_size,
        dns_id,
        qname,
        answers
    );

    if (0 != ret)
    {
        TRACE_LOG(
            "parse dns response failed"
            ",msg_size=%" PRIu32
            ",dns_id=%" PRIu16
            ",qname=%s"
            ",ns=%s",
            udp_data->_size,
            dns_id,
            qname.c_str(),
            peer_addr.to_string(ipstr)
        );
    }

    DNSResult result;
    result.qname = std::move(qname);
    result.now_ms = get_tick_count();
    result.error = ret;
    result.priority = ns->priority;
    result.dns_id = dns_id;
    result.is_ip6_msg = udp_data->is_ip6();
    result.from_answers(answers);

    return process_dns_result(std::move(result));
}

int32_t DNSClient::process_dns_result(DNSResult result)
{
    auto ctx = update_ctx(result);
    if (ctx)
    {
        finish_dns_result(*ctx, result.error);
    }

    if (0 == result.error && !result.list.empty())
    {
        update_dns_cache(std::move(result));
    }

    _ip_stack_checker.set_ready(result.is_ip6_msg);

    return 0;
}

void DNSClient::finish_dns_result(DNSCtx& ctx, int dns_error)
{
    if (ctx._ip_list.empty() && ctx.config.using_dnscache)
    {
        int ip_stack = ctx.ip_stack_checker->ip_stack;
        if (AF_UNSPEC == ip_stack)
        {
            ip_stack = _config.ip_stack_affinity;
        }

        get_dns_from_cache(ip_stack, ctx._domain_name, ctx._ip_list);

        ctx.check_ip_list();

        if (ctx._ip_list.empty())
        {
            ip_stack = ip_stack_get_other(ip_stack);
            get_dns_from_cache(ip_stack, ctx._domain_name, ctx._ip_list);
        }
    }

    ctx._dns_error = dns_error;
}

void DNSClient::process_dns_timeout(uint16_t dns_id)
{
    auto ctx = remove_ctx(dns_id);
    if (ctx)
    {
        auto ip_stack_checker = ctx->ip_stack_checker;
        if (ip_stack_checker)
        {
            ip_stack_checker->on_timeout(_config.ip_stack_affinity, !ctx->list.empty());
            auto ip_list = ctx->list.get(ip_stack_checker->ip_stack);
            if (ip_list && !ip_list->empty())
            {
                ctx->_ip_list = std::move(*ip_list);
            }
        }

        finish_dns_result(*ctx, NetlibError_Dns_Timeout);
    }
}

void DNSClient::process_session_release()
{
}

int32_t DNSClient::create_ctx(const std::string& domain_name,
                              dns_callback dc,
                              void* user_data,
                              const DNSResolveConfig& config)
{
    if (domain_name.empty() || !dc)
    {
        WARNING_LOG("bad dns request params domain:%s", domain_name.c_str());
        return -1;
    }

    std::unique_ptr<DNSCtx> ctx(new DNSCtx);
    ctx->_domain_name = domain_name;
    ctx->_dns_callback = dc;
    ctx->_user_data = user_data;
    ctx->config = config;

    ScopedLock<PlatformMutex> guard(_mutex);
    uint16_t dns_id = _dns_id_generator++;
    if (!_dns_map.emplace(dns_id, std::move(ctx)).second)
    {
        WARNING_LOG("dns id exists %" PRIu16 ",domain:%s", dns_id, domain_name.c_str());
        return -1;
    }

    return dns_id;
}

std::unique_ptr<DNSCtx>
DNSClient::resolve_ctx(uint16_t dns_id)
{
    ScopedLock<PlatformMutex> guard(_mutex);
    auto it = _dns_map.find(dns_id);
    if (_dns_map.end() == it)
    {
        return nullptr;
    }

    auto p = it->second.get();
    p->start_ms = get_tick_count();

    if (!resolve_domain(dns_id, *p))
    {
        return nullptr;
    }

    auto ctx = std::move(it->second);
    _dns_map.erase(it);

    return ctx;
}

std::unique_ptr<DNSCtx>
DNSClient::update_ctx(const DNSResult& result)
{
    ScopedLock<PlatformMutex> guard(_mutex);
    auto it = _dns_map.find(result.dns_id);
    if (it == _dns_map.end())
    {
        return nullptr;
    }

    auto ctx = it->second.get();
    if (!result.list.ip4.empty())
    {
        ctx->list.ip4 = result.list.ip4;
    }

    if (!result.list.ip6.empty())
    {
        ctx->list.ip6 = result.list.ip6;
    }

    auto ip_stack_checker = ctx->ip_stack_checker;
    if (ip_stack_checker)
    {
        ip_stack_checker->on_response(_config.ip_stack_affinity, result.is_ip6_msg);
        auto ip_list = ctx->list.get(ip_stack_checker->ip_stack);
        if (ip_list && !ip_list->empty())
        {
            ctx->_ip_list = std::move(*ip_list);
        }
    }

    if (result.is_ip6_msg)
    {
        ctx->stat.ip6.resp_cnt++;
    }
    else
    {
        ctx->stat.ip4.resp_cnt++;
    }

    if (ctx->_ip_list.empty() && !ctx->all_resp_received())
    {
        return nullptr;
    }

    auto moved_ctx = std::move(it->second);
    _dns_map.erase(it);

    return moved_ctx;
}


std::unique_ptr<DNSCtx>
DNSClient::remove_ctx(uint16_t dns_id)
{
    ScopedLock<PlatformMutex> guard(_mutex);
    auto it = _dns_map.find(dns_id);
    if (it == _dns_map.end())
    {
        return nullptr;
    }

    auto ctx = std::move(it->second);
    _dns_map.erase(it);

    return ctx;
}

void DNSClient::update_dns_cache(DNSResult result)
{
    auto update_pred = [&](const HostCacheEntry& entry) {
        return result.priority >= entry.priority
            || result.now_ms >= entry.deadline_ms;
    };

    HostCacheEntry new_entry;
    new_entry.priority = result.priority;
    new_entry.deadline_ms = result.now_ms + result.ttl * 1000ULL;

    if (!result.list.ip4.empty())
    {
        new_entry.ip_list = std::move(result.list.ip4);
        _domain_cache.ip4.put(result.qname, std::move(new_entry), update_pred);
    }

    if (!result.list.ip6.empty())
    {
        new_entry.ip_list = std::move(result.list.ip6);
        _domain_cache.ip6.put(result.qname, std::move(new_entry), update_pred);
    }
}

const HostCacheEntry *
DNSClient::get_dns_from_cache(int ip_stack, const std::string& domain_name) const
{
    if (!_config.using_dnscache)
    {
        return nullptr;
    }

    auto cache = _domain_cache.get(ip_stack);
    if (!cache)
    {
        return nullptr;
    }

    return cache->get(domain_name);
}

bool DNSClient::get_dns_from_cache(int ip_stack,
                                   const std::string& domain_name,
                                   std::vector<std::string>& ip_list) const
{
    auto result = get_dns_from_cache(ip_stack, domain_name);
    if (!result)
    {
        return false;
    }

    result->copy_to(ip_list);

    return true;
}

bool DNSClient::get_userspec_host_ip(const std::string& domain_name, std::vector<std::string>& ip_list) const
{
    auto it = _domain_userspec_map.find(domain_name);
    if (it == _domain_userspec_map.end())
    {
        return false;
    }

    ip_list = it->second;

    return true;
}

bool DNSClient::get_syshost_host_ip(const std::string& domain_name, std::vector<std::string>& ip_list) const
{
    if (!_config.using_syshost)
    {
        return false;
    }

    auto it = _domain_syshost_map.find(domain_name);
    if (it == _domain_syshost_map.end())
    {
        return false;
    }

    ip_list = it->second;

    return true;
}
}
