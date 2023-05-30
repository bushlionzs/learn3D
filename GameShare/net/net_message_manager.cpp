#include "stdafx.h"
#include"net_message_manager.h"
#include "net_message.h"

template<>
NetManager* GameSingleton<NetManager>::m_sSingleton = NULL;

NetManager::NetManager()
{

}

NetManager::~NetManager()
{

}

bool NetManager::sendNetMessage(NetPacket* packet)
{
	if (packet == nullptr)
	{
		assert(false);
	}
	if (packet->getMessageID() < 10000)
	{
		ScopedLock<PlatformMutex> lock(mClientMutex);
		mClientList.push_back(packet);
	}
	else
	{
		ScopedLock<PlatformMutex> lock(mServerMutex);

		int32_t id = packet->getMessageID();
		//printf("send server message:%d, p:%p\n", id, packet);
		mServerList.push_back(packet);
	}

	return true;
}

void NetManager::fetchServerMessage(std::vector<NetPacket*>& messagelist)
{
	ScopedLock<PlatformMutex> lock(mServerMutex);
	messagelist.swap(mServerList);
}

void NetManager::fetchClientMessage(std::vector<NetPacket*>& messagelist)
{
	ScopedLock<PlatformMutex> lock(mClientMutex);
	messagelist.swap(mClientList);
}