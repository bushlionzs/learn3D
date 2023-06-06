#include "stdafx.h"
#include "OGActorFactoryManager.h"
#include "OGSKeletonMeshActor.h"
#include "OGImpactManager.h"
#include "kcharacter.h"
#include "OGAASCrossFadeByTimeListNode.h"
#include "OGAASCrossFadeByTimeSlotNode.h"
#include "OGSpell.h"
#include "engine_manager.h"
#include "GameTableData.h"
#include "ActionSetManager.h"
#include "GameTableManager.h"
#include "KTable.h"
#include "KDefine.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "game_scene_manager.h"
#include "game_scene.h"
#include "CharacterCommon.h"
#include "GameEntity.h"
#include "Basics.h"
#include "data/GameDataCharacter.h"
#include "KObjectManager.h"
#include "command/command.h"
#include "DirectlyEffectMgr.h"
#include "OgreRoot.h"

class	PlayerAASAnimPlayCallback: public Orphigine::SkeletonMeshComponent::AASAnimEndCallback
{
public:
	virtual void	onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
		uint64_t info)
	{

	}
};


void MyCallback::onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
	uint64_t info)
{
	KCharacter* character = (KCharacter*)info;
	character->onAnimationEnd(animName, parentNodeType, parentNodeName);
}

const Ogre::String FOBJ_ACTOR_FILE = "logic model name";
KCharacter::KCharacter()
{
	m_fRunBaseSpeed = 0.0f;
	m_fWalkBaseSpeed = 0.0f;

	mPathComponent = new PathComponent(this);
}


bool KCharacter::initialize()
{
	m_nAttachID = INVALID_ID;
	m_bInAir = false;
	m_nCurrCharModelID = INVALID_ID;
	m_nCurrMountModelID = INVALID_ID;
	m_bIsCharBaseLogicEnd = true;
	m_bIsCharActionLogicEnd = true;

	m_nCharBaseState = CAHR_STATE_IDLE;
	m_nCharActionState = CAHR_STATE_IDLE;

	m_nJumpActionState = 0;
	mMainEntity = std::make_shared<GameEntity>();
	UpdateCharBaseData();
	
	return true;
}

void KCharacter::setPosition(
	const Ogre::Vector3& position,
	bool useTerrainHeight)
{
	mGamePosition = position;
	
	Ogre::Vector3 fvEnginePosition;
	EngineManager::getSingleton().positionAxisTrans(GAT_GAME, mGamePosition,
		GAT_ENGINE, fvEnginePosition, useTerrainHeight);

	if(mMainEntity)
		mMainEntity->setEntityPosition(fvEnginePosition);
	

	EngineManager::getSingleton().setMyPosition(fvEnginePosition);

	if (mMountObj)
	{
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setPosition(fvEnginePosition);

		((Orphigine::SkeletonMeshActor*)mMountObj.get())->getLogicModel();
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setVisible(true);
	}
}


const Ogre::Vector3& KCharacter::getPosition()
{
	return mGamePosition;
}

Ogre::Real KCharacter::getDirection()
{
	return mMainEntity->getDirection();
}

void KCharacter::setDirection(float dir)
{
	mMainEntity->setDirection(dir);
	if (mMountObj)
	{
		Ogre::Quaternion qu(Ogre::Radian(dir), Ogre::Vector3::UNIT_Y);
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setOrientation(qu);
	}
	
}





CHARACTER_ACTION getAASNodeActionType(CHARACTER_AAS_NODE eNode)
{
	CHARACTER_ACTION eAction = CA_INVALID;
	switch (eNode)
	{
	case AASSLOT_DOWN_IDLE_ATTACK:		eAction = CA_ATTACK;		break;
	case AASSLOT_DOWN_IDLE_MOOD:		eAction = CA_MOOD;			break;
	case AASSLOT_DOWN_IDLE_DACE:		eAction = CA_DANCE;			break;
	case AASSLOT_DOWN_IDLE_DAMAGE:		eAction = CA_DAMAGE;		break;
	case AASSLOT_DOWN_IDLE_STAND:		eAction = CA_IDLE;			break;
	case AASSLOT_DOWN_IDLE_JUMP:		eAction = CA_JUMP;			break;

	case AASSLOT_DOWN_MOVE_ATTACK:		eAction = CA_ATTACK;		break;
	case AASSLOT_DOWN_MOVE_MOOD:		eAction = CA_MOOD;			break;
	case AASSLOT_DOWN_MOVE_DAMAGE:		eAction = CA_DAMAGE;		break;
	case AASSLOT_DOWN_MOVE_JUMP:		eAction = CA_JUMP;			break;

	case AASSLOT_UP_IDLE_ATTACK:		eAction = CA_ATTACK;		break;
	case AASSLOT_UP_IDLE_MOOD:			eAction = CA_MOOD;			break;
	case AASSLOT_UP_IDLE_DAMAGE:		eAction = CA_DAMAGE;		break;
	case AASSLOT_UP_IDLE_STAND:			eAction = CA_IDLE;			break;
	case AASSLOT_UP_IDLE_JUMP:			eAction = CA_JUMP;			break;

	case AASSLOT_UP_MOVE_ATTACK:		eAction = CA_ATTACK;		break;
	case AASSLOT_UP_MOVE_MOOD:			eAction = CA_MOOD;			break;
	case AASSLOT_UP_MOVE_DAMAGE:		eAction = CA_DAMAGE;		break;
	case AASSLOT_UP_MOVE_JUMP:			eAction = CA_JUMP;			break;
	}
	return eAction;
}

void KCharacter::onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName)
{
	::OutputDebugString(animName);
	::OutputDebugString("\n");

	int32_t type = mASSNodeTypeMap[parentNodeName];

	CHARACTER_ACTION eActionType = getAASNodeActionType((CHARACTER_AAS_NODE)type);
	eActionType = CA_IDLE;
	if (eActionType == CA_IDLE)
	{
		ChangeAction(CA_MOOD, 0.f);
		ChangeAction(CA_MOVING, 0.0f);
		ChangeAction(CA_JUMP, 0.0f);
		ChangeAction(CA_MOVING, 0.0f);
		ChangeAction(CA_POSTURE, 0.0f);
		ChangeAction(CA_GUARD, 0.0f);
		setCharActionSlot(AASSLOT_DOWN_IDLE_STAND, BASE_ACTION_N_STAND);
		setCharActionSlot(AASSLOT_UP_IDLE_STAND, BASE_ACTION_N_STAND);
	}
}

void KCharacter::ChangeAction(int32 nActionType, FLOAT fDegree, int32 nActionID, FLOAT fSpeed, BOOL bShowWeapon)
{
	//
	float fCharDegree = fDegree;
	if (INVALID_ID != nActionID)
	{
		const _TABLE_CHARACTER_ACTION_SET* pActionSet = 
			(const _TABLE_CHARACTER_ACTION_SET*)(m_pCharActionSet->Search_Index_EQU(nActionID));
		if (pActionSet)
		{
			fCharDegree = pActionSet->nMonitoringDegree;
		}
	}

	mMainEntity->setAnimationDegree(nActionType, fCharDegree);
	//change mount action
	

	if (mMountObj)
	{
		float fMountDegree = fDegree;
		if (INVALID_ID != nActionID)
		{
			const _TABLE_CHARACTER_ACTION_SET* pActionSet =
				(const _TABLE_CHARACTER_ACTION_SET*)(m_pMountActionSet->Search_Index_EQU(nActionID));
			if (pActionSet)
			{
				fMountDegree = pActionSet->nMonitoringDegree;
			}
		}
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setAdvancedAnimationSystemMonitoringDegree(
			Orphigine::SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree(nActionType), fDegree);

	}
	
}

LPCSTR KCharacter::getCharActionNameByActionSetID(int32_t nActionSetID, int32_t nWeaponType, BOOL* pbHideWeapon, int32_t* pnAppointedWeaponID)
{
	if (NULL == m_pCharActionSet)
		return NULL;

	if (NULL == GetActionSetData())
		return NULL;

	if (INVALID_ID == nActionSetID)
		return NULL;

	int32_t nCalcWeaponType = nWeaponType;

	if (nCalcWeaponType < 0 || nCalcWeaponType >= MAX_WEAPON_TYPE_NUMBER)
		return NULL;

	const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pCharActionSet->Search_Index_EQU(nActionSetID));
	if (pActionSet)
	{
		// ��������
		if (pbHideWeapon)
			*pbHideWeapon = pActionSet->bHideWeapon;

		// ָ������
		if (pnAppointedWeaponID)
			*pnAppointedWeaponID = pActionSet->nAppointedWeaponID;


		// ȡ��Ӧ���У���ʲô�����Ķ����� Ҳ����Npc �� �ֵĶ�����
		return pActionSet->pWeapon_Set[nCalcWeaponType];
	}
	return NULL;
}

eWEAPON_TYPE KCharacter::getMainWeaponType()
{
	//ENUM_WEAPON_LOCATOR_TYPE weapon_type = WL_RIGHT;
	

	return WEAPON_TYPE_FALCHION;
}


bool KCharacter::setCharActionSlot(
	int32_t nAASNode,
	int32_t nActionID,
	bool bActionBySkill,
	FLOAT fRate,
	bool bLoop,
	bool bBlendIn,
	bool bBlendOut)
{
	const CGameTable* pChar_AAS_NodeTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_AAS_NODE_INFO);
	if (NULL == pChar_AAS_NodeTable)
	{
		return false;
	}

	const _TABLE_AAS_NODE_INFO* pInfo = (const _TABLE_AAS_NODE_INFO*)(pChar_AAS_NodeTable->GetFieldDataByIndex(nAASNode));
	if (pInfo)
	{
		auto pSkill = mMainEntity->getCurrentSpell();
		if (pSkill && bActionBySkill)
		{
			actorSetActionSlot(pInfo->szNodeName, pSkill->getAnimationName().c_str(), bLoop, fRate, bBlendIn, bBlendOut);
			return true;
		}

		const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pCharActionSet->Search_Index_EQU(nActionID));
		if (NULL == pActionSet)
			return false;
		/*if (pActionSet->nIsSkill)
			return false;*/

		LPCTSTR lpszCharActionName = getCharActionNameByActionSetID(nActionID, getMainWeaponType(), NULL, NULL);
		if (lpszCharActionName)
		{
			actorSetActionSlot(pInfo->szNodeName, lpszCharActionName, bLoop, fRate, bBlendIn, bBlendOut);
			return true;
		}
		
	}
	return false;
}

bool KCharacter::actorSetActionSlot
(
	LPCTSTR szSlotName,
	LPCTSTR szActionName,
	bool bLoop,
	FLOAT fRate,
	bool bBlendIn,
	bool bBlendOut
)
{
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
			Orphigine::AASCrossFadeByTimeSlotNode* pSlotNode = (Orphigine::AASCrossFadeByTimeSlotNode*)pAASNode;
			if (mLastActionName == szActionName)
			{
				pSlotNode->stopUserDefineAnimation(0.f);
			}

			
			pSlotNode->playUserDefineAnimation(szActionName, fBlendInTime, fBlendOutTime, bLoop == true, fRate, true);
			mLastActionName = szActionName;
			
			return true;
		}
	}

	Orphigine::SkeletonMeshComponent* pLogicModel = mMainEntity->getLogicModel();
	if (pLogicModel)
	{
		Orphigine::AASNode* pAASNode = pLogicModel->findAASNode(szSlotName);
		if (pAASNode && pAASNode->getType() == "CrossFadeByTimeSlot")
		{
			Orphigine::AASCrossFadeByTimeSlotNode* pSlotNode = (Orphigine::AASCrossFadeByTimeSlotNode*)pAASNode;
		
			pSlotNode->playUserDefineAnimation(szActionName, fBlendInTime, fBlendOutTime, bLoop == TRUE, fRate, 1);
			m_mapCharAASNode[szSlotName] = pAASNode;
			mLastActionName = szActionName;
			
			return true;
		}
	}
	return false;
}

void KCharacter::update(float deltatime)
{
	mPathComponent->update(deltatime);
}

bool KCharacter::startSkill()
{
	// ���þ���״̬
	ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE);
	// ��ʼ���ܶ���
	ChangeAction(CA_ATTACK, 1.0f);
	//125 ɱ����
	//103 ��ͨ����
	int32_t nRandAnimID = 100;
	createSkillImpact(nRandAnimID, mDirection);

	

	float fSpeed = 1.0f;
	bool bLoop = false;
	bool bBlendIn = true;
	bool bBlendout = true;

	setCharActionSlot(AASSLOT_DOWN_IDLE_ATTACK, nRandAnimID, true, fSpeed, bLoop, bBlendIn, bBlendout);
	setCharActionSlot(AASSLOT_DOWN_MOVE_ATTACK, nRandAnimID, true, fSpeed, bLoop, bBlendIn, bBlendout);
	setCharActionSlot(AASSLOT_UP_IDLE_ATTACK, nRandAnimID, true, fSpeed, bLoop, bBlendIn, bBlendout);
	setCharActionSlot(AASSLOT_UP_MOVE_ATTACK, nRandAnimID, true, fSpeed, bLoop, bBlendIn, bBlendout);

	return true;
}

void KCharacter::ChangeActionSpeed(FLOAT fSpeed)
{
	// ����
	if (mMainEntity)
	{
		mMainEntity->ChangeModelActionRate(fSpeed);
	}

	// ����
	if (mMountObj)
	{
		mMountObj->ChangeModelActionRate(fSpeed);
	}
}

bool KCharacter::createSkillImpact(int32_t nActionID, float fDir)
{
	LPCSTR lpszCharActionName = getCharActionNameByActionSetID(nActionID, getMainWeaponType(), NULL, NULL);
	if (lpszCharActionName)
	{
		int priority = 0;
		Ogre::Quaternion rot(Ogre::Radian(fDir), Ogre::Vector3(0.f, 1.0f, 0.f));
		mMainEntity->getSkeletonMeshActor()->createSkill(
			lpszCharActionName, rot, Orphigine::E_ANIM_BOTH, true, false, 0.0f, priority);
		// �����Ƿ��б���������
		Orphigine::Spell* pSkill = mMainEntity->getCurrentSpell();
		if (pSkill)
		{
			return true;
		}
	}
	return false;
}

bool KCharacter::startMood()
{
	ChangeAction(CA_GUARD, 0.f);
	ChangeAction(CA_MOOD, 1.f);
	int nActID = 150;
	bool bLoop = false;
	setCharActionSlot(AASSLOT_DOWN_IDLE_MOOD, nActID, TRUE, 1.f, bLoop);
	setCharActionSlot(AASSLOT_DOWN_MOVE_MOOD, nActID, TRUE, 1.f, bLoop);
	setCharActionSlot(AASSLOT_UP_IDLE_MOOD, nActID, TRUE, 1.f, bLoop);
	setCharActionSlot(AASSLOT_UP_MOVE_MOOD, nActID, TRUE, 1.f, bLoop);
	return true;
}

void KCharacter::createMount()
{
	//mMountObj = Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");
	
	int32_t mountId = 5;

	const CGameTable* pCharMountTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MOUNT);
	if (nullptr == pCharMountTable)
	{
		return;
	}

	const _TABLE_CHARACTER_MOUNT* pMount = (const _TABLE_CHARACTER_MOUNT*)(pCharMountTable->GetFieldDataByIndex(mountId));
	if (nullptr == pMount)
		return;

	// ģ�ͱ�
	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (nullptr == pCharModelTable)
	{
		return;
	}

	const _TABLE_CHARACTER_MODEL* pMountModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(pMount->m_nModelID));


	/*mMountObj->createRenderInstance();

	int32_t nObjID = 105;
	((Orphigine::SkeletonMeshActor*)mMountObj.get())->setSkeletonMeshActorTypeandId((Orphigine::SkeletonMeshActor::TypeEnum)0, nObjID);
	*/
	String mountModelName = pMountModel->m_pszModelName;
	mMountObj->setModelName(mountModelName);
	//


	if (pMountModel != NULL && strlen(pMountModel->m_pszActionSetName_None) > 0)
	{
		m_pMountActionSet = GetActionSetData()->GetActionSetFile(pMountModel->m_pszActionSetName_None);
		if (NULL == m_pMountActionSet)
		{
			OGRE_EXCEPT(0);
		}
	}
	else
	{
		OGRE_EXCEPT(0);
	}

	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(0));
	if (NULL == pCharModel)
	{
		OGRE_EXCEPT(0);
		return;
	}

	LPCSTR pszActionSetFileName = nullptr;
	//update charactor action
	// int32 nCharActionIndex = pMount->m_nCharActionIndex; // �������ʱ�Ķ�����,��Ӧchar_model.tab��mount0~19
	int32 nCharActionIndex = pMount->m_nCharActionIndex;
	if (nCharActionIndex >= 0 && nCharActionIndex < MAX_MOUNT_NUMBER)
	{
		if (strlen(pCharModel->m_apszActionSetName_Mount[nCharActionIndex]) > 0)
		{
			pszActionSetFileName = pCharModel->m_apszActionSetName_Mount[nCharActionIndex];
		}
		else
		{
			pszActionSetFileName = pCharModel->m_pszActionSetName_None;

			//KLThrow("pszActionSetFileName Error! nCharActionIndex=%d, m_nCurrMountModelID=%d ", nCharActionIndex, m_nCurrMountModelID );
		}
	}

	if (pszActionSetFileName && '\0' != pszActionSetFileName[0])
	{
		m_pCharActionSet = GetActionSetData()->GetActionSetFile(pszActionSetFileName);
		if (nullptr == m_pCharActionSet)
		{
			OGRE_EXCEPT(0);
		}
	}
	//attach
	auto locator = GetMountLocatorName(LOCATOR_MOUNT_BACK);
	((Orphigine::SkeletonMeshActor*)mMountObj.get())->attachModelObj(
		locator, mMainEntity->getSkeletonMeshActor());


	ChangeAction(CA_RIDING, 1.0f);
}



void KCharacter::setMountId(int32_t mountId)
{
	if (m_nCurrCharModelID != mountId)
	{
		m_nCurrMountModelID = mountId;
		OnChangeOfMountId();
	}
}



void KCharacter::DoDataEvent_DataID()
{
	UpdateCharBaseData();
	UpdateCharModel();
	if (IsCanUpdateMountByModelID())
	{
		UpdateMountModel();
	}
}

void KCharacter::DoDataEvent_ModelID()
{

}

void KCharacter::DoDataEvent_MountID()
{

}

void KCharacter::DoDataEvent_Dir()
{

}

void KCharacter::DoDataEvent_Level()
{

}

void KCharacter::DoDataEvent_MoveSpeed()
{

}

void KCharacter::DoDataEvent_Equip(PLAYER_EQUIP point)
{
	KCharatcterBaseData* pCharacterData = GetCharacterData();

	// ��װ
	if (HEQUIP_SUIT == point)
	{
		UpdateFashion();
	}
	else
	{
		UpdateEquip(point);
	}
}

void KCharacter::OnDataChanged_FaceImage()
{

}

void KCharacter::OnDataChanged_HairMesh()
{

}

void KCharacter::OnDataChanged_FaceMesh()
{

}


int32_t KCharacter::GetCurrCharModelID()
{
	return m_nCurrCharModelID;
}


void KCharacter::OnChangeOfMountId()
{

}


void KCharacter::UpdateModel_CharActionSet(void)
{
	m_pCharActionSet = NULL;

	if (NULL == GetActionSetData())
		return;

	if (INVALID_ID == m_nCurrCharModelID)
		return;

	//	TABLE_DEFINEHANDLE(s_pCharModelDBC, TABLE_CHARACTER_MODEL)
	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return;

	// ������Ч
	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(
		pCharModelTable->GetFieldDataByIndex(m_nCurrCharModelID));
	if (NULL == pCharModel)
	{
		OGRE_EXCEPT(0);
		return;
	}

	mModelName = pCharModel->m_pszModelName;

	//�������ID�Ƿ���Ч
	const CGameTable* pCharMountTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MOUNT);
	if (NULL == pCharMountTable)
		return;

	const char* pszActionSetFileName = NULL;

	// ������Ч���������϶�����
	const _TABLE_CHARACTER_MOUNT* pMount = (const _TABLE_CHARACTER_MOUNT*)(
		pCharMountTable->GetFieldDataByIndex(m_nCurrMountModelID));
	if (pMount)
	{
		const _TABLE_CHARACTER_MODEL* pMountModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(pMount->m_nModelID));
		if (pMountModel)
		{
			mMountModelName = pMountModel->m_pszModelName;
		}
		int32 nCharActionIndex = pMount->m_nCharActionIndex; // �������ʱ�Ķ�����,��Ӧchar_model.tab��mount0~19

		if (nCharActionIndex >= 0 && nCharActionIndex < MAX_MOUNT_NUMBER)
		{
			if (strlen(pCharModel->m_apszActionSetName_Mount[nCharActionIndex]) > 0)
			{
				pszActionSetFileName = pCharModel->m_apszActionSetName_Mount[nCharActionIndex];
			}
			else
			{
				pszActionSetFileName = pCharModel->m_pszActionSetName_None;

				//KLThrow("pszActionSetFileName Error! nCharActionIndex=%d, m_nCurrMountModelID=%d ", nCharActionIndex, m_nCurrMountModelID );
			}
		}
		else
		{
			pszActionSetFileName = pCharModel->m_pszActionSetName_None;
		}
	}
	// ��Ч���������¶�����
	else
	{
		pszActionSetFileName = pCharModel->m_pszActionSetName_None;
	}

	// ���صĶ���
	if (pszActionSetFileName && '\0' != pszActionSetFileName[0])
	{
		m_pCharActionSet = GetActionSetData()->GetActionSetFile(pszActionSetFileName);
		if (NULL == m_pCharActionSet)
		{
			OGRE_EXCEPT(0);
		}
	}
	else
	{
		OGRE_EXCEPT(0);
	}
}

void KCharacter::UpdateModel_MountActionSet(void)
{
	if (nullptr == GetActionSetData())
		return;

	m_pMountActionSet = nullptr;

	const CGameTable* pCharMountTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MOUNT);
	if (NULL == pCharMountTable)
	{
		return;
	}

	const _TABLE_CHARACTER_MOUNT* pMount = (const _TABLE_CHARACTER_MOUNT*)(pCharMountTable->GetFieldDataByIndex(m_nCurrMountModelID));

	if (pMount)
	{
		const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
		if (NULL == pCharModelTable)
		{
			return;
		}

		const _TABLE_CHARACTER_MODEL* pMountModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(pMount->m_nModelID));
		if (pMountModel != NULL && strlen(pMountModel->m_pszActionSetName_None) > 0)
		{
			m_pMountActionSet = GetActionSetData()->GetActionSetFile(pMountModel->m_pszActionSetName_None);
			if (NULL == m_pMountActionSet)
			{
				OGRE_EXCEPT(0);
			}
		}
		else
		{
			OGRE_EXCEPT(0);
		}
	}
}

void KCharacter::createCharRenderInterface(void)
{
	mMainEntity->setModelName(mModelName);
	// ����Ⱦ��ˢ��λ��
	setPosition(mGamePosition);
	mMainEntity->SetModelType(CHAR_MODEL_CHAR);

	if (mWeaponname.empty())
	{
		mWeaponname = "Falchion";
	}
	// ���������������
	mMainEntity->setWeapon(mWeaponname);

	// ���ü�����ɻص�

	mMainEntity->getLogicModel()->setAASAnimEndCallback(new PlayerAASAnimPlayCallback, (uint64_t)this);

}

KCharatcterBaseData* KCharacter::GetCharacterData(void)
{
	if(nullptr == m_pCharacterData)
		m_pCharacterData = new KCharatcterBaseData(this);
	return m_pCharacterData;
}

void KCharacter::ChangeWeaponEffect(
	GameEntity::eWEAPATTR ePart,
	LPCTSTR szEffectName, 
	LPCTSTR nLocatorName, 
	uint32 color)
{
	if ((0 == strcmp(nLocatorName, " ")) || (0 == strcmp(szEffectName, " ")))
	{
		KLThrow("20003");
	}


	if ((NULL == szEffectName) || (NULL == nLocatorName))
		return;
	if ((0 == strcmp(szEffectName, "")) || (0 == strcmp(nLocatorName, "")))
		return;
	if ((0 == strcmp(szEffectName, "-1")) || (0 == strcmp(nLocatorName, "-1")))
		return;


	switch (ePart)
	{
	case GameEntity::WEAP_RIGHT:
		mMainEntity->RightWeapon_SetEffect(
			szEffectName, nLocatorName, color, this->getEffectPriority());
		break;
	case GameEntity::WEAP_LEFT:
		mMainEntity->LeftWeapon_SetEffect(
			szEffectName, nLocatorName, color, this->getEffectPriority());
		break;
	case GameEntity::WEAP_LEFT_SHIELD:
		mMainEntity->Shield_SetEffect(
			szEffectName, nLocatorName, color, this->getEffectPriority());
		break;
	}
}

int32 KCharacter::getEffectPriority()
{
	int32 priority = 3;

	if (mObjectType == ObjectType_PlayerOfMe)
		priority = 0;

	return priority;
}

eWEAPON_TYPE KCharacter::GetMainWeaponType()
{
	ENUM_WEAPON_LOCATOR_TYPE weapon_type = WL_RIGHT;
	if (CHAR_BASE_TYPE_NPC != GetCharacterType() && GetCharacterData())
	{
		if (PROFESSION_QISHE == GetCharacterData()->GetProfession())
			weapon_type = WL_LEFT;
	}

	return GetWeaponType(weapon_type);
}

eWEAPON_TYPE KCharacter::GetWeaponType(ENUM_WEAPON_LOCATOR_TYPE loc) const
{
	if (WL_RIGHT == loc)
		return m_theRWeaponType;
	else if (WL_LEFT == loc)
		return m_theLWeaponType;

	return WEAPON_TYPE_INVALID;
}

void KCharacter::SetWeaponType(
	eWEAPON_TYPE type, 
	ENUM_WEAPON_LOCATOR_TYPE loc)
{
	switch (loc)
	{
	case WL_RIGHT:
		m_theRWeaponType = type;
		break;
	case WL_LEFT:
		m_theLWeaponType = type;
		break;
	case WL_BOTH:
		m_theRWeaponType = type;
		m_theLWeaponType = type;
		break;
	};
}

void KCharacter::SetWeaponAction(LPCTSTR szWeaponAnimName)
{
	m_pWeaponActionSet = NULL;

	if (szWeaponAnimName && GetActionSetData())
	{
		m_pWeaponActionSet = GetActionSetData()->GetActionSetFile(szWeaponAnimName);
	}
}

bool KCharacter::IsModelCreateAllCompleted()
{
	if (nullptr == mMainEntity->getLogicModel())
	{
		return false;
	}
	// ��obj. ��һ�δ���ʱ�ż��. ֻ��⸸obj
	if (IsFollowAttach())
	{
		KObject* pObj = (KObject*)KObjectManager::GetSingleton().getObject(
			GetCharacterData()->Get_AttachID());
		if (pObj)
		{
			if (FALSE == ((KCharacter*)pObj)->IsModelCreateAllCompleted())
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

bool KCharacter::IsFollowAttach()
{
	if (GetCharacterData() && 
		INVALID_ID != GetCharacterData()->Get_AttachID())
	{
		return TRUE;
	}
	return FALSE;
}

void KCharacter::ReleaseCharRenderInterface(void)
{
	//DetachMount();


	mMainEntity->DeleteAllEffect();
	mMainEntity->Destroy();
}


int32_t KCharacter::GetAttachModelNum()
{
	int32 nCount = 0;


	if (INVALID_ID != GetCharacterData()->Get_AttachID())
		++nCount;

	return nCount;
}

bool KCharacter::IsCanUpdateMountByModelID()
{
	int32 nModelID = GetCharacterData()->Get_ModelID();
	if (INVALID_ID == nModelID)
		return TRUE;

	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return TRUE;

	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(nModelID));
	if (NULL == pCharModel)
		return TRUE;

	if (0 <= pCharModel->m_nCheckMount)
		return TRUE;

	return FALSE;
}

bool KCharacter::UpdateMountingState()
{
		if (mMountEntity && mMainEntity)
		{
			// �Ƿ񱻰�
			if (m_nAttachID != INVALID_ID)
			{
				return false;
			}
			// �Ƿ����
			if (!IsCanUpdateMountByModelID())
			{
				return false;
			}
			// �ظ����ű���, ����ָ��һ��Ҫ�ڰ�ָ��֮ǰִ��
			//KObject::SetModel_Scale(1.f);

			// ��
			mMountEntity->Detach_Object(mMainEntity.get());
			mMountEntity->Attach_Object(mMainEntity.get(), GetMountLocatorName(LOCATOR_MOUNT_BACK));

			// ����Ķ���
			UpdateModel_CharActionSet();
			// �����Ķ���
			UpdateModel_WeaponActionSet();

			// �������϶���
			BeginRiding();


			return TRUE;
		}

	return FALSE;

}

bool KCharacter::AddAttachMember(int32 nObjId)
{
	return true;
}

// --------------------------------------------------------------------------
bool KCharacter::RemoveAttachMember(int32 nObjId)
{
	return true;
}

void KCharacter::StopMove()
{
	
}

KCharCmdDate_Logic* KCharacter::GetNextCommand(CHARATER_LOGIC_TYPE nLogicTag)
{
	// �����߼�
	if (CHAR_LOGIC_BASE == nLogicTag)
	{
		if (!m_listBaseStateCommand.empty())
		{
			KCharCmdDate_Logic* pCmd = m_listBaseStateCommand.front();
			m_listBaseStateCommand.pop_front();
			return pCmd;
		}
	}
	// ��Ϊ�߼�
	else
	{
		if (!m_listActionStateCommand.empty())
		{
			KCharCmdDate_Logic* pCmd = m_listActionStateCommand.front();
			m_listActionStateCommand.pop_front();
			return pCmd;
		}
	}

	return NULL;
}

int32 KCharacter::GetSpecifyMountIDByModleID()
{
	int32 nModelID = GetCharacterData()->Get_ModelID();
	if (INVALID_ID == nModelID)
		return INVALID_ID;

	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return INVALID_ID;

	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(nModelID));
	if (NULL == pCharModel)
		return INVALID_ID;

	if (0 >= pCharModel->m_nCheckMount)
		return INVALID_ID;

	return pCharModel->m_nCheckMount;
}


void KCharacter::UpdateMountModel(void)
{
	if (NULL == GetCharacterData())
		return;

	if (INVALID_ID != m_nAttachID)
		return;

	int32 nMountID = GetCharacterData()->Get_MountID();
	if (INVALID_ID != nMountID)
	{
		int32 nModelID = GetCharacterData()->Get_ModelID();
		if (INVALID_ID != nModelID)
		{
			// ������ʱ���Ƿ�ָ�������<0����� >0ָ����� =0��ǰ����
			int32 nSpecifyMountID = GetSpecifyMountIDByModleID();
			if (0 > nSpecifyMountID)
			{
				return;
			}
			else if (0 < nSpecifyMountID)
			{
				nMountID = nSpecifyMountID;
			}
		}
	}
	if (m_nCurrMountModelID == nMountID)
		return;

	const CGameTable* pCharMountTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MOUNT);
	if (NULL == pCharMountTable)
		return;

	const _TABLE_CHARACTER_MOUNT* pCharMount = (const _TABLE_CHARACTER_MOUNT*)(pCharMountTable->GetFieldDataByIndex(nMountID));

	// ����ID��Ч������������
	if (NULL == pCharMount)
	{
		// ����
		//Dismount();
	}
	else
	{
		// ����
		//Mounting(CreateMountRenderInterface(nMountID), nMountID);
	}

	UpdateModel_State();
}

void KCharacter::UpdateAttached()
{
	int32 nAttachID = GetCharacterData()->Get_AttachID();
	if (INVALID_ID != nAttachID)
	{
		// ���ؼ�ģ
		
	}
	if (m_nAttachID != nAttachID)
	{
		if (INVALID_ID != m_nAttachID)
		{
			// ֪ͨ��������
			KObject* pObj = KObjectManager::GetSingleton().getObject(m_nAttachID);
			if (pObj)
			{
				((KCharacter*)pObj)->RemoveAttachMember(getId());
			}
		}
		if (INVALID_ID != nAttachID)
		{
			// ֪ͨ�����
			KObject* pObj = KObjectManager::GetSingleton().getObject(nAttachID);
			
			((KCharacter*)pObj)->AddAttachMember(getId());
			
			// ֹͣ�ƶ��߼�
			StopMove();

		}
		//  �����
		else
		{
			// ��������
			UpdateMountModel();

			auto pos = getPosition();

			Ogre::Vector2 pos2d(pos.x, pos.z);
			mPathComponent->calculateNodePos(pos2d, 0.0f);
		}
	}
}

void KCharacter::UpdateModel_Attach()
{
	// ���������
	UpdateMountingState();

	// ���¸���
	UpdateAttached();

}

bool KCharacter::IsStopped_CharacterState(
	CHARATER_LOGIC_TYPE nLogicTag) const
{
	if (CHAR_LOGIC_BASE == nLogicTag)
	{
		return m_bIsCharBaseLogicEnd;
	}
	else
	{
		return m_bIsCharActionLogicEnd;
	}
}

CHARATER_STATE_TYPE KCharacter::GetCharacterState(
	CHARATER_LOGIC_TYPE nLogicTag) const
{
	if (CHAR_LOGIC_BASE == nLogicTag)
	{
		return m_nCharBaseState;
	}
	else
	{
		return m_nCharActionState;
	}
}

bool KCharacter::IsFightState(void) const
{ 
	return mFightStateTime > 0;
}

bool KCharacter::BeginIdle(void)
{
	// ��Ծʱ�������ƶ�����
	if (IsJumping())
		return FALSE;

	EndJump();
	ChangeAction(CA_MOVING, 0.0f, INVALID_ID, 1.f, FALSE);			// ���÷��ƶ�״̬	

	if (mObjectType == ObjectType_PlayerOfMe)
	{
		ChangeAction(CA_POSTURE, 0.0f, INVALID_ID, 1.f, FALSE);		// ����վ��״̬
		// ����
		if (IsFightState())
		{
			ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE, 1.f, FALSE);	// ���þ���״̬

			SetActionSlot(AASSLOT_DOWN_IDLE_STAND, BASE_ACTION_N_STAND);
			SetActionSlot(AASSLOT_UP_IDLE_STAND, BASE_ACTION_N_STAND);
		}
		// �Ǿ���
		else
		{
			ChangeAction(CA_GUARD, 0.0f, INVALID_ID, 1.0f, FALSE);	// ���÷Ǿ���״̬

			// ���ж���
			if (0 == rand() % 10)
			{
				int32 nIdleActionId = BASE_ACTION_N_IDLE_1 + rand() % 5;
				SetActionSlot(AASSLOT_DOWN_IDLE_STAND, nIdleActionId);
				SetActionSlot(AASSLOT_UP_IDLE_STAND, nIdleActionId);
			}
			// վ������
			else
			{
				SetActionSlot(AASSLOT_DOWN_IDLE_STAND, BASE_ACTION_N_STAND);
				SetActionSlot(AASSLOT_UP_IDLE_STAND, BASE_ACTION_N_STAND);
			}
		}
	}
	// �����
	else
	{
		ChangeAction(CA_POSTURE, 0.0f, INVALID_ID);		// ����վ��״̬
		// ����
		if (IsFightState())
		{
			ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE);	// ���þ���״̬
		}
		// (��ƽ)վ��
		else
		{
			ChangeAction(CA_GUARD, 0.0f, BASE_ACTION_N_STAND);	// ��������״̬
		}
	}
	return TRUE;
}
// --------------------------------------------------------------------------
bool KCharacter::EndIdle(void)
{
	return TRUE;
}
// --------------------------------------------------------------------------
// �ƶ�
bool KCharacter::BeginMove(bool bPlayMoveSound)
{
	if (NULL == GetCharacterData())
		return FALSE;

	// ��Ծʱ�������ƶ�����
	if (IsJumping())
		return FALSE;

	EndJump();
	ChangeAction(CA_MOVING, 1.0f);

	if (MOVE_MODE_WALK == GetCharacterData()->Get_MoveActionMode())
	{
		// ��
		ChangeAction(CA_WALK, 1.0f, BASE_ACTION_N_WALK);
		StopWalkSound();
	}
	else if (MOVE_MODE_RUN == GetCharacterData()->Get_MoveActionMode())
	{
		// ��
		ChangeAction(CA_WALK, 1.0f, BASE_ACTION_N_RUN);

		if (bPlayMoveSound)
		{
			ReadyPlayWalkSound();
		}
	}
	ChangeActionSpeed(GetMoveRate());

	return TRUE;
}
// --------------------------------------------------------------------------
bool KCharacter::EndMove(void)
{
	ChangeAction(CA_MOVING, 0.0f);

	ChangeActionSpeed(1.f);

	// ��ֹ�ƶ�����
	StopWalkSound();

	return TRUE;
}

void KCharacter::ModifyMove(void)
{
	if (GetCharacterState(CHAR_LOGIC_BASE) != CAHR_STATE_MOVE)
		return;

	KCharCmdDate_Move* pMoveCommand = (KCharCmdDate_Move*)GetBaseStateCommand();
	if (pMoveCommand != NULL && pMoveCommand->GetNodeCount() > 0)
	{
		// ���ǲ��߻�ͷ·����˲��
		BOOL bAdjustPos = FALSE;
		GLPos posAdjust;

		// ��ǰ�����������ƶ�����Ľڵ���
		if (m_StateDate_Move.m_nCurrentNodeIndex >= pMoveCommand->GetNodeCount())
		{
			const GLPos* paPos = pMoveCommand->GetNodeList();
			int32 nEndNodeIndex = pMoveCommand->GetNodeCount() - 1;
			// ȡ���һ��λ��
			posAdjust = paPos[nEndNodeIndex];

			bAdjustPos = TRUE;
		}
		// ��ǰΪ���ڵ�
		else if (m_StateDate_Move.m_nCurrentNodeIndex == pMoveCommand->GetNodeCount() - 1)
		{
			const GLPos* paPos = pMoveCommand->GetNodeList();
			int32 nEndNodeIndex = pMoveCommand->GetNodeCount() - 1;
			GLPos posCommandTarget = paPos[nEndNodeIndex];

			FLOAT fLenCSTarget = fabsf(m_StateDate_Move.m_posSaveTarget.m_fX - posCommandTarget.m_fX)
				+ fabsf(m_StateDate_Move.m_posSaveTarget.m_fZ - posCommandTarget.m_fZ);

			// Ŀ���䶯��
			if (fLenCSTarget > 0.01f)
			{
				FLOAT fSaveToServerDist = Ogre::Vector2(m_StateDate_Move.m_posSaveTarget.m_fX, m_StateDate_Move.m_posSaveTarget.m_fZ).distance(
					Ogre::Vector2(posCommandTarget.m_fX, posCommandTarget.m_fZ));

				FLOAT fSaveToCurrentDist = Ogre::Vector2(m_StateDate_Move.m_posSaveTarget.m_fX, m_StateDate_Move.m_posSaveTarget.m_fZ).distance(
					Ogre::Vector2(getPosition().x, getPosition().z));

				// ��������˷�������������Ŀ��㲻��·���ϵ����
				if (fSaveToServerDist - fSaveToCurrentDist >= 0.0f)
				{
					posAdjust = posCommandTarget;
					bAdjustPos = TRUE;
				}

				m_StateDate_Move.m_posSaveTarget.m_fX = posCommandTarget.m_fX;
				m_StateDate_Move.m_posSaveTarget.m_fZ = posCommandTarget.m_fZ;
			}
		}

		// ��Ҫ����
		if (bAdjustPos)
		{
			ModifyCurrPos(Ogre::Vector2(posAdjust.m_fX, posAdjust.m_fZ));

			ShutDown_CharacterState(CHAR_LOGIC_BASE);


		}
	}
}

bool KCharacter::DoJump(void)
{
	if (IsDie())
		return false;

	if (m_nAttachID != INVALID_ID || IsFollowAttach())
		return false;

	KCharatcterBaseData* pCharacterData = GetCharacterData();
	if (pCharacterData == NULL)
		return false;

	if (pCharacterData->Get_IsInStall())
		return false;

	BeginJump();
	//SetProjectile(fabs(ACCELERATION_OF_GRAVITY) * 1.f * 0.5f);

	return TRUE;
}

bool KCharacter::IsJumping() const
{
	return m_bInAir;
}

bool KCharacter::BeginJump()
{
	ChangeAction(CA_MOVING, 1.f);
	ChangeAction(CA_JUMP, 1.f);

	SetSlotIndex(AASSLOT_DOWN_IDLE_JUMP, BASE_ACTION_N_JUMP);

	StopWalkSound();
	SetJumpActionState(ENUM_CHAR_JUMP_STATE_JUMPING);
	return true;
}

bool KCharacter::EndJump()
{
	ChangeAction(CA_MOVING, 0.f);
	ChangeAction(CA_JUMP, 0.f);

	SetJumpActionState(ENUM_CHAR_JUMP_STATE_INVALID);
	return TRUE;
}

bool KCharacter::BeginRiding(void)
{
	ChangeAction(CA_RIDING, 1.0f);

	return TRUE;
}

bool KCharacter::IsDie(void)
{
	if (GetCharacterState(CHAR_LOGIC_BASE) == CAHR_STATE_DEAD)
	{
		return true;
	}
	else if (GetCharacterData())
	{
		return GetCharacterData()->IsDie();
	}
	return false;
}

bool	KCharacter::SetActionSlot(
	int32 nAASNode,
	int32 nActionID,
	BOOL bActionBySkill,
	FLOAT fRate,
	BOOL bLoop,
	BOOL bBlendIn,
	BOOL bBlendOut)
{
	// �����������
	SetWeaponActionSlot(nAASNode, nActionID, bActionBySkill, fRate, bLoop, bBlendIn, bBlendOut);

	// ������ﶯ��
	SetMountActionSlot(nAASNode, nActionID, bActionBySkill, fRate, bLoop, bBlendIn, bBlendOut);

	// ������ﶯ��
	return SetCharActionSlot(nAASNode, nActionID, bActionBySkill, fRate, bLoop, bBlendIn, bBlendOut);

}
// ��������Ӷ���
bool	KCharacter::SetCharActionSlot(
	int32 nAASNode,
	int32 nActionID,
	BOOL bActionBySkill,
	FLOAT fRate,
	BOOL bLoop,
	BOOL bBlendIn,
	BOOL bBlendOut)
{
	const CGameTable* pChar_AAS_NodeTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_AAS_NODE_INFO);
	if (NULL == pChar_AAS_NodeTable)
	{
		return FALSE;
	}

	const _TABLE_AAS_NODE_INFO* pInfo = (const _TABLE_AAS_NODE_INFO*)(pChar_AAS_NodeTable->GetFieldDataByIndex(nAASNode));
	if (pInfo)
	{
		Orphigine::Spell* pSkill = mMainEntity->GetCurrentSkill();
		if (pSkill && bActionBySkill)
		{
			mMainEntity->Actor_SetActionSlot(pInfo->szNodeName, pSkill->getAnimationName().c_str(), bLoop, fRate, bBlendIn, bBlendOut);
			return true;
		}
		else
		{
			if (NULL == GetActionSetData())
				return FALSE;

			if (NULL == m_pCharActionSet)
				return FALSE;

			const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pCharActionSet->Search_Index_EQU(nActionID));
			if (NULL == pActionSet)
				return FALSE;
			if (pActionSet->nIsSkill)
				return FALSE;

			LPCTSTR lpszCharActionName = GetCharActionNameByActionSetID(nActionID, GetMainWeaponType(), NULL, NULL);
			if (lpszCharActionName)
			{
				mMainEntity->Actor_SetActionSlot(pInfo->szNodeName, lpszCharActionName, bLoop, fRate, bBlendIn, bBlendOut);
				return TRUE;
			}
		}
	}
	return FALSE;
}

// ������
bool	KCharacter::SetMountActionSlot(
	int32 nAASNode,
	int32 nActionID,
	BOOL bActionBySkill,
	FLOAT fRate,
	BOOL bLoop,
	BOOL bBlendIn,
	BOOL bBlendOut)
{
	if (NULL == GetActionSetData())
		return FALSE;

	if (NULL == m_pMountActionSet)
		return FALSE;

	const CGameTable* pChar_AAS_NodeTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_AAS_NODE_INFO);
	if (NULL == pChar_AAS_NodeTable)
	{
		return FALSE;
	}

	const _TABLE_AAS_NODE_INFO* pInfo = (const _TABLE_AAS_NODE_INFO*)(pChar_AAS_NodeTable->GetFieldDataByIndex(nAASNode));
	if (pInfo)
	{

		const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pMountActionSet->Search_Index_EQU(nActionID));
		if (NULL == pActionSet)
			return FALSE;
		if (pActionSet->nIsSkill)
			return FALSE;

		LPCTSTR lpszCharActionName = GetMountActionNameByActionSetID(nActionID);
		if (lpszCharActionName)
		{
			mMountObj->Actor_SetActionSlot(pInfo->szNodeName, lpszCharActionName, bLoop, fRate, bBlendIn, bBlendOut);
			return TRUE;
		}
	}
	return FALSE;
}

// ������
bool	KCharacter::SetWeaponActionSlot(
	int32 nAASNode,
	int32 nActionID,
	BOOL bActionBySkill,
	FLOAT fRate,
	BOOL bLoop,
	BOOL bBlendIn,
	BOOL bBlendOut)
{
	if (NULL == GetMainWeaponTypeName())
		return FALSE;

	if (NULL == GetActionSetData())
		return FALSE;

	if (NULL == m_pWeaponActionSet)
		return FALSE;

	const CGameTable* pChar_AAS_NodeTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_AAS_NODE_INFO);
	if (NULL == pChar_AAS_NodeTable)
	{
		return FALSE;
	}

	const _TABLE_AAS_NODE_INFO* pInfo = (const _TABLE_AAS_NODE_INFO*)(pChar_AAS_NodeTable->GetFieldDataByIndex(nAASNode));
	if (pInfo)
	{
		const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pWeaponActionSet->Search_Index_EQU(nActionID));
		if (NULL == pActionSet)
			return FALSE;
		if (pActionSet->nIsSkill)
			return FALSE;

		LPCTSTR lpszCharActionName = GetWeaponActionNameByActionSetID(nActionID, GetMainWeaponType());
		if (lpszCharActionName)
		{
			mMainEntity->Actor_SetWeaponActionSlot(pInfo->szNodeName, lpszCharActionName, GetMainWeaponTypeName(), bLoop, fRate, bBlendIn, bBlendOut);
			return TRUE;
		}
	}
	return FALSE;
}

LPCSTR KCharacter::GetMainWeaponTypeName()
{
	switch (GetMainWeaponType())
	{
	case WEAPON_TYPE_INVALID:
	case WEAPON_TYPE_NONE:
		return NULL;
	case WEAPON_TYPE_BOW:
		return g_szIDSTR_CURRENT_LEFTWEAPON;
	default:
		return g_szIDSTR_CURRENT_RIGHTWEAPON;
	}
	return NULL;
}

LPCSTR KCharacter::GetCharActionNameByActionSetID(
	int32 nActionSetID, 
	int32 nWeaponType, 
	BOOL* pbHideWeapon, 
	int32* pnAppointedWeaponID)
{
	if (NULL == m_pCharActionSet)
		return NULL;

	if (NULL == GetActionSetData())
		return NULL;

	if (INVALID_ID == nActionSetID)
		return NULL;

	int32 nCalcWeaponType = nWeaponType;

	if (nCalcWeaponType < 0 || nCalcWeaponType >= MAX_WEAPON_TYPE_NUMBER)
		return NULL;

	const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pCharActionSet->Search_Index_EQU(nActionSetID));
	if (pActionSet)
	{
		// ��������
		if (pbHideWeapon)
			*pbHideWeapon = pActionSet->bHideWeapon;

		// ָ������
		if (pnAppointedWeaponID)
			*pnAppointedWeaponID = pActionSet->nAppointedWeaponID;

		// ͨ��������������ȡ��������
		if (CHAR_BASE_TYPE_NPC == GetCharacterType())
		{
			assert(false);
		}

		// ȡ��Ӧ���У���ʲô�����Ķ����� Ҳ����Npc �� �ֵĶ�����
		return pActionSet->pWeapon_Set[nCalcWeaponType];
	}
	return NULL;
}

LPCSTR KCharacter::GetMountActionNameByActionSetID(
	int32 nActionSetID)
{
	if (m_pMountActionSet && 
		INVALID_ID != nActionSetID && 
		GetActionSetData())
	{
		const _TABLE_CHARACTER_ACTION_SET* pActionSet = 
			(const _TABLE_CHARACTER_ACTION_SET*)(m_pMountActionSet->Search_Index_EQU(nActionSetID));
		if (pActionSet != NULL)
		{
			return pActionSet->pWeapon_Set[WEAPON_TYPE_NONE];
		}
	}

	return NULL;
}

LPCSTR KCharacter::GetWeaponActionNameByActionSetID(
	int32 nActionSetID, int32 nWeaponType)
{
	if (NULL == GetActionSetData())
		return NULL;

	if (m_pWeaponActionSet && INVALID_ID != nActionSetID && nWeaponType >= 1 && nWeaponType < MAX_WEAPON_TYPE_NUMBER)
	{
		// ͬ���ﶯ�����ʽ��ͬ
		const _TABLE_CHARACTER_ACTION_SET* pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)(m_pWeaponActionSet->Search_Index_EQU(nActionSetID));
		if (pActionSet != NULL)
		{
			return pActionSet->pWeapon_Set[nWeaponType];
		}
	}
	return NULL;
}

bool KCharacter::SetSlotIndex(int32 nAASNode, int32 nActionID)
{
	return SetCharSlotIndex(nAASNode, nActionID);
}

// --------------------------------------------------------------------------
bool KCharacter::SetCharSlotIndex(int32 nAASNode, int32 nActionID)
{
	if (NULL == GetActionSetData() || NULL == m_pCharActionSet)
		return false;

	const CGameTable* pChar_AAS_NodeTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_AAS_NODE_INFO);
	if (NULL == pChar_AAS_NodeTable)
	{
		return false;
	}

	const _TABLE_AAS_NODE_INFO* pInfo = (const _TABLE_AAS_NODE_INFO*)(pChar_AAS_NodeTable->GetFieldDataByIndex(nAASNode));
	if (pInfo)
	{
		const _TABLE_CHARACTER_ACTION_SET* pActionSet =
			(const _TABLE_CHARACTER_ACTION_SET*)(m_pCharActionSet->Search_Index_EQU(nActionID));
		if (pActionSet)
		{
			mMainEntity->Actor_SetSlotIndex(pInfo->szNodeName, (USHORT)pActionSet->nMonitoringDegree + 0.5f);
			return TRUE;
		}
	}

	return FALSE;
}

bool KCharacter::BeginCadaver()
{
	EndJump();
	ChangeAction(CA_LIFE, 0.5, BASE_ACTION_F_CADAVER0);

	return TRUE;
}

bool KCharacter::IsAttached()
{
	return m_nAttachID != INVALID_ID;
}

bool KCharacter::IsInAir()
{
	return false;
}

bool KCharacter::IsMoving()
{
	if (!IsStopped_CharacterState(CHAR_LOGIC_BASE) && 
		CAHR_STATE_MOVE == GetCharacterState(CHAR_LOGIC_BASE))
	{
		return true;
	}
	return false;
}

bool KCharacter::IsUseSkill()
{
	return false;
}

void KCharacter::RefreshBaseAnimation()
{
	if (nullptr == GetCharacterData())
		return;

	if (!IsStopped_CharacterState(CHAR_LOGIC_BASE))
	{
		switch (GetCharacterState(CHAR_LOGIC_BASE))
		{
		case CAHR_STATE_IDLE:
		{
			BeginIdle();
		}
		break;
		case CAHR_STATE_MOVE:
		{
			BeginMove(TRUE);
		}
		break;
		case CAHR_STATE_DEAD:
		{
			BeginCadaver();
			return;
		}
		break;
		default:
			break;
		};
	}
}

void KCharacter::RefreshActionAnimation()
{
	if (NULL == GetCharacterData())
		return;

	if (INVALID_ID != GetCharacterData()->Get_ModelID())
		return;

	if (FALSE == IsStopped_CharacterState(CHAR_LOGIC_ACTION))
	{
		switch (GetCharacterState(CHAR_LOGIC_ACTION))
		{
		case CAHR_STATE_GATHER:
		{
			assert(false);
		}
		break;
		case CAHR_STATE_LEAD:
		{
			assert(false);
		}
		break;
		case CAHR_STATE_SEND:
		{
			assert(false);
		}
		break;
		default:
			break;
		}
	}
}

void KCharacter::RefreshAnimation()
{
	RefreshBaseAnimation();
	RefreshActionAnimation();
}

void KCharacter::UpdateModel_Scale()
{
	FLOAT fScale = GetCharacterData()->Get_CharScale();
	if (mMountObj)
	{
		mMountObj->SetScaleFactor(fScale);
	}
	else
	{
		mMainEntity->SetScaleFactor(fScale);
	}
}


void KCharacter::UpdateModel_Effect()
{

}

void KCharacter::UpdateModel_AllAttr(bool bAfresh)
{
	RefreshAnimation();						// ����	
	UpdateModel_Visible();					// �ɼ�	
	setPosition(getPosition());			// λ��
	setDirection(getDirection());				// ����
	UpdateModel_Scale();					// ����
	UpdateModel_Effect();					// ��Ч
}

void KCharacter::UpdateModel_State()
{
	if (IsModelCreateAllCompleted())
	{
		if (0 < GetAttachModelNum())
		{
			UpdateModel_Attach();
		}
		else
		{
			UpdateModel_AllAttr();
		}
	}
}

void KCharacter::ReadyPlayWalkSound()
{

}

void KCharacter::StopWalkSound()
{

}

void KCharacter::UpdateCharModel(void)
{
	// ������������ݲ������׸���, �����漰������ͷ�������ˢ�»���

	int32 nCharModelID = AnalyseCharModel();
	if (nCharModelID != m_nCurrCharModelID)
	{
		m_nCurrCharModelID = nCharModelID;

		UpdateModel_CharActionSet();

		ReleaseCharRenderInterface();

		if (m_nCurrCharModelID != INVALID_ID)
		{
			createCharRenderInterface();
		}

		UpdateModel_State();
	}
}

void KCharacter::UpdateModel_Visible()
{
	mMainEntity->SetVisible(true);
}

int32 KCharacter::AnalyseCharModel(void)const
{
	return INVALID_ID;
}

void KCharacter::calculateNodePos(
	const Ogre::Vector2& fvPosition, 
	FLOAT fModifyHeight)
{
	auto pActiveScene = GameSceneManager::getSingleton().GetActiveScene();


	//��ǰλ��
	Ogre::Vector3	fvCurObjPos = getPosition();
	FLOAT	fInAirHeight = fvCurObjPos.y;

	//---------------------------------------------------
	//����ȡ���ڵ����ϵĸ߶�
	Ogre::Vector3 fvAtTerrain;
	FLOAT fHeight = -FLT_MAX;

	EngineManager::getSingleton().positionAxisTrans(GAT_GAME, Ogre::Vector3(fvPosition.x, 0.0f, fvPosition.y),
		GAT_SCENE, fvAtTerrain);

	//---------------------------------------------------
	//ȡ�����������ϸ߶�
	if (FALSE == pActiveScene->getCollision().Get3DMapHeight(fvPosition.x, fvCurObjPos.y, fvPosition.y, fHeight))
	{
		fHeight = -FLT_MAX;
	}

	// �������ո߶ȣ� ���������Ƿ����������ϵ�״̬
	FLOAT fRealHeight = 0.0f;

	if (fHeight > fvAtTerrain.y)
	{
		fRealHeight = fHeight;
	}
	else
	{
		fRealHeight = fvAtTerrain.y;
	}

	Ogre::Vector3 position(fvPosition.x, fRealHeight + fModifyHeight, fvPosition.y);
	setPosition(position, false);
}

bool KCharacter::AddCommand(const ObjectCmd* pCmd)
{
	switch (pCmd->m_wID)
	{
		// ����վ��״̬
	case OBJ_CMD_IDLE:
	{
		EnterState_Idle();
	}
	break;
	// �ж��߼�ָ��
	case OBJ_CMD_STOP_ACTION:
	{
		KCharCmdDate_StopLogic* pStopCommand = (KCharCmdDate_StopLogic*)(CreateCharCmd(pCmd));
		if (pStopCommand)
		{
			KCharCmdDate_Logic* pLogicCommand = FindActionStateCommand(pStopCommand->GetLogicCount());
			if (pLogicCommand)
			{
				pLogicCommand->Modify(pStopCommand);
			}
		}
	}
	break;
	// �ƶ��ж�
	case OBJ_CMD_STOP_MOVE:
	{
		// ���󶨾Ͳ������¼�
		if (IsAttached() || IsFollowAttach())
		{
			break;
		}
		KCharCmdDate_StopMove* pStopMoveCommand = (KCharCmdDate_StopMove*)(CreateCharCmd(pCmd));
		if (pStopMoveCommand)
		{
			// �ж��ƶ�
			if (pStopMoveCommand->IsArrive())
			{
				SetBaseLogicCount(pStopMoveCommand->GetLogicCount());

				if (FALSE == IsLogicLocked())
				{
					// ֹͣ�ƶ��߼�
					StopMove();
					// λ���ݴ�
					ModifyCurrPos(Ogre::Vector2(pStopMoveCommand->GetEndPos()->m_fX, pStopMoveCommand->GetEndPos()->m_fZ));
				}
			}
			// ������ǰλ��
			else if ((IsStopped_CharacterState(CHAR_LOGIC_BASE) || GetCharacterState(CHAR_LOGIC_BASE) != CAHR_STATE_MOVE) &&
				pStopMoveCommand->GetLogicCount() == GetBaseLogicCount())
			{
				if (FALSE == IsLogicLocked())
				{
					ModifyCurrPos(Ogre::Vector2(pStopMoveCommand->GetEndPos()->m_fX, pStopMoveCommand->GetEndPos()->m_fZ));
				}
			}
			// �����ƶ�Ŀ���
			else
			{
				KCharCmdDate_Logic* pLogicCommand = FindBaseStateCommand(pStopMoveCommand->GetLogicCount());
				if (pLogicCommand)
				{
					// ����
					pLogicCommand->Modify(pStopMoveCommand);

					// ����������ǵ�ǰ�ƶ�
					if (pStopMoveCommand->GetLogicCount() == GetBaseLogicCount())
					{
						ModifyMove();
					}
				}
			}
			DelObjectCmd(pStopMoveCommand);
		}
	}
	break;
	case OBJ_CMD_MOVE:// �ƶ�	
	{
		// ���󶨾Ͳ������¼�
		if (IsAttached() || IsFollowAttach())
		{
			break;
		}

		KCharCmdDate_Move* pMoveCommand = NULL;

		pMoveCommand = (KCharCmdDate_Move*)(CreateCharCmd(pCmd));
		if (pMoveCommand)
		{
			if (pMoveCommand->IsServerCommond())
			{
				/*
					���Լ�ӵ�п���Ȩ, ���ҷ�����Ҫ�����ƶ�ʱ.
					����������ƶ�������ֹ��, ���÷��������ƶ��¼��ܹ�����ִ��.
					���� �־�״̬.
				*/
				if (IsMoving())
				{
					KCharCmdDate_Move* pCurrCommand = (KCharCmdDate_Move*)GetBaseStateCommand();
					if (pCurrCommand && FALSE == pCurrCommand->IsServerCommond())
					{
						ShutDown_CharacterState(CHAR_LOGIC_BASE);
					}
				}
				AddBaseStateCommand(pMoveCommand);
			}
			else
			{
				// ����͵�ǰ���߼�������� �� ������֮ǰ���߼�����Ͷ���
				if (pMoveCommand->GetLogicCount() <= GetBaseLogicCount())
				{
					DelObjectCmd(pMoveCommand);
				}
				else
				{
					KCharCmdDate_Logic* pFindCommand = FindBaseStateCommand(pMoveCommand->GetLogicCount());
					if (NULL == pFindCommand)
					{
						// û���ҵ���Ӧ��ָ��ż��룬��Ҫ�Ƿ�ֹ��ͻ������ǵ�Ԥ��ָ�����ͻ
						AddBaseStateCommand(pMoveCommand);
					}
					else
					{
						DelObjectCmd(pMoveCommand);
					}
				}
			}
			// ��ǰû��ִ�е��߼�
			if (IsStopped_CharacterState(CHAR_LOGIC_BASE) || CAHR_STATE_IDLE == GetCharacterState(CHAR_LOGIC_BASE))
			{
				ProcessBaseStateCommand();
			}
		}
	}
	break;
	case OBJ_CMD_JUMP:
	{
		// ���󶨾Ͳ������¼�
		if (IsAttached() || IsFollowAttach())
			break;

		/*
			����Ծ���ƶ�ͨ���߼�����ƥ���ϡ�
			����߼�������Ч��͵�ǰһ�£�������ִ�С���ԭ������
			��������ƶ�ָ����һ��ִ�С�
		*/
		KCharCmdDate_Jump* pCommand = (KCharCmdDate_Jump*)(CreateCharCmd(pCmd));
		if (pCommand)
		{
			KCharCmdDate_Logic* pLogicCommand = FindBaseStateCommand(pCommand->GetLogicCount());
			if (pLogicCommand && OBJ_CMD_MOVE == pLogicCommand->GetCmdType())
			{
				if (pCommand->GetLogicCount() == GetBaseLogicCount())
				{
					ProcessStateCommand(pCommand);
				}
				else
				{
					KCharCmdDate_Move* pMoveCmd = (KCharCmdDate_Move*)pLogicCommand;
					pMoveCmd->SetJumpMove();
				}
			}
			else
			{
				ProcessStateCommand(pCommand);
			}
			DelObjectCmd(pCommand);
		}
	}
	break;

	case OBJ_CMD_ACTION:		// ��������ҩ�ȣ�
	case OBJ_CMD_SKILL_SEND:	// ���ܷ���
	case OBJ_CMD_SKILL_CHARGE:	// ���ܾ���
	case OBJ_CMD_SKILL_CHANNEL:	// ��������
	case OBJ_CMD_ABILITY:		// �����
	{
		KCharCmdDate_Logic* pLogicCommand = (KCharCmdDate_Logic*)(CreateCharCmd(pCmd));
		if (pLogicCommand != nullptr)
		{
			AddActionStateCommand(pLogicCommand);
		}
		ProcessActionStateCommand();
	}
	break;

	// ���Ŷ���
	case OBJ_CMD_ACTION_MODIFY:
	{
		int32 nModifyTime, nLogicCount;
		nLogicCount = pCmd->nParam[0];
		nModifyTime = pCmd->nParam[1];

		if (GetActionLogicCount() == nLogicCount && !IsStopped_CharacterState(CHAR_LOGIC_ACTION))
		{
			if (GetCharacterState(CHAR_LOGIC_ACTION) == CAHR_STATE_GATHER)
			{
				KCharCmdDate_SkillCharge* pMagicChargeCommand = (KCharCmdDate_SkillCharge*)(GetActionStateCommand());
				if (nModifyTime >= 0)
				{
					uint32 uModifyTime = (uint32)nModifyTime;
					if (m_StateDate_Charge.m_uCurrentTime > uModifyTime)
					{
						m_StateDate_Charge.m_uCurrentTime -= uModifyTime;
					}
					else
					{
						m_StateDate_Charge.m_uCurrentTime = 0;
					}
				}
				else
				{
					uint32 uModifyTime = (uint32)(abs(nModifyTime));
					if (m_StateDate_Charge.m_uCurrentTime + uModifyTime > pMagicChargeCommand->GetTotalTime())
					{
						m_StateDate_Charge.m_uCurrentTime = pMagicChargeCommand->GetTotalTime();
					}
					else
					{
						m_StateDate_Charge.m_uCurrentTime += uModifyTime;
					}
				}
			}
			else if (GetCharacterState(CHAR_LOGIC_ACTION) == CAHR_STATE_LEAD)
			{
				KCharCmdDate_SkillChannel* pMagicChannelCommand = (KCharCmdDate_SkillChannel*)(GetActionStateCommand());
				if (nModifyTime >= 0)
				{
					uint32 uModifyTime = (uint32)nModifyTime;
					if (m_StateDate_Channel.m_uCurrentTime > uModifyTime)
					{
						m_StateDate_Channel.m_uCurrentTime -= uModifyTime;
					}
					else
					{
						m_StateDate_Channel.m_uCurrentTime = 0;
					}
				}
				else
				{
					uint32 uModifyTime = (uint32)(abs(nModifyTime));
					if (m_StateDate_Channel.m_uCurrentTime + uModifyTime > pMagicChannelCommand->GetTotalTime())
					{
						m_StateDate_Channel.m_uCurrentTime = pMagicChannelCommand->GetTotalTime();
					}
					else
					{
						m_StateDate_Channel.m_uCurrentTime += uModifyTime;
					}
				}
			}
		}
	}
	break;
	// ����ֱ�ӵ�Ч�����ӵ��¼�
	case OBJ_CMD_LOGIC_EVENT:
	{
		LogicEventData* pLogicEvent;
		pLogicEvent = (LogicEventData*)(pCmd->pParam[0]);

		int32 nCreaterID = pLogicEvent->m_nSenderID;
		int32 nCreaterLogicCount = pLogicEvent->m_nSenderLogicCount;

		KObject* pCreater = KObjectManager::GetSingleton().getObject(nCreaterID);

		if (pCreater != nullptr)
		{
			if (!ProcessEvent(pLogicEvent))
			{
				AddEvent(pLogicEvent);
			}
		}
		// ʩ������Ч �� ������һ��skill��Impact�ͷ����¼�������
		else
		{
			AddEvent(pLogicEvent);
		}
	}
	break;
	default:
	{
		// ֱ�Ӵ�������
		HandleCommand(pCmd);
	}
	break;

	};

	return TRUE;
}

eRUN_CMD_RESULT_CODE KCharacter::HandleCommand(const ObjectCmd* pCmd)
{
	eRUN_CMD_RESULT_CODE rcResult = RC_SKIP;

	switch (pCmd->m_wID)
	{
	case OBJ_CMD_TELEPORT:
	{
		// ���󶨾Ͳ������¼�
		if (IsAttached() || IsFollowAttach())
			break;

		// �߼�����
		SetLogicLocked(FALSE);

		// ����λ��
		Ogre::Vector2 fvServerPos;
		fvServerPos.x = pCmd->fParam[0];
		fvServerPos.y = pCmd->fParam[1];
		calculateNodePos(fvServerPos, 0.0f);

		// ����ƶ�
		StopMove();

		// ǿ�����
		if (IsInAir())
		{
			//SetTouchDown();
		}


		rcResult = RC_OK;
	}
	break;

	case OBJ_CMD_DEATH:
	{
		BOOL bPlayDieAni;
		bPlayDieAni = pCmd->bParam[0];
		BOOL bResult = EnterState_Dead(bPlayDieAni);
		if (bResult)
			rcResult = RC_OK;
		else
			rcResult = RC_ERROR;
	}
	break;

	case OBJ_CMD_IMPACT:
	{
		EffectID_t	idImpact;
		BOOL		bEnable;
		ObjID_t		nCreatorID;
		uint32		nNumOflayer;
		uint32		nSN;
		int32			nSenderLogicCount;

		idImpact = (EffectID_t)(pCmd->uParam[0]);
		nSN = pCmd->uParam[1];
		nNumOflayer = pCmd->nParam[2];
		nCreatorID = pCmd->nParam[3];
		bEnable = pCmd->bParam[4];
		nSenderLogicCount = pCmd->nParam[5];

		// ���»�����
		if (bEnable)
		{
			AddImpact(nSN, idImpact, nCreatorID, nNumOflayer, nSenderLogicCount);
		}
		// ɾ��
		else
		{
			DelImpact(nSN);
		}
		rcResult = RC_OK;
	}
	break;

	case OBJ_CMD_PLAY_IMPACT:
	{
		BOOL bMountEffect = pCmd->bParam[0];
		int32  nEffectID = pCmd->nParam[1];

		const _DBC_DIRECT_EFFECT* pImpact = CDirectlyEffectMgr::GetMe()->GetConstDirectlyImpact(nEffectID);
		if (NULL == pImpact)
			break;
		if (0 == strlen(pImpact->m_pszEffectLocator))
			break;

		if (bMountEffect)
		{
			AddMountEffect(pImpact->m_pszEffect, pImpact->m_pszEffectLocator);
		}
		else
		{
			AddBindEffect(pImpact->m_pszEffect, pImpact->m_pszEffectLocator);
		}
	}
	break;

	default:
		rcResult = RC_SKIP;
		break;
	}

	return rcResult;
}

// ����
bool	KCharacter::EnterState_Idle(void)
{
	return true;
}

// ����
bool	KCharacter::EnterState_Action(KCharCmdDate_Logic* pLogicCommand)
{
	return true;
}

// �ƶ�
bool	KCharacter::EnterState_Move(KCharCmdDate_Logic* pLogicCommand)
{
	return true;
}

// ��������
bool	KCharacter::EnterState_Charge(KCharCmdDate_Logic* pLogicCommand)
{
	return true;
}

// ��������
bool	KCharacter::EnterState_Channel(KCharCmdDate_Logic* pLogicCommand)
{
	return true;
}

// ��������
bool	KCharacter::EnterState_Send(KCharCmdDate_Logic* pLogicCommand)
{
	return true;
}

// ����
bool	KCharacter::EnterState_Dead(BOOL bPlayDieAni)
{
	return true;
}

// �����
bool	KCharacter::EnterState_Ability(KCharCmdDate_Logic* pLogicCommand)
{
	return true;
}

// ��̯
bool	EnterState_Stall(BOOL bPlayAni)
{
	return true;
}

KCharCmdDate_Logic* KCharacter::FindBaseStateCommand(int32 nLogicCount)
{
	// ��ǰ����ִ�е�ָ��
	if (m_pBaseLogicCommand != NULL && m_pBaseLogicCommand->GetLogicCount() == nLogicCount)
	{
		return m_pBaseLogicCommand;
	}

	// �����ָ��
	ObjCommandList::iterator itCur, itEnd;
	KCharCmdDate_Logic* pCommand;

	itCur = m_listBaseStateCommand.begin();
	itEnd = m_listBaseStateCommand.end();

	while (itCur != itEnd)
	{
		pCommand = *itCur;
		itCur++;
		if (pCommand->GetLogicCount() == nLogicCount)
		{
			return pCommand;
		}
	}

	return NULL;
}


KCharCmdDate_Logic* KCharacter::FindActionStateCommand(int32 nLogicCount)
{
	if (m_pActionLogicCommand != NULL && m_pActionLogicCommand->GetLogicCount() == nLogicCount)
	{
		return m_pActionLogicCommand;
	}

	// �����ָ��
	ObjCommandList::iterator itCur, itEnd;
	KCharCmdDate_Logic* pCommand;

	itCur = m_listActionStateCommand.begin();
	itEnd = m_listActionStateCommand.end();

	while (itCur != itEnd)
	{
		pCommand = *itCur;
		itCur++;
		if (pCommand->GetLogicCount() == nLogicCount)
		{
			return pCommand;
		}
	}

	return NULL;
}

KCharCmdDate_Logic* KCharacter::GetBaseStateCommand(void)
{
	return m_pBaseLogicCommand;
}
void KCharacter::SetBaseStateCommand(KCharCmdDate_Logic* pLogicCommand)
{
	if (m_pBaseLogicCommand != NULL)
	{
		DelObjectCmd(m_pBaseLogicCommand);
	}
	m_pBaseLogicCommand = pLogicCommand;
}

KCharCmdDate_Logic* KCharacter::GetActionStateCommand(void)
{
	return m_pActionLogicCommand;
}
void KCharacter::SetActionStateCommand(KCharCmdDate_Logic* pLogicCommand)
{
	if (m_pActionLogicCommand != NULL)
	{
		DelObjectCmd(m_pActionLogicCommand);
	}
	m_pActionLogicCommand = pLogicCommand;
}

void KCharacter::DelAllMoveCommand()
{
	ObjCommandList::iterator tempIt;
	ObjCommandList::iterator it = m_listBaseStateCommand.begin();
	while (it != m_listBaseStateCommand.end())
	{
		tempIt = it;
		++it;
		KCharCmdDate_Logic* pLogic = *tempIt;
		if (pLogic && OBJ_CMD_MOVE == pLogic->GetCmdType())
		{
			m_listBaseStateCommand.erase(tempIt);
			DelObjectCmd(pLogic);
		}
	}
}

BOOL KCharacter::AddBaseStateCommand(KCharCmdDate_Logic* pCmd)
{
	int32 nLogicCount = pCmd->GetLogicCount();
	if (!m_listBaseStateCommand.empty())
	{
		ObjCommandList::iterator itCur, itEnd;
		KCharCmdDate_Logic* pCommand;

		itCur = m_listBaseStateCommand.begin();
		itEnd = m_listBaseStateCommand.end();

		while (itCur != itEnd)
		{
			pCommand = *itCur;
			if (pCommand->GetLogicCount() > nLogicCount)
			{
				m_listBaseStateCommand.insert(itCur, pCmd);
				return TRUE;
			}

			itCur++;
		}
	}

	m_listBaseStateCommand.push_back(pCmd);
	return TRUE;
}
BOOL KCharacter::AddActionStateCommand(KCharCmdDate_Logic* pCmd)
{
	int32 nLogicCount = pCmd->GetLogicCount();
	if (!m_listActionStateCommand.empty())
	{
		ObjCommandList::iterator itCur, itEnd;
		KCharCmdDate_Logic* pCommand;

		itCur = m_listActionStateCommand.begin();
		itEnd = m_listActionStateCommand.end();

		while (itCur != itEnd)
		{
			pCommand = *itCur;
			if (pCommand->GetLogicCount() > nLogicCount)
			{
				m_listActionStateCommand.insert(itCur, pCmd);
				return TRUE;
			}

			itCur++;
		}
	}

	m_listActionStateCommand.push_back(pCmd);

		return TRUE;
}

BOOL KCharacter::ProcessBaseStateCommand(void)
{
	if (IsLogicLocked())
		return FALSE;

	// �жϻ����߼��Ƿ�ֹͣ
	if (IsStopped_CharacterState(CHAR_LOGIC_BASE))
	{
		// ִ����һ������
		if (FALSE == ProcessNextCommand(CHAR_LOGIC_BASE))
		{
			EnterState_Idle();
		}
	}
	// ��ǰ�����߼�������
	else if (GetCharacterState(CHAR_LOGIC_BASE) == CAHR_STATE_IDLE)
	{
		ProcessNextCommand(CHAR_LOGIC_BASE);
	}

	FLOAT fSpeed = 1.f;
	int32 nLogicCommandCount = (int32)(m_listBaseStateCommand.size());
	if (nLogicCommandCount > 0)
	{
		fSpeed = (FLOAT)(nLogicCommandCount) * 0.5f + 1.f;
	}
	SetLogicSpeed(fSpeed);

	return TRUE;
}

BOOL KCharacter::ProcessActionStateCommand(void)
{
		if (TRUE == IsLogicLocked())
			return FALSE;


		// ִ�ж���
		if (CheckNextActionStateCommand())
		{
			ProcessNextCommand(CHAR_LOGIC_ACTION);
		}



	// ���ö����ٶ��Լ���Ч�ٶ�
	FLOAT fImpactSpeed = GetActionLogicSpeed();
	FLOAT fActionSpeed = 1.f;

	int32 nLogicCommandCount = (int32)(m_listActionStateCommand.size());
	if (nLogicCommandCount > 0)
	{
		fActionSpeed = 1.15f;
		/*fActionSpeed = (FLOAT)(nLogicCommandCount) * 0.15f + 1.f;
		if (fActionSpeed > 1.5f)
		{
		fActionSpeed = 1.5f;
		}*/
		fImpactSpeed = 1000.f;
	}

	SetActionImpactSpeed(fImpactSpeed);	// ������Ч
	SetActionLogicSpeed(fActionSpeed);	// ��һ��������Ч	

		return TRUE;
}

BOOL KCharacter::CheckNextActionStateCommand()
{
	if (m_listActionStateCommand.empty())
		return FALSE;

	ObjCommandList::iterator it = m_listActionStateCommand.begin();
	KCharCmdDate_Logic* pLogicCommand = *it;
	if (NULL == pLogicCommand)
	{
		return TRUE;
	}

	// ��ǰ�ж���ʱ, ������������һ֡ 
	if (IsUseSkill())
	{
		uint64_t uStartTime = pLogicCommand->GetStartTime();
		uint64_t uNowTime = Ogre::Root::getSingleton().getTimer()->getMicroseconds();

		if (uNowTime < uStartTime + 1)
		{
			return FALSE;
		}
	}
	return TRUE;
}

// ִ����һ���߼�����
BOOL KCharacter::ProcessNextCommand(CHARATER_LOGIC_TYPE nLogicTag)
{
	// �����߼�
	if (CHAR_LOGIC_BASE == nLogicTag)
	{
		if (FALSE == IsEmpty_BaseStateCommand())
		{
			KCharCmdDate_Logic* pLogicCommand = GetNextCommand(CHAR_LOGIC_BASE);

			BOOL bResult = ProcessStateCommand(pLogicCommand);
			if (FALSE == bResult)
			{
				DelObjectCmd(pLogicCommand);
			}
			return bResult;
		}
	}
	// ��Ϊ�߼�
	else
	{
		if (FALSE == IsEmpty_ActionStateCommand())
		{
			KCharCmdDate_Logic* pLogicCommand = GetNextCommand(CHAR_LOGIC_ACTION);

			BOOL bResult = ProcessStateCommand(pLogicCommand);
			if (FALSE == bResult)
			{
				DelObjectCmd(pLogicCommand);
			}
			return bResult;
		}
	}
	return FALSE;
}

// �����߼�����
BOOL KCharacter::ProcessStateCommand(KCharCmdDate_Logic* pLogicCmd)
{
	BOOL bResult = FALSE;
	switch (pLogicCmd->GetCmdType())
	{
	case OBJ_CMD_ACTION:
	{
		bResult = EnterState_Action(pLogicCmd);
	}
	break;
	case OBJ_CMD_MOVE:
	{
		bResult = EnterState_Move(pLogicCmd);
	}
	break;
	case OBJ_CMD_SKILL_SEND:
	{
		bResult = EnterState_Send(pLogicCmd);
	}
	break;
	case OBJ_CMD_SKILL_CHARGE:
	{
		bResult = EnterState_Charge(pLogicCmd);
	}
	break;
	case OBJ_CMD_SKILL_CHANNEL:
	{
		bResult = EnterState_Channel(pLogicCmd);
	}
	break;
	case OBJ_CMD_ABILITY:
	{
		bResult = EnterState_Ability(pLogicCmd);
	}
	break;
	case OBJ_CMD_JUMP:
	{
		bResult = DoJump();
	}
	break;
	default:
		break;
	}

	return bResult;
}

bool KCharacter::IsLogicLocked()
{
	if (TRUE == m_bLogic_Locked)
	{
		UINT64 uCurrTime = Ogre::Root::getSingleton().getTimer()->getMicroseconds();
		if (uCurrTime - m_uLogicLockTimer >= 5000)
		{
			// ��ʱ
			m_bLogic_Locked = false;
		}
	}
	return m_bLogic_Locked;
}

void KCharacter::SetLogicLocked(BOOL bLock)
{
	m_bLogic_Locked = bLock;
	if (m_bLogic_Locked)
	{
		m_uLogicLockTimer = Ogre::Root::getSingleton().getTimer()->getMicroseconds();
	}
}

void KCharacter::SetActionImpactSpeed(FLOAT fSpeed)
{
	if (fabs(m_fActionImpact_Speed - fSpeed) >= 0.01f)
	{
		m_fActionImpact_Speed = fSpeed;
		//mMainEntity->Actor_SetSkillRate(m_fActionImpact_Speed);
	}
}

void KCharacter::ModifyCurrPos(const Ogre::Vector2& fvServerPos)
{
	Ogre::Vector2 targetPos(getPosition().x, getPosition().z);
	FLOAT fStopToCurrentDistSq = fvServerPos.squaredDistance(targetPos);
	if (fStopToCurrentDistSq > DEF_CHARACTER_POS_ADJUST_DIST * DEF_CHARACTER_POS_ADJUST_DIST)
	{
		// ˲�Ƶ���ǰ��������Ӧ��λ��
		calculateNodePos(fvServerPos, 0.0f);
	}
	
}

void KCharacter::ShutDown_CharacterState(CHARATER_LOGIC_TYPE nLogicTag)
{
	if (CHAR_LOGIC_BASE == nLogicTag)
	{
		SetBaseStateCommand(NULL);
	}
	else
	{
		SetActionStateCommand(NULL);
	}
	Exit_CharacterState(nLogicTag);
}

void KCharacter::Exit_CharacterState(CHARATER_LOGIC_TYPE nLogicTag)
{
	// �����߼�ֹͣ
	if (CHAR_LOGIC_BASE == nLogicTag)
	{
		m_bIsCharBaseLogicEnd = TRUE;

		switch (GetCharacterState(CHAR_LOGIC_BASE))
		{
		case CAHR_STATE_IDLE:
		{

		}
		break;
		case CAHR_STATE_MOVE:
		{
			EndMove();
		}
		break;
		case CAHR_STATE_DEAD:
		{

		}
		break;
		case CAHR_STATE_STALL:
		{

		}
		break;
		default:
			break;
		};

		m_nCharBaseState = CAHR_STATE_INVAILD;
	}
	// ��Ϊ�߼�ֹͣ
	else
	{
		m_bIsCharActionLogicEnd = TRUE;

		switch (GetCharacterState(CHAR_LOGIC_ACTION))
		{
		case CAHR_STATE_ABILITY:
		{
		}
		break;
		case CAHR_STATE_ACTION:
			break;
		case CAHR_STATE_LEAD:
			break;
		case CAHR_STATE_GATHER:
		{
		}
		break;
		case CAHR_STATE_SEND:
		{
			if (IsLogicLocked())
			{
				SetLogicLocked(FALSE);
			}
		}
		break;
		default:
			break;
		};

		m_nCharActionState = CAHR_STATE_INVAILD;
	}
}

// --------------------------------------------------------------------------
void KCharacter::SetActionLogicSpeed(FLOAT fSpeed)
{
	if (fabs(m_fActionLogic_Speed - fSpeed) > 0.01f)
	{
		m_fActionLogic_Speed = fSpeed;
	}
}

// --------------------------------------------------------------------------
FLOAT KCharacter::GetActionLogicSpeed() const
{
	return m_fActionLogic_Speed;
}

void KCharacter::SetLogicSpeed(FLOAT fSpeed)
{
	if (fabsf(m_fLogic_Speed - fSpeed) > 0.1f)
	{
		m_fLogic_Speed = fSpeed;
	}
}

void	KCharacter::AddEvent(const LogicEventData* pLogicEvent)
{

}

void	KCharacter::RemoveEvent(int32 nLogicCount)
{

}

void	KCharacter::RemoveAllEvent(void)
{

}

void	KCharacter::Update_Event(void)
{

}

bool	KCharacter::ProcessEvent(const LogicEventData* pLogicEvent)
{
	return true;
}

bool	KCharacter::ProcessEvent_Damage(const LogicEventData* pLogicEvent)
{
	return true;
}

void	KCharacter::UpdateModel_BuffEffect(void)
{

}

bool	KCharacter::AddImpact(
	uint32 nSN,
	int32 idImpact,
	ObjID_t nCreatorID,
	int32 nNumOflayer, int32 nSenderLogicCount)
{
	return true;
}

void	KCharacter::DelImpact(uint32 nSN)
{
	
}

void	KCharacter::ClearBuffEffectHandle()
{

}

void	KCharacter::ClearMountBuffEffect()
{

}

bool KCharacter::AddBindEffect(const STRING& strEffect, const STRING& strBindLocat)
{
	return true;
}

bool KCharacter::AddMountEffect(const STRING& strEffect, const STRING& strBindLocat)
{
	return true;
}