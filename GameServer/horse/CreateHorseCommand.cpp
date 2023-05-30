#include "stdafx.h"
#include "CreateHorseCommand.h"
#include "gameobject/Player.h"
#include "server_settting.h"
#include "data/data_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Horse_CreateHorseCommand::Horse_CreateHorseCommand()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Horse_CreateHorseCommand::~Horse_CreateHorseCommand()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse_CreateHorseCommand::ExecutManipulate(_HorseManipulate *pMamipulate, Player *pPlayer)
{
	__GUARD__ if(NULL == pPlayer)
	{
		return;
	}

	if(!IsCanManipulate(pMamipulate, pPlayer))
	{
		ReCallHorse(pPlayer);  //Huangqinqi
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = pPlayer->GetHorseIndexByGUID(pMamipulate->GetGUID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iIndex == INVALID_ID)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB *pPetDB = pPlayer->GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPetDB->m_byHappiness < g_Config.m_ConfigInfo.m_HorseCallUpHappiness)
	{
		pPlayer->SendOperateResultMsg(OR_NEED_HAPPINESS_60, 0);
		return;
	}

	if(pPetDB->m_nLevel - pPlayer->GetLevel() > g_Config.m_ConfigInfo.m_HorseCallupLevelThanPlayer)
	{
		pPlayer->SendOperateResultMsg(OR_NEED_HIGH_LEVEL, 0);
		return;
	}

	pPlayer->SetMountID(pPetDB->m_iModelID);
	pPlayer->ChangeCallUpHorse(pPetDB->m_GUID);
	pPlayer->SetMountModelID(pPetDB->m_iModelID);

	AddPassiveSkillToOnwer(pPlayer, pPetDB);
	pPlayer->MarkLevelOneAttrDirtyFlag();
	pPlayer->HorseEventScript(HORSE_CALL_SCRIPT_ON);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse_CreateHorseCommand::IsCanManipulate(_HorseManipulate *pMamipulate, Player *pPlayer)
{
	__GUARD__ if(!pPlayer->GetGUIDOfCallUpHorse().IsNull())
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void Horse_CreateHorseCommand::AddPassiveSkillToOnwerOpen(Player *pPlayer, _HORSE_DB *pPetDB)
{
	__GUARD__ 
	AddPassiveSkillToOnwer(pPlayer, pPetDB);
	__UNGUARD__
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse_CreateHorseCommand::AddPassiveSkillToOnwer(Player *pPlayer, _HORSE_DB *pPetDB)
{
	__GUARD__ for(int32 i = 0; i < PET_MAX_APPER_COUNT; ++i)
	{
		pPlayer->SetHorseDataIndex(i, INVALID_ID);
	}

	for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		if(pPetDB->m_SkillList[i].m_bCanUse == FALSE || pPetDB->m_SkillList[i].m_nSkillID == INVALID_ID)
		{
			continue;
		}

		StartPassiveSkill(pPetDB->m_SkillList[i].m_nSkillID, pPlayer, 1, i);
	}

	__UNGUARD__
}


void Horse_CreateHorseCommand::StartPassiveSkill(SpellID_t iSkillID, Player *pPlayer, int32 iSkillLevel, int32 iIndex)
{

	const SpellTemplateData	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(iSkillID);

	if(NULL == pTemplate)
	{
		return;
	}

	if(pTemplate->GetPassiveFlag() <= 0)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SpellInstanceData *pInstance = DataManager::GetSingletonPtr()->getSpellInstance(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pInstance == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const Descriptor	*pDescriptor = pInstance->GetDescriptorByIndex(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pDescriptor == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDataIndex = pDescriptor->GetValueBySkillLevel(iSkillLevel - 1);
	Player	*pTemp = const_cast<Player *>(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pTemp->SetHorseDataIndex(iIndex, iDataIndex);
	g_EffectInterface.SendEffectToUnit(*pTemp, iDataIndex, pPlayer->GetID(), iSkillID);
}
