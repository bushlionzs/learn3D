#include "platform_util.h"
#include <timer_logic.h>
#ifndef _WIN32
#include<time.h>
#include<stdio.h>
#include<time.h>
#include<signal.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include <sys/time.h>
#include <sys/types.h>
#if !defined(__ANDROID__)
#include <ifaddrs.h>
#else
#include "utility/getifaddrs.h"
#endif
#include <netdb.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#else
#include <mmsystem.h>
#endif
#include <platform_defines.h>
#include <platform_common.h>
#include<platform_thread.h>
#include <platform_log.h>
#include <time_util.h>
#include <platform_mutex.h>
#include <scoped_lock.h>

#define TIMER_LOGIC_COUNT 4
static highperformance::CTimerLogic g_timer_logic[TIMER_LOGIC_COUNT];
static uint32_t g_timer_logic_thread_count = TIMER_LOGIC_COUNT;
static IPlatformModule* _timer_module = NULL;

static volatile bool _stopped_timer_ = true;
static std::shared_ptr<Thread> _time_trigger_handle;

#ifdef _WIN32
MMRESULT _win_time_id = NULL;
static uint64_t last_timer_triger_time = 0;
void CALLBACK CallBackTimer(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    uint64_t now = get_tick_count();
    if (now - last_timer_triger_time <= TIMER_DURATION / 2) {
        return;
    }
    last_timer_triger_time = now;

    for (uint32_t i = 0; i < g_timer_logic_thread_count; i++)
    {
        _timer_module->post_module_message(i, 0, 0, 0, 0, 0);
    }
}
#endif

static void timer_service_thread(void *arg)
{
    _stopped_timer_ = false;
    while (!_stopped_timer_)
    {
         usleep(TIMER_DURATION * 1000);
         for (uint32_t i = 0; i < g_timer_logic_thread_count; i++)
         {
            _timer_module->post_module_message(i, 0, 0, 0, 0, 0);
         }
    }
}

static void timer_init()
{
}

static uint32_t timer_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg , uint32_t msg_size, void* pNetThreadData)
{
    g_timer_logic[moduleid].update_timer();
    return 0;
}

static PlatformMutex _g_timer_mutex;
extern struct NetLibParam g_param;
bool platform_timer_init()
{
    if (NULL == _timer_module)
    {
        ScopedLock< PlatformMutex> lock(_g_timer_mutex);
        if (NULL == _timer_module)
        {
            g_timer_logic_thread_count = g_param._timer_thread_count;
            if (g_timer_logic_thread_count > TIMER_LOGIC_COUNT)
            {
                g_timer_logic_thread_count = TIMER_LOGIC_COUNT;
            }

            if (g_timer_logic_thread_count == 0)
            {
                return true;
            }

            INIT_LOG("[thread count:%d]timer thread create sucessfully", g_timer_logic_thread_count);
            _timer_module = create_platform_module(g_timer_logic_thread_count, "timer_run");
            for (uint32_t i = 0; i < g_timer_logic_thread_count; i++)
            {
                _timer_module->attach_module(i, timer_init, timer_entry, NULL);	// NOTE: timer module donot need thread data
            }
            _timer_module->run_module();

#ifndef _WIN32
            ThreadData td;
            td.threadfunc = timer_service_thread;
            strcpy(td._name, "timer_trigger");
            _time_trigger_handle = PlatformRunThread(td);
#else
            _win_time_id = timeSetEvent(TIMER_DURATION, 1, CallBackTimer, 0, TIME_PERIODIC);

            if (NULL == _win_time_id)
            {
                return false;
            }
#endif
        }
    }
    return true;
}

bool platform_timer_destroy()
{
    if (NULL != _timer_module)
    {
        ScopedLock< PlatformMutex> lock(_g_timer_mutex);
        if (NULL != _timer_module)
        {
            _stopped_timer_ = true;
#ifdef _WIN32
            if (_win_time_id != NULL)
            {
                timeKillEvent(_win_time_id);
                _win_time_id = NULL;
            }

#else
            _time_trigger_handle->join();
#endif
            if (_timer_module)
            {
                destory_platform_module(_timer_module);
                _timer_module = NULL;
            }
        }

    }

    return true;
}

platform_timer_t platform_create_timer( uint32_t duration , int32_t (*platfom_timer_callback)(void* param ), void* param )
{
    uint64_t idx = (uint64_t)param % g_timer_logic_thread_count;
    uint32_t tid =  g_timer_logic[idx].add_timer( duration , platfom_timer_callback , param );
    if (tid == 0)
    {
        return INVALID_TIMER_ID;
    }
    return (idx << 32) | tid ;
}


bool platform_delete_timer(platform_timer_t timer)
{
    uint64_t idx = timer >> 32;
    uint32_t timerid = (uint32_t)timer;
    bool result = g_timer_logic[idx].delete_timer(timerid);
    return result;
}

bool platform_clean_timer()
{
    for (uint32_t i = 0; i < g_timer_logic_thread_count; i++)
    {
        g_timer_logic[i].clean();
    }
    return true;
}

