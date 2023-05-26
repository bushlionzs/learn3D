#include "OgreHeader.h"
#include "SkeletonAnimation.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreViewport.h"
#include "OgreAnimationState.h"
#include "OgreSkeleton.h"
#include "ogre_skeleton_serializer.h"

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
		MeshManager::getSingletonPtr()->load(std::string("蒙古贵族女_03.mesh"));

	/*std::string name = "贵族女站立3.skeleton";
	Skeleton* skeleton = new Skeleton("贵族女站立3.skeleton");

	OgreSkeletonSerializerImpl serializer;
	auto stream = ResourceManager::getSingleton().openResource(name);
	serializer.importSkeleton(stream, skeleton);
	std::shared_ptr<Skeleton> ss(skeleton);
	mesh->applySkeleton(ss);*/
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", mesh);
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->updatechildren();
	gltfnode->attachObject(gltf);
	//gltfnode->setPosition(0.0, -1.0f, 0.0f);
	mAnimationState = gltf->getAnimationState(std::string("休闲04_02"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}
	//gltfnode->yaw(Ogre::Radian(-1.57f));
	//gltfnode->pitch(Ogre::Radian(-1.57f));
	
	mGameCamera->setDistance(500);
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