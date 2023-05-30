/*$T MapServer/Server/Item/PlayerExtraBagContainer.cpp GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_PlayerExtraBagContainer.h"
#include "Archive/PlayerDB.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL PlayerExtraBagContainer::Init(const SItemContainerInit *pInit)
{
	__GUARD__ if(!ItemContainer::Init(pInit)) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SPlayerItemExtraContainerInit	*pHICInit = static_cast<const SPlayerItemExtraContainerInit *>(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
BOOL PlayerExtraBagContainer::SetItem(const int32 nIndex, const Item *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	KCheck(pItem);
	KCheck(nIndex < (int32) m_DBOffSet + m_nContainerSize);
	KCheck(pItem->GetItemClass() == ICLASS_EXTRABAG);
	
	return PlayerBaseContainer::SetItem(nIndex,pItem);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerExtraBagContainer::SetItemValue(int32 nIndex, SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	KCheck(nIndex < (int32) m_DBOffSet + m_nContainerSize);
	KCheck(pItem->ItemClass() == ICLASS_EXTRABAG);

	return PlayerBaseContainer::SetItemValue(nIndex,pItem);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerExtraBagContainer::SetItemBeginTime(int32 nIndex)
{
	__GUARD__ 

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

	if ( pDestItem->GetItemData() == NULL )
	 return FALSE;

	KCheck(pDestItem->GetItemData()->ItemClass() == ICLASS_EXTRABAG);
	KCheck(pDestItem->GetItemData()->GetExtraBagData()->m_nBeginTime = INVALID_TIME);

	pDestItem->GetItemData()->GetExtraBagData()->m_nBeginTime = (uint32) GET_TIME().GetCTime();
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemLayedNum(int32 nIndex, int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::DecItemLayedNum(int32 nIndex, int32 nCount)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::IncItemLayedNum(int32 nIndex, int32 nCount)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemDurability(int32 nIndex, int32 nDur)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemDamagePoint(int32 nIndex, int32 nPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemCurMaxDur(int32 nIndex, int32 nDur)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemIdent(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemFreeParam(int32 nIndex, uint32 start, int32 type, int32 value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::AddItemProperty(int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::DelItemProperty(int32 nIndex, _ITEM_PROPERTY iA)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::AddGemInfo(int32 nIndex, int32 GemIndex, uint32 GemType)
{
	__GUARD__ KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::DelGemInfo(int32 nIndex, int32 GemIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::AddHole(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::Bind(int32 nIndex, uchar bindType)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::ItemLevelup(int32 nIndex, int32 nLevel)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::EquipHonorBindLevelup(int32 nIndex, int32 nLevel)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemProperty(int32 nIndex, int32 nAtt, _ITEM_PROPERTY iA)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemPaiType(int32 nIndex, uchar nPaiType)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::ItemLevelBind(int32 nIndex, uint32 nBindLevel)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetItemScore(int32 nIndex, uint32 nScore)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetEquipFromType(int32 nIndex, uchar nType)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBagContainer::SetDBDirty(int32 OffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(OffSet >= 0);
	KCheck(OffSet < m_nContainerSize);

	switch(m_ICTType)
	{
	case ICT_EXTRA_CONTAINER:
		{
			m_pPlayerDB->SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) (CPROPERTY_ARCHIVE_BAG_BEGIN + m_DBOffSet + OffSet));
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
