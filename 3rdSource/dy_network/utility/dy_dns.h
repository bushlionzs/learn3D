#ifndef __DY_DNS_H__
#define __DY_DNS_H__

#include <stdint.h>
#include <string>
#include <vector>

#include "optional.h"

constexpr uint16_t DNS_DEFAULT_PORT = 53;

struct dy_dns_t;
using dns_callback = void(*)(dy_dns_t*);
using DnsHandle = int32_t;

struct dy_dns_t
{
    int32_t _dns_error = 0;
    std::string _domain_name;
    std::vector<std::string> _ip_list;
    void* _user_data = nullptr;
    DnsHandle _dns_handle = -1;
    dns_callback _dns_callback = nullptr;
};

enum DNSReqPolicy : uint8_t
{
    NONE,
    A,
    AAAA,
    BOTH
};

struct DNSConfig
{
    uint32_t timeout = 400;
    uint32_t cache_limit_size = 512;
    int ip_stack_affinity = -1;
    int req_once_cnt = 2;
    uint16_t local_port = 0;
    uint16_t server_port = DNS_DEFAULT_PORT;
    bool use_ip4 = true;
    bool use_ip6 = true;
    bool using_syshost = true;
    bool using_dnscache = true;
};

struct DNSResolveConfig
{
    optional<uint32_t> timeout;
    DNSReqPolicy ip4_req_policy = DNSReqPolicy::A;
    DNSReqPolicy ip6_req_policy = DNSReqPolicy::AAAA;
    bool using_syshost = true;
    bool using_dnscache = true;
};

int32_t dns_init(const DNSConfig& config);
DnsHandle dns_resolve(const std::string& domain_name,
                      dns_callback dc,
                      void* user_data,
                      const DNSResolveConfig& config);
void dns_close(DnsHandle dh);
bool dns_set_timeout(uint32_t timeout);
bool dns_use_syshost(bool enabled);
bool dns_use_cache(bool enabled);
bool dns_add_name_server(const std::string& ns);
bool dns_add_local_host(const std::string& ip, const std::string& domain_name);
bool dns_load_name_server_conf();
bool dns_load_hosts_conf();
int dns_get_ip_stack();

DnsHandle dns_resolve(const std::string& domain_name, dns_callback dc, void* user_data);
void dy_dns_parse_timeout(uint32_t tmo_in_ms);
void dy_dns_using_syshost(bool use);
void dy_dns_using_cache(bool use);
bool add_dns_server_ip(const std::string& dns_ip);
bool add_local_host(const std::string& ip, const std::string& domain_name);

#endif //__DY_DNS_H__