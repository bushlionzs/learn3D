#pragma once
#include <stdint.h>
#include <double_list.h>
#include <net_handle.h>

struct CacheNode
{
	struct list_head _cache_list;
	NetHandle _handle;
	uint32_t _size;
	char _packet[0];
};

class CachePacket
{
public:
	CachePacket(uint32_t max_cache_size);
	~CachePacket();

	void cache_send(NetHandle h, const char* data, uint32_t size);

	void cache_send();

private:
	void _cache_packet(NetHandle h, const char* data, uint32_t size);
private:
	uint32_t _max_cache_size;
	uint32_t _current_cache_size;
	struct list_head _cache_list;


};