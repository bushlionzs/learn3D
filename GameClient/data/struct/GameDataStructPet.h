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
    ���＼�����ݽṹ ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SHorseSpell
{
	const _DBC_SPELL_DATA	*m_pDefine;		/* ���ܱ��� */
	int32						m_nLevel;		/* ���ܵĵ�ǰ���� */
	int32						m_nPosIndex;	/* �ڼ������� (UIͬ��) */
	BOOL					m_bCanUse;		/* �����Ƿ���Ч */

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

/* ����״̬ */
enum MOUNT_STATE
{
	MOUNT_STATE_IDLE	= 0,	/* ������ */
	MOUNT_STATE_MOUNTING,		/* ��ս�� */
	MOUNT_STATE_EXCHANGE,		/* ������ */
	MOUNT_STATE_STALL,			/* ��̯�� */
	MOUNT_STATE_MATING,			/* ������ */
	MOUNT_STATE_FRIEND,			/* ������ */

	MOUNT_STATE_NUM,
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    �������ݽṹ ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SDataPet
{
public:
	const _TABLE_CHARACTER_MOUNT	*m_pModelData;		/* ģ��ID����Ӧchar_mount.tab */

	SHorseGuid					m_GUID;				/* ������ID */
	int32							m_nBaseID;			/* ����ID�� ��Ӧ _TABLE_MOUNT_BASE_DATA ���� */

	int32							m_nState;			/* ״̬��MOUNT_STATE */

	SHorseGuid					m_SpouseGUID;		/* ��żID */
	String						m_szName;			/* ���� */
	String						m_szNickname;		/* �ǳ� */
	int32							m_nGender;			/* �Ա� */
	int32							m_nLevel;			/* �ȼ� */
	int64_t							m_nExp;				/* ���� */
	int64_t							m_nMaxExp;			/* ����� */
	int32							m_nEraCount;		/* ������ */
	int32							m_nHappiness;		/* ���ֶ� */
	int32							m_nSkillGrid;		/* ���������� */

	int32							m_nAttrStr;			/* ���� */
	int32							m_nAttrDex;			/* ���� */
	int32							m_nAttrInt;			/* ���� */
	int32							m_nAttrCon;			/* ���� */

	int32							m_nAttrStrAdd;		/* �����ӵ� */
	int32							m_nAttrDexAdd;		/* ���ݼӵ� */
	int32							m_nAttrIntAdd;		/* �����ӵ� */
	int32							m_nAttrConAdd;		/* �����ӵ� */

	int32							m_nUpRate;			/* �ɳ��� */
	int32							m_nPotential;		/* Ǳ�� */
	int32							m_nBasic;			/* ���� */
	int32							m_nSavvy;			/* ���� */

	int32							m_nAttrStrApt;		/* �������� */
	int32							m_nAttrDexApt;		/* �������� */
	int32							m_nAttrIntApt;		/* �������� */
	int32							m_nAttrConApt;		/* �������� */

	int32							m_nAttrMaxStrApt;	/* ����������� */
	int32							m_nAttrMaxDexApt;	/* ����������� */
	int32							m_nAttrMaxIntApt;	/* ����������� */
	int32							m_nAttrMaxConApt;	/* ����������� */

	int32							m_nServerIndex;		/* ����ڷ������˴洢ʱ������ */
	SkillDetail					m_Skill[PET_MAX_SKILL_COUNT];	/* �����б� */

	BYTE						m_byLock;						/* �Ƿ����� */
	uint32						m_UnLockTime;					/* ����ʱ�� */
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
    ������ص��������� ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MountConfigDate
{
	int32 nCallUpHappiness;				/* ������ֶȴ��ڲſ����ٳ� */
	int32 nMatingSpend;					/* ���ｻ����Ҫ���ѵ���Ϸ�� */
	int32 nComposeSpend;				/* ����ϳ���Ҫ���ѵ���Ϸ�� */
	int32 nComposeLevel;				/* ����ϳɵ���͵ȼ� */
	uint32 uHorseComposeLockPassItem;	/* ����ϳ�ʱ�����������ܵĵ���ID */
	int32 nMatingMainMountLeastEra;		/* ����ʱ�������С�������� */
	int32 nMatingMountEraLimit;			/* ����ʱ�����������˴��������ƣ�ֻ��С������ˣ� */
	int32 nMatingMainMountLeastLevel;		/* ����ʱ�������С�ȼ����� */
	int32 nMatingSecondMountLeastLevel;	/* ����ʱ�������С�ȼ����� */
	int32 nMattingLevelPara;				/* ����ʱ���ݴ�������ȼ�����ʱ��ϵ�� */
	int32 nNumOfTake;						/* ����Я���������� */

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
    ���ܵ����
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

/* ������� */
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
