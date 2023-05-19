#include "OgreHeader.h"
#include "OGActorFactoryManager.h"
#include "OGSKeletonMeshActor.h"
#include "OGImpactManager.h"
#include "player.h"
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


class	PlayerAASAnimPlayCallback: public Orphigine::SkeletonMeshComponent::AASAnimEndCallback
{
public:
	virtual void	onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
		uint64_t info)
	{

	}
};

class PlayerLogicModelHaveCreateCallback:public Orphigine::LogicModelHaveCreateCallback
{
private:
	Player* mPlayer;
public:
	PlayerLogicModelHaveCreateCallback(Player* player)
	{
		mPlayer = player;
	}
	virtual bool onLogicModelHaveCreate(int objId = -1, int logicModelId = -1, int typeId = -1)
	{
		mPlayer->setWeaponname(Ogre::String("Falchion"));
		return true;
	}
};

void MyCallback::onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
	uint64_t info)
{
	Player* player = (Player*)info;
	player->onAnimationEnd(animName, parentNodeType, parentNodeName);
}

const Ogre::String FOBJ_ACTOR_FILE = "logic model name";
Player::Player()
{
	initialize();
}


bool Player::initialize()
{
	mOrphigineObj =
		Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");
	std::string modelname = "ͻ����ʿŮ_01.lmodel";
	mOrphigineObj->createRenderInstance();
	mOrphigineObj->setProperty(FOBJ_ACTOR_FILE, modelname);
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
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->changeAttributes(names, values);


	Orphigine::SkeletonMeshActor* skeletonActor = (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
	Orphigine::SkeletonMeshComponent* model = skeletonActor->getLogicModel();

	if (model)
	{
		model->setWeaponTypeName("Falchion");
	}

	model->setAASAnimEndCallback(new PlayerAASAnimPlayCallback, (uint64_t)this);
	int32_t mCharacterID = 12;
	const CGameTable* pChar_Table = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	const _TABLE_CHARACTER_MODEL* pInfo = (const _TABLE_CHARACTER_MODEL*)pChar_Table->GetFieldDataByIndex(mCharacterID);


	mCallback = new PlayerLogicModelHaveCreateCallback(this);

	if (nullptr == m_pCharActionSet)
	{

		g_nProcess = 9;
		std::string filename = pInfo->m_pszActionSetName_None;

		CDBActionSet* setmgr = GetActionSetData();
		m_pCharActionSet = setmgr->GetActionSetFile(pInfo->m_pszActionSetName_None);
	}

	mPathComponent = new PathComponent(this);

	//mousetarget

	mMouseNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode("mouse");
	Ogre::String effectName = "reachable_projector";
	mProjectorEffect = Orphigine::ImpactManager::getSingleton().createEffect(effectName, 0);
	mProjectorEffect->createSceneNode(mMouseNode);


	//createMount();
	return true;
}

void Player::setGamePosition(Ogre::Vector3& position)
{
	mGamePosition = position;

	Ogre::Vector3 fvEnginePosition;
	EngineManager::getSingleton().positionAxisTrans(GAT_GAME, mGamePosition,
		GAT_ENGINE, fvEnginePosition);

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setPosition(fvEnginePosition);

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getLogicModel();
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setVisible(true);
	//((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setForceIgnoreAAS(true);

	
	EngineManager::getSingleton().setMyPosition(fvEnginePosition);

	if (mMountObj)
	{
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->SetLogicModelIsCreateListener(mCallback);

		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setPosition(fvEnginePosition);

		((Orphigine::SkeletonMeshActor*)mMountObj.get())->getLogicModel();
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setVisible(true);
	}
	
	
	
}


const Ogre::Vector3& Player::getGamePosition()
{
	return mGamePosition;
}

Ogre::Real Player::getDirection()
{
	return mDirection;
}

void Player::setDirection(float dir)
{
	mDirection = dir;

	Ogre::Vector3 rotate;
	rotate.y = dir;

	Ogre::Quaternion qu(Ogre::Radian(dir), Ogre::Vector3::UNIT_Y);
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setOrientation(qu);
	if (mMountObj)
	{
		((Orphigine::SkeletonMeshActor*)mMountObj.get())->setOrientation(qu);
	}
	
}

void Player::setWeaponname(Ogre::String& name)
{

	mWeaponname = name;

	Orphigine::SkeletonMeshActor* actor = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get());
	Orphigine::SkeletonMeshComponent* model = actor->getLogicModel();
	if (model)
	{
		model->setWeaponTypeName(mWeaponname);
	}
}

void Player::input(KeyCode _key)
{
	if(_key == KeyCode::L)
	{
	
	}
	else if (_key == KeyCode::S)
	{
		//startSkill();
	}
	else if (_key == KeyCode::M)
	{
		startMood();
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

void Player::onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName)
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

void Player::ChangeAction(int32_t nActionType, float fDegree, int32_t nActionID)
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

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setAdvancedAnimationSystemMonitoringDegree(
		Orphigine::SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree(nActionType), fDegree);

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

void Player::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (_id == OIS::MB_Left)
	{
		Ogre::Vector3 fvTarget;
		Ogre::Vector3 fvSource(_absx, _absy, 0);
		EngineManager::getSingleton().positionAxisTrans(GAT_SCREEN, 
			fvSource, GAT_GAME, fvTarget);


		Ogre::Vector2 fvMyPos(mGamePosition.x, mGamePosition.z);
		Ogre::Vector2 fvTargetPos(fvTarget.x, fvTarget.z);

		mPathComponent->moveTo(fvMyPos, fvTargetPos);

		Ogre::Vector3 fvEnginePosition;
		EngineManager::getSingleton().positionAxisTrans(GAT_GAME, 
			fvTarget, GAT_ENGINE, fvEnginePosition);

		

		
		mMouseNode->setPosition(fvEnginePosition);
		mMouseNode->updatechildren();
		ChangeAction(CA_MOVING, 0.0f);
		ChangeAction(CA_JUMP, 0.0f);
		ChangeAction(CA_MOVING, 1.0f);
		ChangeAction(CA_WALK, 0.0f, BASE_ACTION_N_RUN);
	}
	
}

LPCSTR Player::getCharActionNameByActionSetID(int32_t nActionSetID, int32_t nWeaponType, BOOL* pbHideWeapon, int32_t* pnAppointedWeaponID)
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

eWEAPON_TYPE Player::getMainWeaponType()
{
	//ENUM_WEAPON_LOCATOR_TYPE weapon_type = WL_RIGHT;
	

	return WEAPON_TYPE_FALCHION;
}


bool Player::setCharActionSlot(
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
		Orphigine::Spell* pSkill = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getCurrentSkill();
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

bool Player::actorSetActionSlot
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

	Orphigine::SkeletonMeshComponent* pLogicModel = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getLogicModel();
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

void Player::update(float deltatime)
{
	mPathComponent->update(deltatime);
}

bool Player::startSkill()
{
	// ���þ���״̬
	ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE);
	// ��ʼ���ܶ���
	ChangeAction(CA_ATTACK, 1.0f);

	int32_t nRandAnimID = 125;
	float dir = mCurrentDirection;
	createSkillImpact(nRandAnimID, dir);

	

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

bool Player::createSkillImpact(int32_t nActionID, float fDir)
{
	LPCSTR lpszCharActionName = getCharActionNameByActionSetID(nActionID, getMainWeaponType(), NULL, NULL);
	if (lpszCharActionName)
	{
		int priority = 0;
		Ogre::Quaternion rot(Ogre::Radian(fDir), Ogre::Vector3(0.f, 1.0f, 0.f));
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->createSkill(
			lpszCharActionName, rot, Orphigine::E_ANIM_BOTH, true, false, 0.0f, priority);
		// �����Ƿ��б���������
		Orphigine::Spell* pSkill = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getCurrentSkill();
		if (pSkill)
		{
			return true;
		}
	}
	return false;
}

bool Player::startMood()
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

void Player::createMount()
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

	// ģ�ͱ�
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
		locator, (Orphigine::SkeletonMeshActor*)mOrphigineObj.get());


	ChangeAction(CA_RIDING, 1.0f);
}
