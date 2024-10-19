#pragma once
#include "application_base.h"
class AnimTexture : public ApplicationBase
{
public:
	AnimTexture();
	~AnimTexture();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual EngineType getEngineType();
	virtual bool isUseMyGUI();
};