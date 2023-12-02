/*$T MapServer/Character.cpp GC 1.140 10/10/07 11:01:48 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "map/game_map.h"

#include "BaseTool.h"
#include "Behavior_Character.h"
#include "Character.h"
#include "skill/Spell_Helper.h"
#include "data/data_manager.h"
#include "CharActionDelegator.h"
#include "gameobject/ObjectManager.h"
#include "script/LuaSystem.h"
#include "net/messages/SCDeltailOfHealsAndDamage.h"
#include "net/net_message_manager.h"
#include "map/map_manager.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "gameobject/ObjectManager.h"
#include "gameobject/Player.h"
#include "gameobject/Behavior_Player.h"
#include "net/messages/SCCharStopAction.h"
#include "server_manager.h"

#define CHECK_SENDMSG_TIME	(1000)
#define ATTR_REFESH_TIME	(500)
#define REFESH_LEVEL_LIMIT	(10)

/*
 =======================================================================================================================
 =======================================================================================================================
 */

eREFESH_PROPERTY_TYPE Calc_RefeshAttrType(Character *pSour, Character *pTarget)
{
	 return REFESH_ATTR_TYPE_INVALID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Character::Character()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Character::~Character()
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::Init(const _INIT_OBJECT *pInit)
{
	__GUARD__ 
	if(!Creature::Init(pInit)) 
		return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	CreateTime = GET_TIME().TickCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	m_AttrMsgTimer.BeginTimer(ATTR_REFESH_TIME, CreateTime);
	m_AttrMsgToTeamIntervalCount = 0;
	m_PublicAttrVersion = 0;
	m_ProtectedAttrVersion = 0;
	MarkAllIntAttrDirtyFlags();
	MarkAllIntAttrRefixDirtyFlags();
	MarkAllBoolAttrDirtyFlags();
	InitAIObj();
	m_nAutoRepeatCooldown = 0;

	m_nView_PrevLevel = GetLevel();

	m_UpdateViewCharacterTimer.BeginTimer(1000, GET_TIME().TickCount());

	ResetReliveInfo();


	uint32	CheckZoneIntervalTime = 5000;

	mStateManager = new CharacterStateManager();

	mStateManager->Init(this);
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::InitAIObj()
{
	m_pAI_Character->Init(this);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::Clear(void)
{
	__GUARD__

	m_AttrMsgTimer.Clear();
	m_AttrMsgToTeamIntervalCount = 0;
	m_PublicAttrVersion = 0;
	m_ProtectedAttrVersion = 0;

	m_CharacterID = INVALID_ID;

	m_RecoverTimer.Clear();

	m_nActionTime = 0;
	m_nLockedTargetID = -1;
	m_nElapsedRevocerTick = 0;
	m_nElapsedRageRevocerTick = 0;
	m_eMoveMode = MOVE_MODE_RUN;
	m_pActionLogic = NULL;
	m_ActionParams.Reset();

	m_IntAttrs.ResetAttrs();
	m_IntAttrRefixs.ResetAttrs();
	m_BoolAttrs.ResetAttrs();

	m_nView_PrevLevel = -1;
	m_nView_PrevStealthLevel = -1;
	m_nView_PrevDetectLevel = -1;
	m_UpdateViewCharacterTimer.Clear();

	m_nMoodState = INVALID_MOOD_STATE;
	m_pGuard = NULL;
	ResetReliveInfo();
	Creature::Clear();
	m_pVisitor = NULL;
	for(int32 i = 0; i < SpellTemplateData::MAX_SUB_SKILL; ++i)
	{
		m_aSubSkill[i] = -1;
	}

	memset(m_DelayTimeSkillMissList, -1, sizeof(m_DelayTimeSkillMissList));
	memset(m_aHorseDataIndex, -1, sizeof(m_aHorseDataIndex));
	m_bImmuneAbsForLater = FALSE;


	m_uBaseAttribCrc = 0;
	m_uBaseAttribSum = 0;



	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::OnEnterMap(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object::	OnEnterMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::OnEnterMapSuccess(void)
{
	Object::OnEnterMapSuccess();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool Character::HeartBeat(uint32 uTime)
{
	if(false == Creature::HeartBeat(uTime))
	{
		return false;
	}

	UpdateGrid();
	HeartBeat_Action(uTime);
	HeartBeat_AutoRepeatCooldown(uTime);
	if(TRUE == IsActiveObj())
	{
		HeartBeat_Recover(uTime);
	}

	mStateManager->OnEvent_HeartBeat(uTime);
	HeartBeat_Cooldown(uTime);

	m_pAI_Character->Logic(uTime);
	if(IsActiveObj())
	{
		if(m_AttrMsgTimer.CountingTimer(uTime))
		{
			SendMsg_RefeshAttrib();

			SyncTeamMemberInfoToClient();
		}
	}

	EffectDelayTimeHeartBeat();
	/*SubSkillAutoUseHeartBeat();

	DelayTimeSkillMissHeartBeat();
	if (m_CheckZoneTimer.CountingTimer(uTime))
	{
		CheckArea();
	}*/

	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::HeartBeat_OutMap(uint32 uTime)
{
	return Creature::HeartBeat_OutMap(uTime);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::OnRegisterToGrid(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object::	OnRegisterToGrid();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}


void	Character::OnCharacterLogicStopped(BOOL bAbortive)
{
	if (!bAbortive)
	{
		return;
	}

	if (FALSE == IsCharacterLogicStopped())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ENUM_CHARACTER_LOGIC	eLogic = GetCharacterLogic();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch (eLogic)
		{
		case CHARACTER_LOGIC_MOVE:
		{
			SendArriveMSG();
		}
		break;

		case CHARACTER_LOGIC_USE_SKILL:
		{
			SendstopActionMSG();
		}
		break;

		case CHARACTER_LOGIC_IDLE:
		default:
			break;
		}
	}
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::SendMsg_RefeshAttrib(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::RequestBaseProperty(Player *pTargetHuman, BASEPROPERTY_REFESH_MODE nMode)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::IsCanRelive(void) const
{
	return m_bCanSkillRelive;
}

const Character::_RELIVE_INFO * Character::GetReliveInfo(BOOL bSkillRelive) const
{
	if(bSkillRelive && m_bCanSkillRelive)
	{
		return &m_SkillReliveInfo;
	}
	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::ResetReliveInfo(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bCanSkillRelive = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_SkillReliveInfo.Reset();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::GetNearCanDropPos(GLPos &pos)
{
	__GUARD__ return FALSE;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::HeartBeat_Action(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Time_t	m_nDeltaTime = GetLogicTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 < m_nActionTime)
	{
		m_nActionTime -= m_nDeltaTime;
		0 > m_nActionTime ? m_nActionTime = 0 : NULL;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::HeartBeat_AutoRepeatCooldown(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Time_t	m_nDeltaTime = GetLogicTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 < m_nAutoRepeatCooldown)
	{
		m_nAutoRepeatCooldown -= m_nDeltaTime;
		if(m_nAutoRepeatCooldown < 0) m_nAutoRepeatCooldown = 0;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::SetReliveInfo(BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo)
{
	if(pReliveInfo == NULL)
	{
		KCheck(pReliveInfo != NULL && "Character::SetReliveInfo");
		return;
	}

	m_bCanSkillRelive = bSkillRelive;
	if(bSkillRelive)
	{
		m_SkillReliveInfo = *pReliveInfo;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Object *Character::GetMyShadowGuard(void)
{
	return nullptr;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Object *Character::GetMyPet(int32 iIndex)
{
	return nullptr;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Object *Character::GetMyMaster(void)
{
	return nullptr;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::UpdateViewCharacter(void)
{

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Character::DepletingUsedItem(void)
{
	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::Accept(CharacterVisitor *pVisitor)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pVisitor = pVisitor;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Character::GetHorseDataIndex(int32 iIndex)
{
	__GUARD__ if(iIndex < 0 || iIndex >= MAX_HORSE_DATA_INDEX)
	{
		return INVALID_ID;
	}

	return m_aHorseDataIndex[iIndex];
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::SetHorseDataIndex(int32 iIndex, int32 iVal)
{
	__GUARD__ if(iIndex < 0 || iIndex >= MAX_HORSE_DATA_INDEX)
	{
		return;
	}

	m_aHorseDataIndex[iIndex] = iVal;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::CleanupHorseBuff()
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Character::SetMoveMode(ENUM_MOVE_MODE eMoveMode)
{
	if (eMoveMode != GetMoveMode())
	{
		m_eMoveMode = eMoveMode;
		MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVE_SPEED);
		MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED);
	}
}

ENUM_CHARACTER_LOGIC	Character::GetCharacterLogic(void)
{
	return mStateManager->GetCurrentLogic();
}


int32	Character::GetExpRefix(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_EXP_REFIX))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseExpRefix();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nValue += GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_EXP_REFIX);
		0 > nValue ? nValue = 0 : NULL;
		MAX_EXP_REFIX_IN_CHAR < nValue ? nValue = MAX_EXP_REFIX_IN_CHAR : NULL;
		SetIntAttr(CharIntProperty::PROPERTY_EXP_REFIX, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_EXP_REFIX);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_EXP_REFIX);
}

int32	Character::GetStealthLevel(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_STEALTH_LEVEL))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_STEALTH_LEVEL);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_STEALTH_LEVEL, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_STEALTH_LEVEL);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_STEALTH_LEVEL);
}

int32	Character::GetDetectLevel(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DETECT_LEVEL))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_DETECT_LEVEL);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_DETECT_LEVEL, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DETECT_LEVEL);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_DETECT_LEVEL);
}

bool		Character::IsAlive(void)
{
	if (0 >= GetHPNoClip())
	{
		return false;
	}

	if (TRUE == GetBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_ALIVE))
	{
		/*~~~~~~~~~~~~~~~~~~*/
		BOOL	bValue = TRUE;
		/*~~~~~~~~~~~~~~~~~~*/

		if (TRUE == Effect_GetBoolAttrRefix(CharBoolAttrs::PROPERTY_ALIVE, bValue))
		{
			SetBoolAttr(CharBoolAttrs::PROPERTY_ALIVE, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs::PROPERTY_ALIVE, TRUE);
		}

		ClearBoolAttrDirtyFlag(CharBoolAttrs::PROPERTY_ALIVE);
	}

	return GetBoolAttr(CharBoolAttrs::PROPERTY_ALIVE);

}

bool Character::IsAliveInDeed(void)
{
	return true;
}

bool Character::IsMoving()
{
	return mStateManager->IsMoving();
}

bool Character::IsUnbreakable()
{
	return false;
}

bool Character::IsLimitMove()
{
	if (CanMove())
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void	Character::FaceTo(const GLPos* pPos)
{
	SetDir(KLAngle(GetGLPos(), pPos));
}

void	Character::FaceTo(const Object* pObj)
{
	FaceTo(pObj->GetGLPos());
}

bool        Character::IsDie()
{
	return(!IsAliveInDeed());
}

BOOL Character::CanMove(void)
{
	if (TRUE == GetBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_CAN_MOVE))
	{
		/*~~~~~~~~~~~~~~~~~~*/
		BOOL	bValue = TRUE;
		/*~~~~~~~~~~~~~~~~~~*/

		if (TRUE == Effect_GetBoolAttrRefix(CharBoolAttrs::PROPERTY_CAN_MOVE, bValue))
		{
			SetBoolAttr(CharBoolAttrs::PROPERTY_CAN_MOVE, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs::PROPERTY_CAN_MOVE, TRUE);
		}

		ClearBoolAttrDirtyFlag(CharBoolAttrs::PROPERTY_CAN_MOVE);
	}

	return GetBoolAttr(CharBoolAttrs::PROPERTY_CAN_MOVE);
}
BOOL	Character::CanUseSkillNow(SpellID_t nID)
{
	BOOL	bCanUse = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (0 >= GetActionTime() && GetGlobalActionDelegator().CanDoNextAction(*this))
	{
		bCanUse = TRUE;
	}

	return bCanUse;
}
BOOL		Character::IsSpellCooldowned(SpellID_t nID)
{
	SpellTemplateData const* pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pSkillTemplate)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	CooldownID_t	nCooldownID = (CooldownID_t)(pSkillTemplate->GetCooldownID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (INVALID_ID == nCooldownID || pSkillTemplate->IsAutoShotSkill())
	{
		if (GetAutoRepeatCooldown() > 0)
		{
			return FALSE;
		}

		return TRUE;
	}
	else if (FALSE == IsCooldowned(nCooldownID))
	{
		return FALSE;
	}

	return TRUE;
}
BOOL		Character::CanUseThisSpellInThisStatus(SpellID_t nSkillID)
{
	SpellTemplateData const* pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pSkillTemplate)
	{
		return FALSE;
	}

	/*if (TRUE == pSkillTemplate->GetDisableByFlag1())
	{
		if (FALSE == CanActionFlag1())
		{
			return FALSE;
		}
	}

	if (TRUE == pSkillTemplate->GetDisableByFlag2())
	{
		if (FALSE == CanActionFlag2())
		{
			return FALSE;
		}
	}

	if (TRUE == pSkillTemplate->GetDisableByFlag3())
	{
		if (INVALID_ID != GetMountID())
		{
			return FALSE;
		}
	}

	if (TRUE == pSkillTemplate->GetDisableByFlag4())
	{
		if (!CanActionFlag3())
		{
			return FALSE;
		}
	}*/

	return TRUE;
}


BOOL Character::RefixSpell(SpellInfo& rSkillInfo)
{
	if (Object::OBJECT_CLASS_MONSTER == GetObjType())
	{
		return TRUE;
	}

	if (Object::OBJECT_CLASS_PLAYER == GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_SPELL_LIST const& rList = ((Player*)this)->GetSpellList();
		uchar const& rCount = rList.m_Count;
		SpellInfo		PassiveSkill;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for (int32 i = 0; rCount > i; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_PLAYER_SPELL const& rSkill = rList.m_aSkill[i];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			PassiveSkill.Init();
			if (TRUE == g_SpellCore.InstanceSpell(PassiveSkill, *this, rSkill.m_nSkillID))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BaseSpellLogic const* pLogic = Spell_GetLogic(PassiveSkill);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (NULL != pLogic)
				{
					pLogic->Refix_SkillInstance(PassiveSkill, rSkillInfo);
				}
			}
		}
	}

	return TRUE;
}

BOOL		Character::FillCampData(Character* pObj, _HUMAN_CAMP_DATA* pData)
{

	ObjectClass		nType = pObj->GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nType == OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player* pPlayer = (Player*)(pObj);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pPlayer);
		KCheck(pPlayer->GetMap());
		pData->nObjId = pPlayer->GetID();
		pData->nLevel = pPlayer->GetLevel();
		pData->nSceneID = pPlayer->GetMap()->MapID();
		/*pData->nSceneSafeLevel = pPlayer->GetMap()->GetMapSafeLevel();
		pData->nSceneRestrictiveMode = pPlayer->GetMap()->GetMapRestrictiveMode();
		pData->nTeamID = pPlayer->GetTeamID();
		pData->nGuildID = pPlayer->GetGuildID();
		pData->nSafeArea = pPlayer->IsInSafeArea(pData->nSafeArea_CampID) ? 1 : 0;
		pData->m_duelData = pPlayer->GetDuelData();*/
	}
	else if (nType == OBJECT_CLASS_PET)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character* pOwner = pObj->GetOwner();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pOwner)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Player* pPlayer = (Player*)(pOwner);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pPlayer);
			KCheck(pPlayer->GetMap());
			pData->nLevel = pPlayer->GetLevel();
			pData->nSceneID = pPlayer->GetMap()->MapID();
			/*pData->nSceneSafeLevel = pPlayer->GetMap()->GetMapSafeLevel();
			pData->nSceneRestrictiveMode = pPlayer->GetMap()->GetMapRestrictiveMode();
			pData->nTeamID = pPlayer->GetTeamID();
			pData->nGuildID = pPlayer->GetGuildID();
			pData->nSafeArea = pPlayer->IsInSafeArea(pData->nSafeArea_CampID) ? 1 : 0;*/
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL	Character::IsEnemyCamp(Character& rTar)
{
	ObjID_t	ObjID_A = GetID();
	ObjID_t			ObjID_B = rTar.GetID();
	ObjID_t			ObjID_Owner_A = GetOwnerID();
	ObjID_t			ObjID_Owner_B = rTar.GetOwnerID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (ObjID_Owner_A != INVALID_ID || ObjID_Owner_B != INVALID_ID)
	{
		if (ObjID_Owner_A == ObjID_B || ObjID_Owner_B == ObjID_A || ObjID_Owner_A == ObjID_Owner_B)
		{
			return FALSE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL			bUsePKMode = FALSE;
	_HUMAN_CAMP_DATA	CampA = GetCampData();
	_HUMAN_CAMP_DATA	CampB = rTar.GetCampData();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (FillCampData(this, &CampA) && FillCampData(&rTar, &CampB))
	{
		bUsePKMode = TRUE;
	}

	if (Calc_RelationType(&CampA, &CampB, bUsePKMode, DataManager::GetSingletonPtr()->getCampAndStandDataMgr()) == RELATION_FRIEND)
		return FALSE;
	else
		return TRUE;
}

BOOL	Character::IsFriendCamp(Character& rTar)
{
	return FALSE == IsEnemyCamp(rTar);
}

BOOL Character::IsEnemy(Character* pCharacter)
{
	return TRUE;
}

BOOL Character::IsFriend(Character* pCharacter)
{
	return !IsEnemy(pCharacter);
}

BOOL Character::IsPartner(Character* pCharacter)
{
	return FALSE;
}

int32	Character::GetIntAttr_EX(CharIntProperty::Index_T nIndex)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(nIndex))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 nBaseAttr = GetBaseIntAttr_EX(nIndex);
		int32 nImpactAndSkillRefix = 0;
		int32 nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nImpactAndSkillRefix = GetIntAttrRefix_EX(GetIntAttrRefixIndexByIntAttrIndex(nIndex));
		nValue = nBaseAttr + nImpactAndSkillRefix;
		CHECK_ATTR_VALUE(nValue);
		SetIntAttr((CharIntProperty::Index_T)nIndex, nValue);
		ClearIntAttrDirtyFlag_EX(nIndex);
	}

	return GetIntAttr((CharIntProperty::Index_T)nIndex);
}

BOOL	Character::GetIntAttrDirtyFlag_EX(CharIntProperty::Index_T nIndex)
{
	bool a = m_IntAttrDirtyFlags.GetFlagByIndex(nIndex);
	CharIntAttrRefixs::Index_T x = GetIntAttrRefixIndexByIntAttrIndex(nIndex);
	bool b = m_IntAttrRefixDirtyFlags.GetFlagByIndex(x);

	return a || b;
}

void	Character::ClearIntAttrDirtyFlag_EX(CharIntProperty::Index_T nIndex)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(nIndex);
}

void	Character::MarkIntAttrDirtyFlag_EX(CharIntProperty::Index_T nIndex)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(nIndex);

	switch (nIndex)
	{
	case CharIntProperty::PROPERTY_STR:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_NEAR);
		break;
	case CharIntProperty::PROPERTY_CON:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MAX_HP);
		break;
	case CharIntProperty::PROPERTY_INT:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MAX_RAGE);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_DEFENCE_MAGIC);
		break;
	case CharIntProperty::PROPERTY_DEX:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_HIT);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MISS);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_CRITICAL);
		break;
	}
}

int32	Character::GetBaseIntAttr_EX(CharIntProperty::Index_T nIndex)
{
	switch (nIndex)
	{
	case CharIntProperty::PROPERTY_ZOOM_SCALE: return 1000;
	}
	return 0;
}

void	Character::SetBaseIntAttr_EX(CharIntProperty::Index_T nIndex, int32 const nValue)
{

}

int32			Character::GetIntAttrRefix_EX(CharIntAttrRefixs::Index_T nIndex)
{
	if (TRUE == GetIntAttrRefixDirtyFlag_EX(nIndex))
	{
		/*~~~~~~~~~~~~~~~*/
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~*/
		if (nIndex == CharIntAttrRefixs::REFIX_PROPERTY_CAMP ||
			nIndex == CharIntAttrRefixs::REFIX_PROPERTY_MODEL_ID ||
			nIndex == CharIntAttrRefixs::REFIX_PROPERTY_MOUNT_ID)
		{
			nValue = INVALID_ID;
		}
		Effect_GetIntAttrRefix(nIndex, nValue);
		SetIntAttrRefix(nIndex, nValue);
		ClearIntAttrRefixDirtyFlag_EX(nIndex);
	}

	return Get_Property_IntAttrRefix(nIndex);
}

void	Character::SetIntAttrRefix_EX(CharIntAttrRefixs::Index_T nIndex, int32 const nValue)
{
	SetIntAttrRefix(nIndex, nValue);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	MarkIntAttrRefixDirtyFlag_EX(nIndex);
}

BOOL			Character::GetIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::Index_T nIndex)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(nIndex);
}
void			Character::ClearIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::Index_T nIndex)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(nIndex);
	switch (nIndex)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_DEX:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_DEX);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_HIT);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MISS);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_CRITICAL);
		break;
	}
}
void			Character::MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::Index_T nIndex)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(nIndex);
	switch (nIndex)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_STR:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_STR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_NEAR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_FAR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_MAGIC);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_HIT);
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_CON:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_CON);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MAX_HP);
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_INT:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_INT);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MAX_RAGE);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_MAGIC);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_NEAR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_FAR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_CRITICAL);
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_DEX:
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_MAGIC);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_NEAR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_ATTACK_FAR);
		m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntProperty::PROPERTY_MISS);
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_STEALTH_LEVEL:
		//OnEvent_StealthLevelChanged();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_DETECT_LEVEL:
		//OnEvent_DetectLevelChanged();
		break;
	}
}

CharIntAttrRefixs::Index_T	Character::GetIntAttrRefixIndexByIntAttrIndex(CharIntProperty::Index_T nIndex)
{
#define PROPERTY_REGISTER(a) case CharIntProperty::a: return RETURNREFIX(a);

		switch (nIndex)
		{
			PROPERTY_REGISTER(PROPERTY_STR)
				PROPERTY_REGISTER(PROPERTY_CON)
				PROPERTY_REGISTER(PROPERTY_INT)
				PROPERTY_REGISTER(PROPERTY_DEX)
				PROPERTY_REGISTER(PROPERTY_MAX_HP)
				PROPERTY_REGISTER(PROPERTY_HP_REGENERATE)
				PROPERTY_REGISTER(PROPERTY_MAX_MP)
				PROPERTY_REGISTER(PROPERTY_MP_REGENERATE)
				PROPERTY_REGISTER(PROPERTY_MAX_STRIKE_POINT)
				PROPERTY_REGISTER(PROPERTY_MAX_RAGE)
				PROPERTY_REGISTER(PROPERTY_RAGE_REGENERATE)
				PROPERTY_REGISTER(PROPERTY_CAMP)
				PROPERTY_REGISTER(PROPERTY_MODEL_ID)
				PROPERTY_REGISTER(PROPERTY_MOUNT_ID)
				PROPERTY_REGISTER(PROPERTY_EXP_REFIX)
				PROPERTY_REGISTER(PROPERTY_STEALTH_LEVEL)
				PROPERTY_REGISTER(PROPERTY_DETECT_LEVEL)
				PROPERTY_REGISTER(PROPERTY_ATTACK_NEAR)
				PROPERTY_REGISTER(PROPERTY_ATTACK_FAR)
				PROPERTY_REGISTER(PROPERTY_DEFENCE_NEAR)
				PROPERTY_REGISTER(PROPERTY_DEFENCE_FAR)
				PROPERTY_REGISTER(PROPERTY_TOUGHNESS)
				PROPERTY_REGISTER(PROPERTY_NEARATT_REDUCE)
				PROPERTY_REGISTER(PROPERTY_FARATT_REDUCE)
				PROPERTY_REGISTER(PROPERTY_MAGICATT_REDUCE)
				PROPERTY_REGISTER(PROPERTY_DREAD_RESIST)
				PROPERTY_REGISTER(PROPERTY_COMA_RESIST)
				PROPERTY_REGISTER(PROPERTY_HUSH_RESIST)
				PROPERTY_REGISTER(PROPERTY_UNARMY_RESIST)
				PROPERTY_REGISTER(PROPERTY_ATTACKSPEED_RESIST)
				PROPERTY_REGISTER(PROPERTY_SKILLSPEED_RESIST)
				PROPERTY_REGISTER(PROPERTY_MOVEREDUCE_RESIST)
				PROPERTY_REGISTER(PROPERTY_ATTACK_MAGIC)
				PROPERTY_REGISTER(PROPERTY_DEFENCE_MAGIC)
				PROPERTY_REGISTER(PROPERTY_ATTACK_COLD)
				PROPERTY_REGISTER(PROPERTY_RESIST_COLD)
				PROPERTY_REGISTER(PROPERTY_ATTACK_FIRE)
				PROPERTY_REGISTER(PROPERTY_RESIST_FIRE)
				PROPERTY_REGISTER(PROPERTY_ATTACK_LIGHT)
				PROPERTY_REGISTER(PROPERTY_RESIST_LIGHT)
				PROPERTY_REGISTER(PROPERTY_ATTACK_POISON)
				PROPERTY_REGISTER(PROPERTY_RESIST_POISON)
				PROPERTY_REGISTER(PROPERTY_MISS)
				PROPERTY_REGISTER(PROPERTY_HIT)
				PROPERTY_REGISTER(PROPERTY_CRITICAL)
				PROPERTY_REGISTER(PROPERTY_MOVE_SPEED)
				PROPERTY_REGISTER(PROPERTY_ATTACK_SPEED)
				PROPERTY_REGISTER(PROPERTY_REDUCE_SLOWER_DURATION)
				PROPERTY_REGISTER(PROPERTY_REDUCE_WEAKEN_DURATION)
				PROPERTY_REGISTER(PROPERTY_REDUCE_FAINT_DURATION)
				PROPERTY_REGISTER(PROPERTY_REDUCE_POISONED_DURATION)
				PROPERTY_REGISTER(PROPERTY_VISION_RANGE)
				PROPERTY_REGISTER(PROPERTY_VIGOR_INC_RATE)
				PROPERTY_REGISTER(PROPERTY_MAX_VIGOR)
				PROPERTY_REGISTER(PROPERTY_CRITICAL_HURT)
				PROPERTY_REGISTER(PROPERTY_IGNORE_NEAR_IMMUNITY)
				PROPERTY_REGISTER(PROPERTY_IGNORE_FAR_IMMUNITY)
				PROPERTY_REGISTER(PROPERTY_IGNORE_MAGIC_IMMUNITY)
				PROPERTY_REGISTER(PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL)
				PROPERTY_REGISTER(PROPERTY_FAR_HIT_FOR_CONTROL_SPELL)
				PROPERTY_REGISTER(PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL)
				PROPERTY_REGISTER(PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL)
				PROPERTY_REGISTER(PROPERTY_FAR_MISS_FOR_CONTROL_SPELL)
				PROPERTY_REGISTER(PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL)
				PROPERTY_REGISTER(PROPERTY_ZOOM_SCALE)

		default: KCheck(FALSE); break;
		}
	return CharIntAttrRefixs::REFIX_PROPERTY_MAX_INDEX;
}

ITEM_PROPERTY				Character::GetItemIntAttrRefixIndexByIntAttrIndex(CharIntProperty::Index_T nIndex)
{
	switch (nIndex)
	{
	case CharIntProperty::PROPERTY_IGNORE_NEAR_IMMUNITY:	return RETURNITEMREFIX(PROPERTY_IGNORE_NEAR_IMMUNITY);
	case CharIntProperty::PROPERTY_IGNORE_FAR_IMMUNITY:	return RETURNITEMREFIX(PROPERTY_IGNORE_FAR_IMMUNITY);
	case CharIntProperty::PROPERTY_IGNORE_MAGIC_IMMUNITY:	return RETURNITEMREFIX(PROPERTY_IGNORE_MAGIC_IMMUNITY);

	case CharIntProperty::PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL:		return RETURNITEMREFIX(PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL);
	case CharIntProperty::PROPERTY_FAR_HIT_FOR_CONTROL_SPELL:		return RETURNITEMREFIX(PROPERTY_FAR_HIT_FOR_CONTROL_SPELL);
	case CharIntProperty::PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL:	return RETURNITEMREFIX(PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL);
	case CharIntProperty::PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL:	return RETURNITEMREFIX(PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL);
	case CharIntProperty::PROPERTY_FAR_MISS_FOR_CONTROL_SPELL:		return RETURNITEMREFIX(PROPERTY_FAR_MISS_FOR_CONTROL_SPELL);
	case CharIntProperty::PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL:	return RETURNITEMREFIX(PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL);
	case CharIntProperty::PROPERTY_ZOOM_SCALE:						return RETURNITEMREFIX(PROPERTY_ZOOM_SCALE);

	}
	KCheck(FALSE);
	return IPROPERTY_NUMBER;
}

void	Character::ClearBoolAttrFlag_EX(CharBoolAttrs::Index_T nIndex)
{
	SetBoolAttr(nIndex, FALSE);
}

void	Character::MarkBoolAttrFlag_EX(CharBoolAttrs::Index_T nIndex)
{
	SetBoolAttr(nIndex, TRUE);
}

BOOL	Character::GetBoolAttrDirtyFlag_EX(CharBoolAttrs::Index_T nIndex)
{
	return m_BoolAttrDirtyFlags.GetFlagByIndex(nIndex);
}

void	Character::ClearBoolAttrDirtyFlag_EX(CharBoolAttrs::Index_T nIndex)
{
	m_BoolAttrDirtyFlags.ClearFlagByIndex(nIndex);
}

void	Character::MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::Index_T nIndex)
{
	m_BoolAttrDirtyFlags.MarkFlagByIndex(nIndex);
}

/**************************************************************************
END 通用的标记操作
**************************************************************************/

void		Character::MarkLevelOneAttrDirtyFlag(void)
{
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CON);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_INT);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEX);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_STR);

	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CON);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_INT);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEX);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_STR);

	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_HP);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_NEAR);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_FAR);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_MAGIC);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HIT);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MISS);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CRITICAL);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_RAGE);

	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_HIT);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MISS);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL);
	MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_RAGE);
}

void		Character::MarkLevelOneAttrDirtyFlagAndSendAttrMsg(void)
{
	MarkLevelOneAttrDirtyFlag();
	SendMsg_RefeshAttrib();
}

int32		Character::GetExpMultRefixDirtyFlag(void)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs::REFIX_MULT_EXP);
}

void		Character::ClearExpMultRefixDirtyFlag(void)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs::REFIX_MULT_EXP);
}

void		Character::MarkExpMultRefixDirtyFlag(void)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs::REFIX_MULT_EXP);
}

void		Character::SetBaseAttribCrcCode(uint64 crc)
{
	m_uBaseAttribCrc = crc;
}

uint64		Character::GetBaseAttribCrcCode(void)
{
	return m_uBaseAttribCrc;
}

void		Character::SetBaseAttribSumCode(uint64 sum)
{
	m_uBaseAttribSum = sum;
}

uint64		Character::GetBaseAttribSumCode(void)
{
	return m_uBaseAttribSum;
}

void		Character::SetGuildInfoCrcCode(uint64)
{
	
}

uint64		Character::GetGuildInfoCrcCode(void)
{
	return 0;
}

void		Character::SetGuildInfoSumCode(uint64)
{

}

uint64		Character::GetGuildInfoSumCode(void)
{
	return 0;
}

void	Character::DirectMoveTo(const GLPos* pTar)
{

}
void	Character::DirectTo(GLPos* pTar, BOOL bMove)
{

}

Behavior_Character* Character::GetAIObj(void) const
{
	return m_pAI_Character;
}

SpellInfo& Character::GetSpellInfo(void)
{
	return m_SkillInfo;
};

SpellTargetingAndDepletingParams& Character::GetTargetingAndDepletingParams(void)
{
	return m_TargetingAndDepletingParams;
};




OPT_RESULT Character::BHV_Idle(void)
{
	return OR_OK;
}

OPT_RESULT Character::BHV_Jump(void)
{
	return OR_OK;
}

OPT_RESULT Character::BHV_Move
(
	int32		nHandleID,
	uint16		wNumTargetPos,
	const GLPos* paTargetPos,
	int32		nStopLogicCount,
	const GLPos* paCurPos,
	ObjID_t		nSenderID
)
{
	__GUARD__ m_oStatePara.nHandleID = nHandleID;
	m_oStatePara.wNumTargetPos = wNumTargetPos;
	m_oStatePara.paTargetPos = paTargetPos;
	m_oStatePara.nStopLogicCount = nStopLogicCount;
	m_oStatePara.paCurPos = paCurPos;
	m_oStatePara.idSender = nSenderID;
	return mStateManager->OnCommandMove();

	if (this->GetID() == 1)
	{
		GameMap* pScene = MapManager::GetSingletonPtr()->getMap(87);

		Object* pObj = pScene->GetSpecificObjByID(15000);

		float fdist = KLSqrt(paTargetPos, pObj->GetGLPos());

		if (fdist < 0.1f)
		{
			int kk = 0;
		}
	}

	__UNGUARD__ return OR_OK;
}

OPT_RESULT	Character::BHV_Stop(void)
{
	mStateManager->OnCommandStop();
	return OR_OK;
}

void	Character::MoveTo(int32 nHandleID, GLPos* pTar)
{

}
void	Character::MoveTo(int32 nHandleID, GLPos* pCur, GLPos* pTar)
{

}

OPT_RESULT Character::BHV_UseSkill
(
	SpellID_t	idSkill,
	ObjID_t		idTarget,
	const GLPos* pTargetPos,
	int32		iHurtDelayTime,
	float		fDir,
	GUID_t		guidTarget
)
{
	m_oStatePara.fDir = fDir;
	m_oStatePara.guidTarget = guidTarget;
	m_oStatePara.idSkill = idSkill;
	m_oStatePara.idTarget = idTarget;
	m_oStatePara.iHurtDelayTime = iHurtDelayTime;
	m_oStatePara.paTargetPos = pTargetPos;

	return mStateManager->OnCommandSkill();
}

OPT_RESULT Character::BHV_StopSkill()
{
	return OR_OK;
}

OPT_RESULT Character::BHV_StopMove()
{
	return OR_OK;
}


const SCampData* Character::GetCampData(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SCampData* pCampData = GetBaseCampData();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pCampData != NULL)
	{
		m_CampDataRefix = *pCampData;
		m_CampDataRefix.m_nCampID = GetCampID();
		return &m_CampDataRefix;
	}
	else
	{
		return NULL;
	}
}

int32_t	Character::GetMountID(void)
{
	return GetIntAttr(CharIntProperty::PROPERTY_MOUNT_ID);
}

void	Character::SetMountID(int32_t iMountID)
{
	SetIntAttr(CharIntProperty::PROPERTY_MOUNT_ID, iMountID);
}


void	Character::OnEvent_ActionStarted(void)
{

}

BOOL		Character::CanActionFlag1(void)
{
	return true;
}

BOOL		Character::CanActionFlag2(void)
{
	return true;
}

BOOL		Character::CanActionFlag3(void)
{
	return true;
}

BOOL Character::IsCharacterLogicStopped(void)
{
	return mStateManager->IsCharacterLogicStopped();
}

void	Character::SendArriveMSG()
{
	//XCArrive	msgArrive;
	///*~~~~~~~~~~~~~~~~~~~~~~*/

	//msgArrive.SetObjID(GetID());
	//msgArrive.SetHandleID(GetMoveLogicCount());
	//msgArrive.SetWorldPos(GetGLPos());

	//GetMap()->BroadCast(&msgArrive, this, TRUE);
	//NetManager::GetSingletonPtr()->sendNetMessage(nullptr);
}

void	Character::SendstopActionMSG()
{
	SCCharStopAction* packet = new SCCharStopAction;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	packet->setObjectId(GetID());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo& oSkillInf = GetSpellInfo();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (oSkillInf.GetSpellLogicCount() != INVALID_ID)
	{
		packet->setLogicCount(oSkillInf.GetSpellLogicCount());
	}
	else
	{
		packet->setLogicCount(GetLogicCount());
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ActionParams_T& rParams = GetActionParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	packet->setStopTime(rParams.GetContinuance());

	//NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

void Character::StopCharacterLogic(BOOL bAbortive)
{
	OnCharacterLogicStopped(bAbortive);
}


void	Character::ResetIntAttrs(void)
{
	m_IntAttrs.ResetAttrs();
	m_IntAttrs.SetAttr(CharIntProperty::PROPERTY_CAMP, INVALID_ID);
	m_IntAttrs.SetAttr(CharIntProperty::PROPERTY_MODEL_ID, INVALID_ID);
	MarkAllIntAttrDirtyFlags();
}

void Character::ResetIntAttrRefixs(void)
{
	m_IntAttrRefixs.ResetAttrs();
	m_IntAttrRefixs.SetAttr(CharIntAttrRefixs::REFIX_PROPERTY_CAMP, INVALID_ID);
	m_IntAttrRefixs.SetAttr(CharIntAttrRefixs::REFIX_PROPERTY_MODEL_ID, INVALID_ID);
	MarkAllIntAttrRefixDirtyFlags();
}

void Character::ResetBoolAttr(void)
{
	m_BoolAttrs.ResetAttrs();
	MarkAllBoolAttrDirtyFlags();
}

void	Character::NormalizeWorldPos(GLPos& sPos) const
{

}

float	Character::WordPosLength(float fX, float fY) const
{
	return 0.0f;
}

void	Character::RefixSkill(SpellInfo& rSkill)
{
	RefixSpell(rSkill);
	Effect_RefixSkill(rSkill);
}

void	Character::ManaIncrement(int32 nIncrement, int32 iLogicCount, Character* pCharacter)
{

}

void	Character::RageIncrement(int32 nIncrement, int32 iLogicCount, Character* pCharacter)
{

}

void	Character::RefixRageRegeneration(int32& rRageRegeneration)
{

}

void	Character::Effect_OnEffectFadeOut(UNIT_EFFECT& rImp, BOOL bForceDispel)
{

}

void	Character::OnEvent_Damages
(
	int32_t const* const	pDamage,
	ObjID_t			nAttackerID,
	BOOL			bCritical,
	SpellID_t		nSkillID,
	int32_t			iLogicCount
)
{
	int32 DamageList[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	DamageList[DAMAGE_TYPE_NEAR] = pDamage[DAMAGE_TYPE_NEAR];
	DamageList[DAMAGE_TYPE_FAR] = pDamage[DAMAGE_TYPE_FAR];
	DamageList[DAMAGE_TYPE_M] = pDamage[DAMAGE_TYPE_M];
	DamageList[DAMAGE_TYPE_COLD] = pDamage[DAMAGE_TYPE_COLD];
	DamageList[DAMAGE_TYPE_FIRE] = pDamage[DAMAGE_TYPE_FIRE];
	DamageList[DAMAGE_TYPE_LIGHT] = pDamage[DAMAGE_TYPE_LIGHT];
	DamageList[DAMAGE_TYPE_POISON] = pDamage[DAMAGE_TYPE_POISON];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = GetMap();
	Character* pAttacker = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pMap && INVALID_ID != nAttackerID)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ObjectManager* pObjManager = pMap->GetObjManager();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL != pObjManager)
		{

			Object* pObj = pObjManager->GetObj(nAttackerID);
			if (pObj)
			{
				if (IsObjCharacter(pObj->GetObjType()))
				{
					pAttacker = (Character*)(pObj);
				}
			}
		}
	}

	Effect_OnDamages(DamageList, pAttacker, nSkillID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage = DamageList[DAMAGE_TYPE_NEAR] +
		DamageList[DAMAGE_TYPE_FAR] +
		DamageList[DAMAGE_TYPE_M] +
		DamageList[DAMAGE_TYPE_COLD] +
		DamageList[DAMAGE_TYPE_FIRE] +
		DamageList[DAMAGE_TYPE_LIGHT] +
		DamageList[DAMAGE_TYPE_POISON];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	0 >= nDamage ? nDamage = 1 : NULL;

	Effect_OnDamage(nDamage, pAttacker, nSkillID);

	Effect_OnFinalDamage(nDamage, pAttacker, nSkillID);

	int32 nFinalDamage = HealthIncrement(-nDamage, iLogicCount, pAttacker, bCritical);

	if (NULL != pAttacker)
	{
		pAttacker->OnEvent_DamageTarget(-nFinalDamage, *this, nSkillID);
	}

	if (Object::OBJECT_CLASS_PLAYER == GetObjType())
	{
		Profession_OnDamage(nDamage);
	}
}

void	Character::OnEvent_Damage
(
	int32_t		nDamage,
	ObjID_t		nAttackerID,
	BOOL		bCritical,
	SpellID_t	nSkillID,
	int32_t		iLogicCount
)
{

}

void	Character::OnEvent_DamageTarget(int32 nDamage, Character& rTar, SpellID_t nSkillID)
{

}

int32	Character::OnEvent_FiltrateEffect(UNIT_EFFECT& rEffect)
{
	return 0;
}

int32_t	Character::HealthIncrement
(
	int32_t		nIncrement,
	int32_t		iLogicCount,
	Character* pCharacter,
	BOOL		bCritical,
	BOOL		bDOT,
	BOOL		bBeatFly,
	BOOL		bPKRateCtr
)
{
	if (IsActiveObj())
	{
		if (nIncrement < 0)
		{
			RefixByInherence(nIncrement, pCharacter, bDOT, bPKRateCtr);
		}

		nIncrement = (0 == nIncrement ? -1 : nIncrement);
		SendHealAndDamageMSG(nIncrement, pCharacter, bCritical, iLogicCount, bBeatFly);

		OnIncementHp(nIncrement, pCharacter);

		OnDecementHP(nIncrement, bDOT, pCharacter);

		SendCharBaseDirectForHP();
		return nIncrement;
	}
	return -1;
}

void	Character::OnEvent_BeSkill(Character& rAttacker, int32 nBehaviorType)
{
	m_pAI_Character->OnEvent_BeSpell(&rAttacker, nBehaviorType);
}

void	Character::OnEvent_BeHit(Character& rAttacker)
{

}

void	Character::OnEvent_HitTarget(Character& rTarget)
{

}

void	Character::OnEvent_Hit(Character& rAttacker, int32 nBehaviorType)
{

}

void	Character::OnEvent_CriticalHitTarget(SpellID_t const nSkill, Character& rTarget)
{

}

void	Character::OnEvent_BeCriticalHit(SpellID_t const nSkill, Character& rAttacker)
{

}

void	Character::OnEvent_HealTarget(SpellID_t const nSkill, Character& rTarget, int32 nHealedHP)
{

}

void	Character::OnEvent_BeHeal(SpellID_t const nSkill, Character& rCaster, int32 nHealedHP)
{

}

void	Character::OnEvent_UseSkillSuccessfully(SpellInfo& rSkill)
{

}

void	Character::OnEvent_DepleteStrikePoints(int32 nStrikePoints)
{

}


int32			Character::Effect_DispelEffectInSpecificCollection
(
	int32	nCollectionID,
	int32	nDispelLevel,
	int32	nNeedDispel
)
{
	return 0;
}

UNIT_EFFECT* Character::Effect_GetFirstEffectOfSpecificEffectID(int32 nEffectID)
{
	return nullptr;
}

UNIT_EFFECT* Character::Effect_GetFirstEffectOfSpecificLogicID(int32 nLogicID)
{
	return nullptr;
}

UNIT_EFFECT* Character::Effect_GetFirstEffectOfSpecificMutexID(int32 nMutexID)
{
	return nullptr;
}

UNIT_EFFECT* Character::Effect_GetFirstEffectOfSpecificSkillID(int32 nSkillID)
{
	return nullptr;
}

UNIT_EFFECT* Character::Effect_GetFirstEffectInSpecificCollection(int32 nCollectionID)
{
	return nullptr;
}

int32_t	Character::Effect_GetEffectVisableType(EffectID_t nEffectID)
{
	const ImpactSEData_T* pSEData = DataManager::GetSingletonPtr()->getImapctSEData(nEffectID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pSEData)
	{
		if (pSEData->IsHaveEfect())
		{
			return IMPACT_BUFF_VISABLE_CAN;
		}
		else
		{
			return IMPACT_BUFF_VISABLE_CANNOT;
		}
	}

	return IMPACT_BUFF_VISABLE_INVALID;
}

void			Character::Effect_CleanAllEffectWhenPetDead(ObjID_t idPet)
{
	
}

BOOL			Character::Effect_IsCanReciveBallEffect(UNIT_EFFECT& rImp)
{
	return FALSE;
}

void	Character::RefixEffect(UNIT_EFFECT& rEffectNeedRedix)
{

}

BOOL	Character::Effect_RegisterEffect(UNIT_EFFECT& rImp)
{
	return Effect_PushToDelayTimeList(rImp);
}

BOOL	Character::Effect_PushToDelayTimeList(UNIT_EFFECT& oEffect)
{
	ID_t	iSkillID = oEffect.GetSkillID();
	Object* pObj = GetEffectCaster(*this, oEffect);
	uint32		iTime = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pObj)
	{
		if (IsObjCharacter(pObj->GetObjType()))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SpellTargetingAndDepletingParams& rParams =
				((Character*)pObj)->GetTargetingAndDepletingParams();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (rParams.GetHurtDelayTime() > 0)
			{
				iTime = rParams.GetHurtDelayTime();
			}

			rParams.SetHurtDelayTime(0);
		}
	}

	if (iTime < 50)
	{
		if (Effect_RegisterEffectImp(oEffect))
		{
			//Effect_SendEffectMsg(oEffect, iTime);
		}

		return TRUE;
	}

	oEffect.SetDelayTime(iTime + NowTime());

	if (MAX_DELAY_TIME_EFFECT_NUM <= m_DelayTimeEffectList.m_Count)
	{
		return FALSE;
	}

	m_DelayTimeEffectList.m_aEffects[m_DelayTimeEffectList.m_Count] = oEffect;
	++m_DelayTimeEffectList.m_Count;
	return TRUE;
}

void	Character::EffectDelayTimeHeartBeat()
{
	for (int32_t i = 0; i < m_DelayTimeEffectList.m_Count; ++i)
	{
		if (m_DelayTimeEffectList.m_aEffects[i].GetDelayTime() <= NowTime())
		{
			if (Effect_RegisterEffectImp(m_DelayTimeEffectList.m_aEffects[i]))
			{
				Effect_SendEffectMsg(m_DelayTimeEffectList.m_aEffects[i], 0);
			}

			m_DelayTimeEffectList.ReplaseArrayItem(i);
		}
	}
}

void	Character::Effect_OnEffectActived(UNIT_EFFECT& rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pLogic = GetEffectLogic(rImp);
	if (NULL == pLogic)
	{
		return;
	}

	if (TRUE == IsEffectOverTimed(rImp))
	{
		pLogic->MarkModifiedAttrDirty(rImp, *this);
		Effect_ActiveScript(rImp);
	}

	pLogic->OnEvent_Active(rImp, *this);

	if (GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		if (GetEffectStandFlag(rImp) == BEHAVIOR_TYPE_HOSTILITY)
		{
			if (GetCharacterLogic() == CHARACTER_LOGIC_USE_ABILITY)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Behavior_Player* pAI = (Behavior_Player*)GetAIObj();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				pAI->PushCmd_Idle();
			}
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nGoodEffect = GetSpellStandFlag(rImp.GetSkillID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (BEHAVIOR_TYPE_HOSTILITY == nGoodEffect)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object* pObj = GetEffectCaster(*this, rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL == pObj)
		{
			return;
		}

		if (IsObjCharacter(pObj->GetObjType()))
		{
			GetAIObj()->OnEvent_Damage(0, static_cast<Character*>(pObj));
		}
	}

	__UNGUARD__
}

BOOL	Character::Effect_RegisterEffectImp(UNIT_EFFECT& rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EffectLogic const* pLogic = GetEffectLogic(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pLogic)
	{
		return FALSE;
	}

	if (IsImmuneAbsForLater())
	{
		return FALSE;
	}

	if (TRUE == IsUnbreakable() && BEHAVIOR_TYPE_HOSTILITY == GetEffectStandFlag(rImp))
	{
		return FALSE;
	}

	if (!IsAlive())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object* pObj = GetSpecificObjInSameSceneByID(rImp.GetCasterObjID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pObj && IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character* pCaster = (Character*)pObj;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		OnEvent_BeSkill(*pCaster, GetEffectStandFlag(rImp));
	}

	if (TRUE == IsEffectOverTimed(rImp))
	{
		if (FALSE == Effect_ReplaceMutuallyExclusiveEffect(rImp))
		{
			Effect_AddNewEffect(rImp);
			return TRUE;
		}
	}
	else
	{
		Effect_OnEffectActived(rImp);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

BOOL	Character::Effect_ReplaceMutuallyExclusiveEffect(UNIT_EFFECT& rEffect)
{
	__GUARD__ _EFFECT_LIST & rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pCurrentImpactLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rCurrentImpact = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pCurrentImpactLogic = GetEffectLogic(rCurrentImpact);

		if (NULL == pCurrentImpactLogic)
		{
			Effect_OnEffectFadeOut(rCurrentImpact);
			continue;
		}
		else if (FALSE == rCurrentImpact.IsFadeOut() && TRUE == IsEffectOverTimed(rCurrentImpact))
		{
			if(
					(GetEffectMutexID(rCurrentImpact) == GetEffectMutexID(rEffect))
					&& (INVALID_ID != GetEffectMutexID(rCurrentImpact))
					)
			{
				if (TRUE == IsEffectsABMutexed(rEffect, rCurrentImpact))
				{
					if (TRUE == CanEffectAReplaceB(rEffect, rCurrentImpact))
					{
						rList.m_VisableType[i] = Effect_GetEffectVisableType(GetEffectID(rEffect));
						Effect_ReplaceEffect(rCurrentImpact, rEffect);
					}
					else
					{
					}

					return TRUE;
				}
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}
void	Character::Effect_ReplaceLastGoodEffect(UNIT_EFFECT& rEffect)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pCurrentImpactLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = rCount - 1; 0 <= i; ++i)
	{
		if (i >= MAX_IMPACT_NUM)
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rCurrentImpact = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pCurrentImpactLogic = GetEffectLogic(rCurrentImpact);
		if (NULL == pCurrentImpactLogic)
		{
			Effect_OnEffectFadeOut(rCurrentImpact);
			continue;
		}
		else if (FALSE == rCurrentImpact.IsFadeOut() && TRUE == IsEffectOverTimed(rCurrentImpact))
		{
			if
				(
					BEHAVIOR_TYPE_HOSTILITY != GetEffectStandFlag(rCurrentImpact)
					&& TRUE == CanEffectBeDispeled(rCurrentImpact)
					)
			{
				Effect_ReplaceEffect(rCurrentImpact, rEffect);
				return;
			}
		}
	}
}

BOOL	Character::Effect_AddNewEffect(UNIT_EFFECT& rEffect)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (rCount < MAX_IMPACT_NUM)
	{
		rList.m_VisableType[rCount] = Effect_GetEffectVisableType(GetEffectID(rEffect));
		Effect_AddSNSeed();
		rEffect.SetSN(Effect_GetSNSeed());

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rLast = rList.m_aImpacts[rCount];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rLast = rEffect;
		++rCount;
		Effect_OnEffectActived(rLast);
		SaveEffectToDB(rEffect, rCount - 1);
		return TRUE;
	}
	else
	{
		Effect_ReplaceLastGoodEffect(rEffect);
		return TRUE;
	}
}

void	Character::Effect_ReplaceEffect(UNIT_EFFECT& rDest, UNIT_EFFECT& rSrc)
{
	Effect_AddSNSeed();

	rSrc.SetSN(Effect_GetSNSeed());
	Effect_OnEffectFadeOut(rDest);

	Effect_AddSNSeed();
	rDest = rSrc;
	Effect_OnEffectActived(rDest);
}

void Character::Effect_OnDamages(int32* const pDamage, Character* const pAttacker, SpellID_t nSkillID)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);

		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut())
		{
			pLogic->OnEvent_Damages(rImp, *this, pAttacker, pDamage, nSkillID);
		}
	}
}

void	Character::Effect_OnDamage(int32& nDamage, Character* const pAttacker, SpellID_t nSkillID)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);

		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut())
		{
			if (FALSE == IsEffectFadeOutWhenUnitOnDamage(rImp))
			{
				pLogic->OnEvent_Damage(rImp, *this, pAttacker, nDamage, nSkillID);
			}
			else
			{
				Effect_OnEffectFadeOut(rImp);
			}
		}
	}
}

void	Character::Effect_OnFinalDamage(int32& nDamage, Character* const pAttacker, SpellID_t nSkillID)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);

		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut())
		{
			if (FALSE == IsEffectFadeOutWhenUnitOnDamage(rImp))
			{
				pLogic->OnEvent_FinalDamage(rImp, *this, pAttacker, nDamage, nSkillID);
			}
			else
			{
				Effect_OnEffectFadeOut(rImp);
			}
		}
	}
}

void	Character::Effect_RefixSkill(SpellInfo& rSkill)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);
		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut() && TRUE == IsEffectOverTimed(rImp))
		{
			pLogic->RefixSkill(rImp, rSkill);
		}
	}
}

BOOL	Character::Effect_GetIntAttrRefix(CharIntAttrRefixs::Index_T nIdx, int32& rIntAttrRefix)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);
		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut() && TRUE == IsEffectOverTimed(rImp))
		{
			pLogic->Get_Property_IntAttrRefix(rImp, *this, nIdx, rIntAttrRefix);
		}
	}

	return TRUE;
}

BOOL	Character::Effect_GetBoolAttrRefix(CharBoolAttrs::Index_T nIdx, BOOL& rBoolAttrRefix)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);

		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut() && TRUE == IsEffectOverTimed(rImp))
		{
			if (TRUE == pLogic->Get_Property_BoolAttrRefix(rImp, *this, nIdx, rBoolAttrRefix))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void	Character::Effect_OnDie(void)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (short i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pLogic = GetEffectLogic(rImp);
		if (NULL == pLogic)
		{
			Effect_OnEffectFadeOut(rImp);
			continue;
		}
		else if (FALSE == rImp.IsFadeOut() && TRUE == IsEffectOverTimed(rImp))
		{
			pLogic->OnEvent_Die(rImp, *this);
		}
	}
}


void	Character::Effect_SendEffectMsg(UNIT_EFFECT& rImp, Time_t iDelayTime)
{
	//if (FALSE == IsAlive()) return;

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//EffectLogic const* pLogic = NULL;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//pLogic = GetEffectLogic(rImp);
	//if (NULL == pLogic) return;

	///*~~~~~~~~~~~~~~~~~~~~~*/
	//GameMap* pMap = GetMap();
	///*~~~~~~~~~~~~~~~~~~~~~*/

	//if (NULL == pMap || FALSE == IsActiveObj()) return;

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//EffectID_t	nEffectID = GetEffectID(rImp);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if (INVALID_ID == nEffectID) return;

	//if (TRUE == IsEffectOverTimed(rImp))
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	int32	nBuffVisableType = Effect_GetEffectVisableType(nEffectID);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if (IMPACT_BUFF_VISABLE_INVALID == nBuffVisableType) return;

	//	if (Object::OBJECT_CLASS_PLAYER == GetObjType())
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		Messages::XCDetailBuff	Msg2Self;
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		Msg2Self.SetReceiverID(GetID());
	//		Msg2Self.SetSenderID(rImp.GetCasterObjID());
	//		Msg2Self.SetEnable(TRUE);
	//		Msg2Self.SetSkillID(rImp.GetSkillID());
	//		Msg2Self.SetSN(rImp.GetSN());
	//		Msg2Self.SetBuffID(nEffectID);
	//		Msg2Self.SetContinuance(rImp.GetContinuance());
	//		Msg2Self.SetDelayTime(iDelayTime);
	//		Msg2Self.SetSenderLogicCount(rImp.GetCasterLogicCount());

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		Connector* pGameConnector = ((Player*)this)->GetConnector();
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if (pGameConnector)
	//		{
	//			pGameConnector->SendPacket(&Msg2Self);
	//		}
	//	}
	//	else if (Object::OBJECT_CLASS_BUS == GetObjType())
	//	{
	//		Messages::XCDetailBuff	Msg2Self;
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		Msg2Self.SetReceiverID(GetID());
	//		Msg2Self.SetSenderID(rImp.GetCasterObjID());
	//		Msg2Self.SetEnable(TRUE);
	//		Msg2Self.SetSkillID(rImp.GetSkillID());
	//		Msg2Self.SetSN(rImp.GetSN());
	//		Msg2Self.SetBuffID(nEffectID);
	//		Msg2Self.SetContinuance(rImp.GetContinuance());
	//		Msg2Self.SetDelayTime(iDelayTime);
	//		Msg2Self.SetSenderLogicCount(rImp.GetCasterLogicCount());

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		Player* pPlayer = (Player*)g_pGUIDMgr->Get(((Bus*)this)->GetOwnerGUID());
	//		Connector* pGameConnector = ((Player*)pPlayer)->GetConnector();
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if (pGameConnector)
	//		{
	//			pGameConnector->SendPacket(&Msg2Self);
	//		}
	//	}

	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	Messages::XCCharBuff	Msg2Other;
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	Msg2Other.SetReceiverID(GetID());
	//	Msg2Other.SetSenderID(rImp.GetCasterObjID());
	//	Msg2Other.SetEnable(TRUE);
	//	Msg2Other.SetSN(rImp.GetSN());
	//	Msg2Other.SetBuffID(nEffectID);
	//	Msg2Other.SetSenderLogicCount(rImp.GetCasterLogicCount());
	//	Msg2Other.SetLastSN(Effect_GetSNSeed());

	//	if (IMPACT_BUFF_VISABLE_CAN == nBuffVisableType)
	//	{
	//		pMap->BroadCast(&Msg2Other, this, TRUE);
	//	}
	//	else if (IMPACT_BUFF_VISABLE_CANNOT == nBuffVisableType)
	//	{
	//		pMap->BroadCast(&Msg2Other, this, TRUE, TRUE);
	//	}
	//}
	//else
	//{
	//	if (g_ImpactDirDataMgr.GetInstanceByID(nEffectID))
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		XCCharDirectImpact	Msg2All;
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		Msg2All.SetReceiverID(GetID());
	//		Msg2All.SetImpactID(nEffectID);
	//		pMap->BroadCast(&Msg2All, this, TRUE);
	//	}
	//}
}

void	Character::Profession_OnDamage(int32 nDamage)
{

}

void	Character::AddDelayTimeSkillMissList(_SkillMissMSGDelayTime& val)
{

}

Object* Character::Spell_CreateObjSpecial(GLPos const& rPosition, int32 nDataID)
{
	return nullptr;
}

void	Character::RefixInherenceBalance(InherenceBalanceRefixValue& rInherenceBalance)
{

}

BOOL			Character::Effect_HaveEffectOfSpecificEffectID(int32 const nEffectID)
{
	return(NULL != Effect_GetFirstEffectOfSpecificEffectID(nEffectID));
}

BOOL			Character::Effect_HaveEffectOfSpecificLogicID(int32 const nLogicID)
{
	return(NULL != Effect_GetFirstEffectOfSpecificLogicID(nLogicID));
}

BOOL			Character::Effect_HaveEffectOfSpecificMutexID(int32 const nMutexID)
{
	return(NULL != Effect_GetFirstEffectOfSpecificMutexID(nMutexID));
}

BOOL			Character::Effect_HaveEffectOfSpecificSkillID(int32 const nSkillID)
{
	return(NULL != Effect_GetFirstEffectOfSpecificSkillID(nSkillID));
}

BOOL Character::Effect_HaveEffectInSpecificCollection(int32 const nCollectionID)
{
	return(NULL != Effect_GetFirstEffectInSpecificCollection(nCollectionID));
}

void Character::Effect_CancelEffectInSpecificCollection(int32 nCollectionID)
{
	_EFFECT_LIST& rList = Effect_GetEffectList();
	uchar& rImpactCount = rList.m_Count;
	EffectLogic const* pLogic = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 nIdx = 0; rImpactCount > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT& rImp = rList.m_aImpacts[nIdx];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (FALSE == rImp.IsFadeOut() && TRUE == CanEffectBeCanceled(rImp))
		{
			if (TRUE == IsEffectInCollection(rImp, nCollectionID))
			{
				Effect_OnEffectFadeOut(rImp);
			}
		}
	}
}


void Character::SendHealAndDamageMSG
(
	int32		nIncrement,
	Character* pCharacter,
	BOOL		bCritical,
	int32		iLogicCount,
	BOOL		bBeatFly
)
{
	SCDeltailOfHealsAndDamage* packet = new SCDeltailOfHealsAndDamage;
	int32			nValue = GetHP() + nIncrement;

	if (nValue <= 0)
	{
		packet->setDeathBlow();
	}
	if (bCritical)
	{
		packet->setCriticalHit();
	}

	packet->setHpModification(nIncrement);
	packet->setObjId(GetID());


	if (pCharacter)
	{
		packet->setSenderId(pCharacter->GetID());
		packet->setSenderLogicCount(iLogicCount);
	}


	//NetManager::GetSingletonPtr()->sendNetMessage(packet);
	
}

void	Character::OnIncementHp(int32 nIncrement, Character* pCharacter)
{
	if (nIncrement > 0)
	{
		int32 nValue = GetHP() + nIncrement;
		if (GetMaxHP() < nValue)
		{
			nValue = GetMaxHP();
		}

		/*~~~~~~~~~~~~~~~~~~~~~*/
		int32	nOldHP = GetHP();
		/*~~~~~~~~~~~~~~~~~~~~~*/

		SetHP(nValue);
		if (nOldHP <= 0 && GetHP() > 0)
		{
			if (this->GetObjType() != OBJECT_CLASS_PLAYER)
				OnEvent_Relive((pCharacter) ? (pCharacter->GetID()) : INVALID_ID);
		}
	}
}

void	Character::OnDecementHP(int32 nIncrement, BOOL bDOT, Character* pCharacter)
{
	if (nIncrement < 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetHP() + nIncrement;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		UpdataEquipDamagePoint(DURSPOIL_DEFENCE);

		if (!bDOT)
		{
			GetGlobalActionDelegator().DisturbCurrentAction(*this);
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Character* pAI = GetAIObj();
		int32		nOldHP = GetHP();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 > nValue)
		{
			nValue = 0;
		}

		SetHP(nValue);

		if (NULL != pAI && NULL != pCharacter)
		{
			pAI->OnEvent_Damage(-nIncrement, pCharacter);
		}

		if (nOldHP > 0 && GetHP() <= 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iTmpID = INVALID_ID;
			/*~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (NULL != pCharacter)
			{
				iTmpID = pCharacter->GetID();
			}

			OnEvent_Die(iTmpID);
		}
	}
}

void	Character::OnEvent_Die(ObjID_t idKiller)
{
	Effect_OnDie();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (GetScriptID() > 0)
	{
		ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
		(
			GetMap()->MapID(),
			GetScriptID(),
			"OnDie",
			GetMap()->MapID(),
			(int32)GetID(),
			(int32)idKiller
		);
	}

	if (FALSE == GetGlobalActionDelegator().CanDoNextAction(*this))
	{
		GetGlobalActionDelegator().InterruptCurrentAction(*this);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Character* pAI = GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pAI)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object* pKiller = GetMap()->GetObjManager()->GetObj(idKiller);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pAI->OnEvent_Die(pKiller);
	}
}

void	Character::OnEvent_Relive(ObjID_t idKiller)
{
	Behavior_Character* pAI = GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pAI)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object* pKiller = GetMap()->GetObjManager()->GetObj(idKiller);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pAI->OnEvent_Relive(pKiller);

		pAI->Relive(TRUE);
	}
}

int32_t Character::GetPercentHP()
{
	int64_t hp, maxhp;
	hp = (int64_t)GetHP();
	hp *= 100;
	maxhp = GetMaxHP();
	int32_t yHPPercent = maxhp > 0 ? ((uchar)Float2Int((hp + maxhp - 1) / maxhp)) : (0);

	if (0 >= yHPPercent)
	{
		yHPPercent = GetHP() > 0 ? 1 : 0;
	}

	return yHPPercent;
}