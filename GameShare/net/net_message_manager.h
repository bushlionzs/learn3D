#pragma once
#include "platform_mutex.h"
#include "scoped_lock.h"
#include "GameSingleton.h"
#include "net_define.h"
#include <functional>
#include <unordered_map>
#include "server_message.pb.h"
#include "net_message.h"



class NetMessageManager:public GameSingleton<NetMessageManager>
{
public:
	NetMessageManager();
	~NetMessageManager();

	void setDefaultNetHandle(NetHandle h)
	{
		mNetHandle = h;
	}
	bool sendNetMessage(NetPacket*);

	bool sendNetMessage(NetHandle h, NetPacket* packet);
	bool sendNetMessage(NetHandle h, uint32_t msg_id, google::protobuf::Message* msg);
	bool sendNetMessage(uint32_t msg_id, google::protobuf::Message* msg);
	void processMessage();
	void processMessage(NetHandle h, const char* msg, uint32_t msg_size);

	void registerMessage(uint32_t msg_id, Handler func);

	void dispatchMessage(NetHandle h, const char* msg, uint32_t msg_size);

private:
	std::vector<NetPacket*> mPacketList;

	PlatformMutex mMutex;

	
	std::unordered_map<uint32_t, Handler> _handlers;

	NetHandle mNetHandle;
};