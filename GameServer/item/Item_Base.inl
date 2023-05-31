#ifndef __ITEM_INL__
#define __ITEM_INL__
#include "StructDB.h"
#include "share/TAB/TabDefine.h"
#include "share/TAB/TabDefine_Map_Item.h"
#include "BaseTool.h"

inline int32 Item::GetLayedNum( ) const
{
	__GUARD__

	switch(m_Type)
	{
	case IDT_ITEM:
		{
			KCheck( m_pItem ) ;
			return m_pItem->GetItemCount();
		}
		break;
	case IDT_PET:
		{
			KCheck(m_pPet);
			return 1;
		}
		break;
	default:
		{
			KCheck(FALSE);
			return 0;
		}
	}


	__UNGUARD__

	return 0 ;
}


inline BOOL Item::IsPWLock() const
{
	__GUARD__
	switch(m_Type)
	{
		case IDT_ITEM:
			{
				KCheck( m_pItem ) ;
				return m_pItem->GetItemPLock();
			}
			break;
		case IDT_PET:
			{
				KCheck(m_pPet);
				return 1;
			}
			break;
		default:
			{
				KCheck(FALSE);
				return 0;
			}
	}

	__UNGUARD__
	return TRUE;
}

inline int32 Item::GetMaxLayedNum( ) const
{
	__GUARD__

	switch(m_Type)
	{
	case IDT_ITEM:
		{
			KCheck( m_pItem ) ;
			SItemType Itemtype = Serial2ItemType(GetItemTableIndex());
			return GetMaxItemTile(Itemtype);
		}
		break;
	case IDT_PET:
		{
			KCheck(m_pPet);
			return 1;
		}
		break;
	default:
		{
			KCheck(FALSE);
			return 0;
		}
	}

	__UNGUARD__

	return 0 ;
}

BOOL	Item::IsFull() const
{
	__GUARD__

	switch(m_Type)
	{
	case IDT_ITEM:
		{
			KCheck(m_pItem);
			return m_pItem->GetItemCount()>= GetMaxLayedNum();
		}
		break;
	case IDT_PET:
		{
			KCheck(m_pPet);
			return !m_pPet->m_GUID.IsNull();
		}
		break;
	default:
		{
			KCheck(FALSE);
			return FALSE;
		}
	}

	__UNGUARD__

	return FALSE;
}

inline SItemGuid Item::GetGUID( )
{
	__GUARD__

		KCheck( m_pItem ) ;
	return m_pItem->m_ItemGUID ;

	__UNGUARD__

		SItemGuid	ig;
	return	ig;
};

inline uint32 Item::GetItemTableIndex( ) const
{
	__GUARD__

		KCheck( m_pItem ) ;
	return m_pItem->m_ItemIndex ;

	__UNGUARD__

		return	-1;
}

inline uchar Item::GetItemClass()	const
{
	__GUARD__

		KCheck(m_pItem);
	return	m_pItem->ItemClass();

	__UNGUARD__

		return	0;

}


inline uchar	Item::GetItemType() const
{
	__GUARD__

		KCheck(m_pItem);
	return	m_pItem->ItemType();

	__UNGUARD__

		return	0;
}

inline uchar	Item::GetItemIndex() const
{
	__GUARD__

		KCheck(m_pItem);
	return	m_pItem->GetIndex();

	__UNGUARD__

		return	0;
}

inline BOOL	Item::IsEquipLocked()		const
{
	KCheck(m_pItem);
	if(m_pItem->ItemClass() == ICLASS_EQUIP)
		return	m_pItem->GetEquipData()->m_byLock;
	return FALSE;
}

inline uint32	Item::GetEquipUnLockTime() const
{
	KCheck(m_pItem);
	if(m_pItem->ItemClass() == ICLASS_EQUIP)
		return	m_pItem->GetEquipData()->m_UnLockTime;
	return 0;
}


uchar					Item::GetAffixSpellCount()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_AffSkillCount;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return 0;
	}
}

uchar					Item::GetEffectSpellCount()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_EffSkillCount;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return 0;
	}
}

_ITEM_EFFECT_SKILL*		Item::GetEffectSpell(uint32 pos)		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		if (pos>=pEquipTable->m_EffSkillCount)
		{
			return NULL;
		}
		return &pEquipTable->m_EffectSkill[pos];
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return NULL;
	}
}

uchar					Item::GetReqJob()				const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_PrefessionReq;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return -1;
	}
}

uchar					Item::GetBaseGemHole()				const		
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_BaseGemHole;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return -1;
	}
}


int32					Item::GetSetNum()			const				
{
	KCheck(m_pItem);
	if(m_pItem->m_ItemIndex==0)
	{
		return 0;
	}
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_EquipSetNum;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return 0;
	}
}
uchar					Item::GetMaxSetCount()			const				
{
	KCheck(m_pItem);
	if(m_pItem->m_ItemIndex==0)
	{
		return 0;
	}
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_EquipSetMaxNum;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return 0;
	}

}
uchar					Item::GetEquipPoint()		const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_EquipPoint;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return -1;

	}

}

uchar					Item::GetMaxDurPoint()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_MaxDur;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return -1;
	}
}

uchar					Item::GetGemSlotMax()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
	if(pEquipTable)
	{
		return pEquipTable->m_MAXGemHole;
	}
	else
	{
		KCheckEx(FALSE,"物品运行时数据出错!或者物品表有问题");
		return -1;
	}
}


BOOL					Item::IsTermEnd()		const 	
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32 uTermEndTime = GetTermTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if(uTermEndTime == 1) return TRUE;
	if(uTermEndTime == 0 || uTermEndTime == 2 || GET_TIME().GetCTime() <= uTermEndTime ) return FALSE;

	return TRUE;
}
BOOL					Item::IsOverTime()		const
{
	KCheck(m_pItem);
	if ( 1 == m_pItem->m_TermEndTime )
		return TRUE;
	return FALSE;
}

BOOL					Item::IsValid() const						
{
	if (GetDurability() == 0)
		return FALSE;

	if (IsOverTime())		
		return FALSE;

	return TRUE;
}


uint16					Item::GetDamagePoint()	const
{
	KCheck(m_pItem);
	return m_pItem->GetEquipData()->m_CurDamagePoint;
}

uchar					Item::GetItemBindType()	const
{
	KCheck(m_pItem);
	return m_pItem->GetItemBindType();
}

BOOL					Item::GetItemIdentify()	const
{
	KCheck(m_pItem);

	return FALSE;
}

uchar					Item::GetRequireLevel()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	return m_pItem->GetEquipData()->m_NeedLevel;
}

uchar					Item::GetCurLevel()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	return m_pItem->GetEquipData()->m_Level;
}

uchar				Item::GetCurLevelType()			const		
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	EQUIPLEVELUP_INFO* pLevelupInfoTb = g_ItemTab.GetEquipLeveupTB(EQUIPLEVEL_TYPE0, (PLAYER_EQUIP)GetEquipPoint(), GetCurLevel());
	if(pLevelupInfoTb)
	{
		return pLevelupInfoTb->m_LevelType;
	}
	return 0;
}

uchar					Item::GetDurability()		const 				
{
	KCheck(m_pItem);
	return m_pItem->GetEquipData()->m_CurDurPoint;
}

uchar					Item::GetCurMaxDurability()		const 				
{
	KCheck(m_pItem);
	return m_pItem->GetEquipData()->m_CurMaxDur;
}

uint32					Item::GetTermTime()		const 				
{
	KCheck(m_pItem);
	return m_pItem->m_TermEndTime;
}

uchar					Item::GetPropertyCount()		const				
{
	KCheck(m_pItem);
	return m_pItem->GetEquipData()->m_AttrCount;
}

uchar					Item::GetEquipGemCount()	const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	return m_pItem->GetEquipData()->m_StoneCount;
}

uchar					Item::GetCurGemHole()		const			
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	return m_pItem->GetEquipData()->m_CurGemHole;
}

uchar					Item::GetEquipBindLevel()
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	return m_pItem->GetEquipData()->GetSoulBindLevel();
}

void					Item::SetEquipBindLevel(uchar uLevel)
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	m_pItem->GetEquipData()->SetSoulBindLevel(uLevel);
}

uchar					Item::GetEquipHonorBindLevel()
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	return m_pItem->GetEquipData()->GetHonorBindLevel();
}

void					Item::SetEquipHonorBindLevel(uchar uLevel)
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	m_pItem->GetEquipData()->SetHonorBindLevel(uLevel);
}

uint32					Item::GetEquipScore()			const
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	return m_pItem->GetEquipData()->m_EquipScore;
}

uchar					Item::GetEquipFromType()		    const
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);

	return m_pItem->GetEquipData()->m_EquipType;
}

uint32					Item::GetEquipGem(int32 nPos)	const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	KCheck(nPos<MAX_ITEM_GEM);
	return m_pItem->GetEquipData()->m_pGemInfo[nPos].m_GemIndex;
}

const _ITEM_PROPERTY				Item::GetEquipProperty(uchar	nIndex)		const	
{	
	KCheck(m_pItem);
	KCheck(nIndex<m_pItem->GetEquipData()->m_AttrCount);
	return m_pItem->GetEquipData()->m_pAttr[nIndex];
}

const SItemGemInfo			Item::GetEquipGemInfo(uchar nIndex)	const		
{
	KCheck(m_pItem);
	KCheck(nIndex<GetGemSlotMax());
	return m_pItem->GetEquipData()->m_pGemInfo[nIndex];
}

uchar						Item::GetEquipPaiType()		    const			
{
	KCheck(m_pItem);
	return m_pItem->GetEquipData()->m_PaiType;
}


uchar						Item::GetReqSpellLevel()	const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_COMITEM);
	SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
	if(pComTable)
	{
		return pComTable->m_nReqSkillLevel;
	}
	KCheck(FALSE);
	return -1;
}

int32							Item::GetReqSpell()			const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_COMITEM);
	SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
	if(pComTable)
	{
		return pComTable->m_nReqSkill;
	}
	KCheck(FALSE);
	return -1;
}
int32							Item::GetScriptID()			const				
{
	KCheck(m_pItem);

	switch( m_pItem->ItemClass() )
	{
	case ICLASS_EQUIP:
		{
			SEquipTab* pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
			if(pEquipTable)
			{
				return pEquipTable->m_nScriptID;
			}
		}
		break;
	case ICLASS_TASKITEM:
		{
			TASKITEM_INFO_TB* pTaskTable = g_ItemTab.GetTaskItemInfoTB( m_pItem->m_ItemIndex );
			if ( pTaskTable )
			{
				return pTaskTable->m_nScriptID;
			}

		}
		break;
	case ICLASS_COMITEM:
		{
			SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			if(pComTable)
			{
				return pComTable->m_nScriptID;
			}
		}
		break;
	default:
		{
			return INVALID_ID;
		}
		break;
	}
	
	return INVALID_ID;
}
int32							Item::GetSpellID()			const				
{
	KCheck(m_pItem);

	switch( m_pItem->ItemClass() )
	{
	case ICLASS_TASKITEM:
		{
			TASKITEM_INFO_TB* pTaskTable = g_ItemTab.GetTaskItemInfoTB( m_pItem->m_ItemIndex );
			if ( pTaskTable )
			{
				return pTaskTable->m_nSkillID;
			}

		}
		break;
	case ICLASS_COMITEM:
		{
			SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			if(pComTable)
			{
				return pComTable->m_nSkillID;
			}
		}
		break;
	default:
		{
			KCheck( FALSE );
		}
		break;
	}

	return INVALID_ID;
}

uchar						Item::GetTargetType()		const			   
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_COMITEM);
	SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
	if(pComTable)
	{
		return pComTable->m_TargetType;
	}
	KCheck(FALSE);
	return -1;
}

BOOL						Item::IsBroadCast()			const				
{
	KCheck(m_pItem);
	switch(m_pItem->ItemClass())
	{
	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			if(pComTable)
			{
				return pComTable->m_bBroadcast;
			}
			KCheck(FALSE);
		}
		break;
	case ICLASS_TASKITEM:
		{
			TASKITEM_INFO_TB* pTaskTable = g_ItemTab.GetTaskItemInfoTB(m_pItem->m_ItemIndex);
			if(pTaskTable)
			{
				return pTaskTable->m_bBroadcast;
			}
			KCheck(FALSE);
		}
	    break;
	case ICLASS_GEM:
		{
			SGemInfoTab* pGemTable = g_ItemTab.GetGemInfoTB(m_pItem->m_ItemIndex);
			if(pGemTable)
			{
				return pGemTable->m_bBroadCast;
			}
			KCheck(FALSE);
		}
		break;
	default:
	    return FALSE;
	}
}

BOOL						Item::IsEquipCanOp(uchar opType)
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EQUIP);
	uchar cType = GetItemType();
	switch(opType)
	{
	case EQUIPOP_USE:
	case EQUIPOP_UNEQUIP:
		{
			switch(cType)
			{
				case EQUIP_MDAO:
				case EQUIP_MJIAN:
				case EQUIP_MGONG:
				case EQUIP_MHUOQIANG:
				case EQUIP_MCHUI:
				case EQUIP_MZHANG:
				case EQUIP_SDUN:
				case EQUIP_SJIAN:
				case EQUIP_SJIANZHI:
				case EQUIP_SZIDAN:
				case EQUIP_SGU:
				case EQUIP_SHAOJIAO:
				case EQUIP_CAP:
				case EQUIP_NECKLACE:
				case EQUIP_SHOULDER:
				case EQUIP_ARMOR:
				case EQUIP_CUFF:
				case EQUIP_HAND:
				case EQUIP_SASH:
				case EQUIP_BOOT:
				case EQUIP_RING:
				case EQUIP_ADORN:
				case EQUIP_SUIT:
				case EQUIP_SIGN:
				case EQUIP_CRUSADE_MASTER_HAND:		//十字军主手
				case EQUIP_FIRE_ENVOY_MASTER_HAND:	//圣火使主手
				case EQUIP_ASSASSIN_MASTER_HAND:	//刺客主手
				case EQUIP_GUARDS_MASTER_HAND:		//近卫军主手
				case EQUIP_FRIAR_MASTER_HAND:		//隐修士主手
				case EQUIP_LAMA_MASTER_HAND:		//喇嘛主手
				case EQUIP_CRUSADE_ASSIST_HAND:		//十字军副手
				case EQUIP_FIRE_ENVOY_ASSIST_HAND:	//圣火使副手
				case EQUIP_ASSASSIN_ASSIST_HAND:	//刺客副手
				case EQUIP_GUARDS_ASSIST_HAND:		//近卫军副手
				case EQUIP_FRIAR_ASSIST_HAND:		//隐修士副手
				case EQUIP_LAMA_ASSIST_HAND:		//喇嘛副手
				{
					return TRUE;
				}
				break;
				default:
				{
					return FALSE;
				}
				break;
			}
		}
		break;
	case EQUIPOP_LEVELUP:
	case EQUIPOP_ADDHOLE:
	case EQUIPOP_USEGEM:
	case EQUIPOP_KEZI:
	case EQUIPOP_CHANGEPAI:
	case EQUIPOP_EXCHANGEPAI:
	case EQUIPOP_DECOMPOUND:
	case EQUIPOP_REMOULD:
	case EQUIPOP_BLUEINTENSIFY:
	case EQUIPOP_BLUEREWORK:
		{
			switch(cType)
			{
				case EQUIP_MDAO:
				case EQUIP_MJIAN:
				case EQUIP_MGONG:
				case EQUIP_MHUOQIANG:
				case EQUIP_MCHUI:
				case EQUIP_MZHANG:
				case EQUIP_SDUN:
				case EQUIP_SJIAN:
				case EQUIP_SJIANZHI:
				case EQUIP_SZIDAN:
				case EQUIP_SGU:
				case EQUIP_SHAOJIAO:
				case EQUIP_CAP:
				case EQUIP_NECKLACE:
				case EQUIP_SHOULDER:
				case EQUIP_ARMOR:
				case EQUIP_CUFF:
				case EQUIP_HAND:
				case EQUIP_SASH:
				case EQUIP_BOOT:
				case EQUIP_RING:
				case EQUIP_ADORN:
				case EQUIP_CRUSADE_MASTER_HAND:		//十字军主手
				case EQUIP_FIRE_ENVOY_MASTER_HAND:	//圣火使主手
				case EQUIP_ASSASSIN_MASTER_HAND:	//刺客主手
				case EQUIP_GUARDS_MASTER_HAND:		//近卫军主手
				case EQUIP_FRIAR_MASTER_HAND:		//隐修士主手
				case EQUIP_LAMA_MASTER_HAND:		//喇嘛主手
				case EQUIP_CRUSADE_ASSIST_HAND:		//十字军副手
				case EQUIP_FIRE_ENVOY_ASSIST_HAND:	//圣火使副手
				case EQUIP_ASSASSIN_ASSIST_HAND:	//刺客副手
				case EQUIP_GUARDS_ASSIST_HAND:		//近卫军副手
				case EQUIP_FRIAR_ASSIST_HAND:		//隐修士副手
				case EQUIP_LAMA_ASSIST_HAND:		//喇嘛副手
				{
					return TRUE;
				}
				break;
				case EQUIP_SUIT:
				{
					if (EQUIPOP_LEVELUP == opType)
					{
						return TRUE;
					}
				}
				break;
				default:
				{
					return FALSE;
				}
				break;
			}
		}
		break;
	default:
		{
			KCheck( FALSE );
		}
		break;
	}
	return FALSE;
}

const _ITEM_PROPERTY				Item::GetGemProperty(uint32 i)		const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass() == ICLASS_GEM);
	SGemInfoTab*	pGET		=		g_ItemTab.GetGemInfoTB( GetItemTableIndex());
	KCheck(pGET);
	KCheck(i<pGET->m_AttCount);
	return pGET->m_GenAttr[i];
}

uint32						Item::GetGemReqNum()		const
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass() == ICLASS_GEM);
	SGemInfoTab*	pGET		=		g_ItemTab.GetGemInfoTB( GetItemTableIndex());
	KCheck(pGET);
	return pGET->m_GemReqCount;
}

const _GEM_REQ_ATT			Item::GetReqGemProperty(int32 nPos)	const		
{
	KCheck(m_pItem);
	KCheck(nPos<MAX_GEM_REQ);
	KCheck(m_pItem->ItemClass() == ICLASS_GEM);
	SGemInfoTab*	pGET		=		g_ItemTab.GetGemInfoTB( GetItemTableIndex());
	KCheck(pGET);
	return pGET->m_GemReqAttr[nPos];
}

uint32				Item::GetGemShowLevel()	const
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass() == ICLASS_GEM);
	SGemInfoTab*	pGET		=		g_ItemTab.GetGemInfoTB( GetItemTableIndex());
	KCheck(pGET);
	return pGET->m_ShowLevel;
}

int32					Item::GetGemUsePrice()
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass() == ICLASS_GEM);
	SGemInfoTab*	pGET		=		g_ItemTab.GetGemInfoTB( GetItemTableIndex());
	KCheck(pGET);
	return pGET->m_nUsePrice;
}

uint32				Item::GetReqEquip(int32 nEquipType) const
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass() == ICLASS_GEM);
	KCheck(nEquipType<MAX_BASE_EQUIP_COUNT);
	SGemInfoTab*	pGET		=		g_ItemTab.GetGemInfoTB( GetItemTableIndex());
	KCheck(pGET);
	return pGET->m_EquipType[nEquipType];
}

uint32					Item::GetExtraBagSellPrice()		const	
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EXTRABAG);
	EXTRABAG_INFO_TB* pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
	if(pExtraBagTable)
	{
		return pExtraBagTable->m_nSellPrice;
	}
	KCheck(FALSE);
	return 0;
}

uint32					Item::GetExtraBagBasePrice()		const	
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EXTRABAG);
	EXTRABAG_INFO_TB* pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
	if(pExtraBagTable)
	{
		return pExtraBagTable->m_nBasePrice;
	}
	KCheck(FALSE);
	return 0;
}

uint32					Item::GetExtraBagValidTime()		const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EXTRABAG);
	EXTRABAG_INFO_TB* pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
	if(pExtraBagTable)
	{
		return pExtraBagTable->m_nValidTime;
	}
	KCheck(FALSE);
	return 0;
}

uint32					Item::GetExtraBagRemainTime()		const				
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EXTRABAG);
	uint32 elpsTime = (uint32)GET_TIME().GetCTime()-m_pItem->GetExtraBagData()->m_nBeginTime;
	uint32 validTime = GetExtraBagValidTime();
	if (elpsTime>=validTime)
	{
		return 0;
	}
	return elpsTime-validTime;
}

uint32					Item::GetExtraBagBeginTime()		const
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EXTRABAG);
	return m_pItem->GetExtraBagData()->m_nBeginTime;
}

uint32					Item::GetExtraBagSize()			const					
{
	KCheck(m_pItem);
	KCheck(m_pItem->ItemClass()==ICLASS_EXTRABAG);
	EXTRABAG_INFO_TB* pExtraBagTable = g_ItemTab.GetExtraBagInfoTB(m_pItem->m_ItemIndex);
	if(pExtraBagTable)
	{
		return pExtraBagTable->m_nSize;
	}
	KCheck(FALSE);
	return 0;
}


inline  BOOL			Item::IsMating() const					
{
	KCheck(m_pPet);
	return (m_pPet->m_iStatus == _HORSE_DB::PET_STATUS_MATING);
}

inline  BOOL			Item::IsCompose() const					
{
	KCheck(m_pPet);
	return (m_pPet->m_iStatus == _HORSE_DB::PET_STATUS_COMPOSE);
}

inline  int32				Item::GetHorseModelID() const			
{
	KCheck(m_pPet);
	return m_pPet->m_iModelID;
}

inline BOOL		Item::IsPetLocked()		const
{
	KCheck(m_pPet);
	return m_pPet->m_byLock;
}

inline void		Item::SetPetStatus(int32 nStatus)		const
{
	KCheck(m_pPet);
	m_pPet->m_iStatus  = nStatus;
}

inline uint32	    Item::GetPetUnLockTime() const
{
	KCheck(m_pPet);
	return m_pPet->m_UnLockTime;
}

inline void	    Item::SetPetUnLock() const
{
	KCheck(m_pPet);
	m_pPet->m_byLock = PET_UNLOCK;
	m_pPet->m_UnLockTime = 0;
}


inline  int32				Item::GetStrengthPer() const			
{
	KCheck(m_pPet);
	return m_pPet->m_iStrengthPerception;
}


inline  int32				Item::GetSmartnessPer() const			
{
	KCheck(m_pPet);
	return m_pPet->m_iSmartnessPerception;
}
inline  int32 			Item::GetMindPer() const				
{
	KCheck(m_pPet);
	return m_pPet->m_iMindPerception;
}

inline  int32 			Item::GetConstitutionPer() const		
{
	KCheck(m_pPet);
	return m_pPet->m_iConstitutionPerception;
}

inline  int32				Item::GetStrengthPoint() const			
{
	KCheck(m_pPet);
	return m_pPet->m_iStrengthPoint;
}

inline  int32				Item::GetSmartnessPoint() const			
{
	KCheck(m_pPet);
	return m_pPet->m_iSmartnessPoint;
}

inline  SHorseGuid		Item::GetHorseGUID( )
{
	KCheck(m_pPet);
	return m_pPet->m_GUID;
}


inline	int32				Item::GetDataID()					
{
	KCheck(m_pPet);
	return m_pPet->m_nDataID;
}
inline  const char*		Item::GetName()	const				
{
	KCheck(m_pPet);
	return m_pPet->m_szName;	
}
inline  const char*		Item::GetNick() const				
{
	KCheck(m_pPet);
	return m_pPet->m_szNick;
}
inline  int32				Item::GetLevel() const				
{
	KCheck(m_pPet);
	return m_pPet->m_nLevel;
}

inline  int32				Item::GetNeedLevel() const				
{
	KCheck(m_pItem);
	return m_pItem->GetEquipData()->m_NeedLevel;
}

inline  int32				Item::GetTakeLevel() const			
{
	KCheck(m_pPet);
	return m_pPet->m_nTakeLevel;
}

inline  int32				Item::GetAttackType() const			
{
	KCheck(m_pPet);
	return m_pPet->m_nAttackType;
}
inline  int32				Item::GetAIType() const				
{
	KCheck(m_pPet);
	return m_pPet->m_AIType;
}
inline  const SCampData *Item::GetCampData() const				
{
	KCheck(m_pPet);
	return &(m_pPet->m_CampData);
}
inline  uchar			Item::GetGeneration() const				
{
	KCheck(m_pPet);
	return m_pPet->m_byGeneration;
}
inline  uchar			Item::GetHappiness() const				
{
	KCheck(m_pPet);
	return m_pPet->m_byHappiness;
}


inline  int32 			Item::GetMindPoint() const			
{
	KCheck(m_pPet);
	return m_pPet->m_iMindPoint;
}

inline  int32 			Item::GetConstitutionPoint() const		
{
	KCheck(m_pPet);
	return m_pPet->m_iConstitutionPoint;
}


inline  float			Item::GetGrowRate() const				
{
	KCheck(m_pPet);
	return m_pPet->m_fGrowRate;
}
inline  int32				Item::GetRemainPoint() const			
{
	KCheck(m_pPet);
	return m_pPet->m_nRemainPoint;
}
inline  int32				Item::GetExp() const					
{
	KCheck(m_pPet);
	return m_pPet->m_nExp;
}
inline  int32				Item::GetLvl1Attr(PLAYER_PROPERTY_LEVEL1 type)const
{
	KCheck(m_pPet);
	return m_pPet->m_BaseAttrLevel1.Get(type);
}
inline  SHorseSkill		Item::GetSkill(uint32 SkillIndex)		
{
	KCheck(m_pPet);
	KCheck(SkillIndex<PET_MAX_SKILL_COUNT);
	return m_pPet->m_SkillList[SkillIndex];
}

inline  int32				Item::GetStallOrder() const					
{
	KCheck(m_pPet);
	return m_pPet->m_iStallOrder;
}


uchar						Item::GetItemLevel()		const				
{
	KCheck(m_pItem);

	switch( m_pItem->ItemClass() )
	{
	case ICLASS_TASKITEM:
		{
			TASKITEM_INFO_TB* pTaskTable = g_ItemTab.GetTaskItemInfoTB( m_pItem->m_ItemIndex );
			if ( pTaskTable )
			{
				return pTaskTable->m_nLevel;
			}

		}
		break;
	case ICLASS_COMITEM:
		{
			SMiscItemInfoTab* pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
			if(pComTable)
			{
				return pComTable->m_nLevel;
			}
		}
		break;
	default:
		{
			KCheck( FALSE );
		}
		break;
	}


	return -1;
}

inline uchar Item::GetMedicLevel(void)
{
	KCheck(m_pItem);

	switch( m_pItem->ItemClass())
	{
		case ICLASS_MATERIAL:
		case ICLASS_COMITEM:
		case ICLASS_TASKITEM:
			{
				return m_pItem->GetMedicData()->m_Level;
			}
			break;
		default:
			{
				KCheck( FALSE );
			}
			break;
	}

	return 0;
}

inline void	Item::SetMedicLevel(const uchar cLevel)
{
	KCheck(m_pItem);
	KCheck(cLevel <= MEDIC_MAX_LEVEL);

	switch( m_pItem->ItemClass())
	{
		case ICLASS_MATERIAL:
		case ICLASS_COMITEM:
		case ICLASS_TASKITEM:
			{
				m_pItem->GetMedicData()->m_Level = cLevel;
			}
			break;
		default:
			{
				KCheck( FALSE );
			}
			break;
	}

	return;
}

///////////////////////////////////////////////
// desc:	对道具以及坐骑统一获取天赋等级的方法实现
// param:	无
// return:	返回道具天赋等级
// auth:	crj
// date:	2010-8-23
///////////////////////////////////////////////
int32 Item::GetReqInherenceLevel()
{	
	// 对物品和坐骑进行不同的数据读取
	if (m_Type == IDT_ITEM)
	{
		KCheck(m_pItem);

		// 分不同的道具大类型去不同的表进行读取
		switch (m_pItem->ItemClass())
		{
		case ICLASS_COMITEM:
		case ICLASS_MATERIAL:
			{
				SMiscItemInfoTab *pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
				if(pComTable)
				{
					return pComTable->m_iReqInherenceLevel;
				}
			}
			break;
		case ICLASS_EQUIP:
			{
				SEquipTab *pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
				if(pEquipTable)
				{
					return pEquipTable->m_iReqInherenceLevel;
				}
			}
			break;
		default: // 其他标的任务,珠宝,扩展背包类型（都是物品索引）默认返回 -1
			{
				return -1;
			}
			break;
		}
	}
	
	return -1;
}

///////////////////////////////////////////////
// desc:	对道具以及坐骑统一获取个人等级的方法实现
// param:	无
// return:	返回道具个人等级
// auth:	crj
// date:	2010-8-23
///////////////////////////////////////////////
int32 Item::GetReqPersonLevel()
{
	// 原理同天赋等级
	if (m_Type == IDT_ITEM)
	{
		KCheck(m_pItem);

		switch (m_pItem->ItemClass())
		{
		case ICLASS_COMITEM:
		case ICLASS_MATERIAL:
			{
				SMiscItemInfoTab *pComTable = g_ItemTab.GetCommItemInfoTB(m_pItem->m_ItemIndex);
				if(pComTable)
				{
					return pComTable->m_iReqPersonLevel;
				}
			}
			break;
		case ICLASS_EQUIP:
			{
				SEquipTab *pEquipTable = g_ItemTab.GetEquipTB(m_pItem->m_ItemIndex);
				if(pEquipTable)
				{
					return pEquipTable->m_iReqPersonLevel;
				}
			}
			break;
		default:
			{
				return -1;
			}
			break;
		}
	}
	
	return -1;
}

int32 Item::GetEquipConstCount()
{
	KCheck(m_pItem);

	switch( m_pItem->ItemClass())
	{
	case ICLASS_EQUIP:
		{
			return m_pItem->GetEquipData()->m_ConstCount;
		}
		break;
	default:
		{
			KCheck( FALSE );
		}
		break;
	}

	return 0;

}
SItemConstInfo*	Item::GetEquipConst()
{
	KCheck(m_pItem);

	switch( m_pItem->ItemClass())
	{
	case ICLASS_EQUIP:
		{
			return m_pItem->GetEquipData()->m_pConst;
		}
		break;
	default:
		{
			KCheck( FALSE );
		}
		break;
	}

	return NULL;

}
#endif					
						
						
						
