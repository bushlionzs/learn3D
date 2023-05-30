/*$T MapServer/Server/Profession/Profession.cpp GC 1.140 10/10/07 10:07:46 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Profession_Base.h"
#include "TabDefine.h"
#include "data/data_manager.h"

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitToughness(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_TOUGHNESS, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitFarAttackPhysics(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_FARATTACK, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitNearAttackPhysics(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_NEARATTACK, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitFarDefencePhysics(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_FARDEFENCE_P, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitNearDefencePhysics(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_NEARDEFENCE_P, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitMaxRage(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_RAGE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitRageRegenerate(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_RAGERESTORE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::GetInitSkillPoint(void) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_SKILL, GetID(), 0);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Profession::OnEvent_Damage(Player &rMe, int32 nDamage) const
{
	if(0 >= nDamage)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRage = nDamage / 40;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*rMe.RefixRageRegeneration(nRage);
	rMe.RageIncrement(nRage, rMe.GetLogicCount(), NULL);*/
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void Profession::OnEvent_DamageTarget(Player &rMe, int32 nDamage) const
{
	if(0 >= nDamage)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRage = nDamage / 40;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*rMe.RefixRageRegeneration(nRage);
	rMe.RageIncrement(nRage, rMe.GetLogicCount(), NULL);*/
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_InitCon(void) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_CON, GetID(), 0);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_ConLevelupRefix(int16 const nLevel) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_CON, GetID(), nLevel); //获得增量
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_InitInt(void) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_INT, GetID(), 0);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_IntLevelupRefix(int16 const nLevel) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_INT, GetID(), nLevel);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_InitDex(void) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_DEX, GetID(), 0);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_DexLevelupRefix(int16 const nLevel) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_DEX, GetID(), nLevel);
}


/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MaxMPLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_MP, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitMPRegenerate(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_MPRESTORE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MPRegenerateLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_MPRESTORE, GetID());
}


/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MaxRageLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_RAGE, GetID());
}


/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_RageRegenerateLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_RAGERESTORE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitStr(void) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_STR, GetID(), 0);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_StrLevelupRefix(int16 const nLevel) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_STR, GetID(), nLevel);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::GetSkillPointLevelupRefix(int16 const nLevel) const
{
	return DataManager::GetSingletonPtr()->getAttrLevelUpValue(CPROPERTY_LEVEL_SKILL, GetID(), nLevel);
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_NearDefencePhysicsLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_NEARDEFENCE_P, GetID());
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_FarDefencePhysicsLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_FARDEFENCE_P, GetID());
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_NearAttackPhysicsStrRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_STR_NEARATTACK, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_NearAttackPhysicsDexRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_DEX_NEARATTACK, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_NearAttackPhysicsIntRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_INT_NEARATTACK, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_NearAttackPhysicsLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_NEARATTACK, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitAttackMagic(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_ATTACK_M, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_AttackMagicStrRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_STR_ATTACK_M, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_AttackMagicDexRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_DEX_ATTACK_M, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_AttackMagicIntRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_INT_ATTACK_M, GetID());
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_FarAttackPhysicsStrRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_STR_FARATTACK, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_FarAttackPhysicsDexRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_DEX_FARATTACK, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_FarAttackPhysicsIntRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_INT_FARATTACK, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_FarAttackPhysicsLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_FARATTACK, GetID());
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_ToughnessLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_TOUGHNESS, GetID());
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_AttackMagicLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_ATTACK_M, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_InitDefenceMagic(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_DEFENCE_M, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_DefenceMagicLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_DEFENCE_M, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_InitHit(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_HIT, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_HitStrRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_STR_HIT, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_HitLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_HIT, GetID());
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_MissLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_MISS, GetID());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int16 Profession::Get_Property_AttackFluctuation(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_ATTACK_FLUCTUATION, GetID());
}


/*
=======================================================================================================================
=======================================================================================================================
*/

int16 Profession::Get_Property_InitMaxHP(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_HP, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MaxHPConRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_CON_HP, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MaxHPLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_HP, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitHPRegenerate(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_HPRESTORE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_HPRegenerateLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_HPRESTORE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitMaxMP(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_MP, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MaxRageIntRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_INT_RAGE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitCritical(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_CRITRATE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_CriticalIntRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_INT_CRITRATE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_CriticalLevelRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_LEVEL_CRITRATE, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_InitMiss(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_BASE_MISS, GetID());
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int16 Profession::Get_Property_MissDexRefix(void) const
{
	return DataManager::GetSingletonPtr()->getProfessionProperty(AINFOTYPE_DEX_MISS, GetID());
}
