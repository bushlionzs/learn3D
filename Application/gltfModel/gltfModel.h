#pragma once
#include "application_base.h"
class gltfModel : public ApplicationBase
{
public:
	gltfModel();
	~gltfModel();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	virtual bool isUseMyGUI()
	{
		return false;
	}
	EngineType getEngineType();
};