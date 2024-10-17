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
				rs->createBufferObject(BufferObjectBinding::BufferObjectBinding_Uniform, BufferUsage::DYNAMIC, sizeof(mFrameConstantBuffer));
		}
		mDefaultTexture = TextureManager::getSingleton().load("white1x1.dds", nullptr);
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
					auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

					auto* shadowTex = mDefaultTexture.get();
					if (mInput.shadowMap)
					{
						shadowTex = mInput.shadowMap;
					}
					for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
					{
						FrameResourceInfo* resourceInfo = mat->getFrameResourceInfo(i);
						rs->updateDescriptorSetTexture(resourceInfo->samplerSet, 3, &shadowTex, 1);
					}
				}

				FrameResourceInfo* resourceInfo = mat->getFrameResourceInfo(frameIndex);
				const Ogre::Matrix4& model = r->getModelMatrix();
				objectConstantBuffer.world = model.transpose();

				rs->updateBufferObject(resourceInfo->modelObjectHandle,
					(const char*)&objectConstantBuffer, sizeof(objectConstantBuffer));

				if (mInput.shadowPass)
				{
					rs->updateDescriptorSetBuffer(resourceInfo->uboShadowSet, 1,
						&mRenderPassInfo.frameDataHandle, 1);
				}
				else
				{
					RawData* rawData = r->getSkinnedData();

					if (rawData)
					{
						rs->updateBufferObject(resourceInfo->skinObjectHandle, rawData->mData, rawData->mDataSize);
					}

					rs->updateDescriptorSetBuffer(resourceInfo->uboSet, 1,
						&mRenderPassInfo.frameDataHandle, 1);

					
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

	std::shared_ptr<OgreTexture> mDefaultTexture;
};

PassBase* createStandardRenderPass(RenderPassInput& input)
{
	return new RenderPass(input);
}

class UserDefineRenderPass : public PassBase
{
public:
	UserDefineRenderPass(RenderPassCallback userCallback)
	{
		mCallback = userCallback;
	}

	void execute(RenderSystem* rs)
	{
		mCallback(mRenderPassInfo);
	}
private:
	RenderPassInfo mRenderPassInfo;
	RenderPassCallback mCallback;
};
PassBase* createUserDefineRenderPass(RenderPassCallback callback)
{
	return new UserDefineRenderPass(callback);
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