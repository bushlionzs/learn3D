//#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
//#include <sys/time.h>
#include <string.h>
#include <net_handle.h>
#include <platform_common.h>
#include <platform_log.h>
#include <server_def.h>
#include <net_header.h>
#include <server_interface.h>
#include "string_util.h"
#include "http_session.h"
#include "http_client_buffer.h"
#include "http_util.h"

#define MAX_CAPACITY (1024 * 128)


//////////////////////////////////////////////////////////////////////////////
HttpClientBuffer::HttpClientBuffer(IServerInterface* server, uint32_t capacity, bool continue_data)
:INetBuffer(server, capacity, true)
{
    _http_state = HttpState_Start;
    _line_start = -1;
    _last_parse_pos = -1;
    _body_offset = 0;
    _continue_data = continue_data;
}

HttpClientBuffer::~HttpClientBuffer()
{

}

bool HttpClientBuffer::process_data(const SessionData& sd)
{
    if (_http_state == HttpState_Execption)
    {
        return false;
    }

	if (_http_state == HttpState_ChunkFull)
	{
		return true;
	}

    if(_last_parse_pos < 0)
    {
        _last_parse_pos = _start;
    }
    uint32_t i = _last_parse_pos;

    std::string str_header;
    std::string str_value;

    if (_line_start < 0)
    {
        _line_start = _start;
    }

    while (i < _end)
    {
        switch(_http_state)
        {
            case HttpState_Start:
                _http_header_map.clear();

                if (i + 1 >= _end)
                {
                    _last_parse_pos = i;
                    return true;
                }

                if (_buf[i] == '\r' && _buf[i+1] == '\n')
                {
                    if (parse_http_status_line(_buf + _line_start, _buf + i, &_status_line))
                    {
                        _http_state = HttpState_Header;
                        i += 2;
                        _line_start = i;

                        on_recv_status_line();
                        continue;
                    }
                    else
                    {
                        post_http_exception(1);
                        return false;
                    }
                }
            break;
            case HttpState_Header:
                if (i + 1 >= _end)
                {
                    _last_parse_pos = i;
                    return true;
                }

                if (_buf[i] == '\r' && _buf[i+1] == '\n')
                {
                    const char* p = dy::strnchr((const char*)(_buf + _line_start), ':', i - _line_start - 1);
                    if (NULL == p)
                    {
                        if (i == _line_start)
                        {
                            //header eof
                            auto itor = _http_header_map.find("transfer-encoding");
                            if (itor != _http_header_map.end())
                            {
                                if (itor->second == "chunked")
                                {
                                    _http_state = HttpState_ChunkSize;
                                    _chunk_start = i + 2;
                                    i += 2;
                                    _str_body.clear();

                                    on_recv_http_headers();
                                    continue;
                                }
                                else
                                {
                                    post_http_exception(2);
                                    return false;
                                }
                            }
                            else
                            {
                                auto itor2 = _http_header_map.find("content-length");
                                if (itor2 != _http_header_map.end())
                                {
                                    _http_state = HttpState_Body;
                                    _body_full_length = atoi(itor2->second.c_str());
                                    DEBUG_LOG("[handle:%" PRIu64 ", size:%d]http client buffer",
                                        _net_handle, _body_full_length);
                                    _body_start = i + 2;
                                    _body_offset = _body_start;
                                    _body_left = _body_full_length;
                                    _chunk_size = 0;
                                    i += 2;

                                    on_recv_http_headers();

                                    if (0 == _body_full_length)
                                    {
                                        post_http_message(0, 0, sd);
                                        return true;
                                    }
                                    else
                                    {
                                        continue;
                                    }

                                }
                                else
                                {
                                    if (!_http_header_map.empty())
                                    {
                                        post_http_exception(3);
                                        return false;
                                    }
                                    
                                }
                            }
                        }
                        else
                        {
                            post_http_exception(4);
                            return false;
                        }
                    }
                    else
                    {
                        str_header.clear();
                        str_value.clear();
                        str_header.assign((const char*)(_buf + _line_start), p - _buf - _line_start);
                        str_value.assign((const char*)p + 2, _buf + i - p - 2);
                        dy::to_lower(str_header);

#ifdef USE_HTTP_CLIENT_MULTI_HEADERS
                        auto header_insert = _http_header_map.emplace(str_header, str_value);
                        if (!header_insert.second)
                        {
                            auto && header_value = header_insert.first->second;
                            header_value.append("\r\n");
                            header_value += str_value;
                        }
#else
                        _http_header_map[str_header] = str_value;
#endif

                        i += 2;
                        _line_start = i;
                        continue;
                    }

                }
            break;
            case HttpState_Body:
                if (_continue_data)
                {
                    if (_end > _body_offset)
                    {
                        if (_body_left > 0)
                        {
                            uint32_t last = _end;

                            if (_body_offset + _body_left < last)
                            {
                                last = _body_offset + _body_left;
                            }
                            post_http_message(_buf + _body_offset, last - _body_offset, sd);
                            _body_left -= last - _body_offset;
                            _body_offset = last;
                            _start = _end;
                            _last_parse_pos = -1;


                            if (0 == _body_left)
                            {
                                post_http_message(_buf, 0, sd);
                            }

                        }
                        else
                        {

                        }
                    }
                }
                else
                {
                    if (_end >= _body_start + _body_full_length)
                    {
                        post_http_message(_buf + _body_start, _body_full_length, sd);
                    }
                }

                return true;
            break;
            case HttpState_ChunkSize:
            {
                if (i + 1 >= _end)
                {
                    _last_parse_pos = i;
                    return true;
                }

                if (_buf[i] == '\r' && _buf[i+1] == '\n')
                {
                    _buf[i] = 0;
                    char * stop;
                    _chunk_size = strtol((const char*)(_buf + _chunk_start), &stop, 16);
                    _buf[i] = '\r';
                    if (0 == _chunk_size)
                    {
                        _http_state = HttpState_ChunkFull;
                        break;
                    }
                    _chunk_body_start = i + 2;
                    i += 2;
                    _http_state = HttpState_ChunkBody;
                    continue;
                }
            }
            break;
            case HttpState_ChunkBody:
            {
               if (_chunk_body_start + _chunk_size + 2 <= _end)
               {
                   i = _chunk_body_start + _chunk_size + 2;
                   _chunk_start = i;
                   if (_continue_data)
                   {
                       post_http_message(_buf + _chunk_body_start, _chunk_size, sd);
                       _start = i;
                   }
                   else
                   {
                       _str_body.append(_buf + _chunk_body_start, _chunk_size);
                   }

                   _http_state = HttpState_ChunkSize;

                   continue;
               }
            }
            break;
            default:
            break;
        }
        i++;
        if (_http_state == HttpState_ChunkFull)
        {
            post_http_message(_str_body.c_str(), static_cast<uint32_t>(_str_body.size()), sd);
			_http_header_map.clear();
            return true;
        }
    }
    _last_parse_pos = i;
	return true;
}

void HttpClientBuffer::data_reset()
{
    if (_continue_data)
    {
        switch (_http_state)
        {
        case HttpState_Body:
            _body_offset = 0;
            _last_parse_pos = 0;
            break;
        case HttpState_ChunkSize:
            _last_parse_pos = 0;
            _chunk_start -= _start;
            break;
        case HttpState_ChunkBody:
            _last_parse_pos = 0;
            _chunk_body_start -= _start;
            break;
        }
    }
}

void HttpClientBuffer::reset()
{
    _http_state = HttpState_Start;
    _line_start = -1;
    _last_parse_pos = -1;
    _body_offset = 0;
    _start = _end = 0;
}

void HttpClientBuffer::post_http_message(const char* data, uint32_t size, const SessionData& sd)
{
    _server->post_network_message(NetMsg_HttpDataResponse, _net_handle, (const uint8_t*)data, size);

    if (0 == size || !_continue_data)
    {
        _start = 0;
        _end = 0;
        _http_state = HttpState_Start;
        _last_parse_pos = -1;
        _line_start = -1;
        _body_offset = 0;
    }
}

void HttpClientBuffer::post_http_exception(int magic)
{
    _server->post_network_message(NetMsg_HttpException, _net_handle, 0, 0);
    _http_state = HttpState_Execption;
}

void HttpClientBuffer::on_recv_status_line()
{
    const HTTPStatusLine* status_line_copy = new HTTPStatusLine(_status_line);

    _server->post_network_message(NetMsg_HttpReponse_StatusLine, _net_handle,
        (const uint8_t*)(&status_line_copy), sizeof(status_line_copy));
}

void HttpClientBuffer::on_recv_http_headers()
{
    const HTTPHeaders* headers_copy = new HTTPHeaders(_http_header_map);

    _server->post_network_message(NetMsg_HttpReponse_Headers, _net_handle,
        (const uint8_t*)(&headers_copy), sizeof(headers_copy));
}
