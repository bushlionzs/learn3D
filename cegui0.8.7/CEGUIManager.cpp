#include "OgreHeader.h"
#include "CEGUIManager.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "OgreRenderWindow.h"
#include "OgreViewport.h"
//#include "System.h"

template<> CEGUIManager* Ogre::Singleton<CEGUIManager>::msSingleton = 0;

CEGUIManager::CEGUIManager()
{
	
}

CEGUIManager::~CEGUIManager()
{

}

bool CEGUIManager::_initialise(Ogre::RenderWindow* window)
{
	/*NOTICE_LOG("CEGUI initialise begin");
	mRenderWindow = window;
	mSceneManager = Ogre::Root::getSingleton().createSceneManger(std::string("cegui"));

	mCamera = mSceneManager->createCamera("cegui_camera");

	mCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	mCamera->setOrthoWindow(2, 2);
	Ogre::Vector3 eyePos = Ogre::Vector3(0, 0, 10);
	mCamera->updateCamera(eyePos, Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_Y);


	mViewPort = mRenderWindow->addViewport(mCamera, 2);
	mViewPort->setClearEveryFrame(false);




	InputManager::getSingleton().addListener(this);

	Ogre::Root::getSingleton().addFrameListener(this);

	m_pCEGUIRender = new CEGUI::OgreCEGUIRenderer
	(
		(Ogre::RenderTarget*)mRenderWindow,
		0,
		false,
		0,
		mSceneManager
	);

	new CEGUI::System(m_pCEGUIRender);


	NOTICE_LOG("CEGUI initialise end");*/
	return true;
}

void CEGUIManager::injectMouseMove(int _absx, int _absy, int _absz)
{
	
}

void CEGUIManager::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	

}

void CEGUIManager::injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id)
{
	
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

