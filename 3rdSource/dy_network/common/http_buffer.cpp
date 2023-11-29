//#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <sys/time.h>

#include "net_handle.h"
#include "platform_common.h"
#include "platform_log.h"
#include "http_buffer.h"
#include "server_def.h"
#include "net_header.h"
#include "server_interface.h"
#include "http_session.h"
#include "http_defines.h"
#include "platform_util.h"
#include "string_util.h"

//////////////////////////////////////////////////////////////////////////////
HttpBuffer::HttpBuffer(IServerInterface* server, uint32_t capacity):
INetBuffer(server, capacity, true)
{
    _http_state = HttpState_Start;
    _http_method = -1;
    _line_start = -1;
    _can_post = true;
}

HttpBuffer::~HttpBuffer()
{
}

bool HttpBuffer::process_data(const SessionData& sd)
{
    if (_http_state == HttpState_Execption)
    {
        return false;
    }
    uint32_t i = _start;
    
    if (_line_start < 0)
    {
        _line_start = _start;
    }

    while (i < _end - 1)
    {
        switch(_http_state)
        {
            case HttpState_Start:
                if (_buf[i] == '\r' && _buf[i+1] == '\n')
                {
                    const char* data = _buf + _line_start;
                    const char* p = dy::strnchr((const char*)data, ' ', i - _line_start);
                    if (NULL == p)
                    {
                        post_http_exception(1, sd);
                        return false;
                    }
                    _str_key.assign((const char*)data, p - (const char*)data);
                    dy::to_lower(_str_key);
                    if (_str_key == "post")
                    {
                        _http_method = 1;
                    }
                    else if(_str_key == "get")
                    {
                        _http_method = 0;
                    }
                    else
                    {
                        post_http_exception(2, sd);
                        return false;
                    }
                    
                    const char *url = p + 1;
                    p = dy::strnchr(url, ' ', i - _line_start - static_cast<int>(_str_key.size()) - 1);
                    
                    if (NULL == p)
                    {
                        post_http_exception(3, sd);
                        return false;
                    }
                    
                    _location.assign(url, p - url);
                    const char* cr = p+1;
                    _http_proto.assign(cr, &_buf[i] - cr);
                    _http_state = HttpState_Header;
                    _line_start = i + 2;
					_start = _line_start;
                }
            break;
            case HttpState_Header:
                if (_buf[i] == '\r' && _buf[i+1] == '\n')
                {
                    const char* p = dy::strnchr((const char*)(_buf + _line_start), ':', i - _line_start - 1);
                    if (NULL == p)
                    {
                        if (i == _line_start)
                        {
                            //header eof
                            if (1 == _http_method)
                            {
                                auto itor2 = _http_header_map.find("content-length");
                                if (itor2 != _http_header_map.end())
                                {
                                    _http_state = HttpState_Body;
                                    int content_length = atoi(itor2->second.c_str());
                                    if (content_length >= 0)
                                    {
                                        _body_full_length = content_length;
                                        _body_start = i + 2;
                                        _start = _body_start;
                                        i += 2;
                                        continue;
                                    }

                                    WARNING_LOG(
                                        "[nethandle:%" PRIu64 "]bad content_length:%d",
                                        _net_handle,
                                        content_length
                                    );
                                }

                                post_http_exception(4, sd);
                                return false;
                            }
                            else
                            {

                                _http_state = HttpState_Body;
                                post_http_message(NULL, 0, sd);
                                return true;
                            }
                        }
                        else
                        {
                            post_http_exception(5, sd);
                            return false;
                        }
                    }
                    else
                    {
                        _str_key.clear();
                        _str_value.clear();
                        _str_key.assign((const char*)(_buf + _line_start), p - _buf - _line_start);
                        _str_value.assign((const char*)p + 2, _buf + i - p - 2);
                        dy::to_lower(_str_key);
                        _http_header_map[_str_key] = _str_value;
                        i += 2;
                        _line_start = i;
                        continue;
                    }
                    
                }
            break;
            case HttpState_Body:
                if (_end >= _body_start + _body_full_length)
                {
                    post_http_message(_buf + _body_start, _body_full_length, sd);
                    return true;
                }
                else
                {
                    return true;
                }
            break;
            default:
            break;
        }
        i++;
    }
	return true;
}
    
void HttpBuffer::post_http_message(const char* data, uint32_t size, const SessionData& sd)
{
	HttpContent* content = new HttpContent;
	content->location = _location;
    content->proto = _http_proto;
    content->param = sd.m_param;

    if (data)
    {
        content->body.assign((const char*)data, size);
    }

    content->peer_ip = sd.m_PeerIP;
    content->peer_port = sd.m_PeerPort;
    content->local_port = sd.m_LocalPort;

    if(_server->is_http_multi_req() || _can_post)
    {
        content->is_reuse = !_can_post;
        _server->post_network_message(NetMsg_HttpData, _net_handle, (const uint8_t*)&content, sizeof(content), sd);
        _can_post = false;
    }
    else
    {
        WARNING_LOG("[nethandle:%" PRIu64 "]un-reused http-session,drop req:'%s'", _net_handle, _location.c_str());
    }

	_start	= 0;
	_end    = 0;
    _http_state = HttpState_Start;
    _http_method = -1;
    _line_start = -1;
}

void HttpBuffer::post_http_exception(int magic, const SessionData& sd)
{
    WARNING_LOG("[nethandle:%" PRIu64 ",magic:%d]pase http exception", _net_handle, magic);
    _server->post_network_message(NetMsg_HttpException, _net_handle, 0, 0, sd);
    _http_state = HttpState_Execption;
}
