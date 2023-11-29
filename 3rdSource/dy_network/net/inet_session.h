#ifndef INETSESSION_H
#define INETSESSION_H

#include <stdint.h>
#include <list>

#include "net_handle.h"
#include "net_helper.h"
#include "ref_count_object.h"

class IClientConnection;
class IServerConnection;
class IServerInterface;
struct SessionData;
struct IOThredData;
struct iovec;
#include <pid.h>

typedef struct
{
    char* _buf;
    uint32_t _size;
}net_buf_pos_t;

class INetBuffer
{
public:
    INetBuffer(IServerInterface* server, uint32_t capacity, bool need_split = true);
	virtual ~INetBuffer();
    virtual net_buf_pos_t* get_recv_buf(struct IOThredData* io_thread_data);
    virtual bool recv_data(const char* data, uint32_t size, const SessionData& sd);
	virtual void recv_udp_data(const char* data, uint32_t size, const sockaddr *addr, int addrlen) {}
    virtual bool OnHandle(NetHandle, const SessionData&);
    virtual bool process_data(const SessionData& sd) = 0;
    virtual void conn_reusing() {}
    virtual void data_reset() {}
    virtual void reset() {}
    void printdata();
protected:
	uint32_t _capacity;
	int32_t _start;
	int32_t _end;
    char* _buf;
    NetHandle _net_handle;
    
    IServerInterface* _server;
    bool _need_split;
    net_buf_pos_t _net_buf_pos;
};




#define _SND_BUF_SIZE  (32*1024)
class INetSession
{
public:
	virtual ~INetSession();
	virtual void OnClose(NetHandle, const SessionData& ) = 0;
	virtual void OnAccept(NetHandle, const SessionData&);
    virtual void OnConnected(NetHandle, const SessionData&);
	virtual void OnCloseServer( NetHandle );
    virtual void on_release(NetHandle, const SessionData&);
	virtual INetBuffer* create_recv_buffer(const SessionData&)=0;
	virtual uint32_t get_send_buffer_size(const SessionData&);
    virtual bool is_ssl() const{return false;}
    virtual bool is_server_reuse_port() { return false; }
    virtual void on_send_bytes(NetHandle h, const SessionData&, uint64_t total) {}
    virtual INetSession* get_changed_session() { return nullptr; }
};

#endif
