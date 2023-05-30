#ifndef __TAB_DEFINE_MAP_ITEM_H__
#define __TAB_DEFINE_MAP_ITEM_H__

#include "item/Item_Types.h"
#include "TypeDefine.h"
#include "StructItem.h"
#include "Enum.h"
#include "TabStruct.h"

#define ALL_JOB_MASK 0x7FFFFFFF

#define CONSTRUCT_SELF(x) \
	x() \
	{ \
		memset(this, 0, sizeof(x)); \
	}

struct SDropBoxTab
{
	CONSTRUCT_SELF(SDropBoxTab);
	uint32		m_DropBoxId;
	int32		m_DropValue;
	SItemType	m_DropItem[MAX_DROPBOX_CARRAGE];
	int32		m_Quality[MAX_DROPBOX_CARRAGE];
};

struct SMinMaxValue
{
	CONSTRUCT_SELF(SMinMaxValue)
	int32	m_minValue;
	int32	m_maxValue;
};

enum eMINMAX_TYPE { VT_MIN, VT_MAX };
struct SItemValueTab
{
	CONSTRUCT_SELF(SItemValueTab)
	uint32		m_ValueType;
	SMinMaxValue	m_Values[MAX_ITEM_TABLE_VALUES];
};

struct EQUIP_ATT_LEVEL_TB
{
	CONSTRUCT_SELF(EQUIP_ATT_LEVEL_TB)
	int32	m_AttID;
	int32	m_Attr[MAX_EQUIP_LEVEL];
};

struct ATTR_INFO
{
	ATTR_INFO()
	{
		m_Attr = 0;
		for(int32 i = 0; i < EQUIP_TYPE_NUM; ++i)
		{
			m_nValidEquipType[i] = -1;
		}
	}
	int32	m_Attr;
	uint32	m_nValidEquipType[EQUIP_TYPE_NUM];
};
struct EQUIP_ATT_SET_TB
{
	CONSTRUCT_SELF(EQUIP_ATT_SET_TB);
	int32		m_IndexID;
	char		m_SetName[100];
	int32		m_AttSetRate;
	int32		m_ReqLevel;
	int32		m_SumRate;
	int32		m_AttCount;
	ATTR_INFO	m_AttrInfo[MAX_EQUIP_EXT_ATTR];
};

struct SEquipTab
{
	CONSTRUCT_SELF(SEquipTab);
	int32			m_IndexID;
	SItemType		m_ItemType;
	uchar			m_Color;
	uchar			m_EquipPoint;
	char			m_RulerID;
	int32			m_EquipSetNum;

	int32			m_ReqLevelCount;
	uchar			m_ReqLevel[MAX_RAND_LEVEL_NUM];
	int32			m_iReqInherenceLevel;	// rj 2010-8-23 天赋及个人等级
	int32			m_iReqPersonLevel;
	uint32			m_BasePrice;
	int32			m_MaxDur;
	int32			m_LevelCount;
	uchar			m_Level[MAX_EQUIP_LEVELUP_NUM];
	uchar			m_BaseGemHole;
	uchar			m_MAXGemHole;
	uchar			m_PrefessionReq;
	uchar			m_PaiType;
	int32			m_EquipScore;
	int32			m_NearAttack;
	int32			m_FarAttack;
	int32			m_MagicAttack;
	int32			m_NearDefence;
	int32			m_FarDefence;
	int32			m_MagicDefense;
	int32			m_EquipSetMaxNum;
	uchar			m_AttCount;
	uchar			m_AffSkillCount;
	uchar			m_EffSkillCount;
	_ITEM_PROPERTY		m_Attr[MAX_EQUIP_EXT_ATTR];
	_ITEM_AFFIX_SKILL	m_AffixSkill[MAX_EQUIP_AFFIX_SKILL];
	_ITEM_EFFECT_SKILL	m_EffectSkill[MAX_EQUIP_EFFECT_SKILL];
	int32			m_nScriptID;
	int32			m_ParamType;
	int32			m_ParamValue;
	int32			m_ConsumeValue;
	int32			m_iTermHour;
	int32			m_minPickLevel;		//最小拾取等级
};

struct MONSTER_DROP_TB
{
	CONSTRUCT_SELF(MONSTER_DROP_TB);
	uint32			m_DropId;
	uint32			m_ValidCount;
	MONSTER_DROPCONTENT	m_Drops[MAX_MONSTER_DROPBOX];
};

struct SGemInfoTab
{
	SGemInfoTab()
	{
		m_nTableIndex = INVALID_ID;
		m_nRulerID = INVALID_RULERID;
		m_nPrice = INVALID_PRICE;
		m_nSellPrice = INVALID_PRICE;
		m_bBroadCast = FALSE;
		m_AttCount = 0;
		m_GemReqCount = 0;
		m_ItemType.Clear();
		for(int32 i = 0; i < MAX_BASE_EQUIP_COUNT; ++i) m_EquipType[i] = 0;
		for(int32 i = 0; i < MAX_GEM_ATT; ++i) m_GenAttr[i].Clear();
		for(int32 i = 0; i < MAX_GEM_REQ; ++i) m_GemReqAttr[i].Clear();
		m_ShowLevel = 0;
		m_nUsePrice = 0;
		m_ParamType = -1;
		m_ParamValue = 0;
		m_ConsumeValue = 0;
		m_nReqEquipLevel = 0;
		m_GemReworkIndex = INVALID_ID;
		m_UninstalledIsBind = 0;
		m_minPickLevel = 0;

	}
	uint32		m_nTableIndex;
	SItemType	m_ItemType;
	char		m_nRulerID;
	uint32		m_EquipType[MAX_BASE_EQUIP_COUNT];
	uint32		m_nPrice;
	uint32		m_nSellPrice;
	int32		m_nReqEquipLevel;
	BOOL		m_bBroadCast;
	uint32		m_AttCount;
	_ITEM_PROPERTY	m_GenAttr[MAX_GEM_ATT];
	uint32		m_GemReqCount;
	_GEM_REQ_ATT	m_GemReqAttr[MAX_GEM_REQ];
	int32		m_ShowLevel;
	int32		m_nUsePrice;
	int32		m_ParamType;
	int32		m_ParamValue;
	int32		m_ConsumeValue;
	int32		m_GemReworkIndex;
	char		m_UninstalledIsBind;
	int32		m_minPickLevel;		//最小拾取等级
};

struct EQUIPHOLE_INFO_TB
{
	EQUIPHOLE_INFO_TB()
	{
		for(int i = 0; i < EQUIP_TYPE_NUM; ++i)
		{
			m_ReqItem[i] = -1;
		}
		m_ReqItemNum = 0;
		m_ReqMoney = 0;
		m_Rate = 0;
	}
	int32	m_ReqItem[EQUIP_TYPE_NUM];
	uint32	m_ReqItemNum;
	uint32	m_ReqMoney;
	uint32	m_Rate;
};

struct EQUIPCHAIN_INFO_TB
{
	EQUIPCHAIN_INFO_TB()
	{
		m_ChainID = INVALID_PAI_TYPE;
		m_ReqPai1 = INVALID_PAI_TYPE;
		m_ReqPai2 = INVALID_PAI_TYPE;
		m_ReqPai3 = INVALID_PAI_TYPE;
		m_Att.Clear();
		m_Flat.Clear();
	}
	uint32		m_ChainID;
	uint32		m_ReqPai1;
	uint32		m_ReqPai2;
	uint32		m_ReqPai3;
	Flag128		m_Flat;
	_ITEM_PROPERTY	m_Att;
};

struct EQUIPSOUL_INFO_TB
{
	CONSTRUCT_SELF(EQUIPSOUL_INFO_TB);
	uint32		m_SoulID;
	int32		m_SoulType;
	uint32		m_ChainID[MAX_CHAIN_NUM];
	uint32		m_ChainID5;
	uint32		m_ChainIDNum[MAX_CHAIN_NUM];
	uint32		ValidSoulNum;

	uint32		m_EffectAttCount;
	_ITEM_PROPERTY	m_Att[MAX_SOUL_EFFECTATT];
	int32		m_ReqItem;
};

struct CHANGEPAI_INFO_TB
{
	uint32	m_nTableIndex;
	int32	m_DestPaiType;
	int32	m_nReqMoney;
};
;
struct SMiscItemInfoTab
{
	SMiscItemInfoTab()
	{
		m_nTableIndex = 0;
		m_nLevel = 0;
		m_nJob = ~ALL_JOB_MASK;//默认没有职业限制
		m_nBasePrice = 0;
		m_nSellPrice = 0;
		m_nLayedNum = 0;
		m_nScriptID = 0;
		m_nSkillID = 0;
		m_nRulerID = 0;
		m_nReqSkill = -1;
		m_nReqSkillLevel = -1;
		m_HoldNum = -1;
		m_TargetType = 0;
		m_bBroadcast = FALSE;
		m_ItemType.Clear();
		m_ParamType = -1;
		m_ParamValue = 0;
		m_ConsumeValue = 0;
		m_nImpactID = -1;
		m_bMultTimes = FALSE;
		m_iMultTimes = INVALID_ID;
		m_nIndexOfGemRework = INVALID_ID;
	}
	int32		m_nTableIndex;
	SItemType	m_ItemType;
	int32		m_nLevel;
	int32		m_iReqInherenceLevel;	// rj 2010-8-23 天赋及个人等级
	int32		m_iReqPersonLevel;
	uint32		m_nJob;//!< 使用最后一个位表示没有职业限制（兼容以前-1，99的情况）
	int32		m_nUseLeve;
	uint32		m_nBasePrice;
	uint32		m_nSellPrice;
	char		m_nRulerID;
	int32		m_nLayedNum;
	int32		m_nScriptID;
	int32		m_nSkillID;
	int32		m_nReqSkill;
	int32		m_nReqSkillLevel;
	int32		m_HoldNum;
	uchar		m_TargetType;
	BOOL		m_bBroadcast;
	int32		m_ParamType;
	int32		m_ParamValue;
	int32		m_ConsumeValue;
	int32		m_nImpactID;
	BOOL		m_bMultTimes;
	int32		m_iMultTimes;
	int32		m_nIndexOfGemRework;
	int32		m_minPickLevel;			//最小拾取等级

public:
	bool isMatchProfession(const char cJob)
	{

		if (m_nJob & (~ALL_JOB_MASK))
		{
			return true;
		}

		KCheck( cJob >= 0 && cJob < PROFESSION_NUMBER);

		return (m_nJob >> cJob) & 0x1;
	}
};

struct TASKITEM_INFO_TB
{
	TASKITEM_INFO_TB()
	{
		m_nTableIndex = 0;
		m_nLevel = 0;
		m_nBasePrice = 0;
		m_nSellPrice = 0;
		m_nLayedNum = 0;
		m_nScriptID = 0;
		m_nSkillID = 0;
		m_nRulerID = 0;
		m_nReqSkill = -1;
		m_nReqSkillLevel = -1;
		m_HoldNum = -1;
		m_TargetType = 0;
		m_bBroadcast = FALSE;
		m_ItemType.Clear();
		m_ParamType = -1;
		m_ParamValue = 0;
		m_ConsumeValue = 0;
	}
	int32		m_nTableIndex;
	SItemType	m_ItemType;
	int32		m_nLevel;
	int32		m_nUseLeve;
	uint32		m_nBasePrice;
	uint32		m_nSellPrice;
	char		m_nRulerID;
	int32		m_nLayedNum;
	int32		m_nScriptID;
	int32		m_nSkillID;
	int32		m_nReqSkill;
	int32		m_nReqSkillLevel;
	int32		m_HoldNum;
	uchar		m_TargetType;
	BOOL		m_bBroadcast;
	int32		m_ParamType;
	int32		m_ParamValue;
	int32		m_ConsumeValue;
};

#define MAX_GIFT_DESC_LENGTH	256
#define MAX_GIFT_DESC_COUNT	2
struct FRIEND_GIFT_TB
{
	FRIEND_GIFT_TB()
	{
		m_nItemTableIndex = -1;
		m_nBuffID = -1;
		m_nFriendPoint = 0;
		m_nScriptID = INVALID_ID;
	}
	int32	m_nItemTableIndex;
	int32	m_nBuffID;
	int32	m_nFriendPoint;

	int32	m_nScriptID;

	int32	m_nBroadcast;

	int32	m_nDescription;
	char	m_strDescription[MAX_GIFT_DESC_COUNT][MAX_GIFT_DESC_LENGTH / MAX_GIFT_DESC_COUNT];
};

struct SDropAttrTab
{
	CONSTRUCT_SELF(SDropAttrTab);
	int32	m_DeltaLevel;
	float	m_AttValue;
	float	m_ExpValue;
	float	m_TeamAttValue;
	float	m_TeamExpValue;
};

struct DROP_POS_TB
{
	CONSTRUCT_SELF(DROP_POS_TB);
	float	m_DropX;
	float	m_DropZ;
};

struct EQUIPLEVELUP_INFO
{
	CONSTRUCT_SELF(EQUIPLEVELUP_INFO);
	uint32	m_EquipLevelReqGemID[MAX_LEVELUP_GEMREQ_NUM];		//装备等级需求宝石
	uint32	m_SuccessRate[MAX_LEVELUP_GEMREQ_NUM];				//成功概率
	uint32	m_ReqMoney[MAX_LEVELUP_GEMREQ_NUM];					//装备等级所需金钱
	int32	m_EquipLevelReq[MAX_LEVELUP_GEMREQ_NUM];			//装备等级需求
	uint32	m_Punishment;
	uint32	m_EffectRate;
	int32	m_EffectAttrType;									//影响属性类别
	int32	m_ReqLevel;
	int32	m_LevelType;
};

struct EQUIP_LEVELUP_TB
{
	CONSTRUCT_SELF(EQUIP_LEVELUP_TB);
	EQUIPLEVELUP_INFO	m_EquipLevelupInfo[MAX_EQUIP_LEVELUP_NUM][EQUIPLEVEL_TYPENUM];
};

struct EQUIP_BIND_TB
{
	CONSTRUCT_SELF(EQUIP_BIND_TB);
	uint32  m_EffectRate;
	uint32	m_GemID[MAX_BIND_GEMREQ_NUM];
	int32	m_nReqMoney[MAX_BIND_GEMREQ_NUM];
	int32   m_EquipLevelReq[MAX_BIND_GEMREQ_NUM];
};

struct EQUIP_SPECIALREPAIR_TB
{
	CONSTRUCT_SELF(EQUIP_SPECIALREPAIR_TB);
	uint32	m_RepairItemID;
	uint32	m_UseItemID;
	uint32	m_UseItemCount;
	int32	m_nReqMoney;
};

struct CREATEITEM_INFO
{
	uint32	m_MaterialType;
	uchar	m_MaterialNum;
	uchar	m_NeedLevel;
	uchar	m_SplitRate;
};

struct REMOULDITEM_INFO
{
	uint32	m_MaterialType;
	uchar	m_MaterialNum;
	uchar	m_NeedLevel;
};

struct ITEM_PRODUCT_INFO_TB
{
	CONSTRUCT_SELF(ITEM_PRODUCT_INFO_TB);
	uint32			m_ProductID;
	uint32			m_PrescriptionID;
	uchar			m_ProductNum;
	uint32			m_nCreateInfoCount;
	CREATEITEM_INFO		m_CreateInfo[MAX_CREATE_MATERIAL_NUM];
	uint32			m_nRemouldInfoCount;
	REMOULDITEM_INFO	m_RemouldInfo[MAX_REMOULD_MATERIAL_NUM];
	uint32			m_OperateTime;
	uint32			m_ScriptID;
	uint32			m_CreateMoney;
	uint32			m_RemouldMoney;
	BOOL			m_IsFixed;
};

struct MATERIAL_LEVEL_INFO_TB
{
	MATERIAL_LEVEL_INFO_TB()
	{
		m_MaterialValue = 0;
	}
	uint32	m_MaterialValue;
};

struct EQUIP_EXTRAATT_SET
{
	int32	m_AttrCount;
	int32	m_Attr[10];
};

struct EQUIPEXTRATT
{
	uint32			m_ValidCount;
	EQUIP_EXTRAATT_SET	m_GenAttr[MAX_ITEM_NATUREATTR];
};

struct EQUIPEXTRATT_TB
{
	CONSTRUCT_SELF(EQUIPEXTRATT_TB);

	uint32		m_nEquipScore;
	EQUIPEXTRATT	m_EquipExtrAtt[MAX_JOB_SUM];
};

struct EXTRABAG_INFO_TB
{
	EXTRABAG_INFO_TB()
	{
		m_nTableIndex = 0;
		m_ItemType.Clear();
		m_nRulerID = 0;
		m_nBasePrice = 0;
		m_nSellPrice = 0;
		m_nValidTime = 0;
		m_nSize = 0;
		m_ParamType = -1;
		m_ParamValue = 0;
		m_ConsumeValue = 0;
	}
	uint32		m_nTableIndex;
	SItemType	m_ItemType;
	char		m_nRulerID;
	uint32		m_nBasePrice;
	uint32		m_nSellPrice;
	uint32		m_nValidTime;
	uint32		m_nSize;
	int32		m_ParamType;
	int32		m_ParamValue;
	int32		m_ConsumeValue;
	int32		m_minPickLevel;		//最小拾取等级	
};

struct PAI_INFO
{
	PAI_INFO()
	{
		m_nPaiID = INVALID_PAI_TYPE;
		m_nRate = 0;
		m_Att.Clear();
		memset(m_nPaiIDSet,0,sizeof(m_nPaiIDSet));
		m_nPaiIDSetCount =0;
	}
	uint32		m_nPaiID;
	_ITEM_PROPERTY	m_Att;
	uint32		m_nRate;
	uint8		m_nPaiIDSet[EQUIP_PAI_NUM];//牌ID集合(对牌ID=1~14的任意牌有效)
	uint8		m_nPaiIDSetCount;			//牌ID集合个数
	
};

struct EQUIPSET_INFO
{
	EQUIPSET_INFO()
	{
		m_nEquipSetNum = 0;
	}
	int32		m_nEquipSetNum;
	_ITEM_PROPERTY	m_ItemAttr;
};

struct SEquipSetTab
{
	CONSTRUCT_SELF(SEquipSetTab);
	int32		m_nEquipSetSerial;
	int32		m_nEquipSetCount;
	int32		m_nValidEquipSetNum;
	EQUIPSET_INFO	m_EquipSetInfo[MAX_ITEM_SET_ATTR];
};

struct _RELEATION_ATTEFFECT
{
	_RELEATION_ATTEFFECT()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_EffectRate, 0, sizeof(int32) * CPROPERTY_LEVEL1_NUMBER);
	}

	int32	m_EffectRate[CPROPERTY_LEVEL1_NUMBER];
};

struct MARRYEFFECT_TB
{
	MARRYEFFECT_TB()
	{
		m_EffectRate[SEX_FEMALE].Clear();
		m_EffectRate[SEX_MALE].Clear();
		m_nExpRate = 0;
		m_nDay = 0;
	}
	_RELEATION_ATTEFFECT	m_EffectRate[SEX_NUMBERS];
	int32			m_nExpRate;
	int32			m_nDay;
};

struct FRIENDEFFECT_TB
{
	FRIENDEFFECT_TB()
	{
		m_nEffectRate = 0;
		m_nFriendPoint = 0;
		m_nFriendDay = 0;
		memset(m_szDesc, 0, sizeof(m_szDesc));
	}
	int32	m_nEffectRate;
	int32	m_nFriendPoint;
	int32	m_nFriendDay;
	char	m_szDesc[MAX_RELATION_DESC_LEN];
};

struct SItemRulerTab :
	public SItemRuler
{
	CONSTRUCT_SELF(SItemRulerTab);
	int32	m_RulerIndex;
};

struct EQUIP_ACTIVATION_TB
{
	int32	m_Index;
	int32	m_Type;
	int32	m_NeedCountMin;
	int32	m_NeedCountMax;
	int32	m_NeedLevel;
	int32	m_PRI;
	int32	m_AttId[EQUIP_ACTIVATION_ATT_NUM];
	int32	m_AttValue[EQUIP_ACTIVATION_ATT_NUM];
	CONSTRUCT_SELF(EQUIP_ACTIVATION_TB);
};

struct EQUIP_COLORCHANGE_TB
{
	uint32	m_YellowItem;
	uint32	m_NeedItem;
	uint32	m_NeedMoney;
	int32	m_NeedLevel;
	uint32	m_PurpleItem;
	CONSTRUCT_SELF(EQUIP_COLORCHANGE_TB);
};

struct EQUIP_PURPLE_REWORK_TB
{
	int32	m_Index;
	uint32	m_NeedItem;
	uint32	m_NeedMoney;
	CONSTRUCT_SELF(EQUIP_PURPLE_REWORK_TB);
};

struct EQUIP_PURPLEATTR_TB
{
	int32		m_AttId;
	float		m_fMin;
	float		m_fMax;
	int32		m_Min;
	int32		m_Max;
	ATTR_INFO	m_AttrInfo;
	uint32		m_Rate;
	CONSTRUCT_SELF(EQUIP_PURPLEATTR_TB);
};

struct GEM_REWORK_TB
{
	int32	m_Index;
	int32	m_NeedNum;
	int32	m_OtherNeedItem;
	int32	m_OtherNeedNum;
	int32	m_NeedMoney;
	int32	m_NewItem;
	int32	m_NewItemNum;
	CONSTRUCT_SELF(GEM_REWORK_TB);
};

struct EQUIP_COPY_TB
{
	int32	m_ItemId;
	int32	m_Type;
	CONSTRUCT_SELF(EQUIP_COPY_TB);
};

struct EQUIP_RECALL_TB
{
	uint32	m_ItemId;
	uint32	m_RecallType;
	uint32	m_RecallValue;
	CONSTRUCT_SELF(EQUIP_RECALL_TB);
};

struct TRANSITEM_POS_TB
{
	uint32 m_MapId;
	uint32 m_CountryLimit;
	CONSTRUCT_SELF(TRANSITEM_POS_TB);
};

struct ATTR_SUCK_BALL_TB
{
	uint32 m_ItemId;
	uint32 m_Rate;
	uint32	m_nNewItem[HEQUIP_NUMBER];
	ATTR_SUCK_BALL_TB()
		:m_ItemId(0), m_Rate(0)
	{
		for(int32 i = 0; i < HEQUIP_NUMBER; ++i)
		{
			m_nNewItem[i] = -1;
		}
	}
};

struct SERVER_EQUIP_POINT_INFO
{
	SERVER_EQUIP_POINT_INFO()
	{
		m_IsValid = 0;
		for(int32_t i = 0; i < HEQUIP_NUMBER; ++i)
		{
			m_nEquipPoint[i] = -1;
		}
	}
	int32_t	m_IsValid;
	uint32_t	m_nEquipPoint[HEQUIP_NUMBER];
};

struct SERVER_ATTR_SUCK_AMULET_TB
{
	uint32_t m_ItemId;
	uint32_t   m_Cost;
	SERVER_EQUIP_POINT_INFO	m_PointInfo[BLUE_ADD_MAX_ENCHASE];
	SERVER_ATTR_SUCK_AMULET_TB()
		: m_ItemId(0), m_Cost(0)
	{
	}
};

struct ATTR_SUCK_BALL_SYB_TB
{
	uchar  m_Level;
	uint32 m_Rate;
	uint32 m_ItemId;
	uint32 m_ItemCount;

	ATTR_SUCK_BALL_SYB_TB()
		:m_Level(0),m_Rate(0),m_ItemId(0),m_ItemCount(0)
	{
	}
};

struct EQUIP_PRODUCE_TB
{
	int32 m_EquipId;
	int32 m_EquipSetId;
	int32 m_MatId1;
	int32 m_MatCount1;
	int32 m_MatId2;
	int32 m_MatCount2;
	int32 m_MatId3;
	int32 m_MatCount3;
	int32 m_MatId4;
	int32 m_MatCount4;

	EQUIP_PRODUCE_TB()
	{
		memset(this, 0, sizeof(EQUIP_PRODUCE_TB));
	}
};


struct EQUIP_BLUEATTR_TB
{
	int32 m_AttrIdx;
	int32 m_AttrId;
	float m_fMinEff;
	float m_fMaxEff;
	int32 m_nMinEff;
	int32 m_nMaxEff;
	ATTR_INFO m_AttrInfo;
	int32 m_nSeed;

	EQUIP_BLUEATTR_TB()
	{
		memset(this, 0, sizeof(EQUIP_BLUEATTR_TB));
	}
};

//橙装蓝属性随机生成表
struct NEW_EQUIP_BLUEATTR_TB
{
	int32 m_AttrIdx;
	int32 m_AttrId;
	float m_fRate;
	ATTR_INFO m_AttrInfo;
	int32 m_nSeed;
	float m_fMinEff;
	float m_fMaxEff;
	int32	m_Attr[MAX_EQUIP_LEVEL];

	NEW_EQUIP_BLUEATTR_TB()
	{
		memset(this, 0, sizeof(NEW_EQUIP_BLUEATTR_TB));
	}
};

//橙装蓝属性打造的配置表
struct NEW_EQUIP_PRODUCE_TB
{
	int32 m_nEquipId;
	int32 m_nNeedMoney;
	int32 m_nNeedItem1;//图谱
	int32 m_nNeedItem1Count;
	int32 m_nNeedItem2;//生活材料
	int32 m_nNeedItem2Count;
	int32 m_nNeedItem3;//特殊材料
	int32 m_nNeedItem3Count; 
	int32 m_nNeedItem4;//添加剂
	int32 m_nNeedItem4Count;
	int32 m_nRate1[EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER];//没有添加剂时的概率
	int32 m_nRate2[EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER];//有添加剂时的概率

	NEW_EQUIP_PRODUCE_TB()
	{
		memset(this, 0, sizeof(NEW_EQUIP_PRODUCE_TB));
	}
};

//蓝属性强化表
struct EQUIP_BLUE_INTENSIFY_TB
{
	int32 m_AttrId;
	int32 m_AttrValue[BLUE_INTENSIFY_MAX_ENCHASE];
	int32 m_ReqIntensifyCount;//需要达到强化的次数，才能提升属性值

	EQUIP_BLUE_INTENSIFY_TB()
	{
		memset(this, 0, sizeof(EQUIP_BLUE_INTENSIFY_TB));
	}
};

struct EQUIP_SWITCH_TB
{
	int32 m_EquipSourceId;
	int32 m_EquipDestId;
	int32 m_Cost;
	int32 m_MaterialId;
	CONSTRUCT_SELF(EQUIP_SWITCH_TB);
};

struct CHANGE_APPEARANCE_TB
{
	uint32 m_ItemId;
	CONSTRUCT_SELF(CHANGE_APPEARANCE_TB);
};

struct EQUIP_CONST_ATTR_TB
{
	int32 m_AttrIndex;
	int32 m_AttrType;
	int32 m_AttrId;
	int32 m_AttrValue;
	uint32	m_nValidEquipType[EQUIP_TYPE_NUM];
	uint32 m_Rate;
	CONSTRUCT_SELF(EQUIP_CONST_ATTR_TB);
};

struct EQUIP_CONST_INFO_TB
{
	int32 m_ConstId;
	int32 m_ActConstId[MAX_EQUIP_CONST_ACTIVE_NEED];
	int32 m_Rate;
	CONSTRUCT_SELF(EQUIP_CONST_INFO_TB);
};

struct EQUIP_CONST_ACTIVE_POINT_TB
{
	int32 m_EquipPoint;
	int32 m_ActEquipPoint;
	CONSTRUCT_SELF(EQUIP_CONST_ACTIVE_POINT_TB);
};

struct EQUIP_CONST_BIND_TB
{
	uint32 m_NeedItemId;
	int32  m_NeedMoney;
	int32 m_AddConstCount[MAX_EQUIP_CONST_ATTR];
	int32  m_Rate[MAX_EQUIP_CONST_ATTR];
	CONSTRUCT_SELF(EQUIP_CONST_BIND_TB);
};

struct ITEM_SPECAIL_TB
{
	uint32 m_nItemId;
	int32  m_nUseType;
	CONSTRUCT_SELF(ITEM_SPECAIL_TB);
};

struct EQUIP_HONOR_BIND_TB
{
	int32  m_Index;
	int32  m_BindLevel;
	int32  m_NeedGem[MAX_EQUIP_HONOR_BIND_COND];
	int32  m_Rate[MAX_EQUIP_HONOR_BIND_COND];
	int32  m_Punish[MAX_EQUIP_HONOR_BIND_COND];
	int32  m_NeedMoney;
	int32  m_Intensify;
	CONSTRUCT_SELF(EQUIP_HONOR_BIND_TB);
};

// 道具表
class	ItemTemplateTable
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ItemTemplateTable();
	~ItemTemplateTable();

	void	Clear();
	BOOL	Init();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	MONSTER_DROP_TB		*GetMonsterDropTB(int32 iMonsterType);

	DROP_POS_TB		*GetDropPosTB(int32 nDropPoint);

	SEquipTab		*GetEquipTB(uint32 itemSerial);
	uint32			GetEquipPointValue(PLAYER_EQUIP equipPoint);
	PAI_INFO		*GetPaiInfo(uint32 nType);

	//获取随机牌型的牌ID,对于普通牌型返回自身牌ID
	int32           GetPaiIDByPaiType(int32 nType);

	EQUIP_ATT_SET_TB	*GetAttSetTB(int32 nSetID);
	EQUIP_ATT_SET_TB	*GetAttSetTBByRate(int32 nRate);
	uint32			GetSumRateByReqLevel(int32 nLevel);
	EQUIP_ATT_LEVEL_TB	*GetAttLevelValue(ITEM_PROPERTY iAtt);

	SMinMaxValue		GetItemValue(ITEM_PROPERTY iAtt, int32 QualityLevel);

	SDropAttrTab		*GetDropAttTB(int32 iDeltaLevel);

	SGemInfoTab		*GetGemInfoTB(uint32 itemSerial);
	EQUIPHOLE_INFO_TB	*GetEquipHoleInfoTB(uint32 nHoleNum);
	EQUIPSOUL_INFO_TB	*GetEquipSoulInfoTB(uint32 nIndex);
	EQUIPCHAIN_INFO_TB	*GetEquipChainInfoTB(uint32 nIndex);
	EQUIPCHAIN_INFO_TB	*GetEquipChainInfoTBByID(uint32 chainID);
	EQUIPLEVELUP_INFO	*GetEquipLeveupTB(EQUIP_LEVEL_TYPE nType, PLAYER_EQUIP equipPoint, uint32 nLevel);
	EQUIP_BIND_TB		*GetEquipBindTB(uint32 nLevel);
	EQUIP_SPECIALREPAIR_TB	*GetSpecialRepairTB(uint32 itemSerial);
	ITEM_PRODUCT_INFO_TB	*GetItemProductInfoTB(uint32 nProductID);
	MATERIAL_LEVEL_INFO_TB	*GetMaterialInfoTB(uint32 nLevel);
	EQUIPEXTRATT_TB		*GetEquipExtraAttInfoTB(PLAYER_EQUIP equipPoint, uint32 nScore);
	EXTRABAG_INFO_TB	*GetExtraBagInfoTB(uint32 itemSerial);
	CHANGEPAI_INFO_TB	*GetChangePaiInfoTB(uint32 itemSerial);
	CHANGEPAI_INFO_TB	*GetExchangeChangePaiInfoTB();

	SMiscItemInfoTab	*GetCommItemInfoTB(uint32 itemSerial);
	TASKITEM_INFO_TB	*GetTaskItemInfoTB(uint32 itemSerial);
	SEquipSetTab		*GetEquipSetTB(int32 EquipSetSerial);

	MARRYEFFECT_TB		*GetMarryEffectTB(int32 MarryLevel);
	int32			GetMarryEffectTBCount();
	FRIENDEFFECT_TB		*GetFriendEffectTB(int32 FriendLevel);
	int32			GetFriendEffectTBCount();

	SItemRulerTab		*GetRuleValueByID(int32 &iIndex);

	const FRIEND_GIFT_TB	*GetFriendGiftData(int32 nItemTableIndex) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	int32 GetAttCount()
	{
		return m_nAttLevelCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetAttSetCount()
	{
		return m_nEquipAttSetCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetEquipChainInfoCount()
	{
		return m_nEquipChainInfoCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetEquipSoulInfoCount()
	{
		return m_nEquipSoulInfoCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetEquipActivationTBCount() const
	{
		return m_nEquipActivationCount;
	}

	const EQUIP_ACTIVATION_TB	*GetEquipActivationTB(int32 index) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetEquipPurpleReworkCount() const
	{
		return m_nEquipPurpleReworkCount;
	}

	const EQUIP_PURPLE_REWORK_TB	*GetEquipPurpleReworkTB(int32 index) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetEquipColorChangeCount() const
	{
		return m_nEquipColorChangeCount;
	};
	const EQUIP_COLORCHANGE_TB	*GetEquipColorChangeTB(uint32 itemSerial) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetEquipPurpleAttrCount() const
	{
		return m_nEquipPurpleAttrCount;
	};
	const EQUIP_PURPLEATTR_TB	*GetEquipPurpleAttrTB(int32 index) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetEquipPurpleAttrRateSum() const
	{
		return m_nEquipPurpleAttrRateCount;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetGemReworkCount() const
	{
		return m_uGemReworkCount;
	};
	const GEM_REWORK_TB	*GetGemReworkTB(uint32 index) const;
	const EQUIP_COPY_TB	*GetEquipCopyTB(uint32 itemId) const;

	uint32 GetEquipRecallCount() const
	{
		return m_uEquipRecallCount;
	}
	const EQUIP_RECALL_TB *GetEquipRecallTB(uint32 itemId) const;

	uint32 GetTransItemPosCount() const
	{
		return m_uTransItemPosCount;
	}
	const TRANSITEM_POS_TB *GetTransItemPosTB(uint32 mapId) const;

	uint32 GetAttrSuckBallCount() const
	{
		return m_uAttrSuckBallCount;
	}
	const ATTR_SUCK_BALL_TB *GetAttrSuckBallTB(uint32 itemId) const;

	uint32 GetAttrSuckAmuletCount() const
	{
		return m_uAttrSuckAmuletCount;
	}
	const SERVER_ATTR_SUCK_AMULET_TB*GetAttrSuckAmuletTB(uint32 itemId) const;

	uint32 GetAttrSuckBallSynCount() const
	{
		return m_uAttrSuckBallSynCount;
	}
	const ATTR_SUCK_BALL_SYB_TB *GetAttrSuckBallSynTB(uchar cLevel) const;

	uint32 GetEquipProduceCount() const
	{
		return m_uEquipProduceCount;
	}
	const EQUIP_PRODUCE_TB *GetEquipProduceTB(uint32 itemId) const;

	uint32 GetEquipBlueAttrCount() const
	{
		return m_uEquipBlueAttrCount;
	}
	const EQUIP_BLUEATTR_TB *GetEquipBlueAttrTB(uint32 itemId) const;

	uint32 GetEquipBlueIntensifyCount() const
	{
		return m_uEquipBlueIntensifyCount;
	}
	const EQUIP_BLUE_INTENSIFY_TB *GetEquipBlueIntensifyTB(uint32 itemId) const;

	uint32 GetEquipSwitchCount() const
	{
		return m_nEquipSwitchCount;
	};
	const EQUIP_SWITCH_TB *GetEquipSwitchTB(uint32 itemSerial) const;

	uint32 GetChangeAppearanceCount() const
	{
		return m_nChangeAppearanceCount;
	};

	const CHANGE_APPEARANCE_TB *GetChangeAppearanceTB(uint32 itemSerial) const;

	//橙装蓝属性相关
	uint32 GetNewEquipBlueAttrCount() const
	{
		return m_nNewEquipBlueAttrCount;
	};

	uint32 GetNewEquipBlueAttrMaxSed() const
	{
		return m_nNewEquipBlueAttrMaxSed;
	};

	//星座铭刻相关
	const NEW_EQUIP_BLUEATTR_TB *GetNewEquipBlueAttrTB(uint32 nTableIndex) const;

	uint32 GetEquipBlueProdcueCount() const
	{
		return m_nNewEquipProduceCount;
	};

	const NEW_EQUIP_PRODUCE_TB *GetNewEquipProduceTB(uint32 nEquipId) const;

	uint32 GetEquipConstAttrCount() const
	{
		return m_nEquipConstAttrCount;
	};

	uint32 GetEquipConstAttrMaxSed(uint32 nAttrType) const
	{
		if (nAttrType >=0 && nAttrType < CONST_ATTR_TYPE_NUMBER)
		{
			return m_nEquipConstAttrMaxSed[nAttrType];
		}
		return 0;
	};
	uint32 GetEquipConstAttrTypeCount(uint32 nAttrType) const
	{
		if (nAttrType >=0 && nAttrType < CONST_ATTR_TYPE_NUMBER)
		{
			return m_nEquipConstAttrTypeCount[nAttrType];
		}
		return 0;
	};

	const EQUIP_CONST_ATTR_TB *GetEquipConstAttrTB(uint32 nAttrIndex) const;

	uint32 GetEquipConstInfoCount() const
	{
		return m_nEquipConstInfoCount;
	};

	uint32 GetEquipConstMaxSed() const
	{
		return m_nEquipConstMaxSed;
	};
	
	const EQUIP_CONST_INFO_TB *GetEquipConstInfoTB(int32 nConstId) const;

	uint32 GetEquipConstActivePointCount() const
	{
		return m_nEquipConstActivePointCount;
	};

	const EQUIP_CONST_ACTIVE_POINT_TB *GetEquipConstActivePointTB(int32 nEquipPoint) const;

	uint32 GetEquipConstBindCount() const
	{
		return m_nEquipConstBindCount;
	};

	const EQUIP_CONST_BIND_TB *GetEquipConstBindTB(uint32 nItemId) const;

	//特殊道具表相关
	uint32 GetItemSpecialCount() const
	{
		return m_nItemSpecialCount;
	};

	const ITEM_SPECAIL_TB *GetItemSpecialTB(const uint32 nItemId,const int32 nUseType) const;

	//荣誉铭刻
	uint32 GetEquipHonorBindCount() const
	{
		return m_nEquipHonorBindCount;
	};

	const EQUIP_HONOR_BIND_TB *GetEquipHonorBindTB(const int32 nBindLevel) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	// 初始化装备基础表
	void	InitEquipTable();
	// 初始化蓝属性等级
	void	InitAttLevelTable();
	// 初始化蓝属性设置
	void	InitEquipATTSetTable();

	// 初始化怪物掉落表
	void	InitMonsterDropTable();
	// 初始化宝石信息表
	void	InitGemInfoTable();
	// 初始化道具合成表
	void	InitCommItemInfoTable();
	// 初始化装备打孔表
	void	InitEquipHoleInfoTable();
	// 初始化装备升级表
	void	InitEquipLevelupInfoTable();
	// 初始化装备绑定表
	void	InitEquipBindInfoTable();
	// 初始化特殊修理表
	void	InitSpecialRepairInfoTable();
	// 初始化装备打造表
	void	InitProductInfoTable();
	// 初始化材料等级表
	void	InitMaterialLevelInfoTable();
	// 初始化装备扩展属性表
	void	InitEquipExtraInfoTable();
	// 初始化装备点
	void	InitEquipPointInfoTable();
	// 初始化扩展背包
	void	InitExtraBagInfoTable();
	// 初始化改变麻将
	void	InitChangePaiInfoTable();
	// 初始化麻将信息表
	void	InitPaiInfoTable();
	// 初始化麻将一副牌需求
	void	InitEquipChainInfoTable();
	// 初始化麻将翻种表
	void	InitEquipSoulInfoTable();

	// 初始化任务道具表
	void	InitTaskItemInfoTable();
	// 初始化掉落属性表
	void	InitDropAttTable();
	// 初始化掉落位置表
	void	InitItemDropPos();
	// 初始化套装属性表
	void	InitEquipSetAttrTable();
	// 初始化结婚效果表
	void	InitEffectMarryTable();
	// 初始化朋友效果表
	void	InitEffectFriend();

	// 初始化道具公式表
	void	InitItemRulerTable();
	// 初始化朋友属性表
	void	InitFriendGiftTable();
	// 初始化装备激活表
	void	InitEquipActivationTable();
	// 初始化装备颜色改变表
	void	InitEquipColorChangeTable();
	// 初始化装备紫色改造，只有一项
	void	InitEquipPurpleReworkTable();
	// 初始化装备紫色属性
	void	InitEquipPurpleAttrTable();
	// 初始化宝石改造
	void	InitGemReworkTable();
	// 初始化装备复制
	void	InitEquipCopyTable();
	// 初始化装备回收
	void	InitEquipRecallTable();
	// 初始化传送符可传送的场景表
	void	InitTransItemPosTable();
	// 初始化蓝属性吸收玩法中能量球的配置
	void	InitAttrSuckBallTable();
	// 初始化蓝属性吸收玩法中护身符的配置
	void	InitAttrSuckAmuletTable();
	//初始化蓝属性吸收玩法中护身符补色
	void	InitAttrSuckBallSynTable();
	// 初始化打造装备配置
	void	InitEquipProduceTable();
	// 初始化蓝色属性表
	void	InitEquipBlueAttrTable();
	// 初始化蓝色强化表
	void	InitEquipBlueIntensifyTable();
	// 初始化装备转化
	void	InitEquipSwitchTable();
	// 初始更换形象表
	void	InitChangeAppearanceTable();
	// 初始橙装蓝属性表
	void	InitNewEquipBlueAttrTable();

	// 初始橙装蓝属性打造配置表
	void	InitNewEquipProduceTable();

	//星座铭刻
	void	InitEquipConstAttrTable();
	void	InitEquipConstInfoTable();
	void	InitEquipConstActivePointTable();
	void	InitEquipConstBindTable();

	//初始化特殊道具表
	void	InitItemSpecialTable();

	//初始化荣誉道具
	void	InitEquipHonorBindTable();
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	uint32			m_nAttLevelCount;
	EQUIP_ATT_LEVEL_TB	*m_pAttLevelTableData;

	uint32			m_nEquipAttSetCount;
	EQUIP_ATT_SET_TB	*m_pEquipAttSetTableData;

	uint32			m_nEquipCount;
	SEquipTab		*m_pEquipTableData;

	uint32			m_nDropBoxCount;
	SDropBoxTab		*m_pDropBoxTableData;

	uint32			m_nMonsterDropCount;
	MONSTER_DROP_TB		*m_pMonsterDropTableData;

	uint32			m_nGemCount;
	SGemInfoTab		*m_pGemInfoData;

	uint32			m_nEquipHoleInfoCount;
	EQUIPHOLE_INFO_TB	*m_EquipHoleInfoData;

	EQUIP_LEVELUP_TB	m_EquipLeveupInfoData[HEQUIP_NUMBER];

	uint32			m_nEquipBindInfoCount;
	EQUIP_BIND_TB		*m_EquipBindInfoData;

	uint32			m_nSpecialRepairCount;
	EQUIP_SPECIALREPAIR_TB	*m_EquipSpecialRepairData;

	uint32			m_nProductCount;
	ITEM_PRODUCT_INFO_TB	*m_pProductInfoData;

	uint32			m_nMaterialLevelInfoCount;
	MATERIAL_LEVEL_INFO_TB	*m_MaterialLevelInfoData;

	uint32			m_nEquipExtraInfoCount;
	EQUIPEXTRATT_TB		*m_EquipExtraInfoData;

	uint32			m_nExtraBagInfoCount;
	EXTRABAG_INFO_TB	*m_pExtraBagInfoData;

	uint32			m_nEquipChainInfoCount;
	EQUIPCHAIN_INFO_TB	*m_EquipChainInfoData;

	uint32			m_nEquipSoulInfoCount;
	EQUIPSOUL_INFO_TB	*m_EquipSoulInfoData;

	uint32			m_nChangePaiInfoCount;
	CHANGEPAI_INFO_TB	*m_pChangePaiInfoData;

	uint32			m_nCommItemCount;
	SMiscItemInfoTab	*m_pCommItemInfoData;

	uint32			m_nTaskItemCount;
	TASKITEM_INFO_TB	*m_pTaskItemInfoData;

	uint32			m_nDropAttCount;
	SDropAttrTab		*m_pDropAttData;

	uint32			m_nDropPosCount;
	DROP_POS_TB		*m_pDropPosData;

	uint32			m_nEquipSetCount;
	SEquipSetTab		*m_pEquipSetData;

	uint32			m_nMarryEffectCount;
	MARRYEFFECT_TB		*m_pMarryEffectData;

	uint32			m_nFriendEffectCount;
	FRIENDEFFECT_TB		*m_pFriendEffectData;

	uint32			m_nItemRulerCount;
	int32			m_nHashOffSet;
	SItemRulerTab		*m_pItemRulerData;

	uint32			m_nFriendGiftCount;
	FRIEND_GIFT_TB		*m_pFriendGiftData;

	uint32			m_nEquipActivationCount;
	EQUIP_ACTIVATION_TB	*m_pEquipActivationData;

	uint32			m_nEquipColorChangeCount;
	EQUIP_COLORCHANGE_TB	*m_pEquipColorChangeData;

	uint32			m_nEquipPurpleReworkCount;
	EQUIP_PURPLE_REWORK_TB	*m_pEquipPurpleReworkData;

	uint32			m_nEquipPurpleAttrCount;
	EQUIP_PURPLEATTR_TB	*m_pEquipPurpleAttrData;
	uint32			m_nEquipPurpleAttrRateCount;

	uint32			m_uGemReworkCount;
	GEM_REWORK_TB		*m_pGemReworkData;

	uint32			m_uEquipCopyCount;
	EQUIP_COPY_TB		*m_pEquipCopyData;

	uint32          m_uEquipRecallCount;
	EQUIP_RECALL_TB		*m_pEquipRecallData;

	uint32			m_uTransItemPosCount;
	TRANSITEM_POS_TB	*m_pTransItemPosData;//传送符可传送的场景表 
	//属性吸收
	uint32			m_uAttrSuckBallCount;
	ATTR_SUCK_BALL_TB	*m_pAttrSuckBallData;
	uint32			m_uAttrSuckAmuletCount;
	SERVER_ATTR_SUCK_AMULET_TB*m_pAttrSuckAmuletData;

	uint32			m_uAttrSuckBallSynCount;
	ATTR_SUCK_BALL_SYB_TB	*m_pAttrSuckBallSynData;

	uint32				m_uEquipProduceCount;
	EQUIP_PRODUCE_TB*	m_pEquipProduceData;

	uint32				m_uEquipBlueAttrCount;
	EQUIP_BLUEATTR_TB*	m_pEquipBlueAttrData;

	//蓝属性强化相关
	uint32				m_uEquipBlueIntensifyCount;
	EQUIP_BLUE_INTENSIFY_TB* m_pEquipBlueIntensifyData;

	uint32			m_nEquipSwitchCount;
	EQUIP_SWITCH_TB	*m_pEquipSwitchData;

	uint32			m_nEquipPointInfo[HEQUIP_NUMBER];
	PAI_INFO		m_nPaiInfo[EQUIP_PAI_NUM];

	uint32					m_nChangeAppearanceCount;
	CHANGE_APPEARANCE_TB	*m_pChangeAppearanceData;

	//橙装蓝属性
	uint32						m_nNewEquipBlueAttrCount;
	int32						m_nNewEquipBlueAttrMaxSed;
	NEW_EQUIP_BLUEATTR_TB	*m_pNewEquipBlueAttrData;

	//橙装蓝属性打造配置
	uint32                      m_nNewEquipProduceCount;
	NEW_EQUIP_PRODUCE_TB       *m_pNewEquipProduceData;

	//星座铭刻
	uint32						m_nEquipConstAttrCount;
	int32						m_nEquipConstAttrMaxSed[CONST_ATTR_TYPE_NUMBER];
	int32						m_nEquipConstAttrTypeCount[CONST_ATTR_TYPE_NUMBER];
	EQUIP_CONST_ATTR_TB			*m_pEquipConstAttrData;
	
	uint32						m_nEquipConstInfoCount;
	int32						m_nEquipConstMaxSed;
	EQUIP_CONST_INFO_TB         *m_pEquipConstInfoData;

	uint32						m_nEquipConstActivePointCount;
	EQUIP_CONST_ACTIVE_POINT_TB *m_pEquipConstActivePointData;

	uint32						m_nEquipConstBindCount;
	EQUIP_CONST_BIND_TB         *m_pEquipConstBindData;

	//特殊道具表
	uint32						m_nItemSpecialCount; 
	ITEM_SPECAIL_TB			    *m_pItemSpecialData;

	//荣誉铭刻
	uint32						m_nEquipHonorBindCount;
	EQUIP_HONOR_BIND_TB         *m_pEquipHonorBindData;


};

uchar			GetMaxItemTile(SItemType &it);

uint32			GetItemMaxLayedNum(uint32 Serial);
uchar			GetItemRuler(uint32 itemIndex);

extern ItemTemplateTable	g_ItemTab;
#endif
