#include "stdafx.h"
#include "ItemBoxManager.h"

#include "ItemBox.h"
#include "map/map_info.h"
#include "map/game_map.h"
#include "TabDefine_Map_Item.h"
#include "Item_Ruler.h"
#include "BaseTool.h"
#include "server_settting.h"

#define DEFAULT_ITEMBOX_MANAGER_SIZE	512
#define ITEMBOXMANAGER_LOGIC_INTERVAL	500

/*
 =======================================================================================================================
 =======================================================================================================================
 */

GatherBoxManager::GatherBoxManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TotalSize = DEFAULT_ITEMBOX_MANAGER_SIZE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;

	m_pItemBoxObjID = new ObjID_t[DEFAULT_ITEMBOX_MANAGER_SIZE];
	KCheck(m_pItemBoxObjID);

	memset(m_pItemBoxObjID, -1, sizeof(ObjID_t) * DEFAULT_ITEMBOX_MANAGER_SIZE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
GatherBoxManager::~GatherBoxManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TotalSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;

	KSafeDelete_ARRAY(m_pItemBoxObjID);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GatherBoxManager::Init()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TotalSize = DEFAULT_ITEMBOX_MANAGER_SIZE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;
	KCheck(m_pItemBoxObjID);
	memset(m_pItemBoxObjID, -1, sizeof(ObjID_t) * DEFAULT_ITEMBOX_MANAGER_SIZE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemBox *GatherBoxManager::GenItemBox()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemBox	*pIB = new ItemBox;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pIB->Clear();

	return pIB;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemBox *GatherBoxManager::GetItemBox(ObjID_t ObjID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemBox	*pItemBox = static_cast<ItemBox *>(GetMap()->GetSpecificObjByID(ObjID));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemBox);
	return pItemBox;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherBoxManager::RemoveAllItemBox()
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCount = m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < iCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemBox *pItemBox = GetItemBox(m_pItemBoxObjID[0]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pItemBox)
		{
			pItemBox->Recycle();
		}
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GatherBoxManager::RecycleItemBox(ObjID_t ObjID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemBox	*pItemBox = GetItemBox(ObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemBox);

	pItemBox->SetActiveFlag(FALSE);
	pItemBox->Clear();

	GetMap()->DeleteObject(pItemBox);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherBoxManager::Add(ItemBox *pItemBox)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	objId = pItemBox->GetID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pItemBoxObjID[m_Count] = objId;
	pItemBox->SetItemBoxID(m_Count);

	m_Count++;

	KCheck(m_Count <= MAX_ITEM_BOX_POOL);

	if(m_Count >= m_TotalSize)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	ret = Resize(DEFAULT_ITEMBOX_MANAGER_SIZE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!ret)
		{
			KCheck(FALSE);
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
BOOL GatherBoxManager::Resize(uint32 iSize)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	*pNew = new ObjID_t[m_TotalSize + iSize];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pNew)
	{
		KCheck(pNew);
		return FALSE;
	}

	memcpy(pNew, m_pItemBoxObjID, sizeof(ObjID_t) * m_TotalSize);
	m_TotalSize = m_TotalSize + iSize;

	KSafeDelete_ARRAY(m_pItemBoxObjID);

	m_pItemBoxObjID = pNew;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherBoxManager::Remove(ObjID_t ObjID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemBox	*pItemBox = GetItemBox(ObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItemBox);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	index = (uint32) (pItemBox->GetItemBoxID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(index < m_Count);

	KCheck(m_Count > 0);
	KCheck(m_pItemBoxObjID[index] == ObjID);

	m_pItemBoxObjID[index] = m_pItemBoxObjID[m_Count - 1];
	pItemBox->SetItemBoxID(INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemBox *pNewItemBox = GetItemBox(m_pItemBoxObjID[index]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pNewItemBox);
	pNewItemBox->SetItemBoxID(index);
	m_Count--;
	KCheck(m_Count >= 0);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GatherBoxManager::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!m_LogicTimer.IsSetTimer())
	{
		m_LogicTimer.BeginTimer(ITEMBOXMANAGER_LOGIC_INTERVAL, uTime);
		return TRUE;
	}

	if(!m_LogicTimer.CountingTimer(uTime)) return TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	uint32	nCount = m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < nCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemBox *pItemBox = GetItemBox(m_pItemBoxObjID[i]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pItemBox == NULL) continue;

		_NET_TRY
		{
			pItemBox->HeartBeat(uTime);
		}

		_NET_CATCH
		{
			QLOGGER_CODEHOLDER();
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemBox *GatherBoxManager::CreateMonsterDropItembox(GLPos *pPos)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemBox	*pItemBox = (ItemBox *) (GetMap()->NewObject(Object::OBJECT_CLASS_ITEM_BOX));
	_INIT_ITEMBOX_OBJECT	initParam;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	initParam.m_uCreateTime = GET_TIME().TickCount();
	initParam.m_uRecycleTime = g_Config.m_ConfigInfo.m_DropBoxRecycleTime;
	initParam.m_Pos = *pPos;
	initParam.m_ItemBoxType = ITYPE_DROPBOX;
	initParam.m_bRecycle = TRUE;
	pItemBox->Init(&initParam);
	return pItemBox;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemBox *GatherBoxManager::CreateGatherPointItemBox(int32 IBType, int32 iCycleTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemBox	*pIB = GenItemBox();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ITYPE_DROPBOX != IBType);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_INIT_ITEMBOX_OBJECT	initParam;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	initParam.m_uCreateTime = GET_TIME().TickCount();
	initParam.m_uRecycleTime = iCycleTime;
	initParam.m_ItemBoxType = IBType;
	initParam.m_bRecycle = iCycleTime != -1;
	pIB->Init(&initParam);

	return pIB;

	__UNGUARD__ return NULL;
}
