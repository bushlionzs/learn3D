#ifndef __PLATFORMSOCKET_H__
#define __PLATFORMSOCKET_H__
#include <platform_mutex.h>
#include <scoped_lock.h>
#include <net_define.h>
#include <net_handle.h>
#include <netlib_error.h>
#include <sock_base.h>
#include <net_ssl.h>

#include "net_helper.h"


class NetConnection;
class INetSession;
class IClientConnection;
class INetBuffer;
class CBuffer;
class IMultiSendPacket;




class PlatformSocket: public SockBase
{
	friend class PlatformIO;
public:
	static bool PlatformSocketInit();
public:
	PlatformSocket( INetSession* session , NetProtocol protocol , const SessionData& sessionData);
	virtual ~PlatformSocket();
public:
    

	bool IsValid() {return true;}
	bool CreateSocketOnly(void* s);
	bool SetSocketOption();
    bool set_tcp_keepalive(const TcpKeepAliveOption *options);
	bool CreateSocket();
	bool AcceptSocket(PlatformSocket* client);
    void update_socket_addrs(void *buffer);
	bool DestroySocket(int magic = 0);
	bool DelayCloseSocket();
	void DelayDelete();
	bool DelaySendData();
	bool DelayRecvData();
	bool DelaySSL();
	virtual bool OnConnected(struct IOThredData* io_thread_data) override;

	bool ssl_connect(struct IOThredData* io_thread_data, bool recv);

	virtual PlatformSocket* CreateAcceptSocket( void*  ){ return NULL;}
    virtual bool OnIOBinded() override;

	
	virtual void OnRecv(const char* buf, uint32_t size) {}
	virtual void OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen){}
	virtual bool OnAccept();
	virtual void OnClose();
	virtual void OnSessionChanged();

	void StoreExtraParam(void* param)
	{
		_sessionData.m_param = param;
	}

	virtual void get_stat_info(net_lib_stat_t& info);

	virtual bool RecvData(struct IOThredData* io_thread_data, OVERLAPPEDPLUS* olrecv, uint32_t size) override;


	int SendUdp( const uint8_t* data, uint32_t size, const sockaddr *addr, int addrlen);
	int SendTcp( const uint8_t* data , uint32_t size);

	bool RecvUdp(struct IOThredData* io_thread_data, INetBuffer* recv_buf);

	int32_t RecvTcp(struct IOThredData* io_thread_data, INetBuffer* recv_buf, uint32_t limit);
	virtual bool conn_reusing(){ return true;}

	virtual uint32_t GetLeftData()
	{
		return 0;
	}
	
	NetProtocol GetProtocol()
	{
		return m_protocol;
	}

	const SessionData& GetSessionData()
	{
		return _sessionData;
	}

	

	virtual void* GetResource()override
	{
		return (void*)m_socketFd;
	}

    bool is_socket_valid();

	int GetSockError( WSAOVERLAPPED* pWSAOVERLAPPED );

	int32_t ssl_transfer();
	
	int32_t SendDirect(CBuffer* send_buf, const char* buf, uint32_t size);
	int32_t WriteSome(const void* buf, uint32_t size);

	

	virtual CBuffer* get_send_buffer() { return NULL; }
	virtual CBuffer* get_ssl_buffer() { return NULL; }
	virtual INetBuffer* get_recv_buffer() { return NULL; }
private:
	int GetSocketType( NetProtocol protocol );
	int GetSocketProtocol( NetProtocol protocol );
	bool MakeSocketNonBlocking();

protected:
	EventOverPlus m_olEventClose;
	EventOverPlus m_olEventRecv;
	EventOverPlus m_olEventSend;
	EventOverPlus m_olEventSSL;
	OVERLAPPEDPLUS m_olConnect;
	OVERLAPPEDPLUS m_olSend;
	OVERLAPPEDPLUS m_olRecv;
	AcceptOverPlus m_olAccept;
	SOCKET         m_socketFd;
	NetProtocol    m_protocol;
	
	DWORD  m_sendbyte;

	PlatformMutex m_mutex;
	bool           m_IsListeningSocket;

	ssl_connection_t *_ssl_connection;



	

	bool m_is_connected;

    uint64_t _send_bytes;
	uint64_t _recv_bytes;
    // for debuging
    
};


#endif //__PLATFORMSOCKET_H__
