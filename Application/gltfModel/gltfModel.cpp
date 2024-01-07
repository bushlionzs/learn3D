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

	auto mesh =
		MeshManager::getSingletonPtr()->load(std::string("Sponza.gltf"));

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	Entity* gltf = mSceneManager->createEntity("gltf", mesh);
	SceneNode* gltfnode = root->createChildSceneNode("gltf");
	gltfnode->attachObject(gltf);
	


	mGameCamera->setDistance(10);
	mGameCamera->setMoveSpeed(25.0f);

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