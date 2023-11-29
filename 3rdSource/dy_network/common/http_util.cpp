#include "http_util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <url.h>
#include <platform_log.h>

enum
{
    IP_STATE_BEGIN  = 0,
    IP_STATE_NUM_1  = 1,
    IP_STATE_NUM_2  = 2,
    IP_STATE_NUM_3  = 3,
    IP_STATE_NUM_4  = 4,
    IP_STATE_RIGHT  = 5
};

bool parse_http_url(const std::string&url, std::string& host, uint16_t& port, std::string& location, bool& ssl)
{
    string_view schema;
    string_view hostport;
    string_view uri;
    string_view vhost;
    if (!util::parse_url(url, &schema, &hostport, &uri))
    {
        WARNING_LOG("parse http url failed:%s", url.c_str());
        return false;
    }

    if (schema == "https")
    {
        ssl = true;
    }
    else
    {
        ssl = false;
    }
    port = 0;
    if (!util::split_host_port(hostport, &vhost, &port))
    {
        WARNING_LOG("split_host_port failed:%s", hostport.to_string().c_str());
        return false;
    }

    if (0 == port)
    {
        if (ssl)
        {
            port = 443;
        }
        else
        {
            port = 80;
        }
    }

    host = vhost.to_string();
    location = uri.to_string();
    return true;
}

bool parse_http_status_line(const char *start, const char *end, HTTPStatusLine *status_line)
{
    enum
    {
        st_http_start,
        st_http_H,
        st_http_HT,
        st_http_HTT,
        st_http_HTTP,
        st_http_major,
        st_http_dot,
        st_http_minor,
        st_http_end,
        st_http_first_status_code,
        st_http_status_code,
        st_http_status_start,
        st_http_status
    } state;

    uint8_t http_major_version = 0;
    uint8_t http_minor_version = 0;
    uint16_t status_code = 0;
    const char *pharse_start = NULL;
    const char *pharse_end = NULL;

    bool stoped = false;
    state = st_http_start;
    for (; start < end && !stoped; ++start)
    {
        char ch = *start;
        switch (state)
        {
        case st_http_start:
            if ('H' != ch)
            {
                return false;
            }

            state = st_http_H;
            break;
        case st_http_H:
            if ('T' != ch)
            {
                return false;
            }

            state = st_http_HT;
            break;
        case st_http_HT:
            if ('T' != ch)
            {
                return false;
            }

            state = st_http_HTT;
            break;
        case st_http_HTT:
            if ('P' != ch)
            {
                return false;
            }

            state = st_http_HTTP;
            break;
        case st_http_HTTP:
            if ('/' != ch)
            {
                return false;
            }

            state = st_http_major;
            break;
        case st_http_major:
            if (ch < '0' || ch > '9')
            {
                return false;
            }

            http_major_version = ch - '0';
            state = st_http_dot;
            break;
        case st_http_dot:
            if ('.' != ch)
            {
                return false;
            }

            state = st_http_minor;
            break;
        case st_http_minor:
            if (ch < '0' || ch > '9')
            {
                return false;
            }

            http_minor_version = ch - '0';
            state = st_http_end;
            break;
        case st_http_end:
            if (' ' != ch)
            {
                return false;
            }

            state = st_http_first_status_code;
            break;
        case st_http_first_status_code:
            if (' ' == ch)
            {
                break;
            }

            if (ch < '0' || ch > '9')
            {
                return false;
            }

            status_code = ch - '0';
            state = st_http_status_code;
            break;
        case st_http_status_code:
            if (' ' == ch)
            {
                state = st_http_status_start;
                break;
            }

            if (ch < '0' || ch > '9')
            {
                return false;
            }

            status_code = status_code * 10 + (ch - '0');
            if (status_code > 999)
            {
                return false;
            }
            break;
        case st_http_status_start:
            if (' ' == ch)
            {
                break;
            }

            pharse_start = start;
            pharse_end = start + 1;
            state = st_http_status;
            break;
        case st_http_status:
            if ('\r' == ch || '\n' == ch)
            {
                stoped = true;
                break;
            }

            pharse_end++;
            break;
        default:
            stoped = true;
            break;
        }
    }

    if (status_line)
    {
        status_line->major_version = http_major_version;
        status_line->minor_version = http_minor_version;
        status_line->status_code = status_code;

        if (pharse_end > pharse_start)
        {
            status_line->phrase.assign(pharse_start, pharse_end);
        }
    }

    return true;
}

const char *http_status_text(HTTPStatusCode sc)
{
    switch (sc)
    {
    /* 1xx */
    case HTTP_STATUS_CODE_CONTINUE:
        return "Continue";
    case HTTP_STATUS_CODE_SWITCHING_PROTOCOLS:
        return "Switching Protocols";
    case HTTP_STATUS_CODE_SWITCHING_PROCESSING:
        return "Processing";
    
    case HTTP_STATUS_CODE_OK:
        return "OK";
    case HTTP_STATUS_CODE_CREATED:
        return "Created";
    case HTTP_STATUS_CODE_ACCEPTED:
        return "Accepted";
    case HTTP_STATUS_CODE_NO_CONTENT:
        return "No Content";
    case HTTP_STATUS_CODE_PARTIAL_CONTENT:
        return "Partial Content";
    
    /* 3xx */
    case HTTP_STATUS_CODE_SPECIAL_RESPONSE:
        return "Multiple Choices";
    case HTTP_STATUS_CODE_MOVED_PERMANENTLY:
        return "Moved Permanently";
    case HTTP_STATUS_CODE_MOVED_TEMPORARILY:
        return "Found";
    case HTTP_STATUS_CODE_SEE_OTHER:
        return "See Other";
    case HTTP_STATUS_CODE_NOT_MODIFIED:
        return "Not Modified";
    case HTTP_STATUS_CODE_TEMPORARY_REDIRECT:
        return "Temporary Redirect";
    
    /* 4xx */
    case HTTP_STATUS_CODE_BAD_REQUEST:
        return "Bad Request";
    case HTTP_STATUS_CODE_UNAUTHORIZED:
        return "Unauthorized";
    case HTTP_STATUS_CODE_FORBIDDEN:
        return "Forbidden";
    case HTTP_STATUS_CODE_NOT_FOUND:
        return "Not Found";
    case HTTP_STATUS_CODE_NOT_ALLOWED:
        return "Method Not Allowed";
    case HTTP_STATUS_CODE_REQUEST_TIME_OUT:
        return "Request Timeout";
    case HTTP_STATUS_CODE_CONFLICT:
        return "Conflict";
    case HTTP_STATUS_CODE_LENGTH_REQUIRED:
        return "Length Required";
    case HTTP_STATUS_CODE_PRECONDITION_FAILED:
        return "Precondition Failed";
    case HTTP_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE:
        return "Request Entity Too Large";
    case HTTP_STATUS_CODE_REQUEST_URI_TOO_LARGE:
        return "Request URI Too Long";
    case HTTP_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE:
        return "Unsupported Media Type";
    case HTTP_STATUS_CODE_RANGE_NOT_SATISFIABLE:
        return "Requested Range Not Satisfiable";
    case HTTP_STATUS_CODE_MISDIRECTED_REQUEST:
        return "Misdirected Request";
    
    /* 5xx */
    case HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR:
        return "Internal Server Error";
    case HTTP_STATUS_CODE_NOT_IMPLEMENTED:
        return "Not Implemented";
    case HTTP_STATUS_CODE_BAD_GATEWAY:
        return "Bad Gateway";
    case HTTP_STATUS_CODE_SERVICE_UNAVAILABLE:
        return "Service Unavailable";
    case HTTP_STATUS_CODE_GATEWAY_TIME_OUT:
        return "Gateway Timeout";
    case HTTP_STATUS_CODE_INSUFFICIENT_STORAGE:
        return "Insufficient Storage";
    default:
        break;
    }

    return "";
}
