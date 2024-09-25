#pragma once
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "game_camera.h"
#include "OgreFrameListener.h"

class ApplicationWindow;
class RenderSystem;
class Ogre::RenderTarget;
class Ogre::Camera;

class ApplicationBase: public Ogre::FrameListener
{
public:
	struct BasicPass
	{
		Ogre::RenderTarget* color = nullptr;
		Ogre::RenderTarget* depth = nullptr;
		SceneManager* sceneMgr = nullptr;
		Ogre::ICamera* cam = nullptr;
		Ogre::OgreTexture* shadowMap = nullptr;
		bool shadowPass = false;
	};
	ApplicationBase();
	~ApplicationBase();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	void run();
	void render();
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

protected:
	void addMainPass(Ogre::OgreTexture* shadowMap);
private:
	virtual bool frameStarted(const FrameEvent& evt);
	void ShowFrameFrequency();
protected:
	ApplicationWindow* mApplicationWindow = nullptr;
	RenderSystem* mRenderSystem;

	uint64_t mLastFPS = 0;

	SceneManager* mSceneManager = nullptr;
	Ogre::Camera* mCamera = nullptr;
	GameCamera* mGameCamera = nullptr;
	Ogre::RenderWindow* mRenderWindow = nullptr;
	Ogre::Viewport* mViewport = nullptr;
	std::vector<BasicPass> mPassList;
	RenderPassInfo mPassInfo;
};