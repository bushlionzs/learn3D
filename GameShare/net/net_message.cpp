#include "stdafx.h"
#include "net_message.h"

NetPacket::NetPacket(uint32_t messageID)
{
	mMessageID = messageID;
}

NetPacket::~NetPacket()
{

}

