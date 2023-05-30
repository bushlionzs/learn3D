#include "stdafx.h"
#include "share/Core/BaseTool.h"

#include "TAB.h"
#include "share/core/FileDef.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "TabDefine_Map_Monster.h"
#include "TabDefine_Map_Quest.h"
extern _NPC_QUEST_TBL	g_NpcQuestTbl;
using namespace TAB;

SMonsterAttrexTab			g_MonsterPropertyExTab;
_BUS_ATTREX_TBL				g_BusAttrExTbl;
SMonsterBHVTab				g_MonsterBehaviorTab;
MonsterWeaponAndSkillTable	g_MonsterWeaponAndSkill;
SMonsterSpeakTab			g_MonsterSpeakTab;
RandomMonsterMap			*g_pRandomMonsterConfig[MAX_SCENE];

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TableInit_Map_Monster::TableInit_Map_Monster()
{}

TableInit_Map_Monster::~TableInit_Map_Monster()
{}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TableInit_Map_Monster::Init()
{
	__GUARD__

	Init_MonsterAttrExTable();
	Init_BusAttrExTable();
	LoadMonsterAITable();
	LoadMonsterSkillTable();
	LoadMonsterSpeakTable();
	LoadRandomMonster(); // 2010-11-26 by rj 增加读取随机怪物表功能

	return TRUE;
	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::ReadWeaponID
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	int32			iType
)
{
	pSplitL1->Reset();
	pSplitL2->Reset();
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	int32	iLineCount = pSplitL2->GetResultLineCount();

	KCheck(MONSTER_EXT_ATTR_ENUM_SIZE >= iLineCount);
	if(MONSTER_EXT_ATTR_ENUM_SIZE < iLineCount)
	{
		return;
	}

	for(int32 iWeapon = 0; iWeapon < iLineCount; ++iWeapon)
	{
		g_MonsterPropertyExTab.m_TableExt[iType].m_WeaponID[iWeapon] = atoi(pSplitL2->GetResultLine(iWeapon));
	}

	g_MonsterPropertyExTab.m_TableExt[iType].m_iWeaponCount = iLineCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::ReadHorseID
(
	SplitStringLevelOne	*pSplitL1,
	SplitStringLevelTwo	*pSplitL2,
	const char		*pSplitString,
	int32			iType
)
{
	pSplitL1->Reset();
	pSplitL2->Reset();
	pSplitL1->Init('|', pSplitL2);
	pSplitL2->Init('~', NULL);
	pSplitL1->DoSplit(pSplitString);

	int32	iLineCount = pSplitL2->GetResultLineCount();

	KCheck(MONSTER_EXT_ATTR_ENUM_SIZE >= iLineCount);
	if(MONSTER_EXT_ATTR_ENUM_SIZE < iLineCount)
	{
		return;
	}

	for(int32 iHorse = 0; iHorse < iLineCount; ++iHorse)
	{
		g_MonsterPropertyExTab.m_TableExt[iType].m_HorseID[iHorse] = atoi(pSplitL2->GetResultLine(iHorse));
	}

	g_MonsterPropertyExTab.m_TableExt[iType].m_iHorseCount = iLineCount;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::Init_MonsterAttrExTable()
{
	__GUARD__ 
		
	enum MonsterAttrData
	{
		MonsterType				= 0,
		MonsterCannotFight,
		MonsterName,
		MonsterOutLook				= 10,
		MonsterCanHandle,
		MonsterBossFlag,
		Monster_CATTR_LEVEL2_SPEED,
		MonsterWalkSpeed,
		MonsterLevel				= 25,
		MonsterRespawnTime,
		MonsterMinDamagePercent,
		MonsterExp,
		Monster_CATTR_LEVEL2_ATTACKRATE_NEAR,
		Monster_CATTR_LEVEL2_ATTACKRATE_FAR,
		Monster_CATTR_LEVEL2_ATTACKRATE_M,
		Monster_CATTR_LEVEL2_DEFENCE_NEAR,
		Monster_CATTR_LEVEL2_DEFENCE_FAR,
		Monster_CATTR_LEVEL2_DEFENCE_M,
		Monster_CATTR_LEVEL2_MAXHP,
		Monster_CATTR_LEVEL2_MAXMP,
		Monster_CATTR_LEVEL2_RESTOREHP,
		Monster_CATTR_LEVEL2_RESTOREMP,
		Monster_CATTR_LEVEL2_HIT,
		Monster_CATTR_LEVEL2_MISS,
		Monster_CATTR_LEVEL2_CRITRATE,
		Monster_CATTR_LEVEL2_TOUGHNESS,
		MonsterAttrAttack1,
		MonsterAttrAttack2,
		MonsterAttrAttack3,
		MonsterAttrAttack4,
		MonsterAttrDefence1,
		MonsterAttrDefence2,
		MonsterAttrDefence3,
		MonsterAttrDefence4,
		MonsterScriptID,
		MonsterAttackAnimTime,
		MonsterAttackCooldownTime,
		Monster_CATTR_LEVEL2_ATTACKSPEED,
		MonsterWeaponID,
		MonsterHorseID,
		MonsterBaseAI,
		MonsterExtAI,
		MonsterCamp,
		MonsterFriendValue,
		MonsterBossSnapImmID,
		MonsterBossDurationImmID,
		MonsterDropSearchRange,
		MonsterDropTeamCount,
		MonsterDropItemSetID,
		MonsterDropRate,
		MonsterDropHorseID,
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_MONSTER_ATTREX);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();

	KCheck(iTableCount > 0 && iTableCount < MAXTYPE_NUMBER);
	g_MonsterPropertyExTab.m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char	*pSplitString = NULL;
	int32		iValue;
	int32		iType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MonsterDropTeamCount < iColumnCount);

	for(int32 i = 0; i < iTableCount; i++)
	{
		iType = ThirdFile.Search_Posistion(i, MonsterType)->iValue;

		if(g_MonsterPropertyExTab.m_MaxType < (uint32) iType) 
			g_MonsterPropertyExTab.m_MaxType = iType;

		g_MonsterPropertyExTab.m_TableExt[i].m_Type = iType;
		iType = i;

		strncpy( g_MonsterPropertyExTab.m_TableExt[iType].m_Name,
				ThirdFile.Search_Posistion(i, MonsterName)->pString,
				sizeof(g_MonsterPropertyExTab.m_TableExt[i].m_Name) - 1 );

		g_MonsterPropertyExTab.m_TableExt[iType].m_Level = ThirdFile.Search_Posistion(i, MonsterLevel)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_RespawnTime = ThirdFile.Search_Posistion(i, MonsterRespawnTime)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_MinDamagePercent = ThirdFile.Search_Posistion(i, MonsterMinDamagePercent)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_BaseExp = ThirdFile.Search_Posistion(i, MonsterExp)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACK_NEAR] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_ATTACKRATE_NEAR)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACK_FAR] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_ATTACKRATE_FAR)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKRATE_M] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_ATTACKRATE_M)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCE_NEAR] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_DEFENCE_NEAR)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCE_FAR] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_DEFENCE_FAR)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCE_M] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_DEFENCE_M)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_MAXHP] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_MAXHP)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_MAXMP] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_MAXMP)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_RESTOREHP] = ThirdFile.Search_Posistion(i,Monster_CATTR_LEVEL2_RESTOREHP)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_RESTOREMP] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_RESTOREMP
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_HIT] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_HIT
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_MISS] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_MISS
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_CRITRATE] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_CRITRATE
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_TOUGHNESS] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_TOUGHNESS
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKCOLD] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack1
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKFIRE] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack2
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKLIGHT] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack3
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKPOISON] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack4
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCECOLD] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence1
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCEFIRE] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence2
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCELIGHT] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence3
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCEPOISON] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence4
			)->iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_ScriptID = ThirdFile.Search_Posistion
			(
				i,
				MonsterScriptID
			)->iValue;

		KCheck(g_MonsterPropertyExTab.m_TableExt[iType].m_ScriptID <= 0 || g_MonsterPropertyExTab.m_TableExt[iType].m_ScriptID >= 100000);

		iValue = ThirdFile.Search_Posistion(i, MonsterAttackAnimTime)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_AttackAnimTime = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterAttackCooldownTime)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_AttackCooldownTime = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterOutLook)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_OutLook = iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_SPEED] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_SPEED
			)->iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterWalkSpeed)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_WalkSpeed = iValue;

		g_MonsterPropertyExTab.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKSPEED] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_ATTACKSPEED
			)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SplitStringLevelOne	oSplitL1;
		SplitStringLevelTwo	oSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitString = ThirdFile.Search_Posistion(i, MonsterWeaponID)->pString;
		ReadWeaponID(&oSplitL1, &oSplitL2, pSplitString, iType);

		pSplitString = ThirdFile.Search_Posistion(i, MonsterHorseID)->pString;

		ReadHorseID(&oSplitL1, &oSplitL2, pSplitString, iType);

		iValue = ThirdFile.Search_Posistion(i, MonsterBaseAI)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_BaseAI = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterExtAI)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_ExtAI = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterCamp)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_Camp = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterCannotFight)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_CannotFight = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterCanHandle)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_CanHandle = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterFriendValue)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_FriendValue = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBossFlag)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_BossFlag = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBossSnapImmID)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_SnapSkillImmID = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBossDurationImmID)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_DurationSkillImmID = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterDropSearchRange)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_DropSearchRange = (float) iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterDropTeamCount)->iValue;
		g_MonsterPropertyExTab.m_TableExt[iType].m_SearchTeamCount = iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char		*pSplitString = ThirdFile.Search_Posistion(i, MonsterDropItemSetID)->pString;
		SplitStringLevelOne	pSplitL1;
		SplitStringLevelTwo	pSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitL1.Reset();
		pSplitL2.Reset();
		pSplitL1.Init('|', &pSplitL2);
		pSplitL2.Init('~', NULL);
		pSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = pSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iLineCount > 10) iLineCount = 0;
		g_MonsterPropertyExTab.m_TableExt[iType].m_MonsterDropSetCount = iLineCount;
		g_MonsterPropertyExTab.m_TableExt[iType].m_MonsterDropItemSetID = new int32[iLineCount];
		for(int32 nID = 0; nID < iLineCount; ++nID)
		{
			g_MonsterPropertyExTab.m_TableExt[iType].m_MonsterDropItemSetID[nID] = atoi(pSplitL2.GetResultLine(nID));
		}

		iValue = ThirdFile.Search_Posistion(i, MonsterDropRate)->iValue;
		if(iValue < 0)
		{
			g_MonsterPropertyExTab.m_TableExt[iType].m_nMonsterDropRate = 0;
		}
		else
		{
			KCheck(iValue <= 100);
			g_MonsterPropertyExTab.m_TableExt[iType].m_nMonsterDropRate = iValue;
		}

		g_MonsterPropertyExTab.m_TableExt[iType].m_nMonsterDropRate = iValue;

		pSplitString = ThirdFile.Search_Posistion(i, MonsterDropHorseID)->pString;
		g_MonsterPropertyExTab.m_TableExt[iType].m_iHorseDropCount = CommonStringSplit
			(
				&oSplitL1,
				&oSplitL2,
				pSplitString,
				MaxHorseDropNum,
				g_MonsterPropertyExTab.m_TableExt[iType].m_aHorseDropID
			);

		g_MonsterPropertyExTab.m_TableExt[iType].m_Used = TRUE;
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::Init_BusAttrExTable()
{
	__GUARD__ enum BusAttrData
	{
		MonsterType				= 0,
		MonsterCannotFight,
		MonsterName,
		MonsterOutLook				= 15,
		MonsterCanHandle,
		MonsterBossFlag,
		MonsterLevel				= 35,
		MonsterRespawnTime,
		MonsterMinDamagePercent,
		MonsterExp,
		Monster_CATTR_LEVEL2_ATTACKRATE_NEAR,
		Monster_CATTR_LEVEL2_ATTACKRATE_FAR,
		Monster_CATTR_LEVEL2_ATTACKRATE_M,
		Monster_CATTR_LEVEL2_DEFENCE_NEAR,
		Monster_CATTR_LEVEL2_DEFENCE_FAR,
		Monster_CATTR_LEVEL2_DEFENCE_M,
		Monster_CATTR_LEVEL2_MAXHP,
		Monster_CATTR_LEVEL2_MAXMP,
		Monster_CATTR_LEVEL2_RESTOREHP,
		Monster_CATTR_LEVEL2_RESTOREMP,
		Monster_CATTR_LEVEL2_HIT,
		Monster_CATTR_LEVEL2_MISS,
		Monster_CATTR_LEVEL2_CRITRATE,
		Monster_CATTR_LEVEL2_TOUGHNESS,
		MonsterAttrAttack1,
		MonsterAttrAttack2,
		MonsterAttrAttack3,
		MonsterAttrAttack4,
		MonsterAttrDefence1,
		MonsterAttrDefence2,
		MonsterAttrDefence3,
		MonsterAttrDefence4,
		MonsterScriptID,
		MonsterAttackAnimTime,
		MonsterAttackCooldownTime,
		Monster_CATTR_LEVEL2_SPEED,
		MonsterWalkSpeed,
		Monster_CATTR_LEVEL2_ATTACKSPEED,
		MonsterWeaponID,
		MonsterHorseID,
		MonsterBaseAI,
		MonsterExtAI,
		MonsterCamp,
		MonsterFriendValue,
		MonsterBossSnapImmID,
		MonsterBossDurationImmID,
		MonsterDropSearchRange,
		MonsterDropTeamCount,
		MonsterDropItemSetID,
		MonsterDropRate,
		MonsterDropHorseID,
		PassiveSkill_1				= MonsterDropHorseID + 5,
		PassiveSkill_2,
		PassiveSkill_3,
		PassiveSkill_4,
		PassiveSkill_5,
		Title,
		IsSysControl,
		MemberNum,
		IsShowPlayer,
		Skill_1,
		Skill_2,
		Skill_3,
		Skill_4,
		Skill_5,
		TypeOfBus,
		PKMode,
		MinValidFollowDist,
		MaxValidFollowDist,
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_BUS_ATTREX);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0 && iTableCount < BUS_MAX_TYPE_NUMBER);
	g_BusAttrExTbl.m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char	*pSplitString = NULL;
	int32		iValue;
	int32		iType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(MaxValidFollowDist < iColumnCount);

	for(int32 i = 0; i < iTableCount; i++)
	{
		iValue = ThirdFile.Search_Posistion(i, MonsterType)->iValue;

		iType = iValue;

		if(g_BusAttrExTbl.m_MaxType < (uint32) iType) g_BusAttrExTbl.m_MaxType = iType;

		g_BusAttrExTbl.m_TableExt[i].m_Type = iType;
		iType = i;

		strncpy
		(
			g_BusAttrExTbl.m_TableExt[iType].m_Name,
			ThirdFile.Search_Posistion(i, MonsterName)->pString,
			sizeof(g_BusAttrExTbl.m_TableExt[i].m_Name) - 1
		);

		iValue = ThirdFile.Search_Posistion(i, MonsterLevel)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_Level = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterRespawnTime)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_RespawnTime = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterMinDamagePercent)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_MinDamagePercent = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterExp)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_BaseExp = iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACK_NEAR] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_ATTACKRATE_NEAR
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACK_FAR] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_ATTACKRATE_FAR
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKRATE_M] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_ATTACKRATE_M
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCE_NEAR] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_DEFENCE_NEAR
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCE_FAR] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_DEFENCE_FAR
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCE_M] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_DEFENCE_M
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_MAXHP] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_MAXHP
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_MAXMP] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_MAXMP
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_RESTOREHP] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_RESTOREHP
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_RESTOREMP] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_RESTOREMP
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_HIT] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_HIT
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_MISS] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_MISS
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_CRITRATE] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_CRITRATE
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_TOUGHNESS] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_TOUGHNESS
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKCOLD] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack1
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKFIRE] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack2
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKLIGHT] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack3
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKPOISON] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrAttack4
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCECOLD] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence1
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCEFIRE] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence2
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCELIGHT] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence3
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_DEFENCEPOISON] = ThirdFile.Search_Posistion
			(
				i,
				MonsterAttrDefence4
			)->iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_ScriptID = ThirdFile.Search_Posistion(i, MonsterScriptID)->iValue;
		KCheck(g_BusAttrExTbl.m_TableExt[iType].m_ScriptID <= 0 || g_BusAttrExTbl.m_TableExt[iType].m_ScriptID >= 100000);

		iValue = ThirdFile.Search_Posistion(i, MonsterAttackAnimTime)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_AttackAnimTime = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterAttackCooldownTime)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_AttackCooldownTime = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterOutLook)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_OutLook = iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_SPEED] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_SPEED
			)->iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterWalkSpeed)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_WalkSpeed = iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Table[CPROPERTY_LEVEL2_ATTACKSPEED] = ThirdFile.Search_Posistion
			(
				i,
				Monster_CATTR_LEVEL2_ATTACKSPEED
			)->iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBaseAI)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_BaseAI = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterExtAI)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_ExtAI = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterCamp)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_Camp = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterCannotFight)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_CannotFight = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterCanHandle)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_CanHandle = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterFriendValue)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_FriendValue = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBossFlag)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_BossFlag = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBossSnapImmID)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_SnapSkillImmID = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterBossDurationImmID)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_DurationSkillImmID = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterDropSearchRange)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_DropSearchRange = (float) iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterDropTeamCount)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_SearchTeamCount = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterDropItemSetID)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_MonsterDropItemSetID = iValue;

		iValue = ThirdFile.Search_Posistion(i, MonsterDropRate)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_nMonsterDropRate = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill_1)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iPassiveSkill_1 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill_2)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iPassiveSkill_2 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill_3)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iPassiveSkill_3 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill_4)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iPassiveSkill_4 = iValue;

		iValue = ThirdFile.Search_Posistion(i, PassiveSkill_5)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iPassiveSkill_5 = iValue;

		strncpy
		(
			g_BusAttrExTbl.m_TableExt[iType].m_Title,
			ThirdFile.Search_Posistion(i, Title)->pString,
			sizeof(g_BusAttrExTbl.m_TableExt[i].m_Title) - 1
		);

		iValue = ThirdFile.Search_Posistion(i, IsSysControl)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_IsSysControl = iValue;

		iValue = ThirdFile.Search_Posistion(i, MemberNum)->iValue;
		if(iValue > BUS_MAX_MEMBER_NUMBER)
		{
			KCheckEx(FALSE, "iValue > BUS_MAX_MEMBER_NUMBER");
			iValue = BUS_MAX_MEMBER_NUMBER;
		}

		g_BusAttrExTbl.m_TableExt[iType].m_iMemberNum = iValue;

		iValue = ThirdFile.Search_Posistion(i, IsShowPlayer)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_IsShowPlayer = iValue;

		iValue = ThirdFile.Search_Posistion(i, Skill_1)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iSkill_1 = iValue;

		iValue = ThirdFile.Search_Posistion(i, Skill_2)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iSkill_2 = iValue;

		iValue = ThirdFile.Search_Posistion(i, Skill_3)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iSkill_3 = iValue;

		iValue = ThirdFile.Search_Posistion(i, Skill_4)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iSkill_4 = iValue;

		iValue = ThirdFile.Search_Posistion(i, Skill_5)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iSkill_5 = iValue;

		iValue = ThirdFile.Search_Posistion(i, TypeOfBus)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_iBusType = iValue;

		iValue = ThirdFile.Search_Posistion(i, PKMode)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_PKMode = iValue;

		iValue = ThirdFile.Search_Posistion(i, MinValidFollowDist)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_MinValidFollowDist = iValue;

		iValue = ThirdFile.Search_Posistion(i, MaxValidFollowDist)->iValue;
		g_BusAttrExTbl.m_TableExt[iType].m_MaxValidFollowDist = iValue;

		g_BusAttrExTbl.m_TableExt[iType].m_Used = TRUE;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::LoadMonsterAITable()
{
	__GUARD__ 
		
	Configer	ini(FILE_MONSTER_BASE_BEHAVIOR);

	g_MonsterBehaviorTab.m_Count = ini.Get_Property_Int("INFO", "AINUMBER");
	KCheck(g_MonsterBehaviorTab.m_Count >= 0 && g_MonsterBehaviorTab.m_Count < MAXAI_NUMBER);

	for(int32 i = 0; i < g_MonsterBehaviorTab.m_Count; i++)
	{
		for(int32 j = 0; j < BHVPARAM_NUMBER; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	szSection[256], szName[256];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			sprintf(szSection, "AI%d", i);
			sprintf(szName, "AIPARAM%d", j);

			if(6 == j) g_MonsterBehaviorTab.m_Table[i][j] = 2000;
			g_MonsterBehaviorTab.m_Table[i][j] = ini.Get_Property_Int(szSection, szName);
			if(0 == j && -1 != g_MonsterBehaviorTab.m_Table[i][j]) g_MonsterBehaviorTab.m_Table[i][j] = 1000;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::LoadMonsterSkillTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	enum MonsterSkillIndex
	{
		MSI_Index				= 0,
		MSI_SkillIndex				= 1,
		MSI_WeaponID				= 3,
		MSI_SkillID				= 4
	};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_MONSTER_SKILL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= MonsterWeaponAndSkillTable::MWAST_MAX_NUM);
	if(MonsterWeaponAndSkillTable::MWAST_MAX_NUM < iTableCount)
	{
		return;
	}

	g_MonsterWeaponAndSkill.m_Count = iTableCount;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne	oSplitL1;
	SplitStringLevelTwo	oSplitL2;
	const char		*pSplitString = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iIndex = ThirdFile.Search_Posistion(i, MSI_Index)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_MonsterWeaponAndSkill.m_aWeaponSkill[iIndex].m_iIndex = iIndex;
		g_MonsterWeaponAndSkill.m_aWeaponSkill[iIndex].m_iWeaponID = ThirdFile.Search_Posistion
			(
				i,
				MSI_WeaponID
			)->iValue;
		pSplitString = ThirdFile.Search_Posistion(i, MSI_SkillIndex)->pString;
		oSplitL1.Reset();
		oSplitL2.Reset();
		oSplitL1.Init('|', &oSplitL2);
		oSplitL2.Init('~', NULL);
		oSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = oSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(MonsterWeaponAndSkillTable::MWAST_MAX_NUM >= iLineCount);
		if(MonsterWeaponAndSkillTable::MWAST_MAX_NUM < iLineCount)
		{
			break;
		}

		for(int32 iLine = 0; iLine < iLineCount; ++iLine)
		{
			g_MonsterWeaponAndSkill.m_aWeaponSkill[iIndex].m_aSkillLevelIndex[iLine] = atoi(oSplitL2.GetResultLine(iLine)) - 1;
		}

		g_MonsterWeaponAndSkill.m_aWeaponSkill[iIndex].m_iSkillLevelIndexCount = iLineCount;

		for(int32 j = 0; j < MonsterWeaponAndSkill::MWAS_MAX_LEVEL; ++j)
		{
			g_MonsterWeaponAndSkill.m_aWeaponSkill[iIndex].m_aSkillLevel[j] = ThirdFile.Search_Posistion
				(
					i,
					MSI_SkillID + j
				)->iValue;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TableInit_Map_Monster::LoadMonsterSpeakTable()
{
	__GUARD__
#define BASENUM (1000)
	TABFile ThirdFile(0);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_NPC_CHAT);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	nLastID = 0, nNewID = 0, nIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		nNewID = ThirdFile.Search_Posistion(i, 0)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char	*pString = ThirdFile.Search_Posistion(i, 1)->pString;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!nLastID)
		{
			g_MonsterSpeakTab.m_TypeCount++;
			g_MonsterSpeakTab.m_NumberOfType[nIndex]++;
		}
		else if(nLastID && nLastID / BASENUM == nNewID / BASENUM)
		{
			g_MonsterSpeakTab.m_NumberOfType[nIndex]++;
		}
		else
		{
			nIndex++;
			g_MonsterSpeakTab.m_TypeCount++;
			g_MonsterSpeakTab.m_NumberOfType[nIndex]++;
		}

		g_MonsterSpeakTab.m_Table[i].nSpeakID = nNewID;
		memset((void *) (g_MonsterSpeakTab.m_Table[i].szSpeakContent), 0, MAX_MONSTERSPEAK_CONTENT);
		memcpy((void *) (g_MonsterSpeakTab.m_Table[i].szSpeakContent), pString, sizeof(pString));
		g_MonsterSpeakTab.m_Table[i].nSpeakID = nNewID;
		g_MonsterSpeakTab.m_Count++;
		nLastID = nNewID;
	}

	__UNGUARD__
}

// 随机怪物表
void TableInit_Map_Monster::LoadRandomMonster()
{	
	__GUARD__ 

enum Monster_Tab
{
	Monster_Tab_Index,
	Monster_Tab_Guid,
	Monster_Tab_Type,
	Monster_Tab_Obj_id,
	Monster_Tab_Camp_id,
	Monster_Tab_Name,
	Monster_Tab_Title,
	Monster_Tab_Pos_x,
	Monster_Tab_Pos_z,
	Monster_Tab_Dir,
	Monster_Tab_Script_id,
	Monster_Tab_Respawn_time,
	Monster_Tab_Group_id,
	Monster_Tab_Team_id,
	Monster_Tab_Base_ai,
	Monster_Tab_Ai_file,
	Monster_Tab_Patrol_id,
	Monster_Tab_Shop0,
	Monster_Tab_Shop1,
	Monster_Tab_Shop2,
	Monster_Tab_Shop3,
	Monster_Tab_ReputationID,
	Monster_Tab_Level,
	Monster_Tab_SceneID,
	Monster_Tab_GroupID,
};
#define DIR_STEP					__PI / 18.f
#define MAX_RANDOMMONSTER_NUMBER	16384

	TABFile ThirdFile(0);

	BOOL	ret = ThirdFile.OpenFromTXT(FILE_RANDOM_MONSTER);
	int32	iTableCount = ThirdFile.GetRecordsNum();
			
	KCheckEx(iTableCount < MAX_RANDOMMONSTER_NUMBER, "程序初始化读取随机怪表格记录超过上限");

	for (int32 i = 0; i < iTableCount; i++)
	{
		MapID_t iSceneID = ThirdFile.Search_Posistion(i, Monster_Tab_SceneID)->iValue;
		ID_t iGroupID = ThirdFile.Search_Posistion(i, Monster_Tab_GroupID)->iValue;

		KCheckEx(iSceneID >= 0 && iSceneID < MAX_SCENE, "程序初始化读取随机怪场景号非法");
		KCheckEx(iGroupID >= 0 && iGroupID < RANDOM_PERMAP_MAXGROUP, "读取随机怪组号非法");

		// 没这个图的配置，全部创建新的
		if (NULL == g_pRandomMonsterConfig[iSceneID])
		{
			g_pRandomMonsterConfig[iSceneID] = new RandomMonsterMap;
			KCheck(g_pRandomMonsterConfig[iSceneID]);

			g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID] = new RandomMonsterGroup;
			KCheck(g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]);
		}
		// 没这个组的配置，创建新的组
		else if (NULL == g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID])
		{
			g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID] = new RandomMonsterGroup;
		}
		
		KCheckEx(g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]->m_uMonsterCount < RANDOM_PERGROUP_MAXMONSTER, "程序初始化单组怪物数量配置超过上限");

		uint32 uMonsterCount = g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]->m_uMonsterCount;

		// 为这个新的该组成员单位创建数据空间
		g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]->m_paMonster[uMonsterCount] = new RandomMonsterConfig;
		KCheck(g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]->m_paMonster[uMonsterCount]);

		// 开始进行表格内容读取赋值到这个成员
		RandomMonsterConfig &rMonsterConfig = *g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]->m_paMonster[uMonsterCount];

		rMonsterConfig.m_iSceneID = iSceneID;
		rMonsterConfig.m_iGroupID = iGroupID;
		rMonsterConfig.m_MonsterConfig.m_GUID = ThirdFile.Search_Posistion(i, Monster_Tab_Guid)->iValue;
		rMonsterConfig.m_MonsterConfig.m_uDataID = ThirdFile.Search_Posistion(i, Monster_Tab_Type)->iValue;

		SMonsterExtAttr *pExtAttr = g_MonsterPropertyExTab.GetExtAttr(rMonsterConfig.m_MonsterConfig.m_uDataID);
		KCheckEx(pExtAttr, "程序初始化配置单位 type 在 mon_attr_ex.tab 表中不存在");

		strncpy
			(
			rMonsterConfig.m_MonsterConfig.m_szName,
			ThirdFile.Search_Posistion(i, Monster_Tab_Name)->pString,
			sizeof(rMonsterConfig.m_MonsterConfig.m_szName) - 1
			);
		strncpy
			(
			rMonsterConfig.m_MonsterConfig.m_szTitle,
			ThirdFile.Search_Posistion(i, Monster_Tab_Title)->pString,
			sizeof(rMonsterConfig.m_MonsterConfig.m_szTitle) - 1
			);

		rMonsterConfig.m_MonsterConfig.m_Pos.m_fX = ThirdFile.Search_Posistion(i, Monster_Tab_Pos_x)->fValue;
		rMonsterConfig.m_MonsterConfig.m_Pos.m_fZ = ThirdFile.Search_Posistion(i, Monster_Tab_Pos_z)->fValue;

		rMonsterConfig.m_MonsterConfig.m_Dir = (float)ThirdFile.Search_Posistion(i, Monster_Tab_Dir)->iValue;
		rMonsterConfig.m_MonsterConfig.m_Dir = (float)(rMonsterConfig.m_MonsterConfig.m_Dir) * DIR_STEP + __HALF_PI;
		if(rMonsterConfig.m_MonsterConfig.m_Dir > 2.f * __PI)
		{
			rMonsterConfig.m_MonsterConfig.m_Dir -= 2.f * __PI;
		}

		rMonsterConfig.m_MonsterConfig.m_ObjGUID = ThirdFile.Search_Posistion(i, Monster_Tab_Obj_id)->iValue;

		if (NPC_QUEST *pQuest = g_NpcQuestTbl.Get(rMonsterConfig.m_MonsterConfig.m_ObjGUID))
		{
			rMonsterConfig.m_MonsterConfig.m_idScript = pQuest->m_ScriptID;
		}
		else
		{
			rMonsterConfig.m_MonsterConfig.m_idScript = ThirdFile.Search_Posistion(i, Monster_Tab_Script_id)->iValue;
		}

		KCheckEx(rMonsterConfig.m_MonsterConfig.m_idScript <= 0 || rMonsterConfig.m_MonsterConfig.m_idScript > 100000, "程序初始化单位获取脚本ID范围非法");

		rMonsterConfig.m_MonsterConfig.m_RespawnTime = ThirdFile.Search_Posistion(i, Monster_Tab_Respawn_time)->iValue;
		rMonsterConfig.m_MonsterConfig.m_uGroupID = ThirdFile.Search_Posistion(i, Monster_Tab_Group_id)->iValue;
		rMonsterConfig.m_MonsterConfig.m_uTeamID = ThirdFile.Search_Posistion(i, Monster_Tab_Team_id)->iValue;
		rMonsterConfig.m_MonsterConfig.m_BaseAI = ThirdFile.Search_Posistion(i, Monster_Tab_Base_ai)->iValue;

		rMonsterConfig.m_MonsterConfig.m_BaseAI = ThirdFile.Search_Posistion(i, Monster_Tab_Base_ai)->iValue;
		if(rMonsterConfig.m_MonsterConfig.m_BaseAI == -1)
		{
			rMonsterConfig.m_MonsterConfig.m_BaseAI = pExtAttr->m_BaseAI;
		}

		rMonsterConfig.m_MonsterConfig.m_ExtAIScript = ThirdFile.Search_Posistion(i, Monster_Tab_Ai_file)->iValue;
		if(rMonsterConfig.m_MonsterConfig.m_ExtAIScript == -1)
		{
			rMonsterConfig.m_MonsterConfig.m_ExtAIScript = pExtAttr->m_ExtAI;
		}

		rMonsterConfig.m_MonsterConfig.m_nPatrolID = ThirdFile.Search_Posistion(i, Monster_Tab_Patrol_id)->iValue;
		rMonsterConfig.m_MonsterConfig.m_nShop[0] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop0)->iValue;
		rMonsterConfig.m_MonsterConfig.m_nShop[1] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop1)->iValue;
		rMonsterConfig.m_MonsterConfig.m_nShop[2] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop2)->iValue;
		rMonsterConfig.m_MonsterConfig.m_nShop[3] = ThirdFile.Search_Posistion(i, Monster_Tab_Shop3)->iValue;
		rMonsterConfig.m_MonsterConfig.m_nLevel = ThirdFile.Search_Posistion(i, Monster_Tab_Level)->iValue;
		rMonsterConfig.m_MonsterConfig.m_LeaderID = -1;
		rMonsterConfig.m_MonsterConfig.m_bPet = FALSE;
		rMonsterConfig.m_MonsterConfig.m_CampID = ThirdFile.Search_Posistion(i, Monster_Tab_Camp_id)->iValue;

		// 增加本组计数
		g_pRandomMonsterConfig[iSceneID]->m_paMonsterGroup[iGroupID]->m_uMonsterCount++;
	}

	__UNGUARD__
}