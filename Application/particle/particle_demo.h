#pragma once
#include "application_base.h"
class ParticleDemo : public ApplicationBase
{
public:
	ParticleDemo();
	~ParticleDemo();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual bool isUseMyGUI()
	{
		return false;
	}
	EngineType getEngineType();

	void addCustomDirectory();
private:
	AnimationState* mAnimationState = nullptr;
};