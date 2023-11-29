#include <sstream>
#include "url.h"
#include "net_helper.h"
#include <climits>

#if defined(__ANDROID__)
#define UINT16_MAX (65535)
#endif
namespace util
{

void replace_str(std::string &str, const std::string &src, const std::string &dst)
{
    std::string::size_type pos = 0;
    std::string::size_type src_len = src.size();
    std::string::size_type dst_len = dst.size();
    while ((pos = str.find(src, pos)) != std::string::npos)
    {
        str.replace(pos, src_len, dst);
        pos += dst_len;
    }
}

std::string escape_ipv6(string_view ipv6)
{
    if (ipv6.empty())
    {
        return "";
    }

    const std::string src(":");
    const std::string dst("%3A");
    if (string_view::npos == ipv6.find(src))
    {
        return ipv6.to_string();
    }

    std::string ret_ip(ipv6.to_string());
    replace_str(ret_ip, src, dst);

    return ret_ip;
}

std::string unescape_ipv6(string_view ipv6)
{
    if (ipv6.empty())
    {
        return "";
    }

    const std::string src("%3A");
    const std::string dst(":");
    if (string_view::npos == ipv6.find(src))
    {
        return ipv6.to_string();
    }

    std::string ret_ip(ipv6.to_string());
    replace_str(ret_ip, src, dst);

    return ret_ip;
}

bool my_atoi(const char *sz, int len, int &out)
{
    if (len < 1)
    {
        return false;
    }

    int64_t max_val = INT_MAX;
    bool is_neg = false;
    int i = 0;
    if ('+' == sz[0])
    {
        i++;
    }
    else if ('-' == sz[0])
    {
        max_val = -static_cast<int64_t>(INT_MIN);
        is_neg = true;
        i++;
    }

    int64_t val = 0;
    for (; i < len; ++i)
    {
        char ch = sz[i];
        if (ch < '0' || ch > '9')
        {
            return false;
        }

        val = val * 10 + (ch - '0');
        if (val > max_val)
        {
            return false;
        }
    }

    if (is_neg)
    {
        val = -val;
    }

    out = static_cast<int>(val);

    return true;
}

bool split_host_port(string_view hostport, string_view *host, uint16_t *port)
{
    if (hostport.empty())
    {
        return false;
    }

    if ('[' == hostport[0]) // ipv6
    {
        string_view::size_type pos = hostport.rfind(']');
        if (string_view::npos == pos)
        {
            return false;
        }

        if (host)
        {
            *host = hostport.substr(1, pos - 1);
        }

        hostport = hostport.substr(pos + 1);
        if (port)
        {
            if (':' == hostport[0])
            {
                int n = 0;
                if (!my_atoi(hostport.data() + 1, hostport.size() - 1, n))
                {
                    return false;
                }

                if (n <= 0 || n >= UINT16_MAX)
                {
                    return false;
                }

                *port = static_cast<uint16_t>(n);
            }
        }
    }
    else
    {
        string_view::size_type pos = hostport.rfind(':');
        if (host)
        {
            *host = hostport.substr(0, pos);
        }

        if (port)
        {
            if (string_view::npos != pos)
            {
                int n = 0;
                if (!my_atoi(hostport.data() + pos + 1, hostport.size() - pos - 1, n))
                {
                    return false;
                }

                if (n <= 0 || n >= UINT16_MAX)
                {
                    return false;
                }

                *port = static_cast<uint16_t>(n);
            }
        }
    }

    return true;
}

bool parse_stream_id_from_path(string_view path, string_view *app, string_view *name, string_view *suffix)
{
    if (path.starts_with('/'))
    {
        path.remove_prefix(1);
    }

    string_view::size_type pos = path.rfind('/');
    if (std::string::npos == pos)
    {
        if (name)
        {
            return false;
        }
        if (app)
        {
            *app = path;
        }
        return true;
    }

    if (app)
    {
        *app = path.substr(0, pos);
    }

    path.remove_prefix(pos + 1);

    pos = path.rfind('.');
    if (std::string::npos == pos)
    {
        if (name)
        {
            return false;
        }
    }
    
    if (name)
    {
        *name = path.substr(0, pos);
        if(suffix)
        {
            *suffix = path.substr(pos);
        }
    }

    return true;
}

bool parse_stream_id_from_dr302_path(string_view path, string_view *host, string_view *app, string_view *name)
{
    if (path.starts_with('/'))
    {
        path.remove_prefix(1);
    }

    string_view::size_type pos = path.find('/');
    if (std::string::npos == pos)
    {
        return false;
    }

    if (host)
    {
        *host = path.substr(0, pos);
    }

    path.remove_prefix(pos + 1);

    return parse_stream_id_from_path(path, app, name);
}

// [/][host][/]{app}/{name}[.{suffix}][?args]
bool parse_stream_path(string_view path, string_view *dr302_host, string_view *app, string_view *name, string_view *suffix)
{
    if (path.starts_with('/'))
    {
        path.remove_prefix(1);
    }

    auto pos = path.find_last_of("?./");
    if (string_view::npos == pos)
    {
        return false;
    }

    // args
    if ('?' == path[pos])
    {
        path.remove_suffix(path.length() - pos);
        pos = path.find_last_of("./");
        if (string_view::npos == pos)
        {
            return false;
        }
    }

    //  suffix
    if ('.' == path[pos])
    {
        if (suffix)
        {
            *suffix = path.substr(pos + 1);
        }

        path.remove_suffix(path.length() - pos);
        pos = path.find_last_of('/');
        if (string_view::npos == pos)
        {
            return false;
        }
    }

    // name
    if (name)
    {
        *name = path.substr(pos + 1);
    }

    path.remove_suffix(path.length() - pos);

    // dr302_host
    if (dr302_host)
    {
        pos = path.find_first_of('/');
        if (string_view::npos != pos)
        {
            *dr302_host = path.substr(0, pos);
            path.remove_prefix(pos + 1);
        }
    }

    // app
    if (app)
    {
        *app = path;
    }

    return true;
}

void parse_url_args(string_view args, std::map<string_view, string_view> *kv)
{
    while (!args.empty())
    {
        string_view::size_type pos = args.find('&');
        string_view arg = args.substr(0, pos);

        if (string_view::npos == pos)
        {
            args.clear();
        }
        else
        {
            args.remove_prefix(pos + 1);
        }

        pos = arg.find('=');
        string_view key = arg.substr(0, pos);

        if (string_view::npos == pos)
        {
            arg.clear();
        }
        else
        {
            arg.remove_prefix(pos + 1);
        }

        (*kv)[key] = arg;
    }
}


bool parse_uri(string_view uri, string_view *path, string_view *args)
{
    if (uri.empty())
    {
        return false;
    }

    string_view::size_type pos = uri.find('?');
    if (path)
    {
        *path = uri.substr(0, pos);
    }

    if (string_view::npos == pos)
    {
        return true;
    }

    if (args)
    {
        *args = uri.substr(pos + 1);
    }

    return true;
}

bool parse_url(string_view url, string_view *scheme, string_view *hostport, string_view *uri)
{
    string_view::size_type pos = url.find("://");
    if (string_view::npos == pos)
    {
        return false;
    }

    if (scheme)
    {
        *scheme = url.substr(0, pos);
    }

    url.remove_prefix(pos + 3);

    pos = url.find_first_of("/?");
    if (hostport)
    {
        *hostport = url.substr(0, pos);
    }

    if (string_view::npos == pos)
    {
        return true;
    }

    if ('/' == url[pos])
    {
        pos++;
    }

    if (uri)
    {
        *uri = url.substr(pos);
    }

    return true;
}

bool parse_rtmp_name(string_view req_name, string_view *name, string_view *args)
{
    if (req_name.empty())
    {
        return false;
    }

    string_view::size_type pos = req_name.find('?');
    if (name)
    {
        *name = req_name.substr(0, pos);
    }

    if (string_view::npos == pos)
    {
        return true;
    }

    if (args)
    {
        *args = req_name.substr(pos + 1);
    }

    return true;

}

bool parse_rtmp_name_from_path(string_view path, string_view *app, string_view *name)
{
    if (path.starts_with('/'))
    {
        path.remove_prefix(1);
    }

    string_view::size_type pos = path.rfind('/');
    if (std::string::npos == pos)
    {
        if (name)
        {
            return false;
        }
        if (app)
        {
            *app = path;
        }
        return true;
    }

    if (app)
    {
        *app = path.substr(0, pos);
    }

    path.remove_prefix(pos + 1);
    if (name)
    {
        *name = path;
    }

    return true;
}

bool is_ipv4(string_view str)
{
    int num = -1;
    int dot = 0;
    bool first_zero = false;

    for (auto c : str)
    {
        if ('.' == c)
        {
            if (num < 0 || num > 255)
            {
                return false;
            }

            dot++;
            if (dot > 3)
            {
                return false;
            }

            num = -1;
            continue;
        }

        if (c < '0' || c > '9')
        {
            return false;
        }

        if (-1 == num)
        {
            first_zero = ('0' == c);
            num = (c - '0');
        }
        else
        {
            if (first_zero)
            {
                return false;
            }

            num = num * 10 + (c - '0');
        }

        if (num < 0 || num > 255)
        {
            return false;
        }
    }

    return 3 == dot;
}

std::string join_host_port(const string_view host, uint32_t port)
{
    if (host.empty() || port == 0)
    {
        return "";
    }

    std::ostringstream oss;
    int family = dy_network::ip_family_from_string(host.to_string().c_str());
    if (AF_INET6 == family)
    {
        oss << "[" << host << "]" << ":" << port;
    }
    else
    {
        oss << host << ":" << port;
    }

    return oss.str();
}

void trim_ipv6_bracket(std::string& ipv6)
{
    auto it = std::find(ipv6.begin(), ipv6.end(), '[');
    if (it != ipv6.end())
    {
        ipv6.erase(it);
    }

    it = std::find(ipv6.begin(), ipv6.end(), ']');
    if (it != ipv6.end())
    {
        ipv6.erase(it);
    }
}


}
