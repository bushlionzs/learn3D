/*$T MapServer/Server/Other/ShangDianManager.h GC 1.140 10/10/07 10:07:37 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _SHOP_MANAGER_H_
#define _SHOP_MANAGER_H_
#include "TypeDefine.h"
#include "item/Item_Manager.h"
#include "item/ItemBoxManager.h"


#define MAX_SHOP_PER_PERSON		10

#define SHOP_ITEM_PROPERTY_NUM		5
#define SHOP_ID				0
#define SHOP_NAME			1
#define SHOP_BUY_TYPE			3
#define SHOP_PRICE_TYPE			4
#define SHOP_SCALE			5
#define SHOP_RATE			6
#define SHOP_TYPE			7
#define SHOP_REFRESH_TIME_1		8
#define SHOP_REFRESH_TIME_2		9
#define SHOP_ITEM_NUM			10
#define SHOP_TIME_TYPE			11
#define SHOP_START_TIME			12
#define SHOP_END_TIME			13
#define SHOP_ITEM_PROPERTY_BEGIN	14
#define DY_SHOP_ITEM_MAX		30


class	Player;
class		Monster;

struct SShop
{
	struct _MERCHANDISE_LIST
	{
		uchar		m_ListCount;
		SItemType	*m_ListType;
		int32		*m_Price;
		int32		*m_PriceType;
		int32		*m_ListTypeIndex;
		int32		*m_TypeCount;
		int32		*m_TypeMaxNum;
		float		*m_AppearRate;
		int32		m_nCurrent;
		uchar		*m_IconType;

		_MERCHANDISE_LIST()
		{
			m_ListCount = 0;
			m_nCurrent = 0;
			m_Price = NULL;
			m_PriceType = NULL;
			m_ListType = NULL;
			m_ListTypeIndex = NULL;
			m_TypeCount = NULL;
			m_AppearRate = NULL;
			m_IconType = NULL;
		};

		_MERCHANDISE_LIST(uchar num)
		{
			m_ListCount = num;
			m_nCurrent = 0;
			m_Price = new int32[m_ListCount];
			m_PriceType = new int32[m_ListCount];
			m_ListType = new SItemType[m_ListCount];
			m_ListTypeIndex = new int32[m_ListCount];
			m_TypeCount = new int32[m_ListCount];
			m_TypeMaxNum = new int32[m_ListCount];
			m_AppearRate = new float[m_ListCount];
			m_IconType = new uchar[m_ListCount];

			memset(m_Price, 0, sizeof(int32) * m_ListCount);
			memset(m_PriceType, 0, sizeof(int32) * m_ListCount);
			memset(m_ListTypeIndex, 0, sizeof(int32) * m_ListCount);
			memset(m_TypeCount, 0, sizeof(int32) * m_ListCount);
			memset(m_TypeMaxNum, 0, sizeof(int32) * m_ListCount);
			memset(m_AppearRate, 0, sizeof(float) * m_ListCount);
			memset(m_IconType, 0, sizeof(uchar) * m_ListCount);
		}
		~_MERCHANDISE_LIST()
		{
			KSafeDelete_ARRAY(m_ListType)
			KSafeDelete_ARRAY(m_ListTypeIndex)
			KSafeDelete_ARRAY(m_TypeCount)
			KSafeDelete_ARRAY(m_TypeMaxNum)
			KSafeDelete_ARRAY(m_AppearRate)
			KSafeDelete_ARRAY(m_Price)
			KSafeDelete_ARRAY(m_PriceType)
			KSafeDelete_ARRAY(m_IconType)
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void AddType
		(
			SItemType	it,
			int32		Count,
			int32		MaxCount,
			float		Rate,
			uchar		nIconType,
			uchar		nPriceType,
			uint32		nPrice
		)
		{
			KCheck(!it.isNull());
			KCheck(m_nCurrent < m_ListCount);
			m_ListType[m_nCurrent] = it;
			m_ListTypeIndex[m_nCurrent] = it.ToSerial();
			m_TypeCount[m_nCurrent] = Count;
			m_TypeMaxNum[m_nCurrent] = MaxCount;
			m_Price[m_nCurrent] = nPrice;
			m_PriceType[m_nCurrent] = nPriceType;
			m_AppearRate[m_nCurrent] = Rate;
			m_IconType[m_nCurrent++] = nIconType;
		}
	};

	SShop()
	{
		m_ShopId = -1;
		m_nBuyType = -1;
		m_scale = 0.0f;
		m_ItemList = NULL;
		m_refreshTime1 = 0;
		m_refreshTime2 = 0;
		m_IsDyShop = FALSE;
		m_nCustomNum = 0;
		m_nRate = 0;
		m_bRefreshTime2 = FALSE;
		m_nVersion = 0;
		m_bInit = FALSE;
		m_TimeType = -1;
		m_StartTime = -1;
		m_EndTime = -1;

		memset(m_ShopName, 0, sizeof(char) * SHOP_NAME_LENGTH);

		m_bDynamicShop = FALSE;
	}
	SShop(int32 itemNum)
	{
		m_ShopId = -1;
		m_nBuyType = -1;
		m_scale = 0.0f;
		m_ItemList = new _MERCHANDISE_LIST(itemNum);
		m_refreshTime1 = 0;
		m_refreshTime2 = 0;
		m_IsDyShop = FALSE;
		m_nCustomNum = 0;
		m_nRate = 0;
		m_bRefreshTime2 = FALSE;
		m_nVersion = 0;
		m_bInit = FALSE;
		m_TimeType = -1;
		m_StartTime = -1;
		m_EndTime = -1;

		memset(m_ShopName, 0, sizeof(char) * SHOP_NAME_LENGTH);

		m_bDynamicShop = FALSE;
	}
	~SShop()
	{
		KSafeDelete(m_ItemList)
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Custom(Player *pC)
	{
		m_nCustomNum = (pC == NULL) ? (m_nCustomNum - 1) : (m_nCustomNum + 1);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 Custom(void)
	{
		return(m_nCustomNum < 0) ? 0 : m_nCustomNum;
	}

	int32			m_ShopId;

	int32			m_nBuyType;
	uchar			m_PriceType;
	float			m_scale;
	int32			m_refreshTime1;
	int32			m_refreshTime2;
	BOOL			m_bRefreshTime2;
	int32			m_nRate;
	_MERCHANDISE_LIST	*m_ItemList;
	BOOL			m_IsDyShop;
	int32			m_nCustomNum;
	uint32			m_nVersion;
	BOOL			m_bInit;
	char			m_ShopName[SHOP_NAME_LENGTH];
	uchar			m_TimeType;
	uint32			m_StartTime;
	uint32			m_EndTime;

	BOOL		m_bDynamicShop;			// 是动态价格商店
};


class	ShangDianManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	friend class	Player;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ShangDianManager();
	~	ShangDianManager();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL Init()
	{
		return TRUE;
	};
	virtual void	Clear();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SShop *GetShopByIndex(int32 index)
	{
		return &m_Shops[index];
	}

	SShop	*GetShopByID(int32 id);
	int32	GetShopIndexByID(int32 id);

	int32 GetShopElementByItemId(
		Player *pPlayer,
		const uint32 ItemId,
		SPlayerShopElement& element);



/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static int32	ItemType2Money(SItemType it);

	static int32	GetShopItemMoney(SShop *pShop, int32 nPosIndex);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	SShop	*m_Shops;
	int32	m_Count;
};

class StaticShangDianManager :
	public ShangDianManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	StaticShangDianManager()
	{ ;
	}

	~	StaticShangDianManager();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL	Init();
	void	Clear();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	LoadShopsFromFile(char *filename);
};

class DynamicShopMgr :
	public ShangDianManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	DynamicShopMgr(Monster *pboss);
	~	DynamicShopMgr();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetShopsNum() const
	{
		return m_nCurrent;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BOOL	Init();
	void	Clear();
	int32	AddDynamicShop(SShop *pSource);
	BOOL	Tick(uint32 uTime);
	void	Fresh(Map *pMap, SShop *pShop);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32		m_nCurrent;

	CTinyTimer	*m_aRefeshTimer;
	Monster		*m_pBoss;
};

class	ShopMsgHelper
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static uint32	FillData
			(
				SShop			*pShop,
				Player			*pPlayer,
				_MERCHANDISE_ITEM	*pItemArray,
				_GUILD_MERCH_EXINFO	*pExInfoList,
				BOOL			&bExInfoEnable
			);

	
	static int32	FillData
		(
			Player			*pPlayer,
			SPlayerShopElement *pShopElement,
			_MERCHANDISE_ITEM  *pMerchandise
		);

	static int32	SendXCShopItemElementList(
		Player	*pPlayer,
		int32	iElementType);
};

extern StaticShangDianManager	*g_pStaticShangDianManager;
#endif
