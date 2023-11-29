#ifndef __NET_TOOLS_H__
#define __NET_TOOLS_H__
#include <stdint.h>
#include <string>

uint32_t get_ip_network_order(const char* ip);

std::string get_ip_string_by_network_order(uint32_t ip_value);

void generate_ip_string(uint32_t ip_value, char* ipstr, int size);

std::string get_ip_by_interface_name(const char* interface_name);

std::string get_local_ip();

uint64_t get_local_usec();
#endif //__NET_TOOLS_H__