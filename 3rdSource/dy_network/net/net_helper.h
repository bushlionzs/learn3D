#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#endif

#include <cstdint>
#include <string>

namespace dy_network
{

inline const char *ipaddr_to_string(int family, const void *addr, char *buf, size_t len)
{
    return inet_ntop(family, addr, buf, len);
}

template<size_t N>
inline const char *ipaddr_to_string(int family, const void *addr, char (&buf)[N])
{
    return inet_ntop(family, addr, buf, N);
}

inline const char *ipaddr_to_string(int family, const void *addr, std::string& ip)
{
    char out[INET6_ADDRSTRLEN];
    if (!ipaddr_to_string(family, addr, out))
    {
        return nullptr;
    }

    out[INET6_ADDRSTRLEN - 1] = 0;
    ip.assign(out);

    return ip.c_str();
}

inline bool ipaddr_from_string(int family, const char *str, void *addr)
{
    return 1 == inet_pton(family, str, addr);
}

inline int ip_family_from_string(const char *str)
{
    in_addr addr4;
    if (ipaddr_from_string(AF_INET, str, &addr4))
    {
        return AF_INET;
    }

    in6_addr addr6;
    if (ipaddr_from_string(AF_INET6, str, &addr6))
    {
        return AF_INET6;
    }

    return AF_UNSPEC;
}

struct Sockaddr : sockaddr
{
    constexpr int family() const noexcept { return this->sa_family; }
};

struct Sockaddr4 : sockaddr_in
{
    constexpr uint16_t family() const noexcept { return this->sin_family; }
    uint16_t port() const noexcept { return ntohs(this->sin_port); }
    void set_port(uint16_t port) noexcept { this->sin_port = htons(port); }
    constexpr size_t size() const noexcept { return sizeof(sockaddr_in); }

    std::string get_ip_string() const noexcept
    {
        std::string out;
        get_ip_string(out);
        return out;
    }

    template<typename ... Args>
    const char *get_ip_string(Args&& ... args) const noexcept
    {
        return ipaddr_to_string(AF_INET, &this->sin_addr, std::forward<Args>(args)...);
    }

    bool set_ip_string(const char *str) noexcept
    {
        return ipaddr_from_string(AF_INET, str, &this->sin_addr);
    }
};

struct Sockaddr6 : sockaddr_in6
{
    constexpr uint16_t family() const noexcept { return this->sin6_family; }
    uint16_t port() const noexcept { return ntohs(this->sin6_port); }
    void set_port(uint16_t port) noexcept { this->sin6_port = htons(port); }
    constexpr size_t size() const noexcept { return sizeof(sockaddr_in6); }

    void zero_unused()
    {
        this->sin6_flowinfo = 0;
        this->sin6_scope_id = 0;
    }

    std::string get_ip_string() const noexcept
    {
        std::string out;
        get_ip_string(out);
        return out;
    }

    template<typename ... Args>
    const char *get_ip_string(Args&& ... args) const noexcept
    {
        return ipaddr_to_string(AF_INET6, &this->sin6_addr, std::forward<Args>(args)...);
    }

    bool set_ip_string(const char *str) noexcept
    {
        return ipaddr_from_string(AF_INET6, str, &this->sin6_addr);
    }
};

struct SockaddrStorage : sockaddr_storage
{
    constexpr uint16_t family() const noexcept { return this->ss_family; }
    Sockaddr *addr() noexcept { return reinterpret_cast<Sockaddr *>(this); }
    const Sockaddr *addr() const noexcept { return reinterpret_cast<const Sockaddr *>(this); }
    Sockaddr4 *addr4() noexcept { return reinterpret_cast<Sockaddr4 *>(this); }
    const Sockaddr4 *addr4() const noexcept { return reinterpret_cast<const Sockaddr4 *>(this); }
    Sockaddr6 *addr6() noexcept { return reinterpret_cast<Sockaddr6 *>(this); }
    const Sockaddr6 *addr6() const noexcept { return reinterpret_cast<const Sockaddr6 *>(this); }

    size_t size() const noexcept
    {
        switch (family())
        {
        case AF_INET:
            return sizeof(sockaddr_in);
        case AF_INET6:
            return sizeof(sockaddr_in6);
        default:
            break;
        }

        return sizeof(sockaddr_storage);
    }

    bool init(const char *ip, uint16_t port)
    {
        if (!set_ip_string(ip))
        {
            return false;
        }

        (void)set_port(port);

        zero_unused();

        return true;
    }

    uint16_t get_port() const noexcept
    {
        uint16_t port = 0;
        get_port(port);
        return port;
    }

    bool set_port(uint16_t port) noexcept
    {
        if (AF_INET == family())
        {
            addr4()->set_port(port);
            return true;
        }

        if (AF_INET6 == family())
        {
            addr6()->set_port(port);
            return true;
        }

        return false;
    }

    bool get_port(uint16_t& port) const noexcept
    {
        if (AF_INET == family())
        {
            port = addr4()->port();
            return true;
        }

        if (AF_INET6 == family())
        {
            port = addr6()->port();
            return true;
        }

        return false;
    }


    std::string get_ip_string() const noexcept
    {
        std::string out;
        get_ip_string(out);
        return out;
    }

    template<typename ... Args>
    const char *get_ip_string(Args&& ... args) const noexcept
    {
        if (AF_INET == family())
        {
            return addr4()->get_ip_string(std::forward<Args>(args)...);
        }

        if (AF_INET6 == family())
        {
            return addr6()->get_ip_string(std::forward<Args>(args)...);
        }

        return nullptr;
    }

    bool set_ip_string(const char *str) noexcept
    {
        if (addr4()->set_ip_string(str))
        {
            this->ss_family = AF_INET;
            return true;
        }

        if (addr6()->set_ip_string(str))
        {
            this->ss_family = AF_INET6;
            return true;
        }

        return false;
    }

    void zero_unused()
    {
        if (AF_INET6 == family())
        {
            addr6()->zero_unused();
        }
    }
};

}
