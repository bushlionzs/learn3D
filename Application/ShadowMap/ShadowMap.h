#pragma once
#include "filament/Engine.h"
#include <fg/FrameGraphTexture.h>
#include "ApplicationBase.h"
class GameCamera;
class RenderSystem;
class Ogre::RenderWindow;
class Ogre::SceneManager;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	void setup(
		RenderSystem* renderSystem,
		Ogre::RenderWindow* renderWindow,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
	void updatePass(std::vector<PassBase*>& passlist);
	FrameGraphId<FrameGraphTexture> fgPass(FrameGraph& fg);
private:
	void base1();
	void base2();
private:
	AnimationState* mAnimationState = nullptr;

	SceneNode* mLightNode = nullptr;

	Ogre::Light* light = nullptr;

	Ogre::SceneManager* mSceneManager;
	GameCamera* mGameCamera;
	RenderSystem* mRenderSystem;
	RenderWindow* mRenderWindow;

	PassBase* mMainPass;
	PassBase* mShadowPass;
	PassBase* clearBufferPass;
};