#pragma once
#include "net_message_define.h"
#include "net/net_message_manager.h"
class NetPacket
{
public:
	NetPacket(uint32_t messageID);
	virtual ~NetPacket();

	virtual bool process() = 0;

	uint32_t getMessageID()
	{
		return mMessageID;
	}
private:
	uint32_t mMessageID;
};