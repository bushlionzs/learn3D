#include "OgreHeader.h"
#include "VoxelConeTracing.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "OGImpact.h"
#include "OGImpactManager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreRenderable.h"

VoxelConeTracingApp::VoxelConeTracingApp()
{

}

VoxelConeTracingApp::~VoxelConeTracingApp()
{

}

void VoxelConeTracingApp::setup(
	RenderSystem* renderSystem,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	mGameCamera   = gameCamera;
	mSceneManager = sceneManager;
	mRenderWindow = renderWindow;
	std::string meshname = "Sponza.gltf";
	std::shared_ptr<Mesh> mesh = MeshManager::getSingletonPtr()->load(meshname);
	auto rootNode = sceneManager->getRoot();
	Entity* sponza = sceneManager->createEntity(meshname, meshname);
	SceneNode* sponzaNode = rootNode->createChildSceneNode(meshname);
	sponzaNode->attachObject(sponza);

	float h = 100.0f;
	gameCamera->updateCamera(Ogre::Vector3(0, h, 0.0f), Ogre::Vector3(-10.f, h, 0.0f));
	gameCamera->setMoveSpeed(50.0f);
	gameCamera->getCamera()->setCameraCull(true);
	
	mRenderSystem = Ogre::Root::getSingleton().getRenderSystem();
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


	for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
	{
		mFrameBufferObjectList[i] =
			rs->createBufferObject(BufferObjectBinding::BufferObjectBinding_Uniform, BufferUsage::DYNAMIC, sizeof(mFrameConstantBuffer));
	}

	auto* cam = gameCamera->getCamera();
	auto* light = sceneManager->createLight("light");
	UpdatePassCallback mainUpdateCallback = [=, this](float delta) {
		this->updateFrameData(cam, light);
		};
	RenderPassCallback renderCallback = [=, this](RenderPassInfo& info) {
		info.renderTargetCount = 1;
		info.renderTargets[0].renderTarget = renderWindow->getColorTarget();
		info.depthTarget.depthStencil = renderWindow->getDepthTarget();
		info.renderTargets[0].clearColour = { 0.678431f, 0.847058f, 0.901960f, 1.000000000f };
		info.depthTarget.clearValue = { 1.0f, 0.0f };
		info.cam = cam;
		static EngineRenderList engineRenerList;
		sceneManager->getSceneRenderList(cam, engineRenerList, false);
		auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		for (auto r : engineRenerList.mOpaqueList)
		{
			Ogre::Material* mat = r->getMaterial().get();
			
			if (!mat->isLoaded())
			{
				mat->load(nullptr);
				r->createFrameResource();
				for (auto i = 0; i < ogreConfig.swapBufferCount; i++)
				{
					FrameResourceInfo* resourceInfo = r->getFrameResourceInfo(i);
					auto frameHandle = this->getFrameHandle(i);
					rs->updateDescriptorSetBuffer(resourceInfo->zeroSet, 1, &frameHandle, 1);
					rs->updateDescriptorSetBuffer(resourceInfo->zeroShadowSet, 1, &frameHandle, 1);
				}
				
			}

			
			r->updateFrameResource(frameIndex);
		}
		rs->beginRenderPass(info);
		rs->multiRender(engineRenerList.mOpaqueList);
		rs->endRenderPass();
		};
	auto mainPass = createUserDefineRenderPass(renderCallback, mainUpdateCallback);
	mPassList.push_back(mainPass);
}

void VoxelConeTracingApp::update(float delta)
{
	mGameCamera->update(delta);
}

void VoxelConeTracingApp::updatePass(std::vector<PassBase*>& passlist)
{
	passlist = mPassList;
}

EngineType VoxelConeTracingApp::getEngineType()
{
	return EngineType_Vulkan;
}

void VoxelConeTracingApp::updateFrameData(ICamera* camera, ICamera* light)
{
	RenderSystem* rs = mRenderSystem;
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

		mFrameConstantBuffer.numDirLights = 1;
		mFrameConstantBuffer.directionLights[0].lightViewProject =
			(light->getProjectMatrix() * light->getViewMatrix()).transpose();
		mFrameConstantBuffer.directionLights[0].Direction = Ogre::Vector3(-100.0f, -100.0f, 0.0f);
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