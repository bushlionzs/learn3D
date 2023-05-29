/*$T Common/StructDB.cpp GC 1.140 10/10/07 10:06:55 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "StructDB.h"
#include "Util.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void SArchiveLoader_Player::Clear()
{
	m_bFirstEnterScence = TRUE;
	m_PortraitID = -1;
	memset(m_Name, 0, MAX_CHARACTER_NAME);
	memset(m_Title, 0, MAX_CHARACTER_TITLE);
	m_GUID = INVALID_ID;
	m_Sex = INVALID_SEX;
	m_CreateDate = 0;
	m_Level = 0;
	m_Vigor = 0;
	m_MaxVigor = 0;
	m_VigorRegeneRate = 0;
	m_Energy = 0;
	m_MaxEnergy = 0;
	m_EnergyRegeneRate = 0;
	m_Exp = 0;
	m_Siller = 0;
	m_Gold = 0;
	m_BindSiller = 0;
	m_BindGold = 0;
	m_MoneyMode = 0;
	memset(m_Passwd, 0, MAX_PWD);
	m_uPwdFlag = 0;
	m_uPwdDelTime = 0;
	m_cLastProtectTime = 0;
	m_cProtectTime = 0;
	m_uProtectDelTime = 0;
	m_HairColor = 0xFFFFFFFF;
	m_FaceColor = 0xFF;
	m_HairModel = -1;
	m_FaceModel = -1;

	m_SoulID = INVALID_SOUL_TYPE;
	m_GemAff = INVALID_ID;
	m_SetSuit = INVALID_ID;
	m_LevelAff = 0;
	m_StartScene = INVALID_ID;
	m_BakScene = INVALID_ID;
	m_NextScene = INVALID_ID;
	m_GuildID = INVALID_ID;
	m_TeamID = INVALID_ID;
	m_FamilyID = INVALID_ID;
	m_nGuildOfficial = INVALID_ID;
	m_Position.Clear();
	m_BakPosition.Clear();
	m_NextPosition.Clear();
	m_OnlineTime = 0;
	m_OnlineTimeToday = 0;
	m_LastLoginTime = 0;
	m_LastLogoutTime = 0;
	m_LeaveGuildTime = 0;
	m_LeftDieTime = 0;
	m_DBVersion = 0;
	m_BusID = INVALID_ID;
	m_nGoodBadValue = 0;

	m_CampData.Clear();
	m_nCountry = INVALID_COUNTRY;
	m_nProfession = INVALID_JOB;
	m_HP = 0;
	m_MP = 0;
	m_StrikePoint = 0;
	m_Rage = 0;
	m_guidCurrentPet.Reset();
	m_BaseAttrLevel1.Clear();
	memset(m_Reserve, 0, sizeof(int32) * MAX_RESERVE);

	m_Level1Points = 0;
	m_RemainSkillPoints = 0;
	m_nGP = 0;
	m_nMerit = 0;
	m_nHonor = 0;
	m_nInherenceExp = 0;
	m_nInherenceLevel = 1;
	m_nPKValue = 0;
	m_nWenCai = 0;
	m_nRongYu = 0;
	m_nShengWang = 0;
	m_nHotValue = 0;
	m_LastForbidChatTime = INVALID_ID;
	m_LastEnjailTime = INVALID_ID;
	m_nCountryOfficial = COUNTRY_POSITION_INVALID;
	m_cGuildBuild_Count = 0;
	m_nGuildBuild_Day = 0;
	m_nLastChgPKModeTime = 0;

	memset(m_S_SkillPoints, 0, sizeof(int32) * COMMON_S_NUMBER);
	m_IsDelChar = FALSE;
	m_nWallowOfflineTime = 0;
	m_nWallowOnlineTime = 0;
	m_nTotalOnlineTime = 0;
	m_nIsNeedRename = 0;
	memset(m_szNewName, 0, sizeof(m_szNewName));
	m_TiredTime = 0;

	m_Titles.Clear();
	m_nKillCountToday = 0;
	m_nPVP2V2_Level = PVP2V2_INIT_LEVEL;
	m_nPVP2V2_Mark = 0;
	m_nPVP2V2_Day = 0;
	m_nPVP2V2_Mark_WeekTotal = 0;

	m_uDBFlag = 0;
	m_nExploit = 0;
	m_nExploitDay = -1;
	
	m_nPlayerWorldID = INVALID_ID;
	m_MountModelID = -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SArchiveLoader_Player::FillCrcData(char *buffer)
{
	/*~~~~~~~~~~~~~~~*/
	int32	nStart = 0;
	/*~~~~~~~~~~~~~~~*/

	memcpy(buffer + nStart, &m_GUID, sizeof(m_GUID));
	nStart += sizeof(m_GUID);

	memcpy(buffer + nStart, &m_Level, sizeof(m_Level));
	nStart += sizeof(m_Level);

	memcpy(buffer + nStart, &m_Exp, sizeof(m_Exp));
	nStart += sizeof(m_Exp);

	/*~~~~~~~~~~~~~~~~~~~~*/
	int32	nReserveExp = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	memcpy(buffer + nStart, &nReserveExp, sizeof(nReserveExp));
	nStart += sizeof(nReserveExp);

	memcpy(buffer + nStart, &m_Siller, sizeof(m_Siller));
	nStart += sizeof(m_Siller);

	memcpy(buffer + nStart, &m_Gold, sizeof(m_Gold));
	nStart += sizeof(m_Gold);

	memcpy(buffer + nStart, &m_BindSiller, sizeof(m_BindSiller));
	nStart += sizeof(m_BindSiller);

	memcpy(buffer + nStart, &m_BindGold, sizeof(m_BindGold));
	nStart += sizeof(m_BindGold);

	memcpy(buffer + nStart, &m_nHonor, sizeof(m_nHonor));
	nStart += sizeof(m_nHonor);

	memcpy(buffer + nStart, &m_nInherenceExp, sizeof(m_nInherenceExp));
	nStart += sizeof(m_nInherenceExp);

	memcpy(buffer + nStart, &m_nInherenceLevel, sizeof(m_nInherenceLevel));
	nStart += sizeof(m_nInherenceLevel);

	memcpy(buffer + nStart, &m_nWenCai, sizeof(m_nWenCai));
	nStart += sizeof(m_nWenCai);

	memcpy(buffer + nStart, &m_nRongYu, sizeof(m_nRongYu));
	nStart += sizeof(m_nRongYu);

	memcpy(buffer + nStart, &m_nShengWang, sizeof(m_nShengWang));
	nStart += sizeof(m_nShengWang);

	memcpy(buffer + nStart, &m_nHotValue, sizeof(m_nHotValue));
	nStart += sizeof(m_nHotValue);

	return nStart;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SHorseSkill::Clear(void)
{
	m_nSkillID = INVALID_ID;
	m_bCanUse = FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _HORSE_DB_LOAD::Clear()
{
	memset(this, 0, sizeof(_HORSE_DB_LOAD));
	m_GUID.Reset();

	m_nDataID = INVALID_ID;
	memset(m_szName, 0, MAX_CHARACTER_NAME);
	memset(m_szNick, 0, MAX_NICK_NAME);

	m_nExp = 0;
	m_nLevel = 0;

	m_nTakeLevel = 0;
	m_nAttackType = 0;
	m_AIType = _HORSE_DB_LOAD::PET_AI_INVALID;
	m_CampData.Clear();

	m_byGeneration = 0;
	m_byHappiness = 0;

	m_iStrengthPerception = 0;
	m_iSmartnessPerception = 0;
	m_iMindPerception = 0;
	m_iConstitutionPerception = 0;

	m_iStrengthPoint = 0;
	m_iSmartnessPoint = 0;
	m_iMindPoint = 0;
	m_iConstitutionPoint = 0;

	m_fGrowRate = 0;
	m_nRemainPoint = 0;
	m_iStatus = PET_STATUS_INVALID;
	m_iModelID = INVALID_ID;
	for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		m_SkillList[i].Clear();
	}

	for(int32 i = 0; i < 6; ++i)
	{
		m_SkillList[i].m_bCanUse = TRUE;
	}

	m_uHappinessLeftTime = 0xFFFFFFFF;
	m_iStallOrder = -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _HORSE_DB_LIST_LOAD::Clear(void)
{
	/*~~~~~~*/
	uint32	i;
	/*~~~~~~*/

	for(i = 0; i < PLAYER_PET_MAX_COUNT; i++)
	{
		m_aPetDB[i].Clear();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _BANKPET_DB_LIST_LOAD::Clear(void)
{
	/*~~~~~~*/
	uint32	i;
	/*~~~~~~*/

	for(i = 0; i < PLAYER_BANKPET_MAX_COUNT; i++)
	{
		m_aPetDB[i].Clear();

		m_aPetDB[i].m_iStallOrder = PLAYER_PET_MAX_COUNT + i;
	}

	m_uValidCount = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 _HORSE_DB_LIST_LOAD::FillCrcData(char *buffer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		i;
	int32		nStart = 0;
	_HORSE_DB_LOAD	*apPet[PLAYER_PET_MAX_COUNT] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		if(m_aPetDB[i].m_GUID.IsNull()) continue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nIndex = m_aPetDB[i].m_iStallOrder;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nIndex < 0 || nIndex >= PLAYER_PET_MAX_COUNT) continue;
		apPet[nIndex] = &m_aPetDB[i];
	}

	for(i = 0; i < PLAYER_PET_MAX_COUNT; ++i)
	{
		if(apPet[i] == NULL) continue;

		memcpy(buffer + nStart, &(apPet[i]->m_nDataID), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_nLevel), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_byGeneration), sizeof(uchar));
		nStart += sizeof(uchar);

		memcpy(buffer + nStart, &(apPet[i]->m_byHappiness), sizeof(uchar));
		nStart += sizeof(uchar);

		memcpy(buffer + nStart, &(apPet[i]->m_iStrengthPerception), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iSmartnessPerception), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iMindPerception), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iConstitutionPerception), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iStrengthPoint), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iSmartnessPoint), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iMindPoint), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_iConstitutionPoint), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_nRemainPoint), sizeof(int32));
		nStart += sizeof(int32);

		memcpy(buffer + nStart, &(apPet[i]->m_nExp), sizeof(int32));
		nStart += sizeof(int32);
	}

	return nStart;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Bank::Clear()
{
	memset(m_pItem, 0, MAX_BANK_SIZE * sizeof(SItem));
	m_Count = 0;
	m_CurEndIndex = CUR_BANK_SIZE;
	m_Money = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SArchiveLoader_Bank::FillCrcData(char *buffer)
{
	/*~~~~~~~~~~~~~~~*/
	int32	nStart = 0;
	/*~~~~~~~~~~~~~~~*/

	memcpy(buffer + nStart, &m_CurEndIndex, sizeof(m_CurEndIndex));
	nStart += sizeof(m_CurEndIndex);

	for(int32 i = 0; i < MAX_BANK_SIZE; ++i)
	{
		if(m_pItem[i].IsNullType()) continue;

		memcpy(buffer + nStart, &(m_pItem[i].m_ItemGUID), SItemGuid::GetSize());
		nStart += SItemGuid::GetSize();

		memcpy(buffer + nStart, &(m_pItem[i].m_ItemIndex), sizeof(uint32));
		nStart += sizeof(uint32);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uchar	byCount = m_pItem[i].GetItemCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		memcpy(buffer + nStart, &byCount, sizeof(uchar));
		nStart += sizeof(uchar);
	}

	return nStart;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Bag::Clear()
{
	memset(m_pItem, 0, MAX_BAG_SIZE * sizeof(SItem));

	m_Count = 0;
	m_BaseBagSize = MAX_BASE_BAG_SIZE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SArchiveLoader_Bag::FillCrcData(char *buffer)
{
	/*~~~~~~~~~~~~~~~*/
	int32	nStart = 0;
	/*~~~~~~~~~~~~~~~*/

	memcpy(buffer + nStart, &m_BaseBagSize, sizeof(m_BaseBagSize));
	nStart += sizeof(m_BaseBagSize);

	memcpy(buffer + nStart, &m_Count, sizeof(m_Count));
	nStart += sizeof(m_Count);

	for(int32 i = 0; i < MAX_BAG_SIZE; ++i)
	{
		if(m_pItem[i].IsNullType()) continue;

		memcpy(buffer + nStart, &(m_pItem[i].m_ItemGUID), SItemGuid::GetSize());
		nStart += SItemGuid::GetSize();

		memcpy(buffer + nStart, &(m_pItem[i].m_ItemIndex), sizeof(uint32));
		nStart += sizeof(uint32);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uchar	byCount = m_pItem[i].GetItemCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		memcpy(buffer + nStart, &byCount, sizeof(uchar));
		nStart += sizeof(uchar);
	}

	return nStart;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Equip::Clear()
{
	memset(m_pItem, 0, HEQUIP_NUMBER * sizeof(SItem));

	m_Flags = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SArchiveLoader_Equip::FillCrcData(char *buffer)
{
	/*~~~~~~~~~~~~~~~*/
	int32	nStart = 0;
	/*~~~~~~~~~~~~~~~*/

	memcpy(buffer + nStart, &m_Flags, sizeof(m_Flags));
	nStart += sizeof(m_Flags);

	for(int32 i = 0; i < HEQUIP_NUMBER; ++i)
	{
		if(m_pItem[i].IsNullType()) continue;

		memcpy(buffer + nStart, &(m_pItem[i].m_ItemGUID), SItemGuid::GetSize());
		nStart += SItemGuid::GetSize();

		memcpy(buffer + nStart, &(m_pItem[i].m_ItemIndex), sizeof(uint32));
		nStart += sizeof(uint32);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uchar	byCount = m_pItem[i].GetItemCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		memcpy(buffer + nStart, &byCount, sizeof(uchar));
		nStart += sizeof(uchar);
	}

	return nStart;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Skill::Clear()
{
	memset(m_aABility, 0, sizeof(_PLAYER_ABILITY) * MAX_CHAR_ABILITY_NUM);
	memset(m_aPrescr, 0, MAX_CHAR_PRESCRIPTION_BYTE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Spell::Clear()
{
	memset(m_aSkill, 0, sizeof(m_aSkill));

	m_Count = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SArchiveLoader_Spell::FillCrcData(char *buffer)
{
	/*~~~~~~~~~~~~~~~*/
	int32	nStart = 0;
	/*~~~~~~~~~~~~~~~*/

	return nStart;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Effect::Clear()
{
	memset(m_aImpacts, 0, sizeof(m_aImpacts));

	m_Count = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _IMPACT_LOAD::Clear()
{
	memset(m_aImpacts, 0, sizeof(m_aImpacts));
	memset(m_VisableType, 0, sizeof(m_VisableType));
	m_Count = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Quest::Clear()
{
	for(int32 i = 0; i < MAX_CHAR_QUEST_NUM; i++) m_aQuest[i].Clear();
	m_Count = 0;
	memset(m_aQuestHaveDoneFlags, 0, sizeof(uint32) * MAX_CHAR_QUEST_FLAG_LEN);
	memset(m_aQuestData, 0, sizeof(int32) * MAX_CHAR_QUEST_DATA_NUM);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SArchiveLoader_Relationship::Clear()
{
	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

}




