//#include "stdafx.h"
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
#include "OgreSubEntity.h"
#include "OgreRoot.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "CryEngineUtil.h"

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
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	ogreConfig.reverseDepth = false;
	mSceneManager = sceneManager;
	mGameCamera = gameCamera;
	mRenderWindow = renderWindow;
	mRenderSystem = renderSystem;
	mRenderPipeline = renderPipeline;
	cryEngineInit();
}

void BasicApplication::update(float delta)
{
	CryEngineContext context;
	context.gameCamera = mGameCamera;
	context.root = mRoot;
	updateCryEngineLevel(context);
}

void BasicApplication::addCustomDirectory()
{
	//ResourceManager::getSingletonPtr()->addDirectory(std::string("D:\\wow3.3.5\\Data"), "wow", true);
}

void BasicApplication::cryEngineInit()
{
	mRoot = mSceneManager->getRoot()->createChildSceneNode("root");

	CryEngineContext context;
	context.sceneManager = mSceneManager;
	context.root = mRoot;
	context.gameCamera = mGameCamera;
	

	mGameCamera->lookAt(
		Ogre::Vector3(95, 148.5, 34), 
		Ogre::Vector3(95, 149.5, 34),
		Ogre::Vector3(0, 0, 1));
	mGameCamera->setCameraType(Ogre::CameraMoveType_FirstPerson);
	mGameCamera->setMoveSpeed(100);
	mGameCamera->setRotateSpeed(0.01f);

	loadCryEngineLevel(context);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	Ogre::Matrix4 m;
	if (ogreConfig.reverseDepth)
	{
		float aspectInverse = ogreConfig.height / (float)ogreConfig.width;
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			Ogre::Math::PI / 3.0f, aspectInverse, 0.1, 6000);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			Ogre::Math::PI / 3.0f, aspect, 0.1, 6000);

	}
	mGameCamera->getCamera()->updateProjectMatrix(m);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);


	auto* rs = Ogre::Root::getSingleton().getRenderSystem();

	ShaderInfo shaderInfo;
	shaderInfo.shaderName = "Illum";
	shaderInfo.technique = "ZPass";
	auto zPrePassHandle = rs->createShaderProgram(shaderInfo, nullptr);
}





