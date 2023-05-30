/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	CharActionDelegator.h
			file path:	F:\khan2\src\MapServer\Server\GameLogic
			file base:
			file ext:	h
author:		
modified:	wujianping
purpose:	�����ӿ��� Ҳ���Ƕ�����װ�� ����ģ��Զ�����ز���ֻ�뱾��򽻵�
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
	//��ǰ�Ƿ������� add by wujianping
	BOOL	IsChanneling(Character &rActor) const;
	//��ǰ�Ƿ��ھ��� add by wujianping
	BOOL	IsCharging(Character &rActor) const;
	//ע��һ��ִ�м��ܵľ������� add by wujianping
	BOOL	Register_ChargeActionForSpell(Character &rActor, ActionID_t nAction, Time_t nContinuance) const;
	//ע��һ��ִ�нű��ľ������� add by wujianping
	BOOL	Register_ChargeActionForScript(Character &rActor, ActionID_t nAction, Time_t nContinuance) const;
	//ע��һ��ִ�м��ܵ��������� add by wujianping
	BOOL	Register_ChannelActionForSpell
		(
			Character	&rActor,
			ActionID_t	nAction,
			Time_t		nContinuance,
			Time_t		nInterval
		) const;
	//ע��һ��ִ�нű����������� add by wujianping
	BOOL	Register_ChannelActionForScript
		(
			Character	&rActor,
			ActionID_t	nAction,
			Time_t		nContinuance,
			Time_t		nInterval
		) const;
	//ע��һ��ִ�м��ܵ�˲������ add by wujianping
	BOOL	Register_InstantActionForSpell(Character &rActor, ActionID_t nAction, Time_t nActionTime) const;
	//ע��һ��ִ�нű���˲������ add by wujianping
	BOOL	Register_InstantActionForScript(Character &rActor, ActionID_t nAction, Time_t nActionTime) const;
	//ע��һ�����鶯�� add by wujianping
	BOOL	Register_EmoteAction(Character &rActor, ActionID_t nAction) const;
	//���ŵ�ǰ���� Ҳ���Ǳ������� ������ִ��ʱ����б仯 add by wujianping
	BOOL	DisturbCurrentAction(Character &rActor) const;
	//���������� add by wujianping
	BOOL	OnEvent_HeartBeat(Character &rActor, Time_t nDeltaTime) const;
	//�ܷ�ִ����һ������ add by wujianping
	BOOL	CanDoNextAction(Character &rActor) const;
	//��ϵ�ǰ���� add by wujianping
	void	InterruptCurrentAction(Character &rActor) const;
	//������ǰ���� add by wujianping
	void	CurrentActionFinished(Character &rActor) const;
	//ֹͣ�������� add by wujianping
	void	StopChanneling(Character &rActor);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	//�йض����Ĺ㲥�Ͷ���ʱ���ͬ�� add by wujianping
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
	//��յ�ǰ���� ������������ʱ��ᱻ���� add by wujianping
	void	ResetForNextAction(Character &rActor) const;
};
ActionDelegator const &GetGlobalActionDelegator(void);
#endif
