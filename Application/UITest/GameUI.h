#pragma once
#include "application_base.h"
#include "OgreAnimationState.h"

class Role;
class GameUI : public ApplicationBase
{
public:
	GameUI();
	~GameUI();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
private:
	AnimationState* mAnimationState = nullptr;
	Role* mRole;
};