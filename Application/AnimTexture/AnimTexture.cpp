#include "OgreHeader.h"
#include "AnimTexture.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "OGImpact.h"
#include "OGImpactManager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreCamera.h"

AnimTexture::AnimTexture()
{

}

AnimTexture::~AnimTexture()
{

}

bool AnimTexture::appInit()
{
	ApplicationBase::appInit();

	mGameCamera->getCamera()->setFarClipDistance(100.0f);

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
	rectnode->setPosition(Ogre::Vector3(-2.0f, 0.0f, 0.0f));


	Entity* rect2 = mSceneManager->createEntity("rect2", mesh);
	SceneNode* rectnode2 = root->createChildSceneNode("rect2");
	rectnode2->attachObject(rect2);
	rectnode2->setPosition(Ogre::Vector3(2.0f, 0.0f, 0.0f));
	auto mat = MaterialManager::getSingleton().getByName("bomb");
	rect2->setMaterial(0, mat);

	mGameCamera->setDistance(10);
	auto cam = mGameCamera->getCamera();
	cam->setProjectionType(PT_ORTHOGRAPHIC);
	cam->setOrthoWindow(10.24, 7.68);
	mGameCamera->setMoveSpeed(20.0f);

	return true;
}

void AnimTexture::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
}

EngineType AnimTexture::getEngineType()
{
	return EngineType_Vulkan;
}

bool AnimTexture::isUseMyGUI()
{
	return false;
}