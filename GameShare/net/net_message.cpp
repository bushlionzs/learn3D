#include "stdafx.h"
#include "net_message.h"
#include "net_header.h"

NetPacket::NetPacket(uint32_t messageID)
{
	mMessageID = messageID;
}


NetPacket::NetPacket(Handler handler, const char* msg, uint32_t msg_size)
{
	mHandler = handler;
	mNetData.assign(msg, msg_size);
}

NetPacket::NetPacket(uint32_t messageID, google::protobuf::Message& msg)
{
	mMessageID = messageID;

	InitNetHeader(mNetData);
	msg.AppendToString(&mNetData);


	InitNetHeader(mNetData, messageID, mNetData.size());
}


NetPacket::~NetPacket()
{

}

bool NetPacket::process()
{
	mHandler(INVALID_NET_HANDLE, mNetData.data(), mNetData.size());
	return true;
}

