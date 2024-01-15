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
#include "mytestWindow.h"
//#include "mainMenuWindow.h"
#include <CEGUI/WindowManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/System.h>
//#include <CEGUI/ImagesetManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/ImageManager.h>

using namespace CEGUI;

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

bool GameUI::appInit()
{
	ApplicationBase::appInit();


	// load windows look
	SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");

	// load font and setup default if not loaded via scheme
	Font& defaultFont = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
	

	// set up defaults
	//guiContext->getMouseCursor().setDefaultImage("WindowsLook/MouseArrow");

	// load the drive icons imageset
	ImageManager::getSingleton().loadImageset("DriveIcons.imageset");

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
	return EngineType_Dx11;
}