/*$T MapServer/Server/Skill/SkillManager.h GC 1.140 10/10/07 10:07:53 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __ABILITYMANAGER_H__
#define __ABILITYMANAGER_H__

#include "TypeDefine.h"
#include "Define.h"

#define MAX_SKILL	MAX_CHAR_ABILITY_NUM

class	BaseSkill;
class	Connector;
struct _SkillExpTable;
struct SSkillPrescriptionTab;

class SkillManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	SkillManager();
	~	SkillManager();

public:
	void		Clear();
	BOOL		Init();

	BaseSkill	*GetAbility(SpellID_t aid);
	uchar GetMaxSkillNum(){	return(uchar) SKILL_CLASS_SIZE;}
	int32	GetUpperLimitExp(SpellID_t id, Player const *pPlayer) const;

	BOOL	InitSkill(const char *filename);
	BOOL	InitPrescriptionList(const char *filename);
	BOOL	InitSkillExpTable();

	_SkillExpTable *GetSkillExpTbl(uint32 index) const
	{
		KCheck(index >= 0 && index < EXP_TABLE_NUM);
		return m_pSkillExpTbl[index];
	}

	const SSkillPrescriptionTab *GetPrescriptionList()
	{
		return m_pPrescriptionList;
	}


public:
	enum { EXP_TABLE_NUM = 14, };

	enum EXP_TABLE
	{
		TABLE_INVALID			= -1,
		TABLE_ZHIYAO			= 0,
		TABLE_GONGYI,
		TABLE_ZHUZAO,
		TABLE_ASSISTANT,
	};

	enum SkillClass
	{
		SKILL_CLASS_INVALID		= -1,
		SKILL_CLASS_NOUSE		= 0,
		SKILL_CLASS_PHARMACY,
		SKILL_CLASS_ARTWORK,
		SKILL_CLASS_FOUNDRY,
		SKILL_CLASS_CAOYAO,
		SKILL_CLASS_YISHU,
		SKILL_CLASS_SMITHING,
		SKILL_CLASS_CRAFT,
		SKILL_CLASS_GEM,
		SKILL_CLASS_PRJ,
		SKILL_CLASS_MESH,
		SKILL_CLASS_GATHER_CAOYAO,
		SKILL_CLASS_GATHER_ORE,
		SKILL_CLASS_GATHER_INSECT,
		SKILL_CLASS_THICKICE,
		SKILL_CLASS_INSECTCULTURING,
		SKILL_CLASS_POISON,
		SKILL_CLASS_INCANTATION,
		SKILL_CLASS_ALCHEMY,
		SKILL_CLASS_THAUMATURGY,
		SKILL_CLASS_ENGINEERING,
		SKILL_CLASS_FIGHTGHOST,
		SKILL_CLASS_SEARCHTSTORE,
		SKILL_CLASS_TRADE,
		SKILL_CLASS_HAGGLE,
		SKILL_CLASS_EXCESSPROFIT,
		SKILL_CLASS_PROCESSING,
		SKILL_CLASS_PHARMACOLOGY,
		SKILL_CLASS_REGIMEN,
		SKILL_CLASS_BUDDHOLOGY,
		SKILL_CLASS_FIREMAKING,
		SKILL_CLASS_BEGSKILL,
		SKILL_CLASS_ICEMAKING,
		SKILL_CLASS_VENATIONFORMULA,
		SKILL_CLASS_INSECTENTICING,
		SKILL_CLASS_MENTALTELEPATHY,
		SKILL_CLASS_TAOISM,
		SKILL_CLASS_BODYBUILDING,
		SKILL_CLASS_SIZE,
	};

private:
	BOOL	InitSkillExpTable_i(uint32 j);
	BOOL	InitSkill_NewSkill_i(int32	nAbilityID, BaseSkill& rTempAbility);

	BaseSkill				*m_pSkill[MAX_SKILL];
	_SkillExpTable			*m_pSkillExpTbl[EXP_TABLE_NUM];
	SSkillPrescriptionTab	*m_pPrescriptionList;
	const static char	*m_VigorExpTablePath;
	const static char	*m_VigorExpTableName[EXP_TABLE_NUM];

};

extern SkillManager	*g_pSkillManager;

#endif
