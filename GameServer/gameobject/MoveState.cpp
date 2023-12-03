/*$T MapServer/Server/Obj/HumanAssistantClass/MoveState.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "MoveState.h"
#include "Character.h"
#include "CharActionDelegator.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "net/net_message_manager.h"
#include "net/messages/SCCharMove.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

OPT_RESULT CharMoveState::OnEnterState()
{
	__GUARD__ if(FALSE == m_pOnwer->IsActiveObj())
	{
		return OR_ERROR;
	}

	if(m_pOnwer->IsDie())
	{
		return OR_DIE;
	}

	if(FALSE == GetGlobalActionDelegator().CanDoNextAction(*m_pOnwer))
	{
		GetGlobalActionDelegator().InterruptCurrentAction(*m_pOnwer);
	}

	if(TRUE == m_pOnwer->IsLimitMove())
	{
		return OR_NEED_STOP_MOVE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OPT_RESULT oRes = AddMove
		(
			m_pOnwer->m_oStatePara.nHandleID,
			m_pOnwer->m_oStatePara.wNumTargetPos,
			m_pOnwer->m_oStatePara.paTargetPos,
			m_pOnwer->m_oStatePara.nStopLogicCount,
			m_pOnwer->m_oStatePara.paCurPos,
			m_pOnwer->m_oStatePara.idSender
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return oRes;
	__UNGUARD__ return OR_ERROR;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharMoveState::OnExitState()
{
	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharMoveState::OnEvent_HeartBeat(uint32 uTime)
{
	__GUARD__ if(m_pOnwer->IsDie())
	{
		return OR_ERROR;
	}

	if(m_pOnwer->IsLimitMove())
	{
		if(m_pOnwer->GetObjType() == Object::OBJECT_CLASS_PLAYER)
		{
			m_pOnwer->m_paramLogic_Move.Reset();
		}

		return OR_ERROR;
	}

	return LogicMoveImp();

	__UNGUARD__ return OR_ERROR;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ENUM_CHARACTER_LOGIC CharMoveState::GetStateType()
{
	return CHARACTER_LOGIC_MOVE;
}


void  CharMoveState::OnStateActive()
{
	int kk = 0;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CharMoveState::Clear()
{
	CharacterState::Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharMoveState::CharMoveState()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharMoveState::~CharMoveState()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharMoveState::LogicMoveImp()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pOnwer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_pOnwer->GetMap());
	KCheck(m_pOnwer->GetMap()->GetMapInfo());

	if(m_pOnwer->m_paramLogic_Move.IsEmpty())
	{
		return OR_ERROR;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uLogicTime = m_pOnwer->GetLogicTime();
	float	fSpeed = GetSafeMoveSpeed();
	float	fMoveDist = fSpeed * uLogicTime * 0.001f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fMoveDist <= 0.01f)
	{
		return OR_OK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float		fDistToTarget = KLSqrt(m_pOnwer->GetGLPos(), m_pOnwer->m_paramLogic_Move.GetCurTargetPos());
	BOOL		bArrive = FALSE;
	GLPos	posSetToPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	posSetToPos.m_fX = m_pOnwer->GetGLPos()->m_fX;
	posSetToPos.m_fZ = m_pOnwer->GetGLPos()->m_fZ;

	if(m_pOnwer->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		
		int count = m_pOnwer->m_paramLogic_Move.GetNodeNum();
		if(count > 1)
		{
			int kk = 0; // zhousha
		}
	}

	while(TRUE)
	{
		// �ƶ��ľ��볬����ǰ��Ŀ���ľ��룬�л���һ��·��
		if(fMoveDist >= fDistToTarget)
		{
			posSetToPos.m_fX = m_pOnwer->m_paramLogic_Move.GetCurTargetPos()->m_fX;
			posSetToPos.m_fZ = m_pOnwer->m_paramLogic_Move.GetCurTargetPos()->m_fZ;

			// ��¼��ʼλ��
			m_pOnwer->m_paramLogic_Move.SetNodeStartPos(&posSetToPos);

			// �����յ�
			if(FALSE == m_pOnwer->m_paramLogic_Move.NextTargetPos())
			{
				// ����һ���ҿ��Ƶ�Obj�����赲ʱ�����ش���
				m_pOnwer->GetMap()->GetMapInfo()->VerifyPos(&posSetToPos);
				if (FALSE == m_pOnwer->GetMap()->GetMapInfo()->IsCanGo(posSetToPos))
				{
					if (m_pOnwer->GetObjType() == Object::OBJECT_CLASS_PLAYER || m_pOnwer->m_paramLogic_Move.IsIgnoreSender())
					{
						return OR_ERROR;
					}					
				}
				bArrive = TRUE;
				break;
			}
			// ��һ��·��
			else
			{
				fMoveDist -= fDistToTarget;
				fDistToTarget = KLSqrt(&posSetToPos, m_pOnwer->m_paramLogic_Move.GetCurTargetPos());

				// �л�·��ʱ������Χͬ����Ϣ���ƶ�����Ϊ��Чֵ��·�㲻����ͬ��
				if (INVALID_ID != m_pOnwer->m_paramLogic_Move.GetCurLogicCount())
				{
					m_pOnwer->SetMoveLogicCount(m_pOnwer->m_paramLogic_Move.GetCurLogicCount());

					BroatMoveMessage(m_pOnwer->m_paramLogic_Move.GetCurTargetPos(), &posSetToPos);

				}				
			}
		}
		else
		{
			if (0.f == fDistToTarget)
				break;

			GLPos	posTarget;
			posTarget.m_fX = m_pOnwer->m_paramLogic_Move.GetCurTargetPos()->m_fX;
			posTarget.m_fZ = m_pOnwer->m_paramLogic_Move.GetCurTargetPos()->m_fZ;

			GLPos	vNormalize;
			vNormalize.m_fX = (posTarget.m_fX - posSetToPos.m_fX) / fDistToTarget;
			vNormalize.m_fZ = (posTarget.m_fZ - posSetToPos.m_fZ) / fDistToTarget;

			if(fDistToTarget > 0.f)
			{
				posSetToPos.m_fX = posSetToPos.m_fX + fMoveDist * vNormalize.m_fX;
				posSetToPos.m_fZ = posSetToPos.m_fZ + fMoveDist * vNormalize.m_fZ;
			}
			else
			{
				posSetToPos.m_fX = posTarget.m_fX;
				posSetToPos.m_fZ = posTarget.m_fZ;
			}

			// ����һ���ҿ��Ƶ�Obj�����赲ʱ�����ش���
			m_pOnwer->GetMap()->GetMapInfo()->VerifyPos(&posSetToPos);
			if (FALSE == m_pOnwer->GetMap()->GetMapInfo()->IsCanGo(posSetToPos))
			{
				if (m_pOnwer->GetObjType() == Object::OBJECT_CLASS_PLAYER || m_pOnwer->m_paramLogic_Move.IsIgnoreSender())
				{
					GLPos oTempPos;
					oTempPos.m_fX = m_pOnwer->GetGLPos()->m_fX + fMoveDist * 4.f * vNormalize.m_fX;
					oTempPos.m_fZ = m_pOnwer->GetGLPos()->m_fZ + fMoveDist * 4.f * vNormalize.m_fZ;

					m_pOnwer->GetMap()->GetMapInfo()->VerifyPos(&oTempPos);
					if(FALSE == m_pOnwer->GetMap()->GetMapInfo()->IsCanGo(oTempPos))
					{
						return OR_ERROR;
					}
				}				
			}
			break;
		}
	}

	float	fDir = KLAngle(m_pOnwer->GetGLPos(), &posSetToPos);
	m_pOnwer->SetObjectDir(fDir);
	m_pOnwer->SetGLPos(&posSetToPos);

	if(bArrive)
	{
		return OR_NEED_STOP_MOVE;
	}

	return OR_OK;

	__UNGUARD__ return OR_ERROR;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharMoveState::AddMove(
	int32		nHandleID,
	uint16		wNumTargetPos,
	const GLPos *paTargetPos,
	int32		nStopLogicCount,
	const GLPos *paCurPos,
	ObjID_t		nSenderID)
{
	__GUARD__
	if (NULL == m_pOnwer)	
		return OR_ERROR;	

	if (NULL == paCurPos || INVALID_ID == nHandleID)
	{
		// ������������ƶ�������������ֵ��ƶ�
		return AfreshMove(wNumTargetPos, paTargetPos);
	}

	// �����ƶ�����
	if (FALSE == m_pOnwer->IsMoving())
	{
		m_pOnwer->m_paramLogic_Move.Reset();
		// ��¼��ʼλ��
		m_pOnwer->m_paramLogic_Move.SetNodeStartPos(m_pOnwer->GetGLPos());
	}

	BOOL bLastNode = m_pOnwer->m_paramLogic_Move.GetNodeNum() == 1;
	BOOL bHaveTarget = TRUE;
	if (NULL == paTargetPos || 0 == wNumTargetPos)
		bHaveTarget = FALSE;

	// ����·��
	if (OR_OK == ModifyMove(nStopLogicCount, paCurPos))
	{
		// �е�ǰλ�ö�û��Ŀ�����ƶ���Ϊ��ҵ�ֹͣ�ƶ�����
		if (bLastNode && FALSE == bHaveTarget)
		{
			BroatMoveMessage(nullptr, paCurPos);
		}		
	}

	if (FALSE == bHaveTarget)
	{
		return OR_OK;
	}

	// ����·�㻺������ʱ������
	if (m_pOnwer->m_paramLogic_Move.m_wNumNode + wNumTargetPos > MAX_CHAR_PATH_NODE_NUMBER)
	{
		//m_pOnwer->SendMoveResMSG(MOVE_RES_NODE_FULL);
		m_pOnwer->m_paramLogic_Move.Reset();
	}

	// �����ƶ�����
	BOOL bAfresh = m_pOnwer->m_paramLogic_Move.IsEmpty();
	if (bAfresh)
	{
		m_pOnwer->SetMoveLogicCount(nHandleID);
	}

	// ����ƶ�·��
	for (uint16 i=0; i<wNumTargetPos; ++i)
	{
		m_pOnwer->m_paramLogic_Move.AddTargetPos(&paTargetPos[i], nHandleID + i);
	}

	// ���ú��Ա�ʶ
	m_pOnwer->m_paramLogic_Move.SetIgnoreSender(TRUE);

	// �������﷽��
	const GLPos *pTargetPos = m_pOnwer->m_paramLogic_Move.GetCurTargetPos();
	float fDir = KLAngle(m_pOnwer->GetGLPos(), pTargetPos);
	m_pOnwer->SetDir(fDir);

	// ����log
	if (INVALID_ID != m_pOnwer->m_paramLogic_Move.m_nSenderID	&&	nSenderID != m_pOnwer->m_paramLogic_Move.m_nSenderID)
	{
	}

	// ��¼�ƶ�������
	m_pOnwer->m_paramLogic_Move.m_nSenderID = nSenderID;

	// ͬ���ƶ�
	if (bAfresh)
	{
		BroatMoveMessage(pTargetPos, m_pOnwer->GetGLPos());
	}
	return OR_OK;

	__UNGUARD__
	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharMoveState::ModifyMove(int32 nStopLogicCount, const GLPos *pModifyTargetPos)
{
	__GUARD__

	if (NULL == pModifyTargetPos)
		return OR_FAILURE;

	if(m_pOnwer->m_paramLogic_Move.IsEmpty())
		return OR_FAILURE;

	if (FALSE == m_pOnwer->IsMoving())
		return OR_FAILURE;

	/*
		�ǵ�ǰ�����ƶ���·��.
		���Ѿ�������Ҫ������·��λ��, ���ҳ���һ������ʱ�������һ�����ߵ�·��.
	*/
	if (nStopLogicCount == m_pOnwer->GetMoveLogicCount())
	{
		float fServerDist = KLLengthSq(m_pOnwer->m_paramLogic_Move.GetNodeStartPos(), m_pOnwer->GetGLPos());	// ��ʼλ�õ�����λ�õľ���
		float fClientDist = KLLengthSq(m_pOnwer->m_paramLogic_Move.GetNodeStartPos(), pModifyTargetPos);		// ��ʼλ�õ�����λ�õľ���

		float fDist = fServerDist - fClientDist;
		if (fDist >= 1.f)
		{
			m_pOnwer->m_paramLogic_Move.ModifyTargetPos(m_pOnwer->GetGLPos(), nStopLogicCount); // ������ǰ·��
			m_pOnwer->m_paramLogic_Move.AddTargetPos(pModifyTargetPos, INVALID_ID);				// ��Ӳ������ͬ����·��
			return OR_OK;
		}
	}

	// ������ǰĿ���λ��
	float fDist = KLLengthSq(pModifyTargetPos, m_pOnwer->m_paramLogic_Move.GetCurTargetPos());
	if (fDist > 0.01f)
	{		
		m_pOnwer->m_paramLogic_Move.ModifyTargetPos(pModifyTargetPos, nStopLogicCount);
		return OR_OK;
	}

	return OR_FAILURE;	
	__UNGUARD__
	return OR_FAILURE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT CharMoveState::AfreshMove(uint16 wNumTargetPos, const GLPos *paTargetPos)
{
	__GUARD__ m_pOnwer->m_paramLogic_Move.Reset();

	if(NULL == paTargetPos || 0 == wNumTargetPos)
	{
		return OR_OK;
	}

	// �ƶ�����������
	m_pOnwer->AddMoveLogicCount();

	// ����ƶ�·��
	for(uint16 i = 0; i < wNumTargetPos; ++i)
	{
		m_pOnwer->m_paramLogic_Move.AddTargetPos(&paTargetPos[i], m_pOnwer->GetMoveLogicCount() + i);
	}

	// ���ú��Ա�ʶ
	m_pOnwer->m_paramLogic_Move.SetIgnoreSender(FALSE);
	const GLPos *pTargetPos = m_pOnwer->m_paramLogic_Move.GetCurTargetPos();

	// �������﷽��
	float fDir = KLAngle(m_pOnwer->GetGLPos(), pTargetPos);	
	m_pOnwer->SetDir(fDir);

	// ��¼��ʼλ��
	m_pOnwer->m_paramLogic_Move.SetNodeStartPos(m_pOnwer->GetGLPos());

	// ͬ���ƶ�
	
	BroatMoveMessage(pTargetPos, m_pOnwer->GetGLPos());
	return OR_OK;
	__UNGUARD__
	return OR_OK;
}


void CharMoveState::BroatMoveMessage(const GLPos* pTargetPos, const GLPos* stopPos)
{
	int32_t logicCount = m_pOnwer->GetMoveLogicCount();

	servermessage::ServerMsgCharMove dummy;
	dummy.set_object_id(m_pOnwer->GetID());
	dummy.set_handle_id(logicCount);

		
	base::GLPos* target = dummy.mutable_target_pos();
	target->set_fx(pTargetPos->m_fX);
	target->set_fz(pTargetPos->m_fZ);

	base::GLPos* stop = dummy.mutable_stop_pos();
	target->set_fx(stopPos->m_fX);
	target->set_fz(stopPos->m_fZ);
    m_pOnwer->GetMap()->broadCast(servermessage::SC_CHARACTER_MOVE, dummy, m_pOnwer);
}

float CharMoveState::GetSafeMoveSpeed()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fSpeed = m_pOnwer->Get_Property_MoveSpeed();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fSpeed < 0.2f)
	{
		fSpeed = 0.2f;
	}
	else if(fSpeed > 20.0f)
	{
		fSpeed = 20.0f;
	}

	return fSpeed;

	__UNGUARD__ return 1.0f;
}
