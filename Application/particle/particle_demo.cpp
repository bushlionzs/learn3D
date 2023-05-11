#include "OgreHeader.h"
#include "particle_demo.h"
#include "engine_manager.h"
#include "OgreParticleSystem.h"
#include "OGImpact.h"
#include "OGImpactManager.h"
#include "myutils.h"
#include "OgreResourceManager.h"
#include "OgreMaterialManager.h"
#include "OgreAnimationState.h"

ParticleDemo::ParticleDemo()
{

}

ParticleDemo::~ParticleDemo()
{

}

bool ParticleDemo::appInit()
{
	ApplicationBase::appInit();

	SceneNode* root = mSceneManager->getRoot()->createChildSceneNode("root");

	std::string m2name = "CREATURE\\AKAMA\\AKAMA.M2";
	m2name = "CREATURE\\GOBLIN\\GLBLINSHREDDER.M2";
	m2name = "CREATURE\\GOBLIN\\GOBLIN.M2";
	m2name = "ITEM\\OBJECTCOMPONENTS\\AMMO\\ARROWFIREFLIGHT_01.M2";

	Ogre::ParticleSystem* p = mSceneManager->createParticleSystem("Smoke", "Examples/Smoke");

	SceneNode* node = root->createChildSceneNode(std::string());
	node->attachObject(p);

	mGameCamera->setDistance(500.0f);
	mGameCamera->setMoveSpeed(25.0f);
	return true;
}

void ParticleDemo::appUpdate(float delta)
{
	ApplicationBase::appUpdate(delta);

}

EngineType ParticleDemo::getEngineType()
{
	return EngineType_Dx11;
}

void ParticleDemo::addCustomDirectory()
{
	ResourceManager::getSingletonPtr()->addDirectory(std::string("D:\\wow3.3.5\\Data"), "wow", true);
}