#include "StdAfx.h"
#include "AI_Player.h"
#include "AICommand.h"
#include "GameTime.h"
#include "SpellDataMgr.h"
#include "OGImpactManager.h"
#include "OGBulletFlowSystemManager.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFindTargetTester.h"
#include "OGBulletOperator.h"
#include "DirectlyEffectMgr.h"
#include "game_scene_manager.h"
#include "net_manager.h"
#include "kplayer.h"
#include "GameDataCharacter.h"
#include "KObjectManager.h"
#include "engine_manager.h"
#include "net_message_manager.h"
#include "struct/GameDataStructSkill.h"
#include "AI_State.h"
#include "kcharacter.h"
#include "Util.h"
#include "utils/GameMath.h"
#include "net/messages/CSCharUseSkill.h"
#include "net/messages/CSCharMove.h"
#include "net/net_message_manager.h"
#include "net/messages/CSQueryEvent.h"
#include "client_message.pb.h"


#include <OgreRay.h>



#define USE_SKILL_FORBID_TIME	(200)

#define KEY_MOVE_DIST			(3.f)
#define MOVE_COOLDOWN			(100)
#define PATH_LINE_MAX_DIST		(60.f)
#define PATH_LINE_EFFECT_DIST	(3.f)

#define COMMUN_NUM			100

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAI_Player::KAI_Player()
{
	Reset();
	m_bLastObjConnectedBySelf = TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAI_Player::~KAI_Player( void )
{
	Reset();
	m_vPathEffectBuffer.clear();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::Reset(void)
{
	ShutDownAI();

	m_SaveCommand.Release();

	m_uCmdForbidTime			= 0;
	m_uCmdForbidStartTime		= 0;
	m_nMovePathRequestCount		= 0;
	m_uSkillSendTime			= 0;
	m_uMoveForbidTime			= 0;
	m_uMoveForbidStartTime		= 0;
	m_pCharacterObj				= NULL;

	m_ConnectDate.Reset();
	m_NextConnectDate.Reset();

	m_bKeyMoveMode			= FALSE;
	m_bKeyMoveForbid		= FALSE;
	m_bCreatePathEffect		= FALSE;
	m_nCurrPathIndex		= 0;
	
	m_MovePathList.clear();
	RemovePathEffect();

	ResetKeyState();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAI_Player::Update(float deltatime)
{
	// Obj连接
	Update_Connect();

	// 指令
	Update_Command();

	// 键盘移动
	Update_KeyMove();

	// 更新路线特效
	Update_PathEffect();


	updateTick(deltatime);
	return KAI::Update();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::Update_Command()
{
	// 指令禁止时间
	if (m_uCmdForbidTime > 0)
	{
		if (GAME_TIME_PTR->GetTimeNow() - m_uCmdForbidStartTime >= m_uCmdForbidTime)
		{
			m_uCmdForbidTime = 0;
		}
	}

	if (0 != m_uCmdForbidTime)
	{
		return;
	}

	// 判断是否有未执行的指令
	if (AI_CMD_UNKOWN == m_SaveCommand.m_wID)
	{
		return;
	}	
	
	eRUN_CMD_RESULT_CODE res = IsLimitCmd( &m_SaveCommand );
	if (RC_ERROR == res)
	{
		m_SaveCommand.m_wID = AI_CMD_UNKOWN;
	}
	else if (RC_OK == res)
	{
		eRUN_CMD_RESULT_CODE rcResult = Handle_Command( &m_SaveCommand );
		if (RC_WAIT != rcResult)
		{
			m_SaveCommand.m_wID = AI_CMD_UNKOWN;
		}
	}	
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SetCmdForbidTime(uint32 nForbidTime)
{
	m_uCmdForbidTime = nForbidTime;
	m_uCmdForbidStartTime = GAME_TIME_PTR->GetTimeNow();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SetMoveForbidTime(uint32 nForbidTime)
{
	m_uMoveForbidTime = nForbidTime;
	m_uMoveForbidStartTime = GAME_TIME_PTR->GetTimeNow();
}


/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_Idle()
{
	AICmd cmdTemp;
	cmdTemp.m_wID = AI_CMD_IDLE;

	return AddCommand(&cmdTemp);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_MoveTo(FLOAT fDestX, FLOAT fDestZ, BOOL bDirectMove, BOOL bShowPath, BOOL bShowCursor)
{
	AICmd cmdTemp;
	cmdTemp.m_wID		= AI_CMD_MOVE;
	cmdTemp.fParam[0]	= fDestX;
	cmdTemp.fParam[1]	= fDestZ;
	cmdTemp.bParam[2]	= bDirectMove;
	cmdTemp.bParam[3]	= bShowPath;
	cmdTemp.bParam[4]	= bShowCursor;

	return AddCommand(&cmdTemp);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_StopMove(BOOL bImme)
{
	AICmd cmdTemp;
	cmdTemp.m_wID		= AI_CMD_STOP_MOVE;
	cmdTemp.bParam[0]	= bImme;

	return AddCommand(&cmdTemp);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_Jump(void)
{
	AICmd cmdTemp;
	cmdTemp.m_wID = AI_CMD_JUMP;

	return AddCommand(&cmdTemp);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_UseSkill(int32 idSkill, GUID_t guidTarget, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir)
{
	AICmd cmdTemp;
	cmdTemp.m_wID		= AI_CMD_USE_SKILL;
	cmdTemp.nParam[0]	= idSkill;
	cmdTemp.nParam[1]	= idTargetObj;
	cmdTemp.fParam[2]	= fTargetX;
	cmdTemp.fParam[3]	= fTargetZ;
	cmdTemp.fParam[4]	= fDir;
	cmdTemp.uParam[5]	= guidTarget;

	return AddCommand(&cmdTemp);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */

eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_DefaultEvent(int32 nEventType, FLOAT fTargetX, FLOAT fTargetY, int32 nTargetId, LPCSTR szTargetName, BOOL bShowPath)
{
	static STRING strTargetName;// 备份目标名, 避免目标名指针失效
	if (szTargetName)
	{
		strTargetName = szTargetName;
	}
	else
	{
		strTargetName = "";
	}

	AICmd cmdTemp;
	cmdTemp.m_wID			= AI_CMD_DEFAULT_EVENT;
	cmdTemp.nParam[0]		= nEventType;
	cmdTemp.fParam[1]		= fTargetX;
	cmdTemp.fParam[2]		= fTargetY;
	cmdTemp.nParam[3]		= nTargetId;
	cmdTemp.pConstParam[4]	= strTargetName.c_str();
	cmdTemp.bParam[5]		= bShowPath;

	return AddCommand(&cmdTemp);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_ActiveTripper(int32 nObjID)
{
	AICmd cmdTemp;
	cmdTemp.m_wID		= AI_CMD_ACTIVE_TRIPPER;
	cmdTemp.nParam[0]	= nObjID;

	return AddCommand( &cmdTemp );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_Follow(int32 nTargetID)
{
	AICmd cmdTemp;
	cmdTemp.m_wID		= AI_CMD_FOLLOW;
	cmdTemp.uParam[0]	= nTargetID;

	return AddCommand( &cmdTemp );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_PickUp()
{
	AICmd cmdTemp;
	cmdTemp.m_wID = AI_CMD_PICKUP;

	return AddCommand( &cmdTemp );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_ComposeItem(int32 nPrescriptionID)
{
	AICmd cmdTemp;
	cmdTemp.m_wID		= AI_CMD_COMPOSE_ITEM;
	cmdTemp.uParam[0]	= nPrescriptionID;

	return AddCommand( &cmdTemp );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_Stall()
{
	AICmd cmd;
	cmd.m_wID = AI_CMD_STALL;

	return AddCommand( &cmd );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_OpenBox()
{
	AICmd cmd;
	cmd.m_wID = AI_CMD_OPEN_BOX;

	return AddCommand( &cmd );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand_Dead()
{
	AICmd cmd;
	cmd.m_wID = AI_CMD_DEAD;

	return AddCommand( &cmd );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
// 压入一条指令
eRUN_CMD_RESULT_CODE KAI_Player::AddCommand( const AICmd *pCmd )
{
	if (NULL == pCmd)
		return RC_ERROR;
	
	// 先清空，不管此次操作是否为空
	m_SaveCommand.m_wID = AI_CMD_UNKOWN;

	if (FALSE == IsLimitCmd(pCmd))
	{
		// 先将pCmd缓存起来
		m_SaveCommand = *pCmd;

		if (0 == m_uCmdForbidTime)
		{
			eRUN_CMD_RESULT_CODE rcResult = Handle_Command( pCmd );
			
			// 如果执行成功则将缓存清空
			if (RC_WAIT != rcResult)
			{				
				m_SaveCommand.m_wID = AI_CMD_UNKOWN;
			}
			return rcResult;
		}
		return RC_WAIT;
	}
	return RC_ERROR;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Handle_Command( const AICmd *pCmd )
{
	eRUN_CMD_RESULT_CODE rcResult = RC_OK;

	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	if (GetCharacter()->IsLogicLocked())
	{
		return RC_WAIT;
	}

	switch( pCmd->m_wID )
	{
	// 休闲
	case AI_CMD_IDLE:
		{
			rcResult = EnterState_Idle();
		}
		break;
	// 移动
	case AI_CMD_MOVE:
		{
			vector2  fv2TargetPos;
			BOOL	 bDirectMove;
			BOOL	 bShowPath;
			BOOL	 bShowCursor;

			fv2TargetPos.x	= pCmd->fParam[0];
			fv2TargetPos.y	= pCmd->fParam[1];
			bDirectMove		= pCmd->bParam[2];
			bShowPath		= pCmd->bParam[3];
			bShowCursor		= pCmd->bParam[4];
			
			rcResult = Enter_Move( fv2TargetPos.x, fv2TargetPos.y, bDirectMove, bShowPath, bShowCursor );
		}
		break;

	// 停止移动
	case AI_CMD_STOP_MOVE:
		{
			BOOL bImme = pCmd->bParam[0];

			rcResult = Enter_StopMove( bImme );
		}
		break;

	// 使用技能
	case AI_CMD_USE_SKILL:
		{
			int32			nTargetID;
			int32			nSkillID;
			GLPos	posTarget;
			FLOAT		fDir;
			GUID_t		guidTarget;			

			nSkillID		= pCmd->uParam[0];
			nTargetID		= pCmd->uParam[1];			
			posTarget.m_fX	= pCmd->fParam[2];
			posTarget.m_fZ	= pCmd->fParam[3];
			fDir			= pCmd->fParam[4];
			guidTarget		= pCmd->uParam[5];			

			rcResult = Enter_UseSkill( nSkillID, nTargetID, guidTarget,  posTarget.m_fX, posTarget.m_fZ, fDir );
		}
		break;

	case AI_CMD_ACTIVE_TRIPPER:
		{
			int32	idItemBox = pCmd->nParam[0];
			rcResult = Enter_ActiveTripperObj( idItemBox );
		}
		break;

	case AI_CMD_COMPOSE_ITEM:
		{
			int32	idPrescription = pCmd->uParam[0];
			rcResult = Enter_ComposeItem( idPrescription );
		}
		break;

	case AI_CMD_DEFAULT_EVENT:
		{
			int32	nEvent;
			int32 dwTargetID;
			FLOAT fTargetX;
			FLOAT fTargetZ;			
			LPCSTR pNpcName;
			BOOL bShowPath;

			nEvent			= pCmd->nParam[0];
			fTargetX		= pCmd->fParam[1];
			fTargetZ		= pCmd->fParam[2];
			dwTargetID		= pCmd->nParam[3];
			pNpcName		= (LPCSTR)pCmd->pConstParam[4];
			bShowPath		= pCmd->bParam[5];

			rcResult = Enter_DefaultEvent( nEvent, fTargetX, fTargetZ, dwTargetID, pNpcName, bShowPath );
		}
		break;

	case AI_CMD_JUMP:
		{
			rcResult = Enter_Jump();
		}
		break;

	case AI_CMD_FOLLOW:
		{
			ObjID_t idTargetObj = pCmd->uParam[0];
			
			rcResult = Enter_Follow( idTargetObj );
		}
		break;

	case AI_CMD_PICKUP:
		{
			rcResult = Enter_PickUpItem();
		}		
		break;

	case AI_CMD_DEAD:
		{
			rcResult = Enter_Dead();
		}
		break;

	case AI_CMD_STALL:
		{
			rcResult = Enter_Stall();
		}
		break;

	case AI_CMD_OPEN_BOX:
		{
			rcResult = Enter_OpenBox();
		}
		break;

	default:
		rcResult = RC_SKIP;
		break;
	};

	return rcResult;
}


/* --------------------------------------------------------------------------------------------
	AI逻辑Enter
-------------------------------------------------------------------------------------------- */

eRUN_CMD_RESULT_CODE KAI_Player::EnterState_Idle()
{
	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}

	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_IDLE, AICmd()))
	{
		return RC_ERROR;
	}
	return RC_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_Dead()
{
	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}

	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_DEAD, AICmd()))
	{
		return RC_ERROR;
	}

	ResetKeyState();

	return RC_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_StopMove(BOOL bImme)
{
	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	if (FALSE == GetCharacter()->IsMoving())
	{
		return RC_ERROR;
	}
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	AICmd cmd;
	// 立即中止移动, 无视同步
	if (bImme)
	{
		cmd.fParam[0] = GetCharacter()->getPosition().x;
		cmd.fParam[1] = GetCharacter()->getPosition().z;
		cmd.fParam[2] = 0.f;
		cmd.bParam[3] = TRUE;
		cmd.bParam[4] = TRUE;
		cmd.nParam[5] = 0;
		cmd.nParam[6] = FALSE;	// 跳跃标识
	}
	// 移动到当前位置, 服务器位置同步, 但会有转身现象
	else
	{		
		cmd.fParam[0] = GetCharacter()->getPosition().x;
		cmd.fParam[1] = GetCharacter()->getPosition().z;
		cmd.fParam[2] = 0.f;
		cmd.bParam[3] = TRUE;
		cmd.bParam[4] = FALSE;
		cmd.nParam[5] = 0;
		cmd.nParam[6] = FALSE;	// 跳跃标识
	}

	// 状态切换
	if (AI_RES_FAILURE != ChangeAIState(AI_STATE_MOVE, cmd))
	{
		return RC_OK;
	}
	return RC_ERROR;	
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_Move(FLOAT fTargetX, FLOAT fTargetZ, BOOL bDirectMove, BOOL bShowPath, BOOL bShowCursor)
{
	KYLIN_TRY
	UINT64 uTimeNow = GAME_TIME_PTR->GetTimeNow();
	static UINT64 s_uLastTime = 0;

	// 离开场景前在bus上时，进入场景若干时间内限制移动，目的是等bus状态等消息接收完毕. 
	if (FALSE == m_bLastObjConnectedBySelf)
	{		
	
	}	

	// 移动禁止时间
	if (m_uMoveForbidTime > 0)
	{
		if (GAME_TIME_PTR->GetTimeNow() - m_uMoveForbidStartTime < m_uMoveForbidTime)
		{
			return RC_ERROR;
		}
		m_uMoveForbidTime = 0;
	}

	// 时间间隔
	if (s_uLastTime + MOVE_COOLDOWN > uTimeNow)
	{
		return RC_WAIT;
	}
	s_uLastTime = uTimeNow;

	if (NULL == GetCharacter())
	{
		return RC_WAIT;
	}	
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	AI_MOVE_PATH_SHOW ePahtShow = AI_MOVE_PATH_SHOW_NOTHING;
	if (bShowPath && bShowCursor)
	{
		ePahtShow = AI_MOVE_PATH_SHOW_PATH_AND_CURSOR;
	}
	else if (bShowPath)
	{
		ePahtShow = AI_MOVE_PATH_SHOW_PATH;
	}
	else if (bShowCursor)
	{
		ePahtShow = AI_MOVE_PATH_SHOW_CURSOR;
	}
	
	AICmd cmd;
	cmd.fParam[0] = fTargetX;
	cmd.fParam[1] = fTargetZ;
	cmd.fParam[2] = 0.f;
	cmd.bParam[3] = bDirectMove;
	cmd.bParam[4] = FALSE;
	cmd.nParam[5] = ePahtShow;
	cmd.nParam[6] = FALSE;

	// 状态切换
	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_MOVE, cmd))
	{
		return RC_ERROR;
	}

	KYLIN_CATCH( "Enter_Move" );
	return RC_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_UseSkill(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir)
{
	KYLIN_TRY

	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}


	AICmd cmd;
	cmd.nParam[0] 	= nSkillID;
	cmd.nParam[1] 	= nTargetID;
	cmd.uParam[2]	= guidTarget;
	cmd.fParam[3] 	= fTargetX;
	cmd.fParam[4] 	= fTargetZ;
	cmd.fParam[5] 	= fDir;

	if (AI_RES_FAILURE != ChangeAIState(AI_STATE_USE_SKILL, cmd))
	{
		return RC_OK;
	}

	KYLIN_CATCH( "Enter_UseSkill" );
	return RC_ERROR;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_ActiveTripperObj( int32 nTargetID )
{
	static UINT64 uSaveTime = 0;
	UINT64 uTimeNow = GAME_TIME_PTR->GetTimeNow();
	UINT64 uSleepTime = 500;
	if(uSaveTime + uSleepTime > uTimeNow)
	{
		return RC_WAIT;
	}
	uSaveTime = uTimeNow;

	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	if (FALSE == IsMySelfObj())
	{
		return RC_ERROR;
	}
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	AICmd cmd;
	cmd.nParam[0] = INVALID_ID;
	cmd.nParam[1] = nTargetID;
	cmd.fParam[2] = 0.f;
	cmd.fParam[3] = 0.f;
	cmd.pParam[4] = (void*)"";
	cmd.nParam[5] = AI_MOVE_PATH_SHOW_NOTHING;

	if (AI_RES_FAILURE != ChangeAIState(AI_STATE_ACTIVE_OBJ, cmd))
	{
		return RC_OK;
	}
	
	return RC_ERROR;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_DefaultEvent(int32 nEvent, FLOAT fTargetX, FLOAT fTargetZ, int32 nTargetID, LPCSTR pName, BOOL bShowPath)
{
	KYLIN_TRY

	static UINT64 uSaveTime = 0;
	UINT64 uTimeNow = GAME_TIME_PTR->GetTimeNow();
	UINT64 uSleepTime = 500;
	if(uSaveTime + uSleepTime > uTimeNow)
	{
		return RC_WAIT;
	}
	uSaveTime = uTimeNow;

	if (NULL == GetCharacter())
	{
		return RC_WAIT;
	}
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	AICmd cmd;
	cmd.nParam[0] = nEvent;
	cmd.nParam[1] = nTargetID;
	cmd.fParam[2] = fTargetX;
	cmd.fParam[3] = fTargetZ;
	cmd.pParam[4] = (void*)pName;
	cmd.nParam[5] = (bShowPath) ? (AI_MOVE_PATH_SHOW_PATH_AND_CURSOR) : (AI_MOVE_PATH_SHOW_NOTHING);

	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_TOSPEAK, cmd))
	{
		return RC_ERROR;
	}

	KYLIN_CATCH( "Enter_DefaultEvent" );
	return RC_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_Follow(int32 nTargetID)
{
	KYLIN_TRY

	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}
	

	AICmd cmd;
	cmd.nParam[0] = nTargetID;
	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_FOLLOW, cmd))
	{
		return RC_ERROR;
	}


	KYLIN_CATCH( "Enter_Follow" );

	return RC_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_PickUpItem( void )
{
	static UINT64 uSaveTime = 0;
	UINT64 uTimeNow = GAME_TIME_PTR->GetTimeNow();
	UINT64 uSleepTime = 500;
	if(uSaveTime + uSleepTime > uTimeNow)
	{
		return RC_WAIT;
	}
	uSaveTime = uTimeNow;

	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	if (GetActiveAI())
	{
		if (GetActiveAI()->GetMutexFlag(ACMT_ACTIVE_OBJ))
		{
			return RC_ERROR;
		}
	}


	return RC_ERROR;	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_ComposeItem(int32 nPrescriptionID)
{
	KYLIN_TRY

	static UINT64 uSaveTime = 0;
	UINT64 uTimeNow = GAME_TIME_PTR->GetTimeNow();
	UINT64 uSleepTime = 500;
	if(uSaveTime + uSleepTime > uTimeNow)
	{
		return RC_WAIT;
	}
	uSaveTime = uTimeNow;

	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	if (FALSE == IsMySelfObj())
	{
		return RC_ERROR;
	}	
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	AICmd cmd;
	cmd.nParam[0] = INVALID_ID;
	cmd.nParam[1] = nPrescriptionID;
	cmd.fParam[2] = 0.f;
	cmd.fParam[3] = 0.f;
	cmd.pParam[4] = (void*)"";
	cmd.nParam[5] = AI_MOVE_PATH_SHOW_NOTHING;

	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_COMPOSE_ITEM, cmd))
	{
		return RC_ERROR;
	}




	KYLIN_CATCH( "Enter_ComposeItem" );

	return RC_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_Stall()
{
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}
	if (FALSE == IsMySelfObj())
	{
		return RC_ERROR;
	}

	AICmd cmd;

	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_STALL, cmd))
	{
		return RC_ERROR;
	}

	return RC_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_OpenBox()
{
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}

	AICmd cmd;
	if (AI_RES_FAILURE == ChangeAIState(AI_STATE_TREASUREBOX, cmd))
	{
		return RC_ERROR;
	}

	
	return RC_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::Enter_Jump()
{
	eRUN_CMD_RESULT_CODE res = GetControlResult();
	if (RC_OK != res)
	{
		return res;
	}
	if (NULL == GetCharacter())
	{
		return RC_ERROR;
	}
	if (FALSE == IsMySelfObj())
	{
		return RC_ERROR;
	}

	// 跳跃中
	if (GetCharacter()->IsJumping())
	{
		return RC_ERROR;
	}

	if (GetActiveAI())
	{
		GetActiveAI()->Jump();
	}
	else
	{
		// 无AI状态时，用移动激活跳跃
		AICmd cmd;
		cmd.fParam[0] = 0.f;
		cmd.fParam[1] = 0.f;
		cmd.fParam[2] = 0.f;
		cmd.bParam[3] = FALSE;
		cmd.bParam[4] = FALSE;
		cmd.nParam[5] = 0;
		cmd.nParam[6] = TRUE;	// 跳跃标识

		// 状态切换
		if (AI_RES_FAILURE == ChangeAIState(AI_STATE_MOVE, cmd))
		{
			return RC_ERROR;
		}
	}	
	return RC_OK;
}

/* --------------------------------------------------------------------------------------------
	AI逻辑
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_Move(const GLPos *pNodeList, uint32 nNodeNum, BOOL bDirectMove, int32 nPathShow, int32 nMoveType)
{
	KYLIN_TRY

	if (NULL == pNodeList)
		return FALSE;

	if (0 == nNodeNum)
		return FALSE;
	auto player = GetCharacter();
	int32 nStopLogicCount = GetMoveLogicCount();
	int32 nLogicCount = AddMoveLogicCount();

	ObjectCmd cmd;
	cmd.m_wID		= OBJ_CMD_MOVE;
	cmd.uParam[0]	= 0;
	cmd.nParam[1]	= nLogicCount;
	cmd.nParam[2]	= nNodeNum;
	cmd.pParam[3]	= (void*)pNodeList;
	cmd.bParam[4]	= FALSE;

	if (OR_OK != player->AddLocalCommand(&cmd ))
	{
		return FALSE;
	}

	// 发送移动消息
	SendMoveMessage(nStopLogicCount, GLPos(player->getPosition().x, player->getPosition().z), nLogicCount, pNodeList, 1);

	KYLIN_CATCH( "Do_Move" );
	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_StopMove()
{
	if (NULL == GetCharacter())
	{
		return FALSE;
	}
	if (FALSE == GetCharacter()->IsMoving())
	{
		return FALSE;
	}

	auto logicCount = GetMoveLogicCount();
	ObjectCmd cmdTemp;
	cmdTemp.m_wID		= OBJ_CMD_STOP_MOVE;
	cmdTemp.nParam[0]	= logicCount;
	cmdTemp.nParam[1]	= 0;
	cmdTemp.fParam[2]	= GetCharacter()->getPosition().x;
	cmdTemp.fParam[3]	= GetCharacter()->getPosition().z;
	cmdTemp.nParam[4]	= TRUE;

	if(FALSE == GetCharacter()->AddCommand( &cmdTemp ))
	{
		return FALSE;
	}

 	SendStopMoveMessage(logicCount, GLPos(GetCharacter()->getPosition().x, GetCharacter()->getPosition().z));
	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_UseSkill(int32 nSkillID, int32 nTargetID, GUID_t guidTarget, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir)
{
	
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_ToSpeak(int32 nEventType, int32 nTargetID)
{
	KCharacter* pCharacter = GetCharacter();
	if (NULL == pCharacter)
	{
		return FALSE;
	}

	//  触发事件
	switch (nEventType)
	{
		// 对话
	case PLAYER_MOVE_TO_SPEAK:
	{
		SendDefaultEventMessage(nTargetID);

		//KObjectManager::GetSingleton().SetMainTarget(nTargetID);
		//KObjectManager::GetSingleton().PlayNpcSpeak(nTargetID);// 播放对话
	}
	break;
	// bus
	case PLAYER_ENTER_CHARIOT:
	{
		SendEnterChariotMessage(nTargetID);
	}
	break;
	default:
		return FALSE;
		break;
	}

	// NPC有效，设置其自身的方向
	KObject* pTarget = (KObject*)KObjectManager::GetSingleton().getObject(nTargetID);
	/*if (pTarget && pTarget->CheckClassType(GET_CLASS(KCharacter_NPC)))
	{
		KCharacter_NPC* pNPC = (KCharacter_NPC*)pTarget;

		if (pNPC->IsCanFaceToPlayer())
		{
			pNPC->SetNeedFaceToPlayer(TRUE);
		}
	}*/
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_ComposeItem(int32 nAbilityID, int32 PrescriptionID, ObjID_t guidPlatform)
{
	SendComposeItemMessage( nAbilityID, PrescriptionID, guidPlatform);
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_ActiveObj(int32 nTargetID)
{
	
	return FALSE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::Do_Jump()
{
	KCharacter* pCharacter = GetCharacter();
	if (NULL == pCharacter)
	{
		return FALSE;
	}

	ObjectCmd cmdTemp;
	cmdTemp.m_wID		= OBJ_CMD_JUMP;
	cmdTemp.nParam[0]	= GetMoveLogicCount();
	if(FALSE == GetCharacter()->AddCommand( &cmdTemp ))
	{
		return FALSE;
	}

	int32 nMoveLogicCount = INVALID_ID;

	// 更新跳跃移动状态
	if (pCharacter->IsMoving())
	{
		nMoveLogicCount = GetMoveLogicCount();
		SetAIStateRefreshFlagByJump(TRUE);
		//pCharacter->SetJumpMove(TRUE);
	}
	else
	{
		//pCharacter->SetJumpMove(FALSE);
	}


	return TRUE;
}
/* --------------------------------------------------------------------------------------------
	向服务器发送命令
-------------------------------------------------------------------------------------------- */

void KAI_Player::SendStopMoveMessage(int32 nStopLogicCount, const GLPos& currPos)
{
	if (NULL == GetCharacter())
		return;


}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SendMoveMessage( int32 nStopLogicCount, const GLPos& currPos,
								  int32 nLogicCount,     const GLPos* pPathNode, int32 nNodeNum )
{
	if( NULL == GetCharacter() )
		return;

	if( NULL == pPathNode || 0 >= nNodeNum )
		return;

	auto myself = KObjectManager::GetSingleton().getMySelf();
	auto mapId = GameSceneManager::getSingleton().getActiveSceneId();
	auto objectId = myself->getId();
	clientmessage::MsgCharMove msg;
	msg.set_handle_id(nLogicCount);
	msg.set_object_id(objectId);
	msg.set_map_id(mapId);
	msg.set_stop_logic_count(nStopLogicCount);
	msg.set_world_x(currPos.m_fX);
	msg.set_world_y(currPos.m_fZ);
	msg.set_target_x(pPathNode->m_fX);
	msg.set_target_y(pPathNode->m_fZ);
	NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_CHAR_MOVE, &msg);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SendUseSkillMessage(
	int32 nSkillID, 
	int32 nTargetID, 
	GUID_t guidTarget, 
	FLOAT fTargetX, 
	FLOAT fTargetZ, 
	FLOAT fDir)
{
	KCharacter* pCharacter = GetCharacter();
	int32_t playerID = pCharacter->getId();

	clientmessage::MsgUseSkill msg;
	msg.set_player_id(playerID);
	msg.set_skill_id(nSkillID);
	msg.set_target_id(nTargetID);
	msg.set_guid(guidTarget);
	msg.set_target_x(fTargetX);
	msg.set_target_y(fTargetZ);
	msg.set_dir(fDir);
	msg.set_map_id(GameSceneManager::getSingleton().getActiveSceneId());
	NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_USE_SKILL, &msg);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SendComposeItemMessage( int32 idAbility, int32 idPrescription,	ObjID_t guidPlatform )
{
	

	//ENGINE_INTERFACE_PTR->AddDeubgInfo("CXCharUseAbility[%d],[%d],[%d]", idAbility, idPrescription,	guidPlatform);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SendDefaultEventMessage( int32 nTargetID )
{
	if (INVALID_ID == nTargetID)
		return;
	auto player = GetCharacter();
	auto playerId = player->getId();
	auto mapId = GameSceneManager::getSingleton().getActiveSceneId();
	
	clientmessage::MsgQueryEvent msg;
	msg.set_player_id(playerId);
	msg.set_map_id(mapId);
	msg.set_object_id(nTargetID);
	NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_QUERY_EVENT, &msg);
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SendEnterChariotMessage( int32 idTargetObj )
{
	

	//ENGINE_INTERFACE_PTR->AddDeubgInfo("CXBusApplyInto");
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::ShowMoveFinalPos(const vector2& fvPos, BOOL bDirectMove, int32 nPathShow)
{
	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::OnTouchDown()
{
 	if (NULL == GetCharacter())	
		return;

	if (FALSE == IsNeedRefreshAIStateByJump())
		return;

	SetAIStateRefreshFlagByJump(FALSE);

	if (GetActiveAI())
	{
		GetActiveAI()->OnTouchDown();
	}
	else
	{
		if (GetCharacter()->IsMoving() && IsCanMove())
		{
			if (FALSE == IsKeyMoveMode())
			{
				Do_StopMove();
			}			
		}
	}
}


/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SetSkillSendProtectTime()
{
	m_uSkillSendTime = GAME_TIME_PTR->GetTimeNow();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::CheckSkillProtectTime()
{
	UINT64 uTime = GAME_TIME_PTR->GetTimeNow();
	if (uTime >= m_uSkillSendTime + 500)
	{
		return TRUE;
	}
	return FALSE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::InterruptAllSkill()
{
	return true;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::TargetChanged()
{
	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::InterruptMoveAI()
{
	if (GetActiveAI())
	{
		GetActiveAI()->InterruptMove();
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
OPT_RESULT KAI_Player::ActivateDefaultSkill(int32 nSkillID, GUID_t guidTarget, int32 nTargetObjID, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir)
{
	
	return OR_OK;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::IsCanDo(AI_COMMAND_MUTEX_TYPE eType)
{
	if (NULL == GetCharacter())	
		return FALSE;
	
	if (GetActiveAI())
	{
		return FALSE == GetActiveAI()->GetMutexFlag(eType);
	}
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::IsHaveAction()
{
	if (NULL == GetCharacter())
		FALSE;
	
	return FALSE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
int32 KAI_Player::AddMoveLogicCount()
{
	if (NULL == GetCharacter())
		return INVALID_ID;

	//KCharacter_Me *pMySelf = (KCharacter_Me*)GetCharacter();
	/*int32 nSimulantLogicCount = pMySelf->GetSimulantLogicCount();
	if (pMySelf->GetBaseLogicCount() != nSimulantLogicCount)
	{
	nSimulantLogicCount = pMySelf->GetBaseLogicCount();
	}

	int32 nLogicCount = nSimulantLogicCount + DEF_CLIENT_LOGIC_COUNT_ADD_STEP;
	pMySelf->SetSimulantLogicCount(nLogicCount);*/

	int32 nLogicCount = GetCharacter()->GetBaseLogicCount() + DEF_CLIENT_LOGIC_COUNT_ADD_STEP;	

	return nLogicCount;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
int32 KAI_Player::GetMoveLogicCount()
{
	if (NULL == GetCharacter())
		return INVALID_ID;

	//KCharacter_Me *pMySelf = (KCharacter_Me*)GetCharacter();
	/*if (pMySelf->GetBaseLogicCount() != pMySelf->GetSimulantLogicCount())
	{
	pMySelf->SetSimulantLogicCount(pMySelf->GetBaseLogicCount());
	}*/

	return GetCharacter()->GetBaseLogicCount();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::IsCanMove()
{
	if (NULL == GetCharacter())
	{
		return FALSE;
	}
	if (NULL == GetCharacter()->GetCharacterData())
	{
		return FALSE;
	}

	if (GetCharacter()->IsLogicLocked())
	{
		return FALSE;
	}

	if (GetActiveAI() && GetActiveAI()->GetMutexFlag(ACMT_MOVE))
	{
		return FALSE;
	}

	// 有限制移动状态
	if (GetCharacter()->GetCharacterData()->IsLimitMove())
	{
		return FALSE;
	}

	if (GetCharacter()->IsAttached() || GetCharacter()->IsFollowAttach())
	{
		return FALSE;
	}

	if ( GetCharacter()->GetCharacterData()->Get_BusState())
	{
		return FALSE;
	}

	
	// temp
	auto myself = KObjectManager::GetSingleton().getMySelf();
	if (myself && myself != GetCharacter())
	{
		if (myself->GetCharacterData()->IsLimitMove())
		{
			return FALSE;
		}
	}

	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::IsLimitCmd( const AICmd *pCmd )
{
	if (NULL == pCmd)
	{
		return RC_ERROR;
	}	

	if (NULL == GetCharacter())
	{
		if (INVALID_ID != m_NextConnectDate.nConnectObjID)
		{
			return RC_WAIT;
		}
		return RC_ERROR;
	}
	return RC_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::PushMovePathBuffer( const GLPos* pPosNode, int32 nNodeNum )
{
	if (NULL == GetCharacter())
		return;

	if (NULL == pPosNode)
		return;	

	m_nMovePathRequestCount = 0;
	m_MovePathList.clear();

	if (0 >= nNodeNum)
		return;	

	for (int32 i=0; i<nNodeNum; ++i)
	{
		m_MovePathList.push_back( pPosNode[i] );
	}

	m_fvPathBeginPos   = GetCharacter()->getPosition();
	m_fvPathFinalPos.x = pPosNode[nNodeNum-1].m_fX;
	m_fvPathFinalPos.z = pPosNode[nNodeNum-1].m_fZ;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
const MovePathList* KAI_Player::GetMovePathBuffer()
{
	return &m_MovePathList;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SendMoveNode(int32 nNodeIndex, const GLPos& posCurr)
{
	if (m_MovePathList.empty())
		return;

	if (0 > nNodeIndex || nNodeIndex >= m_MovePathList.size())
		return;

	if (FALSE == IsCanMove())
	{
		return;
	}

	if (NULL == GetCharacter())
		return;	

	int32 nStopLogicCount = GetMoveLogicCount();
	int32 nLogicCount = AddMoveLogicCount();

	GetCharacter()->SetBaseLogicCount( nLogicCount );

	const GLPos& targetPos = m_MovePathList[nNodeIndex];	

	// 移动消息
	SendMoveMessage(nStopLogicCount, posCurr, nLogicCount, &targetPos, 1);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::CleanUpMovePathBuffer()
{
	m_nMovePathRequestCount = 0;
	m_MovePathList.clear();
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::DisconnectObj()
{
	if (m_pCharacterObj)
	{
		//m_pCharacterObj->AI_Disconnect();
		m_pCharacterObj = NULL;

		m_ConnectDate.Reset();
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::ConnectObj(int32 nObjID)
{
	if (INVALID_ID == nObjID)
	{
		return;
	}

	if (m_pCharacterObj && m_pCharacterObj->getId() == nObjID)
	{
		return;
	}

	KObject* pObj = (KObject*)KObjectManager::GetSingleton().getObject(nObjID);
	// 目标角色有效, 连接
	if (pObj && pObj->getObjectType()>= ObjectType_Npc)
	{
		ConnectObj((KCharacter*)pObj);
	}
	// 角色尚未创建, 先解除当前连接, 并备份目标~
	else if (NULL == pObj)
	{
		DisconnectObj();

		m_NextConnectDate.nConnectObjID = nObjID;
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::ConnectObj(KCharacter* pCharacter)
{
	if (pCharacter)
	{
		DisconnectObj();

		m_pCharacterObj = pCharacter;

		m_ConnectDate.nConnectObjID = m_pCharacterObj->getId();

		if (m_NextConnectDate.nConnectObjID == pCharacter->getId())
		{
			m_ConnectDate.nControlObjFlag = m_NextConnectDate.nControlObjFlag;
		}
		else
		{
			m_ConnectDate.nControlObjFlag = AI_CONTROL_UNKNOW;
		}
		m_NextConnectDate.Reset();
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::Update_Connect()
{
	
}

void    KAI_Player::updateTick(float deltatime)
{
	mTickDuration += deltatime;
	if (mTickDuration >= 5)
	{
		auto myself = KObjectManager::GetSingleton().getMySelf();
		auto mapId = GameSceneManager::getSingleton().getActiveSceneId();
		auto objectId = myself->getId();
		clientmessage::MsgTick msg;
		msg.set_player_id(objectId);
		msg.set_map_id(mapId);
		auto& pos = myself->getPosition();
		msg.set_player_pos_x(pos.x);
		msg.set_player_pos_y(pos.z);
		msg.set_position_x(0);
		msg.set_position_z(0);
		NetMessageManager::GetSingleton().sendNetMessage(clientmessage::CS_TICK, &msg);
		mTickDuration = 0.0f;
	}
	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SetControlOtherObjFlag(BOOL bCanControl, int32 nOtherObjID)
{
	// 当前obj的控制权设置
	if (m_ConnectDate.nConnectObjID == nOtherObjID)
	{
		m_ConnectDate.nControlObjFlag = (bCanControl) ? (AI_CONTROL_TRUE) : (AI_CONTROL_FALSE);
		m_NextConnectDate.Reset();
	}
	// 备份将要连接obj的控制权设置
	else
	{
		if (nOtherObjID != m_NextConnectDate.nConnectObjID && 
			INVALID_ID  != m_NextConnectDate.nConnectObjID &&
			g_bDebug)
		{
			KLAssert(!"SetControlOtherObjFlag ObjID error");
		}

		m_NextConnectDate.nConnectObjID   = nOtherObjID;
		m_NextConnectDate.nControlObjFlag = (bCanControl) ? (AI_CONTROL_TRUE) : (AI_CONTROL_FALSE);
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
eRUN_CMD_RESULT_CODE KAI_Player::GetControlResult()
{
	if (NULL == GetCharacter())
	{
		return RC_WAIT;
	}

	// 当前连接的不是自己时, 判断控制权
	if (KObjectManager::GetSingleton().getMySelf() != GetCharacter())
	{
		if (AI_CONTROL_UNKNOW == GetControlFlag())
		{
			return RC_WAIT;
		}
		else if (AI_CONTROL_FALSE == GetControlFlag())
		{
			return RC_ERROR;
		}
		/*if (NULL == GetCharacter()->GetRenderInterface())
		{
			return RC_WAIT;
		}
		if (FALSE == GetCharacter()->GetRenderInterface()->IsLogicModelCreate())
		{
			return RC_WAIT;
		}*/
	}
	return RC_OK;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_CONTROL_RESULT KAI_Player::GetControlFlag()
{
	return m_ConnectDate.nControlObjFlag;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SaveLeaveSceneObjState()
{
	if (GetCharacter() && KObjectManager::GetSingleton().getMySelf())
	{
		if (GetCharacter() == KObjectManager::GetSingleton().getMySelf())
		{
			m_bLastObjConnectedBySelf = TRUE;
		}
		else
		{
			m_bLastObjConnectedBySelf = FALSE;
		}
	}
	else
	{
		m_bLastObjConnectedBySelf = TRUE;
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::IsMySelfObj()
{
	if (NULL == GetCharacter())
	{
		return FALSE;
	}
	if (KObjectManager::GetSingleton().getMySelf() != GetCharacter())
	{
		return FALSE;
	}
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
	键盘移动相关
-------------------------------------------------------------------------------------------- */
void KAI_Player::SetKeyState(int32 nKeyId, BOOL bKeyUp )
{
	// 限制
	if (FALSE == CanUseKeyMove() || NULL == GetCharacter())
	{
		ResetKeyState();
		return;
	}
	// 按下
	if (FALSE == bKeyUp)
	{
		if (OIS::KC_UP == nKeyId)
		{
			m_nKeyState |= KMT_UP;										// 在按键状态中添加Up的标识
			m_nKeyMoveType = m_nKeyMoveType & KMT_LEFT_OR_RIGHT | KMT_UP;	// 先清除移动模式的Up和Down标识, 然后再添加Up标识
		}
		else if (OIS::KC_DOWN == nKeyId)
		{
			m_nKeyState |= KMT_DOWN;
			m_nKeyMoveType = m_nKeyMoveType & KMT_LEFT_OR_RIGHT | KMT_DOWN;
		}
		else if (OIS::KC_LEFT == nKeyId)
		{
			m_nKeyState |= KMT_LEFT;
			m_nKeyMoveType = m_nKeyMoveType & KMT_UP_OR_DOWN | KMT_LEFT;
		}
		else if (OIS::KC_RIGHT == nKeyId)
		{
			m_nKeyState |= KMT_RIGHT;
			m_nKeyMoveType = m_nKeyMoveType & KMT_UP_OR_DOWN | KMT_RIGHT;
		}
	}
	// 抬起
	else
	{
		if (OIS::KC_UP == nKeyId)
		{
			m_nKeyState	  &= (~(KMT_UP));				// 清除按键状态的Up标识
			m_nKeyMoveType &= (~(KMT_UP));				// 清除移动模式的Up标识
			m_nKeyMoveType |= m_nKeyState & KMT_DOWN;	// 如果在按键状态中Down标识有效, 在移动模式中添加Down标识
		}
		else if (OIS::KC_DOWN == nKeyId)
		{
			m_nKeyState   &= (~(KMT_DOWN));
			m_nKeyMoveType &= (~(KMT_DOWN));
			m_nKeyMoveType |= m_nKeyState & KMT_UP;
		}
		else if (OIS::KC_LEFT == nKeyId)
		{
			m_nKeyState   &= (~(KMT_LEFT));
			m_nKeyMoveType &= (~(KMT_LEFT));
			m_nKeyMoveType |= m_nKeyState & KMT_RIGHT;
		}
		else if (OIS::KC_RIGHT == nKeyId)
		{
			m_nKeyState   &= (~(KMT_RIGHT));
			m_nKeyMoveType &= (~(KMT_RIGHT));
			m_nKeyMoveType |= m_nKeyState & KMT_LEFT;
		}
	}

	if (KMT_INVALID != m_nKeyMoveType)
	{
		m_bKeyMoveMode = TRUE;
	}
}


/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::ResetKeyState()
{
	m_nKeyState				= 0;
	m_nKeyMoveType			= KMT_INVALID;
	m_nKeyMoveTypeBackUp	= KMT_INVALID;
	m_bKeyMoveMode			= FALSE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::StopKeyMove()
{
	if (NULL == GetCharacter())
		return;

	if (m_bKeyMoveMode)
	{
		if (GetCharacter()->IsMoving())
		{
			AddCommand_StopMove();
		}		
		ResetKeyState();
	}
}

/* --------------------------------------------------------------------------------------------
	更新移动状态
-------------------------------------------------------------------------------------------- */
void KAI_Player::Update_KeyMove( void )
{
	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
BOOL KAI_Player::CanUseKeyMove()
{
	if (m_bKeyMoveForbid)
	{
		return FALSE;
	}
	if (NULL == GetCharacter())
	{
		return FALSE;
	}
	
	// 移动限制
	if (FALSE == IsCanMove())
	{
		return FALSE;
	}
	return TRUE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
//===========================================================================================
//
// 路点特效相关

void KAI_Player::Update_PathEffect()
{
	// 创建
	if (m_bCreatePathEffect)
	{
		m_bCreatePathEffect = FALSE;
		CreateNewPathLine();		
	}
	// 更新
	UpdatePathEffect();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::UpdatePathEffect()
{
	if (m_PathEffectList.empty())
		return;

	// 添加可见路点
	UpdateVisibleEffect();

	// 修正当前特效位置
	UpdateEffectPos();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::UpdateVisibleEffect()
{
	if (m_PathEffectList.empty())
		return;

	if (m_MovePathList.empty() || NULL == GetCharacter())
	{
		RemovePathEffect();
		return;	
	}

	vector2 fvCurrPos( GetCharacter()->getPosition().x, GetCharacter()->getPosition().z );
	FLOAT fMaxDistSq = PATH_LINE_MAX_DIST * PATH_LINE_MAX_DIST;

	// 显示进入视野的特效
	PathEffectList::iterator it = m_PathEffectList.begin();
	for (; it!=m_PathEffectList.end(); ++it)
	{
		PathEffectIndex& pathIndex  = *it;

		if (INVALID_ID != pathIndex.m_nPathEffectIndex)
			continue;

		FLOAT fMeToEffectDistSq = CGameMath::KLU_GetDistSq( fvCurrPos, pathIndex.fvPos );
		if (fMeToEffectDistSq > fMaxDistSq)
			break;

		int32 nEffectIndex = GetPathEffect();
		if (INVALID_ID == nEffectIndex)
			break;

		if (FALSE == ActivatePathEffect( nEffectIndex, pathIndex.fvPos, pathIndex.fDir ))
			break;

		pathIndex.m_nPathEffectIndex = nEffectIndex;		
	}

	// 添加可见路点
	while (TRUE)
	{
		PathEffectList::reverse_iterator it = m_PathEffectList.rbegin();
		PathEffectIndex& pathLastIndex  = *it;

		int32 nNodeIndex = pathLastIndex.m_nPathNodeIndex;

		if (nNodeIndex < 0 || nNodeIndex >= m_MovePathList.size()-1)
			break;		

		FLOAT fDistSq = CGameMath::KLU_GetDistSq( vector2(m_MovePathList[nNodeIndex].m_fX, m_MovePathList[nNodeIndex].m_fZ), fvCurrPos);
		if (fDistSq >= fMaxDistSq)
			break;

		// 最后一点进入可见范围, 添加下一段路径
		int32 nNextNodeIndex = nNodeIndex + 1;
		AddPathEffect( nNextNodeIndex, vector2(m_MovePathList[nNodeIndex].m_fX, m_MovePathList[nNodeIndex].m_fZ), 
									   vector2(m_MovePathList[nNextNodeIndex].m_fX, m_MovePathList[nNextNodeIndex].m_fZ));		
	}	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::UpdateEffectPos()
{
	if (m_PathEffectList.empty())
		return;

	if (m_MovePathList.empty() || NULL == GetCharacter())
	{
		RemovePathEffect();
		return;
	}

	vector2 fvCurrPos( GetCharacter()->getPosition().x, GetCharacter()->getPosition().z );
	vector2 fvBeginPos( GetPathBeginPos().x, GetPathBeginPos().z );

	while (TRUE)
	{
		if (m_PathEffectList.empty())
			break;

		if (m_nCurrPathIndex < 0 || m_nCurrPathIndex >= m_MovePathList.size())
		{
			RemovePathEffect();
			break;;
		}		

		const vector2 fvEndPos( m_MovePathList[m_nCurrPathIndex].m_fX, m_MovePathList[m_nCurrPathIndex].m_fZ);

		if (m_nCurrPathIndex > 0)
		{
			fvBeginPos.x = m_MovePathList[m_nCurrPathIndex-1].m_fX;
			fvBeginPos.y = m_MovePathList[m_nCurrPathIndex-1].m_fZ;
		}	

		// 玩家是否在该线路上
		if (CGameMath::KLU_PointInLine( fvCurrPos, fvBeginPos, fvEndPos))
		{
			// 修正
			ModifyPathEffect( m_nCurrPathIndex, fvEndPos );
			break;
		}
		else
		{
			// 清除该路点所有特效
			ClearPathEffect( m_nCurrPathIndex );
			++m_nCurrPathIndex;
		}
	}	
}


/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::CreateNewPathLine()
{
	// 清除
	RemovePathEffect();

	if (m_MovePathList.empty() || NULL == GetCharacter())
		return;	

	vector2 fvCurrPos(GetCharacter()->getPosition().x, GetCharacter()->getPosition().z);

	// 目标点是否过近
	if (1 == m_MovePathList.size())
	{
		FLOAT fDistToSq = CGameMath::KLU_GetDistSq( vector2(m_MovePathList[0].m_fX, m_MovePathList[0].m_fZ), fvCurrPos );
		if (fDistToSq < PATH_LINE_EFFECT_DIST * PATH_LINE_EFFECT_DIST)
		{
			return;
		}
	}
	
	FLOAT fMaxDistSq = PATH_LINE_MAX_DIST * PATH_LINE_MAX_DIST;	

	// 添加路点特效
	for (int32 i=0; i<(int32)m_MovePathList.size(); ++i)
	{
		// 只添加有效距离内的路点
		AddPathEffect(i, fvCurrPos, vector2(m_MovePathList[i].m_fX, m_MovePathList[i].m_fZ) );

		FLOAT fDistSq = CGameMath::KLU_GetDistSq( vector2(m_MovePathList[i].m_fX, m_MovePathList[i].m_fZ), fvCurrPos );
		if (fDistSq >= fMaxDistSq)
			break;

		fvCurrPos.x = m_MovePathList[i].m_fX;
		fvCurrPos.y = m_MovePathList[i].m_fZ;
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::AddPathEffect(int32 nPathIndex, const vector2& fvBeginPos, const vector2& fvTargetPos)
{
	if (NULL == GetCharacter())
		return;
	
	FLOAT fToTargetDist		= CGameMath::KLU_GetDist( fvBeginPos, fvTargetPos );
	FLOAT fMeToEffectDist	= CGameMath::KLU_GetDist( vector2(GetCharacter()->getPosition().x, GetCharacter()->getPosition().z), fvBeginPos );
	FLOAT fDir				= CGameMath::KLU_GetYAngle( fvBeginPos, fvTargetPos );

	vector2 fvPos( fvBeginPos.x, fvBeginPos.y );

	while (TRUE)
	{
		PathEffectIndex pathIndex;
		pathIndex.m_nPathNodeIndex  = nPathIndex;
		pathIndex.fvPos				= fvPos;
		pathIndex.fDir				= fDir;

		// 可视范围内, 添加特效
		if (fMeToEffectDist <= PATH_LINE_MAX_DIST)
		{
			int32 nEffectIndex = GetPathEffect();
			if (INVALID_ID == nEffectIndex)
				break;

			if (FALSE == ActivatePathEffect( nEffectIndex, fvPos, fDir ))
				break;

			pathIndex.m_nPathEffectIndex = nEffectIndex;
		}
		// 范围外, 不创建特效, 只做记录
		else
		{
			pathIndex.m_nPathEffectIndex = INVALID_ID;
		}		
		m_PathEffectList.push_back(pathIndex);	

		fToTargetDist -= PATH_LINE_EFFECT_DIST;
		if (fToTargetDist < PATH_LINE_EFFECT_DIST)
			break;

		fMeToEffectDist += PATH_LINE_EFFECT_DIST;
		fvPos = CGameMath::KLU_GetTargetPos(fvPos, fvTargetPos, PATH_LINE_EFFECT_DIST);
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::RemovePathEffect()
{
	m_nCurrPathIndex = 0;

	if (m_PathEffectList.empty())
		return;

	PathEffectList::iterator it = m_PathEffectList.begin();
	for (; it!=m_PathEffectList.end(); ++it)
	{
		PathEffectIndex& pathIndex = *it;

		ShutdownPathEffect( pathIndex.m_nPathEffectIndex );
	}
	m_PathEffectList.clear();
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
int32 KAI_Player::GetPathEffect()
{
	// 查找空闲的特效
	for (int32 i=0; i<(int32)m_vPathEffectBuffer.size(); ++i)
	{
		if (FALSE == m_vPathEffectBuffer[i].m_bUsed)
		{
			return i;
		}
	}

	// 查找特效
	const _DBC_DIRECT_EFFECT* pImpact = CDirectlyEffectMgr::GetMe()->GetConstDirectlyImpact( IMPACTTYPE_PATH_LINE );
	if (NULL == pImpact)
		return INVALID_ID;

	if (0 == strlen(pImpact->m_pszEffect))
		return INVALID_ID;			
	

	return INVALID_ID;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
int32 KAI_Player::GetPathEffectID(int32 nEffectIndex)
{
	if (nEffectIndex >= 0 && nEffectIndex < m_vPathEffectBuffer.size())
	{
		return m_vPathEffectBuffer[nEffectIndex].m_nOjbEffectId;
	}
	return INVALID_ID;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::SetPathEffectUseFlag(int32 nEffectIndex, BOOL bUsed)
{
	if (nEffectIndex >= 0 && nEffectIndex < m_vPathEffectBuffer.size())
	{
		return m_vPathEffectBuffer[nEffectIndex].SetUsed(bUsed);
	}
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */

BOOL KAI_Player::ActivatePathEffect(int32 nEffectIndex, const vector2& fvPos, FLOAT fDir)
{
		

	return TRUE;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */

void KAI_Player::ShutdownPathEffect(int32 nEffectIndex)
{
	
}


/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::ModifyPathEffect(int32 nPathIndex, const vector2& fvTargetPos)
{
	
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::ClearPathEffect(int32 nPathIndex)
{
	KYLIN_TRY

	while (TRUE)
	{
		if (m_PathEffectList.empty())
			break;

		PathEffectList::iterator it = m_PathEffectList.begin();
		PathEffectIndex& pathEffectIndex  = *it;

		if (pathEffectIndex.m_nPathNodeIndex != nPathIndex)
			break;

		ShutdownPathEffect( pathEffectIndex.m_nPathEffectIndex );
		m_PathEffectList.pop_front();
	}

	KYLIN_CATCH( "ClearPathEffect" );
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI_Player::CreatePathEffect()
{
	m_bCreatePathEffect = TRUE; 
}



//===========================================================================================


