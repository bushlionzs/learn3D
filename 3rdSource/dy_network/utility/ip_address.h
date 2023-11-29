#pragma once

#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#include <string>

#include "utility/string_view.h"

struct SndData;
struct UdpData;

namespace dy_network
{

class IPAddress
{
public:
    static const IPAddress any;
    static const IPAddress any6;
    static const IPAddress loopback;
    static const IPAddress loopback6;
    static const IPAddress v4_mapped6;

    IPAddress() : IPAddress(AF_UNSPEC) {}

    explicit IPAddress(const in_addr& ip4)
        : IPAddress(AF_INET)
    {
        _u.ip4 = ip4;
    }

    explicit IPAddress(const in6_addr& ip6)
        : IPAddress(AF_INET6)
    {
        _u.ip6 = ip6;
    }

    explicit IPAddress(uint32_t ip_in_host_byte_order);

    explicit IPAddress(const UdpData& ud);

    bool operator==(const IPAddress& other) const;
    bool operator<(const IPAddress& other) const;

    bool operator!=(const IPAddress& other) const
    {
        return !((*this) == other);
    }

    bool operator>(const IPAddress& other) const
    {
        return (*this) != other && !((*this) < other);
    }

    int cmp(const IPAddress& other) const;

    int family() const { return _family; }
    in_addr ipv4_address() const { return _u.ip4; }
    in6_addr ipv6_address() const { return _u.ip6; }
    size_t size() const;
    uint32_t v4_as_uint32() const;
    IPAddress as_ipv6_address() const;
    IPAddress as_ipv4_address() const;
    void unwrap_v4_mapped();

    bool is_nil() const { return AF_UNSPEC == _family; }
    bool is_v4() const { return AF_INET == _family; }
    bool is_v6() const { return AF_INET6 == _family; }
    bool is_any() const;
    bool is_loopback() const;
    bool is_link_local() const;
    bool is_private_network() const;
    bool is_private() const;
    bool is_ULA() const;
    bool is_v4_mapped() const;
    bool is_6to4() const;
    bool is_teredo() const;
    bool is_v4_compatibility() const;
    bool is_site_local() const;
    bool is_6bone() const;
    bool is_mac_based() const;
    size_t hash_value() const;

    void set_family(int family) { _family = family; }
    void from_network_order_ipv4(uint32_t ip4);
    bool from_sockaddr(const sockaddr* addr, int len);
    bool from_udp_data(const UdpData& ud);
    void to_send_data(SndData& sd) const;
    std::string to_string() const;
    const char *to_string(char *buf, size_t len) const;
    bool from_string(string_view str);
    bool from_string(const char *str);
    static bool from_string(const std::string& str, IPAddress *out);

    template<size_t N>
    const char *to_string(char(&buf)[N]) const { return to_string(buf, N); }
private:
    explicit IPAddress(int family)
        : _family(family)
    {
        memset(&_u, 0, sizeof(_u));
    }

    int _family = AF_UNSPEC;
    union
    {
        in_addr ip4;
        in6_addr ip6;
    } _u;
};

}

namespace std
{
template<>
struct hash<dy_network::IPAddress>
{
    size_t operator() (const dy_network::IPAddress& ip) const
    {
        return ip.hash_value();
    }
};
}
