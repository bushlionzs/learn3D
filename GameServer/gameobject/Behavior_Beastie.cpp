/*$T MapServer/Server/AI/Behavior_Beastie.cpp GC 1.140 10/10/07 10:07:18 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Character.h"
#include "BaseTool.h"
#include "map/game_map.h"
#include "Behavior_Helper.h"
#include "Behavior_Beastie.h"
#include "Beastie.h"
#include "map/game_map.h"
#include "map/map_info.h"

#define BEASTIE_MOVE_RANGE		(5)
#define BEASTIE_MAX_TRY_TIMES		(5)
#define BEASTIE_DELAY_TIME		(5000)
#define BEASTIE_IDLE_DELAY_TIME		(2000)
#define BEASTIE_RANDOM_MIN_DISTSQR	(1)

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Behavior_Beastie::Behavior_Beastie(void)
{
	m_RandMoveTimer.Clear();
	m_IdleTimer.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Behavior_Beastie::~Behavior_Beastie(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::Reset()
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Beastie::Init(Character *pCharacter)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Behavior_Character::Init(pCharacter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult)
	{
		return FALSE;
	}

	m_RandMoveTimer.Clear();
	m_IdleTimer.Clear();

	if(NULL == m_pCharacter)
	{
		KCheckEx(FALSE, "[AI_Pet::Init]: NULL m_pCharacter Found!! check it now.");
		return FALSE;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::Clear(void)
{
	Behavior_Character::Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::Relive(BOOL bSkillRelive)
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
OPT_RESULT Behavior_Beastie::PushCommand_UseSpell
(
	ObjID_t idSkill,
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
void Behavior_Beastie::Event_OnDie(Object *pKiller)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::Idle_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Beastie	*pBeastie = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pBeastie);
	if(Beastie::BEASTIE_IDLE == pBeastie->GetBeastieType())
	{
		return;
	}
	else if(Beastie::BEASTIE_MOVE == pBeastie->GetBeastieType())
	{
		if(!m_RandMoveTimer.IsSetTimer())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	time = BEASTIE_DELAY_TIME + rand() % BEASTIE_DELAY_TIME;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			m_RandMoveTimer.BeginTimer(time, uTime);
			m_IdleTimer.BeginTimer
				(
					time + BEASTIE_IDLE_DELAY_TIME + rand() % BEASTIE_IDLE_DELAY_TIME,
					uTime
				);
		}

		if(m_RandMoveTimer.CountingTimer(uTime))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	time = BEASTIE_DELAY_TIME + rand() % BEASTIE_DELAY_TIME;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!GetCharacter()->IsMoving())
			{
				ToRandMove();
			}

			return;
		}

		if(m_IdleTimer.CountingTimer(uTime))
		{
			BHV_Stop();
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::Dead_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Beastie	*pBeastie = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pBeastie);
	pBeastie->Enter_Respawn();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::Combat_Logic(uint32 uTime)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Beastie::ToRandMove()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GLPos	Tar;
	BOOL			FindPos = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < BEASTIE_MAX_TRY_TIMES; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	nRandomX = (float) (rand() % BEASTIE_MOVE_RANGE - rand() % BEASTIE_MOVE_RANGE);
		float	nRandomZ = (float) (rand() % BEASTIE_MOVE_RANGE - rand() % BEASTIE_MOVE_RANGE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Tar.m_fX = GetCharacter()->GetRespawnPos()->m_fX + nRandomX;
		Tar.m_fZ = GetCharacter()->GetRespawnPos()->m_fZ + nRandomZ;
		GetCharacter()->GetMap()->GetMapInfo()->VerifyPos(&Tar);
		if(GetCharacter()->GetMap()->GetMapInfo()->IsCanGo(Tar))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			float	nDistSQR = nRandomX * nRandomX + nRandomZ * nRandomZ;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nDistSQR > BEASTIE_RANDOM_MIN_DISTSQR)
			{
				FindPos = TRUE;
				break;
			}
		}
	}

	if(FindPos == FALSE) return;
	if(BHV_Move(&Tar) == FALSE) return;

	__UNGUARD__
}
