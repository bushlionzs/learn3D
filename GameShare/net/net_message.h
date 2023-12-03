#pragma once

#include "net_define.h"
#include "net_client_message_define.h"
#include "net_server_message_define.h"
#include <functional>

using Handler = std::function<void(NetHandle handle, const char* data, uint32_t size)>;


class NetPacket
{
public:
	NetPacket(uint32_t messageID);
	NetPacket(Handler handler, const char* msg, uint32_t msg_size);
	NetPacket(uint32_t messageID, google::protobuf::Message& msg);
	virtual ~NetPacket();

	virtual bool process();

	uint32_t getMessageID()
	{
		return mMessageID;
	}

	const std::string& getNetData()
	{
		return mNetData;
	}
private:
	uint32_t mMessageID;
	Handler  mHandler;
	std::string mNetData;
};