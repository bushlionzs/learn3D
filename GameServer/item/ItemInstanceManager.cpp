/*$T MapServer/Server/Obj/ItemInstanceManager.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "ItemInstanceManager.h"

#include "ItemInstance.h"
#include "map/map_info.h"
#include "map/game_map.h"
#include "gameobject/ObjectManager.h"
#include "TabDefine_Map_Item.h"
#include "Item_Ruler.h"
#include "BaseTool.h"
#include "map/MapDropPosManager.h"
#include "ItemInstance.h"
#include "server_settting.h"

#define DEFAULT_OBJ_ITEM_MANAGER_SIZE	500
#define OBJ_ITEMMANAGER_LOGIC_INTERVAL	500

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ItemInstanceManager::ItemInstanceManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TotalSize = DEFAULT_OBJ_ITEM_MANAGER_SIZE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;

	m_pObj_ItemID = new ObjID_t[DEFAULT_OBJ_ITEM_MANAGER_SIZE];
	KCheck(m_pObj_ItemID);

	memset(m_pObj_ItemID, -1, sizeof(ObjID_t) * DEFAULT_OBJ_ITEM_MANAGER_SIZE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemInstanceManager::~ItemInstanceManager()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TotalSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;

	KSafeDelete_ARRAY(m_pObj_ItemID);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstanceManager::Init()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_TotalSize = DEFAULT_OBJ_ITEM_MANAGER_SIZE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;
	KCheck(m_pObj_ItemID);
	memset(m_pObj_ItemID, -1, sizeof(ObjID_t) * DEFAULT_OBJ_ITEM_MANAGER_SIZE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemInstance *ItemInstanceManager::GenObj_Item()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemInstance	*pIB = new ItemInstance;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pIB->Clear();

	return pIB;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemInstance *ItemInstanceManager::GetObj_Item(ObjID_t ObjID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemInstance	*pItem = static_cast<ItemInstance *>(GetMap()->GetObjManager()->GetObj(ObjID));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	return pItem;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstanceManager::RemoveAllObj_Item()
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	iCount = m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < iCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemInstance	*pObj_Item = GetObj_Item(m_pObj_ItemID[0]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pObj_Item)
		{
			pObj_Item->Recycle();
		}
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstanceManager::RecycleObj_Item(ObjID_t ObjID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemInstance	*pObj_Item = GetObj_Item(ObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pObj_Item);
	pObj_Item->SetActiveFlag(FALSE);
	pObj_Item->Clear();

	GetMap()->DeleteObject(pObj_Item);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstanceManager::Add(ItemInstance *pObj_Item)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_Count <= MAX_OBJ_ITEM_POOL);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_Count >= m_TotalSize)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	ret = Resize(DEFAULT_OBJ_ITEM_MANAGER_SIZE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!ret)
		{
			KCheck(FALSE);
			return FALSE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t objId = pObj_Item->GetID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pObj_ItemID[m_Count] = objId;
	pObj_Item->SetObj_ItemID(m_Count);

	m_Count++;

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstanceManager::Resize(uint32 iSize)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	*pNew = new ObjID_t[m_TotalSize + iSize];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pNew)
	{
		KCheck(pNew);
		return FALSE;
	}

	memset(pNew, -1, sizeof(ObjID_t) * (m_TotalSize + iSize));

	memcpy(pNew, m_pObj_ItemID, sizeof(ObjID_t) * m_TotalSize);
	m_TotalSize = m_TotalSize + iSize;

	KSafeDelete_ARRAY(m_pObj_ItemID);

	m_pObj_ItemID = pNew;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstanceManager::Remove(ObjID_t ObjID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ItemInstance	*pObj_Item = GetObj_Item(ObjID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pObj_Item);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	index = (uint32) (pObj_Item->GetObj_ItemID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(index < m_Count);

	KCheck(m_Count > 0);
	KCheck(m_pObj_ItemID[index] == ObjID);

	m_pObj_ItemID[index] = m_pObj_ItemID[m_Count - 1];
	pObj_Item->SetObj_ItemID(INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstance	*pNewObj_Item = GetObj_Item(m_pObj_ItemID[index]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pNewObj_Item);
	pNewObj_Item->SetObj_ItemID(index);
	m_Count--;
	KCheck(m_Count >= 0);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstanceManager::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!m_LogicTimer.IsSetTimer())
	{
		m_LogicTimer.BeginTimer(OBJ_ITEMMANAGER_LOGIC_INTERVAL, uTime);
		return TRUE;
	}

	if(!m_LogicTimer.CountingTimer(uTime)) return TRUE;

	uint32	nCount = m_Count;

	for(uint32 i = 0; i < nCount; i++)
	{
		ItemInstance	*pObj_Item = GetObj_Item(m_pObj_ItemID[i]);

		if(pObj_Item == nullptr) continue;

		pObj_Item->HeartBeat(uTime);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Obj_ItemContaner ItemInstanceManager::CaculateItemDropFromMonster
(
	uint32	iKillerLevel,
	uint32	iMonsterID,
	float	fControlValue,
	int32	iFadeoutType
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Obj_ItemContaner	IBContaner;
	__GUARD__ Obj_ItemRuler ibr;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ibr.CreateItemFromMonsterDrop(iMonsterID, iKillerLevel, iFadeoutType, fControlValue, IBContaner);

	return IBContaner;
	__UNGUARD__ return IBContaner;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemInstance *ItemInstanceManager::CreateMonsterDropObj_Item(GLPos *pPos, SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(!pItem->IsNullType());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstance		*pObj_Item = (ItemInstance *) (GetMap()->NewObject(Object::OBJECT_CLASS_DROP_ITEM));
	MapDropPosManager	*pDropPosMag = pObj_Item->GetMap()->GetMapDropPosManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDropPosMag);

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	_OBJ_ITEM_INIT	initParam;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	initParam.m_uCreateTime = GetMap()->GetCurHeartBeatTime();
	initParam.m_uRecycleTime = g_Config.m_ConfigInfo.m_DropBoxRecycleTime;
	initParam.m_Pos = *pPos;
	initParam.m_ItemType = ITYPE_MONSTERDROP_OBJ_ITEM;
	initParam.m_bRecycle = TRUE;
	pObj_Item->Init(&initParam);
	pObj_Item->SaveObj_Item(pItem);
	pObj_Item->EnablePickOwnerTime();

	pDropPosMag->SetDropPos(pPos->m_fX, pPos->m_fZ);
	return pObj_Item;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemInstance *ItemInstanceManager::CreatePersonDropItemInstance(GLPos *pPos, SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pItem);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(!pItem->IsNullType());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstance		*pObj_Item = (ItemInstance *) (GetMap()->NewObject(Object::OBJECT_CLASS_DROP_ITEM));
	MapDropPosManager	*pDropPosMag = pObj_Item->GetMap()->GetMapDropPosManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDropPosMag);

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	_OBJ_ITEM_INIT	initParam;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	initParam.m_uCreateTime = GetMap()->GetCurHeartBeatTime();
	initParam.m_uRecycleTime = g_Config.m_ConfigInfo.m_DropBoxRecycleTime;
	initParam.m_Pos = *pPos;
	initParam.m_ItemType = ITYPE_PERSONDROP_OBJ_ITEM;
	initParam.m_bRecycle = TRUE;
	pObj_Item->Init(&initParam);
	pObj_Item->SaveObj_Item(pItem);
	pObj_Item->EnablePickOwnerTime();

	pDropPosMag->SetDropPos(pPos->m_fX, pPos->m_fZ);
	return pObj_Item;

	__UNGUARD__ return NULL;
}
