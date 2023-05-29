/*$T Common/StructPet.h GC 1.140 10/10/07 10:06:56 */

/* StructPet.h */
#ifndef __GAMESTRUCT_PET_H__
#define __GAMESTRUCT_PET_H__

#include "TypeDefine.h"
#include "Enum.h"
#include "StructDB.h"

const int32	MaxHorseDropNum = 16;

/* 宠物操作类型 */
enum ENUM_MANIPULATE_TYPE
{
	MANIPULATE_INVALID		= -1,		/* 无效 */
	MANIPULATE_ASKOTHERPETINFO,			/* 察看其他玩家的宠物信息(宠物征友等用...) */
	MANIPULATE_CREATEHORSE,				/* 召唤坐骑 */
	MANIPULATE_DELETEHORSE,				/* 收回坐骑 */
	MANIPULATE_FREEHORSE,				/* 放生坐骑 */
	MANIPULATE_HORSE_ITEM,				/* 使用物品 */
	MANIPULATE_HORSE_NICKNAME,			/* 修改昵称 */
	MANIPULATE_HORSE_MATING_CONFIRM,	/* 坐骑交配确认 */
	MANIPULATE_ALLHORSEHAPPY,			/* 恢复所有骑乘的快乐度 */
	MANIPULATE_HORSE_COMPOSE_CONFIRM,	/*坐骑合成确认*/
	MANIPULATE_NUMBERS
};

/* 坐骑物品类型 */
enum HORSE_ITEM_TYPE
{
	HORSE_ITEM_INVALID			= -1,
	HORSE_ITEM_HAPPINESS,			/* 快乐度 */
	HORSE_ITEM_SKILL_GIRD,			/* 技能格 */
	HORSE_ITEM_SKILL_FORGET,		/* 技能遗忘 */
	HORSE_ITEM_SKILL_APPER,			/* 技能领悟，对应前6格的技能 */
	HORSE_ITEM_SKILL_STUDY,			/* 技能学习，对应后6格的技能 */
	HORSE_ITEM_STRENGTHPERCEPTION,		/* 力量资质道具 */
	HORSE_ITEM_SMARTNESSPERCEPTION,		/* 敏捷资质道具 */
	HORSE_ITEM_MINDPERCEPTION,		/* 智力资质道具 */
	HORSE_ITEM_CONSTITUTIONPERCEPTION,	/* 体质资质道具 */
	HORSE_ITEM_EXP,			/* 经验道具 */
	HORSE_ITEM_CLEAR_ATTR_POINT,	/* 表示洗点道具 */
	HORSE_ITEM_CHANGE_FADE,		/* 永久变形道具 */
	HORSE_ITEM_RESTORE_FADE,	/* 永久复原道具 */
	HORSE_ITEM_RETURN_TO_CHILD,	/* 还童道具 */
	HORSE_ITEM_QIANNENG,		/* 潜能道具 */
	HORSE_ITEM_RETURN_TO_CHILD_EXT,/* 还龙道具 */
	HORSE_ITEM_NUM
};

/* 附加宠物属性定义 */
enum ePET_FOOD_TYPE
{
	PET_FOOD_TYPE_INVALID			= 0,
	PET_FOOD_TYPE_MEAT,		/* 肉食宠粮 */
	PET_FOOD_TYPE_GRASS,		/* 草类宠粮 */
	PET_FOOD_TYPE_WORM,		/* 虫类宠粮 */
	PET_FOOD_TYPE_PADDY,		/* 谷类宠粮 */

	PET_FOOD_TYPE_NUMBER,
};

struct PET_PROPERTY
{
	int32	m_Type;			/* 宠物编号 */
	char	m_Name[NPC_NAME_LEN];	/* 名称 */
	int32	m_TakeLevel;		/* 可携带等级 */
	int32	m_bVarPet;		/* 是否为变异宠物 */
	int32	m_bBabyPet;		/* 是否为宝宝宠物 */
	int32	m_AI;			/* 宠物性格 */
	int32	m_FoodType;		/* 食物类 */
	int32	m_PassiveSkillCount;	/* 自动技能数 */
	int32	m_VoluntarySkill;	/* 手动技能 */
	int32	m_PassiveSkill1;	/* 自动技能1 */
	int32	m_PassiveSkill2;	/* 自动技能2 */
	int32	m_PassiveSkill3;	/* 自动技能3 */
	int32	m_PassiveSkill4;	/* 自动技能4 */

	/*
	 * int32 m_Life;
	 * // 标准寿命
	 */
	int32	m_iStrengthPerception;	/* 力量资质 */
	int32	m_iSmartnessPerception; /* 敏捷资质 */
	int32	m_iMindPerception;	/* 智力资质 */
	int32	m_iConstitutionPerception;	/* 体质资质 */

	int32	m_GrowRate0;			/* 成长率1 */
	int32	m_GrowRate1;			/* 成长率2 */
	int32	m_GrowRate2;			/* 成长率3 */
	int32	m_GrowRate3;			/* 成长率4 */
	int32	m_GrowRate4;			/* 成长率5 */
	int32	m_CowardiceRate;		/* 胆小几率 */
	int32	m_WarinessRate;			/* 谨慎几率 */
	int32	m_LoyalismRate;			/* 忠诚几率 */
	int32	m_CanninessRate;		/* 精明几率 */
	int32	m_ValourRate;			/* 勇猛几率 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        _PET_DETAIL_PROPERTY 宠物属性
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

	ObjID_t		m_ObjID;	/* 所有Obj类型的ObjID */
	int32		m_nDataID;	/* 模型ID,宠物类型 */
	char		m_szName[MAX_CHARACTER_NAME];	/* 名称 */
	int32		m_nAIType;			/* 性格 */
	SHorseGuid	m_SpouseGUID;			/* 配偶的GUID */
	int32		m_nLevel;			/* 等级 */
	uint32		m_nExp;			/* 经验 */
	int32		m_nHP;			/* 血当前值 */
	int32		m_nHPMax;		/* 血最大值 */
	int32		m_nLife;		/* 当前寿命 */

	uchar		m_byGeneration;		/* 几代宠 */
	uchar		m_byHappiness;		/* 快乐度 */

	int32		m_nAtt_Near;
	int32		m_nDef_Near;
	int32		m_nAtt_Far;
	int32		m_nDef_Far;
	int32		m_nAtt_Magic;		/* 魔法攻击力 */
	int32		m_nDef_Magic;		/* 魔法防御力 */

	int32		m_nHit;			/* 命中率 */
	int32		m_nMiss;		/* 闪避率 */
	int32		m_nCritical;		/* 会心率 */

	int32		m_nModelID;		/* 外形 */
	int32		m_nMountID;		/* 座骑ID */

	int32		m_iStrengthPerception;	/* 力量资质 */
	int32		m_iSmartnessPerception; /* 敏捷资质 */
	int32		m_iMindPerception;	/* 智力资质 */
	int32		m_iConstitutionPerception;	/* 体质资质 */

	int32		m_Str;		/* 力量 */
	int32		m_Con;		/* 体力 */
	int32		m_Dex;		/* 身法 */
	int32		m_Int;		/* 定力 */
	int32		m_GenGu;	/* 根骨 */
	int32		m_nRemainPoint; /* 潜能点 */

	_PLAYER_SPELL	m_aSkill[MAX_PET_SKILL_COUNT];	/* 技能列表 */
};


const int32	MaxSlotSkillNum = 64;
const int32	MaxSlotNum = 12;
const int32	MaxReturnToChildIDNum = 16;
//const int32	MaxHorseDropNum = 16;
const int32	MaxHorseDropGroupNum = 10;

struct _HORSE_SKILL_SLOT
{
	int32	m_aSkillSlot[MaxSlotSkillNum];		/* 技能槽可选的技能ID */
	int32	m_iSkillCount;				/* 此技能槽实际可选的技能ID */
};

struct _HORSE_SKILL_RANDRATE
{
	int32	m_aSkillRandRate[MaxSlotSkillNum];	/* 技能生成概率 */
	int32	m_iSkillCount;	/* 技能实际数量 */
};

struct _HORSE_SKILL_REALIZATION
{
	int32			m_iSkillRealizationID;		/* 技能领悟ID */
	int32			m_iSkillSlotCount;		/* 技能槽数量，最大为12 */
	_HORSE_SKILL_SLOT	m_oSkillSlot[MaxSlotNum];	/* 每个技能槽可领悟的技能ID */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        马属性
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _HORSE_ATTR
{
	int32			m_nDataID;			/* 数据ID */
	char			m_sName[64];			/* 名称 */
	int32			m_iSex;				/* 性别 */
	int32			m_iLevel;			/* 初始等级 */
	int32			m_iTakeLevel;			/* 可携带等级 */
	int32			m_iReqInherenceLevel;	/* rj 2010-8-23 天赋等级 */
	int32			m_iReqPersonLevel;		/* rj 2010-8-23 个人等级 */
	int32			m_iReturnToChildRandSum;	/* 还童概率分母 */
	int32			m_aReturnToChildID[MaxReturnToChildIDNum];		/* 还童后的ID */
	int32			m_aReturnToChildRandRate[MaxReturnToChildIDNum];	/* 还童概率分子 */
	int32			m_iReturnToChildIDCount;		/* 还童后可选ID的实际个数 */
	int32			m_aChildID[MaxReturnToChildIDNum];	/* 交配后，2代的ID,对应QiChengJichu.tab中的ID */
	int32			m_iChildIDCount;			/* 交配后，2代可选ID的个数 */
	int32			m_bCanMating;			/* 是否可以交配 */
	int32			m_bCanCompose;			/* 是否可以炼化 */
	BOOL			m_bVariation;			/* 是否变异 */
	uchar			m_byGeneration;			/* 繁殖代数 */
	int32			m_iLifeHaveMaster;		/* 骑乘的保护时间 */
	int32			m_LifeNoMaster;			/* 无主时的生命周期 */
	int32			m_iStrengthMin;			/* 初始最小力量 */
	int32			m_iStrengthMax;			/* 初始最大力量 */
	int32			m_iSmartnessMin;		/* 初始最小敏捷 */
	int32			m_iSmartnessMax;		/* 初始最大敏捷 */
	int32			m_iMindMin;			/* 初始最小智力 */
	int32			m_iMindMax;			/* 初始最大智力 */
	int32			m_iConstitutionMin;		/* 初始最小体质 */
	int32			m_iConstitutionMax;		/* 初始最大体质 */
	int32			m_iStrengthMinPer;		/* 初始最小力量资质 */
	int32			m_iStrengthMaxPer;		/* 初始最大力量资质 */
	int32			m_iSmartnessMinPer;		/* 初始最小敏捷资质 */
	int32			m_iSmartnessMaxPer;		/* 初始最大敏捷资质 */
	int32			m_iMindMinPer;			/* 初始最小智力资质 */
	int32			m_iMindMaxPer;			/* 初始最大智力资质 */
	int32			m_iConstitutionMinPer;		/* 初始最小体质资质 */
	int32			m_iConstitutionMaxPer;		/* 初始最大体质资质 */
	int32			m_iSavvyMin;			/* 初始最小悟性 */
	int32			m_iSavvyMax;			/* 初始最大悟性 */
	int32			m_GenGuMin;			/* 初始最小根骨 */
	int32			m_GenGuMax;			/* 初始最大根骨 */
	int32			m_iPullulationRateMin;		/* 初始最小成长率 */
	int32			m_iPullulationRateMax;		/* 初始最大成长率 */
	int32			m_iMoveSpeed;			/* 移动速度 */
	int32			m_iBehaveID;			/* 对应表现ID */
	int32			m_iMountID;			/* 对应在坐骑表中的索引 */

	int32			m_iInitSkillRandSum;		/* 马初始技能概率分母 */
	_HORSE_SKILL_SLOT	m_oSkillSlot[MaxSlotNum];	/* 马初始技能列表 */
	_HORSE_SKILL_RANDRATE	m_oSillRandRate[MaxSlotNum];	/* 马初始技能概率列表 */
	int32			m_iRealizationID;		/* 技能领悟ID */
	int32			m_iScriptID;			/* 骑乘事件调用脚本的ID */
	int32			m_bIsFixedHold;			/* 是否不可交易出售等 */
	int32			m_iKindType;			/* 物种类型(交配类型） */
};
/*
-----------------------------------------------------------------------------------------------------------------------
马合成
-----------------------------------------------------------------------------------------------------------------------
*/
struct _HORSE_MIX
{
	int32			m_nDataID;			/* 数据ID */
	int32			m_nMixOdds;			/* 合成几率 */
	int32			m_nMixdeno;		/* 合成几率分母 */
	int32			m_nRemainValue1;	/* 预留1 */
	int32			m_nRemainValue2;	/* 预留2 */
};
/*
-----------------------------------------------------------------------------------------------------------------------
马合成主动技能几率
-----------------------------------------------------------------------------------------------------------------------
*/
struct _HORSE_MIX_SPELL
{
	int32			m_nHorseSpellTotal;			/* 主动技能总数 */
	int32			m_nHorseSpell0;				/* 合成0个几率 */
	int32			m_nHorseSpell1;				/* 合成1个几率 */
	int32			m_nHorseSpell2;				/* 合成2个几率 */
	int32			m_nHorseSpell3;				
	int32			m_nHorseSpell4;				
	int32			m_nHorseSpell5;	
	int32			m_nHorseSpell6;	
};
struct _HORSE_ITEM
{
	/* 道具ID */
	int32	m_iItemID;

	/*
	 * 道具类型 ;
	 * 道具分别对应着不同的使用类型,表示的后面数值的作用的对象不同. ;
	 * 其中1表示的是增加骑乘悟性的道具,2表示增加骑乘根骨的道具 3表 ;
	 * 示的是增加快乐度4表示增加可使用技能格子数5表示对应位置的洗去 ;
	 * 技能格子的笑忘书,-1表示无作用6表示领悟型技能道具, 增加领悟技 ;
	 * 能7表示扩展位置的技能书8表示还童?
	 */
	int32	m_iItemType;

	/*
	 * 改变对应的骑乘的属性的百分比数值 ;
	 * 对应1类型的数值填写表示的含义是按照百分比增加骑乘的悟性,对应 ;
	 * 2表示百分比增加根骨,3表示百分比增加快度,4,5,6,7，8该项数值无 ;
	 * 作用
	 */
	int32	m_iAttrChangePercent;

	/*
	 * 改变对应的骑乘的属性的点数数值 ;
	 * 对应1类型的数值填写表示的含义是按照数值增加骑乘的悟性,对应2表 ;
	 * 示按照数值增加根骨,3表示按照数值增加快乐度, 4表示扩展格子的数 ;
	 * 目,5表示对应洗去的格子位置,8表示新骑乘的成长率6,7该数值无作用
	 */
	int32	m_iAttrChangePoint;

	/*
	 * 技能领悟和学习对应技能ID ;
	 * 当道具类型填写6和7时候,填写该ID添加相应的技能, 对应技能表格的 ;
	 * ID号码,按照成功率添加技能
	 */
	int32	m_iStudySkillID;

	/* 技能领悟和学习的成功率 */
	int32	m_iSuccessRate;

	/* 使用等级,对应骑乘的等级 */
	int32	m_nUseLevel;

	/* 使用等级,对应骑乘的携带等级 */
	int32	m_nTakeLevel;

	/* 是否变异骑乘专用 */
	int32	m_nOnlyAberrance;
};

struct _HORSE_DROP_GROUP
{
	int32	m_iGroupImportance;			/* 马掉落组的价值，计算掉落概率时作分子 */
	int32	m_iGroupMaxDropTimes;			/* 掉落组最大的掉落次数 */
	int32	m_aGroupHorseID[MaxHorseDropNum];	/* 马ID列表，随机选取一个，对应马基础表中的ID */
	int32	m_iHorseIDCount;			/* m_aGroupHorseID中有效数值的个数 */
};

struct _HORSE_DROP
{
	int32			m_iDropID;		/* 马掉落ID,怪物表中索引此ID */
	int32			m_iMonsterImportance;	/* 怪物的价值，计算概率时做分母 */
	int32			m_iMaxDropNum;		/* 怪物的最大掉落数量 */
	_HORSE_DROP_GROUP	m_aDropGroup[MaxHorseDropGroupNum];	/* 掉落组的数组 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        召唤兽初始化属性
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _MONSTER_PET_ATTR
{
	int32	iLifeTime;	/* 存在时间 */
	int32	iImpactToSelf;	/* 召唤兽自身存在效果ID */
	int32	iImpactToOnwer; /* 为主人叠加效果ID */
	int32	aSkillID[MONSTER_PET_MAX_SKILL];	/* 主动技能 */
	int32	OnwerAttackRate;			/* 主人生命影响百分比 */
	int32	OnwerLifeRate;		/* 主人攻击力影响百分比 */
	int32	OnwerDefanceRate;	/* 主人防御力影响百分比 */
	int32	OnwerMissRate;		/* 主人闪避影响百分比 */
	int32	OnwerToughnessRate;	/* 主人韧性影响百分比 */
	int32	OnwerCriticalRate;	/* 主人暴击率影响百分比 */
	int32	OnwerHitRate;		/* 主人命中影响百分比 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        宠物操作参数传递用
 -----------------------------------------------------------------------------------------------------------------------
 */
struct _HorseManipulate
{
	ObjID_t		m_ObjID;	/* 宠物的ObjID;
					 * */
	ObjID_t		m_CharObjID;
	SHorseGuid	m_PetGUID;	/* 一般操作时的宠物,或交配时的主宠 */
	SHorseGuid	m_MattingSecondHorseGuid;	/* 交配时的副宠 */
	int32		m_nType;
	int32		m_iTypeData;			/* 由具体的操作类型解释其数值含义(目前是道具使用数量) */
	char		m_sNickName[MAX_NICK_NAME];	/* 宠物昵称 */
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
