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

	//���������
	MonsterObjectManager* m_pMonsterManager = nullptr;

	//��˹�����
	HorseManager* m_pHorseManager;

	//�ٻ��޹�����
	GuardManager* m_pGuardManager;

	//�ɲ�׽��С���� ������
	BeastieManager* m_pBeastieManager;

	//�ɲɼ�����Ʒ������
	GatherBoxManager* m_pItemBoxManager;

	//������
	GatherPointManager*	m_GrowPointGroup;

	ObjectManager* m_pObjManager = nullptr;

	//��ҹ�����
	PlayerManager* m_pHumanManager = nullptr;

	//�����ɵ����λ�ù�����
	MapDropPosManager* m_pDropPosManager = nullptr;

	//��̬��Ʒ������ Ҳ����װ�� ҩˮ�ȵ� ��Щ�����ǲ��ܰڷŵ������е� ������ڳ����оͱ�ΪDropItem��
	ItemInstanceManager* m_pItemInstanceManager = nullptr;

	MAP_CONFIG* mMapConfig = nullptr;

	PatrolRoadsPointMgr* m_pPatrolPathMgr = nullptr;

	LuaSystem* mLuaSystem = nullptr;

	//�¼��ַ�ϵͳ
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
	//��idZoneΪ������uZoneRadiusΪ�� ����Obj
	BOOL ScanObj(GridID_t idZone, uint32 uZoneRadius, OBJLIST* plistOutObj);

	//��idZoneAΪ������uZoneRadiusΪ��(1Ϊ3*3 2Ϊ5*5) ȷ��һ����������A
	//��idZoneBΪ������uZoneRadiusΪ��(1Ϊ3*3 2Ϊ5*5) ȷ��һ����������B
	//ȡ��A��B�����е�Obj
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
	//��idZoneΪ������uZoneRadiusΪ��(1Ϊ3*3 2Ϊ5*5)����Player����
	bool ScanPlayer(GridID_t idZone, int32 nRadius_ZoneCount, PLAYERLIST* pOutHumanList);

	//��idZoneAΪ������uZoneRadiusΪ��(1Ϊ3*3 2Ϊ5*5) ȷ��һ����������A
	//��idZoneBΪ������uZoneRadiusΪ��(1Ϊ3*3 2Ϊ5*5) ȷ��һ����������B
	//ȡ��A��B�����е�Player
	BOOL	ScanHuman_Sub(GridID_t idZoneA, GridID_t idZoneB, uint32 uZoneRadius, PLAYERLIST* plistOutHuman);

	Object* NewObject(Object::ObjectClass eType);
	void DeleteObject(Object* pObj);
	Object* GetSpecificObjByID(ObjID_t nID) const;
	Player* getPlayer(ObjID_t nID);
	Monster* getMonster(ObjID_t nID);
	Beastie* GetBeastie(ObjID_t nID) const;
	bool ObjectEnterMap(Object* pObj);
	void ObjectLeaveMap(Object* pObj);

	//npc��Ĭ�϶Ի�
	BOOL	OnNpcDefaultDialog(Player* pPlayer, ObjID_t idNpc, GUID_t guidNPC);

	//��ʾnpc���ϰ󶨵�����
	BOOL	OnNpcEventList(Player* pPlayer, ObjID_t idNpc, GUID_t guidNPC);

	//����������
	BOOL	OnAcceptQuestCheck(Player* pPlayer, ScriptID_t idQuestScript);

	uint32_t GetRand100();

	void  broadCast(NetPacket* packet, Character* pOwnCharacter);

	uint32_t GetCurHeartBeatTime()
	{
		return m_BackUpTime;
	}

};