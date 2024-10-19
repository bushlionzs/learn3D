#pragma once
#include "application_base.h"

class RenderToTexture : public ApplicationBase
{
public:
	RenderToTexture();
	~RenderToTexture();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
	virtual bool isUseMyGUI()
	{
		return false;
	}
private:
	void createActor();
private:
	AnimationState* mAnimationState = nullptr;

	SceneNode* mBoxNode = nullptr;
};