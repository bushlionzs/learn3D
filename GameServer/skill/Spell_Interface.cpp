/*$T MapServer/Server/Spell/SpellSystem.cpp GC 1.140 10/10/07 10:07:58 */

// $Id: Spell_Interface.cpp,v 1.1.2.15 2010/06/02 08:10:07 wuwenbin Exp $

/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "Spell_Interface.h"
#include "map/game_map.h"
#include "Spell_EffectLogicManager.h"
#include "BaseTool.h"
#include "TabDefine.h"
#include "gameobject/CharActionDelegator.h"
#include "gameobject/Player.h"
#include "data/data_manager.h"
#include "map/map_info.h"

using namespace Messages;

SpellInterface	g_SpellCore;

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL IsSpellInCollection(SpellInfo const &rSkillInfo, int32 nCollection)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		nID = INVALID_ID;
	IDCollection const	*pCollection = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pCollection = DataManager::GetSingletonPtr()->getCollection(nCollection);
	if(NULL != pCollection)
	{
		switch(pCollection->GetType())
		{
		case IDCollection::TYPE_SPELL_ID:
			nID = rSkillInfo.GetSpellID();
			break;

		case IDCollection::TYPE_BUFF_ID:
		case IDCollection::TYPE_EFFECT_LOGIC_ID:
		case IDCollection::TYPE_EFFECT_MUTEX_ID:
		case IDCollection::TYPE_DIRECT_EFFECT_ID:
		case IDCollection::TYPE_SPELL_LOGIC_ID:
		default:
			nID = INVALID_ID;
			break;
		}

		if(INVALID_ID != nID)
		{
			if(0 < pCollection->GetCollectionSize())
			{
				return pCollection->IsThisIDInCollection(nID);
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
int32 GetSpellInfoDescriptorValueByIndex(SpellInfo const &rSkillInfo, int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Descriptor const	*pDescriptor = rSkillInfo.GetDescriptorByIndex(nIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pDescriptor)
	{
		return pDescriptor->GetValueBySkillLevel(rSkillInfo.GetCharacterSpellLevel());
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
ConditionAndDepleteTerm const *Get_Property_ConDepTermByIndex(SpellInfo const &rSkillInfo, int32 nIndex)
{
	__GUARD__ return rSkillInfo.Get_Property_ConDepTermByIndex(nIndex);
	__UNGUARD__ return NULL;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 GetSpellHurtDelayTime(int32 iSkillID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		HurtDelayTime = 500;
	const SpellTemplateData *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(iSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pSkillTemplate)
	{
		HurtDelayTime = pSkillTemplate->GetHurtDelayTime();
	}

	return HurtDelayTime;
	__UNGUARD__ return 500;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 GetSpellStandFlag(SpellID_t nSkill)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32		nBehaviorType = BEHAVIOR_TYPE_NEUTRALITY;
	SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pSkillTemplate)
	{
		if(0 < pSkillTemplate->GetStandFlag())
		{
			nBehaviorType = BEHAVIOR_TYPE_AMITY;
		}
		else if(0 > pSkillTemplate->GetStandFlag())
		{
			nBehaviorType = BEHAVIOR_TYPE_HOSTILITY;
		}
		else
		{
			nBehaviorType = BEHAVIOR_TYPE_NEUTRALITY;
		}
	}

	return nBehaviorType;
	__UNGUARD__ return BEHAVIOR_TYPE_NEUTRALITY;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */

BOOL SpellInterface::ProcessSpellRequest
(
	Character	&rMe,
	SpellID_t	nSkillID,
	ObjID_t		nTargetID,
	GLPos const &rTargetPos,
	float		fTargetDir,
	GUID_t		guidTarget,
	int32		iHurtDelayTime,
	BOOL		bSubSkill
) const
{
	__GUARD__ if(INVALID_ID == nSkillID)
	{
		return TRUE;
	}

	return ProcessSpellRequestImp
	(
		rMe,
		nSkillID,
		nTargetID,
		rTargetPos,
		fTargetDir,
		guidTarget,
		iHurtDelayTime,
		bSubSkill
	);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GetSkillLevelByEquip(int32 iSkillID, Player *pMe)
{
	 return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL IsCanGo(Character &rMe, GLPos sFinalPos, GLPos sPosCur, GLPos sDir)
{
	__GUARD__ rMe.NormalizeWorldPos(sDir);

	if(sDir.m_fX == 0.0f && sDir.m_fZ == 0.0f) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float		fLengthOfStep = 0.5f;
	float		fLengthTmp = 0;
	GLPos	sPosTmp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 u = 0; u < 100; ++u)
	{
		fLengthTmp = rMe.WordPosLength(sFinalPos.m_fX - sPosCur.m_fX, sFinalPos.m_fZ - sPosCur.m_fZ);
		if(fLengthTmp < fLengthOfStep)
		{
			if(rMe.GetMap()->GetMapInfo()->IsCanGo(sFinalPos)) sPosCur = sFinalPos;
			return TRUE;
		}

		sPosTmp.m_fX = sPosCur.m_fX + sDir.m_fX * fLengthOfStep;
		sPosTmp.m_fZ = sPosCur.m_fZ + sDir.m_fZ * fLengthOfStep;

		if(rMe.GetMap()->GetMapInfo()->IsCanGo(sPosTmp))
		{
			sPosCur = sPosTmp;
		}
		else
		{
			return FALSE;
		}
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellInterface::ProcessSpellRequestImp
(
	Character	&rMe,
	SpellID_t	nSkillID,
	ObjID_t		nTargetID,
	GLPos const &rTargetPos,
	float		fTargetDir,
	GUID_t		guidTarget,
	int32		iHurtDelayTime,
	BOOL		bSubSkill
) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ BOOL				bRet = TRUE;
	SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	SpellTemplateData const			*pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillTemplate)
	{
		rParams.SetErrCode(OR_INVALID_SKILL);
		return FALSE;
	}

	if(INVALID_ID == nSkillID)
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	if(FALSE == rMe.IsAlive())
	{
		rParams.SetErrCode(OR_DIE);
		return FALSE;
	}

	if(FALSE == rMe.CanUseThisSpellInThisStatus(nSkillID))
	{
		rParams.SetErrCode(OR_LIMIT_USE_SKILL);
		return FALSE;
	}

	if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType() && A_SKILL_FOR_PLAYER == pSkillTemplate->GetClassByUser())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		PlayerArchive	*pDB = ((Player *) &rMe)->GetDB();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(FALSE == rMe.HaveSpell(nSkillID) && FALSE == rParams.GetIgnoreConditionCheckFlag())
		{
			if(!CheckCanUseSpellByHorse(rMe, nSkillID))
			{
				if(!CheckCanUseSpellByBus(rMe, nSkillID))
				{
					return FALSE;
				}
			}
		}
		else
		{
			
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iLevel = GetSkillLevelByEquip(nSkillID, ((Player *) &rMe));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rSkillInfo.SetCharacterSpellLevel(iLevel);
		}
	}

	if(FALSE == rMe.IsSpellCooldowned(nSkillID) && !bSubSkill)
	{
		rParams.SetErrCode(OR_COOL_DOWNING);
		return FALSE;
	}

	if(!GetGlobalActionDelegator().CanDoNextAction(rMe) && !bSubSkill)
	{
		rParams.SetErrCode(OR_BUSY);
		return FALSE;
	}

	rParams.SetActivatedSpell(nSkillID);

	rParams.SetTargetObj(nTargetID);

	rParams.SetTargetPosition(rTargetPos);

	rParams.SetTargetDirection(fTargetDir);

	rParams.SetTargetGuid(guidTarget);

	/*~~~~~~~~~~~~~~~~~*/
	SHorseGuid	GUID;
	/*~~~~~~~~~~~~~~~~~*/

	GUID.m_uHighSection = nTargetID;
	GUID.m_uLowSection = guidTarget;
	rParams.SetTargetPetGuid(GUID);

	bRet = ActiveSpellNow(rMe, bSubSkill);

	if(FALSE == bRet && FALSE == bSubSkill)
	{
		g_SpellCore.OnException(rMe);
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellInterface::InstanceSpell(SpellInfo &rSkillInfoOut, Character &rMe, SpellID_t nSkill) const
{
	__GUARD__ if(INVALID_ID == nSkill)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	SpellTemplateData const			*pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(nSkill);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillTemplate)
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"[SpellSystem::InstanceSpell]: Can't find skill date in the SkillTemplateDateMgr TemplateID=%d",
				nSkill
			);

		KCheckEx(FALSE, "[CombatCore_T::InstanceSpell]: Can't find skill date in the SkillTemplateDateMgr!");

		return FALSE;
	}

	rSkillInfoOut = *pSkillTemplate;

	if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType() && A_SKILL_FOR_PLAYER == pSkillTemplate->GetClassByUser())
	{
		if(pSkillTemplate->GetProfession() != INVALID_ID)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iSkillLevel = GetSkillLevelByEquip(nSkill, ((Player *) &rMe));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			rSkillInfoOut.SetCharacterSpellLevel(iSkillLevel);
		}
		else
		{
			rSkillInfoOut.SetCharacterSpellLevel(0);
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellID_t		nSkillInstance = nSkill;
	SpellInstanceData const *pSkillInstance = DataManager::GetSingletonPtr()->getSpellInstance(nSkillInstance);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillInstance)
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"[SpellSystem::InstanceSpell]: Warning Skill Data don't match SkillTemplate Data TemplateID=%d, CharacterSkillLevel=d%, SkillDataID=d%.",
				nSkill,
				rSkillInfoOut.GetCharacterSpellLevel(),
				nSkillInstance
			);
		KCheckEx(FALSE, "[SpellSystem::InstanceSpell]: Can't find skill instance!");
		return FALSE;
	}

	rSkillInfoOut = *pSkillInstance;
	rSkillInfoOut.SetSpellID(nSkill);

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellInterface::ActiveSpellNow(Character &rMe, BOOL bSubSkill) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSkillInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == rMe.IsAlive() || FALSE == rMe.IsActiveObj())
	{
		rParams.SetErrCode(OR_DIE);
		return FALSE;
	}

	rSkillInfo.Init();

	if(FALSE == InstanceSpell(rSkillInfo, rMe, rParams.GetActivatedSpell()))
	{
		rParams.SetErrCode(OR_INVALID_SKILL);
		rParams.SetErrParam(rParams.GetActivatedSpell());
		return FALSE;
	}

	rMe.RefixSkill(rSkillInfo);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			nLogicID = rSkillInfo.GetLogicID();
	BaseSpellLogic const	*pLogic = g_SpellLogicList.GetLogicById(nLogicID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pLogic)
	{
		rParams.SetErrCode(OR_INVALID_SKILL);
		rParams.SetErrParam(rParams.GetActivatedSpell());
		return FALSE;
	}

	if(TRUE == pLogic->IsPassive())
	{
		KCheckEx(FALSE, "[SpellSystem::HeartBeat]: Found passive Skill!!!Data error!!");
		rParams.SetErrCode(OR_IS_PASSIVE_SKILL);
		return FALSE;
	}

	if(TRUE == pLogic->CancelSpellEffect(rMe))
	{
		rParams.SetErrCode(OR_OK);
		return TRUE;
	}

	if
	(
		FALSE == rMe.IsSpellCooldowned(rParams.GetActivatedSpell())
	&&	FALSE == rParams.GetIgnoreConditionCheckFlag()
	&&	!bSubSkill
	)
	{
		rParams.SetErrCode(OR_COOL_DOWNING);
		return FALSE;
	}

	if(!IsCanPassCheckByWeapon(rSkillInfo, rMe, rParams))
	{
		return FALSE;
	}

	if(FALSE == rParams.GetIgnoreConditionCheckFlag())
	{
		if(FALSE == pLogic->IsConditionSatisfied(rMe))
		{
			return FALSE;
		}

		if(FALSE == pLogic->SpecificOperationOnSpellStart(rMe))
		{
			return FALSE;
		}
	}

	ID_t type = rSkillInfo.GetSpellType();
	switch(type)
	{
	case SKILL_INSTANT_LAUNCHING:	pLogic->StartLaunching(rMe); break;
	case SKILL_NEED_CHARGING:	pLogic->StartCharging(rMe); break;
	case SKILL_NEED_CHANNELING:	pLogic->StartChanneling(rMe); break;
	default:			KCheckEx(FALSE, "[SpellSystem::ActiveSpellNow]: Try to active a un-active skill!"); break;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SpellInterface::OnException(Character &rMe) const
{
	__GUARD__ if(Object::OBJECT_CLASS_PLAYER != rMe.GetObjType())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo		&rSkillInfo = rMe.GetSpellInfo();
	SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(rSkillInfo.GetSpellID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSkillTemplate)
	{
		return;
	}

	if(INVALID_ID == pSkillTemplate->GetProfession())
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ORT_FAILED(rParams.GetErrCode()))
	{
		//zhousha todo
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellInterface::IsCanPassCheckByWeapon
(
	SpellInfo				&rSkillInfo,
	Character				&rMe,
	SpellTargetingAndDepletingParams	&rParams
) const
{
	//if(TRUE == rSkillInfo.GetMustUseWeaponFlag())
	//{
	//	if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
	//	{
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		Player	*pPlayer = (Player *) &rMe;
	//		Item	*pMainhand = sItemInterface.GetEquip(pPlayer, HEQUIP_MAINHAND);
	//		Item	*pAssihand = sItemInterface.GetEquip(pPlayer, HEQUIP_ASSIHAND);
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(NULL == pMainhand || NULL == pAssihand)
	//		{
	//			rParams.SetErrCode(OR_NEED_A_WEAPON);
	//			return FALSE;
	//		}
	//		else if(TRUE == pMainhand->IsFree() && TRUE == pAssihand->IsFree())
	//		{
	//			rParams.SetErrCode(OR_NEED_A_WEAPON);
	//			return FALSE;
	//		}
	//	}
	//}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellInterface::CheckCanUseSpellByHorse(Character &rMe, SpellID_t nSkillID) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	//SpellInfo				&rSkillInfo = rMe.GetSpellInfo();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(((Player *) &rMe)->GetGUIDOfCallUpHorse().IsNull())
	//{
	//	rParams.SetErrCode(OR_INVALID_SKILL);
	//	return FALSE;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//Item	*pItem = ((Player *) &rMe)->GetHorseItem(((Player *) &rMe)->GetGUIDOfCallUpHorse());
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(NULL == pItem)
	//{
	//	rParams.SetErrCode(OR_INVALID_SKILL);
	//	return FALSE;
	//}

	///*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//BOOL	bCanUseSkill = FALSE;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	//{
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	SHorseSkill	petSkill = pItem->GetSkill(i);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if(petSkill.m_bCanUse && petSkill.m_nSkillID == nSkillID)
	//	{
	//		rSkillInfo.SetCharacterSpellLevel(0);
	//		bCanUseSkill = TRUE;
	//		break;
	//	}
	//}

	//if(!bCanUseSkill)
	//{
	//	rParams.SetErrCode(OR_INVALID_SKILL);
	//	return FALSE;
	//}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SpellInterface::CheckCanUseSpellByBus(Character &rMe, SpellID_t nSkillID) const
{
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//__GUARD__ SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	//SpellInfo					&rSkillInfo = rMe.GetSpellInfo();
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(((Player *) &rMe)->Skill_HaveBusSkill(nSkillID) == TRUE)
	//{
	//	rSkillInfo.SetCharacterSpellLevel(0);
	//	return TRUE;
	//}

	//rParams.SetErrCode(OR_INVALID_SKILL);
	//return FALSE;

	//__UNGUARD__ 
	return FALSE;
}


