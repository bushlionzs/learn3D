#pragma once
#include "stdafx.h"
#include "SCAbilityResult.h"


SCAbilityResult::SCAbilityResult():
	NetPacket(SC_ABILITY_RESULT)
{

}

SCAbilityResult::~SCAbilityResult()
{

}

bool SCAbilityResult::process()
{
	//if (mResultCode != OR_OK)
	//{
	//	STRING strTmp = ACTION_SYS_PTR->GetOperateResult((OPT_RESULT)mResultCode);

	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strTmp.c_str());
	//	if (mResultCode == OR_FAILURE)
	//	{
	//		switch (mAbilityId)
	//		{
	//		case 3:		
	//			//GAME_AUDIO_PTR->PlayUISoundFunction(22 + 59); 
	//			break;
	//		default:	break;
	//		}

	//		COMMAND_SYS_PTR->AddCommand(GCD_CLOSE_SYNTHESIZE_ENCHASE);
	//	}

	//	const _TABLE_LIFEABILITY_ITEMCOMPOSE* pDefine = NULL;
	//	const CGameTable* pPrescr = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_LIFEABILITY_ITEMCOMPOSE);
	//	if (pPrescr) pDefine = (const _TABLE_LIFEABILITY_ITEMCOMPOSE*)(pPrescr->GetFieldDataByIndex(mPrescriptionId));

	//	/*
	//	 * TABLE_DEFINEHANDLE(s_pPrescrDBC, TABLE_LIFEABILITY_ITEMCOMPOSE);
	//	 * const _TABLE_LIFEABILITY_ITEMCOMPOSE* pDefine = ;
	//	 * (const _TABLE_LIFEABILITY_ITEMCOMPOSE*)s_pPrescrDBC->GetFieldDataByIndex(preId);
	//	 * ;
	//	 * 解除锁定物品
	//	 */
	//	if (pDefine)
	//	{
	//		if (INVALID_ID != pDefine->nStuff1ID)
	//		{
	//			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff1ID);

	//			/* 通知背包锁定状态 */
	//			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
	//		}

	//		if (INVALID_ID != pDefine->nStuff2ID)
	//		{
	//			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff2ID);

	//			/* 通知背包锁定状态 */
	//			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
	//		}

	//		if (INVALID_ID != pDefine->nStuff3ID)
	//		{
	//			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff3ID);

	//			/* 通知背包锁定状态 */
	//			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
	//		}

	//		if (INVALID_ID != pDefine->nStuff4ID)
	//		{
	//			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff4ID);

	//			/* 通知背包锁定状态 */
	//			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
	//		}
	//	}
	//}
	//else
	//{
	//	COMMAND_SYS_PTR->AddCommand(GCD_ABILITY_COOLDOWN_ADD_TIMER, (int32_t)mPrescriptionId);
	//}


	return true;
}

void SCAbilityResult::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void SCAbilityResult::setMapId(int32_t id)
{
	mMapId = id;
}

void SCAbilityResult::setAbilityId(int32_t id)
{
	mAbilityId = id;
}


void SCAbilityResult::setPrescriptionId(int32_t id)
{
	mPrescriptionId = id;
}


void SCAbilityResult::setResult(int32_t res)
{
	mResultCode = res;
}
