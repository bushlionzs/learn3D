#pragma once

#include "net/net_message.h"
#include "StructDB.h"
class SCQuestList : public NetPacket
{
public:
	SCQuestList();
	virtual ~SCQuestList();

	virtual bool process();

	void setPlayerId(int32_t id);
	void addQuest(int32_t i, const OWN_QUEST* quest);
	void setFlagData(uint32_t uIndex);
	void setQuestList(QUEST_LIST* qlist);
private:
	int32_t mPlayerId = -1;

	QUEST_LIST mQuestList;

	typedef FixedFlag<MAX_CHAR_QUEST_DATA_NUM> FlagMD;
	FlagMD mFlagQuest;
};