#pragma once
#include "OgreSingleton.h"
#include "OgreMoveObject.h"
#include "InputManager.h"
#include "OgreFrameListener.h"

namespace CEGUI
{
	class GUIContext;
}

class CEGUIManager : public Ogre::Singleton<CEGUIManager>,
	public FrameListener,
	public InputListener,
	public Ogre::MoveObject
{
public:
	CEGUIManager();
	~CEGUIManager();

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

	Ogre::RenderWindow* getRenderWindows()
	{
		return mRenderWindow;
	}

	CEGUI::GUIContext* getGUIContext()
	{
		return mGUIContext;
	}

	void addRenderable(Ogre::Renderable* r);

	virtual const std::vector<Renderable*>& getRenderableList();

	virtual const AxisAlignedBox& getBoundingBox(void) const;
private:

	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewPort;
	Ogre::SceneNode* mCameraNode;
	Ogre::SceneManager* mSceneManager;
	Ogre::RenderWindow* mRenderWindow;
	int32_t mOldAbsZ;

	Ogre::String mResourceFileName;

	CEGUI::GUIContext* mGUIContext = nullptr;

};