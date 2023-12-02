#include "stdafx.h"
#include"net_message_manager.h"
#include "net_message.h"
#include "server_message.pb.h"
#include "client_message.pb.h"
#include "net_header.h"
#include "platform_log.h"
#include "db/db_manager.h"
#include "db/db_task.h"

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

void NetManager::registerMessage(uint32_t msg_id, Handler func)
{
	_handlers[msg_id] = func;
}

void NetManager::processMessage(NetHandle h, const char* msg, uint32_t msg_size)
{
	NetHeader* header = (NetHeader*)msg;
	uint32_t data_size = msg_size - sizeof(NetHeader);

	auto itor = _handlers.find(header->mMsgId);
	if (itor != _handlers.end())
	{
		itor->second(h, msg + sizeof(NetHeader), msg_size - sizeof(NetHeader));
	}
	else
	{
		WARNING_LOG("invalid message, handle:%lld, msgid:%d, length:%d", h, header->mMsgId, header->mMsgLength);
	}
}
