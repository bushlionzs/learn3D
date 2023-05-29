#pragma once
#include "DefineItem.h"
#include "DefineGuild.h"
#include "Define.h"
#include "TAB.h"

#define EQUIP_CHIEFTAIN_TAG 11990001

/* װ���ϵ���Ч */
#define EQUIP_EFFECT_MAX_NUM	16
struct EQUIP_EFFECT
{
	LPCTSTR szEffect;					/* ��Чid */
	LPCTSTR szBindPoint;				/* ��Ч��� */
};

/* �����ϵ���Ч */
#define MONSTER_EFFECT_MAX_NUM	4
struct MONSTER_EFFECT
{
	LPCTSTR szEffect;
	LPCTSTR szBind;

	MONSTER_EFFECT()
	{
		szEffect = NULL;
		szBind = NULL;
	};
};

enum CHAR_RACE_LOGICTYPE
{
	CHAR_RACE_LOGICTYPE_DEFAULT = 0,
	CHAR_RACE_LOGICTYPE_CREATE_ROLE,
	CHAR_RACE_LOGICTYPE_SELECT_ROLE,
};

/* �������� (CHAR_01) */
#define TABLE_CHARACTER_RACE	(101)		/* ��������(�У�Ů) */
struct _TABLE_CHAR_RACE					/* bc */
{
	table_int_t 	nID;
	table_int_t 	nModelID;						/* ģ�� */
	table_int_t 	nDefHeadGeo;					/* ͷ */
	table_int_t 	nDefHairGeo;					/* �� */
	table_int_t 	nDefShoulder;					/* �� */
	table_int_t 	nDefBody;						/* ���� */
	table_int_t 	nDefArm;						/* �� */
	table_int_t 	nDefFoot;						/* �� */
	table_int_t 	nIdleInterval;					/* ����ʱ�� */
	table_int_t 	nWeaponId;						/* ����ID */
	table_int_t 	nSex;
	table_int_t 	nProfession;
	table_int_t 	nLogicType;					// CHAR_RACE_LOGICTYPE
	table_float_t  	fAddDownHeight;
	table_float_t 	fAddUpHeight;
};

/* ����ͷ��ģ�� (CHAR_02) */
#define TABLE_CHARACTER_HAIR_GEO	(102)	/* ����ͷ��ģ�� */
struct _TABLE_CHAR_HAIR_GEO
{
	table_int_t		nID;
	table_int_t		nRace;						/* RaceID */
	LPCSTR	pMeshFile;
	LPCSTR	pShowName;
	table_int_t		n1;			/* ������ƷID */
	LPCSTR	n2;			/* MaterialName */
	table_int_t		n3;			/* ������Ʒ���� */
	table_int_t		n4;			/* �Ƿ��ڳ�ʼʱ��ѡ */
	table_int_t		nHairType;	/* ͷ������ */
	table_int_t		nColorType; /* ��ɫ���� */
	LPCSTR	pColorName; /* ��ɫ��ʾ���� */
	table_int_t	bIsShowInCreateRole;
};

/* ��������ģ�� (CHAR_04) */
#define TABLE_CHARACTER_HEAD_GEO	(104)				/* ��������ģ�� */
struct _TABLE_CHAR_HEAD_GEO							/* bc */
{
	table_int_t		nID;
	LPCSTR		pMeshFile;
	table_int_t		nRace;
	LPCSTR		pShowName;
	table_int_t		nFaceType;								/* �������� */
	table_int_t		nColorType;								/* ��𣬺ͷ������Ӧ */
	table_int_t		bIsShowInCreateRole;
};

/* ���Ƕ����� (CHAR_06) */
#define TABLE_CHARACTER_ACTION_SET	(106)
#define MAX_WEAPON_TYPE_NUMBER		(18)			/* ������������ */
struct _TABLE_CHARACTER_ACTION_SET
{
	table_int_t		nID;
	LPCSTR	pWeapon_Set[MAX_WEAPON_TYPE_NUMBER];	/* ��Ӧ�������� eWEAPON_TYPE */
	table_int_t 	bHideWeapon;					/* �������� */
	table_int_t	nAppointedWeaponID;				/* ָ��������ID */
	LPCSTR	pszDesc;						/* ���� */
	table_float_t 	nMonitoringDegree;				/* �����ں϶� */
	table_int_t	nIsSkill;						/* �Ƿ��Ǽ��� */
};

/* ������Ч (CHAR_07) */
#define TABLE_CHARACTER_EFFECT	(107)
struct _TABLE_CHARACTER_EFFECT
{
	table_int_t 		nID;
	table_int_t 		nEffect1;
	table_int_t 		nEffect2;
	LPCSTR	pLocator;
	table_int_t 		nSoundID;
	LPCSTR	pWeaponLocator;
};

/* ������������ֵ (CHAR_08) */
#define TABLE_CHARACTER_EXPLEVEL	(108)
struct _TABLE_CHARACTER_EXPLEVEL
{
	table_int_t nID;
	LPCSTR pNeedExp;
};

/* ����ID��Ӧģ������ (CHAR_09) */
#define TABLE_CHARACTER_MODEL (109)
#define MAX_MOUNT_NUMBER	(20)
#define MAX_SOUND_NUMBER	(3)				/* ����ֵ���ݵ�������͵ó� ��Ϊ���ر�ˮ�������� */
struct _TABLE_CHARACTER_MODEL					/* bc */
{
	table_int_t 	m_nID;
	table_float_t 	m_fFuseTime;					/* �����ۺ�ʱ�� */
	LPCSTR	m_pszModelName;					/* ģ���ļ� */
	table_int_t 	m_nSoundId[MAX_SOUND_NUMBER];	/* ��ͬ�����ܲ������� */
	LPCSTR	m_pszActionSetName_None;		/* ��ʹ������Ķ����ļ� */
	LPCSTR	m_apszActionSetName_Mount[MAX_MOUNT_NUMBER];	/* ʹ�������Ķ����ļ� */

	table_int_t 	m_nCheckMount;					// ������Ƿ���������
											// <0������
											// =0���ܣ�����ӵ�е�����
											// >0���ܣ�ֻ����ָ������ char_mount.tab

	table_int_t 	m_nCheckWeapon;					// �Ƿ��ܹҽ�����
											// <0������
											// =0���ܣ��ҽ����������
											// >0���ܣ��ҽ�ָ������ item_loc.tab

	table_int_t 	m_nCanJump;						// �Ƿ����Ծ
};

/* ����ͷ�� */
#define TABLE_CHARACTER_FACE	(110)			/* ����ͷ�� */
struct _TABLE_CHAR_FACE						/* bc */
{
	table_int_t 		nID;
	LPCSTR	pImageSetName;
	table_int_t 		nRace;
	LPCSTR	pImageSetNameGray;
};

/* ����� */
#define MOUNT_EFFECT_MAX_NUM	8
struct MOUNT_EFFECT
{
	const char	*pszEffectLocator;			/* ��Ч�ﶨ�� */
	const char	*pszEffectName;				/* ��Ч���� */
};

struct MOUNT_ATTR_EFFECT
{
	table_int_t 			nType;						/* Ӱ�����,MountAttrEffect_Type */
	table_int_t 			nVal;						/* Ӱ����ֵ */
	const char	*pszEffectLocator;			/* ��Ч�ﶨ�� */
	const char	*pszEffectName;				/* ��Ч���� */
};

enum MountAttrEffect_Type
{
	MAE_INVALID		= -1,
	MAE_APT_ALL_MAX = 0,					/* ��������ȫ�� */

	MAE_APT_STR_MAX,						/* ���������� */
	MAE_APT_DEX_MAX,						/* ���������� */
	MAE_APT_INT_MAX,						/* ���������� */
	MAE_APT_CON_MAX,						/* ���������� */

	MAE_APT_STR_VAL,						/* ����������ֵ */
	MAE_APT_DEX_VAL,						/* ����������ֵ */
	MAE_APT_INT_VAL,						/* ����������ֵ */
	MAE_APT_CON_VAL,						/* ����������ֵ */

	MAE_APT_ONE_MAX,						/* ����һ�������� */

	MAE_NUMBER,
};

#define TABLE_CHARACTER_MOUNT (111)
struct _TABLE_CHARACTER_MOUNT
{
	table_int_t 					m_nID;									/* ���ID */
	table_float_t 					m_fBoardAddHeight;						/* ͷ����Ϣ��߶����� */	
	table_int_t 					m_nModelID;								/* ģ��ID */
	table_int_t 					m_nCharActionIndex;						/* �������ʱ�Ķ�����,��Ӧchar_model.tab��mount0~19 */
	MOUNT_EFFECT			m_EffectInfo[MOUNT_EFFECT_MAX_NUM];		/* ��Ч��Ϣ */
	LPCSTR					m_szIcoName;							/* ͷ���� */
	MOUNT_ATTR_EFFECT		m_AttrEffectInfo[MOUNT_EFFECT_MAX_NUM]; /* ����������Ч */
	table_float_t 					fCameraHeight;							// UI������߶�
	table_float_t 					fCameraDistance;						// UI���������
	table_float_t 					fCameraPitch;							// UI������Ƕ�
	table_float_t 					m_fCameraAddHeight;						// ��Ϸ������߶�����
	
};

/*
 * ������� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * ���ﶨ���ܱ� (CREATURE_01) #define TABLE_BUS_ATTR (201) ;
 * struct _TABLE_CREATURE_ATT_BASE ;
 * { ;
 * table_int_t nMonsterID1;
 * // ������ ;
 * table_int_t nCannotBeAttack;
 * // ���ɱ����� ;
 * table_int_t nID;
 * // ������ ;
 * table_int_t nLevel;
 * // �ȼ� ;
 * table_int_t NOTCARE1[3];
 * //* ˢ������ ;
 * // ��С��Ѫ�ٷֱ�(Hppercent) ;
 * // ����������(EXP) ;
 * table_int_t nAttackRate_N;
 * // ���̹������(table_int_t  range att) ;
 * table_int_t nAttackRate_F;
 * // Զ�̹������(long range att) ;
 * table_int_t nAttackRate_M;
 * // ħ���������(magic att) ;
 * table_int_t nDefence_N;
 * // ���̷���(table_int_t  range recovery) ;
 * table_int_t nDefence_F;
 * // Զ�̷���(long range recovery) ;
 * table_int_t nDefence_M;
 * // ħ������(magic recovery) ;
 * table_int_t nMaxHP;
 * // HP����(hp limit) ;
 * table_int_t nMaxMP;
 * // MP����(mp limit) ;
 * table_int_t nRestoreHP;
 * // HP�ظ�(hp reversion) ;
 * table_int_t nRestoreMP;
 * // MP�ظ�(mp reversion) ;
 * table_int_t nHit;
 * // ����(hit rate) ;
 * table_int_t nMiss;
 * // ���ܣ�volt�� ;
 * table_int_t nCritrate;
 * // �����ʣ�huixin) ;
 * table_int_t nTenacity;
 * //���� ;
 * table_int_t nAttackCold;
 * // ���Թ�����(shuxingatt1 ) �� ;
 * table_int_t nAttackFire;
 * // ���Թ�����(shuxingatt2 ) �� ;
 * table_int_t nAttackLight;
 * // ���Թ�����(shuxingatt3) �� ;
 * table_int_t nAttackPoison;
 * // ���Թ�����(shuxingatt4) �� ;
 * table_int_t nDefenceCold;
 * // ���Է�����(shuxingrecovery1) ;
 * table_int_t nDefenceFire;
 * // ���Է�����(shuxingrecovery2) ;
 * table_int_t nDefenceLight;
 * // ���Է�����(shuxingrecovery3) ;
 * table_int_t nDefencePoison;
 * // ���Է�����(shuxingrecovery4) ;
 * table_int_t NOTCARE2;
 * //* ���ýű�ID ;
 * table_int_t nModelID;
 * // ����ID ;
 * LPCSTR szIconName;
 * // ����ͷ�� ;
 * table_int_t nIsDisplayerName;
 * // �Ƿ���ʾͷ����Ϣ�� ;
 * table_float_t  fBoardHeight;
 * // ���ְ�߶� ;
 * table_float_t  fProjTexRange;
 * // ѡ�л���С ;
 * table_float_t  fShadowRange;
 * // ��Ӱ��С ;
 * table_int_t NOTCARE3[2];
 * // ��������ʱ�� ;
 * // ������ȴʱ�� ;
 * table_int_t nIdleInterval;
 * // ���м��ʱ�� ;
 * table_int_t nSpeed;
 * // �ƶ��ٶ� ;
 * table_int_t nMonsterWalkSpeed;
 * // �����ٶ� ;
 * table_int_t nAttackSpeed;
 * // �����ٶ� ;
 * table_int_t nMArmID;
 * // ��������ID ;
 * table_int_t NOTCARE4[4];
 * //* �����ID ;
 * // ����AI ;
 * // ��չAI ;
 * // ��Ӫ ;
 * table_int_t nCannotBeAttack;
 * // ���ɱ����� ;
 * table_int_t nCanHandle;
 * // �Ƿ���Խ��� ;
 * table_int_t NOTCARE5;
 * // �Ѻ�ֵ ;
 * table_int_t nMonsterBossFlag;
 * // BOSS��� ;
 * table_int_t nMonsterBossSnapImmID;
 * // ˲ʱЧ������ID ;
 * table_int_t nMonsterBossDurationImmID;
 * // ����Ч������ID ;
 * table_int_t NOTCARE6[2];
 * // �������뾶(��) ;
 * // ���������Ч�� ;
 * table_int_t nDropItemSet;
 * //������Ʒ�� ;
 * table_int_t nDropItemRate;
 * //������� ;
 * MONSTER_EFFECT sMonsterEffect[MONSTER_EFFECT_MAX_NUM];
 * // ���ڹ����ϵ���Ч ;
 * LPCSTR pHorseDropID;
 * // �����ID ;
 * table_int_t nDropID;
 * // ����ID ;
 * };
 */
#define TABLE_BUS_ATTR	(201)
struct _TABLE_BUS_ATTR
{
	table_int_t 				nID;					/* ������ */
	table_int_t 				nCannotBeAttack;		/* ���ɱ����� */
	LPCSTR			pName;					/* ���� */
	table_int_t 				nIsCanSwerve;			/* �Ƿ������ת�� */
	table_int_t 				nIsDisplayerName;		/* �Ƿ���ʾͷ����Ϣ�� */
	table_float_t 			fBoardHeight;			/* ���ְ�߶� */
	table_float_t 			fProjTexRange;			/* ѡ�л���С */
	table_float_t 			fShadowRange;			/* ��Ӱ��С */
	LPCSTR			szIconName;				/* ����ͷ�� */
	table_int_t 				nModelID;				/* ����ID */
	table_int_t 				nBusType;				/* Bus������ */
	table_int_t 				nBusMountModelID[2];	/* ��������ģ�� */
	LPCSTR			szMountModelLocator[2]; /* �ҽ���������󶨵����� */
	table_int_t 				nIdleInterval;			/* ���м��ʱ�� */
	table_int_t 				nCanHandle;				/* �Ƿ���Խ��� */
	table_int_t 				nMonsterBossFlag;		/* BOSS��� */
	MONSTER_EFFECT	sMonsterEffect[MONSTER_EFFECT_MAX_NUM]; /* ���ڹ����ϵ���Ч */
	LPCSTR			szPassengerLocator[8];					/* �˿���λ�İ󶨵� */
};

#define TABLE_CREATURE_ATT	(202)
struct _TABLE_CREATURE_ATT				/* : public _TABLE_CREATURE_ATT_BASE */
{
	table_int_t 				nID;				/* ������ */
	table_int_t 				nCannotBeAttack;	/* ���ɱ����� */
	LPCSTR			pName;				/* ���� */
	table_int_t 				nIsCanSwerve;		/* �Ƿ������ת�� */
	table_int_t 				nIsDisplayerName;	/* �Ƿ���ʾͷ����Ϣ�� */
	table_float_t 			fBoardHeight;		/* ���ְ�߶� */
	table_float_t 			fProjTexRange;		/* ѡ�л���С */
	table_float_t 			fShadowRange;		/* ��Ӱ��С */
	LPCSTR			szIconName;			/* ����ͷ�� */
	table_int_t 				nModelID;			/* ����ID */
	table_int_t 				nIdleInterval;		/* ���м��ʱ�� */
	table_int_t 				nCanHandle;			/* �Ƿ���Խ��� */
	table_int_t 				nMonsterBossFlag;	/* BOSS��� */
	table_int_t 				nRunSpeed;			/* �ܲ��ٶ� */
	table_int_t 				nWalkSpeed;			/* �����ٶ� */
	MONSTER_EFFECT	sMonsterEffect[MONSTER_EFFECT_MAX_NUM]; /* ���ڹ����ϵ���Ч */
	table_int_t 				nNPCType;	/* NPC���� */
};

/*
 * ���︽������ (TABLE_PET_EX_ATT) #define TABLE_PET_EX_ATT (202) ;
 * struct _TABLE_PET_EX_ATT // bc ;
 * { ;
 * table_int_t m_Type;
 * // ������ ;
 * table_int_t m_TakeLevel;
 * // ��Я���ȼ� ;
 * LPTSTR m_Name;
 * // ���� ;
 * table_int_t m_Camp;
 * // ��Ӫ ;
 * table_int_t m_Reserve1;
 * // ���� ;
 * table_int_t m_Reserve2;
 * // ���� ;
 * table_int_t m_FoodType;
 * // ʳ���� ;
 * table_int_t m_SkillLearnNum;
 * // ����ѧ�ļ����� ;
 * table_int_t m_PositiveSkill;
 * // �������� ;
 * table_int_t m_PassiveSkill1;
 * // ��������1 ;
 * table_int_t m_PassiveSkill2;
 * // ��������2 ;
 * table_int_t m_PassiveSkill3;
 * // ��������3 ;
 * table_int_t m_PassiveSkill4;
 * // ��������4 ;
 * table_int_t m_Life;
 * // ��׼���� ;
 * table_int_t m_StrPerception;
 * // ��׼�������� ;
 * table_int_t m_ConPerception;
 * // ��׼�������� ;
 * table_int_t m_DexPerception;
 * // ��׼�������� table_int_t m_SprPerception;
 * // ��׼������ ;
 * table_int_t m_IntPerception;
 * // ��׼�������� ;
 * table_int_t m_GrowRate0;
 * // �ɳ���1 ;
 * table_int_t m_GrowRate1;
 * // �ɳ���2 ;
 * table_int_t m_GrowRate2;
 * // �ɳ���3 ;
 * table_int_t m_GrowRate3;
 * // �ɳ���4 ;
 * table_int_t m_GrowRate4;
 * // �ɳ���5 ;
 * table_int_t m_CowardiceRate;
 * // ��С���� ;
 * table_int_t m_WarinessRate;
 * // �������� ;
 * table_int_t m_LoyalismRate;
 * // �ҳϼ��� ;
 * table_int_t m_CanninessRate;
 * // �������� ;
 * table_int_t m_ValourRate;
 * // ���ͼ��� ;
 * };
 * ������������� (CREATURE_03) #define TABLE_CREATURE_SOUND (203) ;
 * struct _TABLE_CREATURE_SOUND // bc ;
 * { ;
 * table_int_t nID;
 * table_int_t nUnderAttack;
 * table_int_t nAttack;
 * table_int_t nDeath;
 * };
 * BUS���Ա��� #define TABLE_BUS_ATTR (204) ;
 * const table_int_t BUS_SKILL_SIZE = 5;
 * ;
 * struct _TABLE_BUS_ATTR ;
 * { ;
 * _TABLE_CREATURE_ATT nMonsterBaseAttr;
 * table_int_t nChariotSkill[BUS_SKILL_SIZE];
 * // ս������1-5 ;
 * LPTSTR szTitle;
 * // title���� ;
 * table_int_t nControl;
 * // ����Ȩ ;
 * table_int_t nSpace;
 * // ս���ռ� ;
 * table_int_t nShowPlayer;
 * // ������ʾ ;
 * };
 * ;
 * ��Ʒ��� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * װ������Ʒ��ʾ���� (ITEM_01)
 */
#define TABLE_ITEM_VISUAL_CHAR	(301)
struct _TABLE_ITEM_VISUAL_CHAR	/* bc */
{
#define CHAR_RACE_NUM	(2)
	table_int_t nID;

	/*
	 * LPCSTR pVisualEntity[ 6 * 2 * CHAR_RACE_NUM ];
	 */
	table_int_t pVisualEntityIndex[12];
};

#define EQUIP_LOC_EFFECT_MAX_NUM	8
#define TABLE_EQUIP_LOC				(303)
struct _TABLE_EQUIP_LOC
{
	table_int_t 				nID;
	LPCSTR			szDesc;
	LPCSTR			pMeshFile;
	LPCSTR			pMatFile;
	EQUIP_EFFECT	szREffect[EQUIP_LOC_EFFECT_MAX_NUM];	/* ������Ч */
};

#define  ITEM_VISUAL_EFFECT_MAX_NUM		(30)
/* �ҽ�����Ʒ��ʾ���� (ITEM_02) */
#define TABLE_ITEM_VISUAL_LOCATOR (302)
struct _TABLE_ITEM_VISUAL_LOCATOR
{
	table_int_t 		nID;

	LPCSTR	pObjFile_Right_Man;			/* ������������ */
	LPCSTR	pMatName_Right_Man;			/* ���������������� */

	LPCSTR	pObjFile_Right_Woman;		/* Ů���������� */
	LPCSTR	pMatName_Right_Woman;		/* Ů�������������� */

	LPCSTR	pObjFile_Left_Man;			/* ���������� */
	LPCSTR	pMatName_Left_Man;			/* �������������� */

	LPCSTR	pObjFile_Left_Woman;			/* ���������� */
	LPCSTR	pMatName_Left_Woman;			/* �������������� */

	LPCSTR	pObjShieldFile;			/* ���ֶ��� */
	LPCSTR	pMatName_Shield;		/* ���ֶܲ����� */

	table_int_t 	nWeaponPointType;		// ���������� ENUM_WEAPON_LOCATOR_TYPE
	table_int_t 	pWeaponType;			/* �������� */
	table_int_t 	nWeaponActor;			/* ��ʾ�������Ƿ��ж��� */

	LPCSTR	pWeaponActorFile_Man_Down;		/* ���������������ļ� */
	LPCSTR	pWeaponActorFile_Woman_Down;	/* Ů�������������ļ� */

	LPCSTR	pWeaponActorFile_Man_Up;		/* ���������������ļ� */
	LPCSTR	pWeaponActorFile_Woman_Up;		/* Ů�������������ļ� */

	LPCSTR	pEffectName[ITEM_VISUAL_EFFECT_MAX_NUM];		/* ����30�и��ֱ�ʯ����Ч */
};

/* ������ */
#define TABLE_ITEM_MONSTER_VISUAL_LOCATOR (320)
struct _TABLE_ITEM_MONSTER_VISUAL_LOCATOR
{
	table_int_t 				nID;			/* id */

	LPCSTR			pObjFile_Right; /* ���������� */
	LPCSTR			pMatName_Right; /* �������������� */
	EQUIP_EFFECT	szREffect[MONSTER_EFFECT_MAX_NUM];	/* ����������Ч */

	LPCSTR			pObjFile_Left;						/* ���������� */
	LPCSTR			pMatName_Left;						/* �������������� */
	EQUIP_EFFECT	szLEffect[MONSTER_EFFECT_MAX_NUM];	/* ����������Ч */

	LPCSTR			pObjShieldFile;						/* ���ֶ��� */
	LPCSTR			pMatName_Shield;					/* ���ֶܲ����� */
	EQUIP_EFFECT	szLSEffect[MONSTER_EFFECT_MAX_NUM]; /* ���ֶܲ���Ч */

	table_int_t 				pWeaponType;						/* �������� */
	table_int_t 				nWeaponActor;						/* ��ʾ�������Ƿ��ж��� */
	LPCSTR			pActorFile; /* ���������ļ� */
};

#define EQUIP_EFFECT_ATTR_MAXNUM	16

/*
 -----------------------------------------------------------------------------------------------------------------------
    װ�����������Ե�Ӱ��
 -----------------------------------------------------------------------------------------------------------------------
 */
struct EQUIP_EFFECT_ATTR
{
	table_int_t nAttrID;						/* Ӱ������Id */
	table_int_t nEffectNum;						/* Ӱ��������ֵ */
};

/* ���Ӽ��������� */
#define EQUIP_ADDEFFECT_SKILL_MAXNUM	4

/* Ӱ�켼�������� */
#define EQUIP_EFFECT_SKILL_MAXNUM	4

struct EQUIP_EFFECT_SKILL
{
	table_int_t nSkillID;						/* Ӱ�켼��id */
	table_int_t nEffectLevel;					/* Ӱ�켼�ܵȼ� */
};

/* ��Ʒ�����_װ�� */
#define TABLE_ITEM_EQUIP	(318)
struct _TABLE_ITEM_EQUIP
{
	table_int_t 					nID;				/* װ�����к� */
	table_int_t 					nClass;				/* ��������class */
	table_int_t 					nType;				/* ��� type */
	table_int_t 					nIndex;				/* ��Ʒ�� */
	table_int_t 					nColorType;			/* ��Ʒ��ɫ���� */
	table_int_t 					nEquipPoint;		/* װ���� */
	table_int_t 					nRule;				/* ��Ӧ���� */
	table_int_t 					nSetID;				/* װ����װ��� */
	LPCSTR					nLevelRequire;		/* �ȼ����� */
	table_int_t 					iReqInherenceLevel;	/* rj 2010-8-23 �츳�ȼ� */
	table_int_t 					iReqPersonLevel;	/* rj 2010-8-23 ���˵ȼ� */
	table_int_t 					nBasePrice;			/* �����۸� */
	table_int_t 					nBMaxDur;			/* max�;� */
	table_int_t 					nTermHour;			/* ����ʱ�ޣ���λ��Сʱ */
	LPCSTR					nStarLeveL;			/* �Ǽ� */
	table_int_t 					nNatureHoleNum;		/* ��Ȼ����Ŀ */
	table_int_t 					nMaxHoleNum;		/* ������Ŀ */
	table_int_t 					nProfessionalReq;	/* ְҵҪ�� */
	table_int_t 					nPaixing;			/* װ������ */
	table_int_t 					nEquipScore;		/* װ������ */
	table_int_t 					nBaseAttackNear;	/* �������̹��� */
	table_int_t 					nBaseAttackFar;		/* ����Զ�̹��� */
	table_int_t 					nBaseAttackMagic;	/* ����ħ������ */
	table_int_t 					nBaseDEefNear;		/* �������̷��� */
	table_int_t 					nBaseDefFar;		/* ����Զ�̷��� */
	table_int_t 					nBaseDefMagic;		/* ����ħ������ */

	/* װ�����������Ե�Ӱ�� */
	EQUIP_EFFECT_ATTR	stEffectAttr[EQUIP_EFFECT_ATTR_MAXNUM];

	/* װ���Լ��ܵ�Ӱ�� */
	EQUIP_EFFECT_SKILL	stADDEffectSkill[EQUIP_ADDEFFECT_SKILL_MAXNUM]; /* ���Ӽ��� */
	EQUIP_EFFECT_SKILL	stEffectSkill[EQUIP_EFFECT_SKILL_MAXNUM];		/* Ӱ�켼�� */
	table_int_t 					nEventScript;
	table_int_t 					nAddParam1;						/* Ԥ�� */
	table_int_t 					nAddParam2;						/* Ԥ�� */
	table_int_t 					nAddParam3;						/* Ԥ�� */
	/*
	 * // װ�����������Ե�Ӱ�� table_int_t stEffectAttr[ EQUIP_EFFECT_ATTR_MAXNUM * 2] ;
	 * // װ���Լ��ܵ�Ӱ�� table_int_t ADDEffectSkill[EQUIP_ADDEFFECT_SKILL_MAXNUM * 2];
	 * // ���Ӽ��� table_int_t EffectSkill[EQUIP_EFFECT_SKILL_MAXNUM * 2];
	 * // Ӱ�켼��
	 */
};

/* by soongxl ��չ�� */
#define TABLE_ITEM_EXTBAG (350)
struct _TABLE_ITEM_EXTBAG
{
	table_int_t 		nID;										/* id */
	table_int_t 		nClass;										/* class */
	table_int_t 		nType;										/* ���� */
	table_int_t 		nIndex;
	LPCSTR	szIcon;										/* icon */
	LPCSTR	szName;										/* ���� */
	LPCSTR	szDesc;										/* ���� */
	table_int_t 		nRule;										/* ��Ӧ���� */
	table_int_t 		nBasePrice;									/* �����۸� */
	table_int_t 		nSalePrice;									/* ���ۼ۸� */
	table_int_t 		nValidTime;									/* ��Чʱ�� */
	table_int_t 		nSize;										/* ��Ч������ */
	table_int_t 		nAddParam1;									/* Ԥ�� */
	table_int_t 		nAddParam2;									/* Ԥ�� */
	table_int_t 		nAddParam3;									/* Ԥ�� */
	LPCTSTR szTypeDesc;									/* ��Ʒ���������� */
	LPCTSTR nDropModelId;								/* ����ʱ������ */
	LPCTSTR szDropEffect;								/* ����ģ�͸�����Ч */
	table_int_t 		szDropSound;								/* �������� */
	LPCTSTR szDropVisColor;								/* ��ʾ������ɫ */
	LPCTSTR szAnimateFrame;								/* ����֡ */
};

/* ��Ʒ�����_ҩƿ (ITEM_06) */
#define TABLE_ITEM_MEDIC	(306)
struct _TABLE_ITEM_MEDIC									/* ef */
{
	table_int_t 		nID;										/* id */
	table_int_t 		nClass;										/* class */
	table_int_t 		nType;										/* ���� */
	table_int_t 		nIndex;
	LPCSTR		szIcon;										/* icon */
	LPCSTR		szName;										/* ���� */
	LPCSTR		szDesc;										/* ���� */
	table_int_t 		nLevel;										/* �ȼ� */
	table_int_t 		iReqInherenceLevel;							/* rj 2010-8-23 �츳�ȼ� */
	table_int_t 		iReqPersonLevel;							/* rj 2010-8-23 ���˵ȼ� */
	LPCSTR		nProfessionalReq;							/* ְҵ���� */
	table_int_t 		nBasePrice;									/* �����۸� */
	table_int_t 		nSalePrice;									/* ���ۼ۸� */
	table_int_t 		nRule;										/* ��Ӧ���� */
	table_int_t 		nPileCount;									/* �������� */
	table_int_t 		nScriptID;									/* �ű���� */
	table_int_t 		nSkillID;									/* ���ܱ�� */
	table_int_t 		NOTCARE[2];									/* �����ܵȼ� */
	table_int_t 		nMaxHold;									/* ���������� */
	table_int_t 		nTargetType;								/* ��Զ������� eITEM_TARGET_TYPE */
	table_int_t 		nBroadcast;									/* �Ƿ�㲥 */
	table_int_t 		nAddParam1;									/* Ԥ�� */
	table_int_t 		nAddParam2;									/* Ԥ�� */
	table_int_t 		nAddParam3;									/* Ԥ�� */
	LPCTSTR		szTypeDesc;									/* ��Ʒ���������� */
	LPCTSTR		nDropModelId;								/* ����ʱ������ */
	LPCTSTR		szDropEffect;								/* ����ģ�͸�����Ч */
	table_int_t 		szDropSound;								/* �������� */
	LPCTSTR		szDropVisColor;								/* ��ʾ������ɫ */
	LPCTSTR		szAnimateFrame;								/* ����֡ */
	table_int_t 		nQualityLevel;								/* Ʒ�ʵȼ� */
	table_int_t 		nEffectId;									/* Ч��ID */
	table_int_t 		nbRecord;									/* �Ƿ�������� */
	table_int_t 		nRecordNum;									/* ���� */
	table_int_t 		nPrescrId;									/* ��Ӧ���䷽ID */
	table_int_t 		nReworkIndex;								/*ϴʯ���ϳɶ�Ӧ����*/
	/* ... NOT CARE */
};

/* ��Ʒ����� ������Ʒ�� */
#define TABLE_ITEM_TASK	(323)
struct _TABLE_ITEM_TASK									/* ef */
{
	table_int_t 		nID;										/* id */
	table_int_t 		nClass;										/* class */
	table_int_t 		nType;										/* ���� */
	table_int_t 		nIndex;
	LPCSTR	szIcon;										/* icon */
	LPCSTR	szName;										/* ���� */
	LPCSTR	szDesc;										/* ���� */
	table_int_t 		nLevelRequire;								/* �ȼ� */
	table_int_t 		nBasePrice;									/* �����۸� */
	table_int_t 		nSalePrice;									/* ���ۼ۸� */
	table_int_t 		nRule;										/* ��Ӧ���� */
	table_int_t 		nPileCount;									/* �������� */
	table_int_t 		nScriptID;									/* �ű���� */
	table_int_t 		nSkillID;									/* ���ܱ�� */
	table_int_t 		NOTCARE[2];									/* �����ܵȼ� */
	table_int_t 		nMaxHold;									/* ���������� */
	table_int_t 		nTargetType;								/* ��Զ������� eITEM_TARGET_TYPE */
	table_int_t 		nBroadcast;									/* �Ƿ�㲥 */
	table_int_t 		nAddParam1;									/* Ԥ�� */
	table_int_t 		nAddParam2;									/* Ԥ�� */
	table_int_t 		nAddParam3;									/* Ԥ�� */
	LPCTSTR szTypeDesc;									/* ��Ʒ���������� */
	LPCTSTR szAnimateFrame;								/* ����֡ */
	LPCTSTR szDropVisColor;								/* ��ʾ������ɫ */
	/* ... NOT CARE */
};

/* ��ʯ���������� */
#define EQUIP_GEMATTR_MAXNUM	4

/* ����ʯ������� */
#define EQUIP_GEMNEED_MAXNUM	3

struct EQUIP_GEM_ATTR
{
	table_int_t nAttr;											/* ǿ������ */
	table_int_t nNum;											/* ǿ����ֵ */
};

struct EQUIP_GEM_NEED
{
	table_int_t nGem;											/* ����ʯ */
	table_int_t nGemNum;										/* ����ʯNUM */
};

/* ��Ʒ�����_��ʯ (ITEM_07) */
#define TABLE_ITEM_GEM	(307)
struct _TABLE_ITEM_GEM									/* ef */
{
	table_int_t 				nID;
	table_int_t 				nClass;								/* ��Ʒ���� */
	table_int_t 				nType;								/* ��Ʒ���� */
	table_int_t 				nGemIndex;							/* ��Ʒ��� */
	LPCTSTR			szIcon;								/* ͼ�� */
	table_int_t 				nRule;								/* ��Ӧ���� */
	LPCTSTR			szWhere;							/* ��Ƕλ�� */
	LPCTSTR			szName;
	LPCTSTR			szDesc;
	table_int_t 				nPrice;								/* ��ʯ�����ļ۸� */
	table_int_t 				nSalePrice;							/* ��ʯ���۵ļ۸� */
	table_int_t 				nNeedMoney;							/* �����Ǯ */
	table_int_t 				nNeedEquipLevel;					/* ����װ���ȼ� */
	table_int_t 				nBroadcast;							/* �Ƿ�㲥 */

	/*
	 * table_int_t nAttr[66];
	 * // ��ʯ�ĸ������� // 5
	 */
	EQUIP_GEM_ATTR	stGemAttr[EQUIP_GEMATTR_MAXNUM];	/* ��ʯ�ĸ������� */
	EQUIP_GEM_NEED	stGemNeed[EQUIP_GEMNEED_MAXNUM];	/* ����������ʯ����Ϣ */
	table_int_t 				nShowLevel;						/* ��ʾ�ȼ� */
	table_int_t 				nAddParam1;						/* Ԥ�� */
	table_int_t 				nAddParam2;						/* Ԥ�� */
	table_int_t 				nAddParam3;						/* Ԥ�� */
	LPCTSTR			szColor;						/* �������Ե���ɫ */
	LPCTSTR			szTypeDesc;						/* �������� */
	LPCTSTR			szEffectColor;					/* ��Ч��ɫֵ */
	table_int_t 				nEffectIndex;					/* ��Ч���� */
	LPCTSTR			nDropModelId;					/* ����ʱ������ */
	LPCTSTR			szDropEffect;					/* ����ģ�͸�����Ч */
	table_int_t 				szDropSound;					/* �������� */
	LPCTSTR			szDropVisColor;					/* ��ʾ������ɫ */
	LPCTSTR			szAnimateFrame;					/* ����֡ */
	table_int_t 				nReworkIndex;

	/* ... NOT CARE */
};

/* Gem_Type.tab client ʹ�� for ��ʯ������Ϣ */
#define TABLE_ITEM_GEM_CLIENT_TYPE	(314)
struct _TABLE_ITEM_GEM_CLIENT_TYPE					/* ef */
{
	table_int_t 		nID;
	LPCTSTR szTypeDesc;								/* �������� */
};

/*
 * ��Ʒ�����_��ͼ (ITEM_08) #define TABLE_ITEM_STOREMAP (308) ;
 * struct _TABLE_ITEM_STOREMAP // ef ;
 * { ;
 * table_int_t nID;
 * table_int_t nClass;
 * table_int_t nQuality;
 * //remove ;
 * table_int_t nType;
 * LPCSTR szIcon;
 * table_int_t nIndex;
 * LPCSTR szName;
 * LPCSTR szDesc;
 * table_int_t nLevelRequire;
 * table_int_t nRule;
 * //....................... ;
 * //... NOT CARE ;
 * };
 * ��װ��Ϻ󸽼����� (ITEM_15)
 */
#define TABLE_ITEM_SETATT (315)
struct _TABLE_ITEM_SETATT
{
	table_int_t nID;
	table_int_t nAtt[66];									/* 59 */
};

/*
 * // ��ͨװ�����α� #define TABLE_ITEM_COMMON_EQUIP_VISUAL (316) struct
 * _TABLE_ITEM_COMMON_EQUIP_VISUAL { table_int_t nIndex;
 * // ��� ����ͬһid��װ�� table_int_t nID;
 * // ���� 10010000 ��ͨװ��ĩ4λΪ0000 table_int_t level;
 * // client��ʹ�� table_int_t nModelID;
 * // ģ��id��������ģ�ͱ����ҵ���Ӧ�ľ���ģ�� LPCTSTR szName;
 * // װ������ ���� xx�� LPCTSTR szDes;
 * // ˵�� ������Ϣ LPCTSTR szIcon;
 * // ͼ�� ui��ʾ�� LPCTSTR szType;
 * // ��, �������� LPCTSTR nDropModelId;
 * //����ʱ������ // LPCTSTR szDropEffect;
 * //����ģ�͸�����Ч table_int_t szDropSound;
 * //�������� LPCTSTR szDropVisColor;
 * //��ʾ������ɫ //LPCTSTR szEffect[EQUIP_EFFECT_MAX_NUM*2];
 * //��Ч EQUIP_EFFECT szEffect[EQUIP_EFFECT_MAX_NUM];
 * //��Ч };
 */
#define TABLE_ITEM__EQUIP_VISUAl_MAXNUM	99
#define TABLE_ITEM__EQUIP_GEM_MAXNUM		7

/*
 * //�߼�װ�����α� #define TABLE_ITEM_ADVANCED_EQUIP_VISUAL (317) struct
 * _TABLE_ITEM_ADVANCED_EQUIP_VISUAL { table_int_t nIndex;
 * // ��� �Ը߼�װ����˵ û�õ��� table_int_t nID;
 * // ���� 10010001 table_int_t nModelID;
 * // ģ��id��������ģ�ͱ����ҵ���Ӧ�ľ���ģ�� LPCTSTR szName;
 * // װ������ ���� xx�� LPCTSTR szDes;
 * // ˵�� ������Ϣ LPCTSTR szIcon;
 * // ͼ�� ui��ʾ�� LPCTSTR szType;
 * // �� LPCTSTR nDropModelId;
 * //����ʱ������ // LPCTSTR szDropEffect;
 * //����ģ�͸�����Ч table_int_t szDropSound;
 * //�������� LPCTSTR szDropVisColor;
 * //��ʾ������ɫ // LPCTSTR szEffect[EQUIP_EFFECT_MAX_NUM*2];
 * //��Ч EQUIP_EFFECT szEffect[EQUIP_EFFECT_MAX_NUM];
 * //��Ч };
 * ;
 * �߼�װ�����α�
 */
#define TABLE_ITEM_EQUIP_VISUAL	(316)
struct _TABLE_ITEM_EQUIP_VISUAL
{
	table_int_t 				nID;							/* ���� 10010001 */
	table_int_t 				nModelID;						/* ģ��id��������ģ�ͱ����ҵ���Ӧ�ľ���ģ�� */
	LPCTSTR			szName;							/* װ������ ���� xx�� */
	LPCTSTR			szDes;							/* ˵�� ������Ϣ */
	LPCTSTR			szIcon;							/* ͼ�� ui��ʾ�� */
	LPCTSTR			szType;							/* �� */

	LPCTSTR			nDropModelId;					/* ����ʱ������ */
	LPCTSTR			szDropEffect;					/* ����ģ�͸�����Ч */
	table_int_t 				szDropSound;					/* �������� */
	LPCTSTR			szDropVisColor;					/* ��ʾ������ɫ */

	EQUIP_EFFECT	szEffect[EQUIP_EFFECT_MAX_NUM]; /* ��Ч */
	LPCTSTR			szAnimateFrame;					/* ����֡ */

	table_int_t 			nType;							// װ������
};

/*
 * װ��������� �� ��ͨװ���Ż��õ�����Ӧ��װ�������ͨװ�������Ի����-1 ;
 * #define TABLE_ITEM_ATTR_GROUP 322 struct _TABLE_ITEM_ATTR_GROUP { table_int_t nGroupId;
 * // ������Id LPCTSTR szGroupName;
 * // ���������� table_int_t nProbability;
 * // �����鼸�� table_int_t nAttrId[EQUIP_EFFECT_ATTR_MAXNUM];
 * // Ӱ������id ��16�� ��Ӧ��װ�����16�� };
 */
#define EQUIP_LEVEL_MAXNUM	100

/*
 * װ�����Եȼ��� ��ͨװ���Ż��õ��� ;
 * #define TABLE_ITEM_ATTR_LEVEL 321 struct _TABLE_ITEM_ATTR_LEVEL { table_int_t nAttrID;
 * //����id LPCSTR szName;
 * //������ table_int_t nLevel[EQUIP_LEVEL_MAXNUM];
 * //װ��Ӱ������ };
 * ;
 * װ���淨 װ����� ;
 * Equip_HoleReqInfo.ta
 */
#define TABLE_EQUIP_HOLE_INFO 330
#define EQUIP_PART_ON_HOLE	(EQUIP_TYPE_NUM-1)
struct _TABLE_EQUIP_HOLE_INFO
{
	table_int_t nHoleNum;						/* �׵���Ŀ */
	table_int_t nItemNeed[EQUIP_PART_ON_HOLE];	/* ��Ҫ�Ĵ�׵��� */
	table_int_t nItemNeedNum;					/* ��Ҫ�ĵ������� */
	table_int_t nMoneyNeed;						/* ��Ҫ�Ľ�Ǯ���� */
	table_int_t nSuccessRatio;					/* �ɹ��� */
	/*
	 * LPCTSTR szName;
	 * //��������
	 */
};

/*
 * װ���� ;
 * Equip_bind.tab
 */
#define TABLE_EQUIP_BINDING_INFO	331

struct _TABLE_EQUIP_BINDING_INFO
{
	table_int_t nBindingLevel;					/* �󶨼��� */
	table_int_t nIntensifyInfo;					/* ǿ������ */
	table_int_t nGemNeed[MAX_BIND_GEMREQ_NUM];	/* ����ʯ */
	table_int_t nNeedMoney[MAX_BIND_GEMREQ_NUM];	/* �����Ǯ */
	table_int_t nNeedEquipLevel[MAX_BIND_GEMREQ_NUM];	/* �����Ǯװ���ȼ�,�����Ĵ˵ȼ���Ӧ���ߣ�������ĸ߼����ӡ����*/
};

/*
 * װ������ ;
 * Equip_levelup.tab
 */
#define TABLE_EQUIP_ADD_START		332
#define ADD_STAR_GEM_TYPE		5
#define EQUIP_STAR_NUM_LIMIT	15
struct EQUIP_ADD_STAR_INFO
{
	table_int_t nEquipLevelReqGemID[MAX_LEVELUP_GEMREQ_NUM];		//װ���ȼ�����ʯ
	/*
	 * table_int_t nGemIdSave;
	 * //�������� Ԥ��������
	 */
	table_int_t nSuccessRate[MAX_LEVELUP_GEMREQ_NUM];				//�ɹ�����
	table_int_t nPunishment;					/* ʧ�ܳͷ� */
	table_int_t nNeedMoney[MAX_LEVELUP_GEMREQ_NUM];/* �����Ǯ */
	table_int_t nIntensifyInfo;					/* ǿ������ */
	table_int_t nIntensifyType;					/* ǿ��������� */
	table_int_t nNeedPlayerLevel;				/* ��Ҫ������ȼ� */
	table_int_t nStartStepLevel;				/* �Ǽ���Ӧλ */
	table_int_t 	nLevelNeed[MAX_LEVELUP_GEMREQ_NUM];/* �ȼ��� */
};

struct _TABLE_EQUIP_ADD_START
{
	table_int_t 					nIndex;			/* ��� */
	table_int_t 					nStarLevel;		/* �Ǽ� */
	table_int_t 					nEquipPoint;	/* װ���� */
	EQUIP_ADD_STAR_INFO Add_Star_Info[ADD_STAR_GEM_TYPE];
};

/*
 * װ�����ޱ� ;
 * Equip_SpecialRepair.tab
 */
#define TABLE_EQUIP_SP_REPAIR 333

struct _TABLE_EQUIP_SP_REPAIR
{
	table_int_t nDestItemID;					/* ��������ƷID */
	table_int_t nUseItemID;						/* ������ƷID */
	table_int_t nUseItemCount;					/* �ָ��;õ� */
	table_int_t nNeedMoney;						/* �����Ǯ */
};

#define MAX_EQUIP_PROMATL_NUM	4
struct _TABLE_EQUIP_PRO_MAT
{
	table_int_t nMaterial;						/* ������ */
	table_int_t nMaterialNum;					/* �������� */
	table_int_t nMatLowestLv;					/* ������͵�1 */
	table_int_t nMaterialLoss;					/* �����ı���4 */
};

#define MAX_EQUIP_RWMATL_NUM	3		/* ����������� */

struct _TABLE_EQUIP_REWORK_MAT
{
	table_int_t nReWorkMaterial;				/* ����1������ */
	table_int_t nReWorkMatNum;					/* ����1�������� */
	table_int_t nReWorkMatLowestLv;				/* ����1������͵ȼ� */
};

#define MAX_EQUIP_SPIRIT_RWMATL_NUM 3	/* ������������� */

#define TABLE_EQUIP_PRODUCT_INFO		334

struct _TABLE_EQUIP_PRODUCT_INFO
{
	table_int_t 						nFormulaId; /* �䷽�� */
	table_int_t 						nProductId; /* ��ƷID */
	LPCSTR						szFormulaName;		/* �䷽���� */
	table_int_t 						nProductNum;		/* ��Ʒ���� */

	/*
	 * table_int_t nMaterial1;
	 * //������1 ;
	 * table_int_t nMaterial1Num;
	 * //��������1 ;
	 * table_int_t nMat1LowestLv;
	 * //������͵ȼ�1 ;
	 * table_int_t nMaterial1Loss;
	 * //�����ı���1 ;
	 * table_int_t nMaterial2;
	 * //������2 ;
	 * table_int_t nMaterial2Num;
	 * //��������2 ;
	 * table_int_t nMat2LowestLv;
	 * //������͵ȼ�2 ;
	 * table_int_t nMaterial2Loss;
	 * //�����ı���2 ;
	 * table_int_t nMaterial3;
	 * //������3 ;
	 * table_int_t nMaterial3Num;
	 * //��������3 ;
	 * table_int_t nMat3LowestLv;
	 * //������͵ȼ�3 ;
	 * table_int_t nMaterial3Loss;
	 * //�����ı���3 ;
	 * table_int_t nMaterial4;
	 * //������4 ;
	 * table_int_t nMaterial4Num;
	 * //��������4 ;
	 * table_int_t nMat4LowestLv;
	 * //������͵ȼ�4 ;
	 * table_int_t nMaterial4Loss;
	 * //�����ı���4
	 */
	_TABLE_EQUIP_PRO_MAT		szMat[MAX_EQUIP_PROMATL_NUM];

	/*
	 * table_int_t nReWorkMaterial1;
	 * //����1������ ;
	 * table_int_t nReWorkMat1Num;
	 * //����1�������� ;
	 * table_int_t nReWorkMat1LowestLv;
	 * //����1������͵ȼ� ;
	 * table_int_t nReWorkMaterial2;
	 * //����2������ ;
	 * table_int_t nReWorkMat2Num;
	 * //����2�������� ;
	 * table_int_t nReWorkMat2LowestLv;
	 * //����2������͵ȼ� ;
	 * table_int_t nReWorkMaterial3;
	 * //����3������ ;
	 * table_int_t nReWorkMat3Num;
	 * //����3�������� ;
	 * table_int_t nReWorkMat3LowestLv;
	 * //����3������͵ȼ�
	 */
	_TABLE_EQUIP_REWORK_MAT	szRwMat[MAX_EQUIP_RWMATL_NUM];

	table_int_t 						nOperateTime;		/* ����ʱ�� */
	table_int_t 						nScriptId;			/* �ű�ID */
	table_int_t 						nProNeedMoney;		/* �����Ǯ */
	table_int_t 						nReNeedMoney;		/* �����Ǯ */
	table_int_t 						nProLevel;			/* ��Ʒ�ȼ� */
	table_int_t 						nProBodyBelong;		/* �������� */
	table_int_t 						nProAttrBelong;		/* ���Թ��� */

	/*
	 * table_int_t nNpcId;
	 * //npcid
	 */
	LPCSTR						szNpcIdList;
	table_int_t 						nCanSelMatLevel;	/* �Ƿ����ѡ����ϵȼ� */
};

/* MaterialLevel_info.tab */
#define TABLE_EQUIP_MATERIAL_INFO 335

struct _TABLE_EQUIP_MATERIAL_INFO
{
	table_int_t nMaterialGrade;					/* ���ϵȼ� */
	table_int_t nMaterialValues;				/* ���Ϸ�ֵ */
};

/*
 * pai_info.tab ;
 * ÿ����
 */
#define TABLE_EQUIP_CARD_INFO 336

struct _TABLE_EQUIP_CARD_INFO
{
	table_int_t 		nCardId;					/* ��id ��Ӧ��ö�� ���� EQUIPPAI_ANY ������ */
	LPCTSTR		szCardName;					/* ���� */
	table_int_t 		nAttrId;					/* ����id */
	table_int_t 		nAttrNum;					/* ����ֵ */
	table_int_t 		nRata;						/* ���� */
	table_int_t 		nPaiItemId;					/* �ƶ�Ӧ��item id */
};

/*
 * chain_info.tab ;
 * 3������
 */
#define TABLE_EQUIP_CARD_GROUP_INFO	337

struct _TABLE_EQUIP_CARD_GROUP_INFO
{
	table_int_t 		nGroupId;					/* ��id */
	LPCTSTR		sznGroupName;				/* ������� */
	table_int_t 		nNeedCardId1;				/* ��������id */
	table_int_t 		nNeedCardId2;				/* ��������id */
	table_int_t 		nNeedCardId3;				/* ��������id */
	table_int_t 		nAttrId;					/* ǿ������ */
	table_int_t 		nAttrNum;					/* ǿ����ֵ */
	LPCTSTR		szEffect;					/* ��Ч */
};

/*
 * soul_info.tab ;
 * ������ ���ڼ���
 */
#define EQUIP_CARD_ACTIVE_ATTR_NUM	4

struct EQUIP_CARD_ATTR
{
	table_int_t nAttrId;						/* ǿ������ */
	table_int_t nAttrNum;						/* ǿ����ֵ */
};

#define EQUIP_CARD_ACTIVE_EFFECT_NUM	2

struct EQUIP_CARD_EFFECT
{
	LPCTSTR szEffect;					/* ��Ч */
	LPCTSTR szEffectBindPoint;			/* ��Ч�󶨵� */
};

#define TABLE_EQUIP_CARD_ALL	338

struct _TABLE_EQUIP_CARD_ALL
{
	static const table_int_t 	EQUIP_CARD_ALL_Sign_COLUMN = 16;
	table_int_t 					nGroupId;		/* ��id */
	LPCTSTR				sznGroupName;	/* ������� */
	table_int_t 					nSoulType;   /*�������*/
	table_int_t 					nNeedGropId1;	/* �������id */
	table_int_t 					nNeedGropId2;	/* �������id */
	table_int_t 					nNeedGropId3;	/* �������id */
	table_int_t 					nNeedGropId4;	/* �������id */
	table_int_t 					nNeedGropId5;	/* �������id */

	EQUIP_CARD_ATTR		stAttr[EQUIP_CARD_ACTIVE_ATTR_NUM]; /* ǿ������ */
	table_int_t 					nNeedSignEquip;						/* ��Ҫ�ķ��� */
	EQUIP_CARD_EFFECT	stEffect[EQUIP_CARD_ACTIVE_EFFECT_NUM];
};

/*
 * ���Ʊ�� ;
 * ChangePai_info.tab
 */
#define TABLE_EQUIP_CARD_TARGET	339

struct _TABLE_EQUIP_CARD_TARGET
{
	table_int_t 		nId;					/* ����i */
	LPCTSTR szName;					/* ˵�� */
	table_int_t 		nTargetId;				/* Ŀ��id */
	table_int_t 		nNeedMoney;				/* �����Ǯ */
};

/*
 * equipset_attr.tab ;
 * װ����װ��
 */
#define TABLE_EQUIP_SET_INFO	340
#define EQUIP_SET_ATTR_NUM	4

struct EQUIP_SET_ATTR
{
	table_int_t nNeedNum;					/* ��������Ե����� */
	table_int_t nAttrId;					/* ����id */
	table_int_t nAttrNum;					/* ������ֵ */
};
#define EQUIP_SET_EFFECT_NUM	4
struct EQUIP_SET_EFFECT
{
	LPCTSTR szEffectName;			/* ��Ч */
	LPCTSTR szBindPointName;		/* �󶨵� */
};

struct _TABLE_EQUIP_SET_INFO
{
	table_int_t 					nSetId;		/* ��װid */
	LPCTSTR				szSetName;	/* ��װ���� */
	table_int_t 					nSetNum;	/* ��װ���� */
	LPCTSTR				szId;		/* ��װ������ϵ��id */
	EQUIP_SET_ATTR		stAttr[EQUIP_SET_ATTR_NUM]; /* ��װ���� */
	EQUIP_SET_EFFECT	stEffect[EQUIP_SET_EFFECT_NUM];
};
#define TABLE_EQUIP_IMPACT		341					/* buff_logic.tab */
#define IMPACT_PARAM_MAX_NUM	16
struct _TABLE_EQUIP_IMPACT
{
	/* �ڱ���ж�Ӧ�ļ�¼������ */
	table_int_t 		m_nDataIndex;

	/* ���� */
	LPCTSTR m_szName;
	LPCTSTR m_szParamDes[IMPACT_PARAM_MAX_NUM * 2];

	/*
	 * �ڱ���ж�Ӧ�ļ�¼������ ;
	 * table_int_t m_nDataIndex;
	 * ��Ӧ�ļ���ID ;
	 * table_int_t m_nLogicID;
	 * û�� ���� ;
	 * LPCTSTR m_szName;
	 * ���� ;
	 * LPCTSTR m_szLogicDesc;
	 * û�� �Ƿ�Ϊ������Ч�� ;
	 * table_int_t m_bIsOverTimed;
	 * û�� ˲����פ��Ч��ID ;
	 * table_int_t m_nImpactID;
	 * û�� ������ID ;
	 * table_int_t m_nMutexID;
	 * û�� �������ȼ� ;
	 * table_int_t m_nLevel;
	 * û�� Ӱ������ ;
	 * table_int_t m_nStandFlag;
	 * û�� �����Ƿ��� ;
	 * table_int_t m_bRemainOnCorpse;
	 * û�� �Ƿ���Ա�������ɢ ;
	 * table_int_t m_bCanBeDispeled;
	 * û�� �Ƿ���Ա��ֶ�ȡ�� ;
	 * table_int_t m_bCanBeCanceled;
	 * û�� �Ƿ���Ҫ����֧�� ;
	 * table_int_t m_bNeedChannelSupport;
	 * û�� �Ƿ���ֱͨЧ��,����������Ӱ�� ;
	 * table_int_t m_bIgnoreFliter;
	 * û�� �ܵ��˺�ʱ�Ƿ���ʧ ;
	 * table_int_t m_bFadeOutWhenUnitOnDamage;
	 * û�� ��ʼ����ʱ�Ƿ���ʧ ;
	 * table_int_t m_bFadeOutWhenUnitStartActions;
	 * û�� ���߾���ʧ�� ;
	 * table_int_t m_bFadeOutWhenUnitOffline;
	 * û�� �����Ƿ���Ȼ��ʱ ;
	 * table_int_t m_bStillTimingWhenUnitOffline;
	 * û�� �ܳ���ʱ��(����) ;
	 * table_int_t m_nContinuance;
	 * û�� ����ʱ����(����) ;
	 * table_int_t m_nInterval;
	 * û�� ��������Ƿ�ο�������ID ;
	 * table_int_t m_bMutexByCaster;
	 * û�� Ԥ�� 2 3 4 5 ;
	 * table_int_t m_nSaved[4];
	 * û�� LPCTSTR m_szParamDes[IMPACT_PARAM_MAX_NUM *2];
	 * ����ֵ ;
	 * LPCTSTR m_szParaValue;
	 * û�� Ч������ ;
	 * LPCTSTR m_szDescription;
	 * û�� ��֪��ͬ�༼����Ҫ���ӵ����� ;
	 * table_int_t m_uBallCount;
	 * û�� �ӵ����������� ;
	 * table_int_t m_uBallLife;
	 * û��
	 */
};

/*
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-// ;
 * ������� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * �����ļ����� (SOUND_0
 */
#define TABLE_SOUND_INFO	(401)
struct _TABLE_SOUND_INFO
{
	table_int_t 		nID;
	LPCSTR	pSoundFile;
};

/*
 * ��Ч��� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * ��Ч���� (EFFECT_01) #define TABLE_EFFECT_DEFINE (501) ;
 * struct _TABLE_EFFECT_DEFINE // bc ;
 * { ;
 * table_int_t nID;
 * LPCSTR pEffectType;
 * LPCSTR pParam1;
 * LPCSTR pParam2;
 * LPCSTR pParam3;
 * LPCSTR pParam4;
 * LPCSTR pParam5;
 * LPCSTR pParam6;
 * };
 * ;
 * ������� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * �츳����� (SKILL_01) #define TABLE_SKILL_TALENT (601) ;
 * struct _TABLE_SKILL_TALENT // bc ;
 * { ;
 * table_int_t nID;
 * LPCSTR pszName;
 * table_int_t nMenpaiID;
 * LPCSTR pszDesc;
 * LPCSTR pszIconName;
 * };
 * ����Ч�� (SKILL_02) #define TABLE_SKILL_ADDIMPACT (602) ;
 * struct _TABLE_SKILL_ADDIMPACT // bc ;
 * { ;
 * table_int_t nID;
 * table_int_t nParamNum;
 * LPCSTR pDesc;
 * table_int_t nAddAttributeNum;
 * LPCSTR pAddAttribute1;
 * LPCSTR pAddAttribute2;
 * LPCSTR pAddAttribute3;
 * LPCSTR pAddAttribute4;
 * table_int_t nSpliceID;
 * LPCSTR pIcon;
 * };
 * ;
 * �ӵ�Ч������ (SKILL_03) #define TABLE_SKILL_BULLET (603) ;
 * struct _TABLE_SKILL_BULLET ;
 * { ;
 * table_int_t nID;
 * //�ӵ����� ;
 * table_int_t nType;
 * /* ;
 * | 0 - ˲�䵽�� ;
 * | 1 - �ƶ����� ;
 */
#define TABLE_BUFF_IMPACT (604)

/* TABLE_BUFF_IMPACT DIRECTLY����Ч�� (DIRECTLY_IMPACT) */
#define TABLE_DIRECTLY_IMPACT (605)

/* TABLE_DIRECTLY_IMPACT �ӵ� (BULLET) */
#define TABLE_BULLET_DATA (606)

/* TABLE_BULLET_DATA ���� (SKILL) */
#define TABLE_SKILL_DATA	(607)

#define TABLE_SPECIAL_OBJ_DATA	(610)
struct _TABLE_SPECIAL_OBJ_DATA						/* cd */
{
	table_int_t 		m_nID;						/* ID */
	LPCSTR		m_lpszName;					/* ���� */
	table_int_t 		m_nType;					/* ��𣨷�����ר�ã� */
	LPCSTR		m_lpszToolTips;				/* ToolTips */
	table_int_t 		m_nLogicID;					/* �߼�ID��������ר�ã� */
	table_int_t 		m_nStealthLevel;			/* ���μ��𣨷�����ר�ã�����ר�ã� */
	table_int_t 		m_nTrapFlags;				/* ������λ���ϣ�������ר�ã�����ר�ã� */
	table_int_t 		m_nActiveTimes;				/* ���Լ����Ĵ�����������ר�ã� */
	LPCSTR		m_lpszEffect_Normal;		/* �����ڳ�����Ч */
	LPCSTR		m_lpszSound_Normal;			/* �����ڳ�����Ч */
	LPCSTR		m_lpszEffect_Active;		/* ������Ч */
	LPCSTR		m_lpszSound_Active;			/* ������Ч */
	LPCSTR		m_lpszEffect_Die;			/* ������Ч */
	LPCSTR		m_lpszSound_Die;			/* ������Ч */
	table_int_t 		m_nReserve1;				/* Ԥ�� */
	table_int_t 		m_nReserve2;				/* Ԥ�� */
	table_int_t 		m_nReserve3;				/* Ԥ�� */
	table_int_t 		m_nBulletID;				/* �ӵ�ID */
	table_int_t 		m_nDuration;				/* ����ʱ�䣨������ר�ã� */
	table_int_t 		m_nInterval;				/* ����򴥷�ʱ������������ר�ã� */
	table_float_t 		m_nTriggerRadius;			/* �����뾶��������ר�ã�����ר�ã� */
	table_float_t 		m_nEffectRadius;			/* Ӱ��뾶��������ר�ã�����ר�ã� */
	table_int_t 		m_nEffectUnitNum;			/* Ӱ�������Ŀ��������ר�ã�����ר�ã� */
	table_int_t 		m_nReserve4;				/* Ԥ�� */
	table_int_t 		m_nReserve5;				/* Ԥ�� */
	table_int_t 		m_nReserve6;				/* Ԥ�� */
	table_int_t 		m_nReserve7;				/* Ԥ�� */
	table_int_t 		m_nReserve8;				/* Ԥ�� */
	LPCSTR		m_lpszParamDesc0;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam0;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc1;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam1;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc2;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam2;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc3;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam3;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc4;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam4;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc5;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam5;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc6;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam6;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc7;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam7;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc8;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam8;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc9;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam9;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc10;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam10;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc11;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam11;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc12;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam12;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc13;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam13;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc14;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam14;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszParamDesc15;			/* ����˵����������ר�ã� */
	table_int_t 		m_nParam15;					/* ����ֵ��������ר�ã� */
	LPCSTR		m_lpszInfo;					/* ��ϸ˵��(�ڲ�ʹ��) */
};

/* ���� (QUEST) */
#define TABLE_QUEST_DELIVERY	(620)
struct _TABLE_QUEST_DELIVERY
{
	table_int_t nQuestIndex;
	table_int_t nDeliveryItemID1;
	table_int_t nDeliveryItemNum1;
	table_int_t nDeliveryItemID2;
	table_int_t nDeliveryItemNum2;
	table_int_t nDeliveryItemID3;
	table_int_t nDeliveryItemNum3;
};

#define TABLE_QUEST_ENTERAREA	(621)
struct _TABLE_QUEST_ENTERAREA
{
	table_int_t 		nQuestIndex;
	LPCSTR		szAreaName;
	table_int_t 		nAreaSceneID;
	table_int_t 		nAreaID;
	table_int_t 		nAreaIndex;
	LPCSTR		szEnterArea;
	table_int_t 		nIfHaveDialog;
	LPCSTR		szEnterAreaDialog;
};

#define TABLE_QUEST_KILLMONSTER (622)
struct _TABLE_QUEST_KILLMONSTER
{
	table_int_t 		nQuestIndex;
	table_int_t 		nMonsterSceneID;
	LPCSTR		szMonsterName;
	LPCSTR		szMonsterTitle;
	table_int_t 		nMonsterType;
	table_int_t 		nMonsterLevelMin;
	table_int_t 		nMonsterLevelMax;
	table_int_t 		nCourseIndex;
	table_int_t 		nKillNum;
};

#define TABLE_QUEST_LOOTITEM	(623)
struct _TABLE_QUEST_LOOTITEM
{
	table_int_t 		nQuestIndex;
	table_int_t 		nLookItemType;
	table_int_t 		nItemID1;
	table_int_t 		nItemNum1;
	table_int_t 		nGrowPointType;
	table_int_t 		nCollectNum;
	table_int_t 		nMonsterSceneID;
	LPCSTR		szMonsterName;
	LPCSTR		szMonsterTitle;
	table_int_t 		nMonsterType;
	table_int_t 		nMonsterLevelMin;
	table_int_t 		nMonsterLevelMax;
	table_int_t 		nCourseIndex;
	table_int_t 		nDropRand;
	table_int_t 		nMaxDropNum;
};

#define TABLE_QUEST_USEITEM (624)
struct _TABLE_QUEST_USEITEM
{
	table_int_t 		nQuestIndex;
	table_int_t 		nUseItemType;
	table_int_t 		nItemID1;
	LPCSTR		szSceneID;
	table_int_t 		nPosX;
	table_int_t 		nPosZ;
	table_int_t 		nRadius;
	table_int_t 		nSkillID;
	LPCSTR		szUseItemDesc;
	table_int_t 		nUseDialog;
	LPCSTR		szUseItemDialog;
};

#define TABLE_QUEST_LIST	(625)
struct _TABLE_QUEST_LIST
{
	table_int_t 		nQuestID;					/* QuestID */
	table_int_t 		nScriptID;					/* ScriptID */
	table_int_t 		nQuestType;					/* �������� 0:��ͨ������� 1:�������� 2:ѭ������ Add CZG */
	LPCSTR		szQuestName;				/* �������� */
	LPCSTR		szQuestDisp;				/* �������� */
	table_int_t 		nPreQuestID1;				/* ǰ������ */
	table_int_t 		nPreQuestID2;				/* ǰ������ */
	table_int_t 		nPreQuestID3;				/* ǰ������*/
	table_int_t 		nMinLevel;					/* Min�ȼ� */
	table_int_t 		nMaxLevel;					/* Max�ȼ� */
	table_int_t 		nNeedMoneyType;				/* �������Ǯ�������� */
	table_int_t 		nNeedMoney;					/* �������Ǯ���� */
	table_int_t 		nCountry;					/* ����:0-3,��Ӧ����; -1�޹�������; */
	table_int_t 		nProfession;				/* ְҵ:0-5,��Ӧְҵ;-1��ְҵ����;*/
	table_int_t 		nCamp;						/* ��Ӫ */
	table_int_t 		nQuestDest1;				/* Ŀ������ */
	table_int_t 		nQuestDest2;				/* Ŀ������ */
	table_int_t 		nQuestDest3;				/* Ŀ������ */
	table_int_t 		nQuestDest4;				/* Ŀ������ */
	table_int_t 		nQuestDest5;				/* Ŀ������ */
	table_int_t 		nMoneyRewardType;			/* �̶���Ǯ�������� */
	table_int_t 		nMoneyRewardP1;				/* �̶���Ǯ���� */
	table_int_t 		nMoneyRewardP2;				/* �̶���Ǯ���� */
	table_int_t 		nMoneyRewardP3;				/* �̶���Ǯ���� */
	table_int_t 		nExpRewardP1;				/* �̶����齱�� */
	table_int_t 		nExpRewardP2;				/* �̶����齱�� */
	table_int_t 		nExpRewardP3;				/* �̶����齱�� */
	table_int_t 		nShengWangType;				/* �������� 0��͢���� 1�������� 2PKֵ 3��������ѫ�� 4�ﹱ 5�Ĳ� 6 ���� 7 �츳���� */
	table_int_t 		nShengWangRewartP1;
	table_int_t 		nShengWangRewartP2;
	table_int_t 		nShengWangRewartP3;
	table_int_t 		nEnergyRewardType;
	table_int_t 		nEnergyReward;
	table_int_t 		nGuildRewardType;
	table_int_t 		nGuildReward;
	table_int_t 		nFixItemID1;				/* �̶���Ʒ����ID */
	table_int_t 		nFixItemNum1;				/* �������� */
	table_int_t 		nFixItemID2;
	table_int_t 		nFixItemNum2;
	table_int_t 		nFixItemID3;
	table_int_t 		nFixItemNum3;
	table_int_t 		nFixItemID4;
	table_int_t 		nFixItemNum4;
	LPCSTR		szSelItemID1;				/* �����Ʒ����ID */
	table_int_t 		nSelItemNum1;				/* �������� */
	table_int_t 		nSelItemID2;
	table_int_t 		nSelItemNum2;
	table_int_t 		nSelItemID3;
	table_int_t 		nSelItemNum3;
	table_int_t 		nSelItemID4;
	table_int_t 		nSelItemNum4;
	table_int_t 		nSelItemID5;
	table_int_t 		nSelItemNum5;
	table_int_t 		nSelItemID6;
	table_int_t 		nSelItemNum6;
	table_int_t 		nRewardScript;				/* �Ƿ񻹵��ýű�������0������1�����ö�Ӧscriptid�ű� */
	LPCSTR		szQuestDesc;				/* �������� */
	LPCSTR		szQuestManual;				/* ������ */
	LPCSTR		szQuestContinue;			/* �������� */
	LPCSTR		szQuestAbandon;				/* �������� */
	LPCSTR		szQuestSuccess;				/* ������� */
	table_int_t 		nSubmitNPCGUID;				/* ������NPC��GUID */
	LPCSTR		szSubmitNPCName;			/* ������NPC���� */
	table_int_t 		nSubmitNPCSceneID;			/* ������NPC���ڵ�ͼID */
	table_int_t 		nPathIndex;					/* �Զ�Ѱ·����(scenemap_npc.tab�ж�Ӧ��index),-1Ϊ�� */
	table_int_t 		nAfterQuestType;			/* �����Զ��������� */
	table_int_t 		nAfterQuestScriptID;		/* �����Զ��������ScriptID */

	LPCSTR		szQuestTarget1;				/* ����Ŀ��1 */
	LPCSTR		szQuestTarget2;				/* ����Ŀ��2 */
	LPCSTR		szQuestTarget3;				/* ����Ŀ��3 */
	LPCSTR		szQuestTarget4;				/* ����Ŀ��4 */
	LPCSTR		szQuestTarget5;				/* ����Ŀ��5 */

	LPCSTR		szQuestHelp;				/* ������� */

	table_int_t 		nSyncServerFlag;			/* ��������ͬ����ǣ����Ϊ1��ʾҪ�ӷ�������ͬ�����ݡ�����ʹ�ÿͻ������� */
	table_int_t 		nTechuFlag;					/* �������⴦����*/
	table_int_t 		nAcceptIconFlag;			/* ������ͼ���� */
};

/*
 * ���������� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * �������� (SCENE_01)
 */


#define TABLE_SCENE_DEFINE	(701)
struct _TABLE_SCENE_DEFINE				/* cd */
{
	static const table_int_t 	SCENE_SERVER_ID_COLUMN = 1;

	table_int_t					nLocalID;
	table_int_t					nServerID;
	LPCSTR					szName;
	table_int_t					nXSize;
	table_int_t					nZSize;
	LPCSTR					szSceneName;
	table_int_t					nBackSound;
	LPCSTR					szSceneMap;
	table_int_t					nWroldMapPosX;
	table_int_t					nWroldMapPosY;				/* ����ͼ�����ڵ�λ�� */
	table_int_t					nNameWroldMapPosX;
	table_int_t					nNameWroldMapPosY;			/* �����������ڵ�λ�� */
	LPCSTR					szSceneType;				/* ������ͼ��ȼ� */
	LPCSTR					szCityNameNormalImageSet;	/* ���������������õ�ͼƬ��Դ */
	LPCSTR					szCityNameNormalImage;		/* ���������������õ�ͼƬ��Դ */
	LPCSTR					szCityNameHoverImageSet;	/* ���������������õ�ͼƬ��Դ */
	LPCSTR					szCityNameHoverImage;		/* ���������������õ�ͼƬ��Դ */
	LPCSTR					szTransImg;					/* �����л�ͼ */
	table_int_t					nSceneType;					/* �������ͣ���(0)����ս(1)������(2) */
	table_int_t					nCountryID;					/* ��������ID */
	table_int_t					nNameColorType;				/* �жϸó�����������ʾ���� */
	LPCSTR					szSceneOriginColorIDList;	// ����ԭɫ��ʶ sceneColor.tab
	table_int_t					nPKType;					// PK����
};

/*
 * ���������ﶨ�� (SCENE_02) #define TABLE_BUILDING_DEINFE (702) ;
 * struct _TABLE_BUILDING_DEFINE // bc ;
 * { ;
 * static const table_int_t MAX_LEVEL = 5;
 * ;
 * table_int_t nID;
 * // ��Դid ;
 * LPCSTR szResType;
 * // ��Դ���� ;
 * LPCSTR szLevel[MAX_LEVEL];
 * // �ȼ�1-5��Դ ;
 * };
 * ���н����ﶨ�� (SCENE_03) #define TABLE_CITY_BUILDING (703) ;
 * struct _TABLE_CITY_BUILDING // de ;
 * { ;
 * table_int_t nID;
 * // id ;
 * table_int_t nCityID;
 * // ����id(TABLE_CITY_DEINFE) ;
 * table_int_t nBuildingID;
 * // ������id(TABLE_BUILDING_DEINFE) ;
 * LPCSTR szGfxPosition;
 * // λ��(gfx) ;
 * table_int_t nInitLevel;
 * // ��ʼ�ȼ� ;
 * LPCSTR szGfxOrientation;
 * // ��ת��Ԫ��(gfx) ;
 * };
 * �������͵㶨�� (SCENE_02
 */
#define TABLE_SCENE_POS_DEFINE	(917)
struct _TABLE_SCENE_POS_DEFINE
{
	table_int_t 		nID;					/* id */
	table_int_t 		nSceneID;				/* ������id */
	LPCSTR		szSceneName;			/* ���������� */
	table_int_t 		nXPos;					/* ���͵��λ�� */
	table_int_t 		nZPos;					/* ���͵��λ�� */
	table_int_t 		nTargetSceneID;			/* Ŀ�곡����id */
	LPCSTR		szTargetSceneName;		/* Ŀ�곡�������� */
	table_int_t 		nTargetXPos;			/* Ŀ�괫�͵��λ�� */
	table_int_t 		nTargetZPos;			/* Ŀ�괫�͵��λ�� */
	table_int_t 		nType;					/* ���͵����� */
};

/* ���͵�·�� */
#define TABLE_SCENE_TRANS_DEFINE	(802)
struct _TABLE_SCENE_TRANS_DEFINE		/* scene_trans_path.tab */
{
	table_int_t 		nID;					/* id */
	table_int_t 		nSrcSceneID;			/* Դ���� */
	table_int_t 		nTarSceneID;			/* Ŀ�곡�� */
	LPCSTR	szTransPath;			/* ·���㣬 ��Ӧ�����͵�� */
};

/*
 * UI��� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * UI�鶨�� (UI_0
 */
#define TABLE_UI_LAYOUTDEFINE (801)
struct _TABLE_UI_LAYOUTDEFINE			/* de */
{
	table_int_t 		nID;
	LPCSTR	szName;
	LPCSTR	szLayout;
	table_int_t 		nDemise;
	LPCSTR	szScript;
	table_int_t 		nEscPriority;			/* ESC���ȼ� */

	/* ������� */
	table_int_t 		nOverlay;				/* �ܷ񸲸� */
	table_int_t 		nBeOverlay;				/* �ܷ񱻸��� */
	table_int_t 		nMouseLock;				/* ����� */
	table_int_t 		nKeyLock;				/* ������ */
	table_int_t 		nChatLock;				/* ������ */

	LPCSTR	szDefaultPos;			/* Ĭ�ϴ򿪴��ڵ�λ�á� */
	table_int_t 		nCloseDistance;			/* �Զ��رվ��� */

	/* ��Ч */
	table_int_t 		nOpenWindowSound;		/* �򿪴�����Ч */
	table_int_t 		nCloseWindowSound;		/* �رմ�����Ч */
};

/*
 * �������� // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * ��Դ������ (LIFE_01
 */
#define TABLE_LIFEABILITY_GROWPOINT	(901)
struct _TABLE_LIFEABILITY_GROWPOINT	/* cd */
{
	table_int_t 		nID;					/* ��� */
	LPCSTR	szName;					/* ���� */
	table_int_t 		nLifeAbility;			/* ���ܱ�� */
	LPCSTR	szMeshFile;				/* ģ���ļ� */
	table_int_t 		nQuestID;				/* ��Ӧ����ID CZG */
	LPCSTR	szTips;					/* Ĭ����ʾ */
	table_int_t 		nTimeNeed;				/* �ɼ�ʱ�� */

	/*
	 * LPCSTR szNotcare[4];
	 */
	table_int_t 		nScriptID;				/* �ű�ID CZG */
	table_int_t 		nAnimOpen;				/* �򿪶��� */
	LPCSTR	szEffect;				/* ��Ч CZG */
	LPCSTR	szQuestId;			/* ����ID */
};

/* ����� (LIFE_02) */
#define TABLE_LIFEABILITY_DEFINE	(902)
struct _TABLE_LIFEABILITY_DEFINE		/* bc */
{
	table_int_t 		nID;
	table_int_t 		nLevelNeed;
	LPCSTR	szName;
	table_int_t 		nLevelMax;
	table_int_t 		nTimeOperation;			/* �ɼ�����ʱ�� */
	table_int_t 		nToolNeed;				/* �ɼ����蹤�� */
	table_float_t 	fPlatformDist;			/* �������� */
	table_int_t 		nPlatformID;			/* ����ƽ̨ */
	table_int_t 		nAnimOperation;			/* ���ﶯ�� */
	LPCSTR	szExpTableName;			/* ����������Ӧ�ı�client������ */
	LPCSTR	szIconName;				/* ͼ�� */
	table_int_t 		nItemVisualLocator;		/* �����ҽ� */
	LPCSTR	szExplain;				/* ��ϸ���� */
	table_int_t 		nPopup;					/* �Ƿ񵯳��¼����� */
	LPCSTR	szProgressbarName;		/* ���������� */
};

/* ����� ��Ʒ�ϳ� (LIFE_03) */
#define TABLE_LIFEABILITY_ITEMCOMPOSE (903)
struct _TABLE_LIFEABILITY_ITEMCOMPOSE /* bc */
{
	table_int_t 		nID;
	LPCSTR	szName;
	table_int_t 		nResultID;
	table_int_t 		nResultNum;
	table_int_t 		nLifeAbility;
	table_int_t 		nLifeAbility_Level;
	table_int_t 		nStuff1ID;
	table_int_t 		nStuff1num;
	table_int_t 		nStuff2ID;
	table_int_t 		nStuff2num;
	table_int_t 		nStuff3ID;
	table_int_t 		nStuff3num;
	table_int_t 		nStuff4ID;
	table_int_t 		nStuff4num;

	/*
	 * table_int_t nStuff5ID;
	 * table_int_t nStuff5num;
	 */
	table_int_t 		nCostVigor;

	/*
	 * table_int_t nAttribute_ID1;
	 * table_int_t nAttribute_Level1;
	 * table_int_t nAttribute_ID2;
	 * table_int_t nAttribute_Level2;
	 */
	table_int_t 		nCoolDown_Time;
	table_int_t 		nFacility;				/* ��Ҫ�Ĺ��� */
	table_int_t 		nCoolDoon_Troop;		/* ��ȴ�� */

	/*
	 * table_int_t nProficiencyRequire;
	 * // ����������
	 */
	table_int_t 		nProficiencyIncrease;	/* ���������� */

	/*
	 * table_int_t NOTCARE;
	 * // �����ĵ�1��
	 */
	table_int_t 		nProficiencyTime;		/* �䷽ʱ�� */
	table_int_t 		nScriptID;				/* �ű�ID */

	/*
	 * table_int_t nFailItem;
	 * // ʧ�ܺ�����Ʒ
	 */
	LPCSTR	szExplain;				/* ��ϸ���� */
	LPCTSTR szTypeName;				/* �䷽�������ṹ�еķ������� */

	/*
	 * ���ܷ��� ;
	 * NOT CARE...
	 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ����� ����ƽ̨ (LIFE_04) #define TABLE_LIFEABILITY_PLATFORM (904) ;
    struct _TABLE_LIFEABILITY_PLATFORM // bc ;
    { ;
    table_int_t nID;
    LPCSTR szName;
    table_int_t nType;
    LPCSTR szMeshFile;
    table_int_t nClickType;
    };
    �������ɫת���ַ� #define TABLE_CODE_CONVERT ( 905 ) ;
    struct _TABLE_CODE_CONVERT // bc ;
    { ;
    table_int_t nID;
    // ID ;
    LPCSTR szCode;
    // �ַ�����ʽ��ʮ���������� ;
    LPCSTR szName;
    // ���� ;
    };
    �츳���� (XINFA_02) #define TABLE_TALENT_TALENTDEFINE (902) ;
    struct _TABLE_TALENT_TALENTDEFINE ;
    { ;
    table_int_t nID;
    // �츳ID ;
    table_int_t nIDMenpai;
    // ְҵID ;
    LPCSTR szName;
    // �츳���� ;
    LPCSTR szTips;
    // �츳���� ;
    LPCSTR szIconName;
    // ͼ������ ;
    };
    �츳�������� (XINFA_02)
 -----------------------------------------------------------------------------------------------------------------------
 */
struct Spend
{
	table_int_t dwSpendMoney;									/* ��Ҫ���ѵĽ�Ǯ�� */
	table_int_t dwSpendExperience;								/* ��Ҫ���ѵľ���ֵ */
};

/*
 * define TABLE_TALENT_STUDYSPEND (907) ;
 * struct _TABLE_TALENT_STUDYSPEND ;
 * { ;
 * table_int_t nStudyLevel;
 * // Ҫѧϰ�ĵȼ� ;
 * Spend StudySpend[54];
 * };
 * �ƺ��б� (TITLE) ;
 * #define TABLE_TITLE_NAME (908) struct _TABLE_TITLE_NAME // bc { table_int_t nTitleIndex;
 * // �ƺŵ����� LPCSTR szTitle;
 * // �ƺŵ����� utable_int_t nReserve;
 * // ���ͱ��� LPCSTR szTitleDesc;
 * // �ƺŵ����� };
 */
#define TABLE_TITLE	(908)								/* title_info.tab */
struct _TABLE_TITLE
{
	enum _TITLE_KIND
	{
		KIND_QUEST= 1,								/* ����ƺ� */
		KIND_GUT,										/* ����ƺ� */
		KIND_SPECIAL,									/* ����ƺ� */
	};

	table_int_t 		nId;										/* �ƺ�ID */
	table_int_t 		nType;										/* TYPE */
	LPCSTR	szColor;									/* ��ʾ��ɫ */
	table_int_t 		bShow;										/* Ĭ���Ƿ���ʾ */
	LPCSTR	szManTitle;									/* ���Գƺ� */
	LPCSTR	szWomanTitle;								/* Ů�Գƺ� */
	LPCSTR	szTitleDesc;								/* �ƺ����� */
	table_int_t 		nTimeLimit;									/* �ƺ�ʱ�� */
	LPCSTR	szAcquireDesc;								/* ��ȡ;�� */
	table_int_t 		nEffectId;									/* Ч��ID */
	LPCSTR	szReclaimCause;								/* ����ԭ�� */
	table_int_t 		nCombinationId;								/* ��ϳƺ�ID */
	table_int_t 		nKind;										/* ���ࣺ���񣬾��飬���� */
};

#define TABLE_COMBIN_TITLE	(977)
struct _TABLE_COMBIN_TITLE								/* title_combination.tab */
{
	table_int_t 					nGroupId;						/* title_inof.tab����ϳƺ�id */
	table_int_t 					nCombinId;						/* ��ϳƺ�id */
	table_int_t 					nId1;							/* ����Ҫ��10���ƺ�id */
	table_int_t 					nId2;
	table_int_t 					nId3;
	table_int_t 					nId4;
	table_int_t 					nId5;
	table_int_t 					nId6;
	table_int_t 					nId7;
	table_int_t 					nId8;
	table_int_t 					nId9;
	table_int_t 					nId10;
	const static table_int_t 	COMBIN_TITLE_NUMBER = 10;
};

/* ��Ӫ���� */
#define TABLE_CAMP_DATA	(909)

/*
 * ���� skillData_v1.txt(��ȡ��) #define TABLE_SKILLDATA_V1_DEPLETE (910) ;
 * struct _TABLE_SKILLDATA_V1_DATA_PAIR ;
 * { ;
 * table_int_t nData;
 * LPCSTR szDesc;
 * ;
 * };
 * struct _TABLE_SKILLDATA_V1_DEPLETE // cd ;
 * { ;
 * table_int_t nId;
 * // ID ;
 * table_int_t nCeHuaId;
 * // �߻�ר��ID ;
 * table_int_t nSkillLogicid;
 * // �����߼�ID ;
 * LPCSTR szEffectDesc;
 * // Ч���ļ�Ҫ�߼�˵�� ;
 * table_int_t nCooldownTime;
 * // ��ȴʱ�� ;
 * table_int_t nJuqiTime;
 * // ����ʱ��(ms) ;
 * table_int_t nDirectTime;
 * // ����ʱ��(ms) ;
 * LPCSTR szCondition1Desc;
 * // ���������Ĳ���˵�� ;
 * table_int_t nCondition11;
 * // ���������Ĳ���ֵ ;
 * table_int_t nCondition12;
 * // ���������Ĳ���ֵ ;
 * LPCSTR szCondition2Desc;
 * // ���������Ĳ���˵�� ;
 * table_int_t nCondition21;
 * // ���������Ĳ���ֵ ;
 * table_int_t nCondition22;
 * // ���������Ĳ���ֵ ;
 * LPCSTR szCondition3Desc;
 * // ���������Ĳ���˵�� ;
 * table_int_t nCondition31;
 * // ���������Ĳ���ֵ ;
 * table_int_t nCondition32;
 * // ���������Ĳ���ֵ ;
 * LPCSTR szCondition4Desc;
 * // ���������Ĳ���˵�� ;
 * table_int_t nCondition41;
 * // ���������Ĳ���ֵ ;
 * table_int_t nCondition42;
 * // ���������Ĳ���ֵ ;
 * LPCSTR szCondition5Desc;
 * // ���������Ĳ���˵�� ;
 * table_int_t nCondition51;
 * // ���������Ĳ���ֵ ;
 * table_int_t nCondition52;
 * // ���������Ĳ���ֵ ;
 * LPCSTR szCondition6Desc;
 * // ����˵�� ;
 * ;
 * // ������ ;
 * _TABLE_SKILLDATA_V1_DATA_PAIR paraPair[12];
 * ;
 * LPCSTR Skill_Desc_Interface;
 * ;
 * };
 */
#define TABLE_QUEST_KIND	(911)
struct _TABLE_QUEST_KIND
{
	table_int_t 	nIndex;										/* ������������� */
	LPCSTR	szKindName;									/* ������������� */
};

/* ����NPC��Ϣ */
#define TABLE_QUEST_INFO	(930)
struct _TABLE_QUEST_INFO
{
	table_int_t 		nIndex;
	LPCSTR	nNpcName;
	LPCSTR	szDefault;
	table_int_t 		nScript;
	LPCSTR	szEventList;
	LPCSTR	szEventList1;
	LPCSTR	szEventList2;
	LPCSTR	szEventList3;
	LPCSTR	szEventList4;
	table_int_t 		nFunctionType;
	LPCSTR	szSpeakSoundId;
};

/* �������ɫת���ַ� */
#define TABLE_STRING_DICT (912)
struct _TABLE_STRING_DICT									/* bc */
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szString;									/* �ַ��� */
	LPCSTR	szKey;										/* �ؼ��� */
};

/* ������Ч�б� */
#define TABLE_ENV_SOUND	(913)
struct _TABLE_ENV_SOUND
{
	table_int_t 		nID;										/* ID */
	table_int_t 	nSoundID;									/* ��ЧID */
	table_int_t 	nXPos;										/* ��Դ��X���� */
	table_int_t 	nZPos;										/* ��Դ��Z���� */
	table_int_t 	nDistance;									/* ������������������ */
	table_int_t 		n1;											/* �������� nRepeatTimes */
	table_int_t 		n2;											/* ���ʱ��(ms) nRepeatIntervalTime */
	table_int_t 		n3;											/* ��һ���������ʱ��(ms) nNextRepeatTime */
};

/* ��Ʒ����� */
#define TABLE_ITEM_RULE	(914)
struct _TABLE_ITEM_RULE									/* bc */
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szName;										/* �������� �������� �߻��� */
	table_int_t 		bCanOverLay;								/* �Ƿ���ص� */
	table_int_t 		bCanDrop;									/* �Ƿ�ɶ��� */
	table_int_t 		bCanQuick;									/* �Ƿ�ɷ������� */
	table_int_t 		bCanSale;									/* �Ƿ���Գ��۸�NPC�̵� */
	table_int_t 		bCanExchange;								/* �Ƿ���Խ��� */
	table_int_t 		bCanUse;									/* �Ƿ����ʹ�� */
	table_int_t 		bPickBind;									/* �Ƿ���ʰȡ� */
	table_int_t 		bEquipBind;									/* �Ƿ���װ��� */
	table_int_t 		bUnique;									/* �Ƿ���Ψһ */
	table_int_t 		bCheck;										/* �Ƿ���Ҫ���� */
	table_int_t 		bUnRealItem;								/* �Ƿ���������� */
	table_int_t 		bAccessInBack;								/* �Ƿ�ɴ������� */
	table_int_t 		bWearOut;									/* �Ƿ����� */
};

/* ���˴ʴʻ�� */
#define TABLE_TALK_FILTER (915)
struct _TABLE_TALK_FILTER
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szString;									/* ���˴ʻ㣨��������˵�Ĵʻ㣩 */

	/*
	 * ���˹��� ;
	 * 0��ʾ���ԣ�1��ʾ���о͹��ˣ�2��ʾ��ȫƥ���?
	 */
	table_int_t 		chatFilter;									/* ����ʱ���� */
	table_int_t 		roleFilter;									/* ��������ʱ���� */
	table_int_t 		nameFilter;									/* ����ʱ���� */
	table_int_t 		stallFilter;								/* ��̯ʱ���� */
	table_int_t 		otherFilter;								/* ����������ʹ�� */
	table_int_t 		darkFilter;									/* ģ�����˸ô��� */
	table_int_t 		findPlayerItemFilter;						/* ׷�ٷ����� */
};

/* �ȼ���Ǯ��Ӧ�� */
#define TABLE_LV_MAXMONEY (916)
struct _TABLE_LV_MAXMONEY									/* bc */
{
	table_int_t nID;											/* ID */
	table_int_t nMaxMoney;										/* ����Ǯ */
	table_int_t nLv;											/* �ȼ� */
};

/* ���춯������� */
#define TABLE_TALK_ACT	(918)
struct _TABLE_TALK_ACT									/* ef */
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szCmd;										/* ���� */
	LPCSTR	szNobody;									/* û��Ŀ��ʱ���ִ� */
	LPCSTR	szMyself;									/* Ŀ���Լ�ʱ���ִ� */
	table_int_t 		n0;											/* ά��״̬�� */
	LPCSTR	szOther;									/* Ŀ�����������ʱ���ִ� */
	LPCSTR	szAct;										/* ����ʼ���յ�������Ϣʱ��Ҫ���Ķ������ */
	LPCSTR	szActPersist;								/* �������� */
	LPCSTR	szActEnd;									/* �������� */

	LPCSTR	szIconName;									/* ͼ�� */
	LPCSTR	szToolTip;									/* ��ʾ��Ϣ */
	table_int_t 		isForce;									/* �Ƿ�ǿ�� */
	table_int_t 		isDouble;									/* �Ƿ�˫�� */
};

/* �����������ñ� */
#define TABLE_TALK_CONFIG (919)
struct _TABLE_TALK_CONFIG									/* cd */
{
	table_int_t 		nID;										/* ID ����eCHAT_TYPE */
	LPCSTR	szChannelName;								/* Ƶ������ */
	table_int_t 		nTimeSlice;									/* ʱ��������λ���룩 */
	LPCSTR	szChannelHeader;							/* Ƶ��ǰ���ַ� */
	table_int_t 		nNeedType1;									/* ��������1 ����eCHAT_NEED_TYPE */
	table_int_t 		nNeedValue1;								/* ������ֵ1 */
	table_int_t 		nNeedType2;									/* ��������2 ����eCHAT_NEED_TYPE */
	table_int_t 		nNeedValue2;								/* ������ֵ2 */
	table_int_t 		nNeedType3;									/* ��������3 ����eCHAT_NEED_TYPE */
	table_int_t 		nNeedValue3;								/* ������ֵ3 */
	table_int_t 		nNeedLv;									/* �ȼ����ƣ������Ƶ�����Ͷ��ټ������ڴ�Ƶ������ */
};

/* ���͸ı����ı� */
#define TABLE_HAIR_STYLE	(920)
struct _TABLE_HAIR_STYLE									/* bc */
{
	table_int_t nID;											/* ID���� */
	table_int_t nItemTableID;									/* ������ƷID */
	table_int_t nRaceID;										/* �Ա����� */
	table_int_t nItemCount;										/* ������Ʒ���� */
};

/* ����ͷ�����ݱ� */
#define TABLE_MONSTER_PAOPAO	(921)
struct _TABLE_MONSTER_PAOPAO
{
	table_int_t 		nID;										/* ID���� */
	LPCSTR	szPaoPaoTxt;								/* ����Ҫ˵��ͷ������ */
};

#define TABLE_CAMP_AND_STAND	(922)						/* ��Ӫ */

/* ������Ϣ��ɫ�� */
#define TABLE_SYSTEM_COLOR	(923)
struct _TABLE_SYSTEM_COLOR								/* bc */
{
	const static table_int_t 	NAME_PLAYER_MYSELF_NEWGUY = 1;	/* ����_����_���� */
	const static table_int_t 	NAME_PLAYER_MYSELF_PK_PUTONG = 2;				/* ����_����_PK�� */
	const static table_int_t 	NAME_PLAYER_MYSELF_PK_PK = 3;					/* ����_����_PK�� */
	const static table_int_t 	NAME_PLAYER_MYSELF_PK_HUNZHAN = 4;				/* ����_����_PK�� */
	const static table_int_t 	NAME_PLAYER_MYSELF_GUARDER = 5;					/* ����_����_���� */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_NEWGUY = 6;		/* ����_�������_ͬ��_���� */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_PUTONG = 7;	/* ����_�������_ͬ��_PK�� */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_PK = 8;		/* ����_�������_ͬ��_PK�� */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_HUNZHAN = 9;	/* ����_�������_ͬ��_PK�� */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_GUARDER = 10;	/* ����_�������_ͬ��_���� */
	const static table_int_t 	NAME_PLAYER_OTHER_ENEMYCOUNTRY_NEWGUY = 11;		/* ����_�������_���_���� */
	const static table_int_t 	NAME_PLAYER_OTHER_ENEMYCOUNTRY_NOTNEWGUY = 12;	/* ����_�������_���_������ */
	const static table_int_t 	NAME_PLAYER_OTHER_ENEMYCOUNTRY_GUARDER = 13;	/* ����_�������_���_���� */
	const static table_int_t 	NAME_NPC_HORSE = 14;						/* ����_NPC_�ɲ�׽�� */
	const static table_int_t 	NAME_NPC_SAMECOUNTRY = 15;					/* ����_NPC_ͬ�� */
	const static table_int_t 	NAME_NPC_ENEMYCOUNTRY_NOTATTACK = 16;		/* ����_NPC_���_��ƽ */
	const static table_int_t 	NAME_NPC_ENEMYCOUNTRY_ATTACK_SCANNPC = 17;	/* ����_NPC_���_�������� */
	const static table_int_t 	NAME_NPC_ENEMYCOUNTRY_ATTACK_NOTSCANNPC = 18;	/* ����_NPC_���_�������� */
	const static table_int_t 	NAME_MONSTER_SCANNPC = 19;						/* ����_NPC_���_�������� */
	const static table_int_t 	NAME_MONSTER_NOTSCANNPC = 20;					/* ����_NPC_���_�������� */

	const static table_int_t 	NANE_GUILDBATTLE_SAME_GUILD_A = 21;		/* ���ս��ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_GUILDBATTLE_SAME_GUILD_B = 22;		/* ���ս��ͬ��������֣�B��Ӫ��ң� */
	const static table_int_t 	NANE_WORLDCUP_SAME_GUILD_A = 23;		/* ���籭��ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_WORLDCUP_SAME_GUILD_B = 24;		/* ���籭��ͬ��������֣�B��Ӫ��ң� */
	const static table_int_t 	NANE_KINGBATTLE_SAME_GUILD_A = 25;		/* ��������ս��ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_KINGBATTLE_SAME_GUILD_B = 26;		/* ��������ս��ͬ��������֣�B��Ӫ��ң� */
	const static table_int_t 	NANE_PVP2V2_SAME_GUILD_A = 27;		/* PVP2V2��ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_PVP2V2_SAME_GUILD_B = 28;		/* PVP2V2��ͬ��������֣�B��Ӫ��ң� */
	const static table_int_t 	NANE_PVP6V6_SAME_GUILD_A = 29;		/* PVP6V6��ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_PVP6V6_SAME_GUILD_B = 30;		/* PVP6V6��ͬ��������֣�B��Ӫ��ң� */
	const static table_int_t 	NANE_ZHUQUE_SAME_GUILD_A = 31;		/* ��ȸ�ػ���ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_ZHUQUE_SAME_GUILD_B = 32;		/* ��ȸ�ػ���ͬ��������֣�B��Ӫ��ң� */
	const static table_int_t 	NANE_QINGLONG_SAME_GUILD_A = 33;	/* �����ػ���ͬ��������֣�A��Ӫ��ң� */
	const static table_int_t 	NANE_QINGLONG_SAME_GUILD_B = 34;	/* �����ػ���ͬ��������֣�B��Ӫ��ң� */

	const static table_int_t 	TITLE_NORMAL = 100;			/* �ƺ�_��ͨ */
	const static table_int_t 	TITLE_BANGPAI = 101;		/* �ƺ�_����ְ�� */
	const static table_int_t 	TITLE_MOOD = 102;			/* �ƺ�_����Զ������� */
	const static table_int_t 	TITLE_PLAYER_SHOP = 103;	/* �ƺ�_����̵� */
	const static table_int_t 	TITLE_COUNTRY = 104;		/* �ƺ�_���ҳƺ� */

	const static table_int_t 	UI_DEBUGLISTBOX = 1000;		/* debuglistbox����ɫ */

	table_int_t 					m_nID;
	LPCSTR				strFontColor;
	LPCSTR				strDesc;
	LPCSTR				strExtenColor;
};

/* ��ȫƥ����˱����ڴ�����ᡢ������֮��ĵط�������ʹ��ϵͳ���� */
#define TABLE_FULLCMP_FILTER	(924)
struct _TABLE_FULLCMP_FILTER		/* bc */
{
	table_int_t 		nID;				/* ID���� */
	LPCSTR	szFullTxt;			/* ��ȫ���δ� */
	LPCSTR	szFilterType;		/* ����ʲô�ط������磺all,guild,team,.....��ʾ�������еط�������ᣬ����ӵȵȡ� */
};

/* ����������Ҫ�ľ���� */
#define TABLE_PET_LEVELUP (925)
struct _TABLE_PET_LEVELUP
{
	table_int_t nID;					/* ID���� */
	table_int_t nExp;					/* ����Ҫ���� */
};

/* ����ѧϰ������ */
#define TABLE_SKILL_STUDY_DATA	(926)

/* �����Ʒ�� */
#define TABLE_MOUNT_ITEM_DATA (927)
struct _TABLE_MOUNT_ITEM_DATA
{
	table_int_t 	nItemID;			/* ��ƷID */
	LPCSTR	szItemDec;			/* ��Ʒ˵��,�߻��� */
	table_int_t 		nType;				/* ��Ʒ���� */
	table_int_t 		nRate;				/* ���Ա��� */
	table_int_t 		nNum;				/* ����ֵ */
	table_int_t 		nSkillID;			/* ����ID */
	table_int_t 		nSucceedRate;		/* �ɹ��� */
	table_int_t 		nUseLevel;			/* ʹ�õȼ� */
	table_int_t 		nTakeLevel;			/* Я���ȼ� */
	table_int_t 		nOnlyAberrance;		/* �Ƿ�������ר�� */
};

/* ��������� */
#define TABLE_MOUNT_BASE_DATA (928)
struct _TABLE_MOUNT_BASE_DATA
{
	table_int_t 		nMountID;			/* ��˵�ID */
	table_int_t 		nLevel;				/* ��˵ȼ� */
	table_int_t 		bMating;			/* �Ƿ���Խ��� */
	table_int_t 		bCompose;			/* �Ƿ�������� */
	LPCSTR		szName;				/* ��ʼ�� */
	table_int_t 		iKindType;			/* �������� */
	LPCSTR		szKindName;			/* �������� */
	table_int_t 		nRequirementLevel;	/* ���Я���ȼ� */
	table_int_t 		iReqInherenceLevel;	/* rj 2010-8-23 �츳�ȼ� */
	table_int_t 		iReqPersonLevel;	/* rj 2010-8-23 ���˵ȼ� */
	table_int_t 		bIsAberrance;		/* �Ƿ���� */
	table_int_t 		IsFixedHold;		/* �Ƿ�ɽ��� */
	/*
	 * LPCSTR szTemp;
	 * // CNC ;
	 * table_int_t nChildPer1;
	 * LPCSTR szChildID;
	 * LPCSTR szChildPer2;
	 * LPCSTR szMatingID;
	 * ;
	 * table_int_t nMountID;
	 * // ��˵�ID ;
	 * const char * szMountName;
	 * // ������� û�� table_int_t nLevel;
	 * // ��˵ȼ� ;
	 * table_int_t nRequirementLevel;
	 * // ���Я���ȼ� û�� const char * szChildID;
	 * // ��ͯID û�� const char * szMatingID;
	 * // ����ID û�� table_int_t bMating;
	 * // �Ƿ���Խ��� ;
	 * table_int_t bAberrance;
	 * // �Ƿ���� û�� table_int_t nDaiShu;
	 * // ��ֳ���� û�� table_int_t nAttach;
	 * // ��˵Ĺ��� û�� table_int_t nSurvivalTime;
	 * // ������˴��ʱ�� û�� table_int_t nMinStr;
	 * // ��ʼ��С���� û�� table_int_t nMaxStr;
	 * // ��ʼ������� û�� table_int_t nMinDex;
	 * // ��ʼ��С���� û�� table_int_t nMaxDex;
	 * // ��ʼ������� û�� table_int_t nMinInt;
	 * // ��ʼ��С���� û�� table_int_t nMaxInt;
	 * // ��ʼ������� û�� table_int_t nMinCon;
	 * // ��ʼ��С���� û�� table_int_t nMaxCon;
	 * // ��ʼ������� û�� table_int_t nMinStrApt;
	 * // ��ʼ��С�������� û�� table_int_t nMaxStrApt;
	 * // ��ʼ����������� û�� table_int_t nMinDexApt;
	 * // ��ʼ��С�������� û�� table_int_t nMaxDexApt;
	 * // ��ʼ����������� û�� table_int_t nMinIntApt;
	 * // ��ʼ��С�������� û�� table_int_t nMaxIntApt;
	 * // ��ʼ����������� û�� table_int_t nMinConApt;
	 * // ��ʼ��С�������� û�� table_int_t nMaxConApt;
	 * // ��ʼ����������� û�� table_int_t nMinSavvy;
	 * // ��ʼ��С���� û�� table_int_t nMaxSavvy;
	 * // ��ʼ������� û�� table_int_t nMinBasic;
	 * // ��ʼ��С���� û�� table_int_t nMaxBasic;
	 * // ��ʼ������ û�� table_int_t nMinGrowRate;
	 * // ��ʼ��С�ɳ��� û�� table_int_t nMaxGrowRate;
	 * // ��ʼ���ɳ��� û�� table_int_t nMoveSpeed;
	 * // �ƶ��ٶ� û�� table_int_t nModelID;
	 * // ��Ӧ���֣ɣ� û�� table_int_t nModelID_A;
	 * // ��Ӧ����ID û�� table_int_t nSkillNum;
	 * // ��˼����� û�� const char * szSkill_1;
	 * // ��˼���1 û�� const char * szSkill_2;
	 * // ��˼���2 û�� const char * szSkill_3;
	 * // ��˼���3 û�� const char * szSkill_4;
	 * // ��˼���4 û�� const char * szSkill_5;
	 * // ��˼���5 û�� const char * szSkill_6;
	 * // ��˼���6 û�� table_int_t nSavvySklll;
	 * // ��������ܣɣ� û��
	 */
};

/* ÿ��������� */
#define MAX_NPC_DIALOG_LEN	70
#define MAX_SCENE_LEN		10
#define MAX_MIS_NAME_LEN	24
#define MAX_MIS_TEXT_LEN	24	/* �������� */
#define MAX_MIS_IMAGCD_LEN	(128)

const table_int_t 	MAX_LEVEL_NUM = 161;
const table_int_t 	MAX_DAY_TIPS_NUM = 512;
const table_int_t MONTH_WEEK_NUM = 6; /* ÿ�����6�� */
const table_int_t WEEK_DAY_NUM = 8;	/* ÿ�����7�� */

/*
 -----------------------------------------------------------------------------------------------------------------------
    �������Чʱ��Ƭ
 -----------------------------------------------------------------------------------------------------------------------
 */
struct VALID_TIME_SLICE
{
	tm		m_Begin;	/* ��ʼʱ�� */
	tm		m_End;		/* ����ʱ�� */

	table_int_t 	m_bShow;	/* �Ƿ���ʾ */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ����������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MIS_PARAM_INFO
{
	table_int_t 	m_DayIdx;						/* �������� */
	table_int_t 	m_DayFrom;						/* �ӵڼ�λ */
	table_int_t 	m_DayTo;						/* ���ڼ�λ */

	table_int_t 	m_DataIdx;						/* �������� */
	table_int_t 	m_DataFrom;						/* �ӵڼ�λ */
	table_int_t 	m_DataTo;						/* ���ڼ�λ */
};

/* ÿ�����ѹ������� */
#include "Define.h"
#define TABLE_DAY_TIPS	(929)
struct _TABLE_DAY_TIPS
{
	table_int_t 					m_Index;			/* index */
	table_int_t 					m_Used;				/* �Ƿ��ѳ�ʼ�� */
	table_int_t 					m_DayNominate;		/* ���Ƽ� */
	table_int_t 					m_MonthNominate;	/* ���Ƽ� */
	table_int_t 					m_ShowAll;			/* �Ƿ�ȫ���ɼ���0Ϊ��1Ϊ�����˿ɼ� */

	table_int_t 					m_ShowLevel[MAX_LEVEL_NUM];						/* �ɼ��ȼ���0��ʾ���еȼ��Ρ� */
	table_int_t 					m_ShowCountry[MAX_COUNTRY_NUM];					/* �ɼ����ң�0��ʾ���й��ҡ� */

	table_int_t 					m_CheckGuild;									/* �Ƿ�����ȼ� */
	table_int_t 					m_ShowGuild[MAX_GUILD_LEVEL];					/* �ɼ����ȼ���0��ʾ���еȼ���� */

	table_int_t 					m_CheckFamily;									/* ������ */

	table_int_t 					m_MisType;										/* �������ͣ�0��ʾѭ������1��ʾ��ʱ�淨�� */
	char					m_MisName[MAX_MIS_NAME_LEN];					/* �������� */

	table_int_t 					m_MisValidMonth[13];							/* ������Ч�·ݣ�0��ʾ�����£������ʾ������������·�*/
	table_int_t 					m_WeekOrDay;									/* ���������ڻ�����������0��ʾ���� */

	table_int_t 					m_MisValidDate[32];								/* m_WeekOrDay=1ʱ��������Ч����,0��ʾ����ʱ��Ҫע��ÿ���²��Ƕ���31��*/

	table_int_t 					m_MisValidWeek[MONTH_WEEK_NUM][WEEK_DAY_NUM];	/* ��������Ϊ��λ���� */

	/*
	 * ��һ���ֶα�ʾ�ڼ��ܣ�Ϊ0��ʾ������ ;
	 * �ڶ����ֶα�ʾ�ܼ���Ϊ0��ʾ����
	 */
	VALID_TIME_SLICE		m_VailidTimeSlice;					/* ����ʼ��������ʱ��,Ϊ0��ʾ����ʱ */

	table_int_t 					m_MisTimeFlag;						/* ȫ��ȫ�ֱ���ʱ���� */
	MIS_PARAM_INFO			m_MisParamInfo;						/* ���������Ϣ */

	table_int_t 					m_MisCount;							/* ÿ�տ������� */
	char					m_MisText[MAX_MIS_TEXT_LEN];		/* �������� */

	table_int_t 					m_NPCId;							/* NPCID */
	char					m_QuestImage[MAX_MIS_IMAGCD_LEN];	/* ����ͼ�� */
};

/* ���а�� */
#define TABLE_TOP_LIST	(931)
struct _TABLE_TOP_LIST
{
	table_int_t 			nID;			/* ID */
	const char	*	szName;			/* ���а��� */
	table_int_t 			nListNum;		/* ���а�������� */
	table_int_t 			nMaxLevel;		/* �������а����С���� */
	table_int_t 			bSaveDB;		/* �Ƿ�����ݿ� */
	table_int_t 			nType;			/* ���а����� */
	table_int_t 			nID_bk;			/* ���ݰ�ID */
	const char	*	szExplain;		/* ���а�˵�� */
	table_int_t 			nAwardType;		/* �������� */
	table_int_t 			nAwardNum;		/* �������� */
	const char	*	szTempDec;
	const char	*	szAwardDec;		/* ����˵�� */
};

/* �������� */
#define TABLE_QUEST_LOG	(932)
struct _TABLE_QUEST_LOG
{
	table_int_t 			nIndexID;		/* ����ID */
	table_int_t 			nQuestID;		/* ���� QuestID */
	table_int_t 			nScriptID;		/* �ű� ScriptID */
	table_int_t 			nQuestType;		/* �������ͣ��������� */
	const char	*	szName;			/* �������� */
	table_int_t 			nNPCId;			/* ������NPCID */

	table_int_t 			nMinLevel;		/* ��������͵ȼ� */
	table_int_t 			nMaxLevel;		/* ��������ߵȼ� */

	/* ǰ������ QuestID */
	table_int_t 			nPrevQuest1;	/* ǰ������1 */
	table_int_t 			nPrevQuest2;	/* ǰ������2 */
	table_int_t 			nPrevQuest3;	/* ǰ������3 */

	table_int_t 			nNeedMoneyType;
	table_int_t 			nNeedMoney;
	table_int_t 			nCountry;
	table_int_t 			nProfession;
	table_int_t 			nCamp;
};

#define TABLE_DEATH_DEAL	(944)
struct _TABLE_DEATH_DEAL
{
	table_int_t 		nDieSceneID;
	char	*szSceneName;		/* ��ͼ�� */
	table_int_t 		nRebirthSceneID;
	table_int_t 		nRebirthWay1;
	table_int_t 		nRebirthWay2;
};

#define TABLE_BRITH_COST	(945)
struct _TABLE_BRITH_COST
{
	table_int_t nMinLv;
	table_int_t nOrgeCost;
	table_int_t nSafeCost;
};

/* �����ͼ��ת�� */
#define TABLE_WORLD_POS	(934)
struct _TABLE_WORLD_POS
{
	table_int_t 		nIndex;				/* index */
	table_int_t 		nSceneId;			/* ��ͼSceneId */
	char	*szSceneName;		/* ��ͼ�� */
	table_int_t 		nPosX;				/* X���� */
	table_int_t 		nPosZ;				/* Z���� */
	table_int_t 		nSceneType;			/* SceneType */
	table_int_t 		nMapLevel;			/* MapLevel */
	table_int_t 		nEnterLevel;		/* EnterLevel */
	char	*szIndexName;		/* ƴ������ */
};

enum SCENEMAP_NPC_LOGIC_TYPE
{
	SNLT_DEFAULT = 0,
	SNLT_ONLY_PIC,
};

/* ��ǰ����NPC�� scenemap_npc.tab */
#define TABLE_SCENEMAP_NPC	(935)
struct _TABLE_SCENEMAP_NPC
{
	table_int_t 	nIndex;				/* index */
	LPCSTR	szSceneId;			/* ��ͼSceneId */
	LPCSTR	szNpcName;			/* ��Ϸ�н�ɫͷ������ */
	LPCSTR	szNpcUIName;		/* ��NPC�б�����ʾ������ */
	table_float_t 	nPosX;				/* X���� */
	table_float_t 	nPosZ;				/* Z���� */
	table_int_t 	nTalkToNpc;			/* SceneType */
	table_int_t 	nNPCType;			/* NPC���� */
	LPCSTR	pNPCTypeName;		/* NPC������ */
	LPCSTR	pFilterName;		/* NPC����ƴ������ */
	LPCSTR	pImageName;			/* NPCͼƬ�� */
	INT		nLogicType;
};

#define TABLE_PROVINCE_ZONE	(936)
struct _TABLE_PROVINCE_ZONE
{
	table_int_t 		m_iPostCode;
	char	*m_strProvince;
	char	*m_strZone;
};

// ����������������
struct CAMERA_INTERACT_STATICMESH
{
	LPCSTR	szStaticMeshName;
	LPCSTR	szSoundName;
	table_int_t 	nBeginTime;
	table_int_t 	bIsLoop;
};
#define CAMERA_INTERACT_STATICMESH_MAX_NUM  (3)


/* ��½��صĳ������� login_scene.tab */
#define TABLE_LOGIN_SCENE				(937)
struct _TABLE_LOGIN_SCENE
{
	table_int_t 			nID;					/* month */
	table_int_t 			nSceneId;				/* login scene id */
	table_int_t 			nBackSound;				/* �������� */
	LPCSTR			szCameraTrack;			/* camera track name */
	table_float_t 			fCameraStartPosX;
	table_float_t 			fCameraStartPosY;
	table_float_t 			fCameraStartPosZ;
	table_float_t 			fCameraStartLookAtX;
	table_float_t 			fCameraStartLookAtY;
	table_float_t 			fCameraStartLookAtZ;	
	table_float_t 			fCameraEndPosX;
	table_float_t 			fCameraEndPosY;
	table_float_t 			fCameraEndPosZ;
	table_float_t 			fCameraEndLookAtX;
	table_float_t 			fCameraEndLookAtY;
	table_float_t 			fCameraEndLookAtZ;
	table_float_t 			fCharPosX;
	table_float_t 			fCharPosZ;
	table_float_t 			fCharDir;
	table_float_t 			fCharScale;
	table_float_t 			fMountPosX;
	table_float_t 			fMountPosZ;
	table_float_t 			fMountDir;
	table_float_t 			fMountScale;
	CAMERA_INTERACT_STATICMESH	staticMesh[CAMERA_INTERACT_STATICMESH_MAX_NUM];	
};

/* ������켣�� camera_track.tab */
#define TABLE_CAMERA_TRACK	(938)
struct _TABLE_CAMERA_TRACK
{
	table_int_t 		nIndex;									/* index */
	char	*szTrackName;							/* Track Name */
	char	*szIndexTrackName;						/* Index Track Name */
};

/* �������б� serverlist.tab */
#define TABLE_SERVER_LIST			(939)
#define SERVER_LIST_FIELDS_NUM	10
struct _TABLE_SERVER_LIST
{
	table_int_t 		nIndex;									/* id */
	String	szAreaName;								/* �������� */
	String	szServerName;							/* �������� */
	String	szTooltip;								/* Tip˵�� */
	table_int_t 		nProvider;								/* 0��ͨ��1���� */
	table_int_t 		nServerNo;								/* ��������� */
	table_int_t 		nServerPower;							/* ���������أ�0Ϊ������1Ϊ��æ��2Ϊ���ã�3Ϊ���ѣ�4Ϊά����10Ϊ���÷�����
													 * */
	table_int_t 		nIsRecommender;							/* �Ƿ�Ϊ�Ƽ������� */
	table_int_t 		nIsNewServer;							/* �Ƿ�Ϊ�¿������� */
	String	szServer1;								/* ����IP���˿� */
	String	szServer2;								/* ������1IP���˿� */
	String	szServer3;								/* ������2IP���˿� */
	String	szServer4;								/* ������3IP���˿� */
};

/* ����ű� public\Script.tab */
#define TABLE_QUEST_SCRIPT	(950)
struct _TABLE_QUEST_SCRIPT
{
	table_int_t 		nIndex;									/* ��� */
	LPCSTR	szQuestLua;							/* ��Ӧ������ű� */
};

/* client equip_show.tab */
#define TABLE_EQUIP_OPERATOR_SHOW (951)
struct _TABLE_EQUIP_OPERATOR_SHOW
{
	table_int_t 		nIndex;									/* �淨��� */

	table_int_t 		nSucSound;								/* �ɹ���Ӧ��sound */
	table_int_t 		nFailSound;								/* ʧ�ܶ�Ӧ��sound */

	LPCSTR		szSucEff;								/* �ɹ���Ӧ����Ч */
	LPCSTR		szFailEff;								/* ʧ�ܶ�Ӧ����Ч */
	table_int_t 		nAnimateTime;							/* ����ʱ�� */
};

/* ��� */
#define TABLE_QUESTIONS	(960)
struct _TABLE_QUESTIONS
{
	table_int_t 		nIndex;
	table_int_t 		nType;
	LPCTSTR szQuiz;
	LPCTSTR szAnswer1;
	LPCTSTR szAnswer2;
	LPCTSTR szAnswer3;
	LPCTSTR szAnswer4;
};

/* ��ᣬְλ��ְ������Ӧ��Ȩ�ޱ� */
#define TABLE_AUTHORITY_GUILD (961)

struct _TABLE_AUTHORITY_GUILD
{
	_TABLE_AUTHORITY_GUILD()
	{
		nIndex = 0;
		szAuthorityName = NULL;
		memset(anPosAuthority, 0, sizeof(anPosAuthority));
	}
	table_int_t 		nIndex;
	LPCTSTR szAuthorityName;
	table_int_t 		anPosAuthority[GUILD_POSITION_SIZE];	/* ְλ��Ӧ��Ȩ�� */
};

/* ���鶯���� */
#define TABLE_MOODANIM	(962)
struct _TABLE_MOODANIM
{
	table_int_t 		nID;
	LPCTSTR sKey;				/* �ؼ��� */
	LPCTSTR sDesc;				/* ����, ����tip��ʾ�������ַ����� */
	LPCTSTR sStr;				/* ������Լ����Լ��ı��飬�ַ��� */
	LPCTSTR sIcon;				/* ��ʾ�ڽ����ͼ�� */
	table_int_t 		nType;				/* ���ͣ�0 == 2D��1 == 3D�� */
	LPCTSTR sMoodRes;			/* ���������Դ��ͼƬ��ģ�ͣ� */
};

#define TABLE_BEASTIE_ATTR	(963)
struct _TABLE_BEASTIE_ATTR
{
	table_int_t 				nID;		/* ID */
	table_int_t 				nModelID;	/* ģ��ID */
	LPCTSTR			szPortrait; /* ͷ�� */
	table_int_t 				nSceneID;	/* ���ɳ��� */
	MONSTER_EFFECT	effect[MONSTER_EFFECT_MAX_NUM]; /* ��Ч */

	/*
	 * LPCTSTR nName_NoUse;
	 * // ���� ;
	 * table_float_t  fPosX_NoUse;
	 * // ��ʼλ��X ;
	 * table_float_t  fPosZ_NoUse;
	 * // ��ʼλ��Z ;
	 * table_int_t nItemID_NoUse;
	 * // ������Ʒ ;
	 * table_float_t  fSpeed_NoUse;
	 * // �ƶ��ٶ�
	 */
};

/* char_fashion.tab */
#define TABLE_CHAR_FASHION	(964)
struct _TABLE_CHAR_FASHION
{
	/* ʱװ��� ���� �� �� ͷ �� ���� ���� */
	table_int_t nFashionID;
	table_int_t nBody;
	table_int_t nHand;
	table_int_t nFoot;
	table_int_t nHair;
	table_int_t nShoulder;
	table_int_t nFace;
	table_int_t nWuShi_RightWeapon;
	table_int_t nWuShi_Shield;
	table_int_t nJianXia_LeftWeapon;
	table_int_t nJianXia_RightWeapon;
	table_int_t nQiShe_LeftWeapon;
	table_int_t nHuoQiang_RightWeapon;
	table_int_t nXianZhi_LeftWeapon;
	table_int_t nXianZhi_RightWeapon;
	table_int_t nShaMan_LeftWeapon;
	table_int_t nSheMan_RightWeapon;

	table_int_t nShiZiJun_LeftWeapon;
	table_int_t nShiZiJun_RightWeapon;
	table_int_t nShengHuoShi_LeftWeapon;
	table_int_t nShengHuoShi_RightWeapon;
	table_int_t nCiKe_LeftWeapon;
	table_int_t nCiKe_RightWeapon;
	table_int_t nJinWeiJun_LeftWeapon;
	table_int_t nJinWeiJun_RightWeapon;
	table_int_t nYinXiuShi_LeftWeapon;
	table_int_t nYinXiuShi_RightWeapon;
	table_int_t nLaMa_LeftWeapon;
	table_int_t nLaMa_RightWeapon;
};

/* guild_level_info.tab */
#define TABLE_GUILD_LEVEL_INFO	(965)
struct _TABLE_GUILD_LEVEL_INFO
{
	table_int_t m_Level;									/* ���ȼ� */
	table_int_t m_MaxFamily;								/* ����������� */
	table_int_t m_Gold;										/* �ü������Ǯ */
	table_int_t m_Contribute;								/* �ü����蹱�� */
	table_int_t m_MaxGuildUser;								/* �������Ա���� */
	table_int_t m_MaxFamilyUser;							/* ������������ */
	table_int_t m_MaxGoldFamilyUser;						/* �ƽ������������ */
	table_int_t m_GuildItemNum;								/* �ü��������������� */
	table_int_t m_GuildMaxExp;								/* ���ȼ����� */
	table_int_t m_nMaxMemberGP;								/* �ﹱ���ֵ */
	table_int_t m_nShiMing;									/* ʹ���� */
	table_int_t m_nPriseShiMing;							// ����ʹ�������
	table_int_t m_nShiMingPriseExp;							/* ʹ���㾭�齱�� */
	table_int_t m_nMoneyLimit;								/* ����Ǯ���� */

	_TABLE_GUILD_LEVEL_INFO()
	{
		m_Level = 0;
		m_MaxFamily = 0;
		m_Gold = 0;
		m_Contribute = 0;
		m_MaxGuildUser = 0;
		m_MaxFamilyUser = 0;
		m_MaxGoldFamilyUser = 0;
		m_GuildItemNum = 0;
		m_GuildMaxExp = 0;
		m_nMaxMemberGP = 0;
		m_nShiMing = 0;
		m_nPriseShiMing = 0;
		m_nShiMingPriseExp = 0;
		m_nMoneyLimit = 0;
	}
};

/* guild_merit_info.tab */
#define TABLE_GUILD_MERIT_INFO	(966)
struct _TABLE_GUILD_MERIT_INFO
{
	table_int_t 	m_nLevel;
	table_int_t 	m_nMerit;
	LPCTSTR	m_pTitle;
	table_float_t 	m_fMultiple;

	_TABLE_GUILD_MERIT_INFO()
	{
		m_nLevel = 0;
		m_nMerit = 0;
		m_pTitle = NULL;
		m_fMultiple = 1.0;
	}
};

#define TABLE_SCENEOB_SOUNE	(970)
struct _TABLE_SCENEOB_SOUNE
{
	table_int_t 		m_nID;
	LPCTSTR m_lpName;
	table_int_t 		m_nIndex;
	LPCTSTR m_lpFileName;
	LPCTSTR m_lpPosition;
	LPCTSTR m_lpLoop;
};

#define TABLE_SCENEOB_LIGHT	(971)
struct _TABLE_SCENEOB_LIGHT
{
	table_int_t 		m_nID;
	LPCTSTR m_lpName;
	LPCTSTR m_lpType;
	LPCTSTR m_lpDiffuse;
	LPCTSTR m_lpSpecular;
	LPCTSTR m_lpPosition;
	LPCTSTR m_lpDirection;
	LPCTSTR m_lpRange;
	LPCTSTR m_lpAttenuationConstant;
	LPCTSTR m_lpAttenuationLinear;
	LPCTSTR m_lpAttenuationQuadric;
	LPCTSTR m_lpSpotlightOuter;
	LPCTSTR m_lpSpotlightInner;
	LPCTSTR m_lpSpotlightFalloff;
	LPCTSTR m_lpCastShadows;
	LPCTSTR m_lpStaticLight;
};

#define TABLE_SCENEOB_EFFECT	(972)
struct _TABLE_SCENEOB_EFFECT
{
	table_int_t 		m_nID;
	LPCTSTR m_lpName;
	LPCTSTR m_lpEffectName;

	/*
	 * LPCTSTR m_lpPosition;
	 */
	table_float_t 	m_fPositionX;
	table_float_t 	m_fPositionY;
	table_float_t 	m_fPositionZ;
};

#define TABLE_GLOBAL_CONFIG	(973)
struct _TABLE_GLOBAL_CONFIG
{
	LPCTSTR m_lpName;
	table_int_t 		m_nValue;
	LPCTSTR m_lpDesc;
};

#define TABLE_MOUNT_APTITUDE	(974)
struct _TABLE_MOUNT_APTITUDE
{
	table_int_t nApt;										/* ���� */
};

#define TABLE_CHANGCD_MAP_TIPS_INFO	(975)
struct _TABLE_CHANGCD_MAP_TIPS_INFO
{
	table_int_t 		m_Index;
	LPCTSTR m_lpTipContext;
};

/* ϵͳ��ʾ��Ϣ */
#define TABLE_SYSTEMINFO	(976)
struct _TABLE_SYSTEMINFO
{
	table_int_t 		nID;
	table_int_t 		nMinLevel;
	table_int_t 		nMaxLevel;
	LPCTSTR szCounty;
	table_int_t 		nPlayCount;
	LPCTSTR szDesc;
};

/* ������Ϣ */
#define TABLE_FRIEND	(978)
struct _TABLE_FRIEND
{
	table_int_t 		nID;
	table_int_t 		nEffect;
	table_int_t 		nFriendPoint;
	table_int_t 		nDayCount;
	LPCTSTR szDesc;
};

/* ��ż��Ϣ */
#define TABLE_SPOUSE	(979)
struct _TABLE_SPOUSE
{
	table_int_t 		nID;
	table_int_t 		nEffect[9];
	table_int_t 		nDayCount;
	LPCTSTR szDesc;
};

/* ���ң�ְλ��ְ������Ӧ��Ȩ�ޱ� */
#define TABLE_AUTHORITY_COUNTRY	(980)
#include "DefineCountry.h"
struct _TABLE_AUTHORITY_COUNTRY
{
	_TABLE_AUTHORITY_COUNTRY()
	{
		nIndex = 0;
		szAuthorityName = NULL;
		memset(anPosAuthority, 0, sizeof(anPosAuthority));
	}
	table_int_t 		nIndex;
	LPCTSTR szAuthorityName;
	table_int_t 		anPosAuthority[COUNTRY_POSITION_SIZE];	/* ְλ��Ӧ��Ȩ�� */
};

/* equip_star_effect.tab */
#define TABLE_EQUIP_STAR_EFFECT	(981)

struct _TABLE_EQUIP_STAR_EFFECT
{
	table_int_t 		nEffectId;						/* ��Ӧ */
	LPCTSTR szEffectName;					/* ��Ч */
	LPCTSTR szBindPointName;				/* �󶨵� */
};

#define TABLE_AAS_NODE_INFO	(982)
struct _TABLE_AAS_NODE_INFO
{
	table_int_t 		nID;							/* ��ʾ CHARACTER_AAS_NODE */
	LPCTSTR szDesc;							/* ˵�� */
	LPCTSTR szNodeName;						/* �ڵ��� */
};

/* ���ְ��� */
#define TABLE_HELP_INFO	(969)
struct _TABLE_HELP_INFO
{
	table_int_t 		nID;							/* �൱�ڲ��� */
	LPCTSTR szImage;						/* ͼƬ���� */
	LPCTSTR szDesc;							/* ���ְ��� */
};

#define EQUIP_SET_EFFECT_MAX_NUM	4
struct EQUIP_SET_EFFECT_INFO
{
	LPCTSTR szEffectName;					/* ��Ч */
	LPCTSTR szBindPointName;				/* �󶨵� */
};

/* taozhuangtexiao.tab */
#define TABLE_EQUIP_SET_EFFECT	(983)
struct _TABLE_EQUIP_SET_EFFECT
{
	table_int_t 						nSetNum;		/* ��װ���� */
	EQUIP_SET_EFFECT_INFO	stEffect[EQUIP_SET_EFFECT_MAX_NUM];
};

/* �����ֽ��̵� */
#define TABLE_WORLD_SHOP_ATTR (984)
struct _TABLE_WORLD_SHOP_ATTR
{
	table_int_t 	m_ShopId;						/* �̵�ID */
	table_int_t 		m_GoldCash;						/* �����ֽ� */
	table_int_t 		m_Charge;						/* �շ� */
	table_int_t 	m_ConcentNum;					/* ����ұ�������һ���̵��еļ��۴��� */
	table_int_t 	m_RemainTime;					/* ʣ����Чʱ�� */
	table_int_t 	m_PageNum;						/* �̵��ҳ���� */
	LPCSTR	m_strIconName;
};

/* ����,���ļ���� */
#define TABLE_EQUIP_ACTIVATION_TABLE	(985)
struct _TABLE_EQUIP_ACTIVATION_TABLE
{
	table_int_t 		m_Index;
	LPCTSTR m_strActivationName;
	table_int_t 		m_Type;
	table_int_t 		m_NeedCountMin;
	table_int_t 		m_NeedCountMax;
	table_int_t 		m_NeedLevel;
	table_int_t 		m_PRI;
	table_int_t 		m_AttId0;
	table_int_t 		m_AttValue0;
	table_int_t 		m_AttId1;
	table_int_t 		m_AttValue1;
};

#define TABLE_EQUIP_COLORCHANGCD_TABLE	(986)
struct _TABLE_EQUIP_COLORCHANGCD_TABLE
{
	table_int_t m_Index;
	table_int_t m_ItemId;
	table_int_t m_Money;
	table_int_t m_NeedLevel;
};

#define TABLE_EQUIP_PURPLEREWORK_TABLE	(987)
struct _TABLE_EQUIP_PURPLEREWORK_TABLE
{
	table_int_t m_Index;
	table_int_t m_ItemId;
	table_int_t m_Money;
};

/* �������� */
#define TABLE_SCENE_ANSWER	(988)
struct _TABLE_SCENE_ANSWER
{
	table_int_t 		nID;

	/*
	 * LPCSTR szQuestion;
	 * // ��Ŀ ;
	 * LPCSTR szAnswer;
	 * // ��
	 */
	LPCSTR	szFalsity[6];					/* ��ѡ */
};

/* ����̵� */
#define TABLE_IB_SHOP		(989)
#define IB_SHOP_SUB_NUM 12
struct IB_SHOP_SUB							/* �������� */
{
	table_int_t 		nShopId;						/* ��Ӧ��shop.tab�� */
	LPCTSTR szShopName;						/* �̵����� */
};
struct _TABLE_IB_SHOP
{
	table_int_t 			nIndex;						/* ���� */
	LPCSTR		szPageName;					/* ҳ����������Ʒ�Ĵ��� */
	IB_SHOP_SUB subShop[IB_SHOP_SUB_NUM];	/* �̵����� */
};

#define TABLE_GEM_REWORK_TABLE	(990)
struct _TABLE_GEM_REWORK_TABLE
{
	table_int_t m_Index;
	table_int_t m_NeedNum;
	table_int_t m_OtherNeedItem;
	table_int_t m_OtherNeedNum;
	table_int_t m_NeedMoney;
	table_int_t m_NewItem;
	table_int_t m_NewItemNum;
	_TABLE_GEM_REWORK_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_GEM_REWORK_TABLE));
	}
};

/* ��¼���� */
#define TABLE_LOGIN_ANSWER	(991)
struct _TABLE_LOGIN_ANSWER
{
	table_int_t 		nID;

	/*
	* LPCSTR szQuestion;
	* // ��Ŀ ;
	* LPCSTR szAnswer;
	* // ��
	*/
	LPCSTR	szFalsity[6];					/* ��ѡ */
};

#define TABLE_EQUIP_COPY_TABLE (992)
struct _TABLE_EQUIP_COPY_TABLE
{
	table_int_t m_ItemId;
	table_int_t m_Type;
	_TABLE_EQUIP_COPY_TABLE()
		:m_ItemId(0), m_Type(0)
	{

	}
};

#define TABLE_EQUIP_RECALL_TABLE (993)
struct _TABLE_EQUIP_RECALL_TABLE
{
	table_int_t m_ItemId;
	table_int_t m_RecallType;
	table_int_t m_RecallValue;
	_TABLE_EQUIP_RECALL_TABLE()
		:m_ItemId(0), m_RecallType(0), m_RecallValue(0)
	{

	}
};

#define TABLE_TRANSITEM_POS_TABLE (994)
struct _TABLE_TRANSITEM_POS_TABLE
{
	table_int_t 	m_MapId;
	table_int_t 	m_CoutryLimit;
	LPCTSTR m_MapName;	
	_TABLE_TRANSITEM_POS_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_TRANSITEM_POS_TABLE));
	}
};

#define TABLE_ENERGYBALL_TABLE (995)
struct _TABLE_ENERGYBALL_TABLE
{
	table_int_t 	m_BallId;
	table_int_t 	m_Rate;
	LPCTSTR m_NewItemId;
	
	_TABLE_ENERGYBALL_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_ENERGYBALL_TABLE));
	}
};

#define TABLE_AMULET_TABLE (996)
struct _TABLE_AMULET_TABLE
{
	table_int_t 	m_ItemId;
	table_int_t 	m_Cost;
	table_int_t 	m_bHole1;
	LPCTSTR m_szPartId1;
	table_int_t 	m_bHole2;
	LPCTSTR m_szPartId2;
	table_int_t 	m_bHole3;
	LPCTSTR m_szPartId3;
	table_int_t 	m_bHole4;
	LPCTSTR m_szPartId4;
	table_int_t 	m_bHole5;
	LPCTSTR m_szPartId5;
	table_int_t 	m_bHole6;
	LPCTSTR m_szPartId6;
	_TABLE_AMULET_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_AMULET_TABLE));
	}
};

#define TABLE_EQUIP_PRODUCE (997)
struct _TABLE_EQUIP_PRODUCE
{
	table_int_t m_EquipId;
	table_int_t m_EquipSetId;
	table_int_t m_MatId1;
	table_int_t m_MatCount1;
	table_int_t m_MatId2;
	table_int_t m_MatCount2;
	table_int_t m_MatId3;
	table_int_t m_MatCount3;
	table_int_t m_MatId4;
	table_int_t m_MatCount4;

	_TABLE_EQUIP_PRODUCE()
	{
		memset(this, 0, sizeof(_TABLE_EQUIP_PRODUCE));
	}
};

#define TABLE_EQUIP_SWITCH (998)
struct _TABLE_EQUIP_SWITCH
{
	table_int_t m_EquipSourceId;
	table_int_t m_EquipDestId;
	table_int_t m_Cost;
	table_int_t m_MaterialId;

	_TABLE_EQUIP_SWITCH()
	{
		memset(this, 0, sizeof(_TABLE_EQUIP_SWITCH));
	}
};

// �츳��Ч
#define TABLE_INHERENCE_IMPACT	(999)
struct _TABLE_INHERENCE_IMPACT
{
	table_int_t 		m_iInherenceLevel;
	table_int_t 		m_iNextLevelExp;
	table_int_t 		m_iNextLevelMoney;
	table_int_t 		m_iNextLevelItem;
	LPCSTR		m_lpszEffect_Continuous;
	LPCSTR		m_lpszBind_Continuous;

	_TABLE_INHERENCE_IMPACT()
	{
		memset(this, 0, sizeof(_TABLE_INHERENCE_IMPACT));
	}
};

// ��ԴԤ����
#define TABLE_RES_PRO_LOAD			(1000)
struct _TABLE_RES_PRO_LOAD
{
	table_int_t 	nID;		// id
	LPCSTR	szResName;	// ��Դ��
};

// ��������
#define  TABLE_SCENE_AREA			(1001)
struct _TABLE_SCENE_AREA
{
	table_int_t 	nID;			// ID
	table_int_t 	nSceneID;		// ����ID
	LPCSTR	szExplain;		// ˵��
	table_float_t 	fTopLeftX;		// ����X
	table_float_t 	fTopLeftZ;		// ����Z
	table_float_t 	fBottomRightX;	// ����X
	table_float_t 	fBottomRightZ;	// ����Z
	table_float_t 	fCharDir;		// ���ﳯ��
	table_float_t 	fCameraDir;		// ���������
};

// �����������
#define TABLE_SCENE_ACTOR_MESH		(1002)
struct _TABLE_SCENE_ACTOR_MESH
{
	table_int_t 	nID;				// ID
	table_int_t 	nSceneID;			// ����ID
	LPCSTR	szMeshName;			// Mesh����
	table_int_t 	bIsActLoop;			// �Ƿ���ѭ��
	table_int_t 	bInitActivation;	// ��ʼ����
};

// ������ɫ
#define TABLE_SCENE_COLOR		(1003)
struct _TABLE_SCENE_COLOR
{
	table_int_t 	nID;
	table_float_t 	fAddColorR;					// ��Ӻ�ɫֵ
	table_float_t 	fAddColorG;					// �����ɫֵ
	table_float_t 	fAddColorB;					// �����ɫֵ
	table_float_t 	fScaleColorR;				// ���ź�ɫֵ 
	table_float_t 	fScaleColorG;				// ������ɫֵ
	table_float_t 	fScaleColorB;				// ������ɫֵ
	table_float_t 	fGrayScale;					// ���ŻҶ�
};

//����ָ��
#define TABLE_WORLD_DIRECTORY	(1004)
struct _TABLE_WORLD_DIRECTORY
{
	table_int_t 	nID;						//����
	LPCSTR	szMenu;						//���˵�
	LPCSTR	szSubMenu0;					//�Ӳ˵�1
	LPCSTR	szSubMenu1;					//�Ӳ˵�2
	LPCSTR	szContext;					//����
	LPCSTR	szMinLevel;					//��С�ȼ�
	LPCSTR	szMaxLevel;					//���ȼ�
	LPCSTR	szTime;						//ʱ��
	LPCSTR	szMap;						//��������
	LPCSTR	szNPC0;						//�����ˣ�¥����
	LPCSTR	szNPC1;						//�����ˣ���ɽ��
	LPCSTR	szNPC2;						//�����ˣ����أ�
	LPCSTR	szNPC3;						//�����ˣ��ػͣ�
	LPCSTR	szEvent;					//�¼��ַ���
};

//��������
#define TABLE_CHANGE_APPEARANCE	(1005)
struct _TABLE_CHANGE_APPEARANCE
{
	table_int_t 	m_ItemId;//������Ʒid
};

enum ENUM_CHAR_SOUND_TYPE
{
	ENUM_CHAR_SOUND_TYPE_BATTLE = 0,
	ENUM_CHAR_SOUND_TYPE_DAMAGE,
	ENUM_CHAR_SOUND_TYPE_DEATH,

	ENUM_CHAR_SOUND_TYPE_NUM,
};

// ��������
#define TABLE_CHAR_SOUND		(1006)
struct _TABLE_CHAR_SOUND
{
	table_int_t 		nID;
	LPCSTR		szSound[ENUM_CHAR_SOUND_TYPE_NUM];
};

// �츳ѧϰ
#define TABLE_GIFT_LEARN		(1007)
struct _TABLE_GIFT_LEARN
{
	table_int_t 		nID;
	LPCSTR		szNeedLevel_Guild;			// �����������ȼ�
	LPCSTR		szNeeddMoney_Guild;			// ������������Ǯ
	LPCSTR		szNeedExp_Guild;			// ����������辭��
	LPCSTR		szNeedItem_Guild;			// ��������������id
	LPCSTR		szNeedItemCount_Guild;		// �����߸���
	table_int_t 		nGuildLevelLargess;			// ����Ĭ�ϵȼ�

	LPCSTR		szNeedGiftLevel_Self;		// ���������츳�ȼ�
	LPCSTR		szNeedGiftTotalPoint_Self;	// ���������츳�ܵȼ�
	LPCSTR		szNeedMoney_Self;			// ������������
	LPCSTR		szNeedBangGong_Self;		// ��������ﹱ
	LPCSTR		szNeedShengWang_Self;		// ������������
	LPCSTR		szNeedWeiWang_Self;			// ������������
	LPCSTR		szNeedItem_Self;			// �����������id
	LPCSTR		szNeedItemCount_Self;		// ���˵��߸���
};

//
#define TABLE_AVG_INHERENCE	(1008)
struct _TABLE_AVG_INHERENCE
{
	table_int_t 	nIndex;
	table_int_t 	nPlayerlevel;
	table_int_t 	nInherencelevel;
};

//
#define TABLE_ENERGYBALLSYN (1009)
struct _TABLE_ENERGYBALLSYN
{
	table_int_t  m_Level; //������ɫ����
	table_int_t m_Rate;  //���ձ���
	table_int_t m_ItemId;//��Ҫ�ĵ���
	table_int_t m_ItemCount;//��Ҫ�ĵ�������
};

// ƽ���츳ѧϰ
#define TABLE_BALANCE_LEARN_1	(1010)
struct _TABLE_BALANCE_LEARN_1
{
	table_int_t 	nID;
	table_int_t 	nLogicID;
	table_int_t 	nMaxLevel;
	LPCSTR	szNeedSelfGiftLevel;
	LPCSTR	szNeedItemID;
	LPCSTR	szNeedItemNum;
	LPCSTR	szName;
	LPCSTR	szIconName;
	LPCSTR	szExplain;
	LPCSTR	szDesc;
};

#define SPECIAL_BALANCE_NUM (2)
struct BalanceLearnInfo
{
	table_int_t 	nLogicID;
	table_int_t 	nMaxLevel;
	table_int_t 	nNeedItemID;
	table_int_t 	nNeedItemNum;
	LPCSTR	szName;
	LPCSTR	szIconName;
	LPCSTR	szExplain;
	LPCSTR	szDesc;
};

#define TABLE_BALANCE_LEARN_2	(1011)
struct _TABLE_BALANCE_LEARN_2
{
	table_int_t 	nID;
	BalanceLearnInfo learnInfo[SPECIAL_BALANCE_NUM];
};

#define TABLE_NPC_SPECIAL_TITLE	(1012)
struct _TABLE_NPC_SPECIAL_TITLE
{
	table_int_t 	m_guid;
	table_int_t 	m_country;
	table_int_t 	m_index;
	table_int_t 	m_optType;  //�����ֹ�����	
};

//
#define TABLE_NEW_EQUIP_PRODUCE (1013)
struct _TABLE_NEW_EQUIP_PRODUCE
{
	static const table_int_t 	ATLAS_COL = 2;
	static const table_int_t 	ADDITIVE_COL = 11;
	table_int_t m_nEquipItemId;     //װ��ID	
	table_int_t m_nNeedMoney;       //�����Ǯ	
	table_int_t m_nAtlasItemId;     //ͼ��	
	table_int_t m_nAtlasCount;      //����	
	table_int_t m_nLifeMetItemId;   //�������	
	table_int_t m_nLifeMetCount;    //����	
	table_int_t m_nSpeMetItemId;    //�������	
	table_int_t m_nSpeMetCout;      //����	
	table_int_t m_nRate1[EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER]; //3��,4��,5�����Լ���		
	table_int_t m_nAdditiveItemId;  //��Ӽ�	
	table_int_t m_nAdditiveCount;   //����	
	table_int_t m_nRate2[EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER]; //3��,4��,5�����Լ���
};

//
#define TABLE_EQUIP_CONST_BIND (1014)
struct _TABLE_EQUIP_CONST_BIND
{
	table_int_t m_nNeedItemId;	  //��Ҫ����ID
	table_int_t m_nNeedMoney;       //�����Ǯ
	table_int_t m_nAddConstCount[MAX_EQUIP_CONST_ATTR];   //������������
	table_int_t m_nRate[MAX_EQUIP_CONST_ATTR]; //�������������ĸ���		
};
#define TABLE_EQUIP_CONST_INFO (1015)
struct _TABLE_EQUIP_CONST_INFO
{
	table_int_t m_nConstId;	      //����ID
	LPCSTR m_szConstName;       //��������
	table_int_t m_nActiveConstId1;   //���������ID
	LPCSTR m_szActiveConstName1; //�������������
	table_int_t m_nActiveConstId2;   //���������ID
	LPCSTR m_szActiveConstName2; //�������������
	table_int_t m_nRate;            //�������������ĸ���		
};

#define TABLE_EQUIP_CONST_ACTIVE_POINT (1016)
struct _TABLE_EQUIP_CONST_ACTIVE_POINT
{
	table_int_t m_nPoint;	      //����ID
	table_int_t m_nActivePoint;       //��������	
};

/* 2010-10-19 by rj �����ҷ�������ʾ */
#define TABLE_WORLD_NAME	(1017)
struct _TABLE_WORLD_NAME
{
	int16	nWorldID;				/* ��������� ID */
	LPCSTR	szWorldName;			/* ������������� */
};

#define TABLE_ITEM_SPECIAL (1018)
struct _TABLE_ITEM_SPECIAL
{
	table_int_t m_nIndex;			  //����
	table_int_t m_nItemId;	      //�������id
	table_int_t m_nUseType;         //�������ʹ������	
};

//! ר��
#define TABLE_GIFT_ZHUANGONG    1019
struct _TABLE_GIFT_ZHUANGONG
{
    table_int_t m_iLevel;             // ���ܵȼ�
    table_int_t m_iNeedXP;            // ����ר������
    table_int_t m_iEffect;            // �������Ч��
};

//! ר��
#define TABLE_GIFT_ZHUANFANG    1020
struct _TABLE_GIFT_ZHUANFANG
{
    table_int_t m_iLevel;             // ���ܵȼ�
    table_int_t m_iNeedPoint;         // ����ר������
    table_int_t m_iEffect;            // �������Ч��
};

//��������
#define TABLE_EQUIP_HONOR_BIND    1021
struct _TABLE_EQUIP_HONOR_BIND
{
	table_int_t m_nBindLevel;                                     // ���̼���
	table_int_t m_NeedGem[MAX_EQUIP_HONOR_BIND_COND];             // ����ʯ
	table_int_t m_SuccRate[MAX_EQUIP_HONOR_BIND_COND];            // �ɹ�����
	table_int_t m_FailPunish[MAX_EQUIP_HONOR_BIND_COND];          // ʧ�ܳͷ�
	table_int_t m_nNeedMoney;									    //��Ҫ��Ǯ
	table_int_t m_nIntensify;									    //ǿ������
};

// ������޼���ѧϰ������
#define TABLE_GUILD_BUS_SKILL_STUDY_CONSUME	(1022)
struct _TABLE_GUILD_BUS_SKILL_STUDY_CONSUME
{
	table_int_t m_nSkillID;										// ��ǰ�ȼ��ļ���ID
	table_int_t m_NextLevelSKillID;								// ��һ���ļ���ID
	table_int_t m_nSkillLevel;									// �ȼ�
	table_int_t m_nNeedGuildLevel;								// ������ȼ�
	table_int_t m_ConsumeMoney;									// ���Ľ�Ǯ
	table_int_t m_ConsumeGuildExp;								// ���İ�ᾭ��
};