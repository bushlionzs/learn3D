#ifndef __PLATFORMSOCKETFACTORY_H__
#define __PLATFORMSOCKETFACTORY_H__

class SockBase;
class PlatformSocket;
class INetSession;
#include <net_define.h>

class PlatformSocketFactory
{
    friend class DyNetworkContaintor;
private:
	PlatformSocketFactory();
	~PlatformSocketFactory();
public:
	PlatformSocket* CreatePlatformSocket(INetSession* session , NetProtocol protocol, const SessionData& sessionData);

	SockBase* CreatePlatformPipe(INetSession* session, const std::string& name, bool client);
};
#endif //__PLATFORMSOCKETFACTORY_H__

