#pragma once

#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"


class BasicApplication
{
public:
	struct FrameData
	{
		filament::backend::Handle<filament::backend::HwDescriptorSet> zeroSet;
		filament::backend::Handle<filament::backend::HwBufferObject> passUniformBuffer;
	};
	BasicApplication();
	~BasicApplication();

	void setup(
		RenderPipeline* renderPipeline,
		RenderContext& context,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);

	void addCustomDirectory();
	void updateFrameData(Ogre::ICamera* camera, FrameConstantBuffer& frameBuffer);
private:
	void cryEngineInit();
private:
	Ogre::AnimationState* mAnimationState = nullptr;
	std::vector<FrameData> mFrameData;
	Ogre::SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	Ogre::RenderWindow* mRenderWindow;
	RenderPipeline* mRenderPipeline; 
	Ogre::SceneNode* mRoot;
};