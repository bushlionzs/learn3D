#pragma once
#include "net/net_message.h"

struct OWN_QUEST;
class SCAddQuest : public NetPacket
{
public:
	SCAddQuest();
	~SCAddQuest();

	virtual bool process();

	void setPlayerId(int32_t playerId);

	void setQuest(const OWN_QUEST* quest);
private:
	int32_t mPlayerId = -1;
	OWN_QUEST mQuest;
};