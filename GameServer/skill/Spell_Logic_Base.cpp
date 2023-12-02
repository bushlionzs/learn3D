/*$T MapServer/Server/Spell/SpellLogic/SpellLogic.cpp GC 1.140 10/10/07 10:07:57 */


/*$6
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


#include "stdafx.h"
#include "Spell_Logic_Base.h"
#include "gameobject/Player.h"
#include "gameobject/Character.h"
#include "gameobject/Monster.h"
#include "gameobject/Pet.h"
#include "map/game_map.h"
#include "Spell_EffectLogicManager.h"
#include "Spell_TrapObjLogic.h"
#include "gameobject/CharActionDelegator.h"
#include "data/data_manager.h"
#include "map/map_info.h"
#include "TabDefine.h"
#include "Spell_Helper.h"
#include "server_settting.h"
#include "skill/Spell_Helper.h"
#include "map/MapScanerOperators.h"
#include "net/messages/SCTargetListAndHitFlags.h"
#include "net/net_message_manager.h"


extern ConditionAndDepleteCore_T	g_ConditionAndDepleteCore;
using namespace Messages;

/*
=======================================================================================================================
=======================================================================================================================
*/

BOOL BaseSpellLogic::SpecificOperationOnSpellStart(Character &rMe) const
{
	__GUARD__ return TRUE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsPassive(void) const
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::OnEvent_Interrupt(Character &rMe) const
{
	__GUARD__ return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::OnEvent_Cancel(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rParams.SetErrCode(OR_INVALID_SKILL);
	rParams.SetErrParam(rParams.GetActivatedSpell());
	return FALSE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/

BOOL BaseSpellLogic::DepleteProcess(Character &rMe) const
{
	__GUARD__ if(FALSE == CommonDeplete(rMe))
	{
		return FALSE;
	}

	if(FALSE == SpecificDeplete(rMe))
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsConditionSatisfied(Character &rMe) const
{
	__GUARD__ if(FALSE == CommonConditionCheck(rMe))
	{
		return FALSE;
	}

	if(FALSE == SpecificConditionCheck(rMe))
	{
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
};

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::StartCharging(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ long				nMaxTime = 0;
	SpellInfo				&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	nMaxTime = rSpellInfo.GetChargeTime();

	/*~~~~~~~~~~~~~~~~*/
	BOOL	bRet = TRUE;
	/*~~~~~~~~~~~~~~~~*/

	if(0 >= nMaxTime)
	{
		bRet = Action_ActivateOnceDispatch(rMe);
	}
	else
	{
		bRet = GetGlobalActionDelegator().Register_ChargeActionForSpell(rMe, rSpellInfo.GetSpellID(), nMaxTime);
	}

	if(TRUE == bRet)
	{
		rParams.SetErrCode(OR_OK);
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::StartChanneling(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	long					nMaxTime = rSpellInfo.GetChannelTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(0 >= nMaxTime)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szText[255] = { '\0' };
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s
			(
			szText,
			sizeof(szText),
			"[SpellLogic::StartChanneling]: Zero channel time found!! SkillId = %d",
			rSpellInfo.GetSpellID()
			);
		KCheckEx(FALSE, szText);
		rParams.SetErrCode(OR_DEFAULT_ERROR);
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~*/
	BOOL	bRet = TRUE;
	/*~~~~~~~~~~~~~~~~*/

	if(FALSE == rParams.GetIgnoreConditionCheckFlag())
	{
		bRet = DepleteProcess(rMe);
	}

	if(TRUE == bRet)
	{
		rMe.OnEvent_UseSkillSuccessfully(rSpellInfo);

		if (TRUE == GetGlobalActionDelegator().Register_ChannelActionForSpell(rMe, rSpellInfo.GetSpellID(),
			nMaxTime, rSpellInfo.GetChargesOrInterval()))
		{
			CooldownProcess(rMe);
			rParams.SetErrCode(OR_OK);

			//立即触发一次 add by wujianping
			SpellTemplateData const *pSkillTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(rSpellInfo.GetSpellID());
			if (pSkillTemplate && pSkillTemplate->IsActionAtOnce())
			{
				SpellInfo &oSkillInfo = rMe.GetSpellInfo();
				const BaseSpellLogic *pLogic = Spell_GetLogic(oSkillInfo);
				if(pLogic)
				{
					if( FALSE == pLogic->Action_ActivateEachTickDispatch(rMe) )
					{
						GetGlobalActionDelegator().InterruptCurrentAction(rMe);
					}
				}
			}
			return TRUE;
		}
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::StartLaunching(Character &rMe) const
{
	__GUARD__ return Action_ActivateOnceDispatch(rMe);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::Action_ActivateOnceDispatch(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	if (rMe.GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		//普通攻击 zhousha
		int kk = 0;
	}
	if(FALSE == IsConditionSatisfied(rMe))
	{
		return FALSE;
	}

	if(!ReCheckConditionForActiveOnce(rMe))
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~*/
	BOOL	bRet = TRUE;
	/*~~~~~~~~~~~~~~~~*/

	if(FALSE == rParams.GetIgnoreConditionCheckFlag())
	{
		bRet = DepleteProcess(rMe);
	}

	if(TRUE == bRet)
	{
		rMe.OnEvent_UseSkillSuccessfully(rSpellInfo);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Time_t	nPlayActionTime = CalculateActionTime(rMe);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if
			(
			FALSE == GetGlobalActionDelegator().Register_InstantActionForSpell
			(
			rMe,
			rSpellInfo.GetSpellID(),
			nPlayActionTime
			)
			)
		{
			return FALSE;
		}

		rMe.SetActionTime(nPlayActionTime);

		CooldownProcess(rMe);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nActivateTimes = rSpellInfo.GetChargesOrInterval();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 >= nActivateTimes)
		{
			nActivateTimes = 1;
		}

		for(int32 nIdx = 0; nActivateTimes > nIdx; ++nIdx)
		{
			rParams.SetDelayTime(rParams.GetDelayTime() + rSpellInfo.GetDelayTime());
			ActivateOnce(rMe);
		}
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::Action_ActivateEachTickDispatch(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == TargetCheckForEachTick(rMe))
	{
		rParams.SetDelayTime(rSpellInfo.GetDelayTime());
		ActivateEachTick(rMe);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Time_t BaseSpellLogic::CalculateActionTime(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Time_t					nPlayActionTime = rSpellInfo.GetPlayActionTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(MELEE_ATTACK == rParams.GetActivatedSpell())
	{
		if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster &rMonster = static_cast<Monster &>(rMe);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nPlayActionTime = rMonster.GetAttackAnimTime();
		}
		else if(Object::OBJECT_CLASS_PET == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Pet	&rPet = static_cast<Pet &>(rMe);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		}
	}

	return nPlayActionTime;
	__UNGUARD__ return 1000;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSpellLogic::CooldownProcess(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Time_t					nPlayActionTime = rSpellInfo.GetPlayActionTime();
	Time_t					nCooldown = rSpellInfo.GetCooldownTime();
	Time_t					nDelayTime = rSpellInfo.GetDelayTime();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(MELEE_ATTACK == rParams.GetActivatedSpell())
	{
		if(Object::OBJECT_CLASS_MONSTER == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Monster &rMonster = static_cast<Monster &>(rMe);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nCooldown = rMonster.GetAttackCooldownTime();
			nPlayActionTime = rMonster.GetAttackAnimTime();
		}
		else if(Object::OBJECT_CLASS_PET == rMe.GetObjType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Pet	&rPet = static_cast<Pet &>(rMe);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		}
	}

	if(nCooldown < nPlayActionTime)
	{
		nCooldown = nPlayActionTime;
	}

	if (nCooldown < COMMON_COOLDOWN)
	{
		nCooldown = COMMON_COOLDOWN;
	}

	if(TRUE == rSpellInfo.IsAutoShotSpell())
	{
		SetAutoRepeatCooldown(rMe, nCooldown);
	}
	else
	{
		SetCooldown(rMe, (CooldownID_t) rSpellInfo.GetCooldownID(), nCooldown);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::CommonConditionCheck(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nIdx;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(nIdx = 0; SpellInstanceData::CONDITION_AND_DEPLETE_TERM_NUMBER - 1 > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ConditionAndDepleteTerm const	*pConDepTerm = Get_Property_ConDepTermByIndex(rSpellInfo, nIdx);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pConDepTerm)
		{
			if(FALSE == g_ConditionAndDepleteCore.ConditionCheck(rMe, *pConDepTerm))
			{
				return FALSE;
			}
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			iIdx = SpellInstanceData::CONDITION_AND_DEPLETE_TERM_NUMBER - 1;
	ConditionAndDepleteTerm const	*pConDepTerm = Get_Property_ConDepTermByIndex(rSpellInfo, nIdx);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pConDepTerm)
	{
		if(FALSE == g_ConditionAndDepleteCore.ConditionCheckByItem(rMe, *pConDepTerm))
		{
			return FALSE;
		}
	}

	if(FALSE == TargetCheckForActivateOnce(rMe))
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
BOOL BaseSpellLogic::CommonDeplete(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nIdx;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(nIdx = 0; SpellInstanceData::CONDITION_AND_DEPLETE_TERM_NUMBER - 1 > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ConditionAndDepleteTerm const	*pConDepTerm = Get_Property_ConDepTermByIndex(rSpellInfo, nIdx);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pConDepTerm)
		{
			if(FALSE == g_ConditionAndDepleteCore.Deplete(rMe, *pConDepTerm))
			{
				return FALSE;
			}
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			iIdx = SpellInstanceData::CONDITION_AND_DEPLETE_TERM_NUMBER - 1;
	ConditionAndDepleteTerm const	*pConDepTerm = Get_Property_ConDepTermByIndex(rSpellInfo, nIdx);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pConDepTerm)
	{
		if(FALSE == g_ConditionAndDepleteCore.DepleteByItem(rMe, *pConDepTerm))
		{
			return FALSE;
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::TargetCheckForEachTick(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(1 != rSpellInfo.GetSelectType())
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = GetTargetObj(rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pObj)
	{
		return FALSE;
	}

	if(IsObjCharacter(pObj->GetObjType()))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Character	&rTar = *(Character *) pObj;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(FALSE == rTar.IsCanViewMe(&rMe))
		{
			rParams.SetErrCode(OR_INVALID_TARGET);
			rParams.SetErrParam(0);
			return FALSE;
		}

		switch(rSpellInfo.GetTargetMustInSpecialState())
		{
		case 0:
			if(FALSE == rTar.IsAlive())
			{
				rParams.SetErrCode(OR_TARGET_DIE);
				rParams.SetErrParam(0);
				return FALSE;
			}
			break;

		case 1:
			if(TRUE == rTar.IsAliveInDeed())
			{
				rParams.SetErrCode(OR_INVALID_TARGET);
				rParams.SetErrParam(0);
				return FALSE;
			}
			break;

		default:
			break;
		};
		if(TRUE == IsOutOfRange(rMe, rTar))
		{
			rParams.SetErrCode(OR_OUT_RANGE);
			rParams.SetErrParam(0);
			return FALSE;
		}
		//if( rTar.IsUnbreakable() )
		//{
		//	rParams.SetErrCode(OR_TARGET_IS_UNBREAKABLE);
		//	rParams.SetErrParam(0);
		//	return FALSE;
		//}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::TargetCheckForActivateOnce(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(1 != rSpellInfo.GetSelectType())
	{
		if(2 == rSpellInfo.GetSelectType())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GLPos	TargetPosition = rParams.GetTargetPosition();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(TRUE == IsOutOfRange(rMe, TargetPosition))
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Object	*pObj = GetTargetObj(rMe);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pObj)
	{
		if(IsObjCharacter(pObj->GetObjType()))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	&rTar = *(Character *) pObj;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(FALSE == rTar.IsCanViewMe(&rMe))
			{
				rParams.SetErrCode(OR_INVALID_TARGET);
				rParams.SetErrParam(0);
				return FALSE;
			}

			switch(rSpellInfo.GetTargetCheckByObjType())
			{
			case 0:
				if(Object::OBJECT_CLASS_PLAYER != rTar.GetObjType())
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				};
				break;

			case 1:
				if(Object::OBJECT_CLASS_PET != rTar.GetObjType())
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;

			case 2:
				if(Object::OBJECT_CLASS_MONSTER != rTar.GetObjType())
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;

			case 3:
				if
					(
					Object::OBJECT_CLASS_PLAYER != rTar.GetObjType()
					&&	Object::OBJECT_CLASS_PET != rTar.GetObjType()
					)
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				};
				break;

			case 4:
				if
					(
					Object::OBJECT_CLASS_PLAYER != rTar.GetObjType()
					&&	Object::OBJECT_CLASS_PET != rTar.GetObjType()
					&&	Object::OBJECT_CLASS_BUS != rTar.GetObjType()
					)
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				};
				break;

			case -1:
			default:
				break;
			};
			switch(rSpellInfo.GetTargetLogicByStand())
			{
			case TC_PARTNER:
				if(FALSE == rMe.IsFriend(&rTar))
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				};
				break;

			case TC_ENEMY:
				if(FALSE == rMe.IsEnemy(&rTar))
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;
			case TC_PARTNER_PET:
				if(FALSE == rMe.IsFriend(&rTar))
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				};
				if(Object::OBJECT_CLASS_PET != rTar.GetObjType())
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
			case TC_PARTNER_EXCEPT_SELF:
				if(FALSE == rMe.IsFriend(&rTar))
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				if( rMe.GetID() == rTar.GetID() )
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;
			case TC_ENEMY_AND_PLAYER:
				if(FALSE == rMe.IsEnemy(&rTar))
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}

				if(Object::OBJECT_CLASS_PLAYER != rTar.GetObjType())
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;
			case -1:
			default:
				break;
			};
			switch(rSpellInfo.GetTargetMustInSpecialState())
			{
			case 0:
				if(FALSE == rTar.IsAlive())
				{
					rParams.SetErrCode(OR_TARGET_DIE);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;

			case 1:
				if(TRUE == rTar.IsAliveInDeed())
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
				break;

			default:
				break;
			};
			if(TRUE == rSpellInfo.IsPartyOnly())
			{
				if(FALSE == rMe.IsPartner(&rTar) || FALSE == rTar.IsPartner(&rMe))
				{
					rParams.SetErrCode(OR_INVALID_TARGET);
					rParams.SetErrParam(0);
					return FALSE;
				}
			}

			if(TRUE == IsOutOfRange(rMe, rTar))
			{
				rParams.SetErrCode(OR_OUT_RANGE);
				rParams.SetErrParam(0);
				return FALSE;
			}

			if(-1 != rSpellInfo.GetSpellLevel())
			{
				if(TRUE == rMe.IsFriend(&rTar))
				{
					if(rSpellInfo.GetSpellLevel() > rTar.GetLevel())
					{
						rParams.SetErrCode(OR_INVALID_TARGET);
						return FALSE;
					}
				}

				if(TRUE == rMe.IsEnemy(&rTar))
				{
					if(rSpellInfo.GetSpellLevel() < rTar.GetLevel())
					{
						rParams.SetErrCode(OR_INVALID_TARGET);
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsOutOfRange(Character &rMe, Character &rTar) const
{
	__GUARD__ if(rMe.GetObjType() == Object::OBJECT_CLASS_PET) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo				&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	float					fAcceptableDistanceError = 0.0f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(Object::OBJECT_CLASS_PLAYER == rMe.GetObjType())
	{
		fAcceptableDistanceError = ACCEPTDISTANCEERROR_FOR_HUMAN / 2.0;
	}
	else
	{
		fAcceptableDistanceError = ACCEPTDISTANCEERROR_FOR_NPC / 4.0;
	}

	if(CHARACTER_LOGIC_MOVE == rTar.GetCharacterLogic())
	{
		fAcceptableDistanceError += 0.5;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fRangeMinSq = rSpellInfo.GetOptimalRangeMin();
	float	fRangeMaxSq = rSpellInfo.GetOptimalRangeMax();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fRangeMinSq -= fAcceptableDistanceError;
	fRangeMaxSq += fAcceptableDistanceError;
	fRangeMinSq = fRangeMinSq > 0 ? fRangeMinSq * fRangeMinSq : 0;
	fRangeMaxSq = fRangeMaxSq > 0 ? fRangeMaxSq * fRangeMaxSq : 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos const &posStart = *(rMe.GetGLPos());
	GLPos const &posEnd = *(rTar.GetGLPos());
	float		fDistToTargetSq = DistanceSq(posStart, posEnd);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistToTargetSq < fRangeMinSq)
	{
		rParams.SetErrCode(OR_OUT_RANGE);
		rParams.SetErrParam((int32) (fDistToTargetSq - fRangeMinSq));
		return TRUE;
	}

	if(fDistToTargetSq > fRangeMaxSq)
	{
		rParams.SetErrCode(OR_OUT_RANGE);
		rParams.SetErrParam((int32) (fDistToTargetSq - fRangeMaxSq));
		return TRUE;
	}

	rParams.SetErrCode(OR_OK);
	return FALSE;
	__UNGUARD__ return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsOutOfRange(Character &rMe, GLPos const &rPosTarget) const
{
	__GUARD__ if(rMe.GetObjType() == Object::OBJECT_CLASS_PET)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo				&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	float					nAcceptableDistanceError = 0.0f;
	float					fRangeMinSq = rSpellInfo.GetOptimalRangeMin() -
		nAcceptableDistanceError;
	float					fRangeMaxSq = rSpellInfo.GetOptimalRangeMax() +
		nAcceptableDistanceError;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fRangeMinSq = fRangeMinSq > 0 ? fRangeMinSq * fRangeMinSq : 0;
	fRangeMaxSq = fRangeMaxSq > 0 ? fRangeMaxSq * fRangeMaxSq : 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const GLPos &posStart = *(rMe.GetGLPos());
	float		fDistToTargetSq = DistanceSq(posStart, rPosTarget);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistToTargetSq < fRangeMinSq)
	{
		rParams.SetErrCode(OR_OUT_RANGE);
		rParams.SetErrParam((int32) (fDistToTargetSq - fRangeMinSq));
		return TRUE;
	}

	if(fDistToTargetSq > fRangeMaxSq)
	{
		rParams.SetErrCode(OR_OUT_RANGE);
		rParams.SetErrParam((int32) (fDistToTargetSq - fRangeMaxSq));
		return TRUE;
	}

	rParams.SetErrCode(OR_OK);
	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
float BaseSpellLogic::DistanceSq(GLPos const &posStart, GLPos const &posEnd) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fDistX, fDistZ;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fDistX = posEnd.m_fX - posStart.m_fX;
	fDistZ = posEnd.m_fZ - posStart.m_fZ;
	return fDistX * fDistX + fDistZ * fDistZ;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSpellLogic::SetCooldown(Character &rMe, CooldownID_t nID, int32 nCooldownTime) const
{
	__GUARD__ rMe.SetCooldown((CooldownID_t) nID, nCooldownTime);
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSpellLogic::SetAutoRepeatCooldown(Character &rMe, int32 nCooldownTime) const
{
	__GUARD__ nCooldownTime += rMe.GetAutoRepeatCooldown();
	rMe.SetAutoRepeatCooldown(nCooldownTime);
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Object *BaseSpellLogic::GetTargetObj(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	Character				*pTar = (Character *) rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pTar)
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return NULL;
	}

	if(NULL == pTar || FALSE == pTar->IsActiveObj())
	{
		rParams.SetErrCode(OR_INVALID_TARGET);
		return NULL;
	}

	return (Object *) pTar;
	__UNGUARD__ return NULL;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsTargetAlive(Character &rTar) const
{
	__GUARD__ if(rTar.IsAlive()) return TRUE;
	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsHit(Character &rMe, Character &rTar, int32 nAccuracy) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CombatSystem	myCombatCore;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	SpellInfo	&oSkillInf = rMe.GetSpellInfo();

	nAccuracy = myCombatCore.CalculateHitRate(rMe, rTar);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRand = 0;
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		nRand = pMap->GetRand100();
	}

	BOOL bRet = myCombatCore.IsHit(nAccuracy, nRand);

	if(g_Config.m_ConfigInfo.m_nToggleDebugInherenceBalance)
	{
		QLogSystem::QUICK_LOG
			(
			QUICK_LOG_DEBUG,
			"IsHit result = %d, nHit = %d, nMiss = %d, nAccuracy = %d, nRand = %d",
			bRet,
			rMe.Get_Property_Hit(),
			rTar.Get_Property_Miss(),
			nAccuracy,
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
BOOL BaseSpellLogic::CheckEffectAvailability(Character &rMe, Character &rTar, UNIT_EFFECT &rImp) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CombatSystem	myCombatCore;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ID_t		nDataIndex = rImp.GetDataIndex();
	EffectData const	*pData = DataManager::GetSingletonPtr()->getEffectData(nDataIndex);
	if( pData == NULL )
		return FALSE;

	int32	nControlType = pData->GetControlType();
	if( SCT_NULL != nControlType )
	{
		int32 nAccuracy = 0;
		nAccuracy = myCombatCore.CalculateHitRateForControlSpell(rMe, rTar, SpellControlType(nControlType));

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRand = 0;
		GameMap	*pMap = rMe.GetMap();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pMap)
		{
			nRand = pMap->GetRand100();
		}

		return myCombatCore.IsHit(nAccuracy, nRand);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsCriticalHit(Character &rMe, int32 nCriticalRate, Character &rTag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CombatSystem	myCombatCore;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(-1 == nCriticalRate)
	{
		nCriticalRate = rMe.Get_Property_Critical();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRand = 0;
	GameMap	*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		nRand = pMap->GetRand100();
	}

	return myCombatCore.IsCriticalHit(rMe, nCriticalRate, nRand, rTag, rTag.GetToughness());
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Time_t BaseSpellLogic::RefixPlayActionTimeWithAttackRate(Time_t nPlayActionTime, int32 nAttackRate) const
{
	return Float2Int(nPlayActionTime * nAttackRate * 0.01f);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Time_t BaseSpellLogic::RefixCooldownTimeWithAttackRate(Time_t nCooldownTime, int32 nAttackRate) const
{
	return Float2Int(nCooldownTime * nAttackRate * 0.01f);
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSpellLogic::RefixPowerByRate(SpellInfo &rSpell, int32 nRate) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nDeplete = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == CanBeRefixed())
	{
		rSpell.SetPowerRefixByRate(nRate);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSpellLogic::RefixDepleteByRate(SpellInfo &rSpell, int32 nRate) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nDeplete = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == CanBeRefixed())
	{
		rSpell.SetDepleteRefixByRate(nRate);
	}

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::ScanUnitForTarget(Character &rMe, float fX, float fZ, OBJLIST &rTargets) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	GameMap					*pMap = rMe.GetMap();
	SCANOR_SECTORSKILL_INIT		ScanOperatorIniter;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ScanOperatorIniter.m_pSkillInfo = &rSpellInfo;
	ScanOperatorIniter.m_pMe = &rMe;
	ScanOperatorIniter.m_pMap = rMe.GetMap();
	ScanOperatorIniter.m_pTargets = &rTargets;
	ScanOperatorIniter.m_fRadius = rSpellInfo.GetRadius();
	ScanOperatorIniter.m_CentrePoint.m_fX = fX;
	ScanOperatorIniter.m_CentrePoint.m_fZ = fZ;
	ScanOperatorIniter.m_fDir = rParams.GetTargetDirection();

	if(-1 == rSpellInfo.Get_Property_MaxTargetNumber())
	{
		ScanOperatorIniter.m_nCount = rTargets.MAX_OBJ_LIST_SIZE - 1;
	}
	else
	{
		ScanOperatorIniter.m_nCount = rSpellInfo.Get_Property_MaxTargetNumber();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Scanor_SectorSkill	Scanor;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Scanor.Init(&ScanOperatorIniter);
	if(NULL != pMap)
	{
		if(FALSE == pMap->Scan(&Scanor))
		{
			rParams.SetErrCode(OR_SCAN_ERROR);
			return FALSE;
		}
	}
	else
	{
		rParams.SetErrCode(OR_NULL_MAP);
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::ActivateOnce(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	SpellTemplateData const			*pSpellTemplate = DataManager::GetSingletonPtr()->getSpellTemplate(rSpellInfo.GetSpellID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pSpellTemplate)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	OBJLIST			Targets;
	HitFlagsForOBJLIST_T	HitFlagList;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CalculateTargetList(rMe, Targets))
	{
		rParams.SetErrCode(OR_NO_TARGET);
		g_SpellCore.OnException(rMe);
		return FALSE;
	}

	HitFlagList.ClearAllFlags();

	/*~~~~~~~~~~~~~*/
	int32	nIdx = 0;
	/*~~~~~~~~~~~~~*/

	for(nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pTarget = Targets.m_aObj[nIdx];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pTarget)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pChar = (Character *) pTarget;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(TRUE == HitThisTarget(rMe, *pChar))
			{
				HitFlagList.MarkFlagByIndex(nIdx);
			}

			RegisterBeSpellEvent(*pChar, rMe, rSpellInfo.GetSpellID(), rSpellInfo.GetDelayTime());
		}
	}

	rParams.SetTargetCount(Targets.m_Count);

	BroadcastTargetListMessage(rMe, Targets, HitFlagList);

	for(nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pTarget = Targets.m_aObj[nIdx];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pTarget)
		{
			if(TRUE == HitFlagList.GetFlagByIndex(nIdx))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Character	*pChar = (Character *) pTarget;
				BOOL		bCriticalHit = CriticalHitThisTarget(rMe, *pChar);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pSpellTemplate->IsRunSkill())
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~*/
					GLPos	oRunTagPos;
					/*~~~~~~~~~~~~~~~~~~~~~~~*/

					if(CalculateCanGoPos(rMe, pChar, oRunTagPos))
					{
						rMe.SetGLPos(pTarget->GetGLPos());
					}
				}

				if(!EffectOnUnitOnce(rMe, *pChar, bCriticalHit))
				{
					g_SpellCore.OnException(rMe);
				}
			}
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::ActivateEachTick(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	OBJLIST					Targets;
	HitFlagsForOBJLIST_T			HitFlagList;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == CalculateTargetList(rMe, Targets))
	{
		return FALSE;
	}

	HitFlagList.ClearAllFlags();

	/*~~~~~~~~~~~~~*/
	int32	nIdx = 0;
	/*~~~~~~~~~~~~~*/

	for(nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pTarget = Targets.m_aObj[nIdx];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pTarget)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character	*pChar = (Character *) pTarget;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(TRUE == HitThisTarget(rMe, *pChar))
			{
				HitFlagList.MarkFlagByIndex(nIdx);
			}
		}
	}

	rParams.SetTargetCount(Targets.m_Count);

	BroadcastTargetListMessage(rMe, Targets, HitFlagList);

	for(nIdx = 0; Targets.m_Count > nIdx; ++nIdx)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pTarget = Targets.m_aObj[nIdx];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NULL != pTarget)
		{
			if(TRUE == HitFlagList.GetFlagByIndex(nIdx))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Character	*pChar = (Character *) pTarget;
				BOOL		bCriticalHit = CriticalHitThisTarget(rMe, *pChar);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				EffectOnUnitEachTick(rMe, *pChar, bCriticalHit);
			}
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::EffectOnUnitEachTick(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::HitThisTarget(Character &rMe, Character &rTar) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	GameMap					*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == rMe.IsFriend(&rTar))
	{
		return TRUE;
	}

	

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iHurtDelayTime = GetHurtDelayTime(rSpellInfo, rMe, rTar);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rParams.SetDelayTime(iHurtDelayTime);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nGoodEffect = GetSpellStandFlag(rSpellInfo.GetSpellID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rMe.OnEvent_Hit(rTar, nGoodEffect);

	if(FALSE == IsHit(rMe, rTar, rSpellInfo.GetAccuracy()))
	{
		if(NULL != pMap)
		{
			pMap->GetEventCore().RegisterSkillMissEvent
				(
				rTar.GetID(),
				rMe.GetID(),
				rSpellInfo.GetSpellID(),
				rParams.GetDelayTime()
				);
		}

		return FALSE;
	}

	if(NULL != pMap)
	{
		pMap->GetEventCore().RegisterSkillHitEvent
			(
			rTar.GetID(),
			rMe.GetID(),
			rSpellInfo.GetSpellID(),
			rParams.GetDelayTime()
			);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::CriticalHitThisTarget(Character &rMe, Character &rTar) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(TRUE == rMe.IsFriend(&rTar))
	{
		return FALSE;
	}

	if(TRUE == IsCriticalHit(rMe, -1, rTar))
	{
		rMe.OnEvent_CriticalHitTarget(rSpellInfo.GetSpellID(), rTar);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::CalculateTargetList(Character &rMe, OBJLIST &rTargets) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rTargets.Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ID_t	nTargetMode = rSpellInfo.GetTargetingLogic();
	BOOL	bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(nTargetMode)
	{
	case TARGET_SELF:
		{
			rTargets.m_aObj[0] = &rMe;

			if (rMe.GetObjType() == Object::OBJECT_CLASS_PLAYER)
			{
				/*if(((Player *) &rMe)->Skill_HaveBusSkill(rSpellInfo.GetSpellID()) == TRUE
					&& ((Player *) &rMe)->GetGotOnFlag())
				{
					Map	*pMap = ((Player *)&rMe)->GetMap();

					if(NULL == pMap)
					{
						KCheckEx(FALSE, "[BaseSpellLogic::CalculateTargetList]: pMap == NULL!!!!Check it now!!");
						return FALSE;
					}

					Bus	*pBus = pMap->GetBusManager()->GetBus(((Player *)&rMe)->GetBusObjID());

					if(NULL == pBus)
					{
						KCheckEx(FALSE, "[BaseSpellLogic::CalculateTargetList]: pBus == NULL!!!!Check it now!!");
						return FALSE;
					}

					rTargets.m_aObj[0] = pBus;
				}*/
			}

			++rTargets.m_Count;
			bRet = TRUE;
		}
		break;

	case TARGET_MY_PET:
		{
			for(int32 i = 0; i < MAX_MONSTER_PET_TAKE; ++i)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Object	*pPet = rMe.GetMyPet(i);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(NULL != pPet)
				{
					rTargets.m_aObj[rTargets.m_Count] = pPet;
					++rTargets.m_Count;
					bRet = TRUE;
				}
			}
		}
		break;

	case TARGET_MY_SHADOW_GUARD:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pGuard = rMe.GetMyShadowGuard();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pGuard)
			{
				rTargets.m_aObj[0] = pGuard;
				++rTargets.m_Count;
				bRet = TRUE;
			}
		}
		break;

	case TARGET_MY_MASTER:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pMaster = rMe.GetMyMaster();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pMaster)
			{
				rTargets.m_aObj[0] = pMaster;
				++rTargets.m_Count;
				bRet = TRUE;
			}
		}
		break;

	case TARGET_AE_AROUND_SELF:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GLPos const *pPos = rMe.GetGLPos();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pPos)
			{
				bRet = ScanUnitForTarget(rMe, pPos->m_fX, pPos->m_fZ, rTargets);
			}
		}
		break;

	case TARGET_SPECIFIC_UNIT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pTarget = rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pTarget)
			{
				rTargets.m_aObj[0] = pTarget;
				++rTargets.m_Count;
				bRet = TRUE;
			}
		}
		break;

	case TARGET_AE_AROUND_UNIT:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Object	*pTarget = rMe.GetSpecificObjInSameSceneByID(rParams.GetTargetObj());
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(NULL != pTarget)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				GLPos const *pPos = pTarget->GetGLPos();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(NULL != pPos)
				{
					bRet = ScanUnitForTarget(rMe, pPos->m_fX, pPos->m_fZ, rTargets);
				}
			}
		}
		break;

	case TARGET_AE_AROUND_POSITION:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			GLPos const &rPos = rParams.GetTargetPosition();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			bRet = ScanUnitForTarget(rMe, rPos.m_fX, rPos.m_fZ, rTargets);
		}
		break;

	case TARGET_POS:
		rTargets.m_aObj[0] = &rMe;
		++rTargets.m_Count;
		bRet = TRUE;
		break;

	default:
		{
			bRet = FALSE;
		}
		break;
	}

	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::RegisterImpactEvent
(
 Character	&rReceiver,
 Character	&rSender,
 UNIT_EFFECT	&rImp,
 Time_t		nDelayTime,
 BOOL		bCriticalFlag
 ) const
{
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rSender.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rSender.GetTargetingAndDepletingParams();
	GameMap					*pMap = rReceiver.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	BOOL bRlt = CheckEffectAvailability(rSender, rReceiver, rImp);

	if (!bRlt)
	{
		if(NULL != pMap)
		{
			pMap->GetEventCore().RegisterSkillMissEvent
				(
				rReceiver.GetID(),
				rSender.GetID(),
				rSpellInfo.GetSpellID(),
				rParams.GetDelayTime(),
				CombatMissFlag::FLAG_RESIST
				);
		}

		return FALSE;
	}

	rImp.SetSkillID(rSpellInfo.GetSpellID());
	if(TRUE == bCriticalFlag)
	{
		rImp.MarkCriticalFlag();
	}

	if(NULL != pMap)
	{
		return pMap->GetEventCore().RegisterImpactEvent
			(
			rReceiver.GetID(),
			rSender.GetID(),
			rImp,
			nDelayTime,
			rImp.GetSkillID()
			);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::RegisterSpellMissEvent
(
 Character	&rReceiver,
 Character	&rSender,
 SpellID_t	nSkill,
 Time_t		nDelayTime
 ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = rReceiver.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		return pMap->GetEventCore().RegisterSkillMissEvent
			(
			rReceiver.GetID(),
			rSender.GetID(),
			nSkill,
			nDelayTime
			);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::RegisterBeSpellEvent
(
 Character	&rReceiver,
 Character	&rSender,
 SpellID_t	nSkill,
 Time_t		nDelayTime
 ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nBehaviorType = GetSpellStandFlag(nSkill);
	GameMap*pMap = rReceiver.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		return pMap->GetEventCore().RegisterBeSkillEvent
			(
			rReceiver.GetID(),
			rSender.GetID(),
			nBehaviorType,
			nDelayTime
			);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::RegisterActiveObj(Object &rObj, Character &rSender, Time_t nDelayTime) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap*pMap = rSender.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pMap)
	{
		return pMap->GetEventCore().RegisterActiveSpecialObjEvent(rObj.GetID(), nDelayTime);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

void BaseSpellLogic::BroadcastTargetListMessage
(
 Character		&rMe,
 OBJLIST			&rTargets,
 HitFlagsForOBJLIST_T	&rHitFlagsForObjList
 ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	
	SCTargetListAndHitFlags* packet = new SCTargetListAndHitFlags;

	const GLPos* pos = rMe.GetGLPos();

	packet->setObjId(rMe.GetID());
	packet->setObjPosition(pos->m_fX, pos->m_fZ);
	packet->setLogicCout(rMe.GetLogicCount());
	packet->setSkillId(rSpellInfo.GetSpellID());

	uchar nNum = rTargets.m_Count;
	int32_t max_target_size = 16;
	if (max_target_size < nNum)
		nNum = max_target_size;

	for (int32 i = 0; i < nNum; ++i)
	{
		Object* pTarget = rTargets.m_aObj[i];
		if (pTarget)
			packet->addTargetId(pTarget->GetID());
	}

	//NetManager::GetSingletonPtr()->sendNetMessage(packet);
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::IsWantedTarget(Character &rMe, Character &rTar, SpellInfo const &rSpellInfo) const
{
	__GUARD__ switch(rSpellInfo.GetTargetCheckByObjType())
	{
	case 0:
		if(Object::OBJECT_CLASS_PLAYER != rTar.GetObjType())
		{
			return FALSE;
		};
		break;

	case 1:
		if(Object::OBJECT_CLASS_PET != rTar.GetObjType())
		{
			return FALSE;
		}
		break;

	case 2:
		if(Object::OBJECT_CLASS_MONSTER != rTar.GetObjType())
		{
			return FALSE;
		}
		break;

	case -1:
	default:
		break;
	};
	if(0 == rSpellInfo.GetTargetMustInSpecialState())
	{
		if(FALSE == rTar.IsAlive())
		{
			return FALSE;
		}
	}

	if(1 == rSpellInfo.GetTargetMustInSpecialState())
	{
		if(FALSE == rTar.IsDie())
		{
			return FALSE;
		}
	}

	if(	TC_PARTNER == rSpellInfo.GetTargetLogicByStand() || 
		TC_PARTNER_EXCEPT_SELF == rSpellInfo.GetTargetLogicByStand() || 
		TC_PARTNER_PET == rSpellInfo.GetTargetLogicByStand() )
	{
		if(FALSE == rMe.IsFriend(&rTar))
		{
			return FALSE;
		}
		else
		{
			if(TRUE == rSpellInfo.IsPartyOnly())
			{
				if(FALSE == rMe.IsPartner(&rTar))
				{
					return FALSE;
				}
			}
		}

		if( TC_PARTNER_EXCEPT_SELF == rSpellInfo.GetTargetLogicByStand() )
		{
			if( rMe.GetID() == rTar.GetID() )
			{
				return FALSE;
			}
		}

		if(TC_PARTNER_PET == rSpellInfo.GetTargetLogicByStand())
		{
			if(Object::OBJECT_CLASS_PET != rTar.GetObjType())
			{
				return FALSE;
			}
		}
	}

	if( TC_ENEMY == rSpellInfo.GetTargetLogicByStand() || TC_ENEMY_AND_PLAYER == rSpellInfo.GetTargetLogicByStand() )
	{
		if(FALSE == rMe.IsEnemy(&rTar))
		{
			return FALSE;
		}

		if( TC_ENEMY_AND_PLAYER == rSpellInfo.GetTargetLogicByStand() )
		{
			if(Object::OBJECT_CLASS_PLAYER != rTar.GetObjType())
			{
				return FALSE;
			}
		}
	}

	
	return IsSpecificTargetWanted(rMe, rTar, rSpellInfo);
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BaseSpellLogic const *Spell_GetLogic(SpellInfo const &rSkill)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ID_t	nLogicID = rSkill.GetLogicID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nLogicID)
	{
		return NULL;
	}

	return g_SpellLogicList.GetLogicById(nLogicID);
	__UNGUARD__ return NULL;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 BaseSpellLogic::GetHurtDelayTime(SpellInfo &rSpellInfo, Character &rMe, Character &rTar) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iBulletSpeed = rSpellInfo.GetSpeedOfBullet();
	int32	iTime = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != iBulletSpeed)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const GLPos *pMyPos = rMe.GetGLPos();
		const GLPos *pTarPos = rTar.GetGLPos();
		int32		iDistance = (int32)
			(rMe.WordPosLength(pMyPos->m_fX - pTarPos->m_fX, pMyPos->m_fZ - pTarPos->m_fZ) * 100);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		iTime = iDistance * 1000 / iBulletSpeed;
	}

	iTime += rSpellInfo.GetHurtDelayTime();
	if(0 > iTime)
	{
		iTime = 0;
	}

	return iTime;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::CalculateCanGoPos(Character &rMe, Object *rTag, GLPos &sPos) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GLPos const	*pPos = rMe.GetGLPos();
	GLPos			sPosMe = *pPos;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pPos = rTag->GetGLPos();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	sPosTag = *pPos;
	GLPos	sDir;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sDir.m_fX = sPosTag.m_fX - sPosMe.m_fX;
	sDir.m_fZ = sPosTag.m_fZ - sPosMe.m_fZ;

	NormalizeWorldPos(sDir);

	if(sDir.m_fX == 0.0f && sDir.m_fZ == 0.0f) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	sFinalPos = sPosTag;
	float		fLengthOfStep = 0.5f;
	float		fLengthTmp = 0;
	GLPos	sPosTmp;
	BOOL		bRet = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 u = 0; u < 100; ++u)
	{
		fLengthTmp = WordPosLength(sFinalPos.m_fX - sPosTag.m_fX, sFinalPos.m_fZ - sPosTag.m_fZ);
		if(fLengthTmp < fLengthOfStep)
		{
			if(rMe.GetMap()->GetMapInfo()->IsCanGo(sFinalPos)) sPosTag = sFinalPos;
			bRet = TRUE;
			break;
		}

		sPosTmp.m_fX = sPosTag.m_fX + sDir.m_fX * fLengthOfStep;
		sPosTmp.m_fZ = sPosTag.m_fZ + sDir.m_fZ * fLengthOfStep;

		if(rMe.GetMap()->GetMapInfo()->IsCanGo(sPosTmp))
		{
			sPosTag = sPosTmp;
		}
		else
		{
			break;
		}
	}

	sPos = sPosTag;
	return bRet;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void BaseSpellLogic::NormalizeWorldPos(GLPos &sPos) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fLength = WordPosLength(sPos.m_fX, sPos.m_fZ);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sPos.m_fX /= fLength;
	sPos.m_fZ /= fLength;
	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
float BaseSpellLogic::WordPosLength(float fX, float fY) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fLength = sqrt(pow(fX, 2.0f) + pow(fY, 2.0f));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return fLength;

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL BaseSpellLogic::ReCheckConditionForActiveOnce(Character &rMe) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpellInfo				&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	BOOL					bResult = TRUE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rSpellInfo.GetTargetingLogic() == TARGET_SPECIFIC_UNIT)
	{
		/*~~~~~~~~~~~~*/
		OBJLIST Targets;
		/*~~~~~~~~~~~~*/

		if(FALSE == CalculateTargetList(rMe, Targets))
		{
			rParams.SetErrCode(OR_NO_TARGET);
			bResult = FALSE;
		}
		else if(!IsObjCharacter(Targets.m_aObj[0]->GetObjType()))
		{
			rParams.SetErrCode(OR_INVALID_TARGET);
			bResult = FALSE;
		}

		if(!bResult)
		{
			if
				(
				TRUE == GetGlobalActionDelegator().IsChanneling(rMe)
				||	TRUE == GetGlobalActionDelegator().IsChanneling(rMe)
				)
			{
				GetGlobalActionDelegator().InterruptCurrentAction(rMe);
			}

			g_SpellCore.OnException(rMe);
			return FALSE;
		}
	}

	return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL ArmorMastery::Refix_ItemEffect
(
 SpellInfo	&rThisPassiveSkill,
 int32		nSlotID,
 int32		nItemType,
 int32		nAttrID,
 int16		&nAttrValue
 ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixDefencePhysics = rThisPassiveSkill.GetDescriptorByIndex(BASE_DEFENCE_NEAR)->GetValueBySkillLevel(rThisPassiveSkill.GetCharacterSpellLevel());
	int32		nRefixDefenceMagic = rThisPassiveSkill.GetDescriptorByIndex(BASE_DEFENCE_MAGIC)->GetValueBySkillLevel(rThisPassiveSkill.GetCharacterSpellLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL TeleportAndEffects::EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellInfo			&rSpellInfo = rMe.GetSpellInfo();
	SpellTargetingAndDepletingParams	&rParams = rMe.GetTargetingAndDepletingParams();
	int32					nValue = 0;
	GameMap					*pMap = rMe.GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	UNIT_EFFECT	impact;
	int32		nImpact = INVALID_ID;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID != GetEffect1(rSpellInfo))
	{
		nImpact = GetEffect1(rSpellInfo);
		g_EffectInterface.SendEffectToUnit(rTar, nImpact, rMe.GetID(), rParams.GetDelayTime());
	}

	if(INVALID_ID != GetEffect2(rSpellInfo))
	{
		nImpact = GetEffect2(rSpellInfo);
		g_EffectInterface.SendEffectToUnit(rTar, nImpact, rMe.GetID(), rParams.GetDelayTime());
	}

	if(INVALID_ID != GetEffect3(rSpellInfo))
	{
		nImpact = GetEffect3(rSpellInfo);
		g_EffectInterface.SendEffectToUnit(rTar, nImpact, rMe.GetID(), rParams.GetDelayTime());
	}

	if(INVALID_ID != GetEffectTeleport(rSpellInfo))
	{
		nImpact = GetEffectTeleport(rSpellInfo);
		g_EffectInterface.InitEffectFromData(nImpact, impact, rMe);

		/*~~~~~~~~~~~~~~~~~~*/
		DI_Teleport_T	logic;
		/*~~~~~~~~~~~~~~~~~~*/

		logic.SetSceneID(impact, INVALID_ID);
		logic.SetPosition_X(impact, rParams.GetTargetPosition().m_fX);
		logic.SetPosition_Z(impact, rParams.GetTargetPosition().m_fZ);
		pMap->GetEventCore().RegisterImpactEvent
			(
			rTar.GetID(),
			rMe.GetID(),
			impact,
			rParams.GetDelayTime() + 500,
			rSpellInfo.GetSpellID()
			);
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 TeleportAndEffects::GetEffect1(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex(rSkill, SkillInfoDescriptorIndex_T::IDX_IMPACT_1);
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 TeleportAndEffects::GetEffect2(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex(rSkill, SkillInfoDescriptorIndex_T::IDX_IMPACT_2);
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 TeleportAndEffects::GetEffect3(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex(rSkill, SkillInfoDescriptorIndex_T::IDX_IMPACT_3);
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 TeleportAndEffects::GetEffectTeleport(SpellInfo const &rSkill) const
{
	__GUARD__ return GetSpellInfoDescriptorValueByIndex(rSkill, SkillInfoDescriptorIndex_T::IDX_IMPACT_TELEPORT);
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL WeaponMastery::Refix_ItemEffect
(
 SpellInfo	&rThisPassiveSkill,
 int32		nSlotID,
 int32		nItemType,
 int32		nAttrID,
 int16		&rAttrValue
 ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 nRefixAttackPhysics = rThisPassiveSkill.GetDescriptorByIndex(BASE_ATTACK_NEAR_REFIX)->GetValueBySkillLevel(rThisPassiveSkill.GetCharacterSpellLevel());
	int32		nRefixAttackMagic = rThisPassiveSkill.GetDescriptorByIndex(BASE_ATTACK_MAGIC_REFIX)->GetValueBySkillLevel(rThisPassiveSkill.GetCharacterSpellLevel());
	int32 const	nMasteryType1 = rThisPassiveSkill.GetDescriptorByIndex(MASTERY_OF_WEAPON_TYPE1)->GetValueBySkillLevel(rThisPassiveSkill.GetCharacterSpellLevel());
	int32 const	nMasteryType2 = rThisPassiveSkill.GetDescriptorByIndex(MASTERY_OF_WEAPON_TYPE2)->GetValueBySkillLevel(rThisPassiveSkill.GetCharacterSpellLevel());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__ return FALSE;
}
