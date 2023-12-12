#ifndef __NETLIB_H__
#define __NETLIB_H__

#include <net_define.h>
#include <inet_session.h>
#include <net_factory.h>
#include <netlib_error.h>

bool netlib_init(struct NetLibParam* param = nullptr);
void netlib_destroy();


#endif //__NETLIB_H__
