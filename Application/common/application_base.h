#pragma once
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "game_camera.h"
#include "OgreFrameListener.h"

class ApplicationWindow;
class RenderSystem;


class ApplicationBase: public Ogre::FrameListener
{
public:
	ApplicationBase();
	~ApplicationBase();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	void run();
	virtual EngineType getEngineType();
	virtual bool isUseMyGUI()
	{
		return true;
	}

	virtual bool isUseCEGUI()
	{
		return false;
	}
	virtual void addCustomDirectory() {}

	virtual void OnSize(uint32_t width, uint32_t height);
private:
	virtual bool frameStarted(const FrameEvent& evt);
	void ShowFrameFrequency();
protected:
	ApplicationWindow* mApplicationWindow = nullptr;
	RenderSystem* mRenderSystem;

	uint64_t mLastFPS = 0;

	SceneManager* mSceneManager = nullptr;
	GameCamera* mGameCamera = nullptr;
	Ogre::RenderWindow* mRenderWindow = nullptr;
	Ogre::Viewport* mViewport = nullptr;
	
};