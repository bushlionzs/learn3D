#include "stdafx.h"
#include "SCAddQuest.h"

SCAddQuest::SCAddQuest():
	NetPacket(SC_ADD_QUEST)
{

}

SCAddQuest::~SCAddQuest()
{

}

bool SCAddQuest::process()
{
	//CMap * pScene = (CMap*)(SCENE_MANAGER_PTR->GetActiveScene());
	//if (NULL == pScene)
	//{
	//	return false;
	//}

	//DPCCmd	cmdTemp;
	//cmdTemp.m_wID = DPC_UPDATE_QUEST_ADD;
	//cmdTemp.pParam[0] = (void*)(&mQuest);

	//printf("add quest:id:%d,script:%d\n", mQuest.m_idQuest, mQuest.m_idScript);

	//GAME_DATA_PTR->ProcessCommand_(&cmdTemp);

	///* Ë¢ÐÂNPCÐÅÏ¢ */
	//OBJECT_MANAGER_PTR->Set_Update_NPC_InfoBoard(TRUE);
	//COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_QUEST, "0");
	
	
	return true;
}

void SCAddQuest::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void SCAddQuest::setQuest(const OWN_QUEST* quest)
{
	mQuest = *quest;
}

