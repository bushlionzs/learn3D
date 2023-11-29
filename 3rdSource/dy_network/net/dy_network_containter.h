#pragma once

#include <platform_mutex.h>
#include <scoped_lock.h>
class NetManager;
class PlatformIO;
class IPlatformModule;
class NetFactory;
class PlatformSocketFactory;
struct NetLibParam;

class DyNetworkContaintor
{
public:
    DyNetworkContaintor();
    ~DyNetworkContaintor();
    bool init(struct NetLibParam* param);
    void destory();

    NetFactory* get_net_factory()
    {
        return _net_factory;
    }

    NetManager* get_net_manager()
    {
        return _net_manager;
    }

    PlatformIO* get_platform_io()
    {
        return _platform_io;
    }
public:
    static IPlatformModule* _asyn_module;
private:
    NetManager* _net_manager = nullptr;
    PlatformIO* _platform_io = nullptr;
    NetFactory* _net_factory = nullptr;
    PlatformSocketFactory* _platform_socket_factory = nullptr;
    PlatformMutex _net_mutex;
    bool _net_init = false;
};