#ifndef __HTTP_UTIL_H__
#define __HTTP_UTIL_H__
#include <string>
#include <stdint.h>

#include "http_defines.h"

bool parse_http_url(const std::string&url, std::string& host, uint16_t& port, std::string& location, bool& ssl);
bool parse_http_status_line(const char *start, const char *end, HTTPStatusLine *status_line);
const char *http_status_text(HTTPStatusCode sc);

#endif //__HTTP_UTIL_H__