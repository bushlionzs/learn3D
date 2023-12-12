#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__
#include <net_define.h>
#include <netlib_error.h>
#include <net_handle.h>
#include "rate_limiter.h"
#include "inet_session.h"
#include <atomic>
enum
{
    EVENT_DELAY_CLOSE = 0,
    EVENT_DELAY_RECV,
    EVENT_DELAY_SEND,
    EVENT_DELAY_SSL,
    EVENT_DELAY_DELETE
};
#ifdef _WIN32
enum IOType
{
    IOConnect,
    IOUdpConnect,
    IORecv,
    IOSend,
    IOAccept,
    IOEvent,
};

typedef struct OverlappedPlus
{
public:
    OVERLAPPED		    m_ol;
    IOType				m_ioType;
    WSABUF				m_wsaBuffer;
    dy_network::SockaddrStorage m_remoteAddr;
    int					m_remoteAddrLen;
    uint64_t            m_param;
}OVERLAPPEDPLUS, * POVERLAPPEDPLUS;


class PlatformSocket;



typedef struct EventOverPlus
{
public:
    OVERLAPPEDPLUS      m_Ov;
    PlatformSocket* m_Owner;
    uint32_t            m_event;
    void* m_param;
}EVENTOVERPLUS, * PEVENTOVERPLUS;

typedef struct AcceptOverPlus
{
public:
    OVERLAPPEDPLUS      m_Ov;
    PlatformSocket* m_Owner;
    char                m_netBuffer[256];
}ACCEPTOVERPLUS, * PACCEPTOVERPLUS;
#else
#endif

class SockBase
{
public:
    SockBase();
    virtual ~SockBase(){}
    
    virtual bool IsListenSocket() {return false;}
    virtual bool DestroySocket(int magic = 0){return true;}
    virtual int32_t Send(){ return NetlibError_SocketError; }
    virtual int32_t Send(const uint8_t* data, uint32_t size, SndData* param) { return 0; }
    virtual bool OnIOBinded() { return true; }
    virtual bool OnInit() { return true; }
    virtual void OnSend(uint32_t ioSize) {}
    virtual void OnEvent(struct IOThredData* io_thread_data, uint32_t event, void* param) {}
    virtual void OnSessionChanged() {}
	#ifdef _WIN32
    virtual bool RecvData(struct IOThredData* io_thread_data, OVERLAPPEDPLUS* olrecv, uint32_t size) { return false; }
	#endif
    virtual bool OnConnected(struct IOThredData* io_thread_data) { return false; }
    virtual int32_t SendQuic(const iovec *msgs, size_t nmsgs, SndData *params) { return NetlibError_None; }
    virtual bool Recv(struct IOThredData* io_thread_data) = 0;
    virtual bool CreateResource() { return false; }
    virtual void* GetResource() { return nullptr; }
#ifndef _WIN32
    virtual int GetSockFd() { return -1; }
    virtual int GetReadSockFd() { return -1; }
#endif
    virtual void OnClose(){}
	virtual void set_keepalive(){}
    virtual uint64_t udp_send_buffer_msg_count() const { return 0; }
    virtual bool DelayCloseSocket() { return true; }
    virtual void deleleSelf() {}
    virtual bool DelaySSL() { return true; }
    bool ssl_connect(struct IOThredData* io_thread_data) { return true; }
    int32_t ref();
    int32_t unref();

    void SetNetHandle(const NetHandle handle)
    {
        _handle = handle;
    }

    NetHandle GetNetHandle()
    {
        return _handle;
    }

    bool is_bind_io()
    {
        return _is_bind_io;
    }
    void set_bind_io(bool is_bind_io)
    {
        _is_bind_io = is_bind_io;
    }

    INetSession* GetNetSession()
    {
        return _session;
    }
	
	const SessionData& GetSessionData()
	{
		return _sessionData;
	}

    void addLimiter(limiter_node* limiter)
    {
        _limiter = limiter;
    }

    void change_session(INetSession* session);
	
private:
    std::atomic<int32_t> _ref;
    

    bool _is_bind_io = false;
protected:
    INetSession* _session;
    NetHandle _handle;
    SessionData    _sessionData;
    limiter_node* _limiter = nullptr;

    bool           _is_ssl = false;
};

#endif //__SOCKET_BASE_H__
