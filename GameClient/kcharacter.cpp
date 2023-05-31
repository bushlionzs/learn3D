#include "OgreHeader.h"
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
	mRaceId = INVALID_ID;
	mCurrCharModelID = INVALID_ID;
	mCurrMountModelID = INVALID_ID;

	m_fRunBaseSpeed = 0.0f;
	m_fWalkBaseSpeed = 0.0f;

	mPathComponent = new PathComponent(this);
}


bool KCharacter::initialize()
{
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
	

	mMainEntity = std::make_shared<GameEntity>();
	mMainEntity->loadModel("突厥武士女_01.lmodel");
	mMainEntity->changeAttributes(names, values);
	mMainEntity->setWeapon("Falchion");

	
	int32_t mCharacterID = 12;
	const CGameTable* pChar_Table = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	const _TABLE_CHARACTER_MODEL* pInfo = (const _TABLE_CHARACTER_MODEL*)pChar_Table->GetFieldDataByIndex(mCharacterID);



	if (nullptr == m_pCharActionSet)
	{
		std::string filename = pInfo->m_pszActionSetName_None;

		CDBActionSet* setmgr = GetActionSetData();
		m_pCharActionSet = setmgr->GetActionSetFile(pInfo->m_pszActionSetName_None);
	}
	//createMount();
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

void KCharacter::ChangeAction(int32_t nActionType, float fDegree, int32_t nActionID)
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
	mMountObj = Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");

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


	mMountObj->createRenderInstance();

	int32_t nObjID = 105;
	((Orphigine::SkeletonMeshActor*)mMountObj.get())->setSkeletonMeshActorTypeandId((Orphigine::SkeletonMeshActor::TypeEnum)0, nObjID);
	mMountObj->setProperty(FOBJ_ACTOR_FILE, String(pMountModel->m_pszModelName));

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

void KCharacter::setRaceId(int32_t raceId)
{
	if (mRaceId != raceId)
	{
		mRaceId = raceId;

		const CGameTable* pCreatureTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CREATURE_ATT);
		if (NULL == pCreatureTable)
		{
			return;
		}

		auto createInfo = (const _TABLE_CREATURE_ATT*)(pCreatureTable->GetFieldDataByIndex(mRaceId));
		if (createInfo)
		{
			m_fRunBaseSpeed = createInfo->nRunSpeed * 0.001f;
			m_fWalkBaseSpeed = createInfo->nWalkSpeed * 0.001f;

			setCharModelId(createInfo->nModelID);
		}
	}
}

void KCharacter::setCharModelId(int32_t modelId)
{
	if (mCurrCharModelID != modelId)
	{
		mCurrCharModelID = modelId;
		OnChangeOfModelId();
	}
}

void KCharacter::setMountId(int32_t mountId)
{
	if (mCurrMountModelID != mountId)
	{
		mCurrMountModelID = mountId;
		OnChangeOfMountId();
	}
}

void KCharacter::UpdateEquip(PLAYER_EQUIP point)
{

}

void KCharacter::DoDataEvent_DataID()
{

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

void KCharacter::OnChangeOfModelId()
{
	UpdateModel_CharActionSet();

	if (mCurrCharModelID != INVALID_ID)
	{
		createCharRenderInterface();
	}
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
	if (mModelName.empty())
	{
		OGRE_EXCEPT(0);
	}
	mMainEntity->loadModel(mModelName);

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
	if (NULL != m_pCharacterData && !_CrtIsValidHeapPointer(m_pCharacterData))
	{
		m_pCharacterData = NULL;
	}
	if (NULL == m_pCharacterData)
	{
		m_pCharacterData = new KCharatcterBaseData(this);
	}
	return m_pCharacterData;
}
