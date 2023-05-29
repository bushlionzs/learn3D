#ifndef __TIME_UTIL_H__
#define __TIME_UTIL_H__

#include <stdint.h>
#include <string>
#include "platform_util.h"
#include "timer_logic.h"
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
#include <dirent.h>
#else
#endif
#include "platform_common.h"
#include<platform_thread.h>

typedef struct
{
    uint32_t tm_msec;
    uint32_t tm_sec;   
    uint32_t tm_min;   
    uint32_t tm_hour; 
    uint32_t tm_mday;  
    uint32_t tm_mon;   
    uint32_t tm_year;  
    uint32_t tm_wday;  
    uint32_t tm_yday;  
}platform_time_t;

#define INVALID_TIMER_ID 0

uint64_t get_tick_count();
uint64_t get_tick_count_us();
uint32_t get_seconds();

void cross_sleep( uint32_t millseconds );

int32_t url_decode(const unsigned char* input, uint32_t input_size, char* output);

int get_local_ip(const char* intf_name, std::string& ip);


#ifdef _WIN32
int gettimeofday(struct timeval *tv, struct timezone *tz);
void usleep(uint32_t wait_time);
#endif

bool platform_get_current_time(platform_time_t* pt);

std::string get_current_time_string();

#endif //__TIME_UTIL_H__
