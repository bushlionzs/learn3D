#include "OgreHeader.h"
#include "application_base.h"
#include "application_window.h"
#include "InputManager.h"
#include "renderSystem.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "engine_manager.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
#include "GameTableManager.h"
#include "engine_manager.h"
#include "CEGUIManager.h"

ApplicationBase::ApplicationBase()
{
}

ApplicationBase::~ApplicationBase()
{

}

bool ApplicationBase::frameStarted(const FrameEvent& evt)
{
	appUpdate(evt.timeSinceLastFrame);
	return true;
}

EngineType ApplicationBase::getEngineType()
{
	return EngineType_Dx12;
}

bool ApplicationBase::appInit()
{
	mApplicationWindow = new ApplicationWindow;
	mApplicationWindow->createWindow(1280, 768);
	if (!InputManager::getSingletonPtr())
	{
		new InputManager();
	}
	
	HWND wnd = mApplicationWindow->getWnd();
	InputManager::getSingletonPtr()->createInput((size_t)wnd);
	EngineType type = getEngineType();
	new Ogre::Root;
	Ogre::Root::getSingleton()._initialise();
	mRenderSystem = Ogre::Root::getSingleton().createRenderEngine(wnd, type);
	if (!mRenderSystem)
	{
		return false;
	}

	new EngineManager;
	EngineManager::getSingleton().initialise();

	
	

	Ogre::ColourValue color(0.678431f, 0.847058f, 0.901960f, 1.000000000f);
	Ogre::NameValuePairList params;
	params["externalWindowHandle"] = Ogre::StringConverter::toString((uint64_t)wnd);
	params["backGroundColor"] = Ogre::StringConverter::toString(color);
	mRenderWindow = mRenderSystem->createRenderWindow("", 1280, 768, &params);

	
	ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\..\\resources"), "sujian", true);
	addCustomDirectory();
	ResourceManager::getSingletonPtr()->loadAllResource();
	
	mSceneManager = EngineManager::getSingletonPtr()->getSceneManager();

	auto camera = EngineManager::getSingletonPtr()->getMainCamera();

	camera->setNearClipDistance(1.0f);
	mViewport = mRenderWindow->addViewport(camera);
	mViewport->setBackgroundColour(color);
	mViewport->setClearEveryFrame(true);
	EngineManager::getSingleton().setViewPort(mViewport);
	mGameCamera = new GameCamera(camera, mSceneManager, mApplicationWindow->getWnd());

	InputManager::getSingletonPtr()->addListener(mGameCamera);

	Ogre::Root::getSingleton().addFrameListener(this);

	if (isUseCEGUI())
	{
		ShowCursor(FALSE);
		SetCursor(NULL);
		new CEGUIManager;
		CEGUIManager::getSingleton()._initialise(mRenderWindow);
	}
	

	
	return true;
}

void ApplicationBase::appUpdate(float delta)
{
	InputManager::getSingletonPtr()->captureInput();
	mGameCamera->update(delta);
}

void ApplicationBase::run()
{
	MSG msg;
	mRenderSystem->ready();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			Ogre::Root::getSingletonPtr()->renderOneFrame();
			ShowFrameFrequency();
		}
	}
}

void ApplicationBase::ShowFrameFrequency()
{
	if (mLastFPS != Ogre::Root::getSingletonPtr()->getCurrentFPS())
	{
		mLastFPS = Ogre::Root::getSingletonPtr()->getCurrentFPS();


		char buffer[256];
		snprintf(buffer, sizeof(buffer), "render:%s, fps:%lld, triangle:%d, batch:%d", 
			mRenderSystem->getRenderSystemName().c_str(),
			mLastFPS, mRenderSystem->getTriangleCount(),
			mRenderSystem->getBatchCount());
		::SetWindowText(mApplicationWindow->getWnd(), buffer);
	}

	
}