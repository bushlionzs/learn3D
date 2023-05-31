#include "stdafx.h"
#include "SCScriptCommand.h"

SCScriptCommand::SCScriptCommand()
    :NetPacket(SC_SCRIPT_COMMAND)
{

}

SCScriptCommand::~SCScriptCommand()
{

}

bool SCScriptCommand::process()
{
	//DPCCmd	cmdTemp;

	//cmdTemp.m_wID = DPC_SCRIPT_COMMAND;
	//cmdTemp.nParam[0] = mCmdId;
	//switch (mCmdId)
	//{
	//case SCRIPT_COMMAND_EVENT_LIST_RESPONSE:
	//	//cmdTemp.pParam[1] = pPacket->GetEnentList();
	//	break;
	//case SCRIPT_COMMAND_QUEST_RESPONSE:
	//	cmdTemp.pParam[1] = &mQuestInfo;
	//	break;
	//case SCRIPT_COMMAND_QUEST_REGIE:
	//	//cmdTemp.pParam[1] = pPacket->GetQuestRegie();
	//	break;
	//case SCRIPT_COMMAND_QUEST_DEMAND_RESPONSE:
	//	//cmdTemp.pParam[1] = pPacket->GetQuestDemandInfo();
	//	break;
	//case SCRIPT_COMMAND_QUEST_CONTINUE_RESPONSE:
	//	cmdTemp.pParam[1] = &mParam;
	//	break;
	//case SCRIPT_COMMAND_QUEST_TIPS:
	//	cmdTemp.pParam[1] = &mQuestTips;
	//	break;
	//case SCRIPT_COMMAND_TRADE:
	//	//cmdTemp.pParam[1] = pPacket->GetTrade();
	//	break;
	//case SCRIPT_COMMAND_QUEST_UPDATE:
	//	//cmdTemp.pParam[1] = pPacket->GetQuestUpdate();
	//	break;
	//case SCRIPT_COMMAND_QUESTDENGMI:
	//	//cmdTemp.pParam[1] = pPacket->GetQuestDengmi();
	//	break;
	//default:
	//	cmdTemp.pParam[1] = NULL;
	//	break;
	//}


	//GAME_DATA_PTR->ProcessCommand_(&cmdTemp);


    return true;
}

void SCScriptCommand::setCmdId(int32_t cmdId)
{
    mCmdId = cmdId;
}

void SCScriptCommand::setParam(ScriptParam_QuestContinueInfo& param)
{
    mParam = param;
}

void SCScriptCommand::setQuestInfo(ScriptParam_QuestInfo& param)
{
	mQuestInfo = param;
}

void SCScriptCommand::setQuestTips(ScriptParam_QuestTips& param)
{
	mQuestTips = param;
}