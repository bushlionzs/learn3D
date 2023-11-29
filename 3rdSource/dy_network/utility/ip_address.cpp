#include "ip_address.h"

#include "byte_order.h"
#include "net_define.h"

namespace dy_network
{

namespace
{
#ifndef _WIN32
constexpr in_addr in4addr_any = { 0 };

#if __BYTE_ORDER == __BIG_ENDIAN
constexpr in_addr in4addr_loopback = { 0x7F000001 };
#else
constexpr in_addr in4addr_loopback = { 0x0100007F };
#endif

constexpr in6_addr in6addr_v4mappedprefix =
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0} };
constexpr in6_addr in6addr_6to4prefix = { {{0x20, 0x02, 0}} };
constexpr in6_addr in6addr_teredoprefix = { {{0x20, 0x01, 0x00, 0x00}} };

#endif

constexpr in6_addr in6addr_private_prefix = { {{0xFD}} };
}

// static 
const IPAddress IPAddress::any(in4addr_any);

// static 
const IPAddress IPAddress::any6(in6addr_any);

const IPAddress IPAddress::loopback(in4addr_loopback);

const IPAddress IPAddress::loopback6(in6addr_loopback);

// static 
const IPAddress IPAddress::v4_mapped6(in6addr_v4mappedprefix);

IPAddress::IPAddress(uint32_t ip_in_host_byte_order)
    : IPAddress(AF_INET)
{
    _u.ip4.s_addr = htobe32(ip_in_host_byte_order);
}

IPAddress::IPAddress(const UdpData& ud)
{
    from_udp_data(ud);
}

bool IPAddress::operator==(const IPAddress& other) const
{
    if (_family != other._family)
    {
        return false;
    }

    if (_family == AF_INET)
    {
        return memcmp(&_u.ip4, &other._u.ip4, sizeof(_u.ip4)) == 0;
    }

    if (_family == AF_INET6)
    {
        return memcmp(&_u.ip6, &other._u.ip6, sizeof(_u.ip6)) == 0;
    }

    return _family == AF_UNSPEC;
}

bool IPAddress::operator<(const IPAddress& other) const
{
    return cmp(other) < 0;
}

int IPAddress::cmp(const IPAddress& other) const
{
    // IPv4 is 'less than' IPv6
    if (_family != other._family)
    {
        if (_family == AF_UNSPEC)
        {
            return -1;
        }

        if (_family == AF_INET && other._family == AF_INET6)
        {
            return -1;
        }

        return 1;
    }

    // Comparing addresses of the same family.
    if (AF_INET == _family)
    {
        int64_t a = be32toh(_u.ip4.s_addr);
        int64_t b = be32toh(other._u.ip4.s_addr);
        int64_t c = a - b;
        return  0 == c ? 0 : (c > 0 ? 1 : -1);
    }

    if (AF_INET6 == _family)
    {
        return memcmp(&_u.ip6.s6_addr, &other._u.ip6.s6_addr, 16);
    }

    // Catches AF_UNSPEC and invalid addresses.
    return 0;
}

size_t IPAddress::size() const
{
    if (AF_INET == _family)
    {
        return sizeof(in_addr);
    }

    if (AF_INET6 == _family)
    {
        return sizeof(in6_addr);
    }

    return 0;
}

uint32_t IPAddress::v4_as_uint32() const
{
    if (_family == AF_INET)
    {
        return be32toh(_u.ip4.s_addr);
    }

    return 0;
}

IPAddress IPAddress::as_ipv6_address() const
{
    if (AF_INET != _family)
    {
        return *this;
    }

    in6_addr v6addr = in6addr_v4mappedprefix;
    memcpy(&v6addr.s6_addr[12], &_u.ip4.s_addr, sizeof(_u.ip4.s_addr));
    return IPAddress(v6addr);
}

IPAddress IPAddress::as_ipv4_address() const
{
    if (AF_INET6 !=_family)
    {
        return *this;
    }

    in_addr v4addr;
    memcpy(&v4addr.s_addr, &_u.ip6.s6_addr[12], sizeof(v4addr.s_addr));
    return IPAddress(v4addr);
}

void IPAddress::unwrap_v4_mapped()
{
    if (AF_INET6 ==_family && is_v4_mapped())
    {
        memmove(&_u.ip4.s_addr, &_u.ip6.s6_addr[12], sizeof(_u.ip4.s_addr));
        _family = AF_INET;
    }
}

bool IPAddress::is_any() const
{
    if (AF_INET == _family)
    {
        return *this == IPAddress::any;
    }

    if (AF_INET6 == _family)
    {
        return *this == IPAddress::any6
            || *this == IPAddress::v4_mapped6;
    }

    return false;
}

bool IPAddress::is_loopback() const
{
    if (AF_INET == _family)
    {
        return ((v4_as_uint32() >> 24) == 127);
    }
 
    if (AF_INET6 == _family)
    {
        return *this == IPAddress(in6addr_loopback);
    }

    return false;
}

bool IPAddress::is_link_local() const
{
    if (AF_INET == _family)
    {
        uint32_t ip_in_host_order = v4_as_uint32();
        return ((ip_in_host_order >> 16) == ((169 << 8) | 254));
    }

    if (AF_INET6 == _family)
    {
        in6_addr addr = _u.ip6;
        return (addr.s6_addr[0] == 0xFE) && ((addr.s6_addr[1] & 0xC0) == 0x80);
    }

    return false;
}

bool IPAddress::is_private_network() const
{
    if (AF_INET == _family)
    {
        uint32_t ip_in_host_order = v4_as_uint32();
        return ((ip_in_host_order >> 24) == 10)
            || ((ip_in_host_order >> 20) == ((172 << 4) | 1))
            || ((ip_in_host_order >> 16) == ((192 << 8) | 168));
    }

    if (AF_INET6 == _family)
    {
        return memcmp(&_u.ip6, &in6addr_private_prefix, (8 >> 3)) == 0;
    }

    return false;
}

bool IPAddress::is_private() const
{
    return is_link_local() || is_loopback() || is_private_network();
}

bool IPAddress::is_ULA() const
{
    return (_u.ip6.s6_addr[0] & 0xFE) == 0xFC;
}

bool IPAddress::is_v4_mapped() const
{
    return memcmp(&_u.ip6, &in6addr_v4mappedprefix, (96 >> 3)) == 0;
}

bool IPAddress::is_6to4() const
{
    return memcmp(&_u.ip6, &in6addr_6to4prefix, (16 >> 3)) == 0;
}

bool IPAddress::is_teredo() const
{
    return memcmp(&_u.ip6, &in6addr_teredoprefix, (32 >> 3)) == 0;
}

bool IPAddress::is_v4_compatibility() const
{
    return false;
}

bool IPAddress::is_site_local() const
{
    return _u.ip6.s6_addr[0] == 0xFE && (_u.ip6.s6_addr[1] & 0xC0) == 0xC0;
}

bool IPAddress::is_6bone() const
{
    return false;
}

bool IPAddress::is_mac_based() const
{
    in6_addr addr = _u.ip6;
    return (addr.s6_addr[8] & 0x02)
        && (addr.s6_addr[11] == 0xFF)
        && (addr.s6_addr[12] == 0xFE);
}

size_t IPAddress::hash_value() const
{
    if (AF_INET == _family)
    {
        return _u.ip4.s_addr;
    }

    if (AF_INET6 == _family)
    {
        in6_addr v6addr = _u.ip6;
        auto v6_as_ints = reinterpret_cast<const uint32_t*>(&v6addr.s6_addr);
        return v6_as_ints[0] ^ v6_as_ints[1] ^ v6_as_ints[2] ^ v6_as_ints[3];
    }

    return 0;
}

void IPAddress::from_network_order_ipv4(uint32_t ip4)
{
    _family = AF_INET;
    _u.ip4.s_addr = ip4;
}

bool IPAddress::from_sockaddr(const sockaddr* addr, int len)
{
    //assert(addr && len > 0);

    _family = addr->sa_family;

    if (AF_INET == addr->sa_family)
    {
        if (len < sizeof(sockaddr_in))
        {
            return false;
        }

        _u.ip4 = reinterpret_cast<const sockaddr_in *>(addr)->sin_addr;

        return true;
    }

    if (AF_INET6 == addr->sa_family)
    {
        if (len < sizeof(sockaddr_in6))
        {
            return false;
        }

        _u.ip6 = reinterpret_cast<const sockaddr_in6 *>(addr)->sin6_addr;

        return true;
    }

    return false;
}

bool IPAddress::from_udp_data(const UdpData& ud)
{
    if (ud.is_ip4())
    {
        _family = AF_INET;
        _u.ip4.s_addr = ud._send_ip;

        return true;
    }

    if (ud.is_ip6())
    {
        _family = AF_INET6;
        _u.ip6 = ud._send_ip6;

        return true;
    }

    _family = AF_UNSPEC;

    return false;
}

void IPAddress::to_send_data(SndData& sd) const
{
    if (AF_INET == _family)
    {
        sd._dst_address = _u.ip4.s_addr;
    }
    else if (AF_INET6 == _family)
    {
        sd._dst_address = 0;
        sd._dst_address6 = _u.ip6;
    }
    else
    {
        sd._dst_address = 0;
        memset(&sd._dst_address6, 0, sizeof(in6_addr));
    }
}

std::string IPAddress::to_string() const
{
    if (_family != AF_INET && _family != AF_INET6)
    {
        return "";
    }

    char buf[INET6_ADDRSTRLEN];
    if (!to_string(buf))
    {
        return "";
    }

    return buf;
}

const char *IPAddress::to_string(char *buf, size_t len) const
{
    return inet_ntop(_family, &_u, buf, len);
}

bool IPAddress::from_string(string_view str)
{
    char buf[INET6_ADDRSTRLEN];
    if (str.size() >= INET6_ADDRSTRLEN)
    {
        return false;
    }

    strncpy(buf, str.data(), str.size());
    buf[str.size()] = 0;

    return from_string(buf);
}

bool IPAddress::from_string(const char *str)
{
    _family = AF_UNSPEC;
    if (inet_pton(AF_INET, str, &_u.ip4) == 0)
    {
        if (inet_pton(AF_INET6, str, &_u.ip6) == 0)
        {
            return false;
        }

        _family = AF_INET6;
    }
    else
    {
        _family = AF_INET;
    }

    return true;
}

// static 
bool IPAddress::from_string(const std::string& str, IPAddress *out)
{
    return out->from_string(str.c_str());
}

}
