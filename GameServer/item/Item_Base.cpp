#include "stdafx.h"
#include "Item_Base.h"
#include "Item_Ruler.h"
#include "StructDB.h"
#include "data/data_manager.h"
#include "share/TAB/TabDefine_Map_Pet.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */

Item::Item()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pPet = NULL;
	m_bLock = FALSE;
	m_bIsInExchange = FALSE;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Item::~Item()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pPet = NULL;
	m_bLock = FALSE;
	m_bIsInExchange = FALSE;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::Init(const CItemInit *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pItem = const_cast<SItem *>(pInit->m_pItem);
	m_pPet = const_cast<_HORSE_DB_LOAD *>(pInit->m_pPet);

	KCheck((m_pItem != 0) || (m_pPet != 0));
	KCheck(!(m_pItem == 0 && m_pPet == 0));
	KCheck(!(m_pItem != 0 && m_pPet != 0));

	if(m_pItem) m_Type = IDT_ITEM;
	if(m_pPet) m_Type = IDT_PET;

	m_bLock = FALSE;

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Item::Clear()
{
	__GUARD__ if(m_pItem)
	{
		memset(m_pItem, 0, sizeof(SItem));
	}

	if(m_pPet)
	{
		m_pPet->Clear();
	}

	m_bLock = FALSE;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::IsFree()
{
	__GUARD__ switch(m_Type)
	{
	case IDT_ITEM:
		{
			if(m_pItem == NULL)
			{
				KCheck(FALSE);
				return TRUE;
			}

			if(m_pItem->IsNullType()) return TRUE;
		}
		break;

	case IDT_PET:
		{
			if(m_pPet == NULL)
			{
				KCheck(FALSE);
				return TRUE;
			}

			if(TRUE == m_pPet->m_GUID.IsNull()) return TRUE;
		}
		break;

	default:
		{
			KCheck(FALSE);
			return TRUE;
		}
	}

	return FALSE;

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::IsEquip() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		bClass = m_pItem->ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bClass == ICLASS_EQUIP) return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::IsCanLay() const
{
	__GUARD__ switch(m_Type)
	{
	case IDT_ITEM:	{ KCheck(m_pItem); return CheckItemRuler::CheckRuler(IRL_TILE, GetRuler()); }break;
	case IDT_PET:	{ KCheck(m_pPet); return FALSE; }break;
	default:	{ KCheck(FALSE); return FALSE; }
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::IsCanEquipBind() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		nRuleID = GetRuler();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return CheckItemRuler::CheckRuler(IRL_EQUIPBIND, nRuleID);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::IsRuler(eITEM_RULER_LIST ruler) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return CheckItemRuler::CheckRuler(ruler, GetRuler());

	__UNGUARD__ return FALSE;
}


/*
 =======================================================================================================================
 =======================================================================================================================*/

BOOL Item::IsBound() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pItem->IsNormalBound();

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL Item::IsNormalBound() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pItem->IsNormalBound();

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL Item::IsGoldBound() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pItem->IsGoldBound();

	__UNGUARD__ return FALSE;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Item::SaveValueTo(SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pItem);

	memcpy(pItem, m_pItem, sizeof(SItem));

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Item::SaveValueTo(_HORSE_DB_LOAD *pPet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pPet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pPet);
	memcpy(pPet, m_pPet, sizeof(_HORSE_DB_LOAD));

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Item::GetItemFreeParam(uint32 start, eITEM_PARAM_VALUE &ipv)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pItem->GetItemFreeParamValue(start, ipv);

	__UNGUARD__ return -1;
}

void Item::SetItemFreeParam(uint32 start, eITEM_PARAM_VALUE &ipv, int32 value)
{
    __GUARD__;

    KCheck( m_pItem);

    m_pItem->SetItemFreeParam( start, ipv, value);

    __UNGUARD__;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Item::SetItemValue(SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pItem);
	*m_pItem = *pItem;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Item::SetTermTime(uint32 newTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pItem->m_TermEndTime = newTime;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item::IsCanExchange()
{
	__GUARD__ switch(m_Type)
	{
	case IDT_ITEM:
		{
			return CheckItemRuler::CheckRuler(IRL_CANEXCHANGE, GetRuler());
		}
		break;

	case IDT_PET:
		{
			KCheck(m_pPet->m_nDataID < MAX_HORSE_TYPE);
			return DataManager::GetSingletonPtr()->getHorseAttr(m_pPet->m_nDataID)->m_bIsFixedHold;
		}
		break;

	default:
		{
			KCheck(FALSE);
			return FALSE;
		}
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}
uchar Item::GetPurplePropertyCount() const
{
	KCheck(m_pItem);

	SEquipInfo * pEquipData = m_pItem->GetEquipData();
	KCheck(pEquipData);

	uchar uPurpleAttrCount = 0;
	for (int i =0;i < pEquipData->m_AttrCount;++i)
	{
		if (pEquipData->m_pAttr[i].m_AttrType >= IPROPERTY_POINT_STR_PURPLE && pEquipData->m_pAttr[i].m_AttrType <= IPROPERTY_SPEED_MOVE_PURPLE)
		{
			++uPurpleAttrCount;
		}
	}

	return uPurpleAttrCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar Item::GetColorType() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pItem->ItemClass() == ICLASS_EQUIP);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SEquipTab	*pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pEquipTable)
	{
		return pEquipTable->m_Color;
	}

	KCheck(FALSE);

	__UNGUARD__ return 0;
}

void STradeItemList::AddItem( Item *it )
{
	int32	i;

	for(i = 0; i < EXCHANGE_BOX_SIZE + EXCHANGE_PET_BOX_SIZE; i++)
	{
		if(m_ListItem[i] == NULL)
		{
			break;
		}
	}

	if(i == EXCHANGE_BOX_SIZE + EXCHANGE_PET_BOX_SIZE)
	{
		KCheck(0);
		return;
	}

	m_ListCount++;
	m_ListItem[i] = it;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uchar Item::GetRuler() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	nType = GetItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(nType)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_RulerID;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	default:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~*/
			char	szMsg[64] = { 0 };
			/*~~~~~~~~~~~~~~~~~~~~~~*/

			tsnprintf_s(szMsg, 64, "ITEMCLASS=%u IS INVALID, ItemIndex=%u", nType, GetItemTableIndex());
			KCheckEx(0, szMsg);
		}
	}

	__UNGUARD__ return -1;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 Item::GetPrice() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		bClass = m_pItem->ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pEquipTable)
			{
				return pEquipTable->m_BasePrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pComTable)
			{
				return pComTable->m_nBasePrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pTaskTable = g_ItemTab.GetTaskItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTaskTable)
			{
				return pTaskTable->m_nBasePrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGemTable = g_ItemTab.GetGemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pGemTable)
			{
				return pGemTable->m_nPrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pExtraBagTable)
			{
				return pExtraBagTable->m_nBasePrice;
			}

			KCheck(FALSE);
		}

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);
	return -1;

	__UNGUARD__ return -1;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 Item::GetSellPrice() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		bClass = m_pItem->ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			uint32	BasePrice = GetPrice();
			uchar	MaxDurPoint = GetMaxDurPoint();
			float	nRate = ((float) 1 / 9) *
				(
				1 + 2 * (float)
				(
				m_pItem->GetEquipData()->m_CurDurPoint *
				m_pItem->GetEquipData()->m_CurMaxDur
				) / (float) (MaxDurPoint * MaxDurPoint)
				);
			float	fSellPrice = (float) BasePrice * nRate;
			uint32	nSellPrice = Float2Int(fSellPrice);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(fSellPrice > (float) nSellPrice)
			{
				nSellPrice += 1;
			}

			if(nSellPrice == 0) nSellPrice = 1;

			return nSellPrice;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pComTable)
			{
				return pComTable->m_nSellPrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pTaskTable = g_ItemTab.GetTaskItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTaskTable)
			{
				return pTaskTable->m_nSellPrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGemTable = g_ItemTab.GetGemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pGemTable)
			{
				return pGemTable->m_nSellPrice;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pExtraBagTable)
			{
				return pExtraBagTable->m_nSellPrice;
			}

			KCheck(FALSE);
		}
		break;

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);
	return -1;

	__UNGUARD__ return -1;
}



/*
=======================================================================================================================
=======================================================================================================================
*/
int32 Item::GetItemFreeParamType()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		bClass = m_pItem->ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_ParamType;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pComTable)
			{
				return pComTable->m_ParamType;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pTaskTable = g_ItemTab.GetTaskItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTaskTable)
			{
				return pTaskTable->m_ParamType;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGemTable = g_ItemTab.GetGemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pGemTable)
			{
				return pGemTable->m_ParamType;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pExtraBagTable)
			{
				return pExtraBagTable->m_ParamType;
			}

			KCheck(FALSE);
		}
		break;

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);
	return -1;

	__UNGUARD__ return -1;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 Item::GetItemTableParamValue()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		bClass = m_pItem->ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_ParamValue;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pComTable)
			{
				return pComTable->m_ParamValue;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pTaskTable = g_ItemTab.GetTaskItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTaskTable)
			{
				return pTaskTable->m_ParamValue;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGemTable = g_ItemTab.GetGemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pGemTable)
			{
				return pGemTable->m_ParamValue;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pExtraBagTable)
			{
				return pExtraBagTable->m_ParamValue;
			}

			KCheck(FALSE);
		}
		break;

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);
	return -1;

	__UNGUARD__ return -1;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 Item::GetConsumeValue()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pItem);
	uchar		bClass = m_pItem->ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(GetItemTableIndex());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_ConsumeValue;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pComTable)
			{
				return pComTable->m_ConsumeValue;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pTaskTable = g_ItemTab.GetTaskItemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTaskTable)
			{
				return pTaskTable->m_ConsumeValue;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGemTable = g_ItemTab.GetGemInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pGemTable)
			{
				return pGemTable->m_ConsumeValue;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pExtraBagTable)
			{
				return pExtraBagTable->m_ConsumeValue;
			}

			KCheck(FALSE);
		}
		break;

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);
	return 0;

	__UNGUARD__ return 0;
}

