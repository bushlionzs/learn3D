/*$T MapServer/Server/AI/Behavior_Template.cpp GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Behavior_Template.h"
#include "TAB.h"

//注册function
BHSFuncMap	g_BHVOperatorTable[] =
{
	REGISTERAISFUNC(BehaviorStateGetELevel)
	REGISTERAISFUNC(BehaviorStateGetESex)
	REGISTERAISFUNC(BehaviorStateGetEHP)
	REGISTERAISFUNC(BehaviorStateGetEMP)
	REGISTERAISFUNC(BehaviorStateGetEProfession)
	REGISTERAISFUNC(BehaviorStateGetLevel)
	REGISTERAISFUNC(BehaviorStateGetEPK)
	REGISTERAISFUNC(BehaviorStateToFlee)
	REGISTERAISFUNC(BehaviorStateToSkill)
	REGISTERAISFUNC(BehaviorStateToSummon)
	REGISTERAISFUNC(BehaviorStateToSpeak)
	REGISTERAISFUNC(BehaviorStateSetPatrolID)
	REGISTERAISFUNC(BehaviorStateStartPatrol)
	REGISTERAISFUNC(BehaviorStateChangeTemplate)
	REGISTERAISFUNC(BehaviorStateHaveBuff)
	REGISTERAISFUNC(BehaviorStateHaveBuffOfLogic)
	REGISTERAISFUNC(BehaviorStateRandomAttack)
	REGISTERAISFUNC(BehaviorStateUseSkillToSpecialProfession)
	REGISTERAISFUNC(BehaviorStateGetHP)
	REGISTERAISFUNC(BehaviorStateGetMP)
};

//注册AI事件对应 function, 如AIE_OnBeSkill 事件时会调用 OnBeSkill
BHVEventMap	g_BHVEventTable[] =
{
	"OnBeSkill",
	AIE_OnBeSkill,
	"OnFlee",
	AIE_OnFlee,
	"OnDie",
	AIE_OnDie,
	"OnGoHome",
	AIE_OnGoHome,
	"OnEnterCombat",
	AIE_OnEnterCombat,
	"OnDamage",
	AIE_OnDamage,
};

//注册AI状态的名称和id对应
Behavior_StateMap	g_Behavior_StateTable[] =
{
	"Idle",
	AIS_Idle,
	"Approach",
	AIS_Approach,
	"Flee",
	AIS_Flee,
	"Combat",
	AIS_Combat,
	"Patrol",
	AIS_Patrol,
	"GoHome",
	AIS_GoHome,
	"Dead",
	AIS_Dead,
	"Terror",
	AIS_Terror,
};

/*
 =======================================================================================================================
 --给一个template 加 record, 一个template可以有多个record
 =======================================================================================================================
 */

BOOL Behavior_Template::AddRecord(const AIRecord &record)
{
	if(!(m_nRecordCount >= 0 && m_nRecordCount < MAX_AIRECORDS_COUNT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szMsg[256] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s(szMsg, 256, "m_nRecordCount=%d,record.m_nID=%d", m_nRecordCount, record.m_nID);
		KCheckEx(m_nRecordCount >= 0 && m_nRecordCount < MAX_AIRECORDS_COUNT, szMsg);
	}

	m_aAIRecord[m_nRecordCount++] = record;
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const AIRecord &Behavior_Template::GetRecord(int32 idx) const
{
	if(!(idx >= 0 && idx < MAX_AIRECORDS_COUNT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szMsg[256] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s(szMsg, 256, "idx=%d", idx);
		KCheckEx(idx >= 0 && idx < MAX_AIRECORDS_COUNT, szMsg);
	}

	return m_aAIRecord[idx];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const Behavior_Template &Behavior_TemplateManager::GetBehavior_Template(int32 id) const
{
	if(!(id >= 0 && id < MAX_AITEMPLATES_COUNT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szMsg[256] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s(szMsg, 256, "Behavior_Template=%d", id);
		KCheckEx(id >= 0 && id < MAX_AITEMPLATES_COUNT, szMsg);
	}

	return m_aBehavior_Template[id];
}

/*
 =======================================================================================================================
 --加载./Config/monster_ai_template.tab
 =======================================================================================================================
 */
void Behavior_TemplateManager::LoadAllBehavior_Templates()
{
	/*~~~~~~~*/
	__GUARD__ enum
	{
		record_id,
		template_id,
		script_id,
		state_name,
		event_name,
		random,
		hp,
		checkOperator,
		check_param0,
		check_param1,
		check_param2,
		times,
		operator0,
		opt0_param0,
		opt0_param1,
		opt0_param2,
		operator1,
		opt1_param0,
		opt1_param1,
		opt1_param2,
		operator2,
		opt2_param0,
		opt2_param1,
		opt2_param2,
	};
	/*~~~~~~~*/

	int32 i;
	for(i = 0; i < MAX_AITEMPLATES_COUNT; ++i)
	{
		m_aBehavior_Template[i].Clear();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TAB::TABFile ThirdFile(0);
	bool	ret = ThirdFile.OpenFromTXT("./Config/monster_ai_template.tab");
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableColumn == 24);
	KCheck(iTableCount > 0);

	for(i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nTemplateID = ThirdFile.Search_Posistion(i, template_id)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(nTemplateID >= 0 && nTemplateID < MAX_AITEMPLATES_COUNT);

		/*~~~~~~~~~~~~~~~~~~~*/
		AIRecord	record;
		/*~~~~~~~~~~~~~~~~~~~*/

		record.m_nID = ThirdFile.Search_Posistion(i, record_id)->iValue;
		record.m_nScriptID = ThirdFile.Search_Posistion(i, script_id)->iValue;
		record.m_nState = GetStateIDByName(ThirdFile.Search_Posistion(i, state_name)->pString);
		record.m_Event.m_EventID = GetEventIDByName(ThirdFile.Search_Posistion(i, event_name)->pString);
		if
		(
			//如果 state, event 同时有效、无效
			!(	//非： state==-1 并且 event有效
				(
					record.m_nState == INVALID_ID
				&&	(
						record.m_Event.m_EventID >= AIE_OnBeSkill
					&&	record.m_Event.m_EventID < AIEvent_Num
					)
				)
			||	( //非： state 有效 并且 event==-1
						record.m_Event.m_EventID == INVALID_ID
					&&	(record.m_nState >= AIS_Idle && record.m_nState < Behavior_State_Num)
					)
			)
		)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~*/
			char	szMsg[256] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~~*/

			tsnprintf_s(szMsg, 256, "record.m_nID=%d...表格数据错误, 状态和事件是互斥的", record.m_nID);
			KCheckEx(0, szMsg);
		}

		record.m_nHP = ThirdFile.Search_Posistion(i, hp)->iValue;
		KCheck(-1 == record.m_nHP || (record.m_nHP > 0 && record.m_nHP <= 100));

		record.m_nRandom = ThirdFile.Search_Posistion(i, random)->iValue;
		KCheck(-1 == record.m_nRandom || (record.m_nRandom > 0 && record.m_nRandom <= 100));

		record.m_CheckOperation.m_FunPtrOperation = GetOperatorByName(ThirdFile.Search_Posistion(i, checkOperator)->pString);
		record.m_CheckOperation.m_aOperationParam[0] = ThirdFile.Search_Posistion(i, check_param0)->iValue;
		record.m_CheckOperation.m_aOperationParam[1] = ThirdFile.Search_Posistion(i, check_param1)->iValue;
		record.m_CheckOperation.m_aOperationParam[2] = ThirdFile.Search_Posistion(i, check_param2)->iValue;

		record.m_nTimes = ThirdFile.Search_Posistion(i, times)->iValue;

		record.m_aAIOperation[0].m_FunPtrOperation = GetOperatorByName(ThirdFile.Search_Posistion(i, operator0)->pString);
		record.m_aAIOperation[0].m_aOperationParam[0] = ThirdFile.Search_Posistion(i, opt0_param0)->iValue;
		record.m_aAIOperation[0].m_aOperationParam[1] = ThirdFile.Search_Posistion(i, opt0_param1)->iValue;
		record.m_aAIOperation[0].m_aOperationParam[2] = ThirdFile.Search_Posistion(i, opt0_param2)->iValue;
		if(BehaviorStateToSummon == record.m_aAIOperation[0].m_FunPtrOperation) KCheck(AIS_Combat != record.m_nState);

		record.m_aAIOperation[1].m_FunPtrOperation = GetOperatorByName(ThirdFile.Search_Posistion(i, operator1)->pString);
		record.m_aAIOperation[1].m_aOperationParam[0] = ThirdFile.Search_Posistion(i, opt1_param0)->iValue;
		record.m_aAIOperation[1].m_aOperationParam[1] = ThirdFile.Search_Posistion(i, opt1_param1)->iValue;
		record.m_aAIOperation[1].m_aOperationParam[2] = ThirdFile.Search_Posistion(i, opt1_param2)->iValue;
		if(BehaviorStateToSummon == record.m_aAIOperation[1].m_FunPtrOperation) KCheck(AIS_Combat != record.m_nState);

		record.m_aAIOperation[2].m_FunPtrOperation = GetOperatorByName(ThirdFile.Search_Posistion(i, operator2)->pString);
		record.m_aAIOperation[2].m_aOperationParam[0] = ThirdFile.Search_Posistion(i, opt2_param0)->iValue;
		record.m_aAIOperation[2].m_aOperationParam[1] = ThirdFile.Search_Posistion(i, opt2_param1)->iValue;
		record.m_aAIOperation[2].m_aOperationParam[2] = ThirdFile.Search_Posistion(i, opt2_param2)->iValue;
		if(BehaviorStateToSummon == record.m_aAIOperation[2].m_FunPtrOperation) KCheck(AIS_Combat != record.m_nState);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Template	&aiTemplate = const_cast<Behavior_Template &>
			(Behavior_TemplateManager::GetInstance().GetBehavior_Template(nTemplateID));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		aiTemplate.AddRecord(record);
	}


	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Behavior_TemplateManager::GetStateIDByName(const char *name)
{
	for(int32 i = 0; i < sizeof(g_Behavior_StateTable) / sizeof(Behavior_StateMap); ++i)
	{
		if(strcmp(name, g_Behavior_StateTable[i].StateName) == 0)
		{
			return g_Behavior_StateTable[i].StateID;
		}
	}

	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Behavior_TemplateManager::GetEventIDByName(const char *name)
{
	for(int32 i = 0; i < sizeof(g_BHVEventTable) / sizeof(BHVEventMap); ++i)
	{
		if(strcmp(name, g_BHVEventTable[i].EventName) == 0)
		{
			return g_BHVEventTable[i].EventID;
		}
	}

	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PLAISFunc Behavior_TemplateManager::GetOperatorByName(const char *name)
{
	for(int32 i = 0; i < sizeof(g_BHVOperatorTable) / sizeof(BHSFuncMap); ++i)
	{
		if(strcmp(name, g_BHVOperatorTable[i].funcname) == 0)
		{
			return g_BHVOperatorTable[i].Func;
		}
	}

	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *Behavior_TemplateManager::GetStateNameByID(int32 id) const
{
	for(int32 i = 0; i < sizeof(g_Behavior_StateTable) / sizeof(Behavior_StateMap); ++i)
	{
		if(id == g_Behavior_StateTable[i].StateID)
		{
			return g_Behavior_StateTable[i].StateName;
		}
	}

	return "NULL";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *Behavior_TemplateManager::GetEventNameByID(int32 id) const
{
	for(int32 i = 0; i < sizeof(g_BHVEventTable) / sizeof(BHVEventMap); ++i)
	{
		if(id == g_BHVEventTable[i].EventID)
		{
			return g_BHVEventTable[i].EventName;
		}
	}

	return "NULL";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *Behavior_TemplateManager::GetOperatorNameByPtr(const PLAISFunc FuncPtr) const
{
	for(int32 i = 0; i < sizeof(g_BHVOperatorTable) / sizeof(BHSFuncMap); ++i)
	{
		if(FuncPtr == g_BHVOperatorTable[i].Func)
		{
			return g_BHVOperatorTable[i].funcname;
		}
	}

	return "NULL";
}
