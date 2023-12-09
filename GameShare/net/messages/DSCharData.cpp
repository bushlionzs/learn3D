#include "stdafx.h"
#include "DSCharData.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "map/map_manager.h"
#include "net/messages/SCEnterMap.h"
#include "net/net_message_manager.h"

DSCharData::DSCharData(CHARDBNODE* charDBNode, NetHandle h) :
    NetPacket(DS_CHAR_DATA)
{
    mCharDBNode = charDBNode;
    mHandle = h;
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
    player->SetConnector(mHandle);
    player->Init(&initHuman, 255);
    
    int sceneid = mCharDBNode->m_Human.m_StartScene;

    GameMap* pMap = MapManager::GetSingletonPtr()->getMap(sceneid);

    pMap->ObjectEnterMap(player);


    return true;
}