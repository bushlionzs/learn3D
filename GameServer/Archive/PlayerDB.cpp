/*$T MapServer/Server/DB/PlayerDB.cpp GC 1.140 10/10/07 10:07:21 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "PlayerDB.h"

#include "StructDB.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

PlayerArchive::PlayerArchive()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	
	{
		m_PlayerSHM = 0;
		m_AttrRegSM = 0;
	}

	m_AttrReg = new PLAYER_DB_ATTR_REG;
	m_AttrFlag = new PLAYER_DB_ATTR_FLAG;
	m_AttrFlag_ToWorld = new PLAYER_DB_ATTR_FLAG;
	m_dbPlayer = new SArchiveLoader_Player;
	m_dbEquip = new SArchiveLoader_Equip;
	m_dbBag = new SArchiveLoader_Bag;
	m_dbBank = new SArchiveLoader_Bank;
	m_dbSpell = new SArchiveLoader_Spell;
	m_dbCooldown = new SArchiveLoader_CoolDown;
	m_dbEffect = new SArchiveLoader_Effect;
	m_dbSkill = new SArchiveLoader_Skill;
	m_DBQuest = new SArchiveLoader_Quest;
	m_dbSetting = new SArchiveLoader_Setting;
	m_dbPetList = new _HORSE_DB_LIST_LOAD;
	m_dbBankPetList = new _BANKPET_DB_LIST_LOAD;
	m_dbRelation = new SArchiveLoader_Relationship;
	m_dbHonorRecord = new SArchiveLoader_Honor;
	m_dbPrivateInfo = new SArchiveLoader_PrivateInfo;
	m_dbMonsterPet = new SArchiveLoader_MonsterPet;
	m_dbSoldList = new SArchiveLoader_SoldList;
	m_dbPlayerExtendInfo = new SArchiveLoader_Player_ExtendInfo;
	_RegisterArchiveAttributes();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PlayerArchive::~PlayerArchive()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete(m_AttrRegSM);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KSafeDelete(m_AttrReg);
	KSafeDelete(m_AttrFlag);
	KSafeDelete(m_AttrFlag_ToWorld);
	KSafeDelete(m_dbPlayer);
	KSafeDelete(m_dbEquip);
	KSafeDelete(m_dbBag);
	KSafeDelete(m_dbBank);
	KSafeDelete(m_dbSpell);
	KSafeDelete(m_dbCooldown);
	KSafeDelete(m_dbEffect);
	KSafeDelete(m_dbSkill);
	KSafeDelete(m_DBQuest);
	KSafeDelete(m_dbSetting);
	KSafeDelete(m_dbPetList);
	KSafeDelete(m_dbBankPetList);
	KSafeDelete(m_dbRelation);
	KSafeDelete(m_dbHonorRecord);
	KSafeDelete(m_dbPrivateInfo);
	KSafeDelete(m_dbMonsterPet);
	KSafeDelete(m_dbSoldList);
	KSafeDelete(m_dbPlayerExtendInfo);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::RefreshArchiveToDBShare(BOOL bForceAll, BOOL &bUpdateAttr)
{
	/*~~~~~~~~~~*/
	int32	iAttr;
	/*~~~~~~~~~~*/

	__GUARD__ if(m_PlayerSHM)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	bNeedUpdate = FALSE;
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(iAttr = CPROPERTY_ARCHIVE_HP; iAttr < CPROPERTY_ARCHIVE_NUMBER; iAttr++)
		{
			if(GetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) iAttr) || bForceAll)
			{
				bNeedUpdate = TRUE;
			}
		}

		if(bNeedUpdate)
		{
			Lock();
			for(iAttr = CPROPERTY_ARCHIVE_HP; iAttr < CPROPERTY_ARCHIVE_NUMBER; iAttr++)
			{
				if(GetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) iAttr) || bForceAll)
				{
					void* pSMAttr = GetSMEnumProperty((PLAYER_PROPERTY_ARCHIVE) iAttr);
					void* pDBAttr = GetArchiveEnumProperty((PLAYER_PROPERTY_ARCHIVE) iAttr);
					int32 smSize = GetSMEnumPropertySize((PLAYER_PROPERTY_ARCHIVE) iAttr);
					int32 dbSize = GetArchiveEnumPropertySize((PLAYER_PROPERTY_ARCHIVE) iAttr);

					if( pSMAttr!=NULL && pDBAttr!=NULL )
					{
						if( (smSize!=dbSize) || (smSize<0) || (smSize>65536) )
						{
							QLogSystem::SLOW_LOG
								( 
									SLOW_LOG_SERVERERROR, 
									"PlayerDB::ValidateShareMem Error! guid=%X, index=%d, pSMAttr=%p, pDBAttr=%p, smSize=%d, dbSize=%d",
									GetGUID(),
									iAttr,
									pSMAttr,
									pDBAttr,
									smSize,
									dbSize
								);
							continue;
						}

						memcpy( pSMAttr, pDBAttr, smSize );
					}

					SetArchiveEnumPropertyDirty((PLAYER_PROPERTY_ARCHIVE) iAttr, FALSE);
				}
			}

			UnLock();
		}

		bUpdateAttr = FALSE;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerArchive::IsNoDirectAttr(PLAYER_PROPERTY_ARCHIVE attrType)
{
	__GUARD__ switch(attrType)
	{
	case CPROPERTY_ARCHIVE_COOLDOWN:
	case CPROPERTY_ARCHIVE_IMPACT:
	case CPROPERTY_ARCHIVE_RELATION:
	case CPROPERTY_ARCHIVE_PRIVATEINFO:
		return TRUE;
		break;

	default:
		return FALSE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::ValidatePlayerID(ConnectorID_t PID)
{
	if(m_PlayerSHM)
	{
		m_PlayerSHM->SetPlayerID(SM_S_WRITE, PID);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::RandSet()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRand = 10000 + rand();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_dbPlayer->m_HP = iRand;
	sprintf(m_dbPlayer->m_Name, "²âÊÔ%d", iRand);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::_RegisterArchiveAttributes()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define REG_ARCHIVE_ATTR(type, var)			_RegArchiveAttr(type, &(var), sizeof(var));
#define REG_ARCHIVE_ATTR_SIZE(type, varPtr, size)	_RegArchiveAttr(type, varPtr, size);
	__GUARD__	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_HP, m_dbPlayer->m_HP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_MP, m_dbPlayer->m_MP);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_STRIKEPOINT, m_dbPlayer->m_StrikePoint);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_VIGOR, m_dbPlayer->m_Vigor);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_MAX_VIGOR, m_dbPlayer->m_MaxVigor);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_VIGOR_REGENE_RATE, m_dbPlayer->m_VigorRegeneRate);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_ENERGY, m_dbPlayer->m_Energy);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_MAX_ENERGY, m_dbPlayer->m_MaxEnergy);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_ENERGY_REGENE_RATE, m_dbPlayer->m_EnergyRegeneRate);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_RAGE, m_dbPlayer->m_Rage);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LEVEL, m_dbPlayer->m_Level);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PKVALUE, m_dbPlayer->m_nPKValue);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_CURRENTPET, m_dbPlayer->m_guidCurrentPet);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_EXP, m_dbPlayer->m_Exp);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_AT_POSITION, m_dbPlayer->m_Position);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BK_POSITION, m_dbPlayer->m_BakPosition);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_NEXT_POSITION, m_dbPlayer->m_NextPosition);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_AT_SCENE, m_dbPlayer->m_StartScene);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BK_SCENE, m_dbPlayer->m_BakScene);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_NEXT_SCENE, m_dbPlayer->m_NextScene);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_STR, m_dbPlayer->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR]);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_CON, m_dbPlayer->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON]);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_INT, m_dbPlayer->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT]);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_DEX, m_dbPlayer->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX]);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_REMAINPOINT, m_dbPlayer->m_Level1Points);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_REMAINSKILLPOINT, m_dbPlayer->m_RemainSkillPoints);
	REG_ARCHIVE_ATTR_SIZE(CPROPERTY_ARCHIVE_S_SKILLPOINT, m_dbPlayer->m_S_SkillPoints, sizeof(int32) * COMMON_S_NUMBER);

	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_CAMP, m_dbPlayer->m_CampData);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PROFESSION, m_dbPlayer->m_nProfession);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_COUNTRY, m_dbPlayer->m_nCountry);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GUILDID, m_dbPlayer->m_GuildID);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_FAMILYID, m_dbPlayer->m_FamilyID);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GUILDOFFICIAL, m_dbPlayer->m_nGuildOfficial);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_TEAMID, m_dbPlayer->m_TeamID);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GUID, m_dbPlayer->m_GUID);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PORTRAITID, m_dbPlayer->m_PortraitID);
	REG_ARCHIVE_ATTR_SIZE(CPROPERTY_ARCHIVE_NAME, m_dbPlayer->m_Name, sizeof(char) * MAX_CHARACTER_NAME);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SEX, m_dbPlayer->m_Sex);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_CREATETIME, m_dbPlayer->m_CreateDate);
	REG_ARCHIVE_ATTR_SIZE(CPROPERTY_ARCHIVE_TITLE, m_dbPlayer->m_Title, sizeof(char) * MAX_CHARACTER_TITLE);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PWD_TYPE, m_dbPlayer->m_uPwdFlag);
	REG_ARCHIVE_ATTR_SIZE(CPROPERTY_ARCHIVE_PASSWORD, m_dbPlayer->m_Passwd, sizeof(char) * MAX_PWD);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PWDDELTIME, m_dbPlayer->m_uPwdDelTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LASTPROTECTIME, m_dbPlayer->m_cLastProtectTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PROTECTIME, m_dbPlayer->m_cProtectTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PROTECDELTIME, m_dbPlayer->m_uProtectDelTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_HAIR_COLOR, m_dbPlayer->m_HairColor);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_FACE_COLOR, m_dbPlayer->m_FaceColor);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_HAIR_MODEL, m_dbPlayer->m_HairModel);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_FACE_MODEL, m_dbPlayer->m_FaceModel);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_ONLINETIME, m_dbPlayer->m_OnlineTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LASTLOGINTIME, m_dbPlayer->m_LastLoginTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LASTLOGOUTTIME, m_dbPlayer->m_LastLogoutTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_DBVERSION, m_dbPlayer->m_DBVersion);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SILLER, m_dbPlayer->m_Siller);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GOLD, m_dbPlayer->m_Gold);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BINDSILLER, m_dbPlayer->m_BindSiller);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BINDGOLD, m_dbPlayer->m_BindGold);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_MONEYMODE, m_dbPlayer->m_MoneyMode);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_WENCAI, m_dbPlayer->m_nWenCai);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_RONGYU, m_dbPlayer->m_nRongYu);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_HONOR, m_dbPlayer->m_nHonor);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_INHERENCE_EXP, m_dbPlayer->m_nInherenceExp);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_INHERENCE_LEVEL, m_dbPlayer->m_nInherenceLevel);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SHENGWANG, m_dbPlayer->m_nShengWang);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_HOTVALUE, m_dbPlayer->m_nHotValue);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SOULID, m_dbPlayer->m_SoulID);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GEMATT, m_dbPlayer->m_GemAff);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SETSUIT, m_dbPlayer->m_SetSuit);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LEVELATT, m_dbPlayer->m_LevelAff);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BANK_MONEY, m_dbBank->m_Money);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BANK_OFFSIZE, m_dbBank->m_CurEndIndex);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LEAVEGUILDTIME, m_dbPlayer->m_LeaveGuildTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_FIRSTLOGIN, m_dbPlayer->m_bFirstEnterScence);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BUS_ID, m_dbPlayer->m_BusID);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LAST_FORBIDCHAT_TIME, m_dbPlayer->m_LastForbidChatTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LAST_ENJAIL_TIME, m_dbPlayer->m_LastEnjailTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_COUNTRY_OFFICIAL, m_dbPlayer->m_nCountryOfficial);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GOODBAD, m_dbPlayer->m_nGoodBadValue);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GUILDPOINT, m_dbPlayer->m_nGP);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_MOUNTMODELID, m_dbPlayer->m_MountModelID);

	/*~~~~~~~~~~~~~~~~~~*/
	int	iBagIndex = 0;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int iDBBag = CPROPERTY_ARCHIVE_BAG_BEGIN; iDBBag <= CPROPERTY_ARCHIVE_BAG_END; iDBBag++)
	{
		REG_ARCHIVE_ATTR((PLAYER_PROPERTY_ARCHIVE) iDBBag, m_dbBag->m_pItem[iBagIndex]);
		iBagIndex++;
	}

	/*~~~~~~~~~~~~~~~~~~~~*/
	int	iEquipIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	for(int iDBEquip = CPROPERTY_ARCHIVE_EQUIP_BEGIN; iDBEquip <= CPROPERTY_ARCHIVE_EQUIP_END; iDBEquip++)
	{
		REG_ARCHIVE_ATTR((PLAYER_PROPERTY_ARCHIVE) iDBEquip, m_dbEquip->m_pItem[iEquipIndex]);
		iEquipIndex++;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	int	iBankIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~*/

	for(int iDBBank = CPROPERTY_ARCHIVE_BANK_BEGIN; iDBBank <= CPROPERTY_ARCHIVE_BANK_END; iDBBank++)
	{
		REG_ARCHIVE_ATTR((PLAYER_PROPERTY_ARCHIVE) iDBBank, m_dbBank->m_pItem[iBankIndex]);
		iBankIndex++;
	}

	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SKILL, *m_dbSpell);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_COOLDOWN, *m_dbCooldown);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_IMPACT, *m_dbEffect);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_ABILITY, *m_dbSkill);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_QUEST, *m_DBQuest);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SETTING, *m_dbSetting);

	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PET, *m_dbPetList);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BANKPET, *m_dbBankPetList);

	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_RELATION, *m_dbRelation);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PRIVATEINFO, *m_dbPrivateInfo);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_TITLEINFO, m_dbPlayer->m_Titles);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SOLDLIST, *m_dbSoldList);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GUILDBUILD_COUNT, m_dbPlayer->m_cGuildBuild_Count);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_GUILDBUILD_DAY, m_dbPlayer->m_nGuildBuild_Day);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_LAST_CHGPKMODE_TIME, m_dbPlayer->m_nLastChgPKModeTime);
	REG_ARCHIVE_ATTR_SIZE(CPROPERTY_ARCHIVE_RESERVE, m_dbPlayer->m_Reserve, sizeof(int32) * MAX_RESERVE);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_IS_DEL_CHAR, m_dbPlayer->m_IsDelChar);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_WALLOWONLINETIME, m_dbPlayer->m_nWallowOnlineTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_WALLOWOFFLINETIME, m_dbPlayer->m_nWallowOfflineTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_TOTALONLINETIME, m_dbPlayer->m_nTotalOnlineTime);
	REG_ARCHIVE_ATTR_SIZE(CPROPERTY_ARCHIVE_NEW_NAME, m_dbPlayer->m_szNewName, sizeof(char) * MAX_CHARACTER_NAME);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_HONOR_RECORD, *m_dbHonorRecord);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_KILL_COUNT_TODAY, m_dbPlayer->m_nKillCountToday);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_TIRED_TIME, m_dbPlayer->m_TiredTime);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PVP2V2_LEVEL, m_dbPlayer->m_nPVP2V2_Level);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PVP2V2_MARK, m_dbPlayer->m_nPVP2V2_Mark);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PVP2V2_DAY, m_dbPlayer->m_nPVP2V2_Day);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_PVP2V2_MARK_WEEKTOTAL, m_dbPlayer->m_nPVP2V2_Mark_WeekTotal);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_DUEL_MARK, m_dbPlayer->m_nDuelMark);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_DBFLAG, m_dbPlayer->m_uDBFlag);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_EXPLOIT, m_dbPlayer->m_nExploit);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_EXPLOITDAY, m_dbPlayer->m_nExploitDay);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_WORLDID, m_dbPlayer->m_nPlayerWorldID);

	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SHOPITEMFAVORITE, m_dbPlayerExtendInfo->m_ShopItemFavorite);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_SHOPITEMBUYHISTORY,m_dbPlayerExtendInfo->m_ShopItemBuyHistory);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_INHERENCEBALANCE,m_dbPlayerExtendInfo->m_InherenceBalance);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_INHERENCEZHUANJING,m_dbPlayerExtendInfo->m_InherenceZhanJing);
	REG_ARCHIVE_ATTR(CPROPERTY_ARCHIVE_BATTLEHONOUR, m_dbPlayerExtendInfo->m_nBattleHonour);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::_RegisterSHMAttributes()
{
	/*~~~~~~~~~~~~~~~~~~~*/
#define REG_SHM_ATTR(type, var)			_RegSHMAttr(type, &(var), sizeof(var));
#define REG_SHM_ATTR_SIZE(type, varPtr, size)	_RegSHMAttr(type, varPtr, size);
	__GUARD__	Lock();
	/*~~~~~~~~~~~~~~~~~~~*/

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_HP, m_PlayerSHM->m_PlayerSM.m_HP);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_MP, m_PlayerSHM->m_PlayerSM.m_MP);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_STRIKEPOINT, m_PlayerSHM->m_PlayerSM.m_StrikePoint);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_VIGOR, m_PlayerSHM->m_PlayerSM.m_Vigor);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_MAX_VIGOR, m_PlayerSHM->m_PlayerSM.m_MaxVigor);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_VIGOR_REGENE_RATE, m_PlayerSHM->m_PlayerSM.m_VigorRegeneRate);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_ENERGY, m_PlayerSHM->m_PlayerSM.m_Energy);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_MAX_ENERGY, m_PlayerSHM->m_PlayerSM.m_MaxEnergy);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_ENERGY_REGENE_RATE, m_PlayerSHM->m_PlayerSM.m_EnergyRegeneRate);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_RAGE, m_PlayerSHM->m_PlayerSM.m_Rage);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LEVEL, m_PlayerSHM->m_PlayerSM.m_Level);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PKVALUE, m_PlayerSHM->m_PlayerSM.m_nPKValue);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_CURRENTPET, m_PlayerSHM->m_PlayerSM.m_guidCurrentPet);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_EXP, m_PlayerSHM->m_PlayerSM.m_Exp);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_AT_POSITION, m_PlayerSHM->m_PlayerSM.m_Position);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BK_POSITION, m_PlayerSHM->m_PlayerSM.m_BakPosition);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_NEXT_POSITION, m_PlayerSHM->m_PlayerSM.m_NextPosition);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_AT_SCENE, m_PlayerSHM->m_PlayerSM.m_StartScene);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BK_SCENE, m_PlayerSHM->m_PlayerSM.m_BakScene);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_NEXT_SCENE, m_PlayerSHM->m_PlayerSM.m_NextScene);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_STR, m_PlayerSHM->m_PlayerSM.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR]);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_CON, m_PlayerSHM->m_PlayerSM.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON]);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_INT, m_PlayerSHM->m_PlayerSM.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT]);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_DEX, m_PlayerSHM->m_PlayerSM.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX]);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_REMAINPOINT, m_PlayerSHM->m_PlayerSM.m_Level1Points);
	REG_SHM_ATTR_SIZE(CPROPERTY_ARCHIVE_S_SKILLPOINT, m_PlayerSHM->m_PlayerSM.m_S_SkillPoints, sizeof(int32) * COMMON_S_NUMBER);

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_REMAINSKILLPOINT, m_PlayerSHM->m_PlayerSM.m_RemainSkillPoints);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_CAMP, m_PlayerSHM->m_PlayerSM.m_CampData);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PROFESSION, m_PlayerSHM->m_PlayerSM.m_nProfession);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_COUNTRY, m_PlayerSHM->m_PlayerSM.m_nCountry);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GUILDID, m_PlayerSHM->m_PlayerSM.m_GuildID);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_FAMILYID, m_PlayerSHM->m_PlayerSM.m_FamilyID);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GUILDOFFICIAL, m_PlayerSHM->m_PlayerSM.m_nGuildOfficial);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_TEAMID, m_PlayerSHM->m_PlayerSM.m_TeamID);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GUID, m_PlayerSHM->m_PlayerSM.m_GUID);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PORTRAITID, m_PlayerSHM->m_PlayerSM.m_PortraitID);
	REG_SHM_ATTR_SIZE(CPROPERTY_ARCHIVE_NAME, m_PlayerSHM->m_PlayerSM.m_Name, sizeof(char) * MAX_CHARACTER_NAME);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SEX, m_PlayerSHM->m_PlayerSM.m_Sex);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_CREATETIME, m_PlayerSHM->m_PlayerSM.m_CreateDate);
	REG_SHM_ATTR_SIZE(CPROPERTY_ARCHIVE_TITLE, m_PlayerSHM->m_PlayerSM.m_Title, sizeof(char) * MAX_CHARACTER_TITLE);
	REG_SHM_ATTR_SIZE(CPROPERTY_ARCHIVE_PASSWORD, m_PlayerSHM->m_PlayerSM.m_Passwd, sizeof(char) * MAX_PWD);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PWD_TYPE, m_PlayerSHM->m_PlayerSM.m_uPwdFlag);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PWDDELTIME, m_PlayerSHM->m_PlayerSM.m_uPwdDelTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LASTPROTECTIME, m_PlayerSHM->m_PlayerSM.m_cLastProtectTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PROTECTIME, m_PlayerSHM->m_PlayerSM.m_cProtectTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PROTECDELTIME, m_PlayerSHM->m_PlayerSM.m_uProtectDelTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_HAIR_COLOR, m_PlayerSHM->m_PlayerSM.m_HairColor);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_FACE_COLOR, m_PlayerSHM->m_PlayerSM.m_FaceColor);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_HAIR_MODEL, m_PlayerSHM->m_PlayerSM.m_HairModel);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_FACE_MODEL, m_PlayerSHM->m_PlayerSM.m_FaceModel);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_ONLINETIME, m_PlayerSHM->m_PlayerSM.m_OnlineTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LASTLOGINTIME, m_PlayerSHM->m_PlayerSM.m_LastLoginTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LASTLOGOUTTIME, m_PlayerSHM->m_PlayerSM.m_LastLogoutTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_DBVERSION, m_PlayerSHM->m_PlayerSM.m_DBVersion);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SILLER, m_PlayerSHM->m_PlayerSM.m_Siller);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GOLD, m_PlayerSHM->m_PlayerSM.m_Gold);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BINDSILLER, m_PlayerSHM->m_PlayerSM.m_BindSiller);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BINDGOLD, m_PlayerSHM->m_PlayerSM.m_BindGold);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_MONEYMODE, m_PlayerSHM->m_PlayerSM.m_MoneyMode);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_WENCAI, m_PlayerSHM->m_PlayerSM.m_nWenCai);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_RONGYU, m_PlayerSHM->m_PlayerSM.m_nRongYu);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_HONOR, m_PlayerSHM->m_PlayerSM.m_nHonor);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_INHERENCE_EXP, m_PlayerSHM->m_PlayerSM.m_nInherenceExp);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_INHERENCE_LEVEL, m_PlayerSHM->m_PlayerSM.m_nInherenceLevel);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SHENGWANG, m_PlayerSHM->m_PlayerSM.m_nShengWang);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_HOTVALUE, m_PlayerSHM->m_PlayerSM.m_nHotValue);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SOULID, m_PlayerSHM->m_PlayerSM.m_SoulID);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GEMATT, m_PlayerSHM->m_PlayerSM.m_GemAff);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SETSUIT, m_PlayerSHM->m_PlayerSM.m_SetSuit);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LEVELATT, m_PlayerSHM->m_PlayerSM.m_LevelAff);

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BANK_MONEY, m_PlayerSHM->m_BankSM.m_Money);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BANK_OFFSIZE, m_PlayerSHM->m_BankSM.m_CurEndIndex);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LEAVEGUILDTIME, m_PlayerSHM->m_PlayerSM.m_LeaveGuildTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_FIRSTLOGIN, m_PlayerSHM->m_PlayerSM.m_bFirstEnterScence);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BUS_ID, m_PlayerSHM->m_PlayerSM.m_BusID);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LAST_FORBIDCHAT_TIME, m_PlayerSHM->m_PlayerSM.m_LastForbidChatTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LAST_ENJAIL_TIME, m_PlayerSHM->m_PlayerSM.m_LastEnjailTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_COUNTRY_OFFICIAL, m_PlayerSHM->m_PlayerSM.m_nCountryOfficial);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GOODBAD, m_PlayerSHM->m_PlayerSM.m_nGoodBadValue);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GUILDPOINT, m_PlayerSHM->m_PlayerSM.m_nGP);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_MOUNTMODELID, m_PlayerSHM->m_PlayerSM.m_MountModelID);

	/*~~~~~~~~~~~~~~~~~~*/
	int	iBagIndex = 0;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int iDBBag = CPROPERTY_ARCHIVE_BAG_BEGIN; iDBBag <= CPROPERTY_ARCHIVE_BAG_END; iDBBag++)
	{
		REG_SHM_ATTR((PLAYER_PROPERTY_ARCHIVE) iDBBag, m_PlayerSHM->m_BagSM.m_pItem[iBagIndex]);
		iBagIndex++;
	}

	/*~~~~~~~~~~~~~~~~~~~~*/
	int	iEquipIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	for(int iDBEquip = CPROPERTY_ARCHIVE_EQUIP_BEGIN; iDBEquip <= CPROPERTY_ARCHIVE_EQUIP_END; iDBEquip++)
	{
		REG_SHM_ATTR((PLAYER_PROPERTY_ARCHIVE) iDBEquip, m_PlayerSHM->m_EquipSM.m_pItem[iEquipIndex]);
		iEquipIndex++;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	int	iBankIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~*/

	for(int iDBBank = CPROPERTY_ARCHIVE_BANK_BEGIN; iDBBank <= CPROPERTY_ARCHIVE_BANK_END; iDBBank++)
	{
		REG_SHM_ATTR((PLAYER_PROPERTY_ARCHIVE) iDBBank, m_PlayerSHM->m_BankSM.m_pItem[iBankIndex]);
		iBankIndex++;
	}

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SKILL, m_PlayerSHM->m_SkillSM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_COOLDOWN, m_PlayerSHM->m_CoolDownDBShareMemory);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_IMPACT, m_PlayerSHM->m_ImpactSM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_ABILITY, m_PlayerSHM->m_AbilitySM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_QUEST, m_PlayerSHM->m_QuestDBShareMemory);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SETTING, m_PlayerSHM->m_SettingSM);

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PET, m_PlayerSHM->m_PetListSM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BANKPET, m_PlayerSHM->m_BankPetListSM);

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_RELATION, m_PlayerSHM->m_RelationSM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PRIVATEINFO, m_PlayerSHM->m_PrivateInfoSM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_TITLEINFO, m_PlayerSHM->m_PlayerSM.m_Titles);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SOLDLIST, m_PlayerSHM->m_SoldList);

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GUILDBUILD_COUNT, m_PlayerSHM->m_PlayerSM.m_cGuildBuild_Count);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_GUILDBUILD_DAY, m_PlayerSHM->m_PlayerSM.m_nGuildBuild_Day);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_LAST_CHGPKMODE_TIME, m_PlayerSHM->m_PlayerSM.m_nLastChgPKModeTime);

	REG_SHM_ATTR_SIZE(CPROPERTY_ARCHIVE_RESERVE, m_PlayerSHM->m_PlayerSM.m_Reserve, sizeof(int32) * MAX_RESERVE);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_IS_DEL_CHAR, m_PlayerSHM->m_PlayerSM.m_IsDelChar);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_WALLOWONLINETIME, m_PlayerSHM->m_PlayerSM.m_nWallowOnlineTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_WALLOWOFFLINETIME, m_PlayerSHM->m_PlayerSM.m_nWallowOfflineTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_TOTALONLINETIME, m_PlayerSHM->m_PlayerSM.m_nTotalOnlineTime);
	REG_SHM_ATTR_SIZE(CPROPERTY_ARCHIVE_NEW_NAME, m_PlayerSHM->m_PlayerSM.m_szNewName, sizeof(char) * MAX_CHARACTER_NAME);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_HONOR_RECORD, m_PlayerSHM->m_HonorRecordSM);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_KILL_COUNT_TODAY, m_PlayerSHM->m_PlayerSM.m_nKillCountToday);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_TIRED_TIME, m_PlayerSHM->m_PlayerSM.m_TiredTime);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PVP2V2_LEVEL, m_PlayerSHM->m_PlayerSM.m_nPVP2V2_Level);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PVP2V2_MARK, m_PlayerSHM->m_PlayerSM.m_nPVP2V2_Mark);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PVP2V2_DAY, m_PlayerSHM->m_PlayerSM.m_nPVP2V2_Day);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_PVP2V2_MARK_WEEKTOTAL, m_PlayerSHM->m_PlayerSM.m_nPVP2V2_Mark_WeekTotal);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_DUEL_MARK, m_PlayerSHM->m_PlayerSM.m_nDuelMark);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_DBFLAG, m_PlayerSHM->m_PlayerSM.m_uDBFlag);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_EXPLOIT, m_PlayerSHM->m_PlayerSM.m_nExploit);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_EXPLOITDAY, m_PlayerSHM->m_PlayerSM.m_nExploitDay);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_WORLDID, m_PlayerSHM->m_PlayerSM.m_nPlayerWorldID);

	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SHOPITEMFAVORITE,m_PlayerSHM->m_PlayerExtendInfoSM.m_ShopItemFavorite);	
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_SHOPITEMBUYHISTORY,m_PlayerSHM->m_PlayerExtendInfoSM.m_ShopItemBuyHistory);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_INHERENCEBALANCE,m_PlayerSHM->m_PlayerExtendInfoSM.m_InherenceBalance);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_INHERENCEZHUANJING,m_PlayerSHM->m_PlayerExtendInfoSM.m_InherenceZhanJing);
	REG_SHM_ATTR(CPROPERTY_ARCHIVE_BATTLEHONOUR, m_PlayerSHM->m_PlayerExtendInfoSM.m_nBattleHonour);

	UnLock();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void *PlayerArchive::GetArchiveEnumProperty(PLAYER_PROPERTY_ARCHIVE eOffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrReg);

	return m_AttrReg->m_AttrPtr[eOffSet];

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void *PlayerArchive::GetSMEnumProperty(PLAYER_PROPERTY_ARCHIVE eOffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrRegSM);

	return m_AttrRegSM->m_AttrPtr[eOffSet];

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 PlayerArchive::GetArchiveEnumPropertySize(PLAYER_PROPERTY_ARCHIVE eOffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrFlag);

	return m_AttrReg->m_AttrSize[eOffSet];

	__UNGUARD__ return 0;
}

int32 PlayerArchive::GetSMEnumPropertySize(PLAYER_PROPERTY_ARCHIVE eOffSet)
{
	__GUARD__	
		
	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	KCheck(eOffSet >= 0);
	KCheck(m_AttrFlag);

	return m_AttrRegSM->m_AttrSize[eOffSet];

	__UNGUARD__ return 0;	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::SetArchiveEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrFlag);

	m_AttrFlag->SetBitFlag(eOffSet, bFlag);

	if(TRUE == bFlag)
	{
		SetToGLEnumPropertyDirty(eOffSet, bFlag);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerArchive::GetArchiveEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrFlag);

	return m_AttrFlag->IsUpdated(eOffSet);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::SetToGLEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet, BOOL bFlag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrFlag_ToWorld);

	m_AttrFlag_ToWorld->SetBitFlag(eOffSet, bFlag);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerArchive::GetToGLEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(eOffSet < CPROPERTY_ARCHIVE_NUMBER);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(eOffSet >= 0);
	KCheck(m_AttrFlag_ToWorld);

	return m_AttrFlag_ToWorld->IsUpdated(eOffSet);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerArchive::SetFreeOwnFlag(int32 Flag)
{
	__GUARD__ if(m_PlayerSHM)
	{
		m_PlayerSHM->SetUseStatus(Flag, SM_S_WRITE);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 PlayerArchive::GetFreeOwnFlag()
{
	__GUARD__ if(m_PlayerSHM)
	{
		return m_PlayerSHM->GetUseStatus(SM_S_WRITE);
	}

	return -1;

	__UNGUARD__ return -1;
}

BOOL PlayerArchive::AddShopItemFavorite(const SPlayerShopElement& element)
{
	if (m_dbPlayerExtendInfo->m_ShopItemFavorite.AddElement(element) == TRUE)
	{
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHOPITEMFAVORITE);

		return TRUE;
	}

	return FALSE;
}

BOOL  PlayerArchive::DelShopItemFavorite(const SPlayerShopElement& element)
{
	if (m_dbPlayerExtendInfo->m_ShopItemFavorite.DelElement(element) == TRUE)
	{
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHOPITEMFAVORITE);

		return TRUE;
	}

	return FALSE;
}

BOOL PlayerArchive::UpdateShopItemFavorite(const SPlayerShopElement& element)
{
	if (m_dbPlayerExtendInfo->m_ShopItemFavorite.UpdateElement(element) == TRUE)
	{
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHOPITEMFAVORITE);

		return TRUE;
	}

	return FALSE;
}

BOOL PlayerArchive::AddShopItemBuyHistory(const SPlayerShopElement& element)
{
	if (m_dbPlayerExtendInfo->m_ShopItemBuyHistory.AddElement(element) == TRUE)
	{
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHOPITEMBUYHISTORY);
		return TRUE;
	}

	return FALSE;
}

BOOL PlayerArchive::DelShopItemBuyHistory(const SPlayerShopElement& element)
{
	if (m_dbPlayerExtendInfo->m_ShopItemBuyHistory.DelElement(element) == TRUE)
	{
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHOPITEMBUYHISTORY);
		return TRUE;
	}

	return FALSE;
}

BOOL PlayerArchive::UpdateShopItemBuyHistory(const SPlayerShopElement& element)
{
	if (m_dbPlayerExtendInfo->m_ShopItemBuyHistory.UpdateElement(element) == TRUE)
	{
		SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_SHOPITEMBUYHISTORY);
		return TRUE;
	}

	return FALSE;
}

int32 PlayerArchive::GetInherenceBalanceLevel(PLAYER_PROPERTY_LEVEL4_BALANCE iBalanceIndex)
{
	KCheck(iBalanceIndex >= 0 && iBalanceIndex < CPROPERTY_LEVEL4_BALANCE_NUMBER);
	return m_dbPlayerExtendInfo->m_InherenceBalance.Get(iBalanceIndex);
}

void PlayerArchive::SetInherenceBalanceLevel(PLAYER_PROPERTY_LEVEL4_BALANCE iBalanceIndex, int32 iValue)
{
	KCheck(iBalanceIndex >= 0 && iBalanceIndex < CPROPERTY_LEVEL4_BALANCE_NUMBER);
	m_dbPlayerExtendInfo->m_InherenceBalance.Set(iBalanceIndex, iValue);
	SetArchiveEnumPropertyDirty(CPROPERTY_ARCHIVE_INHERENCEBALANCE);
}

SPlayerInherenceBalance* PlayerArchive::GetInherenceBalance()
{
	return &m_dbPlayerExtendInfo->m_InherenceBalance;
}
