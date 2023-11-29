#ifndef __HTTP_AGENT_BUFFER_H__
#define __HTTP_AGENT_BUFFER_H__

#include <stdint.h>
#include <vector>
#include <map>
#include <string>
#include <inet_session.h>
#include <net_define.h>
#include <server_def.h>
#include <http_defines.h>

class IServerInterface;


class HttpAgentBuffer :public INetBuffer
{
public:
    HttpAgentBuffer(IServerInterface* server, uint32_t capacity);
    ~HttpAgentBuffer();
public:
    virtual bool  process_data(const SessionData& sd);

private:
    void process_http_header(const SessionData& sd);
    void post_http_message(const char* data, uint32_t size, const SessionData& sd);
    void post_http_exception(int magic, const SessionData& sd);
protected:
    int32_t _body_start = -1;
    std::vector<std::pair<std::string, std::string>> _http_headers;
    std::string _method;
    std::string _location;
    std::string _http_proto;

    std::string _str_key;
    std::string _str_value;

    uint32_t _http_state;

    int32_t _line_start;

    HTTPMethod _http_method;
};

#endif //__HTTP_AGENT_BUFFER_H__