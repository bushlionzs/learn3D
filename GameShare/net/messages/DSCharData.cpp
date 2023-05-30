#include "stdafx.h"
#include "DSCharData.h"
#include "server/gameobject/Player.h"
#include "server/map/game_map.h"
#include "server/map/map_manager.h"
#include "net/messages/SCEnterMap.h"
#include "net/net_message_manager.h"

DSCharData::DSCharData(CHARDBNODE* charDBNode) :
    NetPacket(DS_CHAR_DATA)
{
    mCharDBNode = charDBNode;
}

DSCharData::~DSCharData()
{
    delete mCharDBNode;
}

bool DSCharData::process()
{
    _OBJ_PLAYER_INIT initHuman;
    initHuman.m_pUseData = mCharDBNode;

    Player* player = new Player;
    player->Init(&initHuman, 255);
    
    int sceneid = mCharDBNode->m_Human.m_StartScene;

    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(sceneid);

    pMap->ObjectEnterMap(player);


    return true;
}