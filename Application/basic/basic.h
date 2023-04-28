#pragma once
#include "application_base.h"
class Basic : public ApplicationBase
{
public:
	Basic();
	~Basic();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual bool isUseMyGUI()
	{
		return false;
	}
	EngineType getEngineType();
};