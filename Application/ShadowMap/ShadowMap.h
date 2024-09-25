#pragma once
#include "application_base.h"
class ShadowMap : public ApplicationBase
{
public:
	ShadowMap();
	~ShadowMap();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual bool isUseMyGUI()
	{
		return false;
	}
	EngineType getEngineType();
private:
	AnimationState* mAnimationState = nullptr;

	SceneNode* mLightNode;

	Ogre::Light* light;
};