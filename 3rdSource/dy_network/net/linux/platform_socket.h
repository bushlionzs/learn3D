#ifndef __PLATFORMSOCKET_H__
#define __PLATFORMSOCKET_H__
#include <stdio.h>
#include <stdint.h>
#include <net_define.h>
#include <net_handle.h>
#include <netlib_error.h>
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <net_ssl.h>
#include <sock_base.h>
#include "rate_limiter.h"


class NetConnection;
class INetSession;
class IClientConnection;
class INetBuffer;
struct iovec;
class IMultiSendPacket;


class PlatformSocket:public SockBase
{
    friend class NetConnection;
public:
    static bool PlatformSocketInit();
public:
    PlatformSocket( INetSession* session , NetProtocol protocol , const SessionData& sessionData );
    virtual ~PlatformSocket();
public:
    bool CreateSocketOnly(void* socketHandle);
    bool SetSocketOption();
    bool set_tcp_keepalive(const TcpKeepAliveOption *options);
    bool CreateSocket(  );
    bool AcceptSocket( PlatformSocket* server);
    bool DestroySocket(int magic = 0);
    bool DelayCloseSocket();
	void DelayDelete();
    bool DelaySendData();
    bool DelayRecvData();
    bool OnConnected();

    bool Wait() {return true;}

    virtual PlatformSocket* CreateAcceptSocket(void* socket) {return NULL;}
    virtual bool OnInit(){return true;}
    virtual bool OnIOBinded() { return true; }
    virtual void OnSend( uint32_t ioSize );
    virtual void OnRecv(const char* buf, uint32_t size){}
    virtual void OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen){}
    virtual bool OnAccept();
    virtual void OnClose();
	virtual void OnSessionChanged();
    virtual int GetSockFd()override
    {
        return m_socketFd;
    }
    
    void StoreExtraParam(void* param)
    {
        _sessionData.m_param = param;
    }
    
    virtual void get_stat_info(net_lib_stat_t& info);
    
    virtual int32_t multi_send(IMultiSendPacket *pkt) { return NetlibError_SocketError; }
    virtual int32_t sendv(const iovec *msgs, size_t nmsgs, SndData *params) { return NetlibError_SocketError; }

    virtual int32_t Send( const uint8_t* data , uint32_t size , SndData* param );
    virtual int32_t Send(){ return NetlibError_SocketError; }
    int SendUdp( const uint8_t* data , uint32_t size , const sockaddr *addr, int addrlen);

    int SendTcp( const uint8_t* data , uint32_t size );

    virtual bool Recv(struct IOThredData* io_thread_data){return false;}
    bool RecvUdp(struct IOThredData* io_thread_data, INetBuffer* recv_buf);
    int32_t RecvTcp(struct IOThredData* io_thread_data, INetBuffer* recv_buf, uint32_t limit);
    bool RecvRaw();
    virtual bool conn_reusing(){ return true;}

    virtual uint32_t GetLeftData()
    {
        return 0;
    }

    NetProtocol GetProtocol()
    {
        return m_protocol;
    }


    bool IsListenSocket()
    {
        return m_IsListeningSocket;
    }
    
    bool IsValid() const;
    int32_t WriteSome(const void* buf, uint32_t size);
    int32_t WriteV(const iovec* io_vec, uint32_t size);

    virtual INetBuffer* get_recv_buffer() { return NULL; }
private:
    int GetSocketType( NetProtocol protocol );
    int GetSocketProtocol( NetProtocol protocol );
    bool MakeSocketNonBlocking();
    void UpdateSctpInfo( );
    bool UpdateIpInfo();
    bool UpdateRawIpInfo();
protected:
    int            m_socketFd;
    NetProtocol    m_protocol;
#ifndef DY_NETWORK_DISNABLE_SSL
    bool           _is_ssl;
#else
    const bool     _is_ssl = false;
#endif
    uint32_t bufferDataLen;
    PlatformMutex m_mutex;
    PlatformMutex _recv_mutex;

    bool           m_IsListeningSocket;  /**< whether this socket is used for listening other client to connect */
    ssl_connection_t *_ssl_connection;
    
    bool m_is_connected;
    
    int32_t _magic;
    
    uint64_t _send_bytes;
    uint64_t _recv_bytes;
};


#endif //__PLATFORMSOCKET_H__

