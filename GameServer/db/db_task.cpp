#include "stdafx.h"
#include "db_task.h"
#include "mysql_db.h"
#include "db_manager.h"
#include "net/messages/DSCharData.h"
#include "net/net_message_manager.h"

DBTask::DBTask()
{

}

DBTask::~DBTask()
{

}


CharListTask::CharListTask(std::string& account)
{
    mAccount = account;
}

CharListTask::~CharListTask()
{

}

std::string CharListTask::get_sql()
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select charguid, sex, charname, level, haircolor, facecolor, hairmodel, facemodel, scene, \
        profession, headid, country, firstlogin, settings, soulid, gemaff, setsuit, levelaff, isneedrename, \
        func_get_mountmodelid(charguid, hpetguid, lpetguid) from t_char where accname = '%s' and isvalid = 1", mAccount.c_str());
    return sql;
}

void CharListTask::failed(int32_t errcode)
{

}

void CharListTask::success(CMySQLRecordSet* recordset)
{
    int32_t size = recordset->GetRecordCount();
}

CharDataTask::CharDataTask(std::string& guid)
{
    mGuid = guid;
}

CharDataTask::~CharDataTask()
{

}

std::string CharDataTask::get_sql()
{
    char sql[2048];
    snprintf(sql, sizeof(sql), "select firstlogin, charguid, charname, title, sex, createtime, level, enegry, exp, \
        pw, haircolor, facecolor, hairmodel, facemodel, scene, xpos, zpos, logintime, logouttime, lastloginip, dbversion, \
        camp, profession, country, hp, mp, strikepoint, str, con, ipr, dex, points, settings, guldid, teamid, headid, erecover, \
        vigor, maxvigor, vrecover, energymax, pwdeltime, dietime, bankcount, bankend, bkscene, bkxpos, bkzpos, nextscene, nextxpos, \
        nextzpos, rage, silver, gold, bsilver, bgold, moneymode, rongyu, shengwang, wencai, pwflag, lastpttime, pttime, ptdeltime,  \
        busid, pkvalue, lastmutetime, lastenjailtime, honor, honordata, guildbuildcount, guildbuildday, chgpkmodetime, inherexp, \
        inherlevel, soulid, gemaff, guildpoint, soldlist, setsuit, levelaff, hotvalue, isdelchar, totalonlinetime, wallowonlinetime, \
        wallowofflinetime, leaveguildtime, crc, killcounttoday, tiredtime, goodbad, pvp2v2level, pvp2v2mark, pvp2v2day, bankpetvalidct, \
        pvp2v2markweektotal, dbflag, exploit, exploitday, hpetguid, lpetguid from t_char where charguid = %s and isvalid = 1", mGuid.c_str());
    return sql;
}

void CharDataTask::failed(int32_t errcode)
{
	assert(false);
}


int32_t db_get_property_int(CMySQLRecordSet* recordset, int index)
{
	return atoi(recordset->GetFieldValue(index));
}

uint32_t db_get_property_uint(CMySQLRecordSet* recordset, int index)
{
	const char* data = recordset->GetFieldValue(index);
	return StrToUINT64(data);
}

uint64_t db_get_property_uint64(CMySQLRecordSet* recordset, int index)
{
	return StrToUINT64(recordset->GetFieldValue(index));
}

const char* db_get_property_string(CMySQLRecordSet* recordset, int index)
{
	return recordset->GetFieldValue(index);
}

void copy_text(char* dst, uint32_t size, CMySQLRecordSet* recordset, int index)
{
	strncpy(dst, recordset->GetFieldValue(index), size);
}

void CharDataTask::success(CMySQLRecordSet* recordset)
{

	if (recordset->GetRecordCount() != 1)
	{
		failed(-1);
		return;
	}
    CHARDBNODE* pCharDBNode = new CHARDBNODE;
    pCharDBNode->Clear();

	enum
	{
		DB_FirstLogin = 0,
		DB_CharGuid,
		DB_CharName,
		DB_Title,
		DB_Sex,
		DB_CreateTime,
		DB_Level,
		DB_Enegry,
		DB_Exp,
		DB_Pw,
		DB_HairColor,
		DB_FaceColor,
		DB_HairModel,
		DB_FaceModel,
		DB_Scene,
		DB_XPos,
		DB_ZPos,
		DB_LoginTime,
		DB_LogoutTime,
		DB_LastLoginIP,
		DB_Version,
		DB_Camp,
		DB_Profession,
		DB_Country,
		DB_HP,
		DB_MP,
		DB_StrikePoint,
		DB_Str,
		DB_Con,
		DB_Ipr,
		DB_Dex,
		DB_Points,
		DB_Setting,
		DB_GuildID,
		DB_TeamID,
		DB_HeadID,
		DB_eRecover,
		DB_Vigor,
		DB_MaxVigor,
		DB_VRecover,
		DB_EnergyMax,
		DB_PwdelTime,
		DB_DieTime,
		DB_BankCount,
		DB_BankEnd,
		DB_BackScene,
		DB_BackXPos,
		DB_BackZPos,
		DB_NextScene,
		DB_NextXPos,
		DB_NextZPos,
		DB_Rage,
		DB_Silver,
		DB_Gold,
		DB_BindSilver,
		DB_BindGold,
		DB_MoneyMode,
		DB_Rongyu,
		DB_Shengwang,
		DB_Wencai,
		DB_PwdFlag,
		DB_LastProtectTime,
		DB_ProtectTime,
		DB_ProtectDelTime,
		DB_BusID,
		DB_PkValue,
		DB_LastMuteTime,
		DB_LastEnjailTime,
		DB_Honor,
		DB_HonorData,
		DB_GuildBuildCount,
		DB_GuildBuildDay,
		DB_ChgPKModeTime,
		DB_InherExp,
		DB_InherLevel,
		DB_SoulID,
		DB_GemAff,
		DB_GuildPoint,
		DB_SoldList,
		DB_SetSuit,
		DB_LevelAff,
		DB_HotValue,
		DB_IsDelChar,
		DB_TotalOnlineTime,
		DB_WallowOnlineTime,
		DB_WallowOfflineTime,
		DB_LeaveGuildTime,
		DB_CharCRC,
		DB_KillCountToday,
		DB_TiredTime,
		DB_GoodBad,
		DB_PVP2V2Level,
		DB_PVP2V2Mark,
		DB_PVP2V2Day,
		DB_BankPetValidCt,
		DB_PVP2V2Mark_WeekTotal,
		DB_DBFLAG,
		DB_EXPLOIT,
		DB_EXPLOITDAY,
		DB_HPETGUID,
		DB_LPETGUID,
		//DB_TranPos,
	};
	recordset->GetRecord();

	int fieldcount = recordset->GetFieldCount();
	for (int32 i = 0; i < 1; i++)
	{
		
		pCharDBNode->m_Human.m_bFirstEnterScence = (1 == db_get_property_int(recordset, DB_FirstLogin));
		pCharDBNode->m_Human.m_GUID = db_get_property_uint(recordset, DB_CharGuid);

		strncpy(pCharDBNode->m_Human.m_Name, db_get_property_string(recordset, DB_CharName), sizeof(pCharDBNode->m_Human.m_Name)-1);
		strncpy(pCharDBNode->m_Human.m_Title, db_get_property_string(recordset, DB_Title), sizeof(pCharDBNode->m_Human.m_Title)-1);

		pCharDBNode->m_Human.m_Sex = db_get_property_int(recordset, DB_Sex);
		pCharDBNode->m_Human.m_CreateDate = db_get_property_uint(recordset, DB_CreateTime);
		pCharDBNode->m_Human.m_Level = db_get_property_uint(recordset, DB_Level); 
		pCharDBNode->m_Human.m_Energy = db_get_property_uint(recordset, DB_Enegry); 
		pCharDBNode->m_Human.m_Exp = db_get_property_uint64(recordset, DB_Exp);

		strncpy(pCharDBNode->m_Human.m_Passwd, db_get_property_string(recordset, DB_Pw), sizeof(pCharDBNode->m_Human.m_Passwd) - 1);

		pCharDBNode->m_Human.m_HairColor = db_get_property_uint(recordset, DB_HairColor);
		pCharDBNode->m_Human.m_FaceColor = db_get_property_uint(recordset, DB_FaceColor); 
		pCharDBNode->m_Human.m_HairModel = db_get_property_uint(recordset, DB_HairModel); 
		pCharDBNode->m_Human.m_FaceModel = db_get_property_uint(recordset, DB_FaceModel); 
		pCharDBNode->m_Human.m_StartScene = db_get_property_uint(recordset, DB_Scene); 
		pCharDBNode->m_Human.m_Position.m_fX = db_get_property_uint(recordset, DB_XPos) * 0.01f; 
		pCharDBNode->m_Human.m_Position.m_fZ = db_get_property_uint(recordset, DB_ZPos) * 0.01f; 
		pCharDBNode->m_Human.m_LastLoginTime = db_get_property_uint(recordset, DB_LoginTime); 
		pCharDBNode->m_Human.m_LastLogoutTime = db_get_property_uint(recordset, DB_LogoutTime); 
		pCharDBNode->m_Human.m_DBVersion = db_get_property_uint(recordset, DB_Version); 
		const char* campdata = db_get_property_string(recordset, DB_Camp);

		int32_t size = strlen(campdata);

		uint32_t outLength = 0;
		Str2Binary(campdata, size, (char*)&pCharDBNode->m_Human.m_CampData, sizeof(SCampData), outLength);

		pCharDBNode->m_Human.m_nProfession = db_get_property_uint(recordset, DB_Profession); 
		pCharDBNode->m_Human.m_nCountry = db_get_property_uint(recordset, DB_Country); 
		pCharDBNode->m_Human.m_HP = db_get_property_uint(recordset, DB_HP); 
		pCharDBNode->m_Human.m_MP = db_get_property_uint(recordset, DB_MP); 
		pCharDBNode->m_Human.m_StrikePoint = db_get_property_uint(recordset, DB_StrikePoint); 
		pCharDBNode->m_Human.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR] = db_get_property_uint(recordset, DB_Str);
		pCharDBNode->m_Human.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON] = db_get_property_uint(recordset, DB_Con); 
		pCharDBNode->m_Human.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT] = db_get_property_uint(recordset, DB_Ipr); 
		pCharDBNode->m_Human.m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX] = db_get_property_uint(recordset, DB_Dex); 
		pCharDBNode->m_Human.m_Level1Points = db_get_property_uint(recordset, DB_Points); 

		const char* setting = db_get_property_string(recordset, DB_Setting);

		size = strlen(campdata);

		outLength = 0;
		Str2Binary(setting, size, (char*)&pCharDBNode->m_Setting, sizeof(SArchiveLoader_Setting), outLength);

		pCharDBNode->m_Human.m_GuildID = db_get_property_uint(recordset, DB_GuildID); 
		pCharDBNode->m_Human.m_TeamID = db_get_property_uint(recordset, DB_TeamID); 
		pCharDBNode->m_Human.m_PortraitID = db_get_property_uint(recordset, DB_HeadID); 
		pCharDBNode->m_Human.m_EnergyRegeneRate = db_get_property_int(recordset, DB_eRecover); 
		pCharDBNode->m_Human.m_Vigor = db_get_property_int(recordset, DB_Vigor); 
		pCharDBNode->m_Human.m_MaxVigor = db_get_property_int(recordset, DB_MaxVigor); 
		pCharDBNode->m_Human.m_VigorRegeneRate = db_get_property_int(recordset, DB_VRecover); 
		pCharDBNode->m_Human.m_MaxEnergy = db_get_property_int(recordset, DB_EnergyMax);
		pCharDBNode->m_Human.m_uPwdDelTime = db_get_property_int(recordset, DB_PwdelTime); 
		pCharDBNode->m_Human.m_LeftDieTime = db_get_property_uint(recordset, DB_DieTime); 
		pCharDBNode->m_Bank.m_Count = db_get_property_uint(recordset, DB_BankCount); 
		pCharDBNode->m_Bank.m_CurEndIndex = db_get_property_uint(recordset, DB_BankEnd); 
		pCharDBNode->m_Human.m_BakScene = db_get_property_uint(recordset, DB_BackScene); 
		pCharDBNode->m_Human.m_BakPosition.m_fX = db_get_property_uint(recordset, DB_BackXPos) *0.01f; 
		pCharDBNode->m_Human.m_BakPosition.m_fZ = db_get_property_uint(recordset, DB_BackZPos) * 0.01f;  
		pCharDBNode->m_Human.m_NextScene = db_get_property_uint(recordset, DB_NextScene);
		pCharDBNode->m_Human.m_NextPosition.m_fX = db_get_property_uint(recordset, DB_NextXPos)*0.01f; 
		pCharDBNode->m_Human.m_NextPosition.m_fZ = db_get_property_uint(recordset, DB_NextZPos) * 0.01f; 
		pCharDBNode->m_Human.m_Rage = db_get_property_uint(recordset, DB_Rage);
		pCharDBNode->m_Human.m_Siller = db_get_property_uint(recordset, DB_Silver);
		pCharDBNode->m_Human.m_Gold = db_get_property_uint(recordset, DB_Gold); 
		pCharDBNode->m_Human.m_BindSiller = db_get_property_uint(recordset, DB_BindSilver); 
		pCharDBNode->m_Human.m_BindGold = db_get_property_uint(recordset, DB_BindGold); 
		pCharDBNode->m_Human.m_MoneyMode = db_get_property_uint(recordset, DB_MoneyMode); 
		pCharDBNode->m_Human.m_nRongYu = db_get_property_uint(recordset, DB_Rongyu); 
		pCharDBNode->m_Human.m_nShengWang = db_get_property_int(recordset, DB_Shengwang);
		pCharDBNode->m_Human.m_nWenCai = db_get_property_int(recordset, DB_Wencai); 
		pCharDBNode->m_Human.m_uPwdFlag = db_get_property_uint(recordset, DB_PwdFlag); 
		pCharDBNode->m_Human.m_cLastProtectTime = db_get_property_uint(recordset, DB_LastProtectTime); 
		pCharDBNode->m_Human.m_cProtectTime = db_get_property_uint(recordset, DB_ProtectTime); 
		pCharDBNode->m_Human.m_uProtectDelTime = db_get_property_uint(recordset, DB_ProtectDelTime); 
		pCharDBNode->m_Human.m_BusID = db_get_property_int(recordset, DB_BusID); 
		pCharDBNode->m_Human.m_nPKValue = db_get_property_int(recordset, DB_PkValue); 
		pCharDBNode->m_Human.m_LastForbidChatTime = db_get_property_int(recordset, DB_LastMuteTime); 
		pCharDBNode->m_Human.m_LastEnjailTime = db_get_property_int(recordset, DB_LastEnjailTime); 
		pCharDBNode->m_Human.m_nHonor = db_get_property_int(recordset, DB_Honor); 

		copy_text((char*)&pCharDBNode->m_HonorRecord, sizeof(SArchiveLoader_Honor), recordset, DB_HonorData);

		const char* honor = db_get_property_string(recordset, DB_HonorData);

		size = strlen(honor);

		outLength = 0;
		Str2Binary(honor, size, (char*)&pCharDBNode->m_HonorRecord, sizeof(SArchiveLoader_Honor), outLength);

		pCharDBNode->m_Human.m_cGuildBuild_Count = db_get_property_int(recordset, DB_GuildBuildCount);
		pCharDBNode->m_Human.m_nGuildBuild_Day = db_get_property_int(recordset, DB_GuildBuildDay);
		pCharDBNode->m_Human.m_nLastChgPKModeTime = db_get_property_int(recordset, DB_ChgPKModeTime);

		pCharDBNode->m_Human.m_nInherenceExp = db_get_property_uint(recordset, DB_InherExp);
		pCharDBNode->m_Human.m_nInherenceLevel = db_get_property_uint(recordset, DB_InherLevel);
		pCharDBNode->m_Human.m_SoulID = db_get_property_int(recordset, DB_SoulID);
		pCharDBNode->m_Human.m_GemAff = db_get_property_uint(recordset, DB_GemAff);
		pCharDBNode->m_Human.m_nGP = db_get_property_uint(recordset, DB_GuildPoint);

		copy_text((char*)&pCharDBNode->m_SoldList, sizeof(SArchiveLoader_SoldList), recordset, DB_SoldList);

		const char* soldlist = db_get_property_string(recordset, DB_SoldList);

		size = strlen(honor);

		outLength = 0;
		Str2Binary(soldlist, size, (char*)&pCharDBNode->m_SoldList, sizeof(SArchiveLoader_SoldList), outLength);

		pCharDBNode->m_Human.m_SetSuit = db_get_property_int(recordset, DB_SetSuit);
		pCharDBNode->m_Human.m_LevelAff = db_get_property_int(recordset, DB_LevelAff); 
		pCharDBNode->m_Human.m_nHotValue = db_get_property_int(recordset, DB_HotValue); 
		pCharDBNode->m_Human.m_IsDelChar = db_get_property_int(recordset, DB_IsDelChar);
		pCharDBNode->m_Human.m_nTotalOnlineTime = db_get_property_int(recordset, DB_TotalOnlineTime);
		pCharDBNode->m_Human.m_nWallowOnlineTime = db_get_property_int(recordset, DB_WallowOnlineTime);
		pCharDBNode->m_Human.m_nWallowOfflineTime = db_get_property_int(recordset, DB_WallowOfflineTime);
		pCharDBNode->m_Human.m_LeaveGuildTime = db_get_property_uint(recordset, DB_LeaveGuildTime);

		//m_uCRC = mDBCoreFace->GetUInt(DB_CharCRC, RetCode);

		pCharDBNode->m_Human.m_nKillCountToday = db_get_property_uint(recordset, DB_KillCountToday); 
		pCharDBNode->m_Human.m_TiredTime = db_get_property_uint(recordset, DB_TiredTime);
		pCharDBNode->m_Human.m_nGoodBadValue = db_get_property_int(recordset, DB_GoodBad); 
		pCharDBNode->m_Human.m_nPVP2V2_Level = db_get_property_int(recordset, DB_PVP2V2Level);
		pCharDBNode->m_Human.m_nPVP2V2_Mark = db_get_property_int(recordset, DB_PVP2V2Mark);
		pCharDBNode->m_Human.m_nPVP2V2_Day = db_get_property_int(recordset, DB_PVP2V2Day);
		pCharDBNode->m_BankPetList.m_uValidCount = db_get_property_uint(recordset, DB_BankPetValidCt);
		pCharDBNode->m_Human.m_nPVP2V2_Mark_WeekTotal = db_get_property_int(recordset, DB_PVP2V2Mark_WeekTotal);
		pCharDBNode->m_Human.m_uDBFlag = db_get_property_uint(recordset, DB_DBFLAG);
		pCharDBNode->m_Human.m_nExploit = db_get_property_int(recordset, DB_EXPLOIT);
		pCharDBNode->m_Human.m_nExploitDay = db_get_property_int(recordset, DB_EXPLOITDAY); 
		pCharDBNode->m_Human.m_guidCurrentPet.m_uHighSection = db_get_property_uint(recordset, DB_HPETGUID); 
		pCharDBNode->m_Human.m_guidCurrentPet.m_uLowSection = db_get_property_uint(recordset, DB_LPETGUID); 

		//				mDBCoreFace->GetField( DB_TranPos, (char *) &pCharDBNode->m_Human.m_TransPosInfo, sizeof(TRANS_POS_INFO), RetCode );

		if (pCharDBNode->m_BankPetList.m_uValidCount > PLAYER_BANKPET_MAX_COUNT)
		{
			pCharDBNode->m_BankPetList.m_uValidCount = PLAYER_BANKPET_MAX_COUNT;
		}

		//取得版本
		uint32 dbVersion = pCharDBNode->m_Human.m_DBVersion;


		CharItemTask itemTask(pCharDBNode, mGuid, dbVersion);

		DBManager::GetSingletonPtr()->runDBTask(&itemTask);

		CharSkillTask skillTask(pCharDBNode, mGuid, dbVersion);

		DBManager::GetSingletonPtr()->runDBTask(&skillTask);

		CharAbilityTask abilityTask(pCharDBNode, mGuid, dbVersion);
		DBManager::GetSingletonPtr()->runDBTask(&abilityTask);

		CharPrescriptionTask prescriptionTask(pCharDBNode, mGuid, dbVersion);
		DBManager::GetSingletonPtr()->runDBTask(&prescriptionTask);

		CharQuestTask questTask(pCharDBNode, mGuid, dbVersion);

		DBManager::GetSingletonPtr()->runDBTask(&questTask);

		CharDataExTask dataExTask(pCharDBNode, mGuid, dbVersion);

		DBManager::GetSingletonPtr()->runDBTask(&dataExTask);

		CharHorseTask horseTask(pCharDBNode, mGuid, dbVersion);
		DBManager::GetSingletonPtr()->runDBTask(&horseTask);

		//服务器
		pCharDBNode->m_Human.m_nPlayerWorldID = 1;

		DSCharData* packet = new DSCharData(pCharDBNode);

		NetManager::GetSingletonPtr()->sendNetMessage(packet);

	}
}

CharItemTask::CharItemTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharItemTask::~CharItemTask()
{

}

std::string CharItemTask::get_sql()
{
	char sql[2048];

	snprintf(sql, sizeof(sql) - 1, "select charguid, world, server, guid, itemtype, pos, varattr, creator, termendtime, var, islock, \
		                           unlocktime from t_item where charguid = %s and isvalid = 1 and dbversion = %d", mGuid.c_str(), mdbversion);

	return sql;
}

void CharItemTask::failed(int32_t errcode)
{

}

void CharItemTask::success(CMySQLRecordSet* recordset)
{
	enum
	{
		DB_CharGuid = 0,
		DB_ItemWorld,
		DB_ItemServer,
		DB_ItemGuid,
		DB_ItemType,
		DB_ItemPos,
		DB_VarAttr,
		DB_Creator,
		DB_TermEndTime,
		DB_Var,
		DB_IsLock,
		DB_UnLockTime,
	};

	int32_t count = recordset->GetRecordCount();

	for (int32_t i = 0; i < count; i++)
	{
		recordset->GetRecord();
		uint32_t	CharGuid = db_get_property_uint(recordset, DB_CharGuid);
		uint16	ItemPos = db_get_property_uint(recordset, DB_ItemPos);

		SItem* pItem = mCharDBNode->GetItem(ItemPos);

		pItem->m_ItemGUID.m_World = db_get_property_uint(recordset, DB_ItemWorld);
		pItem->m_ItemGUID.m_Server = db_get_property_uint(recordset, DB_ItemServer);
		pItem->m_ItemGUID.m_Serial = db_get_property_uint(recordset, DB_ItemGuid);
		pItem->m_ItemIndex = db_get_property_uint(recordset, DB_ItemType);


		if (ItemPos == 184)
		{
			int kk = 0;
		}
		const char* attr = recordset->GetFieldValue(DB_VarAttr);

		char	szVarAttr[256] = { 0 };
		uint32_t size = strlen(attr);
		uint32_t OutLength = 0;
		Str2Binary(attr, size, szVarAttr, sizeof(szVarAttr), OutLength);
		pItem->WriteRandomProperty(szVarAttr, sizeof(szVarAttr));

		copy_text(pItem->m_Creator, MAX_ITEM_CREATOR_NAME, recordset, DB_Creator);


		pItem->m_TermEndTime = db_get_property_uint(recordset, DB_TermEndTime);

		copy_text((char*)pItem->m_Param, sizeof(int32)* MAX_ITEM_PARAM, recordset, DB_Var);

		pItem->GetEquipData()->m_byLock = (uchar)(db_get_property_int(recordset, DB_IsLock));
		pItem->GetEquipData()->m_UnLockTime = db_get_property_uint(recordset, DB_UnLockTime);
	}
	
}

//////////////////
CharSkillTask::CharSkillTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharSkillTask::~CharSkillTask()
{

}

std::string CharSkillTask::get_sql()
{
	char sql[2048];
	snprintf(sql, sizeof(sql), "select charguid,skid,skstate,sklevel from t_spell where \
		                         charguid = %s and dbversion=%d order by aid", mGuid.c_str(), mdbversion);
	return sql;
}

void CharSkillTask::failed(int32_t errcode)
{

}

void CharSkillTask::success(CMySQLRecordSet* recordset)
{
	enum 
	{ 
		DB_CharGuid = 0, 
		DB_SkillID, 
		DB_SkillState, 
		DB_SkillLevel 
	};

	int32_t count = recordset->GetRecordCount();

	mCharDBNode->m_Skill.m_Count = count;
	for (int32_t i = 0; i < count; i++)
	{
		recordset->GetRecord();
		uint32_t	CharGuid = db_get_property_uint(recordset, DB_CharGuid);
		int16_t	SkillID = db_get_property_uint(recordset, DB_SkillID);
		int32_t	SkillState = db_get_property_int(recordset, DB_SkillState);
		int32_t	SkillLevel = db_get_property_int(recordset, DB_SkillLevel);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		mCharDBNode->m_Skill.m_aSkill[i].m_nSkillID = SkillID;
		mCharDBNode->m_Skill.m_aSkill[i].m_eState = (_PLAYER_SPELL::_OWN_SKILL_STATE)SkillState;
		mCharDBNode->m_Skill.m_aSkill[i].m_nLevel = SkillLevel;
	}
}
//////
CharAbilityTask::CharAbilityTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharAbilityTask::~CharAbilityTask()
{

}

std::string CharAbilityTask::get_sql()
{
	char sql[2048];
	snprintf(sql, sizeof(sql), "select charguid,abid,ablvl,abexp from t_ability \
	    where charguid = %s and dbversion=%d", mGuid.c_str(), mdbversion);
	return sql;
}

void CharAbilityTask::failed(int32_t errcode)
{

}

void CharAbilityTask::success(CMySQLRecordSet* recordset)
{
	enum 
	{ 
		DB_CharGuid = 0, 
		DB_ABID, 
		DB_ABLvl, 
		DB_ABExp, 
	};

	int32_t count = recordset->GetRecordCount();

	for (int32_t i = 0; i < count; i++)
	{
		recordset->GetRecord();
		uint32_t	CharGuid = db_get_property_uint(recordset, DB_CharGuid);
		uint32_t	AbilityID = db_get_property_uint(recordset, DB_ABID);
		uint32_t	AbilityLvl = db_get_property_int(recordset, DB_ABLvl);
		uint32_t	AbilityExp = db_get_property_int(recordset, DB_ABExp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		mCharDBNode->m_Ability.m_aABility[AbilityID].m_Level = AbilityLvl;
		mCharDBNode->m_Ability.m_aABility[AbilityID].m_Exp = AbilityExp;
	}
}

//////
// //////
CharPrescriptionTask::CharPrescriptionTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharPrescriptionTask::~CharPrescriptionTask()
{

}

std::string CharPrescriptionTask::get_sql()
{
	char sql[2048];
	snprintf(sql, sizeof(sql), "select charguid,pres from t_char where \
		charguid = %s and dbversion=%d", mGuid.c_str(), mdbversion);
	return sql;
}

void CharPrescriptionTask::failed(int32_t errcode)
{

}

void CharPrescriptionTask::success(CMySQLRecordSet* recordset)
{
	enum
	{
		CHARDB_CharGuid = 0,
		CHARDB_PresData,
	};

	int32_t count = recordset->GetRecordCount();

	for (int32_t i = 0; i < 1; i++)
	{
		recordset->GetRecord();
		uint32_t	CharGuid = db_get_property_uint(recordset, CHARDB_CharGuid);
		
		const char* prescription = db_get_property_string(recordset, CHARDB_PresData);

		uint32_t size = strlen(prescription);
		uint32_t OutLength = 0;
		Str2Binary(prescription, size, (char*)(mCharDBNode->m_Ability.m_aPrescr),
			sizeof(char)* MAX_CHAR_PRESCRIPTION_BYTE, OutLength);
	}
}
//////
CharQuestTask::CharQuestTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharQuestTask::~CharQuestTask()
{

}

std::string CharQuestTask::get_sql()
{
	char sql[256];
	snprintf(sql, sizeof(sql), "select charguid,missionid,scriptid,flag,p1,p2,p3,p4,p5,p6,p7,p8 \
		from t_quest where charguid = %s and dbversion=%d", mGuid.c_str(), mdbversion);
	return sql;
}

void CharQuestTask::failed(int32_t errcode)
{

}

void CharQuestTask::success(CMySQLRecordSet* recordset)
{
	enum
	{
		DB_CharGuid = 0,
		DB_TaskID,
		DB_ScriptID,
		DB_Flag,
		DB_TP1,
		DB_TP2,
		DB_TP3,
		DB_TP4,
		DB_TP5,
		DB_TP6,
		DB_TP7,
		DB_TP8,
	};

	int32_t count = recordset->GetRecordCount();

	for (int32_t i = 0; i < count; i++)
	{
		recordset->GetRecord();
		mCharDBNode->m_QuestDB.m_aQuest[i].m_idQuest = db_get_property_uint(recordset, DB_TaskID);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_idScript = db_get_property_uint(recordset, DB_ScriptID);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_yFlags = db_get_property_uint(recordset, DB_Flag);

		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[0] = db_get_property_uint(recordset, DB_TP1);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[1] = db_get_property_uint(recordset, DB_TP2);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[2] = db_get_property_uint(recordset, DB_TP3);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[3] = db_get_property_uint(recordset, DB_TP4);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[4] = db_get_property_uint(recordset, DB_TP5);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[5] = db_get_property_uint(recordset, DB_TP6);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[6] = db_get_property_uint(recordset, DB_TP7);
		mCharDBNode->m_QuestDB.m_aQuest[i].m_anParam[7] = db_get_property_uint(recordset, DB_TP8);
		mCharDBNode->m_QuestDB.m_Count++;
	}

	CharQuestDataTask dataTask(mCharDBNode, mGuid, mdbversion);

	DBManager::GetSingletonPtr()->runDBTask(&dataTask);

}

//////////



//////
CharQuestDataTask::CharQuestDataTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharQuestDataTask::~CharQuestDataTask()
{

}

std::string CharQuestDataTask::get_sql()
{
	char sql[256];
	snprintf(sql, sizeof(sql), "select charguid,mdata,mflag from t_char where charguid = %s and dbversion=%d",
		mGuid.c_str(), mdbversion);
	return sql;
}

void CharQuestDataTask::failed(int32_t errcode)
{

}

void CharQuestDataTask::success(CMySQLRecordSet* recordset)
{
	
	recordset->GetRecord();

	enum { 
		CHARDB_CharGuid = 0, 
		CHARDB_MissionData, 
		CHARDB_MissionFlag};

	const char* str = db_get_property_string(recordset, CHARDB_MissionData);

	int32_t size = strlen(str);
	uint32_t outLength = 0;
	Str2Binary(str, size, (char*)mCharDBNode->m_QuestDB.m_aQuestData, sizeof(int32)* MAX_CHAR_QUEST_DATA_NUM, outLength);
	outLength = 0;
	str = db_get_property_string(recordset, CHARDB_MissionFlag);
	size = strlen(str);
	Str2Binary(str, size, (char*)mCharDBNode->m_QuestDB.m_aQuestHaveDoneFlags, sizeof(int32)* MAX_CHAR_QUEST_DATA_NUM, outLength);
}

/// <summary>
/// /
/// </summary>
/// <param name="pCharDBNode"></param>
/// <param name="guid"></param>
/// <param name="dbversion"></param>
CharDataExTask::CharDataExTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharDataExTask::~CharDataExTask()
{

}

std::string CharDataExTask::get_sql()
{
	char sql[2048];
	snprintf(sql, sizeof(sql), "select shopfavorite,shopbuyhistory,battlehonour,critRate_balance,toughness_balance,hit_balance,miss_balance, \
		 critDamage_balance,critDamageDerate_balance,ctrlHit_balance,ctrlMiss_balance,wushi_zhangong_level,jianxia_zhangong_level,qishe_zhangong_level, \
		huoqiang_zhangong_level,xianzhi_zhangong_level,saman_zhangong_level,shizhijun_zhangong_level,shenghuoshi_zhangong_level,cike_zhangong_level,\
		jinweijun_zhangong_level,yinxiushi_zhangong_level,lama_zhangong_level,wushi_zhangong_point,jianxia_zhangong_point,qishe_zhangong_point,\
		huoqiang_zhangong_point,xianzhi_zhangong_point,saman_zhangong_point,shizhijun_zhangong_point,shenghuoshi_zhangong_point,cike_zhangong_point,\
		jinweijun_zhangong_point,yinxiushi_zhangong_point,lama_zhangong_point,total_zhangong_coefficient,wushi_zhangong_coefficient,\
		jianxia_zhangong_coefficient,qishe_zhangong_coefficient,huoqiang_zhangong_coefficient,xianzhi_zhangong_coefficient,saman_zhangong_coefficient,\
		shizhijun_zhangong_coefficient,shenghuoshi_zhangong_coefficient,cike_zhangong_coefficient,jinweijun_zhangong_coefficient,\
		yinxiushi_zhangong_coefficient,lama_zhangong_coefficient,tatol_zhanfang_point,wushi_zhanfang_level,jianxia_zhanfang_level,\
		qishe_zhanfang_level,huoqiang_zhanfang_level,xianzhi_zhanfang_level,saman_zhanfang_level,shizhijun_zhanfang_level,shenghuoshi_zhanfang_level,\
		cike_zhanfang_level,jinweijun_zhanfang_level,yinxiushi_zhanfang_level,lama_zhanfang_level from t_char_ext where charguid=%s", mGuid.c_str());
	return sql;
}

void CharDataExTask::failed(int32_t errcode)
{

}

void CharDataExTask::success(CMySQLRecordSet* recordset)
{

}


CharHorseTask::CharHorseTask(CHARDBNODE* pCharDBNode, std::string& guid, int32_t dbversion)
{
	mCharDBNode = pCharDBNode;
	mGuid = guid;
	mdbversion = dbversion;
}

CharHorseTask::~CharHorseTask()
{

}


std::string CharHorseTask::get_sql()
{
	char sql[2048];
	snprintf(sql, sizeof(sql), "select charguid ,hpetguid,lpetguid,dataid,petname,petnick,level, \
		                       needlevel,atttype,aitype,camp,genera,enjoy,strper,conper,dexper,iprper, \
                               growrate,repoint,exp,str,con,dex,ipr,skill,strpoint,smartpoint,mindpoint,conpoint, \
                               modelid,mat,happinesslefttime,stallorder,islock,unlocktime from t_horse where \
		                       charguid =%s and dbversion=%d order by stallorder asc", mGuid.c_str(), mdbversion);
	return sql;
}

void CharHorseTask::failed(int32_t errcode)
{

}

void CharHorseTask::success(CMySQLRecordSet* recordset)
{
	enum
	{
		DB_CharGuid = 0,
		DB_hPetGuid,
		DB_lPetGuid,
		DB_PetDataID,
		DB_PetName,
		DB_PetNick,
		DB_Level,
		DB_NeedLevel,
		DB_AttType,
		DB_AIType,
		DB_Camp,
		DB_Genera,
		DB_Enjoy,
		DB_StrPer,
		DB_ConPer,
		DB_DexPer,
		DB_IprPer,
		DB_GrowRate,
		DB_RePoint,
		DB_Exp,
		DB_Str,
		DB_Con,
		DB_Dex,
		DB_Ipr,
		DB_Skill,
		DB_StrPoint,
		DB_SmartPoint,
		DB_MindPoint,
		DB_ConPoint,
		DB_ModelID,
		DB_Mating,
		DB_HappinessLeftTime,
		DB_Stallorder,
		DB_Lock,
		DB_UnLockTime,
	};

	int32_t horse_count = recordset->GetRecordCount();


	mCharDBNode->m_PetList.Clear();
	mCharDBNode->m_BankPetList.Clear();

	for (int32_t i = 0; i < horse_count; i++)
	{
		recordset->GetRecord();
		int32	iStallOrder = db_get_property_int(recordset, DB_Stallorder);

		int index = i;
		if
			(
				iStallOrder >= PLAYER_PET_MAX_COUNT
				&& iStallOrder < PLAYER_PET_MAX_COUNT + PLAYER_BANKPET_MAX_COUNT
				)
		{
			index = iStallOrder - PLAYER_PET_MAX_COUNT;
			uint32	CharGuid = db_get_property_uint(recordset, DB_CharGuid);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


			mCharDBNode->m_BankPetList.m_aPetDB[index].m_GUID.Init
			(
				db_get_property_uint(recordset, DB_hPetGuid),
				db_get_property_uint(recordset, DB_lPetGuid)
			);

			mCharDBNode->m_BankPetList.m_aPetDB[index].m_nDataID = db_get_property_int(recordset, DB_PetDataID);

			copy_text(mCharDBNode->m_BankPetList.m_aPetDB[index].m_szName, MAX_CHARACTER_NAME, recordset, DB_PetName);
			copy_text(mCharDBNode->m_BankPetList.m_aPetDB[index].m_szNick, MAX_NICK_NAME, recordset, DB_PetNick);

			mCharDBNode->m_BankPetList.m_aPetDB[index].m_nLevel = db_get_property_int(recordset, DB_Level);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_nTakeLevel = db_get_property_int(recordset, DB_NeedLevel);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_nAttackType = db_get_property_int(recordset, DB_AttType);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_AIType = db_get_property_int(recordset, DB_AIType);

			const char* campdata = db_get_property_string(recordset, DB_Camp);
			int32_t size = strlen(campdata);
			uint32_t outLength = 0;
			Str2Binary(campdata, size, (char*)&mCharDBNode->m_BankPetList.m_aPetDB[index].m_CampData, sizeof(SCampData), outLength);


			mCharDBNode->m_BankPetList.m_aPetDB[index].m_byGeneration = db_get_property_int(recordset, DB_Genera);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_byHappiness = db_get_property_int(recordset, DB_Enjoy);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iStrengthPerception = db_get_property_int(recordset, DB_StrPer);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iSmartnessPerception = db_get_property_uint(recordset, DB_ConPer);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iMindPerception = db_get_property_uint(recordset, DB_DexPer);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iConstitutionPerception = db_get_property_uint(recordset, DB_IprPer);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_fGrowRate = db_get_property_uint(recordset, DB_GrowRate) * 0.001f;
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_nRemainPoint = db_get_property_int(recordset, DB_RePoint);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_nExp = db_get_property_uint(recordset, DB_Exp);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR] = db_get_property_int(recordset, DB_Str);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON] = db_get_property_int(recordset, DB_Con);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX] = db_get_property_int(recordset, DB_Dex);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT] = db_get_property_int(recordset, DB_Ipr);
			const char* skilldata = db_get_property_string(recordset, DB_Skill);
			size = strlen(skilldata);
			outLength = 0;
			Str2Binary(skilldata, size, (char*)mCharDBNode->m_BankPetList.m_aPetDB[index].m_SkillList,
				sizeof(SHorseSkill)* PET_MAX_SKILL_COUNT, outLength);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iStrengthPoint = db_get_property_int(recordset, DB_StrPoint);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iSmartnessPoint = db_get_property_int(recordset, DB_SmartPoint);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iMindPoint = db_get_property_int(recordset, DB_MindPoint);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iConstitutionPoint = db_get_property_int(recordset, DB_ConPoint);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iModelID = db_get_property_int(recordset, DB_ModelID);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iStatus = db_get_property_int(recordset, DB_Mating);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_uHappinessLeftTime = db_get_property_uint(recordset, DB_HappinessLeftTime);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_iStallOrder = db_get_property_int(recordset, DB_Stallorder);

			mCharDBNode->m_BankPetList.m_aPetDB[index].m_byLock = db_get_property_int(recordset, DB_Lock);
			mCharDBNode->m_BankPetList.m_aPetDB[index].m_UnLockTime = db_get_property_uint(recordset, DB_UnLockTime);
		}
		else
		{
			uint32	CharGuid = db_get_property_uint(recordset, DB_CharGuid);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


			mCharDBNode->m_PetList.m_aPetDB[index].m_GUID.Init
			(
				db_get_property_uint(recordset, DB_hPetGuid),
				db_get_property_uint(recordset, DB_lPetGuid)
			);

			mCharDBNode->m_PetList.m_aPetDB[index].m_nDataID = db_get_property_int(recordset, DB_PetDataID);

			copy_text(mCharDBNode->m_PetList.m_aPetDB[index].m_szName, MAX_CHARACTER_NAME, recordset, DB_PetName);
			copy_text(mCharDBNode->m_PetList.m_aPetDB[index].m_szNick, MAX_NICK_NAME, recordset, DB_PetNick);

			mCharDBNode->m_PetList.m_aPetDB[index].m_nLevel = db_get_property_int(recordset, DB_Level);
			mCharDBNode->m_PetList.m_aPetDB[index].m_nTakeLevel = db_get_property_int(recordset, DB_NeedLevel);
			mCharDBNode->m_PetList.m_aPetDB[index].m_nAttackType = db_get_property_int(recordset, DB_AttType);
			mCharDBNode->m_PetList.m_aPetDB[index].m_AIType = db_get_property_int(recordset, DB_AIType);

			const char* campdata = db_get_property_string(recordset, DB_Camp);
			int32_t size = strlen(campdata);
			uint32_t outLength = 0;
			Str2Binary(campdata, size, (char*)&mCharDBNode->m_PetList.m_aPetDB[index].m_CampData, sizeof(SCampData), outLength);


			mCharDBNode->m_PetList.m_aPetDB[index].m_byGeneration = db_get_property_int(recordset, DB_Genera);
			mCharDBNode->m_PetList.m_aPetDB[index].m_byHappiness = db_get_property_int(recordset, DB_Enjoy);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iStrengthPerception = db_get_property_int(recordset, DB_StrPer);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iSmartnessPerception = db_get_property_uint(recordset, DB_ConPer);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iMindPerception = db_get_property_uint(recordset, DB_DexPer);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iConstitutionPerception = db_get_property_uint(recordset, DB_IprPer);
			mCharDBNode->m_PetList.m_aPetDB[index].m_fGrowRate = db_get_property_uint(recordset, DB_GrowRate) * 0.001f;
			mCharDBNode->m_PetList.m_aPetDB[index].m_nRemainPoint = db_get_property_int(recordset, DB_RePoint);
			mCharDBNode->m_PetList.m_aPetDB[index].m_nExp = db_get_property_uint(recordset, DB_Exp);
			mCharDBNode->m_PetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR] = db_get_property_int(recordset, DB_Str);
			mCharDBNode->m_PetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON] = db_get_property_int(recordset, DB_Con);
			mCharDBNode->m_PetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX] = db_get_property_int(recordset, DB_Dex);
			mCharDBNode->m_PetList.m_aPetDB[index].m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT] = db_get_property_int(recordset, DB_Ipr);
			const char* skilldata = db_get_property_string(recordset, DB_Skill);
			size = strlen(skilldata);
			outLength = 0;
			Str2Binary(skilldata, size, (char*)mCharDBNode->m_PetList.m_aPetDB[index].m_SkillList,
				sizeof(SHorseSkill) * PET_MAX_SKILL_COUNT, outLength);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iStrengthPoint = db_get_property_int(recordset, DB_StrPoint);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iSmartnessPoint = db_get_property_int(recordset, DB_SmartPoint);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iMindPoint = db_get_property_int(recordset, DB_MindPoint);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iConstitutionPoint = db_get_property_int(recordset, DB_ConPoint);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iModelID = db_get_property_int(recordset, DB_ModelID);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iStatus = db_get_property_int(recordset, DB_Mating);
			mCharDBNode->m_PetList.m_aPetDB[index].m_uHappinessLeftTime = db_get_property_uint(recordset, DB_HappinessLeftTime);
			mCharDBNode->m_PetList.m_aPetDB[index].m_iStallOrder = db_get_property_int(recordset, DB_Stallorder);

			mCharDBNode->m_PetList.m_aPetDB[index].m_byLock = db_get_property_int(recordset, DB_Lock);
			mCharDBNode->m_PetList.m_aPetDB[index].m_UnLockTime = db_get_property_uint(recordset, DB_UnLockTime);
		}
		
	}
}
