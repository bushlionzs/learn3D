/*$T MapServer/Server/Obj/Visitor/InitMonsterVisitor.cpp GC 1.140 10/10/07 10:07:35 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "InitMonsterVisitor.h"
#include "Character.h"
#include "Monster.h"
#include "TabDefine.h"
#include "map/game_map.h"
#include "Behavior_Monster.h"
#include "data/data_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

InitMonsterVisitor::InitMonsterVisitor()
{
	m_pChar = NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
InitMonsterVisitor::~InitMonsterVisitor()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CharacterVisitor::VisitorType InitMonsterVisitor::GetType()
{
	return CharacterVisitor_MonsterAttr;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::VisitInitMonster(Character *pChar)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__		m_pChar = (Monster *) pChar;
	MonsterProperty*pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAttr == NULL) return;

	m_pAttr = pAttr;

	InitMinDamagePercent();
	InitBaseExp();
	InitAttackNear();
	InitAttackFar();
	InitAttackMagic();
	InitDefenceNear();
	InitDefenceFar();
	InitDefenceMagic();
	InitMaxHP();
	InitMaxMP();
	InitRestoreHP();
	InitRestoreMP();
	InitHitRate();
	InitCritRate();
	InitMissRete();
	InitAttrAttack1();
	InitAttrAttack2();
	InitAttrAttack3();
	InitAttrAttack4();
	InitAttrDefence1();
	InitAttrDefence2();
	InitAttrDefence3();
	InitAttrDefence4();
	InitWeaponID();
	InitHorseID();
	InitUnbreakble();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitMinDamagePercent()
{
	__GUARD__ if(m_pAttr->m_MinDamagePercent == -1)
	{
	}
	else
	{
		m_pChar->SetMinDamagePercent(m_pAttr->m_MinDamagePercent);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitBaseExp()
{
	__GUARD__ if(m_pAttr->m_BaseExp == -1)
	{
	}
	else
	{
		m_pChar->SetBaseExp(m_pAttr->m_BaseExp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttackNear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACK_NEAR);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->SetBaseAttackNear(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttackFar()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACK_FAR);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->SetBaseAttackFar(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttackMagic()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACKRATE_M);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_AttackMagic(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitDefenceNear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCE_NEAR);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->SetBaseDefenceNear(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitDefenceFar()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCE_FAR);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->SetBaseDefenceFar(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitDefenceMagic()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCE_M);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_DefenceMagic(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitMaxHP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_MAXHP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_MaxHP(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitMaxMP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_MAXMP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_MaxMp(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitRestoreHP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_RESTOREHP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_HPRegenerate(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitRestoreMP()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_RESTOREMP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_MPRegenerate(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitHitRate()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_HIT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_Hit(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitMissRete()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_MISS);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_Miss(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitCritRate()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_CRITRATE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_Critical(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrAttack1()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACKCOLD);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_AttackCold(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrAttack2()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACKFIRE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_AttackFire(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrAttack3()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACKLIGHT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_AttackLight(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrAttack4()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_ATTACKPOISON);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_AttackPoison(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrDefence1()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCECOLD);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_DefenceCold(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrDefence2()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCEFIRE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_DefenceFire(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrDefence3()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCELIGHT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_DefenceLight(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitAttrDefence4()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iTmp = DataManager::GetSingletonPtr()->getMonsterProperty(m_pChar->GetDataID(), CPROPERTY_LEVEL2_DEFENCEPOISON);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(iTmp == -1)
	{
	}
	else
	{
		m_pChar->Set_BaseProperty_DefencePoison(iTmp);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitWeaponID()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iWeaponCount = m_pAttr->m_iWeaponCount;
	int32		iRand = MakeRand(iWeaponCount - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iRand = m_pAttr->m_WeaponID[iRand];
	if(iRand < 0) iRand = 0;
	if(iRand >= SMonsterWeaponAndSkillTable::MWAST_MAX_NUM) iRand = SMonsterWeaponAndSkillTable::MWAST_MAX_NUM - 1;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iWeaponID = DataManager::GetSingletonPtr()->getMonsterWeaponAndSkillTable()->m_aWeaponSkill[iRand].m_iWeaponID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pChar->SetWeaponID(iWeaponID);

	KCheck
	(
		g_MonsterWeaponAndSkill.m_aWeaponSkill[iRand].m_iSkillLevelIndexCount <= MonsterWeaponAndSkill::
				MWAS_MAX_LEVEL
			&&	"mon_wqskl.tab 技能lv 列数值超出上限"
	);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iSkillRand = MakeRand(DataManager::GetSingletonPtr()->getMonsterWeaponAndSkillTable()->m_aWeaponSkill[iRand].m_iSkillLevelIndexCount - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iSkillRand >= 0 && iSkillRand < MonsterWeaponAndSkill::MWAS_MAX_LEVEL);
	iSkillRand = DataManager::GetSingletonPtr()->getMonsterWeaponAndSkillTable()->m_aWeaponSkill[iRand].m_aSkillLevelIndex[iSkillRand];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Monster	*pMonsterAI = m_pChar->GetMonsterAI();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(m_pChar->GetAIScript() != INVALID_ID) return;
	if(m_pAttr->m_ExtAI != INVALID_ID)
	{
		pMonsterAI->SetBehavior_TemplateID(m_pAttr->m_ExtAI);
		m_pChar->SetAIScript(m_pAttr->m_ExtAI);
		return;
	}

	if(pMonsterAI != NULL)
	{
		pMonsterAI->SetBehavior_TemplateID(DataManager::GetSingletonPtr()->getMonsterWeaponAndSkillTable()->m_aWeaponSkill[iRand].m_aSkillLevel[iSkillRand]);
		m_pChar->SetAIScript(DataManager::GetSingletonPtr()->getMonsterWeaponAndSkillTable()->m_aWeaponSkill[iRand].m_aSkillLevel[iSkillRand]);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitHorseID()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iHorseCount = m_pAttr->m_iHorseCount;
	int32		iRand = MakeRand(iHorseCount - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_pChar->SetHorseID(m_pAttr->m_HorseID[iRand]);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 InitMonsterVisitor::MakeRand(int32 iMax)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = m_pChar->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fRand = (float) (pMap->GetRand100()) / 100.0f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fRand *= iMax;

	return(int32) (fRand + 0.5f);
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void InitMonsterVisitor::InitUnbreakble()
{
	__GUARD__
	{
		m_pChar->ClearBoolAttrFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);
	}

	m_pChar->MarkBoolAttrDirtyFlag_EX(CharBoolAttrs::PROPERTY_UNBREAKABLE);

	__UNGUARD__
}
