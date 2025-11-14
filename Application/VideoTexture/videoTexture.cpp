#include "OgreHeader.h"
#include "VideoTexture.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreMeshManager.h"
#include "OgreRoot.h"
#include "OgreEntity.h"

VideoTextureApplication::VideoTextureApplication()
{

}

VideoTextureApplication::~VideoTextureApplication()
{

}

bool VideoTextureApplication::appInit()
{
	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	float w = 1.024f;
	float h = 0.768f;
	Ogre::Vector3 leftop = Ogre::Vector3(-w, h, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-w, -h, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(w, h, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(w, -h, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);
	std::string meshName = "myrect";
	auto mesh = Ogre::MeshManager::getSingletonPtr()->createRect(
		meshName,
		leftop, leftbottom, righttop, rightbottom, normal);

	Ogre::Entity* rect = mSceneManager->createEntity("rect", meshName);
	Ogre::SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	auto mat = Ogre::MaterialManager::getSingleton().getByName("myvideo");
	rect->setMaterial(0, mat);
	mGameCamera->setDistance(2.0f);
	Ogre::Camera* cam = mGameCamera->getCamera();

	cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	cam->setOrthoWindow(2.2, 2.2);
	return true;
}

void VideoTextureApplication::appUpdate(float delta)
{
	
}

void VideoTextureApplication::setup(
	RenderPipeline* renderPipeline,
	RenderContext& context,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{

}

void VideoTextureApplication::update(float delta)
{

}
