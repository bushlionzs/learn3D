/*$T MapServer/Server/Profession/Profession.h GC 1.140 10/10/07 10:07:46 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _PROFESSION_H_
#define _PROFESSION_H_

#include "TypeDefine.h"
#include "Player.h"

class	Profession
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = PROFESSION_NONE, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Profession()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~Profession()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual int32 GetID(void) const
	{
		return PROFESSION_UNKNOW;
	};
	
	//全部都是Get, 没有Set, 这个类没有数据
	int16		GetInitMaxRage(void) const;
	int16		GetInitRageRegenerate(void) const;
	int16		GetInitSkillPoint(void) const;
	int16		GetSkillPointLevelupRefix(int16 const nLevel) const;
	int16		GetInitNearDefencePhysics(void) const;
	int16		GetInitFarDefencePhysics(void) const;
	int16		GetInitNearAttackPhysics(void) const;
	int16		GetInitFarAttackPhysics(void) const;
	int16		GetInitToughness(void) const;

	virtual void OnEvent_Damage(Player &rMe, int32 nDamage) const;
	virtual void OnEvent_DamageTarget(Player &rMe, int32 nDamage) const;
	virtual void OnEvent_HealTarget(Player &rMe, int32 nHealedHp) const{};
	virtual void OnEvent_DepleteStrikePoints(Player &rMe, int32 nStrikePoint) const{};

	int16		Get_Property_InitMaxHP(void) const;
	int16		Get_Property_MaxHPConRefix(void) const;
	int16		Get_Property_MaxHPLevelRefix(void) const;
	int16		Get_Property_InitHPRegenerate(void) const;
	int16		Get_Property_HPRegenerateLevelRefix(void) const;
	int16		Get_Property_InitMaxMP(void) const;
	int16		Get_Property_MaxRageIntRefix(void) const;
	int16		Get_Property_MaxMPLevelRefix(void) const;
	int16		Get_Property_InitMPRegenerate(void) const;
	int16		Get_Property_MPRegenerateLevelRefix(void) const;
	int16		Get_Property_MaxRageLevelRefix(void) const;
	int16		Get_Property_RageRegenerateLevelRefix(void) const;
	int16		Get_Property_InitStr(void) const;
	int16		Get_Property_StrLevelupRefix(int16 const nLevel) const;
	int16		Get_Property_InitCon(void) const;
	int16		Get_Property_ConLevelupRefix(int16 const nLevel) const;
	int16		Get_Property_InitInt(void) const;
	int16		Get_Property_IntLevelupRefix(int16 const nLevel) const;
	int16		Get_Property_InitDex(void) const;
	int16		Get_Property_DexLevelupRefix(int16 const nLevel) const;
	int16		Get_Property_AttackMagicLevelRefix(void) const;
	int16		Get_Property_InitDefenceMagic(void) const;
	int16		Get_Property_DefenceMagicLevelRefix(void) const;
	int16		Get_Property_InitHit(void) const;
	int16		Get_Property_InitAttackMagic(void) const;
	int16		Get_Property_HitLevelRefix(void) const;
	int16		Get_Property_InitCritical(void) const;
	int16		Get_Property_CriticalLevelRefix(void) const;
	int16		Get_Property_InitMiss(void) const;
	int16		Get_Property_MissDexRefix(void) const;
	int16		Get_Property_MissLevelRefix(void) const;
	int16		Get_Property_AttackFluctuation(void) const;
	int16		Get_Property_NearDefencePhysicsLevelRefix(void) const;
	int16		Get_Property_FarDefencePhysicsLevelRefix(void) const;
	int16		Get_Property_NearAttackPhysicsStrRefix(void) const;
	int16		Get_Property_NearAttackPhysicsDexRefix(void) const;
	int16		Get_Property_NearAttackPhysicsIntRefix(void) const;
	int16		Get_Property_NearAttackPhysicsLevelRefix(void) const;
	int16		Get_Property_FarAttackPhysicsStrRefix(void) const;
	int16		Get_Property_FarAttackPhysicsDexRefix(void) const;
	int16		Get_Property_FarAttackPhysicsIntRefix(void) const;
	int16		Get_Property_FarAttackPhysicsLevelRefix(void) const;
	int16		Get_Property_ToughnessLevelRefix(void) const;
	int16		Get_Property_HitStrRefix(void) const;
	int16		Get_Property_AttackMagicStrRefix(void) const;
	int16		Get_Property_AttackMagicDexRefix(void) const;
	int16		Get_Property_AttackMagicIntRefix(void) const;
	int16		Get_Property_CriticalIntRefix(void) const;


protected:
private:
	virtual int32 TransferValueToRage(int32 nDamage) const{	return 0;};
};
#endif
