#pragma once
#include "Data/Struct/GameDataStructSkill.h"
enum PET_SKILL_INDEX
{
	PET_SKILL_0		= 0,
	PET_SKILL_1,
	PET_SKILL_2,
	PET_SKILL_3,
	PET_SKILL_4,
	PET_SKILL_5,
	PET_SKILL_6,
	PET_SKILL_7,
	PET_SKILL_8,
	PET_SKILL_9,
	PET_SKILL_10,
	PET_SKILL_11,
	PET_SKILL_NUM,
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    宠物技能数据结构 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SHorseSpell
{
	const _DBC_SPELL_DATA	*m_pDefine;		/* 技能表定义 */
	int32						m_nLevel;		/* 技能的当前级别 */
	int32						m_nPosIndex;	/* 第几个技能 (UI同步) */
	BOOL					m_bCanUse;		/* 格子是否有效 */

	SHorseSpell()
	{
		m_pDefine = NULL;
		m_nLevel = 0;
		m_nPosIndex = -1;
		m_bCanUse = FALSE;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Clear(void)
	{
		m_pDefine = NULL;
		m_nLevel = 0;
		m_nPosIndex = -1;
		m_bCanUse = FALSE;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	SHorseSpell &operator=(const SHorseSpell &val)
	{
		m_pDefine = val.m_pDefine;
		m_nLevel = val.m_nLevel;
		m_nPosIndex = val.m_nPosIndex;
		m_bCanUse = val.m_bCanUse;
		return *this;
	}
};

/* 坐骑状态 */
enum MOUNT_STATE
{
	MOUNT_STATE_IDLE	= 0,	/* 空闲中 */
	MOUNT_STATE_MOUNTING,		/* 出战中 */
	MOUNT_STATE_EXCHANGE,		/* 交易中 */
	MOUNT_STATE_STALL,			/* 摆摊中 */
	MOUNT_STATE_MATING,			/* 交配中 */
	MOUNT_STATE_FRIEND,			/* 征友中 */

	MOUNT_STATE_NUM,
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    宠物数据结构 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SDataPet
{
public:
	const _TABLE_CHARACTER_MOUNT	*m_pModelData;		/* 模型ID，对应char_mount.tab */

	SHorseGuid					m_GUID;				/* 服务器ID */
	int32							m_nBaseID;			/* 基础ID， 对应 _TABLE_MOUNT_BASE_DATA 索引 */

	int32							m_nState;			/* 状态，MOUNT_STATE */

	SHorseGuid					m_SpouseGUID;		/* 配偶ID */
	String						m_szName;			/* 名称 */
	String						m_szNickname;		/* 昵称 */
	int32							m_nGender;			/* 性别 */
	int32							m_nLevel;			/* 等级 */
	int64_t							m_nExp;				/* 经验 */
	int64_t							m_nMaxExp;			/* 最大经验 */
	int32							m_nEraCount;		/* 几代宠 */
	int32							m_nHappiness;		/* 快乐度 */
	int32							m_nSkillGrid;		/* 技能栏数量 */

	int32							m_nAttrStr;			/* 力量 */
	int32							m_nAttrDex;			/* 敏捷 */
	int32							m_nAttrInt;			/* 智力 */
	int32							m_nAttrCon;			/* 体力 */

	int32							m_nAttrStrAdd;		/* 力量加点 */
	int32							m_nAttrDexAdd;		/* 敏捷加点 */
	int32							m_nAttrIntAdd;		/* 智力加点 */
	int32							m_nAttrConAdd;		/* 体力加点 */

	int32							m_nUpRate;			/* 成长率 */
	int32							m_nPotential;		/* 潜能 */
	int32							m_nBasic;			/* 根骨 */
	int32							m_nSavvy;			/* 悟性 */

	int32							m_nAttrStrApt;		/* 力量资质 */
	int32							m_nAttrDexApt;		/* 敏捷资质 */
	int32							m_nAttrIntApt;		/* 智力资质 */
	int32							m_nAttrConApt;		/* 体力资质 */

	int32							m_nAttrMaxStrApt;	/* 最大力量资质 */
	int32							m_nAttrMaxDexApt;	/* 最大敏捷资质 */
	int32							m_nAttrMaxIntApt;	/* 最大智力资质 */
	int32							m_nAttrMaxConApt;	/* 最大体力资质 */

	int32							m_nServerIndex;		/* 骑乘在服务器端存储时的索引 */
	SkillDetail					m_Skill[PET_MAX_SKILL_COUNT];	/* 技能列表 */

	BYTE						m_byLock;						/* 是否锁定 */
	uint32						m_UnLockTime;					/* 解锁时间 */
public:
	SDataPet()
	{
		Clear();
	}
	void				Clear(void);

	SDataPet &operator =(const SDataPet &val);

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	BOOL IsIdle(void) const
	{
		return(MOUNT_STATE_IDLE == m_nState) ? (TRUE) : (FALSE);
	}
};

LPCSTR	GetMountStateText(int32 nState);

LPCSTR	GetMountTipDesc(int32 nSkillID, LPCSTR szStr, const SDataPet *pPet);

/*
 -----------------------------------------------------------------------------------------------------------------------
    坐骑相关的配置数据 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MountConfigDate
{
	int32 nCallUpHappiness;				/* 坐骑快乐度大于才可以召出 */
	int32 nMatingSpend;					/* 坐骑交配需要花费的游戏币 */
	int32 nComposeSpend;				/* 坐骑合成需要花费的游戏币 */
	int32 nComposeLevel;				/* 坐骑合成的最低等级 */
	uint32 uHorseComposeLockPassItem;	/* 坐骑合成时锁定被动技能的道具ID */
	int32 nMatingMainMountLeastEra;		/* 交配时主骑乘最小代数限制 */
	int32 nMatingMountEraLimit;			/* 交配时副骑乘与主骑乘代数差限制（只能小于主骑乘） */
	int32 nMatingMainMountLeastLevel;		/* 交配时主骑乘最小等级限制 */
	int32 nMatingSecondMountLeastLevel;	/* 交配时副骑乘最小等级限制 */
	int32 nMattingLevelPara;				/* 交配时根据代数计算等级限制时的系数 */
	int32 nNumOfTake;						/* 坐骑携带数量参数 */

	MountConfigDate()
	{
		nCallUpHappiness = 0;
		nMatingSpend = 0;
		nComposeSpend = 0;
		nComposeLevel = 0;
		uHorseComposeLockPassItem = 0;
		nMatingMainMountLeastEra = 0;
		nMatingMountEraLimit = 0;
		nMatingMainMountLeastLevel = 0;
		nMatingSecondMountLeastLevel = 0;
		nMattingLevelPara = 0;
		nNumOfTake = 0;
	}
};
class	KCharacter_NPC;

/*
 -----------------------------------------------------------------------------------------------------------------------
    技能的骑宠
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MountAvatar
{
	int32				nMountID;
	String			strAvatarName;
	KCharacter_NPC	*pAvatar;

	MountAvatar()
	{
		nMountID = INVALID_ID;
		pAvatar = NULL;
		strAvatarName = "";
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Clear()
	{
		nMountID = INVALID_ID;
		pAvatar = NULL;
		strAvatarName = "";
	}
};

/* 骑乘征友 */
enum { MATEMOUNT_MAX_NUM_ONEPAGE = 6, };

struct MateMountInfo
{
	SHorseGuid	m_HorseGuid;
	String		m_szHorseName;
	String		m_szOwnerName;
	String		m_szLeaveWords;
	int32			m_iHorseLevel;
	int32			m_iSex;
	int32			m_iGrowRate;
	int32			m_iDataID;
	int32			m_iMatchNum;

	/*
	 * MateMountInfo() ;
	 * { ;
	 * MateMountInfo=-1;
	 * m_szHorseName="";
	 * m_szOwnerName="";
	 * }
	 */
};

struct MateMount_Avatar
{
	String			m_strFakeObjName;
	int32				m_iDataID;
	KCharacter_NPC	*m_pAvatar;

	MateMount_Avatar()
	{
		m_strFakeObjName = "";
		m_iDataID = 0;
		m_pAvatar = NULL;
	}
};

typedef std::vector<MateMountInfo>	MateMountInfoVec;
