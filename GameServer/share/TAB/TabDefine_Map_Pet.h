#ifndef __TAB_DEFINE_MAP_PET_H__
#define __TAB_DEFINE_MAP_PET_H__

#include "TypeDefine.h"
#include "StructDB.h"
#include "StructPet.h"
#include "TabStruct.h"


// 坐骑表
class TableInit_Map_Pet
{
public:
	TableInit_Map_Pet();
	~TableInit_Map_Pet();

	BOOL	Init();

private:
	// 加载坐骑属性，表里只保存了一项
	void	LoadPetAttrTable();
	// 加载坐骑升级表
	void	LoadPetLevelUpTable();
	// 加载坐骑驯化所要钱
	void	LoadPetDomesticationMoney();
	// 加载坐骑技能分布表，表里只保存了一项
	void	LoadPetSkillDistributeTable();
	// 加载坐骑技能索引表
	void	LoadPetSkillIndexTable();
	// 加载坐骑学习技能表
	void	LoadPetStudySkillTable();
	// 加载坐骑观察技能表
	void	LoadPetApperceiveSkillTable();
	// 加载坐骑ai表
	void	LoadPetAIStrategyTable();
	// 加载坐骑基础表
	void	LoadHorseAttrTable();
	// 加载坐骑合成表
	void	LoadHorseMixTable();
	// 加载坐骑合成主动技能几率表
	void	LoadHorseMixSpellTable();
	// 加载坐骑技能表
	void	LoadHorseRealTable();
	// 加载坐骑道具表
	void	LoadHorseItemTable();
	// 加载坐骑掉落内容表
	void	LoadHorseDropTable();
	// 加载坐骑资质表
	void	LoadHorsePerLimitTable();


private:
	void	ReadHorseSkillSlot
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			_HORSE_SKILL_SLOT	&oSlot
		);
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _PET_PROPERTY_TBL
{
	PET_PROPERTY	m_TableExt[MAXTYPE_NUMBER];
	uint32		m_Count;
	uint32		m_MaxType;

	_PET_PROPERTY_TBL()
	{
		memset(m_TableExt, 0, sizeof(PET_PROPERTY) * MAXTYPE_NUMBER);
		m_Count = 0;
	};

	PET_PROPERTY *GetAttr(uint32 PetType)
	{
		if(PetType <= m_MaxType) return &m_TableExt[PetType];
		return NULL;
	}

	int32 Count()
	{
		return m_Count;
	};
};
extern _PET_PROPERTY_TBL	g_HorsePropertyTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define PET_LEVEL_NUM	(256)
struct SHorseLevelupTab
{
	int32	m_Table[PET_LEVEL_NUM];

	SHorseLevelupTab()
	{
		memset(m_Table, INVALID_ID, PET_LEVEL_NUM);
	}

	int32 GetExp(int32 nLevel)
	{
		KCheck(nLevel <= PET_LEVEL_NUM);
		return m_Table[nLevel];
	}

	int32	m_iCount;
};
extern SHorseLevelupTab g_HorseLevelUpTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SHorseDomesticationMoneyTab
{
	float	m_Table[PET_LEVEL_NUM];

	SHorseDomesticationMoneyTab()
	{
		memset(m_Table, 0, PET_LEVEL_NUM);
	}

	float GetDomesticationMoney(int32 nLevel)
	{
		KCheck(nLevel <= PET_LEVEL_NUM);
		return m_Table[nLevel];
	}
};
extern SHorseDomesticationMoneyTab	g_HorseDomesticationMoneyTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define PET_MAX_NUM	(1024)
struct SHorseSkillDistrTab
{
	struct PET_SKILL_MAP
	{
		int32	m_nSkillIndex;
		int32	m_nSkillRange;

		PET_SKILL_MAP()
		{
			m_nSkillIndex = -1;
			m_nSkillRange = 0;
		}
	};

	PET_SKILL_MAP	m_Table[PET_MAX_SKILL_COUNT - 1];
	int32		m_PetID;
};
extern SHorseSkillDistrTab	g_HorseSpellDistrTab[PET_MAX_NUM];


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define PET_SKILL_NUM	(512)
struct SHorseSkillIndexTab
{
	int32	m_nIndex;
	int32	m_nSkillID;
};
extern SHorseSkillIndexTab	g_HorseSpellIndexTab[PET_SKILL_NUM];


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SHorseStudySkill
{
	int32	m_nID;
	int32	m_nMaxSpaceCount;
	int32	m_nSpaceCount;
	int32	m_nNewPercent;
};

#define GEN_HORSE_STUDYSPELL_ID(x, y)	(x * 10 + y)
#define PET_STUDYSKILLRATE_NUM		(56)
struct SHorseStudySkillTab
{
	SHorseStudySkill m_aStudySkill[PET_STUDYSKILLRATE_NUM];

	const SHorseStudySkill *Get(int32 nMaxSpaceCount, int32 nSpaceCount) const
	{
		int32	nID = GEN_HORSE_STUDYSPELL_ID(nMaxSpaceCount, nSpaceCount);
		if(nID < PET_STUDYSKILLRATE_NUM)
		{
			return &m_aStudySkill[nID];
		}
		else
		{
			return NULL;
		}
	}

	SHorseStudySkillTab (void)
	{
		memset(m_aStudySkill, 0, sizeof(m_aStudySkill));
	}
};
extern SHorseStudySkillTab	g_HorseStudySpellTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define PET_APPERCEIVESKILLRATE_NUM	(24)
struct _PET_APPERCEIVESPELL_TAB
{
	int32	m_nSkillCount;
	int32	m_nLearnedVoluntarySkillCount;
	int32	m_nLearnedPassiveSkillCount;
	int32	m_nApperceiveVoluntarySkillRate;
	int32	m_nApperceivePassiveSkillRate;
};
extern _PET_APPERCEIVESPELL_TAB g_HorseApperceiveSpellTab[PET_APPERCEIVESKILLRATE_NUM];

#define PET_AITYPE	(5)
#define PET_SKILL_TYPE	(5)
extern float			g_HorseAIStrategyTab[PET_SKILL_TYPE][PET_AITYPE];


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32			MAX_HORSE_TYPE = 6000;
struct _HORSE_ATTR_TBL
{
	_HORSE_ATTR	m_aHorseTbl[MAX_HORSE_TYPE];
	int32		m_iCount;
	_HORSE_ATTR_TBL()
	{
		memset(this, 0, sizeof(_HORSE_ATTR_TBL));
	}

	_HORSE_ATTR *GetAttr(int32 PetType)
	{
		if(PetType <= MAX_HORSE_TYPE) return &m_aHorseTbl[PetType];
		return NULL;
	}

	int32 GetTypeCount()
	{
		return m_iCount;
	}
};

extern _HORSE_ATTR_TBL	g_HorseAttrTbl;

/*
=======================================================================================================================
=======================================================================================================================
*/
const int32			MAX_MIX_TYPE = 100;
struct _HORSE_MIX_TBL
{
	_HORSE_MIX	m_aHorseTbl[MAX_MIX_TYPE];
	int32		m_iCount;
	_HORSE_MIX_TBL()
	{
		memset(this, 0, sizeof(_HORSE_MIX_TBL));
	}

	_HORSE_MIX *GetMix(int32 nIndex)
	{
		if(nIndex < MAX_MIX_TYPE) return &m_aHorseTbl[nIndex];
		return NULL;
	}
	_HORSE_MIX *GetMixByType(int32 PetType)
	{
		for(int32 i = 0; i<m_iCount; i++)
		{
			if(m_aHorseTbl[i].m_nDataID == PetType) return &m_aHorseTbl[i];
			return NULL;
		}
		return NULL;
	}
	int32 GetTypeCount()
	{
		return m_iCount;
	}
};

extern _HORSE_MIX_TBL	g_HorseMixTbl;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32			MAX_MIX_SPELL_TOTAL = 32+1;
struct _HORSE_MIX_SPELL_TBL
{
	_HORSE_MIX_SPELL	m_aHorseTbl[MAX_MIX_SPELL_TOTAL];
	int32				m_iCount;
	_HORSE_MIX_SPELL_TBL()
	{
		memset(this, 0, sizeof(_HORSE_MIX_SPELL_TBL));
	}

	_HORSE_MIX_SPELL *GetMixSpell(int32 nIndex)
	{
		if(nIndex < MAX_MIX_SPELL_TOTAL) return &m_aHorseTbl[nIndex];
		return NULL;
	}
	_HORSE_MIX_SPELL *GetMixByTotal(int32 nSpellTotal)
	{
		for(int32 i = 0; i<MAX_MIX_SPELL_TOTAL; i++)
		{
			if(m_aHorseTbl[i].m_nHorseSpellTotal == nSpellTotal)
				return GetMixSpell(i);
		}
		//if(nSpellTotal < MAX_MIX_SPELL_TOTAL) return &m_aHorseTbl[nSpellTotal];
		return NULL;
	}
	int32 GetTypeCount()
	{
		return m_iCount;
	}
};

extern _HORSE_MIX_SPELL_TBL	g_HorseMixSpellTbl;

/*
=======================================================================================================================
=======================================================================================================================
*/
const int32		MAX_HORSE_SKILL_REALIZATION = 256;
struct _HORSE_SKILL_TBL
{
	_HORSE_SKILL_REALIZATION	m_aHorseSkillRealizationTbl[MAX_HORSE_SKILL_REALIZATION];

	int32				m_iCount;
	_HORSE_SKILL_TBL()
	{
		memset(this, 0, sizeof(_HORSE_SKILL_TBL));

		m_aSkillRealRateForSlot[0] = 50;
		m_aSkillRealRateForSlot[1] = 50;
		m_aSkillRealRateForSlot[2] = 50;
		m_aSkillRealRateForSlot[3] = 50;
		m_aSkillRealRateForSlot[4] = 50;
		m_aSkillRealRateForSlot[5] = 50;
		m_aSkillRealRateForSlot[6] = 50;
		m_aSkillRealRateForSlot[7] = 50;
		m_aSkillRealRateForSlot[8] = 50;
		m_aSkillRealRateForSlot[9] = 50;
		m_aSkillRealRateForSlot[10] = 50;
		m_aSkillRealRateForSlot[11] = 50;
	}

	_HORSE_SKILL_REALIZATION *GetAttr(int32 SkillID)
	{
		if(SkillID <= MAX_HORSE_SKILL_REALIZATION) return &m_aHorseSkillRealizationTbl[SkillID];
		return NULL;
	}

	int32 GetTypeCount()
	{
		return m_iCount;
	}

	int32	m_aSkillRealRateForSlot[MaxSlotNum];
};
extern _HORSE_SKILL_TBL g_HorseSkillTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32		MAX_HORSE_ITEM = 1024;
struct _HORSE_ITEM_TBL
{
	_HORSE_ITEM	m_aHorseItem[MAX_HORSE_ITEM];

	int32		m_iCount;
	_HORSE_ITEM	*GetHorseItemAttr(int32 iHorseItemID);
	_HORSE_ITEM_TBL()
	{
		memset(this, 0, sizeof(_HORSE_ITEM_TBL));
	}
};
extern _HORSE_ITEM_TBL	g_HorseItemTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32		MAX_HORSE_DROP = 1024;
struct _HORSE_DROP_TBL
{
	_HORSE_DROP	m_aHorse_drop[MAX_HORSE_DROP];
	int32		m_iCount;
	_HORSE_DROP_TBL()
	{
		memset(this, 0, sizeof(_HORSE_DROP_TBL));
	}
};
extern _HORSE_DROP_TBL	g_HorseDrop;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32		MAX_HORSE_GENRATION = 256;
struct _HORSE_PER_LIMIT_TBL
{
	int32	m_aLimit[MAX_HORSE_GENRATION];
	int32	m_iCount;
	_HORSE_PER_LIMIT_TBL()
	{
		memset(this, 0, sizeof(_HORSE_PER_LIMIT_TBL));
	}
};
extern _HORSE_PER_LIMIT_TBL	g_HorsePerLimit;

/*
 =======================================================================================================================
 =======================================================================================================================
 */


#endif