/*$T MapServer/Server/Item/HorseContainer.cpp GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_HorseContainer.h"
#include "Archive/PlayerDB.h"

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetItemLayedNum(int32 nIndex, int32 nCount)
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
BOOL HorseContainer::DecItemLayedNum(int32 nIndex, int32 nCount)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::IncItemLayedNum(int32 nIndex, int32 nCount)
{
	__GUARD__	KCheck(0);

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetHorseGUID(int32 nIndex, SHorseGuid GUID)
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_GUID = GUID;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetDataID(int32 nIndex, int32 ID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_nDataID = ID;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetName(int32 nIndex, const char *pName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);
	KCheck(pName);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;
	strncpy(pDestItem->GetPet()->m_szName, pName, MAX_CHARACTER_NAME);
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetNick(int32 nIndex, const char *pNick)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);
	KCheck(pNick);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	memset(pDestItem->GetPet()->m_szNick, 0, sizeof(char) * MAX_NICK_NAME);
	strncpy(pDestItem->GetPet()->m_szNick, pNick, MAX_NICK_NAME - 1);
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL HorseContainer::Init(const SItemContainerInit *pInit)
{
	__GUARD__ if(!ItemContainer::Init(pInit)) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SHorseContainerInit *pHICInit = static_cast<const SHorseContainerInit *>(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pHICInit == NULL) return FALSE;

	KCheck(pHICInit->m_pPlayerDB);

	m_ICTType = pHICInit->m_ICTType;
	m_pPlayerDB = pHICInit->m_pPlayerDB;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetItem(const int32 nIndex, const Item *pItem)
{
	__GUARD__;

	KCheck(m_pPlayerDB);

	BOOL bRet = ItemContainer::SetItem(nIndex, pItem);
	if(bRet)
	{
		SetDBDirty(nIndex);
	}

	return bRet;
	__UNGUARD__;
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::EraseItem(uint32_t uIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	BOOL		bRet = ItemContainer::EraseItem(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
BOOL HorseContainer::SetItemBind(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	BOOL		bRet = ItemContainer::SetItemBind(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
BOOL HorseContainer::SetItemValue(int32 nIndex, const _HORSE_DB_LOAD *pPet)
{
	__GUARD__;
	
	//相关指针检查
	KCheck(m_pPlayerDB);
	KCheck(pPet);

	//取得指定位置的数据,如果指定位置取出来的数据为空,报错
	Item *pDestItem = GetItem(nIndex);
	if(!pDestItem)
	{
		KCheck(FALSE);
		return FALSE;
	}

	//检查这个位置是否已经解锁
	if(pDestItem->IsLock())
	{
		KCheck(0);
		return FALSE;
	}

	//检查数据类型
	KCheck(pDestItem->GetDataType() == IDT_PET);

	//数据指针不得为空
	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	//对这个位置的存储索引进行处理,如果大于最大携带骑乘数量,则为骑乘银行相关处理
	int32 iOldStallOrder = pDestItem->GetPet()->m_iStallOrder;
	if(iOldStallOrder >= PLAYER_PET_MAX_COUNT && iOldStallOrder < PLAYER_PET_MAX_COUNT + PLAYER_BANKPET_MAX_COUNT)
	{
		*pDestItem->GetPet() = *pPet;
		pDestItem->GetPet()->m_iStallOrder = iOldStallOrder;
		SetDBDirty(nIndex);
		return TRUE;
	}

	//是不是新宠物
	BOOL bNewPet = pDestItem->GetPet()->m_GUID.IsNull();

	//是否是删除宠物操作
	BOOL bDelPet = pPet->m_GUID.IsNull();

	//???先赋值?
	*pDestItem->GetPet() = *pPet;
	
	if(bDelPet)
	{
		//删除宠物的处理
		ResetHorseStallOrder(iOldStallOrder);
	}
	else if(bNewPet)
	{
		//新宠物的处理
		pDestItem->GetPet()->m_iStallOrder = GetValidCount() - 1;
	}
	else
	{
		//删除宠物和新增宠物之外是啥操作?覆盖操作?
		pDestItem->GetPet()->m_iStallOrder = iOldStallOrder;
	}

	//宠物标记置脏
	SetDBDirty(nIndex);

	//返回成功
	return TRUE;
	__UNGUARD__;
	return FALSE;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetLevel(int32 nIndex, int32 level)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_nLevel = level;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetTakeLevel(int32 nIndex, int32 takeLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_nTakeLevel = takeLevel;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetAttackType(int32 nIndex, int32 attackType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_nAttackType = attackType;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetBHVClass(int32 nIndex, int32 AIType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_AIType = AIType;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetCampData(int32 nIndex, const SCampData *pCamp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);
	KCheck(pCamp);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_CampData = *pCamp;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetPetType(int32 nIndex, uint8_t PetType)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::Set_Property_Generation(int32 nIndex, uint8_t Gen)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_byGeneration = Gen;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetHappiness(int32 nIndex, uint8_t byHappiness)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_byHappiness = byHappiness;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetStrengthPer(int32 nIndex, int32 strper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_iStrengthPerception = strper;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetSmartnessPer(int32 nIndex, int32 conper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_iSmartnessPerception = conper;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetMindPer(int32 nIndex, int32 dexper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);
	if ( pDestItem->GetPet() == NULL )
		return FALSE;
	pDestItem->GetPet()->m_iMindPerception = dexper;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetConstitutionPer(int32 nIndex, int32 intper)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_iConstitutionPerception = intper;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::Set_Property_GrowRate(int32 nIndex, float rate)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_fGrowRate = rate;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetRemainPoint(int32 nIndex, int32 rPoint)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_nRemainPoint = rPoint;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetMatingFlag(int32 iIndex, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
	BOOL		bRet = ItemContainer::SetMatingFlag(iIndex, bFlag);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bRet)
	{
		SetDBDirty(iIndex);
	}

	return bRet;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::SetDBDirty(int32 index)
{
	__GUARD__

		KCheck(m_pPlayerDB);

	switch(m_ICTType)
	{
	case ICT_HUMAN_PET_CONTAINER:
		{ 
			m_pPlayerDB->SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) CPROPERTY_ARCHIVE_PET); 
		}
		break;

	case ICT_HUMAN_BANKPET_CONTAINER:
		{
			m_pPlayerDB->SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) CPROPERTY_ARCHIVE_BANKPET);
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
BOOL HorseContainer::SetExp(int32 nIndex, uint32_t exp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_nExp = exp;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetLvl1Property(int32 nIndex, PLAYER_PROPERTY_LEVEL1 type, int32 value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_BaseAttrLevel1.Set(type, value);

	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::SetSkill(int32 nIndex, uint32_t SkillIndex, SHorseSkill skill)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);
	KCheck(SkillIndex < PET_MAX_SKILL_COUNT);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_SkillList[SkillIndex] = skill;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}
BOOL HorseContainer::ForceLockPet(int32 nIndex)
{
	return LockPet(nIndex);
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::LockPet(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_byLock = PET_LOCK;
	SetDBDirty(nIndex);

	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL HorseContainer::ForceUnlockPet(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_byLock = PET_UNLOCK;
	pDestItem->GetPet()->m_UnLockTime = 0;

	SetDBDirty(nIndex);

	return TRUE;
	__UNGUARD__ return FALSE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseContainer::UnlockPet(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pPlayerDB);
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

	KCheck(pDestItem->GetDataType() == IDT_PET);

	if ( pDestItem->GetPet() == NULL )
		return FALSE;

	pDestItem->GetPet()->m_byLock = PET_UNLOCKING;
	pDestItem->GetPet()->m_UnLockTime = GET_TIME().GetCTime() + g_Config.m_ConfigInfo.m_ItemUnLockCDTime;

	SetDBDirty(nIndex);

	return TRUE;
	__UNGUARD__ return FALSE;
}
