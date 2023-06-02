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

	base3();
	return true;
}

class MyRayResultCallback : public Bullet::RayResultCallback
{
	virtual void addSingleResult(const MoveObject* other, float distance)
	{
		int kk = 0;
	}
};
void Basic::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}

	if (mDynWorld)
	{
		mDynWorld->getBtWorld()->stepSimulation(delta, 1);

		//for (int x = -100; x < 100; x++)
		{
			//for (int z = 0; z < 100; z++)
			{
				Ogre::Ray ray(Ogre::Vector3(210, 1000, 0), Ogre::Vector3(0, -1, 0));
				MyRayResultCallback cb;
				mDynWorld->rayTest(ray, &cb, 2000);
			}
			
		}
		
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
	float aa = 100.0f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, 0.0f, aa);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, 0.0f, -aa);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, 0.0f, aa);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, 0.0f, -aa);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);
	auto mesh = MeshManager::getSingletonPtr()->createRect(
		"myrect",
		leftop, leftbottom, righttop, rightbottom, normal);
	//mesh = MeshManager::getSingletonPtr()->load(std::string("д╬ге2.mesh"));

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* sphere = mSceneManager->createEntity("sphere", mesh);
	SceneNode* spherenode = root->createChildSceneNode("sphere");
	spherenode->attachObject(sphere);
	auto pos = Ogre::Vector3(200, 0, 0);
	spherenode->setPosition(pos);
	const AxisAlignedBox& box = sphere->getBoundingBox();

	mGameCamera->setDistance(2000);
	mGameCamera->setMoveSpeed(100.0f);

	initPhysics();

	mDynWorld->addRigidBody(0, sphere, Bullet::CT_TRIMESH);
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

void Basic::initPhysics()
{
	
	mDynWorld.reset(new Bullet::DynamicsWorld(Vector3(0, -9.8, 0)));
}