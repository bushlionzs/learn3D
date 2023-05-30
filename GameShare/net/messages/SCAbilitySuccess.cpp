#pragma once
#include "stdafx.h"
#include "SCAbilitySuccess.h"
#include "server/map/map_manager.h"
#include "server/map/game_map.h"
#include "server/gameobject/ObjectManager.h"
#include "server/gameobject/Player.h"
#include "server/gameobject/Behavior_Player.h"

SCAbilitySuccess::SCAbilitySuccess():
	NetPacket(SC_ABILITY_SUCCESS)
{

}

SCAbilitySuccess::~SCAbilitySuccess()
{

}

bool SCAbilitySuccess::process()
{
	/* ����һ����ʱ�ĵ��� */
	KItem* pItem = NULL;

	if (mItemSerial != INVALID_ID)
	{
		pItem = ITEM_MANAGER_PTR->CreateNewItem(mItemSerial);
	}

	/* ������ǵ���ɹ��������ؽ������� */
	if (mAbilityId != 9) 
		COMMAND_SYS_PTR->AddCommand(GCD_PROGRESSBAR_HIDE);

	/* �ж������ּ��ܣ�������Ӧ���� */
	switch (mAbilityId)
	{
	case 9:		/* 11 */
		//GAME_AUDIO_PTR->PlayUISoundFunction(11 + 59);
		break;

	case 8:		/* 13 */
		//GAME_AUDIO_PTR->PlayUISoundFunction(13 + 59);
		break;

	case 10:	/* 15 */
		//GAME_AUDIO_PTR->PlayUISoundFunction(15 + 59);
		break;

		/* 19 */
	case 4:		/* ���� */
	case 5:		/* ���� */
	case 6:		/* �������� */
	case 7:		/* ����ѧ */
		//GAME_AUDIO_PTR->PlayUISoundFunction(19 + 59);
		break;

	case 3:		/* 23 //21 */
		//GAME_AUDIO_PTR->PlayUISoundFunction(23 + 59);
		break;

	default:
		break;
	}

	
	STRING	strTemp;

	if (pItem != NULL)
	{
		strTemp = UI_SYSTEM_PTR->ParserString_VarParam("ability_create_item", pItem->GetItemName());
		SHOW_TALKMSG(strTemp.c_str());
		ITEM_MANAGER_PTR->DestroyItem(pItem);
	}
	else if (mPrescriptionId != INVALID_ID)
	{		/* ������䷽�ϳ�ʧ�� */
		strTemp = UI_SYSTEM_PTR->ParserString_VarParam("ability_create_failed");
		SHOW_TALKMSG(strTemp.c_str());
	}
	

	/*
	 * TABLE_DEFINEHANDLE(s_pPrescrDBC, TABLE_LIFEABILITY_ITEMCOMPOSE);
	 */
	const _TABLE_LIFEABILITY_ITEMCOMPOSE* pDefine = NULL;
	const CGameTable* pPrescr = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_LIFEABILITY_ITEMCOMPOSE);

	if (pPrescr) 
		pDefine = (const _TABLE_LIFEABILITY_ITEMCOMPOSE*)(pPrescr->GetFieldDataByIndex(mPrescriptionId));

	/* ���������Ʒ */
	if (pDefine)
	{
		if (INVALID_ID != pDefine->nStuff1ID)
		{
			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff1ID);

			/* ֪ͨ��������״̬ */
			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
		}

		if (INVALID_ID != pDefine->nStuff2ID)
		{
			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff2ID);

			/* ֪ͨ��������״̬ */
			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
		}

		if (INVALID_ID != pDefine->nStuff3ID)
		{
			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff3ID);

			/* ֪ͨ��������״̬ */
			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
		}

		if (INVALID_ID != pDefine->nStuff4ID)
		{
			GAME_DATA_ITEM_PTR->UserBagUnLockAllItemById(pDefine->nStuff4ID);

			/* ֪ͨ��������״̬ */
			COMMAND_SYS_PTR->AddCommand(GCD_PACKAGE_ITEM_CHANGED);
		}
	}

	OBJECT_MANAGER_PTR->GetMySelf()->EndAbility();	//ִ���´κϳ�ǰҪ�ȰѶ����߼�ͣ��
	GAME_OPERATE_PTR->Player_UseLifeAbility(mPrescriptionId);
	return true;
}

void SCAbilitySuccess::setPlayerId(int32_t id)
{
	mPlayerId = id;
}

void SCAbilitySuccess::setMapId(int32_t id)
{
	mMapId = id;
}

void SCAbilitySuccess::setAbilityId(int32_t id)
{
	mAbilityId = id;
}


void SCAbilitySuccess::setPrescriptionId(int32_t id)
{
	mPrescriptionId = id;
}


void SCAbilitySuccess::setResult(int32_t res)
{
	mResultCode = res;
}
