/*$T Client/Game/DataPool/GameDataDefine.h GC 1.140 08/23/09 04:52:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/*
 * ;
 * 游戏数据定义 ;
 * ;
 */
#ifndef _GAME_DATA_DEFINE_H_
#define _GAME_DATA_DEFINE_H_

#include "StructDB.h"
#include "GameTableData.h"
#include "Data\Struct\GameDataStructPet.h"
#include "Data\Struct\GameDataStructPlayerShop.h"
#include "StructCommandScript.h"
namespace	GDataDef
{
/*
 -----------------------------------------------------------------------------------------------------------------------
    冷却组
 -----------------------------------------------------------------------------------------------------------------------
 */
struct COOLDOWN_GROUP
{
	int32		nTotalTime;
	int32		nTimeElapsed;
	UINT64	nCreateTime;

	COOLDOWN_GROUP (void)
	{
		Reset();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Reset(void)
	{
		nTotalTime = 0;
		nTimeElapsed = 0;
		nCreateTime = 0;
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    玩家资料
 -----------------------------------------------------------------------------------------------------------------------
 */
struct PRIVATE_INFO
{
	STRING	m_szName;		/* 在CleanUp中不要清除 */
	int32		m_nInfoType;	/* 保密程度 */
	uint32	m_unCharGUID;	/* 角色编号 */
	int32		m_nAge;			/* 年龄 */
	int32		m_nSex;			/* 性别 */
	STRING	m_szJobInfo;	/* 职业信息 */
	STRING	m_szSchoolInfo; /* 毕业院校 */
	int32		m_nBloodType;	/* 血型 */
	int32		m_nYearAnimal;	/* 生肖 */
	int32		m_birthMonth;
	int32		m_birthDay;
	int32		m_nConsella;	/* 星座 */
	STRING	m_szProvince;	/* 省份 */
	STRING	m_szCity;		/* 城市 */
	STRING	m_szEmailInfo;	/* 邮件 */
	STRING	m_szLuckWord;	/* 心情寄语 */

	STRING	m_szHomePage;	/* 主页 */
	STRING	m_szQQ;			/* QQ */
	STRING	m_szMSN;		/* MSN */

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp(void)
	{
		m_nInfoType = 0;
		m_unCharGUID = 0;
		m_nAge = 0;
		m_nSex = 0;
		m_szJobInfo = "";
		m_szSchoolInfo = "";
		m_nBloodType = 0;
		m_nYearAnimal = 0;
		m_nConsella = 0;
		m_szProvince = "";
		m_szCity = "";
		m_szEmailInfo = "";
		m_szLuckWord = "";

		m_szHomePage = "";
		m_szQQ = "";
		m_szMSN = "";

		m_birthMonth = 0;
		m_birthDay = 0;
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    同城玩家
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SameCityData
{
	GUID_t		m_playerGUID;
	string		m_strName;
	int32			m_iLevel;
	int32			m_iZhiYe;
	int32			m_iCountry;
	string		m_strGuild;
	int32			m_nGuildId;
	int32			m_nGuildPos;
	POSTCODE	m_postCode;

	SameCityData (void)
	{
		m_nGuildId = -1;
		m_nGuildPos = -1;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	SameCityData &operator=(const SameCityData &data)
	{
		m_playerGUID = data.m_playerGUID;
		m_strName = data.m_strName;
		m_iLevel = data.m_iLevel;
		m_iZhiYe = data.m_iZhiYe;
		m_iCountry = data.m_iCountry;
		m_strGuild = data.m_strGuild;
		m_nGuildId = data.m_nGuildId;
		m_nGuildPos = data.m_nGuildPos;
		m_postCode = data.m_postCode;
		m_nGuildId = data.m_nGuildId;
		m_nGuildPos = data.m_nGuildPos;

		return *this;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	BOOL operator==(const SameCityData &data)
	{
		if(data.m_playerGUID == m_playerGUID) return TRUE;

		return FALSE;
	}
};
enum { MAX_SHOW_NUM_ONEPAGE = 2, };

/*
 -----------------------------------------------------------------------------------------------------------------------
    排行数据
 -----------------------------------------------------------------------------------------------------------------------
 */
struct TopData
{
	GUID_t	m_Guid;			/* 玩家GUID */
	int32		m_nLevel;		/* 等级 */
	int32		m_nCountry;		/* 国家 */
	STRING	m_strName;		/* 名称 */
	int32		m_nMenPai;		/* 职业 */
	STRING	m_strGuildName; /* 帮会名称 */
	int32		m_nKeyValue;	/* 排行榜关键值。根据排行榜的类型不同，其数值含义也不同 */
	uint32	m_uTopVersion;	/* 排行榜版本号 */
	int32		m_nReserved[3];

	TopData (void)
	{
		m_Guid = INVALID_ID;
		m_nLevel = 0;
		m_nCountry = INVALID_ID;
		m_nMenPai = INVALID_ID;
		m_nKeyValue = INVALID_ID;
		m_uTopVersion = 0;

		//memset(m_nReserved, 0, sizeof(m_nReserved));
		m_nReserved[0] = -1;
		m_nReserved[1] = -1;
		m_nReserved[2] = -1;
		
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	TopData &operator=(const TopData &val)
	{
		m_Guid = val.m_Guid;
		m_nLevel = val.m_nLevel;
		m_nCountry = val.m_nCountry;
		m_strName = val.m_strName;
		m_nMenPai = val.m_nMenPai;
		m_strGuildName = val.m_strGuildName;
		m_nKeyValue = val.m_nKeyValue;
		m_uTopVersion = val.m_uTopVersion;

		memcpy(m_nReserved, val.m_nReserved, sizeof(m_nReserved));

		return *this;
	}
};

typedef std::map<int32, TopData>	TOP_DATA_MAP;

/*
 -----------------------------------------------------------------------------------------------------------------------
    排行榜数据
 -----------------------------------------------------------------------------------------------------------------------
 */
struct TopTypeData
{
	int32 nMaxTopNum;				/* 当前已收到最大数据索引 */
	int32 nTotalTopNum;			/* 当前记录总数 */
	uint32 uTopVersion;			/* 排行榜版本号 */
	UINT64 uCreateTime;			/* 创建时间 */
	TOP_DATA_MAP TopDataMap;	/* 该排行榜数据 */

	TopTypeData (void)
	{
		nMaxTopNum = 0;
		uTopVersion = -1;
		uCreateTime = 0;
		nTotalTopNum = 0;
	}
};


typedef std::map<INT, TopTypeData, std::less<INT>,
Ogre::StlAllocator<pair<INT, TopTypeData>, Ogre::CompactablePoolAllocPolicy> >									TOP_TYPE_MAP;

typedef std::map<INT, KCharatcterBaseData*, std::less<INT>,
Ogre::StlAllocator<pair<INT, KCharatcterBaseData*>, Ogre::CompactablePoolAllocPolicy> >							MAP_CHARDATA;

typedef std::vector< COOLDOWN_GROUP, Ogre::StlAllocator<COOLDOWN_GROUP, Ogre::CompactablePoolAllocPolicy> >		VECTOR_COOLDOWN;
typedef std::vector< INT, Ogre::StlAllocator<INT, Ogre::CompactablePoolAllocPolicy> >							VECTOR_INT;

typedef std::map<INT, _BUFF_EFFECT_INFO*, std::less<INT>,
Ogre::StlAllocator<pair<INT, _BUFF_EFFECT_INFO*>, Ogre::CompactablePoolAllocPolicy> >							CBuffImpactMap;

typedef std::vector< SameCityData, Ogre::StlAllocator<SameCityData, Ogre::CompactablePoolAllocPolicy> >			SameCityDataVec;

typedef std::map<STRING, SameCityData, std::less<STRING>,
Ogre::StlAllocator<pair<STRING, SameCityData>, Ogre::CompactablePoolAllocPolicy> >								SameCityDataMap;


typedef std::vector< _TABLE_PROVINCE_ZONE >	ZoneVec;				//市区
typedef std::map< STRING, ZoneVec >			ProvinceZoneMap;		//省份市区表
typedef std::pair< STRING, STRING >			ProvinceZonePair;		//市区省份对
typedef std::map< INT, ProvinceZonePair >	PostCodeProvinceZoneMap;//编号省份市区表
typedef std::vector< STRING >				ProvinceVec;

typedef std::deque< INT, Ogre::StlAllocator<INT, Ogre::CompactablePoolAllocPolicy> >							LinkItemQue;
typedef std::vector< SDataPet,  Ogre::StlAllocator<SDataPet, Ogre::CompactablePoolAllocPolicy> >				LinkHorseQue;


/*
 -----------------------------------------------------------------------------------------------------------------------
    BBS上的留言
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SMessageEntry
{
	STRING AuthorName;
	uint32 nID;
	BYTE nHour;
	BYTE nMin;
	BOOL bHasReply;
	STRING szMessage;
	BYTE nReHour;
	BYTE nReMin;
	STRING szReplyMessage;

	SMessageEntry (void)
	{
		AuthorName = "";
		nID = 0;
		nHour = 0;
		nMin = 0;
		bHasReply = 0;
		szMessage = "";
		nReHour = 0;
		nReMin = 0;
		szReplyMessage = "";
	}
};

struct BBS_t
{
	STRING m_szTitle;
	uint32 m_nSerial;
	int32 m_nMessageNum;
	std::vector<SMessageEntry> m_MessageList;

	BBS_t (void)
	{
		CleanUp();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp(void)
	{
		m_nMessageNum = 0;
		m_szTitle = "";
		m_nSerial = 0;

		SMessageEntry BBSinital;

		m_MessageList.resize(MAX_BBS_MESSAGE_NUM, BBSinital);	/* 留言板 */
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    摊位物品
 -----------------------------------------------------------------------------------------------------------------------
 */
struct BAITAN_ITEM
{
	BAITAN_ITEM (void)
	{
		pItem = NULL;
		nPrice = 0;
		nSerial = 0;
		nbIsEnable = 0;
	}
	KItem	*pItem;		/* 物品指针 */
	uint32 nPrice;		/* 价格 */
	uint32 nSerial;		/* 序列号 */
	BYTE nbIsEnable;	/* 这个物品是否上架 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    摊位宠物
 -----------------------------------------------------------------------------------------------------------------------
 */
struct STALL_PET
{
	STALL_PET (void)
	{
		pPet = NULL;
		nPrice = 0;
		nSerial = 0;
		nbIsEnable = TRUE;
		m_GUID.Reset();
	}
	SDataPet	*pPet;	/* 宠物指针 */
	uint32 nPrice;		/* 价格 */
	uint32 nSerial;		/* 序列号 */
	BYTE nbIsEnable;	/* 这个物品是否上架 */
	SHorseGuid m_GUID;
};

enum STALL_DEFAULT_PAGE { ITEM_PAGE = 0,	/* 物品页 */ PET_PAGE, };

/*
 -----------------------------------------------------------------------------------------------------------------------
    摊位盒
 -----------------------------------------------------------------------------------------------------------------------
 */
struct CLIENT_BAITAN_BOX
{
	int32 m_nDefaultPage;					/* 缺省的页面 */
	uint32 m_ObjID;
	BOOL m_bIsOpen;						/* 自己摊位是否已经打开（是否处于交易状态） */
	uint32 m_PosTax;						/* 摊位费 */
	uint32 m_TradeTax;					/* 每次交易税收 */
	STRING m_szStallName;				/* 标示摊位名 */
	STRING m_szOwnerName;				/* 标示摊主名 */
	uint32 m_nFirstPage;					/* 起始页 */
	std::vector<BAITAN_ITEM> m_ItemList; /* 标示摊位中的所有物品 */
	std::vector<STALL_PET> m_PetList;	/* 标示摊位中的所有宠物 */
	BBS_t m_BBS;						/* 摊位留言板 */
	uint32 m_OtGUID;

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp()
	{
		m_nDefaultPage = ITEM_PAGE;
		m_ObjID = 0;		/* 摊位拥有者的ID */
		m_bIsOpen = FALSE;	/* 自己摊位是否已经打开 */

		/*
		 * m_PosTax = 0;
		 * //摊位费 ;
		 * m_TradeTax = 0;
		 * //每次交易税收
		 */
		m_szStallName = ""; /* 标示摊位名 */
		m_szOwnerName = ""; /* 标示摊主名 */
		m_nFirstPage = 0;	/* 起始页 */
		m_OtGUID = 0;
		m_BBS.CleanUp();

		/* 摊位留言板 */
		BAITAN_ITEM stallinital;

		m_ItemList.resize(BAITAN_BOX_SIZE, stallinital);

		/* 标示摊位中的所有物品 */
		STALL_PET stallPetinital;

		m_PetList.resize(BAITAN_HORSE_BOX_SIZE, stallPetinital);	/* 标示摊位中的所有宠物 */
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    标示摊位中的所有物品
 -----------------------------------------------------------------------------------------------------------------------
 */
struct PLAYERSHOP_STALL_BOX
{
	int32 m_bIsEnable;
	std::vector<BAITAN_ITEM> m_ItemList;
	std::vector<STALL_PET> m_PetList;

	PLAYERSHOP_STALL_BOX()
	{
		m_bIsEnable = FALSE;
		BAITAN_ITEM ItemInit;
		m_ItemList.resize(BAITAN_BOX_SIZE, ItemInit);
		STALL_PET PetInit;
		m_PetList.resize(BAITAN_BOX_SIZE, PetInit);
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp()
	{
		m_bIsEnable = FALSE;
		for(int32 i = 0; i < BAITAN_BOX_SIZE; i++)
		{
			BAITAN_ITEM ItemInit;

			m_ItemList[i] = ItemInit;

			STALL_PET PetInit;

			m_PetList[i] = PetInit;
		}
	}
};
enum SHOP_TYPE { NO_SHOP = 0, ITEM_SHOP, PET_SHOP, };

/*
 -----------------------------------------------------------------------------------------------------------------------
    标示商店中的所有柜台
 -----------------------------------------------------------------------------------------------------------------------
 */
struct PLAYERSHOP_BOX
{
	std::vector<PLAYERSHOP_STALL_BOX>	m_StallList;
	uint32 m_BaseMoney;
	uint32 m_ProfitMoney;
	SPlayerShopGuid m_ShopID;
	STRING m_szShopName;	/* 标示商店名 */
	STRING m_szShopDesc;	/* 标示商店描述 */
	STRING m_szOwnerName;	/* 标示店主名 */
	uint32 m_OwnerGuid;		/* 店主GUID */
	BYTE m_bIsSaleOut;		/* 此商店已被盘出 */
	uint32 m_uSaleOutPrice;	/* 商店的盘出价 */
	BYTE m_Serial;			/* 商店的序列号 */
	int32 m_nShopType;		/* 商店的类型 */
	BYTE m_ExRecListNum;	/* 交易记录数量 */
	BYTE m_MaRecListNum;	/* 管理记录数量 */
	BYTE m_StallOpenNum;	/* 已经拥有的柜台数 */
	BYTE m_ShopSubType;		/* 商店子类型 */
	std::vector<SPlayerShopPartners> m_PartnerList;	/* 合伙人列表 */

	PLAYERSHOP_BOX (void)
	{
		m_BaseMoney = 0;
		m_ProfitMoney = 0;
		m_szShopName = "";
		m_szOwnerName = "";
		m_szShopDesc = "";
		m_OwnerGuid = 0;
		m_bIsSaleOut = FALSE;
		m_uSaleOutPrice = 0;
		m_Serial = 0;
		m_ExRecListNum = 0;
		m_MaRecListNum = 0;
		m_StallOpenNum = 0;
		PLAYERSHOP_STALL_BOX StallInit;
		m_StallList.resize(MAX_STALL_NUM_PER_SHOP, StallInit);
		SPlayerShopPartners PartnerInit;
		m_PartnerList.resize(MAX_PARTNER_PER_SHOP, PartnerInit);
		m_nShopType = NO_SHOP;
		m_ShopSubType = 0;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp(void)
	{
		m_BaseMoney = 0;
		m_ProfitMoney = 0;
		m_szShopName = "";
		m_szOwnerName = "";
		m_OwnerGuid = 0;
		m_bIsSaleOut = FALSE;
		m_uSaleOutPrice = 0;
		m_Serial = 0;
		m_ExRecListNum = 0;
		m_MaRecListNum = 0;
		m_StallOpenNum = 0;
		m_ShopID.Reset();
		m_nShopType = NO_SHOP;
		m_ShopSubType = 0;

		for(int32 i = 0; i < MAX_STALL_NUM_PER_SHOP; i++)
		{
			m_StallList[i].CleanUp();
		}

		for(int32 i = 0; i < MAX_PARTNER_PER_SHOP; i++)
		{
			m_PartnerList[i].Clear();
		}
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    商店界面上选中的物品
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SELECT_ITEM
{
	int32 m_nConIndex;
	int32 m_nPosition;

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp()
	{
		m_nConIndex = -1;
		m_nPosition = -1;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    任务奖励物品
 -----------------------------------------------------------------------------------------------------------------------
 */
struct sQuestRewardItem
{
	SQuestBonus	*pItemData;
	KItem			*pItemImpl;
	BOOL bSelected;

	sQuestRewardItem (void)
	:
	pItemData(0),
	pItemImpl(0),
	bSelected(FALSE)
	{
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    任务需要物品
 -----------------------------------------------------------------------------------------------------------------------
 */
struct sQuestDemandItem
{
	SQuestBonusItem	*pDemandItem;
	KItem				*pItemImpl;

	sQuestDemandItem (void)
	:
	pDemandItem(0),
	pItemImpl(0)
	{
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    当前打开的银行
 -----------------------------------------------------------------------------------------------------------------------
 */
struct ShopItemActive
{
	int32 m_nNeedGuildLevel;
	int32 m_nNeedGuildExp;

	ShopItemActive()
	{
		CleanUp();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void CleanUp()
	{
		m_nNeedGuildLevel = 0;
		m_nNeedGuildExp = 0;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    交易盒
 -----------------------------------------------------------------------------------------------------------------------
 */
struct CLIENT_EXCHANGCD_BOX
{
	BOOL m_IsLocked;					/* 标示界面上lock选项是否钩上 */
	BOOL m_CanConform;					/* 标示是否显示确定按钮 */
	uint32 m_Siller;					/* 标示交易的现银 */
	std::vector<KItem *> m_ItemList;	/* 标示交易栏中自己的物品 */
	std::vector<SDataPet *> m_Petlist; /* 标示交易栏中自己的宠物 */

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	void CleanUp(void)
	{
		m_CanConform = FALSE;
		m_IsLocked = FALSE;
		m_Siller = 0;

		m_ItemList.resize(EXCHANGE_BOX_SIZE, 0);
		m_Petlist.resize(EXCHANGE_PET_BOX_SIZE, 0);
	};
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    国战信息
 -----------------------------------------------------------------------------------------------------------------------
 */
struct COUNTRYFIGHTALARMINFO
{
	char m_PlayerName[MAX_CHARACTER_NAME];
	int32 m_SceneID;
	int32 m_PosX;
	int32 m_PosZ;
	int32 m_StartTime;

	COUNTRYFIGHTALARMINFO (void)
	{
		ClearUp();
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void ClearUp(void)
	{
		memset(m_PlayerName, 0, sizeof(m_PlayerName));
		m_SceneID = -1;
		m_PosX = 0;
		m_PosZ = 0;
		m_StartTime = 0;
	}
};
};
/* namespace */
#endif /* _GAME_DATA_DEFINE_H_ */
