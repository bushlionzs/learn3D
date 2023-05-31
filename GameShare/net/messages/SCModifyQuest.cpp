#include "stdafx.h"
#include "SCModifyQuest.h"


SCModifyQuest::SCModifyQuest():
	NetPacket(SC_ADD_QUEST)
{

}

SCModifyQuest::~SCModifyQuest()
{

}

bool SCModifyQuest::process()
{
	//CMap * pScene = (CMap*)(SCENE_MANAGER_PTR->GetActiveScene());
	//if (NULL == pScene)
	//{
	//	return false;
	//}
	//DPCCmd	cmdTemp;
	//cmdTemp.m_wID = DPC_UPDATE_QUEST_MODIFY;
	//cmdTemp.nParam[1] = (int32)mFlag;

	///* 任务修改 */
	//if (mFlag == eQuestModify_Quest)
	//{
	//	cmdTemp.pParam[0] = (void*)mQuest;
	//	cmdTemp.pParam[2] = (void*)&mFlagParam;
	//}
	///* 任务数据修改 */
	//else if (mFlag == eQuestModify_QuestData)
	//{
	//	/*cmdTemp.pParam[0] = (void*)(pPacket->GetQuestData());
	//	cmdTemp.pParam[2] = (void*)(pPacket->GetFlagData());*/
	//	int kk = 0;
	//}

	//GAME_DATA_PTR->ProcessCommand_(&cmdTemp);
	//VARIABLE_SYS_PTR->SetAs_Int("QuestCanPlaySound", 1);

	//GAME_DATA_QUEST_PTR->SortQuest();
	//GAME_DATA_QUEST_PTR->UpdateScoutQuest();

	//COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_QUEST_SCOUT);
	//COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_QUEST, "0");
	//OBJECT_MANAGER_PTR->Set_Update_NPC_InfoBoard(TRUE);
	
	
	return true;
}

void SCModifyQuest::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void SCModifyQuest::setFlag(int32_t flag)
{
	mFlag = flag;
}

void SCModifyQuest::setQuestId(int32_t questId)
{
	mQuestId = questId;
}

void SCModifyQuest::setFlagParam(uint32_t uIndex)
{
	KCheck(uIndex < MAX_QUEST_PARAM_NUM);
	mFlagParam.UpdateBits(uIndex, TRUE);
}

void SCModifyQuest::setQuest(const OWN_QUEST* quest)
{
	mQuest = quest;
}


