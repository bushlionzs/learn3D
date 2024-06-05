#include "OgreHeader.h"
#include "OGActorFactoryManager.h"
#include "OGSKeletonMeshActor.h"
#include "OGImpactManager.h"
#include "KPlayer.h"
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

class PlayerLogicModelHaveCreateCallback:public Orphigine::LogicModelHaveCreateCallback
{
private:
	KPlayer* mPlayer;
public:
	PlayerLogicModelHaveCreateCallback(KPlayer* player)
	{
		mPlayer = player;
	}
	virtual bool onLogicModelHaveCreate(int objId = -1, int logicModelId = -1, int typeId = -1)
	{
		Ogre::String dummy("Falchion");
		mPlayer->setWeaponname(dummy);
		return true;
	}
};

void MyCallback::onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
	uint64_t info)
{
	KPlayer* player = (KPlayer*)info;
	player->onAnimationEnd(animName, parentNodeType, parentNodeName);
}

const Ogre::String FOBJ_ACTOR_FILE = "logic model name";
KPlayer::KPlayer()
{
	initialize();
}


bool KPlayer::initialize()
{
	mOrphigineObj =
		Orphigine::ActorFactoryManager::getSingleton().createInstance("SkeletonMeshActor");

	std::string modelname = "突厥武士女_01.lmodel";
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
		"女主角发型_01_白.mesh",
		"新女主角脸_01.mesh",
		"突厥武士男刀_01.lmodel",
		"突厥武士女身体_01.mesh",
		"突厥武士女双手_01.mesh",
		"突厥武士女双脚_01.mesh"
	};
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->changeAttributes(names, values);


	Orphigine::SkeletonMeshActor* skeletonActor = (Orphigine::SkeletonMeshActor*)mOrphigineObj.get();
	Orphigine::SkeletonMeshComponent* model = skeletonActor->getLogicModel();

	if (model)
	{
		model->setWeaponTypeName("Falchion");
	}

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

	auto pos = Ogre::Vector3(6550.f, -568.960022f, -5200.00000f);
	mMouseNode->setPosition(pos);

	if (mProjectorEffect == nullptr)
	{
		Ogre::String effectName = "reachable_projector";
		mProjectorEffect = Orphigine::ImpactManager::getSingleton().createEffect(effectName, 1);
		mProjectorEffect->createSceneNode(mMouseNode);
		mProjectorEffect->setVisible(true);
	}
	return true;
}

void KPlayer::setGamePosition(Ogre::Vector3& position, bool useTerrainHeight)
{
	mGamePosition = position;

	Ogre::Vector3 fvEnginePosition;
	EngineManager::getSingleton().positionAxisTrans(GAT_GAME, mGamePosition,
		GAT_ENGINE, fvEnginePosition, useTerrainHeight);

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setPosition(fvEnginePosition);

	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getLogicModel();
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setVisible(true);
	//((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setForceIgnoreAAS(true);

	
	EngineManager::getSingleton().setMyPosition(fvEnginePosition);
	
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->SetLogicModelIsCreateListener(mCallback);
	
}


const Ogre::Vector3& KPlayer::getGamePosition()
{
	return mGamePosition;
}

Ogre::Real KPlayer::getDirection()
{
	return mDirection;
}

void KPlayer::setDirection(float dir)
{
	mDirection = dir;

	Ogre::Vector3 rotate;
	rotate.y = dir;

	Ogre::Quaternion qu(Ogre::Radian(dir), Ogre::Vector3::UNIT_Y);
	((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->setOrientation(qu);
}

void KPlayer::setWeaponname(Ogre::String& name)
{

	mWeaponname = name;

	Orphigine::SkeletonMeshActor* actor = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get());
	Orphigine::SkeletonMeshComponent* model = actor->getLogicModel();
	if (model)
	{
		model->setWeaponTypeName(mWeaponname);
	}
}

void KPlayer::input(KeyCode _key)
{
	if(_key == KeyCode::L)
	{
		/*ChangeAction(CA_MOVING, 0.0f);
		ChangeAction(CA_JUMP, 0.0f);
		ChangeAction(CA_MOVING, 1.0f);
		ChangeAction(CA_WALK, 1.0f);*/
	
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

void KPlayer::onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName)
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

void KPlayer::ChangeAction(int32_t nActionType, float fDegree, int32_t nActionID)
{
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
}

void KPlayer::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
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

LPCSTR KPlayer::getCharActionNameByActionSetID(int32_t nActionSetID, int32_t nWeaponType, BOOL* pbHideWeapon, int32_t* pnAppointedWeaponID)
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

eWEAPON_TYPE KPlayer::getMainWeaponType()
{
	//ENUM_WEAPON_LOCATOR_TYPE weapon_type = WL_RIGHT;
	

	return WEAPON_TYPE_FALCHION;
}


bool KPlayer::setCharActionSlot(
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

bool KPlayer::actorSetActionSlot
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

void KPlayer::update(float deltatime)
{
	mPathComponent->update(deltatime);
}

bool KPlayer::startSkill()
{
	// 设置警戒状态
	ChangeAction(CA_GUARD, 1.0f, BASE_ACTION_F_IDLE);
	// 开始技能动作
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

bool KPlayer::createSkillImpact(int32_t nActionID, float fDir)
{
	LPCSTR lpszCharActionName = getCharActionNameByActionSetID(nActionID, getMainWeaponType(), NULL, NULL);
	if (lpszCharActionName)
	{
		int priority = 0;
		Ogre::Quaternion rot(Ogre::Radian(fDir), Ogre::Vector3(0.f, 1.0f, 0.f));
		((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->createSkill(
			lpszCharActionName, rot, Orphigine::E_ANIM_BOTH, true, false, 0.0f, priority);
		// 技能是否有被立即创建
		Orphigine::Spell* pSkill = ((Orphigine::SkeletonMeshActor*)mOrphigineObj.get())->getCurrentSkill();
		if (pSkill)
		{
			return true;
		}
	}
	return false;
}

bool KPlayer::startMood()
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
