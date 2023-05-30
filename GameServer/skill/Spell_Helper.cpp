#include "stdafx.h"
#include "TypeDefine.h"
#include "gameobject/Character.h"
#include "Spell_Helper.h"
#include "skill/Spell_EffectLogic_All.h"
#include "server_settting.h"
#include "gameobject/Profession_Base.h"
#include "data/data_manager.h"
#include "item/Item_Interface.h"


ConditionAndDepleteCore_T	g_ConditionAndDepleteCore;

CombatSystem::CombatSystem()
{
	Reset();
}

CombatSystem::~CombatSystem()
{

}

int32 CombatSystem::GetAdditionalAttackNear(void) const
{
	return m_nAdditionalAttackNear;
}

void CombatSystem::SetAdditionalAttackNear(int32 nValue)
{
	m_nAdditionalAttackNear = nValue;
}

int32 CombatSystem::GetAdditionalAttackFar(void) const
{
	return m_nAdditionalAttackFar;
}

void CombatSystem::SetAdditionalAttackFar(int32 nValue)
{
	m_nAdditionalAttackFar = nValue;
}

int32 CombatSystem::GetAdditionalAttackMagic(void) const
{
	return m_nAdditionalAttackMagic;
}

void CombatSystem::SetAdditionalAttackMagic(int32 nValue)
{
	m_nAdditionalAttackMagic = nValue;
}

int32 CombatSystem::GetAdditionalAttackCold(void) const
{
	return m_nAdditionalAttackCold;
}

void CombatSystem::SetAdditionalAttackCold(int32 nValue)
{
	m_nAdditionalAttackCold = nValue;
}

int32 CombatSystem::GetAdditionalAttackFire(void) const
{
	return m_nAdditionalAttackFire;
}

void CombatSystem::SetAdditionalAttackFire(int32 nValue)
{
	m_nAdditionalAttackFire = nValue;
}

int32 CombatSystem::GetAdditionalAttackLight(void) const
{
	return m_nAdditionalAttackLight;
}

void CombatSystem::SetAdditionalAttackLight(int32 nValue)
{
	m_nAdditionalAttackLight = nValue;
}

int32 CombatSystem::GetAdditionalAttackPoison(void) const
{
	return m_nAdditionalAttackPoison;
}

void CombatSystem::SetAdditionalAttackPoison(int32 nValue)
{
	m_nAdditionalAttackPoison = nValue;
}

int32 GetFinalDamages(int32 iDamage, int32 iResist)
{
	iResist = Property_VerifyResist(iResist);
	return Float2Int(iDamage * (100 - iResist) * 0.01f);
}

static DI_DamagesByValue_T	logicDamages;
enum { IMPACT_DATA_INDEX_OF_DEFAULT_DAMAGES = 0, };

/*
=======================================================================================================================
=======================================================================================================================
*/
void CombatSystem::Reset()
{
	m_nAdditionalAttackNear = 0;
	m_nAdditionalAttackFar = 0;
	m_nAdditionalAttackMagic = 0;
	m_nAdditionalAttackCold = 0;
	m_nAdditionalAttackFire = 0;
	m_nAdditionalAttackLight = 0;
	m_nAdditionalAttackPoison = 0;
	m_nAdditionalDefenceNear = 0;
	m_nAdditionalDefenceFar = 0;
	m_nAdditionalDefenceMagic = 0;
	m_nAdditionalDefenceCold = 0;
	m_nAdditionalDefenceFire = 0;
	m_nAdditionalDefenceLight = 0;
	m_nAdditionalDefencePoison = 0;
	memset(m_ImpactDataTbl, 0, sizeof(m_ImpactDataTbl));
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CombatSystem::GetResultImpact(Character& rAttacker, Character& rDefencer, UNIT_EFFECT& rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nDamage = 0;
	int32		nMaxDamage = 0;
	int32		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_NEAR;
	int32		iLogicID = DI_DamagesByValue_T::ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (DI_DamagesByValue_T::ID == GetEffectLogicID(rImp))
	{
		InitAttackValueData(rImp);
	}
	else
	{
		iLogicID = DI_DamagesByRate_T::ID;
		InitAttackRateData(rImp, rAttacker);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			nFluctuation = g_Config.m_ConfigInfo.m_nDefaultDamageFluctuation;
	int16			nProfession = 9;
	Profession const* pProfession = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER == rAttacker.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player& rPlayer = (Player&)rAttacker;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nProfession = rPlayer.GetProfession();
		pProfession = DataManager::GetSingletonPtr()->getProfessionLogic(nProfession);
		if (NULL != pProfession)
		{
			nFluctuation = pProfession->Get_Property_AttackFluctuation();
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap* pMap = rAttacker.GetMap();
	int32	nRand = 50;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL != pMap)
	{
		nRand -= pMap->GetRand100();
	}

	nFluctuation = Float2Int((2 * nFluctuation * nRand) / 100.0f);

	int32 nProfessionRefixRate = GetProfessionDamageRefixRate(rAttacker, rDefencer);

	nDamage = NearDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackNear, m_nAdditionalDefenceNear);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamageNear(rImp, nDamage);
	nMaxDamage = nDamage;
	nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_NEAR;

	nDamage = FarDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackFar, m_nAdditionalDefenceFar);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamageFar(rImp, nDamage);
	if (nMaxDamage < nDamage)
	{
		nMaxDamage = nDamage;
		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_MAGIC;
	}

	nDamage = MagicalDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackMagic, m_nAdditionalDefenceMagic);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamageMagic(rImp, nDamage);
	if (nMaxDamage < nDamage)
	{
		nMaxDamage = nDamage;
		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_MAGIC;
	}

	nDamage = ColdDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackCold, m_nAdditionalDefenceCold);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamageCold(rImp, nDamage);
	if (nMaxDamage < nDamage)
	{
		nMaxDamage = nDamage;
		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_COLD;
	}

	nDamage = FireDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackFire, m_nAdditionalDefenceFire);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamageFire(rImp, nDamage);
	if (nMaxDamage < nDamage)
	{
		nMaxDamage = nDamage;
		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_FIRE;
	}

	nDamage = LightDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackLight, m_nAdditionalDefenceLight);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamageLight(rImp, nDamage);
	if (nMaxDamage < nDamage)
	{
		nMaxDamage = nDamage;
		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_LIGHT;
	}

	nDamage = PoisonDamage(rAttacker, rDefencer, iLogicID, m_nAdditionalAttackPoison, m_nAdditionalDefencePoison);

	nDamage = nDamage + Float2Int(nDamage * nFluctuation * 0.01f);
	nDamage = Float2Int(nDamage * nProfessionRefixRate * 0.01f);

	logicDamages.SetDamagePoison(rImp, nDamage);
	if (nMaxDamage < nDamage)
	{
		nMaxDamage = nDamage;
		nSpecialEffectID = DAMAGE_SPECIAL_EFFECT_POISON;
	}

	rImp.SetImpactID(nSpecialEffectID);



	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::CalculateHitRate(Character& rAttacker, Character& rTag)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nHit = rAttacker.Get_Property_Hit();
	int32		nMiss = rTag.Get_Property_Miss();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHit = Property_VerifyHitMiss(nHit);
	nMiss = Property_VerifyHitMiss(nMiss);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo& oSkillInf = rAttacker.GetSpellInfo();
	int32		iRefix = oSkillInf.GetAccuracy();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iRefix < 0)
	{
		iRefix = 0;
	}

	int32 iFainlHitRate = RefixHitbyInherenceBalance(nHit, nMiss, rAttacker, rTag);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	iFainlHitRate += iRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (10 > iFainlHitRate)
	{
		iFainlHitRate = 10;
	}

	return iFainlHitRate;
	__UNGUARD__ return 0;
}

int32 CombatSystem::CalculateHitRateForControlSpell(Character& rAttacker, Character& rTag, SpellControlType eType)
{
	__GUARD__

		int32 nHit = 0;
	int32 nMiss = 0;

	if (rAttacker.GetObjType() == Object::OBJECT_CLASS_PLAYER && rTag.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		nHit = rAttacker.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_CTRLHIT);
		nMiss = rTag.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_CTRLMISS);

		InherenceBalanceRefixValue sRefixValue;
		rAttacker.RefixInherenceBalance(sRefixValue);
		nHit += sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_CTRLHIT];
		nHit += rAttacker.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_CTRLHIT);

		sRefixValue.Clear();
		rTag.RefixInherenceBalance(sRefixValue);
		nMiss += sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_CTRLMISS];
		nMiss += rTag.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_CTRLMISS);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 iFainlHitRate = 100 + (nHit - nMiss);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (25 > iFainlHitRate)
	{
		iFainlHitRate = 25;
	}

	return iFainlHitRate;
	__UNGUARD__ return 0;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CombatSystem::IsHit(int32 nHitRate, int32 nRand)
{
	__GUARD__ 0 > nHitRate ? nHitRate = 0 : NULL;
	100 < nHitRate ? nHitRate = 100 : NULL;
	if (nRand < nHitRate)
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CombatSystem::IsCriticalHit(Character& rAttacker, int32 nCriticalRate, int32 nRand, Character& rTar, int32 iToughness)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iSkillPointRefix = 0;
	SpellInfo& rSkillInf = rAttacker.GetSpellInfo();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iSkillPointRefix = rSkillInf.GetCriticalRate();
	if (0 > iSkillPointRefix)
	{
		iSkillPointRefix = 0;
	}

	int32 iFanlCriticalRate = RefixCritRatebyInherenceBalance(nCriticalRate, iToughness, rAttacker, rTar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	iFanlCriticalRate = iFanlCriticalRate + iSkillPointRefix;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iFanlCriticalRate = Property_VerifyCritical(iFanlCriticalRate);

	BOOL bRet = FALSE;
	if (nRand < iFanlCriticalRate)
	{
		bRet = TRUE;
	}

	if (g_Config.m_ConfigInfo.m_nToggleDebugInherenceBalance)
	{
		QLogSystem::QUICK_LOG
		(
			QUICK_LOG_DEBUG,
			"IsCriticalHit result = %d, nCriticalRate = %d, iToughness = %d, iSkillPointRefix = %d, iFanlCriticalRate = %d, nRand = %d",
			bRet,
			nCriticalRate,
			iToughness,
			iSkillPointRefix,
			iFanlCriticalRate,
			nRand
		);
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::ColdDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionalAttack,
	int32		nAdditionalResist
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTab = m_ImpactDataTbl[DAMAGE_TYPE_COLD];
	int32	nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.Get_Property_AttackCold(), nAdditionalAttack, iLogicID, iTab));
	int32	nResist = Property_VerifyDefence(GetValueByCalType(rTar.Get_Property_DefenceCold(), nAdditionalResist, iLogicID, iTab));
	int32	nDamage = AttrDamage(rMe, nResist, nAttack, IPROPERTY_SHIELD_COLD);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nDamage;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::FireDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionalAttack,
	int32		nAdditionalResist
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTab = m_ImpactDataTbl[DAMAGE_TYPE_FIRE];
	int32	nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.Get_Property_AttackFire(), nAdditionalAttack, iLogicID, iTab));
	int32	nResist = Property_VerifyDefence(GetValueByCalType(rTar.Get_Property_DefenceFire(), nAdditionalResist, iLogicID, iTab));
	int32	nDamage = AttrDamage(rMe, nResist, nAttack, IPROPERTY_SHIELD_FIRE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nDamage;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::LightDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionalAttack,
	int32		nAdditionalResist
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTab = m_ImpactDataTbl[DAMAGE_TYPE_LIGHT];
	int32	nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.Get_Property_AttackLight(), nAdditionalAttack, iLogicID, iTab));
	int32	nResist = Property_VerifyDefence(GetValueByCalType(rTar.Get_Property_DefenceLight(), nAdditionalResist, iLogicID, iTab));
	int32	nDamage = AttrDamage(rMe, nResist, nAttack, IPROPERTY_SHIELD_LIGHT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nDamage;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::PoisonDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionalAttack,
	int32		nAdditionalResist
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTab = m_ImpactDataTbl[DAMAGE_TYPE_POISON];
	int32	nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.Get_Property_AttackPoison(), nAdditionalAttack, iLogicID, iTab));
	int32	nResist = Property_VerifyDefence(GetValueByCalType(rTar.Get_Property_DefencePoison(), nAdditionalResist, iLogicID, iTab));
	int32	nDamage = AttrDamage(rMe, nResist, nAttack, IPROPERTY_SHIELD_POISON);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nDamage;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::NearDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionAttack,
	int32		nAdditionDefence
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTab = m_ImpactDataTbl[DAMAGE_TYPE_NEAR];
	int32		nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.GetAttackNear(), nAdditionAttack, iLogicID, iTab));
	int32		nDefence = Property_VerifyDefence(GetValueByCalType(rTar.GetDefenceNear(), nAdditionDefence, iLogicID, iTab));
	int32		nDamage = NormalDamage(rTar, nAttack, nDefence, IPROPERTY_SHIELD_NEAR);
	int32		iResist = rTar.GetNearAttReduce();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nValue = rMe.GetIntAttr_EX(CharIntProperty::PROPERTY_IGNORE_NEAR_IMMUNITY);
	nValue < 0 ? nValue = 0 : NULL;
	iResist -= nValue;
	iResist < 0 ? iResist = 0 : NULL;
	nDamage = GetFinalDamages(nDamage, iResist);

	return nDamage;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::FarDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionAttack,
	int32		nAdditionDefence
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTab = m_ImpactDataTbl[DAMAGE_TYPE_FAR];
	int32		nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.GetAttackFar(), nAdditionAttack, iLogicID, iTab));
	int32		nDefence = Property_VerifyDefence(GetValueByCalType(rTar.GetDefenceFar(), nAdditionDefence, iLogicID, iTab));
	int32		nDamage = NormalDamage(rTar, nAttack, nDefence, IPROPERTY_SHIELD_FAR);
	int32		iResist = rTar.GetFarAttReduce();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nValue = rMe.GetIntAttr_EX(CharIntProperty::PROPERTY_IGNORE_FAR_IMMUNITY);
	nValue < 0 ? nValue = 0 : NULL;
	iResist -= nValue;
	iResist < 0 ? iResist = 0 : NULL;

	nDamage = GetFinalDamages(nDamage, iResist);
	return nDamage;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::MagicalDamage
(
	Character& rMe,
	Character& rTar,
	int32		iLogicID,
	int32		nAdditionAttack,
	int32		nAdditionDefence
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTab = m_ImpactDataTbl[DAMAGE_TYPE_M];
	int32		nAttack = Property_VerifyTraitAttack(GetValueByCalType(rMe.Get_Property_AttackMagic(), nAdditionAttack, iLogicID, iTab));
	int32		nDefence = Property_VerifyDefence(GetValueByCalType(rTar.Get_Property_DefenceMagic(), nAdditionDefence, iLogicID, iTab));
	int32		nDamage = NormalDamage(rTar, nAttack, nDefence, IPROPERTY_SHIELD_M);
	int32		iResist = rTar.GetMagicAttReduce();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	int32 nValue = rMe.GetIntAttr_EX(CharIntProperty::PROPERTY_IGNORE_MAGIC_IMMUNITY);
	nValue < 0 ? nValue = 0 : NULL;
	iResist -= nValue;
	iResist < 0 ? iResist = 0 : NULL;

	nDamage = GetFinalDamages(nDamage, iResist);
	return nDamage;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::NormalDamage(Character& rTar, int32 nAttack, int32 nDefence, int32 iType)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage;
	int32	nIgnoreRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER == rTar.GetObjType())
	{
		nIgnoreRate = rTar.ItemValue(iType).m_Value;
	}

	if (0 == nAttack + nDefence)
	{
		nDamage = 0;
	}
	else
	{
		nDamage = nAttack - nDefence;
	}

	nDamage -= nIgnoreRate;
	0 > nDamage ? nDamage = 0 : NULL;
	return nDamage;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::AttrDamage(Character& rTar, int32& nResist, int32 nAttack, int32 iType)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage;
	int32	nIgnoreRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	/*if(MAX_EFFECTIVE_RESIST < nResist)
	{
	nResist = MAX_EFFECTIVE_RESIST;
	}

	if(-MAX_EFFECTIVE_RESIST > nResist)
	{
	nResist = -MAX_EFFECTIVE_RESIST;
	}*/
	//nDamage = Float2Int(nAttack * (100 - nResist) / 100);
	nResist < 0 ? nResist = 0 : NULL;
	nDamage = nAttack - nResist;
	if (Object::OBJECT_CLASS_PLAYER == rTar.GetObjType())
	{
		nIgnoreRate = rTar.ItemValue(iType).m_Value;
	}

	nDamage -= nIgnoreRate;
	0 > nDamage ? nDamage = 0 : NULL;
	return nDamage;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void CombatSystem::InitAttackValueData(UNIT_EFFECT& rImp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	DI_DamagesByValue_T	logic;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nAdditionalAttackNear += logic.GetDamageNear(rImp);
	m_nAdditionalAttackFar += logic.GetDamageFar(rImp);
	m_nAdditionalAttackMagic += logic.GetDamageMagic(rImp);
	m_nAdditionalAttackCold += logic.GetDamageCold(rImp);
	m_nAdditionalAttackFire += logic.GetDamageFire(rImp);
	m_nAdditionalAttackLight += logic.GetDamageLight(rImp);
	m_nAdditionalAttackPoison += logic.GetDamagePoison(rImp);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void CombatSystem::InitAttackRateData(UNIT_EFFECT& rImp, Character& rMe)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	DI_DamagesByRate_T	logic;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nAdditionalAttackNear += logic.GetDamageNear(rImp);
	m_nAdditionalAttackFar += logic.GetDamageFar(rImp);
	m_nAdditionalAttackMagic += logic.GetDamageMagic(rImp);
	m_nAdditionalAttackCold += logic.GetDamageCold(rImp);
	m_nAdditionalAttackFire += logic.GetDamageFire(rImp);
	m_nAdditionalAttackLight += logic.GetDamageLight(rImp);
	m_nAdditionalAttackPoison += logic.GetDamagePoison(rImp);

	if (DI_DamagesByRate_T::ID != GetEffectLogicID(rImp))
	{
		return;
	}

	memset(m_ImpactDataTbl, 0, sizeof(m_ImpactDataTbl));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	UNIT_EFFECT	impactTab;
	int32		nValue = rImp.GetDataIndex();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_EffectInterface.InitEffectFromData(nValue, impactTab, rMe);
	KCheck(rImp.MAX_IMPACT_PARAM_NUMBER >= DAMAGE_TYPE_NUMBER);
	for (int32 i = 0; i < DAMAGE_TYPE_NUMBER; ++i)
	{
		m_ImpactDataTbl[i] = impactTab.GetParamByIndex(i);
	}
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::GetValueByCalType(int32 iSrc, int32 iAddition, int32 iType, int32 iParaTab)
{
	if (DI_DamagesByValue_T::ID == iType)
	{
		return iSrc + iAddition;
	}

	return(int32)((iSrc + iAddition) * (1.0f + iParaTab * 0.01f) + 0.5f);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CombatSystem::GetProfessionDamageRefixRate(Character& rAttacker, Character& rTar)
{
	int32 nRefixValue = 100;
	if ((rAttacker.GetObjType() == Object::OBJECT_CLASS_PLAYER || rAttacker.GetObjType() == Object::OBJECT_CLASS_PET)
		&& (rTar.GetObjType() == Object::OBJECT_CLASS_PLAYER || rTar.GetObjType() == Object::OBJECT_CLASS_PET))
	{
		Character* pAttacker = &rAttacker;
		if (rAttacker.GetObjType() == Object::OBJECT_CLASS_PET)
		{
			pAttacker = static_cast<Pet*>(&rAttacker)->GetOwner();
		}

		if (pAttacker == NULL)
		{
			QLogSystem::QUICK_LOG
			(
				QUICK_LOG_DEBUG,
				"CombatSystem::GetProfessionDamageRefixRate pAttacker == NULL"
			);
			return nRefixValue;
		}

		Character* pTar = &rTar;
		if (rTar.GetObjType() == Object::OBJECT_CLASS_PET)
		{
			pTar = static_cast<Pet*>(&rTar)->GetOwner();
		}

		if (pTar == NULL)
		{
			QLogSystem::QUICK_LOG
			(
				QUICK_LOG_DEBUG,
				"CombatSystem::GetProfessionDamageRefixRate pTar == NULL"
			);
			return nRefixValue;
		}

		int32 nReduce = pTar->GetProfessionReduce(static_cast<Player*>(pAttacker)->GetProfession());
		int32 nIncrease = pAttacker->GetProfessionIncrease(static_cast<Player*>(pTar)->GetProfession());


		int32 nIncrease_ZhuanJing = 0;
		int32 nReduce_ZhuanJing = 0;

		
		nRefixValue = 100 + nIncrease + nIncrease_ZhuanJing - nReduce - nReduce_ZhuanJing;

		if (g_Config.m_ConfigInfo.m_nToggleDebugInherenceZhuanjing)
		{
			QLogSystem::QUICK_LOG
			(
				QUICK_LOG_DEBUG,
				"CombatSystem::GetProfessionDamageRefixRate AttackerID = %d, ItemRefixIncrease = %d, ZhuanGongRefixIncrease = %d, TarID = %d, ItemRefixReduce = %d, ZhuanFangRefixReduce = %d",
				rAttacker.GetID(),
				nIncrease,
				nIncrease_ZhuanJing,
				rTar.GetID(),
				nReduce,
				nReduce_ZhuanJing
			);
		}

		if (nRefixValue < 10)
		{
			nRefixValue = 10;
		}
	}

	return nRefixValue;
}

int32 CombatSystem::RefixCritRatebyInherenceBalance(int32 nCrit, int32 nToughness, Character& rAttacker, Character& rTar)
{
	int32 refixValue = nCrit - nToughness;

	if (rAttacker.GetObjType() == Object::OBJECT_CLASS_PLAYER && rTar.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		if (refixValue <= 10)
		{
			refixValue += rAttacker.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_CRITRATE);
			InherenceBalanceRefixValue sRefixValue;
			rAttacker.RefixInherenceBalance(sRefixValue);
			refixValue += sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_CRITRATE];
			refixValue += rAttacker.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_CRITRATE);

			if (refixValue > 10)
			{
				refixValue = 10;
			}
		}
		else if (refixValue >= 50)
		{
			refixValue -= rTar.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_TOUGHNESS);
			InherenceBalanceRefixValue sRefixValue;
			rTar.RefixInherenceBalance(sRefixValue);
			refixValue -= sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_TOUGHNESS];
			refixValue -= rTar.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_TOUGHNESS);

			if (refixValue < 50)
			{
				refixValue = 50;
			}
		}
	}

	return refixValue;
}

int32 CombatSystem::RefixHitbyInherenceBalance(int32 nHit, int32 nMiss, Character& rAttacker, Character& rTar)
{
	int32 refixValue = nHit - nMiss;

	if (rAttacker.GetObjType() == Object::OBJECT_CLASS_PLAYER && rTar.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		if (refixValue <= 50)
		{
			refixValue += rAttacker.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_HIT);
			InherenceBalanceRefixValue sRefixValue;
			rAttacker.RefixInherenceBalance(sRefixValue);
			refixValue += sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_HIT];
			refixValue += rAttacker.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_HIT);

			if (refixValue > 50)
			{
				refixValue = 50;
			}
		}
		else if (refixValue >= 80)
		{
			refixValue -= rTar.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_MISS);
			InherenceBalanceRefixValue sRefixValue;
			rTar.RefixInherenceBalance(sRefixValue);
			refixValue -= sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_MISS];
			refixValue -= rTar.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_MISS);

			if (refixValue < 80)
			{
				refixValue = 80;
			}
		}
	}

	return refixValue;
}

float CombatSystem::RefixCritDamagebyInherenceBalance(int32 nCritDamageRate, int32 nCritDamageDerateRatrByToughness, Character& rAttacker, Character& rTar)
{
	float nRefix = (float)(nCritDamageRate - nCritDamageDerateRatrByToughness);

	if (rAttacker.GetObjType() == Object::OBJECT_CLASS_PLAYER && rTar.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		if (nRefix <= 1.5)
		{
			nRefix += rAttacker.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_CRITDAMAGE) / 100;
			InherenceBalanceRefixValue sRefixValue;
			rAttacker.RefixInherenceBalance(sRefixValue);
			nRefix += sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_CRITDAMAGE] / 100;
			nRefix += rAttacker.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_CRITDAMAGE) / 100;

			if (nRefix > 1.5)
			{
				nRefix = 1.5;
			}
		}
		else if (nRefix >= 2)
		{
			nRefix -= rTar.GetInherenceBalanceLevel(CPROPERTY_LEVEL4_BALANCE_CRITDAMAGEDERATE) / 100;
			InherenceBalanceRefixValue sRefixValue;
			rTar.RefixInherenceBalance(sRefixValue);
			nRefix -= sRefixValue.values[CPROPERTY_LEVEL4_BALANCE_CRITDAMAGEDERATE] / 100;
			nRefix -= rTar.GetInherenceBalanceRefixForItem(CPROPERTY_LEVEL4_BALANCE_CRITDAMAGEDERATE) / 100;

			if (nRefix < 2)
			{
				nRefix = 2;
			}
		}
	}

	return nRefix;
}




BOOL CDSystem::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nType = rData.GetType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch (nType)
	{
	case CDUnitHaveImpact::ID:		return m_C_UnitHaveImpact.ConditionCheck(rMe, rData);
	case CDUnitHpLessThanByRate::ID:	return m_C_UnitHpLessThanByRate.ConditionCheck(rMe, rData);
	case CDUnitHpMoreThanByRate::ID:	return m_C_UnitHpMoreThanByRate.ConditionCheck(rMe, rData);
	case CDTargetMustHaveImpact::ID:	return m_C_TargetMustHaveImpact.ConditionCheck(rMe, rData);
	case CDTargetHpLessThanByRate::ID:	return m_C_TargetHpLessThanByRate.ConditionCheck(rMe, rData);
	case CDTargetHpMoreThanByRate::ID:	return m_C_TargetHpMoreThanByRate.ConditionCheck(rMe, rData);
	case CDHpByValue::ID:			return m_CD_HpByValue.ConditionCheck(rMe, rData);
	case CDHpByRate::ID:			return m_CD_HpByRate.ConditionCheck(rMe, rData);
	case CDRage0ByValue::ID:		return m_CD_Rage0ByValue.ConditionCheck(rMe, rData);
	case CDRage1ByValue::ID:		return m_CD_Rage1ByValue.ConditionCheck(rMe, rData);
	case CDRage2ByValue::ID:		return m_CD_Rage2ByValue.ConditionCheck(rMe, rData);
	case CDRage3ByValue::ID:		return m_CD_Rage3ByValue.ConditionCheck(rMe, rData);
	case CDRage4ByValue::ID:		return m_CD_Rage4ByValue.ConditionCheck(rMe, rData);
	case CDRage5ByValue::ID:		return m_CD_Rage5ByValue.ConditionCheck(rMe, rData);
	case CDRage0ByRate::ID:			return m_CD_Rage0ByRate.ConditionCheck(rMe, rData);
	case CDRage1ByRate::ID:			return m_CD_Rage1ByRate.ConditionCheck(rMe, rData);
	case CDRage2ByRate::ID:			return m_CD_Rage2ByRate.ConditionCheck(rMe, rData);
	case CDRage3ByRate::ID:			return m_CD_Rage3ByRate.ConditionCheck(rMe, rData);
	case CDRage4ByRate::ID:			return m_CD_Rage4ByRate.ConditionCheck(rMe, rData);
	case CDRage5ByRate::ID:			return m_CD_Rage5ByRate.ConditionCheck(rMe, rData);
	case CDCancelSpecialImpact_D::ID:	return m_D_CancelSpecialImpact.ConditionCheck(rMe, rData);
	case CDCancelSpecialImpact_CD::ID:	return m_CD_CancelSpecialImpact.ConditionCheck(rMe, rData);
	case CDTargetMustBeMySpouse::ID:	return m_C_TargetMustBeMySpouse.ConditionCheck(rMe, rData);
	default:				return TRUE; break;
	};
	return TRUE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ switch (rData.GetType())
	{
	case CDUnitHaveImpact::ID:		return m_C_UnitHaveImpact.Deplete(rMe, rData);
	case CDUnitHpLessThanByRate::ID:	return m_C_UnitHpLessThanByRate.Deplete(rMe, rData);
	case CDUnitHpMoreThanByRate::ID:	return m_C_UnitHpMoreThanByRate.Deplete(rMe, rData);
	case CDTargetMustHaveImpact::ID:	return m_C_TargetMustHaveImpact.Deplete(rMe, rData);
	case CDTargetHpLessThanByRate::ID:	return m_C_TargetHpLessThanByRate.Deplete(rMe, rData);
	case CDTargetHpMoreThanByRate::ID:	return m_C_TargetHpMoreThanByRate.Deplete(rMe, rData);
	case CDHpByValue::ID:			return m_CD_HpByValue.Deplete(rMe, rData);
	case CDHpByRate::ID:			return m_CD_HpByRate.Deplete(rMe, rData);
	case CDRage0ByValue::ID:		return m_CD_Rage0ByValue.Deplete(rMe, rData);
	case CDRage1ByValue::ID:		return m_CD_Rage1ByValue.Deplete(rMe, rData);
	case CDRage2ByValue::ID:		return m_CD_Rage2ByValue.Deplete(rMe, rData);
	case CDRage3ByValue::ID:		return m_CD_Rage3ByValue.Deplete(rMe, rData);
	case CDRage4ByValue::ID:		return m_CD_Rage4ByValue.Deplete(rMe, rData);
	case CDRage5ByValue::ID:		return m_CD_Rage5ByValue.Deplete(rMe, rData);
	case CDRage0ByRate::ID:			return m_CD_Rage0ByRate.Deplete(rMe, rData);
	case CDRage1ByRate::ID:			return m_CD_Rage1ByRate.Deplete(rMe, rData);
	case CDRage2ByRate::ID:			return m_CD_Rage2ByRate.Deplete(rMe, rData);
	case CDRage3ByRate::ID:			return m_CD_Rage3ByRate.Deplete(rMe, rData);
	case CDRage4ByRate::ID:			return m_CD_Rage4ByRate.Deplete(rMe, rData);
	case CDRage5ByRate::ID:			return m_CD_Rage5ByRate.Deplete(rMe, rData);
	case CDCancelSpecialImpact_D::ID:	return m_D_CancelSpecialImpact.Deplete(rMe, rData);
	case CDCancelSpecialImpact_CD::ID:	return m_CD_CancelSpecialImpact.Deplete(rMe, rData);
	case CDTargetMustBeMySpouse::ID:	return m_C_TargetMustBeMySpouse.Deplete(rMe, rData);
	default:				break;
	};
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::ConditionCheckByItem(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& oHuman = static_cast<Player&>(rMe);
	SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	int32		iItemType = rData.GetParam0();
	int32		iItemCount = rData.GetParam1();
	int32		iTmp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iItemCount > 0 && iItemType != INVALID_ID)
	{
		if (!sItemInterface.HaveEnoughBagItemSpace(&oHuman, iItemType, iItemCount, iTmp))
		{
			rParams.SetErrCode(OR_NOT_ENOUGH_ITEM);
			return FALSE;
		}
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::DepleteByItem(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& oHuman = static_cast<Player&>(rMe);
	SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	int32		iItemType = rData.GetParam0();
	int32		iItemCount = rData.GetParam1();
	int32		iTmp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iItemCount > 0 && iItemType != INVALID_ID)
	{
		if (!sItemInterface.HaveEnoughBagItemSpace(&oHuman, iItemType, iItemCount, iTmp))
		{
			rParams.SetErrCode(OR_NOT_ENOUGH_ITEM);
			return FALSE;
		}

		rParams.SetErrCode(OR_OK);


		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		BOOL	ret = sItemInterface.EraseBagItemByIndex(nullptr, &oHuman, iItemType, iItemCount);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (ret)
		{
		}

		return ret;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDUnitHaveImpact::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	int32					nCollection = rData.GetParam0();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (FALSE == rMe.Effect_HaveEffectInSpecificCollection(nCollection))
	{
		rParams.SetErrCode(OR_U_CANNT_DO_THIS_RIGHT_NOW);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDUnitHaveImpact::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDUnitHpLessThanByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	nHP = rMe.GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP = Float2Int((nHP * iDeplete) / 100.0f);

	nHP = RefixValue(nHP, rMe, rData);
	if (rMe.GetHP() > nHP)
	{
		rParams.SetErrCode(OR_TOO_MUCH_HP);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDUnitHpLessThanByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDUnitHpMoreThanByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	nHP = rMe.GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP = Float2Int((nHP * iDeplete) / 100.0f);
	iDeplete = RefixValue(nHP, rMe, rData);
	if (rMe.GetHP() <= iDeplete)
	{
		rParams.SetErrCode(OR_NOT_ENOUGH_HP);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDUnitHpMoreThanByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDHpByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDeplete = RefixValue(iDeplete, rMe, rData);
	if (rMe.GetHP() <= iDeplete)
	{
		rParams.SetErrCode(OR_NOT_ENOUGH_HP);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDHpByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDeplete = RefixValue(iDeplete, rMe, rData);

	rMe.HealthIncrement(-iDeplete, INVALID_ID, &rMe);
	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetHpLessThanByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	Character* pTar = (Character*)rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	nHP = pTar->GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP = Float2Int((nHP * iDeplete) / 100.0f);
	iDeplete = RefixValue(nHP, rMe, rData);

	if (pTar->GetHP() > iDeplete)
	{
		rParams.SetErrCode(OR_TOO_MUCH_HP);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetHpLessThanByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetHpMoreThanByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	Character* pTar = (Character*)rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	nHP = pTar->GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP = Float2Int((nHP * iDeplete) / 100.0f);
	iDeplete = RefixValue(nHP, rMe, rData);
	if (pTar->GetHP() <= iDeplete)
	{
		rParams.SetErrCode(OR_NOT_ENOUGH_HP);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetHpMoreThanByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetMustHaveImpact::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	int32					nCollection = rData.GetParam0();
	Character* pTar = (Character*)rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if (FALSE == pTar->Effect_HaveEffectInSpecificCollection(nCollection))
	{
		rParams.SetErrCode(OR_OK);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetMustHaveImpact::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDCancelSpecialImpact_D::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDCancelSpecialImpact_D::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	int32					nCollection = rData.GetParam0();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rMe.Effect_CancelEffectInSpecificCollection(nCollection);
	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetMustBeMySpouse::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		nCollection = rData.GetParam0();
	Character* pTar = (Character*)rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	if (Object::OBJECT_CLASS_PLAYER != pTar->GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = static_cast<Player&>(*pTar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER != pTar->GetObjType())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDTargetMustBeMySpouse::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDHpByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = (Player&)rMe;
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	nHp = rPlayer.GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHp = Float2Int((iDeplete * nHp) / 100.0f);
	iDeplete = RefixValue(nHp, rMe, rData);

	if (rPlayer.GetHP() < iDeplete)
	{
		rParams.SetErrCode(OR_NOT_ENOUGH_HP);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDHpByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = (Player&)rMe;
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	nHP = rPlayer.GetMaxHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP = Float2Int((nHP * iDeplete) / 100.0f);
	iDeplete = RefixValue(nHP, rMe, rData);

	rPlayer.HealthIncrement(-iDeplete, INVALID_ID, &rPlayer);
	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CDSystem::ConDepLogic::RefixValue(int32 iValue, Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	int32			iRefixValue = rSkillInfo.GetDepleteRefixByValue();
	int32			iRefixRate = rSkillInfo.GetDepleteRefixByRate();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iRefixRate == 0)
	{
		iValue += iRefixValue;
	}
	else
	{
		iValue = Float2Int(iValue * iRefixRate * 0.01f);
	}

	return iValue;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage0ByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage0ByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage1ByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage1ByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage2ByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByValue(rMe, rData);
	__UNGUARD__ return FALSE;;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage2ByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage3ByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage3ByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage4ByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage4ByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage5ByValue::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage5ByValue::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByValue(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CDSystem::ConDepLogic::GetCommonDeplete(ConditionAndDepleteTerm const& rData, SpellInfo& rSkillInfo) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iPara1 = rData.GetParam0();
	int32	iPara2 = rData.GetParam1();
	int32	iSkillLevel = rSkillInfo.GetCharacterSpellLevel() + 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return iPara1 * iSkillLevel + iPara2;
}

int32 CDSystem::ConDepLogic::NotEnoughRageForProfession(Player& rMe) const
{
	switch (rMe.GetProfession())
	{
	case PROFESSION_WUSHI:
	case PROFESSION_SHIZIJUN:
		return OR_NOT_ENOUGH_RAGE_WUSHI;
	case PROFESSION_JIANXIA:
	case PROFESSION_SHENGHUOSHI:
		return OR_NOT_ENOUGH_RAGE_JIANXIA;
	case PROFESSION_QISHE:
	case PROFESSION_CIKE:
		return OR_NOT_ENOUGH_RAGE_QISHE;
	case PROFESSION_HUOQIANG:
	case PROFESSION_JINWEIJUN:
		return OR_NOT_ENOUGH_RAGE_HUOQIANG;
	case PROFESSION_XIANZHI:
	case PROFESSION_YINXIUSHI:
		return OR_NOT_ENOUGH_RAGE_XIANZHI;
	case PROFESSION_SAMAN:
	case PROFESSION_LAMA:
		return OR_NOT_ENOUGH_RAGE_SAMAN;
	}
	return OR_NOT_ENOUGH_RAGE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::ConDepLogic::RageConditionCheckByValue(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDeplete = RefixValue(iDeplete, rMe, rData);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = (Player&)rMe;
	int32	iRage = rPlayer.Get_Property_Rage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iRage < iDeplete)
	{
		rParams.SetErrCode(NotEnoughRageForProfession(rPlayer));
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::ConDepLogic::RageDepleteByValue(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDeplete = RefixValue(iDeplete, rMe, rData);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = (Player&)rMe;
	int32	iRage = rPlayer.Get_Property_Rage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iRage < iDeplete)
	{
		rParams.SetErrCode(NotEnoughRageForProfession(rPlayer));
		return FALSE;
	}

	rMe.RageIncrement(-iDeplete, INVALID_ID, &rMe);
	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::ConDepLogic::RageConditionCheckByRate(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	iRageNeed = rMe.Get_Property_MaxRage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iRageNeed = Float2Int(iRageNeed * iDeplete * 0.01f);

	iDeplete = RefixValue(iRageNeed, rMe, rData);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = (Player&)rMe;
	int32	iRage = rPlayer.Get_Property_Rage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iRage < iRageNeed)
	{
		rParams.SetErrCode(NotEnoughRageForProfession(rPlayer));
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::ConDepLogic::RageDepleteByRate(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (Object::OBJECT_CLASS_MONSTER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDeplete = GetCommonDeplete(rData, rSkillInfo);
	int32	iRageNeed = rMe.Get_Property_MaxRage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iRageNeed = Float2Int(iRageNeed * iDeplete * 0.01f);

	iDeplete = RefixValue(iRageNeed, rMe, rData);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player& rPlayer = (Player&)rMe;
	int32	iRage = rPlayer.Get_Property_Rage();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iRage < iRageNeed)
	{
		rParams.SetErrCode(NotEnoughRageForProfession(rPlayer));
		return FALSE;
	}

	rMe.RageIncrement(-iDeplete, INVALID_ID, &rMe);
	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDCancelSpecialImpact_CD::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	int32					nCollection = rData.GetParam0();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (FALSE == rMe.Effect_HaveEffectInSpecificCollection(nCollection))
	{
		rParams.SetErrCode(OR_U_CANNT_DO_THIS_RIGHT_NOW);
		return FALSE;
	}

	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDCancelSpecialImpact_CD::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo& rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams& rParams = rMe.GetTargetingAndDepletingParams();
	int32					nCollection = rData.GetParam0();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rMe.Effect_CancelEffectInSpecificCollection(nCollection);
	rParams.SetErrCode(OR_OK);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage0ByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage0ByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage1ByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage1ByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage2ByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage2ByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage3ByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage3ByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage4ByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage4ByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage5ByRate::ConditionCheck(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageConditionCheckByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CDSystem::CDRage5ByRate::Deplete(Character& rMe, ConditionAndDepleteTerm const& rData) const
{
	__GUARD__ return RageDepleteByRate(rMe, rData);
	__UNGUARD__ return FALSE;
}



/*
=======================================================================================================================
=======================================================================================================================
*/
SpellTargetingAndDepletingParams::SpellTargetingAndDepletingParams(void) :
m_nActivatedSpell(INVALID_ID),
m_nActivatedScript(INVALID_ID),
m_nTargetObj(INVALID_ID),
m_guidTargetPartner(INVALID_ID),
m_fTargetDirection(0.0f),
m_nTargetBagSlot(INVALID_ID),
m_bIgnoreConditionCheck(FALSE),
m_nDepletedRage(0),
m_nDepletedStrikePoints(0),
m_nBagIndexOfDepletedItem(INVALID_ID),
m_nItemIndexOfDepletedItem(INVALID_ID),
m_nDelayTime(0),
m_nTargetCount(0),
m_nErrCode(INVALID_ID),
m_nErrParam(0),
m_iHurtDelayTime(0)
{
	m_posTargetPosition.Clear();
	m_guidDepletedItem.Reset();
	m_guidTargetPet.Reset();
	memset((void *) &m_aDynamicParams, 0, sizeof(m_aDynamicParams));
	m_bDeletedItemBind = 0;
}

SpellID_t SpellTargetingAndDepletingParams::GetActivatedSpell(void) const
{
	return m_nActivatedSpell;
}

void SpellTargetingAndDepletingParams::SetActivatedSpell(SpellID_t nSpell)
{
	m_nActivatedSpell = nSpell;
}

ScriptID_t SpellTargetingAndDepletingParams::GetActivatedScript(void) const
{
	return m_nActivatedScript;
}

void SpellTargetingAndDepletingParams::SetActivatedScript(ScriptID_t nScript)
{
	m_nActivatedScript = nScript;
}

ObjID_t SpellTargetingAndDepletingParams::GetTargetObj(void) const
{
	return m_nTargetObj;
}

void SpellTargetingAndDepletingParams::SetTargetObj(ObjID_t nObj)
{
	m_nTargetObj = nObj;
}

GUID_t SpellTargetingAndDepletingParams::GetTargetGuid(void) const
{
	return m_guidTargetPartner;
}

void SpellTargetingAndDepletingParams::SetTargetGuid(GUID_t nGuid)
{
	m_guidTargetPartner = nGuid;
}

GLPos const &SpellTargetingAndDepletingParams::GetTargetPosition(void) const
{
	return m_posTargetPosition;
}

void SpellTargetingAndDepletingParams::SetTargetPosition(GLPos const &rPos)
{
	m_posTargetPosition = rPos;
}

float SpellTargetingAndDepletingParams::GetTargetDirection(void) const
{
	return m_fTargetDirection;
}

void SpellTargetingAndDepletingParams::SetTargetDirection(float fDir)
{
	m_fTargetDirection = fDir;
}

int32 SpellTargetingAndDepletingParams::GetTargetBagSlot(void) const
{
	return m_nTargetBagSlot;
}

void SpellTargetingAndDepletingParams::SetTargetBagSlot(int32 nSlot)
{
	m_nTargetBagSlot = nSlot;
}

SHorseGuid const &SpellTargetingAndDepletingParams::GetTargetPetGuid(void) const
{
	return m_guidTargetPet;
}

void SpellTargetingAndDepletingParams::SetTargetPetGuid(SHorseGuid const &rGuid)
{
	m_guidTargetPet = rGuid;
}

BOOL SpellTargetingAndDepletingParams::GetIgnoreConditionCheckFlag(void) const
{
	return m_bIgnoreConditionCheck;
}

void SpellTargetingAndDepletingParams::SetIgnoreConditionCheckFlag(BOOL bFlag)
{
	m_bIgnoreConditionCheck = bFlag;
}

int32 SpellTargetingAndDepletingParams::GetDepletedRage(void) const
{
	return m_nDepletedRage;
}

void SpellTargetingAndDepletingParams::SetDepletedRage(int32 nDepleted)
{
	m_nDepletedRage = nDepleted;
}

int32 SpellTargetingAndDepletingParams::GetDepletedStrikePoints(void) const
{
	return m_nDepletedStrikePoints;
}

void SpellTargetingAndDepletingParams::SetDepletedStrikePoints(int32 nDepleted)
{
	m_nDepletedStrikePoints = nDepleted;
}

SItemGuid const &SpellTargetingAndDepletingParams::GetDepletedItemGuid(void) const
{
	return m_guidDepletedItem;
}

void SpellTargetingAndDepletingParams::SetDepletedItemGuid(SItemGuid const &rGuid)
{
	m_guidDepletedItem = rGuid;
}

int32 SpellTargetingAndDepletingParams::GetBagIndexOfDepletedItem(void) const
{
	return m_nBagIndexOfDepletedItem;
}

void SpellTargetingAndDepletingParams::SetBagIndexOfDepletedItem(int32 nIndex)
{
	m_nBagIndexOfDepletedItem = nIndex;
}

int32 SpellTargetingAndDepletingParams::GetItemIndexOfDepletedItem(void) const
{
	return m_nItemIndexOfDepletedItem;
}

void SpellTargetingAndDepletingParams::SetItemIndexOfDepletedItem(int32 nIndex)
{
	m_nItemIndexOfDepletedItem = nIndex;
}

void SpellTargetingAndDepletingParams::SetItemBind()
{
	m_bDeletedItemBind = 1;
}

BOOL SpellTargetingAndDepletingParams::IsDepletedItemBind()
{
	return m_bDeletedItemBind;
}

Time_t SpellTargetingAndDepletingParams::GetDelayTime(void) const
{
	return m_nDelayTime;
}

void SpellTargetingAndDepletingParams::SetDelayTime(Time_t nTime)
{
	m_nDelayTime = nTime;
}

int32 SpellTargetingAndDepletingParams::GetTargetCount(void) const
{
	return m_nTargetCount;
}

void SpellTargetingAndDepletingParams::SetTargetCount(int32 nCount)
{
	m_nTargetCount = nCount;
}

ID_t SpellTargetingAndDepletingParams::GetErrCode(void) const
{
	return m_nErrCode;
}

void SpellTargetingAndDepletingParams::SetErrCode(ID_t nErr)
{
	if (nErr == -9)
	{
		int kk = 0;
	}
	m_nErrCode = nErr;
}

int32 SpellTargetingAndDepletingParams::GetErrParam(void) const
{
	return m_nErrParam;
}

void SpellTargetingAndDepletingParams::SetErrParam(int32 nParam)
{
	m_nErrParam = nParam;
}

BOOL SpellTargetingAndDepletingParams::IsDynamicParamIndexLegal(int32 nIndex) const
{
	if(0 <= nIndex && MAX_PARAM_NUMBER > nIndex)
	{
		return TRUE;
	}

	return FALSE;
}

int32 SpellTargetingAndDepletingParams::GetDynamicParamByIndex(int32 nIndex) const
{
	if(TRUE == IsDynamicParamIndexLegal(nIndex))
	{
		return m_aDynamicParams[nIndex];
	}

	return INVALID_ID;
}

void SpellTargetingAndDepletingParams::SetDynamicParamByIndex(int32 nIndex, int32 nValue)
{
	if(TRUE == IsDynamicParamIndexLegal(nIndex))
	{
		m_aDynamicParams[nIndex] = nValue;
	}
}

int32 SpellTargetingAndDepletingParams::GetHurtDelayTime() const
{
	return m_iHurtDelayTime;
}

void SpellTargetingAndDepletingParams::SetHurtDelayTime(int32 val)
{
	m_iHurtDelayTime = val;
}

void SpellTargetingAndDepletingParams::SetFindPlayerItemDataName(const char* name)
{
	strncpy(m_szFindPlayerItemName, name, MAX_CHARACTER_NAME);
}

const char* SpellTargetingAndDepletingParams::GetFindPlayerItemDataName()
{
	return m_szFindPlayerItemName;
}

void SpellTargetingAndDepletingParams::Reset(void)
{
	m_nActivatedSpell = INVALID_ID;
	m_nActivatedScript = INVALID_ID;

	m_nTargetObj = INVALID_ID;
	m_guidTargetPartner = INVALID_ID;
	m_posTargetPosition.Clear();
	m_fTargetDirection = 0.0f;
	m_nTargetBagSlot = INVALID_ID;
	m_guidTargetPet.Reset();

	m_bIgnoreConditionCheck = FALSE;

	m_nDepletedRage = 0;
	m_nDepletedStrikePoints = 0;
	m_guidDepletedItem.Reset();
	m_nBagIndexOfDepletedItem = INVALID_ID;
	m_nItemIndexOfDepletedItem = INVALID_ID;

	m_nDelayTime = 0;
	m_nTargetCount = 0;

	memset((void *) m_aDynamicParams, 0, sizeof(m_aDynamicParams));

	m_nErrCode = INVALID_ID;
	m_nErrParam = 0;
	m_iHurtDelayTime = 0;
	m_bDeletedItemBind = 0;

	memset(m_szFindPlayerItemName, 0, sizeof(m_szFindPlayerItemName));
}

/*
=======================================================================================================================
=======================================================================================================================
*/
SpellTargetingAndDepletingParams &SpellTargetingAndDepletingParams::operator=
(SpellTargetingAndDepletingParams const	 &rhs)
{
	m_nActivatedSpell = rhs.GetActivatedSpell();
	m_nActivatedScript = rhs.GetActivatedScript();

	m_nTargetObj = rhs.GetTargetObj();
	m_guidTargetPartner = rhs.GetTargetGuid();
	m_posTargetPosition = rhs.GetTargetPosition();
	m_fTargetDirection = rhs.GetTargetDirection();
	m_nTargetBagSlot = rhs.GetTargetBagSlot();
	m_guidTargetPet = rhs.GetTargetPetGuid();

	m_bIgnoreConditionCheck = rhs.GetIgnoreConditionCheckFlag();

	m_nDepletedRage = rhs.GetDepletedRage();
	m_nDepletedStrikePoints = rhs.GetDepletedStrikePoints();
	m_guidDepletedItem = rhs.GetDepletedItemGuid();
	m_nBagIndexOfDepletedItem = rhs.GetBagIndexOfDepletedItem();
	m_nItemIndexOfDepletedItem = rhs.GetItemIndexOfDepletedItem();

	m_nDelayTime = rhs.GetDelayTime();
	m_nTargetCount = rhs.GetTargetCount();

	for(int32 nIdx = 0; MAX_PARAM_NUMBER > nIdx; ++nIdx)
	{
		m_aDynamicParams[nIdx] = rhs.GetDynamicParamByIndex(nIdx);
	}

	memset((void *) m_aDynamicParams, 0, sizeof(m_aDynamicParams));

	m_nErrCode = rhs.GetErrCode();
	m_nErrParam = rhs.GetErrParam();
	m_iHurtDelayTime = rhs.m_iHurtDelayTime;
	return *this;
}

BOOL SpellTargetChecker::IsLegal(Character const &rTarget) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL AllTypesAreLegal::IsLegal(Character const &rTarget) const
{
	__GUARD__ if(!IsObjCharacter(rTarget.GetObjType()))
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
BOOL NonPlayerCharactersAreLegal::IsLegal(Character const &rTarget) const
{
	__GUARD__ if(!IsObjCharacter(rTarget.GetObjType())) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object::ObjectClass eObjType = rTarget.GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(eObjType)
	{
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_MONSTER:
		return TRUE;
		break;

	case Object::OBJECT_CLASS_PLAYER:
	default:
		return FALSE;
		break;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL OnlyPlayerCharacterIsLegal::IsLegal(Character const &rTarget) const
{
	__GUARD__ if(!IsObjCharacter(rTarget.GetObjType())) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object::ObjectClass eObjType = rTarget.GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(eObjType)
	{
	case Object::OBJECT_CLASS_PLAYER:
		return TRUE;
		break;

	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_MONSTER:
	default:
		return FALSE;
		break;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL OnlyPetIsLegal::IsLegal(Character const &rTarget) const
{
	__GUARD__ if(!IsObjCharacter(rTarget.GetObjType())) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object::ObjectClass eObjType = rTarget.GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(eObjType)
	{
	case Object::OBJECT_CLASS_PET:
		return TRUE;
		break;

	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	default:
		return FALSE;
		break;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL NonTypeIsLegal::IsLegal(Character const &rTarget) const
{
	__GUARD__ if(!IsObjCharacter(rTarget.GetObjType())) return FALSE;
	return FALSE;
	__UNGUARD__ return FALSE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
SpellInfo::SpellInfo() :
m_nSpellID(INVALID_ID),
m_nInstanceID(INVALID_ID),
m_nAccuracy(INVALID_ID),
m_nCriticalRate(INVALID_ID),
m_nDepleteRefixByValue(0),
m_nDepleteRefixByRate(0),
m_nPowerRefixByValue(0),
m_nPowerRefixByRate(0),
m_nTimeRefixByValue(0),
m_nTimeRefixByRate(0),
m_nCooldownTime(0),
m_nChargeTime(0),
m_nChannelTime(0),
m_iSpellLevel(0),
m_fMinSkillDistance(0),
m_fMaxSkillDistance(0),
m_ChargesOrInterval(1),
m_iMaxTargetNumber(1),
m_iSpellLogicCount(INVALID_ID),
m_iChannelBackRate(0),
m_iChannelBackHappanRate(0)
{
};

/*
=======================================================================================================================
=======================================================================================================================
*/
SpellInfo::SpellInfo(SpellInfo const &rhs) :
m_nSpellID(rhs.m_nSpellID),
m_nInstanceID(rhs.m_nInstanceID),
m_nAccuracy(rhs.m_nAccuracy),
m_nCriticalRate(rhs.m_nCriticalRate),
m_nDepleteRefixByValue(rhs.m_nDepleteRefixByValue),
m_nDepleteRefixByRate(rhs.m_nDepleteRefixByRate),
m_nPowerRefixByValue(rhs.m_nPowerRefixByValue),
m_nPowerRefixByRate(rhs.m_nPowerRefixByRate),
m_nTimeRefixByValue(rhs.m_nTimeRefixByValue),
m_nTimeRefixByRate(rhs.m_nTimeRefixByRate),
m_nCooldownTime(rhs.m_nCooldownTime),
m_nChargeTime(rhs.m_nChargeTime),
m_nChannelTime(rhs.m_nChannelTime),
m_iSpellLevel(rhs.m_nChannelTime),
m_fMinSkillDistance(rhs.m_fMinSkillDistance),
m_fMaxSkillDistance(rhs.m_fMaxSkillDistance),
m_ChargesOrInterval(rhs.m_ChargesOrInterval),
m_iMaxTargetNumber(rhs.m_iMaxTargetNumber),
m_iSpellLogicCount(rhs.m_iSpellLogicCount),
m_iChannelBackRate(rhs.m_iChannelBackRate),
m_iChannelBackHappanRate(rhs.m_iChannelBackHappanRate)
{
};

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellInfo::Init(void)
{
	m_nSpellID = INVALID_ID;
	m_nInstanceID = INVALID_ID;
	m_nAccuracy = INVALID_ID;
	m_nCriticalRate = INVALID_ID;
	m_nDepleteRefixByValue = 0;
	m_nDepleteRefixByRate = 0;
	m_nPowerRefixByValue = 0;
	m_nPowerRefixByRate = 0;
	m_nTimeRefixByValue = 0;
	m_nTimeRefixByRate = 0;
	m_nCooldownTime = 0;
	m_nChargeTime = 0;
	m_nChannelTime = 0;
	m_iSpellLevel = 0;
	m_fMinSkillDistance = 0;
	m_fMaxSkillDistance = 0;
	m_ChargesOrInterval = 1;
	m_iMaxTargetNumber = 1;
	m_iSpellLogicCount = INVALID_ID;
	m_iChannelBackRate = 0;
	m_iChannelBackHappanRate = 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
SpellInfo &SpellInfo::operator=(SpellTemplateData const &rhs)
{
	SetSpellID(rhs.GetSkillID());
	SetAccuracy(rhs.GetAccuracy());
	SetCriticalRate(rhs.GetCriticalRate());
	SetChannelBackRate(rhs.GetChannelBackRate());
	SetChannelBackHappanRate(rhs.GetChannelBackHappanRate());
	return *this;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
SpellInfo &SpellInfo::operator=(SpellInstanceData const &rhs)
{
	SetInstanceID(rhs.GetInstanceID());
	SetCooldownTime(rhs.GetCooldownTimeBySkillLevel(m_iSpellLevel));
	SetChargeTime(rhs.GetChargeTimeBySkillLevel(m_iSpellLevel));
	SetChannelTime(rhs.GetChannelTimeBySkillLevel(m_iSpellLevel));
	return *this;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
SpellInfo &SpellInfo::operator=(SpellInfo const &rhs)
{
	m_nSpellID = rhs.m_nSpellID;
	m_nInstanceID = rhs.m_nInstanceID;
	m_nAccuracy = rhs.m_nAccuracy;
	m_nCriticalRate = rhs.m_nCriticalRate;
	m_nDepleteRefixByValue = rhs.m_nDepleteRefixByValue;
	m_nDepleteRefixByRate = rhs.m_nDepleteRefixByRate;
	m_nPowerRefixByValue = rhs.m_nPowerRefixByValue;
	m_nPowerRefixByRate = rhs.m_nPowerRefixByRate;
	m_nTimeRefixByValue = rhs.m_nTimeRefixByValue;
	m_nTimeRefixByRate = rhs.m_nTimeRefixByRate;
	m_nCooldownTime = rhs.m_nCooldownTime;
	m_nChargeTime = rhs.m_nChargeTime;
	m_nChannelTime = rhs.m_nChannelTime;
	m_iSpellLevel = rhs.m_iSpellLevel;
	m_fMinSkillDistance = rhs.m_fMinSkillDistance;
	m_fMaxSkillDistance = rhs.m_fMaxSkillDistance;
	m_ChargesOrInterval = rhs.m_ChargesOrInterval;
	m_iMaxTargetNumber = rhs.m_iMaxTargetNumber;
	m_iSpellLogicCount = rhs.m_iSpellLogicCount;
	m_iChannelBackRate = rhs.m_iChannelBackRate;
	m_iChannelBackHappanRate = rhs.m_iChannelBackHappanRate;

	return *this;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 SpellInfo::GetProfession(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetProfession();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/

char const *SpellInfo::GetName(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetName();
	}

	return NULL;
	__UNGUARD__ return NULL;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetTalentLevelRequirement(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetTalentLevelRequirement();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::GetMustUseWeaponFlag(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetMustUseWeaponFlag();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::GetDisableByFlag1(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetDisableByFlag1();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::GetDisableByFlag2(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetDisableByFlag2();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::GetDisableByFlag3(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetDisableByFlag3();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetRangedSkillFlag(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetRangedSkillFlag();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::IsForceBreakPreSkill(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->ForceBreakPreSkill();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetTargetMustInSpecialState(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetTargetMustInSpecialState();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetSpellType(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetSkillType();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
CooldownID_t SpellInfo::GetCooldownID(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetCooldownID();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetSelectType(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetSelectType();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetOperateModeForPetSpell(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetOperateModeForPetSkill();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetPetRateOfSpell(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetPetRateOfSkill();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetTypeOfPetSpell(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetTypeOfPetSkill();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetImpactID(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetImpactIDOfSkill();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetTargetingLogic(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetTargetingLogic();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
Time_t SpellInfo::GetPlayActionTime(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetPlayActionTime();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
float SpellInfo::GetOptimalRangeMin(void) const
{
	__GUARD__ return m_fMinSkillDistance;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
float SpellInfo::GetOptimalRangeMax(void) const
{
	__GUARD__ return m_fMaxSkillDistance;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellInfo::SetOptimalRangeMax(float fDistance)
{
	m_fMaxSkillDistance = fDistance;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetStandFlag(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetStandFlag();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetTargetLogicByStand(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetTargetLogicByStand();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetSpeedOfBullet(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetSpeedOfBullet();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetHurtDelayTime(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetHurtDelayTime();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetTargetCheckByObjType(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetTargetCheckByObjType();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/

BOOL SpellInfo::IsPartyOnly(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->IsPartyOnly();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetChargesOrInterval(void) const
{
	__GUARD__ return m_ChargesOrInterval;
	__UNGUARD__ return 1;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::IsAutoShotSpell(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->IsAutoShotSkill();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::UseNormalAttackRate(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->UseNormalAttackRate();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
float SpellInfo::GetRadius(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetRadius();
	}

	return 0.0f;
	__UNGUARD__ return 0.0f;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
float SpellInfo::GetAngle(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetAngle();
	}

	return 0.0f;
	__UNGUARD__ return 0.0f;
};

float SpellInfo::GetRectangleWidth(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetSpellRectangleWidth();
	}

	return 0.0f;
	__UNGUARD__ return 0.0f;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::Get_Property_MaxTargetNumber(void) const
{
	__GUARD__ return m_iMaxTargetNumber;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellInfo::CanInterruptAutoShot(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->CanInterruptAutoShot();
	}

	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
Time_t SpellInfo::GetDelayTime(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetDelayTime();
	}

	return 0;
	__UNGUARD__ return 0;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ID_t SpellInfo::GetLogicID(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInstanceData const	*pInstance = DataManager::GetSingletonPtr()->getSpellInstance(m_nInstanceID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pInstance)
	{
		return pInstance->GetLogicID();
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
ConditionAndDepleteTerm const *SpellInfo::Get_Property_ConDepTermByIndex(int32 const nIdx) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInstanceData const	*pInstance = DataManager::GetSingletonPtr()->getSpellInstance(m_nInstanceID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pInstance)
	{
		return pInstance->Get_Property_ConDepTermByIndex(nIdx);
	}

	return NULL;
	__UNGUARD__ return NULL;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellInfo::GetSpellLevel(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInstanceData const	*pInstance = DataManager::GetSingletonPtr()->getSpellInstance(m_nInstanceID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pInstance)
	{
		return pInstance->GetSkillLevel();
	}

	return NULL;
	__UNGUARD__ return NULL;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
Descriptor const *SpellInfo::GetDescriptorByIndex(int32 const nIdx) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInstanceData const	*pInstance = DataManager::GetSingletonPtr()->getSpellInstance(m_nInstanceID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pInstance)
	{
		return pInstance->GetDescriptorByIndex(nIdx);
	}

	return NULL;
	__UNGUARD__ return NULL;
};

int32 SpellInfo::GetCharacterSpellLevel() const
{
	return m_iSpellLevel;
}

void SpellInfo::SetCharacterSpellLevel(int32 val)
{
	m_iSpellLevel = val;
}

int32 SpellInfo::GetChannelBackRate() const
{
	return m_iChannelBackRate;
}

void SpellInfo::SetChannelBackRate(int32 val)
{
	m_iChannelBackRate = val;
}

int32 SpellInfo::GetChannelBackHappanRate() const
{
	return m_iChannelBackHappanRate;
}

void SpellInfo::SetChannelBackHappanRate(int32 val)
{
	m_iChannelBackHappanRate = val;
}

int32 SpellInfo::GetSpellLogicCount() const
{
	return m_iSpellLogicCount;
}

void SpellInfo::SetSpellLogicCount(int32 val)
{
	m_iSpellLogicCount = val;
}

SpellID_t SpellInfo::GetInstanceID(void) const
{
	return m_nInstanceID;
};

void SpellInfo::SetInstanceID(SpellID_t const nID)
{
	m_nInstanceID = nID;
};
/*
=======================================================================================================================
=======================================================================================================================
*/

SpellID_t SpellInfo::GetSpellID(void) const
{
	return m_nSpellID;
};

void SpellInfo::SetSpellID(SpellID_t const nID)
{
	m_nSpellID = nID;
	InitOptimalRangeMin();
	InitOptimalRangeMax();
	InitChargesOrInterval();
	InitMaxTargetNumber();
}

int32 SpellInfo::GetAccuracy(void) const
{
	return m_nAccuracy;
}

void SpellInfo::SetAccuracy(int32 const nID)
{
	m_nAccuracy = nID;
}

int32 SpellInfo::GetCriticalRate(void) const
{
	return m_nCriticalRate;
}

void SpellInfo::SetCriticalRate(int32 const nRate)
{
	m_nCriticalRate = nRate;
}

int32 SpellInfo::GetDepleteRefixByValue(void) const
{
	return m_nDepleteRefixByValue;
}

void SpellInfo::SetDepleteRefixByValue(int32 nValue)
{
	m_nDepleteRefixByValue = nValue;
}

int32 SpellInfo::GetDepleteRefixByRate(void) const
{
	return m_nDepleteRefixByRate;
}

void SpellInfo::SetDepleteRefixByRate(int32 nRate)
{
	m_nDepleteRefixByRate = nRate;
}

int32 SpellInfo::GetPowerRefixByValue(void) const
{
	return m_nPowerRefixByValue;
}

void SpellInfo::SetPowerRefixByValue(int32 nValue)
{
	m_nPowerRefixByValue = nValue;
}

int32 SpellInfo::GetPowerRefixByRate(void) const
{
	return m_nPowerRefixByRate;
}

void SpellInfo::SetPowerRefixByRate(int32 nRate)
{
	m_nPowerRefixByRate = nRate;
}

int32 SpellInfo::GetTimeRefixByValue(void) const
{
	return m_nTimeRefixByValue;
}

void SpellInfo::SetTimeRefixByValue(int32 nValue)
{
	m_nTimeRefixByValue = nValue;
}

int32 SpellInfo::GetTimeRefixByRate(void) const
{
	return m_nTimeRefixByRate;
}

void SpellInfo::SetTimeRefixByRate(int32 nRate)
{
	m_nTimeRefixByRate = nRate;
}

Time_t SpellInfo::GetCooldownTime(void) const
{
	return m_nCooldownTime;
}

void SpellInfo::SetCooldownTime(Time_t const nTime)
{
	m_nCooldownTime = nTime;
}

Time_t SpellInfo::GetChargeTime(void) const
{
	return m_nChargeTime;
}

void SpellInfo::SetChargeTime(Time_t const nTime)
{
	m_nChargeTime = nTime;
}

Time_t SpellInfo::GetChannelTime(void) const
{
	return m_nChannelTime;
}

void SpellInfo::SetChannelTime(Time_t const nTime)
{
	m_nChannelTime = nTime;
}

float SpellInfo::GetMinSkillDistance() const
{
	return m_fMinSkillDistance;
}

void SpellInfo::SetMinSkillDistance(float val)
{
	m_fMinSkillDistance = val;
}

float SpellInfo::GetMaxSkillDistance() const
{
	return m_fMaxSkillDistance;
}

void SpellInfo::SetMaxSkillDistance(float val)
{
	m_fMaxSkillDistance = val;
}

void SpellInfo::SetChargesOrInterval(int32 val)
{
	m_ChargesOrInterval = val;
}

void SpellInfo::InitOptimalRangeMin()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		m_fMinSkillDistance = pTemplate->GetOptimalRangeMin(m_iSpellLevel);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellInfo::InitOptimalRangeMax()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		m_fMaxSkillDistance = pTemplate->GetOptimalRangeMax(m_iSpellLevel);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellInfo::InitChargesOrInterval()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_ChargesOrInterval = 1;
	if(NULL != pTemplate)
	{
		m_ChargesOrInterval = pTemplate->GetChargesOrInterval();
	}

	//m_ChargesOrInterval = m_ChargesOrInterval > 0 ? m_ChargesOrInterval : 1;
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellInfo::InitMaxTargetNumber()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		m_iMaxTargetNumber = pTemplate->Get_Property_MaxTargetNumber();
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellInfo::SetMaxTargetNumber(int32 val)
{
	m_iMaxTargetNumber = val;
}

int32 SpellInfo::GetControlType(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(m_nSpellID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pTemplate)
	{
		return pTemplate->GetControlType();
	}

	return -1;
	__UNGUARD__ return -1;
}

