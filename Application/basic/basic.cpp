#include "stdafx.h"
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

	base1();
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
	//return EngineType_Dx11;
	return EngineType_Vulkan;
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

	mSceneManager->setSkyBox(true, "SkyLan", 50000);

	mGameCamera->setDistance(6.0f);
	mGameCamera->setMoveSpeed(25.0f);
}

void Basic::base2()
{
	std::string name = "Êé_·ðÉ½_·¿ÎÝ_13.mesh";
	//name = "Â¥À¼ÕÊÅñ04.mesh";
	auto mesh = MeshManager::getSingletonPtr()->load(name);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* sphere = mSceneManager->createEntity("sphere", mesh);
	SceneNode* spherenode = root->createChildSceneNode("sphere");

	//spherenode->attachObject(sphere);

	mGameCamera->setDistance(2000.0f);

	mSceneManager->setSkyBox(true, "SkyLan", 50000);
}

void Basic::base3()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	auto mesh = MeshManager::getSingleton().createBox("box.mesh", 1, "mybox");

	{
		auto entity = mSceneManager->createEntity("box1", mesh);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(0.0f, 0.0f, -5.0f);
	}

	{
		auto entity = mSceneManager->createEntity("box1", mesh);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(0.0f, 0.0f, 5.0f);
	}

	{
		auto entity = mSceneManager->createEntity("box1", mesh);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(-5.0f, 0.0f, 0.0f);
	}

	{
		auto entity = mSceneManager->createEntity("box1", mesh);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(5.0f, 0.0f, 0.0f);
	}
	

	mGameCamera->setDistance(2.0f);

	mGameCamera->setMoveSpeed(25.0f);
}
