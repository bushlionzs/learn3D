#ifndef _URL_H_INCLUDED
#define _URL_H_INCLUDED

#include <stdint.h>

#include <map>

#include "string_view.h"

namespace util
{

bool split_host_port(string_view hostport, string_view *host, uint16_t *port);
bool parse_stream_id_from_path(string_view path, string_view *app, string_view *name, string_view *suffix = NULL);
bool parse_stream_id_from_dr302_path(string_view path, string_view *host, string_view *app, string_view *name);
bool parse_stream_path(string_view path, string_view *dr302_host, string_view *app, string_view *name, string_view *suffix);
void parse_url_args(string_view args, std::map<string_view, string_view> *kv);
bool parse_uri(string_view uri, string_view *path, string_view *args);
bool parse_url(string_view url, string_view *schema, string_view *hostport, string_view *uri);
bool parse_rtmp_name(string_view req_name, string_view *name, string_view *args);
bool parse_rtmp_name_from_path(string_view path, string_view *app, string_view *name);
bool is_ipv4(string_view ip);
std::string join_host_port(const string_view host, uint32_t port);
void trim_ipv6_bracket(std::string& ipv6);

}

#endif //_URL_H_INCLUDED