/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	CharActionLogic.h
file path:	F:\khan2\src\MapServer\Server\GameLogic
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	动作逻辑处理类 一共有3种动作
			1聚气动作
			2引导动作
			3瞬发动作
**********************************************************************************************/


#ifndef VIRTUALACTION_H
#define VIRTUALACTION_H
#include "TypeDefine.h"
#include "Define.h"
#include "Enum.h"
#include "CharActionCallBack.h"
//ACTION_CHARGE 聚气 ACTION_CHANNEL 引导 ACTION_INSTANT 瞬发 add by wujianping
enum { ACTION_INVALID = -1, ACTION_CHARGE = 0, ACTION_CHANNEL = 1, ACTION_INSTANT = 2, };
//动作基类
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

	//动作心跳
	virtual BOOL HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const
	{
		return FALSE;
	};

	//动作被打扰
	virtual BOOL OnEvent_Disturb(ActionParams_T &rParams) const
	{
		return FALSE;
	};

	//动作被打断
	virtual BOOL OnEvent_Interrupt(ActionParams_T &rParams) const
	{
		return FALSE;
	};
};

//引导动作
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

	//动作心跳
	virtual BOOL	HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const;
	//动作被打扰
	virtual BOOL	OnEvent_Disturb(ActionParams_T &rParams) const;
	//动作被打断
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
};

//聚气动作
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

	//动作心跳
	virtual BOOL	HeartBeat(ActionParams_T &rParams, Time_t nDeltaTime) const;
	//动作被打扰
	virtual BOOL	OnEvent_Disturb(ActionParams_T &rParams) const;
	//动作被打断
	virtual BOOL	OnEvent_Interrupt(ActionParams_T &rParams) const;
};

//瞬发动作
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
