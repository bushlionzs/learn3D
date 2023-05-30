#include "stdafx.h"
#include "Item_PlayerExtraBag.h"
#include "Archive/PlayerDB.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL PlayerExtraBag::Init(const SItemContainerInit *pInit)
{
	__GUARD__ if(!ItemContainer::Init(pInit)) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SPlayerItemExtrBagInit *pHICInit = static_cast<const SPlayerItemExtrBagInit *>(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pHICInit == NULL) return FALSE;

	KCheck(pHICInit->m_pPlayerDB);
	KCheck(pHICInit->m_pExtraBagItem);
	m_ICTType = pHICInit->m_ICTType;
	m_pPlayerDB = pHICInit->m_pPlayerDB;
	m_pExtraBagItem = pHICInit->m_pExtraBagItem;
	m_DBOffSet = pHICInit->m_DBOffSet;
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerExtraBag::IsInContainer(uint32 uBagIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(IsValid());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pExtraBagItem->GetItemClass() == ICLASS_EXTRABAG);
	return PlayerBaseContainer::IsInContainer(uBagIndex);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerExtraBag::IsCanUse()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(IsValid());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pExtraBagItem->GetItemClass() == ICLASS_EXTRABAG);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerExtraBag::IsValid()
{
	__GUARD__ if(m_pExtraBagItem->IsFree())
	{
		return FALSE;
	}

	KCheck(m_pExtraBagItem->GetItemClass() == ICLASS_EXTRABAG);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 PlayerExtraBag::GetContainerSize()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(IsValid());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pExtraBagItem->GetItemClass() == ICLASS_EXTRABAG);
	return m_pExtraBagItem->GetExtraBagSize();

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item *PlayerExtraBag::GetItem(const int32 nIndex)
{
	__GUARD__ 
	
	if ( nIndex >= (uint32) GetContainerSize() )
	{
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"PlayerExtraBag::GetItem: nIndex=%d ,ContainerSize=%d",nIndex,GetContainerSize());
	}

	if(!IsInContainer(ConIndex2BagIndex(nIndex)))
	{
		KCheck(0);
		return NULL;
	}

	return ItemContainer::GetItem(nIndex);

	__UNGUARD__ return NULL;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerExtraBag::SetDBDirty(int32 OffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(OffSet >= 0);
	KCheck(OffSet < m_nContainerSize);

	switch(m_ICTType)
	{
	case ICT_BASEBAG_CONTAINER:
	case ICT_EXTRABAG_CONTAINER:
	case ICT_BASE_CONTAINER:
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

