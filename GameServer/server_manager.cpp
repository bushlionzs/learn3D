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

	const std::string scriptname = "..\\..\\server_resources\\Public\\Data\\MyScript.tab";
	BOOL load = g_ScriptFileMgr.Init(scriptname.c_str(), false);
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

	registerMessage();
}

void ServerManager::OnAfterInit()
{
	mUpdateTimer = create_timer(10, nullptr, true);
}

int ServerManager::process_message(NetHandle handle, const char* msg, uint32_t msg_size, void* pNetThreadData)
{
	NetMessageManager::GetSingleton().processMessage(handle, msg, msg_size);
	return 0;
}

void ServerManager::OnTimer(platform_timer_t, void* param)
{
	run_packet();
	MapManager::GetSingletonPtr()->update();
}

void ServerManager::add_packet(NetPacket* packet)
{
	std::lock_guard<std::mutex> lock(mMutex);
	mServerMessageList.push_back(packet);
}

void ServerManager::run_packet()
{
	if (!mServerMessageList.empty())
	{
		std::lock_guard<std::mutex> lock(mMutex);
		for (auto packet : mServerMessageList)
		{
			packet->process();
			delete packet;
		}
		mServerMessageList.clear();
	}
	
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

	NetMessageManager::GetSingleton().registerMessage(clientmessage::CS_EVENT_REQUEST,
		std::bind(cs_event_request, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

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

void run_game_server()
{
	new ServerManager;
	new NetMessageManager;
	new DBManager;

	DBManager::GetSingleton().initialize();
	

	ServerManager::GetSingleton().init();

	printf("server init sucessfully!!!\n");
	ServerManager::GetSingleton().start(true);
}
#include "server_message.pb.h"

void test()
{
	servermessage::ServerMsgMonsterAttribute dummy;

	dummy.set_object_id(14);
	float fMoveSpeed = 1.0f;
	float fAttackSpeed = 100.0f;
	if (true)
	{
		dummy.set_name("Ê¥Ê®×ÖÖ®Áé");
		dummy.set_data_id(11991);
		dummy.set_scale(1000);
		dummy.set_ai_type(1);
		if (fMoveSpeed > 0)
		{
			dummy.set_move_speed(fMoveSpeed);
		}

		if (fAttackSpeed > 0)
		{
			dummy.set_attack_speed((float)fAttackSpeed);
		}


			dummy.set_country_title("aaaa");

			auto nHorseId = -1;
		if (nHorseId != INVALID_ID)
		{
			dummy.set_mount_id(nHorseId);
		}

		dummy.set_level(0);
	}

	dummy.set_hp_percent(100);
	dummy.set_target_id(1);


		dummy.set_steal_level(2);




		base::SCampData* camp_data = dummy.mutable_camp_data();
		camp_data->set_camp_id(20);
		camp_data->set_pk_mode(0);
		camp_data->set_reserve1(-1);
		camp_data->set_reserve2(-1);


		//dummy.set_occupant_guid(1);



		//dummy.set_owner_id(1);


	servermessage::ServerMsgMonsterAttribute tmp;
	std::string output;
	dummy.AppendToString(&output);
	auto size = output.size();
	servermessage::ServerMsgMonsterAttribute kk;
	bool b = kk.ParseFromArray(output.c_str(), size);
	b = b;
}
int main()
{
	test();
	run_game_server();

	return 0 ;
}