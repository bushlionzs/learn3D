#pragma once
#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"
#include "OgreCamera.h"
#include "ddgiTypes.h"
#include "GIContext.h"


class SDFGIApp
{
public:
	SDFGIApp();
	~SDFGIApp();

	void setup(
		RenderPipeline* renderPipeline,
		RenderContext& context,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
private:
	void initScene(RenderContext& context);
	void initResource(RenderContext& context);
	void addPass(RenderContext& context);
private:
	SceneManager* mSceneManager = nullptr;
	GameCamera* mGameCamera = nullptr;
	RenderSystem* mRenderSystem = nullptr;
	RenderWindow* mRenderWindow = nullptr;
	RenderPipeline* mRenderPipeline;
	FrameConstantBuffer mFrameConstantBuffer;
	
	Ogre::Vector3 mLightPos;
	Ogre::Vector3 mLightTarget;

	Ogre::Matrix4 mLightView;
	Ogre::Matrix4 mLightProject;


	SDFGIContext mContext;

	
};