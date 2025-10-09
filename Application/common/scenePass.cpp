#include <OgreHeader.h>
#include "scenePass.h"
#include "OgreRenderTarget.h"
#include "OgreSceneManager.h"
#include "OgreTextureManager.h"
#include "OgreMaterial.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreResourceManager.h"
#include "OgreTexture.h"
#include "OgreTextureUnit.h"

SceneRenderPass::SceneRenderPass(RenderPassInput& input)
{
	rs = Ogre::Root::getSingleton().getRenderSystem();

	mPassInput = input;
	mRenderPassInfo.flipY = input.flipY;
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

	mFrameData.resize(ogreConfig.swapBufferCount);


	for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
	{
		SceneFrameData& frameData = mFrameData.at(i);
		frameData.shadowBufferList.resize(SHADOW_MAP_CASCADE_COUNT);
		Ogre::BufferDesc desc{};
		desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
		desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
		desc.bufferCreationFlags = 0;
		desc.mSize = sizeof(mFrameConstantBuffer);
		frameData.passBufferHandle = rs->createBufferObject(desc);

		desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
		desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
		desc.bufferCreationFlags = 0;
		desc.mSize = sizeof(cascadeInfo);
		frameData.cascadeBufferHandle = rs->createBufferObject(desc);

		for (auto j = 0; j < SHADOW_MAP_CASCADE_COUNT; j++)
		{
			Ogre::BufferDesc desc{};
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(mFrameConstantBuffer);
			frameData.shadowBufferList[j] = rs->createBufferObject(desc);
		}
	}

	auto width = ogreConfig.width;
	auto height = ogreConfig.height;
	mFrameConstantBuffer.RenderTargetSize =
		Ogre::Vector2((float)width,
			(float)height);
	mFrameConstantBuffer.InvRenderTargetSize =
		Ogre::Vector2(1.0f / width, 1.0f / height);
	mFrameConstantBuffer.NearZ = 0.1f;
	mFrameConstantBuffer.FarZ = 10000.0f;

	RenderPassInput* passInput = &mPassInput;
	filament::backend::SamplerParams params{};
	params.filterMag = filament::backend::SamplerFilterType::LINEAR;
	params.filterMin = filament::backend::SamplerFilterType::LINEAR;
	params.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	params.wrapS = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
	params.wrapT = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
	params.wrapR = filament::backend::SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
	params.compareMode = filament::backend::SamplerCompareMode::COMPARE_TO_TEXTURE;
	params.compareFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_LESS_OR_EQUAL;
	params.anisotropyLog2 = 0;
	params.useComparison = 0;
	params.maxLod = 1;
	params.padding2 = 0;
	filament::backend::Handle<filament::backend::HwSampler> shadowMapSampler = rs->createTextureSampler(params);
	RenderableBindCallback bindCallback = [=](RenderContext& context, uint32_t frameIndex, Ogre::Renderable* r, void*) {
		Ogre::DescriptorData descriptorData[2];

		descriptorData[0].mCount = 1;
		descriptorData[0].pName = "cbPass";
		descriptorData[0].ppBuffers = &mFrameData[frameIndex].passBufferHandle;


		FrameResourceInfo* resourceInfo = (FrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
		rs->updateDescriptorSet(resourceInfo->zeroSet, 1, descriptorData);
		if (passInput->shadowMapTarget)
		{
			descriptorData[0].mCount = 1;
			descriptorData[0].pName = "cascadeInfo";
			descriptorData[0].ppBuffers = &mFrameData[frameIndex].cascadeBufferHandle;
			rs->updateDescriptorSet(resourceInfo->zeroSet, 1, descriptorData);
			Ogre::OgreTexture* shadowTexture = passInput->shadowMapTarget->getTarget();
			descriptorData[0].mCount = 1;
			descriptorData[0].pName = "shadowMap";
			descriptorData[0].ppTextures = (const Ogre::OgreTexture**)&shadowTexture;

			descriptorData[1].mCount = 1;
			descriptorData[1].pName = "shadowMapSampler";
			descriptorData[1].ppSamplers = &shadowMapSampler;
			descriptorData[1].descriptorType = Ogre::DESCRIPTOR_TYPE_SAMPLER;


			rs->updateDescriptorSet(resourceInfo->firstSet, 2, descriptorData);
		}

		};

	RenderableDrawCallback drawCallback = [=](RenderContext& context, uint32_t frameIndex, Ogre::Renderable* r, void* param) {
		void* frameData = r->getFrameResourceInfo(frameIndex);
		FrameResourceInfo* resourceInfo = (FrameResourceInfo*)frameData;
		Ogre::Material* mat = r->getMaterial().get();

		auto programHandle = mat->getProgram();
		auto piplineHandle = mat->getPipeline();
		filament::backend::Handle<filament::backend::HwDescriptorSet> descriptorSet[2];

		if (resourceInfo->firstSet)
		{
			descriptorSet[0] = resourceInfo->zeroSet;
			descriptorSet[1] = resourceInfo->firstSet;
			rs->bindPipeline(piplineHandle);
			rs->bindDescriptorSets(piplineHandle, descriptorSet, 2);
		}
		else
		{
			rs->bindPipeline(piplineHandle);
			rs->bindDescriptorSets(piplineHandle, &resourceInfo->zeroSet, 1);
		}



		VertexData* vertexData = r->getVertexData();
		IndexData* indexData = r->getIndexData();
		vertexData->bind(nullptr);
		if (indexData)
		{
			indexData->bind();
			IndexDataView* view = r->getIndexView();
			rs->drawIndexed(view->mIndexCount, 1,
				view->mIndexLocation, view->mBaseVertexLocation, 0);
		}
		else
		{
			assert_invariant(false);
		}
		};

	mRenderPassInfo.passName = "generalPass";


	ShaderInfo shaderInfo;
	shaderInfo.shaderName = "shadow";
	VertexDeclaration decl;
	decl.addElement(0, 0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	decl.addElement(0, 0, 12, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
	decl.addElement(0, 0, 24, Ogre::VET_FLOAT4, Ogre::VES_TANGENT);
	decl.addElement(0, 0, 40, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
	shadowProgramHandle = rs->createShaderProgram(shaderInfo, &decl);

	filament::backend::RasterState rasterState;
	rasterState.depthWrite = true;
	rasterState.depthTest = true;
	rasterState.depthFunc = filament::backend::SamplerCompareFunc::COMPARE_OP_LESS_OR_EQUAL;
	rasterState.colorWrite = true;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_UNKNOWN;
	rasterState.renderTargetCount = 0;
	rasterState.depthBiasConstantFactor = 1.25f;
	rasterState.depthBiasSlopeFactor = 1.75f;

	filament::backend::Handle<filament::backend::HwPipeline> shadowPipelineHandle = rs->createPipeline(rasterState, shadowProgramHandle);

	RenderableBindCallback shadowBindCallback = [=](RenderContext& context, uint32_t frameIndex, Ogre::Renderable* r, void* param) {
		uint64_t index = (uint64_t)param;
		Ogre::DescriptorData descriptorData[3];
		descriptorData[0].mCount = 1;
		descriptorData[0].pName = "cbPass";
		descriptorData[0].ppBuffers = &mFrameData[frameIndex].shadowBufferList[index];
		descriptorData[0].descriptorType = Ogre::DESCRIPTOR_TYPE_BUFFER;

		const std::shared_ptr<Ogre::Material>& mat = r->getMaterial();

		Ogre::OgreTexture* tex = mat->getTexture(0);

		descriptorData[1].mCount = 1;
		descriptorData[1].pName = "colorMapTexture";
		descriptorData[1].ppTextures = (const Ogre::OgreTexture**)&tex;
		descriptorData[1].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE;

		descriptorData[2].mCount = 1;
		descriptorData[2].pName = "colorMapSampler";
		descriptorData[2].ppTextures = (const Ogre::OgreTexture**)&tex;
		descriptorData[2].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE;

		FrameResourceInfo* resourceInfo = (FrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
		auto* rs = Ogre::Root::getSingleton().getRenderSystem();
		rs->updateDescriptorSet(resourceInfo->zeroShadowSet[index], 3, descriptorData);
		};
}

void SceneRenderPass::execute(RenderContext& context)
{
	if (mPassInput.shadowMapTarget)
	{
		drawShadow(context);
	}
	draw(context);
}

void SceneRenderPass::drawShadow(RenderContext& context)
{
	{
		Ogre::RenderTargetBarrier rtBarriers[] =
		{
			{
				mPassInput.shadowMapTarget,
				Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				Ogre::RESOURCE_STATE_DEPTH_WRITE
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, &context.frameContext->cbh);
	}
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	auto& info = mRenderPassInfo;
	auto cam = mPassInput.cam;
	auto sceneManager = mPassInput.sceneMgr;
	info.renderTargetCount = 0;
	info.depthTarget.target.depthStencil = mPassInput.shadowMapTarget;

	info.shadowPass = true;
	float depthValue = 1.0f;
	if (ogreConfig.reverseDepth)
	{
		depthValue = 0.0f;
	}
	info.depthTarget.clearValue = { depthValue, 0.0f };

	for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++)
	{

		info.depthTarget.depthIndex = i;
		
	}

	{
		Ogre::RenderTargetBarrier rtBarriers[] =
		{
			{
				mPassInput.shadowMapTarget,
				Ogre::RESOURCE_STATE_DEPTH_WRITE,
				Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, nullptr);
	}

}

void SceneRenderPass::draw(RenderContext& context)
{
	{
		Ogre::RenderTargetBarrier rtBarriers[] =
		{
			{
				mPassInput.color,
				Ogre::RESOURCE_STATE_PRESENT,
				Ogre::RESOURCE_STATE_RENDER_TARGET
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, &context.frameContext->cbh);
	}

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	auto& info = mRenderPassInfo;
	auto cam = mPassInput.cam;
	auto sceneManager = mPassInput.sceneMgr;
	info.renderTargetCount = 1;
	info.renderTargets[0].target.renderTarget = mPassInput.color;
	info.depthTarget.target.depthStencil = mPassInput.depth;
	info.depthTarget.depthIndex = 0;
	info.renderTargets[0].clearColour = { 0.0, 0.3, 0.0, 1.000000000f };
	float depthValue = 1.0f;
	if (ogreConfig.reverseDepth)
	{
		depthValue = 0.0f;
	}
	info.depthTarget.clearValue = { depthValue, 0.0f };

	EngineRenderList renderList;
	mPassInput.sceneMgr->getSceneRenderList(cam, renderList, false);

	auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();

	uint32_t index = 0;

	auto& js = Ogre::ResourceManager::getSingleton().getJobSystem();
	utils::JobSystem::Job* rootJob = js.createJob();

	for (auto r : renderList.mOpaqueList)
	{
		Ogre::Material* mat = r->getMaterial().get();
		if (!mat->isLoaded())
		{
			mat->loadAsync();
		}
	}

	mRenderPassInfo.cbh = context.frameContext->cbh;

	uint32_t width = ogreConfig.width;
	uint32_t height = ogreConfig.height;
	rs->setViewport(0, 0, width, height, 0.0f, 1.0f, &mRenderPassInfo.cbh);
	rs->setScissor(0, 0, width, height, &mRenderPassInfo.cbh);

	rs->beginRenderPass(mRenderPassInfo);
	for (auto r : renderList.mOpaqueList)
	{
		Ogre::Material* mat = r->getMaterial().get();
		if (!mat->isLoaded())
		{
			continue;
		}

		auto flags = mat->getMaterialFlags();
		if (flags & Ogre::MATERIAL_FLAG_ALPHA_TESTED)
		{
			continue;
		}

		if (!r->hasFlag(frameIndex))
		{
			initObject(frameIndex, r, context);
			bindObject(frameIndex, r, context);
			r->setFlag(frameIndex, true);
		}
		
		updateObject(frameIndex, r, context);

		drawObject(frameIndex, r, context);
	}


	for (auto r : renderList.mOpaqueList)
	{
		Ogre::Material* mat = r->getMaterial().get();
		if (!mat->isLoaded())
		{
			continue;
		}
		auto flags = mat->getMaterialFlags();
		if (flags & Ogre::MATERIAL_FLAG_ALPHA_TESTED)
		{
			if (!r->hasFlag(frameIndex))
			{
				initObject(frameIndex, r, context);
				r->setFlag(frameIndex, true);
			}
			bindObject(frameIndex, r, context);
			updateObject(frameIndex, r, context);
			drawObject(frameIndex, r, context);
		}
	}
	rs->endRenderPass(mRenderPassInfo);
	{
		Ogre::RenderTargetBarrier rtBarriers[] =
		{
			{
				mPassInput.color,
				Ogre::RESOURCE_STATE_RENDER_TARGET,
				Ogre::RESOURCE_STATE_PRESENT
			}
		};
		rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers, &context.frameContext->cbh);
	}

	
}

void SceneRenderPass::update(RenderContext& context)
{
	updateFrameData(mPassInput.cam, mPassInput.light, context);
	updateCascadeMatrices(context);
}
void SceneRenderPass::updateFrameData(Ogre::ICamera* camera, Ogre::Light* light, RenderContext& context)
{
	RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
	const Ogre::Matrix4& view = camera->getViewMatrix();
	const Ogre::Matrix4& proj = camera->getProjectMatrix();
	const Ogre::Vector3& camepos = camera->getDerivedPosition();
	Ogre::Matrix4 invView = view.inverse();
	Ogre::Matrix4 viewProj = proj * view;
	Ogre::Matrix4 invProj = proj.inverse();
	Ogre::Matrix4 invViewProj = viewProj.inverse();

	mFrameConstantBuffer.View = view.transpose();
	mFrameConstantBuffer.InvView = invView.transpose();
	mFrameConstantBuffer.Proj = proj.transpose();
	mFrameConstantBuffer.InvProj = invProj.transpose();
	mFrameConstantBuffer.ViewProj = viewProj.transpose();
	mFrameConstantBuffer.InvViewProj = invViewProj.transpose();

	mFrameConstantBuffer.EyePosW = camepos;

	if (light)
	{
		mFrameConstantBuffer.numDirLights = 1;
		mFrameConstantBuffer.ShadowTransform = (light->getProjectMatrix() * light->getViewMatrix()).transpose();
		mFrameConstantBuffer.directionLights[0].lightViewProject =
			mFrameConstantBuffer.ShadowTransform;
		mFrameConstantBuffer.directionLights[0].Direction = light->getLightDirection();
		mFrameConstantBuffer.directionLights[0].Position = light->getDerivedPosition();
	}
	else
	{
		mFrameConstantBuffer.Shadow = 0;
		mFrameConstantBuffer.directionLights[0].Direction = Ogre::Vector3(0.739942074, 0.642787576, 0.198266909);
		mFrameConstantBuffer.directionLights[0].Direction.normalise();
	}


	mFrameConstantBuffer.TotalTime += Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
	mFrameConstantBuffer.DeltaTime = Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;

	auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();

	rs->updateBufferObject(mFrameData[frameIndex].passBufferHandle,
		(const char*)&mFrameConstantBuffer, sizeof(mFrameConstantBuffer));

	if (mPassInput.cascadeMatrices)
	{
		for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++)
		{
			mFrameConstantBuffer.ShadowTransform = mPassInput.cascadeMatrices->matrices[i];
			rs->updateBufferObject(mFrameData[frameIndex].shadowBufferList[i],
				(const char*)&mFrameConstantBuffer, sizeof(mFrameConstantBuffer));
		}
	}
}

void SceneRenderPass::updateCascadeMatrices(RenderContext& context)
{
	if (mPassInput.cascadeMatrices)
	{
		auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		rs->updateBufferObject(mFrameData[frameIndex].cascadeBufferHandle,
			(const char*)mPassInput.cascadeMatrices,
			sizeof(cascadeInfo));
	}

}

void SceneRenderPass::initObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	auto* rs = Ogre::Root::getSingleton().getRenderSystem();
	if (1)
	{
		FrameResourceInfo* resourceInfo = new FrameResourceInfo;
		resourceInfo->update = false;

		r->updateFrameResource(frameIndex, (void*)resourceInfo);

		Ogre::BufferDesc desc{};
		desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
		desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
		desc.bufferCreationFlags = 0;
		desc.mSize = sizeof(ObjectConstantBuffer);
		desc.pName = "cbPerObject";
		filament::backend::Handle<filament::backend::HwBufferObject> objectBufferHandle =
			rs->createBufferObject(desc);
		resourceInfo->modelObjectHandle = objectBufferHandle;

		Ogre::Material* mat = r->getMaterial().get();

		filament::backend::Handle<filament::backend::HwBufferObject> matBufferHandle;
		if (mat->isPbr())
		{
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(PbrMaterialConstanceBuffer);
			desc.pName = "pbrMaterial";
			matBufferHandle = rs->createBufferObject(desc);
		}
		else
		{
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(GeneralMaterialConstantBuffer);
			desc.pName = "cbMaterial";
			matBufferHandle = rs->createBufferObject(desc);
		}

		resourceInfo->matObjectHandle = matBufferHandle;

		filament::backend::Handle<filament::backend::HwProgram> programHandle = mat->getProgram();

		resourceInfo->zeroSet = rs->createDescriptorSet(programHandle, 0);
		resourceInfo->firstSet = rs->createDescriptorSet(programHandle, 1);

		for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++)
		{
			resourceInfo->zeroShadowSet[i] = rs->createDescriptorSet(shadowProgramHandle, 0);
		}



		Ogre::DescriptorData descriptorData[128];
		uint32_t descriptorCount = 0;
		descriptorData[descriptorCount].pName = "cbPerObject";
		descriptorData[descriptorCount].mCount = 1;
		descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_BUFFER;
		descriptorData[descriptorCount].ppBuffers = &objectBufferHandle;
		descriptorCount++;
		const char* materialName = mat->isPbr() ? "pbrMaterial" : "cbMaterial";
		descriptorData[descriptorCount].pName = materialName;
		descriptorData[descriptorCount].mCount = 1;
		descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_BUFFER;
		descriptorData[descriptorCount].ppBuffers = &matBufferHandle;
		descriptorCount++;


		RawData* rawData = r->getSkinnedData();
		if (rawData)
		{
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(SkinnedConstantBuffer);
			resourceInfo->skinObjectHandle = rs->createBufferObject(desc);
			descriptorData[descriptorCount].pName = "cbSkinned";
			descriptorData[descriptorCount].mCount = 1;
			descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_BUFFER;
			descriptorData[descriptorCount].ppBuffers = &resourceInfo->skinObjectHandle;
			descriptorCount++;
		}

		rs->updateDescriptorSet(resourceInfo->zeroSet, descriptorCount, descriptorData);

		for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++)
		{
			rs->updateDescriptorSet(resourceInfo->zeroShadowSet[i], descriptorCount - 1, descriptorData);
		}


		//update texture
		uint32_t index = 0;
		descriptorCount = 0;

		auto& texs = mat->getAllTexureUnit();
		if (mat->isPbr())
		{
			struct TextureInfo
			{
				const char* texName;
				const char* texSamplerName;
				Ogre::TextureTypePbr pbrType;
			};

#define PBR_TEXTURE_COUNT 9
			TextureInfo texInfo[PBR_TEXTURE_COUNT] =
			{
				{
					"albedo_pbr",
					"albedoSampler",
					Ogre::TextureTypePbr_Albedo
				},
				{
					"ao_pbr",
					"aoSampler",
					Ogre::TextureTypePbr_AmbientOcclusion
				},
				{
					"normal_pbr",
					"normalSampler",
					Ogre::TextureTypePbr_NormalMap
				},
				{
					"emissive_pbr",
					"emissiveSampler",
					Ogre::TextureTypePbr_Emissive
				},
				{
					"metal_roughness_pbr",
					"metalRoughnessSampler",
					Ogre::TextureTypePbr_MetalRoughness
				},
				{
					"roughness_pbr",
					"roughnessSampler",
					Ogre::TextureTypePbr_Roughness
				},
				{
					"brdflut_pbr",
					"brdflutSampler",
					Ogre::TextureTypePbr_BRDF_LUT
				},
				{
					"irradianceCube",
					"irradianceSampler",
					Ogre::TextureTypePbr_IBL_Diffuse
				},
				{
					"prefilteredCube",
					"prefilteredSampler",
					Ogre::TextureTypePbr_IBL_Specular
				},
			};

			Ogre::OgreTexture* texArray[PBR_TEXTURE_COUNT];
			std::shared_ptr<Ogre::OgreTexture> defaultTex = Ogre::TextureManager::getSingleton().load("white1x1.dds", nullptr);
			for (int i = 0; i < PBR_TEXTURE_COUNT; i++)
			{
				Ogre::OgreTexture* tex = mat->getPbrTexture(texInfo[i].pbrType);

				if (texInfo[i].pbrType == Ogre::TextureTypePbr_Emissive && tex)
				{
					int kk = 0;
				}
				if (tex == nullptr)
				{
					tex = defaultTex.get();
				}
				texArray[i] = tex;
				descriptorData[descriptorCount].pName = texInfo[i].texName;
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[i];
				descriptorCount++;

				descriptorData[descriptorCount].pName = texInfo[i].texSamplerName;
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[i];
				descriptorCount++;
			}

			rs->updateDescriptorSet(resourceInfo->firstSet, descriptorCount, descriptorData);
		}
		else
		{
			Ogre::OgreTexture* texArray[4];
			int32_t texIndex = -1;
			for (int32_t i = 0; i < texs.size(); i++)
			{
				if (texs[i]->getTextureProperty()->_texType == Ogre::TEX_TYPE_CUBE_MAP)
					continue;
				texArray[++texIndex] = texs[i]->getRaw();
			}

			if (texIndex >= 0)
			{
				descriptorData[descriptorCount].pName = "first";
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[0];
				descriptorCount++;

				descriptorData[descriptorCount].pName = "firstSampler";
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[0];
				descriptorCount++;
			}

			if (texIndex >= 1)
			{
				descriptorData[descriptorCount].pName = "second";
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[1];
				descriptorCount++;

				descriptorData[descriptorCount].pName = "secondSampler";
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[1];
				descriptorCount++;
			}

			if (texIndex >= 2)
			{
				descriptorData[descriptorCount].pName = "third";
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[2];
				descriptorCount++;

				descriptorData[descriptorCount].pName = "thirdSampler";
				descriptorData[descriptorCount].mCount = 1;
				descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
				descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[2];
				descriptorCount++;
			}

			for (int32_t i = 0; i < texs.size(); i++)
			{
				if (texs[i]->getTextureProperty()->_texType == Ogre::TEX_TYPE_CUBE_MAP)
				{
					texArray[3] = texs[i]->getRaw();
					descriptorData[descriptorCount].pName = "cubeMap";
					descriptorData[descriptorCount].mCount = 1;
					descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
					descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[3];
					descriptorCount++;

					descriptorData[descriptorCount].pName = "cubeSampler";
					descriptorData[descriptorCount].mCount = 1;
					descriptorData[descriptorCount].descriptorType = Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
					descriptorData[descriptorCount].ppTextures = (const Ogre::OgreTexture**)&texArray[3];
					descriptorCount++;
					break;
				}
			}
			rs->updateDescriptorSet(resourceInfo->firstSet, descriptorCount, descriptorData);
		}
	}
}

void SceneRenderPass::bindObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context)
{
	SceneFrameData& frameData = mFrameData[frameIndex];
	Ogre::DescriptorData descriptorData[2];

	descriptorData[0].mCount = 1;
	descriptorData[0].pName = "cbPass";
	descriptorData[0].ppBuffers = &frameData.passBufferHandle;

	FrameResourceInfo* resourceInfo = (FrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
	rs->updateDescriptorSet(resourceInfo->zeroSet, 1, descriptorData);
}

void SceneRenderPass::updateObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context)
{
	void* frameData = r->getFrameResourceInfo(frameIndex);
	FrameResourceInfo* resourceInfo = (FrameResourceInfo*)frameData;
	if (resourceInfo == nullptr)
		return;
	if (resourceInfo->update)
	{
		auto objectType = r->getObjectType();
		if (objectType == ObjectType_Static)
			return;
	}
	else
	{
		//resourceInfo.update = true;
	}

	auto* rs = Ogre::Root::getSingleton().getRenderSystem();
	Ogre::Material* mat = r->getMaterial().get();
	ObjectConstantBuffer objectBuffer;
	const auto& modelMatrix = r->getModelMatrix();

	objectBuffer.world = modelMatrix.transpose();
	objectBuffer.diffuseColor = mat->getDiffuseColor();
	objectBuffer.useShadow = r->haveShadow();
	objectBuffer.haveTexture = mat->hasTexture();
	rs->updateBufferObject(resourceInfo->modelObjectHandle,
		(const char*)&objectBuffer, sizeof(objectBuffer), 0, &context.frameContext->cbh);

	RawData* rawData = r->getSkinnedData();
	if (rawData)
	{
		rs->updateBufferObject(resourceInfo->skinObjectHandle, 
			rawData->mData, rawData->mDataSize, 0, &context.frameContext->cbh);
	}

	if (mat->isPbr())
	{
		auto& matBuffer = mat->getPbrMatInfo();
		rs->updateBufferObject(resourceInfo->matObjectHandle,
			(const char*)&matBuffer, sizeof(matBuffer), 0, &context.frameContext->cbh);
	}
	else
	{
		auto& matBuffer = mat->getMatInfo();
		rs->updateBufferObject(resourceInfo->matObjectHandle,
			(const char*)&matBuffer, sizeof(matBuffer), 0, &context.frameContext->cbh);
	}
}

void SceneRenderPass::drawObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context)
{
	void* frameData = r->getFrameResourceInfo(frameIndex);
	FrameResourceInfo* resourceInfo = (FrameResourceInfo*)frameData;
	Ogre::Material* mat = r->getMaterial().get();

	auto programHandle = mat->getProgram();
	auto piplineHandle = mat->getPipeline();

	rs->bindPipeline(context.frameContext->cbh, piplineHandle);
	rs->bindDescriptorSet(context.frameContext->cbh, programHandle, resourceInfo->zeroSet);
	rs->bindDescriptorSet(context.frameContext->cbh, programHandle, resourceInfo->firstSet);
	


	VertexData* vertexData = r->getVertexData();
	IndexData* indexData = r->getIndexData();
	vertexData->bind(context.frameContext->cbh);
	if (indexData)
	{
		indexData->bind(context.frameContext->cbh);
		IndexDataView* view = r->getIndexView();
		rs->drawIndexed(view->mIndexCount, 1,
			view->mIndexLocation, view->mBaseVertexLocation, 0, &context.frameContext->cbh);
	}
}