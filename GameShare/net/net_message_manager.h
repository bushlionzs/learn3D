#pragma once
#include "platform_mutex.h"
#include "scoped_lock.h"
#include "GameSingleton.h"
#include "net_define.h"
#include <functional>
class NetPacket;

using Handler = std::function<void(NetHandle handle, const char* data, uint32_t size)>;
class NetManager:public GameSingleton<NetManager>
{
public:
	NetManager();
	~NetManager();
	bool sendNetMessage(NetPacket* packet);

	void fetchServerMessage(std::vector<NetPacket*>& messagelist);
	void fetchClientMessage(std::vector<NetPacket*>& messagelist);

	void registerMessage(uint32_t msg_id, Handler func);

	void processMessage(NetHandle h, const char* data, uint32_t size);

private:
	std::vector<NetPacket*> mServerList;
	std::vector<NetPacket*> mClientList;

	PlatformMutex mServerMutex;
	PlatformMutex mClientMutex;

	
	std::unordered_map<uint32_t, Handler> _handlers;
};