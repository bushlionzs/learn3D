#include "stdafx.h"
#include "CSLogin.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "map/map_manager.h"
#include "net/messages/SCEnterMap.h"
#include "net/net_message_manager.h"
#include "db/db_manager.h"
#include "db/db_task.h"

CSLogin::CSLogin():
	NetPacket(CS_LOGIN)
{

}

CSLogin::~CSLogin()
{

}

bool CSLogin::process()
{
	/*uint32_t sceneid = 87;


	Player* player = new Player;

	_INIT_OBJECT init;

	GLPos pos;
	pos.m_fX = 196.578;
	pos.m_fZ = 79.62;

	init.m_Pos = pos;

	init.m_Dir = 0.0f;
	player->Init(&init, 0);
	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(sceneid);

	pMap->ObjectEnterMap(player);*/
	//1610000020 ĞÂÊÖ´å
	//1610000020 »Ê¹¬
	auto id = std::string("1610000020");
	CharDataTask* task = new CharDataTask(id);
	DBManager::GetSingletonPtr()->addDbTask(task);

	return true;
}