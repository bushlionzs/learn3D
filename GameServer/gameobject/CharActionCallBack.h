/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	CharActionCallBack.h
file path:	F:\khan2\src\MapServer\Server\GameLogic
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	�����ص��� ˵�����Ƕ����¼�������
**********************************************************************************************/


#ifndef ACTIONCALLBACK_H
#define ACTIONCALLBACK_H
#include "TypeDefine.h"

class	Character;

class	ActionCallBackFunctor_T;

//������ز���
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
	//��������ʱ��
	Time_t				m_nContinuance;
	//����������ʱ����
	Time_t				m_nInterval;
	//���������Ѿ����ŵ�ʱ����
	Time_t				m_nIntervalElapsed;
	//��������
	Character			*m_pActor;
	//�����¼�������
	ActionCallBackFunctor_T const	*m_pCallBack;
};

////�����¼��������
class	ActionCallBackFunctor_T
{
public:

	ActionCallBackFunctor_T(void)
	{
	};

	~ActionCallBackFunctor_T(void)
	{
	};

	//û��ʹ�õ� ��֪��Ҫ��ɶ
	virtual BOOL IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const
	{
		return FALSE;
	};

	//û��ʹ�õ� ��֪��Ҫ��ɶ
	virtual BOOL IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const
	{
		return FALSE;
	};

	//��ǰ״̬�ܷ����˶���
	virtual BOOL CanDoThisActionInThisStatus(ActionParams_T &) const
	{
		return TRUE;
	}

	//�����
	virtual BOOL OnEvent_Interrupt(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//��Чһ�� ��������
	virtual BOOL OnEvent_ActivateOnce(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//һ��ʱ������Чһ�� ��������
	virtual BOOL OnEvent_ActivateEachTick(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//������ʱ �������Ƿ�ֹͣ����
	virtual BOOL InterruptWhenDisturbed(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//����ʱ ������
	virtual BOOL OnEvent_DisturbForCharging(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//����ʱ ������
	virtual BOOL OnEvent_DisturbForChanneling(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//ֹͣ��ǰ����
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

//�ű����͵Ķ����¼�������
class ActionCallBackFunctorForScript_T :
	public ActionCallBackFunctor_T
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	//û��ʹ�õ� ��֪��Ҫ��ɶ
	virtual BOOL	IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const;
	//û��ʹ�õ� ��֪��Ҫ��ɶ
	virtual BOOL	CanDoThisActionInThisStatus(ActionParams_T &) const;
	//�����
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
	//��Чһ�� ��������
	virtual BOOL	OnEvent_ActivateOnce(ActionParams_T &rParams) const;
	//һ��ʱ������Чһ�� ��������
	virtual BOOL	OnEvent_ActivateEachTick(ActionParams_T &rParams) const;

	//������ʱ �������Ƿ�ֹͣ����
	virtual BOOL InterruptWhenDisturbed(ActionParams_T &rParams) const
	{
		return TRUE;
	};
	//����ʱ ������
	virtual BOOL	OnEvent_DisturbForCharging(ActionParams_T &rParams) const;
	//����ʱ ������
	virtual BOOL	OnEvent_DisturbForChanneling(ActionParams_T &rParams) const;
	//ֹͣ��ǰ����
	virtual void	ResetForNextAction(ActionParams_T &rParams) const;
};

//�������͵Ķ����¼�������
class ActionCallBackFunctorForSkill_T :
	public ActionCallBackFunctor_T
{

public:
	//û��ʹ�õ� ��֪��Ҫ��ɶ
	virtual BOOL	IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const;
	//û��ʹ�õ� ��֪��Ҫ��ɶ
	virtual BOOL	CanDoThisActionInThisStatus(ActionParams_T &) const;
	//�����
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
	//��Чһ�� ��������
	virtual BOOL	OnEvent_ActivateOnce(ActionParams_T &rParams) const;
	//һ��ʱ������Чһ�� ��������
	virtual BOOL	OnEvent_ActivateEachTick(ActionParams_T &rParams) const;

	//������ʱ �������Ƿ�ֹͣ����
	virtual BOOL InterruptWhenDisturbed(ActionParams_T &rParams) const
	{
		return FALSE;
	};
	//����ʱ ������
	virtual BOOL	OnEvent_DisturbForCharging(ActionParams_T &rParams) const;
	//����ʱ ������
	virtual BOOL	OnEvent_DisturbForChanneling(ActionParams_T &rParams) const;
	//ֹͣ��ǰ����
	virtual void	ResetForNextAction(ActionParams_T &rParams) const;

protected:
	BOOL	IsCanInteruptChargOrChannel(ActionParams_T &rParams) const;

};

ActionCallBackFunctor_T const	&GetGlobalScriptCallBackFunctor(void);
ActionCallBackFunctor_T const	&GetGlobalSkillCallBackFunctor(void);
#endif
