#include "OgreHeader.h"
#include "OgreSky.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"

void SkyRenderer::nodeDestroyed(const Node*)
{

}

SkyRenderer::SkyRenderer(SceneManager* owner)
{
    mSceneManager = owner;
}

void SkyRenderer::setEnabled(bool enable)
{

}

void SkyRenderer::postFindVisibleObjects(SceneManager* source, Viewport* vp)
{

}

SkyBoxRenderer::SkyBoxRenderer(SceneManager* owner)
	: SkyRenderer(owner)
{

}

void SkyBoxRenderer::setSkyBox(bool enable, const String& materialName, Real distance,
    uint8 renderQueue, const Quaternion& orientation,
    const String& groupName)
{
    auto mesh = MeshManager::getSingleton().createBox("skybox", distance, materialName);

    SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

    Entity* entity = mSceneManager->createEntity("skybox", mesh);

    root->attachObject(entity);
}

