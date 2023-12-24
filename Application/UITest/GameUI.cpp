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
#include "PackageWindow.h"

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

bool GameUI::appInit()
{
	ApplicationBase::appInit();


	PackageWindow* test = new PackageWindow;
	test->getView()->setPosition(300, 100);
	mViewport->setAutoUpdated(false);

	auto vp = MyGUIManager::getSingleton().getViewport();

	vp->setClearEveryFrame(true);
	Ogre::ColourValue color(0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f);
	vp->setBackgroundColour(color);

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
	return EngineType_Dx11;
}