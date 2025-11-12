#pragma once

#include "ApplicationBase.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "game_camera.h"
#include "OgreFrameListener.h"
#include "pass.h"

class ApplicationWindow;
class RenderSystem;
class Ogre::RenderTarget;
class Ogre::Camera;



class ManualApplication: public Ogre::FrameListener, public RenderPipeline
{
public:
	ManualApplication();
	~ManualApplication();

	void run(AppInfo* info);
	
	virtual bool isUseCEGUI()
	{
		return mUseCEGUI;
	}

	filament::backend::Handle<filament::backend::HwCommandBuffer> getCurrentCommandBuffer();
	void addCustomDirectory() {}
	virtual void OnSize(uint32_t width, uint32_t height);

	void addRenderPass(PassBase* pass);
	void addUIPass();
	Ogre::RenderWindow* wndInit(int64_t appWnd);
private:
	void appInit();
	
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	void ShowFrameFrequency();
	void loop();
protected:
	ApplicationWindow* mApplicationWindow = nullptr;
	RenderSystem* mRenderSystem;

	uint64_t mLastFPS = 0;

	Ogre::SceneManager* mSceneManager = nullptr;
	Ogre::Camera* mCamera = nullptr;
	GameCamera* mGameCamera = nullptr;
	Ogre::RenderWindow* mRenderWindow = nullptr;
	filament::backend::Handle<filament::backend::HwSwapChain> mSwapChainHandle;
	std::vector<PassBase*> mPassList;
	RenderPassInfo mPassInfo;
	AppInfo* mAppInfo;
	bool mUseCEGUI;

	Ogre::Timer mTimer;
	uint64_t mFrameCurrent, mFrameLast;

	uint32_t mWidth;
	uint32_t mHeight;

	bool mNeedResize = true;

	std::vector<FrameContext> frameContextList;
	uint32_t mImageIndex = 0;

	RenderContext context;
};