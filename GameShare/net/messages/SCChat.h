#pragma once
#include "net/net_message.h"
class SCChat : public NetPacket
{
public:
	SCChat();
	~SCChat();

	virtual bool process();

	void setChatType(int32_t type);
	void setChatMsg(const char* msg);
	void setChatShowPos(ENUM_SYSTEM_CHAR_SHOW_POS pos);
private:
	int32_t mChatType;
	std::string mChatMessage;
	ENUM_SYSTEM_CHAR_SHOW_POS mChatShowPosition;
	int32_t mCycleCount = 1;
	int32_t mAnimateImage = -1;
};