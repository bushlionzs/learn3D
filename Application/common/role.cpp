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

	std::string modelname = "ͻ����ʿŮ_01.lmodel";
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
		"Ů���Ƿ���_01_��.mesh",
		"��Ů������_01.mesh",
		"ͻ����ʿ�е�_01.lmodel",
		"ͻ����ʿŮ����_01.mesh",
		"ͻ����ʿŮ˫��_01.mesh",
		"ͻ����ʿŮ˫��_01.mesh"
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