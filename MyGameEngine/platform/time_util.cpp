#include "time_util.h"
#include <thread>

#ifdef _WIN32

void usleep(uint32_t wait_time)
{
    std::this_thread::sleep_for(std::chrono::microseconds(wait_time));
}

struct timezone
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};


#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tv->tv_sec = static_cast<long>(clock);
    tv->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

#endif 


uint64_t get_tick_count()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

    uint64_t tick = tv.tv_sec;
	tick = (tick * 1000) + (tv.tv_usec/1000);
    return tick;
}

uint64_t get_tick_count_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t tick = tv.tv_sec;
    tick = (tick * 1000 * 1000) + tv.tv_usec;
    return tick;
}

uint32_t get_seconds()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

void cross_sleep( uint32_t millseconds )
{
	usleep( millseconds * 1000 );
}



static uint32_t   uri[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0xfc00886d, /* 1111 1100 0000 0000  1000 1000 0110 1101 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x78000000, /* 0111 1000 0000 0000  0000 0000 0000 0000 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0xa8000000, /* 1010 1000 0000 0000  0000 0000 0000 0000 */

        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff  /* 1111 1111 1111 1111  1111 1111 1111 1111 */
    };
    
static u_char   hex[] = "0123456789ABCDEF";
    
int32_t url_decode(const unsigned char* input, uint32_t input_size, char* output)
{
    int32_t      n = 0;
    uint32_t       *escape = uri;
    const unsigned char* src = input;
    char *dst = output;
    uint32_t size = input_size;
    
    while (size) {
        if (escape[*src >> 5] & (1 << (*src & 0x1f))) {
            *dst++ = '%';
            *dst++ = hex[*src >> 4];
            *dst++ = hex[*src & 0xf];
            src++;

        } else {
            *dst++ = *src++;
        }
        size--;
    }
    
    n = (int32_t)(dst - output);
    return n;
}

int get_local_ip(const char* intf_name, std::string& ip)
{
#ifdef _WIN32

#else
    struct ifaddrs *ifaddr, *ifa;
    int family;
    int ret = -1;

#ifndef __ANDROID__
    if (getifaddrs(&ifaddr) == -1)
#else
    if (dy_network::getifaddrs(&ifaddr) == -1)
#endif
    {
        return ret;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        if (0 != strcmp(ifa->ifa_name, intf_name))
        {
            continue;
        }
        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET)
        {
            void* tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[256] = { 0 };
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, 256);

            ip = addressBuffer;
        }
    }
#ifndef __ANDROID__
    freeifaddrs(ifaddr);
#else
    dy_network::freeifaddrs(ifaddr);
#endif
    return ret;
#endif 
    return 0;
}

inline struct tm* platform_localtime(time_t* time, struct tm *tm)
{
#ifdef _WIN32
    localtime_s(tm, time);
    return tm;
#else
    return localtime_r(time, tm);
#endif
}


bool platform_get_current_time(platform_time_t* pt)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    pt->tm_msec = tv.tv_usec / 1000;
    time_t t = tv.tv_sec;
    struct tm cur_tm;
    struct tm* tm = platform_localtime(&t, &cur_tm);
    if (!tm)
    {
        time_t s;
        time(&s);
        tm = platform_localtime(&s, &cur_tm);
        
        pt->tm_year = tm->tm_year + 1900;
        pt->tm_mon = tm->tm_mon + 1;
        pt->tm_mday = tm->tm_mday;
        pt->tm_hour = tm->tm_hour;
        pt->tm_min = tm->tm_min;
        pt->tm_sec = tm->tm_sec;
        pt->tm_wday = tm->tm_wday;
        pt->tm_yday = tm->tm_yday;
    }
    else
    {
        pt->tm_year = tm->tm_year + 1900;
        pt->tm_mon = tm->tm_mon + 1;
        pt->tm_mday = tm->tm_mday;
        pt->tm_hour = tm->tm_hour;
        pt->tm_min = tm->tm_min;
        pt->tm_sec = tm->tm_sec;
        pt->tm_wday = tm->tm_wday;
        pt->tm_yday = tm->tm_yday;
    }
    
    
    return true;
}

std::string get_current_time_string()
{
    platform_time_t pmt;
    platform_get_current_time(&pmt);
    char buffer[512] = { 0 };
    snprintf(buffer, sizeof(buffer), "%.4d%.2d%.2d %.2d:%.2d:%.2d.%.3d", pmt.tm_year, pmt.tm_mon, pmt.tm_mday,
        pmt.tm_hour, pmt.tm_min, pmt.tm_sec, pmt.tm_msec);
    return std::string(buffer);
}
