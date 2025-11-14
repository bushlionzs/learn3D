#pragma once
#include <engine_struct.h>
#include "pass.h"
#include "game_camera.h"
#include "DriverBase.h"
class VideoTextureApplication
{
public:
	VideoTextureApplication();
	~VideoTextureApplication();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	
	void setup(
		RenderPipeline* renderPipeline,
		RenderContext& context,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
private:
	Ogre::SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	Ogre::RenderWindow* mRenderWindow;
	RenderPipeline* mRenderPipeline;
};