/*$T MapServer/Server/Obj/HumanAssistantClass/HumanSkillUpgrad.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "HumanSkillUpgrad.h"
#include "gameobject/Player.h"
#include "SpellDataLoader.h"
#include "TabDefine.h"
#include "skill/Spell_EffectInterface.h"
#include "data/data_manager.h"
#include "item/Item_Interface.h"
#include "Archive/PlayerDB.h"
#include "Share/TAB/TabDefine_Map_Skill.h"
#include "net/messages/SCSkillUpgrade.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

PlayerSkillUpgrade::PlayerSkillUpgrade()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PlayerSkillUpgrade::~PlayerSkillUpgrade()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pHuman = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iSkillID = INVALID_ID;
	m_iLevel = INVALID_ID;

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL PlayerSkillUpgrade::IsEnoughMoneyEx
(
 eCURRENCY_UNIT		&nPriceType,
 int32		nPrice
 )
{
	__GUARD__

	BOOL bRet = TRUE;

	KCheck(m_pHuman);
	if (NULL == m_pHuman)
	{
		return FALSE;
	}

	switch(nPriceType)
	{
	case CU_SILLER:
		{
			if(m_pHuman->GetSiller() < nPrice)
			{
				bRet = FALSE;
			}

			nPriceType = CU_SILLER;
		}
		break;

	case CU_BINDSILLER:
		{
			if(m_pHuman->GetSillerMode() == SILLER_CASH)
			{
				if(m_pHuman->GetSiller() < nPrice)
				{
					bRet = FALSE;
				}
				else
					nPriceType = CU_SILLER;
			}
			else
			{
				if(m_pHuman->GetBindSiller() < nPrice)
				{
					if(m_pHuman->GetSiller() < nPrice)
					{
						bRet = FALSE;
					}
					else
						nPriceType = CU_SILLER;
				}
				else
					nPriceType = CU_BINDSILLER;
			}
		}
		break;

	case CU_GOLD:
		{
			if(m_pHuman->GetCharGold() < nPrice)
			{
				bRet = FALSE;
			}

			nPriceType = CU_GOLD;
		}
		break;

	case CU_BINDGOLD:
		{
			if(m_pHuman->GetGoldMode() == GOLD_CASH)
			{
				if(m_pHuman->GetCharGold() < nPrice)
				{
					bRet = FALSE;
				}
				else
					nPriceType = CU_GOLD;
			}
			else
			{
				if(m_pHuman->GetBindGold() < nPrice)
				{
					if(m_pHuman->GetCharGold() < nPrice)
					{
						bRet = FALSE;
					}
					else
						nPriceType = CU_GOLD;
				}
				else
					nPriceType = CU_BINDGOLD;
			}
		}
		break;

	case CU_CREDIT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nTotal = m_pHuman->GetShengWang() - nPrice;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nTotal < 0)
			{
				bRet = FALSE;
			}
		}
		break;

	case CU_HONOR:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nTotal = m_pHuman->GetHonor() - nPrice;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nTotal < 0)
			{
				bRet = FALSE;
			}
		}
		break;

	case CU_COUNTRYCREDIT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nTotal = m_pHuman->GetRongYu() - nPrice;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nTotal < 0)
			{
				bRet = FALSE;
			}
		}
		break;

	case CU_GOODBAD:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nTotal = m_pHuman->Get_Property_GoodBadValue() - nPrice;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(nTotal < 0)
			{
				bRet = FALSE;
			}
		}
		break;

	case CU_FEASTSCOR:
		{
			int32 nTotal = m_pHuman->GetFeastScore() - nPrice;

			if( nTotal < 0)
			{
				bRet = FALSE;
			}// if
		}
		break;

	default:
		break;
	}

	return bRet;

	__UNGUARD__ return 1;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
void PlayerSkillUpgrade::SpendMoney(eCURRENCY_UNIT &nPriceType, uint32 nPrice)
{
	__GUARD__

	KCheck(m_pHuman);
	if (NULL == m_pHuman)
	{
		return;
	}

	switch(nPriceType)
	{
		case CU_SILLER:
			{
				m_pHuman->ReduceMoney(CU_SILLER, nPrice);
			}
			break;

		case CU_BINDSILLER:
			{
				m_pHuman->DecreaseSiller(nPrice);
			}
			break;

		case CU_GOLD:
			{
				m_pHuman->ReduceCharGold(nPrice);
			}
			break;

		case CU_BINDGOLD:
			{
				m_pHuman->DecreaseBindGold(nPrice);
			}
			break;

		case CU_HONOR:
			{
				m_pHuman->SetHonor(m_pHuman->GetHonor() - nPrice);
			}
			break;

		case CU_CREDIT:
			{
				m_pHuman->SetShengWang(m_pHuman->GetShengWang() - nPrice);
			}
			break;

		case CU_COUNTRYCREDIT:
			{
				m_pHuman->SetRongYu(m_pHuman->GetRongYu() - nPrice);
			}
			break;

		case CU_GOODBAD:
			{
				m_pHuman->Set_Property_GoodBadValue(m_pHuman->Get_Property_GoodBadValue() - nPrice);
			}
			break;

		default:
			{
			}
			break;
	}

	__UNGUARD__
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::HumanSkillLevelUp(const Player *pPlayer, SpellID_t iSkillID, int32 iLevel, int32 iType)
{
	__GUARD__;

	InitAttr(pPlayer, iSkillID, iLevel);
	
	eOPTRESULT	result = OR_ERROR;
	if (TYPE_SKILL ==iType)
	{
		result = CheckCondition();
	}
	else if (TYPE_INHERENCE == iType)
	{
		result = CheckConditionforInherence();
	}

	if(OR_OK != result)
	{
		m_pHuman->SendOperateResultMsg(result, 0);
		SendFailedSkillLevelupMsg(iType);
		return;
	}

	if (TYPE_SKILL ==iType)
	{
		DepleteHumanAttr();
	}
	else if (TYPE_INHERENCE == iType)
	{
		DepleteHumanAttrforInherence();
	}

	UpgradeLevel();
	SendSuccessSkillLevelupMsg(iType);

	StartPassiveSkill(iSkillID, pPlayer);
	return;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL PlayerSkillUpgrade::HumanSkillLevelUpNoCheck(const Player *pPlayer, SpellID_t iSkillID, int32 iLevel)
{
	__GUARD__;

	InitAttr(pPlayer, iSkillID, iLevel);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	eOPTRESULT	result = CheckCondition2();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OR_OK != result)
	{
		return FALSE;
	}

	/*
	 * DepleteHumanAttr();
	 */
	UpgradeLevel();
	SendSuccessSkillLevelupMsg(TYPE_SKILL);

	StartPassiveSkill(iSkillID, pPlayer);
	return TRUE;

	__UNGUARD__;

    return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 PlayerSkillUpgrade::GetHumanSkillLevel(const Player *pPlayer, SpellID_t iSkillID)
{
	__GUARD__;

	InitAttr(pPlayer, iSkillID, -1);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return -1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	&oOwnSkill = *(pSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return oOwnSkill.m_nLevel;

	__UNGUARD__;

    return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::CheckCondition()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return OR_HAVENOT_LEARN_THIS_SKILL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	&oOwnSkill = *(pSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iLevel = oOwnSkill.m_nLevel;
	if(m_iLevel < 0)
	{
		m_iLevel = 0;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	eOPTRESULT	result;
	/*~~~~~~~~~~~~~~~~~~~*/

	result = CheckSkillStudyCondition();
	ORT_TestResult(result);
	result = IsEnoughHumanLevel();
	ORT_TestResult(result);
	result = IsOccupationMatch();
	ORT_TestResult(result);
	result = IsSkillClassSpendEnoughPosints();
	ORT_TestResult(result);
	result = IsEnoughParentSkillLevel();
	ORT_TestResult(result);
	result = IsEnoughSkillPoints();
	ORT_TestResult(result);
	result = IsEnoughMoney();
	ORT_TestResult(result);
	result = IsEnoughExp();
	ORT_TestResult(result);
	result = IsHadEnoughItem1();
	ORT_TestResult(result);
	result = IsHadEnoughItem2();
	ORT_TestResult(result);
	result = IsHadEnoughItem3();
	ORT_TestResult(result);

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::CheckCondition2()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return OR_HAVENOT_LEARN_THIS_SKILL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	&oOwnSkill = *(pSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iLevel = oOwnSkill.m_nLevel;
	if(m_iLevel < 0)
	{
		m_iLevel = 0;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	eOPTRESULT	result;
	/*~~~~~~~~~~~~~~~~~~~*/

	result = CheckSkillStudyCondition();
	ORT_TestResult(result);

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
eOPTRESULT PlayerSkillUpgrade::CheckConditionforInherence()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return OR_HAVENOT_LEARN_THIS_SKILL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	&oOwnSkill = *(pSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iLevel = oOwnSkill.m_nLevel;
	if(m_iLevel < 0)
	{
		m_iLevel = 0;
	}

	assert(false);

	return OR_OK;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteHumanAttr()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	DepleteSkillPoints();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	DepleteMoney();
	DepleteExp();
	DepleteItem1();
	DepleteItem2();
	DepleteItem3();
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void PlayerSkillUpgrade::DepleteHumanAttrforInherence()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	&oOwnSkill = *(pSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iLevel = oOwnSkill.m_nLevel;
	if(m_iLevel < 0)
	{
		m_iLevel = 0;
	}


	assert(false);

	return;
	__UNGUARD__
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::UpgradeLevel()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return;
	}

	m_pHuman->SetSpellLevel(m_iSkillID, pSkill->m_nLevel + 1);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::SendSuccessSkillLevelupMsg(int32 iType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	*pSkill = m_pHuman->GetSpell(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkill)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~*/
	SCSkillUpgrade* packet = new SCSkillUpgrade;
	/*~~~~~~~~~~~~~~~~*/

	packet->setSkillId(m_iSkillID);
	packet->setSkillLevel(pSkill->m_nLevel);
	packet->setSuccess(TRUE);
	packet->setType(iType);

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::SendFailedSkillLevelupMsg(int32 iType)
{
	/*~~~~~~~~~~~~~~~~*/
	SCSkillUpgrade* packet = new SCSkillUpgrade;
	/*~~~~~~~~~~~~~~~~*/

	packet->setSkillId(m_iSkillID);
	packet->setSkillLevel(-1);
	packet->setSuccess(FALSE);
	packet->setType(iType);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsEnoughHumanLevel()
{
	__GUARD__;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHumanLevel = m_pHuman->GetLevel();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iHumanLevel >= g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iPLayerLevelRequire[m_iLevel])
	{
		return OR_OK;
	}

	return OR_NEED_HIGH_LEVEL;

	__UNGUARD__ return OR_NEED_HIGH_LEVEL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsEnoughSkillPoints()
{
	__GUARD__;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iSkillPoints = m_pHuman->GetRemainSpellPoints();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iSkillPoints >= g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendPoints[m_iLevel])
	{
		return OR_OK;
	}

	return OR_DONOT_HAVE_ENOUGH_SKILL_POINT;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsOccupationMatch()
{
	__GUARD__;

	if(g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iOccupationRequire == INVALID_ID)
	{
		return OR_OK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iProfession = m_pHuman->GetProfession();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iProfession == g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iOccupationRequire)
	{
		return OR_OK;
	}

	return OR_INVALID_SKILL;
	__UNGUARD__ return OR_INVALID_SKILL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsEnoughParentSkillLevel()
{
	__GUARD__;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iParentSkillID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iParentSkillID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iParentSkillID == INVALID_ID)
	{
		return OR_OK;
	}

	if(m_pHuman && m_pHuman->SpellHaveSkill(iParentSkillID))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const _PLAYER_SPELL	*parentSkill = m_pHuman->GetSpell(iParentSkillID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == parentSkill)
		{
			return OR_HAVENOT_LEARN_PARENT_SKILL;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iParentSkillLevelRequire = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].
			m_iParentSkillLevelRequire[m_iLevel];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(parentSkill->m_nLevel >= iParentSkillLevelRequire)
		{
			return OR_OK;
		}
	}

	return OR_HAVENOT_LEARN_PARENT_SKILL;

	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsEnoughMoney()
{
	__GUARD__;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iMoneyRequire = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendMoney[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!m_pHuman->IsEnoughMoney(iMoneyRequire))
	{
		return OR_NOT_ENOUGH_MONEY;
	}

	return OR_OK;
	__UNGUARD__ return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsEnoughExp()
{
	__GUARD__;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint64	iExp = m_pHuman->GetPlayerExp();
	uint64	iExpRequire = (uint64)
		(g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendExp[m_iLevel]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iExp >= iExpRequire)
	{
		return OR_OK;
	}

	return OR_NO_ENOUGH_EXP;
	__UNGUARD__ return OR_NO_ENOUGH_EXP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::CheckSkillStudyCondition()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_iSkillID <= g_SkillStudyCondition.m_iCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(m_iLevel <= Skill_Study_Condition::MAX_SKILL_LEVEL);
	if(m_iSkillID > g_SkillStudyCondition.m_iCount)
	{
		return OR_CANNOT_FIND_THIS_SKILL_IN_STUDY_TABLE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillTemplate)
	{
		return OR_INVALID_SKILL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iMaxLevel = pSkillTemplate->GetSkillMaxLevel();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_iLevel >= Skill_Study_Condition::MAX_SKILL_LEVEL)
	{
		return OR_THIS_SKILL_IS_MAX_LEVEL;
	}

	if(m_iLevel >= iMaxLevel)
	{
		return OR_THIS_SKILL_IS_MAX_LEVEL;
	}

	return OR_OK;
	__UNGUARD__ return OR_TRY_CATCH_RETURN;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsSkillClassSpendEnoughPosints()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pSkillTemplate != NULL);
	if(pSkillTemplate == NULL)
	{
		return OR_NOT_ENOUGH_STRIKE_POINT;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iSkillClass = pSkillTemplate->GetSkillClass();
	PlayerArchive	*pDB = m_pHuman->GetDB();
	int32		iSkillClassSpendEnoughPosints = pDB->Get_S_SkillPoints(iSkillClass);
	int32		iSkillClassSpendEnoughPosintsRequire = g_SkillStudyCondition.m_aSkillStydy_Condition[
		m_iSkillID].m_iPlayerPointsRequire[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iSkillClassSpendEnoughPosints >= iSkillClassSpendEnoughPosintsRequire)
	{
		return OR_OK;
	}

	return OR_NOT_ENOUGH_STRIKE_POINT;
	__UNGUARD__ return OR_NOT_ENOUGH_STRIKE_POINT;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsHadEnoughItem1()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iItemID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem1ID[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iItemID == INVALID_ID) || (iItemID == 0))
	{
		return OR_OK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHadItemCount = sItemInterface.CalcInventoryItemCount(m_pHuman, iItemID);
	int32	iRequireItemNum = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem1Num[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iHadItemCount >= iRequireItemNum)
	{
		return OR_OK;
	}

	return OR_NOT_ENOUGH_ITEM;

	__UNGUARD__ return OR_NOT_ENOUGH_ITEM;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsHadEnoughItem2()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iItemID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem2ID[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iItemID == INVALID_ID) || (iItemID == 0))
	{
		return OR_OK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHadItemCount = sItemInterface.CalcInventoryItemCount(m_pHuman, iItemID);
	int32	iRequireItemNum = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem2Num[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iHadItemCount >= iRequireItemNum)
	{
		return OR_OK;
	}

	return OR_NOT_ENOUGH_ITEM;

	__UNGUARD__ return OR_NOT_ENOUGH_ITEM;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eOPTRESULT PlayerSkillUpgrade::IsHadEnoughItem3()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iItemID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem3ID[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iItemID == INVALID_ID) || (iItemID == 0))
	{
		return OR_OK;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHadItemCount = sItemInterface.CalcInventoryItemCount(m_pHuman, iItemID);
	int32	iRequireItemNum = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem3Num[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iHadItemCount >= iRequireItemNum)
	{
		return OR_OK;
	}

	return OR_NOT_ENOUGH_ITEM;

	__UNGUARD__ return OR_NOT_ENOUGH_ITEM;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::InitAttr(const Player *pPlayer, SpellID_t iSkillID, int32 iLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pHuman = const_cast<Player *>(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_iSkillID = iSkillID;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteSkillPoints()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iSkillPoints = m_pHuman->GetRemainSpellPoints();
	int32		iSpend = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendPoints[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iSpend > iSkillPoints) iSpend = iSkillPoints;

	m_pHuman->SetRemainSpellPoints(iSkillPoints - iSpend);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteMoney()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		iMoneyRequire = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendMoney[
		m_iLevel];
	m_pHuman->DecreaseSiller(iMoneyRequire);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteExp()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint64	iExp = m_pHuman->GetPlayerExp();
	uint64			iExpRequire = (uint64)
		(g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendExp[m_iLevel]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iExp < iExpRequire) iExpRequire = iExp;

	m_pHuman->SetPlayerExp(iExp - iExpRequire);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteItem1()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iItemID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem1ID[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iItemID == INVALID_ID) || (iItemID == 0))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHadItemCount = sItemInterface.CalcInventoryItemCount(m_pHuman, iItemID);
	int32	iRequireItemNum = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem1Num[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iHadItemCount >= iRequireItemNum);
	if(sItemInterface.EraseBagItemByIndex(nullptr, m_pHuman, iItemID, iRequireItemNum))
	{
	}
	else
	{
		KCheck(FALSE);
	}

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteItem2()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iItemID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem2ID[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iItemID == INVALID_ID) || (iItemID == 0))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHadItemCount = sItemInterface.CalcInventoryItemCount(m_pHuman, iItemID);
	int32	iRequireItemNum = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem2Num[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iHadItemCount >= iRequireItemNum);
	if(sItemInterface.EraseBagItemByIndex(nullptr, m_pHuman, iItemID, iRequireItemNum))
	{
	}
	else
	{
		KCheck(FALSE);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::DepleteItem3()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iItemID = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem3ID[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iItemID == INVALID_ID) || (iItemID == 0))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHadItemCount = sItemInterface.CalcInventoryItemCount(m_pHuman, iItemID);
	int32	iRequireItemNum = g_SkillStudyCondition.m_aSkillStydy_Condition[m_iSkillID].m_iSpendItem3Num[m_iLevel];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iHadItemCount >= iRequireItemNum);
	if(sItemInterface.EraseBagItemByIndex(nullptr, m_pHuman, iItemID, iRequireItemNum))
	{
	}
	else
	{
		KCheck(FALSE);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::FindSkillIndex()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void PlayerSkillUpgrade::StartPassiveSkill(SpellID_t iSkillID, const Player *pPlayer)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SpellTemplateData *pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTemplate)
	{
		return;
	}

	if(pTemplate->GetPassiveFlag() <= 0)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SpellInstanceData *pInstance = DataManager::GetSingletonPtr()->getSpellInstance(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pInstance == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const Descriptor	*pDescriptor = pInstance->GetDescriptorByIndex(0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pDescriptor == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDataIndex = pDescriptor->GetValueBySkillLevel(m_iLevel);
	Player	*pTemp = const_cast<Player *>(pPlayer);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_EffectInterface.SendEffectToUnit(*pTemp, iDataIndex, pPlayer->GetID(), iSkillID);
}
