#pragma once
#include "platform_mutex.h"
#include "scoped_lock.h"
#include "GameSingleton.h"
class NetPacket;
class NetManager:public GameSingleton<NetManager>
{
public:
	NetManager();
	~NetManager();
	bool sendNetMessage(NetPacket* packet);

	void fetchServerMessage(std::vector<NetPacket*>& messagelist);
	void fetchClientMessage(std::vector<NetPacket*>& messagelist);
private:
	std::vector<NetPacket*> mServerList;
	std::vector<NetPacket*> mClientList;

	PlatformMutex mServerMutex;
	PlatformMutex mClientMutex;
};