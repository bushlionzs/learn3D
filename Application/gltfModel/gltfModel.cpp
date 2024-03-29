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
	auto mesh =
		MeshManager::getSingletonPtr()->load(meshname);

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", meshname);
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->attachObject(gltf);
	


	mGameCamera->setDistance(2);
	mGameCamera->setMoveSpeed(5.0f);

	return true;
}

void gltfModel::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);
}

EngineType gltfModel::getEngineType()
{
	//return EngineType_Vulkan;
	return EngineType_Dx11;
}