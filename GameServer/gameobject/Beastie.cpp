/*$T MapServer/Server/Obj/Beastie/Beastie.cpp GC 1.140 10/10/07 10:07:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "StructDB.h"

#include "map/game_map.h"
#include "ObjectManager.h"
#include "skill/spell_interface.h"
#include "BaseTool.h"
#include "item/Item_HorseContainer.h"
#include "CharActionDelegator.h"
#include "Beastie.h"
#include "Behavior_Beastie.h"
#include "InitBeastieVisitor.h"
#include "Share/TAB/TabDefine_Map_Misc.h"
#include "gameobject/Player.h"
#include "server_settting.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "net/messages/SCManipulatePetRet.h"
#include "net/messages/SCMonsterAttribute.h"
#include "net/messages/SCNewBeastie.h"
#include "data/data_manager.h"


#define TONGQU_BUFF_ID	(7515)

/*
 =======================================================================================================================
 =======================================================================================================================
 */

int32 BeastieItem_Compare(_BEASTIE_DATA_TABLE::_BEASTIE_ITEM *l, _BEASTIE_DATA_TABLE::_BEASTIE_ITEM *r)
{
	if(l->m_uBeastieId < r->m_uBeastieId)
	{
		return -1;
	}
	else if(l->m_uBeastieId > r->m_uBeastieId)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Beastie::Beastie(void)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	m_pAI_Character = new Behavior_Beastie;
	KCheck(m_pAI_Character);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Beastie::~Beastie(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Beastie::Clear()
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	m_nCapturerCount = 0;
	for(i = 0; i < MAX_CAPTURER_NUM; i++)
	{
		m_aCapturer[i] = INVALID_ID;
	}

	m_OwnerID = INVALID_ID;
	m_TargetID = INVALID_ID;
	m_RespawnPos = GLPos(-1.f, -1.f);
	m_RespawnTime = -1;
	m_RespawnTimer.Clear();

	m_GUID = INVALID_GUID;

	m_CampData.Clear();
	memset(m_szName, 0, sizeof(m_szName));
	m_MoveSpeed = 0;
	m_nModelId = INVALID_ID;
	m_nDataID = INVALID_ID;
	m_nItemId = INVALID_ID;
	m_nBeastieType = INVALID_ID;

	m_ImpactList.Clear();

	Character::Clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Beastie::Init(const _INIT_OBJECT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::Init(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _OBJ_BEASTIE_INIT *pBeastieInit = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pBeastieInit = (const _OBJ_BEASTIE_INIT *) pInit;
	if(pBeastieInit == NULL)
	{
		KCheck(FALSE && "Error Beastie::Init, pBeastieInit = NULL");
		return FALSE;
	}

	strncpy(m_szName, pBeastieInit->m_szName, sizeof(m_szName) - 1);
	m_GUID = pBeastieInit->m_GUID;
	m_RespawnTime = pBeastieInit->m_RespawnTime;
	m_RespawnPos = pBeastieInit->m_Pos;
	m_MoveSpeed = pBeastieInit->m_fSpeed * 0.001f;
	m_nModelId = pBeastieInit->m_nModelId;
	m_CampData.m_nCampID = pBeastieInit->m_nCampId;
	SetDataID(pBeastieInit->m_uBeastieId);
	m_nItemId = pBeastieInit->m_nItemId;
	SetDir(pBeastieInit->m_Dir);
	m_nBeastieType = pBeastieInit->m_nBeastieType;

	SetRespawnDir(pInit->m_Dir);

	SetRespawnPos(&pInit->m_Pos);

	m_RespawnTimer.BeginTimer(m_RespawnTime, 0);

	Respawn(m_pVisitor);

	GetAIObj()->ChangeState(ESTATE_IDLE);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Beastie::InitAIObj()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pAI_Character);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pAI_Character->Init(this);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Beastie::IsCanViewMe(const Object *pObj)
{
	if(NULL == pObj)
	{
		return FALSE;
	}

	if(FALSE == IsObjCharacter(pObj->GetObjType()))
	{
		return FALSE;
	}

	if(TRUE == IsPartner((Character *) pObj))
	{
		return TRUE;
	}

	if(INVALID_ID == GetItemID())
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pChar = (Character *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pChar)
	{
		return FALSE;
	}

	/*if(pChar->Effect_HaveEffectOfSpecificEffectID(TONGQU_BUFF_ID))
	{
		return TRUE;
	}*/

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool Beastie::HeartBeat(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::HeartBeat(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return false;

	return true;

	__UNGUARD__ return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Beastie::AddCapturer(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	for(i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if(m_aCapturer[i] == INVALID_ID)
		{
			m_aCapturer[i] = idObj;
			++m_nCapturerCount;
			return TRUE;
		}
	}

	if(i == MAX_CAPTURER_NUM) return FALSE;

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Beastie::DelCapturer(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	for(i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if(m_aCapturer[i] == idObj)
		{
			m_aCapturer[i] = INVALID_ID;
			--m_nCapturerCount;
			if(m_nCapturerCount < 0) m_nCapturerCount = 0;
			return TRUE;
		}
	}

	if(i == MAX_CAPTURER_NUM) return FALSE;

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Beastie::SendCaptureFailedToOthers(ObjID_t idObj)
{
	SCManipulatePetRet* packet = new SCManipulatePetRet;

	for(int32 i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if(INVALID_ID != m_aCapturer[i] && m_aCapturer[i] != idObj)
		{
			/*~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~*/

			Object	*pObj = pMap->GetSpecificObjByID(m_aCapturer[i]);

			if(pObj && pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Player	*pPlayer = (Player *) pObj;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pPlayer)
				{
					GetGlobalActionDelegator().InterruptCurrentAction(*pPlayer);
					packet->setManipulateRet(SCManipulatePetRet::OPT_HORSE_RET_CAPTUREFALID);

					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Behavior_Character	*pAIHuman = pPlayer->GetAIObj();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(pAIHuman)
					{
						pAIHuman->BHV_Stop();
					}

					//todo
				}
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
NetPacket *Beastie::CreateNewObjMsg(void)
{

	const GLPos* pos = GetGLPos();
	SCNewBeastie* packet = new SCNewBeastie;
	packet->setObjID(GetID());
	packet->setPosition(pos->m_fX, pos->m_fZ);
	packet->setDir(GetDir());
	packet->setSpeed(Get_Property_MoveSpeed());

	if(IsMoving())
	{
		packet->setHandleId(GetMoveLogicCount());
		const GLPos* targetPos = GetCurrentTargetPos();
		packet->setTargetPosition(targetPos->m_fX, targetPos->m_fZ);
	}
	return packet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Beastie::DestroyNewObjMsg(NetPacket*pPacket)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Beastie::RequestBaseProperty(Player *pTargetHuman, BASEPROPERTY_REFESH_MODE nMode)
{
	__GUARD__ 
	if(IsCanViewMe(pTargetHuman))
	{
		SCMonsterAttribute* packet = new SCMonsterAttribute;
		uchar			yHPPercent = 100;
		uchar			yMPPercent = 100;
		packet->setLevel(1);
		packet->setObjId(GetID());
		packet->setDataID(GetDataID());
		packet->setName(GetName());
		packet->setHpPercent(yHPPercent);
		if (GetCampData() != NULL) 
			packet->setCampData(*GetCampData());
		packet->setMoveSpeed(Get_Property_MoveSpeed());
		//NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Beastie::Get_Property_MoveSpeed(void)
{
	__GUARD__ return m_MoveSpeed;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Beastie::GetModelID(void)
{
	__GUARD__ return m_nModelId;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Beastie::GetCaptureCount(void) const
{
	return m_nCapturerCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Beastie::Enter_Respawn(void)
{
	__GUARD__ if(m_RespawnTime >= 0)
	{
		m_RespawnTimer.BeginTimer((uint32) (m_RespawnTime * g_Config.m_ConfigInfo.m_fRespawnParam), NowTime());
	}
	else
	{
		m_RespawnTimer.BeginTimer(m_RespawnTime, NowTime());
	}

	SetActiveFlag(FALSE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Beastie::Respawn(CharacterVisitor *pVisitor)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(!IsActiveObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pVisitor != NULL);
	if(pVisitor == NULL)
	{
		GetRespawnPos();
	}

	/*~~~~~~~~~~~~~~~~~*/
	float		fDir;
	GLPos	Pos;
	/*~~~~~~~~~~~~~~~~~*/

	Pos = *GetRespawnPos();
	fDir = GetRespawnDir();
	GetMap()->GetMapInfo()->VerifyPos(&Pos);
	GetMap()->GetMapInfo()->IsCanGo(Pos) ? Pos : Pos = *GetRespawnPos();
	SetGLPos(&Pos);
	m_pVisitor->VisitInitMonster(this);

	UpdateGrid();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Beastie	*pAI = (Behavior_Beastie *) GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAI)
	{
		//pAI->Clear();
		pAI->ChangeState(ESTATE_IDLE);
	}

	SetActiveFlag(TRUE);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Beastie::HeartBeat_OutMap(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::HeartBeat_OutMap(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return bResult;
	if(m_RespawnTime < 0) return FALSE;

	if(m_RespawnTimer.CountingTimer(uTime))
	{
		m_RespawnTimer.Clear();
		Respawn(m_pVisitor);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Beastie::GetBeastieItem(int32 beastieDataId)
{
	_BEASTIE_DATA_TABLE::_BEASTIE_ITEM * pBeastieItem = NULL;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_BEASTIE_DATA_TABLE::_BEASTIE_ITEM	oBeastieItem;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	oBeastieItem.m_uBeastieId = beastieDataId;

	_BEASTIE_DATA_TABLE* beastieTable = DataManager::GetSingletonPtr()->getBeastTable();

	pBeastieItem = (_BEASTIE_DATA_TABLE::_BEASTIE_ITEM *) bsearch
		(
			&oBeastieItem,
			beastieTable->m_BeastieItem,
			beastieTable->m_uCount,
			sizeof(_BEASTIE_DATA_TABLE::_BEASTIE_ITEM),
			(int32(*) (const void *, const void *)) BeastieItem_Compare
		);

	if(pBeastieItem)
	{
		return pBeastieItem->m_nItemId;
	}

	return -1;
}
