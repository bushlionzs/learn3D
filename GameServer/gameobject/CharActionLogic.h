/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	CharActionLogic.h
file path:	F:\khan2\src\MapServer\Server\GameLogic
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	�����߼������� һ����3�ֶ���
			1��������
			2��������
			3˲������
**********************************************************************************************/


#ifndef VIRTUALACTION_H
#define VIRTUALACTION_H
#include "TypeDefine.h"
#include "Define.h"
#include "Enum.h"
#include "CharActionCallBack.h"
//ACTION_CHARGE ���� ACTION_CHANNEL ���� ACTION_INSTANT ˲�� add by wujianping
enum { ACTION_INVALID = -1, ACTION_CHARGE = 0, ACTION_CHANNEL = 1, ACTION_INSTANT = 2, };
//��������
class ActionLogic
{
public:
	enum { ID = ACTION_INVALID, };

	ActionLogic(void)
	{
	};

	~ActionLogic(void)
	{
	};

	virtual int32 GetLogicID(void) const
	{
		return ID;
	}

	//nobody use it add by wujianping
	virtual BOOL	IsPerformingSpecificSkill(ActionParams_T &rParams, SpellID_t nID) const;
	//nobody use it add by wujianping
	virtual BOOL	IsPerformingSpecificScript(ActionParams_T &rParams, ScriptID_t nID) const;

	//��������
	virtual BOOL HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const
	{
		return FALSE;
	};

	//����������
	virtual BOOL OnEvent_Disturb(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//���������
	virtual BOOL OnEvent_Interrupt(ActionParams_T &rParams) const
	{
		return FALSE;
	};
};

//��������
class ChannelActionLogic :
	public ActionLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = ACTION_CHANNEL, };

	ChannelActionLogic(void)
	{
	};

	~ChannelActionLogic(void)
	{
	};

	virtual int32 GetLogicID(void) const
	{
		return ID;
	}

	//��������
	virtual BOOL	HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const;
	//����������
	virtual BOOL	OnEvent_Disturb(ActionParams_T &rParams) const;
	//���������
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
};

//��������
class ChargeActionLogic :
	public ActionLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = ACTION_CHARGE, };

	ChargeActionLogic(void)
	{
	};

	~ChargeActionLogic(void)
	{
	};

	virtual int32 GetLogicID(void) const
	{
		return ID;
	}

	//��������
	virtual BOOL	HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const;
	//����������
	virtual BOOL	OnEvent_Disturb(ActionParams_T &rParams) const;
	//���������
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
};

//˲������
class InstantActionLogic :
	public ActionLogic
{

public:
	enum { ID = ACTION_INSTANT, };

	InstantActionLogic(void)
	{
	};

	~InstantActionLogic(void)
	{
	};

	virtual int32 GetLogicID(void) const
	{
		return ID;
	}
};

ActionLogic const	&GetGlobalChargeActionLogic(void);
ActionLogic const	&GetGlobalChannelActionLogic(void);
ActionLogic const	&GetGlobalInstantActionLogic(void);
#endif
