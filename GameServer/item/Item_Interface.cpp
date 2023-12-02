/*$T MapServer/Server/Item/ItemInterface.cpp GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_Interface.h"
#include "Item_Manager.h"
#include "Item_Ruler.h"
#include "Item_Base.h"
#include "gameobject/Player.h"
#include "ItemInstance.h"
#include "BaseTool.h"
#include "map/game_map.h"
#include "server_settting.h"
#include "item/ItemInstanceManager.h"
#include "ScriptDef.h"
#include "net/messages/SCItemInfo.h"
#include "net/messages/SCNotifyEquip.h"
#include "net/net_message_manager.h"
#include "server_manager.h"

/*
 =======================================================================================================================
 构造函数
 =======================================================================================================================
 */

ItemInterface::ItemInterface()
{
}

/*
 =======================================================================================================================
 析构函数
 =======================================================================================================================
 */
ItemInterface::~ItemInterface()
{
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseItem
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	ItemContainer		*pDestContainer,
	uint32			uSlot
)
{
	KCheck(pLogParam);
	KCheck(pDestContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pDestContainer->GetItem(uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	uchar uBindType = BIND_NONE;
	if(IDT_ITEM == pItem->GetDataType())
	{
		uBindType = pItem->GetItemBindType();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = EraseItem_i(pPlayer, pDestContainer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{

	}

	return bRet;
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseBagItemBySlot
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	uint32			uSlot,
	BOOL			bCheckEquipLock,
	uint32			uCount
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = GetBagItem(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);


	uchar uBindType = pItem->GetItemBindType();

	uchar uRetBindType = BIND_NONE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = EraseBagItemBySlot_i(pPlayer, uSlot, pItem, uRetBindType, bCheckEquipLock, uCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseBankItemBySlot(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < MAX_BANK_SIZE);
	KCheck(pPlayer);

	m_uBind = BIND_NONE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetBankContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uItemIndex = pItem->GetItemTableIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItem->IsLock()) return FALSE;

	uchar uBindType = pItem->GetItemBindType();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = EraseItem_i(pPlayer, pContainer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		if(IDT_ITEM == pItem->GetDataType())
		{
			pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
		}
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseEquipItemBySlot(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < HEQUIP_NUMBER);
	KCheck(pPlayer);

	m_uBind = BIND_NONE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	if(pItem->IsLock()) return FALSE;

	uchar uBindType = pItem->GetItemBindType();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uItemIndex = pItem->GetItemTableIndex();
	BOOL	bRet = EraseItem_i(pPlayer, pContainer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		if(IDT_ITEM == pItem->GetDataType())
		{
			pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
		}
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseBagItemByItemList(ItemLogRecordInfo *pLogParam, Player *pPlayer, SItemList &List)
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uchar bBind = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 iListIndex = 0; iListIndex < List.m_ListCount; iListIndex++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bEraseItem = EraseBagItemByIndex
			(
				pLogParam,
				pPlayer,
				List.m_ListType[iListIndex].ToSerial(),
				List.m_TypeCount[iListIndex]
			);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(FALSE == bEraseItem) return FALSE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseBagItemByIndex(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uItemIndex, uint32 uCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uItemIndex != INVALID_ID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex > 0);
	KCheck(uCount > 0);
	KCheck(pPlayer);
	KCheck(pLogParam);

	m_uBind = BIND_NONE;
	if(uCount < 0)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pContainer = pPlayer->GetBaseContain();
	KCheck(pContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	bTBind = 0;
	int32	nRemainCount = EraseBagItem_i(pPlayer, pContainer, uItemIndex, uCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bTBind == 0)
	{
		bTBind = m_uBind;
	}
	else
	{
		m_uBind = BIND_NORMAL;
	}

	if(nRemainCount > 0)
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pContainer = pPlayer->GetExtraBagContain(i);
			KCheck(pContainer);
			if(pContainer->IsValid())
			{
				nRemainCount = EraseBagItem_i(pPlayer, pContainer, uItemIndex, nRemainCount, TRUE, 0);
				if(bTBind == 0)
				{
					bTBind = m_uBind;
				}
				else
				{
					m_uBind = BIND_NORMAL;
				}
			}

			if(nRemainCount <= 0)
			{
				break;
			}
		}
	}

	if(nRemainCount > 0) return FALSE;

	pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 丢弃操作
 =======================================================================================================================
 */
BOOL ItemInterface::DropBagItem(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uItemIndex = pItem->GetItemIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItem->IsLock()) return FALSE;

	/*~~~~~~~~~~~~~*/
	SItem	itemData;
	/*~~~~~~~~~~~~~*/

	pItem->SaveValueTo(&itemData);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = EraseItem_i(pPlayer, pContainer, pContainer->BagIndex2ConIndex(uSlot));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);



		/*~~~~~~~~~~~~~~~~~*/
		GLPos	nPos;
		/*~~~~~~~~~~~~~~~~~*/

		nPos.m_fX = pPlayer->GetGLPos()->m_fX;
		nPos.m_fZ = pPlayer->GetGLPos()->m_fZ;
		if(pPlayer->GetNearCanDropPos(nPos))
		{
	

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemInstanceManager	*pIBManager = pPlayer->GetMap()->GetItemInstanceManager();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIBManager);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemInstance	*pObj_Item = (ItemInstance *) pIBManager->CreatePersonDropItemInstance
				(
					&nPos,
					&itemData
				);

		}

		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 丢弃操作
 =======================================================================================================================
 */
BOOL ItemInterface::DropEquip(ItemLogRecordInfo *pLogParam, Player *pPlayer, PLAYER_EQUIP uEquipPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uEquipPoint < HEQUIP_NUMBER);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(uEquipPoint);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	if(pItem->IsLock()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uItemIndex = pItem->GetItemIndex();
	SItem	itemData;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pItem->SaveValueTo(&itemData);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = EraseItem_i(pPlayer, pContainer, uEquipPoint);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
		FillAndSaveItemLog(pLogParam, pPlayer, NULL);



		/*~~~~~~~~~~~~~~~~~*/
		GLPos	nPos;
		/*~~~~~~~~~~~~~~~~~*/

		nPos.m_fX = pPlayer->GetGLPos()->m_fX;
		nPos.m_fZ = pPlayer->GetGLPos()->m_fZ;
		if(pPlayer->GetNearCanDropPos(nPos))
		{


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemInstanceManager	*pIBManager = pPlayer->GetMap()->GetItemInstanceManager();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIBManager);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemInstance	*pObj_Item = (ItemInstance *) pIBManager->CreatePersonDropItemInstance
				(
					&nPos,
					&itemData
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pObj_Item);
			pObj_Item->SetDropObjID(pPlayer->GetID());
			pObj_Item->SetActiveFlag(TRUE);
		}

		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateMultiItemToInventory
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	uint32			uItemIndex,
	uint32			uCount,
	uchar			bBind
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uItemIndex != 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != INVALID_ID);
	KCheck(uCount > 0);
	KCheck(pPlayer);
	KCheck(pLogParam);

	/*~~~~~~~~~~~~~~*/
	int32	iNewCount;
	/*~~~~~~~~~~~~~~*/

	uchar uFinalBind = bBind;
	if(BIND_GOLD == bBind)
	{
		uFinalBind |= IEI_GBIND_INFO;
	}
	if(CheckItemRuler::CheckRuler(IRL_PICKBIND, GetItemRuler(uItemIndex)))
	{
		uFinalBind |= IEI_PBIND_INFO;
	}

	if(HaveEnoughBagItemSpace(pPlayer, uItemIndex, uCount, iNewCount, uFinalBind))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	iBagIndex = INVALID_INDEX;
		uint32	iOldBagIndex = INVALID_INDEX;
		uint32	uLastCount = uCount;
		uint32	uEachPileCount = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(uint32 iCount = 0; iCount < uCount; iCount++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL	ret = CreateItemToBagByItemIndex_i(pPlayer, uItemIndex, iBagIndex, uFinalBind, 0);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!ret)
			{
				KCheck(0);
			}

			if(iCount == 0)
			{
				iOldBagIndex = iBagIndex;
			}

			if(iBagIndex != iOldBagIndex)
			{

				SCNotifyEquip* packet = new SCNotifyEquip;
				packet->setBagIndex(iOldBagIndex);
				Item* pItem = GetBagItem(pPlayer, iOldBagIndex);
				pItem->SaveValueTo(packet->getItem());
				//NetManager::GetSingletonPtr()->sendNetMessage(packet);
				iOldBagIndex = iBagIndex;

				uLastCount -= uEachPileCount;
				uEachPileCount = 1;
			}
			else
			{
				uEachPileCount++;
			}
		}

		if(iBagIndex != INVALID_INDEX)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pChangedItem = GetBagItem(pPlayer, iBagIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			

			KCheck(pChangedItem);

			if(pChangedItem->GetLayedNum() == uLastCount)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Item* pItem = GetBagItem(pPlayer, iBagIndex);

				SCNotifyEquip* packet = new SCNotifyEquip;
				packet->setBagIndex(iBagIndex);
				pItem->SaveValueTo(packet->getItem());
				//NetManager::GetSingletonPtr()->sendNetMessage(packet);
			}
			else
			{
				SCItemInfo* packet = new SCItemInfo;
				packet->setIsNull(false);
				packet->setId(iBagIndex);
				packet->setTips(1);
				pChangedItem->SaveValueTo(packet->getItem());
				//NetManager::GetSingletonPtr()->sendNetMessage(packet);
			}
			
			pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ADDITEM);
		}

		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateItemToBagByItemIndex
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	uint32			uItemIndex,
	uint32			&uSlot,
	uchar			bBind
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != 0);
	KCheck(uItemIndex != INVALID_ID);
	KCheck(pLogParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = CreateItemToBagByItemIndex_i(pPlayer, uItemIndex, uSlot, bBind);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = GetBagItem(pPlayer, uSlot);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateItemToBagByINIT
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	_CREATEITEM_INIT	*pInit,
	uint32			&uSlot,
	uchar			&bRetBind ,
	uchar			bBind
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);
	KCheck(pLogParam);

	if(pInit->m_nItemIndex == 0 || pInit->m_nItemIndex == INVALID_ID) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetBaseContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	if(!pContainer)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uContainerPos;
	BOOL	bPickBind = CheckItemRuler::CheckRuler(IRL_PICKBIND, GetItemRuler(pInit->m_nItemIndex));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bPickBind)
	{
		if(bBind == BIND_NONE) 
		{
			bBind = BIND_NORMAL;
			bRetBind =BIND_NORMAL;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = CreateItem_i(bBind, pContainer, uContainerPos, pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(uContainerPos);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		pPlayer->OnEvent_ItemChanged(pInit->m_nItemIndex, ITEM_CHANGE_ADDITEM);
		uSlot = pContainer->ConIndex2BagIndex(uContainerPos);
		FillAndSaveItemLog(pLogParam, pPlayer, pItem);
	}
	else
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pContainer = pPlayer->GetExtraBagContain(i);
			KCheck(pContainer);
			if(pContainer->IsValid())
			{
				if(pContainer->IsCanUse())
				{
					bRet = CreateItem_i(bBind, pContainer, uContainerPos, pInit);
				}
			}

			if(bRet)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Item	*pItem = pContainer->GetItem(uContainerPos);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				KCheck(pItem);
				pPlayer->OnEvent_ItemChanged(pInit->m_nItemIndex, ITEM_CHANGE_ADDITEM);
				uSlot = pContainer->ConIndex2BagIndex(uContainerPos);
				FillAndSaveItemLog(pLogParam, pPlayer, pItem);
				break;
			}
		}

		if(!bRet) uSlot = INVALID_INDEX;
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateItemToContainer
(
	ItemLogRecordInfo	*pLogParam,
	uint32			uItemIndex,
	ItemContainer		*pDestContainer,
	BOOL			&bNewEmptyPos,
	uint32			&uConIndex,
	int32			nDestIndex
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDestContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != 0);
	KCheck(uItemIndex != INVALID_ID);
	KCheck(pLogParam);
	if(!pDestContainer->IsValid())
	{
		return FALSE;
	}

	if(uItemIndex == 0 || uItemIndex == INVALID_ID) return FALSE;

	if(!pDestContainer->IsCanUse())
	{
		return FALSE;
	}

	uConIndex = INVALID_INDEX;
	bNewEmptyPos = FALSE;

	if(nDestIndex != INVALID_INDEX)
	{
		KCheck(nDestIndex < pDestContainer->GetContainerSize());

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pDestContainer->GetItem(nDestIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		if(pItem->IsFree())
		{
			/*~~~~~~~~~~~~~~~*/
			SItem	createItem;
			/*~~~~~~~~~~~~~~~*/

			g_pItemMgr->CreateItem(uItemIndex, createItem);

			if(createItem.IsNullType())
			{
				return FALSE;
			}

			createItem.SetItemBindType(BIND_NONE);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pDestItem = pDestContainer->GetItem(nDestIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pDestItem->IsFree())
			{
				pDestContainer->SetItemValue(nDestIndex, &createItem);
				return TRUE;
			}
			else
			{
				KCheck(FALSE);
			}
		}

		if(pItem->GetItemTableIndex() != uItemIndex)
		{
			return FALSE;
		}

		if(CheckItemRuler::CheckTypeRuler(IRL_TILE, uItemIndex))
		{
			if(pItem->IsLock())
			{
				return FALSE;
			}

			if(pItem->GetLayedNum() < pItem->GetMaxLayedNum())
			{
				uConIndex = nDestIndex;
				bNewEmptyPos = FALSE;
				return IncItemLayedNum(pDestContainer, nDestIndex);
			}

			return FALSE;
		}
	}

	if(CheckItemRuler::CheckTypeRuler(IRL_TILE, uItemIndex))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iNoFullBagIndex = pDestContainer->GetNoFullItemIndexAndBind(uItemIndex, BIND_NONE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iNoFullBagIndex != INVALID_INDEX)
		{
			uConIndex = iNoFullBagIndex;
			bNewEmptyPos = FALSE;

			return IncItemLayedNum(pDestContainer, iNoFullBagIndex);
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iEmptyBagIndex = pDestContainer->GetFreeItemIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iEmptyBagIndex != INVALID_INDEX)
	{
		/*~~~~~~~~~~~~~~~*/
		SItem	createItem;
		/*~~~~~~~~~~~~~~~*/

		g_pItemMgr->CreateItem(uItemIndex, createItem);

		if(createItem.IsNullType())
		{
			return FALSE;
		}

		createItem.SetItemBindType(BIND_NONE);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pDestItem = pDestContainer->GetItem(iEmptyBagIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDestItem);
		if(pDestItem->IsFree())
		{
			pDestContainer->SetItemValue(iEmptyBagIndex, &createItem);
			bNewEmptyPos = TRUE;
			uConIndex = iEmptyBagIndex;
			FillAndSaveItemLog(pLogParam, 0, pDestItem);
			return TRUE;
		}
		else
		{
			KCheck(FALSE);
		}
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 获得操作
 =======================================================================================================================
 */
BOOL ItemInterface::RecieveItemToInventory(ItemLogRecordInfo *pLogParam, Player *pPlayer, SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);
	KCheck(pItem);
	KCheck(!pItem->IsNullType());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		newSpace = INVALID_INDEX;
	int32		nFinalIndex = INVALID_INDEX;
	ItemContainer	*pItemContainer;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pItemContainer = pPlayer->GetBaseContain();
	KCheck(pItemContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SItemType	Itemtype = Serial2ItemType(pItem->m_ItemIndex);
	uchar		nMaxLayNum = GetMaxItemTile(Itemtype);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nMaxLayNum > 1)
	{
		nFinalIndex = pItemContainer->GetIndexByTypeAndBind(
				pItem->m_ItemIndex,
				pItem->GetItemCount(),
				pItem->GetItemBindType()
			);
		/*if(nFinalIndex < 0)
		{
			for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
			{
				pItemContainer = pPlayer->GetExtraBagContain(i);
				KCheck(pItemContainer);
				if(pItemContainer->IsValid())
				{
					if(pItemContainer->IsCanUse())
					{
						nFinalIndex = pItemContainer->GetIndexByTypeAndBind
							(
								pItem->m_ItemIndex,
								pItem->GetItemCount(),
								pItem->GetItemBindType()
							);
					}
				}

				if(nFinalIndex >= 0)
				{
					break;
				}
			}
		}*/

		if(nFinalIndex >= 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	ret = MoveItem_i(pItemContainer, pItem, nFinalIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(ret >= 0);
		}
	}

	if(nFinalIndex < 0)
	{
		pItemContainer = pPlayer->GetBaseContain();
		KCheck(pItemContainer);
		nFinalIndex = MoveItem_i(pItemContainer, pItem);

		if(nFinalIndex < 0)
		{
			for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
			{
				pItemContainer = pPlayer->GetExtraBagContain(i);
				KCheck(pItemContainer);
				if(pItemContainer->IsValid())
				{
					if(pItemContainer->IsCanUse())
					{
						nFinalIndex = MoveItem_i(pItemContainer, pItem);
					}
				}

				if(nFinalIndex >= 0)
				{
					break;
				}
			}
		}
	}

	if(nFinalIndex >= 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pDestItem = pItemContainer->GetItem(nFinalIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDestItem);

		if(pDestItem->GetLayedNum() == pItem->GetItemCount())
		{

			SCNotifyEquip* packet = new SCNotifyEquip;
			int index = pItemContainer->ConIndex2BagIndex(nFinalIndex);
			packet->setBagIndex(index);
			pDestItem->SaveValueTo(packet->getItem());

			//NetManager::GetSingletonPtr()->sendNetMessage(packet);
		}
		else
		{
			SCItemInfo* packet = new SCItemInfo;

			int32_t index = pItemContainer->ConIndex2BagIndex(nFinalIndex);
			packet->setId(index);
			packet->setIsNull(false);
			packet->setTips(1);
			pDestItem->SaveValueTo(packet->getItem());

			//NetManager::GetSingletonPtr()->sendNetMessage(packet);
		}

		pPlayer->OnEvent_ItemChanged(pDestItem->GetItemTableIndex(), ITEM_CHANGE_ADDITEM);

		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 获得操作
 =======================================================================================================================
 */
BOOL ItemInterface::ReceiveBagItemList(ItemLogRecordInfo *pLogParam, Player *pPlayer, SItemList &List)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(List.m_ListCount > 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < List.m_ListCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SItemType	itemType = List.m_ListType[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!CreateMultiItemToInventory(pLogParam, pPlayer, itemType.ToSerial(), List.m_TypeCount[i], List.m_bBind[i]))
		{
			return FALSE;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 获得操作
 =======================================================================================================================
 */
BOOL ItemInterface::RecieveItemToInventory
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	ItemContainer		*pContainer,
	uint32			uIndex
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);
	KCheck(pContainer);
	KCheck(pContainer->IsValid());
	KCheck(uIndex < (uint32) pContainer->GetContainerSize());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItemInSource = pContainer->GetItem(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemInSource);
	if(pItemInSource->IsFree())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uItemIndex = pItemInSource->GetItemTableIndex();
	uint32	uCount = pItemInSource->GetLayedNum();
	BOOL	bFlag = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	UnlockItem(pContainer, uIndex);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pMyContainer = pPlayer->GetBaseContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMyContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	result = MoveItem_i(pContainer, uIndex, bFlag, pMyContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(result < 0)
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pMyContainer = pPlayer->GetExtraBagContain(i);
			KCheck(pMyContainer);
			if(pMyContainer->IsValid())
			{
				if(pMyContainer->IsCanUse())
				{
					result = MoveItem_i(pContainer, uIndex, bFlag, pMyContainer);
				}
			}

			if(result >= 0)
			{
				break;
			}
		}

		if(result < 0)
		{
			return FALSE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItemDest = pMyContainer->GetItem(result);
	uint32	ToIndex = pMyContainer->ConIndex2BagIndex(result);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemDest);
	if(pItemDest->IsRuler(IRL_PICKBIND))
	{
		SetItemBind(pMyContainer, result);
	}

	if(pItemDest->GetLayedNum() == uCount)
	{
		
	}
	else
	{
		
	}

	pPlayer->OnEvent_ItemChanged(pItemDest->GetItemTableIndex(), ITEM_CHANGE_ADDITEM);
	FillAndSaveItemLog(pLogParam, pPlayer, pItemDest);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 减少堆叠操作
 =======================================================================================================================
 */
BOOL ItemInterface::DecBagItemLayCount(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot, uint32 uCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pItem->IsFree()) return FALSE;
	if(pItem->IsLock()) return FALSE;

	if(pItem->GetLayedNum() == 0)
	{
		KCheck(FALSE);
	}
	else if(pItem->GetLayedNum() > 0)
	{
		char uBindType = pItem->GetItemBindType();
		if(pItem->IsGoldBound())
		{

		}



		uint32 idx = pItem->GetItemTableIndex();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bRet = DecItemLayedNum(pContainer, pContainer->BagIndex2ConIndex(uSlot), uCount);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(bRet)
		{
			pPlayer->OnEvent_ItemChanged(idx, ITEM_CHANGE_ERASEITEM);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pItem);
			FillAndSaveItemLog(pLogParam, pPlayer, NULL);
			if(pItem->IsFree())
			{
			
			}
			else
			{
		
			}
		}

		return bRet;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 增加堆叠操作
 =======================================================================================================================
 */
BOOL ItemInterface::IncBagItemLayCount(ItemLogRecordInfo *pLogParam, Player *pPlayer, uint32 uSlot, uint32 uCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pItem->IsFree()) return FALSE;
	if(pItem->IsLock()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = IncItemLayedNum(pContainer, pContainer->BagIndex2ConIndex(uSlot), uCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		FillAndSaveItemLog(pLogParam, pPlayer, pItem);

	
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 移动操作
 =======================================================================================================================
 */
int32 ItemInterface::MoveItemToBag
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	ItemContainer		*pContainer,
	uint32			uSlot
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);
	KCheck(pContainer);
	KCheck(pContainer->IsValid());
	KCheck(uSlot < (uint32) pContainer->GetContainerSize());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pContainer->GetItem(uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pSourItem);

	if(!pSourItem)
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		nBagSlot = INVALID_INDEX;
	uint32		uItemIndex = pSourItem->GetItemTableIndex();
	int32		uContainIndex = -1;
	ItemContainer	*pHumanContainer = pPlayer->GetBaseContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pHumanContainer);

	uContainIndex = MoveItem_i(pContainer, uSlot, pHumanContainer);
	if(uContainIndex < 0)
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pHumanContainer = pPlayer->GetExtraBagContain(i);
			KCheck(pHumanContainer);
			if(pHumanContainer->IsValid())
			{
				if(pContainer->GetContainerType() == ICT_EXTRA_CONTAINER)
				{
					if(uSlot == i)
					{
						continue;
					}
				}

				if(pHumanContainer->IsCanUse())
				{
					uContainIndex = MoveItem_i(pContainer, uSlot, pHumanContainer);
					if(uContainIndex >= 0)
					{
						break;
					}
				}
			}
		}
	}

	if(uContainIndex < 0)
	{
		nBagSlot = uContainIndex;
		return nBagSlot;
	}
	else if(uContainIndex < (uint32) pHumanContainer->GetContainerSize())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pHumanContainer->GetItem(uContainIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		nBagSlot = pHumanContainer->ConIndex2BagIndex(uContainIndex);
		pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ADDITEM);
		return nBagSlot;
	}

	return ITEMOE_UNKNOW;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 移动操作
 =======================================================================================================================
 */
int32 ItemInterface::MoveItemInSameContainer
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	ItemContainer		*pContainer,
	uint32			uSrcSlot,
	uint32			uDstSlot
)
{
	KCheck(pLogParam);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRet = MoveItem_i(pContainer, uSrcSlot, pContainer, uDstSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nRet;
}

/*
 =======================================================================================================================
 移动操作
 =======================================================================================================================
 */
int32 ItemInterface::MoveItemBt2Containers
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	ItemContainer		*pSrcCon,
	uint32			uSrcSlot,
	ItemContainer		*pDstCon,
	uint32			uDstSlot
)
{
	KCheck(pLogParam);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pSrcCon->GetItem(uSrcSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uItemTableIndex = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(IDT_ITEM == pItem->m_Type)
	{
		uItemTableIndex = pItem->GetItemTableIndex();

	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRet = MoveItem_i(pSrcCon, uSrcSlot, pDstCon, uDstSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRet >= 0)
	{
		if(IDT_ITEM == pItem->m_Type)
		{
			if(FALSE == IsBagCon2BagCon(pPlayer, pSrcCon, pDstCon))
			{
				if
				(
					FALSE == IsEquipCon2BagCon(pPlayer, pSrcCon, pDstCon)
				&&	FALSE == IsBagCon2EquipCon(pPlayer, pSrcCon, pDstCon)
				) pPlayer->OnEvent_ItemChanged(uItemTableIndex, ITEM_CHANGE_ADDITEM);
			}
		}

	}

	return nRet;
}

/*
 =======================================================================================================================
 移动操作
 =======================================================================================================================
 */
int32 ItemInterface::MoveItemToHumanBag
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pSrc,
	Player			*pDst,
	ItemContainer		*pSrcCon,
	uint32			uSrcSlot
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pSrc);
	KCheck(pDst);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pDst->GetBaseContain();
	int32		nConSlot = MoveItem_i(pSrcCon, uSrcSlot, pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nConSlot < 0)
	{
		pContainer = pDst->GetExtraBagContain(0);
		nConSlot = MoveItem_i(pSrcCon, uSrcSlot, pContainer);
		if(nConSlot < 0)
		{
			pContainer = pDst->GetExtraBagContain(1);
			nConSlot = MoveItem_i(pSrcCon, uSrcSlot, pContainer);
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBagSlot = pContainer->ConIndex2BagIndex(nConSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nBagSlot >= 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(nConSlot);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	uItemIndex = pItem->GetItemTableIndex();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSrc->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
		pDst->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ADDITEM);

		
	}

	return nBagSlot;
	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 移动操作
 =======================================================================================================================
 */
int32 ItemInterface::MoveItemToHumanEmptyPos
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pSrc,
	Player			*pDst,
	ItemContainer		*pSrcCon,
	uint32			uSrcSlot
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pLogParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pSrc);
	KCheck(pDst);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pDst->GetBaseContain();
	int32		uContainIndex = pContainer->GetFreeItemIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(uContainIndex == INVALID_INDEX)
	{
		pContainer = pDst->GetExtraBagContain(0);
		if(pContainer->IsValid())
		{
			uContainIndex = pContainer->GetFreeItemIndex();
			if(uContainIndex == INVALID_INDEX)
			{
				pContainer = pDst->GetExtraBagContain(1);
				if(pContainer->IsValid())
				{
					uContainIndex = pContainer->GetFreeItemIndex();
				}
			}
		}
		else
		{
			pContainer = pDst->GetExtraBagContain(1);
			if(pContainer->IsValid())
			{
				uContainIndex = pContainer->GetFreeItemIndex();
			}
		}
	}

	if(uContainIndex == INVALID_INDEX) return INVALID_INDEX;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nConSlot = MoveItem_i(pSrcCon, uSrcSlot, pContainer, uContainIndex);
	int32	nBagSlot = pContainer->ConIndex2BagIndex(nConSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nBagSlot >= 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(uContainIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	uItemIndex = pItem->GetItemTableIndex();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSrc->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
		pDst->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ADDITEM);

		
	}

	return nBagSlot;
	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 交换操作
 =======================================================================================================================
 */
int32 ItemInterface::ExchangeItem
(
	ItemLogRecordInfo	*pLogParam,
	Player			*pPlayer,
	Player			*pDestHuman,
	ItemContainer		*pSourContainer,
	int32			nSourIndex,
	ItemContainer		*pDestContainer,
	int32			nDestIndex
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pSourContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestContainer);
	KCheck(pSourContainer->IsValid());
	KCheck(pDestContainer->IsValid());
	KCheck(nSourIndex < pSourContainer->GetContainerSize());
	KCheck(nDestIndex < pDestContainer->GetContainerSize());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	ret = ExchangeItem(pSourContainer, nSourIndex, pDestContainer, nDestIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret >= 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pSourItem = pDestContainer->GetItem(nDestIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pSourItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	uSourItemIndex = pSourItem->GetItemTableIndex();
		Item	*pDestItem = pSourContainer->GetItem(nSourIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDestItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	uDestItemIndex = pDestItem->GetItemTableIndex();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if
		(
			IDT_ITEM == pSourItem->GetDataType()
		&&	IDT_ITEM == pDestItem->GetDataType()
		&&	pPlayer->GetGUID() != pDestHuman->GetGUID()
		)
		{
			

			pPlayer->OnEvent_ItemChanged(uSourItemIndex, ITEM_CHANGE_ERASEITEM);
			pPlayer->OnEvent_ItemChanged(uDestItemIndex, ITEM_CHANGE_ADDITEM);
			pDestHuman->OnEvent_ItemChanged(uDestItemIndex, ITEM_CHANGE_ERASEITEM);
			pDestHuman->OnEvent_ItemChanged(uSourItemIndex, ITEM_CHANGE_ADDITEM);
		}

		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 写日志操作
 =======================================================================================================================
 */
void ItemInterface::TryWriteIBCostLog(ItemLogRecordInfo	*pLogParam, Player *pPlayer, uchar uBindType)
{
__GUARD__
	KCheck(pLogParam);
	KCheck(pPlayer);
	
	if(uBindType & IEI_GBIND_INFO)
	{
		//除了交易、摆摊、买NPCShop外其他情况都记Log
		
	}

__UNGUARD__
}
/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
BOOL ItemInterface::EraseBagItemBySlot_i(Player *pPlayer, uint32 uSlot, Item *pReturnItem, uchar& uRetBindType, BOOL bCheckEquipLock, uint32 uCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uSlot < MAX_BAG_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	m_uBind = BIND_NONE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	if(pItem->IsLock()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32 uItemIndex = pItem->GetItemTableIndex();
	uRetBindType = pItem->GetItemBindType();
	BOOL bRet = EraseItem_i(pPlayer, pContainer, pContainer->BagIndex2ConIndex(uSlot), bCheckEquipLock, uCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		if(IDT_ITEM == pItem->m_Type)
		{
			pReturnItem = pItem;
			pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ERASEITEM);
		}

	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 移除操作
 =======================================================================================================================
 */
int32 ItemInterface::EraseBagItem_i(Player *pPlayer, ItemContainer *pContainer, 
									uint32 uItemIndex, int32 uCount, BOOL bCareIBLog/* = FALSE*/, uint32 OPType/* = 0*/)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uItemIndex != INVALID_ID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex > 0);
	KCheck(uCount > 0);
	KCheck(pPlayer);
	KCheck(pContainer);
	KCheck(pContainer->IsValid());

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = NULL;
	Item	*pReturnItem = NULL;
	int32 i;
	uint32 bTBind = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < pContainer->GetContainerSize() && uCount > 0; ++i)
	{
		pItem = pContainer->GetItem(i);
		KCheck(pItem != NULL);
		if(pItem->GetItemTableIndex() == uItemIndex)
		{
			if(pItem->IsLock())
			{
				continue;
			}

			if(pItem->IsEquipLocked())
			{
				continue;
			}

			if(pItem->GetMaxLayedNum() == 1)
			{
				uchar uRetBindType = BIND_NONE;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL bRet = EraseBagItemBySlot_i
					(
						pPlayer,
						pContainer->ConIndex2BagIndex(i),
						pReturnItem,
						uRetBindType
					);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				KCheck(bRet);
				--uCount;
				if(bTBind == 0)
				{
					bTBind = m_uBind;
				}
				else
				{
					m_uBind = BIND_NORMAL;
				}
			}
			else
			{
				do
				{
					if(pItem->IsNormalBound())
					{
						m_uBind = BIND_NORMAL;
					}

					uchar uBindType = pItem->GetItemBindType();
					DecItemLayedNum(pContainer, i, 1);
					--uCount;

				} while((!pItem->IsFree()) && uCount > 0);

				if(pItem->IsFree())
				{
				
				}
				else
				{
			
				}
			}
		}
	}

	return uCount;

	__UNGUARD__ return uCount;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
int32 ItemInterface::CreateItem_i(Item *pTemplateItem, ItemContainer *pDestContainer, int32 nDestIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDestContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestContainer->IsValid())
	{
		return FALSE;
	}

	if
	(
		pTemplateItem == NULL
	||	pDestContainer == NULL
	||	(nDestIndex < INVALID_INDEX || nDestIndex >= pDestContainer->GetContainerSize())
	)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pTemplateItem;
	Item	*pDestItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pSourItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		if(pSourItem->m_Type != IDT_PET)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32 nSourLayCount = pSourItem->GetLayedNum();
			int32 nRepIndex = pDestContainer->GetIndexByTypeAndBind
				(
					pSourItem->GetItemTableIndex(),
					pSourItem->GetLayedNum(),
					pSourItem->GetItemBindType()
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nRepIndex != INVALID_INDEX)
			{
				pDestItem = pDestContainer->GetItem(nRepIndex);
				if(!pDestItem->IsLock() && pDestItem->IsCanLay())
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					int32 nDestLayCount = pDestItem->GetLayedNum();
					int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(nSourLayCount + nDestLayCount <= nDestMaxLayCount)
					{
						SetItemLayedNum
						(
							pDestContainer,
							nRepIndex,
							nSourLayCount + nDestLayCount
						);
						return nRepIndex;
					}
				}
			}
		}

		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}
	}
	else
	{
		pDestItem = pDestContainer->GetItem(nDestIndex);
		KCheck(pDestItem);

		if(!pDestItem->IsFree())
		{
			return ITEMOE_DESTOPERATOR_HASITEM;
		}
	}

	switch(pSourItem->m_Type)
	{
	case IDT_ITEM:
		{
			/*~~~~~~~~~~~~~~~*/
			SItemGuid NewGUID;
			/*~~~~~~~~~~~~~~~*/

			if(!GenItemGUID(NewGUID))
			{
				return ITEMOE_CREATEGUID_FAIL;
			}

			pDestContainer->SetItem(nFinalDestIndex, pSourItem);
			SetItemGUID(pDestContainer, nFinalDestIndex, &NewGUID);
			pDestItem = pDestContainer->GetItem(nFinalDestIndex);
		}
		break;

	case IDT_PET:
		{
			/*~~~~~~~~~~~~~~~*/
		SHorseGuid NewGUID;
			/*~~~~~~~~~~~~~~~*/

			if(!GenItemGUID(NewGUID))
			{
				return ITEMOE_CREATEGUID_FAIL;
			}

			pDestContainer->SetItem(nFinalDestIndex, pSourItem);
			SetItemGUID(pDestContainer, nFinalDestIndex, &NewGUID);
		}
		break;

	default:
		{
			return ITEMOE_CREATEGUID_FAIL;
			KCheck(FALSE);
		}
	}

	return ITEMOE_SUCCESS;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateItem_i(uchar bBind, ItemContainer *pDestContainer, uint32 &uConIndex, _CREATEITEM_INIT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDestContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pInit);

	if(!pDestContainer->IsValid())
	{
		return FALSE;
	}

	if(pInit->m_nItemIndex == 0 || pInit->m_nItemIndex == INVALID_ID) return FALSE;

	if(!pDestContainer->IsCanUse())
	{
		return FALSE;
	}

	uConIndex = INVALID_INDEX;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 iEmptyBagIndex = pDestContainer->GetFreeItemIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iEmptyBagIndex != INVALID_INDEX)
	{
		/*~~~~~~~~~~~~~*/
		SItem createItem;
		/*~~~~~~~~~~~~~*/

		g_pItemMgr->CreateItem(createItem, pInit);
		if(createItem.IsNullType())
		{
			return FALSE;
		}

		createItem.SetItemBindType(bBind);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pDestItem = pDestContainer->GetItem(iEmptyBagIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDestItem);
		if(pDestItem->IsFree())
		{
			pDestContainer->SetItemValue(iEmptyBagIndex, &createItem);
			uConIndex = iEmptyBagIndex;
			return TRUE;
		}
		else
		{
			KCheck(FALSE);
		}
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateItemToContainer_i
(
	uint32 uItemIndex,
	uchar bBind,
	ItemContainer *pDestContainer,
	BOOL &bNewEmptyPos,
	uint32 &uConIndex,
	int32 nDestIndex
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDestContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != 0);
	KCheck(uItemIndex != INVALID_ID);

	if(!pDestContainer->IsValid())
	{
		return FALSE;
	}

	if(uItemIndex == 0 || uItemIndex == INVALID_ID) return FALSE;

	if(!pDestContainer->IsCanUse())
	{
		return FALSE;
	}

	uConIndex = INVALID_INDEX;
	bNewEmptyPos = FALSE;

	if(nDestIndex != INVALID_INDEX)
	{
		KCheck(nDestIndex < pDestContainer->GetContainerSize());

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pDestContainer->GetItem(nDestIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		if(pItem->IsFree())
		{
			/*~~~~~~~~~~~~~*/
			SItem createItem;
			/*~~~~~~~~~~~~~*/

			g_pItemMgr->CreateItem(uItemIndex, createItem);

			if(createItem.IsNullType())
			{
				return FALSE;
			}

			createItem.SetItemBindType(bBind);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Item	*pDestItem = pDestContainer->GetItem(nDestIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pDestItem->IsFree())
			{
				pDestContainer->SetItemValue(nDestIndex, &createItem);
				pDestContainer->Bind(nDestIndex, bBind);
				return TRUE;
			}
			else
			{
				KCheck(FALSE);
			}
		}

		if(pItem->GetItemTableIndex() != uItemIndex)
		{
			return FALSE;
		}

		if(pItem->GetItemBindType() != bBind)
		{
			return FALSE;
		}

		if(CheckItemRuler::CheckTypeRuler(IRL_TILE, uItemIndex))
		{
			if(pItem->IsLock())
			{
				return FALSE;
			}

			if(pItem->GetLayedNum() < pItem->GetMaxLayedNum())
			{
				uConIndex = nDestIndex;
				bNewEmptyPos = FALSE;
				return IncItemLayedNum(pDestContainer, nDestIndex);
			}

			return FALSE;
		}
	}

	if(CheckItemRuler::CheckTypeRuler(IRL_TILE, uItemIndex))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 iNoFullBagIndex = pDestContainer->GetNoFullItemIndexAndBind(uItemIndex, bBind);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iNoFullBagIndex != INVALID_INDEX)
		{
			uConIndex = iNoFullBagIndex;
			bNewEmptyPos = FALSE;
			return IncItemLayedNum(pDestContainer, iNoFullBagIndex);
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 iEmptyBagIndex = pDestContainer->GetFreeItemIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iEmptyBagIndex != INVALID_INDEX)
	{
		/*~~~~~~~~~~~~~*/
		SItem createItem;
		/*~~~~~~~~~~~~~*/

		g_pItemMgr->CreateItem(uItemIndex, createItem);

		if(createItem.IsNullType())
		{
			return FALSE;
		}

		createItem.SetItemBindType(bBind);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pDestItem = pDestContainer->GetItem(iEmptyBagIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDestItem);
		if(pDestItem->IsFree())
		{
			pDestContainer->SetItemValue(iEmptyBagIndex, &createItem);
			bNewEmptyPos = TRUE;
			uConIndex = iEmptyBagIndex;
			return TRUE;
		}
		else
		{
			KCheck(FALSE);
		}
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 创建操作
 =======================================================================================================================
 */
BOOL ItemInterface::CreateItemToBagByItemIndex_i
(
	Player	*pPlayer,
	uint32 uItemIndex,
	uint32 &uSlot,
	uchar bBind,
	BOOL bNotifyChangeItem
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != 0);
	KCheck(uItemIndex != INVALID_ID);

	if(uItemIndex == 0 || uItemIndex == INVALID_ID) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer;
	BOOL bNewPos;
	uint32 uContainerPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pContainer = pPlayer->GetBaseContain();
	KCheck(pContainer);

	uchar uFinalBind = bBind;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bPickBind = CheckItemRuler::CheckRuler(IRL_PICKBIND, GetItemRuler(uItemIndex));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if(bPickBind)
	{
		uFinalBind |= IEI_PBIND_INFO;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = CreateItemToContainer_i(uItemIndex, uFinalBind, pContainer, bNewPos, uContainerPos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bRet)
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pContainer = pPlayer->GetExtraBagContain(i);
			KCheck(pContainer);
			if(pContainer->IsValid())
			{
				if(pContainer->IsCanUse())
				{
					bRet = CreateItemToContainer_i
					(
						uItemIndex,
						uFinalBind,
						pContainer,
						bNewPos,
						uContainerPos
					);
				}
			}

			if(bRet)
			{
				break;
			}
		}
	}

	if(bRet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(uContainerPos);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		if(bNotifyChangeItem) pPlayer->OnEvent_ItemChanged(uItemIndex, ITEM_CHANGE_ADDITEM);
		uSlot = pContainer->ConIndex2BagIndex(uContainerPos);
	}
	else
	{
		uSlot = INVALID_INDEX;
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 使用物品
 =======================================================================================================================
 */
int32 ItemInterface::UseItem(Player	*pPlayer,ID_t nBagIndex,ObjID_t nTargetObj,const GLPos &posTarget, SHorseGuid const &guidTargetPet,ID_t nTargetItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__				KCheck(pPlayer);
	SpellTargetingAndDepletingParams	&rParams = pPlayer->GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == pPlayer->IsAlive() || FALSE == pPlayer->IsActiveObj())
	{
		rParams.SetErrCode(OR_DIE);
		return USEITEM_INVALID;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pBagItem = GetBagItem(pPlayer, nBagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pBagItem->IsFree())
	{
		return USEITEM_INVALID;
	}

	pPlayer->AddLogicCount();

	rParams.SetTargetBagSlot(nTargetItem);
	rParams.SetBagIndexOfDepletedItem(nBagIndex);
	rParams.SetDepletedItemGuid(pBagItem->GetGUID());
	rParams.SetItemIndexOfDepletedItem(pBagItem->GetItemTableIndex());
	rParams.SetActivatedScript(pBagItem->GetScriptID());
	rParams.SetActivatedSpell(pBagItem->GetSpellID());
	rParams.SetTargetObj(nTargetObj);

	rParams.SetTargetPosition(posTarget);
	if(pBagItem->IsBound())
	{
		rParams.SetItemBind();
	}

	pPlayer->BHV_UseSkill(pBagItem->GetSpellID(), nTargetObj, &posTarget, 0, 0, INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nRet = ActivateItem_i(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return USEITEM_SUCCESS;
	__UNGUARD__ return USEITEM_INVALID;
}

/*
 =======================================================================================================================
 使用装备
 =======================================================================================================================
 */
int32 ItemInterface::UseEquip(Player *pPlayer, int32 BagIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(BagIndex >= 0);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pUseItem = GetBagItem(pPlayer, BagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pUseItem);
	if(pUseItem->IsFree())
	{
		KCheck(0);
		return INVALID_INDEX;
	}

	if((pUseItem->GetReqJob() != PROFESSION_NONE) && (pUseItem->GetReqJob() != -1))
	{
		if(pUseItem->GetRequireLevel() > pPlayer->GetLevel())
		{
			return INVALID_INDEX;
		}
		else if(pUseItem->GetReqJob() != pPlayer->GetProfession())
		{
			return INVALID_INDEX;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	PLAYER_EQUIP Equip_Point = (PLAYER_EQUIP) pUseItem->GetEquipPoint();
	ItemContainer	*pEquipContainer = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pEquipContainer)
	{
		KCheck(0);
		return INVALID_INDEX;;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pEquipItem = pEquipContainer->GetItem((uint32) Equip_Point);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pEquipItem)
	{
		KCheck(0);
		return INVALID_INDEX;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bEquipStatus = (!pEquipItem->IsFree());
	ItemContainer	*pBagContainer = GetBagContainer(pPlayer, BagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bEquipStatus)
	{
		if(Equip_Point == HEQUIP_RING1)
		{
			pEquipItem = pEquipContainer->GetItem((uint32) HEQUIP_RING2);

			if(!pEquipItem)
			{
				KCheck(0);
				return INVALID_INDEX;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL b2EquipStatus = (pEquipItem->IsFree());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(b2EquipStatus)
			{
				MoveItem_i
				(
					pBagContainer,
					pBagContainer->BagIndex2ConIndex(BagIndex),
					pEquipContainer,
					(uint32) HEQUIP_RING2
				);

				Equip_Point = HEQUIP_RING2;
			}
			else
			{
				ExchangeItem
				(
					pBagContainer,
					pBagContainer->BagIndex2ConIndex(BagIndex),
					pEquipContainer,
					(uint32) Equip_Point
				);
			}
		}
		else if(Equip_Point == HEQUIP_ADORN1)
		{
			pEquipItem = pEquipContainer->GetItem((uint32) HEQUIP_ADORN2);

			if(!pEquipItem)
			{
				KCheck(0);
				return INVALID_INDEX;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BOOL b2EquipStatus = (pEquipItem->IsFree());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(b2EquipStatus)
			{
				MoveItem_i
				(
					pBagContainer,
					pBagContainer->BagIndex2ConIndex(BagIndex),
					pEquipContainer,
					(uint32) HEQUIP_ADORN2
				);

				Equip_Point = HEQUIP_ADORN2;
			}
			else
			{
				ExchangeItem
				(
					pBagContainer,
					pBagContainer->BagIndex2ConIndex(BagIndex),
					pEquipContainer,
					(uint32) Equip_Point
				);
			}
		}
		else
		{
			ExchangeItem
			(
				pBagContainer,
				pBagContainer->BagIndex2ConIndex(BagIndex),
				pEquipContainer,
				(uint32) Equip_Point
			);
		}
	}
	else
	{
		MoveItem_i
		(
			pBagContainer,
			pBagContainer->BagIndex2ConIndex(BagIndex),
			pEquipContainer,
			(uint32) Equip_Point
		);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pEquip = pEquipContainer->GetItem((uint32) Equip_Point);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pEquip && pEquip->IsCanEquipBind())
	{
		SetItemBind(pEquipContainer, (uint32) Equip_Point);
	}

	pPlayer->SetEquipVer(pPlayer->GetEquipVer() + 1);

	return Equip_Point;

	__UNGUARD__ return INVALID_INDEX;
}

/*
 =======================================================================================================================
 更新装备伤害点
 =======================================================================================================================
 */
void ItemInterface::UpdataEquipDamagePoint(Player *pPlayer, int32 nType)
{
	
}

/*
 =======================================================================================================================
 锁定装备
 =======================================================================================================================
 */
BOOL ItemInterface::LockEquip(Player *pPlayer, uint32 BagIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(BagIndex >= 0);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, BagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = GetBagItem(pPlayer, BagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	if(ITEM_LOCK == pItem->m_pItem->GetEquipData()->m_byLock)
	{
		return FALSE;
	}

	LuaSystem * pLuaSystem;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);
	pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nRet = pLuaSystem->RunScriptFunction
		(
			pMap->MapID(),
			SCENE_SCRIPTID,
			DEF_MAP_CAN_LOCKEQUIP,
			pMap->MapID(),
			pPlayer->GetID(),
			pItem->GetItemTableIndex()
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == nRet)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = pContainer->LockEquip(pContainer->BagIndex2ConIndex(BagIndex));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 解锁装备
 =======================================================================================================================
 */
BOOL ItemInterface::UnLockEquip(Player *pPlayer, uint32 BagIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(BagIndex >= 0);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, BagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = GetBagItem(pPlayer, BagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	if(ITEM_UNLOCKING == pItem->m_pItem->GetEquipData()->m_byLock)
	{
		return FALSE;
	}

	if(ITEM_LOCK != pItem->m_pItem->GetEquipData()->m_byLock)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = pContainer->UnLockEquip(pContainer->BagIndex2ConIndex(BagIndex));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 更新装备过期属性
 =======================================================================================================================
 */
void ItemInterface::UpdateEquipTermEnd(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	char szMailContent[MAX_MAIL_CONTEX] = { 0 };
	ItemContainer *pContainer = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pContainer)
	{
		KCheckEx(FALSE, "[ItemInterface::UpdateEquipTermEnd]: NULL EquipContainer pointer found!");
	}


	pContainer = pPlayer->GetBaseContain();
	if(NULL == pContainer)
	{
		KCheckEx(FALSE, "[ItemInterface::UpdateEquipTermEnd]: NULL BaseContainer pointer found!");
	}

	pContainer = pPlayer->GetExtraContain();
	if(NULL == pContainer)
	{
		KCheckEx(FALSE, "[ItemInterface::UpdateEquipTermEnd]: NULL ExtraContainer pointer found!");
	}


	for (int32 i = 0; i < MAX_EXTRA_BAG_NUM;++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(NULL == pContainer)
		{
			KCheckEx(FALSE, "[ItemInterface::UpdateEquipTermEnd]: NULL ExtraBagContainer pointer found!");
		}

	}

	pContainer = pPlayer->GetBankContain();
	if(NULL == pContainer)
	{
		KCheckEx(FALSE, "[ItemInterface::UpdateEquipTermEnd]: NULL BankContainer pointer found!");
	}


	__UNGUARD__
}

/*
 =======================================================================================================================
 更新装备过期属性
 =======================================================================================================================
 */
BOOL ItemInterface::UpdateItemContainerTermEnd
(
	Player		*pPlayer,
	ItemContainer	*pContainer,
	BOOL bNotifyClient,
	uchar byPosType
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	if(!pContainer->IsValid()) return FALSE;

	/*~~~~~~~~~~~~~~~~~*/
	BOOL bRet = FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 size = pContainer->GetContainerSize();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < size; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pEquipItem = pContainer->GetItem(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pEquipItem)
		{
			KCheckEx(FALSE, "[ItemInterface::UpdateItemContainerTermEnd]: NULL EquipItem pointer found!");
			continue;
		}

		if(TRUE == pEquipItem->IsFree())
		{
			continue;
		}

		if(pEquipItem->GetItemClass() != ICLASS_EQUIP) continue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32 uTermEndTime = pEquipItem->GetTermTime();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(uTermEndTime == 1 || uTermEndTime == 0 || uTermEndTime == 2) continue;
		if(GET_TIME().GetCTime() <= uTermEndTime) continue;

		pEquipItem->SetTermTime(1);
		if(pEquipItem->GetEquipPoint() == EQUIP_SUIT)
		{
			if(pContainer->GetContainerType() == ICT_EQUIP_CONTAINER)
			{

			}
		}

		bRet = TRUE;

		if(bNotifyClient)
		{
			

			
		}
	}



	return bRet;

	__UNGUARD__ return FALSE;
}

void ItemInterface::UpdateItemUnLockTime(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	uint32 BagIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(BagIndex = DB_BAG_POS_START; BagIndex < DB_BANK_POS_END; ++BagIndex)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SItem	*pItem = const_cast<SItem *>(GetItem(pPlayer, BagIndex));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		if
		(
			ITEM_UNLOCKING == pItem->GetEquipData()->m_byLock
		&&	GET_TIME().GetCTime() >= pItem->GetEquipData()->m_UnLockTime
		)
		{
			pItem->GetEquipData()->m_byLock = ITEM_UNLOCK;

			if(BagIndex >= DB_EQUIP_POS_START && BagIndex < DB_EQUIP_POS_END)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~*/
				uint16 RetPart = 0;
				
			}
			else if(BagIndex >= DB_BANK_POS_START && BagIndex < DB_BANK_POS_END)
			{
				
			}
			else if(BagIndex >= DB_BAG_POS_START && BagIndex < DB_BAG_POS_END)
			{
				
			}
		}
	}

	__UNGUARD__
}

//装备打孔
int32			ItemInterface::AddHole(Player* pPlayer, uint32 BagIndex)
{
	return 0;
}

//装备绑定/铭刻
int32			ItemInterface::EquipBind(Player* pPlayer, uint32 BagIndex)
{
	return 0;
}

//装备麻将牌
int32			ItemInterface::EquipChangePai(Player* pPlayer, uint32 BagIndex, uint32 GemBagIndex)
{
	return 0;
}

//装备打造（类似于做装备）
int32			ItemInterface::EquipRemould(Player* pPlayer, uint32 BagIndex, uint32 nMaterialScore)
{
	return 0;
}

//装备换牌
int32			ItemInterface::EquipChangePai(Player* pPlayer, uint32 BagIndex1, uint32 BagIndex2, uint32 GemBagIndex)
{
	return 0;
}

//装备升星
int32			ItemInterface::EquipLevelup(Player* pPlayer, uint32	BagIndex, EQUIP_LEVEL_TYPE nType, uint32 nGemID, uint32 nGemCount)
{
	return 0;
}


//装备镶嵌
int32			ItemInterface::UseGem(Player* pPlayer, uint32 BagIndex, uint32 GemBagIndex, uint32 GemHolePos)
{
	return 0;
}



//装备颜色改变
EQUIP_WANFA_RESULT	ItemInterface::Equip_ColorChange(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//紫装打造
EQUIP_WANFA_RESULT	ItemInterface::Equip_PurpleRework(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//紫装备属性随机
void			ItemInterface::Equip_PurpleAttrRand(SItem& item) const
{
	
}

//紫装备随机率
uint32			ItemInterface::Equip_PurpleRandIndex() const
{
	return EQUIP_WANFA_SUCC;
}

//紫装备属性刷新
void			ItemInterface::Equip_PurpleAttrRefresh(SItem& item) const
{

}

//取得紫装备属性值
int32			ItemInterface::Equip_PurpleAttrValue(const SItem& item, uint32 index) const
{
	return EQUIP_WANFA_SUCC;
}

//宝石加工
EQUIP_WANFA_RESULT	ItemInterface::GemRework(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//宝石合成
EQUIP_WANFA_RESULT	ItemInterface::GemSynthesize(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//宝石卸载
EQUIP_WANFA_RESULT	ItemInterface::GemUninst(Player* pPlayer, uint32 BagIndex, uchar HolePos)
{
	return EQUIP_WANFA_SUCC;
}

//装备拷贝
EQUIP_WANFA_RESULT	ItemInterface::EquipCopy(Player* pPlayer, uint32 srcBagIndex, uint32	tarBagIndex, const SItemGuid& targGUID, uchar type)
{
	return EQUIP_WANFA_SUCC;
}

//装备回收
EQUIP_WANFA_RESULT ItemInterface::EquipRecall(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//多彩宝石回收
EQUIP_WANFA_RESULT ItemInterface::ItemRecall(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//装备蓝属性吸收
EQUIP_WANFA_RESULT ItemInterface::EquipBlueIn(Player* pPlayer, uint32 equipIndex, uint32 itemIndex, const SItemGuid& itemGUID)
{
	return EQUIP_WANFA_SUCC;
}

//装备蓝属性附加
EQUIP_WANFA_RESULT ItemInterface::EquipBlueAdd(Player* pPlayer, uint32	equipIndex, uint32 itemIndex, const SItemGuid& itemGUID)
{
	return EQUIP_WANFA_SUCC;
}

//物品蓝属性合成
EQUIP_WANFA_RESULT ItemInterface::ItemBlueSyn(Player* pPlayer, const uint32 itemIndex1, const uint32 itemIndex2)
{
	return EQUIP_WANFA_SUCC;
}


//装备转化
EQUIP_WANFA_RESULT			ItemInterface::EquipSwitch(Player* pPlayer, uint32 BagIndex)
{
	return EQUIP_WANFA_SUCC;
}


//装备蓝属性全部随机
void			ItemInterface::Equip_BlueAttrRand(SItem& item)
{
	
}

//从表中恢复装备的基础蓝属性
void			ItemInterface::ResetEquipBlueAttFromTB(Player* pPlayer, uint32 BagIndex)
{
	
}

//根据属性ID重置属性值
void			ItemInterface::SetEquipExtAttrByAttrId(Player* pPlayer, uint32 BagIndex, uchar attrType, int16 attrVal)
{
	
}

//更换形象
int32 ItemInterface::CharChangeAppearance(Player* pPlayer, uint32 BagIndex, int32 nPortraitID, uchar byFaceModel, uchar byHairModel)
{
	return EQUIP_WANFA_SUCC;
}

//橙装打造蓝属性
EQUIP_WANFA_RESULT ItemInterface::NewEquipProduce(Player* pPlayer,
	const uint32 nEquipItemIndex,
	const uint32 nAtlasBagIndex,
	const uint32 nAdditiveBagIndex
)
{
	return EQUIP_WANFA_SUCC;
}

//橙装蓝属性随机
void	ItemInterface::Equip_NewEquipBlueAttrRand(SItem& item, const NEW_EQUIP_PRODUCE_TB* pProduceTab, const BOOL bHasAdditive)
{
	
}

//星座铭刻
EQUIP_WANFA_RESULT	ItemInterface::EquipConstBind(Player* pPlayer, uint32 nEquipBagIndex, uint32 nItemBagIndex)
{
	return EQUIP_WANFA_SUCC;
}

//荣誉铭刻
EQUIP_WANFA_RESULT	ItemInterface::EquipHonorBind(Player* pPlayer, uint32 BagIndex, uint32 nGemID)
{
	return EQUIP_WANFA_SUCC;
}

BOOL ItemInterface::ActivateItem_i(Player *pPlayer)
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::CalcBagSpace(Player *pPlayer) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPlayer)
	{
		KCheck(FALSE);
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nSpace = 0;
	ItemContainer	*pContainer = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pContainer = pPlayer->GetBaseContain();
	KCheck(pContainer);

	nSpace += pContainer->CalcItemFreeSlot();
	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		KCheck(pContainer);
		if(pContainer->IsValid())
		{
			if(pContainer->IsCanUse())
			{
				nSpace += pContainer->CalcItemFreeSlot();
			}
		}
	}

	return nSpace;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::CalcInventoryItemCount(Player *pPlayer, uint32 uItemIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uItemIndex > 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 count = 0;
	Item		*pItem = NULL;
	ItemContainer	*pContainer = pPlayer->GetBaseContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return 0;
	}

	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);

		if(!pItem)
		{
			KCheck(pItem);
			continue;
		}

		if(pItem->IsLock()) continue;
		if(pItem->IsEquipLocked()) continue;

		if(pItem->GetItemTableIndex() == uItemIndex)
		{
			count += pItem->GetLayedNum();
		}
	}

	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(pContainer->IsValid())
		{
			for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
			{
				pItem = pContainer->GetItem(i);

				if(!pItem)
				{
					KCheck(pItem);
					continue;
				}

				if(pItem->IsLock()) continue;

				if(pItem->GetItemTableIndex() == uItemIndex)
				{
					count += pItem->GetLayedNum();
				}
			}
		}
	}

	return count;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::CalcEquipItemCount(Player *pPlayer, uint32 uItemIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != 0);
	KCheck(uItemIndex != INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pEquipContainer = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pEquipContainer);

	if(!pEquipContainer)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~*/
	int32 nCount = 0;
	/*~~~~~~~~~~~~~*/

	for(int32 i = 0; i < HEQUIP_NUMBER; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pEquipItem = pEquipContainer->GetItem(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!pEquipItem) continue;

		if(pEquipItem->GetItemTableIndex() == uItemIndex)
		{
			if(pEquipItem->GetLayedNum() > 0)
			{
				nCount += pEquipItem->GetLayedNum();
			}
		}
	}

	return nCount;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::GetItemLockStatus(Player *pPlayer, uint32 uItemIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex < MAX_BAG_SIZE);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = GetBagItem(pPlayer, uItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	if(pItem->GetItemClass() == ICLASS_EQUIP)
	{
		return pItem->m_pItem->GetEquipData()->m_byLock;
	}

	__UNGUARD__ return ITEM_UNLOCK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::CanBagReceiveItemList(Player *pPlayer, SItemList &List) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iBaseSize = CalcBagSpace(pPlayer);
	int32 iSpaceCount = 0;
	int32 NewSpace = 0;
	ItemContainer	*pContainer;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 iListIndex = 0; iListIndex < List.m_ListCount; iListIndex++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32 uItemIndex = List.m_ListType[iListIndex].ToSerial();
		uint32 uCount = List.m_TypeCount[iListIndex];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pContainer = pPlayer->GetBaseContain();
		KCheck(pContainer);

		/*~~~~~~~~~~~~~~~~*/
		uchar bBindType = 0;
		/*~~~~~~~~~~~~~~~~*/

		if(CheckItemRuler::CheckTypeRuler(IRL_PICKBIND, uItemIndex))
		{
			bBindType = BIND_NORMAL;
		}
		else
		{
			bBindType = (uchar) List.m_bBind[iListIndex];
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 nSpace = pContainer->CalcItemFreeSlot();
		int32 nRemainCount = CalcBagItemSpace_i(pPlayer, pContainer, uItemIndex, uCount, NewSpace, bBindType);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		iBaseSize -= nSpace - NewSpace;

		if(iBaseSize < 0)
		{
			return FALSE;
		}

		if(nRemainCount > 0)
		{
			/*~~~~~~~~~~~~~*/
			int32 nSpace = 0;
			/*~~~~~~~~~~~~~*/

			for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
			{
				pContainer = pPlayer->GetExtraBagContain(i);
				KCheck(pContainer);
				if(pContainer->IsValid())
				{
					if(pContainer->IsCanUse())
					{
						nSpace = pContainer->CalcItemFreeSlot();
						nRemainCount = CalcBagItemSpace_i
							(
								pPlayer,
								pContainer,
								uItemIndex,
								nRemainCount,
								NewSpace,
								bBindType
							);

						iBaseSize -= nSpace - NewSpace;

						if(iBaseSize < 0)
						{
							return FALSE;
						}
					}
				}

				if(nRemainCount <= 0)
				{
					break;
				}
			}
		}

		if(nRemainCount > 0)
		{
			return FALSE;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::CanBagEraseItemList(Player *pPlayer, SItemList &List) const
{
	__GUARD__ for(int32 iListIndex = 0; iListIndex < List.m_ListCount; iListIndex++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32 nItemID = List.m_ListType[iListIndex].ToSerial();
		int32 nItemCount = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nItemCount += CalcInventoryItemCount(pPlayer, nItemID);

		if(nItemCount < List.m_TypeCount[iListIndex]) return FALSE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::CanReceiveExchangeItemList(Player *pPlayer, STradeItemList &List) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemContainer *pBaseContain = pPlayer->GetBaseContain();
	ItemContainer		*pPetContain = pPlayer->GetPetContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pBaseContain);
	KCheck(pPetContain);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pMyContainer = NULL;
	int32 iBaseSize = pBaseContain->CalcExchangeItemSlot();
	int32 iLevel = pPlayer->GetLevel();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iLevel -= g_Config.m_ConfigInfo.m_CaptureHorseMinPlayerLevel;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 iPetSize = (1 + iLevel / g_Config.m_ConfigInfo.m_TakeHorseNumIncLevelStep) - pPlayer->GetHorseCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iPetSize < 0)
	{
		iPetSize = 0;
	}

	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pMyContainer = pPlayer->GetExtraBagContain(i);
		if(pMyContainer->IsValid())
		{
			if(!pMyContainer->IsCanUse()) continue;
			iBaseSize += pMyContainer->CalcExchangeItemSlot();
		}
	}

	for(int32 iListIndex = 0; iListIndex < List.m_ListCount; iListIndex++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = List.m_ListItem[iListIndex];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);
		if(pItem->GetDataType() == IDT_PET)
		{
			iPetSize -= 1;
			if(iPetSize < 0) return FALSE;
		}
		else if(pItem->GetDataType() == IDT_ITEM)
		{
			switch(pItem->GetItemClass())
			{
			case ICLASS_TASKITEM:
			case ICLASS_EQUIP:
			case ICLASS_COMITEM:
			case ICLASS_GEM:
			case ICLASS_MATERIAL:
			case ICLASS_EXTRABAG:
				{
					iBaseSize -= 1;
					if(iBaseSize < 0) return FALSE;
				}
				break;

			default:
				KCheck(FALSE);
				return FALSE;
				break;
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
BOOL ItemInterface::IsVisualPart(Player *pPlayer, PLAYER_EQUIP EquipPoint) const
{
	KCheck(pPlayer);
	switch(EquipPoint)
	{
	case HEQUIP_MAINHAND:
	case HEQUIP_ASSIHAND:
	case HEQUIP_HEAD:
	case HEQUIP_SHOULDER:
	case HEQUIP_BACK:
	case HEQUIP_HAND:
	case HEQUIP_FEET:
	case HEQUIP_SUIT:
		{
			return TRUE;
		}

	default:
		return FALSE;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::VerifyItem(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__				KCheck(pPlayer);
	SpellTargetingAndDepletingParams	&rParams = pPlayer->GetTargetingAndDepletingParams();
	int32 nBagIndex = rParams.GetBagIndexOfDepletedItem();
	Item					*pBagItem = GetBagItem(pPlayer, nBagIndex);
	int32 nItemTableIndex = rParams.GetItemIndexOfDepletedItem();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pBagItem->IsFree() || pBagItem->GetItemTableIndex() != nItemTableIndex)
	{
		if(0 < CalcInventoryItemCount(pPlayer, nItemTableIndex))
		{
			nBagIndex = GetBagItemPosByType(pPlayer, nItemTableIndex);
			if(0 <= nBagIndex)
			{
				rParams.SetBagIndexOfDepletedItem(nBagIndex);
				pBagItem = GetBagItem(pPlayer, nBagIndex);
			}
		}
	}

	if(FALSE == pBagItem->IsFree())
	{
		if(rParams.GetItemIndexOfDepletedItem() == pBagItem->GetItemTableIndex())
		{
			if(rParams.GetActivatedScript() == pBagItem->GetScriptID())
			{
				if(rParams.GetActivatedSpell() == pBagItem->GetSpellID())
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::IsCarrayItem(Player *pPlayer, uint32 ItemType, uint32 ItemCount) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	uint32 count = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	count = CalcEquipItemCount(pPlayer, ItemType);

	count += CalcInventoryItemCount(pPlayer, ItemType);

	return count >= ItemCount;

	__UNGUARD__ return 0;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemInterface::IsHaveEquip(Player *pPlayer, const SItemGuid& ItemGuid) const
{
__GUARD__
	KCheck(pPlayer);

	ItemContainer* pItemContainer = pPlayer->GetEquipContain();
	KCheck(pItemContainer);

	for(int32 i = 0; i < HEQUIP_NUMBER; ++i)
	{
		Item	*pEquip = pItemContainer->GetItem(i);
		KCheck(pEquip);

		if(!pEquip->IsFree())
		{
			if(pEquip->GetGUID() == ItemGuid)
			{
				return TRUE;
			}
		}
	}
	return FALSE;

__UNGUARD__
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::IsHaveItem(Player *pPlayer, uint32 itemIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(itemIndex != 0);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetBaseContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);
	if(pContainer->GetIndexByType(itemIndex) != INVALID_INDEX)
	{
		return TRUE;
	}

	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		KCheck(pContainer);
		if(pContainer->IsValid())
		{
			if(pContainer->GetIndexByType(itemIndex) != INVALID_INDEX)
			{
				return TRUE;
			}
		}
	}

	pContainer = pPlayer->GetEquipContain();
	KCheck(pContainer);
	if(pContainer->GetIndexByType(itemIndex) != INVALID_INDEX)
	{
		return TRUE;
	}

	pContainer = pPlayer->GetBankContain();
	KCheck(pContainer);
	if(pContainer->GetIndexByType(itemIndex) != INVALID_INDEX)
	{
		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::HaveEnoughBagItemSpace
(
	Player	*pPlayer,
	uint32 uItemIndex,
	int32 Number,
	int32 &NewSpace,
	uchar bBindType
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(Number > 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pContainer = pPlayer->GetBaseContain();
	KCheck(pContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nSpace = 0;
	int32 nRemainCount = CalcBagItemSpace_i(pPlayer, pContainer, uItemIndex, Number, NewSpace, bBindType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRemainCount > 0)
	{
		/*~~~~~~~~~~~~~*/
		int32 nSpace = 0;
		/*~~~~~~~~~~~~~*/

		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pContainer = pPlayer->GetExtraBagContain(i);
			KCheck(pContainer);
			if(pContainer->IsValid())
			{
				if(pContainer->IsCanUse())
				{
					nRemainCount = CalcBagItemSpace_i
						(
							pPlayer,
							pContainer,
							uItemIndex,
							nRemainCount,
							nSpace,
							bBindType
						);
					NewSpace += nSpace;
				}
			}

			if(nRemainCount <= 0)
			{
				break;
			}
		}
	}

	if(nRemainCount <= 0)
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::CalcBagItemSpace_i
(
	Player		*pPlayer,
	ItemContainer	*pContainer,
	uint32 uItemIndex,
	int32 Number,
	int32 &NewSpace,
	uchar bBindType
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(Number > 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != INVALID_ID);
	KCheck(pContainer);
	KCheck(pContainer->IsValid());

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 Count = 0;
	int32 PileCount = 0;
	int32 Tile = 0;
	SItemType type = Serial2ItemType(uItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Tile = GetMaxItemTile(type);
	KCheck(Tile > 0);

	for(uint32 i = 0; i < (uint32) pContainer->GetContainerSize(); ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		if(Tile == 1)
		{
			if(pItem->IsFree() == TRUE)
			{
				++Count;
			}
		}
		else
		{
			if(pItem->IsFree() == TRUE)
			{
				++Count;
			}
			else if((pItem->GetItemTableIndex() == uItemIndex) && (pItem->IsCanLay()) && (!pItem->IsLock()))
			{
				if(pItem->GetItemBindType() == bBindType)
				{
					PileCount += Tile - pItem->GetLayedNum();
				}
			}
		}
	}

	if(Count * Tile + PileCount >= Number)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 sum = Number - PileCount;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(sum <= 0)
			NewSpace = Count;
		else
			NewSpace = Count - sum / Tile - ((sum % Tile) ? 1 : 0);
	}
	else
		NewSpace = 0;
	return Number - Count * Tile - PileCount;

	__UNGUARD__ return Number;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInterface::LockItem(ItemContainer *pContainer, int32 nIndex)
{
	__GUARD__ if(pContainer == NULL || nIndex < 0 || nIndex >= pContainer->GetContainerSize())
	{
		KCheckEx(FALSE, "ItemInterface::LockItem");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	pItem->Lock();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInterface::UnlockItem(ItemContainer *pContainer, int32 nIndex)
{
	__GUARD__ if(pContainer == NULL || nIndex < 0 || nIndex >= pContainer->GetContainerSize())
	{
		KCheckEx(FALSE, "ItemInterface::UnlockItem");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	pItem->Unlock();
	pItem->SetInExchange(FALSE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::ExchangeEquipItem(ItemContainer *pSourContainer, int32 nSourIndex, int32 nDestIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pSourContainer->GetContainerType() == ICT_EQUIP_CONTAINER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nSourIndex != HEQUIP_RING1)
	{
		KCheck(nSourIndex == HEQUIP_ADORN1);
		KCheck(nDestIndex == HEQUIP_ADORN2);
	}

	if(nSourIndex != HEQUIP_ADORN1)
	{
		KCheck(nSourIndex == HEQUIP_RING1);
		KCheck(nDestIndex == HEQUIP_RING2);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = NULL;
	Item	*pDestItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	pDestItem = pSourContainer->GetItem(nDestIndex);
	if(pDestItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_DESTOPERATOR_EMPTY;
	}
	else if(pDestItem->IsLock())
	{
		return ITEMOE_DESTOPERATOR_LOCK;
	}

	pSourItem = pSourContainer->GetItem(nSourIndex);
	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SItem TmpITEM;
	const CItemInit Init(&TmpITEM);
	Item tempItem;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tempItem.Init(&Init);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SItem TmpITEM1;
	const CItemInit Init1(&TmpITEM1);
	Item tempItem1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tempItem1.Init(&Init1);
	TmpITEM1 = *pSourItem->m_pItem;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SItem TmpITEM2;
	const CItemInit Init2(&TmpITEM2);
	Item tempItem2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tempItem2.Init(&Init2);
	TmpITEM2 = *pDestItem->m_pItem;

	pSourContainer->SetItem(nSourIndex, &tempItem);
	pSourContainer->SetItem(nDestIndex, &tempItem);

	pSourContainer->SetItem(nSourIndex, &tempItem2);
	pSourContainer->SetItem(nDestIndex, &tempItem1);

	return ITEMOE_SUCCESS;
	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::SplitItem
(
	ItemContainer	*pSourContainer,
	uchar uSourIndex,
	uchar uCount,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	__GUARD__ if
		(
			pSourContainer == NULL
		||	(uSourIndex < 0 || uSourIndex >= pSourContainer->GetContainerSize())
		||	pDestContainer == NULL
		||	(nDestIndex < INVALID_INDEX)
		)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pSourContainer->GetItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->GetLayedNum() <= uCount || uCount == 0)
	{
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}
	}

	if(CreateItem_i(pSourItem, pDestContainer, nFinalDestIndex) != 0)
	{
		return ITEMOE_UNKNOW;
	}

	SetItemLayedNum(pDestContainer, nFinalDestIndex, uCount);
	SetItemLayedNum(pSourContainer, uSourIndex, pSourItem->GetLayedNum() - uCount);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDstItem = pDestContainer->GetItem(nFinalDestIndex);
	Item	*pSrcItem = pSourContainer->GetItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return ITEMOE_SUCCESS;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SplitItem
(
	Player		*pPlayer,
	ItemContainer	*pSourContainer,
	uchar uSourIndex,
	uchar uCount,
	ItemContainer *pDestContainer,
	int32 nDestIndex,
	int32 opType
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pSourContainer);
	KCheck(pDestContainer);
	KCheck(pSourContainer->IsValid());
	KCheck(uSourIndex < pSourContainer->GetContainerSize());

	if(!pDestContainer->IsValid())
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(!pSourContainer->IsCanUse()) return FALSE;
	if(!pDestContainer->IsCanUse()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourceItem = pSourContainer->GetItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pSourceItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pSourceItem->IsFree())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pOldItem = NULL;
	BOOL bOldEmpty = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(nDestIndex != INVALID_INDEX)
	{
		pOldItem = pDestContainer->GetItem(nDestIndex);
		KCheck(pOldItem);
		if(!pOldItem->IsFree())
		{
			bOldEmpty = FALSE;
		}
	}

	if(SplitItem(pSourContainer, uSourIndex, uCount, pDestContainer, nDestIndex) == ITEMOE_SUCCESS)
	{
		pSourceItem = pSourContainer->GetItem(uSourIndex);
		KCheck(pSourceItem);

		

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pDestItem = pDestContainer->GetItem(nDestIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(bOldEmpty)
		{
			
		}
		else
		{
			
		}

		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::SplitItemToEmptyPos
(
	Player		*pPlayer,
	ItemContainer	*pSourContainer,
	uchar uSourIndex,
	uchar uCount,
	Player *pDestHuman
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestHuman);
	KCheck(pPlayer->GetMap());
	KCheck(pDestHuman->GetMap());
	KCheck(pPlayer->GetMap()->MapID() == pDestHuman->GetMap()->MapID());
	KCheck(pSourContainer);
	KCheck(pSourContainer->IsValid());
	KCheck(uSourIndex < pSourContainer->GetContainerSize());

	if(!pSourContainer->IsCanUse()) return INVALID_INDEX;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourceItem = pSourContainer->GetItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pSourceItem)
	{
		KCheck(FALSE);
		return INVALID_INDEX;
	}

	if(pSourceItem->IsFree())
	{
		return INVALID_INDEX;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pDestHuman->GetBaseContain();
	int32 nDestIndex = pContainer->GetFreeItemIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDestIndex == INVALID_INDEX)
	{
		pContainer = pDestHuman->GetExtraBagContain(0);
		if(pContainer->IsValid())
		{
			nDestIndex = pContainer->GetFreeItemIndex();
			if(nDestIndex == INVALID_INDEX)
			{
				pContainer = pDestHuman->GetExtraBagContain(1);
				if(pContainer->IsValid())
				{
					nDestIndex = pContainer->GetFreeItemIndex();
				}
			}
		}
		else
		{
			pContainer = pDestHuman->GetExtraBagContain(1);
			if(pContainer->IsValid())
			{
				nDestIndex = pContainer->GetFreeItemIndex();
			}
		}
	}

	if(nDestIndex == INVALID_INDEX)
	{
		return INVALID_INDEX;
	}

	KCheck(pContainer);
	if(SplitItem(pSourContainer, uSourIndex, uCount, pContainer, nDestIndex) == ITEMOE_SUCCESS)
	{
		pSourceItem = pSourContainer->GetItem(uSourIndex);
		KCheck(pSourceItem);

		

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pDestItem = pContainer->GetItem(nDestIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDestItem);

		

		if(IDT_ITEM == pDestItem->GetDataType())
		{
			pPlayer->OnEvent_ItemChanged(pDestItem->GetItemTableIndex(), ITEM_CHANGE_ERASEITEM);
			pDestHuman->OnEvent_ItemChanged(pDestItem->GetItemTableIndex(), ITEM_CHANGE_ERASEITEM);
		}

		return pContainer->ConIndex2BagIndex(nDestIndex);
	}

	__UNGUARD__ return INVALID_INDEX;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::EraseItem_i(Player *pPlayer, ItemContainer *pDestContainer, uchar uIndex, BOOL bCheckEquipLock, uint32 uCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pDestContainer == NULL || (uIndex < 0 || uIndex >= pDestContainer->GetContainerSize()))
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pDestContainer->GetItem(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pDestItem == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}
	else if(pDestItem->IsFree())
	{
		return FALSE;
	}

	if(IDT_ITEM == pDestItem->GetDataType()) 
	{
		if ( !pDestItem->IsGoldBound() )
			m_uBind = pDestItem->GetItemBindType();
	}

	if(pDestItem->IsLock())
	{
		return FALSE;
	}

	if(IDT_ITEM == pDestItem->GetDataType() && TRUE == bCheckEquipLock)
	{
		if(ITEM_LOCK == pDestItem->m_pItem->GetEquipData()->m_byLock)
		{
			return FALSE;
		}
		else if(ITEM_UNLOCKING == pDestItem->m_pItem->GetEquipData()->m_byLock)
		{
			return FALSE;
		}
	}

	if (0 == uCount)
	{
		return pDestContainer->EraseItem(uIndex);
	}
	else
	{
		do
		{
			DecItemLayedNum(pDestContainer, uIndex, 1);
			--uCount;
		} while((!pDestItem->IsFree()) && uCount > 0);
		
		if(pDestItem->IsFree())
		{
			
		}
		else
		{
			
		}
		
		return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::MoveItem_i(ItemContainer *pDestContainer, SItem *pSourItem, int32 nDestIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDestContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestContainer->IsValid())
	{
		return ITEMOE_UNKNOW;
	}

	if((nDestIndex < INVALID_INDEX) || (nDestIndex >= pDestContainer->GetContainerSize()))
	{
		return ITEMOE_UNKNOW;
	}

	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}
	else if(pSourItem->IsNullType())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bPickBind = CheckItemRuler::CheckRuler(IRL_PICKBIND, GetItemRuler(pSourItem->m_ItemIndex));
	Item	*pDestItem = NULL;
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 nSourLayCount = pSourItem->GetItemCount();
		int32 nRepIndex = pDestContainer->GetIndexByTypeAndBind
			(
				pSourItem->m_ItemIndex,
				pSourItem->GetItemCount(),
				bPickBind
			);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRepIndex != INVALID_INDEX)
		{
			pDestItem = pDestContainer->GetItem(nRepIndex);
			KCheck(pDestItem);
			if(!pDestItem->IsLock() && pDestItem->IsCanLay())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32 nDestLayCount = pDestItem->GetLayedNum();
				int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
				int32 nSourLayCount = pSourItem->GetItemCount();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(nSourLayCount + nDestLayCount <= nDestMaxLayCount)
				{
					SetItemLayedNum(pDestContainer, nRepIndex, nSourLayCount + nDestLayCount);
					return nRepIndex;
				}
			}
		}

		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}
	}
	else
	{
		pDestItem = pDestContainer->GetItem(nDestIndex);
		if(pDestItem == NULL)
		{
			KCheck(FALSE);
			return ITEMOE_UNKNOW;
		}

		if(!pDestItem->IsFree())
		{
			if(!pDestItem->IsLock() && pDestItem->IsCanLay())
			{
				if(pDestItem->GetItemTableIndex() == pSourItem->m_ItemIndex)
				{
					if
					(
						(pDestItem->GetItemBindType() & bPickBind)
					||	((pDestItem->GetItemBindType() == BIND_NONE) && (~bPickBind))
					)
					{
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
						int32 nDestLayCount = pDestItem->GetLayedNum();
						int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
						int32 nSourLayCount = pSourItem->GetItemCount();
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

						if(nSourLayCount + nDestLayCount <= nDestMaxLayCount)
						{
							SetItemLayedNum
							(
								pDestContainer,
								nDestIndex,
								nSourLayCount + nDestLayCount
							);
							return nDestIndex;
						}
					}
				}
			}

			return ITEMOE_DESTOPERATOR_HASITEM;
		}

		KCheck(!pDestItem->IsLock());
	}

	pDestContainer->SetItemValue(nFinalDestIndex, pSourItem);
	return nFinalDestIndex;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::MoveItem_i
(
	ItemContainer	*pSourContainer,
	int32 nSourIndex,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	__GUARD__ if
		(
			pSourContainer == NULL
		||	(nSourIndex < 0)
		||	pDestContainer == NULL
		||	(nDestIndex < INVALID_INDEX)
		)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pSourContainer->IsValid())
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsValid())
	{
		return ITEMOE_UNKNOW;
	}

	if(nDestIndex >= pDestContainer->GetContainerSize())
	{
		return ITEMOE_UNKNOW;
	}

	if(nSourIndex >= pSourContainer->GetContainerSize())
	{
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pSourContainer->GetItem(nSourIndex);
	Item	*pDestItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}
	else if(pSourItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		if(pSourItem->m_Type != IDT_PET)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32 nSourLayCount = pSourItem->GetLayedNum();
			int32 nRepIndex = pDestContainer->GetIndexByTypeAndBind
				(
					pSourItem->GetItemTableIndex(),
					pSourItem->GetLayedNum(),
					pSourItem->GetItemBindType()
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nRepIndex != INVALID_INDEX)
			{
				pDestItem = pDestContainer->GetItem(nRepIndex);
				KCheck(pDestItem);
				if(!pDestItem->IsLock() && pDestItem->IsCanLay())
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					int32 nDestLayCount = pDestItem->GetLayedNum();
					int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
					int32 nSourLayCount = pSourItem->GetLayedNum();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(nSourLayCount + nDestLayCount <= nDestMaxLayCount)
					{
						SetItemLayedNum
						(
							pDestContainer,
							nRepIndex,
							nSourLayCount + nDestLayCount
						);
						pSourContainer->EraseItem(nSourIndex);
						return nRepIndex;
					}
				}
			}
		}

		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}
	}
	else
	{
		pDestItem = pDestContainer->GetItem(nDestIndex);
		if(pDestItem == NULL)
		{
			KCheck(FALSE);
			return ITEMOE_UNKNOW;
		}

		if(!pDestItem->IsFree())
		{
			if(pDestItem->IsLock())
			{
				return ITEMOE_UNKNOW;
			}

			if(pDestItem->IsCanLay())
			{
				if(pSourItem->GetItemTableIndex() == pDestItem->GetItemTableIndex())
				{
					if(pSourItem->GetItemBindType() != pDestItem->GetItemBindType())
					{
						return ITEMOE_UNKNOW;
					}

					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					int32 nDestLayCount = pDestItem->GetLayedNum();
					int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
					int32 nSourLayCount = pSourItem->GetLayedNum();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(nSourLayCount + nDestLayCount <= nDestMaxLayCount)
					{
						SetItemLayedNum
						(
							pDestContainer,
							nDestIndex,
							nSourLayCount + nDestLayCount
						);
						pSourContainer->EraseItem(nSourIndex);
						return nDestIndex;
					}
					else
						return ITEMOE_UNKNOW;
				}
			}
		}
	}

	pDestContainer->SetItem(nFinalDestIndex, pSourItem);
	pSourContainer->EraseItem(nSourIndex);

	return nFinalDestIndex;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::MoveItem_i
(
	ItemContainer	*pSourContainer,
	int32 nSourIndex,
	BOOL &bNewPos,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	__GUARD__ if
		(
			pSourContainer == NULL
		||	(nSourIndex < 0 || nSourIndex >= pSourContainer->GetContainerSize())
		||	pDestContainer == NULL
		||	(nDestIndex < INVALID_INDEX || nDestIndex >= pDestContainer->GetContainerSize())
		)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pSourContainer->GetItem(nSourIndex);
	Item	*pDestItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	bNewPos = FALSE;

	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}
	else if(pSourItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 nRepIndex = pDestContainer->GetIndexByTypeAndBind
			(
				pSourItem->GetItemTableIndex(),
				pSourItem->GetLayedNum(),
				pSourItem->GetItemBindType()
			);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRepIndex != INVALID_INDEX)
		{
			pDestItem = pDestContainer->GetItem(nRepIndex);
			KCheck(pDestItem);
			if(!pDestItem->IsLock() && pDestItem->IsCanLay())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32 nDestLayCount = pDestItem->GetLayedNum();
				int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
				int32 nSourLayCount = pSourItem->GetLayedNum();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(nSourLayCount + nDestLayCount <= nDestMaxLayCount)
				{
					SetItemLayedNum(pDestContainer, nRepIndex, nSourLayCount + nDestLayCount);
					pSourContainer->EraseItem(nSourIndex);
					return nRepIndex;
				}
			}
		}

		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}

		bNewPos = TRUE;
	}
	else
	{
		pDestItem = pDestContainer->GetItem(nDestIndex);
		if(pDestItem == NULL)
		{
			KCheck(FALSE);
			return ITEMOE_UNKNOW;
		}
		else if(!pDestItem->IsFree())
		{
			return ITEMOE_DESTOPERATOR_HASITEM;
		}

		KCheck(!pDestItem->IsLock());
	}

	if(nFinalDestIndex >= 0)
	{
		pDestContainer->SetItem(nFinalDestIndex, pSourItem);
		pSourContainer->EraseItem(nSourIndex);
	}

	return nFinalDestIndex;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemContainer *ItemInterface::GetEquipContainer(Player *pPlayer) const
{
	KCheck(pPlayer);
	return pPlayer->GetEquipContain();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemContainer *ItemInterface::GetBagContainer(Player *pPlayer, uint32 uSlot) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uSlot < MAX_BAG_SIZE);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(uSlot < EXTRA_BAG1_OFFSET)
	{
		return pPlayer->GetBaseContain();
	}
	else
	{
		for (int32 i =0 ; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			int32 nExtraOffSet = EXTRA_BAG_OFFSET(i + 1);
			if (uSlot < nExtraOffSet)
			{
				pContainer = pPlayer->GetExtraBagContain(i);			
				KCheck(pContainer);

				if(pContainer->IsValid())
				{
					if(pContainer->IsInContainer(uSlot))
					{
						return pContainer;
					}
				}
				return NULL;
			}
		}
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemContainer *ItemInterface::GetBagItemContain(Player *pPlayer, SItemGuid *pItemID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pItemContainer = pPlayer->GetBaseContain();
	int32 FinalIndex = pItemContainer->GetIndexByGUID(pItemID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FinalIndex == INVALID_INDEX)
	{
		for (int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pItemContainer = pPlayer->GetExtraBagContain(i);			
			KCheck(pItemContainer);

			if(pItemContainer->IsValid())
			{
				FinalIndex = pItemContainer->GetIndexByGUID(pItemID);
				if(FinalIndex != INVALID_INDEX)
				{
					return pItemContainer;
				}
			}
		}
	}

	if(FinalIndex < 0)
	{
		return NULL;
	}

	return pItemContainer;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemContainer *ItemInterface::GetBagByExtraContainPos(Player *pPlayer, uint32 uExtraIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPlayer)
	{
		KCheck(FALSE);
		return 0;
	}

	if(uExtraIndex < EXTRA_CONTAINER_OFFSET)
	{
		return NULL;
	}

	if(uExtraIndex > MAX_BAG_SIZE)
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetExtraContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nConIndex = pContainer->BagIndex2ConIndex(uExtraIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return pPlayer->GetExtraBagContain(nConIndex);

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemContainer *ItemInterface::GetBagItemContain(Player *pPlayer, SItemGuid *pItemID, int32 &nBagIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pItemContainer = pPlayer->GetBaseContain();
	int32 FinalIndex = pItemContainer->GetIndexByGUID(pItemID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FinalIndex == INVALID_INDEX)
	{
		for (int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			pItemContainer = pPlayer->GetExtraBagContain(i);			
			KCheck(pItemContainer);

			if(pItemContainer->IsValid())
			{
				FinalIndex = pItemContainer->GetIndexByGUID(pItemID);
				if(FinalIndex != INVALID_INDEX)
				{
					nBagIndex = pItemContainer->ConIndex2BagIndex(FinalIndex);
					return pItemContainer;
				}
			}
		}
	}

	if(FinalIndex >= 0)
	{
		nBagIndex = pItemContainer->ConIndex2BagIndex(FinalIndex);
		return pItemContainer;
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *ItemInterface::GetExtraContainerItem(Player *pPlayer, uint32 uExtraContainerIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uExtraContainerIndex >= EXTRA_CONTAINER_OFFSET);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetExtraContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheck(FALSE);
		return NULL;
	}

	return pContainer->GetItem(pContainer->BagIndex2ConIndex(uExtraContainerIndex));

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *ItemInterface::GetExtraBagFromBagIndex(Player *pPlayer, uint32 uSlot) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck((uSlot >= EXTRA_BAG1_OFFSET) && (uSlot < EXTRA_CONTAINER_OFFSET));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item		*pItem = NULL;
	ItemContainer	*pContainer = pPlayer->GetExtraContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);

	for (int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		if(pContainer->IsInContainer(uSlot))
		{
			pItem = pContainer->GetItem(i);
			if(!pItem->IsFree())
			{
				KCheck(pItem->GetItemClass() == ICLASS_EXTRABAG);
				return pItem;
			}
			else
			{
				break;
			}
		}
	}

	KCheck(FALSE);
	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *ItemInterface::GetBankItem(Player *pPlayer, uint32 BankIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(BankIndex < MAX_BANK_SIZE);
	KCheck(BankIndex >= 0);
	if(BankIndex < 0 || BankIndex > MAX_BANK_SIZE)
	{
		KCheckEx(FALSE, "ItemInterface::GetBankItem() BankIndex 不在合法范围 ");
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pBankContainer = pPlayer->GetBankContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pBankContainer);

	if(!pBankContainer)
	{
		return NULL;
	}

	return pBankContainer->GetItem((uint32) BankIndex);

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *ItemInterface::GetBagItem(Player *pPlayer, uint32 uSlot) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(uSlot > EXTRA_CONTAINER_OFFSET) return NULL;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		return NULL;
	}

	if ( pContainer->BagIndex2ConIndex(uSlot) >= pContainer->GetContainerSize() )
	{
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"ItemInterface::GetBagItem: uSlot=%d ,ContainerSize=%d",uSlot,pContainer->GetContainerSize());
	}
	
	return pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::GetBagItemPosByGUID(Player *pPlayer, SItemGuid guid) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(guid.isNull() == FALSE);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 iFinalIndex = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iFinalIndex = pPlayer->GetBaseContain()->GetIndexByGUID(&guid);
	if(iFinalIndex != INVALID_ID) return pPlayer->GetBaseContain()->ConIndex2BagIndex(iFinalIndex);

	if(iFinalIndex == INVALID_ID)
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemContainer	*pContainer = pPlayer->GetExtraBagContain(i);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pContainer->IsValid())
			{
				iFinalIndex = pContainer->GetIndexByGUID(&guid);
			}

			if(iFinalIndex != INVALID_ID)
			{
				return pPlayer->GetExtraBagContain(i)->ConIndex2BagIndex(iFinalIndex);
			}
		}
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::GetBagItemPosByType(Player *pPlayer, uint32 uItemIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uItemIndex > 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != INVALID_ID);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 iFinalIndex = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iFinalIndex = pPlayer->GetBaseContain()->GetIndexByType(uItemIndex);
	if(iFinalIndex != INVALID_ID)
	{
		return pPlayer->GetBaseContain()->ConIndex2BagIndex(iFinalIndex);
	}

	if(iFinalIndex == INVALID_ID)
	{
		for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemContainer	*pContainer = pPlayer->GetExtraBagContain(i);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pContainer->IsValid())
			{
				iFinalIndex = pContainer->GetIndexByType(uItemIndex);
			}

			if(iFinalIndex != INVALID_ID)
			{
				return pPlayer->GetExtraBagContain(i)->ConIndex2BagIndex(iFinalIndex);
			}
		}
	}

	return iFinalIndex;
	__UNGUARD__ return INVALID_ID;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetBagItemCountByLessLevel(Player *pPlayer, uint32 uLevel,uint32 nDataId) const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetBaseContain();

	if(!pContainer)
		return 0;

	//先检查基本背包中的物品数量
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
		{
			continue;
		}

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetCurLevel() >= uLevel )
		{
			count += pItem->GetLayedNum();
		}
	}

	//检查扩展背包中的数量
	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(pContainer->IsValid())
		{
			for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
			{
				pItem = pContainer->GetItem(i);
				if(!pItem)
					continue;

				if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetCurLevel() >= uLevel)
				{
					count += pItem->GetLayedNum();
				}
			}
		}
	}

	return count;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetEquipItemCountByLessLevel(Player *pPlayer, uint32 uLevel,uint32 nDataId) const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetEquipContain();

	if(!pContainer)
		return 0;

	//先检身上装备栏中的物品
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
			continue;

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetCurLevel() >= uLevel )
		{
			count += pItem->GetLayedNum();
		}
	}

	return count;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetBagItemCountByLessHole(Player *pPlayer,uint32 uHole,uint32 nDataId)const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetBaseContain();

	if(!pContainer)
		return 0;

	//先检查基本背包中的物品数量
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
		{
			continue;
		}

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetCurGemHole() >= uHole )
		{
			count += pItem->GetLayedNum();
		}
	}

	//检查扩展背包中的数量
	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(pContainer->IsValid())
		{
			for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
			{
				pItem = pContainer->GetItem(i);
				if(!pItem)
					continue;

				if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetCurGemHole() >= uHole)
				{
					count += pItem->GetLayedNum();
				}
			}
		}
	}

	return count;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetEquipItemCountByLessHole(Player *pPlayer,uint32 uHole,uint32 nDataId)const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetEquipContain();

	if(!pContainer)
		return 0;

	//先检身上装备栏中的物品
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
			continue;

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetCurGemHole() >= uHole )
		{
			count += pItem->GetLayedNum();
		}
	}

	return count;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetBagItemCountByLessGem(Player *pPlayer,uint32 uGem,uint32 nDataId )const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetBaseContain();

	if(!pContainer)
		return 0;

	//先检查基本背包中的物品数量
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
		{
			continue;
		}

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetEquipGemCount() >= uGem )
		{
			count += pItem->GetLayedNum();
		}
	}

	//检查扩展背包中的数量
	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(pContainer->IsValid())
		{
			for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
			{
				pItem = pContainer->GetItem(i);
				if(!pItem)
					continue;

				if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetEquipGemCount() >= uGem)
				{
					count += pItem->GetLayedNum();
				}
			}
		}
	}

	return count;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetEquipItemCountByLessGem(Player *pPlayer,uint32 uGem,uint32 nDataId)const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetEquipContain();

	if(!pContainer)
		return 0;

	//先检身上装备栏中的物品
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
			continue;

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetEquipGemCount() >= uGem )
		{
			count += pItem->GetLayedNum();
		}
	}

	return count;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetBagItemCountByLessSoulBind(Player *pPlayer,uint32 uBindLevel,uint32 nDataId)const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetBaseContain();

	if(!pContainer)
		return 0;

	//先检查基本背包中的物品数量
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
		{
			continue;
		}

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetEquipBindLevel() >= uBindLevel )
		{
			count += pItem->GetLayedNum();
		}
	}

	//检查扩展背包中的数量
	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(pContainer->IsValid())
		{
			for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
			{
				pItem = pContainer->GetItem(i);
				if(!pItem)
					continue;

				if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetEquipBindLevel() >= uBindLevel)
				{
					count += pItem->GetLayedNum();
				}
			}
		}
	}

	return count;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetEquipItemCountByLessSoulBind(Player *pPlayer,uint32 uBindLevel,uint32 nDataId) const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetEquipContain();

	if(!pContainer)
		return 0;

	//先检身上装备栏中的物品
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
			continue;

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetEquipBindLevel() >= uBindLevel )
		{
			count += pItem->GetLayedNum();
		}
	}

	return count;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetBagItemCountByLessPurple(Player *pPlayer,uint32 uPurpleCount,uint32 nDataId) const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetBaseContain();

	if(!pContainer)
		return 0;

	//先检查基本背包中的物品数量
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
		{
			continue;
		}

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetPurplePropertyCount() >= uPurpleCount )
		{

			count += pItem->GetLayedNum();
		}
	}

	//检查扩展背包中的数量
	for(int32 i = 0; i < MAX_EXTRA_BAG_NUM; ++i)
	{
		pContainer = pPlayer->GetExtraBagContain(i);
		if(pContainer->IsValid())
		{
			for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
			{
				pItem = pContainer->GetItem(i);
				if(!pItem)
					continue;

				if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetPurplePropertyCount() >= uPurpleCount)
				{
					count += pItem->GetLayedNum();
				}
			}
		}
	}

	return count;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemInterface::GetEquipItemCountByLessPurple(Player *pPlayer,uint32 uPurpleCount,uint32 nDataId) const
{
	KCheck(pPlayer);

	int32 count = 0;
	Item*pItem = NULL;
	ItemContainer*pContainer = pPlayer->GetEquipContain();

	if(!pContainer)
		return 0;

	//先检身上装备栏中的物品
	for(int32 i = 0; i < pContainer->GetContainerSize(); ++i)
	{
		pItem = pContainer->GetItem(i);
		if(!pItem)
			continue;

		if( pItem->IsEquip() && pItem->GetItemTableIndex() == nDataId && pItem->GetPurplePropertyCount() >= uPurpleCount )
		{
			count += pItem->GetLayedNum();
		}
	}

	return count;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *ItemInterface::GetEquip(Player *pPlayer, PLAYER_EQUIP EquipPoint) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(EquipPoint < HEQUIP_NUMBER);
	KCheck(EquipPoint >= 0);
	if(EquipPoint < 0 || EquipPoint > HEQUIP_NUMBER)
	{
		KCheckEx(FALSE, "ItemInterface::SetBagItemDur() EquipPoint 不在合法范围 ");
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pEquipContainer = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pEquipContainer);

	if(!pEquipContainer)
	{
		return NULL;
	}

	return pEquipContainer->GetItem((uint32) EquipPoint);

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetInventoryItemDurability(Player *pPlayer, uint32 uSlot, int32 iDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uSlot < MAX_BAG_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	return SetItemDurability(pContainer, pContainer->BagIndex2ConIndex(uSlot), iDur);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetBagItemCurMaxDur(Player *pPlayer, uint32 uSlot, int32 iDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uSlot < MAX_BAG_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	return SetItemCurMaxDur(pContainer, pContainer->BagIndex2ConIndex(uSlot), iDur);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetInventoryItemIdentify(Player *pPlayer, uint32 uSlot)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uSlot < MAX_BAG_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = SetItemIdent(pContainer, pContainer->BagIndex2ConIndex(uSlot));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pContainer->GetItem(pContainer->BagIndex2ConIndex(uSlot));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetInventoryItemFreeParam(Player *pPlayer, uint32 uSlot, uint32 Start, int32 Type, int32 value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uSlot < MAX_BAG_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = SetItemFreeParam(pContainer, pContainer->BagIndex2ConIndex(uSlot), Start, Type, value);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetBagEquipDur(Player *pPlayer, uint32 uSlot, int32 iDur)
{
	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	return SetItemDurability(pContainer, pContainer->BagIndex2ConIndex(uSlot), iDur);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetCurBagEquipMaxDur(Player *pPlayer, uint32 uSlot, int32 iDur)
{
	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	return SetItemCurMaxDur(pContainer, pContainer->BagIndex2ConIndex(uSlot), iDur);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetEquipDamagePoint(Player *pPlayer, PLAYER_EQUIP EquipPoint, uint32 nDamagePoint)
{
	KCheck(pPlayer);
	KCheck(EquipPoint < HEQUIP_NUMBER);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pEquipContain = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pEquipContain);

	return SetItemDamagePoint(pEquipContain, EquipPoint, nDamagePoint);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetEquipBind(Player *pPlayer, PLAYER_EQUIP EquipPoint, uchar bBindType)
{
	KCheck(pPlayer);
	KCheck(EquipPoint < HEQUIP_NUMBER);
	KCheck(bBindType < BIND_INVALID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pEquipContain = pPlayer->GetEquipContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pEquipContain);

	return Bind(pEquipContain, EquipPoint, bBindType);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetEquipDur(Player *pPlayer, PLAYER_EQUIP EquipPoint, int32 iDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(EquipPoint < HEQUIP_NUMBER);
	KCheck(EquipPoint >= 0);
	if(EquipPoint < 0 || EquipPoint > HEQUIP_NUMBER)
	{
		KCheckEx(FALSE, "ItemInterface::SetBagItemDur() EquipPoint 不在合法范围 ");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pPlayer->GetEquipContain()->GetItem(EquipPoint);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	if(pItem->IsFree())
	{
		return FALSE;
	}

	if(iDur > pItem->GetCurMaxDurability())
	{
		return FALSE;
	}

	if(iDur == pItem->GetDurability())
	{
		return FALSE;
	}


	return SetItemDurability(pPlayer->GetEquipContain(), EquipPoint, iDur);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetCurEquipMaxDur(Player *pPlayer, PLAYER_EQUIP EquipPoint, int32 iDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(EquipPoint < HEQUIP_NUMBER);
	KCheck(EquipPoint >= 0);
	if(EquipPoint < 0 || EquipPoint > HEQUIP_NUMBER)
	{
		KCheckEx(FALSE, "ItemInterface::SetCurEquipMaxDur() EquipPoint 不在合法范围 ");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pItem = pPlayer->GetEquipContain()->GetItem(EquipPoint);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	if(pItem->IsFree())
	{
		return FALSE;
	}

	if(iDur > pItem->GetMaxDurPoint())
	{
		return FALSE;
	}

	return SetItemCurMaxDur(pPlayer->GetEquipContain(), EquipPoint, iDur);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::MoveSpliceItem
(
	ItemContainer	*pSourContainer,
	uchar uSourIndex,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	__GUARD__ if
		(
			pSourContainer == NULL
		||	(uSourIndex < 0 || uSourIndex >= pSourContainer->GetContainerSize())
		||	pDestContainer == NULL
		||	(nDestIndex < INVALID_INDEX)
		)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pSourContainer->GetItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSourItem)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pDestContainer->GetItem(nDestIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pDestItem)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->GetItemIndex() != pDestItem->GetItemIndex())
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(!pSourItem->IsCanLay())
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->IsFree() || pDestItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}

	if(pSourItem->IsLock() || pDestItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	if(pSourItem->GetItemBindType() != pDestItem->GetItemBindType())
	{
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nSourLayCount = pSourItem->GetLayedNum();
	int32 nDestLayCount = pDestItem->GetLayedNum();
	int32 nMaxLayCount = pDestItem->GetMaxLayedNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nMaxLayCount >= nSourLayCount + nDestLayCount)
	{
		SetItemLayedNum(pDestContainer, nDestIndex, nSourLayCount + nDestLayCount);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL bRet = pSourContainer->EraseItem(uSourIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(bRet);
	}
	else
	{
		SetItemLayedNum(pDestContainer, nDestIndex, nMaxLayCount);
		SetItemLayedNum(pSourContainer, uSourIndex, nSourLayCount + nDestLayCount - nMaxLayCount);
	}

	return ITEMOE_SUCCESS;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::ExchangeItem
(
	ItemContainer	*pSourContainer,
	int32 nSourIndex,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	__GUARD__ if
		(
			pSourContainer == NULL
		||	(nSourIndex < 0 || nSourIndex >= pSourContainer->GetContainerSize())
		||	pDestContainer == NULL
		||	(nDestIndex < INVALID_INDEX || nDestIndex >= pDestContainer->GetContainerSize())
		)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pSourContainer->IsCanUse())
	{
		return ITEMOE_SOUROPUSE_FAIL;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = NULL;
	Item	*pDestItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	pDestItem = pDestContainer->GetItem(nDestIndex);
	if(pDestItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_DESTOPERATOR_EMPTY;
	}
	else if(pDestItem->IsFree())
	{
		return ITEMOE_DESTOPERATOR_EMPTY;
	}
	else if(pDestItem->IsLock())
	{
		return ITEMOE_DESTOPERATOR_LOCK;
	}

	pSourItem = pSourContainer->GetItem(nSourIndex);
	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	if(pSourItem->m_Type != pDestItem->m_Type)
	{
		return ITEMOE_DIFF_ITEM_DATA;
	}

	switch(pSourItem->m_Type)
	{
	case IDT_ITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItem TmpITEM;
			const CItemInit Init(&TmpITEM);
			Item tempItem;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tempItem.Init(&Init);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItem TmpITEM1;
			const CItemInit Init1(&TmpITEM1);
			Item tempItem1;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tempItem1.Init(&Init1);
			TmpITEM1 = *pSourItem->m_pItem;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItem TmpITEM2;
			const CItemInit Init2(&TmpITEM2);
			Item tempItem2;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tempItem2.Init(&Init2);
			TmpITEM2 = *pDestItem->m_pItem;

			pSourContainer->SetItem(nSourIndex, &tempItem);
			pDestContainer->SetItem(nDestIndex, &tempItem);

			pSourContainer->SetItem(nSourIndex, &tempItem2);
			pDestContainer->SetItem(nDestIndex, &tempItem1);
		}
		break;

	case IDT_PET:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_HORSE_DB_LOAD TmpPet;
			const CItemInit Init(&TmpPet);
			Item tempItem;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tempItem.Init(&Init);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_HORSE_DB_LOAD TmpPet1;
			const CItemInit Init1(&TmpPet1);
			Item tempItem1;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tempItem1.Init(&Init1);
			TmpPet1 = *pSourItem->m_pPet;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_HORSE_DB_LOAD TmpPet2;
			const CItemInit Init2(&TmpPet2);
			Item tempItem2;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			tempItem2.Init(&Init2);
			TmpPet2 = *pDestItem->m_pPet;

			pSourContainer->SetItem(nSourIndex, &tempItem);
			pDestContainer->SetItem(nDestIndex, &tempItem);

			pSourContainer->SetItem(nSourIndex, &tempItem2);
			pDestContainer->SetItem(nDestIndex, &tempItem1);
		}
		break;

	default:
		{
			KCheck(FALSE);
			return ITEMOE_UNKNOW;
		}
	}

	return ITEMOE_SUCCESS;
	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::CopyItem
(
	ItemContainer	*pSourContainer,
	int32 nSourIndex,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pSourContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestContainer);
	if(!pSourContainer->IsValid())
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsValid())
	{
		return ITEMOE_UNKNOW;
	}

	if
	(
		pSourContainer == NULL
	||	(nSourIndex < 0 || nSourIndex >= pSourContainer->GetContainerSize())
	||	pDestContainer == NULL
	||	(nDestIndex < INVALID_INDEX || nDestIndex >= pDestContainer->GetContainerSize())
	)
	{
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = NULL;
	Item	*pDestItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	pSourItem = pSourContainer->GetItem(nSourIndex);
	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}
	else if(pSourItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}
	}
	else
	{
		pDestItem = pDestContainer->GetItem(nDestIndex);
		if(pDestItem == NULL)
		{
			KCheck(FALSE);
			return ITEMOE_UNKNOW;
		}

		if(!pDestItem->IsFree())
		{
			return ITEMOE_DESTOPERATOR_HASITEM;
		}

		if(pDestItem->IsLock())
		{
			return ITEMOE_DESTOPERATOR_LOCK;
		}
	}

	pDestContainer->SetItem(nFinalDestIndex, pSourItem);

	return nFinalDestIndex;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::CopyItemFromItemBox
(
	SItemBoxContaner *pSourceContainer,
	int32 nSourceIndex,
	BOOL &bNewPos,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDestContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestContainer->IsValid())
	{
		return ITEMOE_UNKNOW;
	}

	if
	(
		pSourceContainer == NULL
	||	(nSourceIndex < 0 || nSourceIndex >= MAX_BOXITEM_NUMBER)
	||	pDestContainer == NULL
	||	(nDestIndex < INVALID_INDEX || nDestIndex >= pDestContainer->GetContainerSize())
	)
	{
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SItem	*pSourItem = &(pSourceContainer->m_Item[nSourceIndex]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pSourItem == NULL)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = NULL;
	int32 nFinalDestIndex = nDestIndex;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nFinalDestIndex == INVALID_INDEX)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 nRepIndex = pDestContainer->GetIndexByTypeAndBind
			(
				pSourItem->m_ItemIndex,
				pSourItem->GetItemCount(),
				pSourItem->m_nsBind
			);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRepIndex != INVALID_INDEX)
		{
			pDestItem = pDestContainer->GetItem(nRepIndex);
			KCheck(pDestItem);

			if(!pDestItem)
			{
				return ITEMOE_UNKNOW;
			}

			if(!pDestItem->IsFree() && !pDestItem->IsLock() && pDestItem->IsCanLay())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32 nDestLayCount = pDestItem->GetLayedNum();
				int32 nDestMaxLayCount = pDestItem->GetMaxLayedNum();
				int32 nSourLayCount = pSourItem->GetItemCount();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(nSourLayCount + nDestLayCount < nDestMaxLayCount)
				{
					SetItemLayedNum(pDestContainer, nRepIndex, nSourLayCount + nDestLayCount);
					return nRepIndex;
				}
			}
		}

		nFinalDestIndex = pDestContainer->GetFreeItemIndex();
		if(nFinalDestIndex == INVALID_INDEX)
		{
			return ITEMOE_DESTOPERATOR_FULL;
		}

		pDestItem = pDestContainer->GetItem(nFinalDestIndex);
	}
	else
	{
		pDestItem = pDestContainer->GetItem(nDestIndex);
		if(pDestItem == NULL)
		{
			KCheck(FALSE);
			return ITEMOE_UNKNOW;
		}

		if(!pDestItem->IsFree())
		{
			return ITEMOE_DESTOPERATOR_HASITEM;
		}
	}

	pDestItem->SetItemValue(pSourItem);
	bNewPos = TRUE;

	return nFinalDestIndex;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::SpliceItem
(
	ItemContainer	*pSourContainer,
	uchar uSourIndex,
	ItemContainer *pDestContainer,
	int32 nDestIndex
)
{
	__GUARD__ if
		(
			pSourContainer == NULL
		||	(uSourIndex < 0 || uSourIndex >= pSourContainer->GetContainerSize())
		||	pDestContainer == NULL
		||	(nDestIndex < INVALID_INDEX)
		)
	{
		return ITEMOE_UNKNOW;
	}

	if(!pDestContainer->IsCanUse())
	{
		return ITEMOE_DESTOPUSE_FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pSourItem = pSourContainer->GetItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSourItem)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pDestContainer->GetItem(nDestIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pDestItem)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->GetItemIndex() != pDestItem->GetItemIndex())
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	if(pSourItem->IsFree() || pDestItem->IsFree())
	{
		return ITEMOE_SOUROPERATOR_EMPTY;
	}

	if(pSourItem->IsLock() || pDestItem->IsLock())
	{
		return ITEMOE_SOUROPERATOR_LOCK;
	}

	if(pSourItem->GetItemBindType() != pDestItem->GetItemBindType())
	{
		return ITEMOE_UNKNOW;
	}

	if
	(
		!pSourItem->IsCanLay()
	||	!pDestItem->IsCanLay()
	||	pSourItem->GetLayedNum() + pDestItem->GetLayedNum() > pDestItem->GetMaxLayedNum()
	)
	{
		KCheck(FALSE);
		return ITEMOE_UNKNOW;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nSourLayCount = pSourItem->GetLayedNum();
	int32 nDestLayCount = pDestItem->GetLayedNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetItemLayedNum(pDestContainer, nDestIndex, nSourLayCount + nDestLayCount);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = pSourContainer->EraseItem(uSourIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(bRet);

	return ITEMOE_SUCCESS;

	__UNGUARD__ return ITEMOE_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemLayedNum(ItemContainer *pContainer, int32 nIndex, int32 nCount)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemLayCount get invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsFree())
	{
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemLayedNum(nIndex, nCount);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::DecItemLayedNum(ItemContainer *pContainer, int32 nIndex, int32 nCount)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::DecItemLayCount get invalid");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsFree())
	{
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->DecItemLayedNum(nIndex, nCount);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::IncItemLayedNum(ItemContainer *pContainer, int32 nIndex, int32 nCount)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::IncItemLayCount get invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->IncItemLayedNum(nIndex, nCount);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemDurability(ItemContainer *pContainer, int32 nIndex, int32 nDur)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemDur get Invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemDurability(nIndex, nDur);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemIdent(ItemContainer *pContainer, int32 nIndex)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemIdent get Invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemIdent(nIndex);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemDamagePoint(ItemContainer *pContainer, int32 nIndex, int32 nPoint)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemDamagePoint get Invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemDamagePoint(nIndex, nPoint);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemCurMaxDur(ItemContainer *pContainer, int32 nIndex, int32 nDur)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemDur get Invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemCurMaxDur(nIndex, nDur);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemBind(ItemContainer *pContainer, int32 nIndex)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemBind get Invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemBind(nIndex);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemPWLock(ItemContainer *pContainer, int32 nIndex, BOOL bLock)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemPWLock get Invalid");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemPWLock(nIndex, bLock);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemCreator(ItemContainer *pContainer, int32 nIndex, const char *CreatorName)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemCreator get Invalid");
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemCreator(nIndex, CreatorName);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemFreeParam(ItemContainer *pContainer, int32 nIndex, uint32 start, int32 type, int32 value)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemParam get Invalid");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemFreeParam(nIndex, start, type, value);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::GetItemFreeParamValue(ItemContainer *pContainer, int32 nIndex, uint32 Start, eITEM_PARAM_VALUE &ipv)
{
	__GUARD__ if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::GetItemParamValue get Invalid");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);

	return pDestItem->GetItemFreeParam(Start, ipv);

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::AddItemProperty(ItemContainer *pContainer, int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::AddItemAttr() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->AddItemProperty(nIndex, iA);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::DelItemProperty(ItemContainer *pContainer, int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::DelItemAttr() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->DelItemProperty(nIndex, iA);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::DelGemInfo(ItemContainer *pContainer, int32 nIndex, int32 GemIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::DelItemInfo() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->DelGemInfo(nIndex, GemIndex);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::AddGemInfo(ItemContainer *pContainer, int32 nIndex, int32 GemIndex, uint32 GemHolePos)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::AddGemInfo() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->AddGemInfo(nIndex, GemIndex, GemHolePos);

	__UNGUARD__ return FALSE;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::Bind(ItemContainer *pContainer, int32 nIndex, uchar bindType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Bind() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->Bind(nIndex, bindType);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::ItemLevelup(ItemContainer *pContainer, int32 nIndex, int32 nLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::ItemLevelup() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->ItemLevelup(nIndex, nLevel);

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemInterface::EquipHonorBindLevelup(ItemContainer *pContainer, int32 nIndex, int32 nLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::EquipHonorBindLevelup() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->EquipHonorBindLevelup(nIndex, nLevel);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemAttr(ItemContainer *pContainer, int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemAttr() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemProperty(nIndex, nAtt, iA);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemPaiType(ItemContainer *pContainer, int32 nIndex, uchar nPaiType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemPaiType() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemPaiType(nIndex, nPaiType);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::ItemLevelBind(ItemContainer *pContainer, int32 nIndex, uint32 nBindLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::ItemLevelBind() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->ItemLevelBind(nIndex, nBindLevel);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemScore(ItemContainer *pContainer, int32 nIndex, uint32 nScore)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemScore() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemScore(nIndex, nScore);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetEquipFromType(ItemContainer *pContainer, int32 nIndex, uchar nType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetEquipFromType() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetEquipFromType(nIndex, nType);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemBeginTime(ItemContainer *pContainer, int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemBeginTime() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemBeginTime(nIndex);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetItemValue(ItemContainer *pContainer, int32 nIndex, const _HORSE_DB_LOAD *pPet)
{
	__GUARD__;

	KCheck(pContainer);
	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemValue Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	Item *pDestItem = pContainer->GetItem(nIndex);

	KCheck(pDestItem);
	if(!pDestItem) 
		return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetItemValue(nIndex, pPet);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetHorseGUID(ItemContainer *pContainer, int32 nIndex, SHorseGuid GUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetHorseGUID() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetHorseGUID(nIndex, GUID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetDataID(ItemContainer *pContainer, int32 nIndex, int32 ID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetDataID() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetDataID(nIndex, ID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetName(ItemContainer *pContainer, int32 nIndex, const char *pName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetName() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	KCheck(pName);

	return pContainer->SetName(nIndex, pName);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetNick(ItemContainer *pContainer, int32 nIndex, const char *pNick)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetNick() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	KCheck(pNick);

	return pContainer->SetNick(nIndex, pNick);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetLevel(ItemContainer *pContainer, int32 nIndex, int32 level)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetLevel() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetLevel(nIndex, level);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetTakeLevel(ItemContainer *pContainer, int32 nIndex, int32 takeLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetTakeLevel() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetTakeLevel(nIndex, takeLevel);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetAttackType(ItemContainer *pContainer, int32 nIndex, int32 attackType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetAttackType() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetAttackType(nIndex, attackType);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetAIType(ItemContainer *pContainer, int32 nIndex, int32 AIType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetAIType() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetBHVClass(nIndex, AIType);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetCampData(ItemContainer *pContainer, int32 nIndex, const SCampData *pCamp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetCampData() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetCampData(nIndex, pCamp);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetHP(ItemContainer *pContainer, int32 nIndex, int32 hp)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetLife(ItemContainer *pContainer, int32 nIndex, int32 Life)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetPetType(ItemContainer *pContainer, int32 nIndex, uchar PetType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetPetType() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetPetType(nIndex, PetType);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::Set_Property_Generation(ItemContainer *pContainer, int32 nIndex, uchar Gen)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Set_Property_Generation() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->Set_Property_Generation(nIndex, Gen);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetHappiness(ItemContainer *pContainer, int32 nIndex, uchar byHappiness)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetHappiness() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetHappiness(nIndex, byHappiness);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::Set_Property_StrPer(ItemContainer *pContainer, int32 nIndex, int32 strper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Set_Property_StrPer() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetStrengthPer(nIndex, strper);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetSmartnessPer(ItemContainer *pContainer, int32 nIndex, int32 conper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Set_Property_ConPer() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetSmartnessPer(nIndex, conper);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetMindPer(ItemContainer *pContainer, int32 nIndex, int32 dexper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Set_Property_DexPer() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetMindPer(nIndex, dexper);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetConstitutionPer(ItemContainer *pContainer, int32 nIndex, int32 intper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Set_Property_IntPer() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetConstitutionPer(nIndex, intper);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::Set_Property_GrowRate(ItemContainer *pContainer, int32 nIndex, float rate)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::Set_Property_GrowRate() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->Set_Property_GrowRate(nIndex, rate);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetRemainPoint(ItemContainer *pContainer, int32 nIndex, int32 rPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetRemainPoint() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetRemainPoint(nIndex, rPoint);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetExp(ItemContainer *pContainer, int32 nIndex, uint32 exp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetExp() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetExp(nIndex, exp);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetLvl1Attr(ItemContainer *pContainer, int32 nIndex, PLAYER_PROPERTY_LEVEL1 type, int32 value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetLvl1Attr() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetLvl1Property(nIndex, type, value);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetSkill(ItemContainer *pContainer, int32 nIndex, uint32 SkillIndex, SHorseSkill skill)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetSkill() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetSkill(nIndex, SkillIndex, skill);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetMatingFlag(ItemContainer *pContainer, int32 nIndex, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetMatingFlag() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetMatingFlag(nIndex, bFlag);

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemInterface::SetComposeFlag(ItemContainer *pContainer, int32 nIndex, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetComposeFlag() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetComposeFlag(nIndex, bFlag);

	__UNGUARD__ return FALSE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetStrengthPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetStrengthPoint() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetStrengthPoint(nIndex, iPoint);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetSmartnessPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetStrengthPoint() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetSmartnessPoint(nIndex, iPoint);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetMindPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetStrengthPoint() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetMindPoint(nIndex, iPoint);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetConstitutionPoint(ItemContainer *pContainer, int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetStrengthPoint() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem) return FALSE;

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	return pContainer->SetConstitutionPoint(nIndex, iPoint);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::LockPet(Player *pPlayer, const SHorseGuid&petGUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	ItemContainer	*pContainer = pPlayer->GetPetContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pContainer);


	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::LockPet() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nIndex = pContainer->GetIndexByGUID(&petGUID);
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(PET_LOCK == pDestItem->m_pPet->m_byLock)
	{
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		return FALSE;
	}

	LuaSystem * pLuaSystem;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);
	pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nRet = pLuaSystem->RunScriptFunction
		(
			pMap->MapID(),
			SCENE_SCRIPTID,
			DEF_MAP_CAN_LOCKPET,
			pMap->MapID(),
			pPlayer->GetID(),
			pDestItem->GetDataID()
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == nRet)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = pContainer->LockPet(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::UnLockPet(Player *pPlayer, const SHorseGuid&petGUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	ItemContainer	*pContainer = pPlayer->GetPetContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetStrengthPoint() Get Invalid");
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nIndex = pContainer->GetIndexByGUID(&petGUID);
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(PET_UNLOCKING == pDestItem->m_pPet->m_byLock)
	{
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(PET_LOCK != pDestItem->m_pPet->m_byLock)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = pContainer->UnlockPet(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemInterface::GetPetLockStatus(Player *pPlayer, const SHorseGuid&petGUID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	ItemContainer	*pContainer = pPlayer->GetPetContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::GetPetLockStatus() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nIndex = pContainer->GetIndexByGUID(&petGUID);
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	return pDestItem->m_pPet->m_byLock;

	__UNGUARD__ return PET_UNLOCK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInterface::UpdatePetUnLockTime(Player *pPlayer)
{
	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pPetCon = pPlayer->GetPetContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pPet = pPetCon->GetItem(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pPet != NULL && pPet->IsLock() == FALSE)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SHorseGuid petGUID = pPet->GetHorseGUID();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(FALSE == petGUID.IsNull())
			{
				if
				(
					PET_UNLOCKING == pPet->m_pPet->m_byLock
				&&	GET_TIME().GetCTime() >= pPet->m_pPet->m_UnLockTime
				)
				{
					pPet->m_pPet->m_byLock = PET_UNLOCK;
				}
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::MovePetToBank(Player *pPlayer, const SHorseGuid&petGUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = pPlayer->GetPetContain();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::MovePetToBank() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nIndex = pContainer->GetIndexByGUID(&petGUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_INDEX == nIndex) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);

	if(TRUE == pDestItem->IsInExchange())
	{
		return FALSE;
	}

	if(TRUE == pDestItem->IsMating())
	{

		return FALSE;
	}

	if(TRUE == pDestItem->IsLock())
	{

		return FALSE;
	}

	LuaSystem * pLuaSystem;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);
	pLuaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nRet = pLuaSystem->RunScriptFunction
		(
			pMap->MapID(),
			SCENE_SCRIPTID,
			DEF_MAP_CAN_MOVEPETTOBANK,
			pMap->MapID(),
			pPlayer->GetID(),
			pDestItem->GetDataID()
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == nRet)
	{
		return FALSE;
	}

	

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::MovePetFromBank(Player *pPlayer, const SHorseGuid&petGUID)
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::ActiveBankPetSlot(Player *pPlayer)
{
	 return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ItemInterface::GetActiveBankPetSlot(Player *pPlayer)
{
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::SetBagEquipBind(Player *pPlayer, uint32 uSlot, uchar bBindType)
{
	KCheck(uSlot < MAX_BAG_SIZE);
	KCheck(pPlayer);
	KCheck(bBindType < BIND_INVALID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pContainer = GetBagContainer(pPlayer, uSlot);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pContainer == NULL)
	{
		return FALSE;
	}

	if(!pContainer->IsCanUse())
	{
		return FALSE;
	}

	return Bind(pContainer, pContainer->BagIndex2ConIndex(uSlot), bBindType);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::IsEquipCon2BagCon(Player *pPlayer, const ItemContainer *pSrcCon, const ItemContainer *pDstCon)
{
	KCheck(pPlayer);
	KCheck(pSrcCon);
	KCheck(pDstCon);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pEquipCon = pPlayer->GetEquipContain();
	ItemContainer	*pBankCon = pPlayer->GetBankContain();
	ItemContainer	*pBagCon = pPlayer->GetBaseContain();
	ItemContainer	*pBagExtraCon1 = pPlayer->GetExtraBagContain(0);
	ItemContainer	*pBagExtraCon2 = pPlayer->GetExtraBagContain(1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pSrcCon == pEquipCon && (pDstCon == pBagCon || pDstCon == pBagExtraCon1 || pDstCon == pBagExtraCon2))
	{
		return TRUE;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::IsBagCon2EquipCon(Player *pPlayer, const ItemContainer *pSrcCon, const ItemContainer *pDstCon)
{
	KCheck(pPlayer);
	KCheck(pSrcCon);
	KCheck(pDstCon);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pEquipCon = pPlayer->GetEquipContain();
	ItemContainer	*pBankCon = pPlayer->GetBankContain();
	ItemContainer	*pBagCon = pPlayer->GetBaseContain();
	ItemContainer	*pBagExtraCon1 = pPlayer->GetExtraBagContain(0);
	ItemContainer	*pBagExtraCon2 = pPlayer->GetExtraBagContain(1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pDstCon == pEquipCon && (pSrcCon == pBagCon || pSrcCon == pBagExtraCon1 || pSrcCon == pBagExtraCon2))
	{
		return TRUE;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::IsBagCon2BagCon(Player *pPlayer, const ItemContainer *pSrcCon, const ItemContainer *pDstCon)
{
	KCheck(pPlayer);
	KCheck(pSrcCon);
	KCheck(pDstCon);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pExtraCon = pPlayer->GetExtraContain();
	ItemContainer	*pBankCon = pPlayer->GetBankContain();
	ItemContainer	*pBagCon = pPlayer->GetBaseContain();
	ItemContainer	*pBagExtraCon1 = pPlayer->GetExtraBagContain(0);
	ItemContainer	*pBagExtraCon2 = pPlayer->GetExtraBagContain(1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if
	(
		(
			pSrcCon == pBagCon
		||	pSrcCon == pBagExtraCon1
		||	pSrcCon == pBagExtraCon2
		||	pSrcCon == pExtraCon
		)
	&&	(
			pDstCon == pBagCon
		||	pDstCon == pBagExtraCon1
		||	pDstCon == pBagExtraCon2
		||	pDstCon == pExtraCon
		)
	)
	{
		return TRUE;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInterface::SetItemGUID(ItemContainer *pContainer, int32 nIndex, SItemGuid *pGuid)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGuid);

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemGUID() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem)
	{
		return;
	}

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return;
	}

	pContainer->SetItemGuid(nIndex, pGuid);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInterface::SetItemGUID(ItemContainer *pContainer, int32 nIndex, SHorseGuid*pGuid)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pContainer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGuid);

	if(!pContainer)
	{
		KCheckEx(FALSE, "ItemInterface::SetItemGUID() Get Invalid");
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = pContainer->GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDestItem);
	if(!pDestItem)
	{
		return;
	}

	if(pDestItem->IsLock())
	{
		KCheck(FALSE);
		return;
	}

	pContainer->SetItemGuid(nIndex, pGuid);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::GenItemGUID(SItemGuid &ig)
{
	__GUARD__ return g_pItemMgr->GenItemGuid(ig);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInterface::GenItemGUID(SHorseGuid&ig)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInterface::FillAndSaveItemLog(ItemLogRecordInfo *pLogParam, Player *pPlayer, Item *pItem)
{

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const SItem *ItemInterface::GetItem(Player *pPlayer, uint32 uDBPos)
{
	return NULL;
}
