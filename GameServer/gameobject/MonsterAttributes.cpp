#include "stdafx.h"
#include "TypeDefine.h"
#include "Define.h"
#include "Enum.h"
#include "Monster.h"
#include "TabDefine.h"
#include "Behavior_Monster.h"
#include "data/data_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetMaxHP(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_HP))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_MaxHP() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_MAX_HP, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAX_HP);
		if(GetHP() > nValue) SetHP(nValue);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MAX_HP);

	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_MaxHP(void)
{
	__GUARD__ return m_iMaxHP;

	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_MaxHP(int32 const nHp)
{
	m_iMaxHP = nHp;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_HPRegenerate(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HP_REGENERATE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_HPRegenerate() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_HP_REGENERATE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_HP_REGENERATE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HP_REGENERATE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_HP_REGENERATE);

	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_HPRegenerate(void)
{
	__GUARD__ return m_iHPRestore;

	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_HPRegenerate(int32 const nValue)
{
	m_iHPRestore = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_MaxMP(void)
{
	return m_iMaxMP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_MaxMp(int32 const nMp)
{
	m_iMaxMP = nMp;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_MPRegenerate(void)
{
	return m_iMPRestore;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_MPRegenerate(int32 const nValue)
{
	m_iMPRestore = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const SCampData *Monster::GetBaseCampData(void) const
{
	return &m_CampData;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseCampData(const SCampData *pCampData)
{
	m_CampData = *pCampData;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetCampID(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CAMP))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CAMP);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID == nValue)
		{
			nValue = GetBaseCampID();
		}

		SetIntAttr(CharIntProperty::PROPERTY_CAMP, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CAMP);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_CAMP);

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseCampID(void) const
{
	return m_CampData.m_nCampID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseCampID(int32 const nID)
{
	__GUARD__ m_CampData.m_nCampID = nID;
	MarkIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CAMP);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetModelID(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MODEL_ID))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MODEL_ID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID == nValue)
		{
			nValue = Get_BaseProperty_ModelID();
		}

		SetIntAttr(CharIntProperty::PROPERTY_MODEL_ID, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MODEL_ID);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MODEL_ID);
	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_ModelID(void) const
{
	return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_ModelID(int32 const nID)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Monster::IsUnbreakable(void)
{
	__GUARD__ return Character::IsUnbreakable();
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Monster::Get_Property_MoveSpeed(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVE_SPEED))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_MoveSpeed() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_MOVE_SPEED, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVE_SPEED);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fMoveSpeed = GetIntAttr(CharIntProperty::PROPERTY_MOVE_SPEED) * 0.001f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return fMoveSpeed;
	__UNGUARD__ return 1.0f;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_MoveSpeed(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ENUM_MOVE_MODE	eMoveMode = GetMoveMode();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(eMoveMode == MOVE_MODE_WALK)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		MonsterProperty	*pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(GetDataID());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pAttr)
		{
			return pAttr->m_WalkSpeed;
		}
	}

	return DataManager::GetSingletonPtr()->getMonsterProperty(m_uDataID, CPROPERTY_LEVEL2_SPEED);

	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_MoveSpeed(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_AttackSpeed(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_SPEED))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_AttackSpeed() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_SPEED);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(400 < nValue)
		{
			nValue = 400;
		}

		if(25 >= nValue)
		{
			nValue = 25;
		}

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_SPEED, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_SPEED);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_SPEED);
	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_AttackSpeed(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nAttackSpeed = DataManager::GetSingletonPtr()->getMonsterProperty(m_uDataID, CPROPERTY_LEVEL2_ATTACKSPEED);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(75 < nAttackSpeed)
	{
		nAttackSpeed = 75;
	}

	if(-300 > nAttackSpeed)
	{
		nAttackSpeed = -300;
	}

	nAttackSpeed = BASE_ATTACK_SPEED - nAttackSpeed;
	return BASE_ATTACK_SPEED;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_AttackSpeed(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_Miss(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MISS))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_Miss() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MISS);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_MISS, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MISS);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MISS);
	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_Miss(void)
{
	return m_iMissRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_Miss(int32 const nValue)
{
	m_iMissRate = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_Hit(void)
{
	__GUARD__ if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HIT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_Hit() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_HIT);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_HIT, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HIT);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_HIT);
	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_Hit(void)
{
	return m_iHitRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_Hit(int32 const nValue)
{
	m_iHitRate = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_Critical(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CRITICAL))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_Critical() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_CRITICAL, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_CRITICAL);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_CRITICAL);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_Critical(void)
{
	return m_iCriticalRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_Critical(int32 const nValue)
{
	m_iCriticalRate = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetDefenceNear(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_NEAR))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseDefenceNear() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_DEFENCE_NEAR, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_NEAR);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_DEFENCE_NEAR);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseDefenceNear(void)
{
	return m_iDefenceNear;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseDefenceNear(int32 const nValue)
{
	m_iDefenceNear = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetDefenceFar(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_FAR))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseDefenceFar() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_DEFENCE_FAR, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_FAR);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_DEFENCE_FAR);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseDefenceFar(void)
{
	return m_iDefenceFar;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseDefenceFar(int32 const nValue)
{
	m_iDefenceFar = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetAttackNear(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_NEAR))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseAttackNear() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_NEAR, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_NEAR);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_NEAR);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseAttackNear(void)
{
	return m_iAttackNear;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseAttackNear(int32 const nValue)
{
	m_iAttackNear = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetAttackFar(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_FAR))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseAttackFar() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_FAR, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_FAR);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_FAR);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseAttackFar(void)
{
	return m_iAttackFar;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseAttackFar(int32 const nValue)
{
	m_iAttackFar = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetToughness(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_TOUGHNESS))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseToughness() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_TOUGHNESS);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_TOUGHNESS, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_TOUGHNESS);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_TOUGHNESS);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseToughness(void)
{
	return DataManager::GetSingletonPtr()->getMonsterProperty(m_uDataID, CPROPERTY_LEVEL2_TOUGHNESS);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseToughness(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetNearAttReduce(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_NEARATT_REDUCE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseNearAttReduce() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_NEARATT_REDUCE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_NEARATT_REDUCE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_NEARATT_REDUCE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_NEARATT_REDUCE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseNearAttReduce(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseNearAttReduce(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetFarAttReduce(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_FARATT_REDUCE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseFarAttReduce() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_FARATT_REDUCE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_FARATT_REDUCE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_FARATT_REDUCE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_FARATT_REDUCE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseFarAttReduce(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseFarAttReduce(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetMagicAttReduce(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAGICATT_REDUCE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseMagicAttReduce() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAGICATT_REDUCE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_MAGICATT_REDUCE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MAGICATT_REDUCE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MAGICATT_REDUCE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseMagicAttReduce(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseMagicAttReduce(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetDreadAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DREAD_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseDreadAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_DREAD_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_DREAD_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DREAD_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_DREAD_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseDreadAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseDreadAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetComaAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_COMA_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseComaAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_COMA_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_COMA_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_COMA_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_COMA_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseComaAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseComaAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetHushAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HUSH_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseHushAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_HUSH_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_HUSH_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_HUSH_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_HUSH_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseHushAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseHushAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetUnArmyAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_UNARMY_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseUnArmyAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_UNARMY_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_UNARMY_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_UNARMY_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_UNARMY_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseUnArmyAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseUnArmyAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetAttSpeedAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACKSPEED_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseAttSpeedAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACKSPEED_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACKSPEED_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACKSPEED_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACKSPEED_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseAttSpeedAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseAttSpeedAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetSkillSpeedAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_SKILLSPEED_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseSkillSpeedAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_SKILLSPEED_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_SKILLSPEED_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_SKILLSPEED_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_SKILLSPEED_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseSkillSpeedAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseSkillSpeedAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetMoveSpeedAttResist(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVEREDUCE_RESIST))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseMoveSpeedAttResist() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVEREDUCE_RESIST);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_MOVEREDUCE_RESIST, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_MOVEREDUCE_RESIST);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_MOVEREDUCE_RESIST);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetBaseMoveSpeedAttResist(void)
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::SetBaseMoveSpeedAttResist(int32 const nValue)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_AttackMagic(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_MAGIC))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_AttackMagic() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_MAGIC, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_MAGIC);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_MAGIC);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_AttackMagic(void)
{
	return m_iAttackMagic;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_AttackMagic(int32 const nValue)
{
	m_iAttackMagic = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_DefenceMagic(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_MAGIC))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_DefenceMagic() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_DEFENCE_MAGIC, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_DEFENCE_MAGIC);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_DEFENCE_MAGIC);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_DefenceMagic(void)
{
	return m_iDefenceMagic;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_DefenceMagic(int32 const nValue)
{
	m_iDefenceMagic = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_AttackCold(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_COLD))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_AttackCold() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_COLD, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_COLD);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_COLD);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_AttackCold(void)
{
	return m_iAttackCold;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_AttackCold(int32 const nValue)
{
	m_iAttackCold = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_DefenceCold(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_COLD))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_DefenceCold() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_RESIST_COLD, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_COLD);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_RESIST_COLD);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_DefenceCold(void)
{
	return m_iDefenceCold;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_DefenceCold(int32 const nValue)
{
	m_iDefenceCold = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_AttackFire(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_FIRE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_AttackFire() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_FIRE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_FIRE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_FIRE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_AttackFire(void)
{
	return m_iAttackFire;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_AttackFire(int32 const nValue)
{
	m_iAttackFire = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_DefenceFire(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_FIRE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_DefenceFire() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_RESIST_FIRE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_FIRE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_RESIST_FIRE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_DefenceFire(void)
{
	return m_iDefenceFire;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_DefenceFire(int32 const nValue)
{
	m_iDefenceFire = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_AttackLight(void)
{
	if(TRUE ==  GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_LIGHT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_AttackLight() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_LIGHT, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_LIGHT);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_LIGHT);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_AttackLight(void)
{
	return m_iAttackLight;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_AttackLight(int32 const nValue)
{
	m_iAttackLight = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_DefenceLight(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_LIGHT))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_DefenceLight() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_RESIST_LIGHT, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_LIGHT);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_RESIST_LIGHT);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_DefenceLight(void)
{
	return m_iDefenceLight;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_DefenceLight(int32 const nValue)
{
	m_iDefenceLight = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_AttackPoison(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_POISON))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_AttackPoison() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_ATTACK_POISON, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_ATTACK_POISON);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_ATTACK_POISON);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_AttackPoison(void)
{
	return m_iAttackPoison;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_AttackPoison(int32 const nValue)
{
	m_iAttackPoison = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_DefencePoison(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_POISON))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = Get_BaseProperty_DefencePoison() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_RESIST_POISON, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_RESIST_POISON);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_RESIST_POISON);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_BaseProperty_DefencePoison(void)
{
	return m_iDefencePoison;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Set_BaseProperty_DefencePoison(int32 const nValue)
{
	m_iDefencePoison = nValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_ReduceSlowerDuration(void)
{
	return GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_REDUCE_SLOWER_DURATION);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_ReduceWeakenDuration(void)
{
	return GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_REDUCE_WEAKEN_DURATION);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_ReduceFaintDuration(void)
{
	return GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_REDUCE_FAINT_DURATION);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::Get_Property_ReducePoisonedDuration(void)
{
	return GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_REDUCE_POISONED_DURATION);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Monster::GetVisionRange(void)
{
	if(TRUE == GetIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_VISION_RANGE))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nValue = GetBaseVisionRange() + GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_PROPERTY_VISION_RANGE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetIntAttr(CharIntProperty::PROPERTY_VISION_RANGE, nValue);
		ClearIntAttrDirtyFlag_EX(CharIntProperty::PROPERTY_VISION_RANGE);
	}

	return GetIntAttr(CharIntProperty::PROPERTY_VISION_RANGE);
}

