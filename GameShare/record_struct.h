/*$T MapServer/Server/Base/record_struct.h GC 1.140 10/10/09 10:07:21 */

/*
$File Name:
	record_struct.h
$Purpose:
	定义所有游戏系统行为日志的格式
$Update history:
	v1.0 created.
*/
#ifndef _RECORD_STRUCT_H_
#define _RECORD_STRUCT_H_

/*
 * ifndef __RECORD_GAMEWAY_H_ ;
 * #error "Not direct include record_struct.h, Please include record_gameway.h" ;
 * #endif
 */
#include "act_define.h"

struct ItemLogRecordInfo
{
	GUID_t		CharGUID;			/* 自身角色,物品所有者 */
	char		Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	char		TargetName[MAX_CHARACTER_NAME]; /* 目标角色名字 */
	char		IP[IP_SIZE];			/* 所在server IP */
	SItemGuid	ItemGuid;			/* 物品编号 */
	uint32		ItemType;			/* 物品全局编号 */
	GUID_t		TargetGUID;			/* 目标角色 */
	eItemActType	OpType;			/* 操作类型 */
	char		OpDesc[128];		/* 操作描述 */
	eItemActType	SecOpType;		/* 转向类型 */
	uint8		ContainerPos;		/* 容器位置 */
	uint8		DestContainerPos;	/* 目标容器位置 */
	uint32		Count;			/* 变化个数 */
	MapID_t		MapID;			/* 场景编号 */
	int32		NpcType;		/* npc 类型,掉落时填怪物类型 */
	float		XPos;			/* 事件发生位置 */
	float		ZPos;
	int32		ShopGUID;		/* 相关商店号 */
	uint8		GemMax;			/* 最大宝石个数(蓝装必须要) */
	int32		ScriptID;		/* 脚本ID */
	int32		WorldID;		/* 服务器ID */

	ItemLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = TargetGUID = -1;
		OpType = OpType = eItemAct_Unknow;
		ContainerPos = DestContainerPos = -1;
		Count = 1;
		MapID = NpcType = -1;
		XPos = ZPos = 0.0f;
		ShopGUID = -1;
		GemMax = 0;
		ItemType = 0;
		ScriptID = -1;
		WorldID = 0;
		memset(Name, 0, sizeof(Name));
		memset(TargetName, 0, sizeof(TargetName));
		memset(IP, 0, sizeof(IP));
		memset(OpDesc, 0, sizeof(OpDesc));
	}
};

struct EquipLogRecordInfo
{
	GUID_t		CharGUID;	/* 自身角色,物品所有者 */
	char		Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	char		IP[IP_SIZE];			/* 所在server IP */
	SItemGuid	ItemGuid;			/* 物品编号 */
	uint32		ItemType;			/* 物品全局编号 */
	eEquipActType	OpType;		/* 操作类型 */
	uint8		Level;		/* 星级 */
	uint8		MaJiang;	/* 麻将 */
	_ITEM_PROPERTY	AttContent[MAX_EQUIP_EXT_ATTR]; /* 装备属性 */
	MapID_t		MapID;			/* 场景编号 */
	int32		WorldID;	/* 服务器ID */

	EquipLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = -1;
		OpType = eEquipAct_Unknow;
		ItemType = Level = 0;
		MaJiang = INVALID_PAI_TYPE;
		for(int32 i = 0; i < MAX_EQUIP_EXT_ATTR; ++i) AttContent[i].Clear();
		memset(Name, 0, sizeof(Name));
		memset(IP, 0, sizeof(IP));
		ItemGuid.Reset();
		MapID = -1;
		WorldID = 0;
	}
};

struct CurrencyLogRecordInfo
{
	GUID_t			CharGUID;			/* 自身角色,money所有者 */
	GUID_t			TargetGUID;			/* 目标角色 */
	eCurrencyActType	OPType;				/* 操作类型 */
	uint8			MoneyType;			/* 金钱类型 */
	int32			Count;				/* 数量 */
	int32			RemainCount;			/* 剩余金钱总数量 */
	MapID_t			MapID;				/* 场景编号 */
	float			XPos;				/* 事件发生位置 */
	float			ZPos;
	char			Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	int32			ItemIndex;			/* 物品编号(当购买时候有效) */
	int32			ItemCount;			/* 购买物品数量 */
	SHorseGiud		PetGUID;			/* 宠物GUID */
	ScriptID_t		ScriptId;			/* 脚本id*/
	int16			nExt;				/* 保留nExt, 用于扩展更精确的金钱的记录*/
	int32			WorldID;			/* 服务器ID */

	CurrencyLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = TargetGUID = INVALID_ID;
		OPType = eCurrencyAct_Unknow;
		MoneyType = 0;
		Count = 0;
		MapID = -1;
		XPos = ZPos = 0.0f;
		memset(Name, 0, sizeof(Name));
		ItemIndex = -1;
		ItemCount = 0;
		PetGUID.m_uHighSection = 0;
		PetGUID.m_uLowSection = 0;
		ScriptId = 0;
		nExt = 0;	
		WorldID = 0;
	}
};

struct PetLogRecordInfo
{
	GUID_t		CharGUID;	/* 自身角色,Pet所有者 */
	GUID_t		TargetGUID;	/* 目标角色 */
	ePetActType	OPType;		/* 操作类型 */
	MapID_t		MapID;		/* 场景编号 */
	float		XPos;		/* 事件发生位置 */
	float		ZPos;
	SHorseGiud	PetGUID;	/* 宠物GUID */
	int32		DataID;		/* 宠物类型 */
	int32		WorldID;	/* 服务器ID */

	PetLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;
		TargetGUID = INVALID_ID;
		OPType = ePetAct_Unknow;
		MapID = -1;
		DataID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		WorldID = 0;
		PetGUID.m_uHighSection = 0;
		PetGUID.m_uLowSection = 0;
	}
};
struct SkillLogRecordInfo
{
	GUID_t		CharGUID;	/* 自身角色,Skill所有者 */
	eSkillActType	OPType;		/* 操作类型 */
	MapID_t		MapID;		/* 场景编号 */
	float		XPos;		/* 事件发生位置 */
	float		ZPos;
	SpellID_t	SkillID;	/* 技能号 */
	int32		Level;		/* 级别 */
	int32		Count;		/* 技能 */
	int32		WorldID;	/* 服务器ID */

	SkillLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;
		OPType = eSkillAct_Unknow;
		MapID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		SkillID = -1;
		Level = -1;
		Count = 0;
		WorldID = 0;
	}
};

struct AbilityLogRecordInfo
{
	GUID_t		CharGUID;	/* 自身角色,Skill所有者 */
	eAbilityActType OPType;		/* 操作类型 */
	MapID_t		MapID;		/* 场景编号 */
	float		XPos;		/* 事件发生位置 */
	float		ZPos;
	SpellID_t	AbilityID;	/* 技能号 */
	int32		Level;		/* 级别 */
	int32		Count;
	int32		WorldID;

	AbilityLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;
		OPType = eAbilityAct_Unknow;
		MapID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		AbilityID = -1;
		Level = -1;
		Count = 0;
		WorldID = 0;
	}
};

struct QuestLogRecordInfo
{
	GUID_t		CharGUID;	/* 自身角色,Skill所有者 */
	eQuestActType	OPType;		/* 操作类型 */
	MapID_t		MapID;		/* 场景编号 */
	float		XPos;		/* 事件发生位置 */
	float		ZPos;
	QuestID_t	idMission;
	ScriptID_t	idScript;
	uint8		yFlags;
	uint32		aParam[MAX_QUEST_PARAM_NUM];
	int32		nDoneFlagIndex;
	int32		nDoneFlagValue;
	int32		nDataIndex;
	int32		nDataValue;

	QuestLogRecordInfo (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;		/* 自身角色,Skill所有者 */
		OPType = eQuestAct_Unknow;	/* 操作类型 */
		MapID = INVALID_ID;		/* 场景编号 */
		XPos = 0.0f;			/* 事件发生位置 */
		ZPos = 0.0f;
		idMission = INVALID_ID;
		idScript = INVALID_ID;
		yFlags = 0;
		memset(aParam, 0, sizeof(uint32) * MAX_QUEST_PARAM_NUM);
		nDoneFlagIndex = INVALID_INDEX;
		nDoneFlagValue = 0;
		nDataIndex = INVALID_INDEX;
		nDataValue = 0;
	}
};

struct TeamMemberLvlAndJob
{
	int32	Level;
	int32	Job;
	TeamMemberLvlAndJob (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		Job = Level = -1;
	}
};

struct GameWayLogRecoreInfo
{
	GUID_t			CharGUID;			/* 自身角色 */
	char			Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	MapID_t			MapID;	/* 场景编号 */
	int32			GameID;
	uint8			HaveTeam;
	uint8			member_cnt;
	int32			WorldID;		/* 服务器ID */
	TeamMemberLvlAndJob	member[MAX_TEAM_MEMBER];

	GameWayLogRecoreInfo (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		CharGUID = INVALID_ID;		/* 自身角色,Skill所有者 */
		MapID = INVALID_ID;		/* 场景编号 */
		GameID = INVALID_ID;
		HaveTeam = 0;
		member_cnt = 0;
		WorldID = 0;
		for(int32 i = 0; i < MAX_TEAM_MEMBER; ++i) member[i].clear();
	}
};

struct EnterSceneLogRecordInfo
{
	GUID_t	CharGUID;			/* 自身角色 */
	char	Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	MapID_t MapID;	/* 场景编号 */
	int32	GameID;
	int32	DayCount;
	int32	WorldID;

	EnterSceneLogRecordInfo (void)
	{
		clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear()
	{
		CharGUID = INVALID_ID;	/* 自身角色,Skill所有者 */
		MapID = INVALID_ID;	/* 场景编号 */
		GameID = INVALID_ID;
		DayCount = 0;
		WorldID = 0;
	}
};

struct GoldCardLogRecordInfo
{
	GUID_t	guidChar;		/* 玩家GUID */
	char	Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	MapID_t mapId;		/* 场景ID */
	int32	iChangeType;	/* 变更类型 */
	int32	iCostTypeId;	/* 金钱类型 */
	uint32	uPayment;	/* 金钱变更数量 */
	uint32	uItemTypeID;	/* 获得物品ID */
	int32	iItemCount;	/* 获得物品数量 */
	int32	WorldID;

	GoldCardLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		guidChar = INVALID_ID;
		mapId = INVALID_ID;
		iChangeType = INVALID_ID;
		uItemTypeID = 0;
		uPayment = 0;
		iCostTypeId = INVALID_ID;
		memset(Name, 0, sizeof(Name));
		WorldID = 0;
	}
};

enum ManageLogType
{
	MLT_ONLENE_USER_COUNT	= 0,
	MLT_ONLENE_ITEM,
	MLT_ONLENE_MONEY,
	MLT_ONLENE_IB,
	MLT_ONLENE_TRADE,
	MLT_ONLENE_EQUIP,
};

struct TradeLogRecordInfo
{
	struct ItemParam
	{

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void clear(void)
		{
			m_nItemId = INVALID_ID;
			m_nCount = 0;
			m_nItemGuid.Reset();
		}

		int32		m_nItemId;
		SItemGuid	m_nItemGuid;
		int32		m_nCount;
	};
	struct TradeParam
	{
		enum eTradeType { eExchange = 0, eStallSiller, eStallGold };

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void clear(void)
		{
			m_nCharGuid = INVALID_GUID;
			memset(m_szCharName, 0, sizeof(m_szCharName));
			m_nSceneId = INVALID_ID;
			m_nTradeType = eExchange;
			m_nPreGold = 0;
			m_nAftGold = 0;
			for(int32 i = 0; i < EXCHANGE_BOX_SIZE; ++i) m_anItem[i].clear();
			m_nPetId = INVALID_ID;
			m_nPetGuid.Reset();
		}

		GUID_t		m_nCharGuid;
		char		m_szCharName[MAX_CHARACTER_NAME];
		MapID_t		m_nSceneId;
		int32		m_nTradeType;
		int32		m_nPreGold;
		int32		m_nAftGold;
		ItemParam	m_anItem[EXCHANGE_BOX_SIZE];
		int32		m_nPetId;
		SHorseGiud	m_nPetGuid;
	};

	TradeLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		for(int32 i = 0; i < 2; ++i) m_anTradeParam[i].clear();
		m_WorldID = 0;
	}

	TradeParam	m_anTradeParam[2];
	int32		m_WorldID;
};

struct WorldShopLogRecordInfo
{
	GUID_t			OwnerGUID;	/* 所有者GUID */
	GUID_t			BuyerGUID;	/* 购买者GUID */
	eWorldShopCashActType	OPType;		/* 操作类型 */
	int32			ShopId;		/* 商店ID */
	uint32			SerialId;	/* 商店中的位置,-1表示不需要位置 */
	int32			SellGold;	/* 寄售/银行领取现金数 */
	int32			GoldNum;	/* 银行领取时记录的现金笔数 */
	int32			Price;		/* 售价 */
	int32			SillerNum;	/* 银行领取时记录的现银笔数 */
	int32			Charge;		/* 手继费 */
	uint32			CreateTime;	/* 创建时间 */
	uint32			DeleteTime;	/* 删除时间 */
	MapID_t			MapID;		/* 场景ID */
	int32			WorldID;	/* 服务器ID */

	WorldShopLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		OwnerGUID = INVALID_ID;
		BuyerGUID = INVALID_ID;
		OPType = eWorldShopCashAct_Unknow;
		ShopId = -1;
		SerialId = -1;
		SellGold = 0;
		GoldNum = 0;
		Price = 0;
		SillerNum = 0;
		Charge = 0;
		CreateTime = -1;
		DeleteTime = -1;
		MapID = -1;
		WorldID = 0;
	}
};

struct GLGoldShopLogRecordInfo
{
	GUID_t			OwnerGUID;	/* 所有者GUID */
	GUID_t			BuyerGUID;	/* 购买者GUID */
	eWorldShopCashActType	OPType;		/* 操作类型 */
	int32			ShopId;		/* 商店ID */
	uint32			SerialId;	/* 商店中的位置,-1表示不需要位置 */
	int32			SellGold;	/* 寄售/银行领取现金数 */
	int32			GoldNum;	/* 银行领取时记录的现金笔数 */
	int32			Price;		/* 售价 */
	int32			SillerNum;	/* 银行领取时记录的现银笔数 */
	int32			Charge;		/* 手继费 */
	uint32			CreateTime;	/* 创建时间 */
	uint32			DeleteTime;	/* 删除时间 */

	GLGoldShopLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		OwnerGUID = INVALID_ID;
		BuyerGUID = INVALID_ID;
		OPType = eWorldShopCashAct_Unknow;
		ShopId = -1;
		SerialId = -1;
		SellGold = 0;
		GoldNum = 0;
		Price = 0;
		SillerNum = 0;
		Charge = 0;
		CreateTime = -1;
		DeleteTime = -1;
	}
};

struct CheatActLogRecordInfo
{
	char		Account[MAX_ACCOUNT + 1];		/* 帐号 */
	char		CharName[MAX_CHARACTER_NAME + 1];	/* 角色名字 */
	GUID_t		OwnerGUID;	/* 所有者GUID */
	eCheatActType	OPType;		/* 操作类型 */
	MapID_t		MapID;		/* 场景ID */
	uint32		Offset;		/* 随机的偏移量 */
	float		PosX;		/* 角色当前X坐标 */
	float		PosZ;		/* 角色当前Z坐标 */
	int32		WorldID;	/* 服务器ID */

	/*
	 * 移动时起点坐标X+Z，或者是心跳、锁定时的ObiId ;
	 * 登陆验证： 0:基础加密模式，1：随机加密模式，2：时间加密模式
	 */
	uint32		Param;

	CheatActLogRecordInfo()
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		memset(Account, 0, sizeof(Account));
		memset(CharName, 0, sizeof(CharName));
		OwnerGUID = INVALID_ID;
		OPType = eCheatAct_Unknow;
		MapID = INVALID_ID;
		Offset = -1;
		PosX = 0;
		PosZ = 0;
		Param = 0;
		WorldID = 0;
	}
};

struct ReturnToChildLogRecordInfo
{
	uint32	m_uHighSection;
	uint32	m_uLowSection;
	int32	m_nBaseStr;
	int32	m_nBaseCon;
	int32	m_nBaseDex;
	int32	m_nBaseInt;
	int32	m_nExtStr;
	int32	m_nExtCon;
	int32	m_nExtDex;
	int32	m_nExtInt;
	int32	m_nSkill[PET_MAX_SKILL_COUNT];

	ReturnToChildLogRecordInfo()
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
		m_nBaseStr = 0;
		m_nBaseCon = 0;
		m_nBaseDex = 0;
		m_nBaseInt = 0;
		m_nExtStr = 0;
		m_nExtCon = 0;
		m_nExtDex = 0;
		m_nExtInt = 0;
		memset(m_nSkill, 0, sizeof(m_nSkill));
	}

	void Init(_HORSE_DB* data)
	{
		KCheck(data);

		m_uHighSection = data->m_GUID.m_uHighSection;
		m_uLowSection = data->m_GUID.m_uLowSection;

		m_nBaseStr= data->m_BaseAttrLevel1.m_pAttr[0];
		m_nBaseCon= data->m_BaseAttrLevel1.m_pAttr[1];
		m_nBaseDex= data->m_BaseAttrLevel1.m_pAttr[3];
		m_nBaseInt= data->m_BaseAttrLevel1.m_pAttr[2];

		m_nExtStr = data->m_iStrengthPerception;
		m_nExtCon = data->m_iConstitutionPerception;
		m_nExtDex = data->m_iSmartnessPerception;
		m_nExtInt = data->m_iMindPerception;
		for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
		{
			m_nSkill[i] = data->m_SkillList[i].m_nSkillID;
		}
	}
};

//宠物技能日志
struct PetSkillLogRecordInfo
{
	uint32	m_uHighSection;
	uint32	m_uLowSection;
	int32	m_nBaseStr;
	int32	m_nBaseCon;
	int32	m_nBaseDex;
	int32	m_nBaseInt;
	int32	m_nExtStr;
	int32	m_nExtCon;
	int32	m_nExtDex;
	int32	m_nExtInt;
	int32	m_nSkill[PET_MAX_SKILL_COUNT];

	PetSkillLogRecordInfo()
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
		m_nBaseStr = 0;
		m_nBaseCon = 0;
		m_nBaseDex = 0;
		m_nBaseInt = 0;
		m_nExtStr = 0;
		m_nExtCon = 0;
		m_nExtDex = 0;
		m_nExtInt = 0;
		memset(m_nSkill, 0, sizeof(m_nSkill));
	}

	void Init(const _HORSE_DB* data)
	{
		KCheck(data);

		m_uHighSection = data->m_GUID.m_uHighSection;
		m_uLowSection = data->m_GUID.m_uLowSection;

		m_nBaseStr= data->m_BaseAttrLevel1.m_pAttr[0];
		m_nBaseCon= data->m_BaseAttrLevel1.m_pAttr[1];
		m_nBaseDex= data->m_BaseAttrLevel1.m_pAttr[3];
		m_nBaseInt= data->m_BaseAttrLevel1.m_pAttr[2];

		m_nExtStr = data->m_iStrengthPerception;
		m_nExtCon = data->m_iConstitutionPerception;
		m_nExtDex = data->m_iSmartnessPerception;
		m_nExtInt = data->m_iMindPerception;
		for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
		{
			m_nSkill[i] = data->m_SkillList[i].m_nSkillID;
		}
	}
};

struct IBInItemLogRecordInfo
{
	GUID_t		CharGUID;			/* 自身角色,物品所有者 */
	char		Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	SItemGuid	ItemGuid;			/* 物品编号 */
	uint32		ItemType;			/* 物品全局编号 */
	uint32		OpType;			/* 操作类型 */
	uint32		Count;			/* 个数 */
	uint32		GoldCash;		/* 现金数 */
	uint32		TermTime;		/* 有效期 */
	MapID_t		MapID;			/* 场景ID */
	int32		WorldID;		/* 服务器ID */

	IBInItemLogRecordInfo (void)
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		CharGUID =  -1;
		Count = 1;
		ItemType = 0;
		TermTime = 0;
		GoldCash = 0;
		WorldID = 0;
		MapID = -1;
		OpType = eItemAct_Unknow;
		memset(Name, 0, sizeof(Name));
	}
};

struct IBOutItemLogRecordInfo
{
	GUID_t		CharGUID;			/* 自身角色,物品所有者 */
	char		Name[MAX_CHARACTER_NAME];	/* 角色名字 */
	SItemGuid	ItemGuid;			/* 物品编号 */
	uint32		ItemType;			/* 物品全局编号 */
	uint32		OpType;			/* 操作类型 */
	uint32		Count;			/* 个数 */
	uint32		GoldCash;		/* 现金数 */
	MapID_t		MapID;			/* 场景ID */
	int32		WorldID;		/* 服务器ID */

	IBOutItemLogRecordInfo (void)
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		CharGUID =  -1;
		Count = 1;
		ItemType = 0;
		OpType = eItemAct_Unknow;
		memset(Name, 0, sizeof(Name));
		GoldCash = 0;
		WorldID = 0;
		MapID = -1;
	}
};


struct GLStockTradeLogRecordInfo
{
	GUID_t			OwnerGUID;	/* 所有者GUID */
	GUID_t			OtherGUID;	/* 交易另一方GUID */
	eStockActType	OPType;		/* 操作类型 */
	uchar			TradeType;	/* 交易类型 */
	int32			OwnerPrice;	/* 所有者出价：单价 */
	int32			OtherPrice;	/* 交易另一方出价：单价 */
	int32			Gold;		/* 交易的现金总数 */
	uint32			CreateTime;	/* 创建时间 */
	uint32			DeleteTime;	/* 删除时间 */

	GLStockTradeLogRecordInfo(void)
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		OwnerGUID = INVALID_ID;
		OtherGUID = INVALID_ID;
		OPType = eStockAct_Unknow;
		TradeType = STOCK_TRADE_TYPE_BUY;
		OwnerPrice = 0;
		OtherPrice = 0;
		Gold = 0;
		CreateTime = -1;
		DeleteTime = -1;
	}
};

//账户记录LOG
struct MapStockAccLogRecordInfo
{
	GUID_t			OwnerGUID;	/* 所有者GUID */
	eStockAccActType OPType;	/* 操作类型 */
	int32			TransGold;	/* 转账的现金 */
	int32			TransSiller;/* 转账的现银 */
	int32			StockGold;	/* 账户余额 现金 */
	int32			StockSiller;/* 账户余额 现银 */
	MapID_t			MapID;		/* 场景ID */
	int32			WorldID;	/* 服务器ID */

	MapStockAccLogRecordInfo()
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear()
	{
		OwnerGUID = INVALID_ID;
		OPType = eStockAccAct_Unknow;
		TransGold = 0;
		TransSiller = 0;
		StockGold = 0;
		StockSiller = 0;
		MapID = -1;
		WorldID = 0;
	}
};

//账户记录LOG
struct GLStockAccLogRecordInfo
{
	GUID_t			OwnerGUID;	/* 所有者GUID */
	eStockAccActType OPType;	/* 操作类型 */
	int32			TransGold;	/* 转账的现金 */
	int32			TransSiller;/* 转账的现银 */
	int32			StockGold;	/* 账户余额 现金 */
	int32			StockSiller;/* 账户余额 现银 */

	GLStockAccLogRecordInfo()
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear()
	{
		OwnerGUID = INVALID_ID;
		OPType = eStockAccAct_Unknow;
		TransGold = 0;
		TransSiller = 0;
		StockGold = 0;
		StockSiller = 0;
	}
};

// GL帮会属性Log
struct GLGuildLogRecordInfo
{
	GuildID_t		m_GuildId;								//帮会ID
	char			m_szGuildName[MAX_GUILD_NAME_SIZE];		//帮会名
	eGuildActType	m_OpType;								//操作类型
	int32			m_nCount;								//变化值
	int32			m_nRemainCount;							//变化后的值
	int32			m_nParam;								//操作相关的参数
	int32			m_nScriptId;							//脚本Id


	GLGuildLogRecordInfo (void)
	{
		clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void clear(void)
	{
		m_GuildId = INVALID_GUILD_ID;
		memset( m_szGuildName, 0, MAX_GUILD_NAME_SIZE );
		m_OpType = eGuildAct_Unknow;
		m_nCount = 0;
		m_nRemainCount = 0;
		m_nParam = 0;
		m_nScriptId = -1;
	}
};

struct ZhuanJingLogRecordInfo
{
	GUID_t		CharGUID;	/* 自身角色 */
	eZhuanJingActType	OPType;		/* 操作类型 */
	MapID_t		MapID;		/* 场景编号 */
	float		XPos;		/* 事件发生位置 */
	float		ZPos;
	int32		TotalPoint;
	int32		Profession[PROFESSION_NUMBER];
	int32		Reserve_param0;
	int32		Reserve_param1;
	int32		WorldID;	/* 服务器ID */


	ZhuanJingLogRecordInfo()
	{
		clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void clear(void)
	{
		CharGUID = INVALID_ID;
		OPType = eZhuanjingAct_Unknow;
		MapID = -1;
		XPos = 0.0f;
		ZPos = 0.0f;
		TotalPoint = 0;
		Reserve_param0 = 0;
		Reserve_param1 = 0;
		WorldID = 0;
		memset(Profession, 0, sizeof(Profession));
	}
};

#endif /* _RECORD_STRUCT_H_ */

/* ???? */
