#ifndef __PLATFORM_UTIL_H__
#define __PLATFORM_UTIL_H__

#include <stdint.h>
#include <string>

typedef uint64_t platform_timer_t ;

#define INVALID_TIMER_ID 0

bool platform_timer_init();
bool platform_timer_destroy();
platform_timer_t platform_create_timer(uint32_t duration , int32_t (*platfom_timer_callback)(void* param), void* param);
bool platform_delete_timer( platform_timer_t timer );

bool platform_clean_timer();
#endif //__PLATFORM_UTIL_H__
