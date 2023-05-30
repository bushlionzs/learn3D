#pragma once
#include "net/net_message.h"
class SCDelQuest : public NetPacket
{
public:
	SCDelQuest();
	~SCDelQuest();

	virtual bool process();

	void setPlayerId(int32_t playerId);

	void setQuestId(int32_t questId);
private:
	int32_t mPlayerId = -1;
	int32_t mQuestId = -1;
};