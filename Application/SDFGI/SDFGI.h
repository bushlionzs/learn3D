#pragma once
#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"
#include "OgreCamera.h"
#include "ddgiTypes.h"
#include "SDFGIContext.h"


class SDFGIApp
{
public:
	SDFGIApp();
	~SDFGIApp();

	void setup(
		RenderPipeline* renderPipeline,
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
private:
	void initScene();
	void initResource();
	void addPass();
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