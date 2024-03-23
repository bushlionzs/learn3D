/*$T MapServer/Server/Skill/SkillManager.cpp GC 1.140 10/10/07 10:07:53 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Skill_Manager.h"
#include "Skill_All.h"
#include "TAB.h"
#include "StructDB.h"
#include "BaseTool.h"
#include "FileDef.h"

using namespace			TAB;

SkillManager			*g_pSkillManager = NULL;

const char *SkillManager::	m_VigorExpTablePath = "../../server_resources/Public/Config/AbilityLevelUp/";
const char *SkillManager::	m_VigorExpTableName[SkillManager::EXP_TABLE_NUM] =
{
	"zhiyao.tab",
	"gongyi.tab",
	"zhuzao.tab",
	"zhongyuan_caoyao.tab",
	"alabo_yishu.tab",
	"tujue_duanzao.tab",
	"bosi_gongyi.tab",
	"yindu_zhubao.tab",
	"luoma_gongcheng.tab",
	"xiyu_bianzhi.tab",
	"caiji_caoyao.tab",
	"caiji_kuangshi.tab",
	"buzhuo_kunchong.tab",
	"assistant.tab"
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SkillManager::InitPrescriptionList(const char *filename)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(0);
	bool			ret = ThirdFile.OpenFromTXT(filename);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!ret) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount < MAX_SKILL_PRESCRIPTION_NUM);

	/*~~~~~~~~~~~~~~~*/
	int32	iValue = 0;
	int32	Column = 0;
	int32	i;
	/*~~~~~~~~~~~~~~~*/

	for(i = 0; i < iTableCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_SKILL_PRESCRIPTION_DATA	*pData;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pData = &(m_pPrescriptionList->m_Table[i]);

		pData->m_PrescriptionID = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_PrescriptionID)->iValue;

		iValue = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_CompoundID)->iValue;
		if(iValue != INVALID_ID && iValue > 0)
		{
			pData->m_CompoundID = iValue;
		}
		else
		{
			pData->m_CompoundID = INVALID_ID;
		}

		pData->m_CompoundNum = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_CompoundNum)->iValue;
		pData->m_SkillID = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_SkillID)->iValue;
		pData->m_SkillLevel = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_AbilityLevel)->iValue;

		Column = _SKILL_PRESCRIPTION_DATA::Tab_Stuff_BEGIN;

		for(int32 j = 0; j < MAX_PRESCRIPTION_STUFF; ++j)
		{
			iValue = ThirdFile.Search_Posistion(i, Column++)->iValue;
			if(iValue != INVALID_ID && iValue > 0)
			{
				pData->m_Stuff_ID[j] = iValue;
				pData->m_Stuff_Num[j] = ThirdFile.Search_Posistion(i, Column++)->iValue;
			}
			else
			{
				pData->m_Stuff_ID[j] = INVALID_ID;
			}
		}

		pData->m_Attr_Vigor = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_Attr_VIGOR)->iValue;

		pData->m_ColddownTime = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_ColddownTime)->iValue;

		iValue = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_ToolID)->iValue;
		if(iValue != INVALID_ID && iValue > 0)
		{
			pData->m_ToolID = iValue;
		}
		else
		{
			pData->m_ToolID = INVALID_ID;
		}

		pData->m_ColddownID = (CooldownID_t) ThirdFile.Search_Posistion
			(
			i,
			_SKILL_PRESCRIPTION_DATA::Tab_ColddownID
			)->iValue;

		pData->m_ExpIncrement = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_ExpIncrement)->iValue;

		pData->m_nOperaTime = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_OperaTime)->iValue;
		pData->m_ScriptID = ThirdFile.Search_Posistion(i, _SKILL_PRESCRIPTION_DATA::Tab_SCRIPTID)->iValue;
	}

	m_pPrescriptionList->m_Count = i;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SkillManager::Init()
{
	/*~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	ret;
	/*~~~~~~~~~~~~~~~~*/

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load BaseSkill Exp Table...");
	ret = InitSkillExpTable();
	KCheckEx(ret, "Load BaseSkill Exp Table failed.");
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load BaseSkill Exp Table Done.");

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load BaseSkill...");
	ret = InitSkill(FILE_ABILITY);
	KCheckEx(ret, "Init BaseSkill failed.");
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load BaseSkill Done.");

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load BaseSkill Prescription...");
	ret = InitPrescriptionList(FILE_PRESCRIPTION);
	KCheckEx(ret, "Init Prescription failed.");
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Load BaseSkill Prescription Done.");

	return TRUE;

	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
BaseSkill *SkillManager::GetAbility(SpellID_t aid)
{
	/*~~~~~~~~*/
	int32	idx;
	/*~~~~~~~~*/

	idx = (int32) aid;
	if(idx <= SKILL_CLASS_INVALID || idx >= SKILL_CLASS_SIZE)
	{
		KCheck(idx > SKILL_CLASS_INVALID && idx < SKILL_CLASS_SIZE);
		return NULL;
	}

	return m_pSkill[idx];
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */

SkillManager::SkillManager()
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	m_pPrescriptionList = new SSkillPrescriptionTab;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SkillManager::~SkillManager()
{
	/*~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 i = 0;
	/*~~~~~~~~~~~~~~~~~~*/

	for(; i < MAX_SKILL; ++i)
	{
		if(m_pSkill[i] != NULL)
		{
			KSafeDelete(m_pSkill[i]);
		}
	}

	for(i = 0; i < EXP_TABLE_NUM; ++i)
	{
		if(m_pSkillExpTbl[i] != NULL)
		{
			KSafeDelete(m_pSkillExpTbl[i]);
		}
	}

	KSafeDelete(m_pPrescriptionList);

	__UNGUARD__
}


BOOL SkillManager::InitSkill_NewSkill_i(int32	nAbilityID, BaseSkill& rTempAbility)
{
	switch(nAbilityID)
	{
	case SKILL_CLASS_INVALID:
		return FALSE;

	case SKILL_CLASS_PHARMACY:
	case SKILL_CLASS_ARTWORK:
	case SKILL_CLASS_THICKICE:
	case SKILL_CLASS_INSECTCULTURING:
	case SKILL_CLASS_POISON:
	case SKILL_CLASS_INCANTATION:
	case SKILL_CLASS_ALCHEMY:
	case SKILL_CLASS_THAUMATURGY:
	case SKILL_CLASS_ENGINEERING:
	case SKILL_CLASS_CAOYAO:
	case SKILL_CLASS_YISHU:
	case SKILL_CLASS_SMITHING:
	case SKILL_CLASS_CRAFT:
	case SKILL_CLASS_GEM:
	case SKILL_CLASS_PRJ:
	case SKILL_CLASS_MESH:
		m_pSkill[nAbilityID] = new SkillGenericCompound(rTempAbility);
		KCheck(m_pSkill[nAbilityID]);
		break;

	case SKILL_CLASS_FOUNDRY:
		m_pSkill[SKILL_CLASS_FOUNDRY] = new SkillFoundry(rTempAbility);
		KCheck(m_pSkill[SKILL_CLASS_FOUNDRY]);
		break;

	case SKILL_CLASS_FIGHTGHOST:
	case SKILL_CLASS_SEARCHTSTORE:
	case SKILL_CLASS_PROCESSING:
	case SKILL_CLASS_GATHER_CAOYAO:
	case SKILL_CLASS_GATHER_ORE:
	case SKILL_CLASS_GATHER_INSECT:
		m_pSkill[nAbilityID] = new SkillGenericGather(rTempAbility);
		KCheck(m_pSkill[nAbilityID]);
		break;

	case SKILL_CLASS_NOUSE:
	case SKILL_CLASS_TRADE:
	case SKILL_CLASS_HAGGLE:
	case SKILL_CLASS_EXCESSPROFIT:
	case SKILL_CLASS_PHARMACOLOGY:
	case SKILL_CLASS_REGIMEN:
	case SKILL_CLASS_BUDDHOLOGY:
	case SKILL_CLASS_FIREMAKING:
	case SKILL_CLASS_BEGSKILL:
	case SKILL_CLASS_ICEMAKING:
	case SKILL_CLASS_VENATIONFORMULA:
	case SKILL_CLASS_INSECTENTICING:
	case SKILL_CLASS_MENTALTELEPATHY:
	case SKILL_CLASS_TAOISM:
	case SKILL_CLASS_BODYBUILDING:
		m_pSkill[nAbilityID] = new SkillGeneric(rTempAbility);
		KCheck(m_pSkill[nAbilityID]);
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SkillManager::InitSkill(const char *filename)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TABFile	ThirdFile(UINT_MAX);

	bool ret = ThirdFile.OpenFromTXT(filename);
	if(!ret) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iColumnCount = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iColumnCount);
	KCheck(iTableCount);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BaseSkill	TempAbility;
	BaseSkill	&rTempAbility = TempAbility;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		rTempAbility.SetSkillID(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_ID)->iValue);
		rTempAbility.SetSkillName(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_NAME)->pString);
		rTempAbility.SetLevelDemand(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_LEVEL_DEMAND)->iValue);
		rTempAbility.SetSkillLevelLimit(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_LEVEL_LIMIT)->iValue);
		rTempAbility.SetOperationTime(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_OPERATION_TIME)->iValue);
		rTempAbility.SetOperationToolID(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_OPERATION_TOOL)->iValue);
		rTempAbility.SetPlatformDistance(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_PLATFORM_DISTANCE)->fValue);
		rTempAbility.SetPlatformID(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_PLATFORM)->iValue);
		rTempAbility.SetOperationActionID(ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_OPERATION_ACTION)->iValue);
		strncpy
		(
			rTempAbility.GetExpTableName(),
			ThirdFile.Search_Posistion(i, BaseSkill::TEMPLATE_SKILL_EXP_TABLE)->pString,
			BaseSkill::EXPTABLE_NAME_LENGTH
		);

		for(int32 j = 0; j < EXP_TABLE_NUM; ++j)
		{
			if(0 == strcmp(rTempAbility.GetExpTableName(), m_VigorExpTableName[j]))
			{
				rTempAbility.SetExpTableIndex(j);
				rTempAbility.SetExpTable(m_pSkillExpTbl[j]);
				break;
			}
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nAbilityID = rTempAbility.GetSkillID();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		BOOL bRet = InitSkill_NewSkill_i(nAbilityID, rTempAbility);
		if(bRet == FALSE)
			continue;

		rTempAbility.Clear();
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SkillManager::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pPrescriptionList = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(m_pSkillExpTbl, 0, EXP_TABLE_NUM * sizeof(_SkillExpTable *));
	memset(m_pSkill, 0, MAX_SKILL * sizeof(BaseSkill *));

	__UNGUARD__
}

#define EXP_TABLE_BUFF_LEN	128

BOOL SkillManager::InitSkillExpTable_i(uint32 j)
{
	char buff[EXP_TABLE_BUFF_LEN];

	memset(buff, 0, EXP_TABLE_BUFF_LEN);
	strcat(buff, m_VigorExpTablePath);
	strcat(buff, m_VigorExpTableName[j]);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TABFile AbilityExpTableFile(0);
	bool	ret = AbilityExpTableFile.OpenFromTXT(buff);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(ret, buff);
	if(!ret) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = AbilityExpTableFile.GetRecordsNum();
	int32	iTableColumn = AbilityExpTableFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheckEx(iTableCount >= 0 && iTableCount <= _SkillExpTable::MAX_LEVEL_NUM, buff);

	KCheckEx(iTableColumn == _SkillExpTable::ETE_ElementNum, "文件列数不匹配");

	m_pSkillExpTbl[j] = new _SkillExpTable;

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pSkillExpTbl[j]->m_Level[i] = (uchar) AbilityExpTableFile.Search_Posistion
			(
			i,
			_SkillExpTable::ETE_LEVEL
			)->iValue;
		m_pSkillExpTbl[j]->m_CostMoney[i] = AbilityExpTableFile.Search_Posistion
			(
			i,
			_SkillExpTable::ETE_MONEY
			)->iValue;
		m_pSkillExpTbl[j]->m_CostExp[i] = AbilityExpTableFile.Search_Posistion
			(
			i,
			_SkillExpTable::ETE_EXP
			)->iValue;
		m_pSkillExpTbl[j]->m_UpperLimmitExp[i] = AbilityExpTableFile.Search_Posistion
			(
			i,
			_SkillExpTable::ETE_UPPER_EXP
			)->iValue;
		m_pSkillExpTbl[j]->m_PlayerLevel[i] = (uchar) AbilityExpTableFile.Search_Posistion
			(
			i,
			_SkillExpTable::ETE_PLAYER_LEVEL
			)->iValue;
		m_pSkillExpTbl[j]->m_NeedTitle[i] = AbilityExpTableFile.Search_Posistion
			(
			i,
			_SkillExpTable::ETE_NEED_TITLE
			)->iValue;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SkillManager::InitSkillExpTable()
{
	__GUARD__

	for(int32 j = 0; j < EXP_TABLE_NUM; ++j)
	{
		InitSkillExpTable_i(j);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SkillManager::GetUpperLimitExp(SpellID_t id, Player const *pPlayer) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BaseSkill	*ability = g_pSkillManager->GetAbility(id);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ability);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		index = ability->GetExpTableIndex();
	_SkillExpTable	*abilityExpTable = GetSkillExpTbl(index);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(abilityExpTable);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	level = pPlayer->GetAbilityLevel(id);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(level >= 1 && level <= _SkillExpTable::MAX_LEVEL_NUM)
	{
		return abilityExpTable->GetUpperLimmitExp(level - 1);
	}

	return 0;
	__UNGUARD__ return 0;
}
