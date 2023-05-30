/*$T MapServer/Server/Item/PlayerBaseContainer.cpp GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_PlayerBaseContainer.h"
#include "Archive/PlayerDB.h"


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemLayedNum(int32 nIndex, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck( nCount>= 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

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

	if(pItem->IsLock())
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

	if ( pItem->GetItemData() )
		pItem->GetItemData()->SetItemCount(nCount);

	SetDBDirty(nIndex);

	return TRUE;
	__UNGUARD__ return FALSE;
}



/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::DecItemLayedNum(int32 nIndex, int32 nCount)
{
	__GUARD__ if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	Item	*pItem = GetItem(nIndex);

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

	if(pItem->IsLock())
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

	if ( pItem->GetItemData() )
		pItem->GetItemData()->DecCount(nCount);

	if(pItem->GetLayedNum() <= 0)
	{
		ClearItemByIndex(nIndex);
	}

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::IncItemLayedNum(int32 nIndex, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	Item	*pItem = GetItem(nIndex);

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

	if(pItem->IsLock())
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

	if ( pItem->GetItemData() == NULL )
		return FALSE;

	BOOL	bRet = pItem->GetItemData()->IncCount(nCount);

	if(bRet)
	{
		SetDBDirty(nIndex);
	}

	return bRet;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetDBDirty(int32 OffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(OffSet >= 0);
	KCheck(OffSet < m_nContainerSize);

	switch(m_ICTType)
	{
	case ICT_BASE_CONTAINER:
		{
			m_pPlayerDB->SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) (CPROPERTY_ARCHIVE_BAG_BEGIN + OffSet));
		}
		break;

	case ICT_EQUIP_CONTAINER:
		{
			m_pPlayerDB->SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) (CPROPERTY_ARCHIVE_EQUIP_BEGIN + OffSet));
		}
		break;

	case ICT_BANK_CONTAINER:
		{
			m_pPlayerDB->SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) (CPROPERTY_ARCHIVE_BANK_BEGIN + OffSet));
		}
		break;

	default:
		{
			KCheckEx(FALSE, "无效容器类型");
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
BOOL PlayerBaseContainer::Init(const SItemContainerInit *pInit)
{
	__GUARD__ if(!ItemContainer::Init(pInit)) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SPlayerContainerInit	*pHICInit = static_cast<const SPlayerContainerInit *>(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pHICInit == NULL) return FALSE;

	KCheck(pHICInit->m_pPlayerDB);

	m_ICTType = pHICInit->m_ICTType;
	m_pPlayerDB = pHICInit->m_pPlayerDB;
	m_DBOffSet = pHICInit->m_DBOffSet;
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::IsInContainer(uint32 uBagIndex)
{			  
	__GUARD__ if(uBagIndex >= m_DBOffSet && uBagIndex < GetContainerSize() + m_DBOffSet) return TRUE;
	else
		return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 PlayerBaseContainer::ConIndex2BagIndex(uint32 uConIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	if ( uConIndex >= (uint32) GetContainerSize() )
	{
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"PlayerBaseContainer::ConIndex2BagIndex: uConIndex=%d ,ContainerSize=%d",uConIndex,GetContainerSize());
	}
		KCheck(uConIndex < (uint32) GetContainerSize());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_DBOffSet + uConIndex;

	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 PlayerBaseContainer::BagIndex2ConIndex(uint32 uBagIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uBagIndex >= m_DBOffSet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uBagIndex < m_DBOffSet + GetContainerSize());
	
	return uBagIndex - m_DBOffSet;

	__UNGUARD__ return INVALID_INDEX;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItem(const int32 nIndex, const Item *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);

	KCheck(pItem);

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	BOOL		bRet = ItemContainer::SetItem(nIndex, pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		SetDBDirty(nIndex);
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::EraseItem(uint32 uIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(uIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	BOOL		bRet = ItemContainer::EraseItem(uIndex);

	if(bRet)
	{
		SetDBDirty(uIndex);
	}

	return bRet;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemDurability(int32 nIndex, int32 nDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pItem = GetItem(nIndex);

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pItem->GetItemClass() == ICLASS_EQUIP, "非装备不能设置耐久度");
		return FALSE;
	}

	if(nDur > pItem->GetCurMaxDurability())
	{
		KCheck(0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	nEquipPoint = pItem->GetEquipPoint();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if
		(
		nEquipPoint == HEQUIP_RING1
		||	nEquipPoint == HEQUIP_RING2
		||	nEquipPoint == HEQUIP_ADORN1
		||	nEquipPoint == HEQUIP_ADORN2
		)
	{
		return FALSE;
	}

	if ( pItem->GetItemData() )
		pItem->GetItemData()->GetEquipData()->m_CurDurPoint = nDur;

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemDamagePoint(int32 nIndex, int32 nPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}


	Item	*pItem = GetItem(nIndex);
	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pItem->GetItemClass() == ICLASS_EQUIP, "非装备不能设置损伤度");
		return FALSE;
	}

	if ( pItem->GetItemData() )
		pItem->GetItemData()->GetEquipData()->m_CurDamagePoint = nPoint;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemCurMaxDur(int32 nIndex, int32 nDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pItem->GetItemClass() == ICLASS_EQUIP, "非装备不能设置耐久度");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	nMaxDur = pItem->GetMaxDurPoint();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDur > nMaxDur)
	{
		QLogSystem::QUICK_LOG
			(
			QUICK_LOG_DEBUG,
			"SetItemCurMaxDur Item:%d, CurCur:%d, MaxDur:%d",
			nIndex,
			nDur,
			nMaxDur
			);
	}

	KCheckEx(nDur <= 255, "装备最大耐久度255");

	if ( pItem->GetItemData() )
		pItem->GetItemData()->GetEquipData()->m_CurMaxDur = nDur;

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemValue(int32 nIndex, SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);

	if (nIndex >= (uint32) GetContainerSize() )
	{
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"PlayerBaseContainer::SetItemValue: nIndex=%d, uConIndex=%d ,ContainerSize=%d",nIndex,ConIndex2BagIndex(nIndex),GetContainerSize());
	}

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	KCheck(!pItem->IsNullType());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	KCheck(pDestItem->GetDataType() == IDT_ITEM);
	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() )
	{
		memcpy(pDestItem->GetItemData(), pItem, sizeof(SItem));
		SetDBDirty(nIndex);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemBind(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = ItemContainer::SetItemBind(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		SetDBDirty(nIndex);
	}

	return bRet;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemIdent(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() )
		pDestItem->GetItemData()->SetItemIdent(TRUE);
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemCreator(int32 nIndex, const char *CreatorName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	BOOL	bRet = FALSE;

	if(pDestItem->GetDataType() == IDT_PET)
	{
		bRet = TRUE;
	}
	else if(pDestItem->GetDataType() == IDT_ITEM)
	{
		if ( pDestItem->GetItemData() )
		{
			pDestItem->GetItemData()->SetCreatorVar(TRUE);
			strncpy(pDestItem->GetItemData()->m_Creator, CreatorName, MAX_ITEM_CREATOR_NAME);
			pDestItem->GetItemData()->m_Creator[MAX_ITEM_CREATOR_NAME - 1] = '\0';
		}
		bRet = TRUE;
	}

	if(bRet)
	{
		SetDBDirty(nIndex);
	}

	return bRet;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	BOOL	bRet = FALSE;

	if(pDestItem->GetDataType() == IDT_PET)
	{
		bRet =  TRUE;
	}
	else if(pDestItem->GetDataType() == IDT_ITEM)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		eITEM_PARAM_VALUE ipv = (eITEM_PARAM_VALUE) type;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if ( pDestItem->GetItemData() )
			pDestItem->GetItemData()->SetItemFreeParam(start, ipv, value);
		bRet =  TRUE;
	}

	if(bRet)
	{
		SetDBDirty(nIndex);
	}

	return bRet;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pDestItem->GetItemClass() == ICLASS_EQUIP, "非装备不能增加装备属性");
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	AttrCount = pDestItem->GetItemData()->GetEquipData()->m_AttrCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(AttrCount < MAX_ITEM_ATTR)
	{
		KCheck(0);
		return FALSE;
	}

	pDestItem->GetItemData()->GetEquipData()->m_pAttr[AttrCount] = iA;
	pDestItem->GetItemData()->GetEquipData()->m_AttrCount++;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pDestItem->GetItemClass() == ICLASS_EQUIP, "非装备不能删除装备属性");
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	AttrCount = pDestItem->GetItemData()->GetEquipData()->m_AttrCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(AttrCount == 0)
	{
		KCheck(0);
		return FALSE;
	}

	for(int32 iAttrIndex = 0; iAttrIndex < AttrCount; iAttrIndex++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_ITEM_PROPERTY	EquipAttr = pDestItem->GetItemData()->GetEquipData()->m_pAttr[iAttrIndex];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(EquipAttr == iA)
		{
			pDestItem->GetItemData()->GetEquipData()->m_pAttr[iAttrIndex] = pDestItem->GetItemData()->GetEquipData()->m_pAttr[AttrCount - 1];
			pDestItem->GetItemData()->GetEquipData()->m_pAttr[AttrCount - 1].Clear();
		}
	}

	pDestItem->GetItemData()->GetEquipData()->m_AttrCount--;

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemHolePos)
{
	__GUARD__ if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	KCheck(GemHolePos < pDestItem->GetItemData()->GetEquipData()->m_CurGemHole);

	if(pDestItem->GetItemData()->GetEquipData()->m_pGemInfo[GemHolePos].m_GemIndex == INVALID_ITEM_ID)
		++pDestItem->GetItemData()->GetEquipData()->m_StoneCount;
	pDestItem->GetItemData()->GetEquipData()->m_pGemInfo[GemHolePos].m_GemIndex = GemIndex;

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::DelGemInfo(int32 nIndex, int32 GemIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheckEx(pDestItem->GetItemClass() == ICLASS_EQUIP, "非装备不能删除宝石");
		return FALSE;
	}

	if(GemIndex > pDestItem->GetCurGemHole())
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	pDestItem->GetItemData()->GetEquipData()->m_pGemInfo[GemIndex].m_GemIndex = 0;
	--(pDestItem->GetItemData()->GetEquipData()->m_StoneCount);
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::AddHole(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~*/
	BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~*/

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetCurGemHole() >= MAX_GEM_HOLE) return FALSE;

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	++pDestItem->GetItemData()->GetEquipData()->m_CurGemHole;

	if(pDestItem->GetItemData()->GetEquipData()->m_CurGemHole >= MAX_GEM_HOLE)
	{
		pDestItem->GetItemData()->GetEquipData()->m_CurGemHole = MAX_GEM_HOLE;
	}

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::Bind(int32 nIndex, uchar bindType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(bindType < BIND_INVALID);

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item		*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	if(bindType > 0)
	{
		if(pDestItem->GetItemData()->m_nsBind > 0)
		{
			if(pDestItem->GetItemData()->m_nsBind != BIND_NORMAL)
			{
				pDestItem->GetItemData()->SetItemBindType(bindType);
			}
		}
		else
			pDestItem->GetItemData()->SetItemBindType(bindType);
	}

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::ItemLevelup(int32 nIndex, int32 nLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalLevel = pDestItem->GetItemData()->GetEquipData()->m_Level + nLevel;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((nFinalLevel > MAX_EQUIP_LEVELUP_NUM) || (nFinalLevel < 0))
	{
		return FALSE;
	}

	pDestItem->GetItemData()->GetEquipData()->m_Level = nFinalLevel;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::EquipHonorBindLevelup(int32 nIndex, int32 nLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFinalLevel = pDestItem->GetItemData()->GetEquipData()->GetHonorBindLevel() + nLevel;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((nFinalLevel > MAX_EQUIP_HONOR_BIND_LEVEL) || (nFinalLevel < 0))
	{
		return FALSE;
	}

	pDestItem->GetItemData()->GetEquipData()->SetHonorBindLevel((uchar)nFinalLevel);


	if(FALSE == pDestItem->GetItemData()->IsNormalBound())
	{
		pDestItem->GetItemData()->SetItemBindType(BIND_NORMAL);
	}

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~*/
	BOOL bRet = FALSE;
	/*~~~~~~~~~~~~~~*/

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	KCheck(nAtt < pDestItem->GetItemData()->GetEquipData()->m_AttrCount);
	pDestItem->GetItemData()->GetEquipData()->m_pAttr[nAtt].m_AttrType = iA.m_AttrType;
	pDestItem->GetItemData()->GetEquipData()->m_pAttr[nAtt].m_Value.m_Value = iA.m_Value.m_Value;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemPaiType(int32 nIndex, uchar nPaiType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	switch(nPaiType)
	{
	case 0:
	case EQUIPPAI_ANY:
	case EQUIPPAI_ANYFENG:
	case EQUIPPAI_ANYJIAN:
	case EQUIPPAI_ANYZI:
	case EQUIPPAI_ANYFEIZI:
	case EQUIPPAI_ANYTIAO:
	case EQUIPPAI_ANYTONG:
	case EQUIPPAI_ANYWAN:
	case EQUIPPAI_ANYSHUN:
	case EQUIPPAI_ANYKE:
	case EQUIPPAI_ANYJIANG:
	case EQUIPPAI_DONG:
	case EQUIPPAI_NAN:
	case EQUIPPAI_XI:
	case EQUIPPAI_BEI:
	case EQUIPPAI_ZHONG:
	case EQUIPPAI_FA:
	case EQUIPPAI_BAI:
	case EQUIPPAI_1TIAO:
	case EQUIPPAI_2TIAO:
	case EQUIPPAI_3TIAO:
	case EQUIPPAI_4TIAO:
	case EQUIPPAI_5TIAO:
	case EQUIPPAI_6TIAO:
	case EQUIPPAI_7TIAO:
	case EQUIPPAI_8TIAO:
	case EQUIPPAI_9TIAO:
	case EQUIPPAI_1TONG:
	case EQUIPPAI_2TONG:
	case EQUIPPAI_3TONG:
	case EQUIPPAI_4TONG:
	case EQUIPPAI_5TONG:
	case EQUIPPAI_6TONG:
	case EQUIPPAI_7TONG:
	case EQUIPPAI_8TONG:
	case EQUIPPAI_9TONG:
	case EQUIPPAI_1WAN:
	case EQUIPPAI_2WAN:
	case EQUIPPAI_3WAN:
	case EQUIPPAI_4WAN:
	case EQUIPPAI_5WAN:
	case EQUIPPAI_6WAN:
	case EQUIPPAI_7WAN:
	case EQUIPPAI_8WAN:
	case EQUIPPAI_9WAN:
		pDestItem->GetItemData()->GetEquipData()->m_PaiType = nPaiType;
		break;

	default:
		{
			KCheck(0);
			return FALSE;
		}
	}

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::ItemLevelBind(int32 nIndex, uint32 nBindLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(nBindLevel <= MAX_EQUIP_BIND_LEVEL);

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	pDestItem->GetItemData()->GetEquipData()->SetSoulBindLevel((uchar)nBindLevel);
	if(nBindLevel > 0)
	{
		if(!pDestItem->GetItemData()->IsNormalBound())
		{
			pDestItem->GetItemData()->SetItemBindType(BIND_NORMAL);
		}
	}

	SetDBDirty(nIndex);
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemScore(int32 nIndex, uint32 nScore)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	pDestItem->GetItemData()->GetEquipData()->m_EquipScore = nScore;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetEquipFromType(int32 nIndex, uchar nType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);  
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetItemClass() != ICLASS_EQUIP)
	{
		KCheck(0);
		return FALSE;
	}

	KCheck(nType < ITEM_NUM);


	if ( pDestItem->GetItemData() == NULL )
		return FALSE;

	pDestItem->GetItemData()->GetEquipData()->m_EquipType = nType;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::SetItemPWLock(int32 nIndex, BOOL bLock)
{
	__GUARD__ 

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);

	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if(pDestItem->GetDataType() == IDT_PET)
	{
		KCheck(0);
		return TRUE;
	}
	else if(pDestItem->GetDataType() == IDT_ITEM)
	{
		if ( pDestItem->GetItemData() )
			pDestItem->GetItemData()->SetItemPLock(bLock);
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::LockEquip(int32 nIndex)
{
	__GUARD__

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() )
		pDestItem->GetItemData()->GetEquipData()->m_byLock = ITEM_LOCK;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerBaseContainer::UnLockEquip(int32 nIndex)
{
	__GUARD__ 
		
	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return FALSE;
	}

	if(!IsCanUse())
	{
		return FALSE;
	}

	Item	*pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	if ( pDestItem->GetItemData() )
	{
		pDestItem->GetItemData()->GetEquipData()->m_byLock = ITEM_UNLOCKING;
		pDestItem->GetItemData()->GetEquipData()->m_UnLockTime = GET_TIME().GetCTime() + g_Config.m_ConfigInfo.m_ItemUnLockCDTime;
	}

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}


