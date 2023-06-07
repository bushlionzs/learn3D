#pragma once

/* ��ЧID����Ӧ_DBC_DIRECT_EFFECT���� */
enum IMPACTTYPE
{
	IMPACTTYPE_PLYAER_LV_UP = 1,	/* ����������Ч */
	IMPACTTYPE_MOUNT_LV_UP_1= 2,	/* ����������Ч1 */
	IMPACTTYPE_MOUNT_LV_UP_2= 3,	/* ����������Ч2 */
	IMPACTTYPE_MOUNTING		= 4,	/* ������Ч */
	IMPACTTYPE_PATH_LINE	= 5,	/* ·����Ч */
};

/* ����ID ,��Ӧ _DBC_SPELL_DATA ���� */
enum SKILL_ID
{
	SKILLID_INVALID			= -1,
	SKILLID_ENSNARE_MOUNT	= 11,	/* ��׽���� */
	SKILLID_ENSNARE_BEASTIE = 12,	/* ��׽���� */
	SKILLID_MOUNTING		= 13,	/* ������ */
};

enum SKILL_CLASS
{
	SC_CHAR_ACTION_ATTACK	= 0,	/* ���������������� */
	SC_CHAR_ACTION_ASS,				/* ���������������� */
	SC_CHAR_PASSIVITY,				/* ���ﱻ�� */
	SC_CHAR_SPECIAL,				/* �������⼼�� */

	SC_ABILITY_ACTION,				/* ������������ */
	SC_ABILITY_PASSIVITY,			/* ��������� */

	SC_GUILD_ACTION,				/* ����������� */
	SC_GUILD_PASSIVITY,				/* ��ᱻ������ */

	SKILL_CLASS_NUM
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    1) �������ݽṹ ;
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
	const _DBC_SPELL_DATA	*m_pDefine;				/* ���ܱ��� */
	int32					m_nPosIndex;			/* �ڼ������� (UIͬ��) */
	BOOL					m_bLeaned;				/* �Ƿ���� */
	int32					m_nLevel;				/* ���ܼ��� */

	void					Clear(void);
	eOPTRESULT			IsCanUse(int32 idUser, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) const;
	eOPTRESULT			IsCanUse_Leaned(void) const;
	eOPTRESULT			IsCanUse_CheckCoolDown(void) const;
	eOPTRESULT			IsCanUse_CheckSkillCoolDown(void) const;
	eOPTRESULT			IsCanUse_CheckCommonCoolDown(void) const;
	eOPTRESULT			IsCanUse_CheckFlag(int32 idUser) const;
	eOPTRESULT			IsCanUse_CheckDeplete(int32 idUser) const;
	eOPTRESULT			IsCanUse_CheckTarget(int32 idUser, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) const;

	LPCTSTR					GetSkillDesc() const;			/* �õ����ܵ����� */
	LPCTSTR					GetSkillDesc_Interface() const; /* �õ����ܵ����� for ���� */

	FLOAT					GetSkillMaxRange() const;
	FLOAT					GetSkillMinRange() const;
};
typedef std::map<int32, SkillDetail>	SkillDataMap;

/*
 -----------------------------------------------------------------------------------------------------------------------
    2) �ͻ�����������ݽṹ ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _TABLE_LIFEABILITY_DEFINE;
struct SCLIENT_LIFESKILL
{
	const _TABLE_LIFEABILITY_DEFINE	*m_pDefine; /* ����ܱ��еĶ��� */
	int32 m_nPosIndex;	/* �ڼ������� (UIͬ��) */
	int32 m_nLevel;		/* ���ܵȼ� */
	int32 m_nExp;			/* ���������� */
	int32 m_nNextExp;		/* ��һ���������������� */
	int32 m_nNextMoney;	/* ��һ����������Ǯ */
	int32 m_nNextLevel;	/* ��һ������������ҵȼ� */
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
	int32 m_nLevel;		/* ���ܵȼ� */
	int32 m_nExp;			/* ���������� */
	int32 m_nNextExp;		/* ��һ���������������� */
	int32 m_nNextMoney;	/* ��һ����������Ǯ */
	int32 m_nNextLevel;	/* ��һ������������ҵȼ� */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    3) �ͻ����䷽���ݽṹ ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _TABLE_LIFEABILITY_ITEMCOMPOSE;
struct SClientPrescr
{
	const _TABLE_LIFEABILITY_ITEMCOMPOSE	*m_pDefine; /* ���䷽���еĶ��� */
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

//! �츳ר������
struct Inherence_Attack
{
	uint16 m_nLevel;
	uint16 m_nPoint;
	uint16 m_nCoefficient;

};

typedef std::map<int32, GiftData> GIFTDATA_MAP;



