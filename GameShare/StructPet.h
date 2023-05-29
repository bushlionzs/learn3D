/*$T Common/StructPet.h GC 1.140 10/10/07 10:06:56 */

/* StructPet.h */
#ifndef __GAMESTRUCT_PET_H__
#define __GAMESTRUCT_PET_H__

#include "TypeDefine.h"
#include "Enum.h"
#include "StructDB.h"

const int32	MaxHorseDropNum = 16;

/* ����������� */
enum ENUM_MANIPULATE_TYPE
{
	MANIPULATE_INVALID		= -1,		/* ��Ч */
	MANIPULATE_ASKOTHERPETINFO,			/* �쿴������ҵĳ�����Ϣ(�������ѵ���...) */
	MANIPULATE_CREATEHORSE,				/* �ٻ����� */
	MANIPULATE_DELETEHORSE,				/* �ջ����� */
	MANIPULATE_FREEHORSE,				/* �������� */
	MANIPULATE_HORSE_ITEM,				/* ʹ����Ʒ */
	MANIPULATE_HORSE_NICKNAME,			/* �޸��ǳ� */
	MANIPULATE_HORSE_MATING_CONFIRM,	/* ���ｻ��ȷ�� */
	MANIPULATE_ALLHORSEHAPPY,			/* �ָ�������˵Ŀ��ֶ� */
	MANIPULATE_HORSE_COMPOSE_CONFIRM,	/*����ϳ�ȷ��*/
	MANIPULATE_NUMBERS
};

/* ������Ʒ���� */
enum HORSE_ITEM_TYPE
{
	HORSE_ITEM_INVALID			= -1,
	HORSE_ITEM_HAPPINESS,			/* ���ֶ� */
	HORSE_ITEM_SKILL_GIRD,			/* ���ܸ� */
	HORSE_ITEM_SKILL_FORGET,		/* �������� */
	HORSE_ITEM_SKILL_APPER,			/* �������򣬶�Ӧǰ6��ļ��� */
	HORSE_ITEM_SKILL_STUDY,			/* ����ѧϰ����Ӧ��6��ļ��� */
	HORSE_ITEM_STRENGTHPERCEPTION,		/* �������ʵ��� */
	HORSE_ITEM_SMARTNESSPERCEPTION,		/* �������ʵ��� */
	HORSE_ITEM_MINDPERCEPTION,		/* �������ʵ��� */
	HORSE_ITEM_CONSTITUTIONPERCEPTION,	/* �������ʵ��� */
	HORSE_ITEM_EXP,			/* ������� */
	HORSE_ITEM_CLEAR_ATTR_POINT,	/* ��ʾϴ����� */
	HORSE_ITEM_CHANGE_FADE,		/* ���ñ��ε��� */
	HORSE_ITEM_RESTORE_FADE,	/* ���ø�ԭ���� */
	HORSE_ITEM_RETURN_TO_CHILD,	/* ��ͯ���� */
	HORSE_ITEM_QIANNENG,		/* Ǳ�ܵ��� */
	HORSE_ITEM_RETURN_TO_CHILD_EXT,/* �������� */
	HORSE_ITEM_NUM
};

/* ���ӳ������Զ��� */
enum ePET_FOOD_TYPE
{
	PET_FOOD_TYPE_INVALID			= 0,
	PET_FOOD_TYPE_MEAT,		/* ��ʳ���� */
	PET_FOOD_TYPE_GRASS,		/* ������� */
	PET_FOOD_TYPE_WORM,		/* ������� */
	PET_FOOD_TYPE_PADDY,		/* ������� */

	PET_FOOD_TYPE_NUMBER,
};

struct PET_PROPERTY
{
	int32	m_Type;			/* ������ */
	char	m_Name[NPC_NAME_LEN];	/* ���� */
	int32	m_TakeLevel;		/* ��Я���ȼ� */
	int32	m_bVarPet;		/* �Ƿ�Ϊ������� */
	int32	m_bBabyPet;		/* �Ƿ�Ϊ�������� */
	int32	m_AI;			/* �����Ը� */
	int32	m_FoodType;		/* ʳ���� */
	int32	m_PassiveSkillCount;	/* �Զ������� */
	int32	m_VoluntarySkill;	/* �ֶ����� */
	int32	m_PassiveSkill1;	/* �Զ�����1 */
	int32	m_PassiveSkill2;	/* �Զ�����2 */
	int32	m_PassiveSkill3;	/* �Զ�����3 */
	int32	m_PassiveSkill4;	/* �Զ�����4 */

	/*
	 * int32 m_Life;
	 * // ��׼����
	 */
	int32	m_iStrengthPerception;	/* �������� */
	int32	m_iSmartnessPerception; /* �������� */
	int32	m_iMindPerception;	/* �������� */
	int32	m_iConstitutionPerception;	/* �������� */

	int32	m_GrowRate0;			/* �ɳ���1 */
	int32	m_GrowRate1;			/* �ɳ���2 */
	int32	m_GrowRate2;			/* �ɳ���3 */
	int32	m_GrowRate3;			/* �ɳ���4 */
	int32	m_GrowRate4;			/* �ɳ���5 */
	int32	m_CowardiceRate;		/* ��С���� */
	int32	m_WarinessRate;			/* �������� */
	int32	m_LoyalismRate;			/* �ҳϼ��� */
	int32	m_CanninessRate;		/* �������� */
	int32	m_ValourRate;			/* ���ͼ��� */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        _PET_DETAIL_PROPERTY ��������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _PET_DETAIL_PROPERTY
{
public:
	_PET_DETAIL_PROPERTY (void);

	BOOL	Init
		(
			const _HORSE_DB			*pPetDB,
			ObjID_t				idObj,
			int32				nAtt_Near,
			int32				nDef_Near,
			int32				nAtt_Far,
			int32				nDef_Far,
			/* int32 nAtt_Physics, */int32	nAtt_Magic,
			/* int32 nDef_Physics, */int32	nDef_Magic,
			int32				nHit,
			int32				nMiss,
			int32				nCritical,
			int32				nModelID,
			int32				nMountID
		);

	void	Clear(void);

	static uint32 GetSize();
	void	Send(SendStream &oStream) const;
	void	Reci(RecieveStream &iStream);

public:
	SHorseGuid	m_GUID;		/* ID */

	ObjID_t		m_ObjID;	/* ����Obj���͵�ObjID */
	int32		m_nDataID;	/* ģ��ID,�������� */
	char		m_szName[MAX_CHARACTER_NAME];	/* ���� */
	int32		m_nAIType;			/* �Ը� */
	SHorseGuid	m_SpouseGUID;			/* ��ż��GUID */
	int32		m_nLevel;			/* �ȼ� */
	uint32		m_nExp;			/* ���� */
	int32		m_nHP;			/* Ѫ��ǰֵ */
	int32		m_nHPMax;		/* Ѫ���ֵ */
	int32		m_nLife;		/* ��ǰ���� */

	uchar		m_byGeneration;		/* ������ */
	uchar		m_byHappiness;		/* ���ֶ� */

	int32		m_nAtt_Near;
	int32		m_nDef_Near;
	int32		m_nAtt_Far;
	int32		m_nDef_Far;
	int32		m_nAtt_Magic;		/* ħ�������� */
	int32		m_nDef_Magic;		/* ħ�������� */

	int32		m_nHit;			/* ������ */
	int32		m_nMiss;		/* ������ */
	int32		m_nCritical;		/* ������ */

	int32		m_nModelID;		/* ���� */
	int32		m_nMountID;		/* ����ID */

	int32		m_iStrengthPerception;	/* �������� */
	int32		m_iSmartnessPerception; /* �������� */
	int32		m_iMindPerception;	/* �������� */
	int32		m_iConstitutionPerception;	/* �������� */

	int32		m_Str;		/* ���� */
	int32		m_Con;		/* ���� */
	int32		m_Dex;		/* �� */
	int32		m_Int;		/* ���� */
	int32		m_GenGu;	/* ���� */
	int32		m_nRemainPoint; /* Ǳ�ܵ� */

	_PLAYER_SPELL	m_aSkill[MAX_PET_SKILL_COUNT];	/* �����б� */
};


const int32	MaxSlotSkillNum = 64;
const int32	MaxSlotNum = 12;
const int32	MaxReturnToChildIDNum = 16;
//const int32	MaxHorseDropNum = 16;
const int32	MaxHorseDropGroupNum = 10;

struct _HORSE_SKILL_SLOT
{
	int32	m_aSkillSlot[MaxSlotSkillNum];		/* ���ܲۿ�ѡ�ļ���ID */
	int32	m_iSkillCount;				/* �˼��ܲ�ʵ�ʿ�ѡ�ļ���ID */
};

struct _HORSE_SKILL_RANDRATE
{
	int32	m_aSkillRandRate[MaxSlotSkillNum];	/* �������ɸ��� */
	int32	m_iSkillCount;	/* ����ʵ������ */
};

struct _HORSE_SKILL_REALIZATION
{
	int32			m_iSkillRealizationID;		/* ��������ID */
	int32			m_iSkillSlotCount;		/* ���ܲ����������Ϊ12 */
	_HORSE_SKILL_SLOT	m_oSkillSlot[MaxSlotNum];	/* ÿ�����ܲۿ�����ļ���ID */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        ������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _HORSE_ATTR
{
	int32			m_nDataID;			/* ����ID */
	char			m_sName[64];			/* ���� */
	int32			m_iSex;				/* �Ա� */
	int32			m_iLevel;			/* ��ʼ�ȼ� */
	int32			m_iTakeLevel;			/* ��Я���ȼ� */
	int32			m_iReqInherenceLevel;	/* rj 2010-8-23 �츳�ȼ� */
	int32			m_iReqPersonLevel;		/* rj 2010-8-23 ���˵ȼ� */
	int32			m_iReturnToChildRandSum;	/* ��ͯ���ʷ�ĸ */
	int32			m_aReturnToChildID[MaxReturnToChildIDNum];		/* ��ͯ���ID */
	int32			m_aReturnToChildRandRate[MaxReturnToChildIDNum];	/* ��ͯ���ʷ��� */
	int32			m_iReturnToChildIDCount;		/* ��ͯ���ѡID��ʵ�ʸ��� */
	int32			m_aChildID[MaxReturnToChildIDNum];	/* �����2����ID,��ӦQiChengJichu.tab�е�ID */
	int32			m_iChildIDCount;			/* �����2����ѡID�ĸ��� */
	int32			m_bCanMating;			/* �Ƿ���Խ��� */
	int32			m_bCanCompose;			/* �Ƿ�������� */
	BOOL			m_bVariation;			/* �Ƿ���� */
	uchar			m_byGeneration;			/* ��ֳ���� */
	int32			m_iLifeHaveMaster;		/* ��˵ı���ʱ�� */
	int32			m_LifeNoMaster;			/* ����ʱ���������� */
	int32			m_iStrengthMin;			/* ��ʼ��С���� */
	int32			m_iStrengthMax;			/* ��ʼ������� */
	int32			m_iSmartnessMin;		/* ��ʼ��С���� */
	int32			m_iSmartnessMax;		/* ��ʼ������� */
	int32			m_iMindMin;			/* ��ʼ��С���� */
	int32			m_iMindMax;			/* ��ʼ������� */
	int32			m_iConstitutionMin;		/* ��ʼ��С���� */
	int32			m_iConstitutionMax;		/* ��ʼ������� */
	int32			m_iStrengthMinPer;		/* ��ʼ��С�������� */
	int32			m_iStrengthMaxPer;		/* ��ʼ����������� */
	int32			m_iSmartnessMinPer;		/* ��ʼ��С�������� */
	int32			m_iSmartnessMaxPer;		/* ��ʼ����������� */
	int32			m_iMindMinPer;			/* ��ʼ��С�������� */
	int32			m_iMindMaxPer;			/* ��ʼ����������� */
	int32			m_iConstitutionMinPer;		/* ��ʼ��С�������� */
	int32			m_iConstitutionMaxPer;		/* ��ʼ����������� */
	int32			m_iSavvyMin;			/* ��ʼ��С���� */
	int32			m_iSavvyMax;			/* ��ʼ������� */
	int32			m_GenGuMin;			/* ��ʼ��С���� */
	int32			m_GenGuMax;			/* ��ʼ������ */
	int32			m_iPullulationRateMin;		/* ��ʼ��С�ɳ��� */
	int32			m_iPullulationRateMax;		/* ��ʼ���ɳ��� */
	int32			m_iMoveSpeed;			/* �ƶ��ٶ� */
	int32			m_iBehaveID;			/* ��Ӧ����ID */
	int32			m_iMountID;			/* ��Ӧ��������е����� */

	int32			m_iInitSkillRandSum;		/* ���ʼ���ܸ��ʷ�ĸ */
	_HORSE_SKILL_SLOT	m_oSkillSlot[MaxSlotNum];	/* ���ʼ�����б� */
	_HORSE_SKILL_RANDRATE	m_oSillRandRate[MaxSlotNum];	/* ���ʼ���ܸ����б� */
	int32			m_iRealizationID;		/* ��������ID */
	int32			m_iScriptID;			/* ����¼����ýű���ID */
	int32			m_bIsFixedHold;			/* �Ƿ񲻿ɽ��׳��۵� */
	int32			m_iKindType;			/* ��������(�������ͣ� */
};
/*
-----------------------------------------------------------------------------------------------------------------------
��ϳ�
-----------------------------------------------------------------------------------------------------------------------
*/
struct _HORSE_MIX
{
	int32			m_nDataID;			/* ����ID */
	int32			m_nMixOdds;			/* �ϳɼ��� */
	int32			m_nMixdeno;		/* �ϳɼ��ʷ�ĸ */
	int32			m_nRemainValue1;	/* Ԥ��1 */
	int32			m_nRemainValue2;	/* Ԥ��2 */
};
/*
-----------------------------------------------------------------------------------------------------------------------
��ϳ��������ܼ���
-----------------------------------------------------------------------------------------------------------------------
*/
struct _HORSE_MIX_SPELL
{
	int32			m_nHorseSpellTotal;			/* ������������ */
	int32			m_nHorseSpell0;				/* �ϳ�0������ */
	int32			m_nHorseSpell1;				/* �ϳ�1������ */
	int32			m_nHorseSpell2;				/* �ϳ�2������ */
	int32			m_nHorseSpell3;				
	int32			m_nHorseSpell4;				
	int32			m_nHorseSpell5;	
	int32			m_nHorseSpell6;	
};
struct _HORSE_ITEM
{
	/* ����ID */
	int32	m_iItemID;

	/*
	 * �������� ;
	 * ���߷ֱ��Ӧ�Ų�ͬ��ʹ������,��ʾ�ĺ�����ֵ�����õĶ���ͬ. ;
	 * ����1��ʾ��������������Եĵ���,2��ʾ������˸��ǵĵ��� 3�� ;
	 * ʾ�������ӿ��ֶ�4��ʾ���ӿ�ʹ�ü��ܸ�����5��ʾ��Ӧλ�õ�ϴȥ ;
	 * ���ܸ��ӵ�Ц����,-1��ʾ������6��ʾ�����ͼ��ܵ���, �������� ;
	 * ��7��ʾ��չλ�õļ�����8��ʾ��ͯ?
	 */
	int32	m_iItemType;

	/*
	 * �ı��Ӧ����˵����Եİٷֱ���ֵ ;
	 * ��Ӧ1���͵���ֵ��д��ʾ�ĺ����ǰ��հٷֱ�������˵�����,��Ӧ ;
	 * 2��ʾ�ٷֱ����Ӹ���,3��ʾ�ٷֱ����ӿ��,4,5,6,7��8������ֵ�� ;
	 * ����
	 */
	int32	m_iAttrChangePercent;

	/*
	 * �ı��Ӧ����˵����Եĵ�����ֵ ;
	 * ��Ӧ1���͵���ֵ��д��ʾ�ĺ����ǰ�����ֵ������˵�����,��Ӧ2�� ;
	 * ʾ������ֵ���Ӹ���,3��ʾ������ֵ���ӿ��ֶ�, 4��ʾ��չ���ӵ��� ;
	 * Ŀ,5��ʾ��Ӧϴȥ�ĸ���λ��,8��ʾ����˵ĳɳ���6,7����ֵ������
	 */
	int32	m_iAttrChangePoint;

	/*
	 * ���������ѧϰ��Ӧ����ID ;
	 * ������������д6��7ʱ��,��д��ID�����Ӧ�ļ���, ��Ӧ���ܱ��� ;
	 * ID����,���ճɹ�����Ӽ���
	 */
	int32	m_iStudySkillID;

	/* ���������ѧϰ�ĳɹ��� */
	int32	m_iSuccessRate;

	/* ʹ�õȼ�,��Ӧ��˵ĵȼ� */
	int32	m_nUseLevel;

	/* ʹ�õȼ�,��Ӧ��˵�Я���ȼ� */
	int32	m_nTakeLevel;

	/* �Ƿ�������ר�� */
	int32	m_nOnlyAberrance;
};

struct _HORSE_DROP_GROUP
{
	int32	m_iGroupImportance;			/* �������ļ�ֵ������������ʱ������ */
	int32	m_iGroupMaxDropTimes;			/* ���������ĵ������ */
	int32	m_aGroupHorseID[MaxHorseDropNum];	/* ��ID�б����ѡȡһ������Ӧ��������е�ID */
	int32	m_iHorseIDCount;			/* m_aGroupHorseID����Ч��ֵ�ĸ��� */
};

struct _HORSE_DROP
{
	int32			m_iDropID;		/* �����ID,�������������ID */
	int32			m_iMonsterImportance;	/* ����ļ�ֵ���������ʱ����ĸ */
	int32			m_iMaxDropNum;		/* ��������������� */
	_HORSE_DROP_GROUP	m_aDropGroup[MaxHorseDropGroupNum];	/* ����������� */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        �ٻ��޳�ʼ������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _MONSTER_PET_ATTR
{
	int32	iLifeTime;	/* ����ʱ�� */
	int32	iImpactToSelf;	/* �ٻ����������Ч��ID */
	int32	iImpactToOnwer; /* Ϊ���˵���Ч��ID */
	int32	aSkillID[MONSTER_PET_MAX_SKILL];	/* �������� */
	int32	OnwerAttackRate;			/* ��������Ӱ��ٷֱ� */
	int32	OnwerLifeRate;		/* ���˹�����Ӱ��ٷֱ� */
	int32	OnwerDefanceRate;	/* ���˷�����Ӱ��ٷֱ� */
	int32	OnwerMissRate;		/* ��������Ӱ��ٷֱ� */
	int32	OnwerToughnessRate;	/* ��������Ӱ��ٷֱ� */
	int32	OnwerCriticalRate;	/* ���˱�����Ӱ��ٷֱ� */
	int32	OnwerHitRate;		/* ��������Ӱ��ٷֱ� */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        �����������������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _HorseManipulate
{
	ObjID_t		m_ObjID;	/* �����ObjID;
					 * */
	ObjID_t		m_CharObjID;
	SHorseGuid	m_PetGUID;	/* һ�����ʱ�ĳ���,����ʱ������ */
	SHorseGuid	m_MattingSecondHorseGuid;	/* ����ʱ�ĸ��� */
	int32		m_nType;
	int32		m_iTypeData;			/* �ɾ���Ĳ������ͽ�������ֵ����(Ŀǰ�ǵ���ʹ������) */
	char		m_sNickName[MAX_NICK_NAME];	/* �����ǳ� */
	int32		m_iBagIndex;
	uint32		m_uItemID;
	int32		m_iBagIndex2;
	uint32		m_uItemID2;
	BOOL		m_bUseItemResult;
	int32		m_iExtraData;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetObjID(const ObjID_t objID)
	{
		m_ObjID = objID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjID_t GetObjID(void) const
	{
		return m_ObjID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGUID(const SHorseGuid& guid)
	{
		m_PetGUID = guid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SHorseGuid GetGUID(void) const
	{
		return m_PetGUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SHorseGuid GetMattingSecondHorseGuid() const
	{
		return m_MattingSecondHorseGuid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMattingSecondHorseGuid(SHorseGuid& val)
	{
		m_MattingSecondHorseGuid = val;
	}

	/*
	 ===============================================================================================================
	        nType:: ENUM_MANIPULATE_TYPE
	 ===============================================================================================================
	 */
	void SetManipulateType(int32 nType)
	{
		m_nType = nType;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetManipulateType(void) const
	{
		return m_nType;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjID_t GetCharObjID() const
	{
		return m_CharObjID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCharObjID(ObjID_t val)
	{
		m_CharObjID = val;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetTypeData() const
	{
		return m_iTypeData;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTypeData(int32 val)
	{
		m_iTypeData = val;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetNickName() const
	{
		return &m_sNickName[0];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetNickName(const char *val)
	{
		if(strlen(val) >= MAX_NICK_NAME - 1)
			strncpy(m_sNickName, val, sizeof(m_sNickName));
		else
			strcpy(m_sNickName, val);
		m_sNickName[MAX_NICK_NAME - 1] = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetBagIndex() const
	{
		return m_iBagIndex;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetBagIndex(int32 val)
	{
		m_iBagIndex = val;
	}
	/*
	===============================================================================================================
	===============================================================================================================
	*/
	int32 GetBagIndex2() const
	{
		return m_iBagIndex2;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetBagIndex2(int32 val)
	{
		m_iBagIndex2 = val;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetItemID() const
	{
		return m_uItemID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetItemID(uint32 val)
	{
		m_uItemID = val;
	}
	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetItemID2() const
	{
		return m_uItemID2;
	}
	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetItemID2(uint32 val)
	{
		m_uItemID2 = val;
	}
	/*
	===============================================================================================================
	===============================================================================================================
	*/
	int32 GetExtraData() const
	{
		return m_iExtraData;
	}
	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetExtraData(int32 val)
	{
		m_iExtraData = val;
	}

	BOOL GetUseItemResult()const
	{
		return m_bUseItemResult;
	}

	void SetUseItemResult( BOOL bUseItemResult )
	{
		m_bUseItemResult = bUseItemResult;
	}

	_HorseManipulate()
	{
		memset(this, 0, sizeof(_HorseManipulate));
	}
};
class	Player;
struct _UseHorseItem
{
	Player		*pPlayer;
	_HORSE_ITEM	*pHorseItem;
	BOOL		bUseItem;
	_HORSE_DB		*pPetDB;
	int32		iUseItemNum;
	int32		iIndex;
};

enum _HORSE_CALL_SCRIPT_TYPE { HORSE_CALL_SCRIPT_ON = 0, HORSE_CALL_SCRIPT_OFF };

enum _PET_CTRL_STATE { PCS_KILL_TARGET = 0, PCS_IDLE };
#endif /* __GAMESTRUCT_PET_H__ */
