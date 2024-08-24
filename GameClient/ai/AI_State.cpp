

#include "StdAfx.h"
#include "AI_State.h"
#include "AI_Base.h"
#include "AI_Player.h"
#include "kplayer.h"

#include "GameMath.h"
#include "GameTableManager.h"
#include "GameDataCharacter.h"
#include "KTable.h"
#include <GameMapPath.h>
#include "KObjectManager.h"
#include "SpellDataMgr.h"
#include "GameTime.h"
#include "kcharacter.h"
#include "OGImpactManager.h"
#include "OGBulletFlowSystemManager.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFindTargetTester.h"
#include "OGBulletOperator.h"
#include <AICommand.h>
#include <OgreRay.h>



/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState::KAIState(KAI *pAI)
{
	m_pAI = pAI;
	m_bMutexFlag.Clear();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState::CheckCharStateTime(UINT64 uCheckTime)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	UINT64	uCurrTime = GAME_TIME_PTR->GetTimeNow();
	//UINT64	uStartTime = pCharacter->GetBaseAnimStartTime();

	//if(uCurrTime - uStartTime < uCheckTime)
	//{
	//	return FALSE;
	//}

	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState::CheckMoveByTime(UINT64 uDeltaTime)
{
	static UINT64	uTime = 0;

	/*
	 * static const UINT64 uDeltaTime = 500;
	 */
	UINT64			uCurrTime = GAME_TIME_PTR->GetTimeNow();

	if(uCurrTime - uTime > uDeltaTime)
	{
		uTime = uCurrTime;
		return TRUE;
	}

	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState::SetMutexFlag(AI_COMMAND_MUTEX_TYPE eMutex)
{
	if(eMutex >= 0 && eMutex < ACMT_MAX_NUM)
	{
		BOOL bUpdate = TRUE;
		m_bMutexFlag.UpdateBits(eMutex, bUpdate);
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState::GetMutexFlag(AI_COMMAND_MUTEX_TYPE eMutex)
{
	if(eMutex >= 0 && eMutex < ACMT_MAX_NUM)
	{
		return m_bMutexFlag.isSetBit(eMutex);
	}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Idle::KAIState_Idle(KAI *pAI) :
	KAIState(pAI)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Move::KAIState_Move(KAI *pAI) :
	KAIState(pAI)
{
	m_bJumpInFinalNode = FALSE;
	m_bIsInterruptMove = FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Move::~KAIState_Move()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_Move::OnStateActive(const AICmd &cmd)
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)
		return AI_RES_FAILURE;	

	BOOL bJump = cmd.bParam[6];
	if (bJump)
	{
		// 人物移动状态和AI移动不配对时，需要更新目标点
		if (pCharacter->IsMoving())
		{
			m_paramMove.fTargetX = pCharacter->getPosition().x;
			m_paramMove.fTargetZ = pCharacter->getPosition().z;
		}
		// 跳
		if (OR_OK == Jump())
		{
			return AI_RES_OK;
		}
	}
	else
	{
		m_paramMove.fTargetX	= cmd.fParam[0];
		m_paramMove.fTargetZ	= cmd.fParam[1];
		m_paramMove.fModifyDist = cmd.fParam[2];
		m_paramMove.bDirectMove = cmd.bParam[3];
		m_paramMove.bStopMove	= cmd.bParam[4];
		m_paramMove.nPathShow	= cmd.nParam[5];

		if (m_paramMove.bStopMove)
		{
			// 中断移动
			if (OR_OK == StopMove())
			{
				return AI_RES_OK;
			}
		}
		else 
		{
			MoveToParam paramMove;
			paramMove.fTargetX		= m_paramMove.fTargetX;
			paramMove.fTargetZ		= m_paramMove.fTargetZ;
			paramMove.fModifyDist	= m_paramMove.fModifyDist;
			paramMove.bDirectMove	= m_paramMove.bDirectMove;
			paramMove.nPathShow		= m_paramMove.nPathShow;

			if (OR_OK == MoveTo(paramMove))
			{
				return AI_RES_OK;
			}
		}
	}	
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_Move::OnStateShutdown()
{
	m_bJumpInFinalNode = TRUE;
	m_bIsInterruptMove = FALSE;
	m_paramMove.Reset();

	KAIState::OnStateShutdown();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_Move::Update()
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return KRR_FAILED;
	}

	if (FALSE == pCharacter->IsMoving())
	{
		if(FALSE == pCharacter->IsJumping())
		{
			return KRR_FAILED;
		}
	}
	return KRR_SUCCEED;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_Move::RefreshAIStateByJump()
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)
		return FALSE;

	if (GetAI()->IsKeyMoveMode())
		return FALSE;

	if (m_paramMove.bStopMove)
	{
		if (OR_OK == StopMove())
		{
			return TRUE;
		}
	}
	else
	{
		vector2 fvCurrPos(pCharacter->getPosition().x, pCharacter->getPosition().z);
		vector2 fvTargetPos(m_paramMove.fTargetX, m_paramMove.fTargetZ);
		vector2 fvJumpBeginPos(m_fvJumpBeginPos.x, m_fvJumpBeginPos.z);

		FLOAT fDistToJumpSq = CGameMath::KLU_GetDistSq(fvJumpBeginPos, fvCurrPos);
		FLOAT fDistToTargetSq = CGameMath::KLU_GetDistSq(fvJumpBeginPos, fvTargetPos);

		// 是在最终路径上起跳的
		if (m_bJumpInFinalNode)
		{
			// 跳跃的距离小于目标距离
			if (fDistToJumpSq < fDistToTargetSq)
			{
				// 继续移动至目标点
				MoveToParam paramMove;
				paramMove.fTargetX		= m_paramMove.fTargetX;
				paramMove.fTargetZ		= m_paramMove.fTargetZ;
				paramMove.fModifyDist	= m_paramMove.fModifyDist;
				paramMove.bDirectMove	= m_paramMove.bDirectMove;
				paramMove.nPathShow		= m_paramMove.nPathShow;
				paramMove.nMoveType		= AI_MOVE_TYPE_REFRESH;
				
				if (OR_OK == MoveTo(paramMove))
				{
					return TRUE;
				}
			}
			else
			{
				// 中断移动
				if (OR_OK == StopMove())
				{
					return TRUE;
				}
			}
		}
		else
		{
			// 继续移动至目标点
			MoveToParam paramMove;
			paramMove.fTargetX		= m_paramMove.fTargetX;
			paramMove.fTargetZ		= m_paramMove.fTargetZ;
			paramMove.fModifyDist	= m_paramMove.fModifyDist;
			paramMove.bDirectMove	= m_paramMove.bDirectMove;
			paramMove.nPathShow		= m_paramMove.nPathShow;
			paramMove.nMoveType		= AI_MOVE_TYPE_REFRESH;

			if (OR_OK == MoveTo(paramMove))
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_Move::StopMove()
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}
	if(OR_LIMIT_MOVE == IsCanMove())
	{
		return OR_LIMIT_MOVE;
	}
	if (pCharacter->IsJumping())
	{
		m_bJumpInFinalNode = FALSE;
		return OR_OK;
	}
	if(GetAI()->Do_StopMove())
	{
		return OR_OK;
	}
	return OR_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_Move::MoveTo(const MoveToParam& param)
{
	KYLIN_TRY

	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)
		return OR_FAILURE;

	OPT_RESULT res = IsCanMove();
	if  (OR_OK != res)	
		return res;

	static CMapPath	pathFind;

	Ogre::Vector2 fvTargetPos(param.fTargetX, param.fTargetZ);
	Ogre::Vector2 fvMyPos(pCharacter->getPosition().x, pCharacter->getPosition().z);

	// 跳跃中
	if (pCharacter->IsJumping())
	{
		// 已经在移动中，不立即更新移动，等待跳跃结束更新状态
		if (IsMoving() || pCharacter->IsJumpMoving())
		{
			if (FALSE == pathFind.MoveTo(fvMyPos, fvTargetPos, param.fModifyDist, param.bDirectMove))
			{
				return OR_INVALID_TARGET_POS;
			}
			m_bJumpInFinalNode = FALSE;

			// 更新路点光标
			if (FALSE == param.bDirectMove)
			{
				int32 nPathCount = pathFind.GetFinalPathCount();
				if (nPathCount > 0)
				{
					const GLPos* pPos = pathFind.GetFinalPath();
					GetAI()->ShowMoveFinalPos(vector2(pPos[nPathCount-1].m_fX, pPos[nPathCount-1].m_fZ), param.bDirectMove, param.nPathShow);
				}
			}
		}
		// 要在跳跃中移动
		else
		{
			// 评估落地位置
			Ogre::Vector2 fvJumpPos = GetJumpToPos(fvTargetPos);

			// 移动一个跳跃距离
			if (FALSE == pathFind.MoveTo(fvMyPos, fvJumpPos, 0.f, TRUE))
			{
				return OR_INVALID_TARGET_POS;
			}
			if (FALSE == GetAI()->Do_Move(pathFind.GetFinalPath(), pathFind.GetFinalPathCount(), TRUE, AI_MOVE_PATH_SHOW_NOTHING, AI_MOVE_TYPE_JUMP))
			{
				return OR_FAILURE;
			}

			// 备份起跳位置
			m_fvJumpBeginPos = pCharacter->getPosition();

			// 记录是否在最后的路径上起跳
			m_bJumpInFinalNode = TRUE;

			// 更新路点光标
			if (FALSE == param.bDirectMove)
			{
				if (pathFind.MoveTo(fvMyPos, fvTargetPos, 0.f, FALSE))
				{
					int32 nPathCount = pathFind.GetFinalPathCount();
					if (nPathCount > 0)
					{
						const GLPos* pPos = pathFind.GetFinalPath();
						GetAI()->ShowMoveFinalPos(vector2(pPos[nPathCount-1].m_fX, pPos[nPathCount-1].m_fZ), param.bDirectMove, param.nPathShow);
					}
				}
			}
		}
	}
	else
	{
		// 计算路径	
		if (FALSE == pathFind.MoveTo(fvMyPos, fvTargetPos, param.fModifyDist, param.bDirectMove))
		{
			return OR_INVALID_TARGET_POS;
		}
		// 移动
		if (FALSE == GetAI()->Do_Move(pathFind.GetFinalPath(), pathFind.GetFinalPathCount(), param.bDirectMove, param.nPathShow, param.nMoveType))
		{
			return OR_FAILURE;
		}
	}
	KYLIN_CATCH("AI_MoveState::MoveTo")
	return OR_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_Move::DoJump()
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)	
		return OR_FAILURE;	

	// 已经在跳跃中
	if (pCharacter->IsJumping())
		return OR_BUSY;

	if (FALSE == pCharacter->IsCanJump())
		return OR_FAILURE;

	OPT_RESULT res = IsCanMove();
	if  (OR_OK != res)	
		return res;

	/*
		正在移动中.
		移动一个跳跃距离, 跳跃距离是评估出来的一个足够大的值。
	*/
	//if (pCharacter->IsMoving())
	//{
	//	const vector2 fvMyPos(pCharacter->getPosition().x, pCharacter->getPosition().z);

	//	int32 nMaxNodeCount = 0;
	//	int32 nNodeIndex = 0;
	//	const GLPos* pPos = pCharacter->GetCharMovePath(nMaxNodeCount, nNodeIndex);

	//	if (pPos && nMaxNodeCount > 0 && nNodeIndex >= 0 && nNodeIndex < nMaxNodeCount)
	//	{
	//		// 评估落地位置
	//		Ogre::Vector2 fvMoveNextPos(pPos[nNodeIndex].m_fX, pPos[nNodeIndex].m_fZ);
	//		Ogre::Vector2 fvJumpPos = GetJumpToPos(fvMoveNextPos);

	//		MoveToParam param;
	//		param.fTargetX		= fvJumpPos.x;
	//		param.fTargetZ		= fvJumpPos.y;
	//		param.bDirectMove	= TRUE;
	//		param.nMoveType		= AI_MOVE_TYPE_JUMP;

	//		if (OR_OK == MoveTo(param))
	//		{
	//			// 记录起跳位置
	//			m_fvJumpBeginPos = pCharacter->getPosition();

	//			// 记录是否在最后的路径上起跳
	//			m_bJumpInFinalNode = nNodeIndex == nMaxNodeCount-1;
	//		}
	//	}
	//}

	// 跳跃
	GetAI()->Do_Jump();

	return OR_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_Move::Jump()
{
	return DoJump();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_Move::OnTouchDown()
{
	// 刷新AI状态
	RefreshAIStateByJump();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
Ogre::Vector2 KAIState_Move::GetJumpToPos(const Ogre::Vector2& fvTargetPos)
{
	Ogre::Vector2 fvPos = fvTargetPos;

	KCharacter* pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)
		return fvPos;

	FLOAT fDistToTarget = CGameMath::KLU_GetDist(vector2(pCharacter->getPosition().x, pCharacter->getPosition().z), fvTargetPos);

	// temp...
	FLOAT fMoveDist = 20.f;//pCharacter->GetCharacterData()->Get_MoveSpeed() + 2.f;

	FLOAT fDistX = fMoveDist * (fvTargetPos.x - pCharacter->getPosition().x) / fDistToTarget;
	FLOAT fDistZ = fMoveDist * (fvTargetPos.y - pCharacter->getPosition().z) / fDistToTarget;

	fvPos.x = pCharacter->getPosition().x + fDistX;
	fvPos.y = pCharacter->getPosition().z + fDistZ;

	return fvPos;
}


/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_Move::IsCanMove()
{
	if(NULL == GetAI())
		return OR_LIMIT_MOVE;

	if (GetAI()->IsCanMove())
	{
		return OR_OK;
	}
	return OR_LIMIT_MOVE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_Move::IsMoving()
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)
		return FALSE;

	BOOL bIsMoving = FALSE;

	if (pCharacter->IsMoving())
	{
		bIsMoving = TRUE;
	}
	/*else if (AI_STATE_MOVE == GetAI()->GetMySelfAI())
	{
		bIsMoving = TRUE;
	}*/
	return bIsMoving;
}



/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_CombatState::KAIState_CombatState(KAI *pAI) :
	KAIState_Move(pAI)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_CombatState::~KAIState_CombatState()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_CombatState::OnStateActive(const AICmd &cmd)
{
	m_paramSkill.Reset();

	m_paramSkill.nSkillID		= cmd.nParam[0];
	m_paramSkill.nTargetID		= cmd.nParam[1];
	m_paramSkill.guidTarget		= cmd.uParam[2];
	m_paramSkill.fTargetX		= cmd.fParam[3];
	m_paramSkill.fTargetZ		= cmd.fParam[4];
	m_paramSkill.fDir			= cmd.fParam[5];

	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return AI_RES_FAILURE;
	}

	/*const SkillDetail* pSkill = pCharacter->GetSkill(m_paramSkill.nSkillID);
	if (NULL == pSkill)
	{
		return AI_RES_FAILURE;
	}
	m_paramSkill.fMaxRange = pSkill->GetSkillMaxRange();
	m_paramSkill.fMinRange = pSkill->GetSkillMinRange();*/


	OPT_RESULT res = UseSkill(m_paramSkill);

	if (m_paramBHV_UseSkill.IsCurrSkillEnable() || m_paramBHV_UseSkill.IsAutoSkillEnalbe())
	{
		/* 当前有技能正在生效中 */
		return AI_RES_OK;
	}

	//if(OR_OK == res)
	//{
	//	/* 聚气引导技能中断其他AI状态 */
	//	if(SKILL_TYPE_GATHER == pSkill->m_pDefine->m_nType || SKILL_TYPE_LEAD == pSkill->m_pDefine->m_nType)
	//	{
	//		return AI_RES_OK;
	//	}
	//	// 瞬发技能不中断其他AI状态
	//	else if (SKILL_TYPE_LAUNCH == pSkill->m_pDefine->m_nType && FALSE == pSkill->m_pDefine->m_bAutoRedo)
	//	{
	//		return AI_RES_OK_BUT_NO_CHANGE;
	//	}
	//	return AI_RES_OK_AND_SHUTDOWN;
	//}
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_CombatState::OnStateShutdown()
{
	m_paramBHV_UseSkill.Reset();
	m_paramSkill.Reset();

	KAIState_Move::OnStateShutdown();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_CombatState::Update(void)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if (NULL == pCharacter)
	{
		return KRR_FAILED;
	}

	if (NULL == pCharacter->GetCharacterData())
	{
		return KRR_FAILED;
	}

	if (pCharacter->IsLogicLocked())
	{
		return KRR_SUCCEED;
	}

	/* 技能结束标示 */
	BOOL bAutoFinish = TRUE;
	BOOL bCurrFinish = TRUE;

	///* 点选技能 */
	//if (m_paramBHV_UseSkill.IsCurrSkillEnable())
	//{
	//	/* 根据保存的技能id获取技能数据 */
	//	const SkillDetail	*pSkill = pCharacter->GetSkill(m_paramBHV_UseSkill.m_nCurrSkillID);

	//	if(pSkill && pSkill->m_pDefine)
	//	{
	//		OPT_RESULT res = AttackLogic(
	//				m_paramBHV_UseSkill.m_nCurrSkillID,
	//				m_paramBHV_UseSkill.m_nTargetID,
	//				m_paramBHV_UseSkill.m_guidTarget,
	//				m_paramBHV_UseSkill.m_fvTargetPos,
	//				m_paramBHV_UseSkill.m_fvPrevTargetPos,
	//				m_paramBHV_UseSkill.m_fDir,
	//				m_paramBHV_UseSkill.m_fMaxRange);

	//		/* 还在跑动中 */
	//		if(OR_OUT_RANGE == res)
	//		{
	//			bCurrFinish = FALSE;
	//		}
	//	}
	//}

	///* 自动技能 */
	//if(m_paramBHV_UseSkill.IsAutoSkillEnalbe())
	//{
	//	/* 根据保存的技能id获取技能数据 */
	//	const SkillDetail	*pSkill = pCharacter->GetSkill(m_paramBHV_UseSkill.m_nAutoSkillID);

	//	if(pSkill && pSkill->m_pDefine && pSkill->m_pDefine->m_bAutoRedo)
	//	{
	//		OPT_RESULT res = AttackLogic(
	//				m_paramBHV_UseSkill.m_nAutoSkillID,
	//				m_paramBHV_UseSkill.m_nTargetID,
	//				m_paramBHV_UseSkill.m_guidTarget,
	//				m_paramBHV_UseSkill.m_fvTargetPos,
	//				m_paramBHV_UseSkill.m_fvPrevTargetPos,
	//				m_paramBHV_UseSkill.m_fDir,
	//				m_paramBHV_UseSkill.m_fMaxRange);

	//		switch(res)
	//		{
	//		case OR_OK:
	//		case OR_OUT_RANGE:
	//		case OR_BUSY:
	//		case OR_COOL_DOWNING:
	//			{
	//				bAutoFinish = FALSE;
	//			}
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	if(bCurrFinish)
	{
		m_paramBHV_UseSkill.DisableCurrSkill();
	}

	if(bAutoFinish)
	{
		m_paramBHV_UseSkill.DisableAutoSkill();
	}

	if(bAutoFinish && bCurrFinish)
	{
		return KRR_FAILED;
	}
	return KRR_SUCCEED;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_CombatState::RefreshAIStateByJump()
{
	// 重置目标备份位置
	m_paramBHV_UseSkill.m_fvPrevTargetPos.x = 0.f;
	m_paramBHV_UseSkill.m_fvPrevTargetPos.y = 0.f;
	m_paramBHV_UseSkill.m_fvPrevTargetPos.z = 0.f;

	if (FALSE == GetAI()->IsKeyMoveMode())
	{
		// 中断移动
		StopMove();
	}
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::UseSkill(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}
	if(NULL == pCharacter->GetCharacterData())
	{
		return OR_FAILURE;
	}

	/* 加锁中 */
	if(pCharacter->IsLogicLocked())
	{
		return OR_BUSY;
	}

	///* 技能有效 */
	//const SkillDetail* pSkill = pCharacter->GetSkill(skillParam.nSkillID);
	//if(NULL == pSkill)
	//{
	//	STRING strTmp = ACTION_SYS_PTR->GetOperateResult( OR_INVALID_SKILL );
	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strTmp.c_str());
	//	return OR_INVALID_SKILL;
	//}

	//if(NULL == pSkill->m_pDefine)
	//{
	//	STRING strTmp = ACTION_SYS_PTR->GetOperateResult( OR_INVALID_SKILL );
	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strTmp.c_str());
	//	return OR_INVALID_SKILL;
	//}

	///* 检测自我施法 */
	//IsUseToMySelf(skillParam);

	///* 能否使用技能 */
	//OPT_RESULT rcResult = IsCanUseSkill(skillParam);
	//if(OR_OK != rcResult)
	//{
	//	if(pSkill->m_pDefine->m_bAutoRedo && OR_INVALID_TARGET == rcResult)
	//	{
	//		return rcResult;
	//	}
	//	STRING strTmp = ACTION_SYS_PTR->GetOperateResult( rcResult );
	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strTmp.c_str());

	//	return rcResult;
	//}

	///* 触发技能 */
	//switch(pSkill->m_pDefine->m_nSelectType)
	//{
	//case SELECT_TYPE_CHARACTER:
	//case SELECT_TYPE_HUMAN_GUID:
	//	{
	//		rcResult = UseSkill_Target(skillParam);
	//	}
	//	break;
	//case SELECT_TYPE_NONE:
	//case SELECT_TYPE_DIR:
	//case SELECT_TYPE_SELF:
	//	{
	//		rcResult = UseSkill_Dir(skillParam);
	//	}
	//	break;
	//case SELECT_TYPE_POS:
	//	{
	//		rcResult = UseSkill_Pos(skillParam);
	//	}
	//	break;
	//default:
	//	rcResult = OR_INVALID_SKILL;
	//	break;
	//}

	//if(OR_OK != rcResult)
	//{
	//	if(TRUE == pSkill->m_pDefine->m_bAutoRedo && OR_INVALID_TARGET == rcResult)
	//	{
	//		return rcResult;
	//	}
	//	STRING strTmp = ACTION_SYS_PTR->GetOperateResult( rcResult );
	//	COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strTmp.c_str());

	//	return rcResult;
	//}

	///* 中断自动技能 */
	//if(pSkill->m_pDefine->m_nCanInterruptAutoShot < 0)
	//{
	//	DisableAutoSkill();
	//}

	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::UseSkill_Target(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	const SSkillData* pSkillData = GetSpellDataMgr()->GetSkillData(skillParam.nSkillID);
	if (NULL == pSkillData)
	{
		return OR_INVALID_SKILL;
	}	

	/* 该技能是否正在使用中，并且目标也一致，忽略 */
	if (skillParam.nSkillID == m_paramBHV_UseSkill.m_nCurrSkillID ||	
		skillParam.nSkillID == m_paramBHV_UseSkill.m_nAutoSkillID)
	{
		if(skillParam.nTargetID == m_paramBHV_UseSkill.m_nTargetID)
		{
			return OR_OK;
		}
	}

	///* 目标有效 */
	//KObject *pTarget = (KObject *) (OBJECT_MANAGER_PTR->FindServerObject(skillParam.nTargetID));
	//if(NULL == pTarget)
	//{
	//	return OR_INVALID_TARGET;
	//}

	///* 攻击范围内 */
	//if (CheckDistance(pCharacter->GetPosition(), pTarget->GetPosition(), skillParam.fMaxRange))
	//{
	//	// 转移类技能修正
	//	OPT_RESULT oRes = TransferModify(skillParam);
	//	if (OR_OK != oRes)
	//		return oRes;

	//	// 中断移动
	//	OPT_RESULT orRes = InterruptMoveBySkill( pSkillData );
	//	if(OR_OK != orRes)		
	//		return orRes;		

	//	/* 发送消息 */
	//	if(FALSE == pSkillData->m_bAutoRedo)
	//	{
	//		if(FALSE == GetAI()->Do_UseSkill(skillParam.nSkillID, skillParam.nTargetID, skillParam.guidTarget, 
	//										 skillParam.fTargetX, skillParam.fTargetZ,  skillParam.fDir))
	//		{
	//			return OR_FAILURE;
	//		}
	//		m_paramBHV_UseSkill.DisableCurrSkill();
	//	}
	//	/* 自动技能不立即发送 */
	//	else
	//	{
	//		return SaveSkillParam(skillParam);
	//	}
	//}

	///* 范围外 */
	//else
	//{	/* 键盘或自动移动中 */
	//	if(GetAI()->IsKeyMoveMode())
	//	{
	//		return OR_OUT_RANGE;
	//	}

	//	if(FALSE == pCharacter->IsLead() && FALSE == pCharacter->IsGather())
	//	{
	//		/* 需要移动 */
	//		MoveToParam paramMove;
	//		paramMove.fTargetX		= pTarget->GetPosition().x;
	//		paramMove.fTargetZ		= pTarget->GetPosition().z;
	//		paramMove.fModifyDist	= skillParam.fMaxRange;

	//		if (OR_OK == MoveTo(paramMove))
	//		{
	//			return SaveSkillParam(skillParam);
	//		}
	//	}
	//	else if(pSkillData->m_bAutoRedo)
	//	{
	//		return SaveSkillParam(skillParam);
	//	}
	//	return OR_OUT_RANGE;
	//}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::UseSkill_Dir(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	const SSkillData* pSkillData = GetSpellDataMgr()->GetSkillData(skillParam.nSkillID);
	if(NULL == pSkillData)
	{
		return OR_INVALID_SKILL;
	}

	/* 中断移动 */
	OPT_RESULT orRes = InterruptMoveBySkill(pSkillData);
	if(OR_OK != orRes)
	{
		return orRes;
	}

	// 转移类技能修正
	OPT_RESULT oRes = TransferModify(skillParam);
	if (OR_OK != oRes)
		return oRes;

	/* 发送消息 */
	if(FALSE == pSkillData->m_bAutoRedo)
	{
		if (FALSE == GetAI()->Do_UseSkill(skillParam.nSkillID, skillParam.nTargetID, skillParam.guidTarget,
										  skillParam.fTargetX, skillParam.fTargetZ,  skillParam.fDir))
		{
			return OR_FAILURE;
		}
		m_paramBHV_UseSkill.DisableCurrSkill();
	}
	/* 自动技能不立即发送 */
	else
	{
		return SaveSkillParam(skillParam);
	}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::UseSkill_Pos(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	const SSkillData* pSkillData = GetSpellDataMgr()->GetSkillData(skillParam.nSkillID);
	if(NULL == pSkillData)
	{
		return OR_INVALID_SKILL;
	}

	/* 攻击范围内 */
	vector3 fvTargetPos(skillParam.fTargetX, 0.f, skillParam.fTargetZ);

	if(CheckDistance(pCharacter->getPosition(), fvTargetPos, skillParam.fMaxRange))
	{
		/* 中断移动 */
		OPT_RESULT orRes = InterruptMoveBySkill(pSkillData);
		if(OR_OK != orRes)
		{
			return orRes;
		}

		/* 发送消息 */
		if(FALSE == pSkillData->m_bAutoRedo)
		{
			if (FALSE == GetAI()->Do_UseSkill(skillParam.nSkillID, skillParam.nTargetID, skillParam.guidTarget,
											  skillParam.fTargetX, skillParam.fTargetZ,  skillParam.fDir))
			{
				return OR_FAILURE;
			}
			m_paramBHV_UseSkill.DisableCurrSkill();
		}
		/* 自动技能不立即发送 */
		else
		{
			return SaveSkillParam(skillParam);
		}
	}
	/* 范围外 */
	else
	{
		/* 键盘或自动移动中 */
		if(GetAI()->IsKeyMoveMode() )
		{
			return OR_OUT_RANGE;
		}

		//if(FALSE == pCharacter->IsLead() && FALSE == pCharacter->IsGather())
		//{
		//	/* 需要移动 */
		//	MoveToParam paramMove;
		//	paramMove.fTargetX		= skillParam.fTargetX;
		//	paramMove.fTargetZ		= skillParam.fTargetZ;
		//	paramMove.fModifyDist	= skillParam.fMaxRange;

		//	if (OR_OK == MoveTo(paramMove))
		//	{
		//		return SaveSkillParam(skillParam);
		//	}
		//}
		//else if(pSkillData->m_bAutoRedo)
		//{
		//	return SaveSkillParam(skillParam);
		//}
		return OR_OUT_RANGE;
	}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::SaveSkillParam(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	const SSkillData	*pSkillData = GetSpellDataMgr()->GetSkillData(skillParam.nSkillID);
	if(NULL == pSkillData)
	{
		return OR_INVALID_SKILL;
	}

	if (pSkillData->m_bAutoRedo)	
		m_paramBHV_UseSkill.m_nAutoSkillID = skillParam.nSkillID;	
	else	
		m_paramBHV_UseSkill.m_nCurrSkillID = skillParam.nSkillID;
	
	m_paramBHV_UseSkill.m_fMaxRange  = skillParam.fMaxRange;
	m_paramBHV_UseSkill.m_fMinRange  = skillParam.fMinRange;
	m_paramBHV_UseSkill.m_fDir		= skillParam.fDir;

	switch(pSkillData->m_nSelectType)
	{
	/* 目标 */
	case SELECT_TYPE_CHARACTER:
	case SELECT_TYPE_HUMAN_GUID:
		{
			KObject *pTarget = (KObject *)KObjectManager::GetSingleton().getObject(skillParam.nTargetID);
			if(NULL == pTarget)
			{
				return OR_INVALID_TARGET;
			}
			m_paramBHV_UseSkill.m_nTargetID = skillParam.nTargetID;
			m_paramBHV_UseSkill.m_guidTarget = skillParam.guidTarget;
			m_paramBHV_UseSkill.m_fvPrevTargetPos = pTarget->getPosition();
		}
		break;
	/* 位置、方向 */
	case SELECT_TYPE_NONE:
	case SELECT_TYPE_DIR:
	case SELECT_TYPE_POS:
		{
			m_paramBHV_UseSkill.m_fvTargetPos.x = skillParam.fTargetX;
			m_paramBHV_UseSkill.m_fvTargetPos.z = skillParam.fTargetZ;			
		}
		break;
	default:
		return OR_INVALID_SKILL;
		break;
	}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::AttackLogic(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, const vector3& fvTargetPos, vector3& fvPrevPos, FLOAT fDir, FLOAT fMaxRange)

{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	///* 技能有效 */
	//const SkillDetail	*pSkill = pCharacter->GetSkill(nSkillID);
	//if(NULL == pSkill)
	//{
	//	return OR_INVALID_SKILL;
	//}
	//if(NULL == pSkill->m_pDefine)
	//{
	//	return OR_INVALID_SKILL;
	//}



	/* 检测目标 */
	vector3 fvTarget = fvTargetPos;

	//if(	SELECT_TYPE_CHARACTER == pSkill->m_pDefine->m_nSelectType	||	
	//	SELECT_TYPE_HUMAN_GUID == pSkill->m_pDefine->m_nSelectType)
	//{
	//	/* 技能的目标必须和主目标一致 */
	//	KObject *pObj = (KObject *) KObjectManager::GetSingleton().GetMainTarget();
	//	if(NULL == pObj)
	//	{
	//		return OR_INVALID_TARGET;
	//	}
	//	if(pObj->getId() != nTargetID)
	//	{
	//		return OR_INVALID_TARGET;
	//	}

	//	/* 目标有效 */
	//	KCharacter	*pTargetObj = (KCharacter *)KObjectManager::GetSingleton().getObject(nTargetID);
	//	if(NULL == pTargetObj)
	//	{
	//		return OR_INVALID_TARGET;
	//	}
	//	if(pTargetObj->IsDie())
	//	{
	//		return OR_TARGET_DIE;
	//	}
	//	fvTarget = pTargetObj->getPosition();
	//}

	FLOAT fMTDist = CGameMath::KLU_GetDist(vector2(pCharacter->getPosition().x, pCharacter->getPosition().z),vector2(fvTarget.x, fvTarget.z));

	/* 射程外 */
	if(fMTDist > fMaxRange)
	{
		if(CheckMoveByTime(500) || pCharacter->IsIdle() && CheckCharStateTime(500))
		{
			/* 目标移动超过了一定距离 */
			FLOAT fDist = CGameMath::KLU_GetDist(fvTarget, fvPrevPos);
			if(fDist > 1.f)
			{
				/* 移动到的目标位置 */
				MoveToParam paramMove;
				paramMove.fTargetX		= fvTarget.x;
				paramMove.fTargetZ		= fvTarget.z;
				paramMove.fModifyDist	= fMaxRange;

				if (OR_OK != MoveTo(paramMove))
				{
					return OR_IMPASSABLE_ZONE;
				}
				fvPrevPos = fvTarget;
			}
		}
		return OR_OUT_RANGE;
	}

	/* 射程内 */
	else
	{
		///* 某些技能需要等到休闲状态时才能释放 */
		//if(FALSE == pCharacter->IsIdle())
		//{
		//	if(	pSkill->m_pDefine->m_nRangeSkillFlag ||				/* 远程技能 */
		//		pSkill->m_pDefine->m_nType == SKILL_TYPE_GATHER ||	/* 聚气技能 */
		//		pSkill->m_pDefine->m_nType == SKILL_TYPE_LEAD)		/* 引导技能 */	
		//	{
		//		return OR_OUT_RANGE;
		//	}
		//}

		//OPT_RESULT oRes = pSkill->IsCanUse(pCharacter->getId(), nTargetID, fvTargetPos.x, fvTargetPos.z, fDir);
		//if(OR_OK != oRes)
		//	return oRes;

		///* 冲锋类技能, 检测冲锋距离 */
		//if(TRANSFER_TANTIVY == pSkill->m_pDefine->m_nTransferSkill)
		//{
		//	if (FALSE == CheckOnrushDistance(pCharacter->getPosition(), fvTargetPos))
		//		return OR_FAILURE;
		//}
		///* 使用技能 */
		//GetAI()->Do_UseSkill(nSkillID, nTargetID, guidTarget, fvTargetPos.x, fvTargetPos.z, fDir);
	}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_CombatState::CheckDistance(const vector3 &fvPos1, const vector3 &fvPos2, FLOAT fRange)
{
	/* 最大攻击范围 */
	FLOAT fMaxSkillRangeSq = fRange * fRange;

	/* 不可改成使用2D距离, 防止城墙上打城墙下的情况发生 */
	FLOAT fDistToTargetSq = CGameMath::KLU_GetDistSq(fvPos1, fvPos2);

	/* 距离不够,需要移动 */
	if(fDistToTargetSq > fMaxSkillRangeSq)
	{
		return FALSE;
	}

	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_CombatState::CheckOnrushDistance(const vector3 &fvPos1, const vector3 &fvPos2)
{
	//KCharacter	*pCharacter = GetAI()->GetCharacter();

	//if(NULL == pCharacter)
	//{
	//	return FALSE;
	//}

	//vector2					fvTargetPos(fvPos1.x, fvPos1.z);
	//vector2					fvCurrPos(fvPos2.x, fvPos2.z);
	//FLOAT fMaxDist = 29.17f + (FLOAT) (rand() % 10);	/* 随机值, 防止玩家修改作弊 */
	//std::vector<GLPos>	vSkillPathNode;

	//if(pCharacter->GetMovePath(fvCurrPos, fvTargetPos, vSkillPathNode))
	//{
	//	FLOAT fDist = 0.f;
	//	GLPos	pos1(pCharacter->getPosition().x, pCharacter->getPosition().z);

	//	/* 计算需要移动的距离 */
	//	for(uint32 i = 0; i < vSkillPathNode.size(); ++i)
	//	{
	//		GLPos	&pos2 = vSkillPathNode[i];

	//		fDist += CGameMath::KLU_GetDist(vector2(pos1.m_fX, pos1.m_fZ), vector2(pos2.m_fX, pos2.m_fZ));

	//		/* 移动的距离大于最大移动距离 */
	//		if(fDist > fMaxDist)
	//		{
	//			return FALSE;
	//		}

	//		pos1.m_fX = pos2.m_fX;
	//		pos1.m_fZ = pos2.m_fZ;
	//	}
	//}

	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::InterruptMoveBySkill(const _DBC_SPELL_DATA *pSkillData)
{
	if(NULL == pSkillData)
	{
		return OR_INVALID_SKILL;
	}

	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	/* 移动时，聚气、引导、自动技能终止移动 */
	if(pCharacter->IsMoving())
	{
		BOOL bKeyMove = GetAI()->IsKeyMoveMode();
		BOOL bAutoMove = false;

		if(SKILL_TYPE_GATHER == pSkillData->m_nType || SKILL_TYPE_LEAD == pSkillData->m_nType)
		{
			if(bKeyMove)
			{
				return OR_BUSY;
			}
			else
			{
				if(bAutoMove)
				{
					
				}
				StopMove();
			}
		}
		else if(pSkillData->m_bAutoRedo && FALSE == bKeyMove && FALSE == bAutoMove)
		{
			StopMove();
		}
	}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_CombatState::CheckSkillByTarget(int32 nSkillID, int32 nTargetID)
{
	/*KCharacter* pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	const SkillDetail* pSkill = pCharacter->GetSkill(nSkillID);
	if(NULL == pSkill)
	{
		return FALSE;
	}

	if(NULL == pSkill->m_pDefine)
	{
		return FALSE;
	}

	if (SELECT_TYPE_CHARACTER == pSkill->m_pDefine->m_nSelectType ||	
		SELECT_TYPE_HUMAN_GUID == pSkill->m_pDefine->m_nSelectType)
	{
		if (OR_OK != pSkill->IsCanUse_CheckTarget(pCharacter->GetID(), nTargetID, 0.f, 0.f, 0.f))
		{
			return FALSE;
		}
	}*/
	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::IsCanUseSkill(SkillParam &skillParam)
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return OR_FAILURE;
	}

	KCharatcterBaseData* pCharData = pCharacter->GetCharacterData();
	if(NULL == pCharData)
	{
		return OR_FAILURE;
	}

	///* 技能有效 */
	//const SSkillData* pSkillData = GetSpellDataMgr()->GetSkillData(skillParam.nSkillID);
	//if(NULL == pSkillData)
	//{
	//	return OR_INVALID_SKILL;
	//}

	//const SkillDetail* pSkill = pCharacter->GetSkill(skillParam.nSkillID);
	//if(NULL == pSkill)
	//{
	//	return OR_INVALID_SKILL;
	//}
	//if(NULL == pSkill->m_pDefine)
	//{
	//	return OR_INVALID_SKILL;
	//}

	///* 被动技能不可使用 */
	//if(SKILL_TYPE_PASSIVE == pSkill->m_pDefine->m_nType)
	//{
	//	return OR_INVALID_SKILL;
	//}

	//// 正在跳跃中
	//if (pCharacter->IsJumping())
	//{
	//	if (SKILL_TYPE_LEAD == pSkill->m_pDefine->m_nType || SKILL_TYPE_GATHER == pSkill->m_pDefine->m_nType)
	//	{
	//		return OR_BUSY;
	//	}
	//}	

	//OPT_RESULT oResult = pSkill->IsCanUse(pCharacter->GetID(), skillParam.nTargetID, skillParam.fTargetX, skillParam.fTargetZ, skillParam.fDir);
	//if(OR_OK != oResult)
	//{
	//	if(OR_COOL_DOWNING == oResult && pSkill->m_pDefine->m_bAutoRedo)
	//	{
	//		/* ...... */
	//	}
	//	else
	//	{
	//		return oResult;
	//	}
	//}

	//if (pCharacter->IsGather() || pCharacter->IsLead())
	//{
	//	/* 当前是否有技能动作正在进行 (聚气动作或引导动作) */
	//	if(FALSE == pSkill->m_pDefine->m_bAutoRedo)
	//	{
	//		return OR_BUSY;
	//	}
	//}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_CombatState::TargetChanged(int32 nTargetID)
{
	KObject* pObj = (KObject*)KObjectManager::GetSingleton().getObject(nTargetID);

	if(pObj)
	{
		if(m_paramBHV_UseSkill.IsAutoSkillEnalbe())
		{
			if(CheckSkillByTarget(m_paramBHV_UseSkill.m_nAutoSkillID, pObj->getId()))
			{
				m_paramBHV_UseSkill.m_nTargetID = pObj->getId();
			}
			else
			{
				DisableAutoSkill(TRUE);
			}
		}

		if(m_paramBHV_UseSkill.IsCurrSkillEnable())
		{
			if(CheckSkillByTarget(m_paramBHV_UseSkill.m_nCurrSkillID, pObj->getId()))
			{
				m_paramBHV_UseSkill.m_nTargetID = pObj->getId();
			}
			else
			{
				DisableCurrSkill();
			}
		}
	}
	else
	{
		/* 目标消失或死亡时，不发送消息 */
		BOOL bSend = TRUE;

		if(m_paramBHV_UseSkill.IsAutoSkillEnalbe())
		{
			KCharacter	*pCurrObj = (KCharacter *) KObjectManager::GetSingleton().getObject(m_paramBHV_UseSkill.m_nTargetID);

			if(NULL == pCurrObj)
			{
				bSend = FALSE;
			}
			else if(pCurrObj && pCurrObj->IsDie())
			{
				bSend = FALSE;
			}
		}

		DisableAutoSkill(bSend);
		DisableCurrSkill();
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_CombatState::DisableAutoSkill(BOOL bSendMessage)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return;
	}

	if(m_paramBHV_UseSkill.IsAutoSkillEnalbe())
	{
		m_paramBHV_UseSkill.DisableAutoSkill();

		if(bSendMessage)
		{
			
		}
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_CombatState::DisableCurrSkill()
{
	m_paramBHV_UseSkill.DisableCurrSkill();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_CombatState::IsUseToMySelf(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return FALSE;
	}

	//const SkillDetail	*pSkill = pCharacter->GetSkill(skillParam.nSkillID);

	///* 是否自我施法 */
	//if (pSkill && pSkill->m_pDefine &&	
	//	SELECT_TYPE_CHARACTER == pSkill->m_pDefine->m_nSelectType &&	
	//	0 < pSkill->m_pDefine->m_nFriendness)
	//{
	//	/* 按住space键时，目标换为自己 */
	//	if(INPUT_SYS_PTR->IsKeyDown(OIS::KC_LCONTROL) || INPUT_SYS_PTR->IsKeyDown(OIS::KC_RCONTROL))
	//	{
	//		skillParam.nTargetID = pCharacter->GetServerID();
	//		return TRUE;
	//	}
	//	else
	//	{
	//		KCharacter	*pTargetObj = (KCharacter *) (OBJECT_MANAGER_PTR->FindServerObject(skillParam.nTargetID));
	//		/* 目标为敌对时，目标换为自己 */
	//		if(pTargetObj)
	//		{
	//			eRELATION eCampType = GAME_OPERATE_PTR->GetCampType(pCharacter, pTargetObj);

	//			if(RELATION_ENEMY == eCampType || RELATION_INVALID == eCampType)
	//			{
	//				skillParam.nTargetID = pCharacter->GetServerID();
	//				return TRUE;
	//			}
	//		}
	//		/* 无效目标, 目标换为自己 */
	//		else
	//		{
	//			skillParam.nTargetID = pCharacter->GetServerID();
	//			return TRUE;
	//		}
	//	}
	//}
	return FALSE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAIState_CombatState::TransferModify(SkillParam &skillParam)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)	
		return OR_FAILURE;

	const SSkillData* pSkillData = GetSpellDataMgr()->GetSkillData(skillParam.nSkillID);
	if (NULL == pSkillData)	
		return OR_INVALID_SKILL;

	switch (pSkillData->m_nTransferSkill)
	{
		// 冲锋
	case TRANSFER_TANTIVY:
		{
			if(TRUE == pSkillData->m_bAutoRedo)			
				return OR_INVALID_SKILL;			

			KObject *pTarget = (KObject *) (KObjectManager::GetSingleton().getObject(skillParam.nTargetID));
			if(NULL == pTarget)			
				return OR_INVALID_TARGET;			

			/* 检测冲锋距离 */
			if(FALSE == CheckOnrushDistance(pCharacter->getPosition(), pTarget->getPosition()))			
				return OR_OUT_RANGE;			
		}
		break;
		// 后退
	case TRANSFER_RECOIL:
		{
			// 修正方向为正后方
			skillParam.fDir = pCharacter->getDirection() + KLU_PI;
		}
		break;
	default:
		break;
	}
	return OR_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ToEvent::KAIState_ToEvent(KAI *pAI) :
	KAIState_Move(pAI)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ToEvent::~KAIState_ToEvent()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_ToEvent::OnStateActive(const AICmd &cmd)
{
	int32 nEventType	= cmd.nParam[0];
	int32 nTargetID		= cmd.nParam[1];
	FLOAT fTargetPosX	= cmd.fParam[2];
	FLOAT fTargetPosZ	= cmd.fParam[3];
	LPCSTR pName		= (LPCSTR)cmd.pParam[4];
	int32 nPathShow		= cmd.nParam[5];

	return DefaultEvent(nEventType, nTargetID, fTargetPosX, fTargetPosZ, pName, nPathShow);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_ToEvent::OnStateShutdown()
{
	m_paramBHV_DefaultEvent.Reset();

	KAIState_Move::OnStateShutdown();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_ToEvent::Update(void)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)	
		return KRR_FAILED;	

	OPT_RESULT res = IsCanMove();
	if (OR_BUSY == res)
	{
		return KRR_SUCCEED;
	}
	else if (OR_OK != res)
	{
		return KRR_FAILED;
	}

	if (IsInterruptMove())
	{
		return KRR_FAILED;	
	}
	if (pCharacter->IsJumping())
	{
		return KRR_SUCCEED;
	}	

	/* 检测距离 */
	if (CheckDistance(	m_paramBHV_DefaultEvent.m_nEventType, m_paramBHV_DefaultEvent.m_nTargetID,
		m_paramBHV_DefaultEvent.m_fvPrevTargetPos.x, m_paramBHV_DefaultEvent.m_fvPrevTargetPos.z,
		m_paramBHV_DefaultEvent.m_sNpcName.c_str()))
	{
		/* 处理事件 */
		DoEvent(m_paramBHV_DefaultEvent.m_nEventType,
			m_paramBHV_DefaultEvent.m_nTargetID,
			m_paramBHV_DefaultEvent.m_fvPrevTargetPos.x,
			m_paramBHV_DefaultEvent.m_fvPrevTargetPos.z,
 			m_paramBHV_DefaultEvent.m_sNpcName.c_str());

		return KRR_FAILED;
	}
	else
	{
		/* 从新检测目标位置 */
		if(FALSE == RecheckTargetPos())
		{
			return KRR_FAILED;
		}
	}
	return KRR_SUCCEED;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ToEvent::RefreshAIStateByJump()
{
	int32 nEventType	= m_paramBHV_DefaultEvent.m_nEventType;
	int32 nTargetID		= m_paramBHV_DefaultEvent.m_nTargetID;
	FLOAT fTargetPosX	= m_paramBHV_DefaultEvent.m_fvTargetPos.x;
	FLOAT fTargetPosZ	= m_paramBHV_DefaultEvent.m_fvTargetPos.z;
	STRING strName		= m_paramBHV_DefaultEvent.m_sNpcName;
	int32 nPathShow		= m_paramBHV_DefaultEvent.m_nPathShow;

	m_paramBHV_DefaultEvent.Reset();

	if (AI_RES_FAILURE != DefaultEvent(nEventType, nTargetID, fTargetPosX, fTargetPosZ, strName.c_str(), nPathShow))
	{
		return TRUE;
	}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_ToEvent::DefaultEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if (NULL == pCharacter)
	{
		return AI_RES_FAILURE;
	}

	

	/* 检测目标 */
	if (FALSE == CheckTarget(nEventType, nTargetID, fTargetX, fTargetZ, pName, nPathShow))
	{
		return AI_RES_OK_BUT_NO_CHANGE;
	}

	/* 目标是否在范围内 */
	if (CheckDistance(nEventType, nTargetID, fTargetX, fTargetZ, pName))
	{
		/* 中断移动 */
		StopMove();

		/* 处理事件 */
		if (DoEvent(nEventType, nTargetID, fTargetX, fTargetZ, pName))
		{
			return AI_RES_OK_AND_SHUTDOWN;
		}
	}
	else
	{
		/* 移动到目标位置 */
		if (GoToTarget(nEventType, nTargetID, fTargetX, fTargetZ, pName, nPathShow))
		{
			return AI_RES_OK;
		}
	}
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ToSpeak::KAIState_ToSpeak(KAI *pAI) :
	KAIState_ToEvent(pAI)
{
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ToSpeak::~KAIState_ToSpeak()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ToSpeak::CheckTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)
{
	

	m_paramBHV_DefaultEvent.m_nEventType			= nEventType;
	m_paramBHV_DefaultEvent.m_nTargetID				= nTargetID;
	m_paramBHV_DefaultEvent.m_fvTargetPos.x			= fTargetX;
	m_paramBHV_DefaultEvent.m_fvTargetPos.z			= fTargetZ;
	m_paramBHV_DefaultEvent.m_fvPrevTargetPos.x		= fTargetX;
	m_paramBHV_DefaultEvent.m_fvPrevTargetPos.z		= fTargetZ;
	m_paramBHV_DefaultEvent.m_nPathShow				= nPathShow;

	if (pName)
	{
		m_paramBHV_DefaultEvent.m_sNpcName = pName;
	}
	else
	{
		m_paramBHV_DefaultEvent.m_sNpcName = "";
	}
	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ToSpeak::CheckDistance(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	/* 目标位置 */
	vector3 fvTarget(fTargetX, pCharacter->getPosition().y, fTargetZ);
	KObject *pTarget = (KObject *) KObjectManager::GetSingleton().getObject(nTargetID);

	if(pTarget)
	{
		fvTarget = pTarget->getPosition();
	}

	/* 范围内 */
	FLOAT fDistSq = CGameMath::KLU_GetDistSq(fvTarget, pCharacter->getPosition());	
	if(fDistSq <= MAX_CLIENT_DEFAULT_EVENT_DIST_SQ)
	{
		return TRUE;
	}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ToSpeak::GoToTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)
{
	vector3 fvTarget(fTargetX, 0.f, fTargetZ);
	KObject *pTarget = (KObject *)KObjectManager::GetSingleton().getObject(nTargetID);

	if(pTarget)
	{
		fvTarget = pTarget->getPosition();
	}

	MoveToParam paramMove;
	paramMove.fTargetX		= fvTarget.x;
	paramMove.fTargetZ		= fvTarget.z;
	paramMove.fModifyDist	= MAX_CLIENT_DEFAULT_EVENT_DIST;
	paramMove.nPathShow		= nPathShow;

	if (OR_OK == MoveTo(paramMove))
	{
		return TRUE;
	}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ToSpeak::RecheckTargetPos()
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)	
		return FALSE;	

	FLOAT fPrevToTargetSq = 0.f;
	vector3 fvTarget = m_paramBHV_DefaultEvent.m_fvPrevTargetPos;

	KObject *pTarget = (KObject *)KObjectManager::GetSingleton().getObject(m_paramBHV_DefaultEvent.m_nTargetID);
	if(pTarget)
	{
		fvTarget = pTarget->getPosition();
		fPrevToTargetSq = CGameMath::KLU_GetDistSq(fvTarget, m_paramBHV_DefaultEvent.m_fvPrevTargetPos);
	}

	/* 当目标位置变更时, 或自己进入休息状态时, 从新移动 */
	if ((CheckMoveByTime(500) && fPrevToTargetSq > 1.f) || (pCharacter->IsIdle() && CheckCharStateTime(500)))
	{
		MoveToParam paramMove;
		paramMove.fTargetX		= fvTarget.x;
		paramMove.fTargetZ		= fvTarget.z;
		paramMove.fModifyDist	= MAX_CLIENT_DEFAULT_EVENT_DIST;
		paramMove.nPathShow		= m_paramBHV_DefaultEvent.m_nPathShow;

		if (OR_OK != MoveTo(paramMove))
		{
			return FALSE;
		}
		m_paramBHV_DefaultEvent.m_fvPrevTargetPos = fvTarget;
	}
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ToSpeak::DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(nullptr == pCharacter)
	{
		return FALSE;
	}

	int32 nTempTargetID = nTargetID;
	KObject *pTarget = (KObject *)KObjectManager::GetSingleton().getObject(nTempTargetID);

	if(nullptr == pTarget)
	{
		return FALSE;
	}

	/* 触发事件 */
	switch(nEventType)
	{
	/* 对话 */
	case PLAYER_MOVE_TO_SPEAK:
		{
			GetAI()->Do_ToSpeak(nEventType, nTempTargetID);
		}
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ComposeItem::KAIState_ComposeItem(KAI *pAI) :
	KAIState_ToEvent(pAI)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ComposeItem::~KAIState_ComposeItem()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ComposeItem::DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	KCharatcterBaseData *pCharData = pCharacter->GetCharacterData();

	if(NULL == pCharData)
	{
		return FALSE;
	}

	/* 非玩家自己不可合成物品 */
	if(KObjectManager::GetSingleton().getMySelf() != pCharacter)
	{
		return FALSE;
	}

	/*if(pCharacter->IsLead() || pCharacter->IsGather())
	{
		STRING strTmp = ACTION_SYS_PTR->GetOperateResult( OR_BUSY );

		COMMAND_SYS_PTR->AddCommand(GCD_NEW_DEBUGMESSAGE, strTmp.c_str());
		return FALSE;
	}*/

	int32 guidPlatform = INVALID_ID;
	int32 find_platform = 0;

	/*
	 * 此处应检查是否满足合成之条件，如原材料，技能，配方，平台等 ;
	 * item_mix.tab
	 */
	static const CGameTable *pPrescrDBC = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_LIFEABILITY_ITEMCOMPOSE);

	if(NULL == pPrescrDBC)
	{
		KCheck(pPrescrDBC);
		return FALSE;
	}

	const _TABLE_LIFEABILITY_ITEMCOMPOSE	*pPrescrDef =
		(const _TABLE_LIFEABILITY_ITEMCOMPOSE *) pPrescrDBC->GetFieldDataByIndex(nTargetID);

	if(NULL == pPrescrDef)
	{
		KCheck(pPrescrDef);
		return FALSE;
	}

	int32 idAbility = pPrescrDef->nLifeAbility;

	/* ability.tab */
	static const CGameTable			*pLifeAbilityDBC = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_LIFEABILITY_DEFINE);
	const _TABLE_LIFEABILITY_DEFINE	*pAbilityDef =
		(const _TABLE_LIFEABILITY_DEFINE *) pLifeAbilityDBC->GetFieldDataByIndex(idAbility);

	if(NULL == pAbilityDef)
	{
		KCheck(pAbilityDef);
		return FALSE;
	}

	///* 判断等级 */
	//if(pCharData->Get_Level() < pAbilityDef->nLevelNeed)
	//{
	//	STRING strTemp = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("GMAI_Base_Info_Payer_Level_Not_Enough");

	//	COMMAND_SYS_PTR->AddCommand(GCD_PERSONAL_MESSAGE, strTemp.c_str()); /* "人物等级不够。" */

	//	return FALSE;
	//}

	///* 生活技能数据 */
	//const SCLIENT_LIFESKILL	*player_ability = pCharData->Get_LifeAbility(idAbility);

	//if(NULL == player_ability)
	//{
	//	KCheck(player_ability);
	//	return FALSE;
	//}

	//if(player_ability->m_nLevel < pPrescrDef->nLifeAbility_Level)
	//{
	//	STRING strTemp = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("GMAI_Base_Info_Payer_Skill_Level_Not_Enough");

	//	COMMAND_SYS_PTR->AddCommand(GCD_PERSONAL_MESSAGE, strTemp.c_str()); /* "技能等级不够。" */

	//	return FALSE;
	//}

	/*
	 * 操作平台 ;
	 * if( idPlatform >= 0 ) { guidPlatform = Find_Platform(idAbility);
	 * if( guidPlatform == INVALID_ID ) return false;
	 * }
	 */
	if(GetAI()->Do_ComposeItem(idAbility, nTargetID, guidPlatform))
	{
		return TRUE;
	}

	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ActiveObj::KAIState_ActiveObj(KAI *pAI) :
	KAIState_ToEvent(pAI)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_ActiveObj::~KAIState_ActiveObj()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ActiveObj::CheckTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	/* 判断目标是否存在 */
	KObject *pTarget = (KObject *) KObjectManager::GetSingleton().getObject(nTargetID);
	if(NULL == pTarget)	
		return FALSE;	

	m_paramBHV_DefaultEvent.m_nEventType		= nEventType;
	m_paramBHV_DefaultEvent.m_nTargetID			= nTargetID;
	m_paramBHV_DefaultEvent.m_fvTargetPos.x		= fTargetX;
	m_paramBHV_DefaultEvent.m_fvTargetPos.z		= fTargetZ;
	m_paramBHV_DefaultEvent.m_fvPrevTargetPos	= pTarget->getPosition();
	m_paramBHV_DefaultEvent.m_nPathShow			= nPathShow;
	m_paramBHV_DefaultEvent.m_OperationDist		= MAX_DROP_ITEM_OP_DISTANCE;

	///* 采集类型 */
	//if(OERRATE_TYPE_RESOURCE == pTarget->Operate_GetType())
	//{
	//	KOperate_Resource	*pResource = (KOperate_Resource *) (KOperateObject *) pTarget;

	//	/* 是否可以操作 */
	//	if(FALSE == pResource->Resource_CanOperation())
	//	{
	//		return FALSE;
	//	}
	//	m_paramBHV_DefaultEvent.m_OperationDist = pResource->Resource_GetOperationDistance();	/* 操作距离 */
	//}

	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ActiveObj::CheckDistance(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	FLOAT fOperationDistanceSq = m_paramBHV_DefaultEvent.m_OperationDist * m_paramBHV_DefaultEvent.m_OperationDist;
	FLOAT fToTargetDistSq = CGameMath::KLU_GetDistSq(m_paramBHV_DefaultEvent.m_fvPrevTargetPos, pCharacter->getPosition());

	if(fToTargetDistSq <= fOperationDistanceSq)
	{
		return TRUE;
	}

	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ActiveObj::DoEvent(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return FALSE;
	}

	if(GetAI()->Do_ActiveObj(nTargetID))
	{
		return TRUE;
	}

	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_ActiveObj::GoToTarget(int32 nEventType, int32 nTargetID, FLOAT fTargetX, FLOAT fTargetZ, LPCSTR pName, int32 nPathShow)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return FALSE;
	}

	KObject *pTarget = (KObject *)KObjectManager::GetSingleton().getObject(nTargetID);
	if(NULL == pTarget)
	{
		return FALSE;
	}

	//if(OERRATE_TYPE_RESOURCE == pTarget->Operate_GetType() && ((KOperate_Resource *) pTarget)->Resource_IsFish())
	//{
	//	/*
	//	 * 如果是钓鱼的话，就不用走到河里去了。 ;
	//	 * 但是也需要距离合适，如果距离不够，也不能开始钓。 ;
	//	 * SHOW_TALKMSG("距离太远！");
	//	 */
	//	return FALSE;
	//}
	//else
	//{
	//	MoveToParam paramMove;
	//	paramMove.fTargetX		= m_paramBHV_DefaultEvent.m_fvPrevTargetPos.x;
	//	paramMove.fTargetZ		= m_paramBHV_DefaultEvent.m_fvPrevTargetPos.z;
	//	paramMove.fModifyDist	= m_paramBHV_DefaultEvent.m_OperationDist;
	//	paramMove.nPathShow		= nPathShow;

	//	if (OR_OK == MoveTo(paramMove))
	//	{
	//		return TRUE;
	//	}
	//}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Follow::KAIState_Follow(KAI *pAI) :
	KAIState_Move(pAI)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Follow::~KAIState_Follow()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_Follow::OnStateActive(const AICmd &cmd)
{
	KCharacter* pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)	
		return AI_RES_FAILURE;

	int32 nTargetID = cmd.nParam[0];

	/* 不重复对一个对象进行跟随操作 */
	if(m_paramBHV_Follow.m_nTargetID == nTargetID)
	{
		return AI_RES_OK;
	}		

	m_paramBHV_Follow.m_nTargetID = nTargetID;
	m_paramBHV_Follow.m_fvPrevPos = pCharacter->getPosition();

	if (Follow(nTargetID))
	{
		return AI_RES_OK;
	}
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_Follow::OnStateShutdown()
{
	m_paramBHV_Follow.Reset();

	/*STRING strTemp = UI_SYSTEM_PTR->ParserString_NoColor_VarParam("GMAI_Base_Info_Exit_Follow_Staus");
	COMMAND_SYS_PTR->AddCommand(GCD_PERSONAL_MESSAGE, strTemp.c_str());*/

	KAIState_Move::OnStateShutdown();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_Follow::Update(void)
{
	OPT_RESULT res = IsCanMove();
	if (OR_BUSY == res)
	{
		return KRR_SUCCEED;
	}
	else if (OR_OK != res)
	{
		return KRR_FAILED;
	}

	if (FALSE == Follow(m_paramBHV_Follow.m_nTargetID))
	{
		return KRR_FAILED;
	}
	return KRR_SUCCEED;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_Follow::Follow(int32 nTargetID)
{
	OPT_RESULT res = IsCanMove();
	if (OR_BUSY == res)
	{
		return TRUE;
	}
	else if (OR_OK != res)
	{
		return FALSE;
	}

	// 跟随间隔
	if(FALSE == CheckMoveByTime(200))	
		return TRUE;	

	/*KObject *pObj = (KObject *) (OBJECT_MANAGER_PTR->FindServerObject(m_paramBHV_Follow.m_nTargetID));
	if(NULL == pObj)	
		return FALSE;
	
	if (FALSE == pObj->CheckClassType(GET_CLASS(KCharacter)))	
		return FALSE;		

	const vector3	&fTargetPos = pObj->GetPosition();
	FLOAT fDistance = CGameMath::KLU_GetDist(m_paramBHV_Follow.m_fvPrevPos, fTargetPos);

	if (fDistance >= 1.f)
	{
		MoveToParam paramMove;
		paramMove.fTargetX		= pObj->GetPosition().x;
		paramMove.fTargetZ		= pObj->GetPosition().z;
		paramMove.fModifyDist	= 1.5f;

		if (OR_OK != MoveTo(paramMove))
		{
			return FALSE;
		}
		m_paramBHV_Follow.m_fvPrevPos = pObj->GetPosition();
	}*/
	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAIState_Follow::RefreshAIStateByJump()
{
	m_paramBHV_Follow.m_fvPrevPos.x = 0.f;
	m_paramBHV_Follow.m_fvPrevPos.y = 0.f;
	m_paramBHV_Follow.m_fvPrevPos.z = 0.f;

	if (Follow(m_paramBHV_Follow.m_nTargetID))
	{
		return TRUE;
	}
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Dead::KAIState_Dead(KAI *pAI) :
	KAIState(pAI)
{
	SetMutexFlag(ACMT_IDLE);
	SetMutexFlag(ACMT_MOVE);
	SetMutexFlag(ACMT_USE_SKILL);
	SetMutexFlag(ACMT_ACTIVE_OBJ);
	SetMutexFlag(ACMT_TOSPEAK);
	SetMutexFlag(ACMT_DEAD);
	SetMutexFlag(ACMT_FOLLOW);
	SetMutexFlag(ACMT_COMPOSE_ITEM);
	SetMutexFlag(ACMT_STALL);
	SetMutexFlag(ACMT_TREASUREBOX);
	SetMutexFlag(ACMT_USE_ITEM);
	SetMutexFlag(ACMT_JUMP);
	SetMutexFlag(ACMT_MOUNT);
	SetMutexFlag(ACMT_DISMOUNT);
	SetMutexFlag(ACMT_CHANGE_SPEED);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Dead::~KAIState_Dead()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_Dead::OnStateActive(const AICmd &cmd)
{
	if(Update())
	{
		return AI_RES_OK;
	}
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_Dead::OnStateShutdown()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_Dead::Update(void)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();
	if(NULL == pCharacter)
	{
		return KRR_FAILED;
	}

	if(pCharacter->IsDie())
	{
		return KRR_SUCCEED;
	}

	return KRR_FAILED;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Stall::KAIState_Stall(KAI *pAI) :
	KAIState_Move(pAI)
{
	SetMutexFlag(ACMT_IDLE);
	SetMutexFlag(ACMT_MOVE);
	SetMutexFlag(ACMT_USE_SKILL);
	SetMutexFlag(ACMT_ACTIVE_OBJ);
	SetMutexFlag(ACMT_TOSPEAK);
	SetMutexFlag(ACMT_FOLLOW);
	SetMutexFlag(ACMT_COMPOSE_ITEM);
	//SetMutexFlag(ACMT_STALL);
	SetMutexFlag(ACMT_TREASUREBOX);
	SetMutexFlag(ACMT_USE_ITEM);
	SetMutexFlag(ACMT_JUMP);
	SetMutexFlag(ACMT_MOUNT);
	SetMutexFlag(ACMT_DISMOUNT);
	SetMutexFlag(ACMT_CHANGE_SPEED);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_Stall::~KAIState_Stall()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_Stall::OnStateActive(const AICmd &cmd)
{
	StopMove();

	if(Update())
	{
		return AI_RES_OK;
	}
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_Stall::OnStateShutdown()
{
	KAIState_Move::OnStateShutdown();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_Stall::Update(void)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return KRR_FAILED;
	}

	if(pCharacter->GetCharacterData()->Get_IsInStall())
	{
		return KRR_SUCCEED;
	}

	return KRR_FAILED;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_TreasureBox::KAIState_TreasureBox(KAI *pAI) :
	KAIState_Move(pAI)
{
	SetMutexFlag(ACMT_IDLE);
	SetMutexFlag(ACMT_MOVE);
	SetMutexFlag(ACMT_USE_SKILL);
	SetMutexFlag(ACMT_ACTIVE_OBJ);
	SetMutexFlag(ACMT_TOSPEAK);
	SetMutexFlag(ACMT_FOLLOW);
	SetMutexFlag(ACMT_COMPOSE_ITEM);
	SetMutexFlag(ACMT_STALL);
	SetMutexFlag(ACMT_TREASUREBOX);
	SetMutexFlag(ACMT_USE_ITEM);
	SetMutexFlag(ACMT_JUMP);
	SetMutexFlag(ACMT_MOUNT);
	SetMutexFlag(ACMT_DISMOUNT);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState_TreasureBox::~KAIState_TreasureBox()
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAIState_TreasureBox::OnStateActive(const AICmd &cmd)
{
	StopMove();

	if(Update())
	{
		return AI_RES_OK;
	}
	return AI_RES_FAILURE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAIState_TreasureBox::OnStateShutdown()
{
	KAIState_Move::OnStateShutdown();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAIState_TreasureBox::Update(void)
{
	KCharacter	*pCharacter = GetAI()->GetCharacter();

	if(NULL == pCharacter)
	{
		return KRR_FAILED;
	}

	return KRR_FAILED;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AISStateList::AISStateList()
{
	for(int32 i = 0; i < ACMT_MAX_NUM; ++i)
	{
		m_pStateList[i] = NULL;
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AISStateList::~AISStateList()
{
	ReleaseState();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void AISStateList::InitStateList(KAI *pAI)
{
	RegisterState(new KAIState_Idle(pAI));
	RegisterState(new KAIState_Move(pAI));
	RegisterState(new KAIState_CombatState(pAI));
	RegisterState(new KAIState_ToSpeak(pAI));
	RegisterState(new KAIState_ComposeItem(pAI));
	RegisterState(new KAIState_ActiveObj(pAI));
	RegisterState(new KAIState_Follow(pAI));
	RegisterState(new KAIState_Dead(pAI));
	RegisterState(new KAIState_Stall(pAI));
	RegisterState(new KAIState_TreasureBox(pAI));
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void AISStateList::RegisterState(KAIState *pState)
{
	if(NULL == pState)	
		return;	

	int32 nType = pState->GetStateType();

	if(nType >= 0 && nType < ACMT_MAX_NUM)
	{
		m_pStateList[nType] = pState;
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void AISStateList::ReleaseState()
{
	for(int32 i = 0; i < ACMT_MAX_NUM; ++i)
	{
		if(m_pStateList[i])
		{
			m_pStateList[i]->Release();
			KSafeDelete(m_pStateList[i]);
		}
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState * AISStateList::GetStateInstance(AI_STATE eState) const
{
	if(eState >= 0 && eState < ACMT_MAX_NUM)
	{
		return m_pStateList[eState];
	}
	return NULL;
}
