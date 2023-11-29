#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "net_handle.h"
#include "platform_common.h"
#include <platform_log.h>
#include "recv_buffer.h"
#include "server_def.h"
#include "net_header.h"
#include "server_interface.h"

#define NET_MESSAGE_HEADER_LENGTH (sizeof(NetHeader))

//////////////////////////////////////////////////////////////////////////////
RecvBuffer::RecvBuffer(IServerInterface* server, uint32_t capacity, bool need_split):
INetBuffer(server, capacity, need_split)
{
	
}

RecvBuffer::~RecvBuffer()
{
}

bool RecvBuffer::process_data(const SessionData& sd)
{
    while (true)
	{
        uint32_t current_length = _end - _start;
		if (current_length < NET_MESSAGE_HEADER_LENGTH)
		{
			break;
		}

		NetHeader* header = (NetHeader*)(_buf + _start);
		
		auto length = ntohl(header->mMsgLength);
		
		if (length < NET_MESSAGE_HEADER_LENGTH || length > MAX_NET_PACKET_LENGTH)
		{
			WARNING_LOG("invalid packet , length:%u, handle:%llu", length, _net_handle);
			return false;
		}
		if (current_length  < length)
		{
			break;
		}
		header->mMsgLength = length;
		header->mMsgId = ntohl(header->mMsgId);
		header->mCrypto = ntohs(header->mCrypto);
		header->mVersion = ntohs(header->mVersion);
		const char* current = _buf + _start;
        _server->post_network_message(NetMsg_Data, _net_handle, (const uint8_t*)current, length);
        
        _start += length;
        if (_start == _end)
        {
            _start = _end = 0;
        }
	}
	
	return true;
}


