#include "OgreHeader.h"
#include "role.h"
#include "OGSkeletonMeshComponent.h"
#include "OGSkeletonMeshActor.h"
#include "OGActorFactoryManager.h"

Role::Role()
{

}

Role::~Role()
{

}

void Role::createRoleData()
{
	const Ogre::String FOBJ_ACTOR_FILE = "logic model name";
	object =
		Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");

	std::string modelname = "突厥武士女_01.lmodel";
	object->createRenderInstance();
	object->setProperty(FOBJ_ACTOR_FILE, modelname);
	std::vector<std::string> names =
	{ "HairMesh",
	  "FaceMesh",
	  "RightWeaponObj",
	  "MainBodyMesh",
	  "ArmMesh",
	  "FootMesh"
	};
	std::vector<std::string> values =
	{
		"女主角发型_01_白.mesh",
		"新女主角脸_01.mesh",
		"突厥武士男刀_01.lmodel",
		"突厥武士女身体_01.mesh",
		"突厥武士女双手_01.mesh",
		"突厥武士女双脚_01.mesh"
	};
	((Orphigine::SkeletonMeshActor*)object.get())->changeAttributes(names, values);

	


	Orphigine::SkeletonMeshActor* skeletonActor = (Orphigine::SkeletonMeshActor*)object.get();
	Orphigine::SkeletonMeshComponent* model = skeletonActor->getLogicModel();

	if (model)
	{
		model->setWeaponTypeName("Falchion");
	}
}

void Role::setPosition(Ogre::Vector3& position)
{
	Orphigine::SkeletonMeshActor* skeletonActor = (Orphigine::SkeletonMeshActor*)object.get();
	Orphigine::SkeletonMeshComponent* model = skeletonActor->getLogicModel();
	model->setPosition(position);
}

void Role::ChangeAction(
	Orphigine::SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree action,
	float fDegree)
{

	((Orphigine::SkeletonMeshActor*)object.get())->setAdvancedAnimationSystemMonitoringDegree(
		action, fDegree);
}

void Role::walk()
{
	ChangeAction(Orphigine::SkeletonMeshComponent::AASMD_MOVING_DEGREE, 0.0f);
	ChangeAction(Orphigine::SkeletonMeshComponent::AASMD_EQUITATION_DEGREE, 0.0f);
	ChangeAction(Orphigine::SkeletonMeshComponent::AASMD_MOVING_DEGREE, 1.0f);
	ChangeAction(Orphigine::SkeletonMeshComponent::AASMD_WALK_DEGREE, 0.0f);
}