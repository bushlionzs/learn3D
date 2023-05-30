/*$T MapServer/Server/Skill/Skill.h GC 1.140 10/10/07 10:07:53 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "StructDB.h"
#include "gameobject/Player.h"

#define MAX_PRESCRIPTION_STUFF	4

struct SDBC_PrescriptionData
{
	PrescriptionID_t	m_PrescriptionID;
	uint32			m_CompoundID;
	uchar			m_CompoundNum;
	SpellID_t		m_SkillID;
	int32			m_SkillLevel;
	uint32			m_Stuff_ID[MAX_PRESCRIPTION_STUFF];
	uchar			m_Stuff_Num[MAX_PRESCRIPTION_STUFF];
	int32			m_Attr_Vigor;
	int32			m_ColddownTime;
	uint32			m_ToolID;
	CooldownID_t		m_ColddownID;
	int32			m_ExpIncrement;
	int32			m_nOperaTime;
	int32			m_ScriptID;

	enum
	{
		Tab_PrescriptionID		= 0,
		Tab_CompoundID			= 2,
		Tab_CompoundNum			= 3,
		Tab_SkillID,
		Tab_AbilityLevel,
		Tab_Stuff_BEGIN,
		Tab_Stuff_END			= Tab_Stuff_BEGIN +MAX_PRESCRIPTION_STUFF *2 -1,
		Tab_Attr_VIGOR,
		Tab_ColddownTime,
		Tab_ToolID,
		Tab_ColddownID,
		Tab_ExpIncrement,
		Tab_OperaTime,
		Tab_SCRIPTID,
	};
};

typedef SDBC_PrescriptionData	_SKILL_PRESCRIPTION_DATA;

struct SSkillPrescriptionTab
{
	_SKILL_PRESCRIPTION_DATA	m_Table[MAX_SKILL_PRESCRIPTION_NUM];
	int32			m_Count;

	SSkillPrescriptionTab()
	{
		memset(m_Table, 0, sizeof(_SKILL_PRESCRIPTION_DATA) * MAX_SKILL_PRESCRIPTION_NUM);
		m_Count = 0;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	const _SKILL_PRESCRIPTION_DATA *Get_Prescription(PrescriptionID_t id) const
	{
		int32	idx;
		idx = (int32) id;
		KCheck(idx >= 0 && id < m_Count);
		return &m_Table[idx];
	}
};

struct _SkillExpTable
{
	enum ETableElement { ETE_LEVEL = 0, ETE_MONEY, ETE_EXP, ETE_UPPER_EXP, ETE_PLAYER_LEVEL, ETE_NEED_TITLE, ETE_ElementNum = 6 };

	enum { MAX_LEVEL_NUM = 20, };

	uchar m_Level[MAX_LEVEL_NUM];
	int32 m_CostMoney[MAX_LEVEL_NUM];
	int32 m_CostExp[MAX_LEVEL_NUM];
	int32 m_UpperLimmitExp[MAX_LEVEL_NUM];
	uchar m_PlayerLevel[MAX_LEVEL_NUM];
	int32 m_NeedTitle[MAX_LEVEL_NUM];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	int32 GetCostMoney(uint32 index) const
	{
		KCheck(index >= 0 && index < MAX_LEVEL_NUM);
		return m_CostMoney[index];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetCostExp(uint32 index) const
	{
		KCheck(index >= 0 && index < MAX_LEVEL_NUM);
		return m_CostExp[index];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUpperLimmitExp(uint32 index) const
	{
		KCheck(index >= 0 && index < MAX_LEVEL_NUM);
		return m_UpperLimmitExp[index];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetPlayerLevel(uint32 index) const
	{
		KCheck(index >= 0 && index < MAX_LEVEL_NUM);
		return m_PlayerLevel[index];
	}

	int32 GetNeedTitle(uint32 index) const
	{
		KCheck(index >= 0 && index < MAX_LEVEL_NUM);
		return m_NeedTitle[index];
	}
};

class	BaseSkill
{
public:
	BaseSkill();
	~BaseSkill(){};
	void	Clear();

	enum { EXPTABLE_NAME_LENGTH = 30, };

	enum
	{
		TEMPLATE_SKILL_INVALID		= -1,
		TEMPLATE_SKILL_ID			= 0,
		TEMPLATE_SKILL_LEVEL_DEMAND,
		TEMPLATE_SKILL_NAME,
		TEMPLATE_SKILL_LEVEL_LIMIT,
		TEMPLATE_SKILL_OPERATION_TIME,
		TEMPLATE_SKILL_OPERATION_TOOL,
		TEMPLATE_SKILL_PLATFORM_DISTANCE,
		TEMPLATE_SKILL_PLATFORM,
		TEMPLATE_SKILL_OPERATION_ACTION,
		TEMPLATE_SKILL_EXP_TABLE,
	};

public:
	uint32 GetOperationActionID(){return m_OperationActionID;}
	void SetOperationActionID(int32 id){m_OperationActionID = id;}
	char *GetExpTableName(void){return m_ExpTable;}
	void SetExpTableIndex(int32 index){m_ExpTableIndex = index;}
	SkillID_t GetSkillID(){	return m_SkillID;}
	void SetSkillID(int32 id){m_SkillID = id;}
	const char *GetSkillName() const{return m_pStrSkillName;}
	void SetSkillName(const char *name){m_pStrSkillName = name;}
	int32 GetLevelDemand(){	return m_LevelDemand;}
	void SetLevelDemand(int32 lvl){	m_LevelDemand = lvl;}
	int32 GetPlatformID(){return m_PlatformID;}
	void SetPlatformID(int32 id){m_PlatformID = id;}
	float GetPlatformDistance(){return m_PlatformDistance;}
	void SetPlatformDistance(float dis){m_PlatformDistance = dis;}
	int32 GetSkillLevelLimit(){	return m_iSkillLevelLimit;}
	void SetSkillLevelLimit(int32 lvl){	m_iSkillLevelLimit = lvl;}
	int32 GetOperationTime(){return m_OperationTime;}
	void SetOperationTime(int32 time){m_OperationTime = time;}
	uint32 GetOperationToolID(){return m_OperationToolID;}
	void SetOperationToolID(int32 id){m_OperationToolID = id;}
	int32 GetExpTableIndex(void) const{return m_ExpTableIndex;}
	void SetExpTable(_SkillExpTable *pExpTable){m_pExpTabel = pExpTable;}
	_SkillExpTable const *GetExpTable(void) const{return m_pExpTabel;}

public:
	virtual OPT_RESULT CanUseSkill(Player *pPlayer);
	virtual void	OnEvent_ProcInterrupt(Player *pPlayer);
	virtual OPT_RESULT OnEvent_ProcOver(Player *pPlayer){return OR_OK;}

protected:
	SkillID_t	m_SkillID;
	const char	*m_pStrSkillName;
	int32		m_LevelDemand;
	int32		m_iSkillLevelLimit;
	int32		m_OperationTime;
	uint32		m_OperationToolID;
	int32		m_PlatformID;
	float		m_PlatformDistance;
	uint32		m_OperationActionID;
	char		m_ExpTable[EXPTABLE_NAME_LENGTH];
	int32		m_ExpTableIndex;
	_SkillExpTable	*m_pExpTabel;

	virtual OPT_RESULT OnEvent_ProcSuccess(Player *pPlayer){return OR_OK;}
	virtual OPT_RESULT OnEvent_ProcFailure(Player *pPlayer){return OR_OK;}

};


#endif
