#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#include <stdint.h>
#include <platform_common.h>
#ifdef WIN32
#define snprintf _snprintf
#endif

bool platform_init(bool is_init_filesystem = false);
void platform_destroy();

#endif //__PLATFORM_H__
