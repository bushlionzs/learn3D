/*$T MapServer/Server/Obj/Pet.cpp GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "StructDB.h"

#include "Map.h"
#include "ObjectManager.h"

#include "Behavior_Pet.h"
#include "Spell_Interface.h"

#include "XCManipulatePetRet.h"
#include "XCLevelUp.h"

#include "Pet.h"
#include "Pet.inl"
#include "GuardManager.h"
#include "TabDefine.h"
#include "BaseTool.h"
#include "Item_HorseContainer.h"
#include "CharActionDelegator.h"

#include "Spell_EffectInterface.h"
#include "CountryCacheManager.h"

using namespace Messages;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

_PET_PROPERTY_BACKUP::_PET_PROPERTY_BACKUP(void)
{
	m_bNameModified = FALSE;
	m_bTitleModified = FALSE;

	m_MoveSpeed = 0.f;
	m_nOwnerID = INVALID_ID;
	m_nAIType = -1;
	m_Level = -1;

	m_nDataID = INVALID_ID;
	m_nModelID = INVALID_ID;
	m_nMountID = INVALID_ID;

	m_byGeneration = 0;
	m_byHappiness = 0;

	m_iStrength = 0;
	m_iSmartness = 0;
	m_iMind = 0;
	m_iConstitution = 0;

	m_nAtt_Near = -1;
	m_nAtt_Far = -1;
	m_nAtt_Magic = -1;
	m_nDef_Near = -1;
	m_nDef_Far = -1;

	m_nDef_Magic = -1;
	m_nHit = -1;
	m_nMiss = -1;

	m_nExp = -1;

	m_iStrengthPerception = -1;
	m_iSmartnessPerception = -1;
	m_iMindPerception = -1;
	m_iConstitutionPerception = -1;
	m_nRemainPoint = -1;
	m_iPullulationRate = 0;

	m_nTargetID = INVALID_ID;
	m_nScale = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _PET_PROPERTY_BACKUP::Clear(void)
{
	m_bNameModified = FALSE;
	m_bTitleModified = FALSE;
	m_MoveSpeed = 0.f;
	m_CampData.Clear();
	m_nOwnerID = INVALID_ID;
	m_nAIType = -1;
	m_Level = -1;

	m_nDataID = INVALID_ID;
	m_nModelID = INVALID_ID;
	m_nMountID = INVALID_ID;

	m_GUID.Reset();
	m_byGeneration = 0;
	m_byHappiness = 0;

	m_nAtt_Near = -1;
	m_nAtt_Far = -1;

	m_nAtt_Magic = -1;
	m_nDef_Near = -1;
	m_nDef_Far = -1;

	m_nDef_Magic = -1;
	m_nHit = -1;
	m_nMiss = -1;

	m_nExp = -1;

	m_iStrengthPerception = -1;
	m_iSmartnessPerception = -1;
	m_iMindPerception = -1;
	m_iConstitutionPerception = -1;
	m_iPullulationRate = 0;

	m_iStrength = 0;
	m_iSmartness = 0;
	m_iMind = 0;
	m_iConstitution = 0;

	m_nRemainPoint = -1;

	m_nTargetID = INVALID_ID;
	m_nScale = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Pet::Pet(void)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	m_LifeTimer.Clear();
	m_uMoveIntervalTimer = 0;

	m_nCapturerCount = 0;
	for(i = 0; i < MAX_CAPTURER_NUM; i++)
	{
		m_aCapturer[i] = INVALID_ID;
	}

	for(i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		m_aCacheOfSkill[i] = INVALID_ID;
	}

	m_iHitRate = 0;
	m_iMissRate = 0;
	m_iCriticalRate = 0;

	m_OwnerID = INVALID_ID;
	m_TargetID = INVALID_ID;
	m_RespawnPos = GLPos(-1.f, -1.f);
	m_TargetOldPos = GLPos(-1.f, -1.f);
	m_RespawnTime = 0;
	m_bFollowMode = FALSE;
	m_nCtrlState = PCS_KILL_TARGET;

	m_GUID = INVALID_GUID;
	m_PetDB.Clear();
	m_CreatorID = INVALID_ID;
	m_pCreator = NULL;
	m_nIndex = -1;
	m_iLevel = 0;
	m_CooldownList.Clear();

	m_pAI_Character = new Behavior_Pet;
	KCheck(m_pAI_Character);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Pet::~Pet(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::Clear()
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	m_AttrBackUp.Clear();

	m_HappinessTimer.Clear();

	m_LifeTimer.Clear();
	m_uMoveIntervalTimer = 0;

	m_ImpactList.Clear();

	m_nCapturerCount = 0;
	for(i = 0; i < MAX_CAPTURER_NUM; i++)
	{
		m_aCapturer[i] = INVALID_ID;
	}

	for(i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		m_aCacheOfSkill[i] = INVALID_ID;
	}

	m_iHitRate = 0;
	m_iMissRate = 0;
	m_iCriticalRate = 0;

	m_OwnerID = INVALID_ID;
	m_TargetID = INVALID_ID;
	m_RespawnPos = GLPos(-1.f, -1.f);
	m_TargetOldPos = GLPos(-1.f, -1.f);
	m_RespawnTime = 0;
	m_bFollowMode = FALSE;
	m_nCtrlState = PCS_KILL_TARGET;

	m_GUID = INVALID_GUID;
	m_CreatorID = INVALID_ID;
	m_pCreator = NULL;
	m_PetDB.Clear();
	m_nIndex = -1;
	m_iLevel = 0;

	m_CooldownList.Clear();
	Character::Clear();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::Init(const _INIT_OBJECT *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::Init(pInit);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _INIT_PET_OBJECT	*pPetInit = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pPetInit = (const _INIT_PET_OBJECT *) pInit;
	if(pPetInit == NULL)
	{
		KCheck(FALSE && "Error Pet::Init, pPetInit = NULL");
		return FALSE;
	}

	m_GUID = pPetInit->m_GUID;
	m_CreatorID = pPetInit->m_CreatorID;
	m_pCreator = NULL;
	m_nIndex = pPetInit->m_nIndex;
	if(m_CreatorID != INVALID_ID)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pCreator = (Character *) (GetMap()->GetObjManager()->GetObj(m_CreatorID));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pCreator != NULL && pCreator->GetObjType() == OBJECT_CLASS_PLAYER) m_pCreator = (Player *) pCreator;
	}

	if(m_pCreator == NULL)
	{
		m_PetDB = pPetInit->m_PetDB;
		return FALSE;
	}

	m_PetDB.m_nDataID = pPetInit->m_PetDB.m_nDataID;
	m_RespawnTime = pPetInit->m_RespawnTime;

	m_RespawnPos = pPetInit->m_Pos;
	m_OwnerID = pPetInit->m_CreatorID;

	SetDataID(m_pCreator->GetMonsterPetDataID());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			nDataID = GetDataID();
	SMonsterExtAttr	*pPetAttr = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDataID != INVALID_ID)
	{
		pPetAttr = g_MonsterPropertyExTab.GetExtAttr(nDataID);
	}

	if(NULL != pPetAttr)
	{
		strncpy(m_PetDB.m_szName, pPetAttr->m_Name, sizeof(pPetAttr->m_Name) - 1);
	}

	InitSkill();

	InitLife();
	InitBaseAttr();

	GetAIObj()->ChangeState(ESTATE_IDLE);

	InitBackupAttr();

	Effect_InitList();

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::InitAIObj()
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
BOOL Pet::HeartBeat(uint32 uTime)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bResult = Character::HeartBeat(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult) return FALSE;

	HeartBeat_Life(uTime);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::HeartBeat_Happiness(uint32 uTime)
{
	__GUARD__ return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::HeartBeat_Life(uint32 uTime)
{
	__GUARD__ if(GetHP() <= 0)
	{
		RecallPet();
		return TRUE;
	}

	if(-1 == m_oInit.iLifeTime)
	{
		return TRUE;
	}

	if(m_LifeTimer.CountingTimer(GET_TIME().TickCount()))
	{
		RecallPet();
	}

	return TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__UNGUARD__	SetActiveFlag(FALSE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::IsEnemy(Character *pCharacter)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pOwner = GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(GetID() == pCharacter->GetID())
	{
		return FALSE;
	}

	if(pOwner != NULL)
	{
		if(pOwner->GetID() == pCharacter->GetID())
		{
			return FALSE;
		}

		return pOwner->IsEnemy(pCharacter);
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SOT_ShadowGuard_T	logic;
		UNIT_EFFECT		*pImp = Effect_GetFirstEffectOfSpecificLogicID(logic.ID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pImp)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = (Object *) ((GetSpecificObjInSameSceneByID(logic.GetSummonerID(*pImp))));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pObj)
			{
				if(TRUE == IsObjCharacter(pObj->GetObjType()))
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Character	&rSummoner = *static_cast<Character *>(pObj);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					return rSummoner.IsEnemy(pCharacter);
				}
			}
		}

		KCheck(pCharacter);

		/***************************弱国联盟判断开始********************************/
		BOOL	bIsCountryColleague = CountryCacheManager::GetInstance().ProcessCountryColleague(this , pCharacter);
		if (bIsCountryColleague == TRUE)
		{
			return FALSE;
		}
		/***************************弱国联盟判断结束********************************/

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bIsEnemy = IsEnemyCamp(*pCharacter);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		return bIsEnemy;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::IsFriend(Character *pCharacter)
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
BOOL Pet::IsPartner(Character *pCharacter)
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
Character *Pet::GetOwner(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pCharacter = NULL;
	ObjID_t		idOwner = GetOwnerID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(idOwner != INVALID_ID && GetMap() != NULL)
	{
		pCharacter = (Character *) (GetMap()->GetObjManager()->GetObj(idOwner));
	}

	return pCharacter;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::ToAttack(ObjID_t TargetID)
{
	__GUARD__ if(INVALID_ID != TargetID && m_TargetID == TargetID)
	{
		return;
	}

	m_TargetID = TargetID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Pet	*pBehavior_Pet = (Behavior_Pet *) GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pBehavior_Pet)
	{
		pBehavior_Pet->BabyToAttack();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::PushSkillToCache(int32 idSkill)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 i;
	/*~~~~~~~~~~~~~~*/

	for(i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		if(INVALID_ID == m_aCacheOfSkill[i])
		{
			m_aCacheOfSkill[i] = idSkill;
			break;
		}
	}

	if(PLAYER_PET_MAX_COUNT == i)
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
void Pet::GetRateOfBuffTakeEffect(int32 idSkill, int32 &rateOfBuffTakeEffect)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ const SpellTemplateData	*pSkillData_T = g_SpellTemplateDataMgr.GetInstanceByID(idSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pSkillData_T)
	{
		KCheck(NULL && "Pet::GetRateOfBuffTakeEffect...pSkillData_T=NULL...");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ID_t	TypeOfSkill = pSkillData_T->GetTypeOfPetSkill();
	Player	*pCreator = GetCreator();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pCreator)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemContainer	*pItemContainer = pCreator->GetPetContain();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItemContainer);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item	*pItem = pItemContainer->GetItem(m_nIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nAIType = pItem->GetAIType();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nAIType < 0 || nAIType > PET_AITYPE) return;
		if(TypeOfSkill < 0 || TypeOfSkill > PET_SKILL_TYPE) return;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	fLaunchRate = g_HorseAIStrategyTab[TypeOfSkill][nAIType];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rateOfBuffTakeEffect = (int32) (rateOfBuffTakeEffect * fLaunchRate);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::IsFollowMode()
{
	__GUARD__ return m_bFollowMode;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::SetFollowMode(BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bFollowMode = bFlag;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_PET_CTRL_STATE Pet::GetCtrlState(void) const
{
	return m_nCtrlState;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::SetCtrlState(const _PET_CTRL_STATE eState)
{
	m_nCtrlState = eState;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::LevelUp(void)
{
	__GUARD__ if(INVALID_ID == m_OwnerID)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pOwner = GetMap()->GetObjManager()->GetObj(m_CreatorID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pOwner || pOwner->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemContainer	*pPetContainer = ((Player *) pOwner)->GetPetContain();
	Item		*pPetItem = pPetContainer->GetItem(m_nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPetItem);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nLevel = GetLevel() + 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nLevel == PET_LEVEL_NUM)
	{
		return;
	}

	SetLevel(nLevel);

	Set_BaseProperty_Str(Get_BaseProperty_Str() + 1);

	Set_BaseProperty_Con(Get_BaseProperty_Con() + 1);
	Set_BaseProperty_Int(Get_BaseProperty_Int() + 1);
	Set_BaseProperty_Dex(Get_BaseProperty_Dex() + 1);
	SetRemainPoint(pPetItem->GetRemainPoint() + 5);

	SetHP(GetMaxHP());
	SetHappiness(100);

	Spell_Apperceive();

	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	XCLevelUp	msgLevelUp;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	msgLevelUp.SetObjId(GetID());
	msgLevelUp.SetLevel(GetLevel());

	GetMap()->BroadCast(&msgLevelUp, this, TRUE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::SetReliveInfo(BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo)
{
	__GUARD__ if(pReliveInfo == NULL)
	{
		KCheck(pReliveInfo != NULL && "Pet::SetReliveInfo");
		return;
	}

	Character::SetReliveInfo(bSkillRelive, pReliveInfo);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::AddCapturer(ObjID_t idObj)
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
BOOL Pet::DelCapturer(ObjID_t idObj)
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
void Pet::SendCaptureFailedToOthers(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ XCManipulatePetRet	msg;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if(INVALID_ID != m_aCapturer[i] && m_aCapturer[i] != idObj)
		{
			/*~~~~~~~~~~~~~~~~~~~~~*/
			Map	*pMap = GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~*/

			if(!pMap)
			{
				m_nCapturerCount = 0;
				return;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ObjectManager	*pObjMgr = pMap->GetObjManager();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pObjMgr) return;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = pObjMgr->GetObj(m_aCapturer[i]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pObj && pObj->GetObjType() == Object::OBJECT_CLASS_PLAYER)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Player	*pPlayer = (Player *) pObj;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pPlayer)
				{
					GetGlobalActionDelegator().InterruptCurrentAction(*pPlayer);
					msg.SetManipulateRet(XCManipulatePetRet::OPT_HORSE_RET_CAPTUREFALID);

					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Behavior_Character	*pAIHuman = pPlayer->GetAIObj();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(pAIHuman)
					{
						pAIHuman->BHV_Stop();
					}

					pPlayer->GetConnector()->SendPacket(&msg);
				}
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Pet::InitSkill()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Map	*pMap = GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return FALSE;
	}

	if(NULL == m_pCreator)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GuardManager	*pGuardManager = pMap->GetGuardManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pGuardManager)
	{
		return FALSE;
	}

	m_oInit = pGuardManager->GetInitData();

	for(int32 i = 0; i < MONSTER_PET_MAX_SKILL; ++i)
	{
		m_aCacheOfSkill[i] = m_oInit.aSkillID[i];
	}

	if(INVALID_ID != m_oInit.iImpactToSelf)
	{
		g_EffectInterface.SendEffectToUnit(*this, m_oInit.iImpactToSelf, m_pCreator->GetID());
	}

	if(INVALID_ID != m_oInit.iImpactToOnwer)
	{
		g_EffectInterface.SendEffectToUnit(*m_pCreator, m_oInit.iImpactToOnwer, m_pCreator->GetID());
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::InitLife()
{
	__GUARD__ if(-1 != m_oInit.iLifeTime)
	{
		m_LifeTimer.BeginTimer(m_oInit.iLifeTime, GET_TIME().TickCount());
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::RecallPet()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Player	*pOwner = (Player *) GetOwner();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pOwner)
	{
		pOwner->ReCallPet(m_nIndex);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Pet::GetIndexInOnwer()
{
	return m_nIndex;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::InitMonsterPetDB(_Monster_Pet_DB_Struct &oMonsterPet)
{
	__GUARD__ oMonsterPet.iLifeTime = GetLifeTime();

	GetNowImpactList(oMonsterPet);
	oMonsterPet.m_iDataIndex = GetDataID();
	oMonsterPet.m_iHP = GetHP();
	oMonsterPet.m_nCtrlState = GetCtrlState();
	memcpy(oMonsterPet.m_aSkillList, m_aCacheOfSkill, sizeof(oMonsterPet.m_aSkillList));
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Pet::GetLifeTime()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iLife = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_oInit.iLifeTime > 0)
	{
		iLife = m_oInit.iLifeTime - (GET_TIME().TickCount() - m_LifeTimer.GetTickOldTime());
		if(iLife < 0)
		{
			iLife = 0;
		}
	}

	return iLife;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::GetNowImpactList(_Monster_Pet_DB_Struct &oMonsterPet)
{
	__GUARD__ for(int32 i = 0; i < m_ImpactList.m_Count; ++i)
	{
		if(i >= MONSTER_PET_MAX_IMPACT)
		{
			break;
		}

		oMonsterPet.m_aImpactList[i] = m_ImpactList.m_aImpacts[i];
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::InitHP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetHP(Get_BaseProperty_MaxHP());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Pet::InitBaseAttr()
{
	Set_BaseProperty_MaxHP(GetAttrValueByType(CPROPERTY_LEVEL2_MAXHP));
	InitHP();
	SetBaseAttackNear(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACK_NEAR));
	SetBaseAttackFar(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACK_FAR));
	Set_BaseProperty_AttackMagic(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACKRATE_M));
	Set_BaseProperty_AttackCold(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACKCOLD));
	Set_BaseProperty_AttackFire(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACKFIRE));
	Set_BaseProperty_AttackLight(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACKLIGHT));
	Set_BaseProperty_AttackPoison(GetAttrValueByType(CPROPERTY_LEVEL2_ATTACKPOISON));

	SetBaseDefenceNear(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCE_NEAR));
	SetBaseDefenceFar(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCE_FAR));
	Set_BaseProperty_DefenceMagic(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCE_M));
	Set_BaseProperty_DefenceCold(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCECOLD));
	Set_BaseProperty_DefenceFire(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCEFIRE));
	Set_BaseProperty_DefenceLight(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCELIGHT));
	Set_BaseProperty_DefencePoison(GetAttrValueByType(CPROPERTY_LEVEL2_DEFENCEPOISON));

	SetBaseToughness(GetAttrValueByType(CPROPERTY_LEVEL2_TOUGHNESS));
	Set_BaseProperty_Critical(GetAttrValueByType(CPROPERTY_LEVEL2_CRITRATE));
	Set_BaseProperty_Hit(GetAttrValueByType(CPROPERTY_LEVEL2_HIT));
	Set_BaseProperty_Miss(GetAttrValueByType(CPROPERTY_LEVEL2_MISS));
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Pet::RefixByInherence(int32 &nDamage, Character *const pAttacker, BOOL bDOT, BOOL bPKRateCtr)
{
	__GUARD__

	float	nRefix = g_Config.m_ConfigInfo.m_fInherenceFixParam;
	if (NULL != pAttacker)
	{
		if( OBJECT_CLASS_PLAYER == pAttacker->GetObjType())
		{
			nDamage = Float2Int(nRefix * nDamage);
		}
	}
	else
	{
		if (TRUE == bDOT && TRUE == bPKRateCtr)
		{
			nDamage = Float2Int(nRefix * nDamage);
		}
	}

	return;
	__UNGUARD__
}
