/*$T MapServer/Server/AI/Behavior_State.cpp GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "Behavior_Character.h"
#include "Behavior_Monster.h"
#include "Behavior_Player.h"
#include "Player.h"
#include "Behavior_Pet.h"
#include "Character.h"

#include "Behavior_State.h"
#include "skill/Skill_Manager.h"
#include "skill/Skill_Base.h"

SStateList	g_BHVStateList;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::BHV_Move(const Behavior_Character *pAI, int32 nHandleID, uint16 wNumTargetPos, const GLPos *paTargetPos)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		return pCharacter->BHV_Move(nHandleID, wNumTargetPos, paTargetPos);
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::UseSpell
(
	const Behavior_Character	*pAI,
	ObjID_t			idSkill,
	ObjID_t			idTarget,
	float			fTargetX,
	float			fTargetZ,
	int32			iHurtDelayTime,
	float			fDir /* = -1.f */,
	GUID_t			guidTarget
)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanUseSpell(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if(pCharacter == NULL)
	{
		return OR_NULL_POINTER;
	}
	if(pCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_OK;
	}

	if(pCharacter && pCharacter->CanUseSkillNow(idSkill))
	{
		/*~~~~~~~~~~~~~~~~*/
		GLPos	pos;
		/*~~~~~~~~~~~~~~~~*/

		pos.m_fX = fTargetX;
		pos.m_fZ = fTargetZ;
		return pCharacter->BHV_UseSkill(idSkill, idTarget, &pos, iHurtDelayTime, fDir, guidTarget);
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::BHV_UseSpell
(
	const Behavior_Character	*pAI,
	ObjID_t			idSkill,
	ObjID_t			idTarget,
	float			fTargetX,
	float			fTargetZ,
	int32			iHurtDelayTime,
	float			fDir,
	GUID_t			guidTarget
)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter && pCharacter->CanUseSkillNow(idSkill))
	{
		/*~~~~~~~~~~~~~~~~*/
		GLPos	pos;
		/*~~~~~~~~~~~~~~~~*/

		pos.m_fX = fTargetX;
		pos.m_fZ = fTargetZ;
		return pCharacter->BHV_UseSkill(idSkill, idTarget, &pos, iHurtDelayTime, fDir, guidTarget);
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::BHV_UseItem
(
	const Behavior_Character	*pAI,
	ID_t			nBagIndex,
	ObjID_t			nTargetObj,
	GLPos const		&posTarget,
	SHorseGuid const	&nTargetPetGUID,
	ID_t			nTargetItem
)
{
	

	return OR_OK;
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::Jump(const Behavior_Character *pAI)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanJump(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		return pCharacter->BHV_Jump();
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::Stall(const Behavior_Character *pAI)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanStall(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::Stop(const Behavior_Character *pAI)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanStop(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		return pCharacter->BHV_Stop();
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::Move
(
	const Behavior_Character	*pAI,
	int32			nHandleID,
	uint16			wNumTargetPos,
	const GLPos		*paTargetPos,
	int32			nStopLogicCount,
	const GLPos		*paCurPos,
	ObjID_t			nSenderID
)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanMove(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		return pCharacter->BHV_Move(nHandleID, wNumTargetPos, paTargetPos, nStopLogicCount, paCurPos, nSenderID);
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::UseItem
(
	const Behavior_Character	*pAI,
	ID_t			nBagIndex,
	ObjID_t			nTargetObj,
	GLPos const		&posTarget,
	SHorseGuid const	&guidTargetPet,
	ID_t			nTargetItem
)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanUseItem(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCharacter)
	{
		pCharacter->BHV_StopSkill();
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::UseAbility(const Behavior_Character *pAI)
{
	__GUARD__ if(!pAI)
	{
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oResult = CanUseAbility(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult)
	{
		return oResult;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCharacter)
	{
		return OR_NULL_POINTER;
	}

	oResult = CanUseAbility(pAI);
	if(ORT_SUCCEEDED(oResult)) return pCharacter->BHV_UseAbility();

	return oResult;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Character *BHVState::GetCharacter(const Behavior_Character *pAI) const
{
	if(pAI)
	{
		return pAI->GetCharacter();
	}

	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BHVState::CheckSpecialState(Behavior_Character *pAI)
{
	if(!pAI)
	{
		return false;
	}

	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BHVState::Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return false;
	}

	CheckSpecialState(pAI);

	State_Logic(pAI, uTime);

	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Sit_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Sit_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Terror_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Terror_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Idle_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Idle_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Dead_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Dead_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Combat_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Combat_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Flee_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Flee_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Patrol_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Patrol_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Gohome_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Gohome_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Service_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Service_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::Approach_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->Approach_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::TeamFollow_Logic(Behavior_Character *pAI, uint32 uTime)
{
	__GUARD__ if(!pAI)
	{
		return;
	}

	pAI->TeamFollow_Logic(uTime);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::OnEvent_BeSpell(Behavior_Character *pAI, Character *pCharacter, int32 nGoodEffect)
{
	if(pAI)
	{
		pAI->Event_OnBeSpell(pCharacter, nGoodEffect);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::OnEvent_BeHeal(Behavior_Character *pAI, Character *pCharacter, int32 nHeal)
{
	if(pAI)
	{
		pAI->Event_OnBeHeal(pCharacter, nHeal);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::OnEvent_Damage(Behavior_Character *pAI, int32 damage, Character *pAttacker)
{
	if(pAI)
	{
		pAI->Event_OnDamage(damage, pAttacker);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BHVState::OnEvent_Die(Behavior_Character *pAI, Object *pKiller)
{
	if(pAI)
	{
		pAI->ChangeState(ESTATE_DEAD);
		pAI->Event_OnDie(pKiller);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pCharacter = pAI->GetCharacter();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pCharacter)
		{
			pCharacter->BHV_Idle();
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BHVState::IsTransformState(const Behavior_Character *pAI) const
{
	if(!pAI)
	{
		return false;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		if(pCharacter->GetModelID() != pCharacter->Get_BaseProperty_ModelID())
		{
			return true;
		}
	}

	return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BHVState::IsTerrorState(const Behavior_Character *pAI) const
{
	if(!pAI)
	{
		return false;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		return false;
	}

	return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BHVState::IsMountState(const Behavior_Character *pAI) const
{
	if(!pAI)
	{
		return false;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = pAI->GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCharacter)
	{
		if(pCharacter->GetMountID() != INVALID_ID)
		{
			if(pCharacter->GetMountID() != pCharacter->GetBaseMountID())
			{
				return true;
			}
		}
	}

	return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT BHVState::CanUseAbility(const Behavior_Character *pAI) const
{
	if(pAI->GetCharacter()->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return OR_ABILITY_OWNER_ISNOT_HUMAN;
	}
	else
	{
	
		Player* pPlayer = ((Player*)pAI->GetCharacter());
		BaseSkill* pSkill = g_pSkillManager->GetAbility(pPlayer->GetAbilityOpera()->m_SkillID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pSkill)
		{
			return pSkill->CanUseSkill(pPlayer);
		}
		else
		{
			return OR_INVALID_ABILITY;
		}
		
	}

	return OR_DEFAULT_ERROR;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IdleBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Idle_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CombatBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Combat_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL DeadBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Dead_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ServiceBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Service_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ApproachBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Approach_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL FleeBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Flee_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PatrolBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Patrol_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT PatrolBHVState::CanStall(const Behavior_Character *pAI) const
{
	return OR_BUSY;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT PatrolBHVState::CanMove(const Behavior_Character *pAI) const
{
	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT PatrolBHVState::CanUseSpell(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT PatrolBHVState::CanUseAbility(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT PatrolBHVState::CanUseItem(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GohomeBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Gohome_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TeamFollowBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	TeamFollow_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TeamFollowBHVState::OnEvent_BeSpell(Behavior_Character *pAI, int32 nGoodEffect)
{
	pAI->ChangeState(ESTATE_IDLE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT TeamFollowBHVState::CanStall(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT TeamFollowBHVState::CanMove(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT TeamFollowBHVState::CanUseSpell(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT TeamFollowBHVState::CanUseAbility(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT TeamFollowBHVState::CanUseItem(const Behavior_Character *pAI) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = GetCharacter(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pChar && pChar->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		return OR_BUSY;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SitBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Sit_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TerrorBHVState::State_Logic(Behavior_Character *pAI, uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pAI);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Terror_Logic(pAI, uTime);
	return true;
	__UNGUARD__ return false;
}
