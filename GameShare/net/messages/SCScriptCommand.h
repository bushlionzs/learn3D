#pragma once
#include "net/net_message.h"
#include "StructCommandScript.h"
class SCScriptCommand : public NetPacket
{
public:
	SCScriptCommand();
	~SCScriptCommand();

	virtual bool process();

	void setCmdId(int32_t cmdId);
	void setParam(ScriptParam_QuestContinueInfo& param);
	void setQuestInfo(ScriptParam_QuestInfo& param);
	void setQuestTips(ScriptParam_QuestTips& param);
private:
	int32_t mCmdId;
	ScriptParam_QuestContinueInfo mParam;
	ScriptParam_QuestInfo mQuestInfo;
	ScriptParam_QuestTips mQuestTips;
};