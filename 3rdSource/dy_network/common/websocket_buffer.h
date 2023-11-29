#ifndef __WEBSOCKET_BUFFER_H__
#define __WEBSOCKET_BUFFER_H__

#include <stdint.h>
#include <map>
#include <string>
#include <inet_session.h>
#include <net_define.h>
//#include <server_def.h>

class IServerInterface;

struct websocket_head_t
{
    bool FIN;
    uint8_t opcode;
    bool isMasked;
    uint8_t bytePayloadLen;
    uint64_t msgBodySize;

    bool maskGetted;
    uint8_t mask[4];
};

struct websocket_http_header_t
{
    std::string _sec_websocket_key;
    std::string _origin;
};

class WebSocketEncoder
{
    public:
        WebSocketEncoder(char* buffer, uint32_t size) : _buffer(buffer), _size(size), _write_pos(0)
        {
        }
        ~WebSocketEncoder()
        {
        }
        inline bool encode(const void* data, uint32_t size)
        {
            if(getRemainSize() < size)
            {
                return false;
            }
            memmove(_buffer + _write_pos, data, size);
            _write_pos += size;
            return true;
        }

        inline bool encode_mask(const char* data, uint32_t size, uint8_t* mask)
        {
            if (getRemainSize() < size)
            {
                return false;
            }
            for (uint32_t i = 0; i < size; i++)
            {
                _buffer[_write_pos + i] = data[i] ^ mask[i % 4];
            }
            _write_pos += size;
            return true;
        }
        inline uint32_t getRemainSize() const
        {
            return _size - _write_pos;
        }
        inline uint32_t getEncodedSize() const
        {
            return _write_pos;
        }
    private:
        char* _buffer;
        uint32_t _size;
        uint32_t _write_pos;
};
    
class WebsocketBuffer:public INetBuffer
{
public:
    static void websocket_thread_init();
    static void websocket_thread_uninit();
public:
	WebsocketBuffer(IServerInterface* server, uint32_t capacity);
	~WebsocketBuffer();
public:
	virtual bool  process_data(const SessionData& sd);
	void ReleaseData(uint32_t size);
    void set_handshake(bool shake)
    {
        _is_handshake = shake;
    }
private:
    void split_message();
    int process_lines(const char* data, uint32_t size, websocket_http_header_t* ws_http_header);
    int process_handshake(const SessionData& sd);
	void OnRecvSingleMessage(const uint8_t* data, uint32_t size);
    bool send_close_frame();
    bool send_pong_frame();
    void post_ws_close_message(const SessionData& sd);
protected:
    uint32_t _body_start;
    uint32_t _body_full_length;
    
    uint32_t _http_state;
    
    std::map<std::string, std::string> _http_header_map;
	std::string location;
    uint32_t _http_method;

    bool _is_handshake;
    websocket_head_t _ws_head;
    
    bool _is_fragment;
    int _fragment_net_idx;
};

#endif //__WEBSOCKET_BUFFER_H__