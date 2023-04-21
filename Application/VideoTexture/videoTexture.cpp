#include "OgreHeader.h"
#include "VideoTexture.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreCamera.h"

VideoTexture::VideoTexture()
{

}

VideoTexture::~VideoTexture()
{

}

bool VideoTexture::appInit()
{
	ApplicationBase::appInit();

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	float w = 1.024f;
	float h = 0.768f;
	Ogre::Vector3 leftop = Ogre::Vector3(-w, h, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-w, -h, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(w, h, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(w, -h, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);
	auto mesh = MeshManager::getSingletonPtr()->createRect(
		"myrect",
		leftop, leftbottom, righttop, rightbottom, normal);

	Entity* rect = mSceneManager->createEntity("rect", mesh);
	SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	auto mat = MaterialManager::getSingleton().getByName("myvideo");
	rect->setMaterial(0, mat);
	mGameCamera->setDistance(2.0f);
	Ogre::Camera* cam = mGameCamera->getCamera();

	cam->setProjectionType(PT_ORTHOGRAPHIC);
	cam->setOrthoWindow(2.2, 2.2);
	return true;
}

void VideoTexture::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
}

EngineType VideoTexture::getEngineType()
{
	return EngineType_Dx12;
}