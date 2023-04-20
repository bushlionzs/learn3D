#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <atomic>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#include <direct.h>
#define write _write
#define open _open
#define close _close
#define access _access
#define O_CREAT _O_CREAT
#define O_WRONLY _O_WRONLY
#define O_APPEND _O_APPEND
#define F_OK 0
#define vsnprintf _vsnprintf
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined(__ANDROID__)
#include <android/log.h>
#endif
#endif
#include <fcntl.h>
#include <string.h>
#include "time_util.h"
#include "platform_common.h"
#include "platform_file_system.h"
#include "platform_file.h"
#include "platform_log.h"
#include "platform_util.h"
#include "platform_mutex.h"
#include "scoped_lock.h"

const char* g_log_level_str[] = {
    "DEBUG  ",
    "TRACE  ",
    "NOTICE ",
    "WARNING",
    "FATAL  ",
    "FLOW   ",
    "INIT   ",
    "STAT   ",
};

typedef struct
{
    char*     origalname;
    char      curr_name[1024];
    char      curr_name_wf[1024];
    int         last_hour;
    int         last_day;
    int         log_fd;
    int         log_fd_wf;
}platform_log_t;



typedef struct tm	platform_tm_t;

#define NGX_FILE_DEFAULT_ACCESS  0644

ILog* g_dynetwork_log = NULL;

void log_init(void);
uint32_t log_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pThreadData);
void platform_localtime(struct tm *tm);
void platform_gmtime(time_t t, platform_tm_t *tp);
void get_current_tm(platform_tm_t* pmt);



class PlatformLog: public ILog
{
public:
    PlatformLog(bool flow_log_split = false)
    {
        _log_level = PLATFORMLOG_DEBUG;
        _log_cb = NULL;
        _log_ctx = NULL;
        _is_flow_log_split = flow_log_split;
    }
    virtual void write_log(uint32_t level, const char* filename, uint32_t line, const char* fmt, ...)
    {
        if (level < _log_level)
        {
#if (defined(__ANDROID__)) || (defined(__APPLE__))
            return;
#else
            if (level != PLATFORMLOG_FLOW && level != PLATFORMLOG_INIT)
            {
                return;
            }
#endif            
        }
		
        const char* name = filename;

        while (char c = *filename)
        {
            if(c == '/' || c == '\\')
            {
                name = filename;
            }
            filename++;
        }
		char logbuffer[8192];
		memset(logbuffer, 0, sizeof(logbuffer));
		int n = snprintf(logbuffer, sizeof(logbuffer) - 1, "[%s] [%s:%u]", g_log_level_str[level], name, line);

		va_list arglist;
        va_start (arglist, fmt);
        int n2 = vsnprintf(logbuffer + n, sizeof(logbuffer) - n - 1, fmt, arglist);
        va_end(arglist);
        
        n += n2;
        if (n >= (int)sizeof(logbuffer))
        {
            logbuffer[sizeof(logbuffer) - 2] = '\n';
            n = sizeof(logbuffer) - 1;
        }
        else
        {
            logbuffer[n] = '\n';
        }

        std::shared_ptr<IPlatformModule> log_module = _log_module_wptr.lock();
        if (log_module)
        {
            log_module->post_module_message(0, level, (uint64_t)this, 0, logbuffer, n + 1);
        }
    }

    void write_log(const char* msg, uint32_t msg_size, uint32_t msg_id)
    {
        {
            ScopedLock<PlatformMutex> _lock(_log_mutex);
			create_init_directory();
            if (_log_cb && msg && msg_size > 0)
			{
                //__android_log_print(ANDROID_LOG_ERROR, "DYP2P", "%s\n", msg);
#if defined(__ANDROID__)
                _log_cb(_log_ctx, ANDROID_LOG_ERROR, msg, msg_size);  //heshuixia 20190625, for android log callback.
                return;
#else
                _log_cb(_log_ctx, 1, msg, msg_size);
                return;
#endif
            }
        }
        platform_time_t pmt;
        platform_get_current_time(&pmt);
        
        char logbuffer[256];
        
        int size = snprintf((char*)logbuffer, sizeof(logbuffer), 
            "%.4d%.2d%.2d %.2d:%.2d:%.2d.%.3d ",
            pmt.tm_year, pmt.tm_mon, pmt.tm_mday,
            pmt.tm_hour, pmt.tm_min, pmt.tm_sec, pmt.tm_msec);
        if(msg_id == PLATFORMLOG_STAT)
        {
        }
        else
        {
#ifdef DY_NETWORK_LOG_HOUR
            if (_platform_log.last_hour != pmt.tm_hour)
            {
                create_log_fd(&_platform_log, &pmt, _log_name.c_str());
                if (_is_flow_log_split)
                {
                    create_log_fd(&_platform_flow_log, &pmt, _flow_log_name.c_str());
                }
            }
#else
            if (_platform_log.last_day != pmt.tm_mday)
            {
                create_log_fd(&_platform_log, &pmt, _log_name.c_str());
                if (_is_flow_log_split)
                {
                    create_log_fd(&_platform_flow_log, &pmt, _flow_log_name.c_str());
                }
            }
#endif
            if (_is_flow_log_split && msg_id == PLATFORMLOG_FLOW)
            {
                if (_platform_flow_log.log_fd > 0)
                {
                    write(_platform_flow_log.log_fd, logbuffer, size);
                    write(_platform_flow_log.log_fd, msg, msg_size);
                }
            }
            else
            {
                if (_platform_log.log_fd > 0)
                {
                    write(_platform_log.log_fd, logbuffer, size);
                    write(_platform_log.log_fd, msg, msg_size);
                }
            }
            
		}
    }
    
    virtual const std::string get_log_file_name()
    {
        return std::string("dy_server.log");
    }

    virtual const std::string get_flow_file_name()
    {
        return std::string("dy_server.flowlog");
    }

    virtual const std::string get_stat_log_file_name()
    {
        return std::string("dy_server.statlog");
    }

    void set_log_level(int level)
    {
        _log_level = level;
    }

    void set_log_callback(void *log_ctx, p2p_log_cb cb) {
        ScopedLock<PlatformMutex> _lock(_log_mutex);
        _log_cb = cb;
        _log_ctx = log_ctx;
    }

    int get_log_level() 
    {
        return _log_level;
    }
    
    bool init(const char* log_directory)
    {
        CPlatformFileSystem::GetInstance()->InitFileSystem();
        if (log_directory)
        {
            _log_dir = log_directory;

#ifdef _WIN32
        if (_log_dir[_log_dir.size() - 1] != '\\')
        {
            _log_dir += "\\";
        }
        _log_dir = utf8_to_ansi(_log_dir);
#else
            if (_log_dir[_log_dir.size() - 1] != '/')
            {
                _log_dir += "/";
            }
#endif
            
        }
        else
        {
            std::string root_path = CPlatformFileSystem::GetInstance()->GetProcessDirectory();
#ifdef _WIN32
            _log_dir = root_path + "\\log\\";
#else
            _log_dir = root_path + "/log/";
#endif
        }

        if (!_log_module_ptr)
        {
            _log_module_ptr.reset(create_platform_module(1, "net_log"), [](IPlatformModule* p) { destory_platform_module(p); });
            _log_module_wptr = _log_module_ptr;

            _log_module_ptr->attach_module(0, log_init, log_entry, NULL);	// NOTE: log module donot need thread data
            //in-case-of thread creating failed;
            try {
                _log_module_ptr->run_module();
            }
            catch (...)
            {
                return false;
            }
        }

        return true;
    }
    
	bool create_init_directory()
	{
		if (_is_init_log_dir || _log_cb)
		{
			return true;
		}
        _is_init_log_dir = true;
		_log_name = _log_dir + get_log_file_name();
        _flow_log_name = _log_dir + get_flow_file_name();
#if (!defined(__APPLE__))    
        if (0 != create_log_directory(_log_name.c_str()))
        {
            return false;
        }
#endif        
        platform_time_t pmt;
        
        platform_get_current_time(&pmt);
        
        _platform_log.last_hour = -1;
        _platform_log.last_day = -1;
        _platform_log.log_fd = -1;
        _platform_flow_log.last_hour = -1;
        _platform_flow_log.last_day = -1;
        _platform_flow_log.log_fd = -1;
#if (!defined(__ANDROID__)) && (!defined(__APPLE__))      
        if (0 != create_log_fd(&_platform_log, &pmt, _log_name.c_str()))
        {
            return false;
        }

        if (_is_flow_log_split)
        {
            if (0 != create_log_fd(&_platform_flow_log, &pmt, _flow_log_name.c_str()))
            {
                return false;
            }
        }
#endif        
#if (!defined(__ANDROID__)) && (!defined(__APPLE__))
        if (_log_level > PLATFORMLOG_FATAL)
        {
            _log_level = PLATFORMLOG_FATAL;
        }
#else
        if (_log_level >= PLATFORMLOG_INIT)
        {
            _log_level = PLATFORMLOG_INIT;
        }
#endif
        return true;
	}
	
    void clean_expire_log(uint32_t day)
    {
        std::vector<std::string> filelist;
        trave_dir(_log_dir.c_str(), filelist, day);
        NOTICE_LOG("[log_dir:%s,filelist:%zu]clean_expire_log", _log_dir.c_str(), filelist.size());
        std::vector<std::string>::iterator itor = filelist.begin();
        for (; itor != filelist.end(); itor++)
        {
            NOTICE_LOG("[file:%s]delete log file", itor->c_str());
            remove(itor->c_str());
        }
    }

    bool destory()
    {
        _log_module_ptr.reset();
        if (_platform_log.log_fd >= 0)
        {
            close(_platform_log.log_fd);
            _platform_log.log_fd = -1;
        }
        return true;
    }
    
    int create_log_fd(platform_log_t* t, platform_time_t* pmt, const char* log_name)
    {
#ifdef DY_NETWORK_LOG_HOUR
        if (t->last_hour != pmt->tm_hour)
        {
            t->last_hour = pmt->tm_hour;
            snprintf((char*)t->curr_name, sizeof(t->curr_name),
                "%s.%.4d%.2d%.2d%.2d", log_name,
                pmt->tm_year, pmt->tm_mon, pmt->tm_mday, pmt->tm_hour);
            if (t->log_fd >= 0)
            {
                close(t->log_fd);
            }
            t->log_fd = open((const char*)t->curr_name, O_CREAT | O_WRONLY | O_APPEND, NGX_FILE_DEFAULT_ACCESS);
        }
#else
        if (t->last_day != pmt->tm_mday)
        {
            t->last_day = pmt->tm_mday;

            snprintf((char*)t->curr_name, sizeof(t->curr_name), 
                "%s.%.4d%.2d%.2d", log_name,
                pmt->tm_year, pmt->tm_mon, pmt->tm_mday);
            
            if (t->log_fd >= 0)
            {
                close(t->log_fd);
            }
            t->log_fd = open((const char*)t->curr_name, O_CREAT | O_WRONLY| O_APPEND, NGX_FILE_DEFAULT_ACCESS);
        }
#endif      
        return 0;
    }
private:
	uint32_t _log_level;
    std::shared_ptr<IPlatformModule> _log_module_ptr;
    std::weak_ptr<IPlatformModule> _log_module_wptr;

    std::string _log_dir;
    std::string _log_name;
    std::string _flow_log_name;
    platform_log_t _platform_log;
    platform_log_t _platform_flow_log;
    p2p_log_cb _log_cb;
    void* _log_ctx;
    PlatformMutex _log_mutex;
	bool _is_init_log_dir = false;
    bool _is_flow_log_split = false;
};



void platform_setloglevel(uint32_t level)
{
    if (level < PLATFORMLOG_DEBUG)
    {
        level = PLATFORMLOG_DEBUG;
    }
#if (!defined(__ANDROID__)) && (!defined(__APPLE__))
    if (level > PLATFORMLOG_FATAL)
    {
        level = PLATFORMLOG_FATAL;
    }
#else
    if (level >= PLATFORMLOG_INIT)
    {
        level = PLATFORMLOG_INIT;
    }
#endif

    g_dynetwork_log->set_log_level(level);
}

void platform_clean_expire_log(uint32_t day)
{
    g_dynetwork_log->clean_expire_log(day);
}

void platform_setlogcallback(void *log_ctx, p2p_log_cb cb){
    if(g_dynetwork_log){
        g_dynetwork_log->set_log_callback(log_ctx, cb);
    }
}

uint32_t platform_getloglevel()
{
	return g_dynetwork_log->get_log_level();
}

uint32_t  get_log_level()
{
	return g_dynetwork_log->get_log_level();
}

#ifndef _WIN32
int create_log_directory(const char* filename)
{
    uint32_t count = 0;
    char find = '/';

    char* p = (char*)strchr(filename + 1, find);

    while (p)
    {
        *p = 0;
        if (-1 == access(filename, F_OK))
        {
            if (-1 == mkdir(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
            {
                return -1;
            }
        }
        *p = find;
        p = strchr(p + 1, find);
        count++;
        if (count > 100)
        {
            return -1;
        }
        }
    return 0;
    }
#else
int create_log_directory(const char* filename)
{
    uint32_t count = 0;
    char find = '\\';
    char* p = (char*)strchr(filename, find);

    while (p)
    {
        *p = 0;
        
        if (-1 == access(filename, F_OK))
        {
            if (-1 == _mkdir(filename))
            {
                return -1;
            }
        }
        *p = find;
        p = strchr(p + 1, find);
        count++;
        if (count > 100)
        {
            return -1;
        }
    }
    return 0;
}
#endif

ILog* createLog()
{
    return new PlatformLog(false);
}

void platform_localtime(struct tm *tm)
{
    struct tm  *t;
	time_t s;
	time(&s);
    t = localtime(&s);
    *tm = *t;

    tm->tm_mon++;
    tm->tm_year += 1900;
}

void platform_gmtime(time_t t, platform_tm_t *tp)
{
    int32_t   yday;
    uint32_t  n, sec, min, hour, mday, mon, year, wday, days, leap;

    n = (uint32_t) t;

    days = n / 86400;

    wday = (4 + days) % 7;

    n %= 86400;
    hour = n / 3600;
    n %= 3600;
    min = n / 60;
    sec = n % 60;

    days = days - (31 + 28) + 719527;

    year = (days + 2) * 400 / (365 * 400 + 100 - 4 + 1);

    yday = days - (365 * year + year / 4 - year / 100 + year / 400);

    if (yday < 0)
	{
        leap = (year % 4 == 0) && (year % 100 || (year % 400 == 0));
        yday = 365 + leap + yday;
        year--;
    }

    mon = (yday + 31) * 10 / 306;

    mday = yday - (367 * mon / 12 - 30) + 1;

    if (yday >= 306)
	{
        year++;
        mon -= 10;
    }
	else
	{
        mon += 2;
    }

    tp->tm_sec = sec;
    tp->tm_min = min;
    tp->tm_hour = hour;
    tp->tm_mday = mday;
    tp->tm_mon = mon;
    tp->tm_year = year;
    tp->tm_wday = wday;
}

void get_current_tm(platform_tm_t* pmt)
{
	platform_localtime(pmt);
}

static bool _g_log_init = false;
static PlatformMutex _g_log_mutex;

bool platform_log_init(ILog* log, const char* log_directory, bool flow_log_split)
{
    if (false == _g_log_init)
    {
        ScopedLock< PlatformMutex> lock(_g_log_mutex);
        if (false == _g_log_init)
        {
            _g_log_init = true;
            if (NULL == log)
            {
                ILog* default_log = new PlatformLog(flow_log_split);
                g_dynetwork_log = default_log;
                return default_log->init(log_directory);
            }
            else
            {
                g_dynetwork_log = log;
                return log->init(log_directory);
            }
         
        }
        
    }
    return true;
}

void platform_log_destroy()
{
    if (_g_log_init)
    {
        ScopedLock< PlatformMutex> lock(_g_log_mutex);
        if (_g_log_init)
        {
            g_dynetwork_log->destory();
            _g_log_init = false;
        }
    }
    
	
}

void log_init( void )
{
}

uint32_t log_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pThreadData)
{
    PlatformLog* obj = (PlatformLog*)sender;
    obj->write_log((const char*)msg, msg_size, msg_id);
	
	return 0;
}
