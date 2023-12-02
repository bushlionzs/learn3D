#include "OgreHeader.h"
#include "fulldemo.h"
#include "GameWorld.h"
#include "OgreCamera.h"
#include "net_message_manager.h"
#include "net_message.h"
#include "net_context.h"

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

	mNetContext = new NetContext;

	mNetContext->init();

	mNetContext->start(false);

	mGameWorld = new GameWorld(mGameCamera);
	mGameWorld->gameWorldInit();
	return true;
}

void FullDemo::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	mGameWorld->update(delta);
}

EngineType FullDemo::getEngineType()
{
	//return EngineType_Dx12;
	return EngineType_Vulkan;
	
}