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
	mCurrCharModelID = INVALID_ID;
	mCurrMountModelID = INVALID_ID;

	m_fRunBaseSpeed = 0.0f;
	m_fWalkBaseSpeed = 0.0f;

	mPathComponent = new PathComponent(this);

	mObjectType = ObjectType_Npc;
}


bool KCharacter::initialize()
{
	m_nAttachID = INVALID_ID;
	m_bInAir = false;
	mMainEntity = std::make_shared<GameEntity>();
	
	m_pCharacterData = new KCharatcterBaseData(this);

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
		// 隐藏武器
		if (pbHideWeapon)
			*pbHideWeapon = pActionSet->bHideWeapon;

		// 指定武器
		if (pnAppointedWeaponID)
			*pnAppointedWeaponID = pActionSet->nAppointedWeaponID;


		// 取相应的列（拿什么武器的动作， 也包括Npc 和 怪的动作）
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
	// 设置警戒状态
	ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE);
	// 开始技能动作
	ChangeAction(CA_ATTACK, 1.0f);
	//125 杀无赦
	//103 普通攻击
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
	// 人物
	if (mMainEntity)
	{
		mMainEntity->ChangeModelActionRate(fSpeed);
	}

	// 坐骑
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
		// 技能是否有被立即创建
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

	// 模型表
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
	// int32 nCharActionIndex = pMount->m_nCharActionIndex; // 人物骑乘时的动作组,对应char_model.tab的mount0~19
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
	if (mCurrMountModelID != mountId)
	{
		mCurrMountModelID = mountId;
		OnChangeOfMountId();
	}
}



void KCharacter::DoDataEvent_DataID()
{
	const CGameTable* pCreatureTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CREATURE_ATT);
	if (NULL == pCreatureTable)
	{
		return;
	}
	auto id = m_pCharacterData->Get_RaceID();
	auto createInfo = (const _TABLE_CREATURE_ATT*)(
		pCreatureTable->GetFieldDataByIndex(id));
	if (createInfo)
	{
		m_fRunBaseSpeed = createInfo->nRunSpeed * 0.001f;
		m_fWalkBaseSpeed = createInfo->nWalkSpeed * 0.001f;

		if (mCurrCharModelID != createInfo->nModelID)
		{
			mCurrCharModelID = createInfo->nModelID;
			DoDataEvent_ModelID();
		}
	}
}

void KCharacter::DoDataEvent_ModelID()
{
	UpdateModel_CharActionSet();

	if (mCurrCharModelID != INVALID_ID)
	{
		createCharRenderInterface();
	}
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
	return mCurrCharModelID;
}


void KCharacter::OnChangeOfMountId()
{

}


void KCharacter::UpdateModel_CharActionSet(void)
{
	m_pCharActionSet = NULL;

	if (NULL == GetActionSetData())
		return;

	if (INVALID_ID == mCurrCharModelID)
		return;

	//	TABLE_DEFINEHANDLE(s_pCharModelDBC, TABLE_CHARACTER_MODEL)
	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return;

	// 人物有效
	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(
		pCharModelTable->GetFieldDataByIndex(mCurrCharModelID));
	if (NULL == pCharModel)
	{
		OGRE_EXCEPT(0);
		return;
	}

	mModelName = pCharModel->m_pszModelName;

	//检查坐骑ID是否有效
	const CGameTable* pCharMountTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MOUNT);
	if (NULL == pCharMountTable)
		return;

	const char* pszActionSetFileName = NULL;

	// 坐骑有效，加载马上动作组
	const _TABLE_CHARACTER_MOUNT* pMount = (const _TABLE_CHARACTER_MOUNT*)(
		pCharMountTable->GetFieldDataByIndex(mCurrMountModelID));
	if (pMount)
	{
		const _TABLE_CHARACTER_MODEL* pMountModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(pMount->m_nModelID));
		if (pMountModel)
		{
			mMountModelName = pMountModel->m_pszModelName;
		}
		int32 nCharActionIndex = pMount->m_nCharActionIndex; // 人物骑乘时的动作组,对应char_model.tab的mount0~19

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
	// 无效，加载马下动作组
	else
	{
		pszActionSetFileName = pCharModel->m_pszActionSetName_None;
	}

	// 加载的动作
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

	const _TABLE_CHARACTER_MOUNT* pMount = (const _TABLE_CHARACTER_MOUNT*)(pCharMountTable->GetFieldDataByIndex(mCurrMountModelID));

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
	if (!mMainEntity)
	{ 
		mMainEntity = std::make_shared<GameEntity>();
	}

	mMainEntity->setModelName(mModelName);

	// 在渲染层刷新位置
	setPosition(mGamePosition);
	mMainEntity->SetModelType(CHAR_MODEL_CHAR);

	if (mWeaponname.empty())
	{
		mWeaponname = "Falchion";
	}
	// 设置相关武器动作
	mMainEntity->setWeapon(mWeaponname);

	// 设置加载完成回调

	mMainEntity->getLogicModel()->setAASAnimEndCallback(new PlayerAASAnimPlayCallback, (uint64_t)this);

}

KCharatcterBaseData* KCharacter::GetCharacterData(void)
{
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
	// 绑定obj. 第一次创建时才检测. 只检测父obj
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
	mMainEntity.reset();
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
			// 是否被绑定
			if (m_nAttachID != INVALID_ID)
			{
				return false;
			}
			// 是否变身
			if (!IsCanUpdateMountByModelID())
			{
				return false;
			}
			// 回复缩放比例, 缩放指令一定要在绑定指令之前执行
			//KObject::SetModel_Scale(1.f);

			// 绑定
			mMountEntity->Detach_Object(mMainEntity.get());
			mMountEntity->Attach_Object(mMainEntity.get(), GetMountLocatorName(LOCATOR_MOUNT_BACK));

			// 人物的动作
			UpdateModel_CharActionSet();
			// 武器的动作
			UpdateModel_WeaponActionSet();

			// 设置马上动作
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
			// 检测变身时，是否指定了坐骑。<0不能骑， >0指定坐骑， =0当前坐骑
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

	// 坐骑ID无效，当作下马处理
	if (NULL == pCharMount)
	{
		// 下马
		//Dismount();
	}
	else
	{
		// 上马
		//Mounting(CreateMountRenderInterface(nMountID), nMountID);
	}

	UpdateModel_State();
}

void KCharacter::UpdateAttached()
{
	int32 nAttachID = GetCharacterData()->Get_AttachID();
	if (INVALID_ID != nAttachID)
	{
		// 隐藏简模
		
	}
	if (m_nAttachID != nAttachID)
	{
		if (INVALID_ID != m_nAttachID)
		{
			// 通知主体解除绑定
			KObject* pObj = KObjectManager::GetSingleton().getObject(m_nAttachID);
			if (pObj)
			{
				((KCharacter*)pObj)->RemoveAttachMember(getId());
			}
		}
		if (INVALID_ID != nAttachID)
		{
			// 通知主体绑定
			KObject* pObj = KObjectManager::GetSingleton().getObject(nAttachID);
			
			((KCharacter*)pObj)->AddAttachMember(getId());
			
			// 停止移动逻辑
			StopMove();

		}
		//  解除绑定
		else
		{
			// 更新坐骑
			UpdateMountModel();

			auto pos = getPosition();

			Ogre::Vector2 pos2d(pos.x, pos.z);
			mPathComponent->calculateNodePos(pos2d, 0.0f);
		}
	}
}

void KCharacter::UpdateModel_Attach()
{
	// 更新坐骑绑定
	UpdateMountingState();

	// 更新父绑定
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
	// 跳跃时不设置移动动作
	if (IsJumping())
		return FALSE;

	EndJump();
	ChangeAction(CA_MOVING, 0.0f, INVALID_ID, 1.f, FALSE);			// 设置非移动状态	

	if (mObjectType == ObjectType_PlayerOfMe)
	{
		ChangeAction(CA_POSTURE, 0.0f, INVALID_ID, 1.f, FALSE);		// 设置站立状态
		// 警戒
		if (IsFightState())
		{
			ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE, 1.f, FALSE);	// 设置警戒状态

			SetActionSlot(AASSLOT_DOWN_IDLE_STAND, BASE_ACTION_N_STAND);
			SetActionSlot(AASSLOT_UP_IDLE_STAND, BASE_ACTION_N_STAND);
		}
		// 非警戒
		else
		{
			ChangeAction(CA_GUARD, 0.0f, INVALID_ID, 1.0f, FALSE);	// 设置非警戒状态

			// 休闲动作
			if (0 == rand() % 10)
			{
				int32 nIdleActionId = BASE_ACTION_N_IDLE_1 + rand() % 5;
				SetActionSlot(AASSLOT_DOWN_IDLE_STAND, nIdleActionId);
				SetActionSlot(AASSLOT_UP_IDLE_STAND, nIdleActionId);
			}
			// 站立动作
			else
			{
				SetActionSlot(AASSLOT_DOWN_IDLE_STAND, BASE_ACTION_N_STAND);
				SetActionSlot(AASSLOT_UP_IDLE_STAND, BASE_ACTION_N_STAND);
			}
		}
	}
	// 非玩家
	else
	{
		ChangeAction(CA_POSTURE, 0.0f, INVALID_ID);		// 设置站立状态
		// 警戒
		if (IsFightState())
		{
			ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE);	// 设置警戒状态
		}
		// (和平)站立
		else
		{
			ChangeAction(CA_GUARD, 0.0f, BASE_ACTION_N_STAND);	// 设置休闲状态
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
// 移动
bool KCharacter::BeginMove(bool bPlayMoveSound)
{
	if (NULL == GetCharacterData())
		return FALSE;

	// 跳跃时不设置移动动作
	if (IsJumping())
		return FALSE;

	EndJump();
	ChangeAction(CA_MOVING, 1.0f);

	if (MOVE_MODE_WALK == GetCharacterData()->Get_MoveActionMode())
	{
		// 走
		ChangeAction(CA_WALK, 1.0f, BASE_ACTION_N_WALK);
		StopWalkSound();
	}
	else if (MOVE_MODE_RUN == GetCharacterData()->Get_MoveActionMode())
	{
		// 跑
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

	// 终止移动声音
	StopWalkSound();

	return TRUE;
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
	// 添加武器动作
	SetWeaponActionSlot(nAASNode, nActionID, bActionBySkill, fRate, bLoop, bBlendIn, bBlendOut);

	// 添加坐骑动作
	SetMountActionSlot(nAASNode, nActionID, bActionBySkill, fRate, bLoop, bBlendIn, bBlendOut);

	// 添加人物动作
	return SetCharActionSlot(nAASNode, nActionID, bActionBySkill, fRate, bLoop, bBlendIn, bBlendOut);

}
// 给人物添加动作
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

// 给坐骑
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

// 给武器
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
		// 隐藏武器
		if (pbHideWeapon)
			*pbHideWeapon = pActionSet->bHideWeapon;

		// 指定武器
		if (pnAppointedWeaponID)
			*pnAppointedWeaponID = pActionSet->nAppointedWeaponID;

		// 通过对象类型来获取武器类型
		if (CHAR_BASE_TYPE_NPC == GetCharacterType())
		{
			assert(false);
		}

		// 取相应的列（拿什么武器的动作， 也包括Npc 和 怪的动作）
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
		// 同人物动作表格式相同
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

void KCharacter::RefreshBaseAnimation()
{
	if (nullptr == GetCharacterData())
		return;

	if (FALSE == IsStopped_CharacterState(CHAR_LOGIC_BASE))
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
		};
	};
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
	RefreshAnimation();						// 动作	
	UpdateModel_Visible();					// 可见	
	setPosition(getPosition());			// 位置
	setDirection(getDirection());				// 方向
	UpdateModel_Scale();					// 缩放
	UpdateModel_Effect();					// 特效
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
	// 这个函数的内容不可轻易更改, 这里涉及到引擎和服务器的刷新机制

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