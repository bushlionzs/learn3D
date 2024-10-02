#pragma once
#include "application_base.h"
class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	void setup(
		RenderSystem* rs,
		Ogre::SceneManager* sceneManager,
		GameCamera* gameCamera);
	void update(float delta);
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
};