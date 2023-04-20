#ifndef __PLATFORM_LOG_H__
#define __PLATFORM_LOG_H__
#include <stdint.h>
#include <string>
#include <string.h>
#include <inttypes.h>

//#include "compiler_specific.h"
//#include "ct_basename.h"

#define MAX_LOGLEVEL_LENGTH 14
#define LOG_PREFIX_LENGTH 40 + MAX_LOGLEVEL_LENGTH

//heshuixia 20190625, for android log callback.
typedef void(*p2p_log_cb)(void *user_data, int level, const char* msg, uint32_t msg_len);

enum
{
	PLATFORMLOG_DEBUG 		= 0,
	PLATFORMLOG_TRACE 		= 1,
	PLATFORMLOG_NOTICE 		= 2,
	PLATFORMLOG_WARNING 	= 3,
	PLATFORMLOG_FATAL		= 4, 
    PLATFORMLOG_FLOW        = 5,
    PLATFORMLOG_INIT        = 6,
    PLATFORMLOG_STAT        = 7,
};

class ILog
{
public:
#ifdef DY_NETWORK_LOG_FORMAT_CHECK
    virtual void write_log(
        uint32_t level,
        const char* filename,
        uint32_t line,
        _Printf_format_string_ const char* fmt,
        ...) DY_NETWORK_PRINTF_FORMAT(5, 6) = 0;
#else
    virtual void write_log(uint32_t level, 
                        const char* filename, 
                        uint32_t line, 
                        const char* fmt, ...) = 0;
#endif

    virtual void clean_expire_log(uint32_t day) {}
    virtual const std::string get_log_file_name() = 0;
    virtual bool init(const char* log_directory) {return false;}
    virtual bool destory() {return false;}
    virtual void set_log_level(int level){}
    virtual int get_log_level() {return PLATFORMLOG_FATAL;}
    virtual void set_log_callback(void *log_ctx, p2p_log_cb cb) {}
};

bool platform_log_init(ILog* log = NULL, const char* log_directory = NULL, bool flow_log_split = false);
void platform_log_destroy();
void platform_setloglevel(uint32_t level);
void platform_clean_expire_log(uint32_t day);
uint32_t platform_getloglevel();
void platform_setlogcallback(void *log_ctx, p2p_log_cb cb);
int create_log_directory(const char* filename);
ILog* createLog();
extern ILog* g_dynetwork_log;

#ifdef _WIN32
#define _DY_NETWORK_LOG_CHECKER(fmt, ...)  if(0){ printf(fmt, ##__VA_ARGS__); }
#define __DY_NETWORK_BASENAME__ ""
#else
#define _DY_NETWORK_LOG_CHECKER(fmt, ...)
#endif

#define _DY_NETWORK_LOG(LL, fmt, ...)                                                                            \
    do {                                                                                                         \
        if (g_dynetwork_log->get_log_level() <= PLATFORMLOG_##LL)                                                \
        {                                                                                                        \
            g_dynetwork_log->write_log(PLATFORMLOG_##LL, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
            _DY_NETWORK_LOG_CHECKER(fmt, ##__VA_ARGS__)                                                          \
        }                                                                                                        \
    } while (0);

#ifndef DEBUG_LOG
#define DEBUG_LOG(fmt, ...) _DY_NETWORK_LOG(DEBUG, fmt, ##__VA_ARGS__)
#endif
#define TRACE_LOG(fmt, ...) _DY_NETWORK_LOG(TRACE, fmt, ##__VA_ARGS__)
#define NOTICE_LOG(fmt, ...) _DY_NETWORK_LOG(NOTICE, fmt, ##__VA_ARGS__)
#define WARNING_LOG(fmt, ...) _DY_NETWORK_LOG(WARNING, fmt, ##__VA_ARGS__)
#define FATAL_LOG(fmt, ...) _DY_NETWORK_LOG(FATAL, fmt, ##__VA_ARGS__)
#ifndef FLOW_LOG
#define FLOW_LOG(fmt, ...) _DY_NETWORK_LOG(FLOW, fmt, ##__VA_ARGS__)
#endif
#define INIT_LOG(fmt, ...) _DY_NETWORK_LOG(INIT, fmt, ##__VA_ARGS__)
#define STAT_LOG(fmt, ...) _DY_NETWORK_LOG(STAT, fmt, ##__VA_ARGS__)

#endif //__PLATFORM_LOG_H__
