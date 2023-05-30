/*$T MapServer/Server/AI/Behavior_Horse.cpp GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "gameobject/Character.h"
#include "BaseTool.h"
#include "Horse.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "TabDefine.h"
#include "Behavior_Horse.h"
#include "gameobject/Behavior_Helper.h"
#include "gameobject/Pet.h"

#define HORSE_DELAY_TIME	(5000)
#define HORSE_MOVE_RANGE	(10)
#define HORSE_MAX_TRY_TIMES	(5)

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Behavior_Horse::Behavior_Horse(void)
{
	m_RandMoveTimer.Clear();
	m_ScanImpactOfOwnerTimer.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Behavior_Horse::~Behavior_Horse(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Horse::Init(Character *pCharacter)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Behavior_Character::Init(pCharacter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
		KCheckEx(FALSE, "[AI_Pet::Init]: NULL m_pCharacter Found!! check it now.");
		return FALSE;
	}

	m_nDelayTime = HORSE_DELAY_TIME;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Clear(void)
{
	Behavior_Character::Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Idle_Logic(uint32 uTime)
{
	__GUARD__ if(!m_RandMoveTimer.IsSetTimer())
	{
		m_RandMoveTimer.BeginTimer(HORSE_DELAY_TIME + rand() % HORSE_DELAY_TIME, uTime);
	}

	if(m_RandMoveTimer.CountingTimer(uTime))
	{
		ToRandMove();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Combat_Logic(uint32 uTime)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Dead_Logic(uint32 uTime)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::ChangeMoveMode()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Horse *pHorse = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pHorse)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pOwner = pHorse->GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pOwner)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistSqr = CalcDistSqrOfToOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSqr > HORSE_REFOLLOW_DISTSQR_C)
	{
		if(pHorse->CanMove())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			float		fDir = pOwner->GetDir() - __PI / 2;
			float		fX = pOwner->GetGLPos()->m_fX - (-(2 * sin(fDir)));
			float		fZ = pOwner->GetGLPos()->m_fZ - (2 * cos(fDir));
			GLPos	pos;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pos.m_fX = fX;
			pos.m_fZ = fZ;

			pHorse->GetMap()->GetMapInfo()->VerifyPos(&pos);
			pHorse->Teleport(&pos);
			pHorse->SetMoveMode(MOVE_MODE_WALK);
			return;
		}
	}
	else if(fDistSqr > HORSE_REFOLLOW_DISTSQR_B)
	{
		pHorse->SetMoveMode(MOVE_MODE_SPRINT);
	}
	else if(fDistSqr > HORSE_REFOLLOW_DISTSQR_A)
	{
		if(pHorse->GetMoveMode() != MOVE_MODE_SPRINT) pHorse->SetMoveMode(MOVE_MODE_RUN);
	}
	else
	{
		if(pHorse->GetMoveMode() != MOVE_MODE_WALK) pHorse->SetMoveMode(MOVE_MODE_HOBBLE);
	}

	if(!m_pCharacter->IsMoving() && fDistSqr > 4.1f) Go_Baby(pOwner->GetGLPos());

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Behavior_Horse::CalcDistSqrOfToOwner(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Horse *pHorse = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pHorse)
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
void Behavior_Horse::Event_OnDie(Object *pKiller)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Go_Baby(const GLPos *paTargetPos)
{
	__GUARD__ if(!paTargetPos)
	{
		KCheck(NULL && "AI_Pet::Baby_Go...paTargetPos=NULL...");
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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float		fDir = pOwner->GetDir() - __HALF_PI;
	float		fX = paTargetPos->m_fX + (2 * MathSinCos::Sin(fDir));
	float		fZ = paTargetPos->m_fZ + (2 * MathSinCos::Cos(fDir));
	GLPos	pos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pos.m_fX = fX;
	pos.m_fZ = fZ;

	m_pCharacter->GetMap()->GetMapInfo()->VerifyPos(&pos);
	if(m_pCharacter->GetMap()->GetMapInfo()->IsCanGo(pos))
	{
		BHV_Move(&pos);
	}
	else
	{
		BHV_Move(paTargetPos);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Attack_Baby(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::Relive(BOOL bSpellRelive)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	ChangeState(ESTATE_IDLE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::After_Die()
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Horse::PushCommand_UseSpell
(
	ObjID_t idSpell,
	ObjID_t idTarget,
	float	fTargetX,
	float	fTargetZ,
	float	fDir,
	GUID_t	guidTarget
)
{
	__GUARD__ return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Horse::ProcessSpellInCache(BOOL IsAttackState /* TRUE */ )
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Horse::ToRandMove()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GLPos	Tar;
	BOOL			FindPos = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < HORSE_MAX_TRY_TIMES; i++)
	{
		Tar.m_fX = GetCharacter()->GetRespawnPos()->m_fX +
			rand() %
			HORSE_MOVE_RANGE -
			rand() %
			HORSE_MOVE_RANGE;
		Tar.m_fZ = GetCharacter()->GetRespawnPos()->m_fZ +
			rand() %
			HORSE_MOVE_RANGE -
			rand() %
			HORSE_MOVE_RANGE;
		GetCharacter()->GetMap()->GetMapInfo()->VerifyPos(&Tar);
		if(GetCharacter()->GetMap()->GetMapInfo()->IsCanGo(Tar))
		{
			FindPos = TRUE;
			break;
		}
	}

	if(FindPos == FALSE) return;
	if(BHV_Move(&Tar) == FALSE) return;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Horse::IsCombatBeOver()
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}
