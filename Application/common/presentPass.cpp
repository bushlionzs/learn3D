#include <OgreHeader.h>
#include <OgreRoot.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>
#include "presentPass.h"

PresentPass::PresentPass(
	Ogre::RenderTarget* sourceTarget, 
	RenderWindow* renderWindow,
	const char* shaderName)
{
	mSourceTarget = sourceTarget;
	mRenderWindow = renderWindow;
	if (shaderName)
	{
		mShaderName = shaderName;
	}
	else
	{
		mShaderName = "presentShade";
	}
}

PresentPass::~PresentPass()
{

}

bool PresentPass::initialize()
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
	samplerParams.padding0 = 0;
	samplerParams.padding1 = 0;
	samplerParams.padding2 = 0;
	auto repeatBillinearSampler = rs->createTextureSampler(samplerParams);

	ShaderInfo shaderInfo;
	shaderInfo.shaderName = mShaderName.c_str();
	auto presentHandle = rs->createShaderProgram(shaderInfo, nullptr);
	backend::RasterState rasterState{};
	rasterState.depthWrite = false;
	rasterState.depthTest = false;
	rasterState.depthFunc = SamplerCompareFunc::A;
	rasterState.colorWrite = true;
	rasterState.renderTargetCount = 1;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	mPipelineHandle = rs->createPipeline(rasterState, presentHandle);

	mZeroSet = rs->createDescriptorSet(presentHandle, 0);
	DescriptorData descriptorData[2];

	auto* currentTaget = mSourceTarget;
	OgreTexture* sourceTex = currentTaget->getTarget();
	descriptorData[0].mCount = 1;
	descriptorData[0].pName = "SourceTexture";
	descriptorData[0].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
	descriptorData[0].ppTextures = (const OgreTexture**)&sourceTex;

	descriptorData[1].mCount = 1;
	descriptorData[1].pName = "repeatBillinearSampler";
	descriptorData[1].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
	descriptorData[1].ppSamplers = &repeatBillinearSampler;
	rs->updateDescriptorSet(mZeroSet, 2, descriptorData);
    return true;
}

void PresentPass::execute(RenderSystem* rs)
{
	{
		RenderTargetBarrier rtBarriers[] =
		{
			{
				mRenderWindow->getColorTarget(),
				RESOURCE_STATE_PRESENT,
				RESOURCE_STATE_RENDER_TARGET
			},
			{
				mSourceTarget,
				RESOURCE_STATE_UNORDERED_ACCESS,
				RESOURCE_STATE_PIXEL_SHADER_RESOURCE
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 2, rtBarriers);
	}
	RenderPassInfo info;
	info.renderTargetCount = 1;
	info.renderTargets[0].renderTarget = mRenderWindow->getColorTarget();
	info.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
	info.depthTarget.depthStencil = nullptr;
	info.depthTarget.clearValue = { 0.0f, 0.0f };
	auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
	rs->pushGroupMarker("presentPass");
	rs->beginRenderPass(info);
	rs->bindPipeline(mPipelineHandle, &mZeroSet, 1);
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
			},
			{
				mSourceTarget,
				RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				RESOURCE_STATE_UNORDERED_ACCESS
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 2, rtBarriers);
	}
}

void PresentPass::update(float delta)
{

}