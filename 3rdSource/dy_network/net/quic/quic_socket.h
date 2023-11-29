#pragma once

#include <memory>
#include <list>
#include <platform_socket.h>
#include "quic_engine_base.h"
#include "platform_util.h"
#include "inet_session.h"
#include "multi_send_buffer.h"
#include "function_view.h"
#include "rtmp_chunk_slice.h"

enum QuicSendMode : uint8_t
{
    QSM_INIT            = 0,
    QSM_Normal          = 1,
    QSM_FLV_TAG         = 2
};

//////////////////////////////////////////////////
class QuicServerSocket : public PlatformSocket
{
public:
    QuicServerSocket( INetSession* session ,NetProtocol protocol , const SessionData& sessionData );
    ~QuicServerSocket();

    // implementation of PlatformSocket
	virtual bool OnIOBinded();
    virtual bool Recv(struct IOThredData* io_thread_data);
    void OnSend(uint32_t ioSize);
    virtual void OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen);
    virtual int32_t Send(const uint8_t* data, uint32_t size, SndData* param);
    virtual int32_t SendQuic(const iovec *msgs, size_t nmsgs, SndData *params);
    virtual int32_t Send();

    QuicSocket* on_new_stream_socket(lsquic_stream_t* quic_stream);

private:
    int32_t send_nolock();

private:
    CUdpSendBuffer* m_sendBuffer = nullptr;
    QuicEngineBase* _qc_engine = nullptr;
    bool _sending = false;
};


//////////////////////////////////////////////////
class QuicSocket : public PlatformSocket
{
public:
    QuicSocket(INetSession* session, 
                NetProtocol protocol, 
                const SessionData& sessionData, 
                QuicEngineBase* qc_engine,
                lsquic_stream_t* quic_stream);
    virtual ~QuicSocket();

    virtual bool OnInit() override;

    virtual int32_t multi_send(IMultiSendPacket* pkt);
    virtual int32_t Send(const uint8_t* data, uint32_t size, SndData* param);
    virtual int32_t sendv(const iovec *msgs, size_t nmsgs, SndData *params);
    virtual uint32_t GetLeftData();

    virtual bool OnAccept()
    {
        return true;
    }

    virtual CBuffer* get_send_buffer() { return m_sendBuffer; }
    virtual INetBuffer* get_recv_buffer() { return m_recvBuffer; }

    bool DestroySocket(int magic);

    int32_t write_to_quic_buffer(FunctionView<int(const uint8_t*, uint32_t)> f);

    bool UpdateIpInfo(const std::string& remote_ip, 
                        uint16_t remote_port,
                        const std::string& local_ip, 
                        uint16_t local_port);

private:

    uint32_t get_max_pkt_list_size();

protected:
    CBuffer* m_sendBuffer = nullptr;
    INetBuffer* m_recvBuffer = nullptr;

    lsquic_stream_t* _quic_stream = nullptr;

    QuicEngineBase* _qc_engine = nullptr;

    uint32_t _pkt_list_size = 0;
    std::list<IMultiSendPacket*> _pkt_list;
    std::shared_ptr<IChunkSlice> _pkt_chunk_slice;

    bool _is_fresh = true;
    uint32_t _create_time = 0;
};


//////////////////////////////////////////////////
class ServerQuicClientSocket : public QuicSocket
{
public:
    ServerQuicClientSocket(INetSession* session, 
                            NetProtocol protocol, 
                            const SessionData& sessionData, 
                            QuicEngineBase* qc_engine,
                            lsquic_stream_t* quic_stream);
    ~ServerQuicClientSocket();

    virtual bool OnAccept();

    virtual bool Recv(struct IOThredData* io_thread_data) { return false; }
};


//////////////////////////////////////////////////
class QuicClientSocket : public QuicSocket
{
public:
    QuicClientSocket(INetSession* session, NetProtocol protocol, const SessionData& sessionData);
    virtual ~QuicClientSocket();

    virtual bool OnIOBinded();
    virtual void OnSend(uint32_t ioSize);
    virtual bool Recv(struct IOThredData* io_thread_data);
    virtual void OnRecvUdp(const char* buf, uint32_t size, const sockaddr *addr, int addrlen);
    virtual int32_t SendQuic(const iovec *msgs, size_t nmsgs, SndData *params);
    virtual int32_t Send();

    bool on_connected();

private:
    int32_t send_nolock();

private:
    CUdpSendBuffer* m_quic_send_buffer = nullptr;
    bool _sending = false;
};