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
};