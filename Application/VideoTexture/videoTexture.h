#pragma once
#include "application_base.h"
class VideoTexture : public ApplicationBase
{
public:
	VideoTexture();
	~VideoTexture();
	virtual bool appInit();
	virtual void appUpdate(float delta);
	EngineType getEngineType();
	virtual bool isUseMyGUI()
	{
		return false;
	}
};