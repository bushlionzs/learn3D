#pragma once
#include "application_base.h"

class GameWorld;
class NetContext;
class FullDemo : public ApplicationBase
{
public:
	FullDemo();
	~FullDemo();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual EngineType getEngineType();
private:
	void registerMessage();
private:
	GameWorld* mGameWorld;
	NetContext* mNetContext;
};