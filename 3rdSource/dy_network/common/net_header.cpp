#include "net_header.h"
#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif
void NetHeader::SetMsgId(uint32_t id)
{
	mMsgId = htonl(id);
}

void NetHeader::SetMsgLength(uint32_t length)
{
	mMsgLength = htonl(length);
}

void NetHeader::SetCrypto(uint16_t crypto)
{
	mCrypto = htons(crypto);
}

void NetHeader::SetVersion(uint16_t version)
{
	mVersion = htons(version);
}

void InitNetHeader(std::string& msg_data)
{
	msg_data.clear();
	NetHeader header;
	msg_data.append((const char*)&header, sizeof(header));
}

void InitNetHeader(std::string& msg_data, uint32_t msgId, uint32_t msgLength)
{
	NetHeader* header = (NetHeader*)msg_data.data();
	header->SetMsgId(msgId);
	header->SetMsgLength(msgLength);
}