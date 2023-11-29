
#ifndef _WIN32
#include <sys/resource.h>
#endif
#include <string.h>
#include <platform_log.h>
#include "comm_resource.h"

int set_max_openfile(unsigned int file_num)
{
#ifndef _WIN32
    int ret = 0;
    struct rlimit rlim = {0};
    struct rlimit rlim_new = {0};
    ret = getrlimit(RLIMIT_NOFILE, &rlim);
    if (ret == 0)
    {
        if(file_num <= rlim.rlim_cur)
        {
            return ret;
        }

        rlim_new.rlim_cur = file_num;
        rlim_new.rlim_max = rlim.rlim_max;
        ret = setrlimit(RLIMIT_NOFILE, &rlim_new);
        if (ret != 0)
        {
            FATAL_LOG("setrlimit 'OPENFILE' %" PRIu64 "->%" PRIu64 " failed,err=%d", (uint64_t)rlim.rlim_cur, (uint64_t)rlim_new.rlim_cur, ret);

            rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;
            ret = setrlimit(RLIMIT_NOFILE, &rlim_new);
            FATAL_LOG("setrlimit 'OPENFILE' max_value %" PRIu64 ",err=%d", (uint64_t)rlim_new.rlim_max, ret);
        }
    }
    else
    {
        FATAL_LOG("getrlimit 'OPENFILE' failed,err=%d", ret);
    }
    return ret;
#endif
    return 0;
}


