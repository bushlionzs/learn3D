#pragma once
#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"

class VoxelConeTracingApp
{
public:
	VoxelConeTracingApp();
	~VoxelConeTracingApp();

	void setup(
		RenderPipeline* renderPipeline,
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
	void updateFrameData(ICamera* camera, ICamera* light);

	Handle<HwBufferObject> getFrameHandle(uint32_t frameIndex)
	{
		return mFrameBufferObjectList[frameIndex];
	}
private:

	EngineType getEngineType();
	
private:
	SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	RenderWindow* mRenderWindow;
	FrameConstantBuffer mFrameConstantBuffer;
	std::vector<Handle<HwBufferObject>> mFrameBufferObjectList;
};