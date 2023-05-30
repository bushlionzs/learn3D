#include "stdafx.h"
#include "SCQuestList.h"

SCQuestList::SCQuestList()
    :NetPacket(SC_QUEST_LIST)
{

}

SCQuestList::~SCQuestList()
{

}

bool SCQuestList::process()
{
	DPCCmd	cmdTemp;
	cmdTemp.m_wID = DPC_UPDATE_QUEST_LIST;

	cmdTemp.uParam[0] = (uint32)(mPlayerId);
	cmdTemp.pParam[1] = (void*)(&mFlagQuest);
	cmdTemp.pParam[2] = (void*)(&(mQuestList.m_aQuest[0]));

	GAME_DATA_PTR->ProcessCommand_(&cmdTemp);

	CDataDetailAttribPlayer* pAttrib = (CDataDetailAttribPlayer*)GAME_DATA_PLAYER_PTR->GetMySelfDetailAttrib();
	pAttrib->SetQuestHaveDone(mQuestList.m_aQuestHaveDoneFlags);

	pAttrib->ModifyQuestData(mQuestList.m_aQuestData);

	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_QUEST_SCOUT);
	COMMAND_SYS_PTR->AddCommand(GCD_UPDATE_QUEST, "0");
	OBJECT_MANAGER_PTR->Set_Update_NPC_InfoBoard(TRUE);
    return true;
}

void SCQuestList::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void SCQuestList::addQuest(int32_t i, const OWN_QUEST* quest)
{
	if (i < MAX_CHAR_QUEST_NUM)
	{
		mQuestList.m_aQuest[i] = *quest;
		mFlagQuest.UpdateBit(i, TRUE);
	}
}

void SCQuestList::setFlagData(uint32_t uIndex)
{
	mFlagQuest.UpdateBit(uIndex, TRUE);
}

void SCQuestList::setQuestList(QUEST_LIST* qlist)
{
	memcpy(&mQuestList, qlist, sizeof(QUEST_LIST));
}
