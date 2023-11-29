#ifndef __HTTP_BUFFER_H__
#define __HTTP_BUFFER_H__

#include <stdint.h>
#include <map>
#include <string>
#include <inet_session.h>
#include <net_define.h>
#include <server_def.h>

class IServerInterface;


class HttpBuffer:public INetBuffer
{
public:
	HttpBuffer(IServerInterface* server, uint32_t capacity);
	~HttpBuffer();
public:
	virtual bool  process_data(const SessionData& sd);
	//after response to httpReq, call this to ready for another req; 
	virtual void conn_reusing() { _can_post = true; }
private:
	void post_http_message(const char* data, uint32_t size, const SessionData& sd);
    void post_http_exception(int magic, const SessionData& sd);
protected:  
    uint32_t _body_start;
    uint32_t _body_full_length;
  
    uint32_t _http_state;
    bool     _can_post;

    std::map<std::string, std::string> _http_header_map;
	std::string _location;
    std::string _http_proto;
    
    int32_t _line_start;
    uint32_t _http_method;
    
    std::string _str_key;
    std::string _str_value;
};

#endif //__HTTP_BUFFER_H__