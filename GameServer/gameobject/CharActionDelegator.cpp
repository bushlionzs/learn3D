/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	ActionDelegator.cpp
file path:	F:\khan2\src\MapServer\Server\GameLogic
file base:
file ext:	cpp
author:		
modified:	wujianping
purpose:	动作接口类 也就是动作封装类 其他模块对动作相关操作只与本类打交道
**********************************************************************************************/


#include "stdafx.h"
#include "TypeDefine.h"
#include "CharActionLogic.h"

#include "skill/Spell_Helper.h"
#include "CharActionDelegator.h"
#include "Character.h"
#include "map/game_map.h"
#include "SpellDataLoader.h"
#include "TabDefine.h"
#include "data/data_manager.h"
#include "net/messages/SCCharSkill_Gather.h"
#include "net_message_manager.h"


enum { MIN_ACTION_TIME = 500, };

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::IsPerformingTheSpecificSkill(Character &rActor, SpellID_t nSkillID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T			&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return FALSE;
	}

	return pActionLogic->IsPerformingSpecificSkill(rActionParams, nSkillID);
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::IsPerformingTheSpecificScript(Character &rActor, ScriptID_t nScriptID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T			&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return FALSE;
	}

	return pActionLogic->IsPerformingSpecificScript(rActionParams, nScriptID);
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::IsChanneling(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T			&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return FALSE;
	}

	if(ACTION_CHANNEL != pActionLogic->GetLogicID())
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
BOOL ActionDelegator::IsCharging(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T			&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return FALSE;
	}

	if(ACTION_CHARGE != pActionLogic->GetLogicID())
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
BOOL ActionDelegator::Register_ChargeActionForSpell(Character &rActor, ActionID_t nAction, Time_t nContinuance) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CanDoNextAction(rActor))
	{
		return FALSE;
	}

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	rActionParams.SetContinuance(nContinuance);
	rActionParams.SetCallBackFunctor(GetGlobalSkillCallBackFunctor());
	rActor.SetActionLogic(&(GetGlobalChargeActionLogic()));

	rActor.AddLogicCount();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo	&oSkillInf = rActor.GetSpellInfo();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	oSkillInf.SetSpellLogicCount(rActor.GetLogicCount());
	Broadcast_UnitStartChargeAction(rActor, nAction, nContinuance);
	if(0 == rActor.GetActionTime())
	{
		rActor.SetActionTime(MIN_ACTION_TIME);
	}

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::Register_ChargeActionForScript(Character &rActor, ActionID_t nAction, Time_t nContinuance) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CanDoNextAction(rActor))
	{
		return FALSE;
	}

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	rActionParams.SetContinuance(nContinuance);
	rActionParams.SetCallBackFunctor(GetGlobalScriptCallBackFunctor());
	rActor.SetActionLogic(&(GetGlobalChargeActionLogic()));

	rActor.AddLogicCount();
	Broadcast_UnitStartChargeAction(rActor, nAction, nContinuance);
	if(0 == rActor.GetActionTime())
	{
		rActor.SetActionTime(MIN_ACTION_TIME);
	}

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::Register_ChannelActionForSpell
(
	Character	&rActor,
	ActionID_t	nAction,
	Time_t		nContinuance,
	Time_t		nInterval
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CanDoNextAction(rActor))
	{
		return FALSE;
	}

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	if(500 > nContinuance)
	{
		KCheckEx(FALSE, "[ActionDelegator_T::RegisterChannelActionForSkill] illegal nCountinuance found!!");
		nContinuance = 2000;
	}
	rActionParams.SetContinuance(nContinuance);

	if(500 > nInterval && 0 < nInterval)
	{
		KCheckEx(FALSE, "[ActionDelegator_T::RegisterChannelActionForSkill] illegal interval found!!");
		nInterval = 2000;
	}

	// 时间间隔小于等于0时，时间间隔设置为最大引导时间
	if (nInterval <= 0)
		rActionParams.SetInterval(nContinuance);
	else
		rActionParams.SetInterval(nInterval);
	
	rActionParams.SetCallBackFunctor(GetGlobalSkillCallBackFunctor());
	rActor.SetActionLogic(&(GetGlobalChannelActionLogic()));

	rActor.AddLogicCount();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo	&oSkillInf = rActor.GetSpellInfo();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	oSkillInf.SetSpellLogicCount(rActor.GetLogicCount());
	Broadcast_UnitStartChannelAction(rActor, nAction, nContinuance);
	if(0 == rActor.GetActionTime())
	{
		rActor.SetActionTime(MIN_ACTION_TIME);
	}

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::Register_ChannelActionForScript
(
	Character	&rActor,
	ActionID_t	nAction,
	Time_t		nContinuance,
	Time_t		nInterval
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CanDoNextAction(rActor))
	{
		return FALSE;
	}

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	if(500 > nContinuance)
	{
		KCheckEx(FALSE, "[ActionDelegator_T::RegisterChannelActionForScript] illegal nCountinuance found!!");
		nContinuance = 2000;
	}
	rActionParams.SetContinuance(nContinuance);

	if(500 > nInterval && 0 < nInterval)
	{
		KCheckEx(FALSE, "[ActionDelegator_T::RegisterChannelActionForScript] illegal interval found!!");
		nInterval = 2000;
	}

	// 时间间隔小于等于0时，时间间隔设置为最大引导时间
	if (nInterval <= 0)
		rActionParams.SetInterval(nContinuance);
	else
		rActionParams.SetInterval(nInterval);

	rActionParams.SetInterval(nInterval);
	rActionParams.SetCallBackFunctor(GetGlobalScriptCallBackFunctor());
	rActor.SetActionLogic(&(GetGlobalChannelActionLogic()));

	rActor.AddLogicCount();
	Broadcast_UnitStartChannelAction(rActor, nAction, nContinuance);
	if(0 == rActor.GetActionTime())
	{
		rActor.SetActionTime(MIN_ACTION_TIME);
	}

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::Register_InstantActionForSpell(Character &rActor, ActionID_t nAction, Time_t nActionTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CanDoNextAction(rActor))
	{
		return FALSE;
	}

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	rActor.SetActionLogic(NULL);

	rActor.AddLogicCount();
	Broadcast_UnitStartInstantAction(rActor, nAction, nActionTime);
	if(0 == rActor.GetActionTime())
	{
		rActor.SetActionTime(MIN_ACTION_TIME);
	}

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::Register_InstantActionForScript(Character &rActor, ActionID_t nAction, Time_t nActionTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CanDoNextAction(rActor))
	{
		return FALSE;
	}

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	rActor.SetActionLogic(NULL);

	rActor.AddLogicCount();
	Broadcast_UnitStartInstantAction(rActor, nAction, nActionTime);
	if(0 == rActor.GetActionTime())
	{
		rActor.SetActionTime(MIN_ACTION_TIME);
	}

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::Register_EmoteAction(Character &rActor, ActionID_t nAction) const
{
	__GUARD__ if(FALSE == CanDoNextAction(rActor))
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ActionParams_T	&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rActionParams.Reset();
	rActionParams.SetActor(&rActor);
	rActor.SetActionLogic(NULL);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTemplateData const *pSkill = DataManager::GetSingletonPtr()->getSpellTemplate(nAction);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		KCheckEx(FALSE, "[ActionDelegator_T::RegisterEmoteAction]: unknow Action found!!");
		return FALSE;
	}

	rActor.AddLogicCount();
	Broadcast_UnitStartInstantAction(rActor, nAction, pSkill->GetPlayActionTime());

	rActor.OnEvent_ActionStarted();
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::DisturbCurrentAction(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL		bRet = FALSE;
	ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T		&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return FALSE;
	}

	bRet = pActionLogic->OnEvent_Disturb(rActionParams);
	if(FALSE == bRet)
	{
		InterruptCurrentAction(rActor);
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::OnEvent_HeartBeat(Character &rActor, Time_t nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL		bRet = FALSE;
	ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T		&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return FALSE;
	}

	if(FALSE == rActor.IsAlive() || FALSE == rActor.IsActiveObj())
	{
		return FALSE;
	}

	bRet = pActionLogic->HeartBeat(rActionParams, nDeltaTime);
	if(FALSE == bRet)
	{
		InterruptCurrentAction(rActor);
	}
	else
	{
		if(0 >= rActionParams.GetContinuance())
		{
			CurrentActionFinished(rActor);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionDelegator::CanDoNextAction(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T			&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pActionLogic)
	{
		return TRUE;
	}

	if(0 >= rActionParams.GetContinuance())
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::CurrentActionFinished(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL		bRet = FALSE;
	ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T		&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



	ResetForNextAction(rActor);
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ActionDelegator::StopChanneling(Character &rActor)
{
	__GUARD__
	ActionParams_T		&rActionParams = rActor.GetActionParams();
	rActionParams.SetContinuance(0);
	__UNGUARD__
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::InterruptCurrentAction(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL		bRet = FALSE;
	ActionLogic const	*pActionLogic = rActor.GetActionLogic();
	ActionParams_T		&rActionParams = rActor.GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pActionLogic)
	{
		pActionLogic->OnEvent_Interrupt(rActionParams);
	}

	if(IsChanneling(rActor) || IsCharging(rActor))
	{
		
	}

	ResetForNextAction(rActor);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::Broadcast_UnitStartChargeAction(Character &rActor, ActionID_t nAction, Time_t nContinuance) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rActor.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rActor.GetTargetingAndDepletingParams();
	
	SCCharSkill_Gather* packet = new SCCharSkill_Gather;
	packet->setObjId(rActor.GetID());
	packet->setLogicCount(rActor.GetLogicCount());
	packet->setSkillDataId(nAction);
	packet->setUserPosition((rActor.GetGLPos()));
	packet->setTargetId(rParams.GetTargetObj());
	packet->setTargetPosition((const GLPos*)&rParams.GetTargetPosition());
	packet->setDir(rParams.GetTargetDirection());
	packet->setTotalTime(nContinuance);
	NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::Broadcast_UnitStartChannelAction
(
	Character	&rActor,
	ActionID_t	nAction,
	Time_t		nContinuance
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rActor.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rActor.GetTargetingAndDepletingParams();
	

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::Broadcast_UnitStartInstantAction(Character &rActor, ActionID_t nAction, Time_t nActionTime) const
{
	__GUARD__ return;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::Broadcast_UnitChargeTimeChanged(Character &rActor, Time_t nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rActor.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rActor.GetTargetingAndDepletingParams();
	

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::Broadcast_UnitChannelTimeChanged(Character &rActor, Time_t nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rActor.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rActor.GetTargetingAndDepletingParams();
	

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ActionDelegator::ResetForNextAction(Character &rActor) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionParams_T	&rActionParams = rActor.GetActionParams();
	ActionCallBackFunctor_T const	*pCallBack = rActionParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		pCallBack->ResetForNextAction(rActionParams);
	}

	rActionParams.Reset();
	rActor.SetActionLogic(NULL);
	__UNGUARD__
}

ActionDelegator const g_ActionDelegator;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ActionDelegator const &GetGlobalActionDelegator(void)
{
	return g_ActionDelegator;
}
