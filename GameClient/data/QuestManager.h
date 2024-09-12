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
	/* ��һ�κ�npc�Ի����õ�npc���ܼ���Ĳ��� */
	servermessage::ServerMsgQueryEventResult mQueryEventResult;
	/* �ڽ�����ʱ��������������Ϣ */
	servermessage::ServerMsgScriptCommand mQuestInfo;
	/* ����������ٴκ�npc�Ի������õ�������������Ϣ */
	servermessage::ServerMsgScriptCommand mQuestDemandInfo;
	/* �������󣬵�����������ֵ�������Ϣ */
	servermessage::ServerMsgScriptCommand mQuestContinueInfo;
};