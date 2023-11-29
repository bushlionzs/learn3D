#include "net_define.h"

extern NetLibParam g_param;

const char *SessionData::get_local_ip() const
{
    if (!m_LocalIP.empty())
    {
        return m_LocalIP.c_str();
    }

    if (AF_INET == m_family)
    {
        return "0.0.0.0";
    }

    if (AF_INET6 == m_family)
    {
        return "::";
    }

    return nullptr;
}

void SessionData::check_inet_family()
{
    if (AF_UNSPEC != m_family)
    {
        return;
    }

    const char *ip = nullptr;
    if (!m_LocalIP.empty())
    {
        ip = m_LocalIP.c_str();
    }
    else if (!m_PeerIP.empty())
    {
        ip = m_PeerIP.c_str();
    }

    if (ip)
    {
        dy_network::SockaddrStorage check_family_addr;
        if (!check_family_addr.set_ip_string(ip))
        {
            return;
        }

        m_family = check_family_addr.family();
    }
    else
    {
        m_family = g_param._ip_stack_affinity;
    }
}

bool SndData::from_string(const char *str)
{
    if (dy_network::ipaddr_from_string(AF_INET, str, &this->_dst_address))
    {
        return true;
    }

    if (dy_network::ipaddr_from_string(AF_INET6, str, &this->_dst_address6))
    {
        return true;
    }

    return false;
}

bool UdpData::from_addr(const sockaddr* addr, int addrlen)
{
    auto ss = reinterpret_cast<const dy_network::SockaddrStorage *>(addr);
    if (AF_INET == ss->family())
    {
        if (addrlen < sizeof(dy_network::Sockaddr4))
        {
            return false;
        }

        auto v4 = ss->addr4();
        this->_send_ip = v4->sin_addr.s_addr;
        this->_send_port = v4->port();

        return true;
    }

    if (AF_INET6 == ss->family())
    {
        if (addrlen < sizeof(dy_network::Sockaddr6))
        {
            return false;
        }

        auto v6 = ss->addr6();
        this->_send_ip = 0;
        this->_send_ip6 = v6->sin6_addr;
        this->_send_port = v6->port();

        return true;
    }

    return false;
}

bool UdpData::to_addr(sockaddr* addr, int& addrlen) const
{
    if (is_ip4())
    {
        auto addr4 = reinterpret_cast<dy_network::Sockaddr4 *>(addr);
        addr4->sin_family = AF_INET;
        addr4->set_port(_send_port);
        addr4->sin_addr.s_addr = _send_ip;

        addrlen = sizeof(dy_network::Sockaddr4);

        return true;
    }

    if (is_ip6())
    {
        auto addr6 = reinterpret_cast<dy_network::Sockaddr6 *>(addr);
        addr6->sin6_family = AF_INET6;
        addr6->set_port(_send_port);
        addr6->sin6_addr = _send_ip6;
        addr6->zero_unused();

        addrlen = sizeof(dy_network::Sockaddr6);

        return true;
    }

    return false;
}

const char *UdpData::ip_string(char *buf, size_t len) const
{
    if (is_ip4())
    {
        in_addr ip4;
        ip4.s_addr = _send_ip;

        return dy_network::ipaddr_to_string(AF_INET, &ip4, buf, len);
    }

    if (is_ip6())
    {
        return dy_network::ipaddr_to_string(AF_INET6, &_send_ip6, buf, len);
    }

    return nullptr;
}

