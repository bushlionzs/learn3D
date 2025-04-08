#include "OgreHeader.h"
#include "OgreRoot.h"
#include "OgreCommon.h"
#include "pass.h"
#include "engine_struct.h"
#include "renderSystem.h"
#include "game_camera.h"
#include "OgreSceneManager.h"
#include "OgreRenderable.h"
#include "OgreMaterial.h"
#include "OgreRenderTarget.h"
#include "OgreTextureManager.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "renderUtil.h"
#include "presentPass.h"

class StandardRenderPass : public PassBase
{
public:
	StandardRenderPass(RenderPassInput& input)
	{
		mPassInput = input;
		mRenderPassInfo.flipY = input.flipY;
		RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
		mFrameBufferObjectList.resize(ogreConfig.swapBufferCount);
		mCascadeInfoList.resize(ogreConfig.swapBufferCount);

		mShadowBufferList.resize(ogreConfig.swapBufferCount * SHADOW_MAP_CASCADE_COUNT);
		for (auto i = 0; i < mFrameBufferObjectList.size(); i++)
		{
			Ogre::BufferDesc desc{};
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(mFrameConstantBuffer);
			mFrameBufferObjectList[i] = rs->createBufferObject(desc);
		}

		for (auto i = 0; i < mShadowBufferList.size(); i++)
		{
			Ogre::BufferDesc desc{};
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(mFrameConstantBuffer);
			mShadowBufferList[i] = rs->createBufferObject(desc);
		}

		for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
		{
			Ogre::BufferDesc desc{};
			desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
			desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
			desc.bufferCreationFlags = 0;
			desc.mSize = sizeof(cascadeInfo);
			mCascadeInfoList[i] = rs->createBufferObject(desc);
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

		mUserDefineShader.initCallback = initFrameResource;
		RenderPassInput* passInput = &mPassInput;
		filament::backend::SamplerParams params{};
		params.filterMag = filament::backend::SamplerFilterType::LINEAR;
		params.filterMin = filament::backend::SamplerFilterType::LINEAR;
		params.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
		params.wrapS = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
		params.wrapT = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
		params.wrapR = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
		params.compareMode = filament::backend::SamplerCompareMode::COMPARE_TO_TEXTURE;
		params.compareFunc = filament::backend::SamplerCompareFunc::LE;
		params.anisotropyLog2 = 0;
		params.useComparison = 0;
		params.maxLod = 1;
		params.padding2 = 0;
		filament::backend::Handle<filament::backend::HwSampler> shadowMapSampler = rs->createTextureSampler(params);
		RenderableBindCallback bindCallback = [=](uint32_t frameIndex, Ogre::Renderable* r, void*) {
			Ogre::DescriptorData descriptorData[2];
				
			descriptorData[0].mCount = 1;
			descriptorData[0].pName = "cbPass";
			descriptorData[0].ppBuffers = &mFrameBufferObjectList[frameIndex];

			
			FrameResourceInfo* resourceInfo = (FrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
			auto* rs = Ogre::Root::getSingleton().getRenderSystem();
			rs->updateDescriptorSet(resourceInfo->zeroSet, 1, descriptorData);
			if (passInput->shadowMapTarget)
			{
				descriptorData[0].mCount = 1;
				descriptorData[0].pName = "cascadeInfo";
				descriptorData[0].ppBuffers = &mCascadeInfoList[frameIndex];
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
		mUserDefineShader.bindCallback = bindCallback;

		if (this->mPassInput.shadowMapTarget)
		{
			mUserDefineShader.updateCallback = nullptr;
		}
		else
		{
			mUserDefineShader.updateCallback = updateFrameResource;
		}
		
		RenderableDrawCallback drawCallback = [=](uint32_t frameIndex, Ogre::Renderable* r, void* param) {
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
				rs->bindPipeline(piplineHandle, descriptorSet, 2);
			}
			else
			{
				rs->bindPipeline(piplineHandle, &resourceInfo->zeroSet, 1);
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
				/*IndexDataView* view = r->getIndexView();
				uint32_t vertexCount = vertexData->getVertexCount();
				rs->draw(vertexCount, view->mBaseVertexLocation);*/
			}
			};
		mUserDefineShader.drawCallback = drawCallback;
		mRenderPassInfo.passName = "generalPass";


		mUserDefineShaderOfShadow.initCallback = initFrameResource;
		
		mUserDefineShaderOfShadow.updateCallback = updateFrameResource;
		
		ShaderInfo shaderInfo;
		shaderInfo.shaderName = "shadow";
		VertexDeclaration decl;
		decl.addElement(0, 0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		decl.addElement(0, 0, 12, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
		decl.addElement(0, 0, 24, Ogre::VET_FLOAT4, Ogre::VES_TANGENT);
		decl.addElement(0, 0, 40, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
		filament::backend::Handle<filament::backend::HwProgram> shadowProgramHandle = rs->createShaderProgram(shaderInfo, &decl);

		filament::backend::RasterState rasterState;
		rasterState.depthWrite = true;
		rasterState.depthTest = true;
		rasterState.depthFunc = filament::backend::SamplerCompareFunc::LE;
		rasterState.colorWrite = true;
		rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_UNKNOWN;
		rasterState.renderTargetCount = 0;
		rasterState.depthBiasConstantFactor = 1.25f;
		rasterState.depthBiasSlopeFactor = 1.75f;

		filament::backend::Handle<filament::backend::HwPipeline> shadowPipelineHandle = rs->createPipeline(rasterState, shadowProgramHandle);

		RenderableBindCallback shadowBindCallback = [=](uint32_t frameIndex, Ogre::Renderable* r, void* param) {
			    uint64_t index = (uint64_t)param;
			    Ogre::DescriptorData descriptorData[3];
				descriptorData[0].mCount = 1;
				descriptorData[0].pName = "cbPass";
				descriptorData[0].ppBuffers = &mShadowBufferList[frameIndex * SHADOW_MAP_CASCADE_COUNT + index];
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
		mUserDefineShaderOfShadow.bindCallback = shadowBindCallback;
		RenderableDrawCallback shadowDrawCallback = [=](uint32_t frameIndex, Ogre::Renderable* r, void* param) {
			void* frameData = r->getFrameResourceInfo(frameIndex);
			FrameResourceInfo* resourceInfo = (FrameResourceInfo*)frameData;
			uint64_t index = (uint64_t)param;
			rs->bindPipeline(shadowPipelineHandle, &resourceInfo->zeroShadowSet[index], 1);
			
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
		mUserDefineShaderOfShadow.drawCallback = shadowDrawCallback;

		mUserDefineShaderOfShadow.shadowHandle = shadowProgramHandle;
		mUserDefineShader.shadowHandle = shadowProgramHandle;
	}

	virtual void execute(RenderSystem* rs)
	{
		if (mPassInput.shadowMapTarget)
		{
			drawShadow(rs);
		}
		draw(rs);
	}

	void drawShadow(RenderSystem* rs)
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
			rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		}
		auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
		auto& info = mRenderPassInfo;
		auto cam = mPassInput.cam;
		auto sceneManager = mPassInput.sceneMgr;
		info.renderTargetCount = 0;
		info.depthTarget.depthStencil = mPassInput.shadowMapTarget;
		
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
			mUserDefineShaderOfShadow.param = (void*)(uint64_t)i;
			renderScene(cam, sceneManager, mRenderPassInfo, &mUserDefineShaderOfShadow);

			
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
			rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		}
		
	}

	void draw(RenderSystem* rs)
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
			rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		}

		auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
		auto& info = mRenderPassInfo;
		auto cam = mPassInput.cam;
		auto sceneManager = mPassInput.sceneMgr;
		info.renderTargetCount = 1;
		info.renderTargets[0].renderTarget = mPassInput.color;
		info.depthTarget.depthStencil = mPassInput.depth;
		info.depthTarget.depthIndex = 0;
		info.renderTargets[0].clearColour = { 0.0, 0.0, 0.0, 1.000000000f };
		float depthValue = 1.0f;
		if (ogreConfig.reverseDepth)
		{
			depthValue = 0.0f;
		}
		info.depthTarget.clearValue = { depthValue, 0.0f };
		renderScene(cam, sceneManager, mRenderPassInfo, &mUserDefineShader);

		{
			Ogre::RenderTargetBarrier rtBarriers[] =
			{
				{
					mPassInput.color,
					Ogre::RESOURCE_STATE_RENDER_TARGET,
					Ogre::RESOURCE_STATE_PRESENT
				}
			};
			rs->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		}
	}
	virtual void update(float delta)
	{
		updateFrameData(mPassInput.cam, mPassInput.light);
		updateCascadeMatrices();
	}
private:
	void updateFrameData(Ogre::ICamera* camera, Ogre::Light* light)
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

		rs->updateBufferObject(mFrameBufferObjectList[frameIndex], 
			(const char*)&mFrameConstantBuffer, sizeof(mFrameConstantBuffer));

		if (mPassInput.cascadeMatrices)
		{
			for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++)
			{
				mFrameConstantBuffer.ShadowTransform = mPassInput.cascadeMatrices->matrices[i];
				rs->updateBufferObject(mShadowBufferList[frameIndex * SHADOW_MAP_CASCADE_COUNT + i],
					(const char*)&mFrameConstantBuffer, sizeof(mFrameConstantBuffer));
			}
		}
		

	}
	void updateCascadeMatrices()
	{
		if (mPassInput.cascadeMatrices)
		{
			auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
			RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
			rs->updateBufferObject(mCascadeInfoList[frameIndex],
				(const char*)mPassInput.cascadeMatrices,
				sizeof(cascadeInfo));
		}
		
	}
private:
	RenderPassInput mPassInput;
	RenderPassInfo mRenderPassInfo;
	FrameConstantBuffer mFrameConstantBuffer;
	std::vector<filament::backend::Handle<filament::backend::HwBufferObject>> mFrameBufferObjectList;
	std::vector<filament::backend::Handle<filament::backend::HwBufferObject>> mShadowBufferList;
	std::vector<filament::backend::Handle<filament::backend::HwBufferObject>> mCascadeInfoList;
	UserDefineShader mUserDefineShader;
	UserDefineShader mUserDefineShaderOfShadow;
};

PassBase* createStandardRenderPass(RenderPassInput& input)
{
	return new StandardRenderPass(input);
}

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
	ComputePass(ComputePassCallback userCallback,
		UpdatePassCallback updateCallback)
	{
		mCallback = userCallback;
		mUpdateCallback = updateCallback;
	}

	void execute(RenderSystem* rs)
	{
		mCallback();
	}

	void update(float delta)
	{
		if(mUpdateCallback)
			mUpdateCallback(delta);
	}
private:
	ComputePassCallback mCallback;
	UpdatePassCallback  mUpdateCallback;
};

PassBase* createComputePass(
	ComputePassCallback userCallback,
	UpdatePassCallback updateCallback)
{
	return new ComputePass(userCallback, updateCallback);
}

PassBase* createPresentPass(
	Ogre::RenderTarget* sourceTarget, 
	Ogre::RenderWindow* renderWindow,
	const char* shaderName)
{
	return new PresentPass(sourceTarget->getTarget(), renderWindow, shaderName);
}