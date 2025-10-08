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
#include <glm/glm.hpp>
BasicApplication::BasicApplication()
{
	mTotalTime = 0.0f;
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
	mRenderSystem = Ogre::Root::getSingleton().getRenderSystem();
	mRenderPipeline = renderPipeline;
	base2();
}

void BasicApplication::update(float delta)
{
	Ogre::Matrix4 lightViewMatrix;
	mTotalTime += delta;
	//mTotalTime = 0.5f;
	float angle = glm::radians(mTotalTime * 36.0f);
	float radius = 20.0f;
	mLightPosition = Ogre::Vector3(cos(angle) * radius, -radius, sin(angle) * radius);
	mLightDirection = mLightPosition;
	mLightDirection.normalise();
	mGameCamera->updateCascades(mLightDirection);

	mLight->updateDirection(mLightDirection);

	for (uint32_t i = 0; i < SHADOW_MAP_CASCADE_COUNT; i++)
	{
		Cascade* cascade = mGameCamera->getCascade(i);
		mCascadeInfo.matrices[i] = cascade->lightViewProjMatrix.transpose();
		mCascadeInfo.cascadeSplits[i] = cascade->splitDepth;
	}

	/*mLight->updateProjectMatrix(cascades[0].lightOrthoMatrix);
	mLight->updateViewMatrix(cascades[0].lightViewMatrix);*/
}

void BasicApplication::base1()
{
	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	
	std::string meshName = "vulkanscene_shadow.gltf";
	meshName = "samplescene.gltf";
	auto mesh = Ogre::MeshManager::getSingletonPtr()->load(meshName);

	Ogre::Entity* entity = mSceneManager->createEntity(meshName, meshName);
	Ogre::SceneNode* entityNode = root->createChildSceneNode(meshName);
	entityNode->attachObject(entity);

	uint32_t subCount = entity->getNumSubEntities();


	auto mat = Ogre::MaterialManager::getSingleton().getByName("NoTexture");
	for (uint32_t i = 0; i < subCount; i++)
	{
		SubEntity* subEntity = entity->getSubEntity(i);
		auto& source = subEntity->getMaterial();
		auto copy = mat->clone("");
		Vector4 sourceColor = source->getPbrMatInfo().baseColorFactor;
		copy->setDiffuseColor(sourceColor.xyz());
		subEntity->setMaterial(copy);
	}

	float h = -10.0f;
	Ogre::Vector3 camPosition = Ogre::Vector3(0.0f, h, -12.5f);

	Ogre::Vector3 camTarget = Ogre::Vector3(0.0f, h, -13.5f);
	mGameCamera->lookAt(camPosition, camTarget);
	mGameCamera->setCameraType(Ogre::CameraMoveType_LookAt);
	mGameCamera->setMoveSpeed(50);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	Ogre::Matrix4 m;
	if (ogreConfig.reverseDepth)
	{
		float aspectInverse = ogreConfig.height / (float)ogreConfig.width;
		m = Ogre::Math::makePerspectiveMatrixReverseZ(
			Ogre::Math::PI / 3.0f, aspectInverse, 0.1, 6000);
	}
	else
	{
		float aspect = ogreConfig.width / (float)ogreConfig.height;
		m = Ogre::Math::makePerspectiveMatrix(
			Ogre::Math::PI / 3.0f, aspect, 1.0, 256);

	}
	mGameCamera->getCamera()->updateProjectMatrix(m);
	mLight = mSceneManager->createLight("light");

	
	Ogre::Matrix4 lightProjectMatrix;

	uint32_t size = 256;
	Real left = -256 / 2.0f;
	Real right = 256 / 2.0f;
	Real top = 256 / 2.0f;
	Real bottom = -256 / 2.0f;

	lightProjectMatrix = Ogre::Math::makeOrthoRH(left, right, bottom, top, -256, 256);

	lightProjectMatrix = Ogre::Math::makePerspectiveMatrix(Ogre::Math::PI / 4.0f, 1.0f, 1.0f, 96.f);
	mLight->updateProjectMatrix(lightProjectMatrix);

	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	input.light = mLight;
	
	input.shadowMapTarget = nullptr;
	
	
	TextureProperty texProperty;
	texProperty._need_mipmap = false;
	texProperty._width = 2048;
	texProperty._height = 2048;
	texProperty._tex_format = Ogre::PixelFormat::PF_DEPTH32F;
	texProperty._tex_usage = TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

void BasicApplication::base2()
{
	std::string terrain_name = "terrain_gridlines.gltf";

	Ogre::MeshManager::getSingletonPtr()->load(terrain_name);

	std::string tree_name = "oaktree.gltf";
	Ogre::MeshManager::getSingletonPtr()->load(tree_name);
	Ogre::SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Ogre::Entity* terrain = mSceneManager->createEntity(terrain_name, terrain_name);
	Ogre::SceneNode* terrainNode = root->createChildSceneNode(terrain_name);

	terrainNode->attachObject(terrain);

	const std::vector<Ogre::Vector3> positions = {
			Ogre::Vector3(0.0f, 0.0f, 0.0f),
			Ogre::Vector3(1.25f, -0.15f, 1.25f),
			Ogre::Vector3(-1.25f, -0.25f, 1.25f),
			Ogre::Vector3(1.25f, -0.25f, -1.25f),
			Ogre::Vector3(-1.25f, -0.25f, -1.25f),
	};

	for (uint32 i = 0; i < positions.size(); i++)
	{
		std::string entiryName = tree_name + std::to_string(i);
		Ogre::Entity* tree = mSceneManager->createEntity(entiryName, tree_name);
		Ogre::SceneNode* treeNode = root->createChildSceneNode(entiryName);

		treeNode->attachObject(tree);

		treeNode->setPosition(positions[i]);

		for (uint32_t i = 0; i < tree->getNumSubEntities(); i++)
		{
			SubEntity* subEntity = tree->getSubEntity(i);
			subEntity->setShadow(true);
			std::shared_ptr<Material>& mat = subEntity->getMaterial();
			mat->setPbr(false);
			ShaderInfo& shaderInfo = mat->getShaderInfo();
			shaderInfo.shaderMacros.push_back(std::pair<std::string, std::string>("CAST_SHADOW", "1"));
			shaderInfo.shaderName = "basic";
		}
	}

	for (uint32_t i = 0; i < terrain->getNumSubEntities(); i++)
	{
		SubEntity* subEntity = terrain->getSubEntity(i);
		subEntity->setShadow(true);
		std::shared_ptr<Material>& mat = subEntity->getMaterial();
		mat->setPbr(false);
		ShaderInfo&  shaderInfo = mat->getShaderInfo();
		shaderInfo.shaderMacros.push_back(std::pair<std::string, std::string>("CAST_SHADOW", "1"));
		shaderInfo.shaderName = "basic";
	}

	float h = 1.14f;
	mGameCamera->lookAt(
		Ogre::Vector3(-0.12f, h, -5.25f),
		Ogre::Vector3(-0.12f, h, -4.25f));
	mGameCamera->setMoveSpeed(3);
	mGameCamera->setCameraType(Ogre::CameraMoveType_FirstPerson);
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	float aspectInverse = ogreConfig.height / (float)ogreConfig.width;


	mLight = mSceneManager->createLight("light");


	Ogre::Matrix4 m;

	CameraInfo cameraInfo;
	cameraInfo.width = ogreConfig.width;
	cameraInfo.height = ogreConfig.height;
	cameraInfo.fovRadians = Ogre::Math::PI / 4.0f;
	cameraInfo.nearClip = 0.5f;
	cameraInfo.farClip = 48.0f;
	cameraInfo.reverseDepth = ogreConfig.reverseDepth;

	mGameCamera->updateCameraInfo(cameraInfo);
	
	RenderPassInput input;
	input.color = mRenderWindow->getColorTarget();
	input.depth = mRenderWindow->getDepthTarget();
	input.cam = mGameCamera->getCamera();
	input.sceneMgr = mSceneManager;
	input.light = mLight;
	input.flipY = true;
	input.cascadeMatrices = &mCascadeInfo;
	TextureProperty texProperty;
	texProperty._need_mipmap = false;
	texProperty._texType = TEX_TYPE_2D_ARRAY;
	texProperty._width = 4096;
	texProperty._height = 4096;
	texProperty._face = 4;
	texProperty._tex_format = Ogre::PixelFormat::PF_DEPTH32F;
	texProperty._tex_usage = TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	
	input.shadowMapTarget = mRenderSystem->createRenderTarget("shadowTarget", texProperty);
	
	

	auto mainPass = createStandardRenderPass(input);
	mRenderPipeline->addRenderPass(mainPass);
}

