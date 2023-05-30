/*$T MapServer/Server/Skill/AllSkills.cpp GC 1.140 10/10/07 10:07:52 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Skill_Manager.h"
#include "TabDefine.h"
#include "map/game_map.h"
#include "item/Item_Interface.h"
#include "BaseTool.h"
#include "item/ItemBox.h"
#include "item/Item_Manager.h"
#include "server_manager.h"
#include "script/LuaSystem.h"
#include "ScriptDef.h"
#include "data/data_manager.h"
#include "item/Item_GrowPointManager.h"
#include "Share/TAB/TabDefine_Map_Misc.h"
#include "Skill_All.h"
#include "net/messages/SCAbilitySuccess.h"
#include "data/data_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

OPT_RESULT SkillCompound::CanUseSkill(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	OPT_RESULT		res;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	res = BaseSkill::CanUseSkill(pPlayer);
	if(res != OR_OK)
	{
		return res;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SkillOpera			*pAbilityOpera;
	const SSkillPrescriptionTab *pPrescriptionList = g_pSkillManager->GetPrescriptionList();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	if((pAbilityOpera->m_PresID >= 0) && (pAbilityOpera->m_PresID < pPrescriptionList->m_Count))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const _SKILL_PRESCRIPTION_DATA	*pPrescrData;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pPrescrData = pPrescriptionList->Get_Prescription(pAbilityOpera->m_PresID);

		if(pPrescrData->m_SkillID != m_SkillID)
		{
			return OR_WARNING;
		}

		if(pPlayer->IsPrescrHaveLearned(pAbilityOpera->m_PresID) == FALSE)
		{
			return OR_WARNING;
		}

		if(pPrescrData->m_nOperaTime > 0)
		{
			pAbilityOpera->m_nMaxTime = pPrescrData->m_nOperaTime;
		}

		if(pPlayer->GetAbilityLevel(m_SkillID) < pPrescrData->m_SkillLevel)
		{
			return OR_WARNING;
		}

		if(pPrescrData->m_ScriptID > 0 )
		{
			LuaSystem * pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

			/*~~~~~~~~*/
			OPT_RESULT res;
			/*~~~~~~~~*/

			res = (OPT_RESULT) pLuaSystem->RunScriptFunction
				(	
					pPlayer->GetMap()->MapID(), 
					pPrescrData->m_ScriptID,
					DEF_ABILITY_CHECK,
					(int32) pPlayer->GetMap()->MapID(),
					(int32) pPlayer->GetID()
				);

			return res;
		}
		else
		{
			return IsFitPrescr(pPlayer, pPrescrData);
		}
	}

	return OR_WARNING;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillCompound::IsFitPrescr(Player *pPlayer, const _SKILL_PRESCRIPTION_DATA *pPrescrData)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPrescrData);

	if(pPrescrData->m_ToolID != INVALID_ID && sItemInterface.CalcInventoryItemCount(pPlayer, pPrescrData->m_ToolID) < 1)
	{
		return OR_NO_TOOL;
	}

	for(int32 i = 0; i < MAX_PRESCRIPTION_STUFF; ++i)
	{
		if(pPrescrData->m_Stuff_ID[i] == INVALID_ID)
		{
			continue;
		}

		if(sItemInterface.CalcInventoryItemCount(pPlayer, pPrescrData->m_Stuff_ID[i]) < pPrescrData->m_Stuff_Num[i])
		{
			return OR_STUFF_LACK;
		}
	}

	if(pPrescrData->m_Attr_Vigor > 0)
	{
		if(pPlayer->Get_Property_Vigor() - pPrescrData->m_Attr_Vigor < 0)
		{
			return OR_NOT_ENOUGH_VIGOR;
		}
	}

	if((pPrescrData->m_ColddownID >= 0))
	{
		if(FALSE == pPlayer->IsCooldowned(pPrescrData->m_ColddownID))
		{
			return OR_COOL_DOWNING;
		}
	}

	/*~~~~~~~*/
	int32	ns;
	/*~~~~~~~*/

	if
	(
		sItemInterface.HaveEnoughBagItemSpace
			(
				pPlayer,
				pPrescrData->m_CompoundID,
				pPrescrData->m_CompoundNum,
				ns
			) == FALSE
	)
	{
		return OR_BAG_OUT_OF_SPACE;
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillCompound::OnEvent_ProcOver(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__			KCheck(pPlayer);
	SkillOpera			*pAbilityOpera;
	const SSkillPrescriptionTab *pPrescriptionList = g_pSkillManager->GetPrescriptionList();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	if((pAbilityOpera->m_PresID >= 0) && (pAbilityOpera->m_PresID < pPrescriptionList->m_Count))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const _SKILL_PRESCRIPTION_DATA	*pPrescrData;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pPrescrData = pPrescriptionList->Get_Prescription(pAbilityOpera->m_PresID);

		/*~~~~~~~~*/
		OPT_RESULT res;
		/*~~~~~~~~*/

		LuaSystem * pLuaSystem;
		pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

		if(pPrescrData->m_ScriptID > 0 )
		{
			res = (OPT_RESULT) pLuaSystem->RunScriptFunction
				(
					pPlayer->GetMap()->MapID(), 
					pPrescrData->m_ScriptID,
					DEF_ABILITY_CHECK,
					(int32) pPlayer->GetMap()->MapID(),
					(int32) pPlayer->GetID()
				);
			if(res != OR_OK)
			{
				return res;
			}

			pLuaSystem->RunScriptFunction
				(
					pPlayer->GetMap()->MapID(), 
					pPrescrData->m_ScriptID,
					DEF_ABILITY_CONSUME,
					(int32) pPlayer->GetMap()->MapID(),
					(int32) pPlayer->GetID()
				);
		}
		else
		{
			res = IsFitPrescr(pPlayer, pPrescrData);
			if(res != OR_OK)
			{
				return res;
			}

			SkillConsume(pPlayer, pPrescrData);
		}

		if(res == OR_FAILURE)
		{
			return OnEvent_ProcFailure(pPlayer, pPrescrData);
		}

		if(pPrescrData->m_ScriptID > 0 )
		{
			res = (OPT_RESULT) pLuaSystem->RunScriptFunction
				(
					pPlayer->GetMap()->MapID(), 
					pPrescrData->m_ScriptID,
					DEF_ABILITY_PRODUCE,
					(int32) pPlayer->GetMap()->MapID(),
					(int32) pPlayer->GetID()
				);

			return res;
		}
		else
		{
			return OnEvent_ProcSuccess(pPlayer, pPrescrData);
		}
	}

	return OR_DEFAULT_ERROR;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillCompound::OnEvent_ProcSuccess(Player *pPlayer, const _SKILL_PRESCRIPTION_DATA *pPrescrData)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPrescrData);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameConnector	*pGameConnector = (GameConnector *) pPlayer->GetConnector();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPrescrData->m_CompoundNum > 0)
	{
		CreateItemToPlayer(pPlayer, pPrescrData->m_CompoundID, pPrescrData->m_CompoundNum);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	currentExp = pPlayer->GetAbilityExp(m_SkillID);
	int32	curAbilityLevel = pPlayer->GetAbilityLevel(m_SkillID);
	int32	addExp = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((curAbilityLevel - pPrescrData->m_SkillLevel) == 1)
	{
		addExp = pPrescrData->m_ExpIncrement - 2;
		if (addExp >0)
		{
			pPlayer->SetAbilityExp(m_SkillID, currentExp + addExp);

			assert(false);
		}
	}
	else if((curAbilityLevel == pPrescrData->m_SkillLevel))
	{
		addExp = pPrescrData->m_ExpIncrement;
		if (addExp >0)
		{
			pPlayer->SetAbilityExp(m_SkillID, currentExp + addExp);

			assert(false);
		}
	}

	assert(false);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillCompound::OnEvent_ProcFailure(Player *pPlayer, const _SKILL_PRESCRIPTION_DATA *pPrescrData)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPrescrData);

	assert(false);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillCompound::SkillConsume(Player *pPlayer, const _SKILL_PRESCRIPTION_DATA *pPrescrData)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPrescrData);


	for(int32 i = 0; i < MAX_PRESCRIPTION_STUFF; ++i)
	{
		if(pPrescrData->m_Stuff_ID[i] == INVALID_ID)
		{
			continue;
		}

		if
		(
			sItemInterface.EraseBagItemByIndex
				(
					nullptr,
					pPlayer,
					pPrescrData->m_Stuff_ID[i],
					pPrescrData->m_Stuff_Num[i]
				)
		)
		{
		}
	}

	if(pPrescrData->m_Attr_Vigor > 0)
	{
		pPlayer->Set_Property_Vigor(pPlayer->Get_Property_Vigor() - pPrescrData->m_Attr_Vigor);
	}

	if((pPrescrData->m_ColddownID >= 0) && (pPrescrData->m_ColddownTime > 0))
	{
		pPlayer->SetCooldown(pPrescrData->m_ColddownID, pPrescrData->m_ColddownTime);
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SkillCompound::CreateItemToPlayer(Player *pPlayer, uint32 uItemSN, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemSN != INVALID_ID);
	KCheck(nCount > 0);

	if(nCount < 1)
	{
		return FALSE;
	}

	if(uItemSN != INVALID_ID)
	{
		BOOL			bRet;

		if(nCount > 1)
		{
			bRet = sItemInterface.CreateMultiItemToInventory(nullptr, pPlayer, uItemSN, nCount);
		}
		else
		{
			/*~~~~~~~~~~~~*/
			uint32	uBagPos;
			/*~~~~~~~~~~~~*/

			bRet = sItemInterface.CreateItemToBagByItemIndex(nullptr, pPlayer, uItemSN, uBagPos);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pItem = sItemInterface.GetBagItem(pPlayer, uBagPos);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pItem && pItem->IsEquip())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				ItemContainer	*pContainer = NULL;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				pContainer = sItemInterface.GetBagContainer(pPlayer, uBagPos);
				if(pContainer)
				{
					sItemInterface.SetItemCreator
						(
							pContainer,
							pContainer->BagIndex2ConIndex(uBagPos),
							pPlayer->GetName()
						);
				}
			}

			assert(false);
		}

		if(bRet != FALSE)
		{
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SkillGather::SkillGather(BaseSkill &a) :
	BaseSkill(a)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillGather::CanUseSkill(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	OPT_RESULT		res;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	res = BaseSkill::CanUseSkill(pPlayer);
	if(res != OR_OK)
	{
		return res;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t ItemBoxObjID = pAbilityOpera->m_Obj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ItemBoxObjID == INVALID_ID)
	{
		KCheck(FALSE);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = pMap->GetSpecificObjByID(ItemBoxObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj == NULL)
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "AbilityGatherMine: not find obj=%d", ItemBoxObjID);
		return OR_INVALID_TARGET;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemBox *pItemBox = (ItemBox *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItemBox->GetObjType() != Object::OBJECT_CLASS_ITEM_BOX)
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"AbilityGatherMine: ItemBox obj	=	%d\r\n  is Not class of ITEM_CLASS_BOX",
				ItemBoxObjID
			);
		return OR_INVALID_TARGET;
	}

	if(!pItemBox->CanPickBox(pPlayer->GetID(), pPlayer->GetID())) return OR_FAILURE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			ItemBoxType = pItemBox->GetType();
	_GATHER_POINT_INFO	*pGET = DataManager::GetSingletonPtr()->getGatherPointTable()->Get(ItemBoxType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGET);

	if(pGET->m_ScriptID > 0)
	{
		return(eOPTRESULT)
			(
				pMap->GetGatherPointManager()->CallLUAOpenBoxFunc
					(
						pGET->m_ScriptID,
						pPlayer->GetID(),
						ItemBoxObjID,
						pMap->MapID()
					)
			);
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillGather::OnEvent_ProcOver(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t ItemBoxObjID = pAbilityOpera->m_Obj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ItemBoxObjID == INVALID_ID)
	{
		KCheck(FALSE);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = pMap->GetSpecificObjByID(ItemBoxObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj == NULL)
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "SkillGather: not find obj=%d", ItemBoxObjID);
		return OR_INVALID_TARGET;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemBox *pItemBox = (ItemBox *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItemBox->GetObjType() != Object::OBJECT_CLASS_ITEM_BOX)
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"SkillGather: ItemBox obj	=	%d\r\n  is Not class of ITEM_CLASS_BOX",
				ItemBoxObjID
			);
		return OR_INVALID_TARGET;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			ItemBoxType = pItemBox->GetType();
	_GATHER_POINT_INFO	*pGET = DataManager::GetSingletonPtr()->getGatherPointTable()->Get(ItemBoxType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGET);

	if(pGET->m_ScriptID > 0)
	{
		if
		(
			pMap->GetGatherPointManager()->CallLUAProcOverFunc
				(
					pGET->m_ScriptID,
					pPlayer->GetID(),
					ItemBoxObjID,
					pMap->MapID()
				)
		)
		{
			return OnEvent_ProcFailure(pPlayer);
		}
		else
		{
			return OnEvent_ProcSuccess(pPlayer);
		}
	}
	else
	{
		return OnEvent_ProcSuccess(pPlayer);
	}

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillGather::OnEvent_ProcSuccess(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	SkillOpera	*pOpera = pPlayer->GetAbilityOpera();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pOpera);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t		TargetID = pOpera->m_Obj;
	SpellID_t	AbilityID = pOpera->m_SkillID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(TargetID != INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = pPlayer->GetMap()->GetSpecificObjByID(TargetID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj->GetObjType() == Object::OBJECT_CLASS_ITEM_BOX)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemBox *pItemBox = static_cast<ItemBox *>(pObj);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItemBox);

		if(pItemBox->GetItemCount() > 0)
		{
			if(pItemBox->GetOpenFlag() != TRUE)
			{
				pItemBox->SetOpenFlag(TRUE);
			}

			assert(false);
		}
		else
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = pPlayer->GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pMap);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32			ItemBoxType = pItemBox->GetType();
			_GATHER_POINT_INFO	*pGET = DataManager::GetSingletonPtr()->getGatherPointTable()->Get(ItemBoxType);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			if(pGET->m_ScriptID > 0)
			{
				if
				(
					pMap->GetGatherPointManager()->CallLUARecycleFunc
						(
							pGET->m_ScriptID,
							pPlayer->GetID(),
							TargetID,
							pMap->MapID()
						)
				)
				{
					pItemBox->Recycle();
				}
			}
		}

		SCAbilitySuccess* packet = new SCAbilitySuccess;
		/*~~~~~~~~~~~~~~~~~~~~*/

		packet->setAbilityId(AbilityID);
		packet->setPrescriptionId(INVALID_ID);
		NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}
	else
	{
		return OR_INVALID_TARGET;
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

OPT_RESULT SkillGather::OnEvent_ProcFailure(Player *pPlayer)
{
	pPlayer->SendOperateResultMsg(OR_FAILURE, 0);
	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SkillGather::OnEvent_DefaultProcSuccess(Player *pPlayer)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SkillGather::OnEvent_ScriptProcSuccess(Player *pPlayer)
{
}

#define MIN_FISH_TIME	10
#define MAX_FISH_TIME	70

/*
 =======================================================================================================================
 =======================================================================================================================
 */

SkillGatherFish::~SkillGatherFish()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillGatherFish::CanUseSkill(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ OPT_RESULT	res = SkillGather::CanUseSkill(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(res != OR_OK)
	{
		return res;
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillGatherFish::OnEvent_ProcOver(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t ItemBoxObjID = pAbilityOpera->m_Obj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ItemBoxObjID == INVALID_ID)
	{
		KCheck(FALSE);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = pMap->GetSpecificObjByID(ItemBoxObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj == NULL)
	{
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG, "SkillGather: not find obj=%d", ItemBoxObjID);
		return OR_INVALID_TARGET;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemBox *pItemBox = (ItemBox *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItemBox->GetObjType() != Object::OBJECT_CLASS_ITEM_BOX)
	{
		QLogSystem::QUICK_LOG
			(
				QUICK_LOG_DEBUG,
				"SkillGather: ItemBox obj	=	%d\r\n  is Not class of ITEM_CLASS_BOX",
				ItemBoxObjID
			);
		return OR_INVALID_TARGET;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			ItemBoxType = pItemBox->GetType();
	_GATHER_POINT_INFO	*pGET = g_GatherPointInfoTab.Get(ItemBoxType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGET);

	if(pGET->m_ScriptID > 0)
	{
		if
		(
			pMap->GetGatherPointManager()->CallLUAProcOverFunc
				(
					pGET->m_ScriptID,
					pPlayer->GetID(),
					ItemBoxObjID,
					pMap->MapID()
				)
		)
		{
			return OnEvent_ProcFailure(pPlayer);
		}
		else
		{
			if
			(
				pMap->GetGatherPointManager()->CallLUAOpenBoxFunc
					(
						pGET->m_ScriptID,
						pPlayer->GetID(),
						ItemBoxObjID,
						pMap->MapID()
					)
			)
			{
				return OnEvent_ProcFailure(pPlayer);
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			OPT_RESULT res = pPlayer->GetHumanAI()->PushCmd_UseAbility();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(res == OR_OK)
			{
			}

			assert(false);

			return OnEvent_ProcSuccess(pPlayer);
		}
	}
	else
	{
		return OnEvent_ProcSuccess(pPlayer);
	}

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SkillMachining::SkillMachining(const BaseSkill &a) :
	SkillCompound(a)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SkillMachining::IsGemConflict(Player *pPlayer, uchar GemIndex, uchar EquipIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	Item		*pGemItem = sItemInterface.GetBagItem(pPlayer, GemIndex);
	Item		*pEquipItem = sItemInterface.GetBagItem(pPlayer, EquipIndex);
	uint32		uGemSerialNumber = pGemItem->GetItemTableIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	LuaSystem * pLuaSystem;
	pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	/*~~~~~~~~~~~*/
	SItem	tmpGem;
	/*~~~~~~~~~~~*/

	for(int32 i = 0; i < pEquipItem->GetGemSlotMax(); ++i)
	{
		/*~~~~~~~~*/
		uint32	idx;
		/*~~~~~~~~*/

		idx = pEquipItem->GetEquipGemInfo(i).m_GemIndex;
		if(idx < 1) continue;

		if
		(
			pLuaSystem->RunScriptFunction
				(
					pPlayer->GetMap()->MapID(), 
					ABILITY_LOGIC_SCRIPT,
					"IsGemConflict",
					(int32) pPlayer->GetMap()->MapID(),
					(int32) uGemSerialNumber,
					(int32) idx
				)
		)
		{
			return FALSE;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillMachining::OnEvent_ProcOver(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	switch(pAbilityOpera->m_SubType)
	{
	case NORMAL_TYPE:
		return SkillCompound::OnEvent_ProcOver(pPlayer);

	case GEM_COMPOUND:
		{
			/*~~~~~~~~~~~~~~~~~*/
			OPT_RESULT res;
			BOOL	flag = FALSE;
			/*~~~~~~~~~~~~~~~~~*/

			LuaSystem * pLuaSystem;

			/*~~~~~~~~~~~~~~*/
			uint32	itemIndex;
			/*~~~~~~~~~~~~~~*/

			res = CanUseSkill(pPlayer);
			if(res != OR_OK)
			{
				return res;
			}

			pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

			itemIndex = sItemInterface.GetBagItem(pPlayer, pAbilityOpera->m_BagPos[0])->GetItemTableIndex();


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRet = sItemInterface.EraseBagItemBySlot
				(
					nullptr,
					pPlayer,
					pAbilityOpera->m_BagPos[0]
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(bRet)
			{
			}

			assert(false);

			bRet = sItemInterface.EraseBagItemBySlot(nullptr, pPlayer, pAbilityOpera->m_BagPos[1]);
			if(bRet)
			{
			}

			if
			(
				pLuaSystem->RunScriptFunction
					(
						pPlayer->GetMap()->MapID(), 
						ABILITY_LOGIC_SCRIPT,
						"CompoundProc",
						(int32) pPlayer->GetMap()->MapID(),
						(int32) pPlayer->GetID(),
						(int32) itemIndex
					) != FALSE
			)
			{
				flag = TRUE;
				pAbilityOpera->m_uItemIndex = itemIndex;
				res = OnEvent_ProcSuccess(pPlayer);
			}

			if(flag == TRUE)
			{
				return res;
			}
			else
			{
				return OR_FAILURE;
			}
		}
		break;

	case GEM_EMBED:
		{
			/*~~~~~~~~~~~~~~~~~*/
			OPT_RESULT res;
			enum EmbedResult { EMBED_SUCCESS = 0, GEM_GONE, EQUIP_GONE, BOTH_GONE, };
			EmbedResult	flag;
			/*~~~~~~~~~~~~~~~~~*/

			LuaSystem * pLuaSystem;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			uchar	GemBagIndex = pAbilityOpera->m_BagPos[0];
			uchar	EquipBagIndex = pAbilityOpera->m_BagPos[1];
			uint32	GemIndex = sItemInterface.GetBagItem(pPlayer, GemBagIndex)->GetItemTableIndex();
			uint32	EquipIndex = sItemInterface.GetBagItem(pPlayer, EquipBagIndex)->GetItemTableIndex();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			res = CanUseSkill(pPlayer);
			if(res != OR_OK)
			{
				return res;
			}

			pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

			flag = (EmbedResult) pLuaSystem->RunScriptFunction
				(
					pPlayer->GetMap()->MapID(), 
					ABILITY_LOGIC_SCRIPT,
					"EmbedProc",
					(int32) pPlayer->GetMap()->MapID(),
					(int32) pPlayer->GetID(),
					(int32) GemIndex
				);

			assert(false);

			/*~~~~~~~~~~~~~~~~~*/
			BOOL	bRet = FALSE;
			/*~~~~~~~~~~~~~~~~~*/

			switch(flag)
			{
			case EMBED_SUCCESS:
				return OnEvent_ProcSuccess(pPlayer);

			case GEM_GONE:
				bRet = sItemInterface.EraseBagItemBySlot(nullptr, pPlayer, GemBagIndex);

				assert(false);
				return OR_FAILURE;

			case EQUIP_GONE:
				bRet = sItemInterface.EraseBagItemBySlot(nullptr, pPlayer, EquipBagIndex);

				assert(false);
				return OR_FAILURE;

			case BOTH_GONE:
				bRet = sItemInterface.EraseBagItemBySlot(nullptr, pPlayer, EquipBagIndex);

				bRet = sItemInterface.EraseBagItemBySlot(nullptr, pPlayer, GemBagIndex);

				assert(false);
				return OR_FAILURE;

			default:
				KCheck(FALSE);
				return OR_DEFAULT_ERROR;
			}
		}
		break;

	default:
		KCheck(FALSE);
		return OR_DEFAULT_ERROR;
	}

	return OR_WARNING;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillMachining::OnEvent_ProcSuccess(Player *pPlayer, const _SKILL_PRESCRIPTION_DATA *pPrescrData)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPrescrData);

	/*~~~~~~~~*/
	OPT_RESULT res;
	/*~~~~~~~~*/

	res = SkillCompound::OnEvent_ProcSuccess(pPlayer, pPrescrData);
	if(res != OR_OK)
	{
		return res;
	}

	OnEvent_ProcSuccess(pPlayer);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillMachining::OnEvent_ProcSuccess(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	LuaSystem * pLuaSystem;
	pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameConnector	*pGameConnector;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pGameConnector = (GameConnector *) pPlayer->GetConnector();
	KCheck(pGameConnector != NULL);

	switch(pAbilityOpera->m_SubType)
	{
	case NORMAL_TYPE:
		break;

	case GEM_COMPOUND:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemType		GemType;
			uint32			bi;

			GemType = Serial2ItemType(pAbilityOpera->m_uItemIndex);

			sItemInterface.CreateItemToBagByItemIndex(nullptr, pPlayer, GemType.ToSerial(), bi);
			if(bi == INVALID_INDEX)
			{
				return OR_CREATE_ITEM_TO_BAG_ERROR;
			}

			assert(false);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pItem = sItemInterface.GetBagItem(pPlayer, bi);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pItem);
			
		}
		break;

	case GEM_EMBED:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pItem = sItemInterface.GetBagItem(pPlayer, pAbilityOpera->m_BagPos[1]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pItem);

			assert(false);
		}
		break;

	default:
		KCheck(FALSE);
		return OR_DEFAULT_ERROR;
	}

	pLuaSystem->RunScriptFunction
		(
			pPlayer->GetMap()->MapID(), 
			ABILITY_LOGIC_SCRIPT,
			"CheckAbilityLevel",
			(int32) pPlayer->GetMap()->MapID(),
			(int32) pPlayer->GetID(),
			(int32) pAbilityOpera->m_SkillID
		);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillMachining::CanUseSkill(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	SkillOpera	*pAbilityOpera;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAbilityOpera = pPlayer->GetAbilityOpera();
	KCheck(pAbilityOpera);

	switch(pAbilityOpera->m_SubType)
	{
	case NORMAL_TYPE:
		return SkillCompound::CanUseSkill(pPlayer);

	case GEM_COMPOUND:
		{
			/*~~~~~~~~*/
			OPT_RESULT res;
			/*~~~~~~~~*/

			res = BaseSkill::CanUseSkill(pPlayer);
			if(res != OR_OK)
			{
				return res;
			}

			if
			(
				(pAbilityOpera->m_BagPos[0] < 0)
			||	(pAbilityOpera->m_BagPos[0] >= MAX_BAG_SIZE)
			||	(pAbilityOpera->m_BagPos[1] < 0)
			||	(pAbilityOpera->m_BagPos[1] >= MAX_BAG_SIZE)
			)
			{
				KCheck(FALSE);
				return OR_ABILITY_OPERATOR_BAG_POS_ERROR;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pGem1Item = sItemInterface.GetBagItem(pPlayer, pAbilityOpera->m_BagPos[0]);
			Item	*pGem2Item = sItemInterface.GetBagItem(pPlayer, pAbilityOpera->m_BagPos[1]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck((pGem1Item != NULL) && (pGem2Item != NULL));

			if((pGem1Item->GetItemClass() != ICLASS_GEM) || (pGem2Item->GetItemClass() != ICLASS_GEM))
			{
				return OR_STUFF_LACK;
			}

			return OR_OK;
		}
		break;

	case GEM_EMBED:
		{
			/*~~~~~~~~*/
			OPT_RESULT res;
			/*~~~~~~~~*/

			res = BaseSkill::CanUseSkill(pPlayer);
			if(res != OR_OK)
			{
				return res;
			}

			if
			(
				(pAbilityOpera->m_BagPos[0] < 0)
			||	(pAbilityOpera->m_BagPos[0] >= MAX_BAG_SIZE)
			||	(pAbilityOpera->m_BagPos[1] < 0)
			||	(pAbilityOpera->m_BagPos[1] >= MAX_BAG_SIZE)
			)
			{
				KCheck(FALSE);
				return OR_ABILITY_OPERATOR_BAG_POS_ERROR;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pGemItem = sItemInterface.GetBagItem(pPlayer, pAbilityOpera->m_BagPos[0]);
			Item	*pEquipItem = sItemInterface.GetBagItem(pPlayer, pAbilityOpera->m_BagPos[1]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck((pGemItem != NULL) && (pEquipItem != NULL));

			if((pGemItem->GetItemClass() != ICLASS_GEM) || (pEquipItem->GetItemClass() != ICLASS_EQUIP))
			{
				return OR_STUFF_LACK;
			}

			if(IsGemConflict(pPlayer, pAbilityOpera->m_BagPos[0], pAbilityOpera->m_BagPos[1]) == FALSE)
			{
				return OR_GEM_CONFLICT;
			}

			LuaSystem * pLuaSystem;
			pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

			if
			(
				pEquipItem->GetGemSlotMax() <= pEquipItem->GetEquipGemCount()
			||	pLuaSystem->RunScriptFunction
					(
						pPlayer->GetMap()->MapID(), 
						ABILITY_LOGIC_SCRIPT,
						"TooManyGems",
						(int32) pPlayer->GetMap()->MapID(),
						(int32) pPlayer->GetID(),
						(int32) pAbilityOpera->m_BagPos[1]
					)
			)
			{
				return OR_GEM_SLOT_LACK;
			}

			return OR_OK;
		}
		break;

	default:
		KCheck(FALSE);
		return OR_DEFAULT_ERROR;
	}

	return OR_WARNING;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}
