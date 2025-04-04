#include <OgreHeader.h>
#include "OgreCommon.h"
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
#include "SanMiguelMeshInfo.h"
#include "renderUtil.h"
#include "presentPass.h"

BasicApplication::BasicApplication()
{

}

BasicApplication::~BasicApplication()
{

}


void BasicApplication::setup(
	RenderPipeline* renderPipeline,
	RenderSystem* renderSystem,
	Ogre::RenderWindow* renderWindow,
	Ogre::SceneManager* sceneManager,
	GameCamera* gameCamera)
{
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	ogreConfig.reverseDepth = false;
	mSceneManager = sceneManager;
	mGameCamera = gameCamera;
	mRenderWindow = renderWindow;
	mRenderSystem = renderSystem;
	mRenderPipeline = renderPipeline;

	std::string dir = "D:\\godotProject\\Abandoned-Spaceship-Godot-Demo\\Models";
	Ogre::ResourceManager::getSingletonPtr()->addDirectory(dir, "", false);
	base1();
}

void BasicApplication::update(float delta)
{
}

void BasicApplication::base1()
{
	SDFMesh SDFMeshes[NUM_SDF_MESHES];
	SDFMeshes[0].pSubMeshesInfo = opaqueMeshInfos;
	SDFMeshes[0].numSubMeshesGroups = sizeof(opaqueMeshInfos) / sizeof(MeshInfo);

	SDFMeshes[1].pSubMeshesInfo = alphaTestedMeshInfos;
	SDFMeshes[1].pSubMeshesGroupsSizes = alphaTestedGroupSizes;
	SDFMeshes[1].pSubMeshesIndices = alphaTestedMeshIndices;
	SDFMeshes[1].numSubMeshesGroups = sizeof(alphaTestedGroupSizes) / sizeof(uint32_t);

	SDFMeshes[2].pSubMeshesInfo = flagsMeshInfos;
	SDFMeshes[2].numSubMeshesGroups = sizeof(flagsMeshInfos) / sizeof(MeshInfo);

	

	loadBakedSDFData(&SDFMeshes[0], 0, false, sdfVolumeInstances);
	loadBakedSDFData(&SDFMeshes[1], 1, false, sdfVolumeInstances);
	loadBakedSDFData(&SDFMeshes[2], 2, false, sdfVolumeInstances);
	
	Ogre::Vector3i atlasSize(
		SDF_VOLUME_TEXTURE_ATLAS_WIDTH,
		SDF_VOLUME_TEXTURE_ATLAS_HEIGHT,
		SDF_VOLUME_TEXTURE_ATLAS_DEPTH);
	pSDFVolumeTextureAtlas = new SDFVolumeTextureAtlas(atlasSize);
	
	initSDFVolumeTextureAtlasData();

	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	
	mGameCamera->lookAt(Ogre::Vector3(0, 0.0f, -3.f), Ogre::Vector3::ZERO);
	mGameCamera->setCameraType(Ogre::CameraMoveType_LookAt);
	mGameCamera->setMoveSpeed(50);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	Ogre::Matrix4 m;

	CameraInfo& cameraInfo = mGameCamera->getCameraInfo();

	cameraInfo.nearClip = 0.1f;
	cameraInfo.farClip = 1000.0f;
	cameraInfo.aspect = ogreConfig.width / (float)ogreConfig.height;
	cameraInfo.aspectInverse = ogreConfig.height / (float)ogreConfig.width;
	cameraInfo.fovRadians = Ogre::Math::PI / 3.0f;
	if (ogreConfig.reverseDepth)
	{
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			cameraInfo.fovRadians, cameraInfo.aspectInverse, cameraInfo.nearClip, cameraInfo.farClip);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			cameraInfo.fovRadians, cameraInfo.aspect, cameraInfo.nearClip, cameraInfo.farClip);

	}
	mGameCamera->getCamera()->updateProjectMatrix(m);

	ShaderInfo shaderInfo;

	shaderInfo.shaderName = "updateRegion3DTexture";
	mUpdateRegion3DTextureHandle =
		mRenderSystem->createComputeProgram(shaderInfo);
	shaderInfo.shaderName = "visualizeSDFMesh";
	mVisualizeSDFMeshHandle = 
		mRenderSystem->createComputeProgram(shaderInfo);
	uint32_t volumeBufferElementCount =
		SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_X * 
		SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Y * 
		SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Z;

	TextureProperty texProperty;
	texProperty._width = SDF_VOLUME_TEXTURE_ATLAS_WIDTH;
	texProperty._height = SDF_VOLUME_TEXTURE_ATLAS_HEIGHT;
	texProperty._depth = SDF_VOLUME_TEXTURE_ATLAS_DEPTH;
	texProperty._texType = TEX_TYPE_3D;
	texProperty._tex_format = Ogre::PixelFormat::PF_FLOAT16_R;
	texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
	texProperty._need_mipmap = false;
	pTextureSDFVolumeAtlas =
		mRenderSystem->createManualTexture("SDFVolumeAtlas", &texProperty);

	texProperty._width = 2048;
	texProperty._height = 2048;
	texProperty._depth = 1;
	texProperty._texType = TEX_TYPE_2D;
	texProperty._tex_format = Ogre::PixelFormat::PF_DEPTH32F;
	texProperty._tex_usage = Ogre::TextureUsage::DEPTH_ATTACHMENT;
	texProperty._need_mipmap = false;

	depthTarget =
		mRenderSystem->createRenderTarget("depthTarget", texProperty);

	texProperty._width = ogreConfig.width;
	texProperty._height = ogreConfig.height;
	texProperty._depth = 1;
	texProperty._texType = TEX_TYPE_2D;
	texProperty._tex_format = Ogre::PixelFormat::PF_A8B8G8R8;
	texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
	texProperty._need_mipmap = false;

	outputTarget =
		mRenderSystem->createRenderTarget("outputTarget", texProperty);

	mFrameData.resize(2);

	BufferDesc sdfVolumeDataDesc{};
	sdfVolumeDataDesc.mBindingType = BufferObjectBinding_Storge;
	sdfVolumeDataDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	sdfVolumeDataDesc.bufferCreationFlags = 0;
	sdfVolumeDataDesc.mStructStride = sizeof(float);
	sdfVolumeDataDesc.mElementCount = volumeBufferElementCount;
	sdfVolumeDataDesc.mSize = sdfVolumeDataDesc.mStructStride * sdfVolumeDataDesc.mElementCount;
	sdfVolumeDataDesc.pName = "sdfVolumeDataDesc";

	BufferDesc updateSDFVolumeTextureAtlasUniformDesc{};
	updateSDFVolumeTextureAtlasUniformDesc.mBindingType = BufferObjectBinding_Uniform;
	updateSDFVolumeTextureAtlasUniformDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	updateSDFVolumeTextureAtlasUniformDesc.bufferCreationFlags = 0;
	updateSDFVolumeTextureAtlasUniformDesc.mSize = sizeof(UpdateSDFVolumeTextureAtlasConstants);
	updateSDFVolumeTextureAtlasUniformDesc.pName = "updateSDFVolumeTextureAtlasUniformDesc";

	BufferDesc cameraUniformDesc{};
	cameraUniformDesc.mBindingType = BufferObjectBinding_Uniform;
	cameraUniformDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	cameraUniformDesc.bufferCreationFlags = 0;
	cameraUniformDesc.mSize = sizeof(cameraUniformBlock);
	cameraUniformDesc.pName = "cameraUniformDesc";

	BufferDesc meshSDFUniformDesc{};
	meshSDFUniformDesc.mBindingType = BufferObjectBinding_Uniform;
	meshSDFUniformDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	meshSDFUniformDesc.bufferCreationFlags = 0;
	meshSDFUniformDesc.mSize = sizeof(meshSDFUniformBlock);
	meshSDFUniformDesc.pName = "meshSDFUniformDesc";

	BufferDesc pushDesc{};
	pushDesc.mBindingType = BufferObjectBinding_Uniform;
	pushDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	pushDesc.bufferCreationFlags = 0;
	pushDesc.mSize = sizeof(PushConstant);
	pushDesc.pName = "pushDesc";

	backend::SamplerParams params;
	params.filterMag = backend::SamplerFilterType::LINEAR;
	params.filterMin = backend::SamplerFilterType::LINEAR;
	params.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	params.wrapS = backend::SamplerWrapMode::REPEAT;
	params.wrapT = backend::SamplerWrapMode::REPEAT;
	params.wrapR = backend::SamplerWrapMode::REPEAT;
	params.compareMode = backend::SamplerCompareMode::COMPARE_TO_TEXTURE;
	params.compareFunc = backend::SamplerCompareFunc::LE;
	params.anisotropyLog2 = 3;
	params.useComparison = 0;
	params.maxLod = 0;
	params.padding2 = 0;

	clampToEdgeTrillinearSampler = mRenderSystem->createTextureSampler(params);
	params.filterMag = backend::SamplerFilterType::NEAREST;
	params.filterMin = backend::SamplerFilterType::NEAREST;
	params.mipMapMode = backend::SamplerMipMapMode::MIPMAP_MODE_NEAREST;
	params.wrapS = backend::SamplerWrapMode::CLAMP_TO_EDGE;
	params.wrapT = backend::SamplerWrapMode::CLAMP_TO_EDGE;
	params.wrapR = backend::SamplerWrapMode::CLAMP_TO_EDGE;
	params.anisotropyLog2 = 0;
	clampToEdgeNearSampler = mRenderSystem->createTextureSampler(params);
	DescriptorData descriptorData[16];
	for (uint32_t i = 0; i < 2; i++)
	{
		FrameData& frameData = mFrameData[i];
		frameData.pBufferSDFVolumeData = mRenderSystem->createBufferObject(sdfVolumeDataDesc);

		frameData.pBufferUpdateSDFVolumeTextureAtlasConstants = 
			mRenderSystem->createBufferObject(updateSDFVolumeTextureAtlasUniformDesc);

		frameData.zeroSetOfSDFVolume = 
			mRenderSystem->createDescriptorSet(mUpdateRegion3DTextureHandle, 0);
		
		descriptorData[0].pName = "UpdateSDFVolumeTextureAtlasCB";
		descriptorData[0].mCount = 1;
		descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[0].ppBuffers = &frameData.pBufferUpdateSDFVolumeTextureAtlasConstants;

		descriptorData[1].pName = "SDFVolumeTextureAtlas";
		descriptorData[1].mCount = 1;
		descriptorData[1].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
		descriptorData[1].ppTextures = (const Ogre::OgreTexture**)& pTextureSDFVolumeAtlas;

		descriptorData[2].pName = "SDFVolumeDataBuffer";
		descriptorData[2].mCount = 1;
		descriptorData[2].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[2].ppBuffers = &frameData.pBufferSDFVolumeData;


		mRenderSystem->updateDescriptorSet(frameData.zeroSetOfSDFVolume, 3, descriptorData);

		frameData.pBufferCameraUniform = 
			mRenderSystem->createBufferObject(cameraUniformDesc);
		frameData.pBufferMeshSDFUniform = 
			mRenderSystem->createBufferObject(meshSDFUniformDesc);
		frameData.pBufferPushConstant =
			mRenderSystem->createBufferObject(pushDesc);
		frameData.zeroSetOfAtlas =
			mRenderSystem->createDescriptorSet(mVisualizeSDFMeshHandle, 0);
		
		OgreTexture* depthTexture = depthTarget->getTarget();

		descriptorData[0].pName = "DepthTexture";
		descriptorData[0].mCount = 1;
		descriptorData[0].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
		descriptorData[0].ppTextures = (const OgreTexture**)& depthTexture;

		descriptorData[1].pName = "SDFVolumeTextureAtlas";
		descriptorData[1].mCount = 1;
		descriptorData[1].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
		descriptorData[1].ppTextures = (const OgreTexture**)& pTextureSDFVolumeAtlas;

		OgreTexture* outTexture = outputTarget->getTarget();

		descriptorData[2].pName = "OutTexture";
		descriptorData[2].mCount = 1;
		descriptorData[2].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
		descriptorData[2].ppTextures = (const OgreTexture**)&outTexture;

		descriptorData[3].pName = "cameraUniform";
		descriptorData[3].mCount = 1;
		descriptorData[3].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[3].ppBuffers = &frameData.pBufferCameraUniform;

		descriptorData[4].pName = "meshSDFUniform";
		descriptorData[4].mCount = 1;
		descriptorData[4].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[4].ppBuffers = &frameData.pBufferMeshSDFUniform;

		descriptorData[5].pName = "meshSDFUniform";
		descriptorData[5].mCount = 1;
		descriptorData[5].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[5].ppBuffers = &frameData.pBufferMeshSDFUniform;

		descriptorData[5].pName = "meshSDFUniform";
		descriptorData[5].mCount = 1;
		descriptorData[5].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[5].ppBuffers = &frameData.pBufferMeshSDFUniform;

		descriptorData[6].pName = "pushConstant";
		descriptorData[6].mCount = 1;
		descriptorData[6].descriptorType = DESCRIPTOR_TYPE_BUFFER;
		descriptorData[6].ppBuffers = &frameData.pBufferPushConstant;

		descriptorData[7].pName = "clampToEdgeTrillinearSampler";
		descriptorData[7].mCount = 1;
		descriptorData[7].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
		descriptorData[7].ppSamplers = &clampToEdgeTrillinearSampler;

		descriptorData[8].pName = "clampToEdgeNearSampler";
		descriptorData[8].mCount = 1;
		descriptorData[8].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
		descriptorData[8].ppSamplers = &clampToEdgeNearSampler;

		mRenderSystem->updateDescriptorSet(frameData.zeroSetOfAtlas, 9, descriptorData);
	}

	
	FrameData* framedDatas = mFrameData.data();
	RenderPassCallback sdfShadowPassCallback = [=, this](RenderPassInfo& info) {
		auto frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
		FrameData* frameData = &framedDatas[frameIndex];
		SDFVolumeTextureNode* volumeTextureNode = pSDFVolumeTextureAtlas->ProcessQueuedNode();
		
		{
			TextureBarrier texBarriers[] =
			{
				{
					 pTextureSDFVolumeAtlas,
					 RESOURCE_STATE_SHADER_RESOURCE,
					 RESOURCE_STATE_UNORDERED_ACCESS
				}
			};

			mRenderSystem->resourceBarrier(0, nullptr, 1, texBarriers, 0, nullptr);
		}
		
		

		if (volumeTextureNode)
		{
			mRenderSystem->pushGroupMarker("Draw update texture atlas");
			mRenderSystem->updateBufferObject(
				frameData->pBufferSDFVolumeData,
				(const char*)volumeTextureNode->mSDFVolumeData->mSDFVolumeList.data(),
				volumeTextureNode->mSDFVolumeData->mSDFVolumeList.size() * sizeof(float));

			UpdateSDFVolumeTextureAtlasConstants dummy;
			dummy.mSourceAtlasVolumeMinCoord = volumeTextureNode->mAtlasAllocationCoord;
			dummy.mSourceDimensionSize = volumeTextureNode->mSDFVolumeData->mSDFVolumeSize;
			dummy.mSourceAtlasVolumeMaxCoord =
				volumeTextureNode->mAtlasAllocationCoord + 
				(volumeTextureNode->mSDFVolumeData->mSDFVolumeSize - Vector3i(1));

			mRenderSystem->updateBufferObject(
				frameData->pBufferUpdateSDFVolumeTextureAtlasConstants,
				(const char*)&dummy, sizeof(dummy));
		    //drawSDFVolumeTextureAtlas

			mRenderSystem->popGroupMarker();

			UpdateMeshSDFConstants();

			for (uint32_t i = 0; i < 2; i++)
			{
				mRenderSystem->updateBufferObject(
					framedDatas[frameIndex].pBufferMeshSDFUniform,
					(const char*)&mMeshSDFConstants,
					sizeof(mMeshSDFConstants));
			}
		}

		
		{
			TextureBarrier texBarriers[] =
			{
				{
					 pTextureSDFVolumeAtlas,
					 RESOURCE_STATE_UNORDERED_ACCESS,
					 RESOURCE_STATE_SHADER_RESOURCE
				}
			};

			mRenderSystem->resourceBarrier(0, nullptr, 1, texBarriers, 0, nullptr);
		}

		drawSDFMeshVisualizationOnScene(frameIndex);
		};

	UpdatePassCallback updateCallback = [=, this](float delta) {
		};

	auto sdfShadowPass = createUserDefineRenderPass(
		sdfShadowPassCallback, updateCallback);
	mRenderPipeline->addRenderPass(sdfShadowPass);


	PresentPass* presentPass = new PresentPass(
		outputTarget->getTarget(), mRenderWindow);
	presentPass->initialize();
	mRenderPipeline->addRenderPass(presentPass);
}

void BasicApplication::drawSDFMeshVisualizationOnScene(uint32_t frameIndex)
{
	TextureBarrier texBarriers[] =
	{
		{
			 depthTarget->getTarget(),
			 RESOURCE_STATE_UNDEFINED,
			 RESOURCE_STATE_PIXEL_SHADER_RESOURCE
		},
		{
			 outputTarget->getTarget(),
			 RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			 RESOURCE_STATE_UNORDERED_ACCESS
		}
	};

	mRenderSystem->resourceBarrier(0, nullptr, 2, texBarriers, 0, nullptr);

	FrameData* frameData = &mFrameData[frameIndex];
	mRenderSystem->pushGroupMarker("Visualize SDF Geometry On The Scene");
	
	mRenderSystem->updateBufferObject(frameData->pBufferPushConstant,
		(const char*)& mSDFNumObjects, sizeof(mSDFNumObjects));

	mRenderSystem->bindComputePipeline(mVisualizeSDFMeshHandle,
		&frameData->zeroSetOfAtlas, 1);
	int32_t x = ceil(outputTarget->getWidth() / (float)(SDF_MESH_VISUALIZATION_THREAD_X));
	int32_t y= ceil(outputTarget->getHeight() / (float)(SDF_MESH_VISUALIZATION_THREAD_Y));
	int32_t z = 1;
	mRenderSystem->dispatchComputeShader(x, y, z);

	texBarriers[0] =
	{
		 depthTarget->getTarget(),
		 RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		 RESOURCE_STATE_DEPTH_WRITE
	};

	texBarriers[1] =
	{
		 outputTarget->getTarget(),
		 RESOURCE_STATE_UNORDERED_ACCESS,
		 RESOURCE_STATE_PIXEL_SHADER_RESOURCE
	};

	mRenderSystem->resourceBarrier(0, nullptr, 2, texBarriers, 0, nullptr);
	mRenderSystem->popGroupMarker();
}

void BasicApplication::initSDFVolumeTextureAtlasData()
{
	uint32_t instancesSize = sdfVolumeInstances.size();

	for (uint32_t i = 0; i < instancesSize; i++)
	{
		SDFVolumeData* volumeData = sdfVolumeInstances[i];
		SDFVolumeTextureNode* textureNode = &volumeData->mSDFVolumeTextureNode;
		pSDFVolumeTextureAtlas->AddVolumeTextureNode(textureNode);
	}
}

void BasicApplication::UpdateMeshSDFConstants()
{
	const Vector3 inverseSDFTextureAtlasSize(1.f / (float)SDF_VOLUME_TEXTURE_ATLAS_WIDTH, 1.f / (float)SDF_VOLUME_TEXTURE_ATLAS_HEIGHT,
		1.f / (float)SDF_VOLUME_TEXTURE_ATLAS_DEPTH);
	uint32_t   instancesSize = sdfVolumeInstances.size();
	uint32_t   nodeQueueSize = pSDFVolumeTextureAtlas->mPendingNodeQueue.size();
	mSDFNumObjects = instancesSize -
		(uint32_t)(nodeQueueSize - pSDFVolumeTextureAtlas->mNextNodeIndex);
	for (size_t i = 0; i < instancesSize; ++i)
	{
		const Matrix4 meshModelMat = Matrix4::IDENTITY;
		
		SDFVolumeData* sdfVolumeData = sdfVolumeInstances[i];

		Ogre::AxisAlignedBox& sdfVolumeBBox = sdfVolumeData->mLocalBoundingBox;
		const Vector3i& sdfVolumeDimensionSize = sdfVolumeData->mSDFVolumeSize;

		Vector3  sdfVolumeBBoxExtent = calculateAABBExtent(&sdfVolumeBBox);
		float maxExtentValue = sdfVolumeBBoxExtent.maxElem();

		Matrix4 uniformScaleVolumeToWorld =
			meshModelMat * Matrix4::getTrans(calculateAABBCenter(&sdfVolumeBBox)) * Matrix4::getScale(Vector3(maxExtentValue));

		Vector3 invSDFVolumeDimSize(1.f / sdfVolumeDimensionSize.x, 1.f / sdfVolumeDimensionSize.y,
			1.f / sdfVolumeDimensionSize.z);
		mMeshSDFConstants.mWorldToVolumeMat[i] = 
			uniformScaleVolumeToWorld.inverse().transpose();

		// get the extent position in the 0.... 1 scale
		Vector3 localPositionExtent = sdfVolumeBBoxExtent / maxExtentValue;

		Vector3 uvScale = Vector3(sdfVolumeDimensionSize.x * inverseSDFTextureAtlasSize.x,
			sdfVolumeDimensionSize.y * inverseSDFTextureAtlasSize.y,
			sdfVolumeDimensionSize.z * inverseSDFTextureAtlasSize.z);

		Vector3 col0Scale = uniformScaleVolumeToWorld.getCol0();
		Vector3 col1Scale = uniformScaleVolumeToWorld.getCol1();
		Vector3 col2Scale = uniformScaleVolumeToWorld.getCol2();

		float col0SquaredLength = col0Scale.dotProduct(col0Scale);
		float col1SquaredLength = col1Scale.dotProduct(col1Scale);
		float col2SquaredLength = col2Scale.dotProduct(col2Scale);

		float finalColSquaredLength = fmax(fmax(col0SquaredLength, col1SquaredLength), col2SquaredLength);

		float maximumVolumeScale = sqrt(finalColSquaredLength);

		mMeshSDFConstants.mLocalPositionExtent[i] = Vector4(localPositionExtent - invSDFVolumeDimSize, 1.f);

		Vector3 initialUV = Vector3(sdfVolumeDimensionSize.x * inverseSDFTextureAtlasSize.x,
			sdfVolumeDimensionSize.y * inverseSDFTextureAtlasSize.y,
			sdfVolumeDimensionSize.z * inverseSDFTextureAtlasSize.z) *
			0.5f;

		Vector3 newUV = Vector3(initialUV.x / localPositionExtent.x, initialUV.y / localPositionExtent.y,
			initialUV.z / localPositionExtent.z);

		maximumVolumeScale *= (sdfVolumeData->mIsTwoSided ? -1.f : 1.0f);
		mMeshSDFConstants.mUVScaleAndVolumeScale[i] = Vector4(newUV, maximumVolumeScale);

		const Vector3i& atlasAllocationCoord = sdfVolumeData->mSDFVolumeTextureNode.mAtlasAllocationCoord;

		Vector3 offsetUV = Vector3(atlasAllocationCoord.x * inverseSDFTextureAtlasSize.x,
			atlasAllocationCoord.y * inverseSDFTextureAtlasSize.y,
			atlasAllocationCoord.z * inverseSDFTextureAtlasSize.z);

		offsetUV += (0.5f * uvScale);
		mMeshSDFConstants.mUVAddAndSelfShadowBias[i] = Vector4(offsetUV, 0.f);

		mMeshSDFConstants.mSDFMAD[i] = Vector4(sdfVolumeData->mDistMinMax.y - sdfVolumeData->mDistMinMax.x,
			sdfVolumeData->mDistMinMax.x, sdfVolumeData->mTwoSidedWorldSpaceBias, 0.f);
	}
}

void BasicApplication::updateCameraUniform()
{
	cameraUniformBlock cameraBlock;
	auto camera = mGameCamera->getCamera();
	const Ogre::Matrix4& view = camera->getViewMatrix();
	const Ogre::Matrix4& proj = camera->getProjectMatrix();
	const Ogre::Vector3& camepos = camera->getDerivedPosition();

	cameraBlock.View = view.transpose();
	cameraBlock.Project = proj.transpose();
	cameraBlock.ViewProject = (proj * view).transpose();
	cameraBlock.InvView = cameraBlock.View.inverse();
	cameraBlock.InvProj = cameraBlock.Project.inverse();
	cameraBlock.InvViewProject = cameraBlock.ViewProject.inverse();
	cameraBlock.mCameraPos = camepos;

	CameraInfo& cameraInfo = mGameCamera->getCameraInfo();

	cameraBlock.mNear = cameraInfo.nearClip;
	cameraBlock.mFar = cameraInfo.farClip;
	cameraBlock.mFarNearDiff = cameraInfo.farClip - cameraInfo.nearClip;
	cameraBlock.mFarNear = cameraInfo.nearClip * cameraInfo.farClip;

	EngineConfig& config = Ogre::Root::getSingleton().getEngineConfig();
	cameraBlock.mTwoOverRes = Ogre::Vector2(1.5f / config.width, 1.5f / config.height);;
	cameraBlock.mWindowSize = Ogre::Vector2(config.width, config.height);

	float depthMul = proj[2][2];
	float depthAdd = proj[3][2];

	if (depthAdd == 0.f)
	{
		// avoid dividing by 0 in this case
		depthAdd = 0.00000001f;
	}

	if (proj[3][3] < 1.0f)
	{
		float subtractValue = depthMul / depthAdd;
		subtractValue -= 0.00000001f;
		cameraBlock.mDeviceZToWorldZ = Vector4(0.f, 0.f, 1.f / depthAdd, subtractValue);
	}
	else
	{
		cameraBlock.mDeviceZToWorldZ = Vector4::ZERO;
	}

	
}