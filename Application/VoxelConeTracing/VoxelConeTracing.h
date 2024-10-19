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
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
	void updatePass(std::vector<PassBase*>& passlist);
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
	std::vector<PassBase*> mPassList;
	FrameConstantBuffer mFrameConstantBuffer;
	std::vector<Handle<HwBufferObject>> mFrameBufferObjectList;
};