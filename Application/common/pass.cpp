#include "OgreHeader.h"
#include "OgreRoot.h"
#include "pass.h"
#include "engine_struct.h"
#include "renderSystem.h"
#include "OgreSceneManager.h"
#include "OgreRenderable.h"
#include "OgreMaterial.h"

class RenderPass : public PassBase
{
public:
	RenderPass(RenderPassInput& input)
	{
		mInput = input;
		RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		auto& ogreConfig = ::Root::getSingleton().getEngineConfig();
		

		auto width = ogreConfig.width;
		auto height = ogreConfig.height;
		mFrameConstantBuffer.RenderTargetSize =
			Ogre::Vector2((float)width,
				(float)height);
		mFrameConstantBuffer.InvRenderTargetSize =
			Ogre::Vector2(1.0f / width, 1.0f / height);
		mFrameConstantBuffer.NearZ = 0.1f;
		mFrameConstantBuffer.FarZ = 10000.0f;
		mFrameBufferObjectList.resize(ogreConfig.swapBufferCount);

		mRenderPassInfo.frameDataSize = sizeof(mFrameConstantBuffer);
		for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
		{
			mFrameBufferObjectList[i] =
				rs->createBufferObject(BufferObjectBinding::UNIFORM, BufferUsage::DYNAMIC, sizeof(mFrameConstantBuffer));
		}
		
	}

	void execute(RenderSystem* rs)
	{
		if (mInput.color)
		{
			mRenderPassInfo.renderTargetCount = 1;
			mRenderPassInfo.renderTargets[0].renderTarget = mInput.color;
		}
		else
		{
			mRenderPassInfo.renderTargetCount = 0;
		}
		mRenderPassInfo.depthTarget.depthStencil = mInput.depth;
		mRenderPassInfo.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
		mRenderPassInfo.depthTarget.clearValue = { 1.0f, 0.0f };
		mRenderPassInfo.cam = mInput.cam;
		mRenderPassInfo.shadowPass = mInput.shadowPass;
		mRenderPassInfo.shadowMap = mInput.shadowMap;

		auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		mRenderPassInfo.frameDataHandle = mFrameBufferObjectList[frameIndex];
		
		static EngineRenderList engineRenerList;
		mInput.sceneMgr->getSceneRenderList(mInput.cam, engineRenerList, mInput.shadowPass);
		
		if(true)
		{
			updateFrameData(rs, mRenderPassInfo.cam, mInput.light);
			auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
			ObjectConstantBuffer objectConstantBuffer;
			for (auto r : engineRenerList.mOpaqueList)
			{
				Ogre::Material* mat = r->getMaterial().get();
				if (!mat->isLoaded())
				{
					mat->load(nullptr);
				}

				FrameResourceInfo* resourceInfo = mat->getFrameResourceInfo(frameIndex);
				const Ogre::Matrix4& model = r->getModelMatrix();
				objectConstantBuffer.world = model.transpose();

				rs->updateBufferObject(resourceInfo->modelObjectHandle,
					(const char*)&objectConstantBuffer, sizeof(objectConstantBuffer));


				

				RawData* rawData = r->getSkinnedData();

				if (rawData)
				{
					rs->updateBufferObject(resourceInfo->skinObjectHandle, rawData->mData, rawData->mDataSize);
				}

				if (mInput.shadowPass)
				{
					rs->updateDescriptorSetBuffer(resourceInfo->uboShadowSet, 1,
						mRenderPassInfo.frameDataHandle, 0, sizeof(mFrameConstantBuffer));
				}
				else
				{
					rs->updateDescriptorSetBuffer(resourceInfo->uboSet, 1,
						mRenderPassInfo.frameDataHandle, 0, sizeof(mFrameConstantBuffer));
				}

				if (mInput.shadowMap)
				{
					rs->updateDescriptorSetTexture(resourceInfo->samplerSet, 3, mInput.shadowMap);

					
				}

			}
		}
		rs->beginRenderPass(mRenderPassInfo);
		rs->multiRender(engineRenerList.mOpaqueList);
		rs->endRenderPass();
	}

	void updateFrameData(RenderSystem* rs, ICamera* camera, ICamera* light)
	{
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
			mFrameConstantBuffer.ShadowTransform = (light->getProjectMatrix() * light->getViewMatrix()).transpose();
			mFrameConstantBuffer.Shadow = 1;
		}
		else
		{
			mFrameConstantBuffer.Shadow = 0;
		}
		
		
		mFrameConstantBuffer.TotalTime += Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
		mFrameConstantBuffer.DeltaTime = Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
		auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		
		rs->updateBufferObject(
			mFrameBufferObjectList[frameIndex], (const char*)&mFrameConstantBuffer, sizeof(mFrameConstantBuffer));

	}
private:
	RenderPassInput mInput;
	RenderPassInfo mRenderPassInfo;

	FrameConstantBuffer mFrameConstantBuffer;
	std::vector<Handle<HwBufferObject>> mFrameBufferObjectList;
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