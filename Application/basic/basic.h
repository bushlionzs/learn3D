#pragma once
#include "application_base.h"
#include "OGImpact.h"

class Basic : public ApplicationBase
{
public:
	
	Basic();
	~Basic();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual bool isUseMyGUI()
	{
		return true;
	}
	EngineType getEngineType();

	void addCustomDirectory();
private:
	void base1();
	void base2();
	void base3();
	void base4();
	void base5();
private:
	AnimationState* mAnimationState = nullptr;
};