#pragma once

#include <string>
#include <vector>
#include <string.h>
#include "ip_address.h"

#ifdef __ANDROID__
#include <sys/socket.h>
struct ifaddrs
{
    struct ifaddrs* ifa_next;
    char* ifa_name;
    unsigned int ifa_flags;
    struct sockaddr* ifa_addr;
    struct sockaddr* ifa_netmask;
    // Real ifaddrs has broadcast, point to point and data members.
    // We don't need them (yet?).
};
#endif

namespace dy_network
{

struct ifaddrinfo_ip_t
{
    ifaddrinfo_ip_t()
    {
        //memset(ip, 0, sizeof(ip));
    }

    std::string  ifa_name;
    IPAddress    ifa_ip;
    //char         ip[INET6_ADDRSTRLEN];
};

bool getifaddrs_ip_lan(std::vector<ifaddrinfo_ip_t>& addrs);

#ifdef __ANDROID__
int getifaddrs(struct ifaddrs** result);
void freeifaddrs(struct ifaddrs* addrs);
#endif
}