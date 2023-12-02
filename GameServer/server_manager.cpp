#include "stdafx.h"
#include "server_manager.h"
#include "platform_common.h"
#include "quest/quest_manager.h"
#include "net/net_message_manager.h"
#include "net/net_message.h"
#include "share/TAB/TabDefine_Map_Quest.h"
#include "script/LuaSystem.h"
#include "ScriptCacheMgr.h"
#include "platform_util.h"
#include "map/map_manager.h"
#include "data/data_manager.h"
#include "gameobject/Behavior_State.h"
#include "server_settting.h"
#include "db/db_manager.h"
#include "Share/TAB/TabDefine_Map_Item.h"
#include "item/Item_Manager.h"
#include "skill/Skill_Manager.h"
#include "message_process.h"
#include "client_message.pb.h"

extern ScriptCacheMgr g_ScriptFileMgr;
template<>
ServerManager* GameSingleton<ServerManager>::m_sSingleton = NULL;


ServerManager::ServerManager()
{

}

ServerManager::~ServerManager()
{

}

void ServerManager::OnPreInit()
{

	g_pItemMgr = new ItemManager;
	g_pItemMgr->Init();

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

	mUpdateTimer = create_timer(10, nullptr, true);
}

int ServerManager::process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
	NetMessageManager::GetSingleton().dispatchMessage(handle, msg, msg_size);
	return 0;
}

void ServerManager::OnTimer(platform_timer_t, void* param)
{
	NetMessageManager::GetSingleton().processMessage();
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


void ServerManager::registerMessage()
{
	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_LOGIN,
		std::bind(cs_user_login, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_CHAR_MOVE,
		std::bind(cs_char_move, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_USE_SKILL,
		std::bind(cs_char_use_skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_EVENT_REQUEST,
		std::bind(cs_event_request, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_MANIPULATE_PET,
		std::bind(cs_manipulate_pet, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_PICK_ITEM,
		std::bind(cs_pick_item, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_REQUEST_BASEATTR,
		std::bind(cs_player_request_base_attr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_QUERY_EVENT,
		std::bind(cs_query_event, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_QUEST_ABANDON,
		std::bind(cs_quest_abandon, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_QUEST_ACCEPT,
		std::bind(cs_quest_accept, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_QUEST_CONTINUE,
		std::bind(cs_quest_continue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_QUEST_REFUSE,
		std::bind(cs_quest_refuse, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_QUEST_SUBMIT,
		std::bind(cs_quest_submit, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_SWAP_ITEM,
		std::bind(cs_swap_item, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_TICK,
		std::bind(cs_tick, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_UNEQUIP,
		std::bind(cs_takedown_equip, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));



	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_USE_ABILITY,
		std::bind(cs_use_ability, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));



	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_USE_EQUIP,
		std::bind(cs_use_equip, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));



	
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
	new ServerManager;
	new NetMessageManager;
	new DBManager;

	dbModule = create_platform_module(1, "db_module");
	dbModule->attach_module(0, db_init_func, db_entry_func, nullptr);
	dbModule->run_module();

	ServerManager::GetSingleton().init();

	ServerManager::GetSingleton().start(true);
}

int main()
{
	run_game_server();

	return 0 ;
}