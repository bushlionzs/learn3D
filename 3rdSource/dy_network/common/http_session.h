#ifndef __HTTP_SESSION_H__
#define __HTTP_SESSION_H__

#include "net_lib.h"


class IServerInterface;
class HttpSession: public INetSession
{
public:
    HttpSession(IServerInterface* server, bool ssl = false, bool ws = false, bool hc = false, 
        bool reuse_port = false);
	virtual void OnAccept(NetHandle h, const SessionData& data);
    virtual void OnConnected(NetHandle h, const SessionData& data);
	virtual void OnClose(NetHandle h, const SessionData&);
    virtual void on_release(NetHandle, const SessionData&);

	virtual INetBuffer* create_recv_buffer(const SessionData&);
	
	virtual uint32_t get_send_buffer_size(const SessionData&);
    
    virtual bool is_ssl() const
    {
        return _is_ssl; 
    }

    virtual bool is_server_reuse_port() { return _reuse_port; }

private:
    IServerInterface* _server;
    bool _is_ssl;
    bool _is_ws;
    bool _is_hc;
    bool _reuse_port;
};

#endif //__HTTP_SESSION_H__
