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

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	std::string m2name = "CREATURE\\AKAMA\\AKAMA.M2";
	m2name = "CREATURE\\GOBLIN\\GLBLINSHREDDER.M2";
	m2name = "CREATURE\\GOBLIN\\GOBLIN.M2";
	m2name = "ITEM\\OBJECTCOMPONENTS\\AMMO\\ARROWFIREFLIGHT_01.M2";
	//m2name = "akama.mesh";
	//m2name = "ninja.mesh";
	auto mesh =
	MeshManager::getSingletonPtr()->load(m2name);
	Entity* m2 = mSceneManager->createEntity("m2", mesh);
	SceneNode* gltfnode = root->createChildSceneNode("m2");
	gltfnode->attachObject(m2);
	//mAnimationState = m2->getAnimationState(std::string("Walk0"));
	//if (mAnimationState)
	//{
	//	mAnimationState->setEnabled(true);
	//	mAnimationState->setLoop(true);
	//}
	/*float aa = 1.0f;
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
	rectnode->attachObject(rect);*/

	mGameCamera->setDistance(3.0f);
	mGameCamera->setMoveSpeed(25.0f);
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
	ResourceManager::getSingletonPtr()->addDirectory(std::string("D:\\wow3.3.5\\Data"), "wow", true);
}