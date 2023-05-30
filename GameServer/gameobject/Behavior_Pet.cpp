#include "stdafx.h"
#include "Character.h"
#include "BaseTool.h"
#include "Pet.h"
#include "Map.h"
#include "TabDefine.h"
#include "Behavior_Pet.h"
#include "XCPlayerRelive.h"
#include "XCManipulatePetRet.h"
#include "XCOperateResult.h"
#include "Behavior_Helper.h"
#include "Setting.h"

#define DELAY_TIME		(5000)
#define PET_MOVE_RANGE		(5)
#define MAX_TRY_TIMES		(5)
#define PET_RANDOM_MIN_DISTSQR	(1)
#define PET_MOVE_LIMIT_TIME	(200)
#define PET_MOVE_LIMIT_DISTANCE	(1)

float	PET_REFOLLOW_DISTSQR_B = 400;
float	PET_REFOLLOW_DISTSQR_C = 625;
int32	PET_BEGIN_MOVE_RANDOM = 5;
int32	PET_RANDOM_MOVE_TO_A_PLACE = 70;
float	PET_STAND_DISTANCE_TO_ONWER_MIN = 9.0f;
float	PET_STAND_DISTANCE_TO_ONWER_MAX = 36.0f;
float	PET_ATTACK_DISTANCE = 400;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Behavior_Pet::Behavior_Pet(void)
{
	m_RandMoveTimer.Clear();
	m_ScanImpactOfOwnerTimer.Clear();
	m_bCallupFlag = TRUE;
	m_bForceIdle = FALSE;
	m_bForceKill = FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Behavior_Pet::~Behavior_Pet(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Pet::Init(Character *pCharacter)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bForceIdle = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_bForceKill = FALSE;
	PET_REFOLLOW_DISTSQR_B = (float) g_Config.m_ConfigInfo.m_PetReFollowDistanceB * g_Config.m_ConfigInfo.m_PetReFollowDistanceB;
	PET_REFOLLOW_DISTSQR_C = (float) g_Config.m_ConfigInfo.m_PetReFollowDistanceC * g_Config.m_ConfigInfo.m_PetReFollowDistanceC;
	PET_STAND_DISTANCE_TO_ONWER_MIN = (float) g_Config.m_ConfigInfo.m_PetStandDistanceToOnwerMIN * g_Config.m_ConfigInfo.m_PetStandDistanceToOnwerMIN;
	PET_STAND_DISTANCE_TO_ONWER_MAX = (float) g_Config.m_ConfigInfo.m_PetStandDistanceToOnwerMAX * g_Config.m_ConfigInfo.m_PetStandDistanceToOnwerMAX;
	PET_BEGIN_MOVE_RANDOM = g_Config.m_ConfigInfo.m_PetBeginMoveRandom;
	PET_RANDOM_MOVE_TO_A_PLACE = g_Config.m_ConfigInfo.m_PetMoveToAPlaceRandom;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bResult = Behavior_Character::Init(pCharacter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult)
	{
		return FALSE;
	}

	m_RandMoveTimer.Clear();
	m_ScanImpactOfOwnerTimer.Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Pet	*pPet = (Pet *) m_pCharacter;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == m_pCharacter)
	{
		KCheckEx(FALSE, "[Behavior_Pet::Init]: NULL m_pCharacter Found!! check it now.");
		return FALSE;
	}

	m_nDelayTime = DELAY_TIME;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Clear(void)
{
	Behavior_Character::Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Idle_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = (Pet *) GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pPet->SetTargetID(INVALID_ID);

	if(pPet->GetOwnerID() == INVALID_ID)
	{
		if(!m_RandMoveTimer.IsSetTimer())
		{
			m_RandMoveTimer.BeginTimer(DELAY_TIME + rand() % DELAY_TIME, uTime);
		}

		if(m_RandMoveTimer.CountingTimer(uTime))
		{
			ToRandMove();
		}
	}
	else
	{
		if(m_nDelayTime > 0)
		{
			m_nDelayTime -= m_pCharacter->GetLogicTime();
		}
		else
		{
			if(m_pCharacter && !m_pCharacter->IsMoving())
			{
				ProcessSpellInCache(FALSE);
			}
		}

		ChangeMoveMode();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Combat_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = (Pet *) m_pCharacter;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == m_pCharacter)
	{
		KCheckEx(FALSE, "[Behavior_Pet::Logic_Attack]: NULL m_pCharacter Found!! check it now.");
		return;
	}

	if(IsCombatBeOver())
	{
		ChangeState(ESTATE_IDLE);
		pPet->SetTargetID(INVALID_ID);
		return;
	}

	if(FALSE == m_pCharacter->CanUseSkillNow())
	{
		return;
	}

	ProcessSpellInCache();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Dead_Logic(uint32 uTime)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::ChangeMoveMode()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pOwner = pPet->GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pOwner)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Pet	*pMe = (Pet *) GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMe)
	{
		return;
	}

	if(!pMe->IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistSqr = CalcDistSqrOfToOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSqr > PET_REFOLLOW_DISTSQR_C)
	{
		if(!pPet->CanMove())
		{
			if(pOwner->GetObjType() == Object::OBJECT_CLASS_PLAYER)
			{
				((Player *) pOwner)->ReCallPet(pMe->GetIndexInOnwer());
			}

			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float		fDir = pOwner->GetDir() - __PI / 2;
		float		fX = pOwner->GetGLPos()->m_fX - (-(2 * sin(fDir)));
		float		fZ = pOwner->GetGLPos()->m_fZ - (2 * cos(fDir));
		GLPos	pos;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pos.m_fX = fX;
		pos.m_fZ = fZ;

		pPet->GetMap()->GetMapInfo()->VerifyPos(&pos);
		pPet->Teleport(&pos);
		pPet->SetMoveMode(MOVE_MODE_RUN);
		Baby_Go(pOwner->GetGLPos());
		return;
	}
	else if(fDistSqr > PET_REFOLLOW_DISTSQR_B)
	{
		pPet->SetMoveMode(MOVE_MODE_RUN);
	}
	else if(PET_STAND_DISTANCE_TO_ONWER_MAX > fDistSqr)
	{
		pPet->SetMoveMode(MOVE_MODE_WALK);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBeginMoveRandom = rand() % 100;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSqr < PET_STAND_DISTANCE_TO_ONWER_MAX)
	{
		if(PET_BEGIN_MOVE_RANDOM > nBeginMoveRandom)
		{
			pPet->SetFollowMode(FALSE);
			ToRandMove();
		}
	}
	else
	{
		pPet->SetFollowMode(TRUE);
		Baby_Go(pOwner->GetGLPos());
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Behavior_Pet::CalcDistSqrOfToOwner(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pOwner = GetCharacter()->GetOwner();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pOwner)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			float	fDeltaX = pOwner->GetGLPos()->m_fX - m_pCharacter->GetGLPos()->m_fX;
			float	fDeltaZ = pOwner->GetGLPos()->m_fZ - m_pCharacter->GetGLPos()->m_fZ;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			return(fDeltaX * fDeltaX + fDeltaZ * fDeltaZ);
		}
	}

	return 0.f;
	__UNGUARD__ return 0.f;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Event_OnDie(Object *pKiller)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Baby_Go(const GLPos *paTargetPos)
{
	__GUARD__ if(!paTargetPos)
	{
		KCheck(NULL && "Behavior_Pet::Baby_Go...paTargetPos=NULL...");
		return;
	}

	if(!m_pCharacter)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pOwner = GetCharacter()->GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pOwner)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BHVState	*pState = GetBehavior_State();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pState != NULL)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	fDistSqr = CalcDistSqrOfToOwner();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pState->GetStateID() == ESTATE_COMBAT && fDistSqr < PET_REFOLLOW_DISTSQR_B)
		{
			return;
		}
	}

	if(m_bCallupFlag)
	{
		if(OR_OK != BHV_Move(paTargetPos))
		{
			m_pCharacter->DirectMoveTo(paTargetPos);
		}

		m_bCallupFlag = FALSE;
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	pos;
	Pet		*pPet = static_cast<Pet *>(GetCharacter());
	int32		iIndex = pPet->GetIndexInOnwer();
	float		fDistanceRefix = pOwner->GetMap()->GetRand100() * 0.02f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GetStandPos(pOwner, iIndex, paTargetPos, fDistanceRefix, pos);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	oTempPos = *paTargetPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pCharacter->GetMap()->GetMapInfo()->VerifyPos(&pos);
	m_pCharacter->GetMap()->GetMapInfo()->VerifyPos(&oTempPos);

	/*~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT result = OR_OK;
	/*~~~~~~~~~~~~~~~~~~~*/

	if(m_pCharacter->GetMap()->GetMapInfo()->IsCanGo(pos))
	{
		result = BHV_Move(&pos);
	}
	else
	{
		result = BHV_Move(&oTempPos);
	}

	if(OR_OK != result)
	{
		m_pCharacter->DirectMoveTo(&oTempPos);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::BabyToAttack(void)
{
	__GUARD__ if(m_bForceIdle)
	{
		return;
	}

	ChangeState(ESTATE_COMBAT);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::Relive(BOOL bSkillRelive)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::After_Die()
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Pet::PushCommand_UseSpell
(
	ObjID_t idSkill,
	ObjID_t idTarget,
	float	fTargetX,
	float	fTargetZ,
	float	fDir,
	GUID_t	guidTarget
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		KCheck(NULL && "Behavior_Pet::PushCommand_UseSkill...pPet=NULL...");
		return OR_NULL_POINTER;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SLogicSpell_Param	SkillParam;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SkillParam.idSpell = idSkill;
	SkillParam.idTarget = idTarget;
	SkillParam.TargetPos = GLPos(fTargetX, fTargetZ);
	SkillParam.fDir = fDir;
	SkillParam.guidTarget = guidTarget;

	SetSpellParamCache(SkillParam);

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Pet::ProcessSpellInCache(BOOL IsAttackState /* TRUE */ )
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		KCheck(NULL && "Behavior_Pet::ProcessSkillInCache...pPet=NULL...");
		return FALSE;
	}

	if(FALSE == pPet->IsActiveObj())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pCreator = pPet->GetCreator();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCreator)
	{
		return FALSE;
	}

	if(FALSE == pPet->CanUseSkillNow())
	{
		return FALSE;
	}

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for(i = 0; i < MONSTER_PET_MAX_SKILL; ++i)
	{
		if(INVALID_ID == pPet->m_aCacheOfSkill[i])
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bCooldowned = pPet->IsSpellCooldowned(pPet->m_aCacheOfSkill[i]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!bCooldowned)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const SpellTemplateData *pSkillData_T = g_SpellTemplateDataMgr.GetInstanceByID(pPet->m_aCacheOfSkill[i]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!pSkillData_T)
		{
			KCheck(NULL && "Behavior_Pet::ProcessSkillInCache...pSkillData_T=NULL...");
			return FALSE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ID_t	OperateMode = pSkillData_T->GetOperateModeForPetSkill();
		ID_t	TypeOfSkill = pSkillData_T->GetTypeOfPetSkill();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!IsAttackState)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ID_t	RateOfSkill = pSkillData_T->GetPetRateOfSkill();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		RateOfSkill == -1 ? RateOfSkill = 100 : NULL;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nUseSkillRate = RateOfSkill;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(rand() % 100 > nUseSkillRate)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pTarObj = m_pCharacter->GetMap()->GetObjManager()->GetObj(pPet->GetTargetID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pTarObj == NULL || !((Character *) pTarObj)->IsAlive())
		{
			pPet->SetTargetID(INVALID_ID);
			ChangeState(ESTATE_IDLE);

			return FALSE;
		}

		int32	iHurtDelayTime = GetSpellHurtDelayTime(pPet->m_aCacheOfSkill[i]);

		BOOL NeedCheckDist = TRUE;
		if (TARGET_SELF == pSkillData_T->GetTargetingLogic())
		{
			NeedCheckDist = FALSE;
		}

		float	fDist = KLSqrt(pPet->GetGLPos(), pTarObj->GetGLPos());

		if(NeedCheckDist && (fDist > pSkillData_T->GetOptimalRangeMax() || fDist < pSkillData_T->GetOptimalRangeMin()))
		{
			if (0 == i)
			{
				const GLPos* curPos = pTarObj->GetGLPos();
				uint32 nowTime = GET_TIME().TickCount();

				if ( ( nowTime - pPet->GetMoveIntervalTimer() > PET_MOVE_LIMIT_TIME )
					|| KLSqrt(pPet->GetTargetOldPos(),curPos)  > PET_MOVE_LIMIT_DISTANCE)
				{

					ToApproachTar(pTarObj, pPet->m_aCacheOfSkill[i]);

					pPet->SetMoveIntervalTimer(nowTime);
					pPet->SetTargetOldPos(curPos);
				}
			}
		}
		else
		{
			BHV_StopMove();
			BHV_UseSpell
				(
				pPet->m_aCacheOfSkill[i],
				pTarObj->GetID(),
				pTarObj->GetGLPos()->m_fX,
				pTarObj->GetGLPos()->m_fZ,
				iHurtDelayTime
				);
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL Behavior_Pet::ToApproachTar(Object	*pTarObj, ObjID_t idSpell)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet *pPet = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		KCheck(NULL && "Behavior_Pet::ToApproachTar...pPet=NULL...");
		return OR_NULL_POINTER;
	}

	if(!pTarObj)
	{
		KCheck(NULL && "Behavior_Pet::ToApproachTar...pTarObj = NULL...");
		return OR_NULL_POINTER;
	}
	
	pPet->SetMoveMode(MOVE_MODE_RUN);
	
	
	/*~~~~~~~~~~~~~~~~~~~~*/
	GLPos	Tar;
	OPT_RESULT		oResult;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == GetBestPos(Tar, pTarObj, idSpell))
	{
		oResult = BHV_Move(&Tar);
	}
	else
	{
		oResult = BHV_Move(pTarObj->GetGLPos());
	}

	if(OR_OK != oResult && OR_LIMIT_MOVE != oResult)
	{
		pPet->DirectMoveTo(pTarObj->GetGLPos());
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL Behavior_Pet::GetBestPos(GLPos &Tar, Object *pTarObj, ObjID_t idSpell)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet *pPet = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		KCheck(NULL && "Behavior_Pet::GetBestPos...pPet=NULL...");
		return OR_NULL_POINTER;
	}

	if(!pTarObj)
	{
		KCheck(NULL && "Behavior_Pet::GetBestPos...pTarObj = NULL...");
		return OR_NULL_POINTER;
	}

	if(TRUE == pPet->IsLimitMove())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float			fMaxRange = 0.f;
	float			fMinRange = 0.f;
	SpellTemplateData const *pSkillTemplate = g_SpellTemplateDataMgr.GetInstanceByID(idSpell);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pSkillTemplate)
	{
		fMaxRange = pSkillTemplate->GetOptimalRangeMax();
		fMinRange = pSkillTemplate->GetOptimalRangeMin();
	}
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	vX = pTarObj->GetGLPos()->m_fX - pPet->GetGLPos()->m_fX;
		float	vZ = pTarObj->GetGLPos()->m_fZ - pPet->GetGLPos()->m_fZ;
		float	fDist = KLSqrt(pPet->GetGLPos(), pTarObj->GetGLPos());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(fDist < BHV_ZERO_VALUE)
		{
			return FALSE;
		}

		if(fDist >= fMinRange && fDist <= fMaxRange)
		{
			return FALSE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	fAttackRange = fMinRange < fMaxRange * 0.6f ? fMaxRange * 0.6f : fMinRange;
		float	fCos = vX / fDist;
		float	fSin = vZ / fDist;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Tar.m_fX = pPet->GetGLPos()->m_fX + fCos * (fDist - fAttackRange);
		Tar.m_fZ = pPet->GetGLPos()->m_fZ + fSin * (fDist - fAttackRange);
	}

	pPet->GetMap()->GetMapInfo()->VerifyPos(&Tar);
	if(pPet->GetMap()->GetMapInfo()->IsCanGo(Tar))
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::ToRandMove()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GLPos	Tar;
	BOOL			FindPos = FALSE;
	Map			*pMap = GetCharacter()->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	for(int32 i = 0; i < MAX_TRY_TIMES; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	nRandomX = (float) (rand() % PET_MOVE_RANGE - rand() % PET_MOVE_RANGE);
		float	nRandomZ = (float) (rand() % PET_MOVE_RANGE - rand() % PET_MOVE_RANGE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Tar.m_fX = GetCharacter()->GetRespawnPos()->m_fX + nRandomX;
		Tar.m_fZ = GetCharacter()->GetRespawnPos()->m_fZ + nRandomZ;
		pMap->GetMapInfo()->VerifyPos(&Tar);
		if(pMap->GetMapInfo()->IsCanGo(Tar))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			float		nDistSQR = nRandomX * nRandomX + nRandomZ * nRandomZ;
			Character	*pOwner = GetCharacter()->GetOwner();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pOwner)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				float	fDeltaX = pOwner->GetGLPos()->m_fX - Tar.m_fX;
				float	fDeltaZ = pOwner->GetGLPos()->m_fZ - Tar.m_fZ;
				float	fDistSqr = fDeltaX * fDeltaX + fDeltaZ * fDeltaZ;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if
				(
					fDistSqr > PET_STAND_DISTANCE_TO_ONWER_MAX
				||	fDistSqr < PET_STAND_DISTANCE_TO_ONWER_MIN
				)
				{
					continue;
				}
			}

			if(nDistSQR > PET_RANDOM_MIN_DISTSQR)
			{
				FindPos = TRUE;
				break;
			}
		}
	}

	if(FindPos == FALSE) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pOwner = GetCharacter()->GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pOwner)
	{
		BHV_Move(&Tar);
	}
	else
	{
		BHV_Move(&Tar);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Pet::IsCombatBeOver()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = (Pet *) m_pCharacter;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		KCheck(NULL && "Behavior_Pet::IsCombatBeOver...pPet=NULL...");
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pCreator = pPet->GetCreator();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCreator)
	{
		return TRUE;
	}

	if(pCreator->GetStealthLevel() > 0)
	{
		return TRUE;
	}

	if(INVALID_ID == pPet->GetTargetID())
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = pPet->GetMap()->GetObjManager()->GetObj(pPet->GetTargetID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return TRUE;
	}

	if(!((Character *) pObj)->IsAlive())
	{
		return TRUE;
	}

	if(IsObjCharacter(pObj->GetObjType()) != TRUE)
	{
		return TRUE;
	}

	if(((Character *) pObj)->IsCanViewMe(pCreator) == FALSE)
	{
		return TRUE;
	}

	if(Object::OBJECT_CLASS_PLAYER == pObj->GetObjType())
	{
		if(((Player *) pObj)->IsInBus())
		{
			if(((Player *) pObj)->GetGotOnFlag())
			{
				return TRUE;
			}
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDeltaX = pObj->GetGLPos()->m_fX - pPet->GetGLPos()->m_fX;
	float	fDeltaZ = pObj->GetGLPos()->m_fZ - pPet->GetGLPos()->m_fZ;
	float	fDistSqr = fDeltaX * fDeltaX + fDeltaZ * fDeltaZ;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSqr > PET_ATTACK_DISTANCE)
	{
		return TRUE;
	}

	fDeltaX = pCreator->GetGLPos()->m_fX - pPet->GetGLPos()->m_fX;
	fDeltaZ = pCreator->GetGLPos()->m_fZ - pPet->GetGLPos()->m_fZ;
	fDistSqr = fDeltaX * fDeltaX + fDeltaZ * fDeltaZ;

	if(fDistSqr > PET_REFOLLOW_DISTSQR_B)
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::GetStandPos
(
	Character	*pChar,
	int32		iIndex,
	const GLPos *paTargetPos,
	float		fDistanceRefix,
	GLPos	&oOutPos
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fCharDir = pChar->GetDir_i();
	float		fTmp = (float) MAX_MONSTER_PET_TAKE;
	float		fDir = fCharDir - __PI * iIndex / fTmp;
	float		fDisMin = sqrtf(PET_STAND_DISTANCE_TO_ONWER_MIN) + 0.5f;
	float		fX = (fDisMin * MathSinCos::Sin(fDir));
	float		fZ = (fDisMin * MathSinCos::Cos(fDir));
	float		fRefixX = GetGoodRefix(fX, fDistanceRefix);
	float		fRefixZ = GetGoodRefix(fZ, fDistanceRefix);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fX += paTargetPos->m_fX + fRefixX;
	fZ += paTargetPos->m_fZ + fRefixZ;
	oOutPos.m_fX = fX;
	oOutPos.m_fZ = fZ;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Behavior_Pet::GetGoodRefix(float iBase, float iRefix)
{
	__GUARD__ if(iBase >= 0)
	{
		return iRefix;
	}

	return -iRefix;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Pet::ForceChangeState(_PET_CTRL_STATE eState)
{
	__GUARD__ if(PCS_KILL_TARGET == eState)
	{
		m_bForceKill = TRUE;
		m_bForceIdle = FALSE;
	}
	else if(PCS_IDLE == eState)
	{
		m_bForceIdle = TRUE;
		m_bForceKill = FALSE;
		GetCharacter()->SetTargetID(INVALID_ID);
		ChangeState(ESTATE_IDLE);
	}

	__UNGUARD__
}
