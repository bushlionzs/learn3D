#include "OgreHeader.h"
#include "SkeletonAnimation.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreViewport.h"
#include "OgreAnimationState.h"

SkeletonAnimation::SkeletonAnimation()
{

}

SkeletonAnimation::~SkeletonAnimation()
{

}

bool SkeletonAnimation::appInit()
{
	ApplicationBase::appInit();

	

	auto mesh = 
		MeshManager::getSingletonPtr()->load(std::string("CesiumMan.gltf"));

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", mesh);
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->attachObject(gltf);
	gltfnode->setPosition(0.0, -1.0f, 0.0f);
	mAnimationState = gltf->getAnimationState(std::string("Armature"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}
	gltfnode->yaw(Ogre::Radian(-1.57f));
	gltfnode->pitch(Ogre::Radian(-1.57f));
	
	mGameCamera->setDistance(3);
	mGameCamera->setMoveSpeed(25.0f);
	return true;
}

void SkeletonAnimation::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
}

EngineType SkeletonAnimation::getEngineType()
{
	return EngineType_Dx11;
}