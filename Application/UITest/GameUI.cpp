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
#include "mainMenuWindow.h"
#include <CEGUIWindowManager.h>
#include <CEGUIFontManager.h>
#include <CEGUISchemeManager.h>
#include <CEGUISystem.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIWindow.h>
#include <CEGUIPushButton.h>

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


	/*auto test = new MyTestWindow;
	test->getView()->setPosition(10, 100);*/
	/*mViewport->setAutoUpdated(false);

	auto vp = MyGUIManager::getSingleton().getViewport();

	vp->setClearEveryFrame(true);
	Ogre::ColourValue color(0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f);
	vp->setBackgroundColour(color);*/

	WindowManager& winMgr = WindowManager::getSingleton();
	auto root = winMgr.createWindow("DefaultWindow", "Root");

	SchemeManager::getSingleton().loadScheme("TaharezLook.scheme");
	System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	FontManager::getSingleton().createFont(FreeType, "Commonv2c.ttf");
	ImagesetManager::getSingleton().createImagesetFromImageFile("BackgroundImage", "GPN-2000-001437.tga");

	Window* background = winMgr.createWindow("TaharezLook/StaticImage", "background_wnd");
	background->setWindowPosition(UVector2(cegui_reldim(0), cegui_reldim(0)));
	background->setWindowSize(UVector2(cegui_reldim(1), cegui_reldim(1)));
	// disable frame and standard background
	background->setProperty("FrameEnabled", "false");
	background->setProperty("BackgroundEnabled", "false");
	// set the background image
	background->setProperty("Image", "set:BackgroundImage image:full_image");
	// install this as the root GUI sheet
	System::getSingleton().setGUISheet(background);

	Window* sheet = winMgr.createWindow("DefaultWindow", "root_wnd");
	// attach this to the 'real' root
	background->addChildWindow(sheet);

	PushButton* btn = static_cast<PushButton*>(winMgr.createWindow("TaharezLook/Button", "QuitButton"));
	sheet->addChildWindow(btn);
	btn->setText("Quit!");
	btn->setWindowPosition(UVector2(cegui_reldim(0.035f), cegui_reldim(0.0f)));
	btn->setWindowSize(UVector2(cegui_reldim(0.1f), cegui_reldim(0.036f)));
	//btn->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&Demo4Sample::handleQuit, this));
	btn->setAlwaysOnTop(true);

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