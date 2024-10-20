#include "stdafx.h"
#include "basic.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreAnimationState.h"
#include "renderSystem.h"
#include "OgreCamera.h"
#include "OgreRenderTarget.h"
#include "OgreRenderWindow.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"

BasicApplication::BasicApplication()
{

}

BasicApplication::~BasicApplication()
{

}


void BasicApplication::setup(
	RenderPipeline* renderPipeline,
	RenderSystem* renderSystem,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{

	mSceneManager = sceneManager;
	mGameCamera = gameCamera;
	mRenderWindow = renderWindow;
	mRenderSystem = renderSystem;
	base1();

	RenderPassInput input;
	input.color = renderWindow->getColorTarget();
	input.depth = renderWindow->getDepthTarget();
	input.cam = gameCamera->getCamera();
	input.sceneMgr = sceneManager;
	auto mainPass = createStandardRenderPass(input);
	renderPipeline->addRenderPass(mainPass);
}

void BasicApplication::update(float delta)
{
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
}



EngineType BasicApplication::getEngineType()
{
	return EngineType_Vulkan;
}

void BasicApplication::addCustomDirectory()
{
	//ResourceManager::getSingletonPtr()->addDirectory(std::string("D:\\wow3.3.5\\Data"), "wow", true);
}


void BasicApplication::base1()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	float aa = 1.0f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, aa, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, -aa, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, aa, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, -aa, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);

	std::string meshName = "box.gltf";
	
	auto mesh = MeshManager::getSingletonPtr()->createRect(
		nullptr,
		meshName,
		leftop, leftbottom, righttop, rightbottom, normal);

	Entity* rect = mSceneManager->createEntity("rect", meshName);
	SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	//mSceneManager->setSkyBox(true, "SkyLan", 10000);
	mGameCamera->updateCamera(Ogre::Vector3(0, 0.0f, -2.5f), Ogre::Vector3::ZERO);
	mGameCamera->setMoveSpeed(5);

}

void BasicApplication::base2()
{
	std::string name = "��_��ɽ_����_13.mesh";
	name = "¥������04.mesh";
	auto mesh = MeshManager::getSingletonPtr()->load(name);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* sphere = mSceneManager->createEntity("sphere", name);
	SceneNode* spherenode = root->createChildSceneNode("sphere");

	spherenode->attachObject(sphere);

	mSceneManager->setSkyBox(true, "SkyLan", 50000);

	mGameCamera->updateCamera(Ogre::Vector3(2000, 0.0f, 0.0f), Ogre::Vector3(0.0f, 90.0f, 0.0f));
	mGameCamera->setMoveSpeed(200);
}

void BasicApplication::base3()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	auto mesh = MeshManager::getSingleton().createBox("box.mesh", 1, "mybox");

	auto& meshName = mesh->getName();
	{
		auto entity = mSceneManager->createEntity("box1", meshName);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(0.0f, 0.0f, -5.0f);
	}

	{
		auto entity = mSceneManager->createEntity("box1", meshName);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(0.0f, 0.0f, 5.0f);
	}

	{
		auto entity = mSceneManager->createEntity("box1", meshName);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(-5.0f, 0.0f, 0.0f);
	}

	{
		auto entity = mSceneManager->createEntity("box1", meshName);
		SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(5.0f, 0.0f, 0.0f);
	}
	

	mGameCamera->setDistance(2.0f);

	mGameCamera->setMoveSpeed(25.0f);
}

void BasicApplication::base4()
{
	std::string meshname = "�ɹŹ���Ů_03.mesh";
	auto mesh = MeshManager::getSingletonPtr()->load(meshname);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", meshname);
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->updatechildren();
	gltfnode->attachObject(gltf);

	mAnimationState = gltf->getAnimationState(std::string("����04_02"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}

	mGameCamera->setHeight(300.0f);
	mGameCamera->setDistance(500);
	mGameCamera->setMoveSpeed(25.0f);
}

void BasicApplication::base5()
{
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	float aa = 0.5f;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, aa, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, -aa, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, aa, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, -aa, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);

	std::string meshname = "box.gltf";
	auto mesh = MeshManager::getSingletonPtr()->load(meshname);
	Entity* rect = mSceneManager->createEntity(meshname, meshname);
	SceneNode* rectnode = root->createChildSceneNode(meshname);
	rectnode->attachObject(rect);

	mSceneManager->setSkyBox(true, "SkyMap", 1000);

	mGameCamera->setDistance(2.5f);
	mGameCamera->setMoveSpeed(5);
}