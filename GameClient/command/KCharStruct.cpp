#include "StdAfx.h"
#include "KCharStruct.h"


ModelPartData::ModelPartData()
{
	Clear();
}

void ModelPartData::Clear()
{
	m_bUpdateFlag	= FALSE;
	m_strBackUp		= "";
	m_strValue		= "";
	m_nBackUp		= INVALID_ID;
	m_nValue		= INVALID_ID;
}

void ModelPartData::Update()
{
	m_bUpdateFlag	= FALSE;
	m_strBackUp		= m_strValue;
	m_nBackUp		= m_nValue;
}

BOOL ModelPartData::IsFlag()
{
	if (m_bUpdateFlag)
	{
		if (m_strBackUp != m_strValue)
		{
			return TRUE;
		}
		if (m_nValue != m_nBackUp)
		{
			return TRUE;
		}
		m_bUpdateFlag = FALSE;
	}
	return FALSE;
}

void ModelPartData::SetValue(LPCSTR szValue)
{
	if (szValue && m_strValue != szValue)
	{
		m_strValue = szValue;
		m_bUpdateFlag = TRUE;
	}
}

void ModelPartData::SetValue(int32 nValue)
{
	if (m_nValue != nValue)
	{
		m_nValue = nValue;
		m_bUpdateFlag = TRUE;
	}
}

// -------------------------------------------------------------------------
// ап╠М
ModelPartDataList::ModelPartDataList()
{
	m_bUpdateFlag = FALSE;

	m_strPartName[BODY_PART_HAIR]		= g_szIDSTR_HAIR_MESH;
	m_strPartName[BODY_PART_FACE]		= g_szIDSTR_FACE_MESH;
	m_strPartName[BODY_PART_RIGHTHAND]	= g_szIDSTR_CURRENT_RIGHTWEAPON;
	m_strPartName[BODY_PART_LEFTHAND]	= g_szIDSTR_CURRENT_LEFTWEAPON;
	m_strPartName[BODY_PART_SHIELD]		= szIDSTRING_SHIELD_RIGHTWEAPON;
	m_strPartName[BODY_PART_MANTLE]		= szIDSTRING_SHOULDER_MESH;
	m_strPartName[BODY_PART_BODY]		= g_szIDSTR_MAINBODY_MESH;
	m_strPartName[BODY_PART_HAND]		= g_szIDSTR_ARM_MESH;
	m_strPartName[BODY_PART_FEET]		= g_szIDSTR_FOOT_MESH;
}

void ModelPartDataList::SetValue(int32 nPart, int32 nValue)
{
	if (0 > nPart || nPart >= BODY_PART_NUMBER)
		return;

	m_ModelPartData[nPart].SetValue(nValue);
	m_bUpdateFlag = TRUE;
}

void ModelPartDataList::SetValue(int32 nPart, LPCSTR szValue)
{
	if (0 > nPart || nPart >= BODY_PART_NUMBER)
		return;

	m_ModelPartData[nPart].SetValue(szValue);
	m_bUpdateFlag = TRUE;
}

void ModelPartDataList::Clear()
{
	for (int32 i=0; i<BODY_PART_NUMBER; ++i)
	{
		m_ModelPartData[i].Clear();
	}
	m_bUpdateFlag = FALSE;
}

void ModelPartDataList::Update()
{
	for (int32 i=0; i<BODY_PART_NUMBER; ++i)
	{
		m_ModelPartData[i].Update();
	}
	m_bUpdateFlag = FALSE;
}



// ------------------------------------------------------------
KCharCmdDate_Logic::KCharCmdDate_Logic(void)
{
	m_uStartTime	= UINT_MAX;
	m_nLogicCount	= INVALID_ID;
}

KCharCmdDate_Logic::~KCharCmdDate_Logic(void)
{
}

void KCharCmdDate_Logic::Clear(void)
{
	m_uStartTime	= UINT_MAX;
	m_nLogicCount	= INVALID_ID;
}

BOOL KCharCmdDate_Logic::Modify(const KCharCmdDate_StopLogic *pCmd)
{
	return TRUE;
}

// ------------------------------------------------------------
KCharCmdDate_StopLogic::KCharCmdDate_StopLogic(void)
{
	m_nLogicCount	= INVALID_ID;
}

KCharCmdDate_StopLogic::~KCharCmdDate_StopLogic(void)
{
}

void KCharCmdDate_StopLogic::Clear(void)
{
	m_nLogicCount	= INVALID_ID;
}

// ------------------------------------------------------------
KCharCmdDate_Action::KCharCmdDate_Action(void)
{
	m_nActionID		= INVALID_ID;
}

KCharCmdDate_Action::~KCharCmdDate_Action(void)
{
}

bool KCharCmdDate_Action::Initialize(uint32 uStartTime, int32 nLogicCount, int32 nActionID)
{
	SetStartTime(uStartTime);
	SetLogicCount(nLogicCount);
	m_nActionID		= INVALID_ID;


	return true;
}

void KCharCmdDate_Action::Clear(void)
{
	m_nActionID		= INVALID_ID;
	KCharCmdDate_Logic::Clear();
}
// ------------------------------------------------------------
KCharCmdDate_StopAction::KCharCmdDate_StopAction(void)
{
	m_uEndTime			= UINT_MAX;
}

KCharCmdDate_StopAction::~KCharCmdDate_StopAction(void)
{
}

bool KCharCmdDate_StopAction::Initialize(int32 nLogicCount, uint32 uEndTime)
{
	SetLogicCount(nLogicCount);
	m_uEndTime			= uEndTime;

	return true;
}

void KCharCmdDate_StopAction::Clear(void)
{
	m_uEndTime			= UINT_MAX;
	KCharCmdDate_StopLogic::Clear();
}

// ------------------------------------------------------------
KCharCmdDate_Move::KCharCmdDate_Move(void)
{
	m_nNodeCount		= 0;
	m_paposNode			= NULL;
	m_bServerCommond	= FALSE;
	m_bJumpMove			= FALSE;
}

KCharCmdDate_Move::~KCharCmdDate_Move(void)
{
	KCheck(m_paposNode == NULL);
}

bool KCharCmdDate_Move::Initialize(uint32 uStartTime, int32 nLogicCount, int32 nNodeCount, const GLPos *paposNode, BOOL bServerCommond)
{
	KCheck(m_paposNode == NULL);
	SetStartTime(uStartTime);
	SetLogicCount(nLogicCount);
	m_nNodeCount	 = nNodeCount;
	m_bServerCommond = bServerCommond;
	if(m_nNodeCount > 0)
	{
		m_paposNode	= new GLPos[m_nNodeCount];
		memcpy(m_paposNode, paposNode, m_nNodeCount * sizeof(GLPos));
	}
	else
	{
		m_paposNode	= NULL;
	}
	m_bJumpMove = FALSE;
	return true;
}

void KCharCmdDate_Move::Clear(void)
{
	m_nNodeCount	= 0;
	KSafeDelete_ARRAY(m_paposNode);
	KCharCmdDate_Logic::Clear();
}

BOOL KCharCmdDate_Move::Modify(const KCharCmdDate_StopLogic *pCmd)
{
	if(pCmd && pCmd->GetCmdType() == OBJ_CMD_STOP_MOVE)
	{
		KCharCmdDate_StopMove *pStopCmd = (KCharCmdDate_StopMove*)pCmd;
		int32 nEndNodeIndex	= pStopCmd->GetEndNodeIndex();
		if(m_nNodeCount > nEndNodeIndex)
		{
			//m_nNodeCount = nEndNodeIndex + 1;
			m_paposNode[nEndNodeIndex]	= *(pStopCmd->GetEndPos());
		}
		return TRUE;
	}
	return FALSE;
}
// ------------------------------------------------------------
KCharCmdDate_StopMove::KCharCmdDate_StopMove(void)
{
	m_nEndNodeIndex		= -1;
	m_bArrive			= FALSE;
	//m_posEndPos;
}

KCharCmdDate_StopMove::~KCharCmdDate_StopMove(void)
{
}

bool KCharCmdDate_StopMove::Initialize(int32 nLogicCount, int32 nEndNodeIndex, const GLPos *pPos, BOOL bArrive)
{
	SetLogicCount(nLogicCount);

	m_nEndNodeIndex		= nEndNodeIndex;
	m_posEndPos			= *pPos;
	m_bArrive			= bArrive;

	return true;
}

void KCharCmdDate_StopMove::Clear(void)
{
	m_nEndNodeIndex		= -1;
	m_posEndPos			= GLPos(-1.f, -1.f);
	m_bArrive			= FALSE;

	KCharCmdDate_StopLogic::Clear();
}


// ------------------------------------------------------------
KCharCmdDate_SkillSend::KCharCmdDate_SkillSend(void)
{
	m_nMagicID			= INVALID_ID;
	m_nTargetNum		= 0;
	m_fTargetDir		= -1.f;
	memset(m_nTargetObjID, INVALID_ID, sizeof(ObjID_t)*MAX_SKILL_TARGET_NUM);
}

KCharCmdDate_SkillSend::~KCharCmdDate_SkillSend(void)
{
}

bool KCharCmdDate_SkillSend::Initialize(uint32 uStartTime, int32 nLogicCount,int32 nMagicID,int32 nTargetNum,
													  const ObjID_t* pTargetIDList,const GLPos *pTargetPos,FLOAT fTargetDir)
{
	SetStartTime(uStartTime);
	SetLogicCount(nLogicCount);

	m_nMagicID			= nMagicID;
	m_nTargetNum		= nTargetNum;
	m_posTarget			= *pTargetPos;
	m_fTargetDir		= fTargetDir;

	if (pTargetIDList && m_nTargetNum > 0 && m_nTargetNum < MAX_SKILL_TARGET_NUM)
	{
		memcpy(m_nTargetObjID, pTargetIDList, sizeof(uint32)*m_nTargetNum);
	}
	return true;
}

void KCharCmdDate_SkillSend::Clear(void)
{
	m_nMagicID			= INVALID_ID;
	m_nTargetNum		= 0;
	m_posTarget			= GLPos(-1.f, -1.f);
	m_fTargetDir		= -1.f;
	KCharCmdDate_Logic::Clear();
}

// ------------------------------------------------------------
KCharCmdDate_SkillCharge::KCharCmdDate_SkillCharge(void)
{
	m_nMagicID			= INVALID_ID;
	m_nTargetObjID		= INVALID_ID;
	m_fTargetDir		= -1.f;
	m_uTotalTime		= UINT_MAX;
	m_uEndTime			= UINT_MAX;
}

KCharCmdDate_SkillCharge::~KCharCmdDate_SkillCharge(void)
{
}

bool KCharCmdDate_SkillCharge::Initialize(uint32 uStartTime, int32 nLogicCount,int32 nMagicID,ObjID_t nTargetID,
														const GLPos *pTargetPos,FLOAT fTargetDir,uint32 uTotalTime)
{
	SetStartTime(uStartTime);
	SetLogicCount(nLogicCount);

	m_nMagicID			= nMagicID;
	m_nTargetObjID		= nTargetID;
	m_posTarget			= *pTargetPos;
	m_fTargetDir		= fTargetDir;
	m_uTotalTime		= uTotalTime;
	m_uEndTime			= m_uTotalTime;
	m_bFinished			= FALSE;

	return true;
}

void KCharCmdDate_SkillCharge::Clear(void)
{
	m_nMagicID			= INVALID_ID;
	m_nTargetObjID		= INVALID_ID;
	m_posTarget			= GLPos(-1.f, -1.f);
	m_fTargetDir		= -1.f;
	m_uTotalTime		= UINT_MAX;
	m_uEndTime			= UINT_MAX;
	m_bFinished			= FALSE;
	KCharCmdDate_Logic::Clear();
}

BOOL KCharCmdDate_SkillCharge::Modify(const KCharCmdDate_StopLogic *pCmd)
{
	if(pCmd  && pCmd->GetCmdType() == OBJ_CMD_STOP_ACTION)
	{
		KCharCmdDate_StopAction *pStopCmd = (KCharCmdDate_StopAction*)pCmd;
		uint32 uEndTime = 0;
		if(m_uTotalTime > pStopCmd->GetEndTime())
		{
			uEndTime = m_uTotalTime - pStopCmd->GetEndTime();
		}
		if(uEndTime < m_uEndTime)
		{
			m_uEndTime = uEndTime;
		}
		m_bFinished = TRUE;
		return TRUE;
	}
	return FALSE;
}
// ------------------------------------------------------------
KCharCmdDate_SkillChannel::KCharCmdDate_SkillChannel(void)
{
	m_nMagicID			= INVALID_ID;
	m_nTargetObjID		= INVALID_ID;
	//m_posTarget;
	m_fTargetDir		= -1.f;
	m_uTotalTime		= UINT_MAX;
	m_uEndTime			= UINT_MAX;
}

KCharCmdDate_SkillChannel::~KCharCmdDate_SkillChannel(void)
{
}

bool KCharCmdDate_SkillChannel::Initialize(uint32 uStartTime,int32 nLogicCount,int32 nMagicID,ObjID_t nTargetID,
														 const GLPos *pTargetPos,FLOAT fTargetDir,uint32 uTotalTime)
{
	SetStartTime(uStartTime);
	SetLogicCount(nLogicCount);

	m_nMagicID			= nMagicID;
	m_nTargetObjID		= nTargetID;
	m_posTarget			= *pTargetPos;
	m_fTargetDir		= fTargetDir;
	m_uTotalTime		= uTotalTime;
	m_uEndTime			= 0;
	m_bFinished			= FALSE;

	return true;
}

void KCharCmdDate_SkillChannel::Clear(void)
{
	m_nMagicID			= INVALID_ID;
	m_nTargetObjID		= INVALID_ID;
	m_posTarget			= GLPos(-1.f, -1.f);
	m_fTargetDir		= -1.f;
	m_uTotalTime		= UINT_MAX;
	m_uEndTime			= UINT_MAX;
	m_bFinished			= FALSE;
	KCharCmdDate_Logic::Clear();
}

BOOL KCharCmdDate_SkillChannel::Modify(const KCharCmdDate_StopLogic *pCmd)
{
	if(pCmd && pCmd->GetCmdType() == OBJ_CMD_STOP_ACTION)
	{
		KCharCmdDate_StopAction *pStopCmd = (KCharCmdDate_StopAction*)pCmd;
		uint32 uEndTime = pStopCmd->GetEndTime();
		if(uEndTime > m_uEndTime)
		{
			m_uEndTime = uEndTime;
		}
		m_bFinished = TRUE;
		return TRUE;		
	}
	return FALSE;
}

// ------------------------------------------------------------
KCharCmdDate_Ability::KCharCmdDate_Ability(void)
{
	m_nAbilityID		= INVALID_ID;
	m_nPrescriptionID	= INVALID_ID;
	m_nTargetObjID		= INVALID_ID;
	m_uEndTime			= UINT_MAX;
}

KCharCmdDate_Ability::~KCharCmdDate_Ability(void)
{
}

bool KCharCmdDate_Ability::Initialize(uint32 uStartTime, int32 nLogicCount, int32 nAbilityID, int32 nPrescriptionID, ObjID_t nTargetObjID)
{
	SetStartTime(uStartTime);
	SetLogicCount(nLogicCount);
	m_nAbilityID		= nAbilityID;
	m_nPrescriptionID	= nPrescriptionID;
	m_nTargetObjID		= nTargetObjID;
	m_uEndTime			= UINT_MAX;
	m_bFinished			= FALSE;

	return true;
}

void KCharCmdDate_Ability::Clear(void)
{
	m_nAbilityID		= INVALID_ID;
	m_nPrescriptionID	= INVALID_ID;
	m_uEndTime			= UINT_MAX;
	m_nTargetObjID		= INVALID_ID;
	m_bFinished			= FALSE;
	KCharCmdDate_Logic::Clear();
}

BOOL KCharCmdDate_Ability::Modify(const KCharCmdDate_StopLogic *pCmd)
{
	if(pCmd && pCmd->GetCmdType() == OBJ_CMD_STOP_ACTION)
	{
		KCharCmdDate_StopAction *pStopCmd = (KCharCmdDate_StopAction*)pCmd;
		uint32 uEndTime = pStopCmd->GetEndTime();
		if(uEndTime < m_uEndTime)
		{
			m_uEndTime = uEndTime;
		}
		m_bFinished = TRUE;
		return TRUE;
	}
	return FALSE;
}
// ------------------------------------------------------------
KCharCmdDate_Jump::KCharCmdDate_Jump()
{
}
KCharCmdDate_Jump::~KCharCmdDate_Jump()
{
	
}

bool KCharCmdDate_Jump::Initialize(int32 nLogicCount)
{
	SetLogicCount(nLogicCount);
	return true;
}



// ------------------------------------------------------------
KObjectCmdDate *CreateCharCmd(const ObjectCmd *pCmd)
{
	if( NULL == pCmd )
		return NULL;

	switch( pCmd->m_wID )
	{
	case OBJ_CMD_STOP_ACTION:
		{
			KCharCmdDate_StopAction *pNewCmd = new KCharCmdDate_StopAction;

			int32 nLogicCount		= pCmd->nParam[0];
			uint32 uEndTime		= pCmd->uParam[1];

			pNewCmd->Initialize(nLogicCount, uEndTime);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_ACTION:
		{
			KCharCmdDate_Action *pNewCmd = new KCharCmdDate_Action;

			uint32 uStartTime		= pCmd->uParam[0];
			int32 nLogicCount		= pCmd->nParam[1];
			int32 nActionID		= pCmd->nParam[2];

			pNewCmd->Initialize(uStartTime, nLogicCount, nActionID);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_MOVE:
		{
			KCharCmdDate_Move *pNewCmd = new KCharCmdDate_Move;

			uint32 uStartTime			= pCmd->uParam[0];
			int32 nLogicCount			= pCmd->nParam[1];
			int32 nNodeCount			= pCmd->nParam[2];
			GLPos * paposNode	= (GLPos*)(pCmd->pParam[3]);
			BOOL bServerCommond		= pCmd->bParam[4];

			pNewCmd->Initialize( uStartTime, nLogicCount, nNodeCount, paposNode, bServerCommond );
			return pNewCmd;
		}
		break;
	case OBJ_CMD_STOP_MOVE:
		{
			KCharCmdDate_StopMove *pNewCmd = new KCharCmdDate_StopMove;

			GLPos posEnd;
			int32 nLogicCount		= pCmd->nParam[0];
			int32 nEndNodeIndex	= pCmd->nParam[1];
			posEnd.m_fX			= pCmd->fParam[2];
			posEnd.m_fZ			= pCmd->fParam[3];
			BOOL bArrive		= pCmd->nParam[4];

			pNewCmd->Initialize(nLogicCount, nEndNodeIndex, &posEnd, bArrive);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_SKILL_SEND:
		{
			KCharCmdDate_SkillSend *pNewCmd = new KCharCmdDate_SkillSend;

			GLPos	posTarget;
			uint32 uStartTime			= pCmd->uParam[0];
			int32 nLogicCount			= pCmd->nParam[1];
			int32 nMagicID			= pCmd->nParam[2];
			int32 nTargetNum			= pCmd->nParam[3];
			posTarget.m_fX			= pCmd->fParam[4];
			posTarget.m_fZ			= pCmd->fParam[5];
			FLOAT fTargetDir		= pCmd->fParam[6];
			ObjID_t* pTargetIDlist	= (ObjID_t*)(pCmd->pParam[7]);

			pNewCmd->Initialize( uStartTime, nLogicCount, nMagicID, nTargetNum, pTargetIDlist, &posTarget, fTargetDir);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_SKILL_CHARGE:
		{
			KCharCmdDate_SkillCharge *pNewCmd = new KCharCmdDate_SkillCharge;

			GLPos	posTarget;
			uint32 uStartTime			= pCmd->uParam[0];
			int32 nLogicCount			= pCmd->nParam[1];
			int32 nMagicID			= pCmd->nParam[2];
			ObjID_t nTargetObjID	= pCmd->nParam[3];
			posTarget.m_fX			= pCmd->fParam[4];
			posTarget.m_fZ			= pCmd->fParam[5];
			FLOAT fTargetDir		= pCmd->fParam[6];
			uint32 uTotalTime			= pCmd->uParam[7];

			pNewCmd->Initialize(uStartTime, nLogicCount, nMagicID, nTargetObjID, &posTarget, fTargetDir, uTotalTime);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_SKILL_CHANNEL:
		{
			KCharCmdDate_SkillChannel *pNewCmd = new KCharCmdDate_SkillChannel;

			GLPos	posTarget;
			uint32 uStartTime			= pCmd->uParam[0];
			int32 nLogicCount			= pCmd->nParam[1];
			int32 nMagicID			= pCmd->nParam[2];
			ObjID_t nTargetObjID	= pCmd->nParam[3];
			posTarget.m_fX			= pCmd->fParam[4];
			posTarget.m_fZ			= pCmd->fParam[5];
			FLOAT fTargetDir		= pCmd->fParam[6];
			uint32 uTotalTime			= pCmd->uParam[7];

			pNewCmd->Initialize( uStartTime, nLogicCount, nMagicID, nTargetObjID, &posTarget, fTargetDir, uTotalTime);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_ABILITY:
		{
			KCharCmdDate_Ability *pNewCmd = new KCharCmdDate_Ability;

			uint32 uStartTime		= pCmd->uParam[0];
			int32 nLogicCount		= pCmd->nParam[1];
			int32 nAbilityID		= pCmd->nParam[2];
			int32 nPrescriptionID	= pCmd->nParam[3];
			int32 nTargetID		= pCmd->nParam[4];

			pNewCmd->Initialize(uStartTime, nLogicCount, nAbilityID, nPrescriptionID, nTargetID);
			return pNewCmd;
		}
		break;
	case OBJ_CMD_JUMP:
		{
			KCharCmdDate_Jump* pNewCmd = new KCharCmdDate_Jump;

			int32 nLogicCount = pCmd->nParam[0];

			pNewCmd->Initialize(nLogicCount);
			return pNewCmd;            		
		}
		break;
	default:
		break;
	}	
	return NULL;
}




