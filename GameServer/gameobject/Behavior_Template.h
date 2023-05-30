/*$T MapServer/Server/AI/Behavior_Template.h GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __AI_Template_H_
#define __AI_Template_H_

#include "TypeDefine.h"
#include "Behavior_ScriptFunction.h"

#define MAX_AIRECORDS_COUNT	10
#define MAX_AITEMPLATES_COUNT	1024

enum EAIEvent { AIE_OnBeSkill = 0, AIE_OnFlee, AIE_OnDie, AIE_OnGoHome, AIE_OnEnterCombat, AIE_OnDamage, AIEvent_Num, };

enum EBehavior_State
{
	AIS_Idle		= 0,
	AIS_Combat,
	AIS_Flee,
	AIS_Approach,
	AIS_GoHome,
	AIS_Dead,
	AIS_Patrol,
	AIS_Terror,
	Behavior_State_Num,
};
struct AIOperationMap
{
	const char		*funcname;
	PLAISFunc	Func;
};

struct BHVEventMap
{
	const char	*EventName;
	int32	EventID;
};

struct Behavior_StateMap
{
	const char	*StateName;
	int32	StateID;
};

struct AIEvent
{
	AIEvent()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_EventID = INVALID_ID;
	}

	int32	m_EventID;
};

struct AIOperation
{
	AIOperation()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_FunPtrOperation = NULL;
		m_aOperationParam[0] = INVALID_ID;
		m_aOperationParam[1] = INVALID_ID;
		m_aOperationParam[2] = INVALID_ID;
	}

	PLAISFunc	m_FunPtrOperation;
	int32		m_aOperationParam[3];
};

//AI 模板数据， 对应表格：monster_ai_template.tab
struct AIRecord
{
	AIRecord()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nID = INVALID_ID;
		m_nScriptID = INVALID_ID;
		m_nState = INVALID_ID;
		m_nHP = INVALID_ID;
		m_nRandom = INVALID_ID;
		m_nTimes = INVALID_ID;
		m_Event.Clear();
		m_CheckOperation.Clear();
		m_aAIOperation[0].Clear();
		m_aAIOperation[1].Clear();
		m_aAIOperation[2].Clear();
	}

	int32		m_nID;
	int32		m_nScriptID;
	int32		m_nState;
	AIEvent		m_Event;
	int32		m_nHP;
	int32		m_nRandom;
	int32		m_nTimes;
	AIOperation	m_CheckOperation;
	AIOperation	m_aAIOperation[3];
};

//一个Template 可以有多个Record
struct Behavior_Template
{
	Behavior_Template()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		int32	i;
		for(i = 0; i < MAX_AIRECORDS_COUNT; ++i)
		{
			m_aAIRecord[i].Clear();
		}

		m_nRecordCount = 0;
	}

	BOOL		AddRecord(const AIRecord &record);

	const AIRecord	&GetRecord(int32 idx) const;

	int32		m_nRecordCount;
	AIRecord	m_aAIRecord[MAX_AIRECORDS_COUNT];
};

class	Behavior_TemplateManager
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
	~Behavior_TemplateManager()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	static Behavior_TemplateManager &GetInstance()
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		static Behavior_TemplateManager	instance;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		return instance;
	}

	const Behavior_Template	&GetBehavior_Template(int32 id) const;

	void			LoadAllBehavior_Templates();
	const char		*GetStateNameByID(int32 id) const;
	const char		*GetEventNameByID(int32 id) const;
	const char		*GetOperatorNameByPtr(const PLAISFunc FuncPtr) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32		GetStateIDByName(const char *name);
	int32		GetEventIDByName(const char *name);
	PLAISFunc	GetOperatorByName(const char *name);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Behavior_TemplateManager()
	{
	} Behavior_Template	m_aBehavior_Template[MAX_AITEMPLATES_COUNT];
};
#endif
