#pragma once

#include "OGActor.h"
#include "OGSpell.h"
#include "OGSkeletonMeshActor.h"

class GameEntity
{
public:
	GameEntity();
	~GameEntity();

	bool loadModel(const String& modelName);
	bool changeAttributes(
		const std::vector<String>& name, 
		const std::vector<String>& value);
	void setWeapon(const String& weaponName);

	const Ogre::Vector3& getEntityPosition();
	void setEntityPosition(Ogre::Vector3& position);

	Ogre::Real getDirection();
	void setDirection(float dir);

	void setAnimationDegree(int32_t nActionType, float fDegree);

	Orphigine::Spell* getCurrentSpell();

	Orphigine::SkeletonMeshComponent* getLogicModel();

	Orphigine::SkeletonMeshActor* getSkeletonMeshActor();

	//
	void SetModelType(int32 nType);
private:
	Orphigine::ActorPtr		mOrphigineObj;
	Orphigine::ActorPtr     mMountObj;
	Ogre::Vector3 mEntityPosition;
	Ogre::Real  mDirection = 0.0f;
};