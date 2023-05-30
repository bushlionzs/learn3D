/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	ActionLogic.cpp
			file path:	F:\khan2\src\MapServer\Server\GameLogic
			file base:
			file ext:	cpp
author:		
modified:	wujianping
purpose:	动作逻辑处理类 一共有3种动作
			1聚气动作
			2引导动作
			3瞬发动作
**********************************************************************************************/


#include "stdafx.h"
#include "TypeDefine.h"
#include "CharActionLogic.h"
#include "CharActionCallBack.h"
#include "CharActionDelegator.h"
#include "Character.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL ActionLogic::IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		return pCallBack->IsPerformingSpecificSkill(rParams, nID);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ActionLogic::IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		return pCallBack->IsPerformingSpecificScript(rParams, nID);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

ChargeActionLogic const	g_ChargeActionLogic;
ChannelActionLogic const	g_ChannelActionLogic;
InstantActionLogic const	g_InstantActionLogic;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ActionLogic const &GetGlobalChargeActionLogic(void)
{
	return static_cast<ActionLogic const &>(g_ChargeActionLogic);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ActionLogic const &GetGlobalChannelActionLogic(void)
{
	return static_cast<ActionLogic const &>(g_ChannelActionLogic);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ActionLogic const &GetGlobalInstantActionLogic(void)
{
	return static_cast<ActionLogic const &>(g_InstantActionLogic);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ChannelActionLogic::HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCallBack)
	{
		return FALSE;
	}

	if(FALSE == pCallBack->CanDoThisActionInThisStatus(rParams))
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Time_t	nIntervalElapsed = rParams.GetIntervalElapsed();
	Time_t	nContinuance = rParams.GetContinuance();
	Time_t	nInterval = rParams.GetInterval();
	BOOL	bRet = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(500 > nInterval)
	{
		nInterval = 2000;
	}

	if(nDeltaTime > nContinuance)
	{
		nDeltaTime = nContinuance;
	}

	nIntervalElapsed += nDeltaTime;
	nContinuance -= nDeltaTime;
	if(0 >= nContinuance)
	{
		nContinuance = 0;
		rParams.GetActor()->StopCharacterLogic();
	}

	rParams.SetContinuance(nContinuance);

	while(nIntervalElapsed >= nInterval)
	{
		nIntervalElapsed -= nInterval;
		bRet = pCallBack->OnEvent_ActivateEachTick(rParams);
		if(FALSE == bRet)
		{
			return FALSE;
		}
	}

	rParams.SetIntervalElapsed(nIntervalElapsed);

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ChannelActionLogic::OnEvent_Disturb(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		return pCallBack->OnEvent_DisturbForChanneling(rParams);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ChannelActionLogic::OnEvent_Interrupt(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		return pCallBack->OnEvent_Interrupt(rParams);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ChargeActionLogic::HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCallBack)
	{
		return FALSE;
	}

	if(FALSE == pCallBack->CanDoThisActionInThisStatus(rParams))
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Time_t	nContinuance = rParams.GetContinuance() - nDeltaTime;
	BOOL	bRet = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 >= nContinuance)
	{
		nContinuance = 0;
	}

	rParams.SetContinuance(nContinuance);
	if(0 == nContinuance)
	{
		rParams.GetActor()->StopCharacterLogic();
		pCallBack->OnEvent_ActivateOnce(rParams);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ChargeActionLogic::OnEvent_Disturb(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		if(TRUE == pCallBack->InterruptWhenDisturbed(rParams))
		{
			return FALSE;
		}

		return pCallBack->OnEvent_DisturbForCharging(rParams);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ChargeActionLogic::OnEvent_Interrupt(ActionParams_T &rParams) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ActionCallBackFunctor_T const *pCallBack = rParams.GetCallBackFunctor();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCallBack)
	{
		return pCallBack->OnEvent_Interrupt(rParams);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}
