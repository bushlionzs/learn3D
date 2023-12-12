#ifndef __NETMANAGER_H__
#define __NETMANAGER_H__

#include <net_define.h>
#include <net_handle.h>
#include <inet_session.h>
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <vector>
#include <set>
#include <list>

class INetSession;
class SockBase;
class IClientConnection;
class PlatformSocketFactory;
struct NetContext
{
    NetHandle m_netHandle;
	int32_t  m_nRef;
    SockBase* m_pSock;
};

#define NET_MUTEX_COUNT 31
class NetManager
{
    friend class DyNetworkContaintor;
public:
    static NetManager* GetInstance();
    void destroy();

    NetHandle createClientConnection(INetSession* session, NetProtocol protocol, const SessionData& sessionData);
    NetHandle createServerQuicConnection(INetSession* session, 
                                            NetProtocol protocol, 
                                            const SessionData& sessionData);
    NetHandle createServerConnection(INetSession* session, NetProtocol protocol, const SessionData& sessionData);
    bool GetClientConnectionInfo(const NetHandle& handle, SessionData& sessionData);
    bool ClientConnectionValid(const NetHandle& handle);
    bool ClientConnectionReusing(const NetHandle& handle);

    NetHandle CreatePipe(INetSession* session, const std::string& name, bool client);
   

    int32_t SendData(const NetHandle& handle, const uint8_t* data, uint32_t size, SndData* param);
    int32_t Send(const NetHandle& handle);

    uint32_t GetLeftData(const NetHandle& handle);

    bool InitializeConnection(const NetHandle& handle);
    bool InitializeQuicConnection(const NetHandle& handle);
    SockBase* RefHandle(const NetHandle& handle);
    SockBase* UnrefHandle(const NetHandle& handle);

    void ReleaseHandle(SockBase* sock);
    bool AccordClose(const NetHandle& handle);
    bool BindHandle(const NetHandle& handle);
    
    bool StoreExtraParam(const NetHandle& handle, void* param);
	
	bool set_tcp_keepalive(const NetHandle& handle, const TcpKeepAliveOption *options);

    void init(uint32_t max_connection_cnt);

    NetHandle allocNetHandle(SockBase* sock, bool isclient = false);

    uint32_t get_max_connection_count()
    {
        return m_connList.size();
    }

    uint32_t get_alloc_count()
    {
        return m_allocIndexSet.size();
    }

    uint32_t get_free_count()
    {
        return m_freeIndexList.size();
    }

    void handle_test();
private:
	
    NetManager(PlatformSocketFactory* ps_factory)
    {
        _ps_factory = ps_factory;
    }
    

	void releaseIndex(int32_t index);

	NetManager();

	~NetManager();
	

	std::vector<NetContext> m_connList;
    std::list<uint32_t> m_freeIndexList;
    std::set<uint32_t> m_freeIndexSet;
    std::set<uint32_t> m_allocIndexSet;
    
	PlatformMutex m_mutex[NET_MUTEX_COUNT];
    PlatformMutex _index_mutex;
	uint32_t m_nFlag;
    PlatformSocketFactory* _ps_factory;
};

#endif //__NETMANAGER_H__
