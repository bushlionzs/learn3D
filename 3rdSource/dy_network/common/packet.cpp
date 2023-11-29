#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <common_base64.h>
#include "packet.h"
#include "platform_log.h"
#include "net_header.h"
#include "websocket_buffer.h"
#include "platform_socket.h"


NetworkPacket::NetworkPacket(uint32_t size)
{
    _buffer_size = size;
    //_buffer = (char*)malloc(_buffer_size);
    _buffer = new char[_buffer_size];
    _current_size = 0;
}

NetworkPacket::~NetworkPacket()
{
    if (_buffer)
    {
        delete [] _buffer;
        _buffer = NULL;
    }
}

bool NetworkPacket::GenerateMessage(const char* data , uint32_t size)
{
	_current_size = size + sizeof(uint32_t);
    if (_current_size > _buffer_size)
    {
        _current_size = 0;
        return false;
    }
    memmove(_buffer + sizeof(uint32_t), data, size);
    *((uint32_t*)_buffer) = size;
    return true;
}

bool NetworkPacket::GenerateMessage(uint16_t msg_id, const char* data , uint32_t size)
{
    _current_size = size + sizeof(NetHeader);
    if (_current_size > _buffer_size)
    {
        _current_size = 0;
        return false;
    }
    memmove(_buffer + sizeof(NetHeader), data, size);
    NetHeader* header = (NetHeader*)(_buffer);
    memset(header, 0, sizeof(NetHeader));
    header->mMsgId = htonl(msg_id);
	header->mMsgLength = htonl(size);
    return true;
}

bool NetworkPacket::GenerateWebsocketMessage(uint8_t type, const char* data, uint32_t size, bool is_mask)
{
    WebSocketEncoder encodeBuff(_buffer, _buffer_size);
    // 1st byte
    char FINandRSVandOpcode = 0x80 | type; // FIN = 1, opcode 为0x2（二进制数据类型）
    if (false == encodeBuff.encode(&FINandRSVandOpcode, sizeof(FINandRSVandOpcode)))
    {
        return false;
    }
    // 2st byte
    char payloadLen = 0;
    
    uint32_t full_size = size;
    if(full_size <= 125)
    {
        payloadLen = full_size;
    }
    else if(full_size <= 65535)
    {
        payloadLen = 126;
    }
    else
    {
        payloadLen = 127;
    }
    char isMaskAndPayloadLen = ((is_mask? 1:0) << 7) | payloadLen; // mask是最高位，为0，下行消息不加密
    if (false == encodeBuff.encode(&isMaskAndPayloadLen, sizeof(isMaskAndPayloadLen)))
    {
        return false;
    }
    // extendLen
    if(payloadLen == 126)
    {
        uint16_t extendLen = full_size;
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 1, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen), 1))
        {
            return false;
        }
    }
    else if(payloadLen == 127)
    {
        uint64_t extendLen = full_size;
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 7, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 6, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 5, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 4, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 3, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 2, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen) + 1, 1))
        {
            return false;
        }
        
        if (false == encodeBuff.encode(reinterpret_cast<const char*>(&extendLen), 1))
        {
            return false;
        }
    }
    uint8_t mask[4] = { 0xa0, 0xbc, 0x62, 0x9c };
    // mask
    if(isMaskAndPayloadLen & 0x80)
    {
        if (false == encodeBuff.encode(mask, sizeof(mask)))
        {
            return false;
        }
        if (false == encodeBuff.encode_mask(data, size, &mask[0]))
        {
            return false;
        }
    }
    else
    {
        if (false == encodeBuff.encode(data, size))
        {
            return false;
        }
    }
    
    _current_size = encodeBuff.getEncodedSize();
    return true;
}


bool NetworkPacket::build_websocket_request_message(const std::string& hostname, uint16_t port, const std::string& uri)
{
    std::ostringstream oss;
    std::string  tmp = base64_encode_random(16);
    oss << "GET " << uri << " HTTP/1.1\r\nHost: " << hostname << ":" << port << "\r\n";
    oss << "Connection: Upgrade\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nUser-Agent: Douyu Websocket Client\r\n";
    oss << "Upgrade: websocket\r\n" << "Origin: http://www.douyucdn.cn:8080\r\nSec-Websocket-Version: 13\r\nAccept-Encoding: gzip, deflate\r\n" << "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n";
    oss << "Sec-WebSocket-Key: " << tmp << "\r\nSec-WebSocket-Extensions: permessage-deflate; client_max_window_bits" <<"\r\n\r\n";
    tmp = oss.str();

    if (tmp.size() > _buffer_size)
    {
        return false;
    }

    _current_size = static_cast<uint32_t>(tmp.size());
    memmove(_buffer, tmp.c_str(), _current_size);
    return true;
}

bool NetworkPacket::MakeTextPacket(const char* data, uint32_t len)
{
    return false;
}

const char* NetworkPacket::GetTextPktContent()
{
    return NULL;
}

NetworkPacket* NetworkPacket::MakeCurrentCopy()
{
    NetworkPacket* pSnapshot = new NetworkPacket(_current_size);
    memmove(pSnapshot->get_mutable_buffer(), _buffer, _current_size);
    pSnapshot->set_size(_current_size);

    return pSnapshot;
}

int NetworkPacket::send_packet(NetHandle handle)
{
	int ret = NetFactory::GetInstance()->SendData(handle, (const uint8_t*)_buffer, _current_size);
    if (ret != 0)
    {
        WARNING_LOG("[handle:%" PRIu64 ",ret:%d]send packet error", handle, ret);
    }
    return ret;
}

int NetworkPacket::send_packet(PlatformSocket *s)
{
    int32_t ret = s->Send((const uint8_t*)_buffer, _current_size, nullptr);
    if (ret != 0)
    {
        WARNING_LOG("[handle:%p,ret:%d]send packet error", this, ret);
    }
    return ret;
}

