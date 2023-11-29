#include "utility/dns_utils.h"

#include <algorithm>

#include "platform_log.h"
#include "netlib_error.h"
#include "platform_file.h"
#include "url.h"

namespace dy_network
{
bool PriorityNameServers::add(const dy_network::IPAddress& ns, bool front)
{
    auto server = find(ns);
    int priority = calc_priority(front);
    if (server)
    {
        server->priority = priority;
    }
    else
    {
        push_back({ ns, priority });
    }

    char ip[INET6_ADDRSTRLEN];
    FLOW_LOG("dns add name server '%s' priority:%d", ns.to_string(ip), priority);

    sort();

    return true;
}

const NameServer *PriorityNameServers::find(const dy_network::IPAddress& ns) const
{
    return const_cast<PriorityNameServers *>(this)->find(ns);
}

NameServer *PriorityNameServers::find(const dy_network::IPAddress& ns)
{
    auto it = std::find_if(begin(), end(), [&ns](const NameServer& server) {
        return server.addr == ns;
    });

    return end() == it ? nullptr : &(*it);
}

void PriorityNameServers::sort()
{
    std::sort(
        begin(),
        end(),
        [](const NameServer& a, const NameServer& b) {
            return a.priority > b.priority;
        }
    );
}

int PriorityNameServers::calc_priority(bool add_front) const
{
    if (empty())
    {
        return 0;
    }

    if (add_front)
    {
        return front().priority + 1;
    }

    return back().priority - 1;
}

bool NameServers::empty() const
{
    return this->ip4.empty() && this->ip6.empty();
}

void NameServers::clear()
{
    this->ip4.clear();
    this->ip6.clear();
}

bool NameServers::add(const dy_network::IPAddress& ns, bool add_front)
{
    if (ns.is_nil() || ns.is_any() || (ns.is_v6() && ns.is_site_local()))
    {
        return false;
    }

    return get(ns.family())->add(ns, add_front);
}

bool NameServers::add(const std::string& ip, bool add_front)
{
    dy_network::IPAddress ns;
    return ns.from_string(ip.c_str()) && add(std::move(ns), add_front);
}

const NameServer *NameServers::find(const dy_network::IPAddress& ns) const
{
    return get(ns.family())->find(ns);
}

// static
bool DNSUtil::build_dns_request(uint16_t id,
                                const std::string& domain_name,
                                uint16_t qtype,
                                std::string& content)
{
    DNSRequestPrefix drp;
    memset(&drp, 0, sizeof(drp));
    drp._ident_hi = id >> 8;
    drp._ident_lo = (id & 0xff);
    drp._flags[0] = 1;
    drp._flags[1] = 0;
    drp._nqs[1] = 1;

    content.append((char*)&drp, sizeof(drp));

    size_t i = 0;
    size_t last = i;
    while (i < domain_name.size())
    {
        if (domain_name[i] == '.')
        {
            size_t dot_length = i - last;
            if (dot_length == 0 || dot_length >= 128)
            {
                WARNING_LOG("domain name error:%s", domain_name.c_str());
                return false;
            }

            content.push_back((uint8_t)dot_length);
            content.append(domain_name.c_str() + last, dot_length);
            last = i + 1;
        }
        i++;
    }

    if (i > last)
    {
        size_t dot_length = i - last;
        if (dot_length == 0 || dot_length >= 128)
        {
            WARNING_LOG("domain name error:%s", domain_name.c_str());
            return false;
        }
        content.push_back((uint8_t)dot_length);
        content.append(domain_name.c_str() + last, dot_length);
    }
    content.push_back(0);

    DNSRequestSuffix drs;
    drs._typ[0] = static_cast<uint8_t>((qtype >> 8));
    drs._typ[1] = static_cast<uint8_t>(qtype & 0XFF);
    drs._class[0] = 0;
    drs._class[1] = 1;
    content.append((char*)&drs, sizeof(drs));

    return true;
}

// static
int32_t DNSUtil::parse_query_name(const uint8_t* data,
                                  uint32_t start_pos,
                                  uint32_t end_pos,
                                  std::string& domain_name)
{
    domain_name.clear();

    int32_t nptrs = 0;
    uint32_t pos = start_pos;
    uint32_t p = pos;
    while (nptrs < 128)
    {
        if (p >= end_pos)
        {
            return -1;
        }
        uint8_t fst = data[p];
        if (0 == fst)
        {
            if (0 == nptrs)
            {
                pos++;
            }
            break;
        }

        if ((fst & 0xc0) != 0)
        {
            if (0 == nptrs)
            {
                pos += 2;
            }
            nptrs++;
            if ((p + 1) >= end_pos)
            {
                return -2;
            }
            uint8_t snd = data[p + 1];
            p = ((uint16_t)(fst & 0x3f) << 8) + snd;
        }
        else
        {
            if (!domain_name.empty())
            {
                domain_name.push_back('.');
            }
            if ((p + 1 + fst) > end_pos)
            {
                return -3;
            }
            domain_name.append((const char*)(data + p + 1), fst);
            p += 1 + fst;
            if (0 == nptrs)
            {
                pos = p;
            }
        }
    }

    return pos;
}

int32_t DNSUtil::parse_dns_section(uint32_t section,
                                    const uint8_t* data,
                                    uint32_t start_pos,
                                    uint32_t end_pos,
                                    uint32_t answer_size,
                                    std::vector<DNSAnswer>& answers,
                                    bool should_skip)
{
    DNSAnswer answer;

    uint32_t pos = start_pos;
    for (uint32_t i = 0; i < answer_size; i++)
    {
        int32_t ret = parse_query_name(data, pos, end_pos, answer._answer_name);
        if (ret <= 0)
        {
            return NetlibError_Dns_Error;
        }
        pos = ret;
        if ((pos + 10) > end_pos)
        {
            WARNING_LOG("dns response is too small:%d", end_pos);
            return NetlibError_BufferOver;
        }


        uint8_t type_hi = data[pos];
        uint8_t type_lo = data[pos + 1];
        answer._type = (uint16_t)type_hi | type_lo;

        uint8_t class_hi = data[pos + 2];
        uint8_t class_lo = data[pos + 3];
        answer._class = (uint16_t)class_hi | class_lo;

        answer._ttl = (uint32_t)data[pos + 4] << 24 | (uint32_t)data[pos + 5] << 14 | (uint32_t)data[pos + 6] << 14 | (uint32_t)data[pos + 7];

        answer._data_length = (uint16_t)data[pos + 8] | data[pos + 9];
        pos += 10;

        if (answer._type == TYPE_A)
        {
            if (answer._data_length != 4)
            {
                WARNING_LOG("bad A record value length:%d", answer._data_length);
                return NetlibError_Dns_Error;
            }
            if ((pos + 4) > end_pos)
            {
                WARNING_LOG("A record value length:%d bufferOver", answer._data_length);
                return NetlibError_BufferOver;
            }

            in_addr ip4;
            memcpy(&ip4, data + pos, 4);
            dy_network::ipaddr_to_string(AF_INET, &ip4, answer._data);

            pos += 4;
        }
        else if (answer._type == TYPE_CNAME)
        {
            ret = parse_query_name(data, pos, end_pos, answer._data);
            if (ret <= 0)
            {
                WARNING_LOG("fail to parse cname, ret:%d", ret);
                return NetlibError_Dns_Error;
            }
            pos = ret;
        }
        else if (answer._type == TYPE_AAAA)
        {
            if (answer._data_length != 16)
            {
                WARNING_LOG("bad AAAA record value length:%d", answer._data_length);
                return NetlibError_Dns_Error;
            }
            if ((pos + 16) > end_pos)
            {
                WARNING_LOG("AAAA record value length:%d bufferOver", answer._data_length);
                return NetlibError_BufferOver;
            }

            in6_addr ip6;
            memcpy(&ip6, data + pos, 16);
            dy_network::ipaddr_to_string(AF_INET6, &ip6, answer._data);

            pos += 16;
        }
        else
        {
            continue;
        }

        answers.push_back(answer);
    }

    return 0;
}

int32_t DNSUtil::parse_dns_response(const uint8_t *data,
                                    uint32_t size,
                                    uint16_t& dns_id,
                                    std::string& qname,
                                    std::vector<DNSAnswer>& answers)
{
    if (size < 12)
    {
        return NetlibError_Dns_Error;
    }

    uint8_t ident_hi = data[0];
    uint8_t ident_lo = data[1];

    dns_id = (uint16_t)ident_hi << 8 | ident_lo;

    uint8_t flags_hi = data[2];
    uint8_t flags_lo = data[3];

    uint16_t flags = (uint16_t)flags_hi << 8 | flags_lo;


    if (0 == (flags & 0x8000))
    {
        TRACE_LOG("bad QR flag in the DNS response,flags:%d,size:%d", flags, size);
        return NetlibError_Dns_Error;
    }

    if ((flags & 0x200) != 0)
    {
        return NetlibError_Dns_Error;
    }

    uint16_t code = flags & 0xf;

    uint8_t nqs_hi = data[4];
    uint8_t nqs_lo = data[5];

    uint16_t nqs = (uint16_t)nqs_hi << 8 | nqs_lo;
    (void)nqs;

    uint8_t nan_hi = data[6];
    uint8_t nan_lo = data[7];

    uint16_t nan = (uint16_t)nan_hi << 8 | nan_lo;

    uint8_t nns_hi = data[8];
    uint8_t nns_lo = data[9];

    uint16_t nns = (uint16_t)nns_hi << 8 | nns_lo;
    (void)nns;

    uint8_t nar_hi = data[10];
    uint8_t nar_lo = data[11];

    uint16_t nar = (uint16_t)nar_hi << 8 | nar_lo;
    (void)nar;

    int32_t offset = parse_query_name(data, 12, size, qname);

    if (offset <= 0 || qname.empty())
    {
        return NetlibError_Dns_Error;
    }

    if ((uint32_t)offset + 4 + nan * 12 > size)
    {
        return NetlibError_Dns_Error;
    }

    // qtype
    offset += 2;

    uint8_t class_hi = data[offset];
    uint8_t class_lo = data[offset + 1];

    uint16_t qclass = (uint16_t)class_hi << 8 | class_lo;

    int ret = 0;
    if (qclass != 1)
    {
        TRACE_LOG("unknown query class %d in DNS response", qclass);
        ret = NetlibError_Dns_Error;
    }

    offset += 2;

    if (code != 0)
    {
        TRACE_LOG("dns code error:%d", code);
        ret = NetlibError_Dns_Error;
    }

    if (0 == ret)
    {
        ret = parse_dns_section(SECTION_AN, data, offset, size, nan, answers);

        if (ret < 0)
        {
            answers.clear();
        }
    }

    return ret;
}

// static
void DNSUtil::parse_line_tokens(const char* data, uint32_t size, std::vector<std::string>& string_list)
{
    uint32_t i = 0;
    std::string dummy;
    string_list.clear();
    uint32_t last = 0;
    for (i = 0; i < size; i++)
    {
        if (data[i] == ' ')
        {
            if (last == i)
            {
                last++;
            }
            else
            {
                dummy.assign(data + last, i - last);
                string_list.push_back(dummy);
                dummy.clear();
                last = i + 1;
            }
        }
        else if (data[i] == '#')
        {
            break;
        }
    }

    if (i > last)
    {
        dummy.assign(data + last, i - last);
        string_list.push_back(dummy);
    }
}

// static
std::string DNSUtil::get_default_hosts_filename()
{
#ifdef _WIN32
    char szPath[MAX_PATH] = { 0 };
    if (0 == GetSystemDirectoryA(szPath, MAX_PATH))
    {
        FATAL_LOG("GetSystemDirectoryA failed err:%" PRIu32, (uint32_t)::GetLastError());
        return "";
    }

    std::string filename = szPath;
    filename += "\\drivers\\etc\\hosts";

    return filename;
#else
    return "/etc/hosts";
#endif
}

// static
bool DNSUtil::parse_sys_hosts_file(HostMap& host_map, bool only_ipv4)
{
    std::string filename = get_default_hosts_filename();
    if (filename.empty())
    {
        return false;
    }

    std::string content;
    if (!get_file_content(filename.c_str(), content))
    {
        FATAL_LOG("get sys hosts file(%s) content failed", filename.c_str());
        return false;
    }

    if (content.empty())
    {
        WARNING_LOG("sys hosts file(%s) content is empty", filename.c_str());
        return false;
    }

    content += "\n";

    uint32_t last = 0;
    uint32_t i = 0;
    std::string dummy;
    std::vector<std::string> string_list;
    do
    {
        char c = content[i];
        if (c == '\r' || c == '\n')
        {
            if (content[last] == '#')
            {
                if (c == '\n')
                {
                    i++;
                }
                else
                {
                    if (i < content.size() - 1 && content[i + 1] == '\n')
                    {
                        i += 2;
                    }
                }
                last = i;
                continue;
            }
            dummy.clear();
            string_list.clear();
            if (i > last)
            {
                parse_line_tokens(content.c_str() + last, i - last, string_list);
            }

            if (string_list.size() > 1)
            {
                if (!only_ipv4 || util::is_ipv4(string_list[0]))
                {
                    for (uint32_t ix = 1; ix < string_list.size(); ix++)
                    {
                        host_map[string_list[ix]].push_back(string_list[0]);
                    }
                }
            }

            if (c == '\n')
            {
                last = i + 1;
            }
            else
            {
                if (i < content.size() - 1 && content[i + 1] == '\n')
                {
                    last = i + 2;;
                }
            }
        }
        i++;
    } while (i < content.size());

    return true;
}

// static
bool DNSUtil::parse_sys_name_server(NameServers& name_servers)
{
#ifndef _WIN32
    std::string content;
    std::string filename = "/etc/resolv.conf";
    get_file_content(filename.c_str(), content);
    if (content.empty())
    {
        return false;
    }
    content += "\n";

    int32_t last = 0;
    uint32_t i = 0;
    std::string dummy;
    std::vector<std::string> string_list;
    do
    {
        char c = content[i];
        if (c == '\r' || c == '\n')
        {
            if (content[last] == '#')
            {
                if (c == '\n')
                {
                    i++;
                }
                else
                {
                    if (i < content.size() - 1 && content[i + 1] == '\n')
                    {
                        i += 2;
                    }
                }
                last = i;
                continue;
            }

            string_list.clear();
            if (i > last)
            {
                parse_line_tokens(content.c_str() + last, i - last, string_list);
            }

            if (string_list.size() > 1)
            {
                if (string_list[0] == "nameserver")
                {
                    for (int j = 1; j < string_list.size(); j++)
                    {
                        name_servers.add(string_list.at(j));
                    }
                }
            }

            if (c == '\n')
            {
                last = i + 1;
            }
            else
            {
                if (i < content.size() - 1 && content[i + 1] == '\n')
                {
                    last = i + 2;;
                }
            }
        }
        i++;
    } while (i < content.size());

    return true;
#else
    if (get_ns_by_GetAdaptersAddresses(name_servers))
    {
        return true;
    }

    if (get_ns_by_GetNetworkParams(name_servers))
    {
        return true;
    }

    return false;
#endif
}

#ifdef _WIN32
// static
FreeUniquePtr<IP_ADAPTER_ADDRESSES>
DNSUtil::get_adapter_addresses(ULONG flags)
{
    FreeUniquePtr<IP_ADAPTER_ADDRESSES> out;
    ULONG len = 15000;  // As recommended by MSDN for GetAdaptersAddresses.
    UINT rv = ERROR_BUFFER_OVERFLOW;
    // Try up to three times.
    for (unsigned tries = 0; (tries < 3) && (rv == ERROR_BUFFER_OVERFLOW); tries++)
    {
        out.reset(static_cast<PIP_ADAPTER_ADDRESSES>(malloc(len)));
        memset(out.get(), 0, len);
        rv = ::GetAdaptersAddresses(AF_UNSPEC, flags, nullptr, out.get(), &len);
    }

    if (rv != NO_ERROR)
    {
        out.reset();
    }

    return out;
}

// static
bool DNSUtil::get_ns_by_GetAdaptersAddresses(NameServers& name_servers)
{
    auto adapter_addresses = get_adapter_addresses(GAA_FLAG_SKIP_MULTICAST);
    if (!adapter_addresses)
    {
        FATAL_LOG("GetAdapterAddresses failed err:%" PRIu32, ::GetLastError());
        return false;
    }

    dy_network::IPAddress ns;
    for (auto ipaa = adapter_addresses.get(); ipaa; ipaa = ipaa->Next)
    {
        if (ipaa->OperStatus != IfOperStatusUp)
        {
            continue;
        }

        for (auto dns_addr = ipaa->FirstDnsServerAddress; dns_addr; dns_addr = dns_addr->Next)
        {
            if (!ns.from_sockaddr(dns_addr->Address.lpSockaddr, dns_addr->Address.iSockaddrLength))
            {
                continue;
            }

            name_servers.add(ns);
        }
    }

    return true;
}

// static
bool DNSUtil::get_ns_by_GetNetworkParams(NameServers& name_servers)
{
    FIXED_INFO * FixedInfo;
    ULONG   ulOutBufLen = sizeof(FIXED_INFO);
    DWORD    dwRetVal = ERROR_SUCCESS;

    FixedInfo = (FIXED_INFO *)GlobalAlloc(GPTR, ulOutBufLen);
    if (FixedInfo == NULL)
    {
        FATAL_LOG("GlobalAlloc FixedInfo failed");
        return false;
    }

    if (ERROR_BUFFER_OVERFLOW == ::GetNetworkParams(FixedInfo, &ulOutBufLen))
    {
        GlobalFree(FixedInfo);
        FixedInfo = (FIXED_INFO *)GlobalAlloc(GPTR, ulOutBufLen);
    }

    if (FixedInfo == NULL)
    {
        FATAL_LOG("GlobalAlloc FixedInfo failed");
        return false;
    }

    if ((dwRetVal = ::GetNetworkParams(FixedInfo, &ulOutBufLen)) == ERROR_SUCCESS)
    {
        IP_ADDR_STRING *pIPAddr = &(FixedInfo->DnsServerList);
        while (pIPAddr)
        {
            name_servers.add(pIPAddr->IpAddress.String);
            pIPAddr = pIPAddr->Next;
        }
    }
    else
    {
        FATAL_LOG("Call to GetNetworkParams failed. Return Value: %08x\n", dwRetVal);
    }

    GlobalFree(FixedInfo);

    return true;
}

#endif
}
