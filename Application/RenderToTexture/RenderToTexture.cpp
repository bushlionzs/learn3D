#include "OgreHeader.h"
#include "RenderToTexture.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreTextureManager.h"
#include "OgreTexture.h"
#include "OgreRenderTexture.h"
#include "OgreMaterialManager.h"
#include "OgreRoot.h"
#include "OgreAnimationState.h"
#include "OgreRenderWindow.h"
#include "OgreCamera.h"
#include "OgreViewport.h"

RenderToTexture::RenderToTexture()
{

}

RenderToTexture::~RenderToTexture()
{

}

bool RenderToTexture::appInit()
{
	ApplicationBase::appInit();

	auto mesh = MeshManager::getSingleton().load("ninja.mesh");
	Entity* cylinder = mSceneManager->createEntity("cylinder", mesh);
	SceneNode* cylindernode = mSceneManager->getRoot()->createChildSceneNode("cylinder");
	cylindernode->attachObject(cylinder);
	cylindernode->setPosition(Ogre::Vector3(0, -100.0f, 0.0f));
	mAnimationState = cylinder->getAnimationState(std::string("Walk"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}
	
	mGameCamera->setDistance(500.0f);

	TextureProperty texProperty;
	texProperty._tex_usage = TU_RENDERTARGET;
	texProperty._width = 1024;
	texProperty._height = 768;

	texProperty._backgroudColor = ColourValue::Blue;
	TexturePtr renderTexture =
		TextureManager::getSingleton().createManual("RenderToTexture", texProperty);

	RenderTarget* textureTarget = renderTexture->getBuffer()->getRenderTarget(0);

	Viewport* rv = textureTarget->addViewport(mGameCamera->getCamera());
	//DirectX::XMVECTORF32 mClearColor = DirectX::Colors::Gold;
	rv->setBackgroundColour(texProperty._backgroudColor);

	return true;
	MaterialPtr renderMaterial =
		MaterialManager::getSingleton().create("RenderToTextureMaterial");


	renderMaterial->addTexture("RenderToTexture");
	ShaderInfo sinfo;
	sinfo.shaderName = "ogresimple";
	renderMaterial->addShader(sinfo);
	renderMaterial->load();
	///
	auto sceneMgr = Ogre::Root::getSingletonPtr()->createSceneManger(std::string("other"));

	auto boxmesh = MeshManager::getSingleton().createBox("box", 2.5, "RenderToTextureMaterial");


	Entity* box = sceneMgr->createEntity("rect", boxmesh);
	mBoxNode = sceneMgr->getRoot()->createChildSceneNode("rect");
	mBoxNode->attachObject(box);
	mBoxNode->setPosition(Ogre::Vector3(4, 0, 0));
	//box->setMaterial(0, renderMaterial);
	Ogre::Camera* cam = sceneMgr->createCamera("aaaa");

	cam->updateCamera(Ogre::Vector3(0, 0, 15), Ogre::Vector3(0, 0, 0), Ogre::Vector3::UNIT_Y);

	auto vp = mRenderWindow->addViewport(cam, 2);
	vp->setClearEveryFrame(false);
	return true;
}


void RenderToTexture::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}

	if (mBoxNode)
	{
		float value = delta * 25;
		mBoxNode->yaw(Ogre::Degree(value));
		mBoxNode->pitch(Ogre::Degree(value));
	}
}

EngineType RenderToTexture::getEngineType()
{
	return EngineType_Vulkan;
}
