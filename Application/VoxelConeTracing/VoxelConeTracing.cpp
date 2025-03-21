#include "OgreHeader.h"
#include "VoxelConeTracing.h"
#include "OgreParticleSystem.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreTextureManager.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreCamera.h"
#include "OgreRenderWindow.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "OgreRenderable.h"
#include "OgreVertexData.h"
#include "OgreTextureUnit.h"
#include "OgreVertexDeclaration.h"
#include "presentPass.h"
#include "renderUtil.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



VoxelConeTracingApp::VoxelConeTracingApp()
{

}

VoxelConeTracingApp::~VoxelConeTracingApp()
{

}

void VoxelConeTracingApp::setup(
	RenderPipeline* renderPipeline,
	RenderSystem* rs,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	mRenderPipeline = renderPipeline;
	mGameCamera   = gameCamera;
	mSceneManager = sceneManager;
	mRenderWindow = renderWindow;
	mRenderSystem = rs;
	std::string meshname = "sponza.obj";
	std::shared_ptr<Mesh> mesh = MeshManager::getSingletonPtr()->load(meshname);
	auto rootNode = sceneManager->getRoot();
	Entity* sponza = sceneManager->createEntity(meshname, meshname);
	SceneNode* sponzaNode = rootNode->createChildSceneNode(meshname);
	sponzaNode->attachObject(sponza);

	auto h = 7.0f;
	auto camPos = Ogre::Vector3(0.0f, h, 33.0f);
	auto targetPos = Ogre::Vector3(0.0f, h, 0.0f);
	gameCamera->lookAt(camPos, targetPos);
	gameCamera->setMoveSpeed(20);


	float aspect = ogreConfig.width / (float)ogreConfig.height;
	Ogre::Matrix4 m = Ogre::Math::makePerspectiveMatrix(
		Ogre::Math::PI / 3.0f, aspect, 0.1, 1000.0f);

	gameCamera->getCamera()->updateProjectMatrix(m);

	initScene();
	
	mRenderSystem = rs;

	auto* cam = gameCamera->getCamera();
	auto* light = sceneManager->createLight("light");

	if(1)
	{
		sceneGeometryPass();
	}

	if (0)
	{
		shadowPass();
	}

	if (0)
	{
		voxelizationPass();
	}

	if (0)
	{
		computePass();
	}

	if (1)
	{
		Ogre::OgreTexture* source = mVoxelizationContext.diffuseTarget->getTarget();
		auto presentPass = new PresentPass(source, mRenderWindow);
		presentPass->initialize();
		mRenderPipeline->addRenderPass(presentPass);
	}
}

void VoxelConeTracingApp::update(float delta)
{
}

void VoxelConeTracingApp::sceneGeometryPass()
{
	BufferDesc desc{};
	desc.mBindingType = BufferObjectBinding_Uniform;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = 0;
	desc.mSize = sizeof(mFrameConstantBuffer);
	Handle<HwBufferObject> zeroFrameBufferHandle = mRenderSystem->createBufferObject(desc);
	Handle<HwBufferObject> firstFrameBufferHandle = mRenderSystem->createBufferObject(desc);

	VoxelizationContext* context = &mVoxelizationContext;
	static UserDefineShader userDefineShader;
	userDefineShader.initCallback = std::bind(
		&VoxelConeTracingApp::initFrameResource, this, std::placeholders::_1, std::placeholders::_2);
	RenderableBindCallback bindCallback = [=, this](uint32_t frameIndex, Renderable* r) {
		if (r->hasFlag(sceneGeometryPassBit + frameIndex))
		{
			return;
		}
		r->setFlag(sceneGeometryPassBit + frameIndex, true);
		DescriptorData descriptorData[2];
		Handle<HwBufferObject> tmp[2];
		tmp[0] = zeroFrameBufferHandle;
		tmp[1] = firstFrameBufferHandle;
		
		VctFrameResourceInfo* resourceInfo = (VctFrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
		descriptorData[0].mCount = 1;
		descriptorData[0].pName = "cbPass";
		descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[0].ppBuffers = &tmp[frameIndex];
		
		mRenderSystem->updateDescriptorSet(resourceInfo->sceneGeometryZeroSet, 1, descriptorData);

		

		};
	userDefineShader.bindCallback = bindCallback;

	RenderableDrawCallback drawCallback = [=, this](uint32_t frameIndex, Renderable* r) {
		void* frameData = r->getFrameResourceInfo(frameIndex);
		VctFrameResourceInfo* resourceInfo = (VctFrameResourceInfo*)frameData;
		Ogre::Material* mat = r->getMaterial().get();

		Handle<HwDescriptorSet> descriptorSet[2];
		descriptorSet[0] = resourceInfo->sceneGeometryZeroSet;
		descriptorSet[1] = resourceInfo->sceneGeometryFirstSet;
		mRenderSystem->bindPipeline(mSceneGeometryPipelineHandle, descriptorSet, 2);


		VertexData* vertexData = r->getVertexData();
		IndexData* indexData = r->getIndexData();
		vertexData->bind(nullptr);
		indexData->bind();
		IndexDataView* view = r->getIndexView();
		mRenderSystem->drawIndexed(view->mIndexCount, 1,
			view->mIndexLocation, view->mBaseVertexLocation, 0);
		};
	userDefineShader.drawCallback = drawCallback;
	UserDefineShader* pUserDefineShader = &userDefineShader;
	RenderPassCallback sceneGeometryPassCallback = [=, this](RenderPassInfo& info) {
		info.renderTargetCount = 4;
		info.renderTargets[0].renderTarget = mVoxelizationContext.diffuseTarget;
		info.renderTargets[0].clearColour = { 0.0f, 0.0f, 0.0f, 1.0f };
		info.renderTargets[1].renderTarget = mVoxelizationContext.normalTarget;
		info.renderTargets[1].clearColour = { 0.0f, 0.0f, 0.0f, 1.0f };
		info.renderTargets[2].renderTarget = mVoxelizationContext.specularTarget;
		info.renderTargets[2].clearColour = { 0.0f, 0.0f, 0.0f, 1.0f };
		info.renderTargets[3].renderTarget = mVoxelizationContext.emissiveTarget;
		info.renderTargets[3].clearColour = { 0.0f, 0.0f, 0.0f, 1.0f };
		info.depthTarget.depthStencil = mVoxelizationContext.depthTarget;

		info.depthTarget.clearValue = { 1.0f, 0.0f };
		info.passName = "sceneGeometryPass";
		
		mRenderSystem->pushGroupMarker("sceneGeometryPass");
		renderScene(mGameCamera->getCamera(), mSceneManager, 
			info, pUserDefineShader);
		mRenderSystem->popGroupMarker();
		};

	FrameConstantBuffer* pFrameBuffer = &mFrameConstantBuffer;
	UpdatePassCallback updateCallback = [=, this](float delta) {
		uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		updateFrameData(mGameCamera->getCamera(), nullptr, *pFrameBuffer);
		mRenderSystem->updateBufferObject(
			frameIndex? firstFrameBufferHandle:zeroFrameBufferHandle, 
			(const char*)pFrameBuffer, sizeof(mFrameConstantBuffer));
		EngineRenderList renderList;
		mSceneManager->getSceneRenderList(mGameCamera->getCamera(), renderList, false);
		for (auto r : renderList.mOpaqueList)
		{
			updateFrameResource(frameIndex, r);
		}
		};


	auto sceneGeometryPass = createUserDefineRenderPass(
		sceneGeometryPassCallback, updateCallback);
	mRenderPipeline->addRenderPass(sceneGeometryPass);
}

void VoxelConeTracingApp::shadowPass()
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	

	

	VoxelizationContext* context = &mVoxelizationContext;

	static Ogre::Camera mShadowCamera("", nullptr);

	mLightView = Ogre::Math::makeLookAtRH(
		Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Vector3(-0.191f, -1.0f, -0.574f), Ogre::Vector3::UNIT_Y);

	mShadowCamera.updateViewMatrix(mLightView);

	
	uint32_t size = 256;
	Real left = -256 / 2.0f;
	Real right = 256 / 2.0f;
	Real top = 256 / 2.0f;
	Real bottom = -256 / 2.0f;

	mLightProject = Ogre::Math::makeOrthoRH(left, right, bottom, top, -256, 256);
	mShadowCamera.updateProjectMatrix(mLightProject);

	Ogre::Camera* lightCam = &mShadowCamera;

	BufferDesc desc{};
	desc.mBindingType = BufferObjectBinding_Uniform;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = 0;
	desc.mSize = sizeof(mFrameConstantBuffer);
	Handle<HwBufferObject> zeroFrameBufferHandle = mRenderSystem->createBufferObject(desc);
	Handle<HwBufferObject> firstFrameBufferHandle = mRenderSystem->createBufferObject(desc);

	static UserDefineShader userDefineShader;
	userDefineShader.initCallback = std::bind(
		&VoxelConeTracingApp::initFrameResource, this, std::placeholders::_1, std::placeholders::_2);
	RenderableBindCallback bindCallback = [=, this](uint32_t frameIndex, Renderable* r) {
			if (r->hasFlag(shadowPassBit + frameIndex))
			{
				return;
			}
			r->setFlag(shadowPassBit + frameIndex, true);
			DescriptorData descriptorData;
			Handle<HwBufferObject> tmp[2];
			tmp[0] = zeroFrameBufferHandle;
			tmp[1] = firstFrameBufferHandle;

			descriptorData.mCount = 1;
			descriptorData.pName = "cbPass";
			descriptorData.ppBuffers = &tmp[frameIndex];
			FrameResourceInfo* resourceInfo = (FrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
			mRenderSystem->updateDescriptorSet(resourceInfo->zeroShadowSet, 1, &descriptorData);
		};
	userDefineShader.bindCallback = bindCallback;
	RenderableDrawCallback drawCallback = [=, this](uint32_t frameIndex, Renderable* r) {
		void* frameData = r->getFrameResourceInfo(frameIndex);
		VctFrameResourceInfo* resourceInfo = (VctFrameResourceInfo*)frameData;
		Ogre::Material* mat = r->getMaterial().get();

		mRenderSystem->bindPipeline(mShadowPipelineHandle, &resourceInfo->zeroShadowSet, 1);


		VertexData* vertexData = r->getVertexData();
		IndexData* indexData = r->getIndexData();
		vertexData->bind(nullptr);
		indexData->bind();
		IndexDataView* view = r->getIndexView();
		mRenderSystem->drawIndexed(view->mIndexCount, 1,
			view->mIndexLocation, view->mBaseVertexLocation, 0);
		};
	userDefineShader.drawCallback = drawCallback;

	UserDefineShader* pUserDefineShader = &userDefineShader;
	RenderPassCallback shadowPassCallback = [=, this](RenderPassInfo& info) {
		info.renderTargetCount = 0;
		info.depthTarget.depthStencil = mVoxelizationContext.depthTarget;
		info.depthTarget.clearValue = { 1.0f, 0.0f };
		info.passName = "vctShadowPass";
		mRenderSystem->pushGroupMarker("vctShadowPass");
		renderScene(lightCam, mSceneManager,
			info, pUserDefineShader);
		mRenderSystem->popGroupMarker();
		};

	FrameConstantBuffer* pFrameBuffer = &mFrameConstantBuffer;
	UpdatePassCallback updateCallback = [=, this](float delta) {
		uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		updateFrameData(lightCam, nullptr, *pFrameBuffer);
		mRenderSystem->updateBufferObject(
			frameIndex? firstFrameBufferHandle: zeroFrameBufferHandle,
			(const char*)pFrameBuffer, sizeof(mFrameConstantBuffer));
		};

	auto shadowPass = createUserDefineRenderPass(
		shadowPassCallback, updateCallback);
	mRenderPipeline->addRenderPass(shadowPass);
}

void VoxelConeTracingApp::voxelizationPass()
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	
	VoxelizationContext* context = &mVoxelizationContext;

	BufferDesc desc{};
	desc.mBindingType = BufferObjectBinding_Uniform;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = 0;
	desc.mSize = sizeof(VoxelizationBlock);
	Handle<HwBufferObject> zeroVoxelizationBlockHandle = mRenderSystem->createBufferObject(desc);
	Handle<HwBufferObject> firstVoxelizationBlockHandle = mRenderSystem->createBufferObject(desc);

	static UserDefineShader userDefineShader;
	userDefineShader.initCallback = std::bind(
		&VoxelConeTracingApp::initFrameResource, this, std::placeholders::_1, std::placeholders::_2);
	RenderableBindCallback bindCallback = [=, this](uint32_t frameIndex, Renderable* r) {
		if (r->hasFlag(voxelizationPassBit + frameIndex))
		{
			return;
		}
		r->setFlag(voxelizationPassBit + frameIndex, true);
		DescriptorData descriptorData;
		Handle<HwBufferObject> tmp[2];
		tmp[0] = zeroVoxelizationBlockHandle;
		tmp[1] = firstVoxelizationBlockHandle;

		descriptorData.mCount = 1;
		descriptorData.pName = "VoxelizationCB";
		descriptorData.ppBuffers = &tmp[frameIndex];
		VctFrameResourceInfo* resourceInfo = (VctFrameResourceInfo*)r->getFrameResourceInfo(frameIndex);
		mRenderSystem->updateDescriptorSet(resourceInfo->zeroSetOfVoxelization, 1, &descriptorData);
		};
	userDefineShader.bindCallback = bindCallback;
	RenderableDrawCallback drawCallback = [=, this](uint32_t frameIndex, Renderable* r) {
		void* frameData = r->getFrameResourceInfo(frameIndex);
		VctFrameResourceInfo* resourceInfo = (VctFrameResourceInfo*)frameData;
		Ogre::Material* mat = r->getMaterial().get();

		mRenderSystem->bindPipeline(mVoxellizationPipelineHandle, 
			&resourceInfo->zeroSetOfVoxelization, 1);


		VertexData* vertexData = r->getVertexData();
		IndexData* indexData = r->getIndexData();
		vertexData->bind(nullptr);
		indexData->bind();
		IndexDataView* view = r->getIndexView();
		mRenderSystem->drawIndexed(view->mIndexCount, 1,
			view->mIndexLocation, view->mBaseVertexLocation, 0);
		};
	userDefineShader.drawCallback = drawCallback;

	UserDefineShader* pUserDefineShader = &userDefineShader;
	RenderPassCallback voxelizationPassCallback = [=, this](RenderPassInfo& info) {
		VoxelizationContext* context = &this->mVoxelizationContext;
		info.renderTargetCount = 0;
		info.depthTarget.depthStencil = nullptr;
		info.depthTarget.clearValue = { 1.0f, 0.0f };
		info.passName = "VoxelizationPass";
		info.extent[0] = VCT_SCENE_VOLUME_SIZE;
		info.extent[1] = VCT_SCENE_VOLUME_SIZE;
		RenderTargetBarrier rtBarriers[] =
		{
			{
				 context->depthTarget,
				RESOURCE_STATE_DEPTH_WRITE,
				RESOURCE_STATE_SHADER_RESOURCE
			}
		};
		mRenderSystem->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		mRenderSystem->pushGroupMarker("VoxelizationPass");
		mRenderSystem->clearRenderTarget(context->voxelizationTarget, Ogre::Vector4::ZERO);
		rtBarriers[0] = {
			context->voxelizationTarget,
			RESOURCE_STATE_UNORDERED_ACCESS,
			RESOURCE_STATE_UNORDERED_ACCESS
		};
		mRenderSystem->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		renderScene(mGameCamera->getCamera(), mSceneManager,
			info, pUserDefineShader);
		mRenderSystem->popGroupMarker();
		rtBarriers[0] = {
			context->depthTarget,
				RESOURCE_STATE_SHADER_RESOURCE,
				RESOURCE_STATE_DEPTH_WRITE
		};
		mRenderSystem->resourceBarrier(0, nullptr, 0, nullptr, 1, rtBarriers);
		};
	mVoxelizationBlock.worldVoxelScale = 128.0f;
	const Ogre::Matrix4& view = mGameCamera->getCamera()->getViewMatrix();
	const Ogre::Matrix4& proj = mGameCamera->getCamera()->getProjectMatrix();
	mVoxelizationBlock.viewProjection = (proj * view).transpose();

	auto translate = Ogre::Math::makeTranslateMatrix(
		Ogre::Vector3(-VCT_SCENE_VOLUME_SIZE * 0.25f, 
			-VCT_SCENE_VOLUME_SIZE * 0.25f, 
			-VCT_SCENE_VOLUME_SIZE * 0.25f));
	auto scale = Ogre::Math::makeScaleMatrix(Ogre::Vector3(1.0f, -1.0f, 1.0f));
	mVoxelizationBlock.worldVoxelCube = (scale * translate).transpose();
	mVoxelizationBlock.shadowViewProjection = (mLightProject * mLightView).transpose();
	mRenderSystem->updateBufferObject(
		 zeroVoxelizationBlockHandle, (const char*)&mVoxelizationBlock, sizeof(VoxelizationBlock));
	mRenderSystem->updateBufferObject(
		firstVoxelizationBlockHandle, (const char*)&mVoxelizationBlock, sizeof(VoxelizationBlock));
	UpdatePassCallback updateCallback = [=, this](float delta) {
		uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		};

	auto voxelizationPass = createUserDefineRenderPass(
		voxelizationPassCallback, updateCallback);
	mRenderPipeline->addRenderPass(voxelizationPass);
}

void VoxelConeTracingApp::computePass()
{
	
}

void VoxelConeTracingApp::initScene()
{
	Ogre::Matrix4 m;
	Ogre::Vector3 pos;
	/*if (0)
	{
		m = Ogre::Math::makeRotateMatrix(-90, Ogre::Vector3::UNIT_X);
		addEntry("room", "room.fbx", Ogre::Vector3::ZERO, m, Ogre::Vector4(0.7, 0.7, 0.7, 0.0));
		addEntry("dragon", "dragon.fbx", Ogre::Vector3(1.5f, 0.0f, -7.0f),
			Ogre::Matrix4::IDENTITY, Ogre::Vector4(0.044f, 0.627f, 0, 0.0));
		m = Ogre::Math::makeRotateMatrix(-0.3752457f / Ogre::Math::PI * 180, Ogre::Vector3::UNIT_Y);
		addEntry("bunny", "bunny.fbx", Ogre::Vector3(21.0f, 13.9f, -19.0f),
			m, Ogre::Vector4(0.8f, 0.71f, 0, 0.0));
		m = Ogre::Math::makeRotateMatrix(-90, Ogre::Vector3::UNIT_X);
		m = m * Ogre::Math::makeRotateMatrix(1.099557f / Ogre::Math::PI * 180, Ogre::Vector3::UNIT_X);
		addEntry("torus", "torus.fbx", Ogre::Vector3(21.0f, 4.0f, -9.6f), m, Ogre::Vector4(0.329f, 0.26f, 0.8f, 0.8f));
		addEntry("sphere_big", "sphere_big.fbx", Ogre::Vector3(-17.25f, -1.15f, -24.15f),
			Ogre::Matrix4::IDENTITY, Ogre::Vector4(0.692f, 0.215f, 0.0f, 0.6f));
		addEntry("sphere_medium", "sphere_medium.fbx", Ogre::Vector3(-21.0f, -0.95f, -13.20f),
			Ogre::Matrix4::IDENTITY, Ogre::Vector4(0.005, 0.8, 0.426, 0.7f));
		addEntry("sphere_small", "sphere_small.fbx", Ogre::Vector3(-11.25f, -0.45f, -16.20f),
			Ogre::Matrix4::IDENTITY, Ogre::Vector4(0.01, 0.0, 0.8, 0.75f));
		m = Ogre::Math::makeRotateMatrix(-90, Ogre::Vector3::UNIT_X);
		addEntry("block", "block.fbx", Ogre::Vector3(3.0f, 8.0f, -30.0f), m, Ogre::Vector4(0.9, 0.15, 1.0, 0.0));
		m = Ogre::Math::makeRotateMatrix(-0.907571f / Ogre::Math::PI * 180, Ogre::Vector3::UNIT_Y) * m;
		addEntry("cube", "cube.fbx", Ogre::Vector3(21.0f, 5.0f, -19.0f), m, Ogre::Vector4(0.1, 0.75, 0.8, 0.0));
	}*/
	

	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	TextureProperty texProperty;
	texProperty._width = ogreConfig.width;
	texProperty._height = ogreConfig.height;
	texProperty._tex_format = Ogre::PixelFormat::PF_A8R8G8B8;
	texProperty._tex_usage = Ogre::TextureUsage::COLOR_ATTACHMENT;
	texProperty._need_mipmap = false;
	mVoxelizationContext.diffuseTarget = mRenderSystem->createRenderTarget("albedoTarget", texProperty);
	mVoxelizationContext.normalTarget = mRenderSystem->createRenderTarget("normalTarget", texProperty);
	mVoxelizationContext.specularTarget = mRenderSystem->createRenderTarget("specularTarget", texProperty);
	mVoxelizationContext.emissiveTarget = mRenderSystem->createRenderTarget("emissiveTarget", texProperty);
	texProperty._width = 2048;
	texProperty._height = 2048;
	texProperty._tex_format = Ogre::PixelFormat::PF_DEPTH32F;
	texProperty._tex_usage = Ogre::TextureUsage::DEPTH_ATTACHMENT;
	mVoxelizationContext.depthTarget = mRenderSystem->createRenderTarget(
		"depthTarget", texProperty);

	ShaderInfo shaderInfo;
	shaderInfo.shaderName = "sceneGeometryPass";
	VertexDeclaration decl;
	decl.addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
	decl.addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
	decl.addElement(0, 0, 24, VET_FLOAT3, VES_TANGENT);
	decl.addElement(0, 0, 36, VET_FLOAT3, VES_BINORMAL);
	decl.addElement(0, 0, 48, VET_FLOAT2, VES_TEXTURE_COORDINATES);
	mSceneGeometryProgramHandle = mRenderSystem->createShaderProgram(shaderInfo, &decl);
	backend::RasterState rasterState{};
	rasterState.depthBiasConstantFactor = 0.0f;
	rasterState.depthBiasSlopeFactor = 0.0f;
	auto targetCount = 4;
	rasterState.depthFunc = SamplerCompareFunc::LE;
	rasterState.renderTargetCount = targetCount;
	rasterState.depthWrite = true;
	rasterState.depthTest = true;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	rasterState.pixelFormat[1] = Ogre::PixelFormat::PF_A8R8G8B8;
	rasterState.pixelFormat[2] = Ogre::PixelFormat::PF_A8R8G8B8;
	rasterState.pixelFormat[3] = Ogre::PixelFormat::PF_A8R8G8B8;
	mSceneGeometryPipelineHandle = mRenderSystem->createPipeline(rasterState, mSceneGeometryProgramHandle);

	auto swapBufferCount = ogreConfig.swapBufferCount;

	mFrameDatas.resize(swapBufferCount);

	Ogre::DescriptorData descriptorData[16];


	

	//
	shaderInfo.shaderName = "vctShadowPass";

	mShadowProgramHandle = mRenderSystem->createShaderProgram(shaderInfo, &decl);

	rasterState.depthFunc = SamplerCompareFunc::LE;
	rasterState.renderTargetCount = 0;
	rasterState.depthWrite = true;
	rasterState.depthTest = true;
	rasterState.depthBiasSlopeFactor = 10.0f;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	mShadowPipelineHandle = mRenderSystem->createPipeline(rasterState, mShadowProgramHandle);
	rasterState.depthBiasSlopeFactor = 0.0f;
	//
	texProperty._texType = TEX_TYPE_3D;
	texProperty._width = 256;
	texProperty._height = 256;
	texProperty._depth = 256;
	texProperty._tex_format = Ogre::PixelFormat::PF_A8B8G8R8;
	texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
	texProperty._need_mipmap = false;
	mVoxelizationContext.voxelizationTarget = mRenderSystem->createRenderTarget("voxelizationTarget", texProperty);

	shaderInfo.shaderName = "voxelizationPass";
	mVoxellizationProgramHandle = mRenderSystem->createShaderProgram(shaderInfo, &decl);
	rasterState.depthFunc = SamplerCompareFunc::A;
	rasterState.renderTargetCount = 0;
	rasterState.depthWrite = false;
	rasterState.depthTest = false;
	rasterState.pixelFormat[0] = Ogre::PixelFormat::PF_A8R8G8B8;
	mVoxellizationPipelineHandle = mRenderSystem->createPipeline(rasterState, mVoxellizationProgramHandle);

	backend::SamplerParams params;
	params.filterMag = backend::SamplerFilterType::LINEAR;
	params.filterMin = backend::SamplerFilterType::LINEAR;
	params.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_NEAREST;
	params.wrapS = backend::SamplerWrapMode::CLAMP_TO_BODY;
	params.wrapT = backend::SamplerWrapMode::CLAMP_TO_BODY;
	params.wrapR = backend::SamplerWrapMode::REPEAT;
	params.compareMode = backend::SamplerCompareMode::COMPARE_TO_TEXTURE;
	params.compareFunc = backend::SamplerCompareFunc::LE;
	params.anisotropyLog2 = 4;
	params.padding0 = 0;
	params.padding1 = 0;
	params.padding2 = 0;
	Handle<HwSampler>samplerHandle = mRenderSystem->createTextureSampler(params);
	mVoxelizationContext.voxelizationSampler = samplerHandle;
	
	
	//
	/*shaderInfo.shaderName = "tracingConePass";
	mTracingConeHandle = mRenderSystem->createComputeProgram(shaderInfo);*/

	float ratio = 0.8f;

	texProperty._texType = TEX_TYPE_2D;
	texProperty._width = 960.0f;
	texProperty._height = 540.0f;
	texProperty._depth = 1;
	texProperty._tex_format = Ogre::PixelFormat::PF_A8R8G8B8;
	texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
	texProperty._need_mipmap = false;
	mVoxelizationContext.tracingResultTarget = mRenderSystem->createRenderTarget("tracingResult", texProperty);

	params.filterMag = backend::SamplerFilterType::LINEAR;
	params.filterMin = backend::SamplerFilterType::LINEAR;
	params.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	params.wrapS = backend::SamplerWrapMode::CLAMP_TO_EDGE;
	params.wrapT = backend::SamplerWrapMode::CLAMP_TO_EDGE;
	params.wrapR = backend::SamplerWrapMode::CLAMP_TO_EDGE;
	params.compareMode = backend::SamplerCompareMode::COMPARE_TO_TEXTURE;
	params.compareFunc = backend::SamplerCompareFunc::LE;
	params.anisotropyLog2 = 4;
	params.padding0 = 0;
	params.padding1 = 0;
	params.padding2 = 0;
	mVoxelizationContext.tracingSampler = mRenderSystem->createTextureSampler(params);

	texProperty._texType = TEX_TYPE_3D;
	texProperty._width = 128;
	texProperty._height = 128;
	texProperty._depth = 128;
	texProperty._tex_format = Ogre::PixelFormat::PF_A8R8G8B8;
	texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
	texProperty._need_mipmap = true;
}

void VoxelConeTracingApp::addEntry(
	const std::string& entryName,
	const std::string& meshName,
	const Ogre::Vector3& position,
	const Ogre::Matrix4& rotate,
	const Ogre::Vector4& color
)
{
	auto mesh = MeshManager::getSingletonPtr()->load(meshName);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* entry = mSceneManager->createEntity(entryName, meshName);
	SceneNode* node = root->createChildSceneNode(entryName);

	node->setPosition(position);
	Ogre::Quaternion q = rotate.extractQuaternion();
	
	node->setOrientation(q);
	entry->setColor(color);
	node->attachObject(entry);

	SubEntity* subEntity = entry->getSubEntity(0);

	const auto& modelMatrix  = subEntity->getModelMatrix();

	int kk = 0;
}

void VoxelConeTracingApp::initFrameResource(uint32_t frameIndex, Renderable* r)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	auto* rs = Ogre::Root::getSingleton().getRenderSystem();
	if (1)
	{
		VctFrameResourceInfo* resourceInfo = new VctFrameResourceInfo;
		resourceInfo->update = false;

		r->updateFrameResource(frameIndex, (void*)resourceInfo);

		BufferDesc desc{};
		desc.mBindingType = BufferObjectBinding_Uniform;
		desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
		desc.bufferCreationFlags = 0;
		desc.mSize = sizeof(ObjectConstantBuffer);
		Handle<HwBufferObject> objectBufferHandle =
			rs->createBufferObject(desc);
		resourceInfo->modelObjectHandle = objectBufferHandle;

		Ogre::Material* mat = r->getMaterial().get();
		Handle<HwBufferObject> matBufferHandle;
		desc.mBindingType = BufferObjectBinding_Uniform;
		desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
		desc.bufferCreationFlags = 0;
		desc.mSize = sizeof(ObjMaterialBlock);
		matBufferHandle = rs->createBufferObject(desc);
		ObjMaterialBlock matBlock;
		memset(&matBlock, 0, sizeof(matBlock));

		matBlock.u_hasDiffuseTexture = mat->hasTextureUnit(DIFFUSE_TEXTURE);
		matBlock.u_hasNormalMap = mat->hasTextureUnit(NORMAL_TEXTURE);
		matBlock.u_hasSpecularMap = mat->hasTextureUnit(SPECULAR_TEXTURE);
		matBlock.u_hasOpacityMap = mat->hasTextureUnit(OPACITY_TEXTURE);
		matBlock.u_hasEmissionMap = mat->hasTextureUnit(EMISSIVE_TEXTURE);
		matBlock.u_shininess = mat->getShininess();
		matBlock.emissionColor = mat->getEmissiveColor();
		matBlock.specularColor = mat->getSpecularColor();
		matBlock.color = mat->getDiffuseColor();
		rs->updateBufferObject(matBufferHandle, (const char*)&matBlock, sizeof(ObjMaterialBlock));

		resourceInfo->matObjectHandle = matBufferHandle;	
		resourceInfo->sceneGeometryZeroSet = rs->createDescriptorSet(mSceneGeometryProgramHandle, 0);
		resourceInfo->sceneGeometryFirstSet = rs->createDescriptorSet(mSceneGeometryProgramHandle, 1);
		resourceInfo->zeroShadowSet = rs->createDescriptorSet(mShadowProgramHandle, 0);
		resourceInfo->zeroSetOfVoxelization = rs->createDescriptorSet(mVoxellizationProgramHandle, 0);
		DescriptorData descriptorData[256];
		uint32_t descriptorCount = 0;
		descriptorData[0].pName = "cbPerObject";
		descriptorData[0].mCount = 1;
		descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[0].ppBuffers = &objectBufferHandle;
		
		descriptorData[1].pName = "objMaterial";
		descriptorData[1].mCount = 1;
		descriptorData[1].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[1].ppBuffers = &matBufferHandle;
		

		rs->updateDescriptorSet(resourceInfo->sceneGeometryZeroSet, 2, descriptorData);

		//
		descriptorData[0].pName = "cbPerObject";
		descriptorData[0].mCount = 1;
		descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[0].ppBuffers = &objectBufferHandle;

		Ogre::OgreTexture* voxelizationTexture = mVoxelizationContext.voxelizationTarget->getTarget();

		descriptorData[1].pName = "outputTexture";
		descriptorData[1].mCount = 1;
		descriptorData[1].mLevel = 0;
		descriptorData[1].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
		descriptorData[1].ppTextures = (const OgreTexture**)& voxelizationTexture;

		Ogre::OgreTexture* shadowTexture = mVoxelizationContext.depthTarget->getTarget();

		descriptorData[2].pName = "shadowBuffer";
		descriptorData[2].mCount = 1;
		descriptorData[2].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
		descriptorData[2].ppTextures = (const OgreTexture**)& shadowTexture;

		descriptorData[3].pName = "PcfShadowMapSampler";
		descriptorData[3].mCount = 1;
		descriptorData[3].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
		descriptorData[3].ppSamplers = &mVoxelizationContext.voxelizationSampler;

		rs->updateDescriptorSet(resourceInfo->zeroSetOfVoxelization, 4, descriptorData);

		//update texture
		uint32_t index = 0;
		descriptorCount = 0;

		std::vector<std::shared_ptr<TextureUnit>>& texs = mat->getAllTexureUnit();
		
		OgreTexture* texArray[9];
		uint32_t texIndex = 0;

		struct TexResource
		{
			const char* texname;
			const char* shader_texname;
			const char* shader_samplername;
		};

		std::vector<TexResource> texResources =
		{
			{
				"diffuse_texture",
				"diffuse_tex",
				"diffuseSampler"
            },
			{
				"normal_texture",
				"normal_tex",
				"normalSampler"
			},
			{
				"specular_texture",
				"specular_tex",
				"specularSampler"
			},
			{
				"emissive_texture",
				"emissive_tex",
				"emissiveSampler"
			},
			{
				"opacity_texture",
				"opacity_tex",
				"opacitySampler"
			}
		};
		std::shared_ptr<OgreTexture> defaultTex = Ogre::TextureManager::getSingleton().getByName("white1x1.dds");
		for (uint32_t i = 0; i < 5; i++)
		{
			TexResource& texResource = texResources[i];
			std::shared_ptr<TextureUnit>& tu = mat->getTextureUnit(texResource.texname);
			OgreTexture* tex = defaultTex.get();
			if (tu)
			{
				tex = tu->getRaw();
			}
			
			texArray[texIndex] = tex;
			descriptorData[descriptorCount].pName = texResource.shader_texname;
			descriptorData[descriptorCount].mCount = 1;
			descriptorData[descriptorCount].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
			descriptorData[descriptorCount].ppTextures = (const OgreTexture**)&texArray[texIndex];
			descriptorCount++;

			descriptorData[descriptorCount].pName = texResource.shader_samplername;
			descriptorData[descriptorCount].mCount = 1;
			descriptorData[descriptorCount].descriptorType = DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
			descriptorData[descriptorCount].ppTextures = (const OgreTexture**)&texArray[texIndex];
			descriptorCount++;

			texIndex++;
			

		}
		
		
		
		rs->updateDescriptorSet(resourceInfo->sceneGeometryFirstSet, descriptorCount, descriptorData);
	}
}




