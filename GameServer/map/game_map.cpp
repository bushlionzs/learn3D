#include "stdafx.h"
#include "game_map.h"
#include "server_map_path.h"
#include "map_info.h"
#include "server_settting.h"
#include "map/Grid.h"
#include "map/MonsterManager.h"
#include "gameobject/Monster.h"
#include "ObjectManager.h"
#include "gameobject/PlayerManager.h"
#include "gameobject/Player.h"
#include "gameobject/Beastie.h"
#include "horse/Horse.h"
#include "gameobject/Behavior_Helper.h"
#include "net/messages/SCDelObject.h"
#include "net/net_message_manager.h"
#include "item/ItemInstanceManager.h"
#include "map/MapDropPosManager.h"
#include "item/ItemInstance.h"
#include "horse/HorseManager.h"
#include "item/ItemBoxManager.h"
#include "item/Item_GrowPointManager.h"
#include "BeastieManager.h"

#define DEFAULT_MANAGER_NPC_COUNT				(4096)
#define DEFAULT_MANAGER_HUMAN_COUNT				(2048)
#define DEFAULT_SINGLE_MANAGER_MONSTER_COUNT	(2048)
#define DEFAULT_SINGLE_MANAGER_PET_COUNT		(1024)
#define DEFAULT_SINGLE_MANAGER_HUMAN_COUNT		(2048)
#define DEFAULT_SINGLE_MANAGER_SPECIAL_COUNT	(1024)
#define DEFAULT_SINGLE_MANAGER_BUS_COUNT		(512)
#define MANAGER_HUMAN_LOGIC_INTERVAL			(0)
#define MANAGER_MONSTER_LOGIC_INTERVAL			(200)
#define MANAGER_PET_LOGIC_INTERVAL				(100)
#define MANAGER_SPECIAL_LOGIC_INTERVAL			(200)

GameMap::GameMap()
{
	
}

GameMap::~GameMap()
{

}

bool GameMap::initialize(MAP_CONFIG& config)
{
	mMapConfig = &config;
	mMapInfo = new MapInfo();
	
	if (FALSE == mMapInfo->Load(config.m_szNavFileName))
	{
		return false;
	}

	mMapID = config.m_MapID;
	m_MapType = config.m_Type;
	m_MapSafeLevel = config.m_cSecurityLevel;
	m_MapRestrictiveMode = config.m_cRestrictiveMode;
	m_Punish = config.m_bPunish;
	m_CanEnterPos.m_fX = config.m_DefaultX;
	m_CanEnterPos.m_fZ = config.m_DefaultZ;


	if (m_pGrid)
	{
		delete[] m_pGrid;
	}


	int32 cx = (int32)(mMapInfo->CX() / g_Config.m_ConfigInfo.m_ZoneSize);
	int32 cz = (int32)(mMapInfo->CZ() / g_Config.m_ConfigInfo.m_ZoneSize);

	if ((int32)mMapInfo->CX() % g_Config.m_ConfigInfo.m_ZoneSize > 0) cx++;
	if ((int32)mMapInfo->CZ() % g_Config.m_ConfigInfo.m_ZoneSize > 0) cz++;


	if (mGridInfo == nullptr)
		mGridInfo = new _GRID_INFO;
	mGridInfo->m_wZoneSize = (uint16)(cx * cz);
	mGridInfo->m_wZoneW = (uint16)cx;
	mGridInfo->m_wZoneH = (uint16)cz;

	m_pGrid = new Grid[mGridInfo->m_wZoneSize];


	for (uint16_t i = 0; i < mGridInfo->m_wZoneSize; i++)
	{
		m_pGrid[i].SetZoneID((GridID_t)i);
	}

	m_pPatrolPathMgr = new PatrolRoadsPointMgr;
	m_pPatrolPathMgr->Init(this);

	m_pObjManager = new ObjectManager;
	m_pHumanManager = new PlayerManager;
	m_pHumanManager->SetMap(this);
	m_pMonsterManager = new MonsterObjectManager;
	m_pMonsterManager->SetMap(this);
	m_pMonsterManager->LoadMonsterTab(config.m_szMonsterFileName, config.m_MapID);

	m_pItemInstanceManager = new ItemInstanceManager;
	KCheck(m_pItemInstanceManager);
	m_pItemInstanceManager->SetScene(this);
	m_pItemInstanceManager->Init();
	m_EventCore.Init(this);

	SCDelObject* packet = new SCDelObject;
	packet->setSceneId(mMapID);
	mDelObjectPacket = packet;

	m_pDropPosManager = new MapDropPosManager;
	m_pDropPosManager->Clear();
	m_pDropPosManager->SetMap(this);
	m_pDropPosManager->Init((int32_t)mMapInfo->CX(), (int32_t)mMapInfo->CZ());

	m_pBeastieManager = new BeastieManager;
	m_pBeastieManager->SetMap(this);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_INIT_SINGLEMANAGER_OBJECT	initBeastieManager;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	initBeastieManager.m_uLength = DEFAULT_SINGLE_MANAGER_PET_COUNT;
	initBeastieManager.m_pMap = this;
	initBeastieManager.m_uCurrentTime = GET_TIME().TickCount();
	initBeastieManager.m_uLogicInterval = MANAGER_PET_LOGIC_INTERVAL;
	m_pBeastieManager->Init(&initBeastieManager);

	m_pBeastieManager->Reset();
	m_pBeastieManager->LoadBeastie(mMapID);

	m_pHorseManager = new HorseManager;
	m_pHorseManager->SetMap(this);
	_INIT_SINGLEMANAGER_OBJECT	initGuardManager;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	initGuardManager.m_uLength = DEFAULT_SINGLE_MANAGER_PET_COUNT;
	initGuardManager.m_pMap = this;
	initGuardManager.m_uCurrentTime = GET_TIME().TickCount();
	initGuardManager.m_uLogicInterval = MANAGER_PET_LOGIC_INTERVAL;
	m_pHorseManager->Init(&initGuardManager);

	//可采集的物品管理器
	m_pItemBoxManager = new GatherBoxManager;
	KCheck(m_pItemBoxManager);
	m_pItemBoxManager->SetMap(this);
	m_pItemBoxManager->Init();


	m_GrowPointGroup = new GatherPointManager;
	m_GrowPointGroup->SetScene(this);

	m_GrowPointGroup->Clear();
	m_GrowPointGroup->Load(config.m_szGrowPointDataName, config.m_szGrowPointSetupName);

	return true;
}

void GameMap::update(uint64_t utime)
{
	m_BackUpTime = utime;
	m_pMonsterManager->HeartBeat(utime);
	m_pHumanManager->HeartBeat(utime);
	m_pItemInstanceManager->HeartBeat(utime);
	m_pBeastieManager->HeartBeat(utime);
	m_pHorseManager->HeartBeat(utime);
	m_pItemBoxManager->HeartBeat(utime);
	m_GrowPointGroup->HeartBeat(utime);
}

MAP_CONFIG* GameMap::getMapData()
{
	return mMapConfig;
}

BOOL	GameMap::RegisterArea(const Region* pArea)
{
	return true;
}

BOOL		GameMap::ObjGrid_Register(Object* pObj, GridID_t idZone)
{
	if (pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~*/
		OBJLIST listObj;
		/*~~~~~~~~~~~~*/

		ScanObj(idZone, MAX_REFESH_OBJ_GRID_RADIUS, &(listObj));

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player* pPlayer = ((Player*)(pObj));
		Object* pFindObj;
		uchar	i;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for (i = 0; i < listObj.m_Count; i++)
		{
			pFindObj = listObj.m_aObj[i];
			if (pFindObj->IsCanViewMe(pPlayer))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				NetPacket* pPacket = pFindObj->CreateNewObjMsg();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (pPacket != NULL)
				{
					pPlayer->sendPacket(pPacket);
				}
			}
		}
	}
	else
	{
		if (m_pHumanManager->GetCount() > 0)
		{
			NetPacket* pPacket = pObj->CreateNewObjMsg();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (pPacket != NULL)
			{
				NetManager::GetSingletonPtr()->sendNetMessage(pPacket);
			}
		}
		
	}

	GetGrid(idZone)->OnEvent_ObjectEnter(pObj);
	return true;
}

BOOL GameMap::ScanObj(GridID_t idZone, uint32 uZoneRadius, OBJLIST* plistOutObj)
{
	if (idZone == INVALID_ID)
	{
		return FALSE;
	}

	/*~~~~~~~*/
	VRECT	rc;
	/*~~~~~~~*/

	GetRectInRadius(&rc, uZoneRadius, idZone);

	plistOutObj->m_Count = 0;

	/*~~~~~~~~~*/
	int32	h, w;
	/*~~~~~~~~~*/

	for (h = rc.nStartz; h <= rc.nEndz; h++)
	{
		for (w = rc.nStartx; w <= rc.nEndx; w++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GridID_t	zid = w + h * mGridInfo->m_wZoneW;
			ObjectList* pList = GetGrid(zid)->GetObjList();
			_INIT_LIST_NODE* pPoint = pList->m_Head.m_pNext;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			while (pPoint != &pList->m_Tail)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Object* pObj = (Object*)(pPoint->m_pNode);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				pPoint = pPoint->m_pNext;

				plistOutObj->m_aObj[plistOutObj->m_Count++] = pObj;

				if (plistOutObj->m_Count >= plistOutObj->MAX_OBJ_LIST_SIZE) return TRUE;
			}
		}
	}

	return TRUE;
}


BOOL	GameMap::ScanObj_Sub(GridID_t idZoneA, GridID_t idZoneB, uint32 uZoneRadius, OBJLIST* plistOutObj)
{
	if (idZoneA == INVALID_ID || idZoneB == INVALID_ID)
	{
		KCheck
		(
			idZoneA != INVALID_ID
			&& idZoneB != INVALID_ID
			&& "Map::ScanObj_Sub( GridID_t idZoneA, GridID_t idZoneB, uint32 uZoneRadius, OBJLIST *plistOutObj )"
		);
		return FALSE;
	}

	/*~~~~~~~~~~~~~*/
	VRECT	rcA, rcB;
	/*~~~~~~~~~~~~~*/

	GetRectInRadius(&rcA, uZoneRadius, idZoneA);
	GetRectInRadius(&rcB, uZoneRadius, idZoneB);

	plistOutObj->m_Count = 0;

	/*~~~~~~~~~*/
	int32	h, w;
	/*~~~~~~~~~*/

	for (h = rcA.nStartz; h <= rcA.nEndz; h++)
	{
		for (w = rcA.nStartx; w <= rcA.nEndx; w++)
		{
			if (!rcB.IsContinue(w, h))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				GridID_t	zid = w + h * mGridInfo->m_wZoneW;
				ObjectList* pList = GetGrid(zid)->GetObjList();
				_INIT_LIST_NODE* pPoint = pList->m_Head.m_pNext;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				while (pPoint != &pList->m_Tail)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Object* pObj = (Object*)(pPoint->m_pNode);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					pPoint = pPoint->m_pNext;

					plistOutObj->m_aObj[plistOutObj->m_Count++] = pObj;

					if (plistOutObj->m_Count >= plistOutObj->MAX_OBJ_LIST_SIZE) return TRUE;
				}
			}
		}
	}

	return TRUE;
}

Grid* GameMap::GetGrid(GridID_t ZoneID)
{
	if (ZoneID != INVALID_ID)
		return &m_pGrid[ZoneID];
	else
		return NULL;
}
BOOL		GameMap::ObjGrid_Unregister(Object* pObj, GridID_t idZone)
{
	if (pObj == NULL)
	{
		KCheck(pObj == NULL && "Map::ObjGrid_Unregister");
		return FALSE;
	}

	if (idZone < 0 || idZone >= mGridInfo->m_wZoneSize)
	{
		//KCheck(idZone >= 0 && idZone < m_GridInfo.m_wZoneSize && "Map::ObjGrid_Unregister");
		return FALSE;
	}

	if (GetGrid(idZone)->OnEvent_ObjectLeave(pObj) == FALSE)
	{
		QLogSystem::QUICK_LOG
		(
			QUICK_LOG_ERROR,
			"ObjGrid_Unregister Error! mapid=%d, zone=%d",
			mMapID,
			idZone
		);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SCDelObject* pPacket = new SCDelObject;
	pPacket->setSceneId(mMapID);
	pPacket->setObjectId(pObj->GetID());
	
	NetManager::GetSingletonPtr()->sendNetMessage(pPacket);

	//if (pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	//{
	//	/*~~~~~~~~~~~~*/
	//	OBJLIST listObj;
	//	/*~~~~~~~~~~~~*/

	//	ScanObj(idZone, MAX_REFESH_OBJ_GRID_RADIUS, &(listObj));

	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	Player* pPlayer = ((Player*)(pObj));
	//	Object* pFindObj;
	//	uchar	i;
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	for (i = 0; i < listObj.m_Count; i++)
	//	{
	//		pFindObj = listObj.m_aObj[i];
	//		if (pFindObj->IsCanViewMe(pPlayer))
	//		{
	//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//			IMessage* pPacket = pFindObj->CreateDeleteObjPacket();
	//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//			if (pPacket != NULL)
	//			{
	//				pPlayer->GetConnector()->SendPacket(pPacket);

	//				pFindObj->DestroyNewObjMsg(pPacket);
	//			}
	//		}
	//	}
	//}

	return TRUE;
}

BOOL		GameMap::ObjGrid_Changed(Object* pObj, GridID_t idNew, GridID_t idOld)
{
	if (pObj == NULL)
	{
		KCheck(pObj == NULL && "Map::ObjGrid_Changed");
		return FALSE;
	}

	if (idOld < 0 || idOld >= mGridInfo->m_wZoneSize)
	{
		//KCheck(idOld >= 0 && idOld < m_GridInfo.m_wZoneSize && "Map::ObjGrid_Changed");
	}
	else
	{
		if (GetGrid(idOld)->OnEvent_ObjectLeave(pObj) == FALSE)
		{
			QLogSystem::QUICK_LOG
			(
				QUICK_LOG_ERROR,
				"ObjGrid_Changed Error! mapid=%d, zoneold=%d, zonenew=%d",
				mMapID,
				idOld,
				idNew
			);
		}
	}

		

	if (idNew < 0 || idNew >= mGridInfo->m_wZoneSize)
	{
		//KCheck(idOld >= 0 && idOld < m_GridInfo.m_wZoneSize && "Map::ObjGrid_Changed");
	}
	else
	{

		if (pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			NetPacket* pPacket = pObj->CreateNewObjMsg();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (pPacket != NULL)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~*/
				PLAYERLIST	listHuman;
				/*~~~~~~~~~~~~~~~~~~~~~~*/

				if (idOld != INVALID_ID)
				{
					ScanHuman_Sub(idNew, idOld, MAX_REFESH_OBJ_GRID_RADIUS, &(listHuman));
				}
				else
				{
					ScanPlayer(idNew, MAX_REFESH_OBJ_GRID_RADIUS, &(listHuman));
				}

				/*~~~~~~~~~~~~~~~~~*/
				uchar	yNewCount, i;
				/*~~~~~~~~~~~~~~~~~*/

				yNewCount = 0;
				for (i = 0; i < listHuman.m_Count; i++)
				{
					if (pObj->IsCanViewMe(listHuman.m_aHuman[i]))
					{
						listHuman.m_aHuman[yNewCount++] = listHuman.m_aHuman[i];
					}
				}

				listHuman.m_Count = yNewCount;

				if (listHuman.m_Count > 0)
				{
					NetManager::GetSingletonPtr()->sendNetMessage(pPacket);
				}
				else
				{
					delete pPacket;
				}
			}
			else
			{
				KCheck
				(
					pPacket == NULL
					&& "Map::ObjGrid_Changed 刷新Obj创建消息到客户端 CreateNewObjMsg return NULL"
				);
				return FALSE;
			}
		}
		else
		{
			/*~~~~~~~~~~~~*/
			OBJLIST listObj;
			/*~~~~~~~~~~~~*/

			if (idOld != INVALID_ID)
			{
				ScanObj_Sub(idNew, idOld, MAX_REFESH_OBJ_GRID_RADIUS, &(listObj));
			}
			else
			{
				ScanObj(idNew, MAX_REFESH_OBJ_GRID_RADIUS, &(listObj));
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Player* pPlayer = ((Player*)(pObj));
			Object* pFindObj;
			uchar	i;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for (i = 0; i < listObj.m_Count; i++)
			{
				pFindObj = listObj.m_aObj[i];
				if (pFindObj->IsCanViewMe(pPlayer))
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					NetPacket* pPacket = pFindObj->CreateNewObjMsg();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if (pPacket != NULL)
					{
						NetManager::GetSingletonPtr()->sendNetMessage(pPacket);

						pFindObj->DestroyNewObjMsg(pPacket);
					}
					else
					{
						KCheck
						(
							pPacket == NULL
							&& "Map::ObjGrid_Changed 把新进入的区域中的所有角色发往新进来的客户端 CreateDeleteObjPacket return NULL"
						);
						return FALSE;
					}
				}
			}
		}

		GetGrid(idNew)->OnEvent_ObjectEnter(pObj);
	}

	return TRUE;
}

GridID_t	GameMap::CalcGridID(const GLPos* pos)
{
	if (pos == NULL || pos->m_fX < 0.f || pos->m_fZ < 0.f)
	{
		return INVALID_ID;
	}


	uint32_t	uX = (uint32_t)(pos->m_fX / g_Config.m_ConfigInfo.m_ZoneSize);
	uint32_t	uZ = (uint32_t)(pos->m_fZ / g_Config.m_ConfigInfo.m_ZoneSize);


	return(GridID_t)(uX + uZ * mGridInfo->m_wZoneW);
}

void		GameMap::GetRectInRadius(VRECT* pRect, int32_t nRadius, GridID_t zid)
{
	KCheck(zid != INVALID_ID);
	int32_t		nW = zid % mGridInfo->m_wZoneW;
	int32_t		nH = zid / mGridInfo->m_wZoneW;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	0 > nRadius ? nRadius = 0 : NULL;

	pRect->nStartx = nW - nRadius;
	if (pRect->nStartx < 0) pRect->nStartx = 0;

	pRect->nStartz = nH - nRadius;
	if (pRect->nStartz < 0) pRect->nStartz = 0;

	pRect->nEndx = nW + nRadius;
	if (pRect->nEndx >= mGridInfo->m_wZoneW) pRect->nEndx = mGridInfo->m_wZoneW - 1;

	pRect->nEndz = nH + nRadius;
	if (pRect->nEndz >= mGridInfo->m_wZoneH) pRect->nEndz = mGridInfo->m_wZoneH - 1;
}

MapInfo* GameMap::GetMapInfo()
{
	return mMapInfo;
}

ObjectManager* GameMap::GetObjManager()
{
	return m_pObjManager;
}

MapID_t GameMap::MapID()
{
	return mMapID;
}

bool	GameMap::Scan(Scanor* pScan)
{
	return false;
}

bool GameMap::ScanPlayer(GridID_t idZone, int32 nRadius_ZoneCount, PLAYERLIST* pOutHumanList)
{
	pOutHumanList->m_Count = 0;

	/*~~~~~~~*/
	VRECT	rc;
	/*~~~~~~~*/

	GetRectInRadius(&rc, nRadius_ZoneCount, idZone);

	for (int32 h = rc.nStartz; h <= rc.nEndz; h++)
	{
		for (int32 w = rc.nStartx; w <= rc.nEndx; w++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GridID_t	zid = w + h * mGridInfo->m_wZoneW;
			ObjectList* pList = GetGrid(zid)->GetHumanList();
			_INIT_LIST_NODE* pPoint = pList->m_Head.m_pNext;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			while (pPoint != &pList->m_Tail)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Player* pPlayer = (Player*)(pPoint->m_pNode);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				pPoint = pPoint->m_pNext;

				if (pPlayer == NULL)
				{
					KCheck(FALSE && "Map::ScanHuman pPlayer==NULL");
					return false;
				}

				pOutHumanList->m_aHuman[pOutHumanList->m_Count++] = pPlayer;
				if (pOutHumanList->m_Count == MAX_HUMAN_LIST_SIZE) 
					return true;
			};
		}
	}

	return true;
}

BOOL	GameMap::ScanHuman_Sub(GridID_t idZoneA, GridID_t idZoneB, uint32 uZoneRadius, PLAYERLIST* plistOutHuman)
{
	return true;
}

Object* GameMap::NewObject(Object::ObjectClass eType)
{
	Object* pObj = nullptr;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch (eType)
	{
	case Object::OBJECT_CLASS_PLAYER:		
		pObj = NULL; 
		break;
	case Object::OBJECT_CLASS_MONSTER:		
		pObj = new Monster(); 
		break;
	case Object::OBJECT_CLASS_PET:		
	
		break;
	case Object::OBJECT_CLASS_ITEM_BOX:		

		break;
	case Object::OBJECT_CLASS_DROP_ITEM:	
		pObj = new ItemInstance();
		break;
	case Object::OBJECT_CLASS_SPECIAL:		

		break;
	case Object::OBJECT_CLASS_HORSE:		
		pObj = new Horse();
		break;
	case Object::OBJECT_CLASS_BUS:		

		break;
	case Object::OBJECT_CLASS_BEASTIE:		
		pObj = new Beastie();
		break;
	default:				KCheck(FALSE && "Map::NewObject invalid obj type"); pObj = NULL; break;
	}

	if (pObj != NULL)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bResult = ObjectEnterMap(pObj);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (!bResult)
		{
			DeleteObject(pObj);
			return NULL;
		}
	}

	return pObj;
}

void GameMap::DeleteObject(Object* pObj)
{
	ObjectLeaveMap(pObj);
	delete pObj;
}

Object* GameMap::GetSpecificObjByID(ObjID_t nID) const
{
	return m_pObjManager->GetObj(nID);
}

Player* GameMap::getPlayer(ObjID_t nID)
{
	Object* pObj = m_pObjManager->GetObj(nID);

	if (pObj != nullptr && pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return (Player*)pObj;
	}
	return nullptr;
}

Monster* GameMap::getMonster(ObjID_t nID)
{
	Object* pObj = m_pObjManager->GetObj(nID);

	if (pObj != nullptr && pObj->GetObjType() == Object::OBJECT_CLASS_MONSTER)
	{
		return (Monster*)pObj;
	}
	return nullptr;
}

Beastie* GameMap::GetBeastie(ObjID_t nID) const
{
	return m_pBeastieManager->GetBeastie(nID);
}

bool GameMap::ObjectEnterMap(Object* pObj)
{
	__GUARD__ if (pObj == NULL)
	{
		KCheck(pObj != NULL && "Map::ObjectEnterMap");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	eOBJ_ID_TYPE	eIDType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		eIDType = OBJ_ID_TYPE_HUMAN;
	}
	else
	{
		eIDType = OBJ_ID_TYPE_NORMAL;
	}

	/*~~~~~~~~~~~~*/
	BOOL	bResult;
	/*~~~~~~~~~~~~*/

	bResult = m_pObjManager->AddObj(pObj, eIDType);
	if (!bResult)
	{
		KCheck(FALSE && "Map::ObjectEnterMap m_pObjManager->AddObj failed");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL		bSingleManagerAddSucceeded = FALSE;
	Object::ObjectClass eType = pObj->GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch (eType)
	{
	case Object::OBJECT_CLASS_PLAYER:
		bSingleManagerAddSucceeded = m_pHumanManager->Add(pObj);
		break;

	case Object::OBJECT_CLASS_MONSTER:
		bSingleManagerAddSucceeded = m_pMonsterManager->Add(pObj);
		break;

	case Object::OBJECT_CLASS_PET:

		break;

	case Object::OBJECT_CLASS_HORSE:
		bSingleManagerAddSucceeded = m_pHorseManager->Add(pObj);
		break;

	case Object::OBJECT_CLASS_BEASTIE:
		bSingleManagerAddSucceeded = m_pBeastieManager->Add(pObj);
		break;

	case Object::OBJECT_CLASS_BUS:

		break;

	case Object::OBJECT_CLASS_ITEM_BOX:
		bSingleManagerAddSucceeded = m_pItemBoxManager->Add((ItemBox*)pObj);
		break;

	case Object::OBJECT_CLASS_DROP_ITEM:
		bSingleManagerAddSucceeded = m_pItemInstanceManager->Add((ItemInstance*)pObj);
		break;

	case Object::OBJECT_CLASS_SPECIAL:

		break;

	default:
		KCheck(FALSE && "Map::ObjectEnterMap Unknow obj type");
		bSingleManagerAddSucceeded = FALSE;
		break;
	}

	if (!bSingleManagerAddSucceeded)
	{
		m_pObjManager->RemoveObj(pObj->GetID());
		KCheck(FALSE && "Map::ObjectEnterMap add obj to single manager failed");
		return FALSE;
	}

	pObj->SetMap(this);
	pObj->OnEnterMap();

	return TRUE;

	__UNGUARD__ return FALSE;
}

void GameMap::ObjectLeaveMap(Object* pObj)
{
	if (pObj == NULL)
	{
		KCheck(pObj != NULL && "Map::ObjectLeaveMap");
		return;
	}

	pObj->OnLeaveMap();
	pObj->SetMap(NULL);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object::ObjectClass eObjType = pObj->GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch (eObjType)
	{
	case Object::OBJECT_CLASS_PLAYER:
	{
		m_pHumanManager->Remove(pObj);
	}
	break;

	case Object::OBJECT_CLASS_MONSTER:
		m_pMonsterManager->Remove(pObj);
		break;

	case Object::OBJECT_CLASS_PET:
		break;

	case Object::OBJECT_CLASS_ITEM_BOX:
		break;

	case Object::OBJECT_CLASS_DROP_ITEM:
		m_pItemInstanceManager->Remove(pObj->GetID());
		break;

	case Object::OBJECT_CLASS_SPECIAL:
		break;

	case Object::OBJECT_CLASS_HORSE:
		m_pHorseManager->Remove(pObj);
		break;

	case Object::OBJECT_CLASS_BEASTIE:
		m_pBeastieManager->Remove(pObj);
		break;

	case Object::OBJECT_CLASS_BUS:
		break;

	default:
		KCheck(FALSE && "Map::ObjectLeaveMap Unknow obj type");
		break;
	}

	m_pObjManager->RemoveObj(pObj->GetID());
}

//npc的默认对话
BOOL	GameMap::OnNpcDefaultDialog(Player* pPlayer, ObjID_t idNpc, GUID_t guidNPC)
{
	return true;
}

//显示npc身上绑定的任务
BOOL	GameMap::OnNpcEventList(Player* pPlayer, ObjID_t idNpc, GUID_t guidNPC)
{
	return true;
}

//接受任务检查
BOOL	GameMap::OnAcceptQuestCheck(Player* pPlayer, ScriptID_t idQuestScript)
{
	return true;
}

uint32_t GameMap::GetRand100()
{
	return m_Rand100.GetRand();
}

void  GameMap::broadCast(NetPacket* packet, Character* pOwnCharacter)
{
	if (pOwnCharacter->GetGridID() == INVALID_ID)
	{
		delete packet;
		return;
	}

	if (pOwnCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		delete packet;
		return;
	}
	PLAYERLIST	listHuman;
	ScanPlayer(pOwnCharacter->GetGridID(), MAX_RADIUS, &listHuman);

	if (listHuman.m_Count > 0)
	{
		NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}
	else
	{
		delete packet;
		//NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}

}

