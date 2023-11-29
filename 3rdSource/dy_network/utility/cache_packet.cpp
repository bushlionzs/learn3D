#include "cache_packet.h"
#include "net_factory.h"
#include "netlib_error.h"
#include "platform_log.h"

CachePacket::CachePacket(uint32_t max_cache_size)
{
	_max_cache_size = max_cache_size;
	_current_cache_size = 0;
}

CachePacket::~CachePacket()
{

}


void CachePacket::cache_send(NetHandle h, const char* data, uint32_t size)
{
	if (list_empty(&_cache_list))
	{
		int32_t ret = NetFactory::GetInstance()->SendData(h, (const uint8_t*)data, size);

		if (ret == NetlibError_BufferError)
		{
			_cache_packet(h, data, size);
			return;
		}
		else if(ret != 0)
		{
			WARNING_LOG("[handle:%llu, ret:%d]cache_send failed", h, ret);
		}
	}
	else
	{
		_cache_packet(h, data, size);
	}
}

void CachePacket::cache_send()
{
	if (list_empty(&_cache_list))
		return;

	struct list_head* current = _cache_list.m_next;

	while (current != &_cache_list)
	{
		CacheNode* node = list_entry(current, CacheNode, _cache_list);

		int32_t ret = NetFactory::GetInstance()->SendData(node->_handle, (const uint8_t*)node->_packet, node->_size);

		if (ret == NetlibError_BufferError)
		{
			break;
		}
		

		if (ret != 0)
		{
			WARNING_LOG("[handle:%llu, ret:%d]cache send failed", node->_handle, ret);
		}
		struct list_head* next = current->m_next;

		list_del(current);

		current = next;

		_current_cache_size -= node->_size;

		free(node);
	}
}

void CachePacket::_cache_packet(NetHandle h, const char* data, uint32_t size)
{
	if (_current_cache_size + size > _max_cache_size)
	{
		WARNING_LOG("[max_cache_size:%d, size:%d]cache packet failed", _max_cache_size, size);
		return;
	}

	CacheNode* node = (CacheNode*)malloc(sizeof(CacheNode) + size);
	node->_handle = h;
	node->_size = size;
	memcpy(node->_packet, data, size);

	list_add_tail(&node->_cache_list, &_cache_list);

	_current_cache_size += size;
}