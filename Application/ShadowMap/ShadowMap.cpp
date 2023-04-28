#include "OgreHeader.h"
#include "ShadowMap.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMeshManager.h"
#include "OgreTextureManager.h"
#include "OgreRenderTexture.h"
#include "OgreCamera.h"
#include "OgreAnimationState.h"
#include "OgreLight.h"
#include "OgreMaterialManager.h"
#include "OgreViewport.h"

ShadowMap::ShadowMap()
{

}

ShadowMap::~ShadowMap()
{

}


bool ShadowMap::appInit()
{
	ApplicationBase::appInit();
	mViewport->setShadowsEnabled(true);
	auto root = mSceneManager->getRoot();

	MeshManager::getSingletonPtr()->CreateSphere("sphere.mesh", 0.5f, 20, 20);
	MeshManager::getSingletonPtr()->CreateCylinder("cylinder.mesh", 0.5f, 0.3f, 3.0f, 20, 20);
	
	float aa = 20.0f;
	float h = -2.0f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, h , -aa);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, h, aa);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, h, -aa);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, h , aa);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 1.0f, 0.0f);
	auto mesh = MeshManager::getSingletonPtr()->createRect(
		"myrect",
		leftop, leftbottom, righttop, rightbottom, normal);
	auto mat = MaterialManager::getSingleton().getByName("myground");
	mesh->getSubMesh(0)->setMaterial(mat);
	Entity* ground = mSceneManager->createEntity("ground", mesh);
	SceneNode* groundnode = root->createChildSceneNode("ground");
	groundnode->attachObject(ground);

	Entity* sphere = mSceneManager->createEntity("sphere", "sphere.mesh");
	SceneNode* spherenode = root->createChildSceneNode("sphere");
	spherenode->setPosition(Ogre::Vector3(0.0f, 1.5f, 0.0f));
	spherenode->attachObject(sphere);

	Entity* cylinder = mSceneManager->createEntity("cylinder", "cylinder.mesh");
	SceneNode* cylindernode = root->createChildSceneNode("cylinder");
	cylindernode->attachObject(cylinder);
	cylindernode->setPosition(Ogre::Vector3(0, 0.0, 0.0f));
	sphere->setCastShadows(true);
	cylinder->setCastShadows(true);
	ground->setCastShadows(false);
	mesh = MeshManager::getSingleton().load("ninja.mesh");
	Entity* ninja = mSceneManager->createEntity("ninja", mesh);
	SceneNode* ninjanode = root->createChildSceneNode("ninja");
	ninjanode->attachObject(ninja);
	ninjanode->setPosition(Ogre::Vector3(-4, -2, -1.0f));
	ninjanode->yaw(Ogre::Radian(3.14f));
	float s = 0.015f;
	ninjanode->setScale(Ogre::Vector3(s, s, s));
	ninja->setCastShadows(true);
	mAnimationState = ninja->getAnimationState(std::string("Walk"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}

	aa = 0.8f;
	leftop = Ogre::Vector3(-aa, aa, 0.0f);
	leftbottom = Ogre::Vector3(-aa, -aa, 0.0f);
	righttop = Ogre::Vector3(aa, aa, 0.0f);
	rightbottom = Ogre::Vector3(aa, -aa, 0.0f);
	normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);
	mesh = MeshManager::getSingletonPtr()->createRect(
		"myrect",
		leftop, leftbottom, righttop, rightbottom, normal);
	Entity* rect = mSceneManager->createEntity("rect", mesh);
	SceneNode* rectnode = root->createChildSceneNode("rect");
	//rectnode->attachObject(rect);
	rectnode->setPosition(1.5, 0.0f, 3.0f);

	mat = MaterialManager::getSingleton().getByName("shadow");

	rect->setMaterial(0, mat);
	mGameCamera->setDistance(8.0f);
	mGameCamera->setMoveSpeed(10.0f);

	auto light = mSceneManager->createLight("shadow");
	light->setLightType(LightType_Direction, 0);

	auto m4 = Ogre::Math::makeLookAtRH(
		Ogre::Vector3(-20, 20, -20), Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_Y);

	auto q = m4.extractQuaternion();
	
	mLightNode = root->createChildSceneNode("light");

	auto subnode = mLightNode->createChildSceneNode("shadow");
	subnode->attachObject(light);
	subnode->setOrientation(q);
	subnode->setPosition(Ogre::Vector3(-20, 20, -20));


	Matrix3 m3;
	q.ToRotationMatrix(m3);

	auto bb = Ogre::Vector3::ZERO - Ogre::Vector3(-20, 20, -20);
	bb.normalise();
	auto dir = m3.GetColumn(2);

	return true;
}

void ShadowMap::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}

	mLightNode->yaw(Ogre::Radian(3.14) * delta * 0.1);
}

EngineType ShadowMap::getEngineType()
{
	return EngineType_Dx11;
}