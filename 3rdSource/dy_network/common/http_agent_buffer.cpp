#include "http_agent_buffer.h"
#include "string_util.h"
#include "http_defines.h"
#include "server_interface.h"
#include "platform_log.h"


HttpAgentBuffer::HttpAgentBuffer(IServerInterface* server, uint32_t capacity)
	:INetBuffer(server, capacity, true)
{
    _http_state = HttpState_Start;
    _line_start = -1;
    _http_method = HTTP_METHOD_UNKNOWN;
}

HttpAgentBuffer::~HttpAgentBuffer()
{

}

bool  HttpAgentBuffer::process_data(const SessionData& sd)
{
    if (_http_state == HttpState_Execption)
    {
        return false;
    }

    int32_t i = _start;

    if (_line_start < 0)
    {
        _line_start = _start;
    }

    while (i < _end - 1)
    {
        switch (_http_state)
        {
        case HttpState_Start:
            if (_buf[i] == '\r' && _buf[i + 1] == '\n')
            {
                const char* data = _buf + _line_start;
                const char* p = dy::strnchr((const char*)data, ' ', i - _line_start);
                if (nullptr == p)
                {
                    post_http_exception(1, sd);
                    return false;
                }
                _str_key.assign((const char*)data, p - (const char*)data);

                _method = _str_key;
                dy::to_lower(_str_key);

         /*       static std::map<std::string, HTTPMethod> key_map = {
                    {"post", HTTP_METHOD_POST},
                    {"get", HTTP_METHOD_GET},
                    {"head", HTTP_METHOD_HEAD},
                    {"connect", HTTP_METHOD_CONNECT},
                };

                auto itor = key_map.find(_str_key);*/
                if (_str_key == "connect")
                {
                    _http_method = HTTP_METHOD_CONNECT;
                }
                else
                {
                    _http_method = HTTP_METHOD_UNKNOWN;
                }
                

                const char* url = p + 1;
                p = dy::strnchr(url, ' ', i - _line_start - static_cast<int>(_str_key.size()) - 1);

                if (nullptr == p)
                {
                    post_http_exception(3, sd);
                    return false;
                }

                _location.assign(url, p - url);
                const char* cr = p + 1;
                _http_proto.assign(cr, &_buf[i] - cr);
                _http_state = HttpState_Header;
                _line_start = i + 2;
                _start = _line_start;
                i += 2;
                continue;
            }
            break;
        case HttpState_Header:
            if (_buf[i] == '\r' && _buf[i + 1] == '\n')
            {
                const char* p = dy::strnchr((const char*)(_buf + _line_start), ':', i - _line_start - 1);
                if (nullptr == p)
                {
                    if (i == _line_start)
                    {
                        process_http_header(sd);
                        _http_state = HttpState_Body;
                    }
                    else
                    {
                        post_http_exception(5, sd);
                        return false;
                    }
                    _start = i + 2;
                    i += 2;
                    continue;
                }
                else
                {
                    _str_key.clear();
                    _str_value.clear();
                    _str_key.assign((const char*)(_buf + _line_start), p - _buf - _line_start);
                    _str_value.assign((const char*)p + 2, _buf + i - p - 2);
                    _http_headers.push_back(std::pair<std::string,std::string>(_str_key, _str_value));
                    i += 2;
                    _line_start = i;
                    _start = i;
                    continue;
                }

            }
            break;
        case HttpState_Body:
            if (_end > _start)
            {
                post_http_message(_buf + _start, _end - _start, sd);
            }
            break;
        default:
            break;
        }
        i++;
    }
    return true;
}

void HttpAgentBuffer::process_http_header(const SessionData& sd)
{
    HttpContent* content = new HttpContent;
    content->methodstring = _method;
    content->location = _location;
    content->proto = _http_proto;
    content->param = sd.m_param;
    content->method = _http_method;
    content->headers = _http_headers;
    _server->post_network_message(NetMsg_HttpHeader, _net_handle, (const uint8_t*)&content, sizeof(content), sd);
}

void HttpAgentBuffer::post_http_message(const char* data, uint32_t size, const SessionData& sd)
{
    _start = 0;
    _end = 0;

    _server->post_network_message(NetMsg_HttpAgent, _net_handle, (const uint8_t*)data, size, sd);
}

void HttpAgentBuffer::post_http_exception(int magic, const SessionData& sd)
{
    WARNING_LOG("[handle:%llu,magic:%d]HttpAgentBuffer exception", _net_handle, magic);
}