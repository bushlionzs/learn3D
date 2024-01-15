#include "stdafx.h"
#include"net_message_manager.h"
#include "net_message.h"
#include "server_message.pb.h"
#include "client_message.pb.h"
#include "net_header.h"
#include "platform_log.h"
#include "net_factory.h"
//#include "db/db_manager.h"
//#include "db/db_task.h"

template<>
NetMessageManager* GameSingleton<NetMessageManager>::m_sSingleton = NULL;

NetMessageManager::NetMessageManager()
{
}

NetMessageManager::~NetMessageManager()
{

}

bool NetMessageManager::sendNetMessage(NetPacket*)
{
	assert(false);
	return false;
}

bool NetMessageManager::sendNetMessage(NetHandle h, NetPacket* packet)
{
	const std::string& data = packet->getNetData();

	int32_t ret = NetFactory::GetInstance()->SendData(h, (const uint8_t*)data.data(), data.size());

	return true;
}

bool NetMessageManager::sendNetMessage(NetHandle h, uint32_t msg_id, google::protobuf::Message* msg)
{
	std::string msgdata;
	InitNetHeader(msgdata);
	if (!msg->AppendToString(&msgdata))
	{
		WARNING_LOG("fail to create MsgLogin message");
		return false;
	}

	InitNetHeader(msgdata, msg_id, msgdata.size());

	int32_t ret = NetFactory::GetInstance()->SendData(h, (const uint8_t*)msgdata.data(), msgdata.size());

	return true;
}

void NetMessageManager::processMessage()
{
	std::vector<NetPacket*> tmp;
	{
		ScopedLock<PlatformMutex> lock(mMutex);
		tmp.swap(mPacketList);
	}
	
	for (auto packet : tmp)
	{
		packet->process();
		delete packet;
	}
}

void NetMessageManager::processMessage(NetHandle h, const char* msg, uint32_t msg_size)
{
	NetHeader* header = (NetHeader*)msg;
	uint32_t data_size = msg_size - sizeof(NetHeader);

	auto itor = _handlers.find(header->mMsgId);
	if (itor != _handlers.end())
	{
		itor->second(h, msg, msg_size);
	}
	else
	{
		WARNING_LOG("invalid message, handle:%lld, msgid:%d, length:%d", h, header->mMsgId, header->mMsgLength);
	}
}



void NetMessageManager::registerMessage(uint32_t msg_id, Handler func)
{
	_handlers[msg_id] = func;
}

void NetMessageManager::dispatchMessage(NetHandle h, const char* msg, uint32_t msg_size)
{
	NetHeader* header = (NetHeader*)msg;
	uint32_t data_size = msg_size - sizeof(NetHeader);

	auto itor = _handlers.find(header->mMsgId);
	if (itor != _handlers.end())
	{
		NetPacket* packet = new  NetPacket(itor->second, msg + sizeof(NetHeader), data_size);

		mPacketList.push_back(packet);
	}
	else
	{
		WARNING_LOG("invalid message, handle:%lld, msgid:%d, length:%d", h, header->mMsgId, header->mMsgLength);
	}
}
