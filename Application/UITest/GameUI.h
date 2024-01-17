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
	virtual bool isUseMyGUI()
	{
		return false;
	}

	virtual bool isUseCEGUI()
	{
		return true;
	}
private:
	AnimationState* mAnimationState = nullptr;
	Role* mRole;
};