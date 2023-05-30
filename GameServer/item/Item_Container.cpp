/*$T MapServer/Server/Item/ItemContainer.cpp GC 1.140 10/10/07 10:07:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_Container.h"

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemContainer::GetIndexByGUID(const SItemGuid *pGuid)
{
	__GUARD__ KCheck(IsValid());

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SItemGuid	guid = m_aItem[i].GetGUID();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if((*pGuid) == guid)
		{
			return i;
		}
	}

	return INVALID_INDEX;
	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemContainer::GetIndexByGUID(const SHorseGuid*pGuid)
{
	__GUARD__ for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		if((*pGuid) == m_aItem[i].GetHorseGUID())
		{
			return i;
		}
	}

	return INVALID_INDEX;

	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemContainer::GetIndexByType(const uint32 uType)
{
	__GUARD__ KCheck(IsValid());

	if(!IsCanUse())
	{
		return INVALID_INDEX;
	}

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		if(uType == m_aItem[i].GetItemTableIndex())
		{
			return i;
		}
	}

	return INVALID_INDEX;

	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemContainer::GetIndexByType(const uint32 uType, uint32 emptyCount)
{
	__GUARD__ KCheck(IsValid());

	if(!IsCanUse())
	{
		return INVALID_INDEX;
	}

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		if(m_aItem[i].m_bLock)
		{
			continue;
		}

		if
			(
			uType == m_aItem[i].GetItemTableIndex()
			&&	m_aItem[i].GetMaxLayedNum() - m_aItem[i].GetLayedNum() >= (int32) emptyCount
			)
		{
			return i;
		}
	}

	return INVALID_INDEX;

	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemContainer::GetIndexByTypeAndBind(const uint32 uType, uchar bBindType)
{
	__GUARD__ for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		if(uType == m_aItem[i].GetItemTableIndex())
		{
			if(m_aItem[i].GetItemBindType() != bBindType)
			{
				continue;
			}

			return i;
		}
	}

	return INVALID_INDEX;

	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 ItemContainer::GetIndexByTypeAndBind(const uint32 uType, uint32 emptyCount, uchar bBindType)
{
	__GUARD__ KCheck(IsValid());

	if(!IsCanUse())
	{
		return INVALID_INDEX;
	}

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		if(m_aItem[i].m_bLock)
		{
			continue;
		}

		if
			(
			uType == m_aItem[i].GetItemTableIndex()
			&&	m_aItem[i].GetMaxLayedNum() - m_aItem[i].GetLayedNum() >= (int32) emptyCount
			)
		{
			if(m_aItem[i].GetItemBindType() != bBindType)
			{
				continue;
			}

			return i;
		}
	}

	return INVALID_INDEX;

	__UNGUARD__ return INVALID_INDEX;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */

ItemContainer::ItemContainer()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_nContainerSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemContainer::~ItemContainer()
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
BOOL ItemContainer::Init(const SItemContainerInit *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nContainerSize = pInit->m_nContainerSize;

	KCheck(m_nContainerSize >= 0 && m_nContainerSize <= MAX_ITEMCONTAINER_SIZE);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemContainer::Clear()
{
	__GUARD__ for(int32 i = 0; i < MAX_ITEMCONTAINER_SIZE; i++)
	{
		m_aItem[i].Clear();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemContainer::ClearItemByIndex(int32 nIndex)
{
	__GUARD__ 

	if(nIndex >= 0 && nIndex < m_nContainerSize)
		m_aItem[nIndex].Clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemContainer::GetContainerType()
{
	__GUARD__ return m_ICTType;

	__UNGUARD__ return -1;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ItemContainer::CalcItemFreeSlot()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KCheck(IsValid());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsCanUse())
	{
		return 0;
	}

	uint32	uCount = 0;

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].m_bLock)
		{
			continue;
		}

		if(m_aItem[i].IsFree())
		{
			uCount++;
		}
	}

	return uCount;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::IsFree()
{
	__GUARD__ KCheck(IsValid());
		
	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(!m_aItem[i].IsFree())
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
uint32 ItemContainer::CalcExchangeItemSlot()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KCheck(IsValid());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsCanUse())
	{
		return 0;
	}

	uint32	uCount = 0;

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			uCount++;
		}
	}

	return uCount;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *ItemContainer::GetItem(const int32 nIndex)
{
	__GUARD__ if(nIndex >= 0 && nIndex < m_nContainerSize)
	{
		return &(m_aItem[nIndex]);
	}

	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItem(const int32 nIndex, const Item *pItem)
{
	__GUARD__;

	KCheck(pItem);
	
	if(nIndex >= 0 && nIndex < m_nContainerSize)
	{
		switch(pItem->m_Type)
		{
		case IDT_ITEM:
			{
				*m_aItem[nIndex].m_pItem = *pItem->m_pItem;
				m_aItem[nIndex].m_bLock = FALSE;
			}
			break;

		case IDT_PET:
			{
				//新骑乘标记
				BOOL bNewPet = m_aItem[nIndex].m_pPet->m_GUID.IsNull();

				//删除骑乘标记
				BOOL bDelPet = pItem->m_pPet->m_GUID.IsNull();

				//记录当前栏位
				int32 iOldStallOrder = m_aItem[nIndex].m_pPet->m_iStallOrder;

				//赋值???
				*m_aItem[nIndex].m_pPet = *pItem->m_pPet;


				if(bDelPet)
				{
					//删除骑乘处理
					ResetHorseStallOrder(iOldStallOrder);
				}
				else if(bNewPet)
				{
					//新骑乘处理
					m_aItem[nIndex].m_pPet->m_iStallOrder = GetValidCount() - 1;
				}
				else
				{
					//其他是什么情况?
					m_aItem[nIndex].m_pPet->m_iStallOrder = iOldStallOrder;
				}

				//去锁?
				m_aItem[nIndex].m_bLock = FALSE;
			}
			break;

		default:
			KCheck(FALSE);
		}

		return TRUE;
	}

	return FALSE;
	__UNGUARD__;
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemContainer::GetFreeItemIndex()
{
	__GUARD__ KCheck(IsValid());

	if(!IsCanUse())
	{
		return INVALID_INDEX;
	}
		
	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree()) return i;
	}

	return INVALID_INDEX;

	__UNGUARD__ return INVALID_INDEX;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemContainer::GetNoFullItemIndex(uint32 uItemIndex)
{
	__GUARD__ KCheck(IsValid());
		
	if(!IsCanUse())
	{
		return INVALID_INDEX;
	}

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if((m_aItem[i].GetItemTableIndex() == uItemIndex) && (m_aItem[i].IsCanLay()))
		{
			if(m_aItem[i].m_bLock)
			{
				continue;
			}

			if(!m_aItem[i].IsFull()) return i;
		}
	}

	return -1;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemContainer::GetNoFullItemIndexAndBind(uint32 uItemIndex, uchar bBindType)
{
	__GUARD__ KCheck(IsValid());
	
	if(!IsCanUse())
	{
		return INVALID_INDEX;
	}

	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if((m_aItem[i].GetItemTableIndex() == uItemIndex) && (m_aItem[i].IsCanLay()))
		{
			if(m_aItem[i].m_bLock)
			{
				continue;
			}

			if(m_aItem[i].GetItemBindType() != bBindType)
			{
				continue;
			}

			if(!m_aItem[i].IsFull()) return i;
		}
	}

	return -1;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::ExpandSize(const int32 nSize)
{
	__GUARD__ if(nSize < 0 || (m_nContainerSize + nSize) > MAX_ITEMCONTAINER_SIZE)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_nContainerSize += nSize;
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetSize(const int32 nSize)
{
	__GUARD__ if(nSize < 0 || nSize > MAX_ITEMCONTAINER_SIZE)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_nContainerSize = nSize;
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemLayedNum(int32 nIndex, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nCount >= 0);
	Item		*pItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(!pItem->IsCanLay())
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nMaxLayedNum = pItem->GetMaxLayedNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nCount > nMaxLayedNum)
	{
		KCheck(0);
		return FALSE;
	}

	pItem->m_pItem->SetItemCount(nCount);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::DecItemLayedNum(int32 nIndex, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(!pItem->IsCanLay())
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nCurLayedNum = pItem->GetLayedNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nCurLayedNum < nCount)
	{
		KCheck(0);
	}

	pItem->m_pItem->DecCount(nCount);

	if(pItem->GetLayedNum() <= 0)
	{
		pItem->Clear();
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::IncItemLayedNum(int32 nIndex, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(!pItem->IsCanLay())
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nMaxLayedNum = pItem->GetMaxLayedNum();
	int32	nCurLayedNum = pItem->GetLayedNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nCurLayedNum + nCount > nMaxLayedNum)
	{
		KCheck(0);
		return FALSE;
	}

	return pItem->m_pItem->IncCount(nCount);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::EraseItem(uint32 uIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pItem = GetItem(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->GetDataType() == IDT_PET)
	{
		ResetHorseStallOrder(pItem->m_pPet->m_iStallOrder);
	}

	pItem->Clear();

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemDurability(int32 nIndex, int32 nDur)
{
	__GUARD__ KCheck(0);

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemDamagePoint(int32 nIndex, int32 nPoint)
{
	__GUARD__ KCheck(0);

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemCurMaxDur(int32 nIndex, int32 nDur)
{
	__GUARD__ KCheck(0);

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemValue(int32 nIndex, SItem *pItem)
{
	__GUARD__	KCheck(0);

	return FALSE;	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemValue(int32 nIndex, const _HORSE_DB_LOAD *pPet)
{
	__GUARD__	KCheck(0);

	return FALSE;	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemBind(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	pDestItem->m_pItem->SetItemBindType(BIND_NORMAL);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemIdent(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pDestItem->GetItemClass() == ICLASS_EQUIP, "非装备不能增加装备属性");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	AttrCount = pDestItem->m_pItem->GetEquipData()->m_AttrCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(AttrCount < MAX_ITEM_ATTR)
	{
		KCheck(0);
		return FALSE;
	}

	pDestItem->m_pItem->GetEquipData()->m_pAttr[AttrCount] = iA;

	pDestItem->m_pItem->GetEquipData()->m_AttrCount++;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KCheck(0);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::DelGemInfo(int32 nIndex, int32 GemIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KCheck(0);
	return FALSE;
	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KCheck(0);
	
	return FALSE;
	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::AddHole(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ KCheck(0);
	
	return FALSE;
	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::Bind(int32 nIndex, uchar bindType)
{
	__GUARD__	KCheck(FALSE);
	
	return FALSE;
	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::ItemLevelup(int32 nIndex, int32 nLevel)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::EquipHonorBindLevelup(int32 nIndex, int32 nLevel)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemPaiType(int32 nIndex, uchar nPaiType)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::ItemLevelBind(int32 nIndex, uint32 nBindLevel)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemScore(int32 nIndex, uint32 nScore)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetEquipFromType(int32 nIndex, uchar nType)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemBeginTime(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::LockEquip(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::UnLockEquip(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemGuid(int32 nIndex, SItemGuid *pGUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(!pGUID)
	{
		KCheck(pGUID);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_ITEM);

	pDestItem->m_pItem->m_ItemGUID = *pGUID;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetName(int32 nIndex, const char *pName)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetNick(int32 nIndex, const char *pNick)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetLevel(int32 nIndex, int32 level)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetTakeLevel(int32 nIndex, int32 takeLevel)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetAttackType(int32 nIndex, int32 attackType)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetBHVClass(int32 nIndex, int32 BHVClass)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetCampData(int32 nIndex, const SCampData *pCamp)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetItemGuid(int32 nIndex, SHorseGuid*pGUID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(!pGUID)
	{
		KCheck(pGUID);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);

	pDestItem->m_pPet->m_GUID = *pGUID;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetHorseGUID(int32 nIndex, SHorseGuid GUID)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetDataID(int32 nIndex, int32 ID)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetPetType(int32 nIndex, uchar PetType)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::Set_Property_Generation(int32 nIndex, uchar Gen)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetHappiness(int32 nIndex, uchar byHappiness)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetStrengthPer(int32 nIndex, int32 strper)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetSmartnessPer(int32 nIndex, int32 conper)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetMindPer(int32 nIndex, int32 dexper)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetConstitutionPer(int32 nIndex, int32 intper)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::Set_Property_GrowRate(int32 nIndex, float rate)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetRemainPoint(int32 nIndex, int32 rPoint)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetMatingFlag(int32 iIndex, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	if(bFlag) 
		pDestItem->m_pPet->m_iStatus  = _HORSE_DB::PET_STATUS_MATING;
	else
		pDestItem->m_pPet->m_iStatus  = _HORSE_DB::PET_STATUS_NULL;

	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetComposeFlag(int32 iIndex, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	if(bFlag) 
		pDestItem->m_pPet->m_iStatus  = _HORSE_DB::PET_STATUS_COMPOSE;
	else
		pDestItem->m_pPet->m_iStatus  = _HORSE_DB::PET_STATUS_NULL;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetStrengthPoint(int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	pDestItem->m_pPet->m_iStrengthPoint = iPoint;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetSmartnessPoint(int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	pDestItem->m_pPet->m_iSmartnessPoint = iPoint;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetMindPoint(int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	pDestItem->m_pPet->m_iMindPoint = iPoint;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetConstitutionPoint(int32 nIndex, int32 iPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	pDestItem->m_pPet->m_iConstitutionPoint = iPoint;

	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::ForceLockPet(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}
BOOL ItemContainer::ForceUnlockPet(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::LockPet(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::UnlockPet(int32 nIndex)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::IsCanUse()
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::IsValid()
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetItemPWLock(int32 nIndex, BOOL bLock)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetItemCreator(int32 nIndex, const char *CreatorName)
{
	__GUARD__ KCheck(0);

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ItemContainer::SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value)
{
	__GUARD__ 	KCheck(FALSE);

	return FALSE;

	__UNGUARD__ return FALSE;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetExp(int32 nIndex, uint32 exp)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetLvl1Property(int32 nIndex, PLAYER_PROPERTY_LEVEL1 type, int32 value)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::SetSkill(int32 nIndex, uint32 SkillIndex, SHorseSkill skill)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemContainer::IsInContainer(uint32 uBagIndex)
{
	__GUARD__ if(uBagIndex >= 0 && uBagIndex < (uint32) m_nContainerSize)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 重置宠物栏位顺序
 =======================================================================================================================
 */
BOOL ItemContainer::ResetHorseStallOrder(int32 nDeleteOrder)
{
	if( GetContainerType() != ICT_HUMAN_PET_CONTAINER ) 
		return FALSE;

	if( nDeleteOrder < 0 || nDeleteOrder >= PLAYER_PET_MAX_COUNT ) 
		return FALSE;

	if( nDeleteOrder == PLAYER_PET_MAX_COUNT - 1 ) 
		return TRUE;

	for( int32 i = 0; i < m_nContainerSize; i++ )
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		Item *itemHorse = GetItem(i);
		if( NULL != itemHorse )
		{
			if( itemHorse->m_pPet->m_iStallOrder > nDeleteOrder ) 
				itemHorse->m_pPet->m_iStallOrder--;
		}
	}

	return TRUE;
}

/*
 =======================================================================================================================
 取得有效数量
 =======================================================================================================================
 */
int32 ItemContainer::GetValidCount()
{
	int32 count = 0;
	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(!m_aItem[i].IsFree())
		{
			count++;
		}
	}

	return count;
}

/*
 =======================================================================================================================
 栏位值到索引的转换
 =======================================================================================================================
 */
int32 ItemContainer::StallOrderToIndex(int32 iStallOrder)
{
	for(int32 i = 0; i < m_nContainerSize; i++)
	{
		if(m_aItem[i].IsFree())
		{
			continue;
		}

		Item *itemHorse = GetItem(i);
		if(NULL != itemHorse)
		{
			if(itemHorse->m_pPet->m_iStallOrder == iStallOrder) 
				return i;
		}
	}

	return INVALID_ID;
}

/*
 =======================================================================================================================
 设置银行骑乘栏位值
 =======================================================================================================================
 */
void ItemContainer::SetBankPetStallOrder(int32 nIndex, int32 iStallOrder)
{
	Item *pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
	}

	if(pDestItem->m_bLock)
	{
		KCheck(0);
	}

	KCheck(pDestItem->m_Type == IDT_PET);
	pDestItem->m_pPet->m_iStallOrder = iStallOrder;
}
