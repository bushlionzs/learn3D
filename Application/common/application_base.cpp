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
#include "MyGUIManager.h"
#include "OgreViewport.h"

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
	return EngineType_Dx11;
}

bool ApplicationBase::appInit()
{
	mApplicationWindow = new ApplicationWindow;
	mApplicationWindow->createWindow(1024, 768);
	if (!InputManager::getSingletonPtr())
	{
		new InputManager();
	}
	
	HWND wnd = mApplicationWindow->getWnd();
	InputManager::getSingletonPtr()->createInput((size_t)wnd);

	new Ogre::Root();


	EngineType type = getEngineType();
	mRenderSystem = Ogre::Root::getSingleton().createRenderEngine(wnd, type);
	if (!mRenderSystem)
	{
		return false;
	}

	Ogre::ColourValue color = ColourValue::Black;

	Ogre::NameValuePairList params;
	params["externalWindowHandle"] = Ogre::StringConverter::toString((uint64_t)wnd);
	params["backGroundColor"] = Ogre::StringConverter::toString(color);
	mRenderWindow = mRenderSystem->createRenderWindow("", 1024, 768, &params);

	
	ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\resources"), "sujian", true);
	ResourceManager::getSingletonPtr()->addDirectory(std::string("..\\shader"), "sujian", true);
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

	/*new MyGUIManager;
	MyGUIManager::getSingleton()._initialise(mRenderWindow);*/
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
		snprintf(buffer, sizeof(buffer), "render:%s, fps:%lld, triangle:%d", 
			mRenderSystem->getRenderSystemName().c_str(),
			mLastFPS, mRenderSystem->getTriangleCount());
		::SetWindowText(mApplicationWindow->getWnd(), buffer);
	}

	
}