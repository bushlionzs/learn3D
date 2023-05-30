/*$T MapServer/Server/Spell/EffectLogic/SpellEffect.cpp GC 1.140 10/10/07 10:07:54 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Spell_EffectLogic_All.h"
#include "gameobject/Behavior_Monster.h"
#include "data/data_manager.h"
#include "script/LuaSystem.h"
#include "map/map_info.h"
#include "server_manager.h"
#include "ScriptDef.h"
#include "horse/CreateHorseCommand.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void SpellEffect000::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect001::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nDamage = rData.GetDescriptorByIndex(ImpactDataDescriptorIndex::IDX_DAMAGE)->GetValueBySkillLevel(rImp.GetSkillLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamage(rImp, nDamage);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect001::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage = GetDamage(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rMe.OnEvent_Damage
	(
		nDamage,
		rImp.GetCasterObjID(),
		rImp.IsCriticalHit(),
		rImp.GetSkillID(),
		rImp.GetCasterLogicCount()
	);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect001::CriticalRefix(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamage(rImp, GetDamage(rImp) * 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rImp.MarkCriticalFlag();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect001::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetDamage(rImp, Float2Int((GetDamage(rImp) * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect002::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nDamage = rData.GetDescriptorByIndex(ImpactDataDescriptorIndex::IDX_DAMAGE)->GetValueBySkillLevel(rImp.GetSkillLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamage(rImp, nDamage);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect002::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage = GetDamage(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nDamage)
	{
		return;
	}

	nDamage = Float2Int((rMe.Get_BaseProperty_MaxHP() * nDamage) / 100.0f);
	rMe.OnEvent_Damage(nDamage, rImp.GetCasterObjID(), rImp.IsFadeOut(), rImp.GetSkillID(), rImp.GetCasterLogicCount());
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect002::CriticalRefix(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamage(rImp, GetDamage(rImp) * 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rImp.MarkCriticalFlag();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect002::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetDamage(rImp, Float2Int((GetDamage(rImp) * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect003::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamageNear
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_DAMAGE_NEAR,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageFar
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FAR,
				rImp.GetSkillLevel()
			)
	);
	SetDamageMagic
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_MAGIC,
				rImp.GetSkillLevel()
			)
	);
	SetDamageCold
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_COLD,
				rImp.GetSkillLevel()
			)
	);
	SetDamageFire
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FIRE,
				rImp.GetSkillLevel()
			)
	);
	SetDamageLight
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_LIGHT,
				rImp.GetSkillLevel()
			)
	);
	SetDamagePoison
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_POISON,
				rImp.GetSkillLevel()
			)
	);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect003::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	if (rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		//普通攻击 zhousha
		int kk = 0;
	}
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDeltaHP = rMe.GetHP();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vDamage[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDamage[DAMAGE_TYPE_NEAR] = GetDamageNear(rImp);
	vDamage[DAMAGE_TYPE_FAR] = GetDamageFar(rImp);
	vDamage[DAMAGE_TYPE_M] = GetDamageMagic(rImp);
	vDamage[DAMAGE_TYPE_COLD] = GetDamageCold(rImp);
	vDamage[DAMAGE_TYPE_FIRE] = GetDamageFire(rImp);
	vDamage[DAMAGE_TYPE_LIGHT] = GetDamageLight(rImp);
	vDamage[DAMAGE_TYPE_POISON] = GetDamagePoison(rImp);

	rMe.OnEvent_Damages
	(
		vDamage,
		rImp.GetCasterObjID(),
		rImp.IsCriticalHit(),
		rImp.GetSkillID(),
		rImp.GetCasterLogicCount()
	);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect003::CriticalRefix(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamageNear(rImp, GetDamageNear(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageFar(rImp, GetDamageFar(rImp));
	SetDamageMagic(rImp, GetDamageMagic(rImp));
	SetDamageCold(rImp, GetDamageCold(rImp));
	SetDamageFire(rImp, GetDamageFire(rImp));
	SetDamageLight(rImp, GetDamageLight(rImp));
	SetDamagePoison(rImp, GetDamagePoison(rImp));
	rImp.MarkCriticalFlag();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect003::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTemp = GetDamageNear(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageNear(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFar(rImp);
	SetDamageFar(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageMagic(rImp);
	SetDamageMagic(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageCold(rImp);
	SetDamageCold(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFire(rImp);
	SetDamageFire(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageLight(rImp);
	SetDamageLight(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamagePoison(rImp);
	SetDamagePoison(rImp, Float2Int((iTemp * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect004::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetHpModification
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_HP,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetMpModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_MP,
				rImp.GetSkillLevel()
			)
	);
	SetRageModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE,
				rImp.GetSkillLevel()
			)
	);
	SetRage1Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE1,
				rImp.GetSkillLevel()
			)
	);
	SetRage2Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE2,
				rImp.GetSkillLevel()
			)
	);
	SetRage3Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE3,
				rImp.GetSkillLevel()
			)
	);
	SetRage4Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE4,
				rImp.GetSkillLevel()
			)
	);
	SetRage5Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE5,
				rImp.GetSkillLevel()
			)
	);
	SetRefixRate
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_REFIX_RATE,
				rImp.GetSkillLevel()
			)
	);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect004::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pImpactSender)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamage = GetDamageRefix(pImpactSender, rImp);
	int32	nHP = GetHpModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != nHP)
	{
		nHP = nHP + iDamage;
		if(nHP != 0)
		{
			rMe.HealthIncrement(nHP, rImp.GetCasterLogicCount(), pImpactSender);
		}
	}

	if(NULL != pImpactSender)
	{
		pImpactSender->OnEvent_HealTarget(rImp.GetSkillID(), rMe, nHP);
	}

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iRageModify = static_cast<Player &>(rMe).GetProfession();
		int32	nRage = INVALID_ID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch(iRageModify)
		{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:		
			nRage = GetRageModification(rImp); 
		break;
		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:		
			nRage = GetRage1Modification(rImp); 
		break;
		case PROFESSION_QISHE:	
		case PROFESSION_CIKE:	
			nRage = GetRage2Modification(rImp); 
		break;
		case PROFESSION_HUOQIANG:	
		case PROFESSION_JINWEIJUN:		
			nRage = GetRage3Modification(rImp); 
		break;
		case PROFESSION_XIANZHI:
		case PROFESSION_YINXIUSHI:		
			nRage = GetRage4Modification(rImp); 
		break;
		case PROFESSION_SAMAN:
		case PROFESSION_LAMA:		
			nRage = GetRage5Modification(rImp); 
		break;
		default:	break;
		}

		if(INVALID_ID != nRage)
		{
			nRage += iDamage;
			rMe.RageIncrement(nRage, rImp.GetCasterLogicCount(), pImpactSender);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect004::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetHpModification(rImp, Float2Int((GetHpModification(rImp) * nRate) / 100.0f));
	SetMpModification(rImp, Float2Int((GetMpModification(rImp) * nRate) / 100.0f));

	SetRageModification(rImp, Float2Int((GetRageModification(rImp) * nRate) / 100.0f));
	SetRage1Modification(rImp, Float2Int((GetRage1Modification(rImp) * nRate) / 100.0f));
	SetRage2Modification(rImp, Float2Int((GetRage2Modification(rImp) * nRate) / 100.0f));
	SetRage3Modification(rImp, Float2Int((GetRage3Modification(rImp) * nRate) / 100.0f));
	SetRage4Modification(rImp, Float2Int((GetRage4Modification(rImp) * nRate) / 100.0f));
	SetRage5Modification(rImp, Float2Int((GetRage5Modification(rImp) * nRate) / 100.0f));

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect004::GetDamageRefix(Character *pImpactSender, UNIT_EFFECT &rImp) const
{
	if(pImpactSender->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = static_cast<Player *>(pImpactSender);
	int32	iDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if( PROFESSION_WUSHI == pPlayer->GetProfession() || 
		PROFESSION_SHIZIJUN == pPlayer->GetProfession() ||
		PROFESSION_JIANXIA == pPlayer->GetProfession() ||
		PROFESSION_SHENGHUOSHI == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackNear();
	}
	else if(PROFESSION_QISHE == pPlayer->GetProfession() || 
		PROFESSION_CIKE == pPlayer->GetProfession() ||
		PROFESSION_HUOQIANG == pPlayer->GetProfession() ||
		PROFESSION_JINWEIJUN == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackFar();
	}
	else
	{
		iDamage = pPlayer->Get_Property_AttackMagic();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDamage = Float2Int(iDamage * iRefixRate * 0.01f);
	return iDamage;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect005::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetHpModification
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_HP,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetMpModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_MP,
				rImp.GetSkillLevel()
			)
	);
	SetRageModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE,
				rImp.GetSkillLevel()
			)
	);
	SetRage1Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE1,
				rImp.GetSkillLevel()
			)
	);
	SetRage2Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE2,
				rImp.GetSkillLevel()
			)
	);
	SetRage3Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE3,
				rImp.GetSkillLevel()
			)
	);
	SetRage4Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE4,
				rImp.GetSkillLevel()
			)
	);
	SetRage5Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE5,
				rImp.GetSkillLevel()
			)
	);
	SetRefixRate
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_REFIX_RATE,
				rImp.GetSkillLevel()
			)
	);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect005::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pImpactSender == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamage = GetDamageRefix(pImpactSender, rImp);
	int32	nHP = GetHpModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != nHP)
	{
		nHP = Float2Int((nHP * rMe.Get_BaseProperty_MaxHP()) / 100.0f);
		nHP += iDamage;
		rMe.HealthIncrement(nHP, rImp.GetCasterLogicCount(), pImpactSender);
	}

	if(NULL == pImpactSender)
	{
		pImpactSender->OnEvent_HealTarget(rImp.GetSkillID(), rMe, nHP);
	}

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iRageModify = static_cast<Player &>(rMe).GetProfession();
		int32	nRage = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch(iRageModify)
		{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:		
			nRage = GetRageModification(rImp); 
		break;
		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:		
			nRage = GetRage1Modification(rImp); 
		break;
		case PROFESSION_QISHE:	
		case PROFESSION_CIKE:		
			nRage = GetRage2Modification(rImp); 
		break;
		case PROFESSION_HUOQIANG:	
		case PROFESSION_JINWEIJUN:		
			nRage = GetRage3Modification(rImp); 
		break;
		case PROFESSION_XIANZHI:
		case PROFESSION_YINXIUSHI:	
			nRage = GetRage4Modification(rImp); 
			break;
		case PROFESSION_SAMAN:
		case PROFESSION_LAMA:	
			nRage = GetRage5Modification(rImp); 
		break;
		default:	break;
		}

		if(INVALID_ID != nRage)
		{
			nRage = Float2Int((nRage * rMe.GetBaseMaxRage()) / 100.0f);
			nRage += iDamage;
			rMe.RageIncrement(nRage, rImp.GetCasterLogicCount(), pImpactSender);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect005::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetHpModification(rImp, Float2Int((GetHpModification(rImp) * nRate) / 100.0f));
	SetMpModification(rImp, Float2Int((GetMpModification(rImp) * nRate) / 100.0f));
	SetRageModification(rImp, Float2Int((GetRageModification(rImp) * nRate) / 100.0f));

	SetRage1Modification(rImp, Float2Int((GetRage1Modification(rImp) * nRate) / 100.0f));
	SetRage2Modification(rImp, Float2Int((GetRage2Modification(rImp) * nRate) / 100.0f));
	SetRage3Modification(rImp, Float2Int((GetRage3Modification(rImp) * nRate) / 100.0f));
	SetRage4Modification(rImp, Float2Int((GetRage4Modification(rImp) * nRate) / 100.0f));
	SetRage5Modification(rImp, Float2Int((GetRage5Modification(rImp) * nRate) / 100.0f));

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect005::GetDamageRefix(Character *pImpactSender, UNIT_EFFECT &rImp) const
{
	if(pImpactSender->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = static_cast<Player *>(pImpactSender);
	int32	iDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if( PROFESSION_WUSHI == pPlayer->GetProfession() || 
		PROFESSION_SHIZIJUN == pPlayer->GetProfession() ||
		PROFESSION_JIANXIA == pPlayer->GetProfession() ||
		PROFESSION_SHENGHUOSHI == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackNear();
	}
	else if(PROFESSION_QISHE == pPlayer->GetProfession() || 
		PROFESSION_CIKE == pPlayer->GetProfession() ||
		PROFESSION_HUOQIANG == pPlayer->GetProfession() ||
		PROFESSION_JINWEIJUN == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackFar();
	}
	else
	{
		iDamage = pPlayer->Get_Property_AttackMagic();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDamage = Float2Int(iDamage * iRefixRate * 0.01f);
	return iDamage;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect006::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetHpModification
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_HP,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetHappinessModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_HAPPINESS,
				rImp.GetSkillLevel()
			)
	);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect006::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PET != rMe.GetObjType())
	{
		return;
	}

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Pet		&rPet = (Pet &) rMe;
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	int32		nHP = GetHpModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rPet.HealthIncrement(nHP, rImp.GetCasterLogicCount(), pImpactSender);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nHappiness = GetHappinessModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//rPet.IncrementHappyness(nHappiness);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect006::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetHpModification(rImp, Float2Int((GetHpModification(rImp) * nRate) / 100.0f));
	SetHappinessModification(rImp, Float2Int((GetHappinessModification(rImp) * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect007::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetHpModification
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_HP,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetHappinessModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_HAPPINESS,
				rImp.GetSkillLevel()
			)
	);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect007::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PET != rMe.GetObjType())
	{
		return;
	}

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Pet		&rPet = (Pet &) rMe;
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	int32		nHP = GetHpModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP += 100;
	nHP = Float2Int((nHP * rPet.Get_BaseProperty_MaxHP()) / 100.0f);
	rPet.HealthIncrement(nHP, rImp.GetCasterLogicCount(), pImpactSender);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nHappiness = GetHappinessModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHappiness += 100;
	nHappiness = Float2Int((nHappiness * PET_BASE_MAX_HAPPINESS) / 100.0f);
	//rPet.IncrementHappyness(nHappiness);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect007::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetHpModification(rImp, Float2Int((GetHpModification(rImp) * nRate) / 100.0f));
	SetHappinessModification(rImp, Float2Int((GetHappinessModification(rImp) * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect008::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj || !IsObjCharacter(pObj->GetObjType()))
	{
		return;
	}

	if(Object::OBJECT_CLASS_MONSTER != rMe.GetObjType() || !rMe.IsAlive())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster		&rMonster = (Monster &) rMe;
	Behavior_Monster	*pAI = (Behavior_Monster *) (rMonster.GetMonsterAI());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pAI)
	{
		return;
	}

	if(ESTATE_TERROR == pAI->GetBehavior_State()->GetStateID())
	{
		return;
	}

	if(0 >= pAI->BHVParam(BHVPARAM_STRIKEBACK))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iModThreat = GetModThreat(rImp, rImp.GetSkillLevel());
	Character	*pCurEnemy = pAI->GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAI->ModThreatByPtr((Character *) pObj, iModThreat);
	if(pCurEnemy != pAI->GetNextTarget())
	{
		pAI->ToBHVApproachTar();
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect008::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj || !IsObjCharacter(pObj->GetObjType()))
	{
		return;
	}

	if(Object::OBJECT_CLASS_MONSTER != rMe.GetObjType())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster		&rMonster = (Monster &) rMe;
	Behavior_Monster	*pAI = (Behavior_Monster *) (rMonster.GetMonsterAI());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pAI)
	{
		return;
	}

	if(ESTATE_TERROR == pAI->GetBehavior_State()->GetStateID())
	{
		return;
	}

	if(0 >= pAI->BHVParam(BHVPARAM_STRIKEBACK))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iModThreat = GetModThreat(rImp, rImp.GetSkillLevel());
	Character	*pCurEnemy = pAI->GetNextTarget();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAI->ModThreatByPtr((Character *) pObj, -iModThreat);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect009::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetSceneID
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_SCENE_ID,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetPosition_X
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_POSITION_X,
				rImp.GetSkillLevel()
			) + 0.f
	);
	SetPosition_Z
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_POSITION_Z,
				rImp.GetSkillLevel()
			) + 0.f
	);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect009::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	pos;
	MapID_t		nScene = GetSceneID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pos.m_fX = GetPosition_X(rImp) / 100.0f;
	pos.m_fZ = GetPosition_Z(rImp) / 100.0f;
	if(INVALID_ID == nScene || pMap->MapID() == nScene)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	&rObj = static_cast<Object &>(rMe);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rObj.Teleport(&pos);
	}
	else
	{
		//if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
		//{
		//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//	Player	&rPlayer = static_cast<Player &>(rMe);
		//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		//	if(!g_HumanStateMutex.IsCanAccptEvent(&rPlayer, ME_ChangeScene))
		//	{
		//		rPlayer.SendOperateResultMsg(OR_BUSY);
		//		return;
		//	}

		//	rPlayer.ChangeMap(pMap->MapID(), nScene, pos, 9, CS_IMPACT_009);
		//}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect010::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect010::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 nIdx = 0; EffectData::NUMBER_OF_PARAMS > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	impact;
		int32		nDataIndex = GetSubImpactDataIndexByIndex(rImp, nIdx);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 < nDataIndex)
		{
			g_EffectInterface.SendEffectToUnit
				(
					rMe,
					nDataIndex,
					rImp.GetCasterObjID(),
					0,
					rImp.IsCriticalHit(),
					GetRefixRate(rImp)
				);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect010::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect011::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect011::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetAttackNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR);
	}

	if(0 != GetAttackFarRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR);
	}

	if(0 != GetAttackMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC);
	}

	if(0 != GetAttackColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD);
	}

	if(0 != GetAttackFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE);
	}

	if(0 != GetAttackLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT);
	}

	if(0 != GetAttackPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON);
	}

	if(0 != GetDefenceNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);
	}

	if(0 != GetDefenceFarRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR);
	}

	if(0 != GetDefenceMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
	}

	if(0 != GetResistColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD);
	}

	if(0 != GetResistFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE);
	}

	if(0 != GetResistLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT);
	}

	if(0 != GetResistPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect011::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;

	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR:
		{
			if(0 != GetAttackNearRefix(rImp))
			{
				nValue = Float2Int((GetAttackNearRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR:
		{
			if(0 != GetAttackFarRefix(rImp))
			{
				nValue = Float2Int((GetAttackFarRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC:
		{
			if(0 != GetAttackMagicRefix(rImp))
			{
				nValue = Float2Int((GetAttackMagicRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD:
		{
			if(0 != GetAttackColdRefix(rImp))
			{
				nValue = Float2Int((GetAttackColdRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE:
		{
			if(0 != GetAttackFireRefix(rImp))
			{
				nValue = Float2Int((GetAttackFireRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT:
		{
			if(0 != GetAttackLightRefix(rImp))
			{
				nValue = Float2Int((GetAttackLightRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON:
		{
			if(0 != GetAttackPoisonRefix(rImp))
			{
				nValue = Float2Int((GetAttackPoisonRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		{
			if(0 != GetDefenceNearRefix(rImp))
			{
				nValue = Float2Int((GetDefenceNearRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR:
		{
			if(0 != GetDefenceFarRefix(rImp))
			{
				nValue = Float2Int((GetDefenceFarRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		{
			if(0 != GetDefenceMagicRefix(rImp))
			{
				nValue = Float2Int((GetDefenceMagicRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD:
		{
			if(0 != GetResistColdRefix(rImp))
			{
				nValue = Float2Int((GetResistColdRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE:
		{
			if(0 != GetResistFireRefix(rImp))
			{
				nValue = Float2Int((GetResistFireRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT:
		{
			if(0 != GetResistLightRefix(rImp))
			{
				nValue = Float2Int((GetResistLightRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON:
		{
			if(0 != GetResistPoisonRefix(rImp))
			{
				nValue = Float2Int((GetResistPoisonRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect011::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect012::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect012::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetAttackNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR);
	}

	if(0 != GetAttackFarRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR);
	}

	if(0 != GetAttackMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC);
	}

	if(0 != GetAttackColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD);
	}

	if(0 != GetAttackFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE);
	}

	if(0 != GetAttackLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT);
	}

	if(0 != GetAttackPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON);
	}

	if(0 != GetDefenceNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);
	}

	if(0 != GetDefenceFarRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR);
	}

	if(0 != GetDefenceMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
	}

	if(0 != GetResistColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD);
	}

	if(0 != GetResistFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE);
	}

	if(0 != GetResistLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT);
	}

	if(0 != GetResistPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect012::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__

	int32 nRefixType = GetRefixType(rImp);

	if( -1 == nRefixType )
	{
		return TRUE;
	}
	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR:
		{
			if(0 != GetAttackNearRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackNearRefix(rImp) : Float2Int((rMe.GetBaseAttackNear() * GetAttackNearRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;
				
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR:
		{
			if(0 != GetAttackFarRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackFarRefix(rImp) : Float2Int((rMe.GetBaseAttackFar() * GetAttackFarRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;
				
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC:
		{
			if(0 != GetAttackMagicRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackMagicRefix(rImp) : Float2Int((rMe.Get_BaseProperty_AttackMagic() * GetAttackMagicRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD:
		{
			if(0 != GetAttackColdRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackColdRefix(rImp) : Float2Int((rMe.Get_BaseProperty_AttackCold() * GetAttackColdRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE:
		{
			if(0 != GetAttackFireRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackFireRefix(rImp) : Float2Int((rMe.Get_BaseProperty_AttackFire() * GetAttackFireRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT:
		{
			if(0 != GetAttackLightRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackLightRefix(rImp) : Float2Int((rMe.Get_BaseProperty_AttackLight() * GetAttackLightRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON:
		{
			if(0 != GetAttackPoisonRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetAttackPoisonRefix(rImp) : Float2Int((rMe.Get_BaseProperty_AttackPoison() * GetAttackPoisonRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		{
			if(0 != GetDefenceNearRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetDefenceNearRefix(rImp) : Float2Int((rMe.GetBaseDefenceNear() * GetDefenceNearRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR:
		{
			if(0 != GetDefenceFarRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetDefenceFarRefix(rImp) : Float2Int((rMe.GetBaseDefenceFar() * GetDefenceFarRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		{
			if(0 != GetDefenceMagicRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetDefenceMagicRefix(rImp) : Float2Int((rMe.Get_BaseProperty_DefenceMagic() * GetDefenceMagicRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD:
		{
			if(0 != GetResistColdRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetResistColdRefix(rImp) : Float2Int((rMe.Get_BaseProperty_DefenceCold() * GetResistColdRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE:
		{
			if(0 != GetResistFireRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetResistFireRefix(rImp) : Float2Int((rMe.Get_BaseProperty_DefenceFire() * GetResistFireRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT:
		{
			if(0 != GetResistLightRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetResistLightRefix(rImp) : Float2Int((rMe.Get_BaseProperty_DefenceLight() * GetResistLightRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON:
		{
			if(0 != GetResistPoisonRefix(rImp))
			{
				nValue = (0 == nRefixType) ? GetResistPoisonRefix(rImp) : Float2Int((rMe.Get_BaseProperty_DefencePoison() * GetResistPoisonRefix(rImp)) / 100.0f);
				rIntAttrRefix += nValue;

				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect013::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect013::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetHitRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_HIT);
	}

	if(0 != GetMissRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MISS);
	}

	if(0 != GetCriticalRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL);
	}

	if(0 != GetToughnessRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_TOUGHNESS);
	}

	if(0 != GetCriticalHurtRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL_HURT);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect013::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;

	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_HIT:
		{
			if(0 != GetHitRefix(rImp))
			{
				nValue = Float2Int((GetHitRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MISS:
		{
			if(0 != GetMissRefix(rImp))
			{
				nValue = Float2Int((GetMissRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL:
		{
			if(0 != GetCriticalRefix(rImp))
			{
				nValue = Float2Int((GetCriticalRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_TOUGHNESS:
		{
			if(0 != GetToughnessRefix(rImp))
			{
				nValue = Float2Int((GetToughnessRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL_HURT:
		{
			if(0 != GetCriticalHurtRefix(rImp))
			{
				nValue = Float2Int(GetCriticalHurtRefix(rImp));
				KCheck(nValue >= 0);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect013::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect014::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect014::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Character	*pAI = rMe.GetAIObj();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pAI);
		if(ESTATE_DEAD == pAI->GetBehavior_State()->GetStateID()) return;
		if(ESTATE_GOHOME == pAI->GetBehavior_State()->GetStateID()) return;
	}

	rMe.SendMsg_RefeshAttrib();
	if(0 <= GetCanMoveRefix(rImp))
	{
		//rMe.SendArriveMSG();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bNeedStopAction = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 <= GetCanAction1Refix(rImp))
	{
		bNeedStopAction = TRUE;
	}

	if(0 <= GetCanAction2Refix(rImp))
	{
		bNeedStopAction = TRUE;
	}

	if(0 <= GetCanAction3Refix(rImp))
	{
		bNeedStopAction = TRUE;
	}

	if(bNeedStopAction)
	{
		if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Behavior_Character	*pAI = rMe.GetAIObj();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL == pAI)
			{
				return;
			}

			pAI->BHV_StopSpell();
		}
	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect014::OnEvent_FinalDamage(UNIT_EFFECT &rImp,Character &rMe,Character*const pAttacker,int32 &rDamage,SpellID_t nSkillID)const
{
	__GUARD__ ;
	
	if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		Behavior_Character	*pAI = rMe.GetAIObj();

		KCheck(pAI);
		if(ESTATE_DEAD == pAI->GetBehavior_State()->GetStateID()) 
			return;

		if(ESTATE_GOHOME == pAI->GetBehavior_State()->GetStateID()) 
			return;
	}

	//取得技能伤害修正
	if( GetDamageRefix(rImp) > -1 )
	{
		rDamage = GetDamageRefix(rImp)+1;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect014::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 <= GetCanAction1Refix(rImp))
	{
		rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_CAN_ACTION1);
	}

	if(0 <= GetCanAction2Refix(rImp))
	{
		rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_CAN_ACTION2);
	}

	if(0 <= GetCanAction3Refix(rImp))
	{
		rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_CAN_ACTION3);
	}

	if(0 <= GetCanMoveRefix(rImp))
	{
		rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_CAN_MOVE);
	}

	if(0 <= GetUnbreakableRefix(rImp))
	{
		rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
	}

	if(0 != GetMoveSpeedRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED);
	}

	if(0 != GetStealthLevelRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_STEALTH_LEVEL);
	}

	if(0 != GetDetectLevelRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DETECT_LEVEL);
	}

	if(0 <= GetModelRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MODEL_ID);
	}

	if(0 <= GetMountRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOUNT_ID);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect014::Get_Property_BoolAttrRefix
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	CharBoolAttrs::Index_T	nIdx,
	BOOL			&rBoolAttrRefix
) const
{
	__GUARD__ switch(nIdx)
	{
	case CharBoolAttrs::PROPERTY_CAN_ACTION1:
		{
			if(0 <= GetCanAction1Refix(rImp))
			{
				rBoolAttrRefix = 1 == GetCanAction1Refix(rImp);
				return TRUE;
			}
		}
		break;

	case CharBoolAttrs::PROPERTY_CAN_ACTION2:
		{
			if(0 <= GetCanAction2Refix(rImp))
			{
				rBoolAttrRefix = 1 == GetCanAction2Refix(rImp);
				return TRUE;
			}
		}
		break;

	case CharBoolAttrs::PROPERTY_CAN_ACTION3:
		{
			if(0 <= GetCanAction3Refix(rImp))
			{
				rBoolAttrRefix = 1 == GetCanAction3Refix(rImp);
				return TRUE;
			}
		}
		break;

	case CharBoolAttrs::PROPERTY_CAN_MOVE:
		{
			if(0 <= GetCanMoveRefix(rImp))
			{
				rBoolAttrRefix = 1 == GetCanMoveRefix(rImp);
				return TRUE;
			}
		}
		break;

	case CharBoolAttrs::PROPERTY_UNBREAKABLE:
		{
			if(0 <= GetUnbreakableRefix(rImp))
			{
				rBoolAttrRefix = 0 < GetUnbreakableRefix(rImp);
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect014::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;

	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED:
		{
			if(0 != GetMoveSpeedRefix(rImp))
			{
				nValue = Float2Int((GetMoveSpeedRefix(rImp) * nRefixRate) / 100.0f);
				nValue = Float2Int((rMe.Get_BaseProperty_MoveSpeed() * nValue) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_STEALTH_LEVEL:
		{
			if(0 != GetStealthLevelRefix(rImp))
			{
				rIntAttrRefix += GetStealthLevelRefix(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DETECT_LEVEL:
		{
			if(0 != GetDetectLevelRefix(rImp))
			{
				rIntAttrRefix += GetDetectLevelRefix(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MODEL_ID:
		{
			if(INVALID_ID != GetModelRefix(rImp))
			{
				rIntAttrRefix = GetModelRefix(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MOUNT_ID:
		{
			if(INVALID_ID != GetMountRefix(rImp))
			{
				rIntAttrRefix = GetMountRefix(rImp);
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect014::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect014::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect015::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect015::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		if(0 != GetStrRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_STR);
		}

		if(0 != GetConRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CON);
		}

		if(0 != GetIntRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_INT);
		}

		if(0 != GetDexRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEX);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect015::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRefixRate = GetRefixRate(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nRefixRate += 100;

		/*~~~~~~~~~~~~~~~*/
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~*/

		switch(nIdx)
		{
		case CharIntAttrRefixs::REFIX_PROPERTY_STR:
			{
				if(0 != GetStrRefix(rImp))
				{
					nValue = Float2Int((GetStrRefix(rImp) * nRefixRate) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		case CharIntAttrRefixs::REFIX_PROPERTY_CON:
			{
				if(0 != GetConRefix(rImp))
				{
					nValue = Float2Int((GetConRefix(rImp) * nRefixRate) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		case CharIntAttrRefixs::REFIX_PROPERTY_INT:
			{
				if(0 != GetIntRefix(rImp))
				{
					nValue = Float2Int((GetIntRefix(rImp) * nRefixRate) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		case CharIntAttrRefixs::REFIX_PROPERTY_DEX:
			{
				if(0 != GetDexRefix(rImp))
				{
					nValue = Float2Int((GetDexRefix(rImp) * nRefixRate) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		default:
			break;
		}
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect015::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect016::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect016::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		if(0 != GetStrRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_STR);
		}

		if(0 != GetConRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CON);
		}

		if(0 != GetIntRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_INT);
		}

		if(0 != GetDexRefix(rImp))
		{
			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEX);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect016::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType() || Object::OBJECT_CLASS_PET == rMe.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRefixRate = GetRefixRate(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nRefixRate += 100;

		/*~~~~~~~~~~~~~~~*/
		int32	nValue = 0;
		/*~~~~~~~~~~~~~~~*/

		switch(nIdx)
		{
		case CharIntAttrRefixs::REFIX_PROPERTY_STR:
			{
				if(0 != GetStrRefix(rImp))
				{
					nValue = Float2Int((GetStrRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_Str() * nValue) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		case CharIntAttrRefixs::REFIX_PROPERTY_CON:
			{
				if(0 != GetConRefix(rImp))
				{
					nValue = Float2Int((GetConRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_Con() * nValue) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		case CharIntAttrRefixs::REFIX_PROPERTY_INT:
			{
				if(0 != GetIntRefix(rImp))
				{
					nValue = Float2Int((GetIntRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_Int() * nValue) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		case CharIntAttrRefixs::REFIX_PROPERTY_DEX:
			{
				if(0 != GetDexRefix(rImp))
				{
					nValue = Float2Int((GetDexRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_Dex() * nValue) / 100.0f);
					rIntAttrRefix += nValue;
					return TRUE;
				}
			}
			break;

		default:
			break;
		}
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect016::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect017::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect017::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect017::OnEvent_FiltrateImpact(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedCheck) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
	int32		nRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	IDCollection const	*pCollection = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 nIndex = 0; nIndex < ImpactDataDescriptorIndex::IDX_GATHER_COUNT; ++nIndex)
	{
		int32	nCollectionID = GetGatherId(rImp, nIndex);

		if(INVALID_ID != nCollectionID)
		{
			pCollection = DataManager::GetSingletonPtr()->getCollection(nCollectionID);
			if(NULL != pCollection)
			{
				if(0 < pCollection->GetCollectionSize())
				{
					if(TRUE == IsEffectInCollection(rImpactNeedCheck, nCollectionID))
					{
						return CombatMissFlag::FLAG_IMMU;
					}
				}
			}
		}
	}
	

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect018::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect018::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect018::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDispelLevel = GetDispelLevel(rImp);
	int32	nDispelCount = GetDispelCount(rImp);
	int32	nRate = GetRefixRate(rImp);
	int32	nDispeled = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRate += 100;
	nDispelCount = Float2Int((nDispelCount * nRate) / 100.0f);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	IDCollection const	*pCollection = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 nIdx = 0; COLLECTION_NUMBER > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nCollectionID = GetCollectionByIndex(rImp, nIdx);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID != nCollectionID)
		{
			pCollection = DataManager::GetSingletonPtr()->getCollection(nCollectionID);
			if(NULL != pCollection)
			{
				nDispeled = rMe.Effect_DispelEffectInSpecificCollection
					(
						nCollectionID,
						nDispelLevel,
						nDispelCount
					);
				if(0 < nDispelCount)
				{
					if(nDispeled >= nDispelCount)
					{
						break;
					}
				}
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect019::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateTimes(rImp, GetActivateTimesInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect019::RefixEffect(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedRefix) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == GetActivateTimes(rImp) || TRUE == rImp.IsFadeOut())
	{
		return;
	}

	if(FALSE == IsEffectInCollection(rImpactNeedRefix, GetTargetImpactCollection(rImp)))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EffectLogic const	*pLogic = GetEffectLogic(rImpactNeedRefix);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pLogic)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nActivateTimes = GetActivateTimes(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != GetPowerRefix(rImp))
	{
		bRet = bRet || pLogic->RefixPowerByRate(rImpactNeedRefix, GetPowerRefix(rImp));
	}

	if(0 != GetContinuanceRefix(rImp))
	{
		bRet = bRet || pLogic->RefixContinuanceByPoint(rImpactNeedRefix, GetContinuanceRefix(rImp));
	}

	if(TRUE == bRet)
	{
		if(0 < nActivateTimes)
		{
			--nActivateTimes;
			if(0 == nActivateTimes)
			{
				rMe.Effect_OnEffectFadeOut(rImp);
			}

			SetActivateTimes(rImp, nActivateTimes);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect020::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect020::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect020::OnEvent_Die(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRate += 100;
	if(0 > nRate)
	{
		nRate = 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			nValue = 0;
	Character::_RELIVE_INFO ReliveInfo;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ReliveInfo.Reset();
	ReliveInfo.m_bHPUsePercent = TRUE;
	ReliveInfo.m_bMPUsePercent = TRUE;
	ReliveInfo.m_bSPUsePercent = TRUE;
	nValue = GetHpRecoverRate(rImp);
	nValue = Float2Int((nValue * nRate) / 100.0f);
	ReliveInfo.m_nHPPercent = nValue;
	nValue = GetMpRecoverRate(rImp);
	nValue = Float2Int((nValue * nRate) / 100.0f);
	ReliveInfo.m_nMPPercent = nValue;
	nValue = GetRageRecoverRate(rImp);
	nValue = Float2Int((nValue * nRate) / 100.0f);
	ReliveInfo.m_nSPPercent = nValue;
	ReliveInfo.m_MapID = rMe.GetMapID_i();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos const *pPos = rMe.GetGLPos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPos)
	{
		ReliveInfo.m_Pos.m_fX = pPos->m_fX;
		ReliveInfo.m_Pos.m_fZ = pPos->m_fZ;
	}

	rMe.SetReliveInfo(TRUE, &ReliveInfo);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect021::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateTimes(rImp, GetActivateTimesInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect021::RefixSkill(UNIT_EFFECT &rImp, SpellInfo &rSkill) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bFound = FALSE;
	int32		nValue = 0;
	int32		nActiveTimes = GetActivateTimes(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == nActiveTimes)
	{
		return;
	}

	if(FALSE == IsSpellInCollection(rSkill, GetTargetCollection(rImp)))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BaseSpellLogic const	*pSkillLogic = Spell_GetLogic(rSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillLogic)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nHitRefix = GetHitRefix(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nHitRefix)
	{
		rSkill.SetAccuracy(nHitRefix);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nCriticalRefix = GetCriticalRefix(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nCriticalRefix)
	{
		rSkill.SetCriticalRate(nCriticalRefix);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nPowerRefixByValue = GetPowerRefixByValue(rImp);
	int32	nPowerRefixByRate = GetPowerRefixByRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nPowerRefixByValue)
	{
		rSkill.SetPowerRefixByValue(nPowerRefixByValue);
	}

	if(0 != nPowerRefixByRate)
	{
		rSkill.SetPowerRefixByRate(nPowerRefixByRate);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDepleteRefixByValue = GetDepleteRefixByValue(rImp);
	int32	nDepleteRefixByRate = GetDepleteRefixByRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nDepleteRefixByValue)
	{
		rSkill.SetDepleteRefixByValue(nDepleteRefixByValue);
	}

	if(0 != nDepleteRefixByRate)
	{
		rSkill.SetDepleteRefixByRate(nDepleteRefixByRate);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nTimeRefixByValue = GetTimeRefixByValue(rImp);
	int32	nTimeRefixByRate = GetTimeRefixByRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nTimeRefixByValue)
	{
		rSkill.SetTimeRefixByValue(nTimeRefixByValue);
	}

	if(0 != nTimeRefixByRate)
	{
		rSkill.SetTimeRefixByRate(nTimeRefixByRate);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nCooldownRefixByValue = GetCooldownRefixByValue(rImp);
	int32	nCooldownRefixByRate = GetCooldownRefixByRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nCooldownRefixByValue)
	{
		nValue = rSkill.GetCooldownTime();
		nValue += nCooldownRefixByValue;
		if(0 > nValue)
		{
			nValue = 0;
		}

		rSkill.SetCooldownTime(nValue);
	}

	if(0 != nCooldownRefixByRate)
	{
		nValue = rSkill.GetCooldownTime();
		nValue += Float2Int(nValue * nCooldownRefixByRate / 100.0f);
		if(0 > nValue)
		{
			nValue = 0;
		}

		rSkill.SetCooldownTime(nValue);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nChargeRefixByValue = GetChargeRefixByValue(rImp);
	int32	nChargeRefixByRate = GetChargeRefixByRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nChargeRefixByValue)
	{
		nValue = rSkill.GetChargeTime();
		nValue += nChargeRefixByValue;
		if(0 > nValue)
		{
			nValue = 0;
		}

		rSkill.SetChargeTime(nValue);
	}

	if(0 != nChargeRefixByRate)
	{
		nValue = rSkill.GetChargeTime();
		nValue += Float2Int(nValue * nChargeRefixByRate / 100.0f);
		if(0 > nValue)
		{
			nValue = 0;
		}

		rSkill.SetChargeTime(nValue);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nChannelRefixByValue = GetChannelRefixByValue(rImp);
	int32	nChannelRefixByRate = GetChannelRefixByRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nChannelRefixByValue)
	{
		nValue = rSkill.GetChannelTime();
		nValue += nChannelRefixByValue;
		if(0 > nValue)
		{
			nValue = 0;
		}

		rSkill.SetChannelTime(nValue);
	}

	if(0 != nChannelRefixByRate)
	{
		nValue = rSkill.GetChannelTime();
		nValue += Float2Int(nValue * nChannelRefixByRate / 100.0f);
		if(0 > nValue)
		{
			nValue = 0;
		}

		rSkill.SetChannelTime(nValue);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect021::OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bFound = FALSE;
	int32		nActiveTimes = GetActivateTimes(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == nActiveTimes)
	{
		return;
	}

	if(FALSE == IsSpellInCollection(rSkill, GetTargetCollection(rImp)))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BaseSpellLogic const	*pSkillLogic = Spell_GetLogic(rSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillLogic)
	{
		return;
	}

	if(0 < nActiveTimes)
	{
		--nActiveTimes;
		if(0 == nActiveTimes)
		{
			rMe.Effect_OnEffectFadeOut(rImp);
		}

		SetActivateTimes(rImp, nActiveTimes);
		return;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect022::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateTimes(rImp, GetActivateTimesInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
//void SpellEffect022::OnEvent_Damage
//(
//	UNIT_EFFECT		&rImp,
//	Character		&rMe,
//	Character *const	pAttacker,
//	int32			&rDamage,
//	SpellID_t		nSkillID
//) const
//{
//	__GUARD__ if(TRUE == rImp.IsFadeOut())
//	{
//		return;
//	}
//
//	if(!pAttacker)
//	{
//		return;
//	}
//
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	Map	*pMap = rMe.GetMap();
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	if(NULL == pMap)
//	{
//		return;
//	}
//
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	int32	nActivateOdds = GetActivateOdds(rImp);
//	int32	nRet = pMap->GetRand100();
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	if(nRet > nActivateOdds)
//	{
//		return;
//	}
//
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	int32	nDamageCount = GetDamageCount(rImp);
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	for(int32 i = 0; i < nDamageCount; ++i)
//	{
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
//		UNIT_EFFECT	impact;
//		CombatSystem	myCombatCore;
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//		myCombatCore.Reset();
//		myCombatCore.GetResultImpact(rMe, *pAttacker, impact);
//
//		pMap->GetEventCore().RegisterImpactEvent(pAttacker->GetID(), rMe.GetID(), impact, 500);
//	}
//
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	int32	nReflectRate = GetReflectRate(rImp);
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	if(0 < nReflectRate)
//	{
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//		UNIT_EFFECT	impact;
//		int32		nReflectDamage = Float2Int((rDamage * nReflectRate) * 0.01f);
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//		g_EffectCore.InitEffectFromData(IMP_NOTYPE_DAMAGE, impact, *pAttacker);
//
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//		ModifyHpMpRageStrikePointByValue_T	logic;
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//		if(logic.ID != GetEffectLogicID(impact))
//		{
//			KCheckEx(FALSE, "[SpellEffect022::OnEvent_Damage]: Error Data found!");
//			return;
//		}
//
//		logic.SetHpModification(impact, -nReflectDamage);
//		pMap->GetEventCore().RegisterImpactEvent(pAttacker->GetID(), rMe.GetID(), impact, 500);
//	}
//
//	__UNGUARD__
//}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect022::OnEvent_DamageTarget
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	Character	&rTar,
	int32		&rDamage,
	SpellID_t	nSkillID
) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	int32 nRefixType = GetRefixTypeInTable(rImp);
	int32 nActivateTimes = GetActivateTimes(rImp);
	int32 nActivateOdds = GetActivateOddsInTable(rImp);
	int32 nAbsorbValue = GetAbsorbValueInTable(rImp);

	if( -1 == nRefixType )
	{
		return;
	}

	if( 0 >= nActivateTimes && -1 != nActivateTimes )
	{
		rMe.Effect_OnEffectFadeOut(rImp);
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	int32	nRet = pMap->GetRand100();
	
	if( nRet > nActivateOdds && -1 != nActivateOdds )
	{
		return;
	}

	int32	nAbsorbHP = 0;

	nAbsorbHP = (0 == nRefixType) ? nAbsorbValue : Float2Int((rDamage * nAbsorbValue) * 0.01f);

	SetActivateTimes(rImp, --nActivateTimes);
	rMe.HealthIncrement(nAbsorbHP, rImp.GetCasterLogicCount(), &rMe);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect023::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateOdds(rImp, GetActivateOddsInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect023::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	if(0 >= GetDamageIgnoreRate(rImp))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nActivateOdds = GetActivateOdds(rImp);
	int32	nRet = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRet > nActivateOdds)
	{
		return;
	}

	rDamage = Float2Int((rDamage * GetDamageIgnoreRate(rImp)) / 100.0f);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect023::OnEvent_DamageTarget
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	Character	&rTar,
	int32		&rDamage,
	SpellID_t	nSkillID
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nMpDamageRate = GetMpDamageRate(rImp);
	int32		nRageDamageRate = GetRageDamageRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	if(0 >= nMpDamageRate && 0 >= nRageDamageRate)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nActivateOdds = GetActivateOdds(rImp);
	int32	nRet = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRet > nActivateOdds)
	{
		return;
	}

	if(0 < nMpDamageRate)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nMP = Float2Int((nMpDamageRate * rDamage) / 100.0f);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rTar.ManaIncrement(-nMP, rImp.GetCasterLogicCount(), &rMe);
	}

	if(0 < nRageDamageRate)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRage = rTar.Get_Property_Rage();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		nRage = Float2Int((nRageDamageRate * nRage) / 100.0f);
		rTar.RageIncrement(-nRage, rImp.GetCasterLogicCount(), &rMe);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect024::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateOdds(rImp, GetActivateOddsInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect024::OnEvent_FiltrateImpact(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedCheck) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRet = rand() % 100;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRet > GetActivateOdds(rImp))
	{
		return FALSE;
	}

	for(int32 nIndex = 0; COLLECTION_NUMBERS > nIndex; ++nIndex)
	{
		if(TRUE == IsEffectInCollection(rImpactNeedCheck, GetImmunoImpactsByIndex(rImp, nIndex)))
		{
			return CombatMissFlag::FLAG_ABSORB;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect025::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateOdds(rImp, GetActivateOddsInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect025::OnEvent_FiltrateImpact(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedCheck) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRet = rand() % 100;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRet > GetActivateOdds(rImp))
	{
		return FALSE;
	}

	if(TRUE == rImpactNeedCheck.IsCriticalHit())
	{
		return CombatMissFlag::FLAG_ABSORB;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect026::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetShieldHp(rImp, GetShieldHpInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect026::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__;

	//伤害修正处理,加在这里这样就可以处理DOT的伤害了
	if(TRUE == rImp.IsFadeOut())
	{
		return ;
	}


	//伤害处理
	int32 nDamage = 0;
	if( GetIgnoreRate(rImp) > 0 )
	{
		//设置了忽略机率
		int32 nIgnoreRate = GetIgnoreRate(rImp) - GetIgnoreImmunityRate(pAttacker);
		nIgnoreRate < 0 ? nIgnoreRate = 0 : NULL;
		nDamage = Float2Int((rDamage * nIgnoreRate) / 100.0f);
		rDamage -= nDamage;
		rDamage <= 0 ? rDamage = 1 : NULL;
	}

	if( GetAbsorbRate(rImp) > 0  && GetShieldHp(rImp) != -1  )
	{
		//设置了吸收机率
		nDamage = Float2Int((rDamage * GetAbsorbRate(rImp)) / 100.0f);

		int32 nShieldHp = GetShieldHp(rImp);
		if(nDamage > nShieldHp)
		{
			nDamage = nShieldHp;
		}

		nShieldHp -= nDamage;
		nShieldHp <= 0 ? nShieldHp = 0 : NULL;
		SetShieldHp(rImp, nShieldHp);
		rDamage -= nDamage;
		if( nShieldHp <= 0 )
		{
			rMe.Effect_OnEffectFadeOut(rImp);
		}
	}

	if( GetReflectRate(rImp) > 0 )
	{
		//设置了反弹机率
		int32 nRand = 0;
		GameMap	*pMap = rMe.GetMap();
		if(pMap != NULL )
		{
			nRand = pMap->GetRand100();
		}

		if(GetReflectActivateOdds(rImp) > nRand )
		{
			nDamage = Float2Int((rDamage * GetReflectRate(rImp)) / 100.0f);
			if(NULL != pAttacker)
			{
				pAttacker->HealthIncrement(-nDamage, rImp.GetCasterLogicCount(), &rMe);
			}
		}
	}

	//吸收伤害处理
	if( Object::OBJECT_CLASS_PLAYER != rMe.GetObjType() )
	{
		//检查类型
		return;
	}

	if( IsAbsorbDamageByMP(rImp) == 1 )
	{
		//隐修士处理

		//隐修士主要是以吸收为主
		Player* pPlayer = (Player*)&rMe;
		int32 nRage = pPlayer->Get_Property_Rage();
		int32 nValue = 0;
		if( rDamage >= nRage )
		{
			nValue = nRage;
			rDamage -= nRage;
		}
		else
		{
			nValue = rDamage;
			rDamage = 0;
		}
		rMe.RageIncrement(-nValue, rImp.GetCasterLogicCount());
	}

	__UNGUARD__
}

void SpellEffect026::OnEvent_FinalDamage
(
 UNIT_EFFECT		&rImp,
 Character		&rMe,
 Character *const	pAttacker,
 int32			&rDamage,
 SpellID_t		nSkillID
 ) const
{
	__GUARD__;

	
	
	__UNGUARD__
}
/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellEffect026::GetIgnoreImmunityRate(Character *const pAttacker) const
{
	__GUARD__ 
	//KCheck( pAttacker );
	if( NULL == pAttacker || Object::OBJECT_CLASS_PLAYER != pAttacker->GetObjType() )
		return 0;
	Player* pPlayer = (Player*)pAttacker;
	switch( pPlayer->GetProfession() )
	{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:
		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:
			return pAttacker->GetIntAttr_EX(CharIntProperty::PROPERTY_IGNORE_NEAR_IMMUNITY);
		case PROFESSION_QISHE:
		case PROFESSION_HUOQIANG:
		case PROFESSION_CIKE:
		case PROFESSION_JINWEIJUN:
			return pAttacker->GetIntAttr_EX(CharIntProperty::PROPERTY_IGNORE_FAR_IMMUNITY);
		case PROFESSION_XIANZHI:
		case PROFESSION_SAMAN:
		case PROFESSION_YINXIUSHI:
		case PROFESSION_LAMA:
			return pAttacker->GetIntAttr_EX(CharIntProperty::PROPERTY_IGNORE_MAGIC_IMMUNITY);
	}
	return 0;
	__UNGUARD__ return 0;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect027::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	//__GUARD__ if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	Pet	*pPet = ((Player *) &rMe)->GetPet(0);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if(NULL != pPet)
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		int32	nTransferRate = GetTransferRate(rImp);
	//		int32	nTransferedDamage = Float2Int((rDamage * nTransferRate) / 100.0f);
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(TRUE == pPet->IsAlive() && TRUE == pPet->IsActiveObj())
	//		{
	//			pPet->HealthIncrement(-nTransferedDamage, rImp.GetCasterLogicCount(), pAttacker);
	//			rDamage -= nTransferedDamage;
	//			return;
	//		}
	//	}
	//}

	//rMe.Effect_OnEffectFadeOut(rImp);
	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect028::OnEvent_Damages
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32 *const		pDamageList,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~*/
	int32	nIncreaceHP = 0;
	int32	nDamage = 0;
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(0 != GetColdRefix(rImp))
	{
		nValue = Float2Int((pDamageList[DAMAGE_COLD] * GetColdRefix(rImp)) / 100.0f);
		if(0 <= nValue)
		{
			pDamageList[DAMAGE_COLD] += nValue;
		}
		else
		{
			pDamageList[DAMAGE_COLD] = 0;
			nIncreaceHP += -nValue;
		}
	}

	if(0 != GetFireRefix(rImp))
	{
		nValue = Float2Int((pDamageList[DAMAGE_FIRE] * GetFireRefix(rImp)) / 100.0f);
		if(0 <= nValue)
		{
			pDamageList[DAMAGE_FIRE] += nValue;
		}
		else
		{
			pDamageList[DAMAGE_FIRE] = 0;
			nIncreaceHP += -nValue;
		}
	}

	if(0 != GetLightRefix(rImp))
	{
		nValue = Float2Int((pDamageList[DAMAGE_LIGHT] * GetLightRefix(rImp)) / 100.0f);
		if(0 <= nValue)
		{
			pDamageList[DAMAGE_LIGHT] += nValue;
		}
		else
		{
			pDamageList[DAMAGE_LIGHT] = 0;
			nIncreaceHP += -nValue;
		}
	}

	if(0 != GetPoisonRefix(rImp))
	{
		nValue = Float2Int((pDamageList[DAMAGE_POISON] * GetPoisonRefix(rImp)) / 100.0f);
		if(0 <= nValue)
		{
			pDamageList[DAMAGE_POISON] += nValue;
		}
		else
		{
			pDamageList[DAMAGE_POISON] = 0;
			nIncreaceHP += -nValue;
		}
	}

	if(0 < nIncreaceHP)
	{
		rMe.HealthIncrement(nIncreaceHP, rImp.GetCasterLogicCount(), &rMe);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect029::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect029::RefixSkill(UNIT_EFFECT &rImp, SpellInfo &rSkill) const
{
	__GUARD__ if(0 != IsSpellInCollection(rSkill, GetTargetSkillCollection(rImp)))
	{
		RefixAllSkillAttr(rSkill, rImp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect029::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect029::GetRifixResult(int32 iBase, int32 iRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		iRefixResult = iBase + iRefix;
	}
	else
	{
		iRefix += 100;
		iRefixResult = Float2Int((iBase * iRefix) / 100.0f);
	}

	return iRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float SpellEffect029::GetRifixResult(float fBase, float fRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		fRefixResult = fBase + fRefix;
	}
	else
	{
		fRefix += 100;
		fRefixResult = ((fBase * fRefix) / 100.0f);
	}

	return fRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect029::RefixAllSkillAttr(SpellInfo &rSkill, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixType = GetRefixType(rImp);
	int32		iRefixPara = 0;
	int32		iBase = 0;
	int32		iResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iBase = rSkill.GetCooldownTime();
	iRefixPara = GetCooldownTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetCooldownTime(iResult);

	iBase = rSkill.GetChargeTime();
	iRefixPara = GetChargeTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChargeTime(iResult);

	iBase = rSkill.GetChannelTime();
	iRefixPara = GetChannelTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChannelTime(iResult);

	iBase = rSkill.GetChargesOrInterval();
	iRefixPara = GetAttackTimesOrChannelTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChargesOrInterval(iResult);

	iBase = rSkill.GetAccuracy();
	iRefixPara = GetAccuracyRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetAccuracy(iResult);

	iBase = rSkill.GetCriticalRate();
	iRefixPara = GetCriticalrateRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetCriticalRate(iResult);

	iBase = rSkill.Get_Property_MaxTargetNumber();
	iRefixPara = GetMaxTargetRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetMaxTargetNumber(iResult);

	if(iRefixType > 0)
	{
		iBase = rSkill.GetDepleteRefixByRate();
		iRefixPara = GetDepleteRefix(rImp);
		iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
		rSkill.SetDepleteRefixByRate(iResult);
	}
	else
	{
		iBase = rSkill.GetDepleteRefixByValue();
		iRefixPara = GetDepleteRefix(rImp);
		iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
		rSkill.SetDepleteRefixByValue(iResult);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect030::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetShieldHp(rImp, GetShieldHpInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetAbsorbRate(rImp, GetAbsorbRateInTable(rImp));
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect030::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage = Float2Int((rDamage * GetAbsorbRate(rImp)) / 100.0f);
	int32	nShieldHp = GetShieldHp(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDamage > nShieldHp)
	{
		nDamage = nShieldHp;
	}

	nShieldHp -= nDamage;
	SetShieldHp(rImp, nShieldHp);
	rDamage -= nDamage;
	if(0 >= GetShieldHp(rImp))
	{
		rMe.Effect_OnEffectFadeOut(rImp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect030::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pTar = NULL;
	GameMap			*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellEffect030::OnFadeOut]: Empty scene pointer found!!");
		return;
	}

	/*~~~~~~~~~~~~*/
	OBJLIST Targets;
	/*~~~~~~~~~~~~*/

	if
	(
		FALSE == ScanUnitForTarget
			(
				rImp,
				rMe,
				*(rMe.GetGLPos()),
				(float) GetScanRadius(rImp),
				GetEffectedObjCount(rImp),
				Targets
			)
	)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nImpact = GetSubImpactIndex(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nImpact)
	{
		return;
	}

	for(int32 nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		pTar = (Character *) Targets.m_aObj[nIdx];
		if(NULL != pTar)
		{
			pMap->GetEventCore().RegisterBeSkillEvent
				(
					pTar->GetID(),
					rMe.GetID(),
					BEHAVIOR_TYPE_HOSTILITY,
					500
				);
			g_EffectInterface.SendEffectToUnit(*pTar, nImpact, rMe.GetID(), 500);
		}
	}

	return;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect030::IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ if(FALSE == rTar.IsAliveInDeed() || FALSE == rTar.IsActiveObj())
	{
		return FALSE;
	}

	if(rMe.IsEnemy(&rTar))
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect030::RefixEffect(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedRefix) const
{
	__GUARD__ if(TRUE == IsEffectInCollection(rImpactNeedRefix, GetTargetImpactCollection(rImp)))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		EffectLogic const	*pLogic = GetEffectLogic(rImpactNeedRefix);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pLogic)
		{
			pLogic->RefixPowerByRate(rImpactNeedRefix, GetImpactRefixRate(rImp));
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect030::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nValue = GetShieldHp(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRate += 100;
	nValue = Float2Int((nValue * nRate) / 100.0f);
	if(0 > nValue)
	{
		nValue = 0;
	}

	SetShieldHp(rImp, nValue);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect031::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetCollectedDamage(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect031::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	int32		nCollectedDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRand = pMap->GetRand100();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRand > GetAbsorbOdds(rImp))
		{
			nCollectedDamage = Float2Int((rDamage * GetReflectRate(rImp)) / 100.0f);
			rDamage = 0;
			nCollectedDamage += GetCollectedDamage(rImp);
			SetCollectedDamage(rImp, nCollectedDamage);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect031::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;

	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		{
			if(0 != GetDefenceNearRefix(rImp))
			{
				nValue = Float2Int((GetDefenceNearRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		{
			if(0 != GetDefenceMagicRefix(rImp))
			{
				nValue = Float2Int((GetDefenceMagicRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD:
		{
			if(0 != GetResistColdRefix(rImp))
			{
				nValue = Float2Int((GetResistColdRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE:
		{
			if(0 != GetResistFireRefix(rImp))
			{
				nValue = Float2Int((GetResistFireRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT:
		{
			if(0 != GetResistLightRefix(rImp))
			{
				nValue = Float2Int((GetResistLightRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON:
		{
			if(0 != GetResistPoisonRefix(rImp))
			{
				nValue = Float2Int((GetResistPoisonRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect031::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetDefenceNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);;
	}

	if(0 != GetDefenceMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
	}

	if(0 != GetResistColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD);
	}

	if(0 != GetResistFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE);
	}

	if(0 != GetResistLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT);
	}

	if(0 != GetResistPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect031::RefixEffect(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedRefix) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(GetEffectLogicID(rImpactNeedRefix))
	{
	case DI_DamagesByValue_T::ID:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			DI_DamagesByValue_T	Logic;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nDamage = Logic.GetDamageMagic(rImpactNeedRefix);
			nDamage += GetCollectedDamage(rImp);
			SetCollectedDamage(rImp, 0);
			Logic.SetDamageMagic(rImpactNeedRefix, nDamage);
		}
		break;

	case DI_DamageByValue_T::ID:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			DI_DamageByValue_T	Logic;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nDamage = Logic.GetDamage(rImpactNeedRefix);
			nDamage += GetCollectedDamage(rImp);
			SetCollectedDamage(rImp, 0);
			Logic.SetDamage(rImpactNeedRefix, nDamage);
		}
		break;

	default:
		break;
	};
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect032::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetSnareActivateCooldownElapsed(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect032::OnEvent_Damages
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32 *const		pDamageList,
	SpellID_t		nSkillID
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTemplateData const	*pData = DataManager::GetSingletonPtr()->getSpellTemplate(nSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pData)
	{
		if(0 == pData->GetRangedSkillFlag())
		{
			if(GetSnareActivateCooldown(rImp) <= GetSnareActivateCooldownElapsed(rImp))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
				GameMap	*pMap = rMe.GetMap();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(NULL != pMap)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					int32	nRand = pMap->GetRand100();
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(nRand < GetSnareActivateOdds(rImp))
					{
						if(NULL != pAttacker)
						{
							SetSnareActivateCooldownElapsed(rImp, 0);
							g_EffectInterface.SendEffectToUnit
								(
									*pAttacker,
									GetSnareImpactDataIndex(rImp),
									rMe.GetID(),
									500
								);
						}
					}
				}
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Time_t	nCooldownElapsed = GetSnareActivateCooldownElapsed(rImp);
				Time_t	nDeltaTime = rMe.GetLogicTime();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				nCooldownElapsed += nDeltaTime;
				SetSnareActivateCooldownElapsed(rImp, nCooldownElapsed);
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect032::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;

	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		{
			if(0 != GetDefenceNearRefix(rImp))
			{
				nValue = Float2Int((GetDefenceNearRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		{
			if(0 != GetDefenceMagicRefix(rImp))
			{
				nValue = Float2Int((GetDefenceMagicRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD:
		{
			if(0 != GetResistColdRefix(rImp))
			{
				nValue = Float2Int((GetResistColdRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE:
		{
			if(0 != GetResistFireRefix(rImp))
			{
				nValue = Float2Int((GetResistFireRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT:
		{
			if(0 != GetResistLightRefix(rImp))
			{
				nValue = Float2Int((GetResistLightRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON:
		{
			if(0 != GetResistPoisonRefix(rImp))
			{
				nValue = Float2Int((GetResistPoisonRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect032::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetDefenceNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);;
	}

	if(0 != GetDefenceMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
	}

	if(0 != GetResistColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD);
	}

	if(0 != GetResistFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE);
	}

	if(0 != GetResistLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT);
	}

	if(0 != GetResistPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect032::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pTar = NULL;
	GameMap			*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		KCheckEx(FALSE, "[SpellEffect032::OnFadeOut]: Empty scene pointer found!!");
		return;
	}

	/*~~~~~~~~~~~~*/
	OBJLIST Targets;
	/*~~~~~~~~~~~~*/

	if
	(
		FALSE == ScanUnitForTarget
			(
				rImp,
				rMe,
				*(rMe.GetGLPos()),
				(float) GetScanRadius(rImp),
				GetEffectedObjCount(rImp),
				Targets
			)
	)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nImpact = GetFreezeImpactDataIndex(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nImpact)
	{
		return;
	}

	for(int32 nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		pTar = (Character *) Targets.m_aObj[nIdx];
		if(NULL != pTar)
		{
			pMap->GetEventCore().RegisterBeSkillEvent
				(
					pTar->GetID(),
					rMe.GetID(),
					BEHAVIOR_TYPE_HOSTILITY,
					500
				);
			g_EffectInterface.SendEffectToUnit(*pTar, nImpact, rMe.GetID(), 500);
		}
	}

	return;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect032::IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ if(FALSE == rTar.IsAliveInDeed() || FALSE == rTar.IsActiveObj())
	{
		return FALSE;
	}

	if(rMe.IsEnemy(&rTar))
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect033::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetAiTypeRefix(rImp, GetAiTypeRefixInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect033::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster &rMonster = (Monster &) rMe;
		int32	nAI_Type = GetAiTypeRefix(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SetAiTypeRefix(rImp, rMonster.GetAIType());
		rMonster.SetAIType(nAI_Type);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Monster	*pAI = rMonster.GetMonsterAI();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pAI)
		{
			pAI->RemoveThreatByObjID(rImp.GetCasterObjID());
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect033::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Monster &rMonster = (Monster &) rMe;
		int32	nAI_Type = GetAiTypeRefix(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		rMonster.SetAIType(nAI_Type);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Monster	*pAI = rMonster.GetMonsterAI();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pAI)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pObj = GetEffectCaster(rMe, rImp);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pObj && IsObjCharacter(pObj->GetObjType()))
			{
				pAI->ModThreatByPtr((Character *) pObj);
				pAI->ToBHVApproachTar();
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect033::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CAMP);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect033::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ if(CharIntAttrRefixs::REFIX_PROPERTY_CAMP == nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pObj = GetEffectCaster(rMe, rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pObj)
		{
			if(TRUE == IsObjCharacter(pObj->GetObjType()))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Character	&rOwner = *(Character *) pObj;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				rIntAttrRefix = rOwner.GetCampID();
				return TRUE;
			}
		}

		rMe.Effect_OnEffectFadeOut(rImp);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect034::OnEvent_Die(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pTar = NULL;
	OBJLIST			Targets;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if
	(
		FALSE == ScanUnitForTarget
			(
				rImp,
				rMe,
				*(rMe.GetGLPos()),
				(float) GetScanRadius(rImp),
				GetEffectedObjCount(rImp),
				Targets
			)
	)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	UNIT_EFFECT	impact;
	CombatSystem	myCombatCore;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		pTar = (Character *) Targets.m_aObj[nIdx];
		if(NULL != pTar)
		{
			myCombatCore.Reset();
			g_EffectInterface.InitEffectFromData(GetSubImpactDataIndex(rImp), impact, rMe);
			myCombatCore.GetResultImpact(rMe, *pTar, impact);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = rMe.GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pMap)
			{
				pMap->GetEventCore().RegisterBeSkillEvent
					(
						pTar->GetID(),
						rMe.GetID(),
						BEHAVIOR_TYPE_HOSTILITY,
						500
					);
				pMap->GetEventCore().RegisterImpactEvent(pTar->GetID(), rMe.GetID(), impact, 500);
			}
		}
	}

	return;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect034::IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ if(FALSE == rTar.IsAliveInDeed() || FALSE == rTar.IsActiveObj())
	{
		return FALSE;
	}

	if(rMe.IsEnemy(&rTar))
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect035::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_BUS == rMe.GetObjType())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Character	*pAI = rMe.GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAI)
	{
		pAI->BHV_Stop();

		if(ESTATE_DEAD == pAI->GetBehavior_State()->GetStateID()) return;

		if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Behavior_Monster	*pBehavior_Monster = (Behavior_Monster *) pAI;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(ESTATE_GOHOME == pBehavior_Monster->GetBehavior_State()->GetStateID()) return;
			if(ESTATE_DEAD == pBehavior_Monster->GetBehavior_State()->GetStateID()) return;
			if(FALSE == pBehavior_Monster->IsStrickBackMonster()) return;

			if(pBehavior_Monster->IsStrickBackMonster())
			{
				pBehavior_Monster->ModThreatByObjID(rImp.GetCasterObjID());
			}
			else if(TRUE == ((Monster &) rMe).isPatrolMonster())
			{
				pBehavior_Monster->SetAttackPos(*rMe.GetGLPos());
			}
		}

		pAI->ChangeState(ESTATE_TERROR);
	}

	rMe.SendMsg_RefeshAttrib();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect035::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_BUS == rMe.GetObjType())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Character	*pAI = rMe.GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAI)
	{
		pAI->BHV_Stop();

		if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster		&rMonster = (Monster &) rMe;
			Behavior_Monster	*pBehavior_Monster = (Behavior_Monster *) pAI;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(FALSE == pBehavior_Monster->IsStrickBackMonster()) return;

			if(pBehavior_Monster->IsStrickBackMonster())
			{
				pBehavior_Monster->ChangeState(ESTATE_COMBAT);
			}
			else
			{
				/*~~~~~~~~~~~~~~~~*/
				GLPos	Tar;
				/*~~~~~~~~~~~~~~~~*/

				if(rMonster.isPatrolMonster())
					Tar = pBehavior_Monster->GetAttackPos();
				else
					Tar = *(rMonster.GetRespawnPos());
				rMonster.SetMoveMode(MOVE_MODE_RUN);
				if(OR_OK != pBehavior_Monster->BHV_Move(&Tar))
				{
					rMonster.DirectMoveTo(&Tar);
				}

				pBehavior_Monster->ChangeState(ESTATE_GOHOME);
			}
		}
		else
		{
			pAI->ChangeState(ESTATE_COMBAT);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect035::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_BUS == rMe.GetObjType())
	{
		return;
	}

	rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_TERROR);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect035::Get_Property_BoolAttrRefix
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	CharBoolAttrs::Index_T	nIdx,
	BOOL			&rBoolAttrRefix
) const
{
	__GUARD__ if(Object::OBJECT_CLASS_BUS == rMe.GetObjType())
	{
		return FALSE;
	}

	if(nIdx == CharBoolAttrs::PROPERTY_TERROR)
	{
		rBoolAttrRefix = TRUE;
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect036::CanViewSpecialObj(UNIT_EFFECT &rImp, SpecialCreature &rObj) const
{
	__GUARD__ if(rObj.GetStealthLevel() < GetDetectLevelRefix(rImp))
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect037::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateTimes(rImp, GetActivateTimesInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect037::RefixEffect(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedRefix) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 == GetActivateTimes(rImp) || rImp.IsFadeOut())
	{
		return;
	}

	if(FALSE == IsEffectInCollection(rImpactNeedRefix, GetTargetImpactCollection(rImp)))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRate = GetShieldHpRefix(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRate += 100;

	/*~~~~~~~~~~~~*/
	int32	nHp = 0;
	/*~~~~~~~~~~~~*/

	switch(GetEffectLogicID(rImpactNeedRefix))
	{
	case DS_XianZhi009_T::ID:
		{
			/*~~~~~~~~~~~~~~~~~~*/
			DS_XianZhi009_T logic;
			/*~~~~~~~~~~~~~~~~~~*/

			nHp = Float2Int((nHp * nRate) / 100.0f);
			if(0 > nHp)
			{
				nHp = 0;
			}

			bRet = TRUE;
		}
		break;

	case DS_XianZhi014_T::ID:
		{
			/*~~~~~~~~~~~~~~~~~~*/
			DS_XianZhi014_T logic;
			/*~~~~~~~~~~~~~~~~~~*/

			nHp = logic.GetShieldHp(rImpactNeedRefix);
			nHp = Float2Int((nHp * nRate) / 100.0f);
			if(0 > nHp)
			{
				nHp = 0;
			}

			logic.SetShieldHp(rImp, nHp);
			bRet = TRUE;
		}
		break;

	default:
		KCheckEx(FALSE, "[SpellEffect037::RefixImpact]: rImpactNeedRefix isn't XianZhi huti impact!!");
		return;
		break;
	}

	if(TRUE == bRet)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nActivateTimes = GetActivateTimes(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 < nActivateTimes)
		{
			--nActivateTimes;
			if(0 == nActivateTimes)
			{
				rMe.Effect_OnEffectFadeOut(rImp);
			}

			SetActivateTimes(rImp, nActivateTimes);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect039::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetCriticalRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect039::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ if(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL == nIdx)
	{
		if(0 != GetCriticalRefix(rImp))
		{
			rIntAttrRefix += GetCriticalRefix(rImp);
			return TRUE;
		}
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect039::RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nValue = Float2Int((rRageRegeneration * GetRageRegenerateRefix(rImp)) / 100.0f);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rRageRegeneration += nValue;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect040::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateTimes(rImp, GetActivateTimesInTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect040::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetMoveSpeedRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect040::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ if(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED == nIdx)
	{
		if(0 != GetMoveSpeedRefix(rImp))
		{
			rIntAttrRefix += rMe.Get_BaseProperty_MoveSpeed() * GetMoveSpeedRefix(rImp) / 100;
			return TRUE;
		}
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect040::OnEvent_HitTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rTar.GetObjType())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nActivateTimes = GetActivateTimes(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 == nActivateTimes)
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nImpact = GetSubImpact(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		g_EffectInterface.SendEffectToUnit(rTar, nImpact, rMe.GetID(), 500);
		if(0 < nActivateTimes)
		{
			--nActivateTimes;
			SetActivateTimes(rImp, nActivateTimes);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect041::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetAttackNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR);
	}

	if(0 != GetDefenceNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);;
	}

	if(0 != GetAttackMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC);
	}

	if(0 != GetDefenceMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect041::RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
{
	__GUARD__ rRageRegeneration *= GetRageRegenerateRefix(rImp);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect041::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR:
		if(0 != GetAttackNearRefix(rImp))
		{
			rIntAttrRefix += GetAttackNearRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		if(0 != GetDefenceNearRefix(rImp))
		{
			rIntAttrRefix += GetDefenceNearRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC:
		if(0 != GetAttackMagicRefix(rImp))
		{
			rIntAttrRefix += GetAttackMagicRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		if(0 != GetDefenceMagicRefix(rImp))
		{
			rIntAttrRefix += GetDefenceMagicRefix(rImp);
			return TRUE;
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect042::OnEvent_FiltrateImpact(UNIT_EFFECT &rImp, Character &rMe, UNIT_EFFECT &rImpactNeedCheck) const
{
	__GUARD__ if(TRUE == IsEffectInCollection(rImpactNeedCheck, GetImmunoImpactCollectionOne(rImp)))
	{
		return CombatMissFlag::FLAG_IMMU;
	}

	if(TRUE == IsEffectInCollection(rImpactNeedCheck, GetImmunoImpactCollectionTwo(rImp)))
	{
		return CombatMissFlag::FLAG_IMMU;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect042::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetAttackSpeedRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_SPEED);
	}

	if(0 != GetCriticalRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect042::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_SPEED:
		if(0 != GetAttackSpeedRefix(rImp))
		{
			rIntAttrRefix += GetAttackSpeedRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL:
		if(0 != GetCriticalRefix(rImp))
		{
			rIntAttrRefix += GetCriticalRefix(rImp);
			return TRUE;
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect043::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetResistColdRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD);
	}

	if(0 != GetResistFireRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE);
	}

	if(0 != GetResistLightRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT);
	}

	if(0 != GetResistPoisonRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect043::RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
{
	__GUARD__ rRageRegeneration += GetRageRegenerateRefix(rImp);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect043::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD:
		if(0 != GetResistColdRefix(rImp))
		{
			rIntAttrRefix += GetResistColdRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE:
		if(0 != GetResistFireRefix(rImp))
		{
			rIntAttrRefix += GetResistFireRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT:
		if(0 != GetResistLightRefix(rImp))
		{
			rIntAttrRefix += GetResistLightRefix(rImp);
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON:
		if(0 != GetResistPoisonRefix(rImp))
		{
			rIntAttrRefix += GetResistPoisonRefix(rImp);
			return TRUE;
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect044::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetMoveSpeedRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect044::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ if(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED == nIdx)
	{
		if(0 != GetMoveSpeedRefix(rImp))
		{
			rIntAttrRefix += Float2Int((rMe.Get_BaseProperty_MoveSpeed() * GetMoveSpeedRefix(rImp)) / 100.0f);
			return TRUE;
		}
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect044::OnEvent_HitTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
	{
		if(0 >= GetActivateOdds(rImp))
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		GameMap	*pMap = rMe.GetMap();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pMap)
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRand = pMap->GetRand100();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRand <= GetActivateOdds(rImp))
		{
			//rMe.StrikePointIncrement(GetModifyStrikePoint(rImp));
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect045::RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
{
	__GUARD__ if(0 != GetRageRegenerationAdditional(rImp))
	{
		rRageRegeneration += GetRageRegenerationAdditional(rImp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect046::OnEvent_Damages
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32 *const		pDamageList,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	if(NULL == pAttacker)
	{
		return;
	}

	if(INVALID_ID == nSkillID)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	IDCollection const	*pCollection = DataManager::GetSingletonPtr()->getCollection(GetEffectedSkillCollection(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCollection)
	{
		return;
	}

	if(FALSE == pCollection->IsThisIDInCollection(nSkillID))
	{
		return;
	}

	if(pAttacker->GetUniqueID() != rImp.GetCasterUniqueID())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRefixRate = GetPowerRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pDamageList[DAMAGE_TYPE_NEAR] = pDamageList[DAMAGE_TYPE_NEAR] + Float2Int((pDamageList[DAMAGE_TYPE_NEAR] * nRefixRate) / 100.0f);
	pDamageList[DAMAGE_TYPE_FAR] = pDamageList[DAMAGE_TYPE_FAR] + Float2Int((pDamageList[DAMAGE_TYPE_FAR] * nRefixRate) / 100.0f);
	pDamageList[DAMAGE_TYPE_M] = pDamageList[DAMAGE_TYPE_M] + Float2Int((pDamageList[DAMAGE_TYPE_M] * nRefixRate) / 100.0f);
	pDamageList[DAMAGE_TYPE_COLD] = pDamageList[DAMAGE_TYPE_COLD] + Float2Int((pDamageList[DAMAGE_TYPE_COLD] * nRefixRate) / 100.0f);
	pDamageList[DAMAGE_TYPE_FIRE] = pDamageList[DAMAGE_TYPE_FIRE] + Float2Int((pDamageList[DAMAGE_TYPE_FIRE] * nRefixRate) / 100.0f);
	pDamageList[DAMAGE_TYPE_LIGHT] = pDamageList[DAMAGE_TYPE_LIGHT] + Float2Int((pDamageList[DAMAGE_TYPE_LIGHT] * nRefixRate) / 100.0f);
	pDamageList[DAMAGE_TYPE_POISON] = pDamageList[DAMAGE_TYPE_POISON] + Float2Int((pDamageList[DAMAGE_TYPE_POISON] * nRefixRate) / 100.0f);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamage = pDamageList[DAMAGE_TYPE_NEAR] +
		pDamageList[DAMAGE_TYPE_FAR] +
		pDamageList[DAMAGE_MAGIC] +
		pDamageList[DAMAGE_COLD] +
		pDamageList[DAMAGE_FIRE] +
		pDamageList[DAMAGE_LIGHT] +
		pDamageList[DAMAGE_POISON];
	int32	nRage = Float2Int((nDamage * GetRageConvertRate(rImp)) / 100.0f);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAttacker->RageIncrement(nRage, rImp.GetCasterLogicCount(), pAttacker);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect047::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	if(NULL == pAttacker)
	{
		return;
	}

	if(INVALID_ID == nSkillID)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	IDCollection const	*pCollection = DataManager::GetSingletonPtr()->getCollection(GetEffectedSkillCollection(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCollection)
	{
		return;
	}

	if(FALSE == pCollection->IsThisIDInCollection(nSkillID))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRand = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRand >= GetActivateOdds(rImp))
	{
		return;
	}

	g_EffectInterface.SendEffectToUnit(rMe, GetSubImpactDataIndex(rImp), pAttacker->GetID(), 0);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect048::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object	*pObj = GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	&rAttacker = (Character &) *pObj;
			UNIT_EFFECT	impact;
			CombatSystem	myCombatCore;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			myCombatCore.Reset();
			g_EffectInterface.InitEffectFromData(GetSubImpact(rImp), impact, rMe);
			myCombatCore.GetResultImpact(rAttacker, rMe, impact);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = rMe.GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pMap)
			{
				pMap->GetEventCore().RegisterImpactEvent(rMe.GetID(), rAttacker.GetID(), impact, 500);
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect049::OnEvent_DamageTarget
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	Character	&rTar,
	int32		&rDamage,
	SpellID_t	nSkillID
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ IDCollection const	*pCollection = DataManager::GetSingletonPtr()->getCollection(GetEffectedSkillCollection(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pCollection)
	{
		if(TRUE == pCollection->IsThisIDInCollection(nSkillID))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = rMe.GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pMap)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	nRand = pMap->GetRand100();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(nRand <= GetActivateOdds(rImp))
				{
					g_EffectInterface.SendEffectToUnit(rTar, GetSubImpact(rImp), rMe.GetID(), 0);
				}
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect050::RefixRageRegeneration(UNIT_EFFECT const &rImp, int32 &rRageRegeneration) const
{
	__GUARD__ rRageRegeneration *= GetRageRegenerateRefix(rImp);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect051::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetSummonerID(rImp, INVALID_ID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetShadowGuardID(rImp, INVALID_ID);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect051::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	//__GUARD__ if(GetSummonerID(rImp) == rMe.GetID())
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	Character	*pGuard = static_cast<Character *>(rMe.GetMyShadowGuard());
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if(NULL != pGuard)
	//	{
	//		pGuard->GM_killObj();
	//	}
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect051::SpecialHeartBeatCheck(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(GetSummonerID(rImp) == rMe.GetID())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pGuard = static_cast<Character *>(rMe.GetMyShadowGuard());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pGuard)
		{
			if(TRUE == pGuard->IsAlive() && TRUE == pGuard->IsActiveObj())
			{
				return TRUE;
			}
		}
	}

	if(GetShadowGuardID(rImp) == rMe.GetID())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pOwner = static_cast<Character *>
			(rMe.GetSpecificObjInSameSceneByID(GetSummonerID(rImp)));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pOwner)
		{
			if(pOwner->IsAlive() && TRUE == pOwner->IsActiveObj())
			{
				return TRUE;
			}
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect052::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nIdx = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(nIdx = OwnImpactParamIndex::IDX_TRAP_START; OwnImpactParamIndex::IDX_TRAP_END >= nIdx; ++nIdx)
	{
		SetTrapByIndex(rImp, nIdx, INVALID_ID);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ObjID_t SpellEffect052::GetTrapByIndex(UNIT_EFFECT &rImp, int32 nIdx) const
{
	__GUARD__ if(OwnImpactParamIndex::IDX_TRAP_START <= nIdx && OwnImpactParamIndex::IDX_TRAP_END >= nIdx)
	{
		return rImp.GetParamByIndex(OwnImpactParamIndex::IDX_TRAP_START + nIdx);
	}

	return INVALID_ID;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect052::SetTrapByIndex(UNIT_EFFECT &rImp, int32 nIdx, ObjID_t nID) const
{
	__GUARD__ if(OwnImpactParamIndex::IDX_TRAP_START <= nIdx && OwnImpactParamIndex::IDX_TRAP_END >= nIdx)
	{
		rImp.SetParamByIndex(OwnImpactParamIndex::IDX_TRAP_START + nIdx, nID);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect052::AddNewTrap(UNIT_EFFECT &rImp, Character &rMe, ObjID_t nID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	nTrapID = INVALID_ID;
	Object			*pObj = NULL;
	SpecialCreature		*pTrap = NULL;
	int32			nIdx = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(nIdx = OwnImpactParamIndex::IDX_TRAP_START; OwnImpactParamIndex::IDX_TRAP_END >= nIdx; ++nIdx)
	{
		nTrapID = GetTrapByIndex(rImp, nIdx);
		pObj = (SpecialCreature *) rMe.GetSpecificObjInSameSceneByID(nTrapID);
		if(NULL != pObj)
		{
			if(TRUE == IsObjSpecial(pObj->GetObjType()))
			{
				pTrap = (SpecialCreature *) pObj;
				if(FALSE == pTrap->IsFadeOut())
				{
					continue;
				}
			}
		}

		SetTrapByIndex(rImp, nIdx, nID);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect052::GetTrapCountOfSpecificType
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	int32		nType,
	int32		&rAllTypeTotal,
	int32		&rThisTypeCount
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ObjID_t	nTrapID = INVALID_ID;
	Object			*pObj = NULL;
	SpecialCreature		*pTrap = NULL;
	int32			nIdx = 0;
	SpecialObjData_T const	*pData = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(nIdx = OwnImpactParamIndex::IDX_TRAP_START; OwnImpactParamIndex::IDX_TRAP_END >= nIdx; ++nIdx)
	{
		nTrapID = GetTrapByIndex(rImp, nIdx);
		pObj = (SpecialCreature *) rMe.GetSpecificObjInSameSceneByID(nTrapID);
		if(NULL == pObj)
		{
			continue;
		}

		if(FALSE == IsObjSpecial(pObj->GetObjType()))
		{
			continue;
		}

		pTrap = (SpecialCreature *) pObj;
		if(TRUE == pTrap->IsFadeOut())
		{
			continue;
		}

		pData = pTrap->GetDataRecord();
		if(NULL == pData)
		{
			SetTrapByIndex(rImp, nIdx, INVALID_ID);
			continue;
		}

		++rAllTypeTotal;
		if(pData->GetClass() != nType)
		{
			continue;
		}

		++rThisTypeCount;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect052::SpecialHeartBeatCheck(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		nCount = 0;
	ObjID_t			nTrapID = INVALID_ID;
	Object			*pObj = NULL;
	SpecialCreature		*pTrap = NULL;
	int32			nIdx = 0;
	SpecialObjData_T const	*pData = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(nIdx = OwnImpactParamIndex::IDX_TRAP_START; OwnImpactParamIndex::IDX_TRAP_END >= nIdx; ++nIdx)
	{
		nTrapID = GetTrapByIndex(rImp, nIdx);
		pObj = (SpecialCreature *) rMe.GetSpecificObjInSameSceneByID(nTrapID);
		if(NULL == pObj)
		{
			SetTrapByIndex(rImp, nIdx, INVALID_ID);
			continue;
		}

		if(FALSE == IsObjSpecial(pObj->GetObjType()))
		{
			SetTrapByIndex(rImp, nIdx, INVALID_ID);
			continue;
		}

		pTrap = (SpecialCreature *) pObj;
		if(TRUE == pTrap->IsFadeOut())
		{
			SetTrapByIndex(rImp, nIdx, INVALID_ID);
			continue;
		}

		++nCount;
	}

	if(0 >= nCount)
	{
		if(-1 == rImp.GetContinuance())
		{
			rImp.SetContinuance(0);
			rImp.SetContinuanceElapsed(0);
		}
	}
	else
	{
		if(0 <= rImp.GetContinuance())
		{
			rImp.SetContinuance(-1);
			rImp.SetContinuanceElapsed(0);
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect053::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	//__GUARD__ if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	Player			&rPlayer = (Player &) rMe;
	//	const _SPELL_LIST	&rSkillList = rPlayer.GetSpellList();
	//	int32 const		nSkillCount = rSkillList.m_Count;
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	for(int32 nIndex = 0; nSkillCount > nIndex; ++nIndex)
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		SpellID_t	nSkillID = rSkillList.m_aSkill[nIndex].m_nSkillID;
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(INVALID_ID == nSkillID)
	//		{
	//			continue;
	//		}

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nSkillID);
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(NULL == pSkillTemplate)
	//		{
	//			continue;
	//		}

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		CooldownID_t	nCooldownID = pSkillTemplate->GetCooldownID();
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(0 <= nCooldownID)
	//		{
	//			if(nCooldownID != GetCooldownExclude(rImp) && FALSE == rMe.IsCooldowned(nCooldownID))
	//			{
	//				rMe.SetCooldown(nCooldownID, 0);
	//			}
	//		}
	//	}
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect054::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect054::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect054::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRate += 100;
	if(0 > nRate)
	{
		nRate = 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			nValue = 0;
	Character::_RELIVE_INFO ReliveInfo;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ReliveInfo.Reset();
	ReliveInfo.m_bHPUsePercent = TRUE;
	ReliveInfo.m_bMPUsePercent = TRUE;
	ReliveInfo.m_bSPUsePercent = TRUE;
	nValue = GetHpRecoverRate(rImp);
	nValue = Float2Int((nValue * nRate) * 0.01f);
	ReliveInfo.m_nHPPercent = nValue;
	nValue = GetMpRecoverRate(rImp);
	nValue = Float2Int((nValue * nRate) * 0.01f);
	ReliveInfo.m_nMPPercent = nValue;
	nValue = GetRageRecoverRate(rImp);
	nValue = Float2Int((nValue * nRate) * 0.01f);
	nValue = Float2Int((nValue * nRate));
	ReliveInfo.m_nSPPercent = nValue;
	ReliveInfo.m_MapID = rMe.GetMapID_i();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos const *pPos = rMe.GetGLPos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPos)
	{
		ReliveInfo.m_Pos.m_fX = pPos->m_fX;
		ReliveInfo.m_Pos.m_fZ = pPos->m_fZ;
	}

	rMe.SetReliveInfo(TRUE, &ReliveInfo);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect055::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nCollectionID0 = GetTransferCollection0(rImp);
	int32					nCollectionID1 = GetTransferCollection1(rImp);
	int32					nCount = GetTransferImpactCount(rImp);
	int32					nTransfered = 0;
	UNIT_EFFECT				impact;
	GameMap					*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = rMe.GetMyShadowGuard();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return;
	}

	if(FALSE == IsObjCharacter(pObj->GetObjType()))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pGuard = static_cast<Character *>(pObj);
	UNIT_EFFECT	*pTargetImp = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	do
	{
		if(NULL == pTargetImp)
		{
			if(INVALID_ID != nCollectionID0)
			{
				pTargetImp = rMe.Effect_GetFirstEffectInSpecificCollection(nCollectionID0);
			}
		}

		if(NULL == pTargetImp)
		{
			if(INVALID_ID != nCollectionID1)
			{
				pTargetImp = rMe.Effect_GetFirstEffectInSpecificCollection(nCollectionID1);
			}
		}

		if(NULL != pTargetImp)
		{
			impact = *pTargetImp;
			pMap->GetEventCore().RegisterImpactEvent(pGuard->GetID(), impact.GetCasterObjID(), impact, 0);
			rMe.Effect_OnEffectFadeOut(*pTargetImp);
			++nTransfered;
		}
	} while(NULL != pTargetImp && nTransfered < nCount);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect056::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetRefixRate(rImp, 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect056::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetHitRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_HIT);
	}

	if(0 != GetMissRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MISS);
	}

	if(0 != GetCriticalRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL);
	}

	if(0 != GetMaxHpRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP);
	}

	if(0 != GetAttackNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR);
	}

	if(0 != GetDefenceNearRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);;
	}

	if(0 != GetAttackMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC);
	}

	if(0 != GetDefenceMagicRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect056::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nRefixRate += 100;

	/*~~~~~~~~~~~~~~~*/
	int32	nValue = 0;
	/*~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_HIT:
		{
			if(0 != GetHitRefix(rImp))
			{
				nValue = Float2Int((GetHitRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MISS:
		{
			if(0 != GetMissRefix(rImp))
			{
				nValue = Float2Int((GetMissRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL:
		{
			if(0 != GetCriticalRefix(rImp))
			{
				nValue = Float2Int((GetCriticalRefix(rImp) * nRefixRate) / 100.0f);
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR:
		{
			if(0 != GetAttackNearRefix(rImp))
			{
				if (0 == GetRefixType(rImp))
				{
					nValue = Float2Int((GetAttackNearRefix(rImp) * nRefixRate) / 100.0f);
				}
				else
				{
					nValue = Float2Int((GetAttackNearRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.GetBaseAttackNear() * nValue) / 100.0f);
				}
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC:
		{
			if(0 != GetAttackMagicRefix(rImp))
			{
				if (0 == GetRefixType(rImp))
				{
					nValue = Float2Int((GetAttackMagicRefix(rImp) * nRefixRate) / 100.0f);
				}
				else
				{
					nValue = Float2Int((GetAttackMagicRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_AttackMagic() * nValue) / 100.0f);
				}
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		{
			if(0 != GetDefenceNearRefix(rImp))
			{
				if (0 == GetRefixType(rImp))
				{
					nValue = Float2Int((GetDefenceNearRefix(rImp) * nRefixRate) / 100.0f);
				}
				else
				{
					nValue = Float2Int((GetDefenceNearRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.GetBaseDefenceNear() * nValue) / 100.0f);
				}
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		{
			if(0 != GetDefenceMagicRefix(rImp))
			{
				if (0 == GetRefixType(rImp))
				{
					nValue = Float2Int((GetDefenceMagicRefix(rImp) * nRefixRate) / 100.0f);
				}
				else
				{
					nValue = Float2Int((GetDefenceMagicRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_DefenceMagic() * nValue) / 100.0f);
				}
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP:
		{
			if(0 != GetMaxHpRefix(rImp))
			{
				if (0 == GetRefixType(rImp))
				{
					nValue = Float2Int((GetMaxHpRefix(rImp) * nRefixRate) / 100.0f);
				}
				else
				{
					nValue = Float2Int((GetMaxHpRefix(rImp) * nRefixRate) / 100.0f);
					nValue = Float2Int((rMe.Get_BaseProperty_MaxHP() * nValue) / 100.0f);
				}
				rIntAttrRefix += nValue;
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect056::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += GetRefixRate(rImp);
	SetRefixRate(rImp, nRate);
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect057::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PET != rMe.GetObjType())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDamageRate = GetDamageRate(rImp);
	int32	nTransferRateForHp = GetTransferRateForHp(rImp);
	int32	nTransferRateForMp = GetTransferRateForMp(rImp);
	int32	nSubImpactForHeal = GetSubImpactHeal(rImp);
	int32	nDamage = Float2Int(rMe.GetHP() * nDamageRate / 100.0f);
	int32	nTransferedHp = Float2Int(nDamage * nTransferRateForHp / 100.0f);
	int32	nTransferedMp = Float2Int(nDamage * nTransferRateForMp / 100.0f);
	Object	*pObj = rMe.GetMyMaster();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(TRUE == IsObjCharacter(pObj->GetObjType()))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	&rMaster = *static_cast<Character *>(pObj);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rMe.HealthIncrement(-nDamage, rImp.GetCasterLogicCount(), &rMe);

			/*~~~~~~~~~~~~~~~~~~~*/
			UNIT_EFFECT	impact;
			/*~~~~~~~~~~~~~~~~~~~*/

			g_EffectInterface.InitEffectFromData(nSubImpactForHeal, impact, rMe);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ModifyHpMpRageStrikePointByValue_T	logic;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(0 < nTransferRateForHp)
			{
				logic.SetHpModification(impact, nTransferedHp);
			}

			if(0 < nTransferRateForMp)
			{
				logic.SetMpModification(impact, nTransferedMp);
			}

			pMap->GetEventCore().RegisterImpactEvent(rMaster.GetID(), rMe.GetID(), impact, 0);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpellEffect058::SpellEffect058()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpellEffect058::~SpellEffect058()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect058::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect058::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	int32		nHP = GetHpModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rMe.HealthIncrement(nHP, rImp.GetCasterLogicCount(), pImpactSender);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect058::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect058::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	SetHpModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				OwnImpactParamIndex::IDX_HP,
				rImp.GetSkillLevel()
			)
	);
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpellEffect059::SpellEffect059()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SpellEffect059::~SpellEffect059()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect059::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::ComputeLayerChange(UNIT_EFFECT &rImp, Character &rMe, int32 nCount, int32 iCurrentLayer) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect059::LayerFadeOut(UNIT_EFFECT &rImp) const
{
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect059::IsCanSendToUnit(UNIT_EFFECT &rImp, Character &rMe, Character *pChar) const
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect059::ScanUnitForTarget(UNIT_EFFECT &rImp, Character &rMe, float fX, float fZ, OBJLIST &rTargets) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect059::HitThisTarget(Character &rMe, Character &rTar, SpellID_t nSkillID) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect059::IsHit(Character &rMe, Character &rTar, int32 nAccuracy) const
{
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::BroadcastTargetListMessage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	OBJLIST			&rTargets,
	HitFlagsForOBJLIST_T	&rHitFlagsForObjList
) const
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::GetAccuracy(SpellID_t nSkillID) const
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::DoHitTarget
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	OBJLIST			&rTargets,
	HitFlagsForOBJLIST_T	&HitFlagList,
	uint32			&nCount
) const
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect059::SendLayerChangeMsg(UNIT_EFFECT &rImp, Character &rMe) const
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect061::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	InitDamages(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect061::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vDamage[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDamage[DAMAGE_TYPE_NEAR] = GetDamageNear(rImp);
	vDamage[DAMAGE_TYPE_FAR] = GetDamageFar(rImp);
	vDamage[DAMAGE_TYPE_M] = GetDamageMagic(rImp);
	vDamage[DAMAGE_TYPE_COLD] = GetDamageCold(rImp);
	vDamage[DAMAGE_TYPE_FIRE] = GetDamageFire(rImp);
	vDamage[DAMAGE_TYPE_LIGHT] = GetDamageLight(rImp);
	vDamage[DAMAGE_TYPE_POISON] = GetDamagePoison(rImp);

	rMe.OnEvent_Damages
	(
		vDamage,
		rImp.GetCasterObjID(),
		rImp.IsCriticalHit(),
		rImp.GetSkillID(),
		rImp.GetCasterLogicCount()
	);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect061::CriticalRefix(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamageNear(rImp, GetDamageNear(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageFar(rImp, GetDamageFar(rImp));
	SetDamageMagic(rImp, GetDamageMagic(rImp));
	SetDamageCold(rImp, GetDamageCold(rImp));
	SetDamageFire(rImp, GetDamageFire(rImp));
	SetDamageLight(rImp, GetDamageLight(rImp));
	SetDamagePoison(rImp, GetDamagePoison(rImp));
	rImp.MarkCriticalFlag();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect061::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTemp = GetDamageNear(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageNear(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFar(rImp);
	SetDamageFar(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageMagic(rImp);
	SetDamageMagic(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageCold(rImp);
	SetDamageCold(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFire(rImp);
	SetDamageFire(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageLight(rImp);
	SetDamageLight(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamagePoison(rImp);
	SetDamagePoison(rImp, Float2Int((iTemp * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect061::InitDamages(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamageNear
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_DAMAGE_NEAR,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageFar
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FAR,
				rImp.GetSkillLevel()
			)
	);
	SetDamageMagic
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_MAGIC,
				rImp.GetSkillLevel()
			)
	);
	SetDamageCold
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_COLD,
				rImp.GetSkillLevel()
			)
	);
	SetDamageFire
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FIRE,
				rImp.GetSkillLevel()
			)
	);
	SetDamageLight
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_LIGHT,
				rImp.GetSkillLevel()
			)
	);
	SetDamagePoison
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_POISON,
				rImp.GetSkillLevel()
			)
	);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect062::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ 	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect062::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ __UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
//void SpellEffect062::InitDamages(UNIT_EFFECT &rImp) const
//{
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	__GUARD__	SetHP
//			(
//					rImp,
//					GetEffectDataDescriptorValueByIndex
//					(
//						rImp.GetDataIndex(),
//						ImpactDataDescriptorIndex::IDX_REFIX_HP,
//						rImp.GetSkillLevel()
//					)
//			);
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	SetRage0
//	(
//		rImp,
//		GetEffectDataDescriptorValueByIndex
//			(
//				rImp.GetDataIndex(),
//				ImpactDataDescriptorIndex::IDX_REFIX_RAGE0,
//				rImp.GetSkillLevel()
//			)
//	);
//	SetRage1
//	(
//		rImp,
//		GetEffectDataDescriptorValueByIndex
//			(
//				rImp.GetDataIndex(),
//				ImpactDataDescriptorIndex::IDX_REFIX_RAGE1,
//				rImp.GetSkillLevel()
//			)
//	);
//	SetRage2
//	(
//		rImp,
//		GetEffectDataDescriptorValueByIndex
//			(
//				rImp.GetDataIndex(),
//				ImpactDataDescriptorIndex::IDX_REFIX_RAGE2,
//				rImp.GetSkillLevel()
//			)
//	);
//	SetRage3
//	(
//		rImp,
//		GetEffectDataDescriptorValueByIndex
//			(
//				rImp.GetDataIndex(),
//				ImpactDataDescriptorIndex::IDX_REFIX_RAGE3,
//				rImp.GetSkillLevel()
//			)
//	);
//	SetRage4
//	(
//		rImp,
//		GetEffectDataDescriptorValueByIndex
//			(
//				rImp.GetDataIndex(),
//				ImpactDataDescriptorIndex::IDX_REFIX_RAGE4,
//				rImp.GetSkillLevel()
//			)
//	);
//	SetRage5
//	(
//		rImp,
//		GetEffectDataDescriptorValueByIndex
//			(
//				rImp.GetDataIndex(),
//				ImpactDataDescriptorIndex::IDX_REFIX_RAGE5,
//				rImp.GetSkillLevel()
//			)
//	);
//	__UNGUARD__
//}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellEffect062::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pImpactSender)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixType = GetRefixType(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//InitDamages(rImp);

	if(pImpactSender->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamage = GetDamageRefix(pImpactSender, rImp);
	Player	&rPlayer = static_cast<Player &>(*pImpactSender);
	int32	iBase = rPlayer.Get_Property_Rage();
	int32	iRefix = GetRageByZhiYe(rImp, rPlayer.GetProfession());
	int32	iResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != iRefix)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iResult = GetRifixResult(iBase, iRefix, iRefixType);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		iResult += iDamage;
		rMe.RageIncrement(iResult, rImp.GetCasterLogicCount());
		SetOwnRefix(rImp, OwnImpactParamIndex::IDX_REFIX_RATE, iResult);
	}

	iBase = rMe.GetMaxHP();
	iRefix = GetHP(rImp);
	if(INVALID_ID != iRefix)
	{
		iResult = GetRifixResult(iBase, iRefix, iRefixType);
		iResult += iDamage;
		BOOL PKRateFlag = GetEffectPKRateCtr(rImp) > 0 ? TRUE : FALSE;
		rMe.HealthIncrement(iResult, rImp.GetCasterLogicCount(), pImpactSender, FALSE, TRUE, FALSE, PKRateFlag);
		SetOwnRefix(rImp, OwnImpactParamIndex::IDX_REFIX_HP, iResult);

	}

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect062::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	int32 iRage = GetOwnRefix(rImp, OwnImpactParamIndex::IDX_REFIX_RATE);

	if (iRage > 0)
	{
		rMe.RageIncrement(iRage, rImp.GetCasterLogicCount());
	}

	int32 iHp = GetOwnRefix(rImp, OwnImpactParamIndex::IDX_REFIX_HP);

	if (iHp > 0)
	{
		Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
		BOOL PKRateFlag = GetEffectPKRateCtr(rImp) > 0 ? TRUE : FALSE;
		rMe.HealthIncrement(iHp, rImp.GetCasterLogicCount(), pImpactSender, FALSE, TRUE, FALSE, PKRateFlag);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect062::GetRifixResult(int32 iBase, int32 iRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		iRefixResult = iRefix;
	}
	else
	{
		iRefixResult = ((iBase * iRefix) / 100);
	}

	return iRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect062::GetRageByZhiYe(UNIT_EFFECT &rImp, int32 iZhiYe) const
{
	switch(iZhiYe)
	{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:
			return GetRage0(rImp); 
		break;
		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:
			return GetRage1(rImp); 
		break;
		case PROFESSION_QISHE:	
		case PROFESSION_CIKE:
			return GetRage2(rImp); 
		break;
		case PROFESSION_HUOQIANG:	
		case PROFESSION_JINWEIJUN:
			return GetRage3(rImp); 
		break;
		case PROFESSION_XIANZHI:
		case PROFESSION_YINXIUSHI:
			return GetRage4(rImp); 
		break;
		case PROFESSION_SAMAN:
		case PROFESSION_LAMA:
			return GetRage5(rImp); 
		break;
		default:	break;
	}

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect062::GetDamageRefix(Character *pImpactSender, UNIT_EFFECT &rImp) const
{
	if(pImpactSender->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = static_cast<Player *>(pImpactSender);
	int32	iDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if( PROFESSION_WUSHI == pPlayer->GetProfession() || 
		PROFESSION_SHIZIJUN == pPlayer->GetProfession() ||
		PROFESSION_JIANXIA == pPlayer->GetProfession() ||
		PROFESSION_SHENGHUOSHI == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackNear();
	}
	else if(PROFESSION_QISHE == pPlayer->GetProfession() || 
		PROFESSION_CIKE == pPlayer->GetProfession() ||
		PROFESSION_HUOQIANG == pPlayer->GetProfession() ||
		PROFESSION_JINWEIJUN == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackFar();
	}
	else
	{
		iDamage = pPlayer->Get_Property_AttackMagic();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDamage = Float2Int(iDamage * iRefixRate * 0.01f);
	return iDamage;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect063::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect063::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamageType = GetDamageType(rImp);
	int32	iRefixType = GetEffectDataDescriptorValueByIndex
		(
			rImp.GetDataIndex(),
			ImpactDataDescriptorIndex::IDX_REFIX_TYPE,
			rImp.GetSkillLevel()
		);
	int32	iRefix = GetDamagePoint(rImp, iDamageType);
	int32	iBase = rMe.GetMaxHP();
	int32	iResult = GetRifixResult(iBase, iRefix, iRefixType);

	iResult = iResult < 1 ? 1 : iResult;

	GameMap	*pMap = rMe.GetMap();
	if(pMap == NULL)
	{
		return;
	}

	Character *pAttacker = GetEffectCharacterObj(rImp, rMe);
	BOOL PKRateFlag = GetEffectPKRateCtr(rImp) > 0 ? TRUE : FALSE;
	rMe.HealthIncrement(-iResult, rImp.GetCasterLogicCount(), pAttacker, FALSE, TRUE, FALSE, PKRateFlag);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect063::GetRifixResult(int32 iBase, int32 iRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		iRefixResult = iRefix;
	}
	else
	{
		iRefixResult = Float2Int((iBase * iRefix) * 0.01f);
	}

	return iRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect063::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pAttacker = GetEffectCharacterObj(rImp, rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAttacker == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixType = GetEffectDataDescriptorValueByIndex
		(
			rImp.GetDataIndex(),
			ImpactDataDescriptorIndex::IDX_REFIX_TYPE,
			rImp.GetSkillLevel()
		);
	int32	iDamageType = GetDamageType(rImp);
	int32	iDamagePara = GetDamagePara(rImp);
	int32	iAttackWeight = GetAttackWeight(rImp);
	int32	iDefenceWeight = GetDefenceWeight(rImp);
	int32	vDamage[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDamage[DAMAGE_TYPE_NEAR] = pAttacker->GetAttackNear();
	vDamage[DAMAGE_TYPE_FAR] = pAttacker->GetAttackFar();
	vDamage[DAMAGE_TYPE_M] = pAttacker->Get_Property_AttackMagic();
	vDamage[DAMAGE_TYPE_COLD] = pAttacker->Get_Property_AttackCold();
	vDamage[DAMAGE_TYPE_FIRE] = pAttacker->Get_Property_AttackFire();
	vDamage[DAMAGE_TYPE_LIGHT] = pAttacker->Get_Property_AttackLight();
	vDamage[DAMAGE_TYPE_POISON] = pAttacker->Get_Property_AttackPoison();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vDefence[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDefence[DAMAGE_TYPE_NEAR] = rMe.GetDefenceNear();
	vDefence[DAMAGE_TYPE_FAR] = rMe.GetDefenceFar();
	vDefence[DAMAGE_TYPE_M] = rMe.Get_Property_DefenceMagic();
	vDefence[DAMAGE_TYPE_COLD] = rMe.Get_Property_DefenceCold();
	vDefence[DAMAGE_TYPE_FIRE] = rMe.Get_Property_DefenceFire();
	vDefence[DAMAGE_TYPE_LIGHT] = rMe.Get_Property_DefenceLight();
	vDefence[DAMAGE_TYPE_POISON] = rMe.Get_Property_DefencePoison();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vReduce[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(vReduce, 0, sizeof(vReduce));
	vReduce[DAMAGE_TYPE_NEAR] = Property_VerifyResist(rMe.GetNearAttReduce());
	vReduce[DAMAGE_TYPE_FAR] = Property_VerifyResist(rMe.GetFarAttReduce());
	vReduce[DAMAGE_TYPE_M] = Property_VerifyResist(rMe.GetMagicAttReduce());

	//CombatSystem CSHelper;
	//int32 nProfessionRefixRate = CSHelper.GetProfessionDamageRefixRate(*pAttacker, rMe);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//int32	iRefix = iDamagePara + Float2Int(vDamage[iDamageType] * iAttackWeight * 0.01f) - Float2Int(vDefence[iDamageType] * iDefenceWeight * 0.01f);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//iRefix = Float2Int((iRefix * (100 - vReduce[iDamageType])) * 0.01f);

	//iRefix = Float2Int(iRefix * nProfessionRefixRate * 0.01f);

	//SetDamagePoint(rImp, iDamageType, iRefix);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect064::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__ return;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect064::OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
{
	__GUARD__ if(EffectTypeOnSkillSuccess != GetEffectType(rImp))
	{
		return;
	}

	if(!IsHappend(rMe, rImp))
	{
		return;
	}

	if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Character				*pChar = (Character *) pMap->GetSpecificObjByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pChar)
	{
		return;
	}

	if(INVALID_ID == rSkill.GetSpellID())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	IDCollection const	*pCollection = DataManager::GetSingletonPtr()->getCollection(GetEffectedSkillCollection(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCollection)
	{
		return;
	}

	if(FALSE == pCollection->IsThisIDInCollection(rSkill.GetSpellID()))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iTargetType = GetTargetType(rImp);
	Behavior_Character	*pAI = rMe.GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAI == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t		iTargetID = INVALID_ID;
	const GLPos *pPos = NULL;
	GUID_t		iGuid = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTargetType == TargetTypeMe)
	{
		iTargetID = rMe.GetID();
		pPos = rMe.GetGLPos();
	}
	else
	{
		iTargetID = rParams.GetTargetObj();
		pPos = pChar->GetGLPos();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	HurtDelayTime = GetSpellHurtDelayTime(GetSkillID(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Player	*pAIHuman = (Behavior_Player *) pAI;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pAIHuman->PushCmd_UseSpell
			(
				GetSkillID(rImp),
				iTargetID,
				pPos->m_fX,
				pPos->m_fZ,
				rMe.GetDir(),
				iGuid,
				HurtDelayTime,
				TRUE
			);
	}
	else
	{
		pAI->BHV_UseSpell(GetSkillID(rImp), iTargetID, pPos->m_fX, pPos->m_fZ, HurtDelayTime, rMe.GetDir(), iGuid);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect064::OnEvent_BeHit(UNIT_EFFECT &rImp, Character &rMe, Character &rAttacker) const
{
	__GUARD__ if(EffectTypeOnBeHit != GetEffectType(rImp))
	{
		return;
	}

	if(!IsHappend(rMe, rImp))
	{
		return;
	}

	if(TRUE == rImp.IsFadeOut())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo	&rSkill = rAttacker.GetSpellInfo();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == rSkill.GetSpellID())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	IDCollection const	*pCollection = DataManager::GetSingletonPtr()->getCollection(GetEffectedSkillCollection(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pCollection)
	{
		return;
	}

	if(FALSE == pCollection->IsThisIDInCollection(rSkill.GetSpellID()))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iTargetType = GetTargetType(rImp);
	Behavior_Character	*pAI = rMe.GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAI == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t		iTargetID = INVALID_ID;
	const GLPos *pPos = NULL;
	GUID_t		iGuid = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTargetType == TargetTypeMe)
	{
		iTargetID = rMe.GetID();
		pPos = rMe.GetGLPos();
	}
	else
	{
		iTargetID = rAttacker.GetID();
		pPos = rAttacker.GetGLPos();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	HurtDelayTime = GetSpellHurtDelayTime(GetSkillID(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Player	*pAIHuman = (Behavior_Player *) pAI;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pAIHuman->PushCmd_UseSpell
			(
				GetSkillID(rImp),
				iTargetID,
				pPos->m_fX,
				pPos->m_fZ,
				rMe.GetDir(),
				iGuid,
				HurtDelayTime,
				TRUE
			);
	}
	else
	{
		pAI->BHV_UseSpell(GetSkillID(rImp), iTargetID, pPos->m_fX, pPos->m_fZ, HurtDelayTime, rMe.GetDir(), iGuid);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect064::IsHappend(Character &rMe, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRate = GetEffectRate(rImp);
	int32	nRand = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRand <= iRate)
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(!IsCanHappen(rImp, EffectTypeOnDamage, nSkillID, rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
{
	__GUARD__ if(!IsCanHappen(rImp, EffectTypeOnUseSkillSuccessfully, rSkill.GetSpellID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_BeHit(UNIT_EFFECT &rImp, Character &rMe, Character &rAttacker) const
{
	__GUARD__ if(!IsCanHappen(rImp, EffectTypeOnBeHit, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_BeCriticalHit(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnBeCriticalHit, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_BeHeal(UNIT_EFFECT &rImp, Character &rMe, int32 &nHealedHP) const
{
	if(!IsCanHappen(rImp, EffectTypeOnBeHeal, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_CriticalHitTarget(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnCriticalHitTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_Damages
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32 *const		pDamageList,
	SpellID_t		nSkillID
) const
{
	if(!IsCanHappen(rImp, EffectTypeOnDamages, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_DamageTarget
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	Character	&rTar,
	int32		&rDamage,
	SpellID_t	nSkillID
) const
{
	if(!IsCanHappen(rImp, EffectTypeOnDamageTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_Die(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnDie, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnFadeOut, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_HealTarget(UNIT_EFFECT &rImp, Character &rMe, int32 &rHealedHP) const
{
	if(!IsCanHappen(rImp, EffectTypeOnHealTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect065::OnEvent_HitTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	if(!IsCanHappen(rImp, EffectTypeOnHitTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendImpactToMe(rImp, rMe);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect065::IsHappend(Character &rMe, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRate = GetEffectRate(rImp);
	int32	nRand = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRand <= iRate)
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect065::IsCanHappen(UNIT_EFFECT &rImp, int32 iEffectType, SpellID_t nSkillID, Character &rMe) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return FALSE;
	}

	if(iEffectType != GetEffectType(rImp))
	{
		return FALSE;
	}

	if(!IsHappend(rMe, rImp))
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
void SpellEffect065::SendImpactToMe(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nEffectID = GetImpactID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	g_EffectInterface.SendEffectToUnit(rMe, nEffectID, rMe.GetID(), 0);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_Damage
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32			&rDamage,
	SpellID_t		nSkillID
) const
{
	__GUARD__ if(NULL == pAttacker)
	{
		return;
	}

	if(!IsCanHappen(rImp, EffectTypeOnDamage, nSkillID, rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *pAttacker);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
{
	__GUARD__ if(!IsCanHappen(rImp, EffectTypeOnUseSkillSuccessfully, rSkill.GetSpellID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetBeHitTarget(rMe, rImp));
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_BeHit(UNIT_EFFECT &rImp, Character &rMe, Character &rAttacker) const
{
	__GUARD__ if(!IsCanHappen(rImp, EffectTypeOnBeHit, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, rAttacker);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_BeCriticalHit(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnBeCriticalHit, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetAttackerTarget(rMe, rImp));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_BeHeal(UNIT_EFFECT &rImp, Character &rMe, int32 &nHealedHP) const
{
	if(!IsCanHappen(rImp, EffectTypeOnBeHeal, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetAttackerTarget(rMe, rImp));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_CriticalHitTarget(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnCriticalHitTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetBeHitTarget(rMe, rImp));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_Damages
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	Character *const	pAttacker,
	int32 *const		pDamageList,
	SpellID_t		nSkillID
) const
{
	if(NULL == pAttacker)
	{
		return;
	}

	if(!IsCanHappen(rImp, EffectTypeOnDamages, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *pAttacker);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_DamageTarget
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	Character	&rTar,
	int32		&rDamage,
	SpellID_t	nSkillID
) const
{
	if(!IsCanHappen(rImp, EffectTypeOnDamageTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, rTar);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_Die(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnDie, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetAttackerTarget(rMe, rImp));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	if(!IsCanHappen(rImp, EffectTypeOnFadeOut, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetAttackerTarget(rMe, rImp));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_HealTarget(UNIT_EFFECT &rImp, Character &rMe, int32 &rHealedHP) const
{
	if(!IsCanHappen(rImp, EffectTypeOnHealTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, *GetBeHitTarget(rMe, rImp));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect066::OnEvent_HitTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	if(!IsCanHappen(rImp, EffectTypeOnHitTarget, rImp.GetSkillID(), rMe))
	{
		return;
	}

	SendSkillToTarget(rImp, rMe, rTar);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect066::IsHappend(Character &rMe, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRate = GetEffectRate(rImp);
	int32	nRand = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRand <= iRate)
	{
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect066::IsCanHappen(UNIT_EFFECT &rImp, int32 iEffectType, SpellID_t nSkillID, Character &rMe) const
{
	__GUARD__ if(TRUE == rImp.IsFadeOut())
	{
		return FALSE;
	}

	if(iEffectType != GetEffectType(rImp))
	{
		return FALSE;
	}

	if(!IsHappend(rMe, rImp))
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
void SpellEffect066::SendSkillToTarget(UNIT_EFFECT &rImp, Character &rMe, Character &rAttacker) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iTargetType = GetTargetType(rImp);
	Behavior_Character	*pAI = rMe.GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAI == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ObjID_t		iTargetID = INVALID_ID;
	const GLPos *pPos = NULL;
	GUID_t		iGuid = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTargetType == TargetTypeMe)
	{
		iTargetID = rMe.GetID();
		pPos = rMe.GetGLPos();
	}
	else
	{
		iTargetID = rAttacker.GetID();
		pPos = rAttacker.GetGLPos();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	HurtDelayTime = GetSpellHurtDelayTime(GetSkillID(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Behavior_Player		*pAIHuman = (Behavior_Player *) pAI;
		const SpellTemplateData *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(GetSkillID(rImp));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pAIHuman->PushCmd_UseSpell
			(
				GetSkillID(rImp),
				iTargetID,
				pPos->m_fX,
				pPos->m_fZ,
				rMe.GetDir(),
				iGuid,
				HurtDelayTime,
				TRUE
			);
	}
	else
	{
		pAI->BHV_UseSpell(GetSkillID(rImp), iTargetID, pPos->m_fX, pPos->m_fZ, HurtDelayTime, rMe.GetDir(), iGuid);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Character *SpellEffect066::GetAttackerTarget(Character &rMe, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMap == NULL)
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iTargetID = rImp.GetCasterObjID();
	Character	*pChar = (Character *) pMap->GetSpecificObjByID(iTargetID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return pChar;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Character *SpellEffect066::GetBeHitTarget(Character &rMe, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMap == NULL)
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Character				*pChar = (Character *) pMap->GetSpecificObjByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return pChar;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect067::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect067::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ for(int32 i = 0; i < MAX_REFIX; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iType = GetRefixType(rImp, i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID == iType)
		{
			break;
		}

		MarkDirtyFlag(rImp, rMe, iType);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect067::FindIndex(UNIT_EFFECT &rImp, Character &rMe, int32 iType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iResult = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < MAX_REFIX; ++i)
	{
		if(INVALID_ID == iType)
		{
			break;
		}

		if(iType == GetRefixType(rImp, i))
		{
			iResult = i;
			break;
		}
	}

	return iResult;
	__UNGUARD__ return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect067::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_STR:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_STR);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_CON:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_CON);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_INT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_INT);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEX:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEX);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_HP_REGENERATE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_RESTORE_HP);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_MAX_HP);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_HIT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_HIT);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MISS:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_MISS);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_CRIT_RATE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_SPEED);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_SPEED:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_SPEED);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MAX_RAGE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ANGER);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_NEAR);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_FAR);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_MAGIC);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_COLD);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_FIRE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_LIGHT);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_ATTACK_POISON);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_NEAR);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_FAR);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_MAGIC);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_COLD);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_FIRE);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_LIGHT);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iResult = GetRefixResult(rImp, rMe, CHAR_ATT_DEFENCE_POISON);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rIntAttrRefix += iResult;
			return TRUE;
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect067::MarkDirtyFlag(UNIT_EFFECT &rImp, Character &rMe, int32 iType) const
{
	__GUARD__ switch(iType)
	{
	case CHAR_ATT_INVALID:		break;
	case CHAR_ATT_STR:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_STR); break;
	case CHAR_ATT_CON:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CON); break;
	case CHAR_ATT_INT:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_INT); break;
	case CHAR_ATT_DEX:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEX); break;
	case CHAR_ATT_HP:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP); break;
	case CHAR_ATT_MAX_HP:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_HP); break;
	case CHAR_ATT_RESTORE_HP:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_HP_REGENERATE); break;
	case CHAR_ATT_HIT:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_HIT); break;
	case CHAR_ATT_MISS:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MISS); break;
	case CHAR_ATT_CRIT_RATE:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL); break;
	case CHAR_ATT_SPEED:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MOVE_SPEED); break;
	case CHAR_ATT_ATTACK_SPEED:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_SPEED); break;
	case CHAR_ATT_ATTACK_NEAR:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR); break;
	case CHAR_ATT_DEFENCE_NEAR:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR);; break;
	case CHAR_ATT_ATTACK_FAR:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR); break;
	case CHAR_ATT_DEFENCE_FAR:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR); break;
	case CHAR_ATT_ATTACK_MAGIC:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC); break;
	case CHAR_ATT_DEFENCE_MAGIC:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC); break;
	case CHAR_ATT_ATTACK_COLD:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_COLD); break;
	case CHAR_ATT_DEFENCE_COLD:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_COLD); break;
	case CHAR_ATT_ATTACK_FIRE:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FIRE); break;
	case CHAR_ATT_DEFENCE_FIRE:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_FIRE); break;
	case CHAR_ATT_ATTACK_LIGHT:		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_LIGHT); break;
	case CHAR_ATT_DEFENCE_LIGHT:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_LIGHT); break;
	case CHAR_ATT_ATTACK_POISON:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_POISON); break;
	case CHAR_ATT_DEFENCE_POISON:	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RESIST_POISON); break;
	case CHAR_ATT_ANGER:			rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_RAGE); break;
	default:			break;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect067::GetRefixPara(UNIT_EFFECT &rImp, Character &rMe, int32 iIndex) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ int32 iPara = GetRefixParaID(rImp, iIndex);
	//int32		iRate = GetRefixRate(rImp, iIndex);
	//Player		&rPlayer = static_cast<Player &>(rMe);
	//SHorseGiud	guidHorse = rPlayer.GetGUIDOfCallUpHorse();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(guidHorse.IsNull())
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = rPlayer.GetHorseItem(guidHorse);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return 0;
	//}

	//return GetHorseRefix(iPara, pPetItem, iRate);
	//__UNGUARD__ 
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect067::GetRefixResult(UNIT_EFFECT &rImp, Character &rMe, int32 iType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = FindIndex(rImp, rMe, iType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == iIndex)
	{
		return 0;
	}

	return GetRefixPara(rImp, rMe, iIndex);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect068::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect068::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nDeltaHP = rMe.GetHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	InitImpact(rImp);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vDamage[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDamage[DAMAGE_TYPE_NEAR] = GetDamageNear(rImp);
	vDamage[DAMAGE_TYPE_FAR] = GetDamageFar(rImp);
	vDamage[DAMAGE_TYPE_M] = GetDamageMagic(rImp);
	vDamage[DAMAGE_TYPE_COLD] = GetDamageCold(rImp);
	vDamage[DAMAGE_TYPE_FIRE] = GetDamageFire(rImp);
	vDamage[DAMAGE_TYPE_LIGHT] = GetDamageLight(rImp);
	vDamage[DAMAGE_TYPE_POISON] = GetDamagePoison(rImp);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iResult = GetRefixPara(rImp, rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < DAMAGE_TYPE_NUMBER; ++i)
	{
		if(0 >= vDamage[i])
		{
			continue;
		}

		vDamage[i] = iResult;
	}

	FinalDamage(vDamage, rMe);

	rMe.OnEvent_Damages
	(
		vDamage,
		rImp.GetCasterObjID(),
		rImp.IsCriticalHit(),
		rImp.GetSkillID(),
		rImp.GetCasterLogicCount()
	);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect068::CriticalRefix(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamageNear(rImp, GetDamageNear(rImp) * 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageFar(rImp, GetDamageFar(rImp) * 2);
	SetDamageMagic(rImp, GetDamageMagic(rImp) * 2);
	SetDamageCold(rImp, GetDamageCold(rImp) * 2);
	SetDamageFire(rImp, GetDamageFire(rImp) * 2);
	SetDamageLight(rImp, GetDamageLight(rImp) * 2);
	SetDamagePoison(rImp, GetDamagePoison(rImp) * 2);
	rImp.MarkCriticalFlag();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect068::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTemp = GetDamageNear(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageNear(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFar(rImp);
	SetDamageFar(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageMagic(rImp);
	SetDamageMagic(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageCold(rImp);
	SetDamageCold(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFire(rImp);
	SetDamageFire(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageLight(rImp);
	SetDamageLight(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamagePoison(rImp);
	SetDamagePoison(rImp, Float2Int((iTemp * nRate) / 100.0f));
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect068::GetRefixPara(UNIT_EFFECT &rImp, Character &rMe) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ int32 iPara = GetParaID(rImp);
	//int32		iRate = GetRefixRate(rImp);
	//Character	*pChar = (Character *) GetEffectCaster(rMe, rImp);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pChar)
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player		*rPlayer = static_cast<Player *>(pChar);
	//SHorseGiud	guidHorse = rPlayer->GetGUIDOfCallUpHorse();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(guidHorse.IsNull())
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = rPlayer->GetHorseItem(guidHorse);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return 0;
	//}

	//return GetHorseRefix(iPara, pPetItem, iRate);
	//__UNGUARD__ 
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect068::InitImpact(UNIT_EFFECT &rImp) const
{
	SetParaID
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_PARA_ID,
				rImp.GetSkillLevel()
			)
	);

	SetRefixRate
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_REFIX_RATE,
				rImp.GetSkillLevel()
			)
	);
	SetDamageNear
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_NEAR,
				rImp.GetSkillLevel()
			)
	);
	SetDamageFar
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FAR,
				rImp.GetSkillLevel()
			)
	);
	SetDamageMagic
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_MAGIC,
				rImp.GetSkillLevel()
			)
	);
	SetDamageCold
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_COLD,
				rImp.GetSkillLevel()
			)
	);
	SetDamageFire
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FIRE,
				rImp.GetSkillLevel()
			)
	);
	SetDamageLight
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_LIGHT,
				rImp.GetSkillLevel()
			)
	);
	SetDamagePoison
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_POISON,
				rImp.GetSkillLevel()
			)
	);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect069::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect069::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	InitDamages(rImp);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iResult = GetRefixPara(rImp, rMe);
	int32	vDamage[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDamage[DAMAGE_TYPE_NEAR] = GetDamageNear(rImp);
	vDamage[DAMAGE_TYPE_FAR] = GetDamageFar(rImp);
	vDamage[DAMAGE_TYPE_M] = GetDamageMagic(rImp);
	vDamage[DAMAGE_TYPE_COLD] = GetDamageCold(rImp);
	vDamage[DAMAGE_TYPE_FIRE] = GetDamageFire(rImp);
	vDamage[DAMAGE_TYPE_LIGHT] = GetDamageLight(rImp);
	vDamage[DAMAGE_TYPE_POISON] = GetDamagePoison(rImp);
	for(int32 i = 0; i < DAMAGE_TYPE_NUMBER; ++i)
	{
		if(0 == vDamage[i])
		{
			continue;
		}

		vDamage[i] = (int32) (((vDamage[i] + 100) * iResult) * 0.01f + 0.5f);
	}

	FinalDamage(vDamage, rMe);

	rMe.OnEvent_Damages
	(
		vDamage,
		rImp.GetCasterObjID(),
		rImp.IsCriticalHit(),
		rImp.GetSkillID(),
		rImp.GetCasterLogicCount()
	);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect069::CriticalRefix(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetDamageNear(rImp, GetDamageNear(rImp) * 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageFar(rImp, GetDamageFar(rImp) * 2);
	SetDamageMagic(rImp, GetDamageMagic(rImp) * 2);
	SetDamageCold(rImp, GetDamageCold(rImp) * 2);
	SetDamageFire(rImp, GetDamageFire(rImp) * 2);
	SetDamageLight(rImp, GetDamageLight(rImp) * 2);
	SetDamagePoison(rImp, GetDamagePoison(rImp) * 2);
	rImp.MarkCriticalFlag();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect069::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTemp = GetDamageNear(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetDamageNear(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFar(rImp);
	SetDamageFar(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageMagic(rImp);
	SetDamageMagic(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageCold(rImp);
	SetDamageCold(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageFire(rImp);
	SetDamageFire(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamageLight(rImp);
	SetDamageLight(rImp, Float2Int((iTemp * nRate) / 100.0f));
	iTemp = GetDamagePoison(rImp);
	SetDamagePoison(rImp, Float2Int((iTemp * nRate) / 100.0f));

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect069::InitDamages(UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetParaID
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_PARA_ID,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetRefixRate
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_REFIX_RATE,
				rImp.GetSkillLevel()
			)
	);

	SetDamageNear
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_NEAR,
				rImp.GetSkillLevel()
			)
	);
	SetDamageFar
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FAR,
				rImp.GetSkillLevel()
			)
	);
	SetDamageMagic
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_MAGIC,
				rImp.GetSkillLevel()
			)
	);
	SetDamageCold
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_COLD,
				rImp.GetSkillLevel()
			)
	);
	SetDamageFire
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_FIRE,
				rImp.GetSkillLevel()
			)
	);
	SetDamageLight
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_LIGHT,
				rImp.GetSkillLevel()
			)
	);
	SetDamagePoison
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_DAMAGE_POISON,
				rImp.GetSkillLevel()
			)
	);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect069::GetRefixPara(UNIT_EFFECT &rImp, Character &rMe) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ int32 iPara = GetParaID(rImp);
	//int32		iRate = GetRefixRate(rImp);
	//Character	*pChar = (Character *) GetEffectCaster(rMe, rImp);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pChar)
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player		*rPlayer = static_cast<Player *>(pChar);
	//SHorseGiud	guidHorse = rPlayer->GetGUIDOfCallUpHorse();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(guidHorse.IsNull())
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = rPlayer->GetHorseItem(guidHorse);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return 0;
	//}

	//return GetHorseRefix(iPara, pPetItem, iRate);
	//__UNGUARD__ 
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect070::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect070::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamageType = GetDamageType(rImp);
	int32	iRefixType = GetEffectDataDescriptorValueByIndex
		(
			rImp.GetDataIndex(),
			ImpactDataDescriptorIndex::IDX_REFIX_TYPE,
			rImp.GetSkillLevel()
		);
	int32	iRefix = GetDamagePoint(rImp, iDamageType);
	int32	iBase = rMe.GetHP();
	int32	iResult = GetRifixResult(iBase, iRefix, iRefixType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iResult = iResult < 0 ? 0 : iResult;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixPara = GetRefixPara(rImp, rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iResult += iRefixPara;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pAttacker = GetEffectCharacterObj(rImp, rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	BOOL PKRateFlag = GetEffectPKRateCtr(rImp) > 0 ? TRUE : FALSE;
	rMe.HealthIncrement(-iResult, rImp.GetCasterLogicCount(), pAttacker, FALSE, TRUE, FALSE, PKRateFlag);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect070::GetRifixResult(int32 iBase, int32 iRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		iRefixResult = iRefix;
	}
	else
	{
		iRefixResult = Float2Int((iBase * iRefix) * 0.01f);
	}

	return iRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect070::GetRefixPara(UNIT_EFFECT &rImp, Character &rMe) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ int32 iPara = GetParaID(rImp);
	//int32		iRate = GetRefixRate(rImp);
	//Player		&rPlayer = static_cast<Player &>(rMe);
	//SHorseGiud	guidHorse = rPlayer.GetGUIDOfCallUpHorse();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(guidHorse.IsNull())
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = rPlayer.GetHorseItem(guidHorse);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return 0;
	//}

	//return GetHorseRefix(iPara, pPetItem, iRate);
	//__UNGUARD__ 
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect070::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32		iRefixType = GetEffectDataDescriptorValueByIndex
		(
			rImp.GetDataIndex(),
			ImpactDataDescriptorIndex::IDX_REFIX_TYPE,
			rImp.GetSkillLevel()
		);
	Character	*pAttacker = GetEffectCharacterObj(rImp, rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAttacker == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamageType = GetDamageType(rImp);
	int32	iDamagePara = GetDamagePara(rImp);
	int32	iAttackWeight = GetAttackWeight(rImp);
	int32	iDefenceWeight = GetDefenceWeight(rImp);
	int32	vDamage[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDamage[DAMAGE_TYPE_NEAR] = pAttacker->GetAttackNear();
	vDamage[DAMAGE_TYPE_FAR] = pAttacker->GetAttackFar();
	vDamage[DAMAGE_TYPE_M] = pAttacker->Get_Property_AttackMagic();
	vDamage[DAMAGE_TYPE_COLD] = pAttacker->Get_Property_AttackCold();
	vDamage[DAMAGE_TYPE_FIRE] = pAttacker->Get_Property_AttackFire();
	vDamage[DAMAGE_TYPE_LIGHT] = pAttacker->Get_Property_AttackLight();
	vDamage[DAMAGE_TYPE_POISON] = pAttacker->Get_Property_AttackPoison();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vDefence[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vDefence[DAMAGE_TYPE_NEAR] = rMe.GetDefenceNear();
	vDefence[DAMAGE_TYPE_FAR] = rMe.GetDefenceFar();
	vDefence[DAMAGE_TYPE_M] = rMe.Get_Property_DefenceMagic();
	vDefence[DAMAGE_TYPE_COLD] = rMe.Get_Property_DefenceCold();
	vDefence[DAMAGE_TYPE_FIRE] = rMe.Get_Property_DefenceFire();
	vDefence[DAMAGE_TYPE_LIGHT] = rMe.Get_Property_DefenceLight();
	vDefence[DAMAGE_TYPE_POISON] = rMe.Get_Property_DefencePoison();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	vReduce[DAMAGE_TYPE_NUMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(vReduce, 0, sizeof(vReduce));
	vReduce[DAMAGE_TYPE_NEAR] = rMe.GetNearAttReduce();
	vReduce[DAMAGE_TYPE_FAR] = rMe.GetFarAttReduce();
	vReduce[DAMAGE_TYPE_M] = rMe.GetMagicAttReduce();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefix =
		(
			iDamagePara +
			Float2Int
			(
				(
					vDamage[iDamageType] *
					iAttackWeight *
					0.01f
				) -
						vDefence[iDamageType] *
						iDefenceWeight *
						0.01f
			)
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iRefix = Float2Int((iRefix * (100 - vReduce[iDamageType])) * 0.01f);
	SetDamagePoint(rImp, iDamageType, iRefix);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect071::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect071::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ __UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect071::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixType = GetEffectDataDescriptorValueByIndex
		(
			rImp.GetDataIndex(),
			ImpactDataDescriptorIndex::IDX_REFIX_TYPE,
			rImp.GetSkillLevel()
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iDamage = GetDamageRefix(rImp);
	Player	&rPlayer = static_cast<Player &>(rMe);
	int32	iRefixParaHorse = GetHorsePara(rImp);
	int32	iBase = rMe.Get_Property_Rage();
	int32	iRefix = GetRageByZhiYe(rImp, rPlayer.GetProfession());
	int32	iResult = GetRifixResult(iBase, iRefix, iRefixType);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != iRefix)
	{
		iResult += iDamage;

		iResult += iRefixParaHorse;
		rMe.RageIncrement(iResult, rImp.GetCasterLogicCount());
	}

	iBase = GetHPBase(rImp);
	iRefix = GetHP(rImp);
	iResult = GetRifixResult(iBase, iRefix, iRefixType);
	iResult += iDamage;

	iResult += iRefixParaHorse;

	BOOL PKRateFlag = GetEffectPKRateCtr(rImp) > 0 ? TRUE : FALSE;
	rMe.HealthIncrement(iResult, rImp.GetCasterLogicCount(), NULL, FALSE, TRUE, FALSE, PKRateFlag);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect071::GetRifixResult(int32 iBase, int32 iRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		iRefixResult = iRefix;
	}
	else
	{
		iRefixResult = Float2Int((iBase * iRefix) * 0.01f);
	}

	return iRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect071::GetRageByZhiYe(UNIT_EFFECT &rImp, int32 iZhiYe) const
{
	switch(iZhiYe)
	{
	case PROFESSION_WUSHI:
	case PROFESSION_SHIZIJUN:
		return GetRage0(rImp); 
		break;
	case PROFESSION_JIANXIA:
	case PROFESSION_SHENGHUOSHI:
		return GetRage1(rImp); 
		break;
	case PROFESSION_QISHE:	
	case PROFESSION_CIKE:
		return GetRage2(rImp); 
		break;
	case PROFESSION_HUOQIANG:	
	case PROFESSION_JINWEIJUN:
		return GetRage3(rImp); 
		break;
	case PROFESSION_XIANZHI:
	case PROFESSION_YINXIUSHI:
		return GetRage4(rImp); 
		break;
	case PROFESSION_SAMAN:
	case PROFESSION_LAMA:
		return GetRage5(rImp); 
	default:	break;
	}

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect071::GetRefixPara(UNIT_EFFECT &rImp, Character &rMe) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ int32 iPara = GetParaID(rImp);
	//int32		iRate = GetRefixRateHorse(rImp);
	//Player		&rPlayer = static_cast<Player &>(rMe);
	//SHorseGiud	guidHorse = rPlayer.GetGUIDOfCallUpHorse();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(guidHorse.IsNull())
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = rPlayer.GetHorseItem(guidHorse);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return 0;
	//}

	//return GetHorseRefix(iPara, pPetItem, iRate);
	//__UNGUARD__ 
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect071::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	InitDamageRefix(rImp, rMe);
	InitHorseRefix(rImp, rMe);
	InitHPBase(rImp, rMe);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect071::InitDamageRefix(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = static_cast<Player *>(&rMe);
	int32	iDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if( PROFESSION_WUSHI == pPlayer->GetProfession() || 
		PROFESSION_SHIZIJUN == pPlayer->GetProfession() ||
		PROFESSION_JIANXIA == pPlayer->GetProfession() ||
		PROFESSION_SHENGHUOSHI == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackNear();
	}
	else if(PROFESSION_QISHE == pPlayer->GetProfession() || 
		PROFESSION_CIKE == pPlayer->GetProfession() ||
		PROFESSION_HUOQIANG == pPlayer->GetProfession() ||
		PROFESSION_JINWEIJUN == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackFar();
	}
	else
	{
		iDamage = pPlayer->Get_Property_AttackMagic();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDamage = Float2Int(iDamage * iRefixRate * 0.01f);

	rImp.SetParamByIndex(OwnImpactParamIndex::IDX_IMPACT_DAMAGE_REFIX, iDamage);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect071::InitHorseRefix(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefix = GetRefixPara(rImp, rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rImp.SetParamByIndex(OwnImpactParamIndex::IDX_HORSE_REFIX, iRefix);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect071::GetHorsePara(UNIT_EFFECT &rImp) const
{
	__GUARD__ return rImp.GetParamByIndex(OwnImpactParamIndex::IDX_HORSE_REFIX);

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect071::GetDamageRefix(UNIT_EFFECT &rImp) const
{
	__GUARD__ rImp.GetParamByIndex(OwnImpactParamIndex::IDX_IMPACT_DAMAGE_REFIX);

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect071::InitHPBase(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ rImp.SetParamByIndex(OwnImpactParamIndex::IDX_HP_BASE, rMe.GetHP());

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect071::GetHPBase(UNIT_EFFECT &rImp) const
{
	__GUARD__ return rImp.GetParamByIndex(OwnImpactParamIndex::IDX_HP_BASE);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect072::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect072::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	sFinalPos;
	GLPos	sDir;
	GLPos	sPosTag;
	GLPos	oTargetPos;
	float		fDistance;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	if( IsChangePosWithEffectSender(rImp) )
	{
		
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pSenderObj = GetEffectCaster(rMe, rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pSenderObj || !IsObjCharacter(pSenderObj->GetObjType()))
		{
			return;
		}

		Character* pSenderChatacter = (Character*)pSenderObj;
		if( FALSE == pSenderChatacter->IsAlive() || FALSE == pSenderChatacter->IsActiveObj() )
		{
			return;
		}

		GLPos posMe = *(rMe.GetGLPos());
		GLPos posSender = *(pSenderChatacter->GetGLPos());
		TeleportToTarget(rMe, posSender);
		TeleportToTarget(*pSenderChatacter, posMe);
		return;

	}
	if(!GetTargetPos(rImp, rMe, oTargetPos, fDistance))
	{
		return;
	}

	GetFinalPos(rImp, rMe, sFinalPos, sDir, sPosTag, oTargetPos, fDistance);

	GetRealPos(rMe, sFinalPos, sPosTag, sDir);

	TeleportToTarget(rMe, sPosTag);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect072::GetFinalPos
(
	UNIT_EFFECT	&rImp,
	Character	&rMe,
	GLPos	&sFinalPos,
	GLPos	&sDir,
	GLPos	&sPosTag,
	GLPos	&oTargetPos,
	float		fDistance
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ const GLPos	*pMyPos = rMe.GetGLPos();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sDir.m_fX = oTargetPos.m_fX - pMyPos->m_fX;
	sDir.m_fZ = oTargetPos.m_fZ - pMyPos->m_fZ;
	sPosTag = *pMyPos;

	rMe.NormalizeWorldPos(sDir);

	sFinalPos.m_fX = sPosTag.m_fX + fDistance * sDir.m_fX;
	sFinalPos.m_fZ = sPosTag.m_fZ + fDistance * sDir.m_fZ;
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect072::GetRealPos(Character &rMe, GLPos &sFinalPos, GLPos &sPosTag, GLPos &sDir) const
{
	__GUARD__ if(sDir.m_fX == 0 && sDir.m_fZ == 0) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float		fLengthOfStep = 0.5f;
	float		fLengthTmp = 0;
	GLPos	sPosTmp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 u = 0; u < 100; ++u)
	{
		fLengthTmp = rMe.WordPosLength(sFinalPos.m_fX - sPosTag.m_fX, sFinalPos.m_fZ - sPosTag.m_fZ);
		if(fLengthTmp < fLengthOfStep)
		{
			if(rMe.GetMap()->GetMapInfo()->IsCanGo(sFinalPos)) sPosTag = sFinalPos;
			break;
		}

		sPosTmp.m_fX = sPosTag.m_fX + sDir.m_fX * fLengthOfStep;
		sPosTmp.m_fZ = sPosTag.m_fZ + sDir.m_fZ * fLengthOfStep;

		if(rMe.GetMap()->GetMapInfo()->IsCanGo(sPosTmp))
			sPosTag = sPosTmp;
		else
			break;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect072::GetTargetPos(UNIT_EFFECT &rImp, Character &rMe, GLPos &oTargetPos, float &fDistance) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	float fMaxDistance	= (float) GetDistance(rImp);
	fMaxDistance		= fMaxDistance * 0.01f;
	ID_t nTargetMode	= rMe.GetSpellInfo().GetTargetingLogic();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nTargetMode)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	oMyPos = *(rMe.GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TARGET_POS == nTargetMode)
	{
		oTargetPos = rParams.GetTargetPosition();
		fDistance = GetFinalDistance(rMe, oMyPos, oTargetPos, fMaxDistance);
	}
	else if(TARGET_SPECIFIC_UNIT == nTargetMode)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ObjID_t		iID = rParams.GetTargetObj();
		Character	*pTag = (Character *) rMe.GetMap()->GetSpecificObjByID(iID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL == pTag)
		{
			return FALSE;
		}

		oTargetPos = *(pTag->GetGLPos());

		fDistance = GetFinalDistance(rMe, oMyPos, oTargetPos, fMaxDistance);
	}
	else if(TARGET_SELF == nTargetMode)
	{
		fDistance = fMaxDistance;
		oTargetPos = *(rMe.GetGLPos());

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	fDir = rParams.GetTargetDirection();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		oTargetPos.m_fX += sinf(fDir) * fDistance;
		oTargetPos.m_fZ += cosf(fDir) * fDistance;
	}
	else
	{
		return FALSE;
	}

	if(fDistance < 0.005f)
	{
		TeleportToTarget(rMe, oMyPos);

		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float SpellEffect072::GetFinalDistance
(
	Character	&rMe,
	GLPos	&oMyPos,
	GLPos	&oTargetPos,
	float		fMaxDistance
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistance = rMe.WordPosLength(oMyPos.m_fX - oTargetPos.m_fX, oMyPos.m_fZ - oTargetPos.m_fZ);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fMaxDistance < fDistance)
	{
		fDistance = fMaxDistance;
	}

	return fDistance;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect072::TeleportToTarget(Character &rMe, const GLPos &sPosTag) const
{
	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		((Player *) (&rMe))->GetHumanAI()->PushCmd_Idle();
	}

	rMe.DirectTo((GLPos*)&sPosTag, FALSE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect073::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect073::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 != GetHPRecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_HP_REGENERATE);
	}

	if(0 != GetRege0RecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);
	}

	if(0 != GetRege1RecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);
	}

	if(0 != GetRege2RecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);
	}

	if(0 != GetRege3RecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);
	}

	if(0 != GetRege4RecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);
	}

	if(0 != GetRege5RecoverRefix(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect073::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	__GUARD__ switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_HP_REGENERATE:
		{
			if(0 != GetHPRecoverRefix(rImp))
			{
				rIntAttrRefix += GetHPRecoverRefix(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_RAGE_REGENERATE:
		{
			if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
			{
				return TRUE;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Player	&oHuman = static_cast<Player &>(rMe);
			int32	iProfession = oHuman.GetProfession();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			switch(iProfession)
			{
			case 0:		rIntAttrRefix += GetRege0RecoverRefix(rImp); break;
			case 1:		rIntAttrRefix += GetRege1RecoverRefix(rImp); break;
			case 2:		rIntAttrRefix += GetRege2RecoverRefix(rImp); break;
			case 3:		rIntAttrRefix += GetRege3RecoverRefix(rImp); break;
			case 4:		rIntAttrRefix += GetRege4RecoverRefix(rImp); break;
			case 5:		rIntAttrRefix += GetRege5RecoverRefix(rImp); break;
			default:	break;
			}

			return TRUE;
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect074::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetHpModification
			(
				rImp,
				GetEffectDataDescriptorValueByIndex
				(
					rImp.GetDataIndex(),
					ImpactDataDescriptorIndex::IDX_HP,
					rImp.GetSkillLevel()
				)
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SetMpModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_MP,
				rImp.GetSkillLevel()
			)
	);
	SetRageModification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE,
				rImp.GetSkillLevel()
			)
	);
	SetRage1Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE1,
				rImp.GetSkillLevel()
			)
	);
	SetRage2Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE2,
				rImp.GetSkillLevel()
			)
	);
	SetRage3Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE3,
				rImp.GetSkillLevel()
			)
	);
	SetRage4Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE4,
				rImp.GetSkillLevel()
			)
	);
	SetRage5Modification
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_RAGE5,
				rImp.GetSkillLevel()
			)
	);
	SetRefixRate
	(
		rImp,
		GetEffectDataDescriptorValueByIndex
			(
				rImp.GetDataIndex(),
				ImpactDataDescriptorIndex::IDX_REFIX_RATE,
				rImp.GetSkillLevel()
			)
	);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect074::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Character	*pImpactSender = (Character *) GetEffectCaster(rMe, rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pImpactSender == NULL)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixPara = GetRefixPara(rImp, rMe);
	int32	iRefixType = GetRefixType(rImp);
	int32	nHP = GetHpModification(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nHP += iRefixPara;

	rMe.HealthIncrement(nHP, rImp.GetCasterLogicCount(), pImpactSender);
	if(NULL == pImpactSender)
	{
		pImpactSender->OnEvent_HealTarget(rImp.GetSkillID(), rMe, nHP);
	}

	if(rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nMP = GetMpModification(rImp);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iRefixType == 1)
		{
			nHP += 100;
			nMP = Float2Int((nMP * rMe.Get_BaseProperty_MaxMP()) / 100.0f);
		}

		nMP += iRefixPara;
		rMe.ManaIncrement(nMP, rImp.GetCasterLogicCount(), pImpactSender);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iRageModify = static_cast<Player &>(rMe).GetProfession();
		int32	nRage = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch(iRageModify)
		{
		case PROFESSION_WUSHI:
		case PROFESSION_SHIZIJUN:		
			nRage = GetRageModification(rImp); 
		break;
		case PROFESSION_JIANXIA:
		case PROFESSION_SHENGHUOSHI:	
			nRage = GetRage1Modification(rImp); 
		break;
		case PROFESSION_QISHE:	
		case PROFESSION_CIKE:	
			nRage = GetRage2Modification(rImp); 
		break;
		case PROFESSION_HUOQIANG:	
		case PROFESSION_JINWEIJUN:		
			nRage = GetRage3Modification(rImp); 
		break;
		case PROFESSION_XIANZHI:
		case PROFESSION_YINXIUSHI:		
			nRage = GetRage4Modification(rImp); 
		break;
		case PROFESSION_SAMAN:
		case PROFESSION_LAMA:		
			nRage = GetRage5Modification(rImp); 
		break;
		default:	break;
		}

		if(INVALID_ID != nRage)
		{
			if(iRefixType == 1)
			{
				nRage += 100;
				nRage = Float2Int((nRage * rMe.GetBaseMaxRage()) / 100.0f);
			}

			nRage += iRefixPara;
			rMe.RageIncrement(nRage, rImp.GetCasterLogicCount(), pImpactSender);
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect074::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ nRate += 100;
	SetHpModification(rImp, Float2Int((GetHpModification(rImp) * nRate) / 100.0f));
	SetMpModification(rImp, Float2Int((GetMpModification(rImp) * nRate) / 100.0f));
	SetRageModification(rImp, Float2Int((GetRageModification(rImp) * nRate) / 100.0f));

	SetRage1Modification(rImp, Float2Int((GetRage1Modification(rImp) * nRate) / 100.0f));
	SetRage2Modification(rImp, Float2Int((GetRage2Modification(rImp) * nRate) / 100.0f));
	SetRage3Modification(rImp, Float2Int((GetRage3Modification(rImp) * nRate) / 100.0f));
	SetRage4Modification(rImp, Float2Int((GetRage4Modification(rImp) * nRate) / 100.0f));
	SetRage5Modification(rImp, Float2Int((GetRage5Modification(rImp) * nRate) / 100.0f));

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect074::GetDamageRefix(Character *pImpactSender, UNIT_EFFECT &rImp) const
{
	if(pImpactSender->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = static_cast<Player *>(pImpactSender);
	int32	iDamage = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if( PROFESSION_WUSHI == pPlayer->GetProfession() || 
		PROFESSION_SHIZIJUN == pPlayer->GetProfession() ||
		PROFESSION_JIANXIA == pPlayer->GetProfession() ||
		PROFESSION_SHENGHUOSHI == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackNear();
	}
	else if(PROFESSION_QISHE == pPlayer->GetProfession() || 
		PROFESSION_CIKE == pPlayer->GetProfession() ||
		PROFESSION_HUOQIANG == pPlayer->GetProfession() ||
		PROFESSION_JINWEIJUN == pPlayer->GetProfession() )
	{
		iDamage = pPlayer->GetAttackFar();
	}
	else
	{
		iDamage = pPlayer->Get_Property_AttackMagic();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixRate = GetRefixRate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDamage = Float2Int(iDamage * iRefixRate * 0.01f);

	return iDamage;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect074::GetRefixPara(UNIT_EFFECT &rImp, Character &rMe) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ int32 iPara = GetParaID(rImp);
	//int32		iRate = GetRefixRateHorse(rImp);
	//Character	*pChar = (Character *) GetEffectCaster(rMe, rImp);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pChar)
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player		*rPlayer = static_cast<Player *>(pChar);
	//SHorseGiud	guidHorse = rPlayer->GetGUIDOfCallUpHorse();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(guidHorse.IsNull())
	//{
	//	return 0;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = rPlayer->GetHorseItem(guidHorse);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return 0;
	//}

	//return GetHorseRefix(iPara, pPetItem, iRate);
	//__UNGUARD__ 
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect075::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect075::RefixSkill(UNIT_EFFECT &rImp, SpellInfo &rSkill) const
{
	__GUARD__ if(GetTargetSkillID(rImp) == rSkill.GetSpellID())
	{
		RefixAllSkillAttr(rSkill, rImp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect075::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect075::GetRifixResult(int32 iBase, int32 iRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		iRefixResult = iBase + iRefix;
	}
	else
	{
		iRefix += 100;
		iRefixResult = Float2Int((iBase * iRefix) / 100.0f);
	}

	return iRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
float SpellEffect075::GetRifixResult(float fBase, float fRefix, int32 iRefixType) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fRefixResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iRefixType <= 0)
	{
		fRefixResult = fBase + fRefix;
	}
	else
	{
		fRefix += 100;
		fRefixResult = ((fBase * fRefix) * 0.01f);
	}

	return fRefixResult;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect075::RefixAllSkillAttr(SpellInfo &rSkill, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRefixType = GetRefixType(rImp);
	int32		iRefixPara = 0;
	int32		iBase = 0;
	int32		iResult = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iBase = rSkill.GetCooldownTime();
	iRefixPara = GetCooldownTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetCooldownTime(iResult);

	iBase = rSkill.GetChargeTime();
	iRefixPara = GetChargeTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChargeTime(iResult);

	iBase = rSkill.GetChannelTime();
	iRefixPara = GetChannelTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChannelTime(iResult);

	iBase = rSkill.GetChargesOrInterval();
	iRefixPara = GetAttackTimesOrChannelTimeRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChargesOrInterval(iResult);

	iBase = rSkill.GetAccuracy();
	iRefixPara = GetAccuracyRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetAccuracy(iResult);

	iBase = rSkill.GetCriticalRate();
	iRefixPara = GetCriticalrateRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetCriticalRate(iResult);

	iBase = rSkill.Get_Property_MaxTargetNumber();
	iRefixPara = GetMaxTargetRefix(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetMaxTargetNumber(iResult);

	if(iRefixType > 0)
	{
		iBase = rSkill.GetDepleteRefixByRate();
		iRefixPara = GetDepleteRefix(rImp);
		iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
		rSkill.SetDepleteRefixByRate(iResult);
	}
	else
	{
		iBase = rSkill.GetDepleteRefixByValue();
		iRefixPara = GetDepleteRefix(rImp);
		iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
		rSkill.SetDepleteRefixByValue(iResult);
	}

	iBase = rSkill.GetChannelBackRate();
	iRefixPara = GetChannelBackRate(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChannelBackRate(iResult);

	iBase = rSkill.GetChannelBackHappanRate();
	iRefixPara = GetChannelBackHappanRate(rImp);
	iResult = GetRifixResult(iBase, iRefixPara, iRefixType);
	rSkill.SetChannelBackHappanRate(iResult);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect076::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect076::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	//__GUARD__ if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	//{
	//	return;
	//}

	//if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	//{
	//	return;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player	&oHuman = static_cast<Player &>(rMe);
	//int32	iMonsterID = GetMonsterID(rImp);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//oHuman.SetMonsterPetDataID(iMonsterID);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//int32	iMaxCanTake = GetMaxCanTake(rImp);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(MAX_MONSTER_PET_TAKE < iMaxCanTake)
	//{
	//	iMaxCanTake = MAX_MONSTER_PET_TAKE;
	//}

	//oHuman.SetMaxPetCanTake(iMaxCanTake);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//GameMap	*pMap = rMe.GetMap();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pMap)
	//{
	//	return;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//_MONSTER_PET_ATTR	oInit;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//InitAttr(&oInit, rImp);

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//GuardManager	*pGuardManager = pMap->GetGuardManager();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pGuardManager)
	//{
	//	return;
	//}

	//pGuardManager->SetInitData(oInit);

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect076::CriticalRefix(UNIT_EFFECT &rImp) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect076::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ __UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect076::InitAttr(_MONSTER_PET_ATTR *pInit, UNIT_EFFECT &rImp) const
{
	pInit->iLifeTime = GetLifeTime(rImp);
	pInit->iImpactToSelf = GetImpactSelf(rImp);
	pInit->iImpactToOnwer = GetImpactOnwer(rImp);

	for(int32 i = 0; i < MONSTER_PET_MAX_SKILL; ++i)
	{
		pInit->aSkillID[i] = GetSkillIDByIndex(rImp, i + ImpactDataDescriptorIndex::IDX_SKILL1_ID);
	}

	pInit->OnwerAttackRate = GetOnwerAttackRate(rImp);
	pInit->OnwerCriticalRate = GetOnwerCriticalRate(rImp);
	pInit->OnwerDefanceRate = GetOnwerDefanceRate(rImp);
	pInit->OnwerHitRate = GetOnwerHitRate(rImp);
	pInit->OnwerLifeRate = GetOnwerLifeRate(rImp);
	pInit->OnwerMissRate = GetOnwerMissRate(rImp);
	pInit->OnwerToughnessRate = GetOnwerToughnessRate(rImp);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect077::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect077::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(!IsCanUseThisSkill(rMe))
	{
		return;
	}

	if(INVALID_ID == GetSkillID(rImp))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player		*pPlayer = static_cast<Player *>(&rMe);
	Behavior_Player	*pAI = static_cast<Behavior_Player *>(pPlayer->GetAIObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pAI->PushCmd_UseSpell(GetSkillID(rImp), pPlayer->GetID(), 0.f, 0.f, 0.f, INVALID_GUID, 0, TRUE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect077::RefixPowerByRate(UNIT_EFFECT &rImp, int32 nRate) const
{
	__GUARD__ __UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect077::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	//__GUARD__ if(!IsCanUseThisSkill(rMe))
	//{
	//	return;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player	*pPlayer = static_cast<Player *>(&rMe);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//pPlayer->SetHorseChangeFade(GetChangeFadeModelID(rImp));
	//for(int32 i = 0; i < MAX_HORSE_DATA_INDEX; ++i)
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	int32	iDataIndex = pPlayer->GetHorseDataIndex(i);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if(iDataIndex != INVALID_ID)
	//	{
	//		continue;
	//	}

	//	pPlayer->SetHorseDataIndex(i, rImp.GetDataIndex());
	//	break;
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect077::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ Player	*pPlayer = static_cast<Player *>(&rMe);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(pPlayer->GetGUIDOfCallUpHorse().IsNull())
	//{
	//	return;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pItem = pPlayer->GetHorseItem(pPlayer->GetGUIDOfCallUpHorse());
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pItem)
	//{
	//	return;
	//}

	//pPlayer->SetHorseChangeFade(pItem->GetHorseModelID());
	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect077::IsCanUseThisSkill(Character &rMe) const
{
	//__GUARD__ if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	//{
	//	return FALSE;
	//}

	//if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	//{
	//	return FALSE;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player	*pPlayer = static_cast<Player *>(&rMe);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(pPlayer->GetGUIDOfCallUpHorse().IsNull())
	//{
	//	return FALSE;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pPetItem = pPlayer->GetHorseItem(pPlayer->GetGUIDOfCallUpHorse());
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pPetItem)
	//{
	//	return FALSE;
	//}

	//if(pPetItem->GetGeneration() < 2)
	//{
	//	return FALSE;
	//}

	//if(rMe.GetMountID() != pPetItem->GetHorseModelID())
	//{
	//	return FALSE;
	//}

	//return TRUE;
	//__UNGUARD__ 
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect078::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect078::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect078::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect078::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	//__GUARD__ if(0 != GetItemDurability(rImp))
	//{
	//	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_ITEM_DUR_ON_DIE);
	//}

	//if(0 != GetHorseHappiness(rImp))
	//{
	//	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_HORSE_HAPPINESS_ON_DIE);
	//}

	//if(0 != GetHorseHappinessPlus(rImp))
	//{
	//	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_HORSE_HAPPINESS_ON_DIE_PLUS);
	//}

	//if(0 != GetBaiTanExchangeTax(rImp))
	//{
	//	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_STALL_EXCHANGE_TAX);
	//}

	//if(0 != GetVigorIncRate(rImp))
	//{
	//	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_VIGOR_INC_RATE);
	//}

	//if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	//{
	//	return;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Player	*pPlayer = static_cast<Player *>(&rMe);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(0 != GetExpMult(rImp))
	//{
	//	pPlayer->MarkExpMultRefixDirtyFlag();
	//}

	//if(0 != Get_Property_MaxVigor(rImp))
	//{
	//	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_MAX_VIGOR);
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect078::Get_Property_IntAttrRefix
(
	UNIT_EFFECT			&rImp,
	Character			&rMe,
	CharIntAttrRefixs::Index_T	nIdx,
	int32				&rIntAttrRefix
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nValue = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_ITEM_DUR_ON_DIE:
		{
			if(0 != GetItemDurability(rImp))
			{
				rIntAttrRefix += GetItemDurability(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_HORSE_HAPPINESS_ON_DIE:
		{
			if(0 != GetHorseHappiness(rImp))
			{
				rIntAttrRefix += GetHorseHappiness(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_HORSE_HAPPINESS_ON_DIE_PLUS:
		{
			if(0 != GetHorseHappinessPlus(rImp))
			{
				rIntAttrRefix += GetHorseHappinessPlus(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_STALL_EXCHANGE_TAX:
		{
			if(0 != GetBaiTanExchangeTax(rImp))
			{
				rIntAttrRefix += GetBaiTanExchangeTax(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_VIGOR_INC_RATE:
		{
			if(INVALID_ID != GetVigorIncRate(rImp))
			{
				rIntAttrRefix += GetVigorIncRate(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_MULT_EXP:
		{
			if(0 != GetExpMult(rImp))
			{
				rIntAttrRefix += GetExpMult(rImp);
				return TRUE;
			}
		}
		break;

	case CharIntAttrRefixs::REFIX_PROPERTY_MAX_VIGOR:
		{
			if(0 != Get_Property_MaxVigor(rImp))
			{
				rIntAttrRefix += Get_Property_MaxVigor(rImp);
				return TRUE;
			}
		}
		break;

	default:
		break;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect079::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect079::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(!CommonCheck(rMe))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iScriptID = GetScriptID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iScriptID <= 0 )
	{
		return;
	}

	ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
		(
			rMe.GetMapID_i(),
			iScriptID,
			"OnIntervalOverEvent",
			rMe.GetMapID_i(),
			rMe.GetID()
		);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect079::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(!CommonCheck(rMe))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iScriptID = GetScriptID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iScriptID <= 0 )
	{
		return;
	}

	ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction(rMe.GetMapID_i(),iScriptID, "OnActiveEvent", rMe.GetMapID_i(), rMe.GetID());

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect079::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(!CommonCheck(rMe))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iScriptID = GetScriptID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iScriptID <= 0 )
	{
		return;
	}

	ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction(rMe.GetMapID_i(),iScriptID, "OnFadeOutEvent", rMe.GetMapID_i(), rMe.GetID());

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect079::CommonCheck(Character &rMe) const
{
	__GUARD__ if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return FALSE;
	}

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
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
int32 SpellEffect079::GetScriptID(UNIT_EFFECT const &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const EffectData	*pImpactData = GetEffectDataBlock(rImp.GetDataIndex());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pImpactData)
	{
		return INVALID_ID;
	}

	return pImpactData->GetEventScriptID();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect080::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect080::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fRadius = (float) GetDamageRadius(rImp);
	int32		iMaxTarget = GetMaxTarget(rImp);
	int32		iDamage = GetDamagePoint(rImp);
	OBJLIST		oObjList;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	oObjList.Clear();
	ScanUnitForTarget(rImp, rMe, *(rMe.GetGLPos()), fRadius, iMaxTarget, oObjList);

	for(int32 i = 0; i < oObjList.m_Count; ++i)
	{
		if(NULL == oObjList.m_aObj[i])
		{
			continue;
		}

		if(!oObjList.m_aObj[i]->IsActiveObj())
		{
			continue;
		}

		if(!IsObjCharacter(oObjList.m_aObj[i]->GetObjType()))
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	*pChar = static_cast<Character *>(oObjList.m_aObj[i]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		BOOL PKRateFlag = GetEffectPKRateCtr(rImp) > 0 ? TRUE : FALSE;
		pChar->HealthIncrement(-iDamage, rMe.GetLogicCount(), &rMe, FALSE, TRUE, FALSE, PKRateFlag);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect080::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect080::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect080::CommonCheck(Character &rMe) const
{
	__GUARD__ if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return FALSE;
	}

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
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
BOOL SpellEffect080::IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ return rMe.IsEnemy(&rTar);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect081::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(!CommonCheck(rMe))
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iScriptID = GetScriptID(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iScriptID <= 0 )
	{
		return;
	}

	ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction(rMe.GetMapID_i(),iScriptID, "OnActiveEvent", rMe.GetMapID_i(), rMe.GetID());

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect081::CommonCheck(Character &rMe) const
{
	__GUARD__ if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return FALSE;
	}

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
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
int32 SpellEffect081::GetScriptID(UNIT_EFFECT const &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const EffectData	*pImpactData = GetEffectDataBlock(rImp.GetDataIndex());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pImpactData)
	{
		return INVALID_ID;
	}

	return pImpactData->GetEventScriptID();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect082::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType()) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player					*pPlayer = (Player *) &rMe;
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	const SHorseGuid			&GUID = rParams.GetTargetPetGuid();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(GUID.IsNull()) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pPlayer->GetMap();
	

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Item	*pPetItem = pPlayer->GetHorseItem(GUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPetItem == NULL) return;
	if(pPetItem->IsLock()) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iIndex = pPlayer->GetHorseIndexByGUID(GUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iIndex == INVALID_ID) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_DB *pPetDB = pPlayer->GetHorseDB(iIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPetDB == NULL) return;
	if(pPetDB->m_iStatus == _HORSE_DB::PET_STATUS_MATING) return;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HorseManipulate	oHorseManipulate;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	oHorseManipulate.SetGUID(GUID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Horse_CreateHorseCommand	command;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	command.ExecutManipulate(&oHorseManipulate, pPlayer);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect083::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect083::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(!CommonCheck(rMe))
	{
		return;
	}

	WeddingLogic(rMe);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect083::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ rMe.MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_TERROR);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect083::Get_Property_BoolAttrRefix
(
	UNIT_EFFECT		&rImp,
	Character		&rMe,
	CharBoolAttrs::Index_T	nIdx,
	BOOL			&rBoolAttrRefix
) const
{
	__GUARD__ if(nIdx == CharBoolAttrs::PROPERTY_TERROR)
	{
		rBoolAttrRefix = TRUE;
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect083::OnEvent_Active(UNIT_EFFECT &rImp, Character &rMe) const
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect083::OnEvent_FadeOut(UNIT_EFFECT &rImp, Character &rMe) const
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect083::CommonCheck(Character &rMe) const
{
	__GUARD__ if(rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		return FALSE;
	}

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
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
void SpellEffect083::WeddingLogic(Character &rMe) const
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect084::GetRefixPetInitPara(int32 iType, UNIT_EFFECT &rImp, UNIT_EFFECT &rImpOut) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTypeRefix = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(iType)
	{
	case CPROPERTY_LEVEL2_MAXHP:
		iTypeRefix = IDX_ONWER_LIFE_RATE;
		break;

	case CPROPERTY_LEVEL2_ATTACK_NEAR:
	case CPROPERTY_LEVEL2_ATTACK_FAR:
	case CPROPERTY_LEVEL2_ATTACKRATE_M:
	case CPROPERTY_LEVEL2_ATTACKCOLD:
	case CPROPERTY_LEVEL2_ATTACKFIRE:
	case CPROPERTY_LEVEL2_ATTACKLIGHT:
	case CPROPERTY_LEVEL2_ATTACKPOISON:
		iTypeRefix = IDX_ONWER_ATTACK_RATE;
		break;

	case CPROPERTY_LEVEL2_DEFENCE_NEAR:
	case CPROPERTY_LEVEL2_DEFENCE_FAR:
	case CPROPERTY_LEVEL2_DEFENCE_M:
	case CPROPERTY_LEVEL2_DEFENCECOLD:
	case CPROPERTY_LEVEL2_DEFENCEFIRE:
	case CPROPERTY_LEVEL2_DEFENCELIGHT:
	case CPROPERTY_LEVEL2_DEFENCEPOISON:
		iTypeRefix = IDX_ONWER_DEFANCE_RATE;
		break;

	case CPROPERTY_LEVEL2_TOUGHNESS:
		iTypeRefix = IDX_ONWER_TOUGHNESS_RATE;
		break;

	case CPROPERTY_LEVEL2_CRITRATE:
		iTypeRefix = IDX_ONWER_CRITICAL_RATE;
		break;

	case CPROPERTY_LEVEL2_HIT:
		iTypeRefix = IDX_ONWER_HIT_RATE;
		break;

	case CPROPERTY_LEVEL2_MISS:
		iTypeRefix = IDX_ONWER_MISS_RATE;
		break;

	default:
		iTypeRefix = INVALID_ID;
	}

	if(INVALID_ID == iTypeRefix)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iRefixResult = rImpOut.GetParamByIndex(iTypeRefix);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iRefixResult += GetParaValue(iTypeRefix, rImp);
	rImpOut.SetParamByIndex(iTypeRefix, iRefixResult);

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect084::GetParaValue(int32 iType, UNIT_EFFECT &rImp) const
{
	__GUARD__ return GetEffectDataDescriptorValueByIndex(rImp.GetDataIndex(), iType, rImp.GetSkillLevel());

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellEffect060::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	__GUARD__ rImp.SetContinuance(-1);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellEffect060::OnEvent_UseSkillSuccessfully(UNIT_EFFECT &rImp, Character &rMe, SpellInfo &rSkill) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellID_t	iSkillID = rSkill.GetSpellID();
	SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(iSkillID);
	int32			iIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < SpellTemplateData::MAX_SUB_SKILL; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iSubSkillID = pSkillTemplate->GetSubSkill(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(INVALID_ID == iSubSkillID)
		{
			break;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iRateForSubSkill = pSkillTemplate->GetSubSkillSuccessRate(i);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!IsSubSkillCanSuccess(iRateForSubSkill, rMe))
		{
			continue;
		}

		rMe.SetSubSkillID(iIndex, iSubSkillID);
		++iIndex;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpellEffect060::IsSubSkillCanSuccess(int32 iRate, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRet = pMap->GetRand100();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nRet <= iRate)
	{
		return TRUE;
	}

	__UNGUARD__ return FALSE;
}


void SpellEffect085::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ if(0 <= GetIgnoreNearImmunity(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_IGNORE_NEAR_IMMUNITY);
	}

	if(0 <= GetIgnoreFarImmunity(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_IGNORE_FAR_IMMUNITY);
	}

	if(0 <= GetIgnoreMagicImmunity(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_IGNORE_MAGIC_IMMUNITY);
	}

	__UNGUARD__
}

BOOL SpellEffect085::Get_Property_IntAttrRefix
(
 UNIT_EFFECT			&rImp,
 Character			&rMe,
 CharIntAttrRefixs::Index_T	nIdx,
 int32				&rIntAttrRefix
 ) const
{
	__GUARD__
	switch(nIdx)
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_IGNORE_NEAR_IMMUNITY:
		{
			if(0 != GetIgnoreNearImmunity(rImp))
			{
				rIntAttrRefix += GetIgnoreNearImmunity(rImp);
				return TRUE;
			}
		}
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_IGNORE_FAR_IMMUNITY:		
		{
			if(0 != GetIgnoreFarImmunity(rImp))
			{
				rIntAttrRefix += GetIgnoreFarImmunity(rImp);
				return TRUE;
			}
		}
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_IGNORE_MAGIC_IMMUNITY:
		{
			if(0 != GetIgnoreMagicImmunity(rImp))
			{
				rIntAttrRefix += GetIgnoreMagicImmunity(rImp);
				return TRUE;
			}
		}
		break;
	}
	return TRUE;
	__UNGUARD__ return FALSE;
}

int32 SpellEffect086::GetTransformSourceAttrValue(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__
	int32 nRefixAttrType = GetTransformSourceAttrType(rImp);
	int32 nValue = 0;
	switch( nRefixAttrType )
	{
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_NEAR:
		nValue = rMe.GetAttackNear();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_NEAR:
		nValue = rMe.GetDefenceNear();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_FAR:
		nValue = rMe.GetAttackFar();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_FAR:
		nValue = rMe.GetDefenceFar();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_ATTACK_MAGIC:
		nValue = rMe.Get_Property_AttackMagic();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_DEFENCE_MAGIC:
		nValue = rMe.Get_Property_DefenceMagic();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_HIT:
		nValue = rMe.Get_Property_Hit();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_MISS:
		nValue = rMe.Get_Property_Miss();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_TOUGHNESS:
		nValue = rMe.GetToughness();
		break;
	case CharIntAttrRefixs::REFIX_PROPERTY_CRITICAL:
		nValue = rMe.Get_Property_Critical();
		break;
	}
	return nValue;
	__UNGUARD__ return 0;
}

void SpellEffect086::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__

	int32 nValue = GetTransformSourceAttrValue(rImp, rMe);

	SetRefixValue( rImp, Float2Int(nValue * GetTransformRate(rImp) * 0.01) );

	int32 nRefixAttrType = GetTransformSourceAttrType(rImp);
	if( -1 == nRefixAttrType ) return;
	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::Index_T(nRefixAttrType));

	nRefixAttrType = GetTransformDestAttrType(rImp);
	if( -1 == nRefixAttrType ) return;
	rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::Index_T(nRefixAttrType));

	__UNGUARD__
}

BOOL SpellEffect086::Get_Property_IntAttrRefix
(
 UNIT_EFFECT			&rImp,
 Character			&rMe,
 CharIntAttrRefixs::Index_T	nIdx,
 int32				&rIntAttrRefix
 ) const
{

	__GUARD__
	if(GetTransformSourceAttrType(rImp) == nIdx)
	{
		rIntAttrRefix -= GetRefixValue(rImp);
	}

	if(GetTransformDestAttrType(rImp) == nIdx)
	{
		rIntAttrRefix += GetRefixValue(rImp);
	}
	
	return TRUE;
	__UNGUARD__
	return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellEffect087::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pTar = NULL;
	OBJLIST			Targets;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if
		(
		FALSE == ScanUnitForTarget
		(
		rImp,
		rMe,
		*(rMe.GetGLPos()),
		(float) GetScanRadius(rImp),
		GetEffectedObjCount(rImp),
		Targets
		)
		)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	UNIT_EFFECT	impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nDamage = GetDamageValue(rImp, rMe);

	rMe.HealthIncrement(nDamage);
	for(int32 nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		pTar = (Character *) Targets.m_aObj[nIdx];
		if(NULL != pTar)
		{
			g_EffectInterface.InitEffectFromData(GetSubImpactDataIndex(rImp), impact, rMe);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = rMe.GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pMap)
			{
				pMap->GetEventCore().RegisterBeSkillEvent
					(
					pTar->GetID(),
					rMe.GetID(),
					BEHAVIOR_TYPE_HOSTILITY,
					500
					);
				pMap->GetEventCore().RegisterImpactEvent(pTar->GetID(), rMe.GetID(), impact, 500);
			}
		}
	}

	return;
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellEffect087::IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER != rTar.GetObjType() || rMe.GetID() == rTar.GetID() || FALSE == rTar.IsAliveInDeed() || FALSE == rTar.IsActiveObj())
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
int32 SpellEffect087::GetDamageValue(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixType = GetRefixType(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	int nDamageValue = 0;

	if(nRefixType == 0)
	{
		nDamageValue = GetRefixHP(rImp);
	}
	else
	{
		nDamageValue = (rMe.GetMaxHP() * GetRefixHP(rImp)) / 100;
	}

	return nDamageValue;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellEffect088::InitFromData(UNIT_EFFECT &rImp, EffectData const &rData) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	SetActivateTimes(rImp, GetActivateTimesFromTable(rImp));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellEffect088::OnEvent_IntervalOver(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Character	*pTar = NULL;
	OBJLIST			Targets;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if
		(
		FALSE == ScanUnitForTarget
		(
		rImp,
		rMe,
		*(rMe.GetGLPos()),
		(float) GetScanRadius(rImp),
		GetEffectedObjCount(rImp),
		Targets
		)
		)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	UNIT_EFFECT	impact;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nDamage = GetDamageValue(rImp, rMe);
	
	if (0 != nDamage)
	{
		rMe.HealthIncrement(nDamage);
	}

	for(int32 nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		pTar = (Character *) Targets.m_aObj[nIdx];
		if(NULL != pTar)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GameMap	*pMap = rMe.GetMap();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pMap)
			{
				if (pMap->GetRand100() <= GetRate(rImp))
				{
					g_EffectInterface.InitEffectFromData(GetSubImpactDataIndex(rImp), impact, rMe);

					pMap->GetEventCore().RegisterBeSkillEvent
						(
						pTar->GetID(),
						rMe.GetID(),
						BEHAVIOR_TYPE_HOSTILITY,
						500
						);
					pMap->GetEventCore().RegisterImpactEvent(pTar->GetID(), rMe.GetID(), impact, 500);

					int32	nActivateTimes = GetActivateTimes(rImp);
					if(0 < nActivateTimes)
					{
						--nActivateTimes;
						if(0 == nActivateTimes)
						{
							rMe.Effect_OnEffectFadeOut(rImp);
							break;
						}

						SetActivateTimes(rImp, nActivateTimes);
					}
				}
			}
		}
	}
	return;
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL SpellEffect088::IsScanedTargetValid(UNIT_EFFECT &rImp, Character &rMe, Character &rTar) const
{
	/*__GUARD__ if( !IsObjCharacter(rTar.GetObjType()) || rMe.GetID() == rTar.GetID() || FALSE == rTar.IsAliveInDeed() || FALSE == rTar.IsActiveObj())
	{
		return FALSE;
	}

	BOOL bRet = FALSE;

	if (GetCanRepeatFlag(rImp) <= 0)
	{
		bRet = rTar.Effect_HaveEffectOfSpecificEffectID(GetSubImpactDataIndex(rImp));

		if(bRet)
		{
			return FALSE;
		}
	}

	int32 nRelation = GetCampRelation(rImp);

	if (nRelation < 0)
	{
		return TRUE;
	}

	if (nRelation >= CAMP_RELATION_NUM)
	{
		QLogSystem::SLOW_LOG
			(
			SLOW_LOG_SERVER,
			"Effect param is wrong: camp relation."
			);
		return FALSE;
	}


	switch (nRelation)
	{
		case CAMP_RELATION_FRIEND:
			bRet = rMe.IsFriend(&rTar);
			break;
		case CAMP_RELATION_PARTNER:
			bRet = rMe.IsPartner(&rTar);
			break;
		case CAMP_RELATION_ENEMY:
			bRet = rMe.IsEnemy(&rTar);
			break;
		case CAMP_RELATION_PET:
			bRet =  (Object::OBJECT_CLASS_PET == rTar.GetObjType());
			break;
		default:
			bRet = FALSE;
			break;
	}

	return bRet;

	__UNGUARD__*/ 
	return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 SpellEffect088::GetDamageValue(UNIT_EFFECT &rImp, Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixType = GetRefixType(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	int nDamageValue = 0;

	if(nRefixType == 0)
	{
		nDamageValue = GetRefixHP(rImp);
	}
	else
	{
		nDamageValue = (rMe.GetMaxHP() * GetRefixHP(rImp)) / 100;
	}

	return nDamageValue;
	__UNGUARD__ return 0;
}


void SpellEffect089::MarkModifiedAttrDirty(UNIT_EFFECT &rImp, Character &rMe) const
{
	__GUARD__ 
	if(0 < GetZoomScale(rImp))
	{
		rMe.MarkIntAttrRefixDirtyFlag_EX(CharIntAttrRefixs::REFIX_PROPERTY_ZOOM_SCALE);
	}
	__UNGUARD__
}

BOOL SpellEffect089::Get_Property_IntAttrRefix
(
 UNIT_EFFECT			&rImp,
 Character			&rMe,
 CharIntAttrRefixs::Index_T	nIdx,
 int32				&rIntAttrRefix
 ) const
{
	__GUARD__
	switch(nIdx)
	{
		case CharIntAttrRefixs::REFIX_PROPERTY_ZOOM_SCALE:
			{
				if(0 < GetZoomScale(rImp))
				{
					rIntAttrRefix += GetZoomScale(rImp);
					return TRUE;
				}
			}
			break;
	}
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void SpellEffect090::RefixInherenceBalance(UNIT_EFFECT &rImp, InherenceBalanceRefixValue &rInherenceBalance) const
{

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceCritrateRefix = GetRefixBalanceCritrate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceCritrateRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_CRITRATE] += nBalanceCritrateRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceToughnessRefix = GetRefixBalanceToughness(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceToughnessRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_TOUGHNESS] += nBalanceToughnessRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceHitRefix = GetRefixBalanceHit(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceHitRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_HIT] += nBalanceHitRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceMissRefix = GetRefixBalanceMiss(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceMissRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_MISS] += nBalanceMissRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceCritDamageRefix = GetRefixBalanceCritDamage(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceCritDamageRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_CRITDAMAGE] += nBalanceCritDamageRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceCritDamageDerateRefix = GetRefixBalanceCritDamageDerate(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceCritDamageDerateRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_CRITDAMAGEDERATE] += nBalanceCritDamageDerateRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceCtrHitRefix = GetRefixBalanceCtrHit(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceCtrHitRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_CTRLHIT] += nBalanceCtrHitRefix;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nBalanceCtrMissRefix = GetBalanceCtrMiss(rImp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 != nBalanceCtrMissRefix)
	{
		rInherenceBalance.values[CPROPERTY_LEVEL4_BALANCE_CTRLMISS] += nBalanceCtrMissRefix;
	}

}