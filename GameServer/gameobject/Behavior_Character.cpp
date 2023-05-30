#include "stdafx.h"
#include "map/game_map.h"
#include "Character.h"
#include "TabDefine.h"
#include "map/server_map_path.h"
#include "Behavior_Character.h"
#include "map/map_info.h"

#define RANDOM_TIME	(2000)
#define RANDOM_DIST	(15)

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Behavior_Character::Behavior_Character(void)
{
	m_pCharacter = NULL;
	m_currUseSpellID = INVALID_ID;
	m_nIntervalTime = RANDOM_TIME;
	m_pBHVState = g_BHVStateList.InstanceState(ESTATE_IDLE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Behavior_Character::~Behavior_Character(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Character::Init(Character *pCharacter)
{
	m_pCharacter = pCharacter;

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_Jump(void)
{
	__GUARD__ return m_pBHVState->Jump(this);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_Stop(void)
{
	__GUARD__ return m_pBHVState->Stop(this);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_Stall(void)
{
	__GUARD__ return m_pBHVState->Stall(this);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_UseSkill(void)
{
	__GUARD__ return m_pBHVState->UseAbility(this);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_Move(const GLPos *pTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCharacter)
	{
		KCheck(NULL && "Behavior_Character::MoveTo...pCharacter = NULL...");
		return OR_NULL_POINTER;
	}

	if(TRUE == pCharacter->IsLimitMove())
	{
		return OR_LIMIT_MOVE;
	}

	if(NULL == pTar)
	{
		return OR_INVALID_TARGET_POS;
	}

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetMapInfo());
	KCheck(pCharacter->GetMap()->GetMapInfo()->GetPathFinder());

	Event_OnMove(pTar);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int		numNode = 0;
	const GLPos *pCur = pCharacter->GetGLPos();
	GLPos	posNode[MAX_CHAR_PATH_NODE_NUMBER];
	GLPos	posCur = *pCur;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pCharacter->GetMap()->GetMapInfo()->VerifyPos (const_cast<GLPos *>(pTar));
	if(FALSE == pCharacter->GetMap()->GetMapInfo()->IsCanGo(*pTar))
	{
		return OR_IMPASSABLE_ZONE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pCharacter->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap->GetMapInfo()->GetPathFinder()->FindPath(&posCur, const_cast<GLPos *>(pTar), posNode, numNode))
	{
		return OR_CANNOT_FIND_MOVE_PATH;
	}

	if(numNode == 0) return OR_CANNOT_FIND_MOVE_PATH;

	return BHV_Move(INVALID_ID, numNode, posNode, INVALID_ID, NULL);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_Move
(
	int32		nHandleID,
	uint16		wNumTargetPos,
	const GLPos *paTargetPos,
	int32		nStopLogicCount,
	const GLPos *paCurPos,
	ObjID_t		nSenderID
)
{
	__GUARD__ return m_pBHVState->Move
		(
			this,
			nHandleID,
			wNumTargetPos,
			paTargetPos,
			nStopLogicCount,
			paCurPos,
			nSenderID
		);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
GLPos Behavior_Character::GetRandPosOfCircle(const GLPos *pPos, float fRadio)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	Tar;
	__GUARD__ float Vx = (float) (rand() % 11);
	int32		nDir = rand() % 2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!nDir) Vx = -Vx;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	Vz = (float) sqrt(100 - Vx * Vx);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nDir = rand() % 2;
	if(!nDir) Vz = -Vz;

	Tar.m_fX = pPos->m_fX + (Vx / 10) * fRadio;
	Tar.m_fZ = pPos->m_fZ + (Vz / 10) * fRadio;
	__UNGUARD__ return Tar;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Behavior_Character::State_OnActive(int32 nStateID)
{
	__GUARD__ if(NULL == GetCharacter())
	{
		return;
	}

	switch(nStateID)
	{
	case ESTATE_TERROR:
		{
			ForceInterruptAllSpell();

			if(GetCharacter()->IsMoving())
			{
				BHV_Stop();
			}
			else
			{
				//GetCharacter()->SendArriveMSG();
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Behavior_Character::State_OnShutdwon(int32 nStateID)
{
	__GUARD__ 
	if(NULL == GetCharacter())
	{
		return;
	}

	switch(nStateID)
	{
	case ESTATE_TERROR:
		{
			if(GetCharacter()->IsMoving())
			{
				BHV_Stop();
			}
			else
			{
				//GetCharacter()->SendArriveMSG();
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
OPT_RESULT Behavior_Character::BHV_StopSpell()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCharacter)
	{
		//pCharacter->BHV_StopSkill();
	}

	return OR_OK;

	__UNGUARD__ return OR_OK;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
OPT_RESULT Behavior_Character::BHV_StopMove()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCharacter)
	{
		pCharacter->BHV_StopMove();
	}

	return OR_OK;

	__UNGUARD__ return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_UseSpell
(
	ObjID_t idSpell,
	ObjID_t idTarget,
	float	fTargetX,
	float	fTargetZ,
	int32	iHurtDelayTime,
	float	fDir /* = -1.f */,
	GUID_t	guidTarget
)
{
	__GUARD__ return m_pBHVState->UseSpell
		(
			this,
			idSpell,
			idTarget,
			fTargetX,
			fTargetZ,
			iHurtDelayTime,
			fDir,
			guidTarget
		);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Character::BHV_UseItem
(
	ID_t			nBagIndex,
	ObjID_t			nTargetObj,
	GLPos const		&posTarget,
	SHorseGuid const	&guidTargetPet,
	ID_t			nTargetItem
)
{
	__GUARD__ return m_pBHVState->UseItem(this, nBagIndex, nTargetObj, posTarget, guidTargetPet, nTargetItem);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Character::Terror_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCharacter)
	{
		return;
	}

	if(pCharacter->IsMoving())
	{
		return;
	}

	if(RANDOM_TIME == m_nIntervalTime || m_nIntervalTime <= 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float		fLen = (float) (rand() % RANDOM_DIST);
		GLPos	pos = GetRandPosOfCircle(pCharacter->GetGLPos(), fLen);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		BHV_Move_i(&pos);
		m_nIntervalTime = rand() % RANDOM_TIME;

		return;
	}

	m_nIntervalTime -= pCharacter->GetLogicTime();

	__UNGUARD__
}


Character* Behavior_Character::GetCharacter() const
{ 
	return m_pCharacter; 
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Character::OnEvent_Die(Object *pKiller)
{
	__GUARD__ m_pBHVState->OnEvent_Die(this, pKiller);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Character::OnEvent_Relive(Object *pKiller)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Character::OnEvent_Damage(int32 nDamage, Character *pAttacker)
{
	__GUARD__ m_pBHVState->OnEvent_Damage(this, nDamage, pAttacker);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Character::OnEvent_BeSpell(Character *pCharacter, int32 nGoodEffect)
{
	__GUARD__ m_pBHVState->OnEvent_BeSpell(this, pCharacter, nGoodEffect);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Character::OnEvent_BeHeal(Character *pCharacter, int32 nHeal)
{
	__GUARD__ m_pBHVState->OnEvent_BeHeal(this, pCharacter, nHeal);
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Behavior_Character::ChangeState(eSTATE eState)
{
	__GUARD__ if(eState == m_pBHVState->GetStateID()) return;


	BHVState	*s = g_BHVStateList.InstanceState(eState);


	if (ESTATE_COMBAT == eState)
	{
		int kk = 0;
	}

	if(s)
	{
		if(m_pBHVState)
		{
			State_OnShutdwon(m_pBHVState->GetStateID());
		}


		SetBehavior_State(s);
		State_OnActive(m_pBHVState->GetStateID());
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Behavior_Character::Clear(void)
{
	m_pCharacter = NULL;
}



BOOL Behavior_Character::Logic(uint32 uTime)
{
	if (m_pCharacter->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		int kk = 0;
	}
	return m_pBHVState->Logic(this, uTime);
}

void Behavior_Character::SetBehavior_State(BHVState* s)
{ 
	if (m_pBHVState != nullptr && m_pBHVState != s)
	{
		if (m_pBHVState->GetStateID() == 6 && s->GetStateID() == 0)
		{
			int kk = 0;
		}
	}
	m_pBHVState = s; 

}
/*
=======================================================================================================================
=======================================================================================================================
*/
OPT_RESULT Behavior_Character::BHV_Move_i(const GLPos *pTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCharacter = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCharacter)
	{
		KCheck(NULL && "Behavior_Character::MoveTo...pCharacter = NULL...");
		return OR_NULL_POINTER;
	}

	if(TRUE == pCharacter->IsLimitMove())
	{
		return OR_LIMIT_MOVE;
	}

	if(pCharacter->IsDie())
	{
		return OR_DIE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int		numNode = 0;
	const GLPos *pCur = pCharacter->GetGLPos();
	GLPos	posNode[MAX_CHAR_PATH_NODE_NUMBER];
	GLPos	posCur = *pCur;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pCharacter->GetMap());
	KCheck(pCharacter->GetMap()->GetMapInfo());
	KCheck(pCharacter->GetMap()->GetMapInfo()->GetPathFinder());

	pCharacter->GetMap()->GetMapInfo()->VerifyPos (const_cast<GLPos *>(pTar));
	if
		(
		!pCharacter->GetMap()->GetMapInfo()->GetPathFinder()->FindPath
		(
		&posCur,
		const_cast<GLPos *>(pTar),
		posNode,
		numNode
		)
		)
	{
		return OR_CANNOT_FIND_MOVE_PATH;
	}

	if(numNode == 0)
	{
		return OR_CANNOT_FIND_MOVE_PATH;
	}

	return m_pBHVState->BHV_Move(this, INVALID_ID, numNode, posNode);

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
OPT_RESULT Behavior_Character::BHV_UseSpell_i
(
 ObjID_t idSpell,
 ObjID_t idTarget,
 float	fTargetX,
 float	fTargetZ,
 int32	iHurtDelayTime,
 float	fDir /* = -1.f */,
 GUID_t	guidTarget	/* INVALID_ID */
 )
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_currUseSpellID = idSpell;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_pBHVState->BHV_UseSpell(this, idSpell, idTarget, fTargetX, fTargetZ, iHurtDelayTime, fDir, guidTarget);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
OPT_RESULT Behavior_Character::BHV_UseItem_i
(
 ID_t			nBagIndex,
 ObjID_t			nTargetObj,
 GLPos const		&posTarget,
SHorseGuid const	&guidTargetPet,
 ID_t			nTargetItem
 )
{
	__GUARD__ return m_pBHVState->BHV_UseItem(this, nBagIndex, nTargetObj, posTarget, guidTargetPet, nTargetItem);
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

