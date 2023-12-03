/*$T MapServer/Server/Spell/SpellLogic/CommonSpellLogic.cpp GC 1.140 10/10/07 10:07:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "gameobject/Behavior_Character.h"
#include "gameobject/Character.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "Spell_EffectLogicManager.h"
#include "Spell_Logic_Misc.h"
#include "server_manager.h"
#include "ScriptDef.h"
#include "script/LuaSystem.h"
#include "net/messages/SCManipulatePetRet.h"
#include "map/BeastieManager.h"
#include "net_message_manager.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL CommonSpell001::SpecificOperationOnSpellStart(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Player					*pHumanMe = (Player *) &rMe;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(FALSE == pHumanMe->IsCanTakeMoreHorse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pTar = (Character *) GetTargetObj(rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if(Object::OBJECT_CLASS_HORSE != pTar->GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell001::OnEvent_Interrupt(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Character				*pTar = (Character *) (GetTargetObj(rMe));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if
	(
		NULL == pTar
	||	FALSE == pTar->IsAlive()
	||	FALSE == pTar->IsActiveObj()
	||	Object::OBJECT_CLASS_HORSE != pTar->GetObjType()
	)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}



	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell001::OnEvent_Cancel(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Character				*pTar = (Character *) (GetTargetObj(rMe));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if
	(
		NULL == pTar
	||	FALSE == pTar->IsAlive()
	||	FALSE == pTar->IsActiveObj()
	||	Object::OBJECT_CLASS_PET != pTar->GetObjType()
	)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell001::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == rTar.IsAlive() || FALSE == rTar.IsActiveObj() || Object::OBJECT_CLASS_HORSE != rTar.GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rParams.SetErrCode(OR_U_CANNT_DO_THIS_RIGHT_NOW);
		return FALSE;
	}

	

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell002::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32					nValue = 0;
		UNIT_EFFECT				impact;
		SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
		SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nValue = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);

		if(INVALID_ID != nValue)
		{
			g_EffectInterface.InitEffectFromData(nValue, impact, rMe);

			if(!RegisterImpactEvent(rTar, rMe, impact, 0, bCriticalFlag))
			{
				return FALSE;
			}
		}

		
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell003::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	ID_t					nTrapDataIndex = rSkillInfo.GetDescriptorByIndex(0)->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 < nTrapDataIndex)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SpecialCreature* pTrap = nullptr;

		if(NULL == pTrap)
		{
			KCheckEx(FALSE, "[CommonSpell003::EffectOnUnitOnce]: Can't create Special Obj!");
			return FALSE;
		}

		RegisterActiveObj(*pTrap, rMe, 500);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell004::SpecificOperationOnSpellStart(Character &rMe) const
{
	SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	Character* pTar = (Character*)GetTargetObj(rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if (Object::OBJECT_CLASS_BEASTIE != pTar->GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player* pPlayer = (Player*)&rMe;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);


	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	ret = luaSystem->RunScriptFunction
	(
		pPlayer->GetMap()->MapID(),
		SCRIPT_ID_BEASTIE_CAPTURE,
		"IfCanCapture",
		(int32)pPlayer->GetMap()->MapID(),
		(int32)pPlayer->GetID(),
		(int32)pTar->GetID(),
		(int32)pTar->GetDataID()
	);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!ret)
	{
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell004::OnEvent_Interrupt(Character &rMe) const
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell004::OnEvent_Cancel(Character &rMe) const
{
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CommonSpell004::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (FALSE == rTar.IsAlive() || FALSE == rTar.IsActiveObj() || Object::OBJECT_CLASS_BEASTIE != rTar.GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if (Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rParams.SetErrCode(OR_U_CANNT_DO_THIS_RIGHT_NOW);
		return FALSE;
	}
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nDataIndex = GetSpellInfoDescriptorValueByIndex(rSkillInfo, 0);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_EffectInterface.SendEffectToUnit(rTar, nDataIndex, rMe.GetID(), 500);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player* pPlayer = (Player*)&rMe;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			ret = luaSystem->RunScriptFunction
	(
		pPlayer->GetMap()->MapID(),
		SCRIPT_ID_BEASTIE_CAPTURE,
		"OnAddBeastieItem",
		(int32)pPlayer->GetMap()->MapID(),
		(int32)pPlayer->GetID(),
		(int32)rTar.GetID(),
		(int32)rTar.GetDataID()
	);

	SCManipulatePetRet* packet = new SCManipulatePetRet;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (ret == 1)
	{
		packet->setManipulateRet(SCManipulatePetRet::OPT_HORSE_RET_CAPTURESUCC);
		
		

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BeastieManager* pBeastieMgr = rMe.GetMap()->GetBeastieManager();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pBeastieMgr)
		{
			pBeastieMgr->RemoveBeastie(rTar.GetID());
		}
	}
	else
	{
		packet->setManipulateRet(SCManipulatePetRet::OPT_HORSE_RET_CAPTUREFALID);
	}

	NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);

	return TRUE;
}
