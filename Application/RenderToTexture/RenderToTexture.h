#pragma once
#include "application_base.h"
#include "OGActor.h"
#include "SelfEquipWindow.h"
#include "PackageWindow.h"

class RenderToTexture : public ApplicationBase
{
public:
	RenderToTexture();
	~RenderToTexture();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
private:
	void createActor();
private:
	Orphigine::ActorPtr object;
	demo::SelfEquipWindow* mEquipWindow;
	demo::PackageWindow* mPackageWindow;
	AnimationState* mAnimationState = nullptr;

	SceneNode* mBoxNode = nullptr;
};