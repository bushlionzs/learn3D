#include <OgreHeader.h>
#include <OgreRoot.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>
#include "presentPass.h"

PresentPass::PresentPass(
	Ogre::OgreTexture* source,
	Ogre::RenderWindow* renderWindow,
	bool useSRGB)
{
	mSourceTexture = source;
	mRenderWindow = renderWindow;
	mShaderName = "presentShade";
	mUseSRGB = useSRGB;
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
	samplerParams.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.compareMode = filament::backend::SamplerCompareMode::NONE;
	samplerParams.compareFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_NEVER;
	samplerParams.anisotropyLog2 = 0;
	samplerParams.useComparison = 0;
	samplerParams.maxLod = 0;
	samplerParams.padding2 = 0;
	auto repeatBillinearSampler = rs->createTextureSampler(samplerParams);

	ShaderInfo shaderInfo;
	shaderInfo.shaderName = mShaderName.c_str();
	auto presentHandle = rs->createShaderProgram(shaderInfo, nullptr);
	filament::backend::RasterState rasterState{};
	rasterState.depthWrite = false;
	rasterState.depthTest = false;
	rasterState.depthFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_ALWAYS;
	rasterState.colorWrite = true;
	rasterState.renderTargetCount = 1;
	Ogre::EngineConfig& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

	if (mUseSRGB)
	{
		rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8_SRGB;
	}
	else
	{
		rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	}
	
	mPipelineHandle = rs->createPipeline(rasterState, presentHandle);

	mZeroSet = rs->createDescriptorSet(presentHandle, 0);
	Ogre::DescriptorData descriptorData[2];


	descriptorData[0].mCount = 1;
	descriptorData[0].pName = "SourceTexture";
	descriptorData[0].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE;
	descriptorData[0].ppTextures = (const Ogre::OgreTexture**)&mSourceTexture;

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
		Ogre::TextureBarrier texBarriers[] =
		{
			{
				mRenderWindow->getColorTarget()->getTarget(),
				Ogre::RESOURCE_STATE_PRESENT,
				Ogre::RESOURCE_STATE_RENDER_TARGET
			}
		};
		rs->resourceBarrier(0, nullptr, 1, texBarriers, 0, nullptr, nullptr);
	}
	RenderPassInfo info;
	info.renderTargetCount = 1;
	info.renderTargets[0].target.renderTarget = mRenderWindow->getColorTarget();
	info.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
	info.depthTarget.target.depthStencil = nullptr;
	info.depthTarget.clearValue = { 0.0f, 0.0f };
	auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
	rs->pushGroupMarker("presentPass");
	rs->beginRenderPass(info);
	rs->bindPipeline(mPipelineHandle);
	rs->bindDescriptorSets(mPipelineHandle, &mZeroSet, 1);
	rs->draw(3, 1, 0, 0);
	rs->endRenderPass(info);
	rs->popGroupMarker();

	{
		Ogre::TextureBarrier texBarriers[] =
		{
			{
				mRenderWindow->getColorTarget()->getTarget(),
				Ogre::RESOURCE_STATE_RENDER_TARGET,
				Ogre::RESOURCE_STATE_PRESENT
			}
		};
		rs->resourceBarrier(0, nullptr, 1, texBarriers, 0, nullptr, nullptr);
	}
}

void PresentPass::update(float delta)
{

}