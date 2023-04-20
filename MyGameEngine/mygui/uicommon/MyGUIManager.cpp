#include "OgreHeader.h"
#include "MyGUIManager.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "MyGUI_InputManager.h"
#include "MyGUI_Gui.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"

template<> MyGUIManager* Ogre::Singleton<MyGUIManager>::msSingleton = 0;

MyGUIManager::MyGUIManager()
{

}

MyGUIManager::~MyGUIManager()
{

}

bool MyGUIManager::_initialise(Ogre::RenderWindow* window)
{
	mRenderWindow = window;
	mSceneManager = Ogre::Root::getSingleton().createSceneManger(std::string("mygui"));

	mCamera = mSceneManager->createCamera("MyguiCamera");

	mCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	mCamera->setOrthoWindow(2, 2);

	mCameraNode = mSceneManager->getRoot()->createChildSceneNode(BLANKSTRING);
	mCameraNode->attachObject(mCamera);
	mCameraNode->setPosition(0, 0, 10);


	mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(mRenderWindow, mSceneManager, "");

	Ogre::Viewport* vp = mRenderWindow->addViewport(mCamera, 1);
	vp->setClearEveryFrame(false);
	mResourceFileName = "MyGUI_Core.xml";
	mGUI = new MyGUI::Gui();
	mGUI->initialise(mResourceFileName);

	

	InputManager::getSingleton().addListener(this);

	Ogre::Root::getSingleton().addFrameListener(this);

	return true;
}

void MyGUIManager::injectMouseMove(int _absx, int _absy, int _absz)
{
	MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
}

void MyGUIManager::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, (MyGUI::MouseButton::Enum)_id);

}

void MyGUIManager::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
	MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, (MyGUI::MouseButton::Enum)_id);
}

void MyGUIManager::injectKeyPress(KeyCode _key, uint32_t _text)
{
	MyGUI::InputManager::getInstance().injectKeyPress((MyGUI::KeyCode::Enum)_key.getValue(), _text);
}

void MyGUIManager::injectKeyRelease(KeyCode _key)
{
	MyGUI::InputManager::getInstance().injectKeyPress((MyGUI::KeyCode::Enum)_key.getValue());
}

void MyGUIManager::injectMouseWheel(int _absz)
{

}

bool MyGUIManager::frameStarted(const FrameEvent& evt)
{
	mSceneManager->update(evt.timeSinceLastFrame);
	return true;
}

void MyGUIManager::createGuiPlatform()
{
	
}

