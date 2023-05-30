#ifndef __TAB_DEFINE_MAP_MISC_H__
#define __TAB_DEFINE_MAP_MISC_H__

#include "TypeDefine.h"
#include "StructDB.h"
#include "PetConfig.h"
#include "SpellDataLoader.h"
#include "Camp.h"
#include "TabTemplateLoader.h"
#include "ScriptCacheMgr.h"
#include "StructPet.h"
#include "shop/ShopManager.h"
#include "SplitStringLevelOne.h"
#include "StructWorldShop.h"
#include "IntegerHashMap.h"
#include "TabStruct.h"

#include <vector>
using namespace std;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
class TableInit_Map_Misc
{
public:
	TableInit_Map_Misc();
	~TableInit_Map_Misc();

	BOOL	Init();

	BOOL	LoadIdCollectionMgr();
	BOOL	LoadSpecialObjDataMgr();

	void	LoadGMTable();

private:
	// BaseValueTable.ini
	void	Init_BaseValueTable();
	// 初始化世界位置表
	void	Init_MapInfoTable();
	// 加载称号表
	void	Init_TitleInfoTable();
	// 加载组合称号表
	void	Init_TitleCombinationTable();
	// 加载属性升级表
	void	LoadAttrLevelupTable();
	// 加载玩家升级经验表
	void	LoadLevelExpTable();
	// 加载内部经验表
	void	LoadInherenceExpTable();
	// 加载天赋平均等级表
	void	LoadInherenceLevelAverageTable();
	// 加载生长点表
	void	LoadGrowPointTable();
	// 加载游戏打开活动表
	void	LoadGameOpenTable();
	// 加载Script.tab
	void	LoadScriptListFile();
	// 加载ip能够使用范围表
	void	LoadIPRange();
	// 加载聊天配置
	void	LoadChatConsume();
	// 加载头发风格
	void	LoadHairStyleTable();
	// 不知道
	void	LoadDyShopInfoTable();
	// 加载商店信息
	void	g_StrLoadShopInfoTable();
	// 不知道
	void	LoadPKPointInfoTable();
	// 加载pk等级信息
	void	LoadPKLevelInfoTable();
	// 加载pk惩罚信息
	void	LoadPKPunishInfoTable();
	// 加载开箱子信息
	void	LoadOpenBoxInfoTable();
	// 加载耐久损耗信息
	void	LoadDurSpoilInfoTable();
	// 加载怪物死亡信息
	void	LoadOndieMonsterTable();
	// 不知道
	void	LoadOndieNopunishTable();
	// 不知道
	void	LoadOndieDiffCountryTable();
	// 不知道
	void	LoadOndieSameCountryTable();
	// 不知道
	void	LoadOndieSameCountryKillerTable();
	// 加载重生花费表
	void	LoadReliveCostTable();
	// 加载死亡处理表
	void	LoadDeathDealTable();
	// 加载小动物数据表
	void	LoadBeastieDataTable();
	// 加载玩家能量数据表
	void	LoadVigorDataTable();
	// 加载奖品数据表
	void	LoadAwardInfoTable();
	// 加载场景公共数据表
	void	LoadSceneCommonTable();
	// 加载世界商店信息
	void	LoadWorldShopInfoTable();
	// 加载加密信息表
	void	LoadEncryptInfoTable();
	// 加载问答信息
	void	LoadAnswerInfoTable();
	// 加载副本数据
	void	LoadFubenDataTable();
	// 加载玩家错误回复数据
	void	LoadCheatActDataTable();
	// 加载帮会商店
	void	LoadGuildMechTable();
    // 加载职业转换技能对应表
	void    LoadChangeProfession();

private:
	void	ReadSceneCommonScriptData
		(
			SplitStringLevelOne	*pSplitL1,
			SplitStringLevelTwo	*pSplitL2,
			const char		*pSplitString,
			ScriptID_t		*pVal,
			int32 MaxCnt
		);
};

#define PARAMETER_NUM		5

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SBaseValueTab
{
	int32	m_Table[AINFOTYPE_NUMBER][PROFESSION_NUMBER];

	SBaseValueTab()
	{
		memset(m_Table, 0, sizeof(int32) * AINFOTYPE_NUMBER * PROFESSION_NUMBER);
	};

	int32 Get(uint32_t AttrInfo, uint32_t Profession)
	{
		KCheck(AttrInfo < AINFOTYPE_NUMBER && Profession < PROFESSION_NUMBER);
		return m_Table[AttrInfo][Profession];
	};
};
extern SBaseValueTab	g_BaseProfessionValueTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */

#define MAX_MAP_INFO_NUM	4096

struct _MAP_INFO_ATTR
{
	int32	m_Index;
	int32	m_PartIndex;
	MapID_t m_SceneId;
	char	m_SceneName[SCENE_NAME_LEN];
	int32	m_DestPosX;
	int32	m_DestPosZ;
	int32	m_SceneType;
	int32	m_MinMapLevel;
	int32	m_MinUserLevel;
	int32	m_NeedMoney;
	int32	m_NeedItem;
	int32	m_SourceSceneId;
	int32	m_SourcePosX;
	int32	m_SourcePosZ;
};

struct _MAP_INFO_ATTR_TAB
{
	_MAP_INFO_ATTR	m_TableExt[MAX_MAP_INFO_NUM];

	uint32_t		m_Count;

	_MAP_INFO_ATTR_TAB()
	{
		memset(m_TableExt, 0, sizeof(_MAP_INFO_ATTR) * MAX_MAP_INFO_NUM);
		m_Count = 0;
	};

	int32 Count()
	{
		return m_Count;
	};
};

extern _MAP_INFO_ATTR_TAB	g_MapInfoAttrTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _TITLE_INFO_TBL
{
	STitle::TITLE_TABLE_INFO	m_TableInfo[MAX_TITLE_SIZE];

	_TITLE_INFO_TBL()
	{
	};
	STitle::TITLE_TABLE_INFO *
	Get(uint32_t uTitileID)
	{
		KCheck(uTitileID < MAX_TITLE_SIZE);
		return &m_TableInfo[uTitileID];
	};
};
extern _TITLE_INFO_TBL	g_TitleInfoTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _TITLE_COMBINATION_TBL
{
	STitle::TITLE_COMBINATION	m_TableCombination[MAX_TITLE_SIZE];

	_TITLE_COMBINATION_TBL()
	{
	};

	STitle::TITLE_COMBINATION *
	Get(uint32_t uCombinationID)
	{
		KCheck(uCombinationID < MAX_TITLE_SIZE);
		return &m_TableCombination[uCombinationID];
	};
};
extern _TITLE_COMBINATION_TBL	g_TitleComTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _PROPERTY_LEVELUP_TAB
{
	int32	m_Table[CPROPERTY_LEVEL_NUMBER][PROFESSION_NUMBER][MAX_TABLE_DEFINE_LEVEL + 1];

	_PROPERTY_LEVELUP_TAB()
	{
		memset(m_Table, 0, sizeof(int32) * CPROPERTY_LEVEL_NUMBER * PROFESSION_NUMBER * MAX_TABLE_DEFINE_LEVEL);
	}

	int32 Get(uint32_t Attr, uint32_t Profession, uint32_t iLevel)
	{
		KCheck(Attr < CPROPERTY_LEVEL_NUMBER && Profession < PROFESSION_NUMBER && iLevel <= MAX_TABLE_DEFINE_LEVEL);
		return m_Table[Attr][Profession][iLevel];
	}

	void Set(uint32_t Attr, uint32_t Profession, uint32_t iLevel, int32 iValue)
	{
		KCheck(Attr < CPROPERTY_LEVEL_NUMBER && Profession < PROFESSION_NUMBER && iLevel <= MAX_TABLE_DEFINE_LEVEL);
		m_Table[Attr][Profession][iLevel] = iValue;
	}
};
extern _PROPERTY_LEVELUP_TAB	g_PropertyLevelupTab;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SLevelupExpTab
{
	uint64	m_Table[MAX_PLAYER_EXP_LEVEL][2];

	SLevelupExpTab()
	{
		memset(m_Table, 0, sizeof(uint64) * MAX_PLAYER_EXP_LEVEL * 2);
	}

	uint64 Get(uint32_t Level)
	{
		KCheck(Level < MAX_PLAYER_EXP_LEVEL);
		KCheck(Level >= 0);
		return m_Table[Level][1];
	}
};

struct _INHERENCE_EXP_TBL
{
	uint32_t	m_Table_Exp[MAX_PLAYER_INHERENCE_LEVEL];
	uint32_t	m_Table_Money[MAX_PLAYER_INHERENCE_LEVEL];
	uint32_t	m_Table_Item[MAX_PLAYER_INHERENCE_LEVEL];

	_INHERENCE_EXP_TBL()
	{
		memset(m_Table_Exp, 0, sizeof(m_Table_Exp));
		memset(m_Table_Money, 0, sizeof(m_Table_Money));
		memset(m_Table_Item, 0, sizeof(m_Table_Item));
	}
};

extern SLevelupExpTab		g_LevelupExpTab;
extern _INHERENCE_EXP_TBL	g_InherenceExpTbl;

struct _INHERENCE_LEVEL_AVERAGE_TBL
{
	uint32_t	m_Table_Player_level[MAX_INHERENCE_LEVEL_AVERAGE];
	uint32_t	m_Table_Inherence_level[MAX_INHERENCE_LEVEL_AVERAGE];

	_INHERENCE_LEVEL_AVERAGE_TBL()
	{
		memset(m_Table_Player_level, 0, sizeof(m_Table_Player_level));
		memset(m_Table_Inherence_level, 0, sizeof(m_Table_Inherence_level));
	}
};

extern _INHERENCE_LEVEL_AVERAGE_TBL	g_InherenceLevelTab;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _GATHER_POINT_INFO
{
	int32		m_GrowPointIndex;
	int32		m_OpenTime;
	uint16_t		m_OpenAbility;
	ScriptID_t	m_ScriptID;
	int32		m_OpenAnim;
};

struct _GATHER_POINT_INFO_TAB
{
	_GATHER_POINT_INFO	*m_Table;

	int32			m_Count;

	_GATHER_POINT_INFO_TAB()
	{
		m_Table = 0;
		m_Count = 0;
	}
	_GATHER_POINT_INFO	*Get(int32 GrowType);
};

extern _GATHER_POINT_INFO_TAB	g_GatherPointInfoTab;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _GAME_OPEN_INFO
{
	int32	m_GameOpenIndex;
	int32	m_nGameId;
	uint16_t	m_nValue;
};

struct _GAME_OPEN_INFO_TBL
{
	_GAME_OPEN_INFO *m_Table;

	int32		m_Count;

	_GAME_OPEN_INFO_TBL()
	{
		m_Table = 0;
		m_Count = 0;
	}
};

extern _GAME_OPEN_INFO_TBL	g_GameOpenInfoTbl;

class GameOpenManager
{
public:
    void        SetGameOpen( int32 gameId, BOOL bOpen);

private:
    FastLock    m_Lock;

};
extern GameOpenManager  g_GameOpenManager;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<IDCollection> IDCollectionMgr_T;
extern IDCollectionMgr_T g_CollectionIDMgr;
#define AISCRIPT_NUM	(1024)

/*
 =======================================================================================================================
 =======================================================================================================================
 */
extern CampAndStandDataMgr g_CampDataMgr;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
typedef class TemplateManager<SpecialObjData_T> SpecialObjDataMgr;
extern SpecialObjDataMgr g_SpecialObjDataTemplate;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
extern ScriptCacheMgr g_ScriptFileMgr;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define MAX_IP_RANGE	256
struct SIPFilter
{
	int32	m_EnableCount;
	char	m_aaIPEnable[MAX_IP_RANGE][IP_SIZE];
	char	m_aaMaskEnable[MAX_IP_RANGE][IP_SIZE];
	int32	m_DisableCount;
	char	m_aaIPDisable[MAX_IP_RANGE][IP_SIZE];
	char	m_aaMaskDisable[MAX_IP_RANGE][IP_SIZE];

	SIPFilter()
	{
		m_EnableCount = 0;
	}
};

extern SIPFilter g_IPFilter;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define MAX_CHAT_CONSUME_TYPE	3
struct SChatConsumeType
{
	uint32_t	m_DelayTime;
	int32	m_ConsumeCount;
	int32	m_ConsumeType[MAX_CHAT_CONSUME_TYPE];
	int32	m_ConsumeValue[MAX_CHAT_CONSUME_TYPE];
	int32	m_NeedLevel;

	SChatConsumeType()
	{
		Clear();
	};

	void Clear()
	{
		m_DelayTime = 1000;
		m_ConsumeCount = 0;
		for(int32 i = 0; i < MAX_CHAT_CONSUME_TYPE; i++)
		{
			m_ConsumeType[i] = CHAT_NEED_NONE;
			m_ConsumeValue[i] = 0;
		}

		m_NeedLevel = 0;
	};
};

#define MAX_CHAT_TYPE_INTABLE	16
struct SChatConsume
{
	uint32_t			m_Count;
	SChatConsumeType	m_ChatComsumeType[MAX_CHAT_TYPE_INTABLE];

	SChatConsume()
	{
		Clear();
	}

	void Clear()
	{
		m_Count = 0;
	}
};

extern SChatConsume	g_ChatConsumeTab;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct SHairStyleType
{
	enum
	{
		HAIRSTYLE_NONE		= -1,
		HAIRSTYLE_INDEX,
		HAIRSTYLE_RACEID	= 1,
		HAIRSTYLE_ITEMSERIAL	= HAIRSTYLE_RACEID +3,
		HAIRSTYLE_ITEMCOSTCOUNT = HAIRSTYLE_ITEMSERIAL +2,
		HAIRSTYLE_USESCOPE,
	};

	int32 m_nIndex;
	int32 m_nRaceID;
	uint32_t m_uItemSerial;
	int32 m_nItemCostCount;
	int32 m_nUseScope;

	SHairStyleType()
	{
		Clear();
	}

	void Clear()
	{
		m_nIndex = -1;
		m_nRaceID = 0;
		m_uItemSerial = 0;
		m_nItemCostCount = 0;
		m_nUseScope = 0;
	}
};

#define MAX_HAIR_STYLE_INTABLE	256
struct SHairStyle
{
	uint32_t			m_uCount;
	SHairStyleType	m_HairStyle[MAX_HAIR_STYLE_INTABLE];

	SHairStyle()
	{
		Clear();
	}

	void Clear()
	{
		m_uCount = 0;
	}
};
extern SHairStyle	g_Hair_Style_Tab;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define MAX_GM_SIZE	256
struct SGMTab
{
	int32	m_uCount;
	GUID_t	m_aGUID[MAX_GM_SIZE];
	int32	m_nRight[MAX_GM_SIZE];

	SGMTab()
	{
		Clear();
	};

	void Clear()
	{
		m_uCount = 0;
	}
};
extern SGMTab	g_GMTab;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct DYSHOP_GROUP
{
	enum { DY_GROUPID = 0, DY_NUM, DY_BEGIN = 2, DY_ITEM_PROPERTY_NUM = 26, };

	struct DY_ITEM
	{
		int32	m_ItemID;
		int32	m_ItemNumMin;
		int32	m_ItemNumMax;

		int32	m_Rate;

		char	m_RandPriceType;
		int32	m_PriceNum;
		int32	m_PriceType[MAX_DY_GROUP_PRICE_NUM];
		int32	m_Price[MAX_DY_GROUP_PRICE_NUM];
	};

	int32	m_GroupId;
	int32	m_GoodsNum;
	DY_ITEM m_Goods[MAX_DY_PER_GROUP_GOODS_NUM];
};

const int32		MAX_DYSHOP_GROUP = 256;
struct _DYSHOP_INFO_TBL
{
	DYSHOP_GROUP	m_aGroupInfo[MAX_DYSHOP_GROUP];
	int32		m_iCount;

	_DYSHOP_INFO_TBL()
	{
		memset(this, 0, sizeof(_DYSHOP_INFO_TBL));
	}
};
extern _DYSHOP_INFO_TBL g_DyShopInfoTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32			MAX_SHOP_GROUP = 1024;
const int32			MAX_GUILD_MERCH = 128;
struct _SHOP_INFO_TBL
{
	SShop	m_aShop[MAX_SHOP_GROUP];
	int32	m_iCount;

	_SHOP_INFO_TBL()
	{
		memset(this, 0, sizeof(_SHOP_INFO_TBL));
	}
};
extern _SHOP_INFO_TBL	g_ShopInfoTbl;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32		MAX_PK_NUM = 256;

struct _PKPOINT_INFO_TBL
{
	PK_INFO m_aPKPointInfo[MAX_PK_NUM];
	int32	m_nCount;
};
extern _PKPOINT_INFO_TBL	g_PKPointTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _PKLEVEL_INFO_TBL
{
	PK_INFO m_aPKPointInfo[MAX_PK_NUM];
	int32	m_nCount;
};
extern _PKLEVEL_INFO_TBL	g_PKLevelTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _PKPUNISH_INFO_TBL
{
	PK_INFO m_aPKPointInfo[MAX_PK_NUM];
	int32	m_nCount;
};
extern _PKPUNISH_INFO_TBL	g_PKPunishTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct OpenBox_ItemInfo_Table
{
	enum { ITEM_KIND_MAX_NUM = 120, COLUMN_MAX_NUM = 91, };

	struct ItemInfoRow
	{
		enum { ITEM_INFO_MAX_NUM = 30, };

		struct ItemInfo
		{
			int32	m_ItemID;
			int32	m_Rate1;
			int32	m_Rate2;
		public:
			ItemInfo()
			:
			m_ItemID(0),
			m_Rate1(0),
			m_Rate2(0)
			{
			}

			ItemInfo &operator=(const ItemInfo &oItemInfo)
			{
				m_ItemID = oItemInfo.m_ItemID;
				m_Rate1 = oItemInfo.m_Rate1;
				m_Rate2 = oItemInfo.m_Rate2;

				return *this;
			}
		};

		ItemInfo	m_ItemInfo[ITEM_INFO_MAX_NUM];
		int32		m_RealNum;
		int32		m_Index;
	public:
		ItemInfoRow()
		:
		m_RealNum(0),
		m_Index(0)
		{
		}

		ItemInfoRow &operator=(const ItemInfoRow &oItemInfoRow)
		{
			m_RealNum = oItemInfoRow.m_RealNum;

			if(m_RealNum > 0 && m_RealNum <= ITEM_INFO_MAX_NUM)
			{
				for(int i = 0; i < m_RealNum; ++i)
				{
					m_ItemInfo[i] = oItemInfoRow.m_ItemInfo[i];
				}
			}

			return *this;
		}
	};

	ItemInfoRow	m_ItemInfoRow[ITEM_KIND_MAX_NUM];

	int32		m_KindRealNum;
public:
	OpenBox_ItemInfo_Table()
	:
	m_KindRealNum(0)
	{
	}
};

extern OpenBox_ItemInfo_Table	g_OpenBox_ItemInfo_Table;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _DURSPOIL_VALUE_TBL
{
	struct SPOIL_VALUE
	{
		int32	m_nDamageMode;
		uint32_t	m_nValue;
	};

	SPOIL_VALUE	m_Table[EQUIP_TYPE_NUM];

	_DURSPOIL_VALUE_TBL()
	{
		for(int32 i = 0; i < EQUIP_TYPE_NUM; ++i)
		{
			m_Table[i].m_nDamageMode = -1;
			m_Table[i].m_nValue = -1;
		}
	};

	SPOIL_VALUE &Get(uchar equipType)
	{
		KCheck(equipType < EQUIP_TYPE_NUM);
		return m_Table[equipType];
	};
};
extern _DURSPOIL_VALUE_TBL	g_DurSpoilValueTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32			MAX_ONDIE_NUM = 16;
struct _ONDIE_MONSTER_TBL
{
	int32	m_aEndureMin[MAX_ONDIE_NUM];
	int32	m_aEndureMax[MAX_ONDIE_NUM];
	int32	m_aBagDropMin[MAX_ONDIE_NUM];
	int32	m_aBagDropMax[MAX_ONDIE_NUM];
	int32	m_aEquipDropMin[MAX_ONDIE_NUM];
	int32	m_aEquipDropMax[MAX_ONDIE_NUM];

	int32	m_nCount;
};
extern _ONDIE_MONSTER_TBL	g_OndieMonsterTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _ONDIE_NOPUNISH_TBL
{
	int32	m_aEndureMin[MAX_ONDIE_NUM];
	int32	m_aEndureMax[MAX_ONDIE_NUM];

	int32	m_nCount;
};
extern _ONDIE_NOPUNISH_TBL	g_OndieNopunishTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32			MAX_ONDIE_NUM_2 = 32;
struct _ONDIE_DIFFCOUNTRY_TBL
{
	int32	m_aEndureMin[MAX_ONDIE_NUM_2];
	int32	m_aEndureMax[MAX_ONDIE_NUM_2];
	int32	m_aBagDropMin[MAX_ONDIE_NUM_2];
	int32	m_aBagDropMax[MAX_ONDIE_NUM_2];
	int32	m_aEquipDropMin[MAX_ONDIE_NUM_2];
	int32	m_aEquipDropMax[MAX_ONDIE_NUM_2];
	int32	m_aSelfHonor[MAX_ONDIE_NUM_2];
	int32	m_aKillerHonor[MAX_ONDIE_NUM_2];

	int32	m_nCount;
};
extern _ONDIE_DIFFCOUNTRY_TBL	g_OndieDiffCountryTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _ONDIE_SAMECOUNTRY_TBL
{
	int32	m_aEndureMin[MAX_ONDIE_NUM_2];
	int32	m_aEndureMax[MAX_ONDIE_NUM_2];
	int32	m_aBagDropMin[MAX_ONDIE_NUM_2];
	int32	m_aBagDropMax[MAX_ONDIE_NUM_2];
	int32	m_aEquipDropMin[MAX_ONDIE_NUM_2];
	int32	m_aEquipDropMax[MAX_ONDIE_NUM_2];
	int32	m_aSelfPK[MAX_ONDIE_NUM_2];

	int32	m_nCount;
};
extern _ONDIE_SAMECOUNTRY_TBL	g_OndieSameCountryTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _ONDIE_SAMECOUNTRY_KILLER_TBL
{
	int32	m_aPK1[MAX_ONDIE_NUM_2];
	int32	m_aPK2[MAX_ONDIE_NUM_2];

	int32	m_nCount;
};
extern _ONDIE_SAMECOUNTRY_KILLER_TBL	g_OndieSameCountryKillerTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define MAX_RELIVE_COST 12
struct _ONRELIVE_COST_TBL
{
	int32	m_aCost1[MAX_RELIVE_COST];
	int32	m_aCost2[MAX_RELIVE_COST];

	int32	m_nCount;
};
extern _ONRELIVE_COST_TBL	g_ReliveCostTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _ONDEATH_DEAL_TBL
{
	int32	m_aSceneID[MAX_SCENE];
	int32	m_aX[MAX_SCENE];
	int32	m_aZ[MAX_SCENE];

	int32	m_nCount;
};
extern _ONDEATH_DEAL_TBL	g_DeathDealTbl;



/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _BEASTIE_DATA_TABLE
{
	enum { MAX_ITEM_COUNT = 100, };

	struct _BEASTIE_ITEM
	{
		int32 m_uBeastieId;
		char m_szName[MAX_CHARACTER_NAME];
		float m_PosX;
		float m_PosZ;
		int32 m_nItemId;
		float m_fSpeed;
		int32 m_nModelId;
		int32 m_RespawnTime;
		int32 m_nSceneId;
		float m_fDirection;
		int32 m_nType;
		_BEASTIE_ITEM()
		{
			memset(this, 0, sizeof(_BEASTIE_ITEM));
		}
	};

	uint32_t m_uCount;
	_BEASTIE_ITEM m_BeastieItem[MAX_ITEM_COUNT];

	_BEASTIE_DATA_TABLE()
	:
	m_uCount(0)
	{
	}
};
extern _BEASTIE_DATA_TABLE g_BeastieDataTable;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _VIGOR_DATA_TABLE
{
	enum { MAX_ITEM_COUNT = 160, };

	struct _VIGOR_DATA_ITEM
	{
		uchar m_Level;
		int32 m_RecoverOnce;
		int32 m_MaxVigor;
		_VIGOR_DATA_ITEM()
		{
			memset(this, 0, sizeof(_VIGOR_DATA_ITEM));
		}
	};

	_VIGOR_DATA_ITEM &GetVigorInfo_ByPlayerLevel(int32 level)
	{
		KCheck(level > 0 && level <= MAX_PLAYER_EXP_LEVEL);
		return m_VigorItem[level - 1];
	}

	_VIGOR_DATA_ITEM m_VigorItem[MAX_ITEM_COUNT];
};
extern _VIGOR_DATA_TABLE g_VigorDataTable;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct _GUILD_MERCH_TBL
{
	_GUILD_MERCH_INFO	m_aMerchList[MAX_GUILD_MERCH];
	int32			m_iCount;
	BOOL			m_bInitOK;
	_GUILD_MERCH_TBL()
	{
		memset(this, 0, sizeof(_GUILD_MERCH_TBL));
	}

	int32 GetIndexByItemID(int32 itemID)
	{
		for(int i = 0; i < MAX_GUILD_MERCH; i++)
		{
			if(m_aMerchList[i].m_nMerchID == itemID) return i;
		}

		return -1;
	}
};
extern _GUILD_MERCH_TBL g_GuildMerchTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32 AWARD_NAME_LEN = 32;
const int32 AWARD_TEXT_LEN = 1024;
const int32 AWARD_ITEM_NUM = 1024;
const int32 AWARD_EXT_ATTR_ENUM_SIZE = 2000;

struct AWARD_EXT_ATTR
{
	int32 m_AwardId;
	char m_AwardName[AWARD_NAME_LEN];
	char m_AwardText[AWARD_TEXT_LEN];
	ScriptID_t m_ScriptId;
	int32 m_BagNeedSpace;
	uint32_t m_MinSpliceNum;
};

struct AWARD_ATTREX_ATTR
{
	AWARD_EXT_ATTR m_TableExt[AWARD_EXT_ATTR_ENUM_SIZE];
	uint32_t m_Count;
	uint32_t m_MaxType;

	AWARD_ATTREX_ATTR()
	{
		memset(m_TableExt, 0, sizeof(AWARD_EXT_ATTR) * AWARD_EXT_ATTR_ENUM_SIZE);
		m_Count = 0;
	};

	int32 Count()
	{
		return m_Count;
	};
};

extern AWARD_ATTREX_ATTR g_AwardAttrExTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
const int32 SC_MAX_SCRIPT_NUM = 32;

struct SCENE_COMMON_ATTR
{
	MapID_t m_SceneId;
	ScriptID_t m_ScriptList[SC_MAX_SCRIPT_NUM];

	BOOL m_IsTiredScene;
};

struct SENE_COMMON_TABLE
{
	uint32_t m_Count;
	SCENE_COMMON_ATTR m_TableExt[MAX_SCENE];

	SENE_COMMON_TABLE()
	{
		m_Count = 0;
		memset(m_TableExt, 0, sizeof(m_TableExt));
	}
};

extern SENE_COMMON_TABLE g_SceneCommonTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct WORLD_SHOP_EXT_ATTR
{
	uchar m_ShopId;
	int32 m_GoldCash;
	int32 m_Charge;
	uchar m_ConcentNum;
	uint32_t m_RemainTime;
	uchar m_PageNum;
};

struct WORLD_SHOP_ATTREX_ATTR
{
	WORLD_SHOP_EXT_ATTR m_TableExt[SHOP_LIST_NUM];
	uint32_t m_Count;

	WORLD_SHOP_ATTREX_ATTR()
	{
		memset(m_TableExt, 0, sizeof(WORLD_SHOP_EXT_ATTR) * SHOP_LIST_NUM);
		m_Count = 0;
	};
	int32 Count()
	{
		return m_Count;
	};
};
extern WORLD_SHOP_ATTREX_ATTR g_GLShopAttrExTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define MAX_ENCRYPT_INFO_NUM	8196

struct _ENCRYPT_INFO_ATTR
{
	int32 m_Index;
	uint32_t m_Parameter[ENCRYPT_OP_PARAM_NUM];
	ScriptID_t m_ScriptId;
	char m_FnName[ENCRYPT_OP_FUNCTION_NAME_SIZE];
	int32 m_Result;
};

struct _ENCRYPT_INFO_ATTR_TAB
{
	_ENCRYPT_INFO_ATTR m_TableExt[MAX_ENCRYPT_INFO_NUM];

	uint32_t m_Count;

	_ENCRYPT_INFO_ATTR_TAB()
	{
		memset(m_TableExt, 0, sizeof(_ENCRYPT_INFO_ATTR) * MAX_ENCRYPT_INFO_NUM);
		m_Count = 0;
	};

	int32 Count()
	{
		return m_Count;
	};
};

extern _ENCRYPT_INFO_ATTR_TAB g_EncryptInfoAttrTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define ANSWER_LIST_NUM 10000

struct ANSWER_EXT_ATTR
{
	uint32_t m_AnswerId;
	char m_Title[ANSWER_TITLE_NUM + 1];
	uchar m_Result;
};

struct ANSWERP_ATTREX_ATTR
{
	ANSWER_EXT_ATTR m_TableExt[ANSWER_LIST_NUM];
	uint32_t m_Count;

	ANSWERP_ATTREX_ATTR()
	{
		memset(m_TableExt, 0, sizeof(ANSWER_EXT_ATTR) * ANSWER_LIST_NUM);
		m_Count = 0;
	};

	int32 Count()
	{
		return m_Count;
	};
};

extern ANSWERP_ATTREX_ATTR g_AnawerAttrExTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
struct FUBEN_DATA_ATTR
{
	int32 nId;
	ScriptID_t nScriptId;
	int32 nBossFlag;
	int32 nIndexFlag;
	int32 nLevelMin;
	int32 nLevelMax;
	char strName[MAX_CHARACTER_NAME];
	char strTitle[MAX_CHARACTER_NAME];
	int32 nDataId;
	GUID_t nGUID;
	float nPosX;
	float nPosZ;
	int32 nPosR;
	int32 nAI;
	int32 nAIScript;
	int32 nFlag0;
	int32 nFlag1;
	int32 nFlag2;
	int32 nFlag3;
	int32 nCreateCount;
	int32 nFaceDir;
	int32 nPatrolId;
	int32 nCampID;
};

struct FUBEN_DATA_TABLE
{
	int32 m_Count;
	FUBEN_DATA_ATTR *m_FubenData;

	FUBEN_DATA_TABLE()
	{
		m_Count = 0;
		m_FubenData = 0;
	};

	~FUBEN_DATA_TABLE()
	{
		Clear();
	}

	void Clear()
	{
		m_Count = 0;
		if(m_FubenData)
		{
			delete[] m_FubenData;
			m_FubenData = 0;
		}
	}

	int32 Count()
	{
		return m_Count;
	};
};

extern FUBEN_DATA_TABLE g_FubenDataAttrTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
#define CHEAT_ACT_NUM	128

struct CHEAT_ACT_ATTR
{
	int32 nId;
	BOOL bValid;
	int32 nErrorCount;
	int32 nOPMode;
};

struct CHEAT_ACT_TABLE
{
	int32 m_Count;
	CHEAT_ACT_ATTR m_TableExt[CHEAT_ACT_NUM];

	CHEAT_ACT_TABLE()
	{
		m_Count = 0;
		memset(m_TableExt, 0, sizeof(CHEAT_ACT_ATTR) * CHEAT_ACT_NUM);
	};

	int32 Count()
	{
		return m_Count;
	};
};

extern CHEAT_ACT_TABLE g_CheatActAttrTbl;


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Compare_GatherPointTab(const void *pArg1, const void *pArg2);

/*
 =======================================================================================================================
 =======================================================================================================================
 */

struct CHANGE_PROFESSION_ATTR
{
    int32 m_Index;
    int32 m_ProfSrc;
    int32 m_SkillSrc;
    int32 m_SkillDst;
    int32 m_ProfDest;
};

struct CHANGE_PROFESSION_TABLE
{
    int32                   m_iCount[ PROFESSION_NUMBER];
    CHANGE_PROFESSION_ATTR  m_arrConvert[ PROFESSION_NUMBER][ MAX_CHAR_SKILL_NUM];

    CHANGE_PROFESSION_TABLE()
    {
        memset( m_iCount, 0, sizeof( int32) * PROFESSION_NUMBER);
        memset( m_arrConvert, 0, sizeof( CHANGE_PROFESSION_ATTR) * PROFESSION_NUMBER * MAX_CHAR_SKILL_NUM);
    }
};
extern CHANGE_PROFESSION_TABLE g_ChangeProfessionTbl;


#endif