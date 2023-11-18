#include "OgreHeader.h"
#include "fulldemo.h"
#include "GameWorld.h"
#include "OgreCamera.h"
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

	mGameWorld->update(delta);
}

EngineType FullDemo::getEngineType()
{
	return EngineType_Dx11;
	return EngineType_Vulkan;
	return EngineType_Dx12;
}