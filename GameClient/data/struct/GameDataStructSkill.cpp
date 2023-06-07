#include "StdAfx.h"
#include "GameDataStructSkill.h"
#include "KObjectManager.h"
#include "kcharacter.h"
#include "data/GameDataCharacter.h"
#include "KTable.h"
#include "GameClientUtil.h"
#include "data/GameDataManager.h"

typedef std::vector<FLOAT> FloatVector;
typedef std::map<int32, FloatVector> RangeMap;;


void SkillDetail::Clear(void)
{
	m_pDefine = NULL;
	m_nPosIndex = -1;
	m_bLeaned = FALSE;
	m_nLevel = 0;
}	
/*
 =======================================================================================================================
 =======================================================================================================================
 */

OPT_RESULT SkillDetail::IsCanUse(int32 idUser, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) const
{
	OPT_RESULT oResult;

	oResult = IsCanUse_Leaned();			/* 是否已经学会 */
	if(ORT_FAILED(oResult)) return oResult;

	oResult = IsCanUse_CheckCoolDown();		/* 冷却 */
	if(ORT_FAILED(oResult))
	{
		/*
		 * 设置可以使用技能， 用普通攻击 ;
		 * if( HELPER_SYSTEM_PTR->GetSystemState() ) ;
		 * HELPER_SYSTEM_PTR->SetUseSkillState( TRUE );
		 */
		return oResult;
	}

	oResult = IsCanUse_CheckFlag(idUser);	/* 其他条件判断 */
	if(ORT_FAILED(oResult)) return oResult;

	/*
	 * oResult = IsCanUse_CheckDeplete( idUser );
	 * // 消耗 ;
	 * if ( ORT_FAILED( oResult ) ) ;
	 * return oResult;
	 */
	oResult = IsCanUse_CheckTarget(idUser, idTargetObj, fTargetX, fTargetZ, fDir);	/* 对选择目标进行判断 */
	if(ORT_FAILED(oResult)) return oResult;

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_Leaned(void) const
{
	if(m_nLevel <= 0) return OR_CHAR_DO_NOT_KNOW_THIS_SKILL;
	if(!m_bLeaned) return OR_CHAR_DO_NOT_KNOW_THIS_SKILL;

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_CheckCoolDown(void) const
{
	/* 冷却判断 */
	OPT_RESULT res = IsCanUse_CheckSkillCoolDown();

	if(OR_OK != res)
	{
		return res;
	}

	return IsCanUse_CheckCommonCoolDown();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_CheckSkillCoolDown(void) const
{
	/* 技能冷却组 */
	int32 nCoolDownID = m_pDefine->m_nCooldownID;

	if(INVALID_ID != nCoolDownID)
	{
		if(0 < GameDataManager::GetSingleton().GetCoolDownGroupTime(nCoolDownID))
		{
			return OR_COOL_DOWNING;
		}
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_CheckCommonCoolDown(void) const
{
	/* 公共冷却 */
	if(m_pDefine->m_bAutoRedo)
	{
		UINT64	uLastTime = GameDataManager::GetSingleton().GetSpecialCoolDown();
		UINT64	uCurrTime = GameClientUtil::GetTimeNow();

		if(uCurrTime - uLastTime < COMMONCOOLDOWN_TIME)
		{
			return OR_COOL_DOWNING;
		}
	}
	else
	{
		if(GameDataManager::GetSingleton().GetCommonCoolDown() > 0)
		{
			return OR_COOL_DOWNING;
		}
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_CheckFlag(int32 idUser) const
{
	if(NULL == m_pDefine) return OR_INVALID_SKILL;

	KCharacter* pUser = (KCharacter*)KObjectManager::GetSingleton().getObject(idUser);

	if(pUser == NULL)
	{
		KCheck(pUser != NULL && "SkillDetail::IsCanUse_CheckFlag");
		return OR_INVALID_SKILL;
	}

	KCharatcterBaseData *pCharData = pUser->GetCharacterData();

	if(pCharData == NULL)
	{
		KCheck(pCharData != NULL && "SkillDetail::IsCanUse_CheckFlag");
		return OR_INVALID_SKILL;
	}

	if(TRUE == m_pDefine->m_nDisableByFlag1)
	{
		if(FALSE == pCharData->IsHaveCanActionFlag1())
		{
			return OR_LIMIT_USE_SKILL;
		}
	}

	if(TRUE == m_pDefine->m_nDisableByFlag2)
	{
		if(FALSE == pCharData->IsHaveCanActionFlag2())
		{
			return OR_LIMIT_USE_SKILL;
		}
	}

	if(TRUE == m_pDefine->m_nDisableByFlag3)
	{
		if(pCharData->Get_ModelID() != INVALID_ID || /* 变身状态 */ pCharData->Get_MountID() != INVALID_ID) /* 骑乘状态 */
		{
			return OR_LIMIT_USE_SKILL;
		}
	}

	/* bus */
	if(pCharData->Get_BusState())
	{
		return OR_LIMIT_USE_SKILL;
	}

	/* 武器判断 */
	if(m_pDefine->m_bMustUseWeapon)
	{
		if(CHAR_BASE_TYPE_NPC == pUser->GetCharacterType())
		{
			return OR_LIMIT_USE_SKILL;
		}

		if(pUser->GetCharacterData()->Get_Equip(HEQUIP_MAINHAND) == INVALID_ID)
		{
			/* if( pUser->GetCharacterData()->Get_Equip( HEQUIP_ASSIHAND )== INVALID_ID ) */
			{
				return OR_NEED_A_WEAPON;
			}
		}
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_CheckDeplete(int32 idUser) const
{
	if(NULL == m_pDefine) return OR_INVALID_SKILL;

	KCharacter	*pUser = (KCharacter *)KObjectManager::GetSingleton().getObject(idUser);

	if(pUser == NULL)
	{
		KCheck(pUser != NULL && "SkillDetail::IsCanUse_CheckDeplete");
		return OR_INVALID_SKILL;
	}

	KCharatcterBaseData *pCharData = pUser->GetCharacterData();

	if(pCharData == NULL)
	{
		KCheck(pCharData != NULL && "SkillDetail::IsCanUse_CheckDeplete");
		return OR_INVALID_SKILL;
	}

	int32 nCon11 = m_pDefine->m_nCondition11;
	int32 nValue = m_pDefine->m_nCondition12 + (m_nLevel + 1) * nCon11;

	if(pCharData->Get_Rage() < nValue) return OR_NOT_ENOUGH_RAGE;

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
OPT_RESULT SkillDetail::IsCanUse_CheckTarget(int32 idUser, int32 idTargetObj, FLOAT fTargetX, FLOAT fTargetZ, FLOAT fDir) const
{
	/* 对象数量 */
	int32 objNum = 0;

	switch(m_pDefine->m_nSelectType)
	{
	case SELECT_TYPE_NONE:
		break;

	case SELECT_TYPE_CHARACTER:
		{
			if(idTargetObj == INVALID_ID)
			{
				
				return OR_NO_TARGET;
			}

			/*
			 * m_nTargetMustInSpecialState--> 0:活的；1:死的;
			 * -1:没有要求
			 */
			int32			nTargetMustAliveFlag = !(m_pDefine->m_nTargetMustInSpecialState);
			KCharacter	*pTargetObj = (KCharacter *)KObjectManager::GetSingleton().getObject(idTargetObj);

			if(!pTargetObj)
			{
				KCheck(NULL == "[SkillDetail::IsCanUse_CheckTarget]...pTargetObj = NULL...");
				return OR_INVALID_TARGET;
			}

			KCharacter	*pThisObj = (KCharacter *)KObjectManager::GetSingleton().getObject(idUser);

			if(!pThisObj)
			{
				KCheck(NULL == "[SkillDetail::IsCanUse_CheckTarget]...pThisObj = NULL...");
				return OR_INVALID_SKILL;
			}

			/* 阵营判断 */
			eRELATION	eCampType = 
				GameDataManager::GetSingleton().GetCampType(pThisObj, pTargetObj);

			if(m_pDefine->m_nFriendness < 0 && eCampType == RELATION_ENEMY)			/* 敌对 */
				;
			else if(m_pDefine->m_nFriendness > 0 && eCampType == RELATION_FRIEND)	/* 友好 */
				;
			else if(m_pDefine->m_nFriendness == 0)
				;
			else
			{
				return OR_INVALID_TARGET;
			}

			if(!(pTargetObj->IsDie()) && nTargetMustAliveFlag)						/* 活的 */
			{
				/* 该技能只对活目标有效 */
			}
			else if(pTargetObj->IsDie() && !nTargetMustAliveFlag)					/* 死的 */
			{
				/* 该技能只对死目标有效 */
			}
			else
			{
				/*
				 * 内挂系统判断 ;
				 * if( HELPER_SYSTEM_PTR->GetSystemState() ) ;
				 * { ;
				 * int32 nSkillId = 0;
				 * HELPER_SYSTEM_PTR->CheckUseSkillState( nSkillId, idTargetObj );
				 * }
				 */
				return OR_INVALID_TARGET;
			}
		}
		break;

	case SELECT_TYPE_POS:
		{
			if(!(fTargetX >= 0.f && fTargetZ >= 0.f))
			{
				return OR_INVALID_TARGET_POS;
			}
		}
		break;

	case SELECT_TYPE_DIR:
		break;

	case SELECT_TYPE_SELF:
		break;

	case SELECT_TYPE_HUMAN_GUID:
		break;

	default:
		break;
	}

	return OR_OK;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LPCTSTR SkillDetail::GetSkillDesc() const	/* 得到技能的描述 */
{
	static TCHAR	szBuf2[32] = { 0 };

	return szBuf2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LPCTSTR SkillDetail::GetSkillDesc_Interface() const /* 得到技能的描述 */
{
	static TCHAR	szBuf2[32] = { 0 };
	return szBuf2;
}

FLOAT SkillDetail::GetSkillMaxRange() const
{
	if (NULL == m_pDefine)
		return 0.f;

	int32 nLevel = m_nLevel > 0 ? m_nLevel : 1;
	return ParseSkillMaxRange(m_pDefine, nLevel);
}

FLOAT SkillDetail::GetSkillMinRange() const
{
	if (NULL == m_pDefine)
		return 0.f;

	int32 nLevel = m_nLevel > 0 ? m_nLevel : 1;
	return ParseSkillMinRange(m_pDefine, nLevel);
}

FLOAT ParseSkillMaxRange(const _DBC_SPELL_DATA* pSkillData, int32 nLevel)
{
	STRING	strOut = CGameTable::GetSplitData(pSkillData->m_lpszMaxAttackRange, nLevel);
	FLOAT	fRange = atof(strOut.c_str());
	return fRange;
}

FLOAT ParseSkillMinRange(const _DBC_SPELL_DATA* pSkillData, int32 nLevel)
{
	STRING	strOut = CGameTable::GetSplitData(pSkillData->m_lpszMinAttackRange, nLevel);
	FLOAT	fRange = atoi(strOut.c_str());
	return fRange;
}

