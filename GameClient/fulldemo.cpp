#include "OgreHeader.h"
#include "fulldemo.h"
#include "GameWorld.h"
#include "OgreCamera.h"
#include "net_message_manager.h"
#include "net_message.h"
#include "net_context.h"
#include "message_process.h"
#include "server_message.pb.h"

FullDemo::FullDemo()
{

}

FullDemo::~FullDemo()
{

}

bool FullDemo::appInit()
{
	registerMessage();
	ApplicationBase::appInit();
	mGameCamera->getCamera()->setNearClipDistance(100.0f);

	mNetContext = new NetContext;

	mNetContext->init();

	mNetContext->start(false);

	mGameWorld = new GameWorld(mGameCamera);
	mGameWorld->gameWorldInit();
	return true;
}

void FullDemo::registerMessage()
{
	new NetMessageManager;

	NetMessageManager::GetSingleton().registerMessage(servermessage::SC_ENTER_MAP, sc_enter_scene);
	NetMessageManager::GetSingleton().registerMessage(servermessage::SC_HUMAN_BASE_ATTR, sc_human_base_attr);
	NetMessageManager::GetSingleton().registerMessage(servermessage::SC_DETAIL_EQUIP_LIST, sc_detail_equip);
	NetMessageManager::GetSingleton().registerMessage(servermessage::SC_DETAIL_ITEM_LIST, sc_detail_item);
	NetMessageManager::GetSingleton().registerMessage(servermessage::SC_DETAIL_SKILL_LIST, sc_detail_skill);
	NetMessageManager::GetSingleton().registerMessage(servermessage::SC_NEWMONSTER, sc_new_monster);
}

void FullDemo::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);

	NetMessageManager::GetSingleton().processMessage();
	mGameWorld->update(delta);
}

EngineType FullDemo::getEngineType()
{
	//return EngineType_Dx12;
	return EngineType_Vulkan;
	
}