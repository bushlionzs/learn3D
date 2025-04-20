#pragma once

#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"
#include "ApplicationBase.h"
#include "ManualApplication.h"
class BasicApplication
{
public:
	struct FrameData
	{
		filament::backend::Handle<filament::backend::HwDescriptorSet> zeroSet;
		filament::backend::Handle<filament::backend::HwBufferObject> passUniformBuffer;
	};
	BasicApplication(ManualApplication* app);
	~BasicApplication();

	void setup(
		RenderPipeline* renderPipeline,
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);

	void addCustomDirectory();
	void updateFrameData(Ogre::ICamera* camera, FrameConstantBuffer& frameBuffer);

	void userInit(AppInfo* appInfo);
	void godotWndCallback(AppInfo* appInfo, int64_t wnd);
private:
	void base1();
	void base2();
	void ibl_init();
private:
	Ogre::AnimationState* mAnimationState = nullptr;
	std::vector<FrameData> mFrameData;
	Ogre::SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	Ogre::RenderWindow* mRenderWindow;
	RenderPipeline* mRenderPipeline;
	Ogre::RenderTarget* brdfTarget;
	Ogre::RenderTarget* prefilteredTarget;
	Ogre::RenderTarget* irradianceTarget;
	ManualApplication* mApplication;
};