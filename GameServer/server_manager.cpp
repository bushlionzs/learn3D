#include "stdafx.h"
#include "server_manager.h"
#include "platform_common.h"
#include "server/quest/quest_manager.h"
#include "net/net_message_manager.h"
#include "net/net_message.h"
#include "share/TAB/TabDefine_Map_Quest.h"
#include "server/script/LuaSystem.h"
#include "Share/ScriptCacheMgr.h"
#include "platform_util.h"
#include "server/map/map_manager.h"
#include "server/data/data_manager.h"
#include "server/gameobject/Behavior_State.h"
#include "server/server_settting.h"
#include "server/db/db_manager.h"
#include "Share/TAB/TabDefine_Map_Item.h"
#include "server/item/Item_Manager.h"
#include "server/skill/Skill_Manager.h"

extern ScriptCacheMgr g_ScriptFileMgr;
template<>
ServerManager* GameSingleton<ServerManager>::m_sSingleton = NULL;


ServerManager::ServerManager()
{

}

ServerManager::~ServerManager()
{

}

bool ServerManager::initialize()
{

	g_Config.Init();

	g_BHVStateList.InitStateList();
	mQuestManager = new QuestManager;
	mQuestTable = new TableInit_Map_Quest;
	mLuaSystem = new LuaSystem;
	new DataManager;
	new MapManager;
	mQuestManager->Initialize();

	mQuestTable->Init();

	const std::string scriptname = "D:\\Khan2\\Bin\\Client\\Public\\Data\\MyScript.tab";
	g_ScriptFileMgr.Init(scriptname.c_str(), false);
	ScriptCache* cache = g_ScriptFileMgr.GetFileData(200001);
	if (cache)
	{
		const char* filename  = cache->GetFileName();
		printf("%s\n", filename);
	}

	mLuaSystem->Initialize();
	DataManager::GetSingletonPtr()->initialize();
	MapManager::GetSingletonPtr()->initialize();

	g_pSkillManager = new SkillManager;
	g_pSkillManager->Init();

	g_ItemTab.Init();

	
	
	return true;
}

void ServerManager::run()
{
	processNetMessage();
	MapManager::GetSingletonPtr()->update();
}

void ServerManager::QueryEvent(uint32_t mapId, uint32_t playeId, uint32_t objectId)
{
	mLuaSystem->RunScriptFunction(0, 101000, "test");
}

QuestManager* ServerManager::getQuestManager()
{
	return mQuestManager;
}

void ServerManager::processNetMessage()
{
	mNetMessageList.clear();
	NetManager::GetSingletonPtr()->fetchClientMessage(mNetMessageList);

	uint32_t count = mNetMessageList.size();

	for (int32_t i = 0; i < count; i++)
	{
		NetPacket* packet = mNetMessageList[i];
		packet->process();
		delete packet;
	}
}

void server_init_func()
{
	
	ServerManager* serverManager = new ServerManager;

	g_pItemMgr = new ItemManager;
	g_pItemMgr->Init();
	serverManager->initialize();
}

uint32_t server_entry_func(uint32_t moduleid,
	uint32_t msg_id,
	uint64_t sender,
	uint64_t param,
	void* msg,
	uint32_t msg_size,
	void* pModulePrivateData)
{
	ServerManager::GetSingletonPtr()->run();
	return 0;
}

void db_init_func()
{
	bool ret = DBManager::GetSingletonPtr()->initialize();

	assert(ret);
}

uint32_t db_entry_func(uint32_t moduleid,
	uint32_t msg_id,
	uint64_t sender,
	uint64_t param,
	void* msg,
	uint32_t msg_size,
	void* pModulePrivateData)
{
	DBManager::GetSingletonPtr()->run();
	return 0;
}


IPlatformModule* serverModule = nullptr;
IPlatformModule* dbModule = nullptr;
int32_t server_timer_callback(void* param)
{
	serverModule->post_module_message(0,
		0,
		0,
		0,
		0,
		0,
		false);

	dbModule->post_module_message(0,
		0,
		0,
		0,
		0,
		0,
		false);
	return 0;
}

void run_game_server()
{
	new NetManager;
	new DBManager;

	serverModule =
		create_platform_module(1, "server_module");
	serverModule->attach_module(0, server_init_func, server_entry_func, nullptr);
	serverModule->run_module();

	platform_create_timer(10, server_timer_callback, nullptr);

	dbModule = create_platform_module(1, "db_module");
	dbModule->attach_module(0, db_init_func, db_entry_func, nullptr);
	dbModule->run_module();
}