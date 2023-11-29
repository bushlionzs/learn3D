
#ifndef __PACKET_H__
#define __PACKET_H__
#include <stdint.h>

#include "net_lib.h"

struct MessageBase;
class PlatformSocket;

class NetworkPacket
{
public:
	NetworkPacket(uint32_t size = 1024 * 512);
    virtual ~NetworkPacket();

	const uint8_t* get_buffer()
	{
		return (const uint8_t*)_buffer;
	}
    
    char* get_mutable_buffer()
    { 
        return _buffer;
    }
    uint32_t get_capacity()
    {
        return _buffer_size;
    }
	
	uint32_t get_size()
	{
		return _current_size;
	}

    void set_size(uint32_t size)
    {
        if (size > _buffer_size)
        {
            return ;
        }

        _current_size = size;
    }

	bool GenerateMessage(const char* data , uint32_t size);
    
    bool GenerateMessage(uint16_t msg_id, const char* data , uint32_t size);
    
    bool GenerateWebsocketMessage(uint8_t type, const char* data, uint32_t size, bool is_mask = false);

    bool build_websocket_request_message(const std::string& hostname, uint16_t port, const std::string& uri);
	
    bool MakeTransmitData(const MessageBase* pSrcMsg);

    virtual bool MakeTextPacket(const char* data, uint32_t len);
    virtual const char* GetTextPktContent();

    virtual NetworkPacket* MakeCurrentCopy();

	int send_packet(NetHandle handle);
    int send_packet(PlatformSocket *s);

protected:
	char* _buffer;
	uint32_t _buffer_size;
	uint32_t _current_size;
};

#endif //__PACKET_H__



