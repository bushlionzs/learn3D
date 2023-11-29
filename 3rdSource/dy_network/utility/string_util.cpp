#include "string_util.h"

#ifdef WIN32
#include <windows.h>
#else
#include <string.h>
#endif

namespace dy
{
    std::string get_short_name(std::string& fullname)
    {
        if (fullname.empty())
        {
            return fullname;
        }


        std::string::size_type iPos = fullname.find_last_of("/\\");

        if (iPos == std::string::npos)
        {
            return fullname;
        }

        iPos++;
        return fullname.substr(iPos, fullname.length() - iPos);
    }

    char const* strnchr(char const* str, int ch, int which)
    {
        for (int i = 0; i < which; i++)
        {
            if (*(str + i) == ch)
            {
                return str + i;
            }
        }
        return NULL;
    }

    void to_lower(std::string& content)
    {
        for (uint32_t i = 0; i < content.size(); i++)
        {
            if (content[i] >= 'A' && content[i] <= 'Z')
            {
                content[i] += 32;
            }
        }
    }

    static uint8_t hex_to_value(char c)
    {
        if (c >= '0' && c <= '9')
        {
            return c - '0';
        }
        else if (c >= 'a' && c <= 'f')
        {
            return (c - 'a' + 10);
        }

        return 0;
    }

    bool  hex_to_binary(const std::string& hex, std::string& output)
    {
        if (hex.size() % 2)
        {
            return false;
        }

        for (size_t i = 0; i < hex.size(); i += 2)
        {
            uint8_t tmp = 0;

            char hi = hex_to_value(hex[i]);
            char lo = hex_to_value(hex[i + 1]);

            tmp = hi << 4 | lo;

            output.push_back(tmp);
        }
        return true;
    }

    void binary_to_hex(const char* data, uint32_t size, std::string& output)
    {
        for (uint32_t i = 0; i < size; i++)
        {
            char c = data[i];
            if (c >= 0 && c <= 9)
            {
                output.push_back(c + '0');
            }
            else if (c >= 'a' && c <= 'z')
            {
                output.push_back('a' + c);
            }
        }
    }

    void split_string(const char* str, char sep, std::vector<std::string>& strlist)
    {
        strlist.clear();
        const char* start = str;

        const char* p = str;
        std::string tmp;

        while (*p)
        {
            if (*p == sep)
            {
                tmp.assign(start, p - start);
                strlist.push_back(tmp);
                p++;
                start = p;
            }
            else
            {
                p++;
            }
        }

        if (p >= start)
        {
            tmp.assign(start, p - start);
            strlist.push_back(tmp);
        }
    }

    uint64_t StrToUINT64(const char* szBuff)
    {
        uint64_t	ret = 0;
        char* end;
        ret = strtoll(szBuff, &end, 10);
        return ret;
    }
}
