#pragma once

#include "MisBuf.h"
#include "gameobject/object.h"
#include "gameobject/EventSystem.h"
#include "StructScript.h"
#include "Grid.h"

struct MAP_CONFIG;
struct Grid;
struct _GRID_INFO;
struct Region;

class MapInfo;
class Object;
class ObjectManager;
class GuardManager;
class PlayerManager;
class MonsterObjectManager;
class PatrolRoadsPointMgr;
class Character;
class Scanor;
struct PLAYERLIST;
class MapDropPosManager;
class ItemInstanceManager;
class BeastieManager;
class HorseManager;
class GatherBoxManager;
class NetPacket;
class LuaSystem;
class Beastie;
class Player;
class Monster;
class GatherPointManager;
class GameMap
{
public:
	struct SQuestBuffer m_QuestBuffer;
	SXParam		m_XParam;
	SItemList	mItemList;
private:
	MapInfo* mMapInfo = nullptr;

	Grid* m_pGrid = nullptr;
	_GRID_INFO* mGridInfo = nullptr;

	int32_t			m_MapType;
	int32_t			m_MapSafeLevel;
	int32_t			m_MapRestrictiveMode;
	int32_t         mMapID;
	BOOL			m_Punish;

	GLPos		m_CanEnterPos;

	//怪物管理器
	MonsterObjectManager* m_pMonsterManager = nullptr;

	//骑乘管理器
	HorseManager* m_pHorseManager;

	//召唤兽管理器
	GuardManager* m_pGuardManager;

	//可捕捉的小动物 管理器
	BeastieManager* m_pBeastieManager;

	//可采集的物品管理器
	GatherBoxManager* m_pItemBoxManager;

	//生长点
	GatherPointManager*	m_GrowPointGroup;

	ObjectManager* m_pObjManager = nullptr;

	//玩家管理器
	PlayerManager* m_pHumanManager = nullptr;

	//场景可掉落的位置管理器
	MapDropPosManager* m_pDropPosManager = nullptr;

	//静态物品管理器 也就是装备 药水等等 这些东西是不能摆放到场景中的 如果丢在场景中就变为DropItem类
	ItemInstanceManager* m_pItemInstanceManager = nullptr;

	MAP_CONFIG* mMapConfig = nullptr;

	PatrolRoadsPointMgr* m_pPatrolPathMgr = nullptr;

	LuaSystem* mLuaSystem = nullptr;

	//事件分发系统
	EventSystem		m_EventCore;

	uint32_t		m_BackUpTime = 0;

	NetPacket* mDelObjectPacket = nullptr;

	KL100RandomTab	m_Rand100;
public:
	GameMap();
	~GameMap();

	bool initialize(MAP_CONFIG& config);
	void update(uint64_t utime);
	MAP_CONFIG* getMapData();
	BOOL		RegisterArea(const Region* pArea);

	BOOL		ObjGrid_Register(Object* pObj, GridID_t idZone);
	BOOL		ObjGrid_Unregister(Object* pObj, GridID_t idZone);
	BOOL		ObjGrid_Changed(Object* pObj, GridID_t idNew, GridID_t idOld);
	//以idZone为中心以uZoneRadius为阶 查找Obj
	BOOL ScanObj(GridID_t idZone, uint32 uZoneRadius, OBJLIST* plistOutObj);

	//以idZoneA为中心以uZoneRadius为阶(1为3*3 2为5*5) 确定一个矩形区域A
	//以idZoneB为中心以uZoneRadius为阶(1为3*3 2为5*5) 确定一个矩形区域B
	//取得A和B交集中的Obj
	BOOL	ScanObj_Sub(GridID_t idZoneA, GridID_t idZoneB, uint32 uZoneRadius, OBJLIST* plistOutObj);
	Grid* GetGrid(GridID_t ZoneID);
	GridID_t	CalcGridID(const GLPos* pos);

	void		GetRectInRadius(VRECT* pRect, int32 nRadius, GridID_t zid);

	MapInfo* GetMapInfo();

	EventSystem& GetEventCore()
	{
		return m_EventCore;
	}

	ObjectManager* GetObjManager();

	PlayerManager* GetPlayerManager()
	{
		return m_pHumanManager;
	}

	HorseManager* GetHorseManager()
	{
		return m_pHorseManager;
	}

	BeastieManager* GetBeastieManager()
	{
		return m_pBeastieManager;
	}
	

	GatherBoxManager* GetItemBoxManager()
	{
		return m_pItemBoxManager;
	}


	GatherPointManager* GetGatherPointManager()
	{
		return m_GrowPointGroup;
	}
	
	MapDropPosManager* GetMapDropPosManager()
	{
		return m_pDropPosManager;
	}

	ItemInstanceManager* GetItemInstanceManager()
	{
		return m_pItemInstanceManager;
	};

	GuardManager* GetGuardManager()
	{
		return nullptr;
	}

	PatrolRoadsPointMgr* GetPatrolPathMgr() const
	{
		return m_pPatrolPathMgr;
	};

	MapID_t MapID();

	int32_t GetMapType()
	{
		return m_MapType;
	}

	bool	Scan(Scanor* pScan);
	//以idZone为中心以uZoneRadius为阶(1为3*3 2为5*5)进行Player查找
	bool ScanPlayer(GridID_t idZone, int32 nRadius_ZoneCount, PLAYERLIST* pOutHumanList);

	//以idZoneA为中心以uZoneRadius为阶(1为3*3 2为5*5) 确定一个矩形区域A
	//以idZoneB为中心以uZoneRadius为阶(1为3*3 2为5*5) 确定一个矩形区域B
	//取得A和B交集中的Player
	BOOL	ScanHuman_Sub(GridID_t idZoneA, GridID_t idZoneB, uint32 uZoneRadius, PLAYERLIST* plistOutHuman);

	Object* NewObject(Object::ObjectClass eType);
	void DeleteObject(Object* pObj);
	Object* GetSpecificObjByID(ObjID_t nID) const;
	Player* getPlayer(ObjID_t nID);
	Monster* getMonster(ObjID_t nID);
	Beastie* GetBeastie(ObjID_t nID) const;
	bool ObjectEnterMap(Object* pObj);
	void ObjectLeaveMap(Object* pObj);

	//npc的默认对话
	BOOL	OnNpcDefaultDialog(Player* pPlayer, ObjID_t idNpc, GUID_t guidNPC);

	//显示npc身上绑定的任务
	BOOL	OnNpcEventList(Player* pPlayer, ObjID_t idNpc, GUID_t guidNPC);

	//接受任务检查
	BOOL	OnAcceptQuestCheck(Player* pPlayer, ScriptID_t idQuestScript);

	uint32_t GetRand100();

	void  broadCast(NetPacket* packet, Character* pOwnCharacter);

	uint32_t GetCurHeartBeatTime()
	{
		return m_BackUpTime;
	}

};