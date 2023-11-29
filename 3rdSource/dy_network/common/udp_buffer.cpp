#include "udp_buffer.h"
#include <net_handle.h>
#include <platform_common.h>
#include <platform_log.h>
#include <server_def.h>
#include <net_header.h>
#include <server_interface.h>

UdpBuffer::UdpBuffer(IServerInterface* server, uint32_t capacity):
INetBuffer(server, capacity, true)
{

}

UdpBuffer::~UdpBuffer()
{

}

void UdpBuffer::recv_udp_data(const char* data, uint32_t size, const sockaddr *addr, int addrlen)
{
	UdpData* containter = (UdpData*)malloc(sizeof(UdpData) + size);
	containter->_net_handle = _net_handle;
    containter->from_addr(addr, addrlen);
	containter->_size = size;
	memcpy(containter->_data, data, size);
	_server->post_network_message(NetMsg_UdpData, (uint64_t)containter, 0, 0);
}

bool  UdpBuffer::process_data(const SessionData& sd)
{
	return true;
}