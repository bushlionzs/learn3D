#pragma once
#include "server_message.pb.h"
class QuestManager
{
public:
	struct QuestInfoMemo
	{
		std::string strQuestName;
		std::string strQuestDesc;
		std::string strQuestHelp;
		std::string strQuestManual;
		std::string strQuestSubmitNPC;
	};

	struct QuestReward
	{
		std::string rewardDesc;
		uint32_t itemId;
	};
public:
	QuestManager();
	~QuestManager();
	void clearQuest();
	void addQuest(const ::base::Quest& quest);
	void modifyQuest(const ::base::Quest& quest);
	const base::Quest& getQuest(uint32_t index)
	{
		return mQuestList[index];
	}
	uint32_t getQuestCount()
	{
		return mQuestList.size();
	}

	bool getQuestInfoMemo(uint32_t index, QuestInfoMemo& memo);

	bool getQuestReward(uint32_t quest_id, std::vector<QuestReward>& rewardlist);
private:
	std::vector<base::Quest> mQuestList;
};