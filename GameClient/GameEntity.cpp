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
#include "CharacterCommon.h"


GameEntity::GameEntity()
{
	mOrphigineObj =
		Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");
	mOrphigineObj->createRenderInstance();
}

GameEntity::~GameEntity()
{

}

static const Ogre::String FOBJ_ACTOR_FILE = "logic model name";
bool GameEntity::setModelName(const String& modelName)
{
	if (mModelName == modelName)
		return true;
	mModelName = modelName;
	mOrphigineObj->setProperty(FOBJ_ACTOR_FILE, modelName);
	//((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setVisible(true);
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

String	GameEntity::AddEffect
(
	LPCSTR effectName,
	LPCSTR locatorName,
	int32 id,
	LPCSTR name,
	int32 priority)
{
	if (!mOrphigineObj)
		return "";


	return((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->addEffect(
		Ogre::String(effectName), Ogre::String(locatorName), Orphigine::SkeletonMeshComponent::GTIT_POSITION, Ogre::ColourValue::White, priority).c_str();

}

void GameEntity::Weapon_RemoveEffect(eWEAPATTR eWeaponAttr)
{
	if (!mOrphigineObj) return;

	
	switch (eWeaponAttr)
	{
	case WEAP_RIGHT:
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->clearWeaponEffect(Orphigine::SkeletonMeshComponent::WE_RIGHT);
		break;

	case WEAP_LEFT:
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->clearWeaponEffect(Orphigine::SkeletonMeshComponent::WE_LEFT);
		break;

	case WEAP_LEFT_SHIELD:
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->clearWeaponEffect(Orphigine::SkeletonMeshComponent::WE_LEFT_SHIELD);
		break;
	};

}

void GameEntity::RightWeapon_SetEffect(
	LPCTSTR szEffectName, 
	LPCSTR szLocatorName, 
	uint32 color, 
	int32 priority)
{
	if (!mOrphigineObj) return;
	Orphigine::SkeletonMeshActor* actor = (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
	
	actor->setWeaponEffect(
		(char*)szEffectName, 
		(char*)szLocatorName, 
		Orphigine::SkeletonMeshComponent::WE_RIGHT, 
		priority);

}

void GameEntity::LeftWeapon_SetEffect(
	LPCTSTR szEffectName, 
	LPCSTR szLocatorName, 
	uint32 color, int32 priority)
{
	Orphigine::SkeletonMeshActor* actor = (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
	actor->setWeaponEffect((char*)szEffectName, (char*)szLocatorName, Orphigine::SkeletonMeshComponent::WE_LEFT, priority);
}

void GameEntity::Shield_SetEffect(
	LPCTSTR szEffectName, 
	LPCSTR szLocatorName, 
	uint32 color, 
	int32 priority)
{

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setWeaponEffect((char*)szEffectName, (char*)szLocatorName, Orphigine::SkeletonMeshComponent::WE_LEFT_SHIELD, priority);

}

void GameEntity::Weapon_SetAasAnim(int32 eWeqaponType)
{
	String str;

	switch ((eWEAPON_TYPE)eWeqaponType)
	{
		// ͽ��
	case WEAPON_TYPE_NONE:		str = "Unarmed";		break;
		// ����
	case WEAPON_TYPE_LONG:		str = "LongHandle";		break;
		// ��
	case WEAPON_TYPE_FALCHION:	str = "Falchion";		break;
		// �
	case WEAPON_TYPE_GAVEL:		str = "Gavel";			break;
		// ����
	case WEAPON_TYPE_BOW:		str = "Bow";			break;
		// ��ǹ
	case WEAPON_TYPE_GUN:		str = "Gun";			break;
		// ��
	case WEAPON_TYPE_SWORD:		str = "Sword";			break;
		// ����
	case WEAPON_TYPE_FLAG:		str = "Flag";			break;
		// ��
	case WEAPON_TYPE_STAFF:		str = "Wand";			break;
		// ˫��
	case WEAPON_TYPE_DOUBLE:	str = "Epee";			break;
		// ��ì
	case WEAPON_TYPE_SPEAR:		str = "Spear";			break;
		// ��
	case WEAPON_TYPE_TOKEN:		str = "Token";			break;
		// ��
	case WEAPON_TYPE_CROSSBOW:	str = "Crossbow";		break;
		// ���
	case WEAPON_TYPE_FIREGUN:	str = "Firegun";		break;
		// ʮ�ּ�
	case WEAPON_TYPE_CROSS:		str = "Cross";			break;
		// ��
	case WEAPON_TYPE_FAN:		str = "Fan";			break;
		// ˫��
	case WEAPON_TYPE_HOLD:		break;
	};

	
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setWeaponTypeName(str.c_str());

}

void GameEntity::DeleteEffect(LPCSTR effect)
{
	if (0 == strcmp(effect, ""))
		return;

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->delEffect(effect);

}

void GameEntity::SetVisible(bool bVisible)
{
	mVisible = bVisible;

	{
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setVisible(
			bVisible);
	}

}

