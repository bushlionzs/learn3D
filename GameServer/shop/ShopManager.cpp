/*$T MapServer/Server/Other/ShangDianManager.cpp GC 1.140 10/10/07 10:07:37 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "ShopManager.h"

#include "gameobject/Player.h"
#include "gameobject/Monster.h"

#include "TAB.h"
#include "item/Item_Helper.h"
#include "TabDefine_Map_Item.h"
#include "BaseTool.h"
#include "FileDef.h"
#include "map/game_map.h"

using namespace		TAB;
StaticShangDianManager	*g_pStaticShangDianManager = NULL;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ShangDianManager::ShangDianManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_Count = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Shops = NULL;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ShangDianManager::~ShangDianManager()
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ShangDianManager::Clear()
{
	__GUARD__ KSafeDelete_ARRAY(m_Shops) __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ShangDianManager::ItemType2Money(SItemType it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(it.isNull() == FALSE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(it.m_Class)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(it.ToSerial());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_BasePrice;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(it.ToSerial());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nBasePrice;
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(it.ToSerial());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nBasePrice;
			return 1;
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(it.ToSerial());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nPrice;
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(it.ToSerial());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nBasePrice;
		}
		break;

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ShangDianManager::GetShopItemMoney(SShop *pShop, int32 nPosIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nPosIndex < pShop->m_ItemList->m_ListCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pShop->m_IsDyShop)
	{
		return pShop->m_ItemList->m_Price[nPosIndex];
	}

	switch(pShop->m_PriceType)
	{
	case CU_SILLER:
	case CU_BINDSILLER:
		{
			return ItemType2Money(pShop->m_ItemList->m_ListType[nPosIndex]);
		}
		break;

	case CU_HONOR:
	case CU_GP:
	case CU_CREDIT:
	case CU_COUNTRYCREDIT:
	case CU_GOLD:
	case CU_BINDGOLD:
	case CU_GOODBAD:
	case CU_PVP2V2MARK:
    case CU_FEASTSCOR:
	case CU_BATTLEHONOUR:
		{
			return pShop->m_ItemList->m_Price[nPosIndex];
		}
		break;

	default:
		{
			KCheck(pShop->m_ItemList->m_PriceType[nPosIndex] >= 10000000);
			return pShop->m_ItemList->m_Price[nPosIndex];
		}
		break;
	}

	return -1;
	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SShop *ShangDianManager::GetShopByID(int32 id)
{
	__GUARD__ for(int32 i = 0; i < m_Count; i++)
	{
		if(m_Shops[i].m_ShopId == id)
		{
			return &m_Shops[i];
		}
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ShangDianManager::GetShopIndexByID(int32 id)
{
	__GUARD__ for(int32 i = 0; i < m_Count; i++)
	{
		if(m_Shops[i].m_ShopId == id)
		{
			return i;
		}
	}

	return -1;
	__UNGUARD__ return -1;
}

int32 ShangDianManager::GetShopElementByItemId(	Player *pPlayer,
											   const uint32 ItemId,
											   SPlayerShopElement& element)
{
	__GUARD__ if (NULL == pPlayer)
	{
		return -1;
	}

	GameMap* pMap = pPlayer->GetMap();

	if(NULL == pMap)
	{
		return -1;
	}

	for(int32 i = 0; i < m_Count; i++)
	{
		for (int32 j =0; j < m_Shops[i].m_ItemList->m_ListCount;++j )
		{
			if(m_Shops[i].m_ItemList->m_ListTypeIndex[j] == ItemId)
			{
				int32 iShopIndex = pMap->GetLuaSystem()->RunScriptFunction
					(	pMap->MapID(),
					GOLD_SHOP_SCRIPT,
					"GetShopIndexByShopId",
					(int32) pMap->MapID(),
					(int32) pPlayer->GetID(),
					(int32) m_Shops[i].m_ShopId
					);

				if (INVALID_ID != iShopIndex)
				{
					element.m_nShopId = m_Shops[i].m_ShopId;
					element.m_nIndex = j;
					element.m_ItemId = ItemId;

					return 0;
				}	
			}
		}

	}
	return -1;

	__UNGUARD__ return -1;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
StaticShangDianManager::~StaticShangDianManager()
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL StaticShangDianManager::Init()
{
	return LoadShopsFromFile(FILE_SHOP);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void StaticShangDianManager::Clear()
{
	__GUARD__ KSafeDelete_ARRAY(m_Shops) __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL StaticShangDianManager::LoadShopsFromFile(char *filename)
{
	__GUARD__ if(g_GuildMerchTbl.m_bInitOK == FALSE)
	{
		KCheckEx(FALSE, "StaticShopManager的初始化必须在g_TabInit_Map初始化之后");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	d = sizeof(SItem);
	TABFile ShopFile(0);
	BOOL	ret = ShopFile.OpenFromTXT(filename);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!ret) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ShopFile.GetRecordsNum();
	int32	iTableColumn = ShopFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = iTableCount;
	m_Shops = new SShop[m_Count];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		itemnum = 0;
	int32		i, j, k;
	int32		itemTypeSn;
	SItemType	itemType;
	int32		PerItemNum = 0;
	int32		MaxItemNum = 0;
	uint32		nPrice = 0;
	float		PerRate = 0.0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < iTableCount; i++)
	{
		m_Shops[i].m_ShopId = ShopFile.Search_Posistion(i, SHOP_ID)->iValue;
		strncpy(m_Shops[i].m_ShopName, ShopFile.Search_Posistion(i, SHOP_NAME)->pString, SHOP_NAME_LENGTH - 1);
		m_Shops[i].m_ShopName[SHOP_NAME_LENGTH - 1] = 0;
		m_Shops[i].m_nBuyType = ShopFile.Search_Posistion(i, SHOP_BUY_TYPE)->iValue;
		m_Shops[i].m_PriceType = ShopFile.Search_Posistion(i, SHOP_PRICE_TYPE)->iValue;
		m_Shops[i].m_scale = ShopFile.Search_Posistion(i, SHOP_SCALE)->fValue;
		m_Shops[i].m_nRate = ShopFile.Search_Posistion(i, SHOP_RATE)->iValue;
		m_Shops[i].m_IsDyShop = ShopFile.Search_Posistion(i, SHOP_TYPE)->iValue;
		m_Shops[i].m_refreshTime1 = ShopFile.Search_Posistion(i, SHOP_REFRESH_TIME_1)->iValue;
		m_Shops[i].m_refreshTime2 = ShopFile.Search_Posistion(i, SHOP_REFRESH_TIME_2)->iValue;
		itemnum = ShopFile.Search_Posistion(i, SHOP_ITEM_NUM)->iValue;
		KCheck(itemnum <= 40);

		/*~~~~~~~~~~~~~*/
		int32	nNum = 0;
		/*~~~~~~~~~~~~~*/

		for(k = 0; k < itemnum * SHOP_ITEM_PROPERTY_NUM; k++)
		{
			itemTypeSn = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + k)->iValue;

			if(itemTypeSn == 0)
			{
				break;
			}

			nNum++;
			k = k + 4;
		}

		itemnum = nNum;

		m_Shops[i].m_ItemList = new SShop::_MERCHANDISE_LIST(itemnum);

		for(j = 0; j < itemnum * SHOP_ITEM_PROPERTY_NUM; j++)
		{
			itemTypeSn = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + j)->iValue;

			if(m_Shops[i].m_PriceType == CU_GP)
			{
				if(itemTypeSn <= 0 || itemTypeSn >= MAX_GUILD_MERCH)
				{
					/*~~~~~~~~~~~~~~~~~~~*/
					char	assetmsg[1024];
					/*~~~~~~~~~~~~~~~~~~~*/

					sprintf(assetmsg, "文件%s中第%d行第%d列的帮贡商品索引不正确", filename, i, j);
					KCheckEx(FALSE, assetmsg);
				}

				itemTypeSn = g_GuildMerchTbl.m_aMerchList[itemTypeSn - 1].m_nMerchID;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			STSerialHelper	help(itemTypeSn);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			itemType = help.GetItemTypeStruct();

			PerItemNum = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			if(PerItemNum < 0) PerItemNum = 1;
			if(PerItemNum > 100) PerItemNum = 100;

			MaxItemNum = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			if(MaxItemNum == 0) MaxItemNum = -1;
			if(PerItemNum > 100) PerItemNum = 100;

			nPrice = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			if(nPrice == -1) nPrice = 0;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nRate = ShopFile.Search_Posistion(i, SHOP_ITEM_PROPERTY_BEGIN + (++j))->iValue;
			uchar	nIconType = 0;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nRate >= 100)
			{
				nIconType = nRate - 100;
				nRate = 100;
			}

			if(nRate == -1)
				PerRate = 1.0;
			else
				PerRate = (float) nRate / 100;

			m_Shops[i].m_ItemList->AddType
				(
					itemType,
					PerItemNum,
					MaxItemNum,
					PerRate,
					nIconType,
					m_Shops[i].m_PriceType,
					nPrice
				);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
DynamicShopMgr::DynamicShopMgr(Monster *pboss)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pBoss = pboss;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = MAX_SHOP_PER_PERSON;
	m_Shops = new SShop[m_Count];

	m_aRefeshTimer = new CTinyTimer[m_Count];
	memset(m_aRefeshTimer, 0, m_Count * sizeof(CTinyTimer));
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
DynamicShopMgr::~DynamicShopMgr()
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL DynamicShopMgr::Init()
{
	m_nCurrent = 0;
	return(m_Shops != NULL) ? TRUE : FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void DynamicShopMgr::Clear()
{
	KSafeDelete_ARRAY(m_Shops) KSafeDelete_ARRAY(m_aRefeshTimer) return;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 DynamicShopMgr::AddDynamicShop(SShop *pSource)
{
	__GUARD__ if(m_nCurrent > MAX_SHOP_PER_PERSON) return -1;

	for(int32 i = 0; i < m_nCurrent; i++)
	{
		if(m_Shops[i].m_ShopId == pSource->m_ShopId)
		{
			return -1;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	itemnum;
	SShop	&ShopRef = m_Shops[m_nCurrent];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ShopRef.m_ShopId = pSource->m_ShopId;
	ShopRef.m_scale = pSource->m_scale;
	ShopRef.m_refreshTime1 = pSource->m_refreshTime1;
	ShopRef.m_refreshTime2 = pSource->m_refreshTime2;
	itemnum = pSource->m_ItemList->m_ListCount;
	ShopRef.m_ItemList = new SShop::_MERCHANDISE_LIST(DY_SHOP_ITEM_MAX);
	ShopRef.m_ItemList->m_nCurrent = pSource->m_ItemList->m_nCurrent;
	ShopRef.m_nRate = pSource->m_nRate;
	ShopRef.m_ItemList->m_ListCount = DY_SHOP_ITEM_MAX;
	ShopRef.m_IsDyShop = TRUE;
	strncpy(ShopRef.m_ShopName, pSource->m_ShopName, SHOP_NAME_LENGTH - 1);

	if(pSource->m_refreshTime2 > 0)
		m_aRefeshTimer[m_nCurrent].BeginTimer(pSource->m_refreshTime2, GET_TIME().TickCount());

	return m_nCurrent++;
	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL DynamicShopMgr::Tick(uint32 uTime)
{
	__GUARD__ if(!m_pBoss) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Map	*pCurScene = m_pBoss->GetMap();
	int32	GoodsCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < m_nCurrent; i++)
	{
		if(m_Shops[i].m_IsDyShop)
		{
			if(!m_Shops[i].m_bInit)
			{
				Fresh(pCurScene, &m_Shops[i]);
				m_Shops[i].m_bInit = TRUE;
				return TRUE;
			}

			/*~~~~~~~~~~~~~~~~~~~~*/
			BOOL	bRefesh = FALSE;
			/*~~~~~~~~~~~~~~~~~~~~*/

			if(m_Shops[i].m_refreshTime2 > 0)
			{
				if(m_aRefeshTimer[i].CountingTimer(uTime))
				{
					bRefesh = TRUE;
				}
			}
			else if(m_Shops[i].m_refreshTime1 != 0 && !m_Shops[i].m_bRefreshTime2)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				uchar	wday = m_Shops[i].m_refreshTime1 % 10;
				uchar	hour = (m_Shops[i].m_refreshTime1 / 1000);
				uchar	min = (m_Shops[i].m_refreshTime1 % 1000) / 10;
				time_t	time = GET_TIME().GetCTime();
				tm	*ptm = localtime(&time);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(ptm->tm_wday == wday || wday >= 7)
				{
					if(ptm->tm_hour >= hour)
					{
						if(ptm->tm_min >= min)
						{
							bRefesh = TRUE;
							m_Shops[i].m_bRefreshTime2 = TRUE;
						}
					}
				}
			}

			if(bRefesh)
			{
				Fresh(pCurScene, &m_Shops[i]);
			}
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void DynamicShopMgr::Fresh(Map *pMap, SShop *pShop)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 GoodsCount = 0;
	int32		nShopID = pShop->m_ShopId - 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	++pShop->m_nVersion;

	KCheck(nShopID >= 0 && nShopID < MAX_DYSHOP_GROUP);

	for(int32 i = 0; i < pShop->m_ItemList->m_ListCount; i++)
	{
		pShop->m_ItemList->m_ListTypeIndex[i] = 0;
		pShop->m_ItemList->m_TypeMaxNum[i] = 0;
		pShop->m_ItemList->m_Price[i] = 0;
		pShop->m_ItemList->m_PriceType[i] = 0;
	}

	for(int32 j = 0; j < g_ShopInfoTbl.m_aShop[nShopID].m_ItemList->m_ListCount; j++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nGroupID = g_ShopInfoTbl.m_aShop[nShopID].m_ItemList->m_ListTypeIndex[j];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(nGroupID < MAX_DYSHOP_GROUP && (nGroupID - 1) >= 0);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nGoodsNum = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_GoodsNum;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 k = 0; k < nGoodsNum; ++k)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nRand2 = pMap->GetRand100();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nRand2 < g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_Rate)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	nRand3 = pMap->GetRand100();
				int32	nPriceNUm = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_PriceNum;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				switch(g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_RandPriceType)
				{
				case 0:
					{
						nRand3 %= nPriceNUm;

						pShop->m_ItemList->m_Price[GoodsCount] = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_Price[nRand3];
						pShop->m_ItemList->m_PriceType[GoodsCount] = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_PriceType[nRand3];
					}
					break;

				case 1:
					{
						for(int32 m = 0; m < nPriceNUm; ++m)
						{
							if
							(
								pShop->m_ItemList->m_Price[GoodsCount] ==
									g_DyShopInfoTbl.m_aGroupInfo[
										nGroupID - 1].m_Goods[k].m_Price[m]
										&&	pShop->m_ItemList->m_PriceType[GoodsCount] ==
									g_DyShopInfoTbl.m_aGroupInfo[
										nGroupID - 1].m_Goods[k].
											m_PriceType[m]
							)
							{
								/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
								int32	n = (m + 1) % nPriceNUm;
								/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

								pShop->m_ItemList->m_Price[GoodsCount] =
									g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].
										m_Goods[k].m_Price[n];
								pShop->m_ItemList->m_PriceType[GoodsCount] =
									g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].
										m_Goods[k].m_PriceType[n];
								break;
							}
						}

						pShop->m_ItemList->m_Price[GoodsCount] = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_Price[0];
						pShop->m_ItemList->m_PriceType[GoodsCount] = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_PriceType[0];
					}
					break;
				}

				pShop->m_ItemList->m_ListTypeIndex[GoodsCount] = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_ItemID;

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	nCount = g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_ItemNumMax -
					g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_ItemNumMin;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				nRand3 = RandGenerator::GetRand(0, nCount);
				KCheck(nRand3 <= nCount);
				pShop->m_ItemList->m_TypeMaxNum[GoodsCount] = nRand3 + g_DyShopInfoTbl.m_aGroupInfo[nGroupID - 1].m_Goods[k].m_ItemNumMin;
				++GoodsCount;

				if(GoodsCount >= pShop->m_ItemList->m_ListCount) break;
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ShopMsgHelper::FillData
(
	SShop			*pShop,
	Player			*pPlayer,
	_MERCHANDISE_ITEM	*pItemArray,
	_GUILD_MERCH_EXINFO	*pExInfoList,
	BOOL			&bExInfoEnable
)
{
	__GUARD__ if(pShop == NULL || pPlayer == NULL || pItemArray == NULL) return 0;

	bExInfoEnable = FALSE;



	if(pShop->m_PriceType == CU_GP)
	{
		if(pExInfoList != NULL) bExInfoEnable = TRUE;
	}

	/*~~~~~~~~~~*/
	int32	k = 0;
	/*~~~~~~~~~~*/

	for(int32 i = 0; i < pShop->m_ItemList->m_ListCount; i++)
	{
		(pItemArray + k)->idTable = pShop->m_ItemList->m_ListTypeIndex[i];
		if(pShop->m_IsDyShop == TRUE)
			(pItemArray + k)->MaxNumber = pShop->m_ItemList->m_TypeMaxNum[i];
		else
			(pItemArray + k)->MaxNumber = -1;

		switch(pShop->m_IsDyShop)
		{
		case FALSE:
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				uint32	BaseMoney = ShangDianManager::GetShopItemMoney(pShop, i);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(BaseMoney < 0) BaseMoney = 0;

				/*
				 * BaseMoney *= pShop->m_ItemList->m_AppearRate[i];
				 */
				(pItemArray + k)->nPrice = BaseMoney;
				(pItemArray + k)->nPriceType = pShop->m_ItemList->m_PriceType[i];
				(pItemArray + k)->AppearRate = pShop->m_ItemList->m_AppearRate[i];
				(pItemArray + k)->IconType = pShop->m_ItemList->m_IconType[i];
			}
			break;

		case TRUE:
			{
				(pItemArray + k)->nPrice = pShop->m_ItemList->m_Price[i];
				(pItemArray + k)->nPriceType = pShop->m_ItemList->m_PriceType[i];
			}
			break;
		}

		if(pShop->m_PriceType == CU_GP)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	merchIndex = g_GuildMerchTbl.GetIndexByItemID((pItemArray + k)->idTable);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(merchIndex >= 0 && merchIndex < MAX_GUILD_MERCH)
			{
				if(pExInfoList != NULL)
				{
						(
							pExInfoList +
							k
						)->m_nGuildLevel = g_GuildMerchTbl.m_aMerchList[merchIndex].
							m_nGuildLevel;
					(
						pExInfoList +
						k
					)->m_nGuildExp = g_GuildMerchTbl.m_aMerchList[merchIndex].m_nGuildExp;
				}

				GuildCache* pCache = GuildCacheManager::GetInstance().GetCache( pPlayer->GetWorldID(),pPlayer->GetGuildID() );
				if( pCache && pCache->IsGoodsActiveToGuild(merchIndex) )
				{
					(pItemArray + k)->byActiveState |= 1 << SHOP_ACTIVE_GUILD;
				}
			}
		}
		(pItemArray + k)->byNumber = pShop->m_ItemList->m_TypeCount[i];
		k++;
	}

	return k;
	__UNGUARD__ return 0;
}

int32 ShopMsgHelper::FillData
(
	Player			*pPlayer,
	SPlayerShopElement *pShopElement,
	_MERCHANDISE_ITEM  *pMerchandise
 )
{
	__GUARD__ 

	if (NULL == pPlayer || NULL == pShopElement || NULL == pMerchandise)
	{
		return -1;
	}
	
	Map* pMap = pPlayer->GetMap();

	if(NULL == pMap)
	{
		return -1;
	}

	int32 iShopId = pShopElement->m_nShopId;
	int32 iIndex = pShopElement->m_nIndex;
	uint32 iItemId = pShopElement->m_ItemId;

	BOOL bFoundItemByIndex = TRUE;

	//检查各个条件
	//ShopId
	SShop	*pShop = g_pStaticShangDianManager->GetShopByID(iShopId);
	if(bFoundItemByIndex) 
	{
		if (NULL == pShop)
		{
			bFoundItemByIndex = FALSE;
		}
	}

	//ShopIndex
	int32 iShopIndex = pMap->GetLuaSystem()->RunScriptFunction
		(	pMap->MapID(),
			GOLD_SHOP_SCRIPT,
			"GetShopIndexByShopId",
			(int32) pMap->MapID(),
			(int32) pPlayer->GetID(),
			(int32) iShopId
		);

	if (INVALID_ID == iShopIndex)
	{		
		bFoundItemByIndex = FALSE;	
	}

	//Shop Index
	if (bFoundItemByIndex)
	{
		if (iIndex < 0 || iIndex >= pShop->m_ItemList->m_ListCount)
		{
			bFoundItemByIndex = FALSE;
		}
	}

	//Item Id
	if(bFoundItemByIndex)
	{
		if (iItemId != (uint32)(pShop->m_ItemList->m_ListTypeIndex[iIndex]))
		{
			bFoundItemByIndex = FALSE;
		}
	}

	//从表中获取信息
	if (FALSE == bFoundItemByIndex)
	{
		int32 iRet = g_pStaticShangDianManager->GetShopElementByItemId(pPlayer,iItemId,*pShopElement);

		if (iRet !=0 )
		{
			return -1;
		}

		iShopId = pShopElement->m_nShopId;
		iIndex = pShopElement->m_nIndex;

		pShop = g_pStaticShangDianManager->GetShopByID(iShopId);

		if (NULL == pShop)
		{
			return -1;
		}

		if (iIndex < 0 || iIndex >= pShop->m_ItemList->m_ListCount)
		{
			return -1;
		}

		iShopIndex = pMap->GetLuaSystem()->RunScriptFunction
			(	pMap->MapID(),
			GOLD_SHOP_SCRIPT,
			"GetShopIndexByShopId",
			(int32) pMap->MapID(),
			(int32) pPlayer->GetID(),
			(int32) iShopId
			);

		if (INVALID_ID == iShopIndex)
		{		
			return -1;
		} 

		if (iItemId != (uint32)(pShop->m_ItemList->m_ListTypeIndex[iIndex]))
		{
			return -1;
		}

	}

	pShopElement->m_nShopId =  iShopIndex;//给客户端实际发的是ShopIndex

	pMerchandise->idTable = pShop->m_ItemList->m_ListTypeIndex[iIndex];

	if(pShop->m_IsDyShop == TRUE)
		pMerchandise->MaxNumber = pShop->m_ItemList->m_TypeMaxNum[iIndex];
	else
		pMerchandise->MaxNumber = -1;

	switch(pShop->m_IsDyShop)
	{
		case FALSE:
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				uint32	BaseMoney = ShangDianManager::GetShopItemMoney(pShop, iIndex);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(BaseMoney < 0) BaseMoney = 0;

				pMerchandise->nPrice = BaseMoney;
				pMerchandise->nPriceType = pShop->m_ItemList->m_PriceType[iIndex];
				pMerchandise->AppearRate = pShop->m_ItemList->m_AppearRate[iIndex];
				pMerchandise->IconType   = pShop->m_ItemList->m_IconType[iIndex];
			}
			break;

		case TRUE:
			{
				pMerchandise->nPrice = pShop->m_ItemList->m_Price[iIndex];
				pMerchandise->nPriceType = pShop->m_ItemList->m_PriceType[iIndex];
			}
			break;
	}

	pMerchandise->byNumber = pShop->m_ItemList->m_TypeCount[iIndex];


	return 0;
	__UNGUARD__ return -1;	
}

int32	ShopMsgHelper::SendXCShopItemElementList(
	Player	*pPlayer,
	int32	iElementType)
{

	__GUARD__

	if (NULL == pPlayer)
	{
		return -1;
	}

	Map* pMap = pPlayer->GetMap();

	if(NULL == pMap)
	{
		return -1;
	}

	if (iElementType != XCShopItemElementList::ELEMENT_FAVORITE
		&& iElementType != XCShopItemElementList::ELEMENT_BUYHISTORY)
	{
		return -1;
	}

	const SPlayerShopFolder* pShopFolder = NULL;

	if (iElementType == XCShopItemElementList::ELEMENT_FAVORITE)
	{
		pShopFolder = pPlayer->GetShopItemFavorite();
	}
	else if (iElementType == XCShopItemElementList::ELEMENT_BUYHISTORY)
	{
		pShopFolder = pPlayer->GetShopItemBuyHistory();
	}

	if (NULL != pShopFolder)
	{
		XCShopItemElementList Msg;			

		Msg.SetElementType(iElementType);

		SPlayerShopElement aElement;
		_MERCHANDISE_ITEM aMerchandise;

		uint32  delItemIdList[MAX_SHOP_ELEMENT_NUMBER] = {0};
		int32 iDelCount = 0;

		for (int k =0;k < 2 && pShopFolder->m_count > 0;++k)
		{
			int32 i =-1;
			int32 iEnd = 0;

			if (k ==0)//第一区间
			{
				i = pShopFolder->m_index;
				iEnd =0;			
			}
			else if (k == 1)//第二区间
			{
				i = pShopFolder->m_count - 1;
				iEnd =  pShopFolder->m_index + 1;
			}

			for (;i >= iEnd;--i)
			{

				aElement = (*pShopFolder).m_list[i];

				aMerchandise.Clear();

				int32 ret = ShopMsgHelper::FillData(
					pPlayer,
					&aElement,
					&aMerchandise);

				if(ret != 0)
				{
					delItemIdList[iDelCount++] = (*pShopFolder).m_list[i].m_ItemId;
					continue;
				}

				Msg.AddElement(aElement);

				Msg.GetMerchadiseList()[Msg.GetElementCount()-1] = aMerchandise;

			}
		}

		SPlayerShopElement delElement;

		for (int32 j =0;j < iDelCount; ++j)
		{
			delElement.m_ItemId = delItemIdList[j];
			if (iElementType == XCShopItemElementList::ELEMENT_FAVORITE)
			{
				pPlayer->DelShopItemFavorite(delElement);
			}
			else if (iElementType == XCShopItemElementList::ELEMENT_BUYHISTORY)
			{
				pPlayer->DelShopItemBuyHistory(delElement);
			}
		}

		
		pPlayer->GetConnector()->SendPacket(&Msg);
	}

	return 0;

	__UNGUARD__ return -1;
}