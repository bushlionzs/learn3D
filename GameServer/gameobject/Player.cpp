/*$T MapServer/Server/Obj/Player.cpp GC 1.140 10/10/07 10:07:33 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Monster.h"
#include "TabDefine.h"
#include "BaseTool.h"
#include "Share/TAB/TabDefine_Map_Quest.h"
#include "Character.h"
#include "skill/Spell_Helper.h"
#include "Player.h"
#include "Player.inl"
#include "StructPet.h"
#include "HumanStateMutexDefine.h"
#include "Struct.h"
#include "server_settting.h"
#include "map/game_map.h"
#include "data/data_manager.h"
#include "net/net_message_manager.h"
#include "net/messages/SCEnterMap.h"
#include "ObjectList.h"
#include "Behavior_Player.h"
#include "StructDB.h"
#include "Archive/PlayerDB.h"
#include "item/Item_Interface.h"
#include "net/messages/SCDetailEquipList.h"
#include "net/messages/SCDetailItemList.h"
#include "net/messages/SCQuestList.h"
#include "net/messages/SCAddQuest.h"
#include "net/messages/SCDelQuest.h"
#include "net/messages/SCModifyQuest.h"
#include "net/messages/SCCharHumanBaseAttrib.h"
#include "net/messages/SCDetailSkillList.h"
#include "net/messages/SCItemInfo.h"
#include "net/messages/SCDetailAbilityInfo.h"
#include "net/messages/SCOperateResult.h"
#include "quest/quest_manager.h"
#include "horse/HorseManager.h"
#include "horse/Horse.h"
#include "net/messages/SCDetailAttribPet.h"
#include "net/messages/SCCharEquipment.h"
#include "net/messages/SCQuestListRefresh.h"
#include "net/messages/SCOperateResult.h"
#include "Share/TAB/TabDefine_Map_Pet.h"
#include "server_manager.h"
#include "script/LuaSystem.h"
#include "ScriptDef.h"
#include "skill/Skill_Base.h"
#include "skill/Skill_Manager.h"

_PLAYER_ATTR_BACKUP::_PLAYER_ATTR_BACKUP(void)
{
	m_bNameModified = FALSE;
	m_bNormalTitleModified = FALSE;
	m_bGuildTitleModified = FALSE;
	m_bCountryTitleModified = FALSE;
	m_Level = -1;
	m_Exp = -1;
	m_HP = -1;
	m_MP = -1;
	m_HPPercent = 100;
	m_HPGuardPercent = 100;
	m_MaxHp = -1;
	m_MaxMp = -1;
	m_MoveSpeed = -1;
	m_nMoveMode = -1;
	m_nDataID = INVALID_ID;
	m_nPortraitID = INVALID_ID;
	m_nModelID = INVALID_ID;
	m_nMountID = INVALID_ID;
	m_uFaceMeshID = INVALID_ID;
	m_uHairMeshID = INVALID_ID;
	m_uHairColor = 0xFFFFFFFF;
	m_nStealthLevel = -1;
	m_nMoodState = INVALID_MOOD_STATE;

	m_Siller = 0;
	m_BindSiller = 0;
	m_Gold = 0;
	m_BindGold = 0;
	m_SillerMode = -1;
	m_nGoodBadValue = 0;
	m_nStr = -1;

	m_nCon = -1;
	m_nInt = -1;
	m_nDex = -1;
	m_nPointRemain = -1;
	m_nSkillPointRemain = -1;

	memset(m_nS_SkillPoints, 0, sizeof(int32) * COMMON_S_NUMBER);
	m_nReHpSpeed = -1;
	m_nReMpSpeed = -1;

	m_nAttNear = -1;
	m_nAttFar = -1;
	m_nAttMagic = -1;
	m_nDefNear = -1;
	m_nDefFar = -1;

	m_nDefMagic = -1;
	m_nToughness = -1;
	m_nHit = -1;
	m_nMiss = -1;
	m_nCritic = -1;
	m_nCriticHurt = -1;

	m_MaxRage = -1;
	m_nRage = -1;
	m_nStrikePoint = -1;

	m_nAttSpeed = -1;

	m_nAttCold = -1;
	m_nDefCold = -1;
	m_nAttFire = -1;
	m_nDefFire = -1;
	m_nAttLight = -1;
	m_nDefLight = -1;

	m_nAttPoison = -1;
	m_nDefPoison = -1;

	m_nNearReduce = -1;
	m_nFarReduce = -1;
	m_nMagicReduce = -1;
	m_nDreadReduce = -1;
	m_nComaReduce = -1;
	m_nHushReduce = -1;
	m_nUnarmReduce = -1;
	m_nAttSpeedResist = -1;
	m_nSkillSpeedResist = -1;
	m_nMoveSpeedResist = -1;

	m_nCountry = -1;
	m_nProfession = -1;

	m_nOwnerID = INVALID_ID;
	m_guidCurrentHorse.Reset();

	m_Vigor = -1;
	m_MaxVigor = -1;
	m_Energy = -1;
	m_MaxEnergy = -1;
	m_nWenCai = 0;
	m_nRongYu = 0;
	m_nShengWang = 0;
	m_nHotValue = 0;

	m_bLimitMove = FALSE;
	m_bTerran = FALSE;
	m_bCanActionFlag1 = FALSE;
	m_bCanActionFlag2 = FALSE;

	m_bQuestHaveDoneFlagsChanged = FALSE;

	m_bMainWeaponModified = FALSE;
	m_bAssiWeaponModified = FALSE;
	m_bCapModified = FALSE;
	m_bShoulderModified = FALSE;
	m_bArmorModified = FALSE;
	m_bCuffModified = FALSE;
	m_bBootModified = FALSE;
	m_bSuitModified = FALSE;
	m_bSoulModified = FALSE;
	m_bGemAffModified = FALSE;

	m_bStallIsOpen = FALSE;
	m_bStallNameChanged = FALSE;

	m_GuildID = INVALID_ID;
	m_bBusStateModified = FALSE;

	m_iTargetId = INVALID_ID;

	m_bTiredTimeModified = FALSE;

	m_nZoomScale = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _PLAYER_ATTR_BACKUP::Clear(void)
{
	m_bNameModified = FALSE;
	m_bNormalTitleModified = FALSE;
	m_bGuildTitleModified = FALSE;
	m_bCountryTitleModified = FALSE;
	m_Level = -1;
	m_Exp = -1;
	m_HP = -1;
	m_HPPercent = 100;
	m_HPGuardPercent = 100;
	m_MP = -1;
	m_MaxHp = -1;
	m_MaxMp = -1;
	m_MoveSpeed = -1;
	m_nMoveMode = -1;
	m_nDataID = INVALID_ID;
	m_nPortraitID = INVALID_ID;
	m_nModelID = INVALID_ID;
	m_nMountID = INVALID_ID;
	m_uFaceMeshID = INVALID_ID;
	m_uHairMeshID = INVALID_ID;
	m_uHairColor = 0xFFFFFFFF;
	m_nStealthLevel = -1;
	m_nMoodState = INVALID_MOOD_STATE;

	m_Siller = 0;
	m_BindSiller = 0;
	m_Gold = 0;
	m_BindGold = 0;
	m_SillerMode = -1;
	m_GoldMode = -1;
	m_nGoodBadValue = 0;
	m_nStr = -1;

	m_nCon = -1;
	m_nInt = -1;
	m_nDex = -1;
	m_nPointRemain = -1;
	m_nSkillPointRemain = -1;
	memset(m_nS_SkillPoints, 0, sizeof(int32) * COMMON_S_NUMBER);

	m_nReHpSpeed = -1;
	m_nReMpSpeed = -1;
	m_nAttNear = -1;
	m_nAttFar = -1;

	m_nAttMagic = -1;

	m_nDefNear = -1;
	m_nDefFar = -1;
	m_nDefMagic = -1;
	m_nToughness = -1;
	m_nHit = -1;
	m_nMiss = -1;
	m_nCritic = -1;
	m_nCriticHurt = -1;

	m_MaxRage = -1;
	m_nRage = -1;
	m_nStrikePoint = -1;

	m_nAttSpeed = -1;

	m_nAttCold = -1;
	m_nDefCold = -1;
	m_nAttFire = -1;
	m_nDefFire = -1;
	m_nAttLight = -1;
	m_nDefLight = -1;

	m_nAttPoison = -1;
	m_nDefPoison = -1;
	m_nNearReduce = -1;
	m_nFarReduce = -1;
	m_nMagicReduce = -1;
	m_nDreadReduce = -1;
	m_nComaReduce = -1;
	m_nHushReduce = -1;
	m_nUnarmReduce = -1;
	m_nAttSpeedResist = -1;
	m_nSkillSpeedResist = -1;
	m_nMoveSpeedResist = -1;

	m_nCountry = -1;
	m_nProfession = -1;
	m_CampData.Clear();
	m_nOwnerID = INVALID_ID;
	m_guidCurrentHorse.Reset();

	m_Vigor = -1;
	m_MaxVigor = -1;
	m_RegeneRate = 0;
	m_Energy = -1;
	m_MaxEnergy = -1;
	m_nGP = 0;
	m_nHonor = 0;
	m_nInherenceExp = 0;
	m_nInherenceLevel = 1;
	m_nPK = 0;
	m_nWenCai = 0;
	m_nRongYu = 0;
	m_nShengWang = 0;
	m_nHotValue = 0;

	m_bLimitMove = FALSE;
	m_bCanActionFlag1 = FALSE;
	m_bCanActionFlag2 = FALSE;
	m_bTerran = TRUE;
	m_bQuestHaveDoneFlagsChanged = FALSE;

	m_bMainWeaponModified = FALSE;
	m_bAssiWeaponModified = FALSE;
	m_bCapModified = FALSE;
	m_bShoulderModified = FALSE;
	m_bArmorModified = FALSE;
	m_bCuffModified = FALSE;
	m_bBootModified = FALSE;
	m_bSuitModified = FALSE;
	m_bSoulModified = FALSE;
	m_bGemAffModified = FALSE;

	m_bStallIsOpen = FALSE;
	m_bStallNameChanged = FALSE;

	m_GuildID = INVALID_ID;
	m_nTeamID = INVALID_ID;

	m_QuestListRefresh.Clear();
	m_bBusStateModified = FALSE;
	m_nPostCode = -1;
	m_iStrengthPerception = INVALID_ID;
	m_iSmartnessPerception = INVALID_ID;
	m_iMindPerception = INVALID_ID;
	m_iConstitutionPerception = INVALID_ID;
	m_byGeneration = INVALID_ID;

	m_iTargetId = INVALID_ID;
	m_nKillCountToday = 0;
	m_bTiredTimeModified = FALSE;
	m_nBattleHonour = 0;
	m_nPVP2V2_Mark = 0;
	m_nPVP2V2_Level = 0;
	m_nPVP2V2_Mark_WeekTotal = 0;
	m_nMerit = 0;
    m_iFeastScore = 0;
	m_nZoomScale = 0;
	m_WorldID = INVALID_ID;
}

extern eREFESH_PROPERTY_TYPE	Calc_RefeshAttrType(Character *pSour, Character *pTarget);

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Player::Player()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_EquipEffectNum = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_EffectSkillNum = 0;
	m_iTargetForExp = 0;

	m_pHumanNode = new _INIT_LIST_NODE(this);
	m_bCanSkillRelive = FALSE;

	m_EquipVer = 0;

	m_pShop = NULL;
	BankIsOpen = FALSE;




	KCheck(m_pAvoidOverlap);

	Clear();


	m_uAreaID = UINT_MAX;
	m_uAreaScript = UINT_MAX;

	


	m_bIsPasswdUnlock = FALSE;
	m_bProtectUnlock = FALSE;
	m_OnlinePasswdErrorCount = 0;





	m_pAI_Character = new Behavior_Player;
	KCheck(m_pAI_Character);

	m_iDataID = INVALID_ID;

	m_QuizGameCount = 0;
	m_QuizQuestionCycle = 0;
	m_QuizRightCount = 0;
	m_QuizWrongCount = 0;

	m_LoginProtectTime = 0;
	m_RemainProtectTime = 0;
	m_iLastUpdateEquipTerm = 0;
	for(int32_t i = 0; i < FIGHT_INFO_NUM; ++i)
	{
		m_aFightInfo[i].Clear();
	}


	m_bReconnect = FALSE;
	m_bInitBecauseReconnect = FALSE;

	m_ChatNearTimeStamp = 0;
	m_ChatWorldTimeStamp = 0;
	m_ChatUserTimeStamp = 0;
	m_ChatCountryTimeStamp = 0;
	m_ChatTooFastTimes = 0;
	m_MailTimeStamp = 0;
	m_MailTooFastTimes = 0;
	m_nChatReport_LastTime = 0;
	m_VipLevel = 0;
	m_IsBindPWCard = FALSE;
	m_IsBindPhone = FALSE;

	m_IsEnableStockAccount = FALSE;
	m_nElapsedVigorRecoverTick = 0;
	m_bReliveFlagforImpact = FALSE;

	m_ComposeNewPetDB.Clear();
	m_ComposeMainPetDB.Clear();
	m_bComposeRepent = FALSE;
	m_bComposeBest = FALSE;

	
	mDB = new PlayerArchive;

	printf("%p\n", mDB);
	

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Player::~Player()
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/




	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ConnectorID_t Player::GetPlayerID()
{
	return 0;
}

GUID_t	Player::GetGUID(void)const
{
	return mDB->GetGUID();
}

bool	Player::HeartBeat(uint32 uTime)
{
	if (false == Character::HeartBeat(uTime))
	{
		return false;
	}
	return true;
}

uint32 Player::GetUniqueID() const
{
	return GetGUID();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Player::Init(const _INIT_OBJECT *pInit, const uchar age)
{
	__GUARD__ if(!Character::Init(pInit)) return FALSE;


	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_OBJ_PLAYER_INIT	*pHumanInit = (_OBJ_PLAYER_INIT *) pInit;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pHumanInit != NULL)
	{
		if (pHumanInit->m_pUseData != NULL)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const CHARDBNODE* pData = pHumanInit->m_pUseData;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			mDB->WritePlayerArchive(&pData->m_Human);
			mDB->WriteEquipArchive(&pData->m_Equip);
			mDB->WriteBagArchive(&pData->m_Bag);
			mDB->WriteBankArchive(&pData->m_Bank);
			mDB->WriteSpellArchive(&pData->m_Skill);
			mDB->WriteCooldownArchive(&pData->m_CoolDownDB);
			mDB->WriteAbilityArchive(&pData->m_Ability);
			mDB->WriteImpactArchive(&pData->m_Impact);
			mDB->WriteQuestArchive(&pData->m_QuestDB);
			mDB->WritePetArchive(&pData->m_PetList);
			mDB->WriteBankPetArchive(&pData->m_BankPetList);
			mDB->WriteRelationArchive(&pData->m_Relation);
			mDB->WriteHonorRecordArchive(&pData->m_HonorRecord);
			mDB->WriteSettingArchive(&pData->m_Setting);
			mDB->WritePrivateInfoArchive(&pData->m_PrivateInfo);
			mDB->WriteMonsterPetArchive(&pData->m_dbMonsterPet);
			mDB->WriteSoldListArchive(&pData->m_SoldList);
			mDB->WritePlayerExtendInfoArchive(&pData->m_PlayerExtendInfo);
			
		}
	}

	SPlayerContainerInit	containInit;

	containInit.m_nContainerSize = mDB->GetBaseBagSize();
	containInit.m_pPlayerDB = mDB;
	containInit.m_ICTType = ICT_BASE_CONTAINER;
	containInit.m_DBOffSet = BASE_CONTAINER_OFFSET;

	m_BaseItem.Init(&containInit);

	for (uint32 i = 0; i < mDB->GetBaseBagSize(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		CItemInit	itemInit(mDB->GetBagItem(BASE_CONTAINER_OFFSET + i));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_BaseItem.GetItem(i)->Init(&itemInit);
	}
	//初始化扩展背包容器
	SPlayerItemExtraContainerInit	ExtracontainInit;

	ExtracontainInit.m_nContainerSize = mDB->GetExtraContainerSize();
	ExtracontainInit.m_pPlayerDB = mDB;
	ExtracontainInit.m_ICTType = ICT_EXTRA_CONTAINER;
	ExtracontainInit.m_DBOffSet = EXTRA_CONTAINER_OFFSET;

	m_ExtraContainerItem.Init(&ExtracontainInit);

	for (uint32 i = 0; i < mDB->GetExtraContainerSize(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		CItemInit	itemInit(mDB->GetBagItem(EXTRA_CONTAINER_OFFSET + i));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_ExtraContainerItem.GetItem(i)->Init(&itemInit);
	}

	//初始化扩展背包
	SPlayerItemExtrBagInit	ExtraBagInit;
	for (int32 nExtraBagIndex = 0; nExtraBagIndex < MAX_EXTRA_BAG_NUM; ++nExtraBagIndex)
	{
		ExtraBagInit.m_nContainerSize = 0;
		ExtraBagInit.m_pPlayerDB = mDB;
		ExtraBagInit.m_ICTType = ICT_EXTRABAG_CONTAINER;
		ExtraBagInit.m_DBOffSet = EXTRA_BAG_OFFSET(nExtraBagIndex);
		ExtraBagInit.m_pExtraBagItem = m_ExtraContainerItem.GetItem(nExtraBagIndex);
		m_ExtraBagItem[nExtraBagIndex].Init(&ExtraBagInit);
	}

	containInit.m_nContainerSize = HEQUIP_NUMBER;
	containInit.m_ICTType = ICT_EQUIP_CONTAINER;
	containInit.m_DBOffSet = EQUIP_CONTAINER_OFFSET;

	m_EquipItem.Init(&containInit);
	for (uint32 i = 0; i < HEQUIP_NUMBER; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		CItemInit	itemInit(mDB->GetEquipItem((PLAYER_EQUIP)i));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_EquipItem.GetItem(i)->Init(&itemInit);
	}

	SHorseContainerInit	PetContainInit;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	PetContainInit.m_nContainerSize = PLAYER_PET_MAX_COUNT;
	PetContainInit.m_pPlayerDB = mDB;
	PetContainInit.m_ICTType = ICT_HUMAN_PET_CONTAINER;

	m_PetItem.Init(&PetContainInit);
	for (uint32 i = 0; i < PLAYER_PET_MAX_COUNT; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		CItemInit	itemInit(mDB->GetPet(i));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_PetItem.GetItem(i)->Init(&itemInit);
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	RefreshIntervalTime = 5000;
	uint32	CreateTime = GET_TIME().TickCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	m_RefeshTimer.BeginTimer(RefreshIntervalTime, CreateTime);

	m_AttrBackUp.m_bQuestHaveDoneFlagsChanged = TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	AttrUpdateIntervalTime = DB_2_SM_TIME;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_UpdateTimer.BeginTimer(AttrUpdateIntervalTime, CreateTime);
	m_ItemTimer.BeginTimer(5000, CreateTime);





	m_EquipEffectNum = 0;
	m_EffectSkillNum = 0;
	





	GET_TIME().Update();

	memset(m_pItemEffect, 0, sizeof(SItemEffect) * IPROPERTY_NUMBER);

	reset_AbilityOpera();

	return TRUE;

	__UNGUARD__ return FALSE;
}

void		Player::InitHorseUsedSkillList()
{
	if (GetGUIDOfCallUpHorse().IsNull())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = GetHorseIndexByGUID(GetGUIDOfCallUpHorse());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iIndex == INVALID_ID)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB* pPetDB = GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pPetDB)
	{
		return;
	}

	for (int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		if (pPetDB->m_SkillList[i].m_bCanUse == FALSE || pPetDB->m_SkillList[i].m_nSkillID == INVALID_ID)
		{
			continue;
		}

		StartPassiveSkillList(pPetDB->m_SkillList[i].m_nSkillID, 1, i);
	}
}

void		Player::StartPassiveSkillList(SpellID_t iSkillID, int32 iSkillLevel, int32 iIndex)
{
	const SpellTemplateData* pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTemplate)
	{
		return;
	}

	if (pTemplate->GetPassiveFlag() <= 0)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SpellInstanceData* pInstance = DataManager::GetSingletonPtr()->getSpellInstance(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pInstance == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const Descriptor* pDescriptor = pInstance->GetDescriptorByIndex(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pDescriptor == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDataIndex = pDescriptor->GetValueBySkillLevel(iSkillLevel - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetHorseDataIndex(iIndex, iDataIndex);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::InitHorseIfRide()
{
	SHorseGuid	HorseGUID = GetDB()->GetCurrentPetGUID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (HorseGUID.IsNull())
	{
		ReCallHorse();
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = GetHorseIndexByGUID(HorseGUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iIndex == INVALID_ID)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB* pPetDB = GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetMountID(pPetDB->m_iModelID);
	SetMountModelID(pPetDB->m_iModelID);

	m_ActiveHorse.ResetCallUpHorse(FALSE);

	InitHorseUsedSkillList();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::OnEnterMapSuccess(void)
{
	((Behavior_Player *) GetAIObj())->ClearTargetList();

	GetAIObj()->ChangeState(ESTATE_IDLE);

	
	InitHorseIfRide();

	Character::OnEnterMapSuccess();



	/*~~~~~~~~~~~~~~~~~~*/
	int32_t	iHP = GetHP();
	/*~~~~~~~~~~~~~~~~~~*/

	if(iHP > GetMaxHP())
	{
		SetHP(GetMaxHP());
	}

	/*~~~~~~~~~~~~~~~~~~*/
	int32_t	iMP = GetMP();
	/*~~~~~~~~~~~~~~~~~~*/

	if(iMP > GetMaxMP())
	{
		SetMP(GetMaxMP());
	}

	




}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::OnEnterMap(void)
{
	Character::OnEnterMap();

	SetGLPos(GetDB()->GetDBPosition());

	SCEnterMap* packet = new SCEnterMap;
	
	packet->setActorID(GetID(), this->GetGUID());
	const GLPos* pos = GetGLPos();
	packet->setPosition(pos->m_fX, pos->m_fZ);
	packet->setSceneId(GetMap()->MapID());


	NetManager::GetSingletonPtr()->sendNetMessage(packet);

	SetActiveFlag(true);

	OnEnterMapSuccess();

	
	updateAttr();
	updateHorse();
	updateSkills();
	updateEquip();

	updateBag();

	updateQuest();

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::ValidatePlayerID()
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::InitAIObj()
{
	int kk = 0;
	m_pAI_Character->Init(this);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::Clear(void)
{
	
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::OnRegisterToGrid(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character::	OnRegisterToGrid();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::OnUnregisterFromGrid()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character::	OnUnregisterFromGrid();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_paramLogic_Move.Reset();
	((Behavior_Player *) (GetAIObj()))->GetBehavior_State()->Stop((Behavior_Player *) (GetAIObj()));
	__UNGUARD__
}

void	Player::OnEvent_KillObject(ObjID_t idObj)
{
	Character* pObj = (Character*)(GetMap()->GetSpecificObjByID(idObj));

	if (pObj == NULL)
		return;
	m_iTargetForExp = idObj;

	QuestManager::GetSingletonPtr()->OnEvent_KillObject(this, pObj);
}

void	Player::OnEvent_PetChanged(uint32 uPetDataID)
{
	QuestManager::GetSingletonPtr()->OnEvent_PetChanged(this, uPetDataID);
}

void Player::OnEvent_ItemChanged(uint32 uItemDataID, int32 nChangeType)
{
	__GUARD__;

	QuestManager::GetSingletonPtr()->OnEvent_ItemChanged(this, uItemDataID, nChangeType);

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Player::IsFirstEnterGame()
{
	return false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::ClearFirstEnterGame()
{
	
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::ValidateShareMem(BOOL bForceAll)
{
	
}

/*
 =======================================================================================================================
 怒气恢复时间
 =======================================================================================================================
 */
void Player::ClearRageRecoverTick(void)
{
	
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Player::CheckArea()
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Player::GetPosition(GLPos &Pos, const GLPos *pRefPos, float fDir)
{
	Pos.m_fX = pRefPos->m_fX - sin(fDir);
	Pos.m_fZ = pRefPos->m_fZ - cos(fDir);
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t Player::GetHPNoClip(void)
{
	return 100;
}

void Player::CalculatePetDetailAttrib
(
	SCDetailAttribPet& rMsg,
	Item* pPetItem,
	BOOL bUpdateSkill,
	int32 iIndex
)
{
	if (!pPetItem)
	{
		return;
	}

	if (pPetItem->GetHorseGUID().IsNull())
	{
		return;
	}
	auto horseGuid = pPetItem->GetHorseGUID();
	rMsg.setHorseGuid(horseGuid);
	rMsg.setIndex(iIndex);
	rMsg.setDataID(pPetItem->GetDataID());
	rMsg.setName(pPetItem->GetName());
	rMsg.setNickName(pPetItem->GetNick());
	rMsg.setHP(pPetItem->GetHP());
	rMsg.setAIType(pPetItem->GetAIType());
	rMsg.setLevel(pPetItem->GetLevel());
	rMsg.setGeneration(pPetItem->GetGeneration());
	rMsg.setHappiness(pPetItem->GetHappiness());
	rMsg.setExp(pPetItem->GetExp());

	rMsg.setStrPerception(pPetItem->GetStrengthPer());
	rMsg.setConPerception(pPetItem->GetConstitutionPer());
	rMsg.setDexPerception(pPetItem->GetSmartnessPer());
	rMsg.setIntPerception(pPetItem->GetMindPer());
	if (pPetItem->IsMating())
	{
		rMsg.setHorseState(SCDetailAttribPet::HorseState_Mating);
	}

	rMsg.setStrength(pPetItem->GetLvl1Attr(CPROPERTY_LEVEL1_STR));
	rMsg.setCon(pPetItem->GetLvl1Attr(CPROPERTY_LEVEL1_CON));
	rMsg.setDex(pPetItem->GetLvl1Attr(CPROPERTY_LEVEL1_DEX));
	rMsg.setIntelligence(pPetItem->GetLvl1Attr(CPROPERTY_LEVEL1_INT));

	rMsg.setHPMax(pPetItem->Get_BaseProperty_MaxHP());
	rMsg.setLevel(pPetItem->GetLevel());


	_HORSE_ATTR_TBL* horseAttrTable = DataManager::GetSingletonPtr()->getHorseAttrTable();
	rMsg.setModelID(horseAttrTable->m_aHorseTbl[pPetItem->GetDataID()].m_iBehaveID);
	rMsg.setMountID(pPetItem->GetHorseModelID());
	rMsg.setRemainPoint(pPetItem->GetRemainPoint());

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iGeneration = pPetItem->GetGeneration();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iGeneration < 1)
	{
		iGeneration = 1;
	}

	_HORSE_PER_LIMIT_TBL* horsePerlimitTable = DataManager::GetSingletonPtr()->getHorsePerlimitTable();

	if (iGeneration > horsePerlimitTable->m_iCount)
	{
		iGeneration = horsePerlimitTable->m_iCount;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iPerLimit = horsePerlimitTable->m_aLimit[iGeneration - 1];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rMsg.setStrPerceptionLimit(iPerLimit);
	rMsg.setConPerceptionLimit(iPerLimit);
	rMsg.setDexPerceptionLimit(iPerLimit);
	rMsg.setIntPerceptionLimit(iPerLimit);

	if (pPetItem->IsCompose())			//上线后将合成坐骑解锁
	{
		if (pPetItem->IsPetLocked() == PET_LOCK)
		{
			pPetItem->SetPetUnLock();
		}
		pPetItem->SetPetStatus(_HORSE_DB::PET_STATUS_NULL);
	}
	rMsg.setPetLock(pPetItem->IsPetLocked());
	rMsg.setUnLockTime(pPetItem->GetPetUnLockTime());
	rMsg.setStrengthPoint(pPetItem->GetStrengthPoint());
	rMsg.setConstitutionPoint(pPetItem->GetConstitutionPoint());
	rMsg.setSmartnessPoint(pPetItem->GetSmartnessPoint());
	rMsg.setMindPoint(pPetItem->GetMindPoint());

	rMsg.setGrowRate((int32)pPetItem->GetGrowRate());

	rMsg.setStallOrder(pPetItem->GetStallOrder());
	if (!bUpdateSkill)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	SHorseSkill	ownSkill;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < PET_MAX_SKILL_COUNT; i++)
	{
		ownSkill = pPetItem->GetSkill(i);
		rMsg.SetSkill(i, &ownSkill);
	}
}

void Player::RefeshHorseDetailAttrib(SHorseGuid guidPet, BOOL bUpdateSkill)
{
	if (guidPet.IsNull())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item* pPetItem = GetHorseItem(guidPet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pPetItem)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = GetHorseIndexByGUID(guidPet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (INVALID_ID == iIndex)
	{
		return;
	}

	SCDetailAttribPet* packet = new SCDetailAttribPet;
	CalculatePetDetailAttrib(*packet, pPetItem, bUpdateSkill, iIndex);
	NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

OPT_RESULT Player::TestCallUpPet(const SHorseGuid guidPet)
{
	__GUARD__ return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Player::CallUpPet(void)
{
	 return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Player::ReCallHorse(void)
{
	if (FALSE == IsActiveObj()) return OR_ERROR;
	if (CST_SCENE_CHANGEING == GetChangeMapState()) return OR_ERROR;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	SHorseGuid	oPetGUID;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	CleanupHorseBuff();
	SetMountID(INVALID_ID);
	HorseEventScript(HORSE_CALL_SCRIPT_OFF);
	ChangeCallUpHorse(oPetGUID);
	SetMountModelID(-1);
	MarkLevelOneAttrDirtyFlag();

	return OR_OK;
}




/*
 =======================================================================================================================
 添加骑乘到玩家身上
 =======================================================================================================================
 */
BOOL Player::AddHorse(_HORSE_DB *pPetDB)
{
	//指针检查
	if (pPetDB == NULL)
		return FALSE;

	//查找空位置
	int32 iFind = 0;;
	for (; iFind < PLAYER_PET_MAX_COUNT; iFind++)
	{
		Item* pPetFind = GetPetContain()->GetItem(iFind);
		if (pPetFind != NULL && pPetFind->IsLock() == FALSE)
		{
			SHorseGuid guidFind = pPetFind->GetHorseGUID();
			if (guidFind.IsNull())
			{
				break;
			}
		}
	}

	//检查查找结果
	if (iFind >= PLAYER_PET_MAX_COUNT)
	{
		//骑乘已满
		SendOperateResultMsg(OR_HORSE_FULL, 0);
		return FALSE;
	}
	else
	{
		//设置骑乘数据
		sItemInterface.SetItemValue(GetPetContain(), iFind, pPetDB);
		RefeshHorseDetailAttrib(pPetDB->m_GUID, TRUE);
		OnEvent_PetChanged(pPetDB->m_nDataID);
	}

	return TRUE;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Player::RemovePet(PetLogRecordInfo *pPetLogParam, SHorseGuid guid)
{
	__GUARD__ return FALSE;

	__UNGUARD__ return FALSE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT Player::FreePetToNature(PetLogRecordInfo *pPetLogParam, SHorseGuid guidPet)
{
	__GUARD__ return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

void Player::BabyToAttack(void)
{
	
}

void Player::BabyToStopAttack(void)
{
	
}

void Player::BabyToProtectMe(ObjID_t iObjID)
{
	
}

int32	Player::GetMonsterPetDataID() const
{
	return m_iDataID;
}

void Player::SetMonsterPetDataID(int32 val)
{
	m_iDataID = val;
}

void Player::SetMountModelID(int32 nModelID)
{
	mDB->SetMountModelID(nModelID);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Player::CaptureHorse(PetLogRecordInfo *pPetLogParam, ObjID_t PetID)
{
	Object* pObj = GetMap()->GetSpecificObjByID(PetID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pObj || pObj->GetObjType() != Object::OBJECT_CLASS_HORSE || !((Character*)pObj)->IsAlive())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Horse* pHorse = (Horse*)pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!pHorse)
	{
		KCheck(NULL && "Player::CapturePet...pPet=NULL...");
		return FALSE;
	}

	if (NULL != pHorse->GetOwner())
	{
		SendOperateResultMsg(OR_INVALID_TARGET, 0);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nTakeLevel = pHorse->GetPetDB()->m_nTakeLevel;
	_HORSE_ATTR* pAttr = DataManager::GetSingletonPtr()->getHorseAttr(pHorse->GetDataID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (GetLevel() < nTakeLevel)
	{
		// rj 2010-8-23 加入天赋与个人等级并行条件, 新的条件成为与原条件"或"的关系, 忽略全 -1 值的比较
		if (pAttr == NULL || (pAttr->m_iReqInherenceLevel == -1 && pAttr->m_iReqPersonLevel == -1) ||
			(int32)GetInherenceLevel() < pAttr->m_iReqInherenceLevel || GetLevel() < pAttr->m_iReqPersonLevel)

		{
			SendOperateResultMsg(OR_NEED_HIGH_LEVEL, 0);
			return FALSE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nCapturerCount = pHorse->GetCaptureCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!nCapturerCount) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB* pPetDB = const_cast<_HORSE_DB*>(pHorse->GetPetDB());
	BOOL	bResult = GetMap()->GetHorseManager()->CreateGUIDOfHorse(pPetDB, GetID(), PetID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!bResult)
	{
		return FALSE;
	}

	return AddHorseToHuman(pPetDB, pPetLogParam);
}

BOOL Player::CaptureBeastie(PetLogRecordInfo* pPetLogParam, ObjID_t beastieID)
{
	return FALSE;
}

BOOL Player::AddHorseToHuman(_HORSE_DB* pPetDB, PetLogRecordInfo* pPetLogParam)
{
	if (!IsCanTakeMoreHorse())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bResult = AddHorse(pPetDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!bResult)
	{
		return FALSE;
	}
	return TRUE;
}

int32_t Player::GetHorseCount(void) const
{
	return 0;
}

_HORSE_DB *Player::GetHorseDB(int32_t nIndex) const
{
	if (nIndex < 0 || nIndex >= PLAYER_PET_MAX_COUNT)
	{
		return NULL;
	}

	if (mDB->m_dbPetList->m_aPetDB[nIndex].m_GUID.IsNull()) return NULL;

	return &(mDB->m_dbPetList->m_aPetDB[nIndex]);
}

_HORSE_DB *Player::GetEmptyHorseDB()
{
	for (int32 i = 0; i < PLAYER_PET_MAX_COUNT; i++)
	{
		if (mDB->m_dbPetList->m_aPetDB[i].m_GUID.IsNull())
		{
			return &(mDB->m_dbPetList->m_aPetDB[i]);
		}
	}

	return nullptr;
}

Item* Player::GetHorseItem(SHorseGuid guid)
{
	Item* pPetItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pPetFind = GetPetContain()->GetItem(i);
		SHorseGuid	guidFind = pPetFind->GetHorseGUID();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if ((guidFind == guid))
		{
			pPetItem = pPetFind;
			break;
		}
	}

	return pPetItem;
}


int32 Player::GetHorseIndexByGUID(SHorseGuid guid)
{
	Item* pPetItem = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pPetFind = GetPetContain()->GetItem(i);
		SHorseGuid	guidFind = pPetFind->GetHorseGUID();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if ((guidFind == guid))
		{
			return i;
		}
	}

	return -1;
}

SHorseGuid	Player::GetGUIDOfCallUpHorse()
{
	return mDB->GetCurrentPetGUID();
}

void Player::ChangeCallUpHorse(SHorseGuid val)
{
	SHorseGuid	oldVal = mDB->GetCurrentPetGUID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mDB->SetCurrentPetGUID(val);

	if (!val.IsNull())
	{
		m_ActiveHorse.ResetCallUpHorse(TRUE);

		oldVal.Reset();
		SetLastHorseGuid(oldVal);
	}
	else
	{
		m_ActiveHorse.Clear();

		SetLastHorseGuid(oldVal);
	}
}

bool Player::UpdateHorseExp(int32 iExp)
{
	return m_ActiveHorse.OnExpChange(iExp);
}

bool Player::UpdateHorseExpAbsolute(int32 iExp)
{
	return m_ActiveHorse.OnExpChange(iExp, FALSE, TRUE, FALSE);
}

SHorseGuid	Player::GetLastHorseGuid()
{
	return m_guidLastHorse;
}

void Player::SetLastHorseGuid(SHorseGuid horseGuid)
{
	m_guidLastHorse = horseGuid;
}

void	Player::HorseEventScript(int32 iReason)
{
	SHorseGuid	idHorse = GetGUIDOfCallUpHorse();
	int32			iIndex = GetHorseIndexByGUID(idHorse);
	_HORSE_DB* pPetDB = GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pPetDB)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_ATTR* pAttr = DataManager::GetSingletonPtr()->getHorseAttr(pPetDB->m_nDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pAttr)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptID_t	iScriptID = pAttr->m_iScriptID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iScriptID <= 0)
	{
		return;
	}

	LuaSystem* luaSystem = ServerManager::GetSingletonPtr()->getLuaSystem();

	luaSystem->RunScriptFunction
	(
		GetMap()->MapID(),
		iScriptID,
		DEF_PROC_EVENT_ENTRY_FN,
		GetMap()->MapID(),
		(int32)GetID(),
		pPetDB->m_nDataID,
		iReason
	);
}

void Player::HorseHeartBeat(uint32 uTime)
{
	m_ActiveHorse.HeartBeat(uTime);
}

BOOL Player::IsCanTakeMoreHorse(int32 nCount)
{
	if(GetHorseCount() >= PLAYER_PET_MAX_COUNT)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLevel = GetLevel();
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	iLevel -= g_Config.m_ConfigInfo.m_CaptureHorseMinPlayerLevel;
	if(0 > iLevel)
	{
		SendOperateResultMsg(OR_NEED_HIGH_LEVEL, 0);
		return FALSE;
	}

	iLevel = (iLevel / g_Config.m_ConfigInfo.m_TakeHorseNumIncLevelStep) + nCount;
	if(GetHorseCount() < iLevel)
	{
		return TRUE;
	}
	return FALSE;
}

int32_t Player::GetRuntimeData(int32_t index)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(index >= 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(index < MAX_RUNTIME_DATA);
	return m_RuntimeData[index];

	__UNGUARD__ return INVALID_ID;
}

void Player::SetRuntimeData(int32_t index, int32_t value)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(index >= 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(index < MAX_RUNTIME_DATA);
	m_RuntimeData[index] = value;

	__UNGUARD__
}

void Player::sendPacket(NetPacket* packet)
{
	NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

float	Player::Get_Property_MoveSpeed(void)
{
	SItemEffect* pIE = NULL;


	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVE_SPEED))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = Get_BaseProperty_MoveSpeed();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_SPEED_MOVE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_SPEED_MOVE_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix += pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED);
		nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + nItemRateRefix;
		SetIntAttr(CharIntProperty::PROPERTY_MOVE_SPEED, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVE_SPEED);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fMoveSpeed = GetIntAttr(CharIntProperty::PROPERTY_MOVE_SPEED) * 0.001f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return fMoveSpeed;
}

int32_t	Player::Get_BaseProperty_MoveSpeed(void)
{
	ENUM_MOVE_MODE	eMoveMode = GetMoveMode();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (eMoveMode == MOVE_MODE_WALK)
	{
		return g_Config.m_ConfigInfo.m_DefaultWalkSpeed;
	}

	return g_Config.m_ConfigInfo.m_DefaultMoveSpeed;
}

void	Player::Set_BaseProperty_MoveSpeed(int32_t const nValue)
{

}

int32_t	Player::Get_Property_AttackSpeed(void)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_SPEED))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = Get_BaseProperty_AttackSpeed();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_ATTACK_SPEED);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_SPEED);
		nValue = nBaseAttr - nImpactAndSkillRefix - nItemPointRefix;
		nValue < 0 ? nValue = 0 : NULL;
		if (400 < nValue)
		{
			nValue = 400;
		}

		if (25 >= nValue)
		{
			nValue = 25;
		}

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_SPEED, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_SPEED);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_SPEED);
}
int32_t	Player::Get_BaseProperty_AttackSpeed(void)
{
	return 0;
}
void	Player::Set_BaseProperty_AttackSpeed(int32_t const nValue)
{

}

int32_t	Player::Get_Property_Miss(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_Miss(void)
{
	return 0;
}
void	Player::Set_BaseProperty_Miss(int32_t const nValue)
{

}

int32				Player::GetIattributeMiss()
{
	int32 nMiss = 0;
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pIE = ItemEffect(IPROPERTY_MISS);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nMiss += pIE->m_Attr.m_Value;
	}

	pIE = ItemEffect(IPROPERTY_MISS_PURPLE);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nMiss += pIE->m_Attr.m_Value;
	}

	return nMiss;
}

int32_t	Player::Get_Property_Hit(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HIT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32 nBaseAttr = GetAttrLevel1Hit();
		int32 nImpactAndSkillRefix = 0;
		int32 nItemPointRefix = 0;
		int32 nItemRateRefix = 0;
		int32 nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nItemPointRefix = GetIattributeHit();

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_HIT);
		nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + nItemRateRefix;
		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_HIT, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HIT);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_HIT);
}
int32_t	Player::Get_BaseProperty_Hit(void)
{
	return 0;
}
void	Player::Set_BaseProperty_Hit(int32_t const nValue)
{

}

int32				Player::GetIattributeHit()
{
	int32 nHit = 0;
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pIE = ItemEffect(IPROPERTY_HIT);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nHit += pIE->m_Attr.m_Value;
	}

	pIE = ItemEffect(IPROPERTY_HIT_PURPLE);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nHit += pIE->m_Attr.m_Value;
	}

	return nHit;
}


int32				Player::GetIattributeCritiacalRefix()
{
	int32 nICR = 0;
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pIE = ItemEffect(IPROPERTY_CRIT);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nICR += pIE->m_Attr.m_Value;
	}

	pIE = ItemEffect(IPROPERTY_CRIT_PURPLE);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nICR += pIE->m_Attr.m_Value;
	}

	return nICR;
}


int32_t	Player::GetEquipCriticalHurt()
{
	int32 nIE = 0;
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	pIE = ItemEffect(IPROPERTY_CRIT_HURT);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nIE += pIE->m_Attr.m_Value;
	}

	pIE = ItemEffect(IPROPERTY_CRIT_HURT_PURPLE);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		nIE += pIE->m_Attr.m_Value;
	}

	return nIE;
}

int32_t				Player::GetCriticalHurt()
{
	int32 nValue = g_Config.m_ConfigInfo.m_nCriticalDamageRate +
		GetEquipCriticalHurt() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL_HURT);
	//GetCriticalHurtRefix();
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nValue;
}

int32_t	Player::Get_Property_Critical(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_Critical(void)
{
	return 0;
}
void	Player::Set_BaseProperty_Critical(int32_t const nValue)
{

}

int32_t	Player::GetDefenceNear(void)
{
	return 0;
}
int32_t	Player::GetBaseDefenceNear(void)
{
	return 0;
}
void	Player::SetBaseDefenceNear(int32_t const nValue)
{

}

int32_t	Player::GetDefenceFar(void)
{
	return 0;
}
int32_t	Player::GetBaseDefenceFar(void)
{
	return 0;
}
void	Player::SetBaseDefenceFar(int32_t const nValue)
{

}

int32_t	Player::GetAttackNear(void)
{
	return 60;
}
int32_t	Player::GetBaseAttackNear(void)
{
	return 0;
}
void	Player::SetBaseAttackNear(int32_t const nValue)
{

}

int32	Player::GetAttackFar(void)
{
	return 0;
}
int32_t	Player::GetBaseAttackFar(void)
{
	return 0;
}
void	Player::SetBaseAttackFar(int32_t const nValue)
{

}

int32_t	Player::GetToughness(void)
{
	return 0;
}
int32_t	Player::GetBaseToughness(void)
{
	return 0;
}
void	Player::SetBaseToughness(int32_t const nValue)
{

}

int32_t	Player::GetNearAttReduce(void)
{
	return 0;
}
int32_t	Player::GetBaseNearAttReduce(void)
{
	return 0;
}
void	Player::SetBaseNearAttReduce(int32_t const nValue)
{

}

int32_t	Player::GetFarAttReduce(void)
{
	return 0;
}
int32_t	Player::GetBaseFarAttReduce(void)
{
	return 0;
}
void	Player::SetBaseFarAttReduce(int32_t const nValue)
{

}

int32_t	Player::GetMagicAttReduce(void)
{
	return 0;
}
int32_t	Player::GetBaseMagicAttReduce(void)
{
	return 0;
}
void	Player::SetBaseMagicAttReduce(int32_t const nValue)
{

}

int32_t	Player::GetDreadAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseDreadAttResist(void)
{
	return 0;
}
void	Player::SetBaseDreadAttResist(int32_t const nValue)
{

}

int32_t	Player::GetComaAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseComaAttResist(void)
{
	return 0;
}
void	Player::SetBaseComaAttResist(int32_t const nValue)
{

}

int32_t	Player::GetHushAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseHushAttResist(void)
{
	return 0;
}
void	Player::SetBaseHushAttResist(int32_t const nValue)
{

}

int32_t	Player::GetUnArmyAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseUnArmyAttResist(void)
{
	return 0;
}
void	Player::SetBaseUnArmyAttResist(int32_t const nValue)
{

}

int32_t	Player::GetAttSpeedAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseAttSpeedAttResist(void)
{
	return 0;
}
void	Player::SetBaseAttSpeedAttResist(int32_t const nValue)
{

}

int32_t	Player::GetSkillSpeedAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseSkillSpeedAttResist(void)
{
	return 0;
}
void	Player::SetBaseSkillSpeedAttResist(int32_t const nValue)
{

}

int32_t	Player::GetMoveSpeedAttResist(void)
{
	return 0;
}
int32_t	Player::GetBaseMoveSpeedAttResist(void)
{
	return 0;
}
void	Player::SetBaseMoveSpeedAttResist(int32_t const nValue)
{

}

int32_t	Player::Get_Property_AttackMagic(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_AttackMagic(void)
{
	return 0;
}
void	Player::Set_BaseProperty_AttackMagic(int32_t const nValue)
{

}

int32_t	Player::Get_Property_DefenceMagic(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_DefenceMagic(void)
{
	return 0;
}
void	Player::Set_BaseProperty_DefenceMagic(int32_t const nValue)
{

}

int32_t	Player::Get_Property_AttackCold(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_AttackCold(void)
{
	return 0;
}
void	Player::Set_BaseProperty_AttackCold(int32_t const nValue)
{

}

int32_t	Player::Get_Property_DefenceCold(void)
{
	return 0;
}

int32_t	Player::Get_BaseProperty_DefenceCold(void)
{
	return 0;
}
void	Player::Set_BaseProperty_DefenceCold(int32_t const nValue)
{

}

int32	Player::Get_Property_AttackFire(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_AttackFire(void)
{
	return 0;
}
void	Player::Set_BaseProperty_AttackFire(int32_t const nValue)
{

}

int32_t	Player::Get_Property_DefenceFire(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_DefenceFire(void)
{
	return 0;
}
void	Player::Set_BaseProperty_DefenceFire(int32_t const nValue)
{

}

int32_t	Player::Get_Property_AttackLight(void)
{
	return 0;
}

int32_t	Player::Get_BaseProperty_AttackLight(void)
{
	return 0;
}
void	Player::Set_BaseProperty_AttackLight(int32_t const nValue)
{

}

int32_t	Player::Get_Property_DefenceLight(void)
{
	return 0;
}

int32_t	Player::Get_BaseProperty_DefenceLight(void)
{
	return 0;
}
void	Player::Set_BaseProperty_DefenceLight(int32_t const nValue)
{

}

int32_t	Player::Get_Property_AttackPoison(void)
{
	return 0;
}

int32_t	Player::Get_BaseProperty_AttackPoison(void)
{
	return 0;
}
void	Player::Set_BaseProperty_AttackPoison(int32_t const nValue)
{
}

int32_t	Player::Get_Property_DefencePoison(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_DefencePoison(void)
{
	return 0;
}
void	Player::Set_BaseProperty_DefencePoison(int32_t const nValue)
{

}

int32_t	Player::Get_Property_ReduceSlowerDuration(void)
{
	return 0;
}

int32_t	Player::Get_Property_ReduceWeakenDuration(void)
{
	return 0;
}

int32_t	Player::Get_Property_ReduceFaintDuration(void)
{
	return 0;
}

int32_t	Player::Get_Property_ReducePoisonedDuration(void)
{
	return 0;
}


int32_t Player::Get_Property_Rage(void)
{
	if (mDB->Get_Property_Rage() > Get_Property_MaxRage())
	{
		mDB->Set_Property_Rage(Get_Property_MaxRage());
	}

	return mDB->Get_Property_Rage();
}

void	Player::Set_Property_Rage(int32_t nRage)
{
	if (0 > nRage)
	{
		nRage = 0;
	}

	if (nRage > Get_Property_MaxRage())
	{
		nRage = Get_Property_MaxRage();
	}

	mDB->Set_Property_Rage(nRage);
}

int32_t	Player::GetVisionRange(void)
{
	return 0;
}


int32				Player::GetProfessionReduce(int32 nTarProfession)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nItemPointRefix = 0;

	if (nTarProfession <= PROFESSION_UNKNOW || nTarProfession >= PROFESSION_NUMBER)
	{
		return nItemPointRefix;
	}

	switch (nTarProfession)
	{
	case PROFESSION_WUSHI:
		pIE = ItemEffect(IPROPERTY_WUSHI_HURT_RESIST);
		break;
	case PROFESSION_JIANXIA:
		pIE = ItemEffect(IPROPERTY_JIANXIA_HURT_RESIST);
		break;
	case PROFESSION_QISHE:
		pIE = ItemEffect(IPROPERTY_QISHE_HURT_RESIST);
		break;
	case PROFESSION_HUOQIANG:
		pIE = ItemEffect(IPROPERTY_HUOQIANG_HURT_RESIST);
		break;
	case PROFESSION_XIANZHI:
		pIE = ItemEffect(IPROPERTY_XIANZHI_HURT_RESIST);
		break;
	case PROFESSION_SAMAN:
		pIE = ItemEffect(IPROPERTY_SAMAN_HURT_RESIST);
		break;
	case PROFESSION_SHIZIJUN:
		pIE = ItemEffect(IPROPERTY_SHIZIJUN_HURT_RESIST);
		break;
	case PROFESSION_SHENGHUOSHI:
		pIE = ItemEffect(IPROPERTY_SHENGHUOSHI_HURT_RESIST);
		break;
	case PROFESSION_CIKE:
		pIE = ItemEffect(IPROPERTY_CIKE_HURT_RESIST);
		break;
	case PROFESSION_JINWEIJUN:
		pIE = ItemEffect(IPROPERTY_JINWEIJUN_HURT_RESIST);
		break;
	case PROFESSION_YINXIUSHI:
		pIE = ItemEffect(IPROPERTY_YINXIUSHI_HURT_RESIST);
		break;
	case PROFESSION_LAMA:
		pIE = ItemEffect(IPROPERTY_LAMA_HURT_RESIST);
		break;
	}

	KCheck(pIE);
	if (pIE->IsActive())
	{
		nItemPointRefix = pIE->m_Attr.m_Value;
	}

	return nItemPointRefix;
}

int32				Player::GetProfessionIncrease(int32 nTarProfession)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nItemPointRefix = 0;

	if (nTarProfession <= PROFESSION_UNKNOW || nTarProfession >= PROFESSION_NUMBER)
	{
		return nItemPointRefix;
	}

	switch (nTarProfession)
	{
	case PROFESSION_WUSHI:
		pIE = ItemEffect(IPROPERTY_WUSHI_HURT_INCREASE);
		break;
	case PROFESSION_JIANXIA:
		pIE = ItemEffect(IPROPERTY_JIANXIA_HURT_INCREASE);
		break;
	case PROFESSION_QISHE:
		pIE = ItemEffect(IPROPERTY_QISHE_HURT_INCREASE);
		break;
	case PROFESSION_HUOQIANG:
		pIE = ItemEffect(IPROPERTY_HUOQIANG_HURT_INCREASE);
		break;
	case PROFESSION_XIANZHI:
		pIE = ItemEffect(IPROPERTY_XIANZHI_HURT_INCREASE);
		break;
	case PROFESSION_SAMAN:
		pIE = ItemEffect(IPROPERTY_SAMAN_HURT_INCREASE);
		break;
	case PROFESSION_SHIZIJUN:
		pIE = ItemEffect(IPROPERTY_SHIZIJUN_HURT_INCREASE);
		break;
	case PROFESSION_SHENGHUOSHI:
		pIE = ItemEffect(IPROPERTY_SHENGHUOSHI_HURT_INCREASE);
		break;
	case PROFESSION_CIKE:
		pIE = ItemEffect(IPROPERTY_CIKE_HURT_INCREASE);
		break;
	case PROFESSION_JINWEIJUN:
		pIE = ItemEffect(IPROPERTY_JINWEIJUN_HURT_INCREASE);
		break;
	case PROFESSION_YINXIUSHI:
		pIE = ItemEffect(IPROPERTY_YINXIUSHI_HURT_INCREASE);
		break;
	case PROFESSION_LAMA:
		pIE = ItemEffect(IPROPERTY_LAMA_HURT_INCREASE);
		break;
	}

	KCheck(pIE);
	if (pIE->IsActive())
	{
		nItemPointRefix = pIE->m_Attr.m_Value;
	}

	return nItemPointRefix;
}

int32				Player::GetInherenceBalanceRefixForItem(PLAYER_PROPERTY_LEVEL4_BALANCE index)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nItemPointRefix = 0;

	if (index < CPROPERTY_LEVEL4_BALANCE_CRITRATE || index >= CPROPERTY_LEVEL4_BALANCE_NUMBER)
	{
		return nItemPointRefix;
	}

	switch (index)
	{
	case CPROPERTY_LEVEL4_BALANCE_CRITRATE:
		pIE = ItemEffect(IPROPERTY_CRIT_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_TOUGHNESS:
		pIE = ItemEffect(IPROPERTY_TOUGHNESS_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_HIT:
		pIE = ItemEffect(IPROPERTY_HIT_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_MISS:
		pIE = ItemEffect(IPROPERTY_MISS_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_CRITDAMAGE:
		pIE = ItemEffect(IPROPERTY_CRIT_HURT_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_CRITDAMAGEDERATE:
		pIE = ItemEffect(IPROPERTY_CRIT_REDUCE_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_CTRLHIT:
		pIE = ItemEffect(IPROPERTY_HIT_CONTROL_BALANCE);
		break;
	case CPROPERTY_LEVEL4_BALANCE_CTRLMISS:
		pIE = ItemEffect(IPROPERTY_RESIST_CONTROL_BALANCE);
		break;
	default:
		break;
	}

	KCheck(pIE);
	if (pIE->IsActive())
	{
		nItemPointRefix = pIE->m_Attr.m_Value;
	}

	return nItemPointRefix;
}

int32_t	Player::GetModelID(void)
{
	return 0;
}
int32_t	Player::Get_BaseProperty_ModelID(void) const
{
	return 0;
}
void	Player::Set_BaseProperty_ModelID(int32 const nID)
{

}


BOOL Player::IsHideName()
{
	if (Effect_HaveEffectOfSpecificEffectID(HIDE_NAME_IMPACT_MAN) || Effect_HaveEffectOfSpecificEffectID(HIDE_NAME_IMPACT_WOMAN))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL Player::IsUnbreakable(void)
{
	return(this->Character::IsUnbreakable()) || IsGod() || GetChangeMapState() != CST_NO_CHANGE;
}

void		Player::SetName(const char* pszName)
{

}

const char* Player::GetName(void) const
{
	return mDB->GetName();
}

void		Player::SetTitle(const char* pszTitle)
{

}

const char* Player::GetTitle(void) const
{
	return "";
}

void		Player::SetHP(int32_t nHP)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nMaxHP = GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nHP > nMaxHP)
	{
		nHP = nMaxHP;
	}

	mDB->SetHP(nHP);
}

int32_t		Player::GetHP(void)
{
	return mDB->GetHP();
}

void		Player::SetMP(int32_t nMP)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nMaxMP = GetMaxMP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nMP > nMaxMP)
	{
		nMP = nMaxMP;
	}

	mDB->SetMP(nMP);
}

int32_t		Player::GetMP(void)
{
	return mDB->GetMP();
}


void Player::SetLevel(int32_t nLevel)
{
	if (nLevel != mDB->GetLevel())
	{
		mDB->SetLevel(nLevel);
	}
}

int32_t		Player::GetLevel(void) const
{
	return mDB->GetPlayerArchive()->m_Level;
}

int32				Player::GetBaseIntAttr_EX(CharIntProperty::Index_T nIndex)
{
	switch (nIndex)
	{
	case CharIntProperty::PROPERTY_NEAR_HIT_FOR_CONTROL_SPELL:
	case CharIntProperty::PROPERTY_FAR_HIT_FOR_CONTROL_SPELL:
	case CharIntProperty::PROPERTY_MAGIC_HIT_FOR_CONTROL_SPELL:
		return 1000 + GetInherenceLevel() * 10;
		break;
	case CharIntProperty::PROPERTY_NEAR_MISS_FOR_CONTROL_SPELL:
	case CharIntProperty::PROPERTY_FAR_MISS_FOR_CONTROL_SPELL:
	case CharIntProperty::PROPERTY_MAGIC_MISS_FOR_CONTROL_SPELL:
		return GetInherenceLevel() * 10;
		break;
	case CharIntProperty::PROPERTY_ZOOM_SCALE:
		return 1000;
		break;
	}
	return 0;
}

NetPacket* Player::CreateNewObjMsg(void)
{
	return nullptr;
}
void	Player::DestroyNewObjMsg(NetPacket* pPacket)
{

}

void Player::SendOperateResultMsg(int32 nCode, int32 nResType)
{
	SCOperateResult* packet = new SCOperateResult;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	packet->setResType(nResType);
	packet->setResult(nCode);
	NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

_EFFECT_LIST& Player::Effect_GetEffectList(void)
{
	return m_oEffectList;
}

const uchar		Player::GetTitleType(void) const
{
	return 0;
}


void Player::initSkill()
{
	_PLAYER_SPELL skill;
	skill.m_nSkillID = 31;
	skill.m_eState = _PLAYER_SPELL::OWN_SKILL_CAN_USE;
	skill.m_nLevel = 1;

	mSkillMap[skill.m_nSkillID] = skill;

}



ItemContainer* Player::GetBankPetContain()
{
	return nullptr;
}

ItemContainer* Player::GetBankContain()
{
	return nullptr;
}

ItemContainer* Player::GetBaseContain()
{
	return &m_BaseItem;
}
ItemContainer* Player::GetExtraContain()
{
	return &m_ExtraContainerItem;
}
ItemContainer* Player::GetExtraBagContain(int32 nIndex)
{
	return &m_ExtraBagItem[nIndex];
}
ItemContainer* Player::GetEquipContain()
{
	return &m_EquipItem;
}
ItemContainer* Player::GetPetContain()
{
	return &m_PetItem;
}

void Player::updateAttr()
{
	SCCharHumanBaseAttrib* packet = new SCCharHumanBaseAttrib;

	packet->setPlayerId(this->GetID());
	packet->setJob(this->GetProfession());
	packet->setCountry(this->GetCountry());
	packet->setDataId(this->GetDataID());
	packet->setLevel(this->GetLevel());

	int32_t hp = GetHP();
	int32_t max_hp = GetMaxHP();
	packet->setHPPercent(hp/(float)max_hp);
	packet->setHP(hp);
	packet->setHPMAX(max_hp);

	float move_speed = Get_Property_MoveSpeed();
	packet->setMoveSpeed(move_speed);
	float attack_speed = Get_Property_AttackSpeed();
	packet->setAttackSpeed(attack_speed/100.0f);
	const SCampData* data = GetCampData();
	if (data)
	{
		packet->setCampData(*data);
	}

	packet->setFaceMeshID(Get_Property_FaceModel());
	packet->setHairMeshID(Get_Property_HairModel());
	packet->setPortraitID(GetPortraitID());

	packet->setModelID(GetModelID());
	packet->setMountID(GetMountID());

	SHorseGuid guid = GetGUIDOfCallUpHorse();
	packet->setCurentHorseGuid(guid);
	packet->setStealthLevel(GetStealthLevel());
	packet->setMoodState(GetMoodState());
	packet->setTargetID(GetLockedTarget());
	packet->setRage(Get_Property_Rage());

	packet->setCurInherenceExp(GetCurInherenceExp());
	packet->setInherenceLevel(GetInherenceLevel());

	packet->setName(this->GetName());

	NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

void Player::updateHorse()
{
	for (int32_t i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pPetFind = GetPetContain()->GetItem(i);
		SHorseGuid	guidFind = pPetFind->GetHorseGUID();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (!guidFind.IsNull())
		{
			RefeshHorseDetailAttrib(guidFind, TRUE);
		}
	}
}

void Player::updateSkills()
{
	//生活技能
	SCDetailAbilityInfo* packet = new SCDetailAbilityInfo;
	const _ABILITY_LIST* pAbilityList = GetAbilityList();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pAbilityList);

#define MAX_SKILL_NUM 38

	for (int32 i = 0; i < MAX_SKILL_NUM; ++i)
	{
		if (pAbilityList->m_aABility[i].m_Level < 1)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nextAbilityLevel = pAbilityList->m_aABility[i].m_Level + 1;
		int32	nextNeedExp = -1;
		int32	nextNeedMoney = -1;
		int32	nextNeedLevel = -1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (nextAbilityLevel < _SkillExpTable::MAX_LEVEL_NUM)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			BaseSkill* ability = g_pSkillManager->GetAbility(i);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(ability);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32		index = ability->GetExpTableIndex();
			_SkillExpTable* abilityExpTable = g_pSkillManager->GetSkillExpTbl(index);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(abilityExpTable);

			nextNeedExp = abilityExpTable->GetCostExp(nextAbilityLevel - 1);
			nextNeedMoney = abilityExpTable->GetCostMoney(nextAbilityLevel - 1);
			nextNeedLevel = abilityExpTable->GetPlayerLevel(nextAbilityLevel - 1);
		}

		packet->setAbility(pAbilityList->m_aABility[i], i, nextNeedLevel, nextNeedExp, nextNeedMoney);
	}

	packet->setPrescrList(pAbilityList->m_aPrescr);
	NetManager::GetSingletonPtr()->sendNetMessage(packet);

	//技能
	SCDetailSkillList* packet2 = new SCDetailSkillList;
	packet2->setPlayerId(GetID());
	const _SPELL_LIST&  spelllist = GetSpellList();
	packet2->setSkillList(spelllist.m_Count, spelllist.m_aSkill);
	NetManager::GetSingletonPtr()->sendNetMessage(packet2);
}

void Player::updateEquip()
{
	SCDetailEquipList* packet = new SCDetailEquipList;

	for (int32_t i = 0; i < HEQUIP_NUMBER; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pEquipItem = sItemInterface.GetEquip(this, (PLAYER_EQUIP)i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pEquipItem);

		if (pEquipItem->IsFree()) continue;

		packet->addItem(i, *pEquipItem->GetItemData());
	};

	packet->setObjectId(GetID());

	NetManager::GetSingletonPtr()->sendNetMessage(packet);
}

void Player::updateBag()
{
	ItemContainer* container = GetBaseContain();

	SCDetailItemList* packet = new SCDetailItemList;
	uint32_t	nItemCount = 0;

	for (int32 i = 0; i < container->GetContainerSize(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pItem = container->GetItem(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		if (!(pItem->IsFree()))
		{
			int32_t index = container->ConIndex2BagIndex(i);
			packet->addItem(index, *pItem->GetItemData());
		}
	}
	packet->setObjectId(GetID());

	NetManager::GetSingletonPtr()->sendNetMessage(packet);
}


void Player::updateQuest()
{
	SCQuestList* packet = new SCQuestList;

	packet->setPlayerId(GetID());

	const OWN_QUEST* pQuest;
	/*~~~~~~~~~~~~~~~~~~~~*/
	const SArchiveLoader_Quest* quest = GetQuestList();
	for (int32_t i = 0; i < MAX_CHAR_QUEST_NUM; i++)
	{
		pQuest = GetQuest(i);
		if (pQuest->m_idQuest != INVALID_ID)
		{
			packet->addQuest((uchar)i, pQuest);
		}
	}

	const DataManager::FlagMD& FlagMDRef = DataManager::GetSingletonPtr()->getFlagMDClientFilter();
	for (int32_t i = 0; i < MAX_CHAR_QUEST_DATA_NUM; i++)
	{
		if (FlagMDRef.IsSetBit(i))
		{
			packet->setFlagData(i);
		}
	}

	packet->setQuestList((QUEST_LIST*)GetQuestList());
	NetManager::GetSingletonPtr()->sendNetMessage(packet);

}

BOOL		Player::IsEnemy(Character* pCharacter)
{
	if (GetID() == pCharacter->GetID())
	{
		return FALSE;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bIsEnemy = IsEnemyCamp(*pCharacter);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return bIsEnemy;
}

BOOL		Player::IsFriend(Character* pCharacter)
{
	return !IsEnemy(pCharacter);
}

BOOL		Player::IsPartner(Character* pCharacter)
{
	return FALSE;
}

BOOL		Player::IsMySpouse(Player& rPlayer)
{
	return FALSE;
}

void		Player::Teleport(const GLPos* pos, uchar bShowChangeState)
{

}



BOOL Player::GetRelationHeartBeatFlag() const
{
	return FALSE;
}

const GUID_TYPE* Player::GetDetailRelation(int32 index) const
{
	return nullptr;
}

uint32 Player::GetBattleHonour()
{
	return 0;
}

uint32 Player::GetDataID(void) const
{
	return mDB->GetPlayerArchive()->m_Sex;
}

void Player::SetPortraitID(int32 nID)
{
	mDB->SetPortraitID(nID);
}

int32 Player::GetPortraitID() const
{
	return mDB->GetPortraitID();
}

BOOL Player::GetSex()
{
	return mDB->GetSex();
}

int32 Player::GetCountry()
{
	return mDB->GetCountry();
}


uint16						Player::GetWenCai()
{
	return 0;
}

void					Player::SetWenCai(uint16 nWenCai)
{

}

int32					Player::GetRongYu()
{
	return mDB->GetRongYu();
}

void					Player::SetRongYu(int32 nRongYu)
{

}

int32					Player::GetShengWang()
{
	return mDB->GetShengWang();
}
void					Player::SetShengWang(int32 nShengWang)
{

}

int32					Player::GetHotValue()
{
	return mDB->GetHotValue();
}
void					Player::SetHotValue(int32 nHotValue)
{

}

int32_t						Player::GetProfession()
{
	return mDB->GetProfession();
}

void	Player::SetProfession(int32_t Profession)
{

}



void					Player::SetGod(uchar bGod)
{
	m_bGod = bGod;
}

BOOL					Player::IsGod(void) const
{
	return (BOOL)m_bGod;
}

void					Player::SetGMGodStealth(uchar bSet)
{
	m_bGodStealth = bSet;
}

BOOL					Player::GetGMGodStealth(void) const
{
	return (BOOL)m_bGodStealth;
}

const _SUIT_SETTING& Player::GetEquipSuitSetting(uint32 nEquipSuitNum) const
{
	return mDB->GetSettingArchive()->m_SuitSetting[nEquipSuitNum];
}

void			Player::SetEquipSuitSetting(_SUIT_SETTING& nSuitSetting, uint32 nEquipSuitNum)
{
	memcpy((void*)&GetSettingList()->m_SuitSetting[nEquipSuitNum], (void*)&nSuitSetting, sizeof(_SUIT_SETTING));
}

const SArchiveLoader_Setting* Player::GetSettingList(void)
{
	return mDB->GetSettingArchive();
}

void Player::SetSettingData(int32 nType, _PLAYER_SETTING* Value)
{
	mDB->SetSettingData(nType, Value);
}

const SArchiveLoader_Setting* Player::GetConstSettingList(void) const
{
	return mDB->GetSettingArchive();
}

uchar	Player::DecreaseSiller(int32_t iMoneyRequire)
{
	return CU_INVALID;
}

void	Player::IncreaseSiller(int32_t iMoneyRequire)
{

}

uchar	Player::DecreaseBindSiller(int32_t iMoneyRequire)
{
	return CU_INVALID;
}

void	Player::IncreaseBindSiller(int32_t iMoneyRequire)
{

}

uchar	Player::SpendGold(int32_t iGoldRequire)
{
	return CU_INVALID;
}

void	Player::IncreaseMoney(uchar MoneyType, int32 nCount)
{

}

void	Player::ReduceMoney(uchar MoneyType, int32 nCount)
{

}

void	Player::IncreaseCharGold(uint32 nCount)
{

}

void	Player::ReduceCharGold(int32 nCount)
{

}

void	Player::DecreaseBindGold(int32 bindGold)
{

}

void	Player::IncreaseBindGold(int32 bindGold)
{

}

int32			Player::GetMoneyByType(int32 type)
{
	return 0;
}

bool			Player::IsEnoughGold(int32 iGoldRequire)
{
	return false;
}

bool			Player::IsEnoughMoney(int32 iMoneyRequire)
{
	return false;
}

uchar			Player::GetSillerModeToSpend(int32 iMoneyRequire)
{
	return CU_INVALID;
}

int32			Player::GetSiller()
{
	return 0;
}

int32			Player::GetCharGold()
{
	return 0;
}

int32			Player::GetGold()
{
	return 0;
}

int32			Player::GetBindSiller()
{
	return 0;
}

int32			Player::GetBindGold()
{
	return 0;
}

uchar			Player::GetSillerMode()
{
	return 0;
}

void			Player::SetSillerMode(uchar sillerMode)
{

}

uchar			Player::GetGoldMode()
{
	return 0;
}

void			Player::SetGoldMode(uchar goldMode)
{

}

uint32			Player::GetAccountGold()
{
	return 0;
}

void			Player::SetAccountGold(uint32 gold)
{

}

void			Player::SetStockAccountEnable(BOOL flag)
{

}

bool			Player::IsEnableStockAccount()
{
	return false;
}

void			Player::SetSiller(int32 siller)
{

}

void			Player::SetBindSiller(int32 bindSiller)
{

}

void			Player::SetBindGold(int32 bindGold)
{

}

void	Player::InitBackupAttr()
{

}

void	Player::SendMsg_RefeshAttrib(void)
{
	SendMsg_RefeshAttribToMyself();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SendMsg_RefeshAttribToOther();

	UpdateBackUpAttrib();
}

void	Player::RequestBaseProperty(Player* pTargetHuman, BASEPROPERTY_REFESH_MODE nMode)
{

}

void	Player::AskMsg_DetailAttrib(Player* pAsker)
{

}

BOOL Player::CheckRefeshBase(
	SCCharHumanBaseAttrib* pBaseMsg,
	BASEPROPERTY_REFESH_MODE	nMode
)
{
	bool bBaseModified = false;
	pBaseMsg->setPlayerId(GetID());

	if (m_AttrBackUp.m_WorldID != GetWorldID())
	{
		if (SEND_TO_SELF == nMode || SEND_TO_OTHER == nMode)
		{
			bBaseModified = true;
			pBaseMsg->setWorldID(GetWorldID());
		}
	}

	if (m_AttrBackUp.m_bNameModified)
	{
		if (SEND_TO_SELF == nMode || SEND_TO_OTHER == nMode)
		{
			bBaseModified = TRUE;
			pBaseMsg->setName(GetName());
		}
	}

	if (m_AttrBackUp.m_bNormalTitleModified)
	{
		bBaseModified = TRUE;
		pBaseMsg->setNormalTitle(GetCurNormalTitleName());
	}

	if (m_AttrBackUp.m_bGuildTitleModified)
	{
		bBaseModified = TRUE;
		pBaseMsg->setGuildTitle(GetCurGuildTitleName());
	}

	if (m_AttrBackUp.m_bCountryTitleModified)
	{
		bBaseModified = TRUE;
		pBaseMsg->setCountryTitle(GetCurCountryTitleName());
	}

	int32_t hp = GetHP();
	int32_t max_hp = GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	yHPPercent = max_hp ? ((uchar)((hp * 100 + max_hp - 1) / max_hp)) : (0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (m_AttrBackUp.m_HPPercent != yHPPercent)
	{
		bBaseModified = TRUE;
		pBaseMsg->setHPPercent(yHPPercent);
	}

	if (m_AttrBackUp.m_HP != hp)
	{
		bBaseModified = TRUE;
		pBaseMsg->setHPPercent(hp);
	}

	if (m_AttrBackUp.m_MaxHp != max_hp)
	{
		bBaseModified = TRUE;
		pBaseMsg->setHPPercent(max_hp);
	}

	if (m_AttrBackUp.m_MaxRage != Get_Property_MaxRage())
	{
		bBaseModified = TRUE;
		pBaseMsg->setMaxRage(Get_Property_MaxRage());
	}

	if (m_AttrBackUp.m_nRage != Get_Property_Rage())
	{
		bBaseModified = TRUE;
		pBaseMsg->setRage(Get_Property_Rage());
	}

	if (fabs(m_AttrBackUp.m_MoveSpeed - Get_Property_MoveSpeed()) > 0.001f)
	{
		bBaseModified = TRUE;
		pBaseMsg->setMoveSpeed(Get_Property_MoveSpeed());
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SCampData* pCampData = GetCampData();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pCampData != NULL)
	{
		if (m_AttrBackUp.m_CampData != *pCampData)
		{
			bBaseModified = TRUE;
			pBaseMsg->setCampData(*pCampData);
		}
	}

	if (m_AttrBackUp.m_nPortraitID != GetPortraitID())
	{
		bBaseModified = TRUE;
		pBaseMsg->setPortraitID(GetPortraitID());
	}

	if (m_AttrBackUp.m_nModelID != GetModelID())
	{
		bBaseModified = TRUE;
		pBaseMsg->setModelID(GetModelID());
	}

	if (m_AttrBackUp.m_nMountID != GetMountID())
	{
		bBaseModified = TRUE;
		pBaseMsg->setMountID(GetMountID());
	}

	if (m_AttrBackUp.m_guidCurrentHorse != GetGUIDOfCallUpHorse())
	{
		bBaseModified = TRUE;
		pBaseMsg->setCurentHorseGuid(GetGUIDOfCallUpHorse());
	}

	if(
			m_AttrBackUp.m_uHairMeshID != Get_Property_HairModel()
			|| m_AttrBackUp.m_uHairColor != Get_Property_HairColor()
			|| m_AttrBackUp.m_uFaceMeshID != Get_Property_FaceModel()
			)
	{
		bBaseModified = TRUE;
		pBaseMsg->setFaceMeshID(Get_Property_FaceModel());
		pBaseMsg->setHairMeshID(Get_Property_HairModel());
	}

	if (m_AttrBackUp.m_nStealthLevel != GetStealthLevel())
	{
		bBaseModified = TRUE;
		pBaseMsg->setStealthLevel(GetStealthLevel());
	}

	if (m_AttrBackUp.m_nMoodState != GetMoodState())
	{
		bBaseModified = TRUE;
		pBaseMsg->setMoodState(GetMoodState());
	}

	if (m_AttrBackUp.m_Level != GetLevel())
	{
		bBaseModified = TRUE;
		pBaseMsg->setLevel(GetLevel());
	}


	if (m_AttrBackUp.m_nProfession != GetProfession())
	{
		bBaseModified = TRUE;
		pBaseMsg->setJob(GetProfession());
	}

	if (m_AttrBackUp.m_nCountry != GetCountry())
	{
		bBaseModified = TRUE;
		pBaseMsg->setCountry(GetCountry());
	}

	if (m_AttrBackUp.m_nAttSpeed != Get_Property_AttackSpeed())
	{
		bBaseModified = TRUE;
		pBaseMsg->setAttackSpeed((float)Get_Property_AttackSpeed() / 100);
	}

	if (m_AttrBackUp.m_iTargetId != GetLockedTarget())
	{
		bBaseModified = TRUE;
		pBaseMsg->setTargetID(GetLockedTarget());
	}

	if (m_AttrBackUp.m_nZoomScale != GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE))
	{
		bBaseModified = TRUE;
		//pBaseMsg->setScale(GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE));
	}

	//需要天赋特效是打开
	if (m_AttrBackUp.m_nInherenceExp != GetCurInherenceExp())
	{
		bBaseModified = TRUE;
		pBaseMsg->setCurInherenceExp(GetCurInherenceExp());
	}

	if (m_AttrBackUp.m_nInherenceLevel != GetInherenceLevel())
	{
		bBaseModified = TRUE;
		pBaseMsg->setInherenceLevel(GetInherenceLevel());
	}

	return bBaseModified;
}

BOOL Player::CheckRefeshDetail(SCDetailAttrib* pDetailMsg)
{
	return true;
}

BOOL Player::CheckRefeshEquip(SCCharEquipment* pEquipMsg)
{
	return true;
}

BOOL			Player::CheckRefeshQuest(SCQuestListRefresh* pQuestMsg)
{
	return true;
}

void Player::UpdateBackUpAttrib(void)
{
	UpdateBaseBackUp();

	UpdateEquipBackUp();

	UpdateQuestBackUp();
}

void Player::UpdateBaseBackUp(void)
{
	if (m_AttrBackUp.m_bNameModified)
	{
		m_AttrBackUp.m_bNameModified = FALSE;
	}

	if (m_AttrBackUp.m_bNormalTitleModified)
	{
		m_AttrBackUp.m_bNormalTitleModified = FALSE;
	}

	if (m_AttrBackUp.m_bGuildTitleModified)
	{
		m_AttrBackUp.m_bGuildTitleModified = FALSE;
	}

	if (m_AttrBackUp.m_bCountryTitleModified)
	{
		m_AttrBackUp.m_bCountryTitleModified = FALSE;
	}

	if (m_AttrBackUp.m_bBusStateModified)
	{
		m_AttrBackUp.m_bBusStateModified = FALSE;
	}

	int32_t hp = GetHP();
	int32_t hp_max = GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	yHPPercent = hp_max ? ((uchar)((hp * 100 + hp_max - 1) / hp_max)) : (0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (m_AttrBackUp.m_HPPercent != yHPPercent)
	{
		m_AttrBackUp.m_HPPercent = yHPPercent;
	}

	if (m_AttrBackUp.m_HP != hp)
	{
		m_AttrBackUp.m_HP = hp;
	}

	if (m_AttrBackUp.m_MaxHp != hp_max)
	{
		m_AttrBackUp.m_MaxHp = hp_max;
	}

	if (m_AttrBackUp.m_MaxRage != Get_Property_MaxRage())
	{
		m_AttrBackUp.m_MaxRage = Get_Property_MaxRage();
	}

	if (m_AttrBackUp.m_nRage != Get_Property_Rage())
	{
		m_AttrBackUp.m_nRage = Get_Property_Rage();
	}

	if (fabs(m_AttrBackUp.m_MoveSpeed - Get_Property_MoveSpeed()) > 0.001f)
	{
		m_AttrBackUp.m_MoveSpeed = Get_Property_MoveSpeed();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SCampData* pCampData = GetCampData();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pCampData != NULL && m_AttrBackUp.m_CampData != *pCampData)
	{
		m_AttrBackUp.m_CampData = *pCampData;
	}

	if (m_AttrBackUp.m_nDataID != GetDataID())
	{
		m_AttrBackUp.m_nDataID = GetDataID();
	}

	if (m_AttrBackUp.m_nPortraitID != GetPortraitID())
	{
		m_AttrBackUp.m_nPortraitID = GetPortraitID();
	}

	if (m_AttrBackUp.m_nModelID != GetModelID())
	{
		m_AttrBackUp.m_nModelID = GetModelID();
	}

	if (m_AttrBackUp.m_nMountID != GetMountID())
	{
		m_AttrBackUp.m_nMountID = GetMountID();
	}

	if
		(
			m_AttrBackUp.m_uHairMeshID != Get_Property_HairModel()
			|| m_AttrBackUp.m_uHairColor != Get_Property_HairColor()
			|| m_AttrBackUp.m_uFaceMeshID != Get_Property_FaceModel()
			)
	{
		m_AttrBackUp.m_uHairMeshID = Get_Property_HairModel();
		m_AttrBackUp.m_uFaceMeshID = Get_Property_FaceModel();
		m_AttrBackUp.m_uHairColor = Get_Property_HairColor();
	}

	if (m_AttrBackUp.m_nStealthLevel != GetStealthLevel())
	{
		m_AttrBackUp.m_nStealthLevel = GetStealthLevel();
	}

	if (m_AttrBackUp.m_nMoodState != GetMoodState())
	{
		m_AttrBackUp.m_nMoodState = GetMoodState();
	}

	if (m_AttrBackUp.m_Level != GetLevel())
	{
		m_AttrBackUp.m_Level = GetLevel();
	}

	if (m_AttrBackUp.m_bStallNameChanged)
	{
		m_AttrBackUp.m_bStallNameChanged = FALSE;
	}

	if (m_AttrBackUp.m_nProfession != GetProfession())
	{
		m_AttrBackUp.m_nProfession = GetProfession();
	}

	if (m_AttrBackUp.m_nCountry != GetCountry())
	{
		m_AttrBackUp.m_nProfession = GetCountry();
	}

	if (m_AttrBackUp.m_nAttSpeed != Get_Property_AttackSpeed())
	{
		m_AttrBackUp.m_nAttSpeed = Get_Property_AttackSpeed();
	}

	if (m_AttrBackUp.m_guidCurrentHorse != GetGUIDOfCallUpHorse())
	{
		m_AttrBackUp.m_guidCurrentHorse = GetGUIDOfCallUpHorse();
	}

	if (!GetGUIDOfCallUpHorse().IsNull())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Item* pItem = GetHorseItem(GetGUIDOfCallUpHorse());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL != pItem && m_AttrBackUp.m_byGeneration != pItem->GetGeneration())
		{
			m_AttrBackUp.m_byGeneration = pItem->GetGeneration();
		}
	}

	if (m_AttrBackUp.m_iTargetId != GetLockedTarget())
	{
		m_AttrBackUp.m_iTargetId = GetLockedTarget();
	}

	if (m_AttrBackUp.m_nZoomScale != GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE))
	{
		m_AttrBackUp.m_nZoomScale = GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE);
	}

	if (m_AttrBackUp.m_WorldID != GetWorldID())
	{
		m_AttrBackUp.m_WorldID = GetWorldID();
	}
}

void Player::UpdateDetailBackUp(void)
{

}

void Player::UpdateEquipBackUp(void)
{
	if (m_AttrBackUp.m_bMainWeaponModified)
	{
		m_AttrBackUp.m_bMainWeaponModified = FALSE;
	}

	if (m_AttrBackUp.m_bAssiWeaponModified)
	{
		m_AttrBackUp.m_bAssiWeaponModified = FALSE;
	}

	if (m_AttrBackUp.m_bCapModified)
	{
		m_AttrBackUp.m_bCapModified = FALSE;
	}

	if (m_AttrBackUp.m_bShoulderModified)
	{
		m_AttrBackUp.m_bShoulderModified = FALSE;
	}

	if (m_AttrBackUp.m_bArmorModified)
	{
		m_AttrBackUp.m_bArmorModified = FALSE;
	}

	if (m_AttrBackUp.m_bCuffModified)
	{
		m_AttrBackUp.m_bCuffModified = FALSE;
	}

	if (m_AttrBackUp.m_bBootModified)
	{
		m_AttrBackUp.m_bBootModified = FALSE;
	}

	if (m_AttrBackUp.m_bSuitModified)
	{
		m_AttrBackUp.m_bSuitModified = FALSE;
	}

	if (m_AttrBackUp.m_bSoulModified)
	{
		m_AttrBackUp.m_bSoulModified = FALSE;
	}

	if (m_AttrBackUp.m_bGemAffModified)
	{
		m_AttrBackUp.m_bGemAffModified = FALSE;
	}
}

void Player::UpdateQuestBackUp(void)
{
	for (uint32 uQuestDataIndex = 0; uQuestDataIndex < MAX_CHAR_QUEST_DATA_NUM; ++uQuestDataIndex)
	{
		if (m_AttrBackUp.m_QuestListRefresh.m_aQuestData[uQuestDataIndex] != GetQuestData(uQuestDataIndex))
		{
			m_AttrBackUp.m_QuestListRefresh.m_aQuestData[uQuestDataIndex] = GetQuestData(uQuestDataIndex);
		}
	}

	for (uint32 uQuestIndex = 0; uQuestIndex < MAX_CHAR_QUEST_NUM; ++uQuestIndex)
	{
		for (uint32 uParamIndex = 0; uParamIndex < MAX_QUEST_PARAM_NUM; ++uParamIndex)
		{
			if
				(
					m_AttrBackUp.m_QuestListRefresh.m_aQuestRefresh[uQuestIndex].m_anParam[
						uParamIndex] != GetQuestParam(uQuestIndex, uParamIndex)
							)
			{
				m_AttrBackUp.m_QuestListRefresh.m_aQuestRefresh[uQuestIndex].m_anParam[uParamIndex] = GetQuestParam(uQuestIndex, uParamIndex);
			}
		}
	}

	for (uint32 uQuestDone = 0; uQuestDone < MAX_CHAR_QUEST_FLAG_LEN; ++uQuestDone)
	{
		if
			(
				m_AttrBackUp.m_QuestListRefresh.m_aQuestHaveDoneFlags[uQuestDone] != GetQuestList()
				->m_aQuestHaveDoneFlags[uQuestDone]
				)
		{
			m_AttrBackUp.m_QuestListRefresh.m_aQuestHaveDoneFlags[uQuestDone] = GetQuestList()->m_aQuestHaveDoneFlags[uQuestDone];
		}
	}
}

void Player::SendMsg_RefeshAttribToMyself(void)
{
	if (!mSCCharHumanBaseAttrib)
		mSCCharHumanBaseAttrib = new SCCharHumanBaseAttrib;
	if (!mSCCharEquipment)
		mSCCharEquipment = new SCCharEquipment;
	if (!mSCQuestListRefresh)
		mSCQuestListRefresh = new SCQuestListRefresh;
	
	if (CheckRefeshBase(mSCCharHumanBaseAttrib))
	{
		NetManager::GetSingletonPtr()->sendNetMessage(mSCCharHumanBaseAttrib);
		mSCCharHumanBaseAttrib = nullptr;
	}


	if (CheckRefeshEquip(mSCCharEquipment))
	{
		NetManager::GetSingletonPtr()->sendNetMessage(mSCCharEquipment);
		mSCCharEquipment = nullptr;
	}


	if (CheckRefeshQuest(mSCQuestListRefresh))
	{
		NetManager::GetSingletonPtr()->sendNetMessage(mSCQuestListRefresh);
		mSCQuestListRefresh = nullptr;
	}
}

void Player::SendMsg_RefeshAttribToOther(void)
{

}

void Player::RefreshAttrToWorld(uint32 uTime)
{

}

void Player::RefreshAttrToWorldImmediately()
{

}

void Player::RefeshAttrMsg()
{

}

void Player::SetChangeMapState(uchar bChangeSceneState)
{
	m_bChangeMapState = bChangeSceneState;
}

uchar Player::GetChangeMapState(void) const
{
	return m_bChangeMapState;
}

const _ABILITY_LIST* Player::GetAbilityList() const
{
	return mDB->GetSkillArchive();
}

SkillOpera* Player::GetAbilityOpera()
{
	return &m_LastOpera;
}

void Player::reset_AbilityOpera()
{
	m_LastOpera.Clear();
}

void Player::interruptCurrentAbilityOpera()
{
	BaseSkill* pSkill = DataManager::GetSingletonPtr()->getSkill(m_LastOpera.m_SkillID);
	
	if (pSkill != NULL)
	{
		pSkill->OnEvent_ProcInterrupt(this);
	}

	reset_AbilityOpera();
}

const BOOL Player::IsAbilityHaveLearned(SpellID_t abilityid) const
{
	if (abilityid < 1 || abilityid > MAX_CHAR_ABILITY_NUM)
	{
		return FALSE;
	}

	if (GetAbilityList()->Get_Ability(abilityid).m_Level > 0)
	{
		return TRUE;
	}

	return FALSE;
}

const int32 Player::GetAbilityLevel(const SpellID_t abilityid) const
{
	if (abilityid < 1 || abilityid > MAX_CHAR_ABILITY_NUM)
	{
		return 0;
	}

	return GetAbilityList()->Get_Ability(abilityid).m_Level;
}

void Player::SetAbilityLevel(const SpellID_t abilityid, int32 lvl)
{
	if (_SkillExpTable::MAX_LEVEL_NUM >= lvl)
	{
		mDB->SetAbilityLevel(abilityid, lvl);
	}
	else
	{
		mDB->SetAbilityLevel(abilityid, _SkillExpTable::MAX_LEVEL_NUM);
	}
}

const int32 Player::GetAbilityExp(const SpellID_t abilityid) const
{
	if (abilityid < 1 || abilityid > MAX_CHAR_ABILITY_NUM)
	{
		return 0;
	}

	return GetAbilityList()->Get_Ability(abilityid).m_Exp;
}

void Player::SetAbilityExp(const SpellID_t abilityid, int32 exp)
{
	if (exp <= g_pSkillManager->GetUpperLimitExp(abilityid, this))
	{
		mDB->SetAbilityExp(abilityid, exp);
	}
	else
	{
		mDB->SetAbilityExp(abilityid, g_pSkillManager->GetUpperLimitExp(abilityid, this));
	}
}

const BOOL Player::IsPrescrHaveLearned(const PrescriptionID_t prescrid) const
{
	int32 idx;
	/*~~~~~~~~~~~~~~~~*/

	idx = (int32)prescrid;
	if (idx < 0 || idx >= MAX_SKILL_PRESCRIPTION_NUM)
	{
		KCheck(FALSE);
		return FALSE;
	}

	/*~~~~~~~~~~~~*/
	char	cPrescr;
	/*~~~~~~~~~~~~*/

	cPrescr = GetAbilityList()->m_aPrescr[idx >> 3];
	cPrescr >>= idx % 8;

	if (cPrescr & 0x01)
	{
		return TRUE;
	}

	return FALSE;
}

void Player::SetPrescrLearnedFlag(const PrescriptionID_t prescrid, BOOL flag)
{
	mDB->SetPrescrLearnedFlag(prescrid, flag);
}

OPT_RESULT Player::BHV_UseAbility(void)
{
	mStateManager->OnCommandAbility();
	return OR_OK;
}

uint32 Player::Get_Property_HairColor() const
{
	return mDB->Get_Property_HairColor();
}

void Player::SetHairColor(uint32 haircolor)
{
	mDB->SetHairColor(haircolor);
}

uchar Player::Get_Property_HairModel() const
{
	return mDB->Get_Property_HairModel();
}

void Player::SetHairModel(uchar hairmodel)
{
	mDB->SetHairModel(hairmodel);
}

uchar Player::Get_Property_FaceModel() const
{
	return mDB->Get_Property_FaceModel();
}

void Player::SetFaceModel(uchar byModel)
{
	mDB->SetFaceModel(byModel);
}

void Player::SetAlterPlayerExp(uint64_t AlterExp)
{
	__GUARD__ if (!IsAlive())
	{
		return;
	}

	if (AlterExp == 0)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint64	CurExp = mDB->GetExp();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (AlterExp > 0)
	{
		if (CurExp + AlterExp <= CurExp)
		{
			//SendOperateResultMsg(OR_EXP_FULL);
			return;
		}
	}

	SetPlayerExp(CurExp + AlterExp);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//uint64	CurrentExp = GetPlayerExp();
	//uint32	iLevel = GetLevel();
	//uint64	LevelExp = g_LevelupExpTab.Get(iLevel - 1);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if (CurrentExp >= LevelExp && iLevel < MAX_HAND_LEVEL)
	//{
	//	CurrentExp -= LevelExp;
	//	this->SetPlayerExp(CurrentExp);
	//	this->Levelup();

	//	this->SetHP(this->GetMaxHP());
	//	this->SetMP(this->GetMaxMP());

	//	/*~~~~~~~~~~~~~~~~~~~~~~*/
	//	XCLevelUpResult ResultMsg;
	//	/*~~~~~~~~~~~~~~~~~~~~~~*/

	//	ResultMsg.SetRemainExp(CurrentExp);
	//	ResultMsg.SetLevelUpResult(LEVELUP_SUCCESS);

	//	GetConnector()->SendPacket(&ResultMsg);

	//	/*~~~~~~~~~~~~~~~~~~~~~*/
	//	XCLevelUp	otherMsg;
	//	/*~~~~~~~~~~~~~~~~~~~~~*/

	//	otherMsg.SetObjId(this->GetID());
	//	otherMsg.SetLevel(this->GetLevel());

	//	GetMap()->BroadCast(&otherMsg, this, TRUE);

	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	XGLevelUp* pWorldMsg = CREATE_PACKET_OBJ(XGLevelUp, PACKET_XG_LEVEUP);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	pWorldMsg->SetGUID(this->GetGUID());
	//	pWorldMsg->SetLevel(this->GetLevel());
	//	pWorldMsg->SetExp(this->GetPlayerExp());

	//	g_pServerConnectorMgr->SendPacket_MultiMode(pWorldMsg, GetWorldID());
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//uint64	afterExp = GetPlayerExp();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if ((afterExp == CurExp) && GetWallow() > 0.0f)
	//{
	//	SendOperateResultMsg(OR_EXP_FULL);
	//}

	__UNGUARD__
}

void Player::SetAlterPlayerExpEx(uint64_t AlterExp)
{

}

uint64_t Player::GetPlayerExp()
{
	return 0;
}

void Player::SetPlayerExp(uint64_t uExp)
{

}

void Player::DecreasePlayerExp(uint64_t nExp)
{
	uint64_t nCurExp = GetPlayerExp();

	SetPlayerExp(nCurExp - nExp);
}

bool Player::IsPlayerExpFull()
{
	return false;
}

uint32 Player::GetEquipID(PLAYER_EQUIP equipPoint)
{
	return 0;
}

uint32 Player::GetEquipLevel(PLAYER_EQUIP equipPoint)
{
	return 0;
}

void Player::AddTitleBuff(int32_t buffID1, int32_t buffID2)
{

}

void Player::DelTitleBuff(int32_t buffID1, int32_t buffID2)
{
}

const char* Player::GetTitleNameByID(int32_t iTitleID, int32_t iSex)
{
	return "";
}

const char* Player::GetCurCountryTitleName()
{
	return "";
}

const char* Player::GetCurGuildTitleName()
{
	return "";
}

const char* Player::GetCurNormalTitleName()
{
	return "";
}



const char* Player::GetGuildTitleName() const
{
	return "";
}


void                    Player::SetNormalTitleName(const char* pszTitle, int32_t iSize)
{
	m_AttrBackUp.m_bNormalTitleModified = TRUE;
}

const char* Player::GetNormalTitleName() const
{
	return "";
}

void Player::SetCommonSpellPoints(int32 nS, int32 Point)
{
	mDB->SetDB_S_SkillPoints(nS, Point);
}

int32 Player::GetRemainSpellPoints()
{
	return mDB->GetRemainSkillPoints();
}

void Player::SetRemainSpellPoints(int32 Point)
{
	mDB->SetDBRemainSkillPoints(Point);
}


int32 Player::GetSpellPoints(int32 nS)
{
	return mDB->Get_S_SkillPoints(nS);
}

void Player::SetSpellPoints(int32 nS, int32 Point)
{
	mDB->SetDB_S_SkillPoints(nS, Point);
}

int32		Player::SpellCharacter(Character* pCharacter, SpellID_t SkillID, BOOL bNow)
{
	return 0;
}

BOOL Player::SpellRefixItemAttr(int32 nSlotID, int32 nItemType, int32 nATTRID, int16& nAttrValue)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_SPELL_LIST const& rList = ((Player*)this)->GetSpellList();
	uchar const& rCount = rList.m_Count;
	SpellInfo			PassiveSkill;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_PLAYER_SPELL const& rSkill = rList.m_aSkill[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 < rSkill.m_nSkillID)
		{
			PassiveSkill.Init();
			if (TRUE == g_SpellCore.InstanceSpell(PassiveSkill, *this, rSkill.m_nSkillID))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BaseSpellLogic const* pLogic = Spell_GetLogic(PassiveSkill);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (NULL != pLogic)
				{
					pLogic->Refix_ItemEffect(PassiveSkill, nSlotID, nItemType, nATTRID, nAttrValue);
				}
			}
		}
	}

	return TRUE;
}

BOOL Player::SpellDepleteItem(void)
{
	SpellInfo& rSkillInfo = GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = GetTargetingAndDepletingParams();
	SItemGuid				itemGuid = rParams.GetDepletedItemGuid();
	int32					nItemIndex = rParams.GetItemIndexOfDepletedItem();
	int32					nBagIndex = rParams.GetBagIndexOfDepletedItem();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (INVALID_ID == nBagIndex)
	{
		if (FALSE == itemGuid.isNull())
		{
			nBagIndex = sItemInterface.GetBagItemPosByGUID(this, itemGuid);
		}

		if (INVALID_ID == nBagIndex)
		{
			nBagIndex = sItemInterface.GetBagItemPosByType(this, nItemIndex);
		}
	}

	if (INVALID_ID == nBagIndex)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item* pItem = sItemInterface.GetBagItem(this, nBagIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pItem)
	{
		return FALSE;
	}

	if (pItem->GetItemTableIndex() != rParams.GetItemIndexOfDepletedItem())
	{
		return FALSE;
	}

	if (FALSE == pItem->IsRuler(IRL_CANUSE))
	{
		return FALSE;
	}

	if (TRUE == pItem->IsRuler(IRL_CONSUME))
	{
		if (pItem->GetLayedNum() < 1)
		{
			rParams.SetErrCode(OR_NOT_ENOUGH_ITEM);
			return FALSE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemContainer* pContainer = sItemInterface.GetBagContainer(this, nBagIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL == pContainer)
		{
			KCheckEx(FALSE, "[Player::Skill_DepleteItem]: Can't find the specified container!!");
			return FALSE;
		}


		if (pItem->GetItemFreeParamType() == 1)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			eITEM_PARAM_VALUE	ipv = IPV_INT;
			int32		nReamin = pItem->GetItemFreeParam(0, ipv);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(nReamin > 0);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nTatol = pItem->GetItemTableParamValue();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(nTatol > 0);

			/*~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nConsumeValue = 0;
			/*~~~~~~~~~~~~~~~~~~~~~~*/

			if (pItem->GetConsumeValue() <= 0)
			{
				if (pItem->GetItemClass() == ICLASS_COMITEM)
				{
					switch (pItem->GetItemType())
					{
					case COMMON_ITEM_1:
					{
						if (GetMaxHP() - GetHP() > nReamin)
						{
							nConsumeValue = nReamin;
						}
						else
							nConsumeValue = GetMaxHP() - GetHP();
						nReamin -= (GetMaxHP() - GetHP());
					}
					break;

					case COMMON_ITEM_2:
					{
						if (Get_Property_MaxRage() - Get_Property_Rage() > nReamin)
						{
							nConsumeValue = nReamin;
						}
						else
							nConsumeValue = GetMaxHP() - GetHP();
						nReamin -= (Get_Property_MaxRage() - Get_Property_Rage());
					}
					break;
					}
				}
			}
			else
			{
				nReamin -= pItem->GetConsumeValue();
				nConsumeValue = pItem->GetConsumeValue();
			}

			if (nReamin <= 0)
			{
				nReamin = 0;
				if (pItem->IsCanLay())
				{
					if (sItemInterface.DecBagItemLayCount(nullptr, this, nBagIndex, 1))
					{
						rParams.SetDynamicParamByIndex(0, nConsumeValue);
					}
					else
					{
						return FALSE;
					}
				}
				else
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					BOOL	Ret = sItemInterface.EraseBagItemBySlot(nullptr, this, nBagIndex);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if (Ret)
					{
						rParams.SetDynamicParamByIndex(0, nConsumeValue);
					}
				}
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL	Ret = sItemInterface.SetItemFreeParam
				(
					pContainer,
					pContainer->BagIndex2ConIndex(nBagIndex),
					0,
					IPV_INT,
					nReamin
				);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (Ret)
				{
					rParams.SetDynamicParamByIndex(0, nConsumeValue);
					SCItemInfo* packet = new SCItemInfo;
					packet->setId(nBagIndex);
					packet->setIsNull(false);
					pItem->SaveValueTo(packet->getItem());
					NetManager::GetSingletonPtr()->sendNetMessage(packet);
				}
				else
					return FALSE;
			}
		}
		else
		{
			if (pItem->IsCanLay())
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL	Ret = sItemInterface.DecBagItemLayCount(nullptr, this, nBagIndex, 1);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (!Ret)
				{
					return FALSE;
				}
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				BOOL	Ret = sItemInterface.EraseBagItemBySlot(nullptr, this, nBagIndex);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (!Ret)
				{
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

BOOL		Player::SpellHaveSkill(SpellID_t const nID) const
{
	SpellTemplateData const* pSkillTemplateData = DataManager::GetSingletonPtr()->getSpellTemplate(nID);
	_SPELL_LIST const& rList = ((Player*)this)->GetSpellList();
	uchar const& rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (MAX_CHAR_SKILL_NUM < rCount)
	{
		KCheck(!"Skill_HaveSkill");
		return FALSE;
	}

	if (SUB_SKILL == pSkillTemplateData->GetProfession())
	{
		return TRUE;
	}

	for (int32 i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_PLAYER_SPELL const& rSkill = rList.m_aSkill[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (nID == rSkill.m_nSkillID)
		{
			if (INVALID_ID == pSkillTemplateData->GetProfession())
			{
				return TRUE;
			}
			else if (rSkill.m_nLevel > 0)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL		Player::SpellModify(SpellID_t const nID, int32 const nModifyFlag)
{
	if (0 < nModifyFlag)
	{
		return RegisterSpell(nID);
	}
	else if (0 > nModifyFlag)
	{
		return UnregisterSpell(nID);
	}
	return FALSE;
}

void		Player::SpellOnEquipItem(void)
{
	const _SPELL_LIST& rList = GetSpellList();
	uchar				rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const _PLAYER_SPELL& rSkill = rList.m_aSkill[i];
		BaseSpellLogic const* pLogic = g_SpellLogicList.GetLogicById(rSkill.m_nSkillID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL != pLogic)
		{
		}
	}
}

void				Player::SetSpellLevel(SpellID_t const nID, int32 const nLevel)
{
	_SPELL_LIST const& rList = ((Player*)this)->GetSpellList();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (MAX_CHAR_SKILL_NUM < rList.m_Count)
	{
		KCheck(!"Skill_SetSkillLevel");
		return;
	}

	for (int32 i = 0; i < rList.m_Count; ++i)
	{
		if (nID == rList.m_aSkill[i].m_nSkillID)
		{
			mDB->SetSkillLevel(nID, i, nLevel);
			return;
		}
	}

	if (MAX_CHAR_SKILL_NUM > rList.m_Count)
	{
		/*~~~~~~~~~~~~~~~~~~~~~*/
		_PLAYER_SPELL	newSkill;
		/*~~~~~~~~~~~~~~~~~~~~~*/

		newSkill.m_nSkillID = nID;
		newSkill.m_nLevel = nLevel;

		mDB->SetSkillID(newSkill, rList.m_Count);
		mDB->SetSkillCount(rList.m_Count + 1);
	}
}

const _PLAYER_SPELL* Player::GetSpell(int32 const nID)
{
	_SPELL_LIST const& rList = ((Player*)this)->GetSpellList();
	uchar const& rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (MAX_CHAR_SKILL_NUM < rCount)
	{
		KCheck(!"Skill_GetSkill");
		return NULL;
	}

	for (int32 i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_PLAYER_SPELL const& rSkill = rList.m_aSkill[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (nID == rSkill.m_nSkillID)
		{
			return &rSkill;
		}
	}

	return nullptr;
}

const _SPELL_LIST& Player::GetSpellList(void)
{
	const _SPELL_LIST* pSkillList = mDB->GetSpellArchive();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	return *pSkillList;
}

Time_t		Player::GetCooldownRemained(CooldownID_t const nID) const
{
	return mDB->GetCooldownRemain(nID);
}

BOOL		Player::IsCooldowned(CooldownID_t const nID) const
{
	return mDB->IsCooldowned(nID);
}

void		Player::SetCooldown(CooldownID_t const nID, Time_t nCooldown)
{
	mDB->SetCooldown(nID, nCooldown);

	///*~~~~~~~~~~~~~~~~~~~~~~~~*/
	//XCCooldownUpdate	Msg;
	///*~~~~~~~~~~~~~~~~~~~~~~~~*/

	//Msg.CooldownModified(nID, nCooldown);

	//todo
	
}

BOOL		Player::HeartBeat_Cooldown(uint32 uTime)
{
	int32 nDeltaTime = GetLogicTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mDB->HeartBeat_Cooldown(nDeltaTime);

	return TRUE;
}

void		Player::ClearCoolDown(void)
{
	mDB->ClearCooldown();
}

BOOL		Player::HaveSpell(SpellID_t const nID) const
{
	return SpellHaveSkill(nID);
}


void Player::ReloadAllPassiveSpell()
{
	_SPELL_LIST const& rList = GetSpellList();
	uchar const& rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (MAX_CHAR_SKILL_NUM < rCount)
	{
		KCheck(!"Skill_ReloadAllPassiveSkill");
		return;
	}

	for (int32 i = 0; rCount > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_PLAYER_SPELL const& rSkill = rList.m_aSkill[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (0 >= rSkill.m_nLevel)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const SpellTemplateData* pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(rSkill.m_nSkillID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL == pTemplate)
		{
			continue;
		}

		if (pTemplate->GetPassiveFlag() <= 0)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iSkillID = rSkill.m_nSkillID;
		int32	iSkillLevel = rSkill.m_nLevel - 1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (iSkillLevel < 0)
		{
			iSkillLevel = 0;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const SpellInstanceData* pInstance = DataManager::GetSingletonPtr()->getSpellInstance(iSkillID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pInstance == NULL)
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const Descriptor* pDescriptor = pInstance->GetDescriptorByIndex(0);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pDescriptor == NULL)
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iDataIndex = pDescriptor->GetValueBySkillLevel(iSkillLevel);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_EffectInterface.SendEffectToUnit(*this, iDataIndex, GetID(), iSkillID);
	}
}

void Player::RefixByInherence(int32& nDamage, Character* const pAttacker, BOOL bDOT, BOOL bPKRateCtr)
{
	float	nRefix = g_Config.m_ConfigInfo.m_fInherenceFixParam;
	if (NULL != pAttacker)
	{
		if (OBJECT_CLASS_PLAYER == pAttacker->GetObjType())
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
}

void Player::InitSpellList()
{

}

BOOL Player::RegisterSpell(SpellID_t const nID)
{
	return FALSE;
}

BOOL Player::UnregisterSpell(SpellID_t const nID)
{
	return FALSE;
}

uint16	 Player::GetEquipVer()
{
	return m_EquipVer;
}

void					Player::SetEquipVer(uint16 Ver)
{
	m_EquipVer = Ver;
}

MapID_t				Player::GetTransMapID()
{
	return m_TransMapID;
}

void					Player::SetTransMapID(MapID_t id)
{
	m_TransMapID = id;
}

GLPos* Player::GetTransWorldPos()
{
	return &m_TransWorldPos;
}

void Player::SetTransWorldPos(const GLPos* pPos)
{
	m_TransWorldPos = *pPos;
}

void		Player::SetExpMult(float fMult)
{
	m_fExpMult = fMult;
}

float		Player::GetExpMult()
{
	return m_fExpMult + GetExpMultRefix() * 0.01f;
}

float		Player::GetBaseExp()
{
	return m_fExpMult;
}

int32		Player::GetExpMultRefix(void)
{
	if (TRUE == GetExpMultRefixDirtyFlag())
	{
		/*~~~~~~~~~~~~~~~*/
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~*/

		Effect_GetIntAttrRefix(CharIntAttrRefixs::REFIX_MULT_EXP, nValue);
		SetIntAttrRefix(CharIntAttrRefixs::REFIX_MULT_EXP, nValue);
		ClearExpMultRefixDirtyFlag();
	}

	return Get_Property_IntAttrRefix(CharIntAttrRefixs::REFIX_MULT_EXP);
}

void		Player::SetWanFaExpMult(float fMult)
{
	m_fWanFaExpMult = fMult;
}

float		Player::GetWanFaExpMult()
{
	return m_fWanFaExpMult;
}

float		Player::GetEquipExpMult()
{
	SItemEffect* pIE = ItemEffect(IPROPERTY_EXPRENCE_GET);
	KCheck(pIE);
	if (pIE->IsActive())
	{
		return pIE->m_Attr.m_Value / 100.0f;
	}
	return 0.0f;
}

void	Player::OnQuestHaveDoneFlagsChanged(QuestID_t idQuest)
{
	m_AttrBackUp.m_bQuestHaveDoneFlagsChanged = TRUE;
}

void	Player::OnQuestParamChanged(uint32 uIndexQuest, uint32 uIndexParam, int32 index)
{
	SCModifyQuest* packet = new SCModifyQuest;
	packet->setQuestId(uIndexQuest);
	packet->setFlag(index);
	switch (index)
	{
	case 0:
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const OWN_QUEST* pQuest = &(GetQuestList()->m_aQuest[uIndexQuest]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		packet->setQuest(pQuest);
		packet->setFlagParam(uIndexParam);
		NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}
	break;

	case 1:
	{
		if (QuestManager::GetSingletonPtr()->getFlagMDClientFilter().IsSetBit(uIndexQuest))
		{
			packet->setFlagParam(uIndexParam);
			NetManager::GetSingletonPtr()->sendNetMessage(packet);
		}
		
	}
	default:
		return;
	}
	
}

void	Player::OnAddQuest(uint32 uIndex)
{


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const OWN_QUEST* pQuest = &(GetQuestList()->m_aQuest[uIndex]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	
	SCAddQuest* packet = new SCAddQuest;

	packet->setPlayerId(this->GetID());
	packet->setQuest(pQuest);

	NetManager::GetSingletonPtr()->sendNetMessage(packet);

}

void	Player::OnRemoveQuest(QuestID_t idQuest)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameConnector* pGameConnector = (GameConnector*)(GetConnector());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGameConnector != NULL && "Player::OnRemoveQuest");
	if (pGameConnector != NULL)
	{
		SCDelQuest* packet = new SCDelQuest;

		packet->setPlayerId(this->GetID());
		packet->setQuestId(idQuest);
		NetManager::GetSingletonPtr()->sendNetMessage(packet);
	}

	__UNGUARD__
}

const SArchiveLoader_Quest* Player::GetQuestList(void) const
{
	return mDB->GetQuestArchive();
}

void Player::SetQuestHaveDone(QuestID_t idQuest, BOOL bHaveDone)
{
	QuestID_t idIndex = (idQuest >> 5);
	if (idIndex >= 0 && idIndex < MAX_CHAR_QUEST_FLAG_LEN)
	{
		if (bHaveDone)
			mDB->SetQuestDone(idQuest, idIndex);
		else
			mDB->SetQuestUnDone(idQuest, idIndex);


		OnQuestHaveDoneFlagsChanged(idIndex);

	}
	else
	{

	}
}

BOOL Player::IsQuestHaveDone(QuestID_t idQuest)const
{
	if (idQuest < 0) return FALSE;

	QuestID_t idIndex = (idQuest >> 5);
	if (idIndex >= 0 && idIndex < MAX_CHAR_QUEST_FLAG_LEN)
		return ((GetQuestList()->m_aQuestHaveDoneFlags[idIndex] & (0x00000001 << ((uint32)idQuest & 0x0000001F))) != 0);
	else
		return FALSE;
}

int32_t Player::IsQuestCompleted(uint32 uIndexQuest) const
{
	return QuestManager::GetSingletonPtr()->IsQuestCompleted(this, uIndexQuest);
}

OPT_RESULT Player::AddQuest
(
	QuestID_t	idQuest,
	ScriptID_t	idScript,
	BOOL		bKillObjectEvent,
	BOOL		bEnterAreaEvent,
	BOOL		bItemChangedEvent,
	BOOL		bClickNPCEvent
)
{
	__GUARD__
	int32_t questCount = GetQuestList()->m_Count;
	if (questCount >= MAX_CHAR_QUEST_NUM) return OR_QUEST_LIST_FULL;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uIndex = GetQuestIndexByID(idQuest);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (uIndex != UINT_MAX) return OR_QUEST_HAVE;

	uIndex = UINT_MAX;

	/*~~~~~~*/
	uint32	i;
	/*~~~~~~*/

	for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
	{
		if (GetQuestList()->m_aQuest[i].m_idQuest == INVALID_ID)
		{
			uIndex = i;
			break;
		}
	}

	if (uIndex == UINT_MAX) return OR_QUEST_IS_FULL;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const OWN_QUEST* pQuest = GetQuest(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mDB->SetQuest(uIndex, idQuest, idScript);

	mDB->SetFlags_KillObject(uIndex, bKillObjectEvent);
	mDB->SetFlags_EnterArea(uIndex, bEnterAreaEvent);
	mDB->SetFlags_ItemChanged(uIndex, bItemChangedEvent);
	mDB->SetFlags_ClickNPC(uIndex, bClickNPCEvent);

	mDB->SetQuestCount(GetQuestList()->m_Count + 1);

	OnAddQuest(uIndex);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

OPT_RESULT Player::AddQuestEx(QuestID_t idQuest, ScriptID_t idScript)
{
	__GUARD__ if (GetQuestList()->m_Count >= MAX_CHAR_QUEST_NUM) return OR_QUEST_LIST_FULL;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uIndex = GetQuestIndexByID(idQuest);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (uIndex != UINT_MAX) return OR_QUEST_HAVE;

	uIndex = UINT_MAX;

	/*~~~~~~*/
	uint32	i;
	/*~~~~~~*/

	for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
	{
		if (GetQuestList()->m_aQuest[i].m_idQuest == INVALID_ID)
		{
			uIndex = i;
			break;
		}
	}

	if (uIndex == UINT_MAX) return OR_QUEST_IS_FULL;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const OWN_QUEST* pQuest = GetQuest(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mDB->SetQuest(uIndex, idQuest, idScript);

	mDB->SetFlags_KillObject(uIndex, FALSE);
	mDB->SetFlags_EnterArea(uIndex, FALSE);
	mDB->SetFlags_ItemChanged(uIndex, FALSE);
	mDB->SetFlags_ClickNPC(uIndex, TRUE);

	mDB->SetQuestCount(GetQuestList()->m_Count + 1);

	OnAddQuest(uIndex);

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

OPT_RESULT Player::SetQuestEvent(QuestID_t idQuest, int32 EventID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uIndex = GetQuestIndexByID(idQuest);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (uIndex == UINT_MAX) return OR_CANNOT_FIND_THIS_QUEST;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const OWN_QUEST* pQuest = GetQuest(uIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pQuest == NULL) return OR_CANNOT_FIND_THIS_QUEST;

	switch (EventID)
	{
	case TASK_EVENT_KILLOBJ:	mDB->SetFlags_KillObject(uIndex, TRUE); break;
	case TASK_EVENT_ENTERAREA:	mDB->SetFlags_EnterArea(uIndex, TRUE); break;
	case TASK_EVENT_ITEMCHANGED:	mDB->SetFlags_ItemChanged(uIndex, TRUE); break;
	case TASK_EVENT_PETCHANGED:	mDB->SetFlags_PetChanged(uIndex, TRUE); break;
	default:			KCheck(FALSE); break;
	}

	return OR_OK;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

BOOL Player::DelQuest(QuestID_t idQuest)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uIndex = GetQuestIndexByID(idQuest);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (uIndex == UINT_MAX) return FALSE;

	DelQuestByIndex(uIndex);
	return TRUE;
	__UNGUARD__ return FALSE;
}

void Player::DelQuestByIndex(uint32 uIndex)
{
	__GUARD__ if (uIndex < MAX_CHAR_QUEST_NUM && GetQuestList()->m_aQuest[uIndex].m_idQuest != INVALID_ID)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const OWN_QUEST* pQuest = GetQuest(uIndex);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		OnRemoveQuest(pQuest->m_idQuest);

		mDB->ClearQuest(uIndex);
	}

	__UNGUARD__
}

uint32_t Player::GetQuestIndexByID(QuestID_t idQuest) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	i;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	for (i = 0; i < MAX_CHAR_QUEST_NUM; i++)
	{
		if (GetQuestList()->m_aQuest[i].m_idQuest == idQuest)
		{
			return i;
		}
	}

	return UINT_MAX;
	__UNGUARD__ return UINT_MAX;
}

BOOL Player::IsHaveQuest(QuestID_t idQuest) const
{
	return (GetQuestIndexByID(idQuest) != UINT_MAX);
}

void Player::SetQuestParam(uint32 uIndexQuest, uint32 uIndexParam, int32 nValue)
{
	mDB->SetQuestParam(uIndexQuest, uIndexParam, nValue);
	OnQuestParamChanged(uIndexQuest, uIndexParam);
}

int32 Player::GetQuestParam(uint32 uIndexQuest, uint32 uIndexParam) const
{
	if (uIndexQuest < MAX_CHAR_QUEST_NUM && uIndexParam < MAX_QUEST_PARAM_NUM)
		return GetQuestList()->m_aQuest[uIndexQuest].m_anParam[uIndexParam];
	else
		return FALSE;
}

void Player::SetQuestParam_Unsigned(uint32 uIndexQuest, uint32 uIndexParam, uint32 nValue)
{
	//if (uIndexQuest < MAX_CHAR_QUEST_NUM && uIndexParam < MAX_QUEST_PARAM_NUM)
	{
		mDB->SetQuestParam_Unsigned(uIndexQuest, uIndexParam, nValue);
		OnQuestParamChanged(uIndexQuest, uIndexParam);
	}
}

uint32 Player::GetQuestParam_Unsigned(uint32 uIndexQuest, uint32 uIndexParam) const
{
	if (uIndexQuest < MAX_CHAR_QUEST_NUM && uIndexParam < MAX_QUEST_PARAM_NUM)
		return GetQuestList()->m_aQuest[uIndexQuest].m_aParam[uIndexParam];
	else
		return FALSE;
}

const OWN_QUEST* Player::GetQuest(uint32 uIndex) const
{
	if (uIndex < MAX_CHAR_QUEST_NUM)
		return &GetQuestList()->m_aQuest[uIndex];
	return nullptr;
}

int32_t Player::GetQuestData(int32_t nIndex)
{
	__GUARD__
		if (nIndex < 0 || nIndex >= MAX_CHAR_QUEST_DATA_NUM)
		{
			KCheckEx(FALSE, "下标超出范围");
			return 0;
		}
	return GetQuestList()->m_aQuestData[nIndex];
	__UNGUARD__
		return -1;
}
void Player::SetQuestData(int32_t nIndex, int32_t nData)
{
	__GUARD__
		if (nIndex < 0 || nIndex >= MAX_CHAR_QUEST_DATA_NUM)
		{
			KCheckEx(FALSE, "下标超出范围");
		}
	mDB->SetQuestData(nIndex, nData);
	OnQuestParamChanged(nIndex, nData, 1);
	__UNGUARD__
}

int32_t Player::GetQuestDataByBit(int32_t nIndex, int32_t nOffset, int32_t nSize)
{
	__GUARD__
		uint32	nQuestData = (uint32)GetQuestData(nIndex);

	KCheck(nOffset >= 0);
	KCheck(nSize > 0);
	KCheck((nOffset + nSize) <= 32);

	if (nOffset > 0) nQuestData <<= nOffset;
	if (nSize != 32) nQuestData >>= (32 - nSize);
	return nQuestData;
	__UNGUARD__
		return 0;
}
void Player::SetQuestDataByBit(int32_t nIndex, int32_t nOffset, int32_t nSize, int32_t nData)
{
	__GUARD__
		KCheck(nOffset >= 0);
	KCheck(nSize > 0);
	KCheck((nOffset + nSize) <= 32);

	if (nIndex < 0 || nIndex >= MAX_CHAR_QUEST_DATA_NUM)
	{
		return;
	}

	int32_t	nQuestData = GetQuestData(nIndex);

	for (int32_t i = 0; i < nSize; i++)
	{
		int32_t	nBit = nData & 1 << i;
		if (nBit)
		{
			nQuestData |= (1 << (32 - nOffset - nSize + i));
		}
		else
		{
			nQuestData &= (~(1 << (32 - nOffset - nSize + i)));
		}
	}

	SetQuestData(nIndex, nQuestData);
	__UNGUARD__
}

int32_t	Player::IfCanRecvQuest(const _QUEST_DATA_t* pData, ObjID_t targetId)
{
	__GUARD__ if (pData == NULL) return FALSE;

	if (pData->nMinLevel != -1 && GetLevel() < pData->nMinLevel)
	{
		return -1;
	}

	if (pData->nMaxLevel != -1 && GetLevel() > pData->nMaxLevel)
	{
		return -2;
	}

	if (pData->nProfession != -1 && GetProfession() != pData->nProfession)
	{
		return -5;
	}

	if (pData->nCamp != -1)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object* pTargetObj = (Object*)GetMap()->GetSpecificObjByID(targetId);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pTargetObj == NULL) return -6;
		if (pTargetObj->GetObjType() != Object::OBJECT_CLASS_MONSTER) return -6;
	}

	return 1;

	__UNGUARD__ return 0;
}



void Player::SetCurTarget(ObjID_t idTarget)
{
	m_CurTargetID = idTarget;
}

ObjID_t Player::GetCurTarget(void) const
{
	return m_CurTargetID;
}

void Player::SetPatrolID(int32_t nIndex)
{

}

int32_t Player::GetPatrolID(void) const
{
	return 0;
}

void Player::SetCurrentPathNode(int32_t nNode)
{

}

int32_t Player::GetCurrentPathNode(void) const
{
	return 0;
}





void Player::SetExploit(int32_t nExploit)
{

}

int32_t Player::GetExploit()
{
	return 0;
}

void Player::SetExploitDay(int16 nDay)
{

}

int16 Player::GetExploitDay()
{
	return 0;
}

int32 Player::Get_Property_GoodBadValue()
{
	return 0;
}

int32 Player::Set_Property_GoodBadValue(int32 nValue)
{
	return 0;
}

int32 Player::IncGoodBadValue(int32 nValue)
{
	return 0;
}

int32 Player::DecGoodBadValue(int32 nValue)
{
	return 0;
}

int32 Player::GetHonor()
{
	return 0;
}

void Player::SetHonor(int32 nHonor)
{

}

int32 Player::GetFeastScore()
{
	return 0;
}

void Player::SetFeastScore(int32 iFeastScore)
{

}

uint32 Player::GetCurInherenceExp()
{
	return 0;
}

void Player::SetCurInherenceExp(uint32 nInherenceExp)
{

}

void Player::DecCurInherenceExp(uint32 nInherenceExp)
{

}

uint32 Player::GetNextInherenceExp()
{
	return 0;
}

uint32 Player::GetNextInherenceMoney()
{
	return 0;
}

uint32 Player::GetNextInherenceItem()
{
	return 0;
}

uint16 Player::GetInherenceLevel()
{
	return 0;
}

uint32 Player::RefixInherenceExp(uint32 nInherenceExp)
{
	return 0;
}

int32 Player::GetGuildSkillAllPoint()
{
	return 0;
}

void Player::SetGuildSkillAllPoint(int32 nallPoint)
{

}

void Player::CountGuildSkillAllPoint()
{

}

bool Player::IsGuildSkill(int32 nSpelllID)
{
	return true;
}


ID_t Player::GetWorldID()
{
	return 0;
}

int32				Player::GetAttack()
{
	SItemEffect* pIE = NULL;
	int32		nBaseAttr = 0;
	int32		nEquipBaseAttr = 0;
	int32		nItemBaseRateRefix = 0;
	int32		nItemBasePointRefix = 0;
	int32		nItemPointRefix = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (
		(GetProfession() == PROFESSION_WUSHI) || (GetProfession() == PROFESSION_QISHE) ||
		(GetProfession() == PROFESSION_SHIZIJUN) || (GetProfession() == PROFESSION_CIKE)
		)
	{
		nBaseAttr = GetBaseAttackNear();
		nItemBaseRateRefix = 0;
		pIE = ItemEffect(IPROPERTY_BASE_ATTACK_NEAR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemBasePointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_BASE_RATE_ATTACK_ENEAR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemBaseRateRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_ATTACK_NEAR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_ATTACK_NEAR_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix += pIE->m_Attr.m_Value;
		}

		nEquipBaseAttr = nBaseAttr +
			Float2Int((nItemBasePointRefix + nBaseAttr) * nItemBaseRateRefix / 100.0f) +
			nItemBasePointRefix +
			nItemPointRefix;
	}
	else if (
		(GetProfession() == PROFESSION_XIANZHI) || (GetProfession() == PROFESSION_HUOQIANG) ||
		(GetProfession() == PROFESSION_YINXIUSHI) || (GetProfession() == PROFESSION_JINWEIJUN)
		)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = GetBaseAttackFar();
		int32	nItemBaseRateRefix = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_BASE_ATTACK_FAR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemBasePointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_BASE_RATE_ATTACK_FAR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemBaseRateRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_ATTACK_FAR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_ATTACK_FAR_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix += pIE->m_Attr.m_Value;
		}

		nEquipBaseAttr = nBaseAttr +
			Float2Int((nItemBasePointRefix + nBaseAttr) * nItemBaseRateRefix / 100.0f) +
			nItemBasePointRefix +
			nItemPointRefix;
	}
	else if (
		(GetProfession() == PROFESSION_JIANXIA) || (GetProfession() == PROFESSION_SAMAN) ||
		(GetProfession() == PROFESSION_SHENGHUOSHI) || (GetProfession() == PROFESSION_LAMA)
		)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = Get_BaseProperty_AttackMagic();
		int32	nItemBaseRateRefix = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_BASE_ATTACK_M);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemBasePointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_BASE_RATE_ATTACK_M);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemBaseRateRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_ATTACK_M);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_ATTACK_M_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix += pIE->m_Attr.m_Value;
		}

		nEquipBaseAttr = nBaseAttr +
			Float2Int((nItemBasePointRefix + nBaseAttr) * nItemBaseRateRefix / 100.0f) +
			nItemBasePointRefix +
			nItemPointRefix;
	}

	return nEquipBaseAttr;
}

int32				Player::Get_Property_MaxStrikePoint(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_STRIKE_POINT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseMaxStrikePoint() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_STRIKE_POINT);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nValue > MAX_STRIKE_POINT ? nValue = MAX_STRIKE_POINT : NULL;
		SetIntAttr(CharIntProperty::PROPERTY_MAX_STRIKE_POINT, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_STRIKE_POINT);
		if (Get_Property_StrikePoint() > nValue) Set_Property_StrikePoint(nValue);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MAX_STRIKE_POINT);
}

int32				Player::GetAttrLevel1AttackNear(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::GetBaseAttackNear]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->GetInitNearAttackPhysics();
	int32 nAttrLevelStrRefix = pProfessionLogic->Get_Property_NearAttackPhysicsStrRefix();
	int32 nAttrLevelDexRefix = pProfessionLogic->Get_Property_NearAttackPhysicsDexRefix();
	int32 nAttrLevelIntRefix = pProfessionLogic->Get_Property_NearAttackPhysicsIntRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_NearAttackPhysicsLevelRefix();
	int32 nBase = nInitAttr +
		Get_Property_Str() *
		nAttrLevelStrRefix +
		Get_Property_Dex() *
		nAttrLevelDexRefix +
		Get_Property_Int() *
		nAttrLevelIntRefix +
		GetLevel() *
		nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32				Player::GetAttrLevel1AttackFar(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::GetBaseAttackFar]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->GetInitFarAttackPhysics();
	int32 nAttrLevelStrRefix = pProfessionLogic->Get_Property_FarAttackPhysicsStrRefix();
	int32 nAttrLevelDexRefix = pProfessionLogic->Get_Property_FarAttackPhysicsDexRefix();
	int32 nAttrLevelIntRefix = pProfessionLogic->Get_Property_FarAttackPhysicsIntRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_FarAttackPhysicsLevelRefix();
	int32 nBase = nInitAttr +
		Get_Property_Str() *
		nAttrLevelStrRefix +
		Get_Property_Dex() *
		nAttrLevelDexRefix +
		Get_Property_Int() *
		nAttrLevelIntRefix +
		GetLevel() *
		nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32				Player::GetAttrLevel1AttackMagic(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_AttackMagic]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->Get_Property_InitAttackMagic();
	int32 nAttrLevelStrRefix = pProfessionLogic->Get_Property_AttackMagicStrRefix();
	int32 nAttrLevelDexRefix = pProfessionLogic->Get_Property_AttackMagicDexRefix();
	int32 nAttrLevelIntRefix = pProfessionLogic->Get_Property_AttackMagicIntRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_AttackMagicLevelRefix();
	int32 nBase = nInitAttr +
		Get_Property_Str() *
		nAttrLevelStrRefix +
		Get_Property_Dex() *
		nAttrLevelDexRefix +
		Get_Property_Int() *
		nAttrLevelIntRefix +
		GetLevel() *
		nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32				Player::GetAttrLevel1Hit(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_Hit]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->Get_Property_InitHit();
	int32 nAttrLevel1Refix = pProfessionLogic->Get_Property_HitStrRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_HitLevelRefix();
	int32 nBase = nInitAttr + Get_Property_Str() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32				Player::GetAttrLevel1Miss(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_Miss]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->Get_Property_InitMiss();
	int32 nAttrLevel1Refix = pProfessionLogic->Get_Property_MissDexRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_MissLevelRefix();
	int32 nBase = nInitAttr + Get_Property_Dex() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32				Player::GetAttrLevel1Critical(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_Critical]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->Get_Property_InitCritical();
	int32 nAttrLevel1Refix = pProfessionLogic->Get_Property_CriticalIntRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_CriticalLevelRefix();
	int32 nBase = nInitAttr + Get_Property_Int() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32 Player::GetAttrLevel1MaxHP(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_MaxHP]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->Get_Property_InitMaxHP();
	int32 nAttrLevel1Refix = pProfessionLogic->Get_Property_MaxHPConRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_MaxHPLevelRefix();
	int32 nBase = nInitAttr + Get_Property_Con() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
	__UNGUARD__ return 0;
}

int32				Player::GetAttrLevel1MaxRage(void)
{
	int32 nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::GetBaseMaxRage]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nInitAttr = pProfessionLogic->GetInitMaxRage();
	int32 nAttrLevel1Refix = pProfessionLogic->Get_Property_MaxRageIntRefix();
	int32 nLevelRefix = pProfessionLogic->Get_Property_MaxRageLevelRefix();
	int32 nBase = nInitAttr + Get_Property_Int() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

int32				Player::Get_Property_Str(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_STR))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		nItemValue = 0;
		int32		nBaseAttr = Get_BaseProperty_Str();
		int32		nImpactAndSkillRefix = 0;
		int32		nItemRateRefix = 0;
		SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_STR);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_STR_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue += pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_STR);

		nBaseAttr = nBaseAttr + nItemValue + nImpactAndSkillRefix;

		pIE = ItemEffect(IPROPERTY_RATE_STR);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr * (pIE->m_Attr.m_Value)) / 100.0f);
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = nBaseAttr + nItemRateRefix;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_STR, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_STR);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_STR);
}

int32				Player::Get_BaseProperty_Str(void)
{
	return mDB->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_STR);
}

void				Player::Set_BaseProperty_Str(int32 const nValue)
{
	mDB->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_STR, nValue);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_STR);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_NEAR);
}

int32				Player::Get_Property_Con(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CON))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		nItemValue = 0;
		int32		nBaseAttr = Get_BaseProperty_Con();
		int32		nImpactAndSkillRefix = 0;
		int32		nItemRateRefix = 0;
		SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_CON);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_CON_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue += pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CON);

		nBaseAttr = nBaseAttr + nItemValue + nImpactAndSkillRefix;

		pIE = ItemEffect(IPROPERTY_RATE_CON);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr * (pIE->m_Attr.m_Value)) / 100.0f);
		}


		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = nBaseAttr + nItemRateRefix;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_CON, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CON);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_CON);
}

int32				Player::Get_BaseProperty_Con(void)
{
	return mDB->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_CON);
}

void				Player::Set_BaseProperty_Con(int32 const nValue)
{
	mDB->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_CON, nValue);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CON);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_HP);
}

int32				Player::Get_Property_Int(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_INT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		nItemValue = 0;
		int32		nBaseAttr = Get_BaseProperty_Int();
		int32		nImpactAndSkillRefix = 0;
		int32		nItemRateRefix = 0;
		SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_INT);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_INT_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue += pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_INT);

		nBaseAttr = nBaseAttr + nItemValue + nImpactAndSkillRefix;

		pIE = ItemEffect(IPROPERTY_RATE_INT);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr * (pIE->m_Attr.m_Value)) / 100.0f);
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = nBaseAttr + nItemRateRefix;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_INT, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_INT);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_INT);
}

int32				Player::Get_BaseProperty_Int(void)
{
	return mDB->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_INT);
}

void				Player::Set_BaseProperty_Int(int32 const nValue)
{
	mDB->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_INT, nValue);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_INT);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_MP);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_MAGIC);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CRITICAL);
}

int32				Player::Get_Property_Dex(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEX))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		nItemValue = 0;
		int32		nBaseAttr = Get_BaseProperty_Dex();
		int32		nImpactAndSkillRefix = 0;
		int32		nItemRateRefix = 0;
		SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_DEX);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_DEX_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemValue += pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEX);

		nBaseAttr = nBaseAttr + nItemValue + nImpactAndSkillRefix;
		pIE = ItemEffect(IPROPERTY_RATE_DEX);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr * (pIE->m_Attr.m_Value)) / 100.0f);
		}

	
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = nBaseAttr + nItemRateRefix;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_DEX, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEX);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_DEX);
}

int32				Player::Get_BaseProperty_Dex(void)
{
	return mDB->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_DEX);
}

void				Player::Set_BaseProperty_Dex(int32 const nValue)
{
	mDB->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_DEX, nValue);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEX);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_FAR);
}

int32_t     Player::GetMaxHP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_HP))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = GetAttrLevel1MaxHP();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_POINT_MAXHP);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		pIE = ItemEffect(IPROPERTY_POINT_MAXHP_PURPLE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix += pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP);

		nBaseAttr = nBaseAttr + nItemPointRefix + nImpactAndSkillRefix;
		pIE = ItemEffect(IPROPERTY_RATE_MAXHP);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr * (pIE->m_Attr.m_Value)) / 100.0f);
		}

		nValue = nBaseAttr + nItemRateRefix;
		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_MAX_HP, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_HP);
		if (GetHP() > nValue) SetHP(nValue);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MAX_HP);
	__UNGUARD__ return 0;
}

int32				Player::Get_BaseProperty_MaxHP(void)
{
	int32		nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_MaxHP]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nInitAttr = pProfessionLogic->Get_Property_InitMaxHP();
	int32	nAttrLevel1Refix = pProfessionLogic->Get_Property_MaxHPConRefix();
	int32	nLevelRefix = pProfessionLogic->Get_Property_MaxHPLevelRefix();
	int32	nBase = nInitAttr + Get_BaseProperty_Con() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

void				Player::Set_BaseProperty_MaxHP(int32 const nHp)
{

}

int32				Player::Get_Property_HPRegenerate(void)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HP_REGENERATE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = Get_BaseProperty_HPRegenerate();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_HP_RESTORE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_HP_REGENERATE);
		nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix;
		SetIntAttr(CharIntProperty::PROPERTY_HP_REGENERATE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HP_REGENERATE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_HP_REGENERATE);
}

int32				Player::Get_BaseProperty_HPRegenerate(void)
{
	int32			nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_HPRegenerate]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nInitAttr = pProfessionLogic->Get_Property_InitHPRegenerate();
	int32	nLevelRefix = pProfessionLogic->Get_Property_HPRegenerateLevelRefix();
	int32	nBase = nInitAttr + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

void				Player::Set_BaseProperty_HPRegenerate(int32 const nValue)
{

}

int32				Player::GetMaxMP(void)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_MP))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = Get_BaseProperty_MaxMP();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_POINT_MAXMP);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_MP);

		nBaseAttr = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix;
		pIE = ItemEffect(IPROPERTY_RATE_MAXMP);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr * (pIE->m_Attr.m_Value)) / 100.0f);
		}

		nValue = nBaseAttr + nItemRateRefix;
		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_MAX_MP, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_MP);
		if (GetMP() > nValue) SetMP(nValue);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MAX_MP);
}

int32				Player::Get_BaseProperty_MaxMP(void)
{
	int32			nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_MaxMP]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nInitAttr = pProfessionLogic->Get_Property_InitMaxMP();
	int32	nAttrLevel1Refix = 0;
	int32	nLevelRefix = pProfessionLogic->Get_Property_MaxMPLevelRefix();
	int32	nBase = nInitAttr + Get_Property_Int() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

void				Player::Set_BaseProperty_MaxMp(int32 const nMp)
{

}

int32				Player::Get_Property_MPRegenerate(void)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MP_REGENERATE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = Get_BaseProperty_MPRegenerate();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pIE = ItemEffect(IPROPERTY_MP_RESTORE);
		KCheck(pIE);
		if (pIE->IsActive())
		{
			nItemPointRefix = pIE->m_Attr.m_Value;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MP_REGENERATE);
		nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + nItemRateRefix;
		SetIntAttr(CharIntProperty::PROPERTY_MP_REGENERATE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MP_REGENERATE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MP_REGENERATE);
}

int32				Player::Get_BaseProperty_MPRegenerate(void)
{
	int32			nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::Get_BaseProperty_MPRegenerate]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nInitAttr = pProfessionLogic->Get_Property_InitMPRegenerate();
	int32	nLevelRefix = pProfessionLogic->Get_Property_MPRegenerateLevelRefix();
	int32	nBase = nInitAttr + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

void				Player::Set_BaseProperty_MPRegenerate(int32 const nValue)
{

}

int32				Player::Get_Property_MaxRage(void)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_RAGE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = GetAttrLevel1MaxRage();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nItemValue = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch (GetProfession())
		{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_WUSHI_MAXRAGE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_WUSHI_MAXRAGE_PURPLE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix += pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_WUSHI_MAXRAGE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}
		}
		break;

		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_JIANXIA_MAXRAGE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_JIANXIA_MAXRAGE_PURPLE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix += pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_JIANXIA_MAXRAGE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}
		}
		break;

		case PROFESSION_QISHE:
		case PROFESSION_CIKE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_QISHE_MAXRAGE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_QISHE_MAXRAGE_PURPLE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix += pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_QISHE_MAXRAGE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}
		}
		break;

		case PROFESSION_HUOQIANG:
		case PROFESSION_JINWEIJUN:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_HUOQIANG_MAXRAGE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_HUOQIANG_MAXRAGE_PURPLE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix += pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_HUOQIANG_MAXRAGE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}
		}
		break;

		case PROFESSION_XIANZHI:
		case PROFESSION_YINXIUSHI:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_XIANZHI_MAXRAGE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_XIANZHI_MAXRAGE_PURPLE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix += pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_XIANZHI_MAXRAGE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}
		}
		break;

		case PROFESSION_SAMAN:
		case PROFESSION_LAMA:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_SAMAN_MAXRAGE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_SAMAN_MAXRAGE_PURPLE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix += pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_SAMAN_MAXRAGE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}
		}
		break;

		default:
			KCheck(0);
			break;
		}

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_RAGE);

		nBaseAttr = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix;

		nValue = nBaseAttr + Float2Int((nBaseAttr * nItemRateRefix) / 100.0f);
		CHECK_ATTR_VALUE(nValue);
		SetIntAttr(CharIntProperty::PROPERTY_MAX_RAGE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_RAGE);
		if (Get_Property_Rage() > nValue) Set_Property_Rage(nValue);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MAX_RAGE);
}

int32				Player::GetBaseMaxRage(void)
{
	int32		nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::GetBaseMaxRage]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nInitAttr = pProfessionLogic->GetInitMaxRage();
	int32	nAttrLevel1Refix = pProfessionLogic->Get_Property_MaxRageIntRefix();
	int32	nLevelRefix = pProfessionLogic->Get_Property_MaxRageLevelRefix();
	int32	nBase = nInitAttr + Get_BaseProperty_Int() * nAttrLevel1Refix + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	0 <= nBase ? NULL : nBase = 0;
	return nBase;
}

void				Player::SetBaseMaxRage(int32 const nRage)
{

}

int32				Player::GetRageRegenerate(void)
{
	SItemEffect* pIE = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RAGE_REGENERATE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nBaseAttr = GetBaseRageRegenerate();
		int32	nImpactAndSkillRefix = 0;
		int32	nItemPointRefix = 0;
		int32	nItemRateRefix = 0;
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nImpactAndSkillRefix = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);

		switch (GetProfession())
		{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_WUSHI_RAGE_RESTORE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_WUSHI_RAGE_RESTORE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}

			nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + Float2Int((Get_Property_MaxRage() * nItemRateRefix) / 100.0f);
		}
		break;

		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_JIANXIA_RAGE_RESTORE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_JIANXIA_RAGE_RESTORE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}

			nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + Float2Int((Get_Property_MaxRage() * nItemRateRefix) / 100.0f);
		}
		break;

		case PROFESSION_QISHE:
		case PROFESSION_CIKE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_QISHE_RAGE_RESTORE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_QISHE_RAGE_RESTORE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}

			nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + Float2Int((Get_Property_MaxRage() * nItemRateRefix) / 100.0f);
		}
		break;

		case PROFESSION_HUOQIANG:
		case PROFESSION_JINWEIJUN:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_HUOQIANG_RAGE_RESTORE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_HUOQIANG_RAGE_RESTORE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}

			nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + Float2Int((Get_Property_MaxRage() * nItemRateRefix) / 100.0f);
		}
		break;

		case PROFESSION_XIANZHI:
		case PROFESSION_YINXIUSHI:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_XIANZHI_RAGE_RESTORE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_XIANZHI_RAGE_RESTORE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}

			nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + Float2Int((Get_Property_MaxRage() * nItemRateRefix) / 100.0f);
		}
		break;

		case PROFESSION_SAMAN:
		case PROFESSION_LAMA:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SItemEffect* pIE = ItemEffect(IPROPERTY_POINT_SAMAN_RAGE_RESTORE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemPointRefix = pIE->m_Attr.m_Value;
			}

			pIE = ItemEffect(IPROPERTY_RATE_SAMAN_RAGE_RESTORE);
			KCheck(pIE);
			if (pIE->IsActive())
			{
				nItemRateRefix = pIE->m_Attr.m_Value;
			}

			nValue = nBaseAttr + nImpactAndSkillRefix + nItemPointRefix + Float2Int((Get_Property_MaxRage() * nItemRateRefix) / 100.0f);
		}
		break;

		default:
			KCheck(0);
			break;
		}

		if (nValue == 0)
		{
			if (GetProfession() != PROFESSION_WUSHI && GetProfession() != PROFESSION_SHIZIJUN)
			{
				QLogSystem::SLOW_LOG
				(
					SLOW_LOG_SERVERERROR,
					"Attr RageRegeValue = 0, nJob = %d, nBaseAttr = %d, nImpactAndSkillRefix = %d, nItemPointRefix=%d, MaxRage=%d, nItemRateRefix=%d",
					GetProfession(),
					nBaseAttr,
					nImpactAndSkillRefix,
					nItemPointRefix,
					Get_Property_MaxRage(),
					nItemRateRefix
				);
			}
		}

		SetIntAttr(CharIntProperty::PROPERTY_RAGE_REGENERATE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RAGE_REGENERATE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_RAGE_REGENERATE);
}

int32				Player::GetBaseRageRegenerate(void)
{
	int32			nProfessionID = GetProfession();
	Profession const* pProfessionLogic = g_ProfessionLogicList.GetLogicById(nProfessionID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pProfessionLogic)
	{
		KCheckEx(FALSE, "[Player::GetBaseRageRegenerate]: Can't not find Profession Logic!");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nInitAttr = pProfessionLogic->GetInitRageRegenerate();
	int32	nLevelRefix = pProfessionLogic->Get_Property_RageRegenerateLevelRefix();
	int32	nBase = nInitAttr + GetLevel() * nLevelRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nBase = Float2Int((nBase) / 100.0f);
	return nBase;
}

void				Player::SetBaseRageRegenerate(int32 const nValue)
{

}

const SCampData* Player::GetBaseCampData(void) const
{
	return mDB->GetDBCampData();
}

void Player::SetBaseCampData(const SCampData* pCampData)
{
	mDB->SetDBCampData(pCampData);
}

int32_t Player::GetCampID(void)
{
	if (TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CAMP))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CAMP);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (INVALID_ID == nValue)
		{
			nValue = GetBaseCampID();
		}

		SetIntAttr(CharIntProperty::PROPERTY_CAMP, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CAMP);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_CAMP);
}

int32_t			Player::GetBaseCampID(void) const
{
	PlayerArchive* pDB = (PlayerArchive*)mDB;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return pDB->GetDBCampData()->m_nCampID;
}

void Player::SetBaseCampID(int32_t const nID)
{
	SCampData	stCampData = *(mDB->GetDBCampData());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	stCampData.m_nCampID = nID;
	mDB->SetDBCampData(&stCampData);
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CAMP);
}

void				Player::RefixCamp()
{
	int32 nCountry = GetCountry();
	int32		nCamp = GetCampID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nCountry == COUATTRIBUTE_LOULAN && nCamp != CAMP_A)
	{
		SetBaseCampID(CAMP_A);
	}
	else if (nCountry == COUATTRIBUTE_LAIYIN && nCamp != CAMP_B)
	{
		SetBaseCampID(CAMP_B);
	}
	else if (nCountry == COUATTRIBUTE_KUNLUN && nCamp != CAMP_C)
	{
		SetBaseCampID(CAMP_C);
	}
	else if (nCountry == COUATTRIBUTE_DUNHUANG && nCamp != CAMP_D)
	{
		SetBaseCampID(CAMP_D);
	}
	else if
		(
			nCountry != COUATTRIBUTE_LOULAN
			&& nCountry != COUATTRIBUTE_KUNLUN
			&& nCountry != COUATTRIBUTE_DUNHUANG
			&& nCountry != COUATTRIBUTE_LAIYIN
			)
	{
		QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG, "Player::RefixCamp error country:%d, camp:%d", nCountry, nCamp);
	}
}





