#include "stdafx.h"
#include "map_manager.h"
#include "server_settting.h"
#include "platform_file_system.h"
#include "game_map.h"
#include "MonsterManager.h"
#include "time_util.h"
#include "BaseTool.h"
#include "item/Item_GrowPointManager.h"


template<>
MapManager* GameSingleton<MapManager>::m_sSingleton = NULL;


void GATHER_POINT_FILE::Clear()
{
	memset(m_szFileName, 0, sizeof(char) * _MAX_PATH);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KSafeDelete(m_pGrowpoint);
	m_Count = 0;
}

MapManager::MapManager()
{
	
}

MapManager::~MapManager()
{

}

bool MapManager::initialize()
{
	loadSceneConfig();


	std::set<int32_t> idmapset = {87};
	for (int32_t i = 0; i < mMapCount; i++)
	{
		if (!idmapset.count(mMapConfig[i].m_MapID))
		{
			continue;
		}
		GameMap* map = new GameMap();

		map->initialize(mMapConfig[i]);

		mSceneMap[mMapConfig[i].m_MapID] = map;
	}
	return true;
}

void MapManager::update()
{
	static uint64_t start_time  = get_tick_count();
	uint64_t current = get_tick_count();
	auto it = mSceneMap.begin();
	for (; it != mSceneMap.end(); it++)
	{
		it->second->update(current);
	}
}

MAP_CONFIG* MapManager::getMapData(MapID_t id)
{
	auto itor = mSceneMap.find(id);

	if (itor != mSceneMap.end())
	{
		return itor->second->getMapData();
	}

	return nullptr;
}

GameMap* MapManager::getMap(uint32_t map_id)
{
	auto itor = mSceneMap.find(map_id);

	if (itor != mSceneMap.end())
	{
		return itor->second;
	}

	return nullptr;
}

bool MapManager::loadSceneConfig()
{
	std::string mapfilename = "../ServerConfig/mapdefines.tab";

	TAB::TABFile ThirdFile(0);
	bool ret = ThirdFile.OpenFromTXT(mapfilename.c_str());

	int32_t	mapCount = ThirdFile.GetRecordsNum();

	struct MAP_CONFIG* mapconfig = new MAP_CONFIG[mapCount];

	memset(mapconfig, 0, sizeof(MAP_CONFIG) * mapCount);

	enum SceneDefinesTab
	{
		SDT_SceneID,
		SDT_ThreadIndex,
		SDT_SceneName,
		SDT_SceneEnable,
		SDT_SceneFilePath,
		SDT_ServerID,
		SDT_SceneType,
		SDT_SecurityLevel,
		SDT_RestrictiveMode,
		SDT_Punish,
		SDT_DefaultX,
		SDT_DefaultZ,
		SDT_ClientRes,
		SDT_DefaultCamp,
		SDT_BusPramID,
	};

	const std::string& workDir = CPlatformFileSystem::GetInstance()->GetWorkDirectory();

	std::string temp;

	for (int32_t i = 0; i < mapCount; i++)
	{
		mapconfig[i].m_MapID = (MapID_t)ThirdFile.Search_Posistion(i, SDT_SceneID)->iValue;

		if (i == 0 && mapconfig[i].m_MapID != 0)
		{
			assert(false);
		}

		mapconfig[i].m_IsActive = ThirdFile.Search_Posistion(i, SDT_SceneEnable)->iValue;

		strncpy
		(
			mapconfig[i].m_szName,
			ThirdFile.Search_Posistion(i, SDT_SceneName)->pString,
			_MAX_PATH - 1
		);

		strncpy
		(
			mapconfig[i].m_szFileName,
			ThirdFile.Search_Posistion(i, SDT_SceneFilePath)->pString,
			_MAX_PATH - 1
		);

		mapconfig[i].m_ServerID = (ID_t)(ThirdFile.Search_Posistion(i, SDT_ServerID)->iValue);
		mapconfig[i].m_Type = (ID_t)(ThirdFile.Search_Posistion(i, SDT_SceneType)->iValue);
		mapconfig[i].m_ThreadIndex = (ID_t)(ThirdFile.Search_Posistion(i, SDT_ThreadIndex)->iValue);
		mapconfig[i].m_cSecurityLevel = (char)(ThirdFile.Search_Posistion(i, SDT_SecurityLevel)->iValue);
		mapconfig[i].m_cRestrictiveMode = (char)(ThirdFile.Search_Posistion(i, SDT_RestrictiveMode)->iValue);
		mapconfig[i].m_bPunish = (BOOL)(ThirdFile.Search_Posistion(i, SDT_Punish)->iValue);
		mapconfig[i].m_DefaultX = ThirdFile.Search_Posistion(i, SDT_DefaultX)->iValue;
		mapconfig[i].m_DefaultZ = ThirdFile.Search_Posistion(i, SDT_DefaultZ)->iValue;
		mapconfig[i].m_ClientRet = ThirdFile.Search_Posistion(i, SDT_ClientRes)->iValue;
		mapconfig[i].m_DefaultCamp = ThirdFile.Search_Posistion(i, SDT_DefaultCamp)->iValue;
		mapconfig[i].m_BusParam = ThirdFile.Search_Posistion(i, SDT_BusPramID)->iValue;

		//nav monster filename


		temp = CPlatformFileSystem::get_filename(mapconfig[i].m_szFileName, true);

		snprintf(mapconfig[i].m_szNavFileName, sizeof(mapconfig[i].m_szNavFileName), "%s\\..\\map\\%s\\%s.nav",
			workDir.c_str(), temp.c_str(), temp.c_str());
		snprintf(mapconfig[i].m_szMonsterFileName, sizeof(mapconfig[i].m_szMonsterFileName), "%s\\..\\map\\%s\\%s_monster.tab",
				workDir.c_str(), temp.c_str(), temp.c_str());
		snprintf(mapconfig[i].m_szSceneConfigName, sizeof(mapconfig[i].m_szSceneConfigName), "%s\\..\\map\\%s\\%s.scn",
			workDir.c_str(), temp.c_str(), temp.c_str());
		snprintf(mapconfig[i].m_szPatrolPointName, sizeof(mapconfig[i].m_szPatrolPointName), "%s\\..\\map\\%s\\%s_patrolpoint.ini",
			workDir.c_str(), temp.c_str(), temp.c_str());
		snprintf(mapconfig[i].m_szGrowPointDataName, sizeof(mapconfig[i].m_szGrowPointDataName), "%s\\..\\map\\%s\\%s_growpoint.txt",
			workDir.c_str(), temp.c_str(), temp.c_str());
		snprintf(mapconfig[i].m_szGrowPointSetupName, sizeof(mapconfig[i].m_szGrowPointSetupName), "%s\\..\\map\\%s\\%s_growpointsetup.txt",
			workDir.c_str(), temp.c_str(), temp.c_str());
	}


	
	mMapConfig = mapconfig;
	mMapCount = mapCount;
	return true;
}

REGION_FILE* MapManager::GetAreaFile(const char* szAreaFileName)
{
	return nullptr;
}

REGION_FILE* MapManager::GetEmptyAreaFile()
{
	return nullptr;
}

SMonsterFile* MapManager::GetMonsterFile(const char* szMonsterFileName)
{
	auto itor = mMonsterFileMap.find(szMonsterFileName);

	if (itor != mMonsterFileMap.end())
	{
		return itor->second;
	}
	return nullptr;
}

SMonsterFile* MapManager::GetEmptyMonsterFile(const char* szMonsterFileName)
{
	SMonsterFile* pMonsterFile = new SMonsterFile();
	mMonsterFileMap[szMonsterFileName] = pMonsterFile;
	return pMonsterFile;
}

GATHER_POINT_FILE* MapManager::GetGatherpointFile(const char* szGrowpointFileName)
{
	if (szGrowpointFileName == NULL || szGrowpointFileName[0] == 0)
	{
		return NULL;
	}

	for (int32 i = 0; i < MAX_SCENE; i++)
	{
		if (m_aGrowpointFile[i].m_pGrowpoint == NULL) continue;
		if (m_aGrowpointFile[i].m_szFileName[0] == 0) continue;
		if (strcmp(m_aGrowpointFile[i].m_szFileName, szGrowpointFileName) == 0) 
			return &m_aGrowpointFile[i];
	}

	return nullptr;
}

GATHER_POINT_FILE* MapManager::GetEmptyGatherpointFile()
{
	for (int32 i = 0; i < MAX_SCENE; i++)
	{
		if (m_aGrowpointFile[i].m_szFileName[0] == 0)
		{
			return &m_aGrowpointFile[i];
		}
	}

	return nullptr;
}