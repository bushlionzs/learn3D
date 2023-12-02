#include "stdafx.h"
#include "net_message.h"

NetPacket::NetPacket(uint32_t messageID)
{
	mMessageID = messageID;
}


NetPacket::NetPacket(Handler handler, const char* msg, uint32_t msg_size)
{
	mHandler = handler;
	mNetData.assign(msg, msg_size);
}
NetPacket::~NetPacket()
{

}

bool NetPacket::process()
{
	mHandler(INVALID_NET_HANDLE, mNetData.data(), mNetData.size());
	return true;
}

