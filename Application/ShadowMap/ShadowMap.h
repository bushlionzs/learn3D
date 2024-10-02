#pragma once
#include "application_base.h"
class ShadowMap : public ApplicationBase
{
public:
	ShadowMap();
	~ShadowMap();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
private:
	void base1();
	void base2();
private:
	AnimationState* mAnimationState = nullptr;

	SceneNode* mLightNode = nullptr;

	Ogre::Light* light = nullptr;
};