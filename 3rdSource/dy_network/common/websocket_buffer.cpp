#include "websocket_buffer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <platform_log.h>
#include <platform_util.h>
#include "net_handle.h"
#include "platform_common.h"
#include "server_def.h"
#include "net_header.h"
#include "server_interface.h"
#include "http_session.h"
#include "http_defines.h"
#include "string_util.h"


const uint8_t WEBSOCKET_DATA_TYPE_CONTINUE  = 0;
const uint8_t WEBSOCKET_DATA_TYPE_TEXT      = 1;
const uint8_t WEBSOCKET_DATA_TYPE_BINARY    = 2;
constexpr uint64_t WEBSOCKET_MAX_BODY_SIZE = 0XFFFF;

static IPlatformModule* _websocket_module = NULL;

static void websocket_init()
{
}
static uint32_t websocket_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pNetThreadData)
{
    NetHandle h = (NetHandle)param;
    if(msg != NULL)
    {
        NetFactory::GetInstance()->SendData(h, (const uint8_t*)msg, msg_size, NULL);
    }
    return 0;
}

void WebsocketBuffer::websocket_thread_init()
{
    _websocket_module = create_platform_module(1, "ws_ping_pong");
    _websocket_module->attach_module(0, websocket_init, websocket_entry, NULL);
    _websocket_module->run_module();
}

void WebsocketBuffer::websocket_thread_uninit()
{
    destory_platform_module(_websocket_module);
    _websocket_module = nullptr;
}

static void post_private_websocket_message(NetHandle h, const uint8_t* data, uint32_t size)
{
    _websocket_module->post_module_message(0, 0, 0, h, data, size);
}

//////////////////////////////////////////////////////////////////////////////
WebsocketBuffer::WebsocketBuffer(IServerInterface* server, uint32_t capacity)
:INetBuffer(server, capacity, true)
{
    _http_state = HttpState_Start;
    _http_method = 0;
    _is_handshake = false;
    _is_fragment = false;
    _fragment_net_idx = 0;
}

WebsocketBuffer::~WebsocketBuffer()
{
}

bool WebsocketBuffer::process_data(const SessionData& sd)
{    
    if (0 != process_handshake(sd))
    {
        return true;
    }
     
    uint32_t index = 0;
    bool is_close_frame = false;
    bool is_ping_pong = false;

    while (_start < _end)
    {
        if (_start + index + 2 > _end)
        {
            return true;
        }
        
        memset(&_ws_head, 0, sizeof(_ws_head));
        uint8_t first   = _buf[_start + index];
        uint8_t second  = _buf[_start + index + 1];
        uint8_t fin = first & 0x80;
        
        index += 2;
        
        _ws_head.opcode   = first & 0xF;
        _ws_head.isMasked = second & 0x80;
        _ws_head.bytePayloadLen = second & 0x7F;
        
        if (_ws_head.bytePayloadLen <= 125)
        {
            _ws_head.msgBodySize = _ws_head.bytePayloadLen;
        }
        else if (_ws_head.bytePayloadLen == 126)
        {
            if (_start + index + 2 > _end)
            {
                return true;
            }
            ((char*)&_ws_head.msgBodySize)[0] = _buf[_start + index + 1];
            ((char*)&_ws_head.msgBodySize)[1] = _buf[_start + index + 0];
            index += 2;
        }
        else if(_ws_head.bytePayloadLen == 127)
        {
            if (_start + index + 8 > _end)
            {
                return true;
            }
            ((char*)&_ws_head.msgBodySize)[0] = _buf[_start + index + 7];
            ((char*)&_ws_head.msgBodySize)[1] = _buf[_start + index + 6];
            ((char*)&_ws_head.msgBodySize)[2] = _buf[_start + index + 5];
            ((char*)&_ws_head.msgBodySize)[3] = _buf[_start + index + 4];
            ((char*)&_ws_head.msgBodySize)[4] = _buf[_start + index + 3];
            ((char*)&_ws_head.msgBodySize)[5] = _buf[_start + index + 2];
            ((char*)&_ws_head.msgBodySize)[6] = _buf[_start + index + 1];
            ((char*)&_ws_head.msgBodySize)[7] = _buf[_start + index + 0];
            index += 8;
        }
        else
        {
            WARNING_LOG("bytePayloadLen error[%d]", _ws_head.bytePayloadLen);
            _server->post_network_message(NetMsg_WebSocket_Exception, _net_handle, 0, 0, sd);
            return false;
        }

        if (_ws_head.msgBodySize > WEBSOCKET_MAX_BODY_SIZE)
        {
            WARNING_LOG("msgBodySize error size=%" PRIu64, _ws_head.msgBodySize);
            _server->post_network_message(NetMsg_WebSocket_Exception, _net_handle, 0, 0, sd);
            return false;
        }
        
        if (_start + index + 4 > _end)
        {
            return true;
        }
        
        if (_ws_head.isMasked)
        {
            memmove((char*)_ws_head.mask, (const char*)(_buf + _start + index), 4);
            index += 4;
        }
        
        if (_ws_head.opcode == WEBSOCKET_DATA_TYPE_TEXT || _ws_head.opcode == WEBSOCKET_DATA_TYPE_BINARY)
        {
            if (_ws_head.msgBodySize > _end - (_start + index))
            {
                return true;
            }
            
            int msg = NetMsg_WebSocket_Data;
            if (0 == fin)
            {
                //first fragment
                _is_fragment = true;
                msg = NetMsg_WebSocket_Fragment;
            }
            else
            {
                if (_is_fragment)
                {
                    WARNING_LOG("_is_fragment error,%d", _end - _start);
                    _server->post_network_message(NetMsg_WebSocket_Exception, _net_handle, 0, 0, sd);
                    return true;
                }
            }
            
            
            char* body = _buf + _start + index;
            if (_ws_head.isMasked)
            {
                for(uint32_t i = 0; i < _ws_head.msgBodySize; ++i)
                {
                    body[i] ^= _ws_head.mask[i % 4];
                }
            }
            index += static_cast<uint32_t>(_ws_head.msgBodySize);
            _server->post_network_message(msg, _net_handle, (const uint8_t*)body, static_cast<uint32_t>(_ws_head.msgBodySize), sd);
        }
        else if (_ws_head.opcode == WEBSOCKET_DATA_TYPE_CONTINUE)
        {
            if (_ws_head.msgBodySize > _end - (_start + index))
            {
                return true;
            }
            
            if (!_is_fragment)
            {
                WARNING_LOG("websocket continue fragment exception,%d", _end - _start);
                _server->post_network_message(NetMsg_WebSocket_Exception, _net_handle, 0, 0, sd);
                return false;
            }
            
            char* body = _buf + _start + index;
            if (_ws_head.isMasked)
            {
                for(uint32_t i = 0; i < _ws_head.msgBodySize; ++i)
                {
                    body[i] ^= _ws_head.mask[i % 4];
                }
            }
            
            int msg = NetMsg_WebSocket_Fragment;
            
            if (0 != fin)
            {
                msg = NetMsg_WebSocket_Fragment_Eof;
                _is_fragment = false;
            }
            index += static_cast<uint32_t>(_ws_head.msgBodySize);
            _server->post_network_message(msg, _net_handle, (const uint8_t*)body, static_cast<uint32_t>(_ws_head.msgBodySize), sd);
        }
        else if (_ws_head.opcode == 0x8)
        {
            is_close_frame = true;
        }
        else if (_ws_head.opcode == 0x9)
        {
            DEBUG_LOG("[handle:%" PRIu64 "]send pong frame", _net_handle);

            is_ping_pong = true;

        }
        else if (_ws_head.opcode == 0xA)
        {
            //recv pong frame
            DEBUG_LOG("[handle:%" PRIu64 "]recv pong frame", _net_handle);
        }
        else
        {
            WARNING_LOG("[opcode:%d, handle:%" PRIu64 "]recv unkown opcode", _ws_head.opcode, _net_handle);
            return false;
        }
        
        _start += index;
        index = 0;
    }
    

    if (is_close_frame)
    {
        post_ws_close_message(sd);
    }

    if (is_ping_pong)
    {
        send_pong_frame();
    }

    if (_start == _end)
    {
        _start = _end  = 0;
    }
	return true;
}


int WebsocketBuffer::process_handshake(const SessionData& sd)
{
    if (_is_handshake)
    {
        return 0;
    }
    
    if (_end - _start <= 4)
    {
        return -1;
    }
    
    for (uint32_t i = _start; i < _end - 3; i++)
    {
        if (_buf[i] == '\r' && _buf[i+1] == '\n' && _buf[i+2] == '\r' && _buf[i+3] == '\n')
        {
            websocket_http_header_t* ws_http_header = new websocket_http_header_t;
            process_lines((const char*)_buf, i + 2 - _start, ws_http_header);
            _start = i + 4;
            if (_start == _end)
            {
                _start = _end = 0;
            }
            _is_handshake = true;
            _server->post_network_message(NetMsg_Websokcet_HandShake, _net_handle, (const uint8_t*)&ws_http_header, sizeof(ws_http_header), sd);
            
            return 0;
        }
    }
    return -1;
}

int WebsocketBuffer::process_lines(const char* data, uint32_t size, websocket_http_header_t* ws_http_header)
{       
    const char* start = data;
    for (uint32_t i = 0; i < size - 2; i++)
    {
        if (data[i] == '\r' && data[i+1] == '\n')
        {
            const char* find = dy::strnchr(start, ':', static_cast<int>(data + i - start));
            if (find && find[1] == ' ')
            {
                std::string key;
                std::string value;
                key.assign(start, find - start);
                value.assign(find + 2, data + i - find - 2);
                dy::to_lower(key);
                if (key == "sec-websocket-key")
                {
                    ws_http_header->_sec_websocket_key = value;
                }
                else if(key == "origin")
                {
                    ws_http_header->_origin = value;
                }
            }
            start = data + i + 2;
        }
    }
    return 0;
}

void WebsocketBuffer::OnRecvSingleMessage(const uint8_t* data, uint32_t size)
{
	HttpContent* content = new HttpContent;
	content->location = location;
	content->body.assign((const char*)data, size);
	_server->post_network_message(NetMsg_HttpData, _net_handle, (const uint8_t*)&content, sizeof(content));
    
	_start	= 0;
	_end		= 0;
    _http_state = HttpState_Start;
    _http_method = 0;
}

#define WEBSOCKET_BUFFER_SIZE 1024
bool WebsocketBuffer::send_close_frame()
{
    char buff[WEBSOCKET_BUFFER_SIZE];
    WebSocketEncoder encodeBuff(buff, WEBSOCKET_BUFFER_SIZE);

    // 1st byte
    unsigned char FINandRSVandOpcode = 0x80 | 0x8; // FIN = 1, opcode 为0x2（二进制数据类型）
    encodeBuff.encode(&FINandRSVandOpcode, sizeof(FINandRSVandOpcode));
    // 2st byte
    char payloadLen = 0;
    char isMaskAndPayloadLen = 0x00 | payloadLen; // mask是最高位，为0，下行消息不加密
    encodeBuff.encode(&isMaskAndPayloadLen, sizeof(isMaskAndPayloadLen));
    post_private_websocket_message(_net_handle, (const uint8_t*)buff, encodeBuff.getEncodedSize());
    return true;
}

bool WebsocketBuffer::send_pong_frame()
{
    char buff[WEBSOCKET_BUFFER_SIZE];
    WebSocketEncoder encodeBuff(buff, WEBSOCKET_BUFFER_SIZE);

    // 1st byte
    char FINandRSVandOpcode = 0x00 | 0xA; // FIN = 1, opcode 为0x2（二进制数据类型）
    encodeBuff.encode(&FINandRSVandOpcode, sizeof(FINandRSVandOpcode));
    // 2st byte
    char payloadLen = 0;
    char isMaskAndPayloadLen = 0x00 | payloadLen; // mask是最高位，为0，下行消息不加密
    encodeBuff.encode(&isMaskAndPayloadLen, sizeof(isMaskAndPayloadLen));
    post_private_websocket_message(_net_handle, (const uint8_t*)buff, encodeBuff.getEncodedSize());
    return true;
}

void WebsocketBuffer::post_ws_close_message(const SessionData& sd)
{
    _server->post_network_message(NetMsg_WebSocket_Close, _net_handle, 0, 0, sd);
}

