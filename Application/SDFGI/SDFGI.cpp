#include "OgreHeader.h"
#include "SDFGI.h"
#include "OgreParticleSystem.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
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
#include "renderUtil.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GBuffer.h"
#include "DDGI.h"
#include "Composite.h"
#include "presentPass.h"


void addMacro(RaytracingShaderInfo& shaderInfo, std::string first, std::string second)
{
	shaderInfo.shaderMacros.push_back(std::pair<std::string, std::string>(first, second));
}

void addMacro(ShaderInfo& shaderInfo, std::string first, std::string second)
{
	shaderInfo.shaderMacros.push_back(std::pair<std::string, std::string>(first, second));
}

SDFGIApp::SDFGIApp()
{

}

SDFGIApp::~SDFGIApp()
{

}

void SDFGIApp::setup(
	RenderPipeline* renderPipeline,
	RenderContext& context,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	mRenderPipeline = renderPipeline;
	mGameCamera   = gameCamera;
	mSceneManager = sceneManager;
	mRenderWindow = renderWindow;
	mRenderSystem = Ogre::Root::getSingleton().getRenderSystem();

	ResourceInfo* res = ResourceManager::getSingleton().getResourceInfo("sponza.ini");
	mContext.mConfig.app.filepath = res->_fullname.c_str();
	std::ofstream log;
	Configs::Load(mContext.mConfig, log);
	float h = 1.0f;
	const Configs::Camera& cam = mContext.mConfig.scene.cameras[0];
	Ogre::Vector3 camPos = cam.position;

	Ogre::Matrix4 m3 = Ogre::Math::yawPitchRoll(
		-cam.yaw * Ogre::Math::PI / 180.0f, -cam.pitch * Ogre::Math::PI / 180.0f, 0.0f);
	auto forward = m3.getForward();
	Ogre::Vector3 targetPos = forward + camPos;
	mGameCamera->lookAt(camPos, targetPos);

	float aspect = ogreConfig.width / (float)ogreConfig.height;
	Ogre::Matrix4 m = Ogre::Math::makePerspectiveMatrix(
		Ogre::Math::PI / 3.0f, aspect, 0.1, 5000);

	gameCamera->getCamera()->updateProjectMatrix(m);
	gameCamera->setMoveSpeed(10.0f);
	gameCamera->setCameraType(CameraMoveType_FirstPerson);
	initScene(context);
	initResource(context);
	addPass(context);
	
}

void SDFGIApp::update(float delta)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

	uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
	SDFGICameraInfo& cameraInfo = mContext.mSDFGICameraInfo;
	cameraInfo.resolution.x = ogreConfig.width;
	cameraInfo.resolution.y = ogreConfig.height;
	cameraInfo.aspect = cameraInfo.resolution.x / cameraInfo.resolution.y;
	cameraInfo.fov = 60;
	cameraInfo.tanHalfFovY = std::tan(cameraInfo.fov * (Ogre::Math::PI / 180.f) * 0.5f);

	const Ogre::Matrix4& view = mGameCamera->getCamera()->getViewMatrix();

	cameraInfo.up = view.getUp();
	cameraInfo.right = -view.getRight();
	cameraInfo.forward = view.getForward();

	cameraInfo.position = mGameCamera->getCamera()->getDerivedPosition();
	mRenderSystem->updateBufferObject(mContext.mCameraBufferHandle,
		(const char*)&cameraInfo, sizeof(cameraInfo), frameIndex * SDFGICameraInfo::GetAlignedSizeInBytes());

	GlobalConstants& globalConstants = mContext.mGlobalConstants;
	globalConstants.app.frameNumber = Ogre::Root::getSingleton().getCurrentFrame();
	
	mContext.mGlobalConstants.composite.useFlags = COMPOSITE_FLAG_USE_DDGI;
	mContext.mGlobalConstants.post.useFlags =
		POSTPROCESS_FLAG_USE_EXPOSURE |
		POSTPROCESS_FLAG_USE_TONEMAPPING |
		POSTPROCESS_FLAG_USE_GAMMA;
	mRenderSystem->updateBufferObject(mContext.mGlobalConstHandle,
		(const char*)&globalConstants, sizeof(globalConstants),
		frameIndex * globalConstants.GetAlignedSizeInBytes());
}

void SDFGIApp::initScene(RenderContext& context)
{
	std::string name = "Sponza.gltf";
	std::shared_ptr<Mesh> mesh = MeshManager::getSingletonPtr()->load(name);
	Entity* entity = mSceneManager->createEntity(name, name);
	auto rootNode = mSceneManager->getRoot();
	SceneNode* gltfNode = rootNode->createChildSceneNode(name);
	gltfNode->attachObject(entity);

	AccelerationStructureDesc         asDesc = {};
	AccelerationStructureGeometryDesc geomDescs[128] = {};

	uint32_t subEntityCount = entity->getNumSubEntities();
	//subEntityCount = 1;
	std::vector<TransformMatrix> transformMatrices;
	transformMatrices.reserve(subEntityCount);

	uint32_t transformSize = sizeof(TransformMatrix) * subEntityCount;
	BufferDesc desc{};
	desc.mBindingType = BufferObjectBinding_Storge;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
		BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mSize = transformSize;
	desc.mElementCount = subEntityCount;
	desc.mStructStride = sizeof(TransformMatrix);
	Handle< HwBufferObject> transformBufferHandle = mRenderSystem->createBufferObject(desc);

	auto& js = ResourceManager::getSingleton().getJobSystem();
	utils::JobSystem::Job* rootJob = js.createJob();

	for (uint32_t i = 0; i < subEntityCount; i++)
	{
		SubEntity* subEntity = entity->getSubEntity(i);
		auto& mat = subEntity->getMaterial();
		mat->load(rootJob);
	}

	js.runAndWait(rootJob);
	
	mContext.geometryNodes.resize(subEntityCount);
	mContext.materialList.resize(subEntityCount);
	mContext.mIndexBufferList.resize(subEntityCount);
	mContext.mVertexBufferList.resize(subEntityCount);

	for (uint32_t i = 0; i < subEntityCount; i++)
	{
		SubEntity* subEntity = entity->getSubEntity(i);
		VertexData* vertexData = subEntity->getVertexData();
		IndexData* indexData = subEntity->getIndexData();

		mContext.mIndexBufferList[i] = indexData->getHandle();
		mContext.mVertexBufferList[i] = vertexData->getBuffer(0);
		auto& mat = subEntity->getMaterial();
		PbrMaterialConstanceBuffer& pbrConstance = mat->getPbrMatInfo();

		auto materialFlag = mat->getMaterialFlags();

		auto& matInfo = mContext.materialList[i];
		matInfo.albedo = Ogre::Vector3(pbrConstance.baseColorFactor.ptr());
		matInfo.opacity = pbrConstance.baseColorFactor[3];
		matInfo.roughness = pbrConstance.metallicRoughnessValues[1];
		matInfo.metallic = pbrConstance.metallicRoughnessValues[0];
		matInfo.alphaCutoff = pbrConstance.alphaMaskCutoff;
		matInfo.alphaMode = pbrConstance.alphaMode;

		const Ogre::Matrix4& subMatrix = subEntity->getModelMatrix();
		TransformMatrix transformMatrix;

		memcpy(&transformMatrix, (void*)&subMatrix, sizeof(transformMatrix));
		transformMatrices.push_back(transformMatrix);
		geomDescs[i].mFlags = (matInfo.alphaMode == 0)
			? ACCELERATION_STRUCTURE_GEOMETRY_FLAG_OPAQUE
			:ACCELERATION_STRUCTURE_GEOMETRY_FLAG_NO_DUPLICATE_ANYHIT_INVOCATION ;
		IndexDataView* indexView = subEntity->getIndexView();
		geomDescs[i].vertexBufferHandle = vertexData->getBuffer(0);
		geomDescs[i].mVertexCount = (uint32_t)vertexData->getVertexCount();
		uint32_t stride = vertexData->getVertexSize(0);
		geomDescs[i].mVertexStride = stride;
		geomDescs[i].mVertexOffset = indexView->mBaseVertexLocation * stride;
		geomDescs[i].mVertexElementType = VertexElementType::VET_FLOAT3;
		geomDescs[i].indexBufferHandle = indexData->getHandle();
		geomDescs[i].transformBufferHandle = transformBufferHandle;
		uint32_t indexSize = indexData->getIndexSize();
		geomDescs[i].mIndexCount = indexView->mIndexCount;
		geomDescs[i].mIndexOffset = indexView->mIndexLocation * indexSize;
		geomDescs[i].mIndexType = indexSize == 2 ? INDEX_TYPE_UINT16 : INDEX_TYPE_UINT32;

		int baseColorIndex = -1;
		int occlusionIndex = -1;
		auto* baseColorTexture = mat->getPbrTexture(TextureTypePbr_Albedo);
		if (baseColorTexture)
		{
			matInfo.albedoTexIdx = mContext.sceneTextureList.size();
			mContext.sceneTextureList.push_back(baseColorTexture);
		}
		else
		{
			matInfo.albedoTexIdx = -1;
		}

		auto* normalTexture = mat->getPbrTexture(TextureTypePbr_NormalMap);

		if (normalTexture)
		{
			matInfo.normalTexIdx = mContext.sceneTextureList.size();
			mContext.sceneTextureList.push_back(normalTexture);
		}
		else
		{
			matInfo.normalTexIdx = -1;
		}

		auto* metalRoughnessTexture = mat->getPbrTexture(TextureTypePbr_MetalRoughness);

		if (metalRoughnessTexture)
		{
			matInfo.roughnessMetallicTexIdx = mContext.sceneTextureList.size();
			mContext.sceneTextureList.push_back(metalRoughnessTexture);
		}
		else
		{
			matInfo.roughnessMetallicTexIdx = -1;
		}

		auto* emissiveTexture = mat->getPbrTexture(TextureTypePbr_Emissive);

		if (emissiveTexture)
		{
			matInfo.emissiveTexIdx = mContext.sceneTextureList.size();
			mContext.sceneTextureList.push_back(emissiveTexture);
		}
		else
		{
			matInfo.emissiveTexIdx = -1;
		}

		GeometryData& geometryNode = mContext.geometryNodes[i];
		geometryNode.vertexOffset = indexView->mBaseVertexLocation;
		geometryNode.indexOffset = indexView->mIndexLocation;
		geometryNode.m = subMatrix.transpose();
	}


	desc.mBindingType = BufferObjectBinding_Storge;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mElementCount = subEntityCount;
	desc.mStructStride = sizeof(GeometryData);
	desc.mSize = desc.mElementCount * desc.mStructStride;
	mContext.geometryBufferHandle = mRenderSystem->createBufferObject(desc);

	mRenderSystem->updateBufferObject(
		mContext.geometryBufferHandle, (const char*)mContext.geometryNodes.data(), desc.mSize);

	mRenderSystem->updateBufferObject(transformBufferHandle,
		(const char*)transformMatrices.data(), transformSize);

	AccelerationStructure* pBottomAS = nullptr;
	AccelerationStructure* pTopAS = nullptr;


	asDesc.mBottom.mDescCount = subEntityCount;
	asDesc.mBottom.pGeometryDescs = geomDescs;
	asDesc.mType = ACCELERATION_STRUCTURE_TYPE_BOTTOM;
	asDesc.mFlags = ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;

	mRenderSystem->addAccelerationStructure(&asDesc, &pBottomAS);

	TransformMatrix transformMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f };

	AccelerationStructureInstanceDesc instanceDesc = {};
	instanceDesc.mFlags = ACCELERATION_STRUCTURE_INSTANCE_FLAG_NONE;
	instanceDesc.mInstanceContributionToHitGroupIndex = 0;
	instanceDesc.mInstanceID = 0;
	instanceDesc.mInstanceMask = 1;
	memcpy(instanceDesc.mTransform, &transformMatrix, sizeof(float[12]));
	instanceDesc.pBottomAS = pBottomAS;


	mRenderSystem->beginCmd();
	asDesc = {};
	asDesc.mType = ACCELERATION_STRUCTURE_TYPE_TOP;
	asDesc.mFlags = ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE;
	asDesc.mTop.mDescCount = 1;
	asDesc.mTop.pInstanceDescs = &instanceDesc;

	mRenderSystem->addAccelerationStructure(&asDesc, &pTopAS);

	// Build Acceleration Structures
	RaytracingBuildASDesc buildASDesc = {};
	buildASDesc.pAccelerationStructure = pBottomAS;
	buildASDesc.mIssueRWBarrier = true;
	mRenderSystem->buildAccelerationStructure(&buildASDesc);


	buildASDesc = {};
	buildASDesc.pAccelerationStructure = pTopAS;

	mRenderSystem->buildAccelerationStructure(&buildASDesc);
	mRenderSystem->flushCmd(context.cqh, true);
	mRenderSystem->removeAccelerationStructureScratch(pBottomAS);
	mRenderSystem->removeAccelerationStructureScratch(pTopAS);

	mContext.pTopAS = pTopAS;
	mContext.pBottomAS = pBottomAS;
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	mContext.frameCount = ogreConfig.swapBufferCount;
}

void SDFGIApp::initResource(RenderContext& context)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	backend::SamplerParams samplerParams{};
	samplerParams.wrapS = SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.wrapT = SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.wrapR = SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.filterMag = SamplerFilterType::LINEAR;
	samplerParams.filterMin = SamplerFilterType::LINEAR;
	samplerParams.mipMapMode = SamplerMipMapMode::MIPMAP_MODE_NEAREST;
	samplerParams.compareMode = SamplerCompareMode::NONE;
	samplerParams.compareFunc = SamplerCompareFunc::COMPARE_OP_ALWAYS;
	samplerParams.anisotropyLog2 = 0;
	mContext.mSamplerHandle[0] = mRenderSystem->createTextureSampler(samplerParams);

	samplerParams.wrapS = SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
	samplerParams.wrapT = SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
	samplerParams.wrapR = SamplerWrapMode::SAMPLER_REPEAT_MODE_CLAMP_TO_EDGE;
	samplerParams.filterMag = SamplerFilterType::NEAREST;
	samplerParams.filterMin = SamplerFilterType::NEAREST;
	mContext.mSamplerHandle[1] = mRenderSystem->createTextureSampler(samplerParams);

	samplerParams.mipMapMode = SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	samplerParams.wrapS = SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.wrapT = SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.wrapR = SamplerWrapMode::SAMPLER_REPEAT_MODE_REPEAT;
	samplerParams.filterMag = SamplerFilterType::LINEAR;
	samplerParams.filterMin = SamplerFilterType::LINEAR;
	samplerParams.anisotropyLog2 = 4;
	mContext.mSamplerHandle[2] = mRenderSystem->createTextureSampler(samplerParams);


	BufferDesc desc{};
	desc.mBindingType = BufferObjectBinding_Uniform;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
		BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mStructStride = GlobalConstants::GetAlignedSizeInBytes();
	desc.mElementCount = mContext.frameCount;
	desc.mSize = desc.mStructStride * desc.mElementCount;
	mContext.mGlobalConstHandle = mRenderSystem->createBufferObject(desc);
	////
	 desc.mBindingType = BufferObjectBinding_Uniform;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
		BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mStructStride = DDGIRootConstants::GetAlignedSizeInBytes();
	desc.mElementCount = 1;
	desc.mSize = desc.mStructStride * desc.mElementCount;
	mContext.mDDGIHandle = mRenderSystem->createBufferObject(desc);

	DDGIRootConstants ddgiRootConstant;
	memset(&ddgiRootConstant, 0, sizeof(ddgiRootConstant));
	mRenderSystem->updateBufferObject(mContext.mDDGIHandle, (const char*)&ddgiRootConstant, sizeof(ddgiRootConstant));
	////
	desc.mBindingType = BufferObjectBinding_Uniform;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT | 
		BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mStructStride = SDFGICameraInfo::GetAlignedSizeInBytes();
	desc.mElementCount = mContext.frameCount;
	desc.mSize = desc.mStructStride * desc.mElementCount;
	mContext.mCameraBufferHandle = mRenderSystem->createBufferObject(desc);
	///
	
	///
	desc.mBindingType = BufferObjectBinding_Storge;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
		BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mStructStride = SDFDIMaterial::GetAlignedSizeInBytes();
	desc.mElementCount = mContext.materialList.size();
	desc.mSize = desc.mStructStride * desc.mElementCount;
	mContext.materialBufferHandle = mRenderSystem->createBufferObject(desc);
	mRenderSystem->updateBufferObject(mContext.materialBufferHandle,
		(const char*)mContext.materialList.data(), desc.mSize);

	TextureProperty texProperty;
	texProperty._width = ogreConfig.width;
	texProperty._height = ogreConfig.height;
	texProperty._depth = 1;
	texProperty._tex_format = PF_A8R8G8B8;
	texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT;
	texProperty._need_mipmap = false;
	mContext.mGBufferTargetA = mRenderSystem->createRenderTarget("targetA", texProperty);

	texProperty._tex_format = PF_FLOAT32_RGBA;
	mContext.mGBufferTargetB = mRenderSystem->createRenderTarget("targetB", texProperty);

	mContext.mGBufferTargetC = mRenderSystem->createRenderTarget("targetC", texProperty);

	mContext.mGBufferTargetD = mRenderSystem->createRenderTarget("targetD", texProperty);
	texProperty._tex_format = PF_FLOAT16_RGBA;
	mContext.mIndirectTarget = mRenderSystem->createRenderTarget("outputView", texProperty);

	RenderTargetBarrier rtBarriers[] =
	{
		{
			mContext.mGBufferTargetA,
			RESOURCE_STATE_UNDEFINED,
			RESOURCE_STATE_COMMON
		},
		{
			mContext.mGBufferTargetB,
			RESOURCE_STATE_UNDEFINED,
			RESOURCE_STATE_COMMON
		},
		{
			mContext.mGBufferTargetC,
			RESOURCE_STATE_UNDEFINED,
			RESOURCE_STATE_COMMON
		},
		{
			mContext.mGBufferTargetD,
			RESOURCE_STATE_UNDEFINED,
			RESOURCE_STATE_COMMON
		}
	};

	mRenderSystem->resourceBarrier(0, nullptr, 0, nullptr, 4, rtBarriers, &context.frameContext->cbh);

	GlobalConstants& globalConstants = mContext.mGlobalConstants;
	memset(&globalConstants, 0, sizeof(GlobalConstants));

	globalConstants.app.skyRadiance =
	{
		 0.1f, 0.1f, 0.1f
	};
	globalConstants.pt.rayNormalBias = 0.01f;
	globalConstants.lights.hasDirectionalLight = true;
	globalConstants.post.exposure = 2.0f;
	//lights
	mContext.mlights.emplace_back();
	SDFGILight& light = mContext.mlights.back();
	light.type = 0;
	light.direction = { 0.0, -1.0, 0.3};
	light.color = {1.0, 1.0, 1.0};
	light.power = 3.14;

	desc.mBindingType = BufferObjectBinding_Storge;
	desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
		BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
	desc.mStructStride = SDFGILight::GetAlignedSizeInBytes();
	desc.mElementCount = mContext.mlights.size();
	desc.mSize = desc.mStructStride * desc.mElementCount;
	mContext.mLightBufferHandle = mRenderSystem->createBufferObject(desc);

	mRenderSystem->updateBufferObject(mContext.mLightBufferHandle,
		(const char*)mContext.mlights.data(), desc.mSize);
}

void SDFGIApp::addPass(RenderContext& context)
{
	
	{
		GBuffer* pass = new GBuffer(mContext);
		pass->initialize();
	    mRenderPipeline->addRenderPass(pass);
	}

	{
		DDGIPass* pass = new DDGIPass(mContext);
		pass->initialize(context);
		mRenderPipeline->addRenderPass(pass);
	}

	

	/*Ogre::OgreTexture* source = mContext.mGBufferTargetD->getTarget();
	source = mContext.volumes[0]->GetProbeRayData();
	PassBase* presentPass = new PresentPass(source, mRenderWindow);
	presentPass->initialize();
	mRenderPipeline->addRenderPass(presentPass);*/
	
	PassBase* compositePass = new CompositePass(mRenderWindow, mContext);
	compositePass->initialize();
	mRenderPipeline->addRenderPass(compositePass);
}



