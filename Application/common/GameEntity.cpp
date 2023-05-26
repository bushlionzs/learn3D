#include "OgreHeader.h"
#include "GameEntity.h"
#include "OGActorFactoryManager.h"
#include "OGSKeletonMeshActor.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"
#include "GameTableManager.h"
#include "GameTableData.h"
#include "KTable.h"
#include "KDefine.h"
#include "OGSpell.h"


GameEntity::GameEntity()
{

}

GameEntity::~GameEntity()
{

}

static const Ogre::String FOBJ_ACTOR_FILE = "logic model name";
bool GameEntity::loadModel(const String& modelName)
{
	mOrphigineObj =
		Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");
	mOrphigineObj->createRenderInstance();
	mOrphigineObj->setProperty(FOBJ_ACTOR_FILE, modelName);

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setVisible(true);
	return true;
}

bool GameEntity::changeAttributes(
	const std::vector<String>& names,
	const std::vector<String>& values)
{
	return ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->changeAttributes(
		names, values);
}

void GameEntity::setWeapon(const String& weaponName)
{
	Orphigine::SkeletonMeshActor* actor = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get());
	Orphigine::SkeletonMeshComponent* model = actor->getLogicModel();
	model->setWeaponTypeName(weaponName);
}

const Ogre::Vector3& GameEntity::getEntityPosition()
{
	return mEntityPosition;
}

void GameEntity::setEntityPosition(Ogre::Vector3& position)
{
	mEntityPosition = position;
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setPosition(position);
}

Ogre::Real GameEntity::getDirection()
{
	return mDirection;
}

void GameEntity::setDirection(float dir)
{
	mDirection = dir;

	Ogre::Quaternion qu(Ogre::Radian(dir), Ogre::Vector3::UNIT_Y);
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setOrientation(qu);
}

void GameEntity::setAnimationDegree(int32_t nActionType, float fDegree)
{
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setAdvancedAnimationSystemMonitoringDegree(
		Orphigine::SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree(nActionType), fDegree);

}

Orphigine::Spell* GameEntity::getCurrentSpell()
{
	Orphigine::SkeletonMeshActor* dummy = (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
	return dummy->getCurrentSkill();
}

Orphigine::SkeletonMeshComponent* GameEntity::getLogicModel()
{
	Orphigine::SkeletonMeshActor* dummy = (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
	return dummy->getLogicModel();
}

Orphigine::SkeletonMeshActor* GameEntity::getSkeletonMeshActor()
{
	return (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
}

void GameEntity::SetModelType(int32 nType)
{

}

