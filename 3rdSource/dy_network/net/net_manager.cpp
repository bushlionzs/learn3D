
#include <stdio.h>
#include <assert.h>
#include <net_manager.h>
#include <platform_socket.h>
#include <platform_socket_factory.h>
#include <platform_thread.h>
#include <platform_log.h>
#include <platform.h>
#include <inet_session.h>
#include "netlib_error.h"
#include "platform_io.h"
#include <net_define.h>
#include <platform_util.h>
#include <dy_network_containter.h>

extern DyNetworkContaintor *g_dy_network_containtor;
extern struct NetLibParam g_param;

#ifdef _WIN32
#define WIN_ASSERT(v) assert(v)
#else
#define WIN_ASSERT(v)
#endif
NetManager* NetManager::GetInstance()
{
    return g_dy_network_containtor->get_net_manager();
}

NetManager::NetManager()
{
	
}

NetManager::~NetManager()
{
}

void NetManager::init(uint32_t max_connection_cnt)
{
	m_nFlag = 0;
	m_connList.resize(max_connection_cnt);
	for (uint32_t index = 0; index < m_connList.size(); index++)
	{
		m_connList.at(index).m_netHandle        = INVALID_NET_HANDLE;
        m_connList.at(index).m_pSock = NULL;
		m_connList.at(index).m_nRef             = 0;
        if (index > 0)
        {
            m_freeIndexList.push_back(index);
            m_freeIndexSet.insert(index);
        }
	}
}

void NetManager::destroy()
{
	for (uint32_t index = 0; index <  m_connList.size(); index++)
	{
		if (m_connList.at(index).m_netHandle != INVALID_NET_HANDLE)
		{
		#ifdef _WIN32
			AccordClose(m_connList.at(index).m_netHandle);
		#else
			UnrefHandle(m_connList.at(index).m_netHandle, true);
		#endif 
		}
	}
	m_freeIndexList.clear();
	m_freeIndexSet.clear();
	m_allocIndexSet.clear();
}

NetHandle NetManager::createClientConnection(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
{
	SessionData tmp = sessionData;
	tmp.m_is_client = 1;
	PlatformSocket* platformSocket = _ps_factory->CreatePlatformSocket(session, protocol, tmp);
	if (NULL != platformSocket)
	{
		return allocNetHandle(platformSocket, true);
	}
    FATAL_LOG("platformSocket create failed!");
	return INVALID_NET_HANDLE;
}

NetHandle NetManager::createServerQuicConnection(INetSession* session, 
                                                NetProtocol protocol, 
                                                const SessionData& sessionData)
{
    PlatformSocket* platformSocket = _ps_factory->CreatePlatformSocket(session, protocol, sessionData);
    if (NULL != platformSocket)
    {
        return allocNetHandle(platformSocket, true);
    }
    FATAL_LOG("platformSocket create failed!");
    return INVALID_NET_HANDLE;
}

NetHandle NetManager::createServerConnection(INetSession* session, NetProtocol protocol, const SessionData& sessionData)
{
	NetHandle handle = INVALID_NET_HANDLE;

	PlatformSocket* platformSocket = _ps_factory->CreatePlatformSocket(session, protocol, sessionData);
	if (NULL != platformSocket)
	{
        handle = this->allocNetHandle(platformSocket);
	}

	return handle;
}

bool NetManager::GetClientConnectionInfo(const NetHandle& handle, SessionData& sessionData)
{
	PlatformSocket* platformSocket = (PlatformSocket*)RefHandle( handle );
	if( platformSocket )
	{
		sessionData = platformSocket->GetSessionData();
        UnrefHandle(handle);
		return true;
	}
	else
	{
		return false;
	}
}

bool NetManager::ClientConnectionValid(const NetHandle& handle)
{
    bool valid = false;
    PlatformSocket* platformSocket = (PlatformSocket*)RefHandle( handle );
    if( platformSocket )
    {
        if(platformSocket->IsValid())
        {
            valid = true;
        }
        UnrefHandle(handle);
    }
    return valid;
}

bool NetManager::ClientConnectionReusing(const NetHandle& handle)
{
    bool success = false;
    PlatformSocket* platformSocket = (PlatformSocket*)RefHandle( handle );
    if( platformSocket )
    {
        success = platformSocket->conn_reusing();
        UnrefHandle(handle);
    }
    return success;
}

NetHandle NetManager::CreatePipe(INetSession* session, const std::string& name, bool client)
{
    NetHandle handle = INVALID_NET_HANDLE;
    SockBase* sock = _ps_factory->CreatePlatformPipe(session, name, client);
    if (NULL != sock)
    {
        handle = allocNetHandle(sock);
    }

    return handle;

}



int32_t NetManager::SendData(const NetHandle& handle, const uint8_t* data, uint32_t size, SndData* param)
{
	SockBase* sock = RefHandle(handle);
	if(sock)
	{
		int32_t ret = sock->Send(data, size, param);
		UnrefHandle(handle);
		return ret;
	}
	else
	{
		return NetlibError_HandleError;
	}
}


int32_t NetManager::Send(const NetHandle& handle)
{
#ifndef _WIN32
    SockBase* sock = RefHandle(handle);
	if( sock )
	{
		int32_t ret = sock->Send();
		UnrefHandle(handle);
		return ret;
	}
	else
	{
		return NetlibError_HandleError;
	}
#else
    return NetlibError_None;
#endif
}

bool NetManager::CloseHandle(const NetHandle& handle)
{
#ifdef _WIN32
    return AccordClose(handle);
#else
	return UnrefHandle(handle, true);
#endif
}

uint32_t NetManager::GetLeftData(const NetHandle& handle)
{
	PlatformSocket* platformSocket = (PlatformSocket*)RefHandle(handle);
	if( platformSocket )
	{
		uint32_t ret =  platformSocket->GetLeftData();
		UnrefHandle(handle);
		return ret;
	}
	else
	{
		return 0;
	}
}

bool NetManager::InitializeConnection(const NetHandle& handle)
{
	SockBase* conn = RefHandle(handle);
	if (conn != NULL)
	{
		conn->OnInit();
		bool ret =  PlatformIO::GetInstance()->BindSocket(conn);
        if (ret)
        {
            if (!conn->OnIOBinded())
            {
                ret = false;
            }
        }

        if (!ret)
        {
            ReleaseHandle(conn);
        }

		UnrefHandle(handle);
		return ret;
	}
	else
	{
		return false;
	}
	return true;
}

bool NetManager::InitializeQuicConnection(const NetHandle& handle)
{
    SockBase* conn = RefHandle(handle);
    if (conn != NULL)
    {
        conn->OnInit();
        bool ret =  PlatformIO::GetInstance()->BindSocket(conn);
        if (ret)
        {
            if (!conn->OnIOBinded())
            {
                ret = false;
            }
        }

        if (!ret)
        {
            ReleaseHandle(conn);
        }

        UnrefHandle(handle);
        return ret;
    }
    else
    {
        return false;
    }
    return true;
}


SockBase* NetManager::RefHandle(const NetHandle& handle)
{
    uint32_t idx = handle % NET_MUTEX_COUNT;
	ScopedLock<PlatformMutex> lock(m_mutex[idx]);
	uint32_t index = GETSOCKETINDEX(handle);
	if (index >= m_connList.size())
	{
		return NULL;
	}

	SockBase* conn = m_connList.at(index).m_pSock;

	if (conn == NULL)
	{
		return NULL;
	}

	if (m_connList.at(index).m_netHandle != handle)
	{
		return NULL;
	}
	
	m_connList.at(index).m_nRef++;
	
    conn->ref();

	return conn;
}

SockBase* NetManager::UnrefHandle(const NetHandle& handle, bool destroy)
{
    uint32_t idx = handle % NET_MUTEX_COUNT;
    SockBase* conn = NULL;
    bool need_del = false;
    {
        ScopedLock<PlatformMutex> lock(m_mutex[idx]);
        uint32_t index = GETSOCKETINDEX(handle);
        if (index >= m_connList.size())
        {
            WIN_ASSERT(false);
            return nullptr;
        }

        conn = m_connList.at(index).m_pSock;

        if (conn == nullptr)
        {
            WIN_ASSERT(false);
            return nullptr;
        }

        if (m_connList.at(index).m_netHandle != handle)
        {
            WIN_ASSERT(false);
            return nullptr;
        }

        m_connList.at(index).m_nRef--;

        if (m_connList.at(index).m_nRef <= 0)
        {
            releaseIndex(index);
            m_connList.at(index).m_netHandle = INVALID_NET_HANDLE;
            m_connList.at(index).m_pSock = NULL;
            need_del = true;
        }

        int ret = conn->unref();

        if (ret > 0)
        {
            if (destroy || need_del)
            {
                conn->DelayCloseSocket();
            }
        }
    }
    
	return conn;
}

void NetManager::ReleaseHandle(SockBase* sock)
{
#ifdef _WIN32
    NetHandle handle = sock->GetNetHandle();


    uint32_t idx = handle % NET_MUTEX_COUNT;
    SockBase* conn = NULL;
    {
        ScopedLock<PlatformMutex> lock(m_mutex[idx]);
        uint32_t index = GETSOCKETINDEX(handle);
        if (index >= m_connList.size())
        {
            WIN_ASSERT(false);
            return;
        }

        conn = m_connList.at(index).m_pSock;

        if (conn == NULL)
        {
            WIN_ASSERT(false);
            return;
        }

        if (m_connList.at(index).m_netHandle != handle)
        {
            WIN_ASSERT(false);
            return;
        }

        m_connList.at(index).m_nRef--;
        int ret = sock->unref();
        if (m_connList.at(index).m_nRef <= 0)
        {
            releaseIndex(index);
            m_connList.at(index).m_netHandle = INVALID_NET_HANDLE;
            m_connList.at(index).m_pSock = NULL;
        }
        
    }
#endif
}

bool NetManager::AccordClose(const NetHandle& handle)
{
#ifdef _WIN32
    uint32_t idx = handle % NET_MUTEX_COUNT;
    SockBase* conn = NULL;
    {
        ScopedLock<PlatformMutex> lock(m_mutex[idx]);
        uint32_t index = GETSOCKETINDEX(handle);
        if (index >= m_connList.size())
        {
            return false;
        }

        conn = m_connList.at(index).m_pSock;

        if (conn == NULL)
        {
            return false;
        }

        if (m_connList.at(index).m_netHandle != handle)
        {
            return false;
        }

        conn->DelayCloseSocket();
    }
#endif
    return true;
}

bool NetManager::BindHandle(const NetHandle& handle)
{
    SockBase* sock = RefHandle(handle);
    if (sock)
    {
        bool ret = PlatformIO::GetInstance()->BindSocket(sock);
        UnrefHandle(handle);
        return ret;
    }
    else
    {
        FATAL_LOG("unlikly socket conn is null, handle: %llu", handle);
        return false;
    }
}

bool NetManager::StoreExtraParam(const NetHandle& handle, void* param)
{
    PlatformSocket* pPlatformSocket = (PlatformSocket*)RefHandle(handle);
    if (pPlatformSocket)
    {
        pPlatformSocket->StoreExtraParam(param);
        UnrefHandle(handle);
        return true;
    }
    else
    {
        FATAL_LOG("unlikly socket conn is null, handle: %llu", handle);
        return false;
    }
}

bool NetManager::set_tcp_keepalive(const NetHandle& handle, const TcpKeepAliveOption *options)
{
	PlatformSocket* pPlatformSocket = (PlatformSocket*)RefHandle(handle);
    bool ret = false;
    if (pPlatformSocket)
    {
        ret = pPlatformSocket->set_tcp_keepalive(options);
        UnrefHandle(handle);
    }
    else
    {
        FATAL_LOG("unlikly socket conn is null, handle: %llu", handle);
    }

    return ret;
}

NetHandle NetManager::allocNetHandle(SockBase* sock, bool isclient)
{
    ScopedLock<PlatformMutex> lock(_index_mutex);
	if (m_freeIndexList.empty())
    {
        FATAL_LOG("m_freeIndexList empty!");
        return INVALID_NET_HANDLE;
    }
 
    uint32_t index = *m_freeIndexList.begin();
    m_freeIndexList.pop_front();
    m_allocIndexSet.insert(index);

    NetHandle handle = (uint32_t)index;
    uint64_t flag = m_nFlag++;
    handle |= ( flag << 32 );
    if (isclient)
    {
        handle |= NET_HANDLE_CLIENT_FLAG;
    }
    sock->SetNetHandle( handle );
    m_connList.at(index).m_pSock = sock;
    m_connList.at(index).m_netHandle = handle;
	m_connList.at(index).m_nRef = 1;
    return handle;
}

void NetManager::releaseIndex(int32_t index)
{
    ScopedLock<PlatformMutex> lock(_index_mutex);
    if (m_allocIndexSet.find(index) != m_allocIndexSet.end())
    {
        m_freeIndexList.push_back(index);
        m_allocIndexSet.erase(index);
        m_connList.at(index).m_pSock = NULL;
        m_connList.at(index).m_netHandle = INVALID_NET_HANDLE;
    }
    else
    {
        FATAL_LOG("[index:%d]releaseIndex error", index);
    }
}

void NetManager::handle_test()
{
    int times = 0;
    for (uint32_t i = 0; i < m_connList.size(); i++)
    {
        auto handle = m_connList.at(i).m_netHandle;
        auto ref = m_connList.at(i).m_nRef;

        if (handle != INVALID_NET_HANDLE)
        {
            NOTICE_LOG("[handle:%llu,ref:%d]handle_test", handle, ref);
            times++;
        }

        if (times > 100)
        {
            break;
        }
    }
}