#include <net_lib.h>

#include <dy_network_containter.h>

DyNetworkContaintor *g_dy_network_containtor = new DyNetworkContaintor;

bool netlib_init(struct NetLibParam* param)
{
    return g_dy_network_containtor->init(param);
}

void netlib_destroy()
{
    return g_dy_network_containtor->destory();
}


