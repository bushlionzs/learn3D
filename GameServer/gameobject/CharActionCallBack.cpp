/*$T MapServer/Server/Action/ActionCallBack.cpp GC 1.140 10/10/07 10:07:18 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "CharActionCallBack.h"
#include "Character.h"
#include "CharActionDelegator.h"
#include "script/LuaSystem.h"
#include "skill/Spell_Logic_Base.h"


ActionCallBackFunctorForSkill_T const	g_ActionCallBackFunctorForSkill;
ActionCallBackFunctorForScript_T const	g_ActionCallBackFunctorForScript;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ActionCallBackFunctor_T const &GetGlobalScriptCallBackFunctor(void)
{
	return static_cast<ActionCallBackFunctor_T const &>(g_ActionCallBackFunctorForScript);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ActionCallBackFunctor_T const &GetGlobalSkillCallBackFunctor(void)
{
	return static_cast<ActionCallBackFunctor_T const &>(g_ActionCallBackFunctorForSkill);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character				&rActor = *(static_cast<Character *>(pObj));
		SpellTargetingAndDepletingParams	&rScriptParams = rActor.GetTargetingAndDepletingParams();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nID == rScriptParams.GetActivatedScript())
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::CanDoThisActionInThisStatus(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character				&rActor = *(static_cast<Character *>(pObj));
		SpellTargetingAndDepletingParams	&rTargetingAndDepletingParams = rActor.
			GetTargetingAndDepletingParams();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(TRUE == rActor.CanUseThisSpellInThisStatus(rTargetingAndDepletingParams.GetActivatedSpell()))
		{
			return TRUE;
		}

		if(TRUE == rActor.CanActionFlag1() && TRUE == rActor.CanActionFlag2())
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::OnEvent_Interrupt(ActionParams_T &rParams) const
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::OnEvent_ActivateOnce(ActionParams_T &rParams) const
{
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::OnEvent_ActivateEachTick(ActionParams_T &rParams) const
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::OnEvent_DisturbForCharging(ActionParams_T &rParams) const
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForScript_T::OnEvent_DisturbForChanneling(ActionParams_T &rParams) const
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionCallBackFunctorForScript_T::ResetForNextAction(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character				&rActor = *(static_cast<Character *>(pObj));
		SpellTargetingAndDepletingParams	&rScriptParams = rActor.GetTargetingAndDepletingParams();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rScriptParams.Reset();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	&rActor = *(static_cast<Character *>(pObj));
		SpellInfo	&rSkillInfo = rActor.GetSpellInfo();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nID == rSkillInfo.GetSpellID())
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::CanDoThisActionInThisStatus(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character				&rActor = *(static_cast<Character *>(pObj));
		SpellTargetingAndDepletingParams	&rTargetingAndDepletingParams = rActor.
			GetTargetingAndDepletingParams();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(TRUE == rActor.CanUseThisSpellInThisStatus(rTargetingAndDepletingParams.GetActivatedSpell()))
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::OnEvent_Interrupt(ActionParams_T &rParams) const
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::OnEvent_ActivateOnce(ActionParams_T &rParams) const
{
	Object* pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pObj)
	{
		return FALSE;
	}

	if (TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character& rActor = *(static_cast<Character*>(pObj));
		SpellInfo& rSkillInfo = rActor.GetSpellInfo();
		BaseSpellLogic const* pLogic = Spell_GetLogic(rSkillInfo);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL != pLogic)
		{
			return pLogic->Action_ActivateOnceDispatch(rActor);
		}
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::OnEvent_ActivateEachTick(ActionParams_T &rParams) const
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::OnEvent_DisturbForCharging(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	&rActor = *(static_cast<Character *>(pObj));
		SpellInfo	&rSkillInfo = rActor.GetSpellInfo();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!IsCanInteruptChargOrChannel(rParams))
		{
			return TRUE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Time_t		nContinuance = rParams.GetContinuance();
		Time_t const	nChargeTime = rSkillInfo.GetChargeTime();
		Time_t		nLimitTime = nChargeTime - nContinuance;
		SpellID_t	iSkillID = rSkillInfo.GetSpellID();
		float		fBackRate = (float) rSkillInfo.GetChannelBackRate();
		Time_t		nDeltaTime = (int32) (fBackRate * nChargeTime / 100.0f);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nDeltaTime > nLimitTime)
		{
			nDeltaTime = nLimitTime;
		}

		nContinuance += nDeltaTime;
		rParams.SetContinuance(nContinuance);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ActionDelegator	ActionOptor;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		ActionOptor.Broadcast_UnitChargeTimeChanged(rActor, nDeltaTime);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::OnEvent_DisturbForChanneling(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	&rActor = *(static_cast<Character *>(pObj));
		SpellInfo	&rSkillInfo = rActor.GetSpellInfo();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!IsCanInteruptChargOrChannel(rParams))
		{
			return TRUE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Time_t		nContinuance = rParams.GetContinuance();
		Time_t		nChannelTime = rSkillInfo.GetChannelTime();
		SpellID_t	iSkillID = rSkillInfo.GetSpellID();
		float		fBackRate = (float) rSkillInfo.GetChannelBackRate();
		Time_t		nDeltaTime = (int32) (fBackRate * nChannelTime / 100.0f);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nDeltaTime > nContinuance)
		{
			nDeltaTime = nContinuance;
		}

		nContinuance -= nDeltaTime;
		rParams.SetContinuance(nContinuance);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ActionDelegator	ActionOptor;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		ActionOptor.Broadcast_UnitChannelTimeChanged(rActor, nDeltaTime);
		if(0 >= nContinuance)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionCallBackFunctorForSkill_T::ResetForNextAction(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = rParams.GetActor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return;
	}

	if(TRUE == IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character				&rActor = *(static_cast<Character *>(pObj));
		SpellInfo				&rSkillInfo = rActor.GetSpellInfo();
		SpellTargetingAndDepletingParams	&rParams = rActor.GetTargetingAndDepletingParams();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rParams.Reset();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionCallBackFunctorForSkill_T::IsCanInteruptChargOrChannel(ActionParams_T &rParams) const
{
	 return FALSE;
}
