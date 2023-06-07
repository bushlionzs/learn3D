/*$T Client/Game/DataPool/GameDataStructPlayerShop.h GC 1.140 08/23/09 04:52:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#pragma once

/* 商店类型 */
enum TYPE_PLAYER_SHOP
{
	TYPE_PLAYER_SHOP_INVALID	= 0,		/* 无效类别，还没有分配出去 */
	TYPE_PLAYER_SHOP_ITEM,					/* 物品店 */
	TYPE_PLAYER_SHOP_GEM,					/* 宝石店 */
	TYPE_PLAYER_SHOP_WEAPON,				/* 武器店 */
	TYPE_PLAYER_SHOP_ARMOR,					/* 护甲店 */
	TYPE_PLAYER_SHOP_MATERIAL,				/* 材料店 */
	TYPE_PLAYER_SHOP_PET,					/* 宠物店 */
};

struct SPlayershopApplyInfo
{
	FLOAT	m_ComFactor;					/* 当前商业指数 */
	uint32	m_Cost;							/* 开店金额 */
	BYTE	m_Type;							/* 可开的类型 */
	SPlayershopApplyInfo()
	{
		memset(this, 0, sizeof(SPlayershopApplyInfo));
	}
};

struct SPlayerShopInfo
{
	String				m_szShopName;		/* 商店名 */
	String				m_szShopDesc;		/* 商店描述 */
	String				m_szOwnerName;		/* 摊主名 */
	BYTE				m_StallNumOpened;	/* 开放的柜台数 */
	BYTE				m_StallNumOnSale;	/* 开张的柜台数 */
	BYTE				m_Type;				/* 店铺的类型 */
	SPlayerShopGuid	m_ID;				/* 店铺的唯一ID */
	uint32				m_OwnerGuid;		/* 摊主GUID */
	String				m_szFoundedTime;	/* 建立时间 */
	BYTE				m_Serial;			/* 商店序列号 */
	BYTE				m_bIsFavor;			/* 是否在收藏家内 */

	SPlayerShopInfo()
	{
		m_szShopName = "";					/* 商店名 */
		m_szShopDesc = "";					/* 商店描述 */
		m_szOwnerName = "";					/* 摊主名 */
		m_StallNumOpened = 0;				/* 开放的柜台数 */
		m_StallNumOnSale = 0;				/* 开张的柜台数 */
		m_Type = 0;				/* 店铺的类型 */
		m_ID.Reset();			/* 店铺的唯一ID */
		m_OwnerGuid = 0;		/* 摊主GUID */
		m_szFoundedTime = "";	/* 建立时间 */
		m_Serial = 0;
		m_bIsFavor = 0;			/* 是否在收藏家内 */
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    玩家商店合伙人 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SPlayerShopPartners
{
	GUID_t	m_Guid;
	String	m_szName;

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Clear()
	{
		m_Guid = INVALID_GUID;
		m_szName = "";
	}
};
