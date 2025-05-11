#include "path_utils.h"
#include "CommonUtils.h"
#ifdef _WINDOWS
#include <windows.h>
#endif

namespace CommonUtils
{
    std::string getPath(const char* name)
    {
        std::string dir = "E:/myproject/opengl_demo/resources/";
        return dir + name;
    }

    const char* getSuffix(const std::string& name)
    {
        size_t pos = name.find_last_of('.');
        if (pos == std::string::npos)
        {
            return name.c_str() + name.size();
        }

        return name.c_str() + pos;
    }

    const char* getSuffix(const char* name)
    {
        const char* p = name;
        const char* ret = nullptr;
        while (*p != 0)
        {
            if (*p == '.')
            {
                ret = p;
            }
            p++;
        }

        return ret;
    }

    std::string removeSuffix(const std::string& name)
    {
        std::string tmp;
        size_t pos = name.find_last_of('.');
        if (pos == std::string::npos)
        {
            return name;
        }

        tmp = name.substr(0, pos);
        return tmp;
    }

    std::string getShortFilename(const std::string& name)
    {
        std::string tmp;
        size_t pos = name.find_last_of('\\');
        size_t pos2 = name.find_last_of('/');
        size_t current = std::max(pos, pos2);
        if (current == std::string::npos)
        {
            return name;
        }

        tmp = name.substr(current + 1);
        return tmp;
    }

    std::string getDirectory(const char* filename)
    {
        assert_invariant(false);
        std::string aa;
        return aa;
    }

    std::string getParentDirectory(const char* filename)
    {
        assert_invariant(false);
        std::string aa;
        return aa;
    }
}