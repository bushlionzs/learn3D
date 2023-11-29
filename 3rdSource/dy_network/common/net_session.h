#ifndef __NET_SESSION_H__
#define __NET_SESSION_H__

#include "net_lib.h"

class IServerInterface;
class NetSession: public INetSession
{
public:
    NetSession(IServerInterface* server, bool need_split = true);
	virtual void OnAccept(NetHandle h, const SessionData& data);
    virtual void OnConnected(NetHandle h, const SessionData& data);
	virtual void OnClose(NetHandle h, const SessionData&);
    virtual void on_release(NetHandle, const SessionData&);
	virtual INetBuffer* create_recv_buffer(const SessionData&);
	
	virtual uint32_t get_send_buffer_size(const SessionData&);
private:
    IServerInterface* _server;
    bool _need_split;
};

#endif //__NET_SESSION_H__
