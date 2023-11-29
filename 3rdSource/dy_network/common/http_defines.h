#ifndef _HTTP_DEFINES_H_INCLUDED
#define _HTTP_DEFINES_H_INCLUDED

#include <map>
#include <vector>
#include <string>


enum HTTPMethod
{
    HTTP_METHOD_UNKNOWN = 0,
    HTTP_METHOD_GET,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_POST,
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_MKCOL,
    HTTP_METHOD_COPY,
    HTTP_METHOD_MOVE,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_PROPFIND,
    HTTP_METHOD_PROPPATCH,
    HTTP_METHOD_LOCK,
    HTTP_METHOD_UNLOCK,
    HTTP_METHOD_PATCH,
    HTTP_METHOD_TRACE
};


enum HTTPStatusCode
{
    HTTP_STATUS_CODE_UNKNOWN                    = 0,

    /* 1xx */
    HTTP_STATUS_CODE_CONTINUE                   = 100,
    HTTP_STATUS_CODE_SWITCHING_PROTOCOLS        = 101,
    HTTP_STATUS_CODE_SWITCHING_PROCESSING       = 102,

    /* 2xx */
    HTTP_STATUS_CODE_OK                         = 200,
    HTTP_STATUS_CODE_CREATED                    = 201,
    HTTP_STATUS_CODE_ACCEPTED                   = 202,
    HTTP_STATUS_CODE_NO_CONTENT                 = 204,
    HTTP_STATUS_CODE_PARTIAL_CONTENT            = 206,

    /* 3xx */
    HTTP_STATUS_CODE_SPECIAL_RESPONSE           = 300,
    HTTP_STATUS_CODE_MOVED_PERMANENTLY          = 301,
    HTTP_STATUS_CODE_MOVED_TEMPORARILY          = 302,
    HTTP_STATUS_CODE_SEE_OTHER                  = 303,
    HTTP_STATUS_CODE_NOT_MODIFIED               = 304,
    HTTP_STATUS_CODE_TEMPORARY_REDIRECT         = 307,

    /* 4xx */
    HTTP_STATUS_CODE_BAD_REQUEST                = 400,
    HTTP_STATUS_CODE_UNAUTHORIZED               = 401,
    HTTP_STATUS_CODE_FORBIDDEN                  = 403,
    HTTP_STATUS_CODE_NOT_FOUND                  = 404,
    HTTP_STATUS_CODE_NOT_ALLOWED                = 405,
    HTTP_STATUS_CODE_REQUEST_TIME_OUT           = 408,
    HTTP_STATUS_CODE_CONFLICT                   = 409,
    HTTP_STATUS_CODE_LENGTH_REQUIRED            = 411,
    HTTP_STATUS_CODE_PRECONDITION_FAILED        = 412,
    HTTP_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE   = 413,
    HTTP_STATUS_CODE_REQUEST_URI_TOO_LARGE      = 414,
    HTTP_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE     = 415,
    HTTP_STATUS_CODE_RANGE_NOT_SATISFIABLE      = 416,
    HTTP_STATUS_CODE_MISDIRECTED_REQUEST        = 421,

    /* 5xx */
    HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR      = 500,
    HTTP_STATUS_CODE_NOT_IMPLEMENTED            = 501,
    HTTP_STATUS_CODE_BAD_GATEWAY                = 502,
    HTTP_STATUS_CODE_SERVICE_UNAVAILABLE        = 503,
    HTTP_STATUS_CODE_GATEWAY_TIME_OUT           = 504,
    HTTP_STATUS_CODE_INSUFFICIENT_STORAGE       = 507,
};

struct HTTPRequestLine
{
    uint8_t method;
    std::string uri;
    uint8_t major_version;
    uint8_t minor_version;

    HTTPRequestLine() 
        : method(HTTP_METHOD_UNKNOWN), uri(), major_version(0), minor_version(0) {}
};

typedef std::map<std::string, std::string> HTTPHeaders;

struct HTTPRequest
{
    HTTPRequestLine request_line;
    HTTPHeaders headers;
};

struct HTTPStatusLine
{
    uint8_t major_version;
    uint8_t minor_version;
    uint16_t status_code;
    std::string phrase;

    HTTPStatusLine() 
        : major_version(0), minor_version(0), status_code(HTTP_STATUS_CODE_UNKNOWN), phrase() {}
};

struct HTTPResponse
{
    HTTPStatusLine status_line;
    HTTPHeaders headers;
};

struct HttpContent
{
    std::string methodstring;
    std::string location;
    std::string proto;
    std::string body;
    std::vector<std::pair<std::string, std::string>> headers;
    std::string peer_ip;
    void *param = nullptr;
    uint16_t peer_port;
    uint16_t local_port;
    bool is_reuse = false;
    HTTPMethod method = HTTP_METHOD_UNKNOWN;
};


struct HttpRange
{
    int32_t start;
    int32_t end;
};

#endif // !_HTTP_DEFINES_H_INCLUDED