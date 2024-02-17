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
#include "OGAASNode.h"
#include "OGAASCrossFadeByTimeListNode.h"
#include "OGAASCrossFadeByTimeSlotNode.h"
#include "CharacterCommon.h"


GameEntity::GameEntity(KObject* owner)
{
	mOrphigineObj =
		Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");
	mOrphigineObj->createRenderInstance();
	mOrphigineObj->setData((uint64_t)this);

	mOwner = owner;
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
	mOrphigineObj->setData((uint64_t)this);
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
		// Í½ÊÖ
	case WEAPON_TYPE_NONE:		str = "Unarmed";		break;
		// ³¤±ú
	case WEAPON_TYPE_LONG:		str = "LongHandle";		break;
		// µ¶
	case WEAPON_TYPE_FALCHION:	str = "Falchion";		break;
		// é³
	case WEAPON_TYPE_GAVEL:		str = "Gavel";			break;
		// ¹­¼ý
	case WEAPON_TYPE_BOW:		str = "Bow";			break;
		// »ðÇ¹
	case WEAPON_TYPE_GUN:		str = "Gun";			break;
		// ½£
	case WEAPON_TYPE_SWORD:		str = "Sword";			break;
		// Æì×Ó
	case WEAPON_TYPE_FLAG:		str = "Flag";			break;
		// ÕÈ
	case WEAPON_TYPE_STAFF:		str = "Wand";			break;
		// Ë«ÊÖ
	case WEAPON_TYPE_DOUBLE:	str = "Epee";			break;
		// ³¤Ã¬
	case WEAPON_TYPE_SPEAR:		str = "Spear";			break;
		// Áî
	case WEAPON_TYPE_TOKEN:		str = "Token";			break;
		// åó
	case WEAPON_TYPE_CROSSBOW:	str = "Crossbow";		break;
		// »ðï¥
	case WEAPON_TYPE_FIREGUN:	str = "Firegun";		break;
		// Ê®×Ö¼Ü
	case WEAPON_TYPE_CROSS:		str = "Cross";			break;
		// ·«
	case WEAPON_TYPE_FAN:		str = "Fan";			break;
		// Ë«³Ö
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

void GameEntity::DeleteAllEffect(void)
{
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->delAllEffect();
}

void GameEntity::Destroy(void)
{
	mOrphigineObj->setData(0);
}

bool GameEntity::Attach_Object(
	GameEntity* pObject, LPCTSTR szAttachLocator)
{
	TCHAR szTmp[MAX_PATH];

	szTmp[0] = 0;
	snprintf(szTmp, MAX_PATH, "20065 %s", szAttachLocator);


	
	if (mOrphigineObj && 
		pObject != nullptr )
	{
		GameEntity* pRFObject = (GameEntity*)pObject;

		Orphigine::SkeletonMeshActor* pActorImplObj = 
			(Orphigine::SkeletonMeshActor*)pRFObject->mOrphigineObj.get();
		return((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->attachModelObj(szAttachLocator, pActorImplObj);
	}

	return false;
}


bool GameEntity::Detach_Object(GameEntity* pObject)
{
	if (mOrphigineObj)
	{
		GameEntity* pRFObject = (GameEntity*)pObject;

		Orphigine::SkeletonMeshActor* pActorImplObj =
			(Orphigine::SkeletonMeshActor*)pRFObject->mOrphigineObj.get();

		return((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->detachModelObj(pActorImplObj);
	}

	return false;
}

bool GameEntity::Actor_SetSlotIndex(
	LPCTSTR szSlotName, USHORT uSlotIndex)
{
	if (NULL == szSlotName) return FALSE;

	auto	it = m_mapCharAASNode.find(szSlotName);

	if (it != m_mapCharAASNode.end())
	{
		Orphigine::AASNode* pAASNode = it->second;

		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeList")
		{
			auto* pSlotNode = (Orphigine::AASCrossFadeByTimeListNode*)pAASNode;

			try
			{
				pSlotNode->setActiveChild(uSlotIndex, BLEND_OUT_TIME);
			}
			catch (...)
			{
				if (g_bDebug)
				{
					throw;
				}
			}
			return TRUE;
		}
	}

	Orphigine::SkeletonMeshComponent* pLogicModel = 
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getLogicModel();
	if (pLogicModel)
	{
		Orphigine::AASNode* pAASNode = pLogicModel->findAASNode(szSlotName);
		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeList")
		{
			m_mapCharAASNode[szSlotName] = pAASNode;
			try
			{
				Orphigine::AASCrossFadeByTimeListNode* pSlotNode = (Orphigine::AASCrossFadeByTimeListNode*)pAASNode;
				pSlotNode->setActiveChild(uSlotIndex, BLEND_OUT_TIME);
			}
			catch (...)
			{
				if (g_bDebug)
				{
					throw;
				}
			}
			return TRUE;
		}
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool GameEntity::Actor_SetActionSlot
(
	LPCTSTR szSlotName,
	LPCTSTR szActionName,
	BOOL bLoop,
	FLOAT fRate,
	BOOL bBlendIn,
	BOOL bBlendOut
)
{
	if (NULL == szSlotName || NULL == szActionName) return FALSE;

	FLOAT fBlendInTime = 0.f;

	if (bBlendIn)
	{
		fBlendInTime = BLEND_IN_TIME;
	}

	FLOAT fBlendOutTime = 0.f;

	if (bBlendOut)
	{
		fBlendOutTime = BLEND_OUT_TIME;
	}

	AASNODE_MAP::iterator	it = m_mapCharAASNode.find(szSlotName);

	if (it != m_mapCharAASNode.end())
	{
		Orphigine::AASNode* pAASNode = it->second;

		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeSlot")
		{
			auto* pSlotNode = (Orphigine::AASCrossFadeByTimeSlotNode*)pAASNode;
			if (m_strLastActionName == szActionName)
			{
				pSlotNode->stopUserDefineAnimation(0.f);
			}

			try
			{
				pSlotNode->playUserDefineAnimation(szActionName, fBlendInTime, fBlendOutTime, bLoop == TRUE, fRate, TRUE);
				m_strLastActionName = szActionName;
			}
			catch (...)
			{
				if (g_bDebug)
				{
					throw;
				}
			}
			return TRUE;
		}
	}

	Orphigine::SkeletonMeshComponent* pLogicModel = 
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getLogicModel();
	if (pLogicModel)
	{
		Orphigine::AASNode* pAASNode = pLogicModel->findAASNode(szSlotName);
		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeSlot")
		{
			Orphigine::AASCrossFadeByTimeSlotNode* pSlotNode = (Orphigine::AASCrossFadeByTimeSlotNode*)pAASNode;
			try
			{
				pSlotNode->playUserDefineAnimation(szActionName, fBlendInTime, fBlendOutTime, bLoop == TRUE, fRate, 1);
				m_mapCharAASNode[szSlotName] = pAASNode;
				m_strLastActionName = szActionName;
			}
			catch (...)
			{
				if (g_bDebug)
				{
					throw;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
bool GameEntity::Actor_SetWeaponActionSlot
(
	LPCTSTR szSlotName,
	LPCTSTR szActionName,
	LPCTSTR	szWeaponTypeName,
	BOOL bLoop,
	FLOAT fRate,
	BOOL bBlendIn,
	BOOL bBlendOut
)
{
	if (NULL == szSlotName || NULL == szActionName || NULL == szWeaponTypeName)
		return FALSE;

	FLOAT fBlendInTime = 0.f;

	if (bBlendIn)
	{
		fBlendInTime = BLEND_IN_TIME;
	}

	FLOAT fBlendOutTime = 0.f;

	if (bBlendOut)
	{
		fBlendOutTime = BLEND_OUT_TIME;
	}

	String strSlotName = "Weapon_";
	strSlotName += szSlotName;

	AASNODE_MAP::iterator	it = m_mapWeaponAASNode.find(strSlotName.c_str());

	if (it != m_mapWeaponAASNode.end())
	{
		Orphigine::AASNode* pAASNode = it->second;

		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeSlot")
		{
			Orphigine::AASCrossFadeByTimeSlotNode* pSlotNode = (Orphigine::AASCrossFadeByTimeSlotNode*)pAASNode;

			if (m_strLastActionName == szActionName)
			{
				pSlotNode->stopUserDefineAnimation(0.f);
			}

			try
			{
				pSlotNode->playUserDefineAnimation(szActionName, fBlendInTime, fBlendOutTime, bLoop == TRUE, fRate, 1);
			}
			catch (...)
			{
				if (g_bDebug)
				{
					throw;
				}
			}
			return TRUE;
		}
	}

	Orphigine::SkeletonMeshComponent* pLogicModel = 
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getLogicModel();
	if (pLogicModel)
	{
		Orphigine::SkeletonMeshComponent* pWeaponModel = pLogicModel->getAttributePtr(szWeaponTypeName);
		if (NULL == pWeaponModel)
			return FALSE;

		Orphigine::AASNode* pAASNode = pWeaponModel->findAASNode(szSlotName);
		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeSlot")
		{
			m_mapWeaponAASNode[strSlotName.c_str()] = pAASNode;

			Orphigine::AASCrossFadeByTimeSlotNode* pSlotNode = (Orphigine::AASCrossFadeByTimeSlotNode*)pAASNode;

			try
			{
				pSlotNode->playUserDefineAnimation(szActionName, fBlendInTime, fBlendOutTime, bLoop == TRUE, fRate, 1);
			}
			catch (...)
			{
				if (g_bDebug)
				{
					throw;
				}
			}
			return TRUE;
		}
	}

	return FALSE;
}

void GameEntity::SetScaleFactor(FLOAT fScale)
{
	if (fabs(m_fScale - fScale) < 0.001)
		return;
	m_fScale = fScale;


	auto fvScaleFactor = m_fvDefaultScale * fScale;
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setScaleFactor(fvScaleFactor);

}

Orphigine::Spell* GameEntity::GetCurrentSkill()
{
	return((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getCurrentSkill();
}

void GameEntity::ChangeModelActionRate(FLOAT fRate)
{
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setAASGlobalAnimRate(fRate);

}
