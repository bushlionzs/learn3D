#include "getifaddrs.h"
namespace dy_network
{

#ifdef __ANDROID__
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

struct netlinkrequest
{
    nlmsghdr header;
    ifaddrmsg msg;
};

const int kMaxReadSize = 4096;

int set_ifname(struct ifaddrs* ifaddr, int interface)
{
    char buf[IFNAMSIZ] = { 0 };
    char* name = if_indextoname(interface, buf);
    if (name == nullptr)
    {
        return -1;
    }

    ifaddr->ifa_name = new char[strlen(name) + 1];
    strncpy(ifaddr->ifa_name, name, strlen(name) + 1);
    return 0;
}

int set_flags(struct ifaddrs* ifaddr)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        return -1;
    }

    ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifaddr->ifa_name, IFNAMSIZ - 1);
    int rc = ioctl(fd, SIOCGIFFLAGS, &ifr);
    close(fd);
    if (rc == -1)
    {
        return -1;
    }

    ifaddr->ifa_flags = ifr.ifr_flags;

    return 0;
}

int set_addresses(struct ifaddrs* ifaddr, ifaddrmsg* msg, void* data, size_t len)
{
    if (msg->ifa_family == AF_INET)
    {
        sockaddr_in* sa = new sockaddr_in;
        sa->sin_family = AF_INET;
        memcpy(&sa->sin_addr, data, len);
        ifaddr->ifa_addr = reinterpret_cast<sockaddr*>(sa);
    }
    else if (msg->ifa_family == AF_INET6)
    {
        sockaddr_in6* sa = new sockaddr_in6;
        sa->sin6_family = AF_INET6;
        sa->sin6_scope_id = msg->ifa_index;
        memcpy(&sa->sin6_addr, data, len);
        ifaddr->ifa_addr = reinterpret_cast<sockaddr*>(sa);
    }
    else
    {
        return -1;
    }

    return 0;
}

int make_prefixes(struct ifaddrs* ifaddr, int family, int prefixlen)
{
    char* prefix = nullptr;
    if (family == AF_INET)
    {
        sockaddr_in* mask = new sockaddr_in;
        mask->sin_family = AF_INET;
        memset(&mask->sin_addr, 0, sizeof(in_addr));
        ifaddr->ifa_netmask = reinterpret_cast<sockaddr*>(mask);
        if (prefixlen > 32)
        {
            prefixlen = 32;
        }
        prefix = reinterpret_cast<char*>(&mask->sin_addr);
    }
    else if (family == AF_INET6)
    {
        sockaddr_in6* mask = new sockaddr_in6;
        mask->sin6_family = AF_INET6;
        memset(&mask->sin6_addr, 0, sizeof(in6_addr));
        ifaddr->ifa_netmask = reinterpret_cast<sockaddr*>(mask);
        if (prefixlen > 128) {
            prefixlen = 128;
        }
        prefix = reinterpret_cast<char*>(&mask->sin6_addr);
    }
    else
    {
        return -1;
    }
    for (int i = 0; i < (prefixlen / 8); i++)
    {
        *prefix++ = 0xFF;
    }

    char remainder = 0xff;
    remainder <<= (8 - prefixlen % 8);
    *prefix = remainder;
    return 0;
}

int populate_ifaddrs(struct ifaddrs* ifaddr, ifaddrmsg* msg, void* bytes, size_t len)
{
    if (set_ifname(ifaddr, msg->ifa_index) != 0)
    {
        return -1;
    }

    if (set_flags(ifaddr) != 0)
    {
        return -1;
    }

    if (set_addresses(ifaddr, msg, bytes, len) != 0)
    {
        return -1;
    }
    if (make_prefixes(ifaddr, msg->ifa_family, msg->ifa_prefixlen) != 0)
    {
        return -1;
    }

    return 0;
}

int getifaddrs(struct ifaddrs** result)
{
    int fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (fd < 0)
    {
        return -1;
    }

    netlinkrequest ifaddr_request;
    memset(&ifaddr_request, 0, sizeof(ifaddr_request));
    ifaddr_request.header.nlmsg_flags = NLM_F_ROOT | NLM_F_REQUEST;
    ifaddr_request.header.nlmsg_type = RTM_GETADDR;
    ifaddr_request.header.nlmsg_len = NLMSG_LENGTH(sizeof(ifaddrmsg));

    ssize_t count = send(fd, &ifaddr_request, ifaddr_request.header.nlmsg_len, 0);
    if (static_cast<size_t>(count) != ifaddr_request.header.nlmsg_len)
    {
        close(fd);
        return -1;
    }

    struct ifaddrs* start = nullptr;
    struct ifaddrs* current = nullptr;
    char buf[kMaxReadSize];
    ssize_t amount_read = recv(fd, &buf, kMaxReadSize, 0);
    while (amount_read > 0)
    {
        nlmsghdr* header = reinterpret_cast<nlmsghdr*>(&buf[0]);
        size_t header_size = static_cast<size_t>(amount_read);
        for (; NLMSG_OK(header, header_size);
            header = NLMSG_NEXT(header, header_size))
        {
            switch (header->nlmsg_type)
            {
            case NLMSG_DONE:
                // Success. Return.
                *result = start;
                close(fd);
                return 0;
            case NLMSG_ERROR:
                close(fd);
                freeifaddrs(start);
                return -1;
            case RTM_NEWADDR:
            {
                ifaddrmsg* address_msg =
                    reinterpret_cast<ifaddrmsg*>(NLMSG_DATA(header));
                rtattr* rta = IFA_RTA(address_msg);
                ssize_t payload_len = IFA_PAYLOAD(header);
                while (RTA_OK(rta, payload_len))
                {
                    if ((address_msg->ifa_family == AF_INET &&
                        rta->rta_type == IFA_LOCAL) ||
                        (address_msg->ifa_family == AF_INET6 &&
                            rta->rta_type == IFA_ADDRESS))
                    {
                        ifaddrs* newest = new ifaddrs;
                        memset(newest, 0, sizeof(ifaddrs));
                        if (current)
                        {
                            current->ifa_next = newest;
                        }
                        else
                        {
                            start = newest;
                        }

                        if (populate_ifaddrs(newest, address_msg, RTA_DATA(rta),
                            RTA_PAYLOAD(rta)) != 0)
                        {
                            freeifaddrs(start);
                            *result = nullptr;
                            return -1;
                        }
                        current = newest;
                    }

                    rta = RTA_NEXT(rta, payload_len);
                }
                break;
            }
            }
        }
        amount_read = recv(fd, &buf, kMaxReadSize, 0);
    }
    close(fd);
    freeifaddrs(start);
    return -1;
}

void freeifaddrs(struct ifaddrs* addrs)
{
    struct ifaddrs* last = nullptr;
    struct ifaddrs* cursor = addrs;
    while (cursor)
    {
        delete[] cursor->ifa_name;
        delete cursor->ifa_addr;
        delete cursor->ifa_netmask;
        last = cursor;
        cursor = cursor->ifa_next;
        delete last;
    }
}

#endif

#if !_WIN32

#include <arpa/inet.h>
#ifndef __ANDROID__
#include <sys/socket.h>
#include <net/if.h>
#include <ifaddrs.h>
#endif

bool getifaddrs_ipv4(std::vector<ifaddrinfo_ip_t>& _addrs)
{
    struct ifaddrs* ifap, *ifa;

    getifaddrs(&ifap);

    for (ifa = ifap; ifa; ifa = ifa->ifa_next)
    {
        sockaddr_in* sa = (struct sockaddr_in*) ifa->ifa_addr;

        if (NULL == sa || 0 != (ifa->ifa_flags & IFF_LOOPBACK))
        {
            continue;
        }
        
        ifaddrinfo_ip_t addr;
        addr.ifa_name = ifa->ifa_name;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            addr.ifa_ip = IPAddress(sa->sin_addr);
            //inet_ntop(sa->sin_family, &(sa->sin_addr), addr.ip, sizeof(addr.ip));
        }
        else if (ifa->ifa_addr->sa_family == AF_INET6)
        {
            sockaddr_in6* sa6 = (struct sockaddr_in6*) ifa->ifa_addr;

            addr.ifa_ip = IPAddress(sa6->sin6_addr);
            //inet_ntop(sa6->sin6_family, &(sa6->sin6_addr), addr.ip, sizeof(addr.ip));
        }
        _addrs.push_back(addr);
    }

    freeifaddrs(ifap);
    return !_addrs.empty();
}


bool getifaddrs_ip_lan(std::vector<ifaddrinfo_ip_t>& _addrs)
{
    struct ifaddrs* ifap, *ifa;

    getifaddrs(&ifap);

    for (ifa = ifap; ifa; ifa = ifa->ifa_next)
    {
        sockaddr_in* sa = (struct sockaddr_in*) ifa->ifa_addr;

        if (NULL == sa) continue;

        if (!(ifa->ifa_flags & IFF_LOOPBACK)
            && !(ifa->ifa_flags & IFF_POINTOPOINT)
            && (ifa->ifa_flags & IFF_BROADCAST)
            && (ifa->ifa_flags & IFF_RUNNING)) 
        {
            ifaddrinfo_ip_t addr;
            addr.ifa_name = ifa->ifa_name;

            if (ifa->ifa_addr->sa_family == AF_INET) 
            {
                addr.ifa_ip = IPAddress(sa->sin_addr);
                //inet_ntop(sa->sin_family, &(sa->sin_addr), addr.ip, sizeof(addr.ip));                
            }
            else if (ifa->ifa_addr->sa_family == AF_INET6)
            {
                sockaddr_in6* sa6 = (struct sockaddr_in6*) ifa->ifa_addr;

                addr.ifa_ip = IPAddress(sa6->sin6_addr);
                //inet_ntop(sa6->sin6_family, &(sa6->sin6_addr), addr.ip, sizeof(addr.ip));
            }

            _addrs.push_back(addr);
        }
    }

    freeifaddrs(ifap);
    return !_addrs.empty();
}

#else

#ifdef _WIN32
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "Ws2_32.lib")

#endif // WIN32

    static const char *inet_ntop_v4(const void *src, char *dst, socklen_t size) {
        const char digits[] = "0123456789";
        int i;
        struct in_addr *addr = (struct in_addr *)src;
        u_long a = ntohl(addr->s_addr);
        const char *orig_dst = dst;

        if (size < 16) {
            //xerror("ENOSPC: size = %0", size);
            return NULL;
        }
        for (i = 0; i < 4; ++i) {
            int n = (a >> (24 - i * 8)) & 0xFF;
            int non_zerop = 0;

            if (non_zerop || n / 100 > 0) {
                *dst++ = digits[n / 100];
                n %= 100;
                non_zerop = 1;
            }
            if (non_zerop || n / 10 > 0) {
                *dst++ = digits[n / 10];
                n %= 10;
                non_zerop = 1;
            }
            *dst++ = digits[n];
            if (i != 3)
                *dst++ = '.';
        }
        *dst++ = '\0';
        return orig_dst;
    }

    bool getifaddrs_ip_lan(std::vector<ifaddrinfo_ip_t>& _addrs) {
        ULONG outBufLen = 0;
        GetAdaptersAddresses(AF_UNSPEC, 0, NULL, NULL, &outBufLen);

        PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
        GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST, NULL, pAddresses, &outBufLen);

        PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
        PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
        LPSOCKADDR addr = NULL;
        pCurrAddresses = pAddresses;

        while (pCurrAddresses)
        {
            if (pCurrAddresses->OperStatus != IfOperStatusUp)
            {
                pCurrAddresses = pCurrAddresses->Next;
                continue;
            }
            pUnicast = pCurrAddresses->FirstUnicastAddress;

            while (pUnicast)
            {
                if (pCurrAddresses->IfType != MIB_IF_TYPE_LOOPBACK)
                {
                    ifaddrinfo_ip_t addr_t;
                    addr = pUnicast->Address.lpSockaddr;
                    if (addr->sa_family == AF_INET)
                    {
                        sockaddr_in *sa_in = (sockaddr_in *)addr;
                        //char* strIP = inet_ntoa((sa_in->sin_addr));
                        addr_t.ifa_name = pCurrAddresses->AdapterName;
                        addr_t.ifa_ip = IPAddress(sa_in->sin_addr);
                        //inet_ntop_v4(&(sa_in->sin_addr), addr_t.ip, sizeof(addr_t.ip));
                        
                    }
                    else if (addr->sa_family == AF_INET6)
                    {
                        sockaddr_in6 *sa_in6 = (sockaddr_in6 *)addr;
                        addr_t.ifa_ip = IPAddress(sa_in6->sin6_addr);
                        //inet_ntop(sa_in6->sin6_family, &(sa_in6->sin6_addr), addr_t.ip, sizeof(addr_t.ip));
                        addr_t.ifa_name = pCurrAddresses->AdapterName;
                    }

                    if (pCurrAddresses->IfType == IF_TYPE_IEEE80211)
                    {
                        _addrs.insert(_addrs.begin(), addr_t);
                    }
                    else
                    {
                        _addrs.push_back(addr_t);
                    }
                }
                
                pUnicast = pUnicast->Next;
            }
            pCurrAddresses = pCurrAddresses->Next;
        }
        free(pAddresses);
        return !_addrs.empty();
    }

#endif
}
