#include "OgreHeader.h"
#include "SkeletonAnimation.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"

SkeletonAnimation::SkeletonAnimation()
{

}

SkeletonAnimation::~SkeletonAnimation()
{

}

bool SkeletonAnimation::appInit()
{
	ApplicationBase::appInit();

	

	auto mesh = MeshManager::getSingletonPtr()->load(std::string("Â¥À¼ÕÊÅñ04.mesh"));

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* sphere = mSceneManager->createEntity("sphere", mesh);
	SceneNode* spherenode = root->createChildSceneNode("sphere");

	//spherenode->attachObject(sphere);

	mGameCamera->setDistance(1000.0f);

	mSceneManager->setSkyBox(true, "SkyLan", 50000);

	return true;
}

void SkeletonAnimation::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
}

EngineType SkeletonAnimation::getEngineType()
{
	return EngineType_Dx12;
}