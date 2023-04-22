#pragma once
#include "OGActor.h"
#include "OGSkeletonMeshComponent.h"
class Role
{
public:
	Role();
	~Role();

	void createRoleData();

	void setPosition(Ogre::Vector3& position);

	void ChangeAction(
		Orphigine::SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree action,
		float fDegree);

	void walk();
private:
	Orphigine::ActorPtr object;
};