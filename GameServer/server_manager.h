#pragma once
class QuestManager;
class NetPacket;
class ScriptCacheMgr;
class TableInit_Map_Quest;
class TableInit_Map;


class LuaSystem;


class ServerManager :public GameSingleton<ServerManager>
{
public:
	ServerManager();
	~ServerManager();

	bool initialize();
	void run();

	QuestManager* getQuestManager();


	void QueryEvent(uint32_t mapId, uint32_t playeId, uint32_t objectId);

	LuaSystem* getLuaSystem()
	{
		return mLuaSystem;
	}
private:
	void processNetMessage();
private:
	QuestManager* mQuestManager = nullptr;

	ScriptCacheMgr* mScriptFileMgr = nullptr;

	TableInit_Map_Quest* mQuestTable = nullptr;

	TableInit_Map* mMapTable = nullptr;

	std::vector<NetPacket*> mNetMessageList;

	LuaSystem* mLuaSystem = nullptr;

	
};

void run_game_server();