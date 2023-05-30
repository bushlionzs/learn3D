/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	CharActionDelegator.h
			file path:	F:\khan2\src\MapServer\Server\GameLogic
			file base:
			file ext:	h
author:		
modified:	wujianping
purpose:	动作接口类 也就是动作封装类 其他模块对动作相关操作只与本类打交道
**********************************************************************************************/


#ifndef ACTIONDELEGATOR_H
#define ACTIONDELEGATOR_H
#include "TypeDefine.h"
#include "Define.h"
#include "Enum.h"

#include "CharActionCallBack.h"

class	Character;

class	ActionDelegator
{
	friend class	ActionCallBackFunctorForScript_T;
	friend class	ActionCallBackFunctorForSkill_T;
	friend class	ActionCallBackFunctor_T;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ActionDelegator(void)
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~ActionDelegator(void)
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//nobody use it add by wujianping
	BOOL	IsPerformingTheSpecificSkill(Character &rActor, SpellID_t nSkillID) const;
	//nobody use it add by wujianping
	BOOL	IsPerformingTheSpecificScript(Character &rActor, ScriptID_t nScriptID) const;
	//当前是否在引导 add by wujianping
	BOOL	IsChanneling(Character &rActor) const;
	//当前是否在聚气 add by wujianping
	BOOL	IsCharging(Character &rActor) const;
	//注册一个执行技能的聚气动作 add by wujianping
	BOOL	Register_ChargeActionForSpell(Character &rActor, ActionID_t nAction, Time_t nContinuance) const;
	//注册一个执行脚本的聚气动作 add by wujianping
	BOOL	Register_ChargeActionForScript(Character &rActor, ActionID_t nAction, Time_t nContinuance) const;
	//注册一个执行技能的引导动作 add by wujianping
	BOOL	Register_ChannelActionForSpell
		(
			Character	&rActor,
			ActionID_t	nAction,
			Time_t		nContinuance,
			Time_t		nInterval
		) const;
	//注册一个执行脚本的引导动作 add by wujianping
	BOOL	Register_ChannelActionForScript
		(
			Character	&rActor,
			ActionID_t	nAction,
			Time_t		nContinuance,
			Time_t		nInterval
		) const;
	//注册一个执行技能的瞬发动作 add by wujianping
	BOOL	Register_InstantActionForSpell(Character &rActor, ActionID_t nAction, Time_t nActionTime) const;
	//注册一个执行脚本的瞬发动作 add by wujianping
	BOOL	Register_InstantActionForScript(Character &rActor, ActionID_t nAction, Time_t nActionTime) const;
	//注册一个表情动作 add by wujianping
	BOOL	Register_EmoteAction(Character &rActor, ActionID_t nAction) const;
	//打扰当前动作 也就是被攻击了 动作的执行时间会有变化 add by wujianping
	BOOL	DisturbCurrentAction(Character &rActor) const;
	//动作的心跳 add by wujianping
	BOOL	OnEvent_HeartBeat(Character &rActor, Time_t nDeltaTime) const;
	//能否执行下一个动作 add by wujianping
	BOOL	CanDoNextAction(Character &rActor) const;
	//打断当前动作 add by wujianping
	void	InterruptCurrentAction(Character &rActor) const;
	//结束当前动作 add by wujianping
	void	CurrentActionFinished(Character &rActor) const;
	//停止引导动作 add by wujianping
	void	StopChanneling(Character &rActor);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//有关动作的广播和动作时间的同步 add by wujianping
	void	Broadcast_UnitStartChargeAction(Character &rActor, ActionID_t nAction, Time_t nContinuance) const;
	void	Broadcast_UnitStartChannelAction(Character &rActor, ActionID_t nAction, Time_t nContinuance) const;
	void	Broadcast_UnitStartInstantAction(Character &rActor, ActionID_t nAction, Time_t nActionTime) const;
	void	Broadcast_UnitChargeTimeChanged(Character &rActor, Time_t nDeltaTime) const;
	void	Broadcast_UnitChannelTimeChanged(Character &rActor, Time_t nDeltaTime) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	//清空当前动作 当动作结束的时候会被调用 add by wujianping
	void	ResetForNextAction(Character &rActor) const;
};
ActionDelegator const &GetGlobalActionDelegator(void);
#endif
