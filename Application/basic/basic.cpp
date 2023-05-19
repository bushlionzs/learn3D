#include "OgreHeader.h"
#include "basic.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "OGImpact.h"
#include "OGImpactManager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreAnimationState.h"

Basic::Basic()
{

}

Basic::~Basic()
{

}

bool Basic::appInit()
{
	ApplicationBase::appInit();

	base3();
	return true;
}

void Basic::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
}

EngineType Basic::getEngineType()
{
	return EngineType_Dx11;
}

void Basic::addCustomDirectory()
{
	//ResourceManager::getSingletonPtr()->addDirectory(std::string("D:\\wow3.3.5\\Data"), "wow", true);
}

void Basic::base1()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");


	float aa = 1.0f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, aa, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, -aa, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, aa, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, -aa, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);
	auto mesh = MeshManager::getSingletonPtr()->createRect(
		"myrect",
		leftop, leftbottom, righttop, rightbottom, normal);
	Entity* rect = mSceneManager->createEntity("rect", mesh);
	SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	mGameCamera->setDistance(3.0f);
	mGameCamera->setMoveSpeed(25.0f);
}

void Basic::base2()
{
	auto mesh =
		MeshManager::getSingletonPtr()->load(std::string("sphere.mesh"));

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* sphere = mSceneManager->createEntity("sphere", mesh);
	SceneNode* spherenode = root->createChildSceneNode("sphere");
	spherenode->attachObject(sphere);

	mGameCamera->setDistance(300.0f);
	mGameCamera->setMoveSpeed(100.0f);
}

void Basic::base3()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	SceneNode* node = root->createChildSceneNode("sphere");
	Ogre::String effectName = "reachable_projector";
	mProjectorEffect = Orphigine::ImpactManager::getSingleton().createEffect(effectName, 0);
	mProjectorEffect->createSceneNode(node);

	mGameCamera->setDistance(300.0f);
	mGameCamera->setHeight(30.0f);

	mGameCamera->setMoveSpeed(25.0f);
}