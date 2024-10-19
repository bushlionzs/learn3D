#include "OgreHeader.h"
#include "OgreRoot.h"
#include "pass.h"
#include "engine_struct.h"
#include "renderSystem.h"
#include "OgreSceneManager.h"
#include "OgreRenderable.h"
#include "OgreMaterial.h"
#include "OgreRenderTarget.h"
#include "OgreTextureManager.h"

class UserDefineRenderPass : public PassBase
{
public:
	UserDefineRenderPass(
		RenderPassCallback renderCallback,
		UpdatePassCallback updateCallback)
	{
		mRenderCallback = renderCallback;
		mUpdateCallback = updateCallback;
	}

	void execute(RenderSystem* rs)
	{
		mRenderCallback(mRenderPassInfo);
	}

	void update(float delta)
	{
		mUpdateCallback(delta);
	}
private:
	RenderPassInfo mRenderPassInfo;
	RenderPassCallback mRenderCallback;
	UpdatePassCallback mUpdateCallback;
};
PassBase* createUserDefineRenderPass(
	RenderPassCallback renderCallback,
	UpdatePassCallback updateCallback)
{
	return new UserDefineRenderPass(renderCallback, updateCallback);
}

class ComputePass : public PassBase
{
public:
	ComputePass(ComputePassCallback userCallback)
	{
		mCallback = userCallback;
	}

	void execute(RenderSystem* rs)
	{
		mCallback(mComputePassInfo);
		
	}
private:
	ComputePassInfo mComputePassInfo;
	ComputePassCallback mCallback;
};

PassBase* createComputePass(ComputePassCallback userCallback)
{
	return new ComputePass(userCallback);
}