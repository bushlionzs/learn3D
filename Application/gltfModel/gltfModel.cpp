#include "OgreHeader.h"
#include "gltfModel.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "OGImpact.h"
#include "OGImpactManager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"

gltfModel::gltfModel()
{

}

gltfModel::~gltfModel()
{

}

bool gltfModel::appInit()
{
	ApplicationBase::appInit();

	std::string meshname = "FlightHelmet.gltf";
	meshname = "matBall.bin";
	auto mesh = MeshManager::getSingletonPtr()->load(meshname);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", meshname);

	gltf->setMaterialName("Copper");
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->attachObject(gltf);
	


	mGameCamera->setDistance(10);
	mGameCamera->setHeight(0.0f);
	mGameCamera->setMoveSpeed(200);
	//glslangValidator  -V material_pbr.frag -o material_pbr.frag.spv
	//gltf-pipeline -i input.gltf -o output.glb

	return true;
}

void gltfModel::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
}

EngineType gltfModel::getEngineType()
{
	return EngineType_Vulkan;
	return EngineType_Dx11;
}