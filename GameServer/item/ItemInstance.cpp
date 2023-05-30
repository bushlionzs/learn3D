#include "stdafx.h"
#include "ItemInstance.h"
#include "map/game_map.h"
#include "BaseTool.h"
#include "server_settting.h"
#include "TabDefine.h"
#include "Item_Interface.h"
#include "map/MapDropPosManager.h"
#include "gameobject/Player.h"
#include "gameobject/PlayerManager.h"
#include "net/messages/SCNewItem.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ItemInstance::ItemInstance()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemInstance::~ItemInstance()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstance::Init(const _INIT_OBJECT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	BOOL		bResult = Object::Init(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_OBJ_ITEM_INIT	*pItemInit = (_OBJ_ITEM_INIT *) pInit;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pItemInit == NULL) return FALSE;

	m_OwnerCount = 0;
	m_OwnerCount = 0;
	m_DropObjID = INVALID_ID;
	m_CreateTime = pItemInit->m_uCreateTime;
	m_RecycleTime = pItemInit->m_uRecycleTime;
	m_Obj_ItemType = pItemInit->m_ItemType;
	m_PickOwnerTime = g_Config.m_ConfigInfo.m_DropProtectTime;
	if(pItemInit->m_bRecycle)
	{
		m_RecycleTimer.BeginTimer(m_RecycleTime, m_CreateTime);
	}
	else
	{
		m_RecycleTimer.Clear();
	}

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool ItemInstance::HeartBeat(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Object::HeartBeat(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	UpdateGrid();

	if(m_RecycleTimer.CountingTimer(uTime))
	{
		Recycle();
		return TRUE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
NetPacket*ItemInstance::CreateNewObjMsg(void)
{
	SItem* pItem = GetObj_Item();

	SCNewItem* packet = new SCNewItem;

	packet->setObjId(GetID());
	packet->setSceneId(GetMap()->MapID());
	packet->setItemIndex(pItem->m_ItemIndex);
	packet->setItemCount(pItem->GetItemCount());
	const GLPos* pos = GetGLPos();
	packet->setPosition(pos->m_fX, pos->m_fZ);
	return packet;
}

void	ItemInstance::DestroyNewObjMsg(NetPacket* pPacket)
{
	
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
ePICK_RESULT_CODE ItemInstance::CanPick(GUID_t nPickID, ObjID_t HumanID,SItem *pItem)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
	PlayerManager* playerManager = GetMap()->GetPlayerManager();
	Player	*pPlayer = playerManager->GetPlayer(HumanID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pItem);
	KCheck(pPlayer);

	uchar uClass = pItem->ItemClass();
	
	switch(uClass)
	{
	case ICLASS_EQUIP:
		{
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(pItem->m_ItemIndex);
			if ( pGET )
			{
				if ( pGET->m_minPickLevel > pPlayer->GetLevel() )
					return PICK_LEVEL_LIMIT;
			}
		}
		break;

	case ICLASS_MATERIAL:
		{
			SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(pItem->m_ItemIndex);
			if ( pGET )
			{
				if ( pGET->m_minPickLevel > pPlayer->GetLevel() )
					return PICK_LEVEL_LIMIT;
			}
		}
		break;

	case ICLASS_COMITEM:
		{
			SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(pItem->m_ItemIndex);
			if ( pGET )
			{
				if ( pGET->m_minPickLevel > pPlayer->GetLevel() )
					return PICK_LEVEL_LIMIT;
			}
		}
		break;

	case ICLASS_GEM:
		{
			SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(pItem->m_ItemIndex);
			if ( pGET )
			{
				if ( pGET->m_minPickLevel > pPlayer->GetLevel() )
					return PICK_LEVEL_LIMIT;
			}
		}
		break;

	case ICLASS_TASKITEM:
		break;

	case ICLASS_EXTRABAG:
		{
			EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(pItem->m_ItemIndex);
			if ( pGET )
			{
				if ( pGET->m_minPickLevel > pPlayer->GetLevel() )
					return PICK_LEVEL_LIMIT;
			}
		}
		break;
	}

	if(GetType() == ITYPE_MONSTERDROP_OBJ_ITEM)
	{
		return PICK_SUCCESS;
	}
	else if(GetType() == ITYPE_PERSONDROP_OBJ_ITEM)
	{
		return PICK_SUCCESS;
	}

	__UNGUARD__ return PICK_INVALID_OWNER;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemInstance::IsCanViewMe(const Object *pObj)
{
	__GUARD__ if(!pObj) return FALSE;

	if(pObj->GetObjType() == OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player	*pPlayer = (Player *) pObj;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!pPlayer) return FALSE;

		return TRUE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstance::EnablePickOwnerTime()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_FinalPickTime = GET_TIME().TickCount() + m_PickOwnerTime;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ItemInstance::GetPickOwnerTime()
{
	return m_PickOwnerTime;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstance::SetPickOwnerTime(uint32 uPickTime)
{
	m_PickOwnerTime = uPickTime;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstance::Recycle()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GLPos	worldPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	worldPos.m_fX = GetGLPos()->m_fX;
	worldPos.m_fZ = GetGLPos()->m_fZ;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	Type = GetType();
	GameMap	*pMap = GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapDropPosManager	*pDropPosMag = pMap->GetMapDropPosManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDropPosMag);

	
	SetActiveFlag(FALSE);
	pMap->DeleteObject(this);

	if((Type == ITYPE_MONSTERDROP_OBJ_ITEM) || (Type == ITYPE_PERSONDROP_OBJ_ITEM))
	{
		pDropPosMag->ClearDropPos(worldPos.m_fX, worldPos.m_fZ);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstance::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_CreateTime = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_RecycleTime = 0;
	m_Obj_ItemType = -1;
	m_RecycleTimes = 0;

	m_PickOwnerTime = 0;

	m_FinalPickTime = 0;
	for(int32 i = 0; i < MAX_TEAM_MEMBER; ++i)
	{
		m_OwnerId[i] = INVALID_ID;
	}

	m_DropObjID = INVALID_ID;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScriptID_t ItemInstance::GetScriptID() const
{
	__GUARD__ if(m_Obj_ItemType == ITYPE_DROPBOX)
	{
		return INVALID_ID;
	}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//_GATHER_POINT_INFO	*pGET = g_GatherPointInfoTab.Get(m_Obj_ItemType);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//KCheck(pGET);
	//if(pGET->m_ScriptID > 0)
	//{
	//	return pGET->m_ScriptID;
	//}

	return INVALID_ID;

	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemInstance::SaveObj_Item(SItem *pItem)
{
	KCheck(pItem);
	memcpy(&m_Obj_Item, pItem, sizeof(SItem));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SItem *ItemInstance::GetObj_Item()
{
	return &m_Obj_Item;
}
