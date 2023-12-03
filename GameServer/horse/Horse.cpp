/*$T MapServer/Server/Obj/Horse/Horse.cpp GC 1.140 10/10/07 10:07:29 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "StructDB.h"

#include "map/game_map.h"
#include "ObjectManager.h"

#include "Behavior_Horse.h"
#include "skill/Spell_Interface.h"



#include "TabDefine.h"
#include "BaseTool.h"
#include "item/Item_HorseContainer.h"
#include "gameobject/CharActionDelegator.h"
#include "Horse.h"
#include "HorseManager.h"
#include "data/data_manager.h"
#include "net/messages/SCMonsterAttribute.h"
#include "net/net_message_manager.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */

Horse::Horse(void)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	m_nCapturerCount = 0;
	for(i = 0; i < MAX_CAPTURER_NUM; i++)
	{
		m_aCapturer[i] = INVALID_ID;
	}

	m_RespawnPos = GLPos(-1.f, -1.f);
	m_RespawnTime = 0;

	m_GUID = INVALID_GUID;
	m_PetDB.Clear();
	m_nOwnerCount = 0;
	for(i = 0; i < MAX_TEAM_MEMBER; i++)
	{
		m_aOwnerGUID[i] = INVALID_GUID;
	}

	m_pCreator = NULL;
	m_pAI_Character = new Behavior_Horse;
	m_LifeTimer.Clear();
	m_LifeTimerMaster.Clear();
	KCheck(m_pAI_Character);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Horse::~Horse(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::Clear()
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	m_AttrBackUp.Clear();

	m_nCapturerCount = 0;
	for(i = 0; i < MAX_CAPTURER_NUM; i++)
	{
		m_aCapturer[i] = INVALID_ID;
	}

	m_RespawnPos = GLPos(-1.f, -1.f);
	m_RespawnTime = 0;

	m_GUID = INVALID_GUID;
	m_nOwnerCount = 0;
	for(i = 0; i < MAX_TEAM_MEMBER; i++)
	{
		m_aOwnerGUID[i] = INVALID_GUID;
	}

	m_pCreator = NULL;
	m_PetDB.Clear();

	m_ImpactList.Clear();
	m_LifeTimer.Clear();
	m_LifeTimerMaster.Clear();

	Character::Clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::Init(const _INIT_OBJECT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::Init(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _OBJ_HORSE_INIT	*pPetInit = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pPetInit = (const _OBJ_HORSE_INIT *) pInit;
	if(pPetInit == NULL)
	{
		KCheck(FALSE && "Error Horse::Init, pPetInit = NULL");
		return FALSE;
	}

	m_GUID = pPetInit->m_GUID;
	m_pCreator = NULL;

	m_nOwnerCount = pPetInit->m_nOwnerCount;
	if(m_nOwnerCount > 0)
	{
		if(m_nOwnerCount > MAX_TEAM_MEMBER) m_nOwnerCount = MAX_TEAM_MEMBER;

		memcpy(m_aOwnerGUID, pPetInit->m_aOwnerGUID, sizeof(GUID_t) * m_nOwnerCount);
	}

	if(m_pCreator == NULL) m_PetDB = pPetInit->m_PetDB;

	m_PetDB.m_nDataID = pPetInit->m_PetDB.m_nDataID;
	m_RespawnTime = pPetInit->m_RespawnTime;
	m_RespawnPos = pPetInit->m_Pos;
	GetMap()->GetHorseManager()->MakeCapturePetAttrib(&m_PetDB);
	GetAIObj()->ChangeState(ESTATE_IDLE);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::InitAIObj()
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
bool Horse::HeartBeat(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::HeartBeat(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	HeartBeat_Happiness(uTime);
	HeartBeat_Life(uTime);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::HeartBeat_Happiness(uint32 uTime)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::HeartBeat_Life(uint32 uTime)
{
	__GUARD__ if(!m_LifeTimerMaster.IsSetTimer())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_HORSE_ATTR	*pPetAttr = NULL;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(m_PetDB.m_nDataID != INVALID_ID)
		{
			pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(m_PetDB.m_nDataID);
			if(pPetAttr != NULL) m_LifeTimerMaster.BeginTimer(pPetAttr->m_iLifeHaveMaster, uTime);
		}
	}

	if(m_LifeTimerMaster.CountingTimer(uTime))
	{
		m_nOwnerCount = 0;
		for(uint32 n = 0; n < MAX_TEAM_MEMBER; n++)
		{
			m_aOwnerGUID[n] = INVALID_GUID;
		}

		if(!m_LifeTimer.IsSetTimer())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_HORSE_ATTR	*pPetAttr = NULL;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(m_PetDB.m_nDataID != INVALID_ID)
			{
				pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(m_PetDB.m_nDataID);
				if(pPetAttr != NULL) m_LifeTimer.BeginTimer(pPetAttr->m_LifeNoMaster, uTime);
			}
		}
	}

	if(m_LifeTimer.CountingTimer(uTime))
	{
		SetActiveFlag(FALSE);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::IsEnemy(Character *pCharacter)
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::IsFriend(Character *pCharacter)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pOwner = GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pOwner != NULL)
	{
		return pOwner->IsFriend(pCharacter);
	}
	else
	{
		KCheck(pCharacter);
		return FALSE == IsEnemy(pCharacter);
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::IsPartner(Character *pCharacter)
{
	__GUARD__ if(NULL == pCharacter)
	{
		return FALSE;
	}

	if(GetID() == pCharacter->GetID())
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pOwner = GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pOwner != NULL)
	{
		return pOwner->IsPartner(pCharacter);
	}
	else
	{
		return FALSE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::PushSkillToCache(int32 idSkill)
{
	__GUARD__ __UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::GetRateOfBuffTakeEffect(int32 idSkill, int32 &rateOfBuffTakeEffect)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::LevelUp(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::SetReliveInfo(BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo)
{
	__GUARD__ if(pReliveInfo == NULL)
	{
		KCheck(pReliveInfo != NULL && "Horse::SetReliveInfo");
		return;
	}

	Character::SetReliveInfo(bSkillRelive, pReliveInfo);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::AddCapturer(ObjID_t idObj)
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
BOOL Horse::DelCapturer(ObjID_t idObj)
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
void Horse::SendCaptureFailedToOthers(ObjID_t idObj)
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ XCManipulatePetRet	msg;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//for(int32 i = 0; i < MAX_CAPTURER_NUM; ++i)
	//{
	//	if(INVALID_ID != m_aCapturer[i] && m_aCapturer[i] != idObj)
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~*/
	//		GameMap	*pMap = GetMap();
	//		/*~~~~~~~~~~~~~~~~~~~~~*/

	//		if(!pMap)
	//		{
	//			m_nCapturerCount = 0;
	//			return;
	//		}

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		ObjectManager	*pObjMgr = pMap->GetObjManager();
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(!pObjMgr) return;

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		Object	*pObj = pObjMgr->GetObj(m_aCapturer[i]);
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(pObj && pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
	//		{
	//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//			Player	*pPlayer = (Player *) pObj;
	//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//			if(pPlayer)
	//			{
	//				GetGlobalActionDelegator().InterruptCurrentAction(*pPlayer);
	//				msg.SetManipulateRet(XCManipulatePetRet::OPT_HORSE_RET_CAPTUREFALID);

	//				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//				Behavior_Character	*pAIHuman = pPlayer->GetAIObj();
	//				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//				if(pAIHuman)
	//				{
	//					pAIHuman->BHV_Stop();
	//				}

	//				pPlayer->GetConnector()->SendPacket(&msg);
	//			}
	//		}
	//	}
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Horse::GetModelID(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iDataID = GetDataID();
	_HORSE_ATTR	*pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(iDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPetAttr) return INVALID_ID;

	return pPetAttr->m_iBehaveID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
NetPacket *Horse::CreateNewObjMsg(void)
{
	if(GetMap() != NULL)
	{
		if(!IsAlive())
		{
			KCheck(FALSE && "Horse should be never do this");
			return NULL;
		}
		else if(IsMoving())
		{
			///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			//XCNewHorse_Move *pPacket = (XCNewHorse_Move *) (GetMap()->m_pPacket_NewHorse_Move);
			///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			//pPacket->SetObjID(GetID());
			//pPacket->SetHandleID(GetMoveLogicCount());
			//pPacket->SetWorldPos(GetGLPos());
			//pPacket->SetTargetPos(GetCurrentTargetPos());
			//pPacket->SetMoveSpeed(Get_Property_MoveSpeed());

			//return pPacket;
		}
		else
		{
			///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			//XCNewHorse	*pPacket = (XCNewHorse *) (GetMap()->m_pPacket_NewHorse);
			///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			//pPacket->SetObjID(GetID());
			//pPacket->SetWorldPos((GetGLPos()));
			//pPacket->SetDir(GetDir());
			//pPacket->SetMoveSpeed(Get_Property_MoveSpeed());

			//return pPacket;
		}
	}
	else
	{
		KCheck(GetMap() != NULL && "Obj_Pet::CreateNewObjMsg");
		return NULL;
	}

	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::DestroyNewObjMsg(NetPacket *pPacket)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Horse::Get_Property_MoveSpeed(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ _HORSE_ATTR	*pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(GetDataID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPetAttr) return 0;

	return (float) pPetAttr->m_iMoveSpeed;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::RequestBaseProperty(Player *pTargetHuman, BASEPROPERTY_REFESH_MODE nMode)
{
	if(IsCanViewMe(pTargetHuman))
	{
		SCMonsterAttribute* packet = new SCMonsterAttribute;
		packet->setObjId(GetID());
		packet->setDataID(GetMountID());
		packet->setLevel(GetLevel());
		packet->setName(GetName());
		packet->setHpPercent(GetPercentHP());
		packet->setStealthLevel(GetStealthLevel());
		if (GetCampData() != NULL) 
			packet->setCampData(*GetCampData());
		packet->setOwnerID(INVALID_ID);
		packet->setMountID(INVALID_ID);
		packet->setMoveSpeed(Get_Property_MoveSpeed());
		packet->setAttackSpeed((float)Get_Property_AttackSpeed());
		NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Horse::AskMsg_DetailAttrib(Player *pTargetHuman)
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__	KCheck(NULL != pTargetHuman);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(pTargetHuman == GetOwner())
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	XCDetailAttrib_Pet	msgDetail;
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	msgDetail.SetGUID(&GetHorseGUID());
	//	msgDetail.SetIndex(INVALID_ID);
	//	msgDetail.SetObjID(GetID());
	//	msgDetail.SetDataID(GetDataID());
	//	msgDetail.SetName(GetName());
	//	msgDetail.SetHP(GetHP());
	//	msgDetail.SetHPMax(GetMaxHP());
	//	msgDetail.SetAIType(GetAIType());
	//	msgDetail.SetLevel(GetLevel());
	//	msgDetail.SetDataID(GetDataID());
	//	msgDetail.SetModelID(GetModelID());
	//	msgDetail.SetMountID(GetMountID());
	//	msgDetail.SetGeneration(GetGeneration());

	//	msgDetail.SetAtt_Near(Property_VerifyGeneralAttack(GetAttackNear()));
	//	msgDetail.SetAtt_Far(Property_VerifyGeneralAttack(GetAttackFar()));

	//	msgDetail.SetAtt_Magic(Property_VerifyGeneralAttack(Get_Property_AttackMagic()));
	//	msgDetail.SetDef_Near(Property_VerifyDefence(GetDefenceNear()));
	//	msgDetail.SetDef_Far(Property_VerifyDefence(GetDefenceFar()));

	//	msgDetail.SetDef_Magic(Property_VerifyDefence(Get_Property_DefenceMagic()));
	//	msgDetail.SetHit(Get_Property_Hit());
	//	msgDetail.SetMiss(Get_Property_Miss());
	//	msgDetail.SetCritical(Get_Property_Critical());
	//	msgDetail.SetExp(GetExp());
	//	msgDetail.SetStrPerception(GetStrPerception());
	//	msgDetail.SetConPerception(GetSmartnessPerception());
	//	msgDetail.SetDexPerception(GetMindPerception());
	//	msgDetail.SetIntPerception(GetConstitutionPerception());
	//	msgDetail.SetStr(Get_Property_Str());
	//	msgDetail.SetCon(Get_Property_Con());
	//	msgDetail.SetDex(Get_Property_Dex());
	//	msgDetail.SetInt(Get_Property_Int());
	//	msgDetail.SetRemainPoint(GetRemainPoint());
	//	pTargetHuman->GetConnector()->SendPacket(&msgDetail);
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Horse::GetMountID(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iDataID = GetDataID();
	_HORSE_ATTR	*pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(iDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPetAttr) return INVALID_ID;

	return pPetAttr->m_iMountID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Horse::GetCaptureCount(void) const
{
	return m_nCapturerCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Horse::IsOwner(GUID_t guidHuman)
{
	if(m_nOwnerCount < 1) return TRUE;
	if(m_nOwnerCount > MAX_TEAM_MEMBER) m_nOwnerCount = MAX_TEAM_MEMBER;
	for(uint32 n = 0; n < m_nOwnerCount; n++)
	{
		if(m_aOwnerGUID[n] == guidHuman) return TRUE;
	}

	return FALSE;
}
