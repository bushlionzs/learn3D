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
	RenderPipeline* renderPipeline,
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
	//gameCamera->updateCamera(Ogre::Vector3(-10, h, 0.0f), Ogre::Vector3(0.f, h, 0.0f));
	mGameCamera->updateCamera(Ogre::Vector3(-10, 0.0f, 0.0f), Ogre::Vector3::ZERO);
	gameCamera->setMoveSpeed(200);
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
	
	RenderPassInput input;
	input.color = renderWindow->getColorTarget();
	input.depth = renderWindow->getDepthTarget();
	input.cam = cam;
	input.sceneMgr = sceneManager;
	auto mainPass = createStandardRenderPass(input);
	renderPipeline->addRenderPass(mainPass);
}

void VoxelConeTracingApp::update(float delta)
{
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