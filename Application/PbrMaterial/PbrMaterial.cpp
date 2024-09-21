#include "stdafx.h"
#include <string_util.h>
#include "PbrMaterial.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "renderSystem.h"
#include "OgreViewport.h"

#include "OgreTextureManager.h"
#include "OgreMaterialManager.h"
#include "OgreRenderTexture.h"
#include "OgreCamera.h"
#include "OgreSubEntity.h"
#include "role.h"
#include "application_util.h"
#include "pbrWindow.h"
#include "OgreRoot.h"
#include <platform_file.h>
#include <OgreRoot.h>
#include <algorithm>

PbrMaterial::PbrMaterial()
{
   

}

PbrMaterial::~PbrMaterial()
{

}

std::vector<std::string> matNameList =
{
	"Aluminum",
	"ScratchedGold",
	"Copper",
	"TiledMetal",
	"OldIron",
	"Bronze",
	"WoodenPlank05",
	"WoodenPlank06",
	"Wood03",
	"Wood08",
	"Wood16",
	"Wood18",
	"ForgeGround",
	"ForgePlate",
};
#define ENTRY_INSTANCE_COUNT 6
bool PbrMaterial::appInit()
{
	ApplicationBase::appInit();
	uiInit();
#define PI 3.14159265358

	float baseX = 22.0f;
	float baseY = -1.8f;
	float baseZ = 12.0f;
	float offsetX = 8.0f;
	float scaleVal = 4.0f;
	float roughDelta = 1.0f;
	float materialPlateOffset = 4.0f;
	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");
	std::string cubeName = "cube.bin";
	auto cube = MeshManager::getSingletonPtr()->load(cubeName);

	std::string matBallName = "matBall.bin";
	auto matBall = MeshManager::getSingletonPtr()->load(matBallName);
	
	matBallList.resize(ENTRY_INSTANCE_COUNT);

	

	for (uint32_t i = 0; i < ENTRY_INSTANCE_COUNT; ++i)
	{
		std::string entryName = "matBall_" + std::to_string(i);
		Entity* entity = mSceneManager->createEntity(entryName, matBallName);

		entity->setMaterialName(matNameList[i]);
		auto* r = entity->getSubEntity(0);
		Ogre::Vector3 pos = Ogre::Vector3(baseX - i - offsetX * i, baseY, baseZ);
		r->setLocalMatrix(pos,
			Ogre::Vector3(4.0), 
			Ogre::Quaternion(Ogre::Radian(PI), Ogre::Vector3::UNIT_Y));

		SceneNode* entityNode = root->createChildSceneNode(entryName);
		entityNode->attachObject(entity);

		matBallList[i] = entity;
	}

	std::vector<Ogre::Entity*> cubeList;
	cubeList.resize(ENTRY_INSTANCE_COUNT);
	for (uint32_t i = 0; i < ENTRY_INSTANCE_COUNT; ++i)
	{
		std::string entryName = "cube_" + std::to_string(i);
		Entity* entity = mSceneManager->createEntity(entryName, cubeName);

		entity->setMaterialName("ForgePlate");
		auto* r = entity->getSubEntity(0);
		r->setLocalMatrix(Ogre::Vector3(baseX - i - offsetX * i, -5.8f, baseZ + materialPlateOffset),
			Ogre::Vector3(3.0f, 0.1f, 1.0f),
			Ogre::Quaternion(Ogre::Radian(PI/5.0f), Ogre::Vector3::UNIT_X));

		SceneNode* entityNode = root->createChildSceneNode(entryName);
		entityNode->attachObject(entity);

		cubeList[i] = entity;
	}

	{
		std::string entryName = "cube_ground";
		Entity* entity = mSceneManager->createEntity(entryName, cubeName);

		entity->setMaterialName("ForgeGround");
		auto* r = entity->getSubEntity(0);
		r->setLocalMatrix(Ogre::Vector3(0.0f, -6.0f, 5.0f),
			Ogre::Vector3(30.0f, 0.2f, 30.0f),
			Ogre::Quaternion::IDENTITY);

		SceneNode* entityNode = root->createChildSceneNode(entryName);
		entityNode->attachObject(entity);
	}

	

	std::vector<Ogre::MaterialPtr> matList;
	for (auto& name : matNameList)
	{
		auto mat = MaterialManager::getSingleton().getByName(name);
		PbrMaterialConstanceBuffer& matInfo = mat->getMatInfo();
		matList.push_back(mat);
	}
	
	TextureProperty tp;
	

	auto rs = Ogre::Root::getSingleton().getRenderSystem();
	
	tp._need_mipmap = false;
	tp._texType = TEX_TYPE_CUBE_MAP;
	tp._tex_addr_mod = TAM_CLAMP;
	tp._samplerParams.filterMag = filament::backend::SamplerMagFilter::LINEAR;
	tp._samplerParams.filterMin = filament::backend::SamplerMinFilter::LINEAR_MIPMAP_LINEAR;
	tp._samplerParams.wrapS = filament::backend::SamplerWrapMode::REPEAT;
	tp._samplerParams.wrapT = filament::backend::SamplerWrapMode::REPEAT;
	tp._samplerParams.wrapR = filament::backend::SamplerWrapMode::REPEAT;
	tp._samplerParams.anisotropyLog2 = 0;
	auto environmentCube = TextureManager::getSingletonPtr()->load("LA_Helipad3D.dds", &tp, true).get();

	std::string prefilteredenvName = "prefilteredMap";
	auto prefilteredMap = rs->generateCubeMap(prefilteredenvName, environmentCube, PF_FLOAT32_RGBA, 128, CubeType_Prefiltered);
	TextureManager::getSingleton().addTexture(prefilteredenvName, prefilteredMap);
	tp._pbrType = TextureTypePbr_IBL_Specular;

	std::for_each(matList.begin(), matList.end(),
		[&prefilteredenvName, &tp](Ogre::MaterialPtr& mat)
		{mat->addTexture(prefilteredenvName, &tp); });

	
	std::string irradianceName = "IrradianceMap";
	auto irradianceMap = rs->generateCubeMap(irradianceName, environmentCube, PF_FLOAT32_RGBA, 32, CubeType_Irradiance);
	TextureManager::getSingleton().addTexture(irradianceName, irradianceMap);
	tp._pbrType = TextureTypePbr_IBL_Diffuse;
	std::for_each(matList.begin(), matList.end(),
		[&irradianceName, &tp](Ogre::MaterialPtr mat)
		{mat->addTexture(irradianceName, &tp); });


	std::string brdfLutName = "brdflut";
	auto brdf = rs->generateBRDFLUT(brdfLutName);
	TextureManager::getSingleton().addTexture(brdfLutName, brdf);
	tp._pbrType = TextureTypePbr_BRDF_LUT;

	std::for_each(matList.begin(), matList.end(),
		[&brdfLutName, &tp](Ogre::MaterialPtr mat)
		{mat->addTexture(brdfLutName, &tp); });

	

	mSceneManager->setSkyBox(true, "SkyMap", 10000);
	mGameCamera->updateCamera(Ogre::Vector3(0, 10.0f, 60.0f), Ogre::Vector3::ZERO);

	mGameCamera->setMoveSpeed(20);
	return true;
}

void PbrMaterial::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);

	
}

EngineType PbrMaterial::getEngineType()
{
	return EngineType_Vulkan;
	return EngineType_Dx11;
}

void PbrMaterial::uiInit()
{
	PBRWindow* window = new PBRWindow(this);
}

void PbrMaterial::updateRenderMode(uint32_t mode)
{
	for (auto& name : matNameList)
	{
		auto mat = MaterialManager::getSingleton().getByName(name);
		PbrMaterialConstanceBuffer& matInfo = mat->getMatInfo();
		matInfo.debugRenderMode = mode;
	}
}

void PbrMaterial::updateMaterialType(uint32_t type)
{
	for (auto i = 0; i < matBallList.size(); i++)
	{
		matBallList[i]->setMaterialName(matNameList[i + type* ENTRY_INSTANCE_COUNT]);
	}
}

void PbrMaterial::updateLightDirection(const Ogre::Vector3& dir)
{
	auto* rs = Ogre::Root::getSingleton().getRenderSystem();
	FrameConstantBuffer* frameBuffer = rs->getFrameConstantBuffer();

	frameBuffer->directionLights[0].Direction = dir;
}

