#pragma once
class QuestManager;
class NetPacket;
class ScriptCacheMgr;
class TableInit_Map_Quest;
class TableInit_Map;


class LuaSystem;

#include "GameSingleton.h"
#include "server_logic.h"
class ServerManager :public GameSingleton<ServerManager>, public ServerLogic
{
public:
	ServerManager();
	~ServerManager();

	virtual std::string get_server_ip()
	{
		return "0.0.0.0";
	}

	virtual uint16_t get_server_port()
	{
		return 8888;
	}
	
	virtual void OnPreInit();
	virtual int process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData) override;
	void run();

	QuestManager* getQuestManager();


	void QueryEvent(uint32_t mapId, uint32_t playeId, uint32_t objectId);

	LuaSystem* getLuaSystem()
	{
		return mLuaSystem;
	}
private:
	void registerMessage();
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