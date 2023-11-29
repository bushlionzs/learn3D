#ifndef __CROSSPLATFORMSOCKET_H__
#define __CROSSPLATFORMSOCKET_H__

#include <atomic>

#include <platform_socket.h>

#include <list>
#include "platform_util.h"
#include "inet_session.h"


struct Node
{
	int8_t* m_buffer;
	uint32_t m_size;
};

class StreamSocket;
class CBuffer;
class CUdpSendBuffer;
class INetBuffer;
class MultiSendBuffer;

class ServerSocket: public PlatformSocket
{
public:
	ServerSocket( INetSession* session ,NetProtocol protocol , const SessionData& sessionData );

	~ServerSocket();

	virtual PlatformSocket* CreateAcceptSocket(void* socket);
	virtual bool Recv(struct IOThredData* io_thread_data);
private:
    PlatformSocket* _tmp;
};



class TcpSocket: public PlatformSocket
{
public:
	TcpSocket( INetSession* session ,NetProtocol protocol , const SessionData& sessionData);
	virtual ~TcpSocket();

	virtual void OnSend(uint32_t ioSize);
	virtual int32_t Send( const uint8_t* data , uint32_t size , SndData* param );
	virtual int32_t Send();
	virtual bool Recv(struct IOThredData* io_thread_data);
	virtual bool conn_reusing();
	virtual uint32_t GetLeftData();

    virtual bool OnAccept();
	void OnRecv(const char* buf, uint32_t size);
	virtual void OnEvent(struct IOThredData* io_thread_data, uint32_t event, void* param);

#ifdef _WIN32
	virtual CBuffer* get_send_buffer() { return m_sendBuffer; }
	virtual CBuffer* get_ssl_buffer() { return m_sslBuffer; }
#endif
	virtual INetBuffer* get_recv_buffer() { return m_recvBuffer; }
private:
	int32_t SendNolock();
protected:
#ifdef _WIN32
	CBuffer* m_sslBuffer;
#endif 
	CBuffer* m_sendBuffer;
	INetBuffer* m_recvBuffer;


    bool _delay_sending = false;
};

class ServerTcpClientSocket: public TcpSocket
{
public:
	ServerTcpClientSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData);
    ~ServerTcpClientSocket();
	virtual bool OnAccept();
};


class TcpClientSocket: public TcpSocket
{
public:
	TcpClientSocket(INetSession* session, NetProtocol protocol , const SessionData& sessionData);
    ~TcpClientSocket();
	virtual int32_t Send();
	virtual bool OnInit();
};

class UdpSocket : public PlatformSocket
{
public:
	UdpSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData);
	virtual ~UdpSocket();

	virtual void OnSend(uint32_t ioSize);
	virtual void OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen);
	virtual int32_t Send(const uint8_t* data, uint32_t size, SndData* param);
	virtual int32_t Send();
	virtual bool Recv(struct IOThredData* io_thread_data);
	virtual bool OnInit();
    uint64_t udp_send_buffer_msg_count() const override;
private:
    int32_t send_nolock();
private:
	CUdpSendBuffer* m_sendBuffer;
	INetBuffer* m_recvBuffer;
	bool _sending = false;
	PlatformMutex m_mutex;
    std::atomic<uint64_t> _send_buffer_msg_count{ 0 };
};

#endif //__CROSSPLATFORMSOCKET_H__
