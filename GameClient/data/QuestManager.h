#pragma once
#include "server_message.pb.h"
#include "StructCommandScript.h"

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

	void updateQueryEvent(servermessage::ServerMsgQueryEventResult& msg)
	{
		mLastQueryEvent = true;
		mQuestInfoResponse = false;
		mQueryEventResult = msg;
	}

	servermessage::ServerMsgQueryEventResult& getQueryEvent()
	{
		return mQueryEventResult;
	}

	bool haveQueryEvent()
	{
		return mLastQueryEvent;
	}

	bool haveQuestInfoResponse()
	{
		return mQuestInfoResponse;
	}
	void updateQuestInfoResponse(servermessage::ServerMsgScriptCommand& msg)
	{
		mQuestInfoResponse = true;
		mLastQueryEvent = false;
		mQuestInfo = msg;
	}

	servermessage::ServerMsgScriptCommand& getScriptCommand()
	{
		return mQuestInfo;
	}

	std::string getQuestString(uint32_t type, SQuestBonus& bonus);
private:
	std::vector<base::Quest> mQuestList;

	bool mLastQueryEvent = false;
	bool mQuestInfoResponse = false;
	/* 第一次和npc对话，得到npc所能激活的操作 */
	servermessage::ServerMsgQueryEventResult mQueryEventResult;
	/* 在接任务时，看到的任务信息 */
	servermessage::ServerMsgScriptCommand mQuestInfo;
	/* 接受任务后，再次和npc对话，所得到的任务需求信息 */
	servermessage::ServerMsgScriptCommand mQuestDemandInfo;
	/* 完成任务后，点击继续，出现的任务信息 */
	servermessage::ServerMsgScriptCommand mQuestContinueInfo;
};