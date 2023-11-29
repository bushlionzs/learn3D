#ifndef __NET_HEADER_H__
#define __NET_HEADER_H__

#include <stdint.h>
#include <string>
#define MAX_NET_PACKET_LENGTH (1024 * 1024)
#pragma pack(push, 1)

struct NetHeader
{
    uint32_t mMsgId;
    uint32_t mMsgLength;
    uint16_t mCrypto;
    uint16_t mVersion;
    void SetMsgId(uint32_t id);
    void SetMsgLength(uint32_t length);
    void SetCrypto(uint16_t crypto);
    void SetVersion(uint16_t version);
};


#pragma pack(pop)

void InitNetHeader(std::string& msg_data);
void InitNetHeader(std::string& msg_data, uint32_t msgId, uint32_t msgLength);

#endif //__NET_HEADER_H__