#pragma once
#include "net/net_message.h"

struct OWN_QUEST;
class SCModifyQuest : public NetPacket
{
public:
	enum
	{
		eQuestModify_Quest,
		eQuestModify_QuestData,
	};
public:
	SCModifyQuest();
	~SCModifyQuest();

	virtual bool process();

	void setPlayerId(int32_t playerId);

	void setFlag(int32_t flag);
	void setQuestId(int32_t questId);
	void setFlagParam(uint32_t uIndex);
	void setQuest(const OWN_QUEST* quest);
private:
	int32_t mPlayerId = -1;
	int32_t mQuestId = -1;
	int32_t mFlag = eQuestModify_Quest;
	Flag32 mFlagParam;
	const OWN_QUEST* mQuest = nullptr;
};