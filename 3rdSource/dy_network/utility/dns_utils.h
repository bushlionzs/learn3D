#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

#ifdef _WIN32
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#include <Iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")
#else
#include <arpa/inet.h>
#endif

#include "utility/ip_stack_checker.h"
#include "utility/ip_address.h"

namespace dy_network
{

enum DNSType : uint16_t
{
    TYPE_A = 1,
    TYPE_NS = 2,
    TYPE_CNAME = 5,
    TYPE_PTR = 12,
    TYPE_MX = 15,
    TYPE_TXT = 16,
    TYPE_AAAA = 28,
    TYPE_SRV = 33,
    TYPE_SPF = 99,
};

enum DNSSection : uint16_t
{
    SECTION_AN = 1,
    SECTION_NS = 2,
    SECTION_AR = 3,
};

#pragma pack(push, 1)
struct DNSRequestPrefix
{
    uint8_t _ident_hi;
    uint8_t _ident_lo;
    uint8_t _flags[2];
    uint8_t _nqs[2];
    uint8_t _nan[2];
    uint8_t _nns[2];
    uint8_t _nar[2];
};

struct DNSRequestSuffix
{
    uint8_t _typ[2];
    uint8_t _class[2];
};
#pragma pack(pop)

struct DNSAnswer
{
    std::string _answer_name;
    uint16_t _type;
    uint16_t _class;
    uint32_t _ttl;
    uint16_t _data_length;
    std::string _data;
};

struct NameServer
{
    dy_network::IPAddress addr;
    int priority;
};

class PriorityNameServers : public std::vector<NameServer>
{
public:
    bool add(const dy_network::IPAddress& ns, bool add_front = false);
    const NameServer *find(const dy_network::IPAddress& ns) const;
private:
    NameServer *find(const dy_network::IPAddress& ns);

    void sort();
    int calc_priority(bool add_front) const;
};

struct NameServers : IPStackPair<PriorityNameServers>
{
    bool empty() const;
    void clear();
    bool add(const dy_network::IPAddress& ns, bool add_front = false);
    bool add(const std::string& ip, bool add_front = false);
    const NameServer *find(const dy_network::IPAddress& ns) const;
};

struct FreeDeleter
{
    template<typename T>
    void operator()(const T* ptr)
    {
        free(const_cast<T *>(ptr));
    }
};

template<typename T>
using FreeUniquePtr = std::unique_ptr<T, FreeDeleter>;

using HostMap = std::unordered_map<std::string, std::vector<std::string>>;

struct DNSUtil
{
    static bool build_dns_request(uint16_t id,
                                  const std::string& domain_name,
                                  uint16_t qtype,
                                  std::string& content);

    static int32_t parse_query_name(const uint8_t* data,
                                    uint32_t start_pos,
                                    uint32_t end_pos,
                                    std::string& domain_name);

    static int32_t parse_dns_section(uint32_t section,
                                     const uint8_t* data,
                                     uint32_t start_pos,
                                     uint32_t end_pos,
                                     uint32_t answer_size,
                                     std::vector<DNSAnswer>& answers,
                                     bool should_skip = false);

    static int32_t parse_dns_response(const uint8_t *data,
                                      uint32_t size,
                                      uint16_t& dns_id,
                                      std::string& qname,
                                      std::vector<DNSAnswer>& answers);

    static void parse_line_tokens(const char* data, uint32_t size, std::vector<std::string>& string_list);

    static std::string get_default_hosts_filename();

    static bool parse_sys_hosts_file(HostMap& host_map, bool only_ipv4);

    static bool parse_sys_name_server(NameServers& name_servers);

#ifdef _WIN32
    static FreeUniquePtr<IP_ADAPTER_ADDRESSES> get_adapter_addresses(ULONG flags);

    static bool get_ns_by_GetAdaptersAddresses(NameServers& name_servers);

    // win32 api can only get ipv4 name servers ip
    static bool get_ns_by_GetNetworkParams(NameServers& name_servers);
#endif
};

}

