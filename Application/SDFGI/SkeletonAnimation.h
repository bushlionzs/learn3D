#pragma once
#include "application_base.h"
class SkeletonAnimation : public ApplicationBase
{
public:
	SkeletonAnimation();
	~SkeletonAnimation();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
	virtual bool isUseMyGUI()
	{
		return false;
	}
private:
	AnimationState* mAnimationState = nullptr;
};