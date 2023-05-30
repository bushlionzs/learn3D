#include "stdafx.h"
#include "Spell_ScriptLogic.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "Spell_EffectLogicManager.h"
#include "TabDefine.h"
#include "gameobject/CharActionDelegator.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL SpellScriptLogic::StartCharging(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ long				nMaxTime = 0;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Time_t					nChargeTime = rSkillInfo.GetChargeTime();
	BOOL					bRet = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == rParams.GetIgnoreConditionCheckFlag())
	{
		if(FALSE == LUA_OnConditionCheck_i(rMe))
		{
			return FALSE;
		}
	}

	if(0 < nChargeTime)
	{
		bRet = GetGlobalActionDelegator().Register_ChargeActionForScript
			(
				rMe,
				rParams.GetActivatedSpell(),
				nChargeTime
			);
	}
	else
	{
		return StartLaunching(rMe);
	}

	if(TRUE == bRet)
	{
		rParams.SetErrCode(OR_OK);
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::StartChanneling(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Time_t					nChannelTime = rSkillInfo.GetChannelTime();
	Time_t					nCooldown = rSkillInfo.GetCooldownTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 < nChannelTime)
	{
		if(FALSE == rParams.GetIgnoreConditionCheckFlag())
		{
			if(FALSE == LUA_OnConditionCheck_i(rMe))
			{
				return FALSE;
			}

			if(FALSE == LUA_OnDeplete_i(rMe))
			{
				return FALSE;
			}
		}

		SetCooldown(rMe, (CooldownID_t) rSkillInfo.GetCooldownID(), nCooldown);
		if
		(
			TRUE == GetGlobalActionDelegator().Register_ChannelActionForScript
				(
					rMe,
					rParams.GetActivatedSpell(),
					nChannelTime,
					rSkillInfo.GetChargesOrInterval()
				)
		)
		{
			rParams.SetErrCode(OR_OK);
			LUA_OnActivateOnce_i(rMe);
			return TRUE;
		}
	}
	else
	{
		return StartLaunching(rMe);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::StartLaunching(Character &rMe) const
{
	__GUARD__ return Action_ActivateOnceDispatch(rMe);
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::Item_IsSpellLikeScript(Character &rMe, ScriptID_t nScript) const
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Item_IsSkillLikeScript]: pMap == NULL!!!!Check it now!!");
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Item_IsSkillLikeScript]: pLuaInerface == NULL!!!!Check it now!!");
		return FALSE;
	}

	try
	{
		nRet = pLuaSystem->RunScriptFunction(pMap->MapID(),nScript, "IsSkillLikeScript", pMap->MapID(), rMe.GetID());
	}
	catch(...)
	{
		nRet = 0;
	}

	return 0 < nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::CallItemDefaultEvent(Character &rMe, ScriptID_t nScript, int32 nBagIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::CallDefaultEvent]: pMap == NULL!!!!Check it now!!");
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::CallDefaultEvent]: pLuaInerface == NULL!!!!Check it now!!");
		return FALSE;
	}

	try
	{
		nRet = pLuaSystem->RunScriptFunction(pMap->MapID(),nScript, DEF_PROC_EVENT_ENTRY_FN, pMap->MapID(), rMe.GetID(), nBagIndex);
	}
	catch(...)
	{
		nRet = 0;
	}

	return 0 < nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::Equip_CallDefaultEvent(Character &rMe, ScriptID_t nScript, int32 equipPoint, int32 opType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::CallDefaultEvent]: pMap == NULL!!!!Check it now!!");
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::CallDefaultEvent]: pLuaInerface == NULL!!!!Check it now!!");
		return FALSE;
	}

	try
	{
		nRet = pLuaSystem->RunScriptFunction
			(
				pMap->MapID(),
				nScript,
				DEF_PROC_EVENT_ENTRY_FN,
				pMap->MapID(),
				rMe.GetID(),
				equipPoint,
				opType
			);
	}
	catch(...)
	{
		nRet = 0;
	}

	return 0 < nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::Action_ActivateOnceDispatch(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL				bRet = FALSE;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == rParams.GetIgnoreConditionCheckFlag())
	{
		if(FALSE == LUA_OnConditionCheck_i(rMe))
		{
			return FALSE;
		}

		if(FALSE == LUA_OnDeplete_i(rMe))
		{
			return FALSE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Time_t	nPlayActionTime = rSkillInfo.GetPlayActionTime();
	Time_t	nCooldown = rSkillInfo.GetCooldownTime();
	Time_t	nDelayTime = rSkillInfo.GetDelayTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if
	(
		FALSE == GetGlobalActionDelegator().Register_InstantActionForScript
			(
				rMe,
				rParams.GetActivatedSpell(),
				nPlayActionTime
			)
	)
	{
		return FALSE;
	}

	rMe.SetActionTime(nPlayActionTime);

	SetCooldown(rMe, (CooldownID_t) rSkillInfo.GetCooldownID(), nCooldown);
	rParams.SetDelayTime(rSkillInfo.GetDelayTime());
	return LUA_OnActivateOnce_i(rMe);
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::Action_ActivateEachTickDispatch(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return LUA_OnActivateEachTick_i(rMe);
	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellScriptLogic::SetCooldown(Character &rMe, CooldownID_t nID, int32 nCooldownTime) const
{
	__GUARD__ rMe.SetCooldown((CooldownID_t) nID, nCooldownTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::RegisterImpactEvent
(
	Character	&rReceiver,
	Character	&rSender,
	UNIT_EFFECT	&rImp,
	Time_t		nDelayTime,
	BOOL		bCriticalFlag
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rSender.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rSender.GetTargetingAndDepletingParams();
	Map					*pMap = rReceiver.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rImp.SetSkillID(rSkillInfo.GetSpellID());
	if(TRUE == bCriticalFlag)
	{
		rImp.MarkCriticalFlag();
	}

	if(NULL != pMap)
	{
		return pMap->GetEventCore().RegisterImpactEvent(rReceiver.GetID(), rSender.GetID(), rImp, nDelayTime);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::RegisterBeSkillEvent
(
	Character	&rReceiver,
	Character	&rSender,
	int32		nBehaviorType,
	Time_t		nDelayTime
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Map	*pMap = rReceiver.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		return pMap->GetEventCore().RegisterBeSkillEvent
			(
				rReceiver.GetID(),
				rSender.GetID(),
				nBehaviorType,
				nDelayTime
			);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::LUA_CancelImpacts(Character &rMe, ScriptID_t nScriptID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(nScriptID == INVALID_ID)
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_CancelImpacts]: pMap == NULL!!!!Check it now!!");
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_CancelImpacts]: pLuaInerface == NULL!!!!Check it now!!");
		return FALSE;
	}

	try
	{
		nRet = pLuaSystem->RunScriptFunction(pMap->MapID(),nScriptID, "CancelImpacts", pMap->MapID(), rMe.GetID());
	}
	catch(...)
	{
		nRet = 0;
	}

	return 0 < nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::LUA_OnConditionCheck_i(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32				nRet = 0;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rScriptParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rScriptParams.GetActivatedScript() == INVALID_ID)
	{
		return TRUE;
	}

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rScriptParams.SetErrCode(OR_INVALID_SKILL);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnConditionCheck]: pMap == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_MAP);
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnConditionCheck]: pLuaInerface == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_POINTER);
		return FALSE;
	}

	try
	{
		nRet = pLuaSystem->RunScriptFunction
			(
				pMap->MapID(),
				rScriptParams.GetActivatedScript(),
				"OnConditionCheck",
				pMap->MapID(),
				rMe.GetID()
			);
	}
	catch(...)
	{
		nRet = 0;
	}

	if(0 < nRet)
	{
		rScriptParams.SetErrCode(OR_OK);
		return TRUE;
	}

	return 0 < nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::LUA_OnDeplete_i(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32				nRet = 0;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rScriptParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rScriptParams.SetErrCode(OR_INVALID_SKILL);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnDeplete]: pMap == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_MAP);
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnDeplete]: pLuaInerface == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_POINTER);
		return FALSE;
	}

	try
	{
		nRet = pLuaSystem->RunScriptFunction
			(
				pMap->MapID(),
				rScriptParams.GetActivatedScript(),
				"OnDeplete",
				pMap->MapID(),
				rMe.GetID()
			);
	}
	catch(...)
	{
		nRet = 0;
	}

	if(0 < nRet)
	{
		rScriptParams.SetErrCode(OR_OK);
	}

	return nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::LUA_OnActivateOnce_i(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32				nRet = 0;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rScriptParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rScriptParams.SetErrCode(OR_INVALID_SKILL);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnActivateOnce]: pMap == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_MAP);
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnActivateOnce]: pLuaInerface == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_POINTER);
		return FALSE;
	}

	try
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SItemGuid		itemGuid = rScriptParams.GetDepletedItemGuid();
		int32			nItemIndex = rScriptParams.GetItemIndexOfDepletedItem();
		SMiscItemInfoTab	*pCommItem = g_ItemTab.GetCommItemInfoTB(nItemIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pCommItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nImpactId = pCommItem->m_nImpactID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nRet = pLuaSystem->RunScriptFunction
			(
				pMap->MapID(),
				rScriptParams.GetActivatedScript(),
				"OnActivateOnce",
				pMap->MapID(),
				rMe.GetID(),
				nImpactId
			);
	}
	catch(...)
	{
		nRet = 0;
	}

	if(0 < nRet)
	{
		rScriptParams.SetErrCode(OR_OK);
	}

	return 0 < nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellScriptLogic::LUA_OnActivateEachTick_i(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32				nRet = 0;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rScriptParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rScriptParams.SetErrCode(OR_INVALID_SKILL);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellScriptLogic::Script_OnActivateEachTick]: pMap == NULL!!!!Check it now!!");
		rScriptParams.SetErrCode(OR_NULL_MAP);
		return FALSE;
	}

	LuaScript::LuaSystem * pLuaSystem = pMap->GetLuaSystem();
	if(NULL == pLuaSystem)
	{
		KCheckEx
		(
			FALSE,
			"[SpellScriptLogic::Script_OnActivateEachTick]: pLuaInerface == NULL!!!!Check it now!!"
		);
		rScriptParams.SetErrCode(OR_NULL_POINTER);
		return FALSE;
	}

	try
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SItemGuid		itemGuid = rScriptParams.GetDepletedItemGuid();
		int32			nItemIndex = rScriptParams.GetItemIndexOfDepletedItem();
		SMiscItemInfoTab	*pCommItem = g_ItemTab.GetCommItemInfoTB(nItemIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pCommItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nImpactId = pCommItem->m_nImpactID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nRet = pLuaSystem->RunScriptFunction
			(
				pMap->MapID(),
				rScriptParams.GetActivatedScript(),
				"OnActivateEachTick",
				pMap->MapID(),
				rMe.GetID(),
				nImpactId
			);
	}
	catch(...)
	{
		nRet = 0;
	}

	if(0 < nRet)
	{
		rScriptParams.SetErrCode(OR_OK);
		return TRUE;
	}

	return(0 < nRet);
	__UNGUARD__ return FALSE;
}

SpellScriptLogic	g_ScriptLogic;
