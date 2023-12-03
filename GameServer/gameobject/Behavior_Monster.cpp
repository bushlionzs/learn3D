/*$T MapServer/Server/AI/Behavior_Monster.cpp GC 1.140 10/10/07 10:07:19 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Behavior_Monster.h"
#include "Character.h"
#include "Monster.h"
#include "Pet.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "BaseTool.h"
#include "TabDefine.h"

#include "gameobject/Behavior_Helper.h"
#include "map/server_map_path.h"
#include "map/map_manager.h"
#include "data/data_manager.h"

#include "ScriptCacheMgr.h"
#include "FileDef.h"
#include "gameobject/ObjectManager.h"
#include "server_settting.h"
#include "gameobject/Player.h"
#include "net/messages/SCCharMove.h"
#include "server_message.pb.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */

Behavior_Monster::Behavior_Monster()
{
	m_nAITemplte = 0;
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Behavior_Monster::~Behavior_Monster()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::Init(Character *pCharacter)
{
	Reset();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bResult = Behavior_Character::Init(pCharacter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult)
	{
		return FALSE;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Behavior_Character:: Clear();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Reset()
{
	/*~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Init();
	/*~~~~~~~~~~~~~~~~~~~*/

	m_ScanTimer.Clear();
	m_RandMoveTimer.Clear();
	m_BodyTimer.Clear();

	m_nIndexOfPassed = 0;
	m_nIndexOfMoveTo = 0;
	m_baHead = TRUE;
	m_TeammateCount = 0;
	for(int32 j = 0; j < BHV_MAX_TEAMMATE_COUNT; ++j)
	{
		m_TeammateID[j] = INVALID_ID;
	}

	InitTimesFromBehavior_Template(m_nAITemplte);

	m_bCheckJam = FALSE;
	m_uServiceTime = 0;

	ToBHVIdle();

	__UNGUARD__
}


Monster* Behavior_Monster::GetCharacter(void) const
{
	Character* pCharacter = Behavior_Character::GetCharacter();
	return((Monster*)pCharacter);
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Init()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_EnemyCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_SpellID = 0;
	m_NextSpellID = INVALID_ID;
	m_ItemID = INVALID_ID;
	m_bContinuePatrol = FALSE;
	m_bLogicStop = FALSE;

	m_nRefusePaoPaoTime = 0;
	m_nSettleTime = 0;
	m_PatrolScriptID = -1;
	m_SpellSenderID = INVALID_ID;
	m_bConvoyNPC = FALSE;
	SetSpeedyOfRecover();
	for(int32 i = 0; i < BHV_MAX_ENEMY_COUNT; ++i)
	{
		m_EnemyID[i] = INVALID_ID;
	}

	m_pNextTarget = NULL;
	m_nThreatCount = 0;
	m_ThreatList.clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 -- Idle状态逻辑
 =======================================================================================================================
 */
void Behavior_Monster::Idle_Logic(uint32 uTime)
{
	__GUARD__ GET_MONSTER_MAP((void) 0)
	
	if(!GetCharacter()->IsActiveObj())
	{
		return;
	}


	Update_RefusePaoPaoTime();

	if(TRUE == ScanEnemy(uTime)) return;

	if(BHVParam(BHVPARAM_RANDMOVETIME) > 0 && !GetCharacter()->IsMoving() && !GetNextTarget())
	{
		if(!m_RandMoveTimer.IsSetTimer())
		{
			m_RandMoveTimer.BeginTimer
				(
					BHVParam(BHVPARAM_RANDMOVETIME) + (rand() % BHVParam(BHVPARAM_RANDMOVETIME)),
					uTime
				);
		}

		if(m_RandMoveTimer.CountingTimer(uTime))
		{
			ToBHVRandMove();
		}
	}

	ExcuteStateBehavior_Template(AIS_Idle);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Approach_Logic(uint32 uTime)
{
	__GUARD__ GET_MONSTER_MAP((void) 0)
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character *pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCurEnemy || !pCurEnemy->IsAlive() || !pCurEnemy->IsCanViewMe(pMonster))
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	float	fMTDist, fETDist;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCurEnemy)
	{
		KCheck(NULL && "Behavior_Monster::Logic_Approach...pCurEnemy=NULL...");
		ToBHVGoHome();
		return;
	}

	if(IsToGoHome(fMTDist, fETDist))
	{
		ToBHVGoHome();
		return;
	}

	if(BHV_ZERO_VALUE > fMTDist)
	{
		ToBHVAttack();
	}
	else
	{
		if(fETDist > (float) BHVParam(BHVPARAM_RESETTARGET_DIST) / 1000.0f)
		{
			ToBHVApproachTar();
		}
		else if(!GetCharacter()->IsMoving())
		{
			ToBHVApproachTar();
		}
	}

	ExcuteStateBehavior_Template(AIS_Approach);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Flee_Logic(uint32 uTime)
{
	__GUARD__ GET_MONSTER_MAP((void) 0)
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character *pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCurEnemy || !pCurEnemy->IsAlive() || !pCurEnemy->IsCanViewMe(pMonster))
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(GetCharacter()->GetGLPos(), GetCharacter()->GetFinalTarPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == GetCharacter()->IsMoving())
	{
		if(fDist >= BHV_ZERO_VALUE)
		{
			BHV_Move(GetCharacter()->GetFinalTarPos());
			return;
		}
		else
		{
			if(pCurEnemy == NULL || !pCurEnemy->IsAlive() || fDist < BHV_ZERO_VALUE)
			{
				GetCharacter()->SetMoveMode(MOVE_MODE_WALK);

				switch(m_FleeType)
				{
				case MONSTER_BHV_FLEE_RANDOM:
				case MONSTER_BHV_FLEE_NEARESTFRIEND:
				case MONSTER_BHV_FLEE_NEARESTPOINT:
					SummonTeammate
					(
						(int32) GetCharacter()->GetGLPos()->m_fX,
						(int32) GetCharacter()->GetGLPos()->m_fZ
					);
					ToBHVApproachTar();
					break;

				default:
					KCheck(false);
					break;
				}
			}

			ExcuteStateBehavior_Template(AIS_Flee);
			return;
		}
	}

	if(pCurEnemy == NULL || !pCurEnemy->IsAlive() || fDist < BHV_ZERO_VALUE)
	{
		GetCharacter()->SetMoveMode(MOVE_MODE_WALK);

		switch(m_FleeType)
		{
		case MONSTER_BHV_FLEE_RANDOM:
		case MONSTER_BHV_FLEE_NEARESTFRIEND:
		case MONSTER_BHV_FLEE_NEARESTPOINT:
			SummonTeammate
			(
				(int32) GetCharacter()->GetGLPos()->m_fX,
				(int32) GetCharacter()->GetGLPos()->m_fZ
			);
			ToBHVApproachTar();
			break;

		default:
			KCheck(false);
			break;
		}
	}

	ExcuteStateBehavior_Template(AIS_Flee);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
GLPos Behavior_Monster::GetPosByIndexOfPassed(int32 nIndexOfPassed)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos		Tar;
	__GUARD__ Monster	*pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMonster);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMap);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	PatrolRoadsPointMgr	*pPatrolPathMgr = pMap->GetPatrolPathMgr();
	int32		patrolPathIndex = pMonster->GetPatrolPathIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nIndexOfMoveTo = pPatrolPathMgr->GetPatrolRoadsPoint
		(
			patrolPathIndex,
			m_nIndexOfPassed,
			m_baHead,
			Tar,
			m_nSettleTime,
			m_PatrolScriptID
		);

	pMap->GetMapInfo()->VerifyPos(&Tar);
	__UNGUARD__ return Tar;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Patrol_Logic(uint32 uTime)
{
	__GUARD__ GET_MONSTER_MAP((void) 0) if(!(pMonster->IsActiveObj()))
	{
		return;
	}

	if(TRUE == ScanEnemy(uTime))
	{
		return;
	}

	if(!m_bConvoyNPC && !m_bContinuePatrol)
	{
		BHV_Stop();
		return;
	}

	if(pMonster->IsLimitMove())
	{
		return;
	}

	if(!pMonster->IsMoving())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		GLPos	Tar = GetPosByIndexOfPassed(m_nIndexOfPassed);
		GLPos	curTar = *(pMonster->GetGLPos());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(curTar == Tar)
		{
			if(m_PatrolScriptID > 0 )
			{
				/*pMonster->GetMap()->GetLuaSystem()->RunScriptFunction
					(
						pMonster->GetMap()->MapID(),
						m_PatrolScriptID,
						DEF_PROC_EVENT_ENTRY_FN,
						pMonster->GetMapID_i(),
						pMonster->GetID()
					);*/
			}

			if(m_nSettleTime > 0)
			{
				m_nSettleTime -= pMonster->GetLogicTime();
				return;
			}

			m_nIndexOfPassed = m_nIndexOfMoveTo;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GLPos	NextTar = GetPosByIndexOfPassed(m_nIndexOfPassed);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			MonsterGo(&NextTar);
			m_nRefusePaoPaoTime = 0;
		}
		else
		{
			MonsterGo(&Tar);
		}
	}

	ExcuteStateBehavior_Template(AIS_Patrol);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Gohome_Logic(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	
	//如果可以回到原始状态
	if (BHVParam(BHVPARAM_RET_ORI_STATE))
	{
		RecoverHP();
	}
	Monster		*pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMonster);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float		fDist = 0.f;
	const GLPos *posCur = pMonster->GetFinalTarPos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	*pPos = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if(pMonster->isPatrolMonster())
		pPos = const_cast<GLPos *>(&GetAttackPos());
	else
		pPos = const_cast<GLPos *>(pMonster->GetRespawnPos());

	//当行走逻辑没有目标点时，让其进入休闲状态
	const _LOGICPARAM_MOVE *pLogicMoveParam = pMonster->GetLogicMoveParam();
	if (pLogicMoveParam && pLogicMoveParam->IsEmpty())
	{
		fDist = KLSqrt(pMonster->GetGLPos(), pPos);
		if (fDist < BHV_ZERO_VALUE)
		{
			ToBHVIdle();
			ExcuteStateBehavior_Template(AIS_GoHome);
			return ;
		}
		
	}

	if(posCur)
	{
		fDist = KLSqrt(pMonster->GetGLPos(), posCur);
	}

	if(fDist < BHV_ZERO_VALUE)
	{
		ToBHVIdle();
	}
	else
	{
		if(!pMonster->IsMoving())
		{
			//如果可以回到原始状态
			if (BHVParam(BHVPARAM_RET_ORI_STATE))
			{
				pMonster->MarkBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_CAN_MOVE);
				pMonster->MarkBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
				pMonster->ClearBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
			}

			pMonster->SetMoveMode(MOVE_MODE_RUN);			

			if(OR_OK != BHV_Move(pPos))
			{
				pMonster->DirectMoveTo(pPos);
			}
		}
	}

	ExcuteStateBehavior_Template(AIS_GoHome);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Dead_Logic(uint32 uTime)
{
	__GUARD__ if(m_RandMoveTimer.IsSetTimer())
	{
		m_RandMoveTimer.Clear();
	}

	if(m_BodyTimer.CountingTimer(uTime))
	{
		m_BodyTimer.Clear();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster *pMonster = GetCharacter();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pMonster->Enter_Respawn();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Combat_Logic(uint32 uTime)
{
	GET_MONSTER_MAP((void)0) 
	if (!pMonster->IsAlive())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character* pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pCurEnemy)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bNeedRemove = FALSE;
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pCurEnemy->GetMapID_i() != pMonster->GetMapID_i()) bNeedRemove = TRUE;
		if (!pCurEnemy->IsAlive()) bNeedRemove = TRUE;
		if (!pCurEnemy->IsCanViewMe(pMonster)) bNeedRemove = TRUE;
		if (!pCurEnemy->IsActiveObj()) bNeedRemove = TRUE;

		if (bNeedRemove)
		{
			RemoveCurrentThreat();
			if (NULL == GetNextTarget())
			{
				ToBHVGoHome();
			}

			return;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//容错处理
	if (NULL == pCurEnemy)
	{
		ToBHVGoHome();
		return;
	}

	if (TRUE == pMonster->IsMoving() || FALSE == pMonster->CanUseSkillNow())
	{
		return;
	}

	if (FALSE == m_bCheckJam)
	{
		CheckJamAndRemove();
		m_bCheckJam = TRUE;
		return;
	}

	if (pCurEnemy->IsUnbreakable() || pCurEnemy->IsImmuneAbsForLater())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character* pTmp = GetMostHated();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pTmp && GetNextTarget() != pCurEnemy)
		{
			ToBHVApproachTar();
			return;
		}
	}

	if (m_SAICommand.commandType != E_COMMAND_TYPE_INVALID)
	{
		ExcuteCommand();
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(pMonster->GetGLPos(), pCurEnemy->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (BHV_MIN_DIST > fDist && !pMonster->IsLimitMove())
	{
		/*~~~~~~~~~~~~~~~~*/
		GLPos	Tar;
		/*~~~~~~~~~~~~~~~~*/

		Tar.m_fX = pMonster->GetGLPos()->m_fX + BHV_FX_DELTA;
		Tar.m_fZ = pMonster->GetGLPos()->m_fZ + BHV_FZ_DELTA;
		pMap->GetMapInfo()->VerifyPos(&Tar);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	fDist = KLSqrt(pMonster->GetGLPos(), pCurEnemy->GetGLPos());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (TRUE == pMap->GetMapInfo()->IsCanGo(Tar)) MovePhonily(Tar);
	}

	if (INVALID_ID != m_NextSpellID)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iSkillHurtDelayTime = GetSpellHurtDelayTime(m_SpellID);
		OPT_RESULT oResult = BHV_UseSpell
		(
			m_SpellID,
			pCurEnemy->GetID(),
			pCurEnemy->GetGLPos()->m_fX,
			pCurEnemy->GetGLPos()->m_fZ,
			iSkillHurtDelayTime
		);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_NextSpellID = INVALID_ID;
	}

	ExcuteStateBehavior_Template(AIS_Combat);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iSkillHurtDelayTime = GetSpellHurtDelayTime(m_SpellID);
	OPT_RESULT oResult = BHV_UseSpell
	(
		m_SpellID,
		pCurEnemy->GetID(),
		pCurEnemy->GetGLPos()->m_fX,
		pCurEnemy->GetGLPos()->m_fZ,
		iSkillHurtDelayTime
	);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (OR_OK != oResult)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SpellTemplateData const* pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_SpellID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pSkillTemplate);

		float rangemax = pSkillTemplate->GetOptimalRangeMax();
		float rangemin = pSkillTemplate->GetOptimalRangeMin();
		if (fDist > rangemax || fDist < rangemin)
		{
			ToBHVApproachTar();

		}
			
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Service_Logic(uint32 uTime)
{
	__GUARD__ GET_MONSTER_MAP((void) 0) if(!GetCharacter()->IsActiveObj())
	{
		return;
	}

	if(!GetCharacter()->IsAlive())
	{
		return;
	}

	if(TRUE == ScanEnemy(uTime)) return;

	if(m_uServiceTime < GetCharacter()->GetLogicTime())
		m_uServiceTime = 0;
	else
		m_uServiceTime -= GetCharacter()->GetLogicTime();

	if(0 == m_uServiceTime) StopService();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::TeamFollow_Logic(uint32 uTime)
{
	__GUARD__ GET_MONSTER_MAP((void) 0) Update_RefusePaoPaoTime();

	if(TRUE == ScanEnemy(uTime))
	{
		return;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Event_OnBeSpell(Character *pObj_Character, int32 nGoodEffect)
{
	__GUARD__ if(NULL == pObj_Character) return;

	if(FALSE == IsObjCharacter(pObj_Character->GetObjType())) return;
	if(nGoodEffect > 0) return;
	if(FALSE == IsNeedStrickBack(pObj_Character, nGoodEffect)) return;

	ExcuteEventBehavior_Template(AIE_OnBeSkill);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Event_OnMove(const GLPos *pTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bCheckJam = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Event_OnDie(Object *pKiller)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	idKiller = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pKiller != NULL)
	{
		idKiller = pKiller->GetID();
	}

	ChangeState(ESTATE_DEAD);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMomster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_BodyTimer.BeginTimer(g_Config.m_ConfigInfo.m_DefaultBodyTime, pMomster->NowTime());

	ExcuteEventBehavior_Template(AIE_OnDie);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Event_OnDamage(int32 nDamage, Character *pAttacker)
{
	if (pAttacker == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster* pMe = (Monster*)GetCharacter();
	SpellID_t	nSkillID = pAttacker->GetSpellInfo().GetSpellID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pMe)
	{
		pMe->UpdateDamageList(nDamage, pAttacker);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nGoodEffect = GetSpellStandFlag(nSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (FALSE == IsNeedStrickBack(pAttacker, nGoodEffect)) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character* pPrevNextTarget = GetNextTarget();
	int32		nMount = CalcThreat(pAttacker, INVALID_ID, nDamage);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ModThreatByPtr(pAttacker, nMount);
	if (pPrevNextTarget != GetNextTarget()) ToBHVApproachTar();

	ExcuteEventBehavior_Template(AIE_OnDamage);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::ResetAllCombatInfo()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster)
	{
		RemoveAllThreat();
		pMonster->ResetCooldownList();
		InitTimesFromBehavior_Template(m_nAITemplte);

		Init();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ScanEnemy(uint32 uTime)
{
	return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::AddTeammate(ObjID_t TeammateID)
{
	__GUARD__ for(int32 i = 0; i < BHV_MAX_TEAMMATE_COUNT; ++i)
	{
		if(INVALID_ID == m_TeammateID[i])
		{
			m_TeammateID[i] = TeammateID;
			++m_TeammateCount;
			break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::DelAllTeammate()
{
	__GUARD__ for(int32 i = 0; i < BHV_MAX_TEAMMATE_COUNT; ++i)
	{
		m_TeammateID[i] = INVALID_ID;
		m_TeammateCount = 0;
		break;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::SummonTeammate(int32 nX, int32 nZ, int32 count)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
GLPos Behavior_Monster::FindNearestFriend()
{
	GLPos pos;
	return pos;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::StartTeamFollow(BOOL bRespawn)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::AddEnemyToTeammate(ObjID_t EnemyID)
{
	__GUARD__ GET_MONSTER_MAP((void) 0) for(int32 i = 0; i < BHV_MAX_TEAMMATE_COUNT; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pObj = pMap->GetObjManager()->GetObj(m_TeammateID[i]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pObj && pObj->GetObjType() == Object::OBJECT_CLASS_MONSTER)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Behavior_Monster	*pAI = (Behavior_Monster *) ((Monster *) pObj)->GetAIObj();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pAI)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Object	*pEnemy = pMap->GetObjManager()->GetObj(EnemyID);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pEnemy && IsObjCharacter(pEnemy->GetObjType()))
				{
					pAI->ModThreatByPtr((Character *) pEnemy);
					pAI->ToBHVApproachTar();
					pAI->SetAttackPos(*(pObj->GetGLPos()));
				}
			}
		}
		else
		{
			break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Teammate_Go_Fight(ObjID_t EnemyID)
{
	__GUARD__ GET_MONSTER_MAP((void) 0) if(m_TeammateCount > 0)
	{
		AddEnemyToTeammate(EnemyID);
	}
	else if(INVALID_ID != pMonster->GetLeaderID())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pObj = pMap->GetObjManager()->GetObj(pMonster->GetLeaderID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pObj && pObj->GetObjType() == Object::OBJECT_CLASS_MONSTER)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Behavior_Character	*pAI = ((Monster *) pObj)->GetAIObj();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pAI)
			{
				((Behavior_Monster *) pAI)->AddEnemyToTeammate(EnemyID);
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::StartPatrol(BOOL bConvoyNPC, BOOL bRespawn)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID() && !bRespawn)
	{
		return;
	}

	m_bConvoyNPC = bConvoyNPC;
	m_bContinuePatrol = TRUE;
	m_nThreatCount = 0;
	m_ThreatList.clear();

	Monster* pMonster = GetCharacter();
	KCheck(pMonster);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	PatrolRoadsPointMgr	*pPatrolPathMgr = pMonster->GetMap()->GetPatrolPathMgr();
	int32		patrolPathIndex = pMonster->GetPatrolPathIndex();
	GLPos	Tar;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nIndexOfMoveTo = pPatrolPathMgr->GetPatrolRoadsPoint
		(
			patrolPathIndex,
			m_nIndexOfPassed,
			m_baHead,
			Tar,
			m_nSettleTime,
			m_PatrolScriptID
		);

	pMonster->SetMoveMode(MOVE_MODE_WALK);
	pMonster->GetMap()->GetMapInfo()->VerifyPos(&Tar);
	if(pMonster->GetMap()->GetMapInfo()->IsCanGo(Tar))
	{
		MonsterGo(&Tar);
	}
	else
	{
		pMonster->Teleport(&Tar);
	}

	ChangeState(ESTATE_PATROL);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::PausePatrol(void)
{
	m_bContinuePatrol = FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::StopPatrol(void)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	m_bContinuePatrol = FALSE;
	m_bConvoyNPC = FALSE;

	BHV_Stop();

	m_nIndexOfPassed = 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster)
	{
		pMonster->Teleport(pMonster->GetRespawnPos());
	}

	ChangeState(ESTATE_IDLE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ToBHVRandMove()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GLPos	Tar;
	BOOL			FindPos = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < BHV_MAX_RAND_TIMES; i++)
	{
		Tar.m_fX = GetCharacter()->GetRespawnPos()->m_fX +
			rand() %
			GetCharacter()->GetPosRange() -
			rand() %
			GetCharacter()->GetPosRange();
		Tar.m_fZ = GetCharacter()->GetRespawnPos()->m_fZ +
			rand() %
			GetCharacter()->GetPosRange() -
			rand() %
			GetCharacter()->GetPosRange();
		GetCharacter()->GetMap()->GetMapInfo()->VerifyPos(&Tar);
		if(GetCharacter()->GetMap()->GetMapInfo()->IsCanGo(Tar))
		{
			FindPos = TRUE;
			break;
		}
	}

	if(FindPos == FALSE) return FALSE;
	if(OR_OK != BHV_Move(&Tar)) return FALSE;

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ToBHVIdle()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Monster	*pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster)
	{
		pMonster->ClearBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
		pMonster->SetMoveMode(MOVE_MODE_WALK);
		pMonster->SetDir(pMonster->GetRespawnDir());

		Init();
		if(pMonster->isPatrolMonster())
		{
			StartPatrol();
		}
		else
		{
			ChangeState(ESTATE_IDLE);
		}

		pMonster->ClearKiller();
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ToBHVFlee(int32 type, float fX, float fZ)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonster)
	{
		KCheck(NULL && "Behavior_Monster::ToFlee...pMonster = NULL...");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	Tar = *(pMonster->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_FleeType = type;
	switch(type)
	{
	case MONSTER_BHV_FLEE_RANDOM:
		Tar = *pMonster->GetGLPos();
		Tar = GetRandPosOfCircle(&Tar, BHV_MAX_FLEE_LENGTH);
		break;

	case MONSTER_BHV_FLEE_NEARESTFRIEND:
		Tar = FindNearestFriend();
		break;

	case MONSTER_BHV_FLEE_NEARESTPOINT:
		Tar.m_fX = fX;
		Tar.m_fZ = fZ;
		break;

	default:
		KCheck(FALSE);
		break;
	}

	pMonster->GetMap()->GetMapInfo()->VerifyPos(&Tar);
	if(FALSE == pMonster->GetMap()->GetMapInfo()->IsCanGo(Tar))
	{
		return FALSE;
	}

	if(OR_OK != BHV_Move(&Tar))
	{
		GetCharacter()->SetMoveMode(MOVE_MODE_WALK);
		return FALSE;
	}

	ChangeState(ESTATE_FLEE);

	ExcuteEventBehavior_Template(AIE_OnFlee);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ToBHVAttack(void)
{
	__GUARD__ if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonster)
	{
		KCheck(NULL && "Behavior_Monster::ToAttack...pMonster=NULL...");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap)
	{
		KCheck(NULL && "Behavior_Monster::ToAttack...pMap=NULL...");
		return FALSE;
	}

	pMonster->SetMoveMode(MOVE_MODE_RUN);

	/*~~~~~~~~~~~~~~~~*/
	GLPos	Tar;
	/*~~~~~~~~~~~~~~~~*/

	if(TRUE == GetBestPos(Tar))
	{
		pMonster->DirectMoveTo(&Tar);
	}

	ChangeState(ESTATE_COMBAT);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ToBHVGoHome()
{
	__GUARD__ GET_MONSTER_MAP(FALSE) if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return FALSE;
	}
	
	if (BHVParam(BHVPARAM_RET_ORI_STATE))
	{
		pMonster->FadeOutAllEffect();
		GetCharacter()->MarkBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
		GetCharacter()->ClearBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
	}

	GetCharacter()->SetMoveMode(MOVE_MODE_RUN);

	/*~~~~~~~~~~~~~~~~*/
	GLPos	Tar;
	/*~~~~~~~~~~~~~~~~*/

	if(pMonster->isPatrolMonster())
		Tar = GetAttackPos();
	else
		Tar = *(pMonster->GetRespawnPos());

	if(OR_OK != BHV_Move(&Tar))
	{
		GetCharacter()->DirectMoveTo(&Tar);
	}

	ChangeState(ESTATE_GOHOME);

	ExcuteEventBehavior_Template(AIE_OnGoHome);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ToBHVApproachTar()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	GET_MONSTER_MAP(FALSE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return FALSE;
	}

	pMonster->SetMoveMode(MOVE_MODE_RUN);
	pMonster->ClearBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCurEnemy || !pCurEnemy->IsAlive())
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return FALSE;
	}

	if(!pCurEnemy)
	{
		KCheck(NULL && "Behavior_Monster::ToApproachTar...pCurEnemy = NULL...");
		return FALSE;
	}

	ChangeState(ESTATE_APPROACH);

	/*~~~~~~~~~~~~~~~~~~~~~*/
	float	fMaxRange = 0.0f;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	if
	(
		(ESTATE_COMBAT == m_pBHVState->GetStateID() || ESTATE_APPROACH == m_pBHVState->GetStateID())
	&&	TRUE == ExcuteStateBehavior_Template(AIS_Combat)
	)
	{
		ToBHVAttack();
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~*/
	GLPos	Tar;
	OPT_RESULT		oResult;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == GetBestPos(Tar))
	{
		oResult = BHV_Move(&Tar);
	}
	else
	{
		oResult = BHV_Move(pCurEnemy->GetGLPos());
	}

	if(OR_OK != oResult && OR_LIMIT_MOVE != oResult)
	{
		pMonster->DirectMoveTo(pCurEnemy->GetGLPos());
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
GLPos Behavior_Monster::GetPosOfMemeberGo(const GLPos &rTargetPos, int32 index, float fDist)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos		Pos;
	__GUARD__ Monster	*pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonster)
	{
		KCheck(NULL && "Behavior_Monster::GetPosOfMemeberGo...pMonster=NULL...");
		return Pos;
	}

	/*~~~~~~~~~~~*/
	float	radian;
	/*~~~~~~~~~~~*/

	switch(index)
	{
	case 0:		radian = __HALF_PI + __QUARTER_PI; break;
	case 1:		radian = __QUARTER_PI; break;
	case 2:		radian = 0.f; break;
	case 3:		radian = -__QUARTER_PI; break;
	case 4:		radian = -(__HALF_PI + __QUARTER_PI); break;
	case 5:		radian = -__PI; break;
	default:	break;
	}

	radian += pMonster->GetDir();
	Pos.m_fX = rTargetPos.m_fX + fDist * MathSinCos::Sin(radian);
	Pos.m_fZ = rTargetPos.m_fZ + fDist * MathSinCos::Cos(radian);

	return Pos;

	__UNGUARD__ return Pos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::MemeberGo(const GLPos &rTargetPos, float fDist)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Behavior_Monster::MonsterGo(const GLPos *pPos)
{
	__GUARD__ GET_MONSTER_MAP(OR_NULL_MAP)
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT	       oResult = BHV_Move(pPos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != oResult && OR_LIMIT_MOVE != oResult)
	{
		GetCharacter()->DirectMoveTo(pPos);
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::MovePhonily(const GLPos &rTar)
{
	GET_MONSTER_MAP((void) 0) pMonster->SetGLPos(&rTar);
	pMonster->AddMoveLogicCount();

	/*~~~~~~~~~~~~~~~~*/
	SCCharMove*	packet = new SCCharMove;
	/*~~~~~~~~~~~~~~~~*/

	packet->setObjectID(pMonster->GetID());
	packet->setHandleID(pMonster->GetMoveLogicCount());
	packet->setTargetPos(&rTar);

	servermessage::ServerMsgCharMove dummy;
	dummy.set_object_id(pMonster->GetID());
	dummy.set_handle_id(pMonster->GetMoveLogicCount());
	base::GLPos* target = dummy.mutable_target_pos();
	target->set_fx(rTar.m_fX);
	target->set_fz(rTar.m_fZ);


	pMonster->GetMap()->broadCast(servermessage::SC_CHARACTER_MOVE, dummy, pMonster);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Behavior_Monster::BHVParam(uint32 AIParam)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(GetCharacter());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MonsterAIData* aidata = DataManager::GetSingletonPtr()->getMonsterAIData();
	return aidata->get(GetCharacter()->GetAIType(), AIParam);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::IsToGoHome(float &fMTDist, float &fETDist)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Monster	*pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMonster)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szMsg[128] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s(szMsg, 128, "Behavior_Monster::IsToGoHome...pMonster = NULL...");
		KCheckEx(FALSE, szMsg);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCurEnemy == NULL)
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return TRUE;
	}

	fETDist = KLSqrt(pCurEnemy->GetGLPos(), pMonster->GetFinalTarPos());

	fMTDist = KLSqrt(pMonster->GetGLPos(), pMonster->GetFinalTarPos());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(pMonster->GetGLPos(), pCurEnemy->GetGLPos());
	float	fRDist;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster->isPatrolMonster())
		fRDist = KLSqrt(pMonster->GetGLPos(), &GetAttackPos());
	else
		fRDist = KLSqrt(pMonster->GetGLPos(), pMonster->GetRespawnPos());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pEnemyScene = pCurEnemy->GetMap();
	GameMap*pMyScene = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMyScene == NULL)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szMsg[128] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s(szMsg, 128, "pMyScene=NULL...");
		KCheckEx(pMyScene, szMsg);
	}

	if(NULL == pEnemyScene)
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return TRUE;
	}

	if(pEnemyScene->MapID() != pMyScene->MapID())
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return TRUE;
	}

	if(FALSE == pCurEnemy->IsAlive())
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return TRUE;
	}

	if(fRDist >= BHVParam(BHVPARAM_RETURN) / 1000.0f)
	{
		RemoveCurrentThreat();
		if(NULL == GetNextTarget())
		{
			ToBHVGoHome();
		}

		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::Update_RefusePaoPaoTime()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = GetCharacter();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonster)
	{
		return;
	}

	if(m_nRefusePaoPaoTime > 0)
	{
		m_nRefusePaoPaoTime -= GetCharacter()->GetLogicTime();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RecoverHP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nCurHP = GetCharacter()->GetHP();
	int32		nMaxHP = GetCharacter()->GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nCurHP < nMaxHP)
	{
		nCurHP += (int32) (GetSpeedyOfRecover() * nMaxHP);
		if(nCurHP > nMaxHP) nCurHP = nMaxHP;

		GetCharacter()->SetHP(nCurHP);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::ExcuteCommand()
{
	__GUARD__ switch(m_SAICommand.commandType)
	{
	case E_COMMAND_TYPE_TOFLEE:
		{
			ToBHVFlee(m_SAICommand.param[0], (float) m_SAICommand.param[1], (float) m_SAICommand.param[2]);
		}
		break;

	case E_COMMAND_TYPE_TOATTACK:
		break;

	case E_COMMAND_TYPE_TOIDLE:
		break;

	default:
		break;
	}

	m_SAICommand.Clear();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::GetBestPos(GLPos &Tar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	GET_MONSTER_MAP(FALSE);
	Character	*pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pCurEnemy)
	{
		return FALSE;
	}

	if(TRUE == pMonster->IsLimitMove())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float			fMaxRange = 0.f;
	float			fMinRange = 0.f;
	SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_SpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pSkillTemplate)
	{
		fMaxRange = pSkillTemplate->GetOptimalRangeMax();
		fMinRange = pSkillTemplate->GetOptimalRangeMin();
	}
	
	float target_x = pCurEnemy->GetGLPos()->m_fX;
	float target_z = pCurEnemy->GetGLPos()->m_fZ;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	vX = target_x - pMonster->GetGLPos()->m_fX;
	float	vZ = target_z - pMonster->GetGLPos()->m_fZ;
	float	fDist = KLSqrt(pMonster->GetGLPos(), pCurEnemy->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDist < BHV_ZERO_VALUE)
	{
		return FALSE;
	}

	if(fDist >= fMinRange && fDist < fMaxRange)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fAttackRange = fMinRange < fMaxRange * 0.6f ? fMaxRange * 0.6f : fMinRange;
	float	fCos = vX / fDist;
	float	fSin = vZ / fDist;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Tar.m_fX = pMonster->GetGLPos()->m_fX + fCos * (fDist - fAttackRange);
	Tar.m_fZ = pMonster->GetGLPos()->m_fZ + fSin * (fDist - fAttackRange);
	

	pMap->GetMapInfo()->VerifyPos(&Tar);
	if(pMap->GetMapInfo()->IsCanGo(Tar))
	{
		float	fDist = KLSqrt(&Tar, pCurEnemy->GetGLPos());
		char buffer[256];
		sprintf(buffer, "getbestpos, tarx:%f, tarz:%f, enemyx:%f, enemyy:%f, dis:%f\n",
			Tar.m_fX, Tar.m_fZ, pCurEnemy->GetGLPos()->m_fX, pCurEnemy->GetGLPos()->m_fZ, fDist);
		::OutputDebugString(buffer);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::ProcessPaoPao(void)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::SetSpeedyOfRecover(float fSpeedyOfRecover)
{
	__GUARD__ fSpeedyOfRecover < 0.f ? fSpeedyOfRecover = 0.f : NULL;
	fSpeedyOfRecover > 1.f ? fSpeedyOfRecover = 1.f : NULL;
	m_fSpeedyOfRecover = fSpeedyOfRecover;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::ChangeState(eSTATE eState)
{
	__GUARD__ if(eState == m_pBHVState->GetStateID())
	{
		return;
	}

	if(ESTATE_PATROL == eState)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster *pMonster = GetCharacter();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pMonster);

		RemoveAllThreat();
		pMonster->ResetCooldownList();
		InitTimesFromBehavior_Template(m_nAITemplte);
	}
	else if(ESTATE_IDLE == eState || ESTATE_DEAD == eState || ESTATE_GOHOME == eState)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster *pMonster = GetCharacter();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pMonster);

		RemoveAllThreat();
		pMonster->ResetCooldownList();
		InitTimesFromBehavior_Template(m_nAITemplte);

		Init();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BHVState	*s = g_BHVStateList.InstanceState(eState);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(s)
	{
		m_pBHVState = s;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::PrintThreatList(Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ char szContex[128] = { 0 };
	char szMostHated[32] = { 0 };
	int32 state = GetBehavior_State()->GetStateID();
	Character *pMostHated = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMostHated) tsnprintf_s(szMostHated, 32, pMostHated->GetName());
	tsnprintf_s
	(
		szContex,
		128,
		">>BHVState=%d MostHated=%s HighestThreat=%d m_NextTargetID=%d<<",
		state,
		szMostHated,
		m_nCurrentHighestThreat,
		m_NextTargetID
	);

	

	__UNGUARD__
}

// [Todo][khan-2][2010-03-25][内容制作][head]制作3环副本——印度神庙3环
BOOL Behavior_Monster::TestThreat(Player* pPlayer)
{
	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RemoveAllThreat()
{
	m_nCurrentHighestThreat = 0;
	m_pNextTarget = NULL;
	m_NextTargetID = INVALID_ID;
	m_ThreatList.clear();
	m_nThreatCount = 0;
	memset((void *) m_aThreatList, 0, sizeof(m_aThreatList));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RemoveCurrentThreat()
{
	RemoveThreatByPtr(m_pNextTarget);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RemoveThreatByObjID(ObjID_t objID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(objID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pChar = ((Character *) pObj);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pChar);

			RemoveThreatByPtr(pChar);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RemoveThreatByPtr(Character *pChar)
{
	__GUARD__ if(NULL == pChar) return;

	if(FALSE == pChar->IsActiveObj() || FALSE == pChar->IsAlive())
	{
		RemoveThreatByObjID_i(m_NextTargetID);
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	*pThreat = (int32 *) getThreat(pChar->GetID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pThreat)
		{
			RemoveThreatByPtr_i(pChar);
		}
	}

	if(GetNextTarget() == pChar)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pTmp = GetMostHated();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pTmp) SetNextTarget(pTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RemoveThreatByObjID_i(ObjID_t objID)
{
	m_ThreatList.erase(objID);
	--m_nThreatCount;
	if(m_ThreatList.empty())
	{
		m_nCurrentHighestThreat = 0;
		m_pNextTarget = NULL;
		m_NextTargetID = INVALID_ID;
		m_nThreatCount = 0;
		m_ThreatList.clear();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::RemoveThreatByPtr_i(Character *pChar)
{
	KCheck(pChar);
	m_ThreatList.erase(pChar->GetID());

	--m_nThreatCount;
	if(m_ThreatList.empty())
	{
		m_nCurrentHighestThreat = 0;
		m_pNextTarget = NULL;
		m_NextTargetID = INVALID_ID;
		m_nThreatCount = 0;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ModThreatByObjID(ObjID_t objID, int32 nMount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(objID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pChar = ((Character *) pObj);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pChar);
			return ModThreatByPtr(pChar, nMount);
		}
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ModThreatByPtr(Character *pChar, int32 nMount)
{
	__GUARD__ 
	if(GetCharacter()==NULL)
		return FALSE;
	if(!GetCharacter()->IsAlive()) return FALSE;
	if(NULL == pChar) return FALSE;
	if(!pChar->IsActiveObj() || !pChar->IsAlive()) return FALSE;
	if(pChar->GetMapID_i() != GetCharacter()->GetMapID_i()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pPrevTextTarget = GetNextTarget();
	int32		*pThreat = (int32 *)getThreat(pChar->GetID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == pThreat)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	*pThreatSlot = GetFreeThreatSlot();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pThreatSlot)
		{
			return FALSE;
		}

		*pThreatSlot = nMount;
		addThreat(pChar->GetID(), pThreatSlot);

		if(nMount > m_nCurrentHighestThreat)
		{
			m_nCurrentHighestThreat = nMount;
			SetNextTarget(pChar);
		}
	}
	else if(nMount > 0)
	{
		(*pThreat) += nMount;
		if(*pThreat > m_nCurrentHighestThreat)
		{
			m_nCurrentHighestThreat = *pThreat;
			SetNextTarget(pChar);
		}
	}

	if(pChar == GetNextTarget())
	{
		if(nMount < 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pTmp = GetMostHated();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTmp) SetNextTarget(pTmp);
		}
	}
	
	if(NULL == GetNextTarget())
	{
		SetNextTarget(pChar);
	}

	if(NULL == pPrevTextTarget && GetNextTarget())
	{
		if(g_Config.m_ConfigInfo.m_nToggleDebugBehavior_Template)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pCurrentEnemy = GetNextTarget();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pCurrentEnemy && pCurrentEnemy->GetID() >= 15000)
			{
				QLogSystem::SLOW_LOG
					(
						SLOW_LOG_SERVER,
						"obj=%d,EnterCombat...EnemyID=%d",
						GetCharacter()->GetID(),
						GetNextTarget()->GetID()
					);
			}
		}

		ExcuteEventBehavior_Template(AIE_OnEnterCombat);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::RandomAttack(int32 nModThreat)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nCount = 0;
	ObjID_t pObjIDList[MAX_THREAT_COUNT];
	auto it = m_ThreatList.begin();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(; it != m_ThreatList.end(); ++it)
	{
		if(INVALID_ID != it->first)
		{
			pObjIDList[nCount++] = it->first;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nIndex = rand() % nCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return ModThreatByObjID(pObjIDList[nIndex], m_nCurrentHighestThreat + nModThreat);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::UseSpellToSpecialProfession(int32 nProfession, int32 nSkillID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ auto	it = m_ThreatList.begin();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(; it != m_ThreatList.end(); ++it)
	{
		if(INVALID_ID != it->first)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(it->first);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pObj && Object::OBJECT_CLASS_PLAYER == pObj->GetObjType())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Player	*pPlayer = (Player *) pObj;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(nProfession == pPlayer->GetProfession())
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					OPT_RESULT oResult = BHV_UseSpell
						(
							nSkillID,
							it->first,
							pPlayer->GetGLPos()->m_fX,
							pPlayer->GetGLPos()->m_fZ,
							INVALID_ID
						);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					return(OR_OK == oResult);
				}
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::AttackSpecialProfession(int32 nProfession, int32 nModThreat)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ auto	it = m_ThreatList.begin();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(; it != m_ThreatList.end(); ++it)
	{
		if(INVALID_ID != it->first)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(it->first);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pObj && Object::OBJECT_CLASS_PLAYER == pObj->GetObjType())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Player	*pPlayer = (Player *) pObj;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(nProfession == pPlayer->GetProfession())
				{
					return ModThreatByObjID(pPlayer->GetID(), m_nCurrentHighestThreat + nModThreat);
				}
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Character *Behavior_Monster::GetMostHated()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nCurrentTreat = -1;
	ObjID_t defaultID = INVALID_ID;
	ObjID_t mosthatedID = INVALID_ID;
	auto it2 = m_ThreatList.begin();
	auto it =it2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(; it2 != m_ThreatList.end();)
	{
		it = it2;
		++it2;

		if(INVALID_ID != it->first)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32 nThreat = *(int32 *) (it->second);
			Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(it->first);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL == pObj)
			{
				continue;
			}

			KCheck(IsObjCharacter(pObj->GetObjType()));

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pChar = ((Character *) pObj);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pChar);

			if(FALSE == pChar->IsActiveObj() || FALSE == pChar->IsAlive())
			{
				continue;
			}

			defaultID = pChar->GetID();

			if(pChar->IsUnbreakable() || pChar->IsImmuneAbsForLater())
			{
				continue;
			}

			if(nThreat > nCurrentTreat)
			{
				nCurrentTreat = nThreat;
				m_nCurrentHighestThreat = nCurrentTreat;
				mosthatedID = pChar->GetID();
			}
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = GetCharacter()->GetSpecificObjInSameSceneByID(mosthatedID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pObj == NULL)
	{
		pObj = GetCharacter()->GetSpecificObjInSameSceneByID(defaultID);
		if(pObj == NULL) return NULL;
	}

	KCheck(IsObjCharacter(pObj->GetObjType()));

	return (Character *) pObj;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::SetNextTarget(Character *pChar)
{
	KCheck(pChar);
	KCheck(pChar->IsActiveObj() && pChar->IsAlive());

	m_pNextTarget = pChar;
	m_NextTargetID = pChar->GetID();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Behavior_Monster::CalcThreat(Character *pChar, int32 nSpellID, int32 nDmg)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pChar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(GetCharacter()->IsFriend(pChar))
	{
		return 0;
	}

	/*~~~~~~~~~~*/
	int32 mod = 0;
	/*~~~~~~~~~~*/

	if(INVALID_ID != nSpellID)
	{
	}
	else
	{
		mod = nDmg;
	}

	return mod;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 *Behavior_Monster::GetFreeThreatSlot()
{
	__GUARD__ if(m_nThreatCount < 0 || m_nThreatCount >= MAX_THREAT_COUNT) return NULL;
	return &m_aThreatList[m_nThreatCount++];
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::InitTimesFromBehavior_Template(int32 nBehavior_Template)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const Behavior_Template	&rBehavior_Template = Behavior_TemplateManager::GetInstance().GetBehavior_Template(m_nAITemplte);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < rBehavior_Template.m_nRecordCount; ++i)
	{
		m_aBehavior_TemplateTimes[i] = rBehavior_Template.GetRecord(i).m_nTimes;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::ChangeAITemplete(int32 nNewBehavior_Template)
{
	m_nAITemplte = nNewBehavior_Template;
	InitTimesFromBehavior_Template(m_nAITemplte);
	GetCharacter()->ResetCooldownList();
}

/*
 =======================================================================================================================
 --执行 AI的 状态
 =======================================================================================================================
 */
BOOL Behavior_Monster::ExcuteStateBehavior_Template(int32 state)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	const Behavior_Template &rBehavior_Template = Behavior_TemplateManager::GetInstance().GetBehavior_Template(m_nAITemplte);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < rBehavior_Template.m_nRecordCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const AIRecord	&rAIRecord = rBehavior_Template.GetRecord(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID != rAIRecord.m_nScriptID)
		{
			return ExcuteScriptInState(state);
		}

		if(rAIRecord.m_nState == state)
		{
			if(CheckCondition(rAIRecord, m_aBehavior_TemplateTimes[i]))
			{
				if(DoOperator(rAIRecord, state, -1))
				{
					if(INVALID_ID != m_aBehavior_TemplateTimes[i])
					{
						m_aBehavior_TemplateTimes[i]--;
					}

					return TRUE;
				}
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ExcuteEventBehavior_Template(int32 event)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	if(AIE_OnEnterCombat == event)
	{
		GetCharacter()->ClearBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
		SetAttackPos(*GetCharacter()->GetGLPos());
	}

	if(MAP_TYPE_FUBEN == GetCharacter()->GetMap()->GetMapType())
	{
		if(AIE_OnEnterCombat == event)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pCurrentEnemy = GetNextTarget();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const Behavior_Template	&rBehavior_Template = Behavior_TemplateManager::GetInstance().GetBehavior_Template(m_nAITemplte);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < rBehavior_Template.m_nRecordCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const AIRecord	&rAIRecord = rBehavior_Template.GetRecord(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID != rAIRecord.m_nScriptID)
		{
			return ExcuteScriptOnEvent(event);
		}

		if(rAIRecord.m_Event.m_EventID == event)
		{
			if(CheckCondition(rAIRecord, m_aBehavior_TemplateTimes[i]))
			{
				if(DoOperator(rAIRecord, -1, event))
				{
					if(INVALID_ID != m_aBehavior_TemplateTimes[i])
					{
						m_aBehavior_TemplateTimes[i]--;
					}

					return TRUE;
				}
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ExcuteScriptOnEvent(int32 event)
{
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::ExcuteScriptInState(int32 state)
{
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::CheckCondition(const AIRecord &record, int32 times)
{
	__GUARD__ if(INVALID_ID == record.m_nTimes || 0 < times)
	{
		if(INVALID_ID != record.m_nHP)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32 nHPRate = (GetCharacter()->GetHP() * 100) / (GetCharacter()->GetMaxHP());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nHPRate >= record.m_nHP) return FALSE;
		}

		if(INVALID_ID != record.m_nRandom)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32 nRandom = RandGenerator::GetRand(0, 100);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nRandom >= record.m_nRandom) return FALSE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		PLAISFunc CheckOperationPtr = record.m_CheckOperation.m_FunPtrOperation;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(CheckOperationPtr)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32 nRet = CheckOperationPtr
				(
					GetCharacter(),
					record.m_aAIOperation[0].m_aOperationParam[0],
					record.m_aAIOperation[0].m_aOperationParam[1],
					record.m_aAIOperation[0].m_aOperationParam[2]
				);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(INVALID_ID == nRet) return FALSE;
		}

		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::DoOperator(const AIRecord &record, int32 state, int32 event)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRet = 0;
	PLAISFunc OperatorPtr = record.m_aAIOperation[0].m_FunPtrOperation;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OperatorPtr)
	{
		nRet = OperatorPtr
		(
			GetCharacter(),
			record.m_aAIOperation[0].m_aOperationParam[0],
			record.m_aAIOperation[0].m_aOperationParam[1],
			record.m_aAIOperation[0].m_aOperationParam[2]
		);

		if(g_Config.m_ConfigInfo.m_nToggleDebugBehavior_Template)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pCurrentEnemy = GetNextTarget();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pCurrentEnemy && pCurrentEnemy->GetID() >= 15000)
			{
				QLogSystem::SLOW_LOG
					(
						SLOW_LOG_AIDEBUG,
						"obj=%d,Opeartor0=%s,param0=%d,param1=%d,param2=%d,bRet=%d,oResult=%s,state=%s,event=%s",
						GetCharacter()->GetID(),
						Behavior_TemplateManager::GetInstance().GetOperatorNameByPtr(OperatorPtr),
						record.m_aAIOperation[0].m_aOperationParam[0],
						record.m_aAIOperation[0].m_aOperationParam[1],
						record.m_aAIOperation[0].m_aOperationParam[2],
						nRet,
						GetORTText(GetSpellErrorCode()),
						Behavior_TemplateManager::GetInstance().GetStateNameByID(state),
						Behavior_TemplateManager::GetInstance().GetEventNameByID(event)
					);
			}
		}

		if(INVALID_ID == nRet)
		{
			return FALSE;
		}
	}

	OperatorPtr = record.m_aAIOperation[1].m_FunPtrOperation;
	if(OperatorPtr)
	{
		nRet = OperatorPtr
		(
			GetCharacter(),
			record.m_aAIOperation[1].m_aOperationParam[0],
			record.m_aAIOperation[1].m_aOperationParam[1],
			record.m_aAIOperation[1].m_aOperationParam[2]
		);

		if(g_Config.m_ConfigInfo.m_nToggleDebugBehavior_Template)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pCurrentEnemy = GetNextTarget();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pCurrentEnemy && pCurrentEnemy->GetID() >= 15000)
			{
				QLogSystem::SLOW_LOG
					(
						SLOW_LOG_AIDEBUG,
						"obj=%d,Opeartor1=%s,param0=%d,param1=%d,param2=%d,bRet=%d,oResult=%s,state=%s,event=%s",
						GetCharacter()->GetID(),
						Behavior_TemplateManager::GetInstance().GetOperatorNameByPtr(OperatorPtr),
						record.m_aAIOperation[1].m_aOperationParam[0],
						record.m_aAIOperation[1].m_aOperationParam[1],
						record.m_aAIOperation[1].m_aOperationParam[2],
						nRet,
						GetORTText(GetSpellErrorCode()),
						Behavior_TemplateManager::GetInstance().GetStateNameByID(state),
						Behavior_TemplateManager::GetInstance().GetEventNameByID(event)
					);
			}
		}

		if(INVALID_ID == nRet)
		{
			return FALSE;
		}
	}

	OperatorPtr = record.m_aAIOperation[2].m_FunPtrOperation;
	if(OperatorPtr)
	{
		nRet = OperatorPtr
		(
			GetCharacter(),
			record.m_aAIOperation[2].m_aOperationParam[0],
			record.m_aAIOperation[2].m_aOperationParam[1],
			record.m_aAIOperation[2].m_aOperationParam[2]
		);

		if(g_Config.m_ConfigInfo.m_nToggleDebugBehavior_Template)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pCurrentEnemy = GetNextTarget();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pCurrentEnemy && pCurrentEnemy->GetID() >= 15000)
			{
				QLogSystem::SLOW_LOG
					(
						SLOW_LOG_AIDEBUG,
						"obj=%d,Opeartor2=%s,param0=%d,param1=%d,param2=%d,bRet=%d,oResult=%s,state=%s,event=%s",
						GetCharacter()->GetID(),
						Behavior_TemplateManager::GetInstance().GetOperatorNameByPtr(OperatorPtr),
						record.m_aAIOperation[2].m_aOperationParam[0],
						record.m_aAIOperation[2].m_aOperationParam[1],
						record.m_aAIOperation[2].m_aOperationParam[2],
						nRet,
						GetORTText(GetSpellErrorCode()),
						Behavior_TemplateManager::GetInstance().GetStateNameByID(state),
						Behavior_TemplateManager::GetInstance().GetEventNameByID(event)
					);
			}
		}

		if(INVALID_ID == nRet)
		{
			return FALSE;
		}
	}

	return nRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::IsStrickBackMonster()
{
	if(0 >= BHVParam(BHVPARAM_STRIKEBACK))
	{
		return FALSE;
	}

	return TRUE;
}

void* Behavior_Monster::getThreat(uint32_t id)
{
	auto it = this->m_ThreatList.find(id);
	if (it != m_ThreatList.end())
	{
		return it->second;
	}
	return nullptr;
}
void  Behavior_Monster::addThreat(uint32_t id, void* slot)
{
	m_ThreatList[id] = slot;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::IsNeedStrickBack(Character *pObj_Character, int32 nGoodEffect)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pObj_Character);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 >= BHVParam(BHVPARAM_STRIKEBACK))
	{
		return FALSE;
	}

	if(ESTATE_GOHOME == GetBehavior_State()->GetStateID() || ESTATE_TERROR == GetBehavior_State()->GetStateID())
	{
		return FALSE;
	}

	if(NULL == pObj_Character || pObj_Character->GetID() == GetCharacter()->GetID() || !pObj_Character->IsAlive())
	{
		return FALSE;
	}

	if(BEHAVIOR_TYPE_HOSTILITY != nGoodEffect)
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Behavior_Monster::IsJam(const GLPos &rTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character* pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pCurEnemy) return FALSE;

	/*~~~~~~~~~~~~~~*/
	BOOL bJam = FALSE;
	/*~~~~~~~~~~~~~~*/

	if (pCurEnemy->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player* pPlayer = (Player*)pCurEnemy;
		std::unordered_map<uint32_t, void*>* pTargetList = ((Behavior_Player*)pPlayer->GetAIObj())->GetTargetList();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pTargetList);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		std::unordered_map<uint32_t, void*>::iterator it = pTargetList->begin();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for (; it != pTargetList->end(); ++it)
		{
			if (INVALID_ID != it->first)
			{
				if (it->first == GetCharacter()->GetID()) continue;

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Character* pTarget = (Character*)it->second;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				KCheck(pTarget);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				float fDist = fabs(rTar.m_fX - pTarget->GetGLPos()->m_fX) + fabs(rTar.m_fZ - pTarget->GetGLPos()->m_fZ);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (fDist <= 1.0f)
				{
					bJam = TRUE;
					break;
				}
			}
		}
	}

	return(TRUE == bJam);
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::CheckJamAndRemove()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pCurEnemy = GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCurEnemy) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos pos = *GetCharacter()->GetGLPos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCurEnemy->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~*/
		int32 i;
		/*~~~~*/

		for(i = 0; i < BHV_AVOIDOVERLAPNUM; ++i)
		{
			if(FALSE == IsJam(pos)) break;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			float fDist = fabs(pos.m_fX - pCurEnemy->GetGLPos()->m_fX) + fabs(pos.m_fZ - pCurEnemy->GetGLPos()->m_fZ);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(fDist <= 3.0f)
				pos = GetRemovePos(*pCurEnemy->GetGLPos());
			else
			{
				/*~~~~~~~~~~~~~~*/
				GLPos bestPos;
				/*~~~~~~~~~~~~~~*/

				if(GetBestPos(bestPos))
					pos = GetRemovePos(bestPos);
				else
					break;
			}
		}
	}

	if(pos == *GetCharacter()->GetGLPos()) return;

	GetCharacter()->GetMap()->GetMapInfo()->VerifyPos(&pos);
	if(GetCharacter()->GetMap()->GetMapInfo()->IsCanGo(pos)) MovePhonily(pos);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
GLPos Behavior_Monster::GetRemovePos(const GLPos &rTar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos pos;
	static GLPos OffsetPos[BHV_AVOIDOVERLAPNUM];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	OffsetPos[0] = GLPos(1.414f, 0.f);
	OffsetPos[1] = GLPos(-1.414f, 0.f);
	OffsetPos[2] = GLPos(1.414f, 1.414f);
	OffsetPos[3] = GLPos(1.414f, -1.414f);
	OffsetPos[4] = GLPos(1.8f, 0.f);
	OffsetPos[5] = GLPos(-1.8f, 0.f);
	OffsetPos[6] = GLPos(0.f, 1.8f);
	OffsetPos[7] = GLPos(0.f, -1.8f);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nIndex = RandGenerator::GetRand(0, BHV_AVOIDOVERLAPNUM - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pos.m_fX = rTar.m_fX + OffsetPos[nIndex].m_fX;
	pos.m_fZ = rTar.m_fZ + OffsetPos[nIndex].m_fZ;

	return pos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::StartService(void)
{
	if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	m_uServiceTime = BHV_SERVICETIME;
	ChangeState(ESTATE_SERVICE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Behavior_Monster::StopService(void)
{
	if(ESTATE_DEAD == GetBehavior_State()->GetStateID())
	{
		return;
	}

	m_uServiceTime = 0;
	ToBHVIdle();
}
/*
=======================================================================================================================
=======================================================================================================================
*/
ObjID_t Behavior_Monster::FindNearestTeammate(int32 nRadius)
{
	return -1;
}
