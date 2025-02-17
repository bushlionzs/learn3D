#include <OgreHeader.h>
#include <OgreRoot.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>
#include "presentPass.h"

PresentPass::PresentPass(
	Ogre::RenderTarget* sourceTarget, 
	Ogre::RenderWindow* renderWindow,
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

	filament::backend::SamplerParams samplerParams;
	samplerParams.filterMag = filament::backend::SamplerFilterType::LINEAR;
	samplerParams.filterMin = filament::backend::SamplerFilterType::LINEAR;
	samplerParams.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	samplerParams.wrapS = filament::backend::SamplerWrapMode::REPEAT;
	samplerParams.wrapT = filament::backend::SamplerWrapMode::REPEAT;
	samplerParams.wrapR = filament::backend::SamplerWrapMode::REPEAT;
	samplerParams.compareMode = filament::backend::SamplerCompareMode::NONE;
	samplerParams.compareFunc = filament::backend::SamplerCompareFunc::N;
	samplerParams.anisotropyLog2 = 0;
	samplerParams.padding0 = 0;
	samplerParams.padding1 = 0;
	samplerParams.padding2 = 0;
	auto repeatBillinearSampler = rs->createTextureSampler(samplerParams);

	ShaderInfo shaderInfo;
	shaderInfo.shaderName = mShaderName.c_str();
	auto presentHandle = rs->createShaderProgram(shaderInfo, nullptr);
	filament::backend::RasterState rasterState{};
	rasterState.depthWrite = false;
	rasterState.depthTest = false;
	rasterState.depthFunc = filament::backend::SamplerCompareFunc::A;
	rasterState.colorWrite = true;
	rasterState.renderTargetCount = 1;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	mPipelineHandle = rs->createPipeline(rasterState, presentHandle);

	mZeroSet = rs->createDescriptorSet(presentHandle, 0);
	Ogre::DescriptorData descriptorData[2];

	auto* currentTaget = mSourceTarget;
	Ogre::OgreTexture* sourceTex = currentTaget->getTarget();
	descriptorData[0].mCount = 1;
	descriptorData[0].pName = "SourceTexture";
	descriptorData[0].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE;
	descriptorData[0].ppTextures = (const Ogre::OgreTexture**)&sourceTex;

	descriptorData[1].mCount = 1;
	descriptorData[1].pName = "repeatBillinearSampler";
	descriptorData[1].descriptorType = Ogre::DESCRIPTOR_TYPE_SAMPLER;
	descriptorData[1].ppSamplers = &repeatBillinearSampler;
	rs->updateDescriptorSet(mZeroSet, 2, descriptorData);
    return true;
}

void PresentPass::execute(RenderSystem* rs)
{
	{
		Ogre::RenderTargetBarrier rtBarriers[] =
		{
			{
				mRenderWindow->getColorTarget(),
				Ogre::RESOURCE_STATE_PRESENT,
				Ogre::RESOURCE_STATE_RENDER_TARGET
			},
			{
				mSourceTarget,
				Ogre::RESOURCE_STATE_UNORDERED_ACCESS,
				Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE
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
		Ogre::RenderTargetBarrier rtBarriers[] =
		{
			{
				mRenderWindow->getColorTarget(),
				Ogre::RESOURCE_STATE_RENDER_TARGET,
				Ogre::RESOURCE_STATE_PRESENT
			},
			{
				mSourceTarget,
				Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				Ogre::RESOURCE_STATE_UNORDERED_ACCESS
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 2, rtBarriers);
	}
}

void PresentPass::update(float delta)
{

}