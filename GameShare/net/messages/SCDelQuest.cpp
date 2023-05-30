#include "stdafx.h"
#include "SCDelQuest.h"
#include "server/server_manager.h"

SCDelQuest::SCDelQuest():
	NetPacket(SC_DEL_QUEST)
{

}

SCDelQuest::~SCDelQuest()
{

}

bool SCDelQuest::process()
{
	CMap * pScene = (CMap*)(SCENE_MANAGER_PTR->GetActiveScene());
	if (NULL == pScene)
	{
		return false;
	}

	DPCCmd	cmdTemp;

	cmdTemp.m_wID = DPC_UPDATE_QUEST_REMOVE;
	cmdTemp.uParam[0] = (uint32)(mQuestId);
	GAME_DATA_PTR->ProcessCommand_(&cmdTemp);
	
	OBJECT_MANAGER_PTR->Set_Update_NPC_InfoBoard(TRUE);
	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_QUEST, "0");

	return true;
}

void SCDelQuest::setPlayerId(int32_t playerId)
{
	mPlayerId = playerId;
}

void SCDelQuest::setQuestId(int32_t questId)
{
	mQuestId = questId;
}

