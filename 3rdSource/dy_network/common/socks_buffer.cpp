#include "socks_buffer.h"
#include "server_def.h"
#include "server_interface.h"

SocksBuffer::SocksBuffer(IServerInterface* server, uint32_t capacity)
	:INetBuffer(server, capacity, true)
{

}

SocksBuffer::~SocksBuffer()
{

}

bool  SocksBuffer::process_data(const SessionData& sd)
{
	while (true)
	{
		uint32_t current_length = _end - _start;
		if (current_length < 2)
			break;
		uint32_t method_length = (uint32_t)_buf[1];
		if (current_length < (method_length + 2))
			break;
		const char* current = _buf + _start;
		uint32_t length = method_length + 2;
		_server->post_network_message(NetMsg_Data, _net_handle, (const uint8_t*)current, method_length + 2);
	}
	return true;
}