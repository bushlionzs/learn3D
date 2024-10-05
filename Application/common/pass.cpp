#include "OgreHeader.h"
#include "pass.h"
#include "engine_struct.h"
#include "renderSystem.h"
#include "OgreSceneManager.h"

class RenderPass : public PassBase
{
public:
	RenderPass(RenderPassInput& input)
	{
		mInput = input;
	}

	void execute(RenderSystem* rs)
	{
		mRenderPassInfo.renderTargets[0].renderTarget = mInput.color;
		mRenderPassInfo.depthTarget.depthStencil = mInput.depth;
		mRenderPassInfo.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
		mRenderPassInfo.depthTarget.clearValue = { 1.0f, 0.0f };
		mRenderPassInfo.cam = mInput.cam;
		mRenderPassInfo.shadowPass = mInput.shadowPass;
		mRenderPassInfo.shadowMap = mInput.shadowMap;
		rs->beginRenderPass(mRenderPassInfo);
		static EngineRenderList engineRenerList;
		mInput.sceneMgr->getSceneRenderList(mInput.cam, engineRenerList, mInput.shadowPass);
		rs->multiRender(engineRenerList.mOpaqueList);
		rs->endRenderPass();
	}
private:
	RenderPassInput mInput;
	RenderPassInfo mRenderPassInfo;
};

PassBase* createRenderPass(RenderPassInput& input)
{
	return new RenderPass(input);
}

class ComputePass : public PassBase
{
public:
	ComputePass(ComputePassInput& input)
	{
		mComputePassInfo.shaderName = input.shaderName;
		mComputePassInfo.pipelineLayout = input.pipelineLayout;
		mComputePassInfo.ds = input.ds;
		mComputePassInfo.computeGroup = input.computeGroup;
	}

	void execute(RenderSystem* rs)
	{
		rs->beginComputePass(mComputePassInfo);
		rs->endComputePass();
	}
private:

	ComputePassInfo mComputePassInfo;
};

PassBase* createComputePass(ComputePassInput& input)
{
	return new ComputePass(input);
}