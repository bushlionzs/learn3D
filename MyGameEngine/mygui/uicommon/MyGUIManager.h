#pragma once
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include "OgreSingleton.h"
#include "InputManager.h"
#include "OgreFrameListener.h"

class MyGUIManager : public Ogre::Singleton<MyGUIManager>, 
	public FrameListener,
	public InputListener
{
public:
	MyGUIManager();
	~MyGUIManager();

	bool _initialise(Ogre::RenderWindow* window);

	virtual void injectMouseMove(int _absx, int _absy, int _absz);
	virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
	virtual void injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id);
	virtual void injectKeyPress(KeyCode _key, uint32_t _text);
	virtual void injectKeyRelease(KeyCode _key);

	virtual void injectMouseWheel(int _absz);

	Ogre::Camera* getCamera()
	{
		return mCamera;
	}
	Ogre::Viewport* getViewport()
	{
		return mViewPort;
	}
	virtual bool frameStarted(const FrameEvent& evt);
private:
	void createGuiPlatform();
private:
	MyGUI::Gui* mGUI = nullptr;

	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewPort;
	Ogre::SceneNode* mCameraNode;
	Ogre::SceneManager* mSceneManager;
	Ogre::RenderWindow* mRenderWindow;
	int32_t mOldAbsZ;

	String mResourceFileName;

	MyGUI::OgrePlatform* mPlatform = nullptr;
};