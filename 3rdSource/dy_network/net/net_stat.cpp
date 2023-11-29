#include <net_stat.h>
#include <atomic>
#include <net_manager.h>
#include <platform_socket.h>

struct net_lib_stat_private_t
{
    std::atomic<int64_t> _recv_bytes;
    std::atomic<int64_t> _send_bytes;
};

static net_lib_stat_private_t _net_lib_stat;

void net_lib_stat_init()
{
    _net_lib_stat._recv_bytes = 0;
    _net_lib_stat._send_bytes = 0;
}

void get_net_lib_stat_info(net_lib_stat_t& stat)
{
    stat._recv_bytes = _net_lib_stat._recv_bytes;
    stat._send_bytes = _net_lib_stat._send_bytes;
}

bool get_stat_info_single(NetHandle h, net_lib_stat_t& stat)
{
    PlatformSocket* ps = (PlatformSocket*)NetManager::GetInstance()->RefHandle(h);
    if (ps)
    {
        ps->get_stat_info(stat);
        NetManager::GetInstance()->UnrefHandle(h);
        return true;
    }
    else
    {
        return false;
    }
}

void incr_recv_data_size(uint32_t n)
{
    _net_lib_stat._recv_bytes += n;
}

void incr_send_data_size(uint32_t n)
{
    _net_lib_stat._send_bytes += n;
}