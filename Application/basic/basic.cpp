#include "OgreHeader.h"
#include "basic.h"
#include "engine_manager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreAnimationState.h"
#include "renderSystem.h"
#include "OgreCamera.h"
#include "OgreRenderTarget.h"
#include "OgreRenderWindow.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreRoot.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"

BasicApplication::BasicApplication()
{

}

BasicApplication::~BasicApplication()
{

}


void BasicApplication::setup(
	RenderPipeline* renderPipeline,
	RenderContext& context,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	ogreConfig.reverseDepth = false;
	mSceneManager = sceneManager;
	mGameCamera = gameCamera;
	mRenderWindow = renderWindow;
	mRenderPipeline = renderPipeline;
	mRenderSystem = Ogre::Root::getSingleton().getRenderSystem();
	base6();
}

void BasicApplication::update(float delta)
{
	if (mAnimationState)
	{
		mAnimationState->addTime(delta);
	}
}

void BasicApplication::base1()
{
	Ogre::BufferDesc desc{};
	desc.mBindingType = Ogre::BufferObjectBinding_Uniform;
	desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = 0;
	desc.mSize = 128;
	mRenderSystem->createBufferObject(desc);

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
	filament::backend::Handle<filament::backend::HwSampler> shadowMapSampler = mRenderSystem->createTextureSampler(params);

	bool b = PixelUtil::isCompressed(PFG_BC1_UNORM_SRGB);
	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	float aa = 1;
	Ogre::Vector3 leftop = Ogre::Vector3(-aa, aa, 0.0f);
	Ogre::Vector3 leftbottom = Ogre::Vector3(-aa, -aa, 0.0f);
	Ogre::Vector3 righttop = Ogre::Vector3(aa, aa, 0.0f);
	Ogre::Vector3 rightbottom = Ogre::Vector3(aa, -aa, 0.0f);
	Ogre::Vector3 normal = Ogre::Vector3(0.0f, 0.0f, 1.0f);


	std::string meshName = "rect";
	
	auto mesh = Ogre::MeshManager::getSingletonPtr()->createRect(
		meshName,
		leftop, leftbottom, righttop, rightbottom, normal);

	Ogre::Entity* rect = mSceneManager->createEntity("rect", meshName);
	Ogre::SceneNode* rectnode = root->createChildSceneNode("rect");
	rectnode->attachObject(rect);

	Ogre::SubEntity* subEntry = rect->getSubEntity(0);
	auto& mat = subEntry->getMaterial();

	ShaderInfo& info = mat->getShaderInfo();
	mGameCamera->lookAt(Ogre::Vector3(0, 0.0f, -3.f), Ogre::Vector3::ZERO);
	mGameCamera->setCameraType(Ogre::CameraMoveType_LookAt);
	mGameCamera->setMoveSpeed(0.01);

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

	CameraInfo cameraInfo;
	cameraInfo.width = ogreConfig.width;
	cameraInfo.height = ogreConfig.height;
	cameraInfo.nearClip = 0.1f;
	cameraInfo.farClip = 6000.f;
	cameraInfo.fovRadians = Ogre::Math::PI / 3.0f;
	cameraInfo.reverseDepth = ogreConfig.reverseDepth;
	mGameCamera->updateCameraInfo(cameraInfo);


	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createSceneRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

void BasicApplication::base2()
{
	std::string name = "Â¥À¼ÕÊÅñ04.mesh";
	name = "dragon.fbx";
	auto mesh = Ogre::MeshManager::getSingletonPtr()->load(name);

	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Ogre::Entity* sphere = mSceneManager->createEntity(name, name);
	Ogre::SceneNode* spherenode = root->createChildSceneNode(name);

	//sphere->setMaterialName("myrect");

	spherenode->attachObject(sphere);

	mGameCamera->lookAt(
		Ogre::Vector3(0.0f, 7.0f, 33.0f),
		Ogre::Vector3(0.0f, 7.0f, 32.0f));
	mGameCamera->setMoveSpeed(20);
	mGameCamera->setCameraType(Ogre::CameraMoveType_FirstPerson);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	float aspectInverse = ogreConfig.height / (float)ogreConfig.width;


	CameraInfo cameraInfo;
	cameraInfo.width = ogreConfig.width;
	cameraInfo.height = ogreConfig.height;
	cameraInfo.nearClip = 0.1f;
	cameraInfo.farClip = 6000.f;
	cameraInfo.fovRadians = Ogre::Math::PI / 3.0f;
	cameraInfo.reverseDepth = ogreConfig.reverseDepth;
	mGameCamera->updateCameraInfo(cameraInfo);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createSceneRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

void BasicApplication::base3()
{
	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	std::string meshName = "box";
	auto mesh = Ogre::MeshManager::getSingleton().createBox(meshName, 1, "mybox");

	{
		auto entity = mSceneManager->createEntity("box1", meshName);
		Ogre::SceneNode* node = root->createChildSceneNode("box1");
		node->attachObject(entity);
		node->setPosition(0.0f, 0.0f, -5.0f);
	}

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	float aspectInverse = ogreConfig.height / (float)ogreConfig.width;

	mGameCamera->setCameraType(Ogre::CameraMoveType_LookAt);
	mGameCamera->lookAt(
		Ogre::Vector3(0.5f, 0.0f, -7),
		Ogre::Vector3(0.0f, 0.0f, 0.0f));
	mGameCamera->setMoveSpeed(5);

	Ogre::Matrix4 m;

	if (ogreConfig.reverseDepth)
	{
		float aspectInverse = ogreConfig.height / (float)ogreConfig.width;
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			Ogre::Math::PI / 4.0f, aspectInverse, 0.1, 10000.f);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			Ogre::Math::PI / 4.0f, aspect, 0.1, 10000.f);
	}
	mGameCamera->getCamera()->updateProjectMatrix(m);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

void BasicApplication::base4()
{
	std::string meshname = "ÃÉ¹Å¹ó×åÅ®_03.mesh";
	auto mesh = Ogre::MeshManager::getSingletonPtr()->load(meshname);

	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Ogre::Entity* gltf = mSceneManager->createEntity("gltf", meshname);
	Ogre::SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->updatechildren();
	gltfnode->attachObject(gltf);

	mAnimationState = gltf->getAnimationState(std::string("ÐÝÏÐ04_02"));
	if (mAnimationState)
	{
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
	}

	mGameCamera->lookAt(
		Ogre::Vector3(0.0f, 0.0f, 500.0f),
		Ogre::Vector3(0.0f, 0.0f, 0.0f));
	mGameCamera->setMoveSpeed(25);

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	float aspectInverse = ogreConfig.height / (float)ogreConfig.width;

	Ogre::Matrix4 m;

	if (ogreConfig.reverseDepth)
	{
		float aspectInverse = ogreConfig.height / (float)ogreConfig.width;
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			Ogre::Math::PI / 2.0f, aspectInverse, 0.1, 10000.f);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			Ogre::Math::PI / 2.0f, aspect, 0.1, 10000.f);
	}
	mGameCamera->getCamera()->updateProjectMatrix(m);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

void BasicApplication::base5()
{
	std::string meshname = "bunny.fbx";
	meshname = "sphere_big.fbx";
	auto mesh = Ogre::MeshManager::getSingletonPtr()->load(meshname);

	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Ogre::Entity* gltf = mSceneManager->createEntity("fbx", meshname);
	Ogre::SceneNode* gltfnode = root->createChildSceneNode("fbx");
	gltfnode->updatechildren();
	gltfnode->attachObject(gltf);

	mGameCamera->lookAt(
		Ogre::Vector3(0.0f, 0.0, 20),
		Ogre::Vector3(0.0f, 0.0f, 0.0f));
	mGameCamera->setMoveSpeed(25);

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	float aspectInverse = ogreConfig.height / (float)ogreConfig.width;

	Ogre::Matrix4 m;

	if (ogreConfig.reverseDepth)
	{
		float aspectInverse = ogreConfig.height / (float)ogreConfig.width;
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			Ogre::Math::PI / 2.0f, aspectInverse, 0.1, 1000);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			Ogre::Math::PI / 2.0f, aspect, 0.1, 1000);
	}
	mGameCamera->getCamera()->updateProjectMatrix(m);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}


void BasicApplication::base6()
{
	std::string name = "Sponza.gltf";
	auto mesh = Ogre::MeshManager::getSingletonPtr()->load(name);

	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Ogre::Entity* sphere = mSceneManager->createEntity(name, name);
	Ogre::SceneNode* spherenode = root->createChildSceneNode(name);

	//sphere->setMaterialName("myrect");

	spherenode->attachObject(sphere);
	Ogre::Vector3 camPos(-1.0f, 1.f, 0.0f);
	Ogre::Vector3 lookAt(-2.0f, 1.f, 0.0f);
	mGameCamera->lookAt(camPos,lookAt);
	mGameCamera->setMoveSpeed(0.01);
	mGameCamera->setRotateSpeed(0.02);
	mGameCamera->setCameraType(Ogre::CameraMoveType_FirstPerson);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

	CameraInfo cameraInfo;
	cameraInfo.width = ogreConfig.width;
	cameraInfo.height = ogreConfig.height;
	cameraInfo.nearClip = 0.1f;
	cameraInfo.farClip = 2000;
	cameraInfo.fovRadians = Ogre::Math::PI / 3.0f;
	cameraInfo.reverseDepth = ogreConfig.reverseDepth;
	mGameCamera->updateCameraInfo(cameraInfo);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}