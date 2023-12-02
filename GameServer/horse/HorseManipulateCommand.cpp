#include "stdafx.h"
#include "HorseManipulateCommand.h"
#include "gameobject/Player.h"
#include "net/messages/SCManipulatePetRet.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */
HorseManipulateCommand::HorseManipulateCommand()
{
	m_OpType = ePetAct_Unknow;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
HorseManipulateCommand::~HorseManipulateCommand()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManipulateCommand::IsCanManipulate(_HorseManipulate *pMamipulate, Player *pPlayer)
{
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManipulateCommand::CommonCheck(_HorseManipulate *pMamipulate, Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ _HORSE_DB	*pPetDB = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMamipulate->GetGUID().IsNull()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pPetItem = pPlayer->GetHorseItem(pMamipulate->GetGUID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPetItem == NULL) return FALSE;

	if(pPetItem->IsLock())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = pPlayer->GetHorseIndexByGUID(pMamipulate->GetGUID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iIndex == INVALID_ID)
	{
		return FALSE;
	}

	pPetDB = pPlayer->GetHorseDB(iIndex);
	if(pPetDB == NULL)
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
BOOL HorseManipulateCommand::IsMating(Player *pPlayer, _HorseManipulate *pMamipulate)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iIndex = pPlayer->GetHorseIndexByGUID(pMamipulate->GetGUID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iIndex == INVALID_ID)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB *pPetDB = pPlayer->GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPetDB == NULL)
	{
		return TRUE;
	}

	return pPetDB->m_iStatus == _HORSE_DB::PET_STATUS_MATING;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManipulateCommand::SendResult(Player *pPlayer, int32 iResult)
{
	SCManipulatePetRet* packet = new SCManipulatePetRet;

	packet->setManipulateRet(iResult);
	//NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManipulateCommand::ReCallHorse(Player *pPlayer)
{
	pPlayer->ReCallHorse();
}
