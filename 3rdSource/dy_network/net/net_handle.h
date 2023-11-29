#ifndef __NETHANDLE_H__
#define __NETHANDLE_H__

#include <stdint.h>

typedef uint64_t NetHandle;

#define GETSOCKETINDEX(handle) (handle & 0xfffff)

#define INVALID_NET_HANDLE 0xffffffff

#define NET_HANDLE_CLIENT_FLAG ((uint64_t)1 << 31)

#endif //__NETHANDLE_H__
