#ifndef __NET_STAT_H__
#define __NET_STAT_H__

#include <net_define.h>

void net_lib_stat_init();

void get_net_lib_stat_info(net_lib_stat_t& stat);
bool get_stat_info_single(NetHandle h, net_lib_stat_t& stat);
void incr_recv_data_size(uint32_t n);
void incr_send_data_size(uint32_t n);
#endif //__NET_STAT_H__