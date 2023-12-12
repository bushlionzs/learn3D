#ifndef NETFACTORY_H
#define NETFACTORY_H

#include <stdint.h>
#include <string>
#include <memory>
#include <net_handle.h>
#include <net_define.h>

class INetSession;
class UdpSession;

struct SessionData;


class NetFactory
{
    friend class DyNetworkContaintor;
public:
	static NetFactory* GetInstance();
    static bool is_client_handle(NetHandle h);
private:
	NetFactory();
	~NetFactory();
public:
	NetHandle CreateUdpConnection(UdpSession* session, const SessionData& sessionData);
	NetHandle CreateTcpConnection(INetSession* session, const SessionData& sessionData);
    NetHandle CreateQuicConnection(INetSession* session, const SessionData& sessionData);
    NetHandle CreateQuicServer(INetSession* session, 
                            const std::string& ip, 
                            uint16_t port, 
                            const std::shared_ptr<QuicConfig>& quic_cfg);
	
	void DisconnectHandle(const NetHandle& handle);
	NetHandle CreateTcpServer(INetSession* session, const std::string& ip, uint16_t port);
	int32_t SendData(const NetHandle& handle, const uint8_t* data,  uint32_t size, SndData* param = nullptr);
	NetHandle CreateTcpServer(INetSession* session , const SessionData& sessionData);

	NetHandle CreatePipe(INetSession* session, const std::string& name, bool client);
};


#endif
