
#include "StdAfx.h"
#include "AI_Base.h"

KAI::KAI() :
	m_pAIState(NULL)
{
	m_StateList.InitStateList(this);
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAI::~KAI(void)
{
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KHAN_RETURN_RESULT KAI::Update()
{
	if(NULL == m_pAIState) return KRR_FAILED;

	if(KRR_FAILED == m_pAIState->Update())
	{
		m_pAIState->OnStateShutdown();
		m_pAIState = NULL;

		return KRR_FAILED;
	}

	return KRR_SUCCEED;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_ACTIVE_RESULT KAI::ChangeAIState(AI_STATE eAI, const AICmd &cmd)
{
	KAIState* pState = m_StateList.GetStateInstance(eAI);
	if (NULL == pState)
		return AI_RES_FAILURE;

	if(m_pAIState)
	{
		/* ×´Ì¬»¥³â */
		if(m_pAIState->GetMutexFlag(pState->GetCommandMutexType()))
		{
			return AI_RES_FAILURE;
		}
	}

	AI_ACTIVE_RESULT res = pState->OnStateActive(cmd);
	switch(res)
	{
	case AI_RES_OK:
		{
			if(m_pAIState && m_pAIState->GetStateType() != pState->GetStateType())
			{
				m_pAIState->OnStateShutdown();
			}
			m_pAIState = pState;
		}
		break;
	case AI_RES_OK_AND_SHUTDOWN:
		{
			if(m_pAIState)
			{
				m_pAIState->OnStateShutdown();
			}
			pState->OnStateShutdown();
			m_pAIState = NULL;
		}
		break;
	case AI_RES_OK_BUT_NO_CHANGE:
		{
			if(m_pAIState && m_pAIState->GetStateType() != pState->GetStateType())
			{
				pState->OnStateShutdown();
			}
		}
		break;
	case AI_RES_FAILURE:
	default:
		{
			pState->OnStateShutdown();
		}
		break;
	}
	return res;
}

/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
void KAI::ShutDownAI()
{
	if(m_pAIState)
	{
		m_pAIState->OnStateShutdown();
		m_pAIState = NULL;
	}
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
AI_STATE KAI::GetMySelfAI(void)
{
	if (GetActiveAI())
	{
		return (AI_STATE)GetActiveAI()->GetStateType();
	}
	return AI_STATE_IDLE;
}
/* --------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------- */
KAIState* KAI::GetAIState(AI_STATE eAI)
{
	KAIState* pState = m_StateList.GetStateInstance(eAI);
	return pState;
}
