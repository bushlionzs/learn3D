#pragma once

struct Region;
struct REGION_FILE
{
	char	m_szFileName[_MAX_PATH];
	Region* m_pArea;
	int32	m_Count;

	REGION_FILE()
	{
		memset(m_szFileName, 0, sizeof(char) * _MAX_PATH);
		m_pArea = NULL;
		m_Count = 0;
	};
	~REGION_FILE();
	void	Clear();
};
struct GATHER_POINT_LOAD;
struct GATHER_POINT_FILE
{
	char		m_szFileName[_MAX_PATH];
	GATHER_POINT_LOAD* m_pGrowpoint;
	int32		m_Count;

	GATHER_POINT_FILE()
	{
		memset(m_szFileName, 0, sizeof(char) * _MAX_PATH);
		m_pGrowpoint = NULL;
		m_Count = 0;
	}
	~GATHER_POINT_FILE()
	{
		Clear();
	}
	void	Clear();
};

class GameMap;
struct MAP_CONFIG;
struct SMonsterFile;
class MapManager:public GameSingleton<MapManager>
{
public:
	MapManager();
	~MapManager();

	bool initialize();
	void update();
	MAP_CONFIG* getMapData(MapID_t id);
	GameMap* getMap(uint32_t map_id);

	REGION_FILE* GetAreaFile(const char* szAreaFileName);
	REGION_FILE* GetEmptyAreaFile();

	SMonsterFile* GetMonsterFile(const char* szMonsterFileName);
	SMonsterFile* GetEmptyMonsterFile(const char* szMonsterFileName);

	GATHER_POINT_FILE* GetGatherpointFile(const char* szGatherpointFileName);
	GATHER_POINT_FILE* GetEmptyGatherpointFile();
	
private:
	bool loadSceneConfig();
private:
	std::unordered_map<uint32_t, GameMap*> mSceneMap;

	MAP_CONFIG* mMapConfig = nullptr;
	int32_t mMapCount = 0;

	std::unordered_map<std::string, SMonsterFile*> mMonsterFileMap;

	GATHER_POINT_FILE	m_aGrowpointFile[MAX_SCENE];
};
