#pragma once

/* 特效ID，对应_DBC_DIRECT_EFFECT索引 */
enum IMPACTTYPE
{
	IMPACTTYPE_PLYAER_LV_UP = 1,	/* 人物升级特效 */
	IMPACTTYPE_MOUNT_LV_UP_1= 2,	/* 坐骑升级特效1 */
	IMPACTTYPE_MOUNT_LV_UP_2= 3,	/* 坐骑升级特效2 */
	IMPACTTYPE_MOUNTING		= 4,	/* 上马特效 */
	IMPACTTYPE_PATH_LINE	= 5,	/* 路点特效 */
};

/* 技能ID ,对应 _DBC_SPELL_DATA 索引 */
enum SKILL_ID
{
	SKILLID_INVALID			= -1,
	SKILLID_ENSNARE_MOUNT	= 11,	/* 捕捉坐骑 */
	SKILLID_ENSNARE_BEASTIE = 12,	/* 捕捉动物 */
	SKILLID_MOUNTING		= 13,	/* 上马技能 */
};

enum SKILL_CLASS
{
	SC_CHAR_ACTION_ATTACK	= 0,	/* 人物主动攻击技能 */
	SC_CHAR_ACTION_ASS,				/* 人物主动辅助技能 */
	SC_CHAR_PASSIVITY,				/* 人物被动 */
	SC_CHAR_SPECIAL,				/* 人物特殊技能 */

	SC_ABILITY_ACTION,				/* 生活主动技能 */
	SC_ABILITY_PASSIVITY,			/* 生活被动技能 */

	SC_GUILD_ACTION,				/* 帮会主动技能 */
	SC_GUILD_PASSIVITY,				/* 帮会被动技能 */

	SKILL_CLASS_NUM
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    1) 技能数据结构 ;
    $$
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _DBC_SPELL_DATA;

/*
 -----------------------------------------------------------------------------------------------------------------------
    struct _TABLE_SKILL_DEPLETE;
 -----------------------------------------------------------------------------------------------------------------------
 */
FLOAT ParseSkillMaxRange(const _DBC_SPELL_DATA* pSkillData, int32 nLevel);
FLOAT ParseSkillMinRange(const _DBC_SPELL_DATA* pSkillData, int32 nLevel);

struct SkillDetail
{
public:
	const _DBC_SPELL_DATA	*m_pDefine;				/* 技能表定义 */
	int32					m_nPosIndex;			/* 第几个技能 (UI同步) */
	BOOL					m_bLeaned;				/* 是否可用 */
	int32					m_nLevel;				/* 技能级别 */

	void					Clear(void);
	eOPTRESULT			IsCanUse(int32 idUser, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) const;
	eOPTRESULT			IsCanUse_Leaned(void) const;
	eOPTRESULT			IsCanUse_CheckCoolDown(void) const;
	eOPTRESULT			IsCanUse_CheckSkillCoolDown(void) const;
	eOPTRESULT			IsCanUse_CheckCommonCoolDown(void) const;
	eOPTRESULT			IsCanUse_CheckFlag(int32 idUser) const;
	eOPTRESULT			IsCanUse_CheckDeplete(int32 idUser) const;
	eOPTRESULT			IsCanUse_CheckTarget(int32 idUser, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) const;

	LPCTSTR					GetSkillDesc() const;			/* 得到技能的描述 */
	LPCTSTR					GetSkillDesc_Interface() const; /* 得到技能的描述 for 界面 */

	FLOAT					GetSkillMaxRange() const;
	FLOAT					GetSkillMinRange() const;
};
typedef std::map<int32, SkillDetail>	SkillDataMap;

/*
 -----------------------------------------------------------------------------------------------------------------------
    2) 客户端生活技能数据结构 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _TABLE_LIFEABILITY_DEFINE;
struct SCLIENT_LIFESKILL
{
	const _TABLE_LIFEABILITY_DEFINE	*m_pDefine; /* 生活技能表中的定义 */
	int32 m_nPosIndex;	/* 第几个技能 (UI同步) */
	int32 m_nLevel;		/* 技能等级 */
	int32 m_nExp;			/* 技能熟练度 */
	int32 m_nNextExp;		/* 下一级技能需求熟练度 */
	int32 m_nNextMoney;	/* 下一级技能需求钱 */
	int32 m_nNextLevel;	/* 下一级技能需求玩家等级 */
	SCLIENT_LIFESKILL()
	:
	m_pDefine(NULL),
	m_nPosIndex(0),
	m_nLevel(0),
	m_nExp(0),
	m_nNextExp(-1),
	m_nNextLevel(-1),
	m_nNextMoney(-1)
	{
	}
};

typedef std::map<int32, SCLIENT_LIFESKILL>	SLIFEABILITY_MAP;

struct _ARG_SCLIENT_LIFEABILITY
{
	int32 m_ID;
	int32 m_nLevel;		/* 技能等级 */
	int32 m_nExp;			/* 技能熟练度 */
	int32 m_nNextExp;		/* 下一级技能需求熟练度 */
	int32 m_nNextMoney;	/* 下一级技能需求钱 */
	int32 m_nNextLevel;	/* 下一级技能需求玩家等级 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    3) 客户端配方数据结构 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _TABLE_LIFEABILITY_ITEMCOMPOSE;
struct SClientPrescr
{
	const _TABLE_LIFEABILITY_ITEMCOMPOSE	*m_pDefine; /* 在配方表中的定义 */
};
typedef std::map<int32, SClientPrescr>	SPRESCR_MAP;


struct GiftData
{
	int32 m_nID;
	int32 m_nLevel;

	GiftData()
	{
		m_nID = INVALID_ID;
		m_nLevel = 0;
	}
};

//! 天赋专攻属性
struct Inherence_Attack
{
	uint16 m_nLevel;
	uint16 m_nPoint;
	uint16 m_nCoefficient;

};

typedef std::map<int32, GiftData> GIFTDATA_MAP;



