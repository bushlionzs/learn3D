#include "stdafx.h"
#include "GameUI.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "SelfEquipWindow.h"
#include "PackageWindow.h"
#include "OgreViewport.h"
#include "MyGUIManager.h"
#include "OgreTextureManager.h"
#include "OgreMaterialManager.h"
#include "OgreRenderTexture.h"
#include "OgreCamera.h"
#include "role.h"

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

bool GameUI::appInit()
{
	ApplicationBase::appInit();

	SelfEquipWindow* selfEquipWindow = new SelfEquipWindow;
	selfEquipWindow->getView()->setPosition(300, 100);
	mViewport->setAutoUpdated(false);

	/*auto mesh = MeshManager::getSingleton().load("ninja.mesh");
	Entity* cylinder = mSceneManager->createEntity("cylinder", mesh);
	SceneNode* cylindernode = mSceneManager->getRoot()->createChildSceneNode("cylinder");
	cylindernode->attachObject(cylinder);
	cylindernode->setPosition(Ogre::Vector3(0, -100.0f, 0.0f));
	cylindernode->yaw(Ogre::Radian(3.14));
	mAnimationState = cylinder->getAnimationState(std::string("Walk"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}*/

	mRole = new Role;
	mRole->createRoleData();
	auto rolepos = Ogre::Vector3(15.0, -90.0f, 0.0f);
	mRole->setPosition(rolepos);
	mRole->walk();
	auto vp = MyGUIManager::getSingleton().getViewport();

	vp->setClearEveryFrame(true);
	Ogre::ColourValue color(0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f);
	vp->setBackgroundColour(color);

	TextureProperty texProperty;
	texProperty._tex_usage = TU_RENDERTARGET;
	texProperty._width = 512;
	texProperty._height = 512;

	texProperty._backgroudColor = color;
	texProperty._backgroudColor.a = 0.0f;
	TexturePtr renderTexture =
		TextureManager::getSingleton().createManual("RenderToTexture", texProperty);

	RenderTarget* textureTarget = renderTexture->getBuffer()->getRenderTarget(0);

	Viewport* rv = textureTarget->addViewport(mGameCamera->getCamera());
	float width = 190.0f;
	float height = 330;
	mGameCamera->getCamera()->setAspectRatio(width / height);
	mGameCamera->setDistance(320);
	//DirectX::XMVECTORF32 mClearColor = DirectX::Colors::Gold;
	rv->setBackgroundColour(texProperty._backgroudColor);


	selfEquipWindow->setModelTexture("RenderToTexture");

	return true;
}

void GameUI::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);

	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
}

EngineType GameUI::getEngineType()
{
	return EngineType_Vulkan;
}