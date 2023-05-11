#pragma once
#include "application_base.h"

class World;

class WowMap : public ApplicationBase
{
public:
	WowMap();
	~WowMap();
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

	World* mWorld = nullptr;
};