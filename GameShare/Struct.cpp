/*$T Common/Struct.cpp GC 1.140 10/10/07 10:06:55 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "Struct.h"
#include "StructCountry.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

uchar GetClassBySerial(uint32_t Serial)
{
	return(uchar) (Serial / 1000000);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar GetTypeBySerial(uint32_t Serial)
{
	return(uchar) ((Serial % 1000000) / 10000);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetIndexBySerial(uint32_t Serial)
{
	return(Serial % 10000);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ISCommonEquip(uint32_t Serial)
{
	return(Serial % 10000) < 1000 ? TRUE : FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32_t GenMaterialIndex(uint32_t nMaterialType, uint32_t nMaterialLevel)
{
	KCheck(nMaterialType < 100);
	KCheck(nMaterialLevel <= MAX_MATERIAL_LEVEL);
	return(ICLASS_MATERIAL * 1000000) + (nMaterialType * 10000) + nMaterialLevel;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SItemType Serial2ItemType(uint32_t Serial)
{
	/*~~~~~~~~~~~~~~~*/
	SItemType	it;
	/*~~~~~~~~~~~~~~~*/

	it.m_Class = GetClassBySerial(Serial);
	it.m_Type = GetTypeBySerial(Serial);
	it.m_Index = GetIndexBySerial(Serial);

	return it;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetNewItemVarSize(const SItem &it)
{
	if(it.ItemClass() == ICLASS_EQUIP)
	{
		return SItemGuid::GetSize() + sizeof(uint32) + sizeof(int32) + sizeof(uchar);
	}
	else if(it.ItemClass() == ICLASS_GEM)
	{
		return SItemGuid::GetSize() + sizeof(uint32);
	}
	else if(it.ItemClass() == ICLASS_COMITEM)
	{
		return SItemGuid::GetSize() + sizeof(uint32);
	}
	else if(it.ItemClass() == ICLASS_MATERIAL)
	{
		return SItemGuid::GetSize() + sizeof(uint32);
	}
	else if(it.ItemClass() == ICLASS_TASKITEM)
	{
		return SItemGuid::GetSize() + sizeof(uint32);
	}
	else
		return SItemGuid::GetSize() + sizeof(uint32) + sizeof(char) + sizeof(int32) * MAX_ITEM_PARAM + sizeof(char);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetItemVarSize(const SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	CreatorSize = it.GetCreatorVar() ? (sizeof(char) * MAX_ITEM_CREATOR_NAME) : 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(it.ItemClass() == ICLASS_EQUIP)
	{
		return SItemGuid::GetSize() //m_ItemGUID
			+ sizeof(uint32) //m_ItemIndex
			+ sizeof(char)   //m_nsBind
			+ sizeof(int32) * MAX_ITEM_PARAM //m_Param[MAX_ITEM_PARAM]
			+ sizeof(int32)					//m_TermEndTime
			+ CreatorSize   // m_Creator[MAX_ITEM_CREATOR_NAME]
			+ sizeof(uchar)	* 10				//m_Bind;m_PaiType;m_EquipType;m_AttrCount;m_NeedLevel;m_Level;m_CurMaxDur;m_CurDurPoint;m_CurGemHole;m_StoneCount;
			+ sizeof(uint32)				//m_CurDamagePoint
			+ sizeof(uint16)				//m_EquipScore
			+ sizeof(SItemGemInfo) * MAX_ITEM_GEM // m_pGemInfo[MAX_ITEM_GEM]
			+ (sizeof(uchar) + sizeof(uchar) + sizeof(int16)) * it.GetEquipData()->m_AttrCount //m_pAttr[MAX_EQUIP_EXT_ATTR]
			+ sizeof(uchar) * 2   // m_byLock;m_ConstCount
			+ sizeof(uint32) //m_UnLockTime	
			+ (sizeof(uchar) + (sizeof(uchar) + sizeof(uchar) + sizeof(int16)) * CONST_ATTR_TYPE_NUMBER) * it.GetEquipData()->m_ConstCount;  //SItemConstInfo  m_pConst[MAX_EQUIP_CONST_ATTR]
		
	}
	else if(it.ItemClass() == ICLASS_GEM)
	{
		return SItemGuid::GetSize() //m_ItemGUID
			+ sizeof(uint32)		//m_ItemIndex
			+ sizeof(char)			//m_nsBind
			+ sizeof(int32) * MAX_ITEM_PARAM //m_Param[MAX_ITEM_PARAM]
			+ sizeof(int32)			//m_TermEndTime
			+ CreatorSize;			//m_Creator[MAX_ITEM_CREATOR_NAME]
	}
	else if(it.ItemClass() == ICLASS_COMITEM)
	{
		return SItemGuid::GetSize() + sizeof(uint32) + sizeof(char) + sizeof(int32) * MAX_ITEM_PARAM + sizeof(int32) + sizeof(uchar) + CreatorSize + sizeof(uchar);
	}
	else if(it.ItemClass() == ICLASS_MATERIAL)
	{
		return SItemGuid::GetSize()				//m_ItemGUID
			+ sizeof(uint32)					//m_ItemIndex
			+ sizeof(char)						//m_nsBind
			+ sizeof(int32) * MAX_ITEM_PARAM	//m_Param[MAX_ITEM_PARAM]
			+ sizeof(int32)						//m_TermEndTime
			+ sizeof(uchar)						//m_nCount
			+ CreatorSize						//m_Creator[MAX_ITEM_CREATOR_NAME]
			+ sizeof(uchar);					//m_Level
	}
	else if(it.ItemClass() == ICLASS_TASKITEM)
	{
		return SItemGuid::GetSize()				//m_ItemGUID
			+ sizeof(uint32)					//m_ItemIndex
			+ sizeof(char)						//m_nsBind
			+ sizeof(int32) * MAX_ITEM_PARAM	//m_Param[MAX_ITEM_PARAM]
			+ sizeof(int32)						//m_TermEndTime
			+ sizeof(uchar)						//m_nCount
			+ CreatorSize						//m_Creator[MAX_ITEM_CREATOR_NAME]
			+ sizeof(uchar);					//m_Level
	}
	else if(it.ItemClass() == ICLASS_EXTRABAG)
	{
		return SItemGuid::GetSize()            //m_ItemGUID 
			+ sizeof(uint32)		           //m_ItemIndex
			+ sizeof(char)			           //m_nsBind
			+ sizeof(int32) * MAX_ITEM_PARAM   //m_Param[MAX_ITEM_PARAM]
			+ sizeof(int32)					   //m_TermEndTime
			+ sizeof(int32)					   //m_nBeginTime
			+ CreatorSize;					  //m_Creator[MAX_ITEM_CREATOR_NAME]
	}
	else
	{
		return SItemGuid::GetSize() + sizeof(uint32) + sizeof(char) + sizeof(int32) * MAX_ITEM_PARAM + sizeof(int32) + CreatorSize;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SwapItem(SItem *pItemA, SItem *pItemB)
{
	KCheck(pItemA);
	KCheck(pItemB);

	/*~~~~~~~~~~~~~*/
	SItem	tempItem;
	/*~~~~~~~~~~~~~*/

	memcpy(&tempItem, pItemA, sizeof(SItem));
	memcpy(pItemA, pItemB, sizeof(SItem));
	memcpy(pItemB, &tempItem, sizeof(SItem));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::IsFixProperty(uchar attrType)
{
	switch(attrType)
	{
	case IPROPERTY_BASE_ATTACK_NEAR:
	case IPROPERTY_BASE_ATTACK_FAR:
	case IPROPERTY_BASE_ATTACK_M:
	case IPROPERTY_BASE_DEFENCE_NEAR:
	case IPROPERTY_BASE_DEFENCE_FAR:
	case IPROPERTY_BASE_DEFENCE_M:
		{
			return TRUE;
		}
		break;

	default:
		return FALSE;
	}
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar SItem::GetFixPropertyCount()
{
	return GetEquipData()->m_AttrCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar SItem::GetItemBindType() const
{
	//if(m_nsBind & IEI_GBIND_INFO)
	//	return BIND_GOLD;
	//else if(m_nsBind & IEI_PBIND_INFO)
	//{
	//	return BIND_NORMAL;
	//}

	//return BIND_NONE;
	//if(BIND_NORMAL == m_nsBind)
	//	return BIND_NORMAL;
	//if(BIND_GOLD == m_nsBind)
	//	return BIND_NONE;
	//return BIND_NONE;

	return m_nsBind;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SItem::SetItemBindType(uchar bBind)
{
	//if(bBind)
	//{
	//	m_nsBind |= IEI_PBIND_INFO;
	//}

	if(IEI_PBIND_INFO & bBind)
		m_nsBind |= IEI_PBIND_INFO;
	if(IEI_GBIND_INFO & bBind)
		m_nsBind |= IEI_GBIND_INFO;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SItem::IsNormalBound() const
{
	if(m_nsBind & IEI_PBIND_INFO)
	{
		return TRUE;
	}	
	return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SItem::IsGoldBound() const
{
	if(m_nsBind & IEI_GBIND_INFO)
	{
		return TRUE;
	}	
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::GetItemIdent() const
{
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SItem::SetItemIdent(BOOL bIdent)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::GetCreatorVar() const
{
	if(m_nsBind & IEL_CREATOR) return TRUE;
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SItem::SetCreatorVar(BOOL bCreator)
{
	if(bCreator)
		m_nsBind |= IEL_CREATOR;
	else
		m_nsBind &= (~(IEL_CREATOR));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::GetItemPLock() const
{
	if(m_nsBind & IEI_PLOCK_INFO) return TRUE;
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SItem::SetItemPLock(BOOL bLock)
{
	if(bLock)
		m_nsBind |= IEI_PLOCK_INFO;
	else
		m_nsBind &= (~(IEI_PLOCK_INFO));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SItem::GetItemFreeParamValue(uint32 Start, eITEM_PARAM_VALUE &ipv) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	TotalSize = sizeof(int32) * MAX_ITEM_PARAM;
	int32	size;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(ipv)
	{
	case IPV_CHAR:
		{
			size = 1;
			if(Start > (uint32) (TotalSize - size))
			{
				KCheck(FALSE);
			}

			return *((char *) m_Param + Start);
		}
		break;

	case IPV_SHORT:
		{
			size = 2;
			if(Start > (uint32) (TotalSize - size))
			{
				KCheck(FALSE);
			}

			return *((int16 *) ((char *) m_Param + Start));
		}
		break;

	case IPV_INT:
		{
			size = 4;
			if(Start > (uint32) (TotalSize - size))
			{
				KCheck(FALSE);
			}

			return *((int32 *) ((char *) m_Param + Start));
		}
		break;

	default:
		KCheck(FALSE);
	}

	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SItem::SetItemFreeParam(uint32 start, eITEM_PARAM_VALUE &ipv, int32 value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	TotalSize = sizeof(int32) * MAX_ITEM_PARAM;
	int32	size;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(ipv)
	{
	case IPV_CHAR:
		{
			size = 1;
			if(start > (uint32) (TotalSize - size))
			{
				KCheck(FALSE);
			}

			*((char *) m_Param + start) = (char) value;
		}
		break;

	case IPV_SHORT:
		{
			size = 2;
			if(start > (uint32) (TotalSize - size))
			{
				KCheck(FALSE);
			}

			*((int16 *) ((char *) m_Param + start)) = (int16) value;
		}
		break;

	case IPV_INT:
		{
			size = 4;
			if(start > (uint32) (TotalSize - size))
			{
				KCheck(FALSE);
			}

			*((int32 *) ((char *) m_Param + start)) = (int32) value;
		}
		break;

	default:
		KCheck(FALSE);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::WriteFixProperty(char *pIn, int32 BuffLength)
{
	KCheck(pIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	bClass = ItemClass();
	char	*pBuff = pIn;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nsBind = *((uchar *) pBuff);
	pBuff += sizeof(uchar);

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			GetEquipData()->m_AttrCount = *((uchar *) pBuff);
			pBuff += sizeof(uchar);

			for(int32 i = 0; i < GetEquipData()->m_AttrCount; i++)
			{
				GetEquipData()->m_pAttr[i].m_AttrType = *((uchar *) pBuff);
				pBuff += sizeof(uchar);

				GetEquipData()->m_pAttr[i].m_Value.m_Value = *((int16 *) pBuff);
				pBuff += sizeof(int16);
			}
		}
		break;

	case ICLASS_GEM:
		{
		}
		break;

	case ICLASS_COMITEM:
	case ICLASS_MATERIAL:
	case ICLASS_TASKITEM:
		{
		}
		break;

	default:
		{
			KCheck(FALSE);
		}
	}

	KCheck(BuffLength >= (pBuff - pIn));

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::ReadFixProperty(char *pOut, int32 &OutLength, int32 BuffLength)
{
	KCheck(pOut);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	bClass = ItemClass();
	char	*pBuff = pOut;
	uchar	FixAttrCount = GetFixPropertyCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*((uchar *) pBuff) = m_nsBind;
	pBuff += sizeof(uchar);

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			*((uchar *) pBuff) = GetEquipData()->m_AttrCount;
			pBuff += sizeof(uchar);

			for(int32 i = 0; i < FixAttrCount; i++)
			{
				*((uchar *) pBuff) = GetEquipData()->m_pAttr[i].m_AttrType;
				pBuff += sizeof(uchar);

				*((int16 *) pBuff) = GetEquipData()->m_pAttr[i].m_Value.m_Value;
				pBuff += sizeof(int16);
			}
		}
		break;

	case ICLASS_GEM:
		{
		}
		break;

	case ICLASS_COMITEM:
	case ICLASS_MATERIAL:
	case ICLASS_TASKITEM:
		{
		}
		break;

	default:
		{
			KCheck(FALSE);
		}
	}

	OutLength = (int32) (pBuff - pOut);
	KCheck(BuffLength >= OutLength);

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::WriteRandomProperty(char *pIn, int32 BuffLength)
{
	KCheck(pIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	bClass = ItemClass();
	char	*pBuff = pIn;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nsBind = *pBuff;
	pBuff++;

	m_TermEndTime = *((uint32 *) pBuff);
	pBuff += sizeof(uint32);



	switch(bClass)
	{
	case ICLASS_EQUIP:
		{

		SEquipInfo* pEquipInfo = GetEquipData();
		pEquipInfo->m_NeedLevel = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_Bind = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_PaiType = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_EquipType = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_EquipScore = *((uchar *) pBuff);
			pBuff += sizeof(uint32);
			pEquipInfo->m_Level = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_CurMaxDur = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_CurDurPoint = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
			pEquipInfo->m_CurDamagePoint = *((uint16 *) pBuff);
			pBuff += sizeof(uint16);

			pEquipInfo->m_CurGemHole = *((uchar *) pBuff);
			pBuff += sizeof(uchar);

			pEquipInfo->m_StoneCount = (uchar) (*((uchar *) pBuff));
			pBuff += sizeof(uchar);
			KCheck(pEquipInfo->m_StoneCount <= MAX_ITEM_GEM);

			for(int32 i = 0; i < MAX_ITEM_GEM; i++)
			{
				pEquipInfo->m_pGemInfo[i].m_GemIndex = *((uint32 *) pBuff);
				pBuff += sizeof(uint32);
			}

			pEquipInfo->m_AttrCount = *((uchar *) pBuff);
			pBuff += sizeof(uchar);

			for(int32 i = 0; i < pEquipInfo->m_AttrCount; i++)
			{
				pEquipInfo->m_pAttr[i].m_AttrType = *((uchar *) pBuff);
				pBuff += sizeof(uchar);

				pEquipInfo->m_pAttr[i].m_Value.m_Value = *((int16 *) pBuff);
				pBuff += sizeof(int16);
			}

			for(int32 i = 0; i < pEquipInfo->m_AttrCount; i++)
			{
				pEquipInfo->m_pAttr[i].m_IntensifyCount = *((uchar *) pBuff);
				pBuff += sizeof(uchar);
			}

			pEquipInfo->m_ConstCount = *((uchar *) pBuff);
			pBuff += sizeof(uchar);

			for(int32 i = 0; i < pEquipInfo->m_ConstCount; i++)
			{
				pEquipInfo->m_pConst[i].m_ConstId = *((uchar *) pBuff);
				pBuff += sizeof(uchar);

				for (int32 j = 0; j < CONST_ATTR_TYPE_NUMBER; ++j)
				{
					pEquipInfo->m_pConst[i].m_ConstAttr[j].m_AttrType = *((uchar *) pBuff);
					pBuff += sizeof(uchar);
					pEquipInfo->m_pConst[i].m_ConstAttr[j].m_IntensifyCount = *((uchar *) pBuff);
					pBuff += sizeof(uchar);
					pEquipInfo->m_pConst[i].m_ConstAttr[j].m_Value.m_Value = *((int16 *) pBuff);
					pBuff += sizeof(int16);
				}
			}
		}
		break;

	case ICLASS_GEM:
		{
		}
		break;

	case ICLASS_COMITEM:
	case ICLASS_MATERIAL:
	case ICLASS_TASKITEM:
		{
			GetMedicData()->m_nCount = *((uchar *) pBuff);
			pBuff += sizeof(uchar);

			GetMedicData()->m_Level = *((uchar *) pBuff);
			pBuff += sizeof(uchar);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			GetExtraBagData()->m_nBeginTime = *((uint32 *) pBuff);
			pBuff += sizeof(uint32);
		}
		break;

	default:
		{
			KCheck(FALSE);
		}
	}

	KCheck(BuffLength >= (pBuff - pIn));

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::ReadRandomProperty(char *pOut, int32 &OutLength, int32 BuffLength)
{
	KCheck(pOut);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	bClass = ItemClass();
	char	*pBuff = pOut;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	*pBuff = m_nsBind;
	pBuff++;

	*((uint32 *) pBuff) = m_TermEndTime;
	pBuff += sizeof(uint32);

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			*((uchar *) pBuff) = GetEquipData()->m_NeedLevel;
			pBuff += sizeof(uchar);
			*((uchar *) pBuff) = GetEquipData()->m_Bind;
			pBuff += sizeof(uchar);
			*((uchar *) pBuff) = GetEquipData()->m_PaiType;
			pBuff += sizeof(uchar);
			*((uchar *) pBuff) = GetEquipData()->m_EquipType;
			pBuff += sizeof(uchar);
			*((uint32 *) pBuff) = GetEquipData()->m_EquipScore;
			pBuff += sizeof(uint32);
			*((uchar *) pBuff) = GetEquipData()->m_Level;
			pBuff += sizeof(uchar);
			*((uchar *) pBuff) = GetEquipData()->m_CurMaxDur;
			pBuff += sizeof(uchar);
			*((uchar *) pBuff) = GetEquipData()->m_CurDurPoint;
			pBuff += sizeof(uchar);
			*((uint16 *) pBuff) = GetEquipData()->m_CurDamagePoint;
			pBuff += sizeof(uint16);
			*((uchar *) pBuff) = GetEquipData()->m_CurGemHole;
			pBuff += sizeof(uchar);
			*((uchar *) pBuff) = GetEquipData()->m_StoneCount;
			pBuff += sizeof(uchar);
			KCheck(GetEquipData()->m_StoneCount <= MAX_ITEM_GEM);
			for(int32 i = 0; i < MAX_ITEM_GEM; i++)
			{
				*((uint32 *) pBuff) = GetEquipData()->m_pGemInfo[i].m_GemIndex;
				pBuff += sizeof(uint32);
			}

			*((uchar *) pBuff) = GetEquipData()->m_AttrCount;
			pBuff += sizeof(uchar);

			for(int32 i = 0; i < GetEquipData()->m_AttrCount; i++)
			{
				*((uchar *) pBuff) = GetEquipData()->m_pAttr[i].m_AttrType;
				pBuff += sizeof(uchar);

				*((int16 *) pBuff) = GetEquipData()->m_pAttr[i].m_Value.m_Value;
				pBuff += sizeof(int16);
			}

			for(int32 i = 0; i < GetEquipData()->m_AttrCount; i++)
			{
				*((uchar *) pBuff) = GetEquipData()->m_pAttr[i].m_IntensifyCount;
				pBuff += sizeof(uchar);
			}

			*((uchar *) pBuff) = GetEquipData()->m_ConstCount;
			pBuff += sizeof(uchar);

			for(int32 i = 0; i < GetEquipData()->m_ConstCount; i++)
			{
				*((uchar *) pBuff) = GetEquipData()->m_pConst[i].m_ConstId;
				pBuff += sizeof(uchar);

				for (int32 j = 0; j < CONST_ATTR_TYPE_NUMBER; ++j)
				{
					*((uchar *) pBuff) = GetEquipData()->m_pConst[i].m_ConstAttr[j].m_AttrType;
					pBuff += sizeof(uchar);
					*((uchar *) pBuff) = GetEquipData()->m_pConst[i].m_ConstAttr[j].m_IntensifyCount;
					pBuff += sizeof(uchar);
					*((int16 *) pBuff) = GetEquipData()->m_pConst[i].m_ConstAttr[j].m_Value.m_Value;
					pBuff += sizeof(int16);
				}
			}
		}
		break;

	case ICLASS_GEM:
		{
		}
		break;

	case ICLASS_COMITEM:
	case ICLASS_MATERIAL:
	case ICLASS_TASKITEM:
		{
			*((uchar *) pBuff) = GetMedicData()->m_nCount;
			pBuff += sizeof(uchar);

			*((uchar *) pBuff) = GetMedicData()->m_Level;
			pBuff += sizeof(uchar);

		}
		break;

	case ICLASS_EXTRABAG:
		{
			*((uint32 *) pBuff) = GetExtraBagData()->m_nBeginTime;
			pBuff += sizeof(uint32);
		}
		break;

	default:
		{
			KCheck(FALSE);
		}
	}

	OutLength = (int32) (pBuff - pOut);
	KCheck(BuffLength >= OutLength);
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar SItem::GetItemCount() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	bClass = ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bClass == ICLASS_EQUIP)
	{
		return 1;
	}
	else if(bClass == ICLASS_GEM)
	{
		return 1;
	}
	else if(bClass == ICLASS_EXTRABAG)
	{
		return 1;
	}
	else if(bClass == ICLASS_COMITEM)
	{
		return GetMedicData()->m_nCount;
	}
	else if(bClass == ICLASS_MATERIAL)
	{
		return GetMedicData()->m_nCount;
	}
	else if(bClass == ICLASS_TASKITEM)
	{
		return GetMedicData()->m_nCount;
	}
	else
		return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SItem::SetItemCount(int32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	bClass = ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bClass == ICLASS_COMITEM)
	{
		GetMedicData()->m_nCount = nCount;
	}
	else if(bClass == ICLASS_MATERIAL)
	{
		GetMedicData()->m_nCount = nCount;
	}
	else if(bClass == ICLASS_TASKITEM)
	{
		GetMedicData()->m_nCount = nCount;
	}
	else
	{
		KCheck(FALSE);
		return;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::IncCount(uint32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const uchar	bClass = ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			return FALSE;
		}
		break;

	case ICLASS_GEM:
		{
			return FALSE;
		}
		break;

	case ICLASS_COMITEM:
	case ICLASS_MATERIAL:
	case ICLASS_TASKITEM:
		{
			GetMedicData()->m_nCount += nCount;
			return TRUE;
		}
		break;

	default:
		return FALSE;
		break;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SItem::DecCount(uint32 nCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const uchar	bClass = ItemClass();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			return FALSE;
		}
		break;

	case ICLASS_GEM:
		{
			return FALSE;
		}
		break;

	case ICLASS_TASKITEM:
	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			KCheck(GetItemCount() > 0);
			GetMedicData()->m_nCount -= nCount;
			return TRUE;
		}
		break;

	default:
		return FALSE;
		break;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Item2String(SItem *pItem, char *pOut, int32 &OutLength, int32 BuffLength)
{
	KCheck(pItem);
	KCheck(pOut);

	/*~~~~~~~~~~~~~~~~~~*/
	char	*pBuff = pOut;
	/*~~~~~~~~~~~~~~~~~~*/

	*((uint32 *) pBuff) = pItem->m_ItemIndex;
	pBuff += sizeof(uint32);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	NameLength = (uchar) strlen(pItem->m_Creator);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NameLength >= MAX_ITEM_CREATOR_NAME)
	{
		NameLength = 0;
	}

	*((uchar *) pBuff) = NameLength;
	pBuff += sizeof(uchar);

	memcpy(pBuff, pItem->m_Creator, sizeof(char) * NameLength);
	pBuff += sizeof(char) * NameLength;

	for(int32 i = 0; i < MAX_ITEM_PARAM; ++i)
	{
		*((int32 *) pBuff) = pItem->m_Param[i];
		pBuff += sizeof(int32);
	}

	*((uint32 *) pBuff) = pItem->m_ItemGUID.m_Serial;
	pBuff += sizeof(uint32);
	*((uint32 *) pBuff) = pItem->m_ItemGUID.m_Server;
	pBuff += sizeof(uint32);
	*((uint32 *) pBuff) = pItem->m_ItemGUID.m_World;
	pBuff += sizeof(uint32);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	Length = sizeof(uint32) +
		sizeof(uchar) +
		sizeof(char) *
		NameLength +
		sizeof(int32) *
		MAX_ITEM_PARAM +
		sizeof(uint32) *
		3;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pItem->ReadRandomProperty(pBuff, OutLength, BuffLength - Length);
	OutLength += Length;

	/*~~~~~~~~~~~*/
	char	p[MAX_ITEM_STRING_ASCII_BUFFER];
	/*~~~~~~~~~~~*/

	memset(p, 0, MAX_ITEM_STRING_ASCII_BUFFER);

	Binary2Str(pOut, OutLength, p, sizeof(p));
	strcpy(pOut, p);
	OutLength = (int32) strlen(p);
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL String2Item(char *pIn, int32 BuffLength, SItem *pItem)
{
	KCheck(pItem);
	KCheck(pIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	static int32	nItemSerialCount = 1;
	char		p[MAX_ITEM_STRING_BIN_BUFFER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(p, 0, MAX_ITEM_STRING_BIN_BUFFER);

	/*~~~~~~~~~*/
	uint32	iOut;
	/*~~~~~~~~~*/

	Str2Binary(pIn, BuffLength, p, sizeof(p), iOut);

	/*~~~~~~~~~~~~~~~*/
	char	*pBuff = p;
	/*~~~~~~~~~~~~~~~*/

	pItem->m_ItemIndex = *((uint32 *) pBuff);
	pBuff += sizeof(uint32);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	NameLength = *((uchar *) pBuff);;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(NameLength < MAX_ITEM_CREATOR_NAME);
	pBuff += sizeof(char);

	memcpy(pItem->m_Creator, pBuff, sizeof(char) * NameLength);
	pBuff += sizeof(char) * NameLength;

	for(int32 i = 0; i < MAX_ITEM_PARAM; ++i)
	{
		pItem->m_Param[i] = *((int32 *) pBuff);
		pBuff += sizeof(int32);
	}

	pItem->m_ItemGUID.m_Serial = nItemSerialCount;
	pBuff += sizeof(uint32);

	pItem->m_ItemGUID.m_Server = *((uint32 *) pBuff);
	pBuff += sizeof(uint32);

	pItem->m_ItemGUID.m_World = *((uint32 *) pBuff);
	pBuff += sizeof(uint32);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	Length = sizeof(uint32) +
		sizeof(uchar) +
		sizeof(char) *
		NameLength +
		sizeof(int32) *
		MAX_ITEM_PARAM +
		sizeof(uint32) *
		3;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iOut = BuffLength - Length;
	pItem->WriteRandomProperty(pBuff, iOut);

	if(nItemSerialCount > 10000000) nItemSerialCount = 0;
	++nItemSerialCount;
	return TRUE;
}



/*
 =======================================================================================================================
 设置国王数据
 =======================================================================================================================
 */
void RetAllCountryData::SetKingInfo(CountryID_t nCountry,GUID_t nGUID,const char* strName )
{
	KCheck( nCountry>=0 && nCountry < MAX_COUNTRY_NUM );
	KCheck( strName != NULL );

	m_nKingGUID[nCountry] = nGUID;
	if( nGUID <= 0 || strName == NULL )
		return ;

	m_nKingNameSize[nCountry] = (uchar)strlen(strName);
	strncpy(m_szKingName[nCountry], strName, MAX_CHARACTER_NAME - 1);

	if( m_nKingNameSize[nCountry] > MAX_CHARACTER_NAME )
		m_nKingNameSize[nCountry] = MAX_CHARACTER_NAME;

	if( m_nKingNameSize[nCountry] > 0 )
		m_szKingName[nCountry][MAX_CHARACTER_NAME-1] = 0;
}

/*
 =======================================================================================================================
 设置朱雀信息
 =======================================================================================================================
 */
void RetAllCountryData::SetZhuQueInfo(CountryID_t nCountry,GUID_t nGUID,const char* strName )
{
	KCheck( nCountry>=0 && nCountry < MAX_COUNTRY_NUM );
	KCheck( strName != NULL );

	m_nZhuQueGUID[nCountry] = nGUID;
	if( nGUID <= 0 || strName == NULL )
		return ;

	m_nZhuQueNameSize[nCountry] = (uchar)strlen(strName);
	strncpy(m_szZhuQueName[nCountry], strName, MAX_CHARACTER_NAME - 1);

	if( m_nZhuQueNameSize[nCountry] > MAX_CHARACTER_NAME )
		m_nZhuQueNameSize[nCountry] = MAX_CHARACTER_NAME;

	if( m_nZhuQueNameSize[nCountry] > 0 )
		m_szZhuQueName[nCountry][MAX_CHARACTER_NAME-1] = 0;
}

/*
 =======================================================================================================================
 设置青龙信息
 =======================================================================================================================
 */
void RetAllCountryData::SetQingLongInfo(CountryID_t nCountry,GUID_t nGUID,const char* strName )
{
	KCheck( nCountry>=0 && nCountry < MAX_COUNTRY_NUM );

	m_nQingLongGUID[nCountry] = nGUID;
	if( nGUID <= 0 || strName == NULL )
		return ;

	m_nQingLongNameSize[nCountry] = (uchar)strlen(strName);
	strncpy(m_szQingLongName[nCountry], strName, MAX_CHARACTER_NAME - 1);

	if( m_nQingLongNameSize[nCountry] > MAX_CHARACTER_NAME )
		m_nQingLongNameSize[nCountry] = MAX_CHARACTER_NAME;

	if( m_nQingLongNameSize[nCountry] > 0 )
		m_szQingLongName[nCountry][MAX_CHARACTER_NAME-1] = 0;
}

/*
=======================================================================================================================
设置国家排行帮数据
=======================================================================================================================
*/
void RetAllCountryData::SetCountryRankInfo(CountryID_t nCountry,uchar nRank )
{
	KCheck( nCountry>=0 && nCountry < MAX_COUNTRY_NUM );
	
	if(nRank<COUNTRY_RANK_STRONG || nRank>COUNTRY_RANK_WEAK)
	{
		return;
	}

	m_rank[nCountry] = nRank;

}

/*
 =======================================================================================================================
 取得包大小
 =======================================================================================================================
 */
uint32 RetAllCountryData::GetPacketSize()const
{
	uint32 uSize = 0;
	for( int i = 0; i<MAX_COUNTRY_NUM; ++i )
	{
		uSize += sizeof(m_nKingGUID[i]);
		if( m_nKingGUID[i] > 0 )
		{
			uSize += sizeof(m_nKingNameSize[i]);
			uSize += sizeof(char) * m_nKingNameSize[i];
		}

		uSize += sizeof(m_nZhuQueGUID[i]);
		if( m_nZhuQueGUID[i] > 0 )
		{
			uSize += sizeof(m_nZhuQueNameSize[i]);
			uSize += sizeof(char) * m_nZhuQueNameSize[i];
		}

		uSize += sizeof(m_nQingLongGUID[i]);
		if( m_nQingLongGUID[i] > 0 )
		{
			uSize += sizeof(m_nQingLongNameSize[i]);
			uSize += sizeof(char) * m_nQingLongNameSize[i];
		}

		uSize += sizeof(m_rank[i]);  
	}

	return uSize;
}

void SPlayerShopFolder::Read(char *pIn, int32 BuffLength)
{
	KCheck(pIn);
	char *pBuff = pIn;

	m_count = *((uint32 *) pBuff);
	pBuff += sizeof(uint32);

	m_index = *((int32 *) pBuff);
	pBuff += sizeof(int32);

	KCheck(m_count>=0 && m_count <= MAX_SHOP_ELEMENT_NUMBER );

	KCheck(m_index>= -1 && m_index < MAX_SHOP_ELEMENT_NUMBER );

	for(int32 i = 0; i < m_count; ++i)
	{
		m_list[i].m_nShopId =  *((short *) pBuff);
		pBuff += sizeof(short);

		m_list[i].m_nIndex =  *((short *) pBuff);
		pBuff += sizeof(short);

		m_list[i].m_ItemId = *((uint32 *) pBuff);
		pBuff += sizeof(uint32);
	}

}

void SPlayerShopFolder::Write(char *pOut, int32 &OutLength, int32 BuffLength)
{
	KCheck(pOut);

	KCheck(m_count>=0 && m_count <= MAX_SHOP_ELEMENT_NUMBER );

	KCheck(m_index>=-1 && m_index < MAX_SHOP_ELEMENT_NUMBER );

	char *pBuff = pOut;

	*((uint32 *) pBuff) = m_count;
	pBuff += sizeof(uint32);

	*((int32 *) pBuff) = m_index;
	pBuff += sizeof(int32);


	for(int32 i = 0; i < m_count; ++i)
	{
		*((short *) pBuff) = m_list[i].m_nShopId;
		pBuff += sizeof(short);

		*((short *) pBuff) = m_list[i].m_nIndex;
		pBuff += sizeof(short);

		*((uint32 *) pBuff) = m_list[i].m_ItemId;
		pBuff += sizeof(uint32);
	}

	OutLength = (int32) (pBuff - pOut);
	KCheck(BuffLength >= OutLength);
}

BOOL SPlayerShopFolder::AddElement(const SPlayerShopElement& element)
{
	KCheck(m_count>=0 && m_count <= MAX_SHOP_ELEMENT_NUMBER );
	KCheck(m_index>=-1 && m_index < MAX_SHOP_ELEMENT_NUMBER );

	if (element.m_nShopId == INVALID_ID || element.m_nIndex == INVALID_ID || element.m_ItemId == 0)
	{
		return FALSE;
	}

	int i =0;
	for (;i < m_count;++i)
	{
		if (m_list[i].m_ItemId == element.m_ItemId)
		{
			break;
		}
	}

	if (i < m_count)
	{
		DelElement(element);
	}

	if (m_index >= MAX_SHOP_ELEMENT_NUMBER -1)
	{
		m_index = 0;
	}
	else
	{
		++m_index;
	}

	m_list[m_index] = element;

	if(m_count < MAX_SHOP_ELEMENT_NUMBER)
	{
		++m_count;
	}

	return TRUE;
}

BOOL SPlayerShopFolder::DelElement(const SPlayerShopElement& element)
{
	KCheck(m_count>=0 && m_count <= MAX_SHOP_ELEMENT_NUMBER );
	KCheck(m_index>=-1 && m_index < MAX_SHOP_ELEMENT_NUMBER );

	if (element.m_ItemId == 0)
	{
		return FALSE;
	}

	int k =0;

	for (;k < m_count;++k)
	{
		if (m_list[k].m_ItemId == element.m_ItemId)
		{
			break;
		}
	}

	if (k >= m_count || m_count == 0)
	{
		return FALSE;
	}
	
	SPlayerShopElement swapElementList[MAX_SHOP_ELEMENT_NUMBER];
	int32 swapCount = 0;

	for (int32 i = m_index + 1 ;i < m_count;++i)//第一个区间
	{
		if (m_list[i].m_ItemId == element.m_ItemId)
		{
			continue;
		}
		else
		{
			swapElementList[swapCount++] = m_list[i];
		}
	}

	for (int32 i = 0 ;i <= m_index;++i)//第二个区间
	{
		if (m_list[i].m_ItemId == element.m_ItemId)
		{
			continue;
		}
		else
		{
			swapElementList[swapCount++] = m_list[i];
		}
	}

	KCheck(swapCount>=0 && swapCount <= MAX_SHOP_ELEMENT_NUMBER );

	memcpy(m_list,swapElementList,MAX_SHOP_ELEMENT_NUMBER * sizeof(SPlayerShopElement));

	m_count = swapCount;

	m_index = (int32)m_count -1;

	return TRUE;

}

BOOL SPlayerShopFolder::UpdateElement(const SPlayerShopElement& element)
{
	KCheck(m_count>=0 && m_count <= MAX_SHOP_ELEMENT_NUMBER );
	KCheck(m_index>=-1 && m_index < MAX_SHOP_ELEMENT_NUMBER );

	if (element.m_ItemId == 0)
	{
		return FALSE;
	}

	for (int32 k =0 ;k < m_count;++k)
	{
		if (m_list[k].m_ItemId == element.m_ItemId)
		{
			m_list[k] = element;

			return TRUE;
		}
	}

	return FALSE;

}
