#include "dy_dns.h"
#include "platform_log.h"
#include "utility/dns_client.h"

dy_network::DNSClient *g_dns_client = nullptr;

int32_t dns_init(const DNSConfig& config)
{
    if (g_dns_client)
    {
        return 0;
    }

    g_dns_client = new dy_network::DNSClient(config);
    return g_dns_client->init();
}

DnsHandle dns_resolve(const std::string& domain_name,
                      dns_callback dc,
                      void* user_data,
                      const DNSResolveConfig& config)
{
    return g_dns_client->resolve(domain_name, dc, user_data, config);
}

void dns_close(DnsHandle dh)
{
    uint16_t dns_id = (uint16_t)(dh & 0xffff);
    g_dns_client->cancel(dns_id);
}

bool dns_set_timeout(uint32_t timeout)
{
    if ((timeout <= 100) || (timeout >= 60000))
    {
        return false;
    }

    if (!g_dns_client)
    {
        return false;
    }

    g_dns_client->set_timeout(timeout);

    return true;
}

bool dns_use_syshost(bool enabled)
{
    if (!g_dns_client)
    {
        return false;
    }

    g_dns_client->using_syshost(enabled);

    return true;
}

bool dns_use_cache(bool enabled)
{
    if (!g_dns_client)
    {
        return false;
    }

    g_dns_client->using_cache(enabled);

    return true;
}

bool dns_add_name_server(const std::string& ns)
{
    return g_dns_client && g_dns_client->add_name_server(ns);
}

bool dns_add_local_host(const std::string& ip, const std::string& domain_name)
{
    if (!g_dns_client)
    {
        return false;
    }

    g_dns_client->add_local_host(ip, domain_name);

    return true;
}

bool dns_load_name_server_conf()
{
    if (!g_dns_client)
    {
        return false;
    }

    g_dns_client->load_name_server_conf();

    return true;
}

bool dns_load_hosts_conf()
{
    if (!g_dns_client)
    {
        return false;
    }

    g_dns_client->load_hosts_conf();

    return true;
}

int dns_get_ip_stack()
{
    return g_dns_client ? g_dns_client->ip_stack() : AF_UNSPEC;
}

DnsHandle dns_resolve(const std::string& domain_name, dns_callback dc, void* user_data)
{
    return dns_resolve(domain_name, dc, user_data, {});
}

void dy_dns_parse_timeout(uint32_t tmo_in_ms)
{
    dns_set_timeout(tmo_in_ms);
}

void dy_dns_using_syshost(bool use)
{
    NOTICE_LOG("config using_syshost as dns result:%s", use ? "true" : "false");
    dns_use_syshost(use);
}

void dy_dns_using_cache(bool use)
{
    NOTICE_LOG("config using_cache as :%s", use ? "true" : "false");
    dns_use_cache(use);
}

bool add_dns_server_ip(const std::string& dns_ip)
{
    return dns_add_name_server(dns_ip);
}

bool add_local_host(const std::string& ip, const std::string& domain_name)
{
    return dns_add_local_host(ip, domain_name);
}
