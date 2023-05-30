/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	CharActionCallBack.h
file path:	F:\khan2\src\MapServer\Server\GameLogic
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	动作回调类 说白了是动作事件处理类
**********************************************************************************************/


#ifndef ACTIONCALLBACK_H
#define ACTIONCALLBACK_H
#include "TypeDefine.h"

class	Character;

class	ActionCallBackFunctor_T;

//动作相关参数
class	ActionParams_T
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ActionParams_T(void) :
	m_nContinuance(0),
	m_nInterval(0),
	m_nIntervalElapsed(0),
	m_pActor(NULL),
	m_pCallBack(NULL)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~ActionParams_T(void)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ActionParams_T(ActionParams_T const &rhs) :
	m_nContinuance(rhs.m_nContinuance),
	m_nInterval(rhs.m_nInterval),
	m_nIntervalElapsed(rhs.m_nIntervalElapsed),
	m_pActor(rhs.m_pActor),
	m_pCallBack(rhs.m_pCallBack)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ActionParams_T &operator=(ActionParams_T const &rhs)
	{
		m_nContinuance = rhs.GetContinuance();
		m_nInterval = rhs.GetInterval();
		m_nIntervalElapsed = rhs.GetIntervalElapsed();
		m_pActor = rhs.GetActor();
		m_pCallBack = rhs.GetCallBackFunctor();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_nContinuance = 0;
		m_nInterval = 0;
		m_nIntervalElapsed = 0;
		m_pActor = NULL;
		m_pCallBack = NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Time_t GetContinuance(void) const
	{
		return m_nContinuance;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetContinuance(Time_t nTime)
	{
		m_nContinuance = nTime;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Time_t GetInterval(void) const
	{
		return m_nInterval;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetInterval(Time_t nTime)
	{
		m_nInterval = nTime;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Time_t GetIntervalElapsed(void) const
	{
		return m_nIntervalElapsed;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetIntervalElapsed(Time_t nTime)
	{
		m_nIntervalElapsed = nTime;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Character *GetActor(void) const
	{
		return m_pActor;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetActor(Character *pActor)
	{
		m_pActor = pActor;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ActionCallBackFunctor_T const *GetCallBackFunctor(void) const
	{
		return m_pCallBack;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCallBackFunctor(ActionCallBackFunctor_T const &rCallBack)
	{
		m_pCallBack = &rCallBack;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	//动作持续时间
	Time_t				m_nContinuance;
	//引导动作的时间间隔
	Time_t				m_nInterval;
	//引导动作已经流逝的时间间隔
	Time_t				m_nIntervalElapsed;
	//做动作者
	Character			*m_pActor;
	//动作事件处理类
	ActionCallBackFunctor_T const	*m_pCallBack;
};

////动作事件处理基类
class	ActionCallBackFunctor_T
{
public:

	ActionCallBackFunctor_T(void)
	{
	};

	~ActionCallBackFunctor_T(void)
	{
	};

	//没有使用到 不知道要干啥
	virtual BOOL IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const
	{
		return FALSE;
	};

	//没有使用到 不知道要干啥
	virtual BOOL IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const
	{
		return FALSE;
	};

	//当前状态能否做此动作
	virtual BOOL CanDoThisActionInThisStatus(ActionParams_T &) const
	{
		return TRUE;
	}

	//被打断
	virtual BOOL OnEvent_Interrupt(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//生效一次 聚气动作
	virtual BOOL OnEvent_ActivateOnce(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//一定时间间隔生效一次 引导动作
	virtual BOOL OnEvent_ActivateEachTick(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//当聚气时 被打扰是否停止动作
	virtual BOOL InterruptWhenDisturbed(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//聚气时 被打扰
	virtual BOOL OnEvent_DisturbForCharging(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//引导时 被打扰
	virtual BOOL OnEvent_DisturbForChanneling(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//停止当前动作
	virtual void ResetForNextAction(ActionParams_T &rParams) const
	{
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

//脚本类型的动作事件处理类
class ActionCallBackFunctorForScript_T :
	public ActionCallBackFunctor_T
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//没有使用到 不知道要干啥
	virtual BOOL	IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const;
	//没有使用到 不知道要干啥
	virtual BOOL	CanDoThisActionInThisStatus(ActionParams_T &) const;
	//被打断
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
	//生效一次 聚气动作
	virtual BOOL	OnEvent_ActivateOnce(ActionParams_T &rParams) const;
	//一定时间间隔生效一次 引导动作
	virtual BOOL	OnEvent_ActivateEachTick(ActionParams_T &rParams) const;

	//当聚气时 被打扰是否停止动作
	virtual BOOL InterruptWhenDisturbed(ActionParams_T &rParams) const
	{
		return TRUE;
	};
	//聚气时 被打扰
	virtual BOOL	OnEvent_DisturbForCharging(ActionParams_T &rParams) const;
	//引导时 被打扰
	virtual BOOL	OnEvent_DisturbForChanneling(ActionParams_T &rParams) const;
	//停止当前动作
	virtual void	ResetForNextAction(ActionParams_T &rParams) const;
};

//技能类型的动作事件处理类
class ActionCallBackFunctorForSkill_T :
	public ActionCallBackFunctor_T
{

public:
	//没有使用到 不知道要干啥
	virtual BOOL	IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const;
	//没有使用到 不知道要干啥
	virtual BOOL	CanDoThisActionInThisStatus(ActionParams_T &) const;
	//被打断
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
	//生效一次 聚气动作
	virtual BOOL	OnEvent_ActivateOnce(ActionParams_T &rParams) const;
	//一定时间间隔生效一次 引导动作
	virtual BOOL	OnEvent_ActivateEachTick(ActionParams_T &rParams) const;

	//当聚气时 被打扰是否停止动作
	virtual BOOL InterruptWhenDisturbed(ActionParams_T &rParams) const
	{
		return FALSE;
	};
	//聚气时 被打扰
	virtual BOOL	OnEvent_DisturbForCharging(ActionParams_T &rParams) const;
	//引导时 被打扰
	virtual BOOL	OnEvent_DisturbForChanneling(ActionParams_T &rParams) const;
	//停止当前动作
	virtual void	ResetForNextAction(ActionParams_T &rParams) const;

protected:
	BOOL	IsCanInteruptChargOrChannel(ActionParams_T &rParams) const;

};

ActionCallBackFunctor_T const	&GetGlobalScriptCallBackFunctor(void);
ActionCallBackFunctor_T const	&GetGlobalSkillCallBackFunctor(void);
#endif
