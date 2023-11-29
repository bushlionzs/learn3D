#pragma once

#include <functional>
#include <memory>

#include "server_interface.h"
#include "platform_common.h"
#include "platform_mutex.h"
#include "scoped_lock.h"
#include "udp_session.h"
#include "platform_util.h"
#include "utility/dy_dns.h"
#include "utility/dns_utils.h"
#include "utility/lru_cache.h"

namespace dy_network
{

enum DNSSendResult : uint16_t
{
    DNS_SEND_SUCCESSFUL = 0,
    DNS_BUILD_FAILED = 1,
    DNS_HANDLE_ERROR = 2,
};
class DNSClient;

struct DNSIPList : IPStackPair<std::vector<std::string>>
{
    bool empty() const;
};

struct DNSResult
{
    std::string qname;
    DNSIPList list;
    uint64_t now_ms = 0;
    uint32_t ttl = 60 * 10;
    int error = 0;
    int priority = -1;
    uint16_t dns_id = 0;
    bool is_ip6_msg = false;

    void from_answers(const std::vector<DNSAnswer>& answers);
};

struct DNSStat
{
    uint32_t query_cnt = 0;
    uint32_t resp_cnt = 0;

    bool all_resp_received() const { return this->resp_cnt >= this->query_cnt; }
};

struct HostCacheEntry
{
    std::vector<std::string> ip_list;
    uint64_t deadline_ms = 0;
    mutable size_t start_index = 0;
    int priority = -1;

    bool copy_to(uint64_t now, std::vector<std::string>& result) const;
    void copy_to(std::vector<std::string>& result) const;
};

using HostCache = dy_network::LRUCache<std::string, HostCacheEntry>;

struct DNSCtx : dy_dns_t
{
    uint64_t start_ms = 0;
    DNSResolveConfig config;
    DNSIPList list;
    IPStackPair<DNSStat> stat;
    IPStackChecker *ip_stack_checker = nullptr;

    ~DNSCtx();
    bool all_resp_received() const;
    void check_ip_list();
    void fix_error();
};

class DNSClient : public IServerInterface
{
public:
    explicit DNSClient(const DNSConfig& config);

    int init();
    int32_t resolve(const std::string& domain_name,
                    dns_callback dc,
                    void* user_data,
                    const DNSResolveConfig& config);
    void cancel(uint16_t dns_id);
    void load_name_server_conf();
    void load_hosts_conf();
    bool add_name_server(const std::string& ip);
    void add_local_host(const std::string&ip, const std::string& domain_name);
    void using_syshost(bool use);
    void using_cache(bool use);
    void set_timeout(uint32_t timeout);
    int ip_stack() const;
private:
    using DNSTask = std::function<void(DNSClient&)>;
    bool post_task(DNSTask task);

    NetHandle create_net_handle(uint16_t net_family);
    virtual int post_network_message(uint32_t msg_id, uint64_t param, const uint8_t* data, uint32_t size) override;

    static uint32_t thread_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pNetThreadData);
    static int32_t timer_entry(platform_timer_t, void* timer_self, void* timer_param);

    void do_resolve(uint16_t dns_id);
    void do_load_name_server_conf();
    void do_load_hosts_conf();
    bool do_add_name_server(const std::string& ip);
    void do_add_local_host(const std::string&ip, const std::string& domain_name);
    void do_using_syshost(bool use);
    void do_using_cache(bool use);
    void do_set_timeout(uint32_t timeout);

    bool resolve_domain(uint16_t dns_id, DNSCtx& ctx);
    int32_t process_dns_request(uint16_t dns_id, DNSCtx& ctx);
    DNSSendResult send_request(uint16_t id,
                      const std::string& domain_name,
                      uint16_t qtype,
                      NetHandle hnet,
                      const PriorityNameServers& name_servers,
                      uint16_t dport,
                      DNSStat& stat);
    DNSSendResult send_request(uint16_t id,
                      const std::string& domain_name,
                      DNSReqPolicy req_policy,
                      NetHandle hnet,
                      const PriorityNameServers& name_servers,
                      uint16_t dport,
                      DNSStat& stat);

    bool send_ip4_request(uint16_t id, DNSReqPolicy req_policy, DNSCtx& ctx);
    bool send_ip6_request(uint16_t id, DNSReqPolicy req_policy, DNSCtx& ctx);

    int32_t process_dns_response(const UdpData* udp_data);
    int32_t process_dns_result(DNSResult result);
    void finish_dns_result(DNSCtx& ctx, int dns_error);

    void process_dns_timeout(uint16_t dns_id);
    void process_session_release();

    int32_t create_ctx(const std::string& domain_name,
                       dns_callback dc,
                       void* user_data,
                       const DNSResolveConfig& config);
    std::unique_ptr<DNSCtx> resolve_ctx(uint16_t dns_id);
    std::unique_ptr<DNSCtx> update_ctx(const DNSResult& result);
    std::unique_ptr<DNSCtx> remove_ctx(uint16_t dns_id);

    void update_dns_cache(DNSResult result);
    const HostCacheEntry *
    get_dns_from_cache(int ip_stack, const std::string& domain_name) const;
    bool get_dns_from_cache(int ip_stack,
                            const std::string& domain_name,
                            std::vector<std::string>& ip_list) const;

    bool get_userspec_host_ip(const std::string& domain_name, std::vector<std::string>& ip_list) const;
    bool get_syshost_host_ip(const std::string& domain_name, std::vector<std::string>& ip_list) const;

    DNSConfig _config;
    IPlatformModule *_module = nullptr;
    std::unique_ptr<UdpSession> _session;
    IPStackPair<NetHandle> _udp_handle = { INVALID_NET_HANDLE, INVALID_NET_HANDLE };
    std::unordered_map<uint16_t, std::unique_ptr<DNSCtx>> _dns_map;
    PlatformMutex _mutex;
    uint16_t _dns_id_generator = 0;
    IPStackChecker _ip_stack_checker;
    HostMap _domain_syshost_map;
    HostMap _domain_userspec_map;
    IPStackPair<HostCache> _domain_cache;
    NameServers _name_servers;
    NameServers _user_name_servers;
};
}

