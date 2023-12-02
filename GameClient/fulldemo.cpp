#include "OgreHeader.h"
#include "fulldemo.h"
#include "GameWorld.h"
#include "OgreCamera.h"
#include "net_message_manager.h"
#include "net_message.h"
FullDemo::FullDemo()
{

}

FullDemo::~FullDemo()
{

}

bool FullDemo::appInit()
{
	ApplicationBase::appInit();
	mGameCamera->getCamera()->setNearClipDistance(100.0f);

	mGameWorld = new GameWorld(mGameCamera);
	mGameWorld->gameWorldInit();
	return true;
}

void FullDemo::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	std::vector<NetPacket*> messagelist;
	NetManager::GetSingletonPtr()->fetchServerMessage(messagelist);

	for (auto packet : messagelist)
	{
		packet->process();
		delete packet;
	}
	mGameWorld->update(delta);
}

EngineType FullDemo::getEngineType()
{
	//return EngineType_Dx12;
	return EngineType_Vulkan;
	
}