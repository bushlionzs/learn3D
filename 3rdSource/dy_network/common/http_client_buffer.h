#ifndef __HTTP_CLIENT_BUFFER_H__
#define __HTTP_CLIENT_BUFFER_H__

#include <stdint.h>
#include <map>
#include <string>
#include <inet_session.h>
#include <net_define.h>
#include <server_def.h>

#include "http_defines.h"

class IServerInterface;


class HttpClientBuffer:public INetBuffer
{
public:
	HttpClientBuffer(IServerInterface* server, uint32_t capacity, bool continue_data = false);
	~HttpClientBuffer();
public:
	virtual bool  process_data(const SessionData& sd);
    virtual void data_reset();
    virtual void reset();
private:
    void split_message();
	void post_http_message(const char* data, uint32_t size, const SessionData& sd);
    void post_http_exception(int magic);
    void on_recv_status_line();
    void on_recv_http_headers();
protected:
    int32_t  _line_start;
    uint32_t _body_start;
    uint32_t _body_offset;
    uint32_t _body_left;
    uint32_t _body_full_length;
    uint32_t _chunk_start;
    uint32_t _chunk_body_start;
    uint32_t _chunk_size;
    std::string _str_body;
    
    uint32_t _http_state;
    int32_t  _last_parse_pos;
    std::map<std::string, std::string> _http_header_map;
    HTTPStatusLine _status_line;

    bool _continue_data;
};

#endif //__HTTP_CLIENT_BUFFER_H__