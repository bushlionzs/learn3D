#include "OgreHeader.h"
#include "CEGUIManager.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include <CEGUI/System.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/System.h>
//#include <CEGUI/ImagesetManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/ImageManager.h>
#include "Renderer.h"

using namespace CEGUI;
template<> CEGUIManager* Ogre::Singleton<CEGUIManager>::msSingleton = 0;

CEGUIManager::CEGUIManager()
{
	
}

CEGUIManager::~CEGUIManager()
{

}

bool CEGUIManager::_initialise(Ogre::RenderWindow* window)
{
	NOTICE_LOG("CEGUI initialise begin");
	mRenderWindow = window;
	mSceneManager = Ogre::Root::getSingleton().createSceneManger(std::string("cegui"));

	mCamera = mSceneManager->createCamera("cegui_camera");

	mCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	auto width = window->getWidth();
	auto height = window->getHeight();

	

	mCamera->setOrthoWindow(width, height);
	Ogre::Vector3 eyePos = Ogre::Vector3(0, 0, 10);
	mCamera->updateCamera(eyePos, Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_Y);


	mViewPort = mRenderWindow->addViewport(mCamera, 2);
	mViewPort->setClearEveryFrame(false);


	InputManager::getSingleton().addListener(this);

	Ogre::Root::getSingleton().addFrameListener(this);

	CEGUI::OgreRenderer& render = CEGUI::OgreRenderer::create();

	CEGUI::System::create(render, nullptr, 0, nullptr, 0, "");

	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		CEGUI::Sizef((float)width, (float)height));

	auto& rt = render.getDefaultRenderTarget();
	auto& context = CEGUI::System::getSingleton().createGUIContext(rt);

	mGUIContext = &context;

	ImageManager::getSingleton().loadImageset("MouseCursor.imageset");
	context.getMouseCursor().setDefaultImage("MouseCursor/Normal");
	
	if(1)
	{
		ImageManager::getSingleton().loadImageset("ui_duihua_1.imageset.xml");
		ImageManager::getSingleton().loadImageset("ui_mainboard_2.imageset.xml");
		ImageManager::getSingleton().loadImageset("ui_mainboard_3.imageset.xml");
		ImageManager::getSingleton().loadImageset("DriveIcons.imageset");
		ImageManager::getSingleton().loadImageset("cjsh_icons_1.imageset");
		CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	}

	

	auto mNode = mSceneManager->getRoot()->createChildSceneNode("cegui");
	mNode->attachObject(this);

	NOTICE_LOG("CEGUI initialise end");
	return true;
}

void CEGUIManager::addRenderable(Ogre::Renderable* r)
{
	mRenderables.push_back(r);
}

const std::vector<Renderable*>& CEGUIManager::getRenderableList()
{
	mRenderables.clear();
	mGUIContext->draw();

	return mRenderables;
}

const AxisAlignedBox& CEGUIManager::getBoundingBox(void) const
{
	static AxisAlignedBox box;
	box.setInfinite();
	return box;
}

void CEGUIManager::injectMouseMove(int _absx, int _absy, int _absz)
{
	mGUIContext->injectMousePosition(_absx, _absy);
}

void CEGUIManager::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	CEGUI::MouseButton dummy;
	dummy = (CEGUI::MouseButton)_id;
	//mGUIContext->injectMousePosition(_absx, _absy);
	mGUIContext->injectMouseButtonDown(dummy);

}

void CEGUIManager::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
	CEGUI::MouseButton dummy;
	dummy = (CEGUI::MouseButton)_id;
	//mGUIContext->injectMousePosition(_absx, _absy);
	mGUIContext->injectMouseButtonUp(dummy);
}

void CEGUIManager::injectKeyPress(KeyCode _key, uint32_t _text)
{
	
}

void CEGUIManager::injectKeyRelease(KeyCode _key)
{

}

void CEGUIManager::injectMouseWheel(int _absz)
{

}

bool CEGUIManager::frameStarted(const FrameEvent& evt)
{
	mSceneManager->update(evt.timeSinceLastFrame);
	return true;
}

