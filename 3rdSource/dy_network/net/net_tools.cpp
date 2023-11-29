#include <stdio.h>      
#include <sys/types.h>
#ifndef _WIN32
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/time.h>
#if !defined(__ANDROID__)
#include <ifaddrs.h>
#else
#include "utility/getifaddrs.h"
#endif
#else
#include <winsock.h>
#endif
#include <string.h> 
#include <stdlib.h>


#include <vector>

#include "net_tools.h"

uint32_t get_ip_network_order(const char* ip)
{
    uint32_t value = inet_addr(ip);
    return value;
}

std::string get_ip_string_by_network_order(uint32_t ip_value)
{
	std::string ip_str;
	char buffer[128];
	uint8_t* tmp = (uint8_t*)&ip_value;
	snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", tmp[0], tmp[1], tmp[2], tmp[3]);
	ip_str = buffer;
	return ip_str;
}

void generate_ip_string(uint32_t ip_value, char* ipstr, int size)
{
    uint8_t* tmp = (uint8_t*)&ip_value;
    snprintf(ipstr, size, "%d.%d.%d.%d", tmp[0], tmp[1], tmp[2], tmp[3]); 
}

std::string get_ip_by_interface_name(const char* interface_name)
{
    std::string ip;
#ifndef _WIN32
    struct ifaddrs * ifAddrStruct = NULL;
    void * tmpAddrPtr = NULL;

#ifndef __ANDROID__
    getifaddrs(&ifAddrStruct);
#else
    dy_network::getifaddrs(&ifAddrStruct);
#endif
    struct ifaddrs *ifa = ifAddrStruct;

    while (ifa != NULL)
    {
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if (strcmp(interface_name, ifa->ifa_name) == 0)
            {
                ip = addressBuffer;
                free(ifAddrStruct);

                return ip;
            }
        }

        ifa = ifa->ifa_next;
    }

    if (ifAddrStruct != NULL)
    {
        free(ifAddrStruct);
    }
#endif     
    return ip;
}

static bool is_ip_inrange(const std::string&ip, const char* start_ip, const char* end_ip)
{
    uint32_t  start = get_ip_network_order(start_ip);
    uint32_t  end    = get_ip_network_order(end_ip);
    
    uint32_t ip_value = get_ip_network_order(ip.c_str());
    if (ip_value >= start && ip_value <= end)
    {
        return true;
    }
    return false;
}
std::string get_local_ip()
{
    std::vector<std::string> ip_list;
#ifndef _WIN32
    struct ifaddrs * ifAddrStruct=NULL;
    void * tmpAddrPtr=NULL;

#ifndef __ANDROID__
    getifaddrs(&ifAddrStruct);
#else
    dy_network::getifaddrs(&ifAddrStruct);
#endif

    struct ifaddrs * ifa = ifAddrStruct;
    
    while (ifa != NULL) 
    {
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);            
            std::string ip = addressBuffer;
            ip_list.push_back(ip);
        }
        
        ifa=ifa->ifa_next;
    }

    if (ifAddrStruct != NULL)
    {
        free(ifAddrStruct);
    }
    
    std::vector<std::string>::iterator itor = ip_list.begin();
    
    for (; itor != ip_list.end(); itor++)
    {
        const std::string& current = *itor;
        
        if (current == "127.0.0.1")
        {
            continue;
        }
        if (is_ip_inrange(current, "10.0.0.0", "10.255.255.255"))
        {
            return current;
        }
        
        if (is_ip_inrange(current, "172.16.0.0", "172.31.255.255"))
        {
            return current;
        }
        
        if (is_ip_inrange(current, "192.168.0.0", "192.168.255.255"))
        {
            return current;
        }
        
        if (is_ip_inrange(current, "169.254.0.0", "169.254.255.255"))
        {
            return current;
        }
    }
#endif
    return std::string();
}
