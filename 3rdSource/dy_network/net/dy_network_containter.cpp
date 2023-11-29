#include "dy_network_containter.h"
#include <platform_io.h>
#include <platform_socket.h>

#include <platform_socket_factory.h>
#include <net_manager.h>
#include <platform_thread.h>
#include <platform.h>
#include <platform_log.h>
#include <platform_util.h>
#include <net_stat.h>
#include <net_ssl.h>
#include <time_util.h>
#include <websocket_buffer.h>
#include <net_factory.h>
#include <platform_socket_factory.h>
#include "dy_dns.h"

#ifdef _WIN32
#define platform_geterror ::GetLastError()
#else
#define platform_geterror  errno
#endif
struct NetLibParam g_param;
IPlatformModule* DyNetworkContaintor::_asyn_module = nullptr;
int32_t net_platfom_timer_callback(void* param)
{
    NetHandle h = (NetHandle)param;
    int ret = NetManager::GetInstance()->Send(h);
    if (ret != NetlibError_None)
    {
        FATAL_LOG("[handle:%" PRIu64 ",ret:%d]fail to asyn send", h, ret);
    }
    return 0;
}

void post_async_handle(NetHandle h)
{
    uint32_t idx = h % g_param._async_io_thread_count;
    DyNetworkContaintor::_asyn_module->post_module_message(idx, 0, 0, (uint64_t)h, 0, 0);
}

static void async_init()
{
}

static uint32_t async_entry(uint32_t moduleid, uint32_t msg_id, uint64_t sender, uint64_t param, void* msg, uint32_t msg_size, void* pNetThreadData)
{
    NetHandle h = (NetHandle)param;
    int ret = NetManager::GetInstance()->Send(h);
    if (ret != NetlibError_None)
    {
        FATAL_LOG("[handle:%" PRIu64 ",ret:%d]fail to asyn send", h, ret);
    }
    return 0;
}

DyNetworkContaintor::DyNetworkContaintor()
{
}

DyNetworkContaintor::~DyNetworkContaintor()
{

}

bool DyNetworkContaintor::init(struct NetLibParam* param)
{
    if (_net_init)
    {
        return true;
    }
    ScopedLock< PlatformMutex> lock(_net_mutex);
    if (_net_init)
    {
        return true;
    }

    if (param != NULL)
    {
        g_param = *param;
    }

    if (g_param._io_thread_count > 8)
    {
        g_param._io_thread_count = 8;
    }

    if (g_param._max_queuing_connection_number > 10000)
    {
        g_param._max_queuing_connection_number = 10000;
    }

    if (g_param._max_recv_buffer_size > 10 * 1024 * 1024)
    {
        g_param._max_recv_buffer_size = 10 * 1024 * 1024;
    }

    if (g_param._net_lib_buffer_block_size > 512 * 1024)
    {
        g_param._net_lib_buffer_block_size = 512 * 1024;
    }
    if (g_param._net_lib_buffer_block_size < 16 * 1024)
    {
        g_param._net_lib_buffer_block_size = 16 * 1024;
    }

    if (nullptr == _net_factory)
    {
        _net_factory = new NetFactory;
    }

    if (nullptr == _platform_socket_factory)
    {
        _platform_socket_factory = new PlatformSocketFactory;
    }

    if (nullptr == _net_manager)
    {
        _net_manager = new NetManager(_platform_socket_factory);
    }

    if (nullptr == _platform_io)
    {
        _platform_io = new PlatformIO();
    }

    if (g_param._is_async_send)
    {
        if (nullptr == _asyn_module)
        {
            _asyn_module = create_platform_module(g_param._async_io_thread_count, "asyn_io");

            for (uint32_t i = 0; i < g_param._async_io_thread_count; i++)
            {
                _asyn_module->attach_module(i, async_init, async_entry, NULL);
            }
            _asyn_module->run_module();
        }
    }

    net_lib_stat_init();

    if (!PlatformSocket::PlatformSocketInit())
    {
        INIT_LOG("platform socket init failed, err:%d", platform_geterror);
        return false;
    }

    platform_timer_init();

    if (!_platform_io->InitIO())
    {
        INIT_LOG("platform io init failed, err:%d", platform_geterror);
        return false;
    }

    _platform_io->RunIO();

#ifdef __WEBSOCKET__
    WebsocketBuffer::websocket_thread_init();
#endif
    if (0 != net_ssl_init(g_param._ssl_crt_file_name.c_str(), g_param._ssl_key_file_name.c_str(), g_param._ssl_cdn))
    {
        INIT_LOG("net_ssl_init failed");
        return false;
    }

    INIT_LOG("net_ssl_init,crt:%s,key:%s", g_param._ssl_crt_file_name.c_str(), g_param._ssl_key_file_name.c_str());

    _net_manager->init(g_param._max_connection_cnt);

    DNSConfig dns_config;
    dns_config.timeout = g_param._dns_timeout;
    dns_config.use_ip6 = g_param._dns_enable_ip6;
    dns_config.local_port = g_param._dns_client_port;
    dns_config.cache_limit_size = g_param._dns_cache_limit;
    dns_config.ip_stack_affinity = g_param._ip_stack_affinity;

    if (0 != dns_init(dns_config))
    {
        return false;
    }

    _net_init = true;
    return true;
}

void DyNetworkContaintor::destory()
{
    ScopedLock< PlatformMutex> lock(_net_mutex);
    if (!_net_init)
    {
        return;
    }
    _platform_io->StopIO();
    _net_manager->destroy();

    cross_sleep(1);
    platform_timer_destroy();
    if (_asyn_module != NULL)
    {
        destory_platform_module(_asyn_module);
        _asyn_module = NULL;
    }

    WebsocketBuffer::websocket_thread_uninit();

    _net_init = false;
}
