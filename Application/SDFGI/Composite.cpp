#include <OgreHeader.h>
#include <OgreRoot.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>
#include "Composite.h"
#include "SDFGI.h"

CompositePass::CompositePass(
	RenderWindow* renderWindow, 
	SDFGIContext& context):
	mContext(context)
{
	mRenderWindow = renderWindow;
}

CompositePass::~CompositePass()
{

}

bool CompositePass::initialize()
{
	RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();

	backend::SamplerParams samplerParams;
	samplerParams.filterMag = backend::SamplerFilterType::LINEAR;
	samplerParams.filterMin = backend::SamplerFilterType::LINEAR;
	samplerParams.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	samplerParams.wrapS = backend::SamplerWrapMode::REPEAT;
	samplerParams.wrapT = backend::SamplerWrapMode::REPEAT;
	samplerParams.wrapR = backend::SamplerWrapMode::REPEAT;
	samplerParams.compareMode = backend::SamplerCompareMode::NONE;
	samplerParams.compareFunc = backend::SamplerCompareFunc::N;
	samplerParams.anisotropyLog2 = 0;
	samplerParams.useComparison = 0;
	samplerParams.maxLod = 0;
	samplerParams.padding2 = 0;
	auto repeatBillinearSampler = rs->createTextureSampler(samplerParams);

	ShaderInfo shaderInfo;
	shaderInfo.shaderName = "CompositePass";
	addMacro(shaderInfo, "HLSL", "1");
	addMacro(shaderInfo, "RTXGI_BINDLESS_TYPE", std::to_string(RTXGI_BINDLESS_TYPE_RESOURCE_ARRAYS));
	auto presentHandle = rs->createShaderProgram(shaderInfo, nullptr);
	backend::RasterState rasterState{};
	rasterState.depthWrite = false;
	rasterState.depthTest = false;
	rasterState.depthFunc = SamplerCompareFunc::A;
	rasterState.colorWrite = true;
	rasterState.renderTargetCount = 1;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	mPipelineHandle = rs->createPipeline(rasterState, presentHandle);

	mCompositeZeroSets.resize(mContext.frameCount);

	for (uint32_t i = 0; i < mContext.frameCount; i++)
	{
		mCompositeZeroSets[i] = rs->createDescriptorSet(presentHandle, 0);
	}
	

	DescriptorData descriptorData[2];

	std::array<OgreTexture*, 7> rwTex2D =
	{
		mContext.mGBufferTargetA->getTarget(),
		mContext.mGBufferTargetB->getTarget(),
		mContext.mGBufferTargetC->getTarget(),
		mContext.mGBufferTargetD->getTarget(),
		mContext.mIndirectTarget->getTarget(),
		nullptr,
		nullptr
	};

	descriptorData[0].mCount = rwTex2D.size();
	descriptorData[0].pName = "RWTex2D";
	descriptorData[0].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
	descriptorData[0].ppTextures = (const OgreTexture**)rwTex2D.data();

	for (uint32_t i = 0; i < mContext.frameCount; i++)
	{
		BufferView globalConstBufferView;
		globalConstBufferView.buffer = mContext.mGlobalConstHandle;
		globalConstBufferView.offset = GlobalConstants::GetAlignedSizeInBytes()* i;
		descriptorData[1].mCount = 1;
		descriptorData[1].pName = "GlobalConst";
		descriptorData[1].descriptorType = DESCRIPTOR_TYPE_BUFFER_VIEW;
		descriptorData[1].pBufferView = &globalConstBufferView;

		rs->updateDescriptorSet(mCompositeZeroSets[i], 2, descriptorData);
	}
	
	return true;
}

void CompositePass::execute(RenderSystem* rs)
{
	{
		RenderTargetBarrier rtBarriers[] =
		{
			{
				mRenderWindow->getColorTarget(),
				RESOURCE_STATE_PRESENT,
				RESOURCE_STATE_RENDER_TARGET
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
	}
	RenderPassInfo info;
	info.renderTargetCount = 1;
	info.renderTargets[0].renderTarget = mRenderWindow->getColorTarget();
	info.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
	info.depthTarget.depthStencil = nullptr;
	info.depthTarget.clearValue = { 0.0f, 0.0f };
	auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
	rs->pushGroupMarker("compositePass");
	rs->beginRenderPass(info);
	rs->bindPipeline(mPipelineHandle, &mCompositeZeroSets[frameIndex], 1);
	rs->draw(3, 0);
	rs->endRenderPass(info);
	rs->popGroupMarker();

	{
		RenderTargetBarrier rtBarriers[] =
		{
			{
				mRenderWindow->getColorTarget(),
				RESOURCE_STATE_RENDER_TARGET,
				RESOURCE_STATE_PRESENT
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
	}
}

void CompositePass::update(float delta)
{

}