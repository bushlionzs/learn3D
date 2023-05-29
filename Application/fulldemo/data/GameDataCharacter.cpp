#include "stdafx.h"
#include "SpellDataMgr.h"
#include "GameDataCharacter.h"
#include "character.h"



#define MUST_NOT_CHECK(typeName) \
	if(m_pObjRef->GetCharacterType() == typeName) \
		KLThrow("Character must not %s,(File:%s Line:%d)", #typeName, __FILE__, __LINE__);

/*
 =======================================================================================================================
 =======================================================================================================================
 */

KCharatcterBaseData::KCharatcterBaseData(Character *pCharObj)
{
	KLAssert(pCharObj);

	m_nType = INVALID_ID;
	m_pObjRef = pCharObj;
	m_pData = NULL;

	ResetData();
}

void KCharatcterBaseData::ResetData()
{
	if (NULL == m_pObjRef)
		return;

	m_nType = INVALID_ID;

	switch(m_pObjRef->GetCharacterType())
	{
	case CHAR_BASE_TYPE_ME:
		{
			if (NULL == m_pData)
				m_pData = new SDataPlayerMyself;
			_Init_AsCharacter();
			_Init_AsNPC();
			_Init_AsPlayerOther();
			_Init_AsPlayerMySelf();
		}		
		break;
	case CHAR_BASE_TYPE_OHTER:
		{
			if (NULL == m_pData)
				m_pData = new SDataPlayerOther;
			_Init_AsCharacter();
			_Init_AsNPC();
			_Init_AsPlayerOther();
		}		
		break;
	case CHAR_BASE_TYPE_NPC:
		{
			if (NULL == m_pData)
				m_pData = new SDataNPC;
			_Init_AsCharacter();
			_Init_AsNPC();
		}
		break;
	default:
		break;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
KCharatcterBaseData::~KCharatcterBaseData()
{
	if(m_pData && m_pObjRef)
	{
		switch(m_pObjRef->GetCharacterType())
		{
		case CHAR_BASE_TYPE_ME:		delete (SDataPlayerMyself *) m_pData; break;
		case CHAR_BASE_TYPE_OHTER:	delete (SDataPlayerOther *) m_pData; break;
		case CHAR_BASE_TYPE_NPC:	delete (SDataNPC *) m_pData; break;
		default:					KLThrow("Invalid Character type");
		}

		m_nType = INVALID_ID;
		m_pData = NULL;
		m_pObjRef = NULL;
	}

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::_Init_AsCharacter(void)
{
	m_pData->m_nRaceID = INVALID_ID;
	m_pData->m_nPortraitID = -1;		/* 默认头像的值 */
	m_pData->m_strName = "";
	m_pData->m_strCountryTitle = "";	/* 当前国家称号 */
	m_pData->m_strGuildTitle = "";		/* 当前帮会称号 */
	m_pData->m_strTitle = "";			/* 当前玩法称号 */
	m_pData->m_strConsortName = "";
	m_pData->m_TitleType = INVALID_ID;
	m_pData->m_fHPPercent = 0.f;
	m_pData->m_fMPPercent = 0.f;
	m_pData->m_nHP = 0;
	m_pData->m_nMaxHP = 0;
	m_pData->m_nRage = 0;
	m_pData->m_nMaxRage = 0;
	m_pData->m_fMoveSpeed = -1.f;
	m_pData->m_nOwnerID = INVALID_ID;
	m_pData->m_nRelative = NPC_AI_TYPE_CANNOTATTACK;
	m_pData->m_nModelID = INVALID_ID;
	m_pData->m_nMountID = INVALID_ID;
	m_pData->m_nLevel = 0;
	m_pData->m_bFightState = FALSE;
	m_pData->m_nStealthLevel = 0;
	m_pData->m_bSit = FALSE;
	m_pData->m_nAIType = 0;
	m_pData->m_nCountry = INVALID_ID;
	m_pData->m_nAttachID = INVALID_ID;
	m_pData->m_nGuild = INVALID_ID;
	m_pData->m_nGuildPosition = INVALID_ID;
	m_pData->m_fSpeedRate = 1.f;
	m_pData->m_nTargetId = INVALID_ID;
	m_pData->m_bVisibleState = TRUE;
	m_pData->m_fDir = 0.f;
	m_pData->m_nMoveLogicMode = MOVE_MODE_RUN;
	m_pData->m_nMoveActionMode = MOVE_MODE_RUN;
	m_pData->m_bAttachSetFlag = FALSE;
	m_pData->m_bLimitMove = FALSE;
	m_pData->m_bLimitMove_2 = FALSE;
	m_pData->m_bCanActionFlag1 = TRUE;
	m_pData->m_bCanActionFlag2 = TRUE;
	m_pData->m_nControlState = 0;
	m_pData->m_bBusState = FALSE;
	m_pData->m_fCharScale = 1.f;
	m_pData->m_nDefaultSkill = INVALID_ID;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::_Init_AsNPC(void)
{
	((SDataNPC *) m_pData)->m_nWeaponID = INVALID_ID;

	for(int32 i = 0; i < DEF_BUS_MAX_PASSENGER_COUNT; ++i)
	{
		((SDataNPC *) m_pData)->m_nAttachMemberID[i] = INVALID_ID;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::_Init_AsPlayerOther(void)
{
	((SDataPlayerOther *) m_pData)->m_nProfession = INVALID_ID;
	((SDataPlayerOther *) m_pData)->m_nHairMeshID = INVALID_ID;

	/*
	 * ((SDataPlayerOther*)m_pData)->m_uHairColor = 0xFFFFFFFF;
	 */
	((SDataPlayerOther *) m_pData)->m_nFaceMeshID = INVALID_ID;
	((SDataPlayerOther *) m_pData)->m_nEquipVer = 0;

	for(int32 i = 0; i < HEQUIP_NUMBER; i++)
	{
		((SDataPlayerOther *) m_pData)->m_nEquipmentID[i] = INVALID_ID;
		((SDataPlayerOther *) m_pData)->m_nEquipmentGemID[i] = INVALID_ID;
	}

	for(int32 j = 0; j < MAX_EQUIP_SUIT_NUM; j++)
	{
		((SDataPlayerOther *) m_pData)->m_oChangeSuit[j].Clear();
	}
	((SDataPlayerOther *) m_pData)->m_bShowFashion = TRUE;

	((SDataPlayerOther *) m_pData)->m_nCurTitleIndex = INVALID_ID;
	((SDataPlayerOther *) m_pData)->m_bIsInStall = FALSE;
	((SDataPlayerOther *) m_pData)->m_strStallName = "";
	((SDataPlayerOther *) m_pData)->m_nFamily = INVALID_ID;
	((SDataPlayerOther *) m_pData)->m_nTeamID = INVALID_ID;
	((SDataPlayerOther *) m_pData)->m_nPKValue = 0;
	((SDataPlayerOther *) m_pData)->m_strProvince = "";
	((SDataPlayerOther *) m_pData)->m_strZone = "";
	((SDataPlayerOther *) m_pData)->m_strGuildName = "";
	((SDataPlayerOther *) m_pData)->m_strFamilyName = "";
	((SDataPlayerOther *) m_pData)->m_NameColor = 0;
	((SDataPlayerOther *) m_pData)->m_nMountStrApt = 0;
	((SDataPlayerOther *) m_pData)->m_nMountDexApt = 0;
	((SDataPlayerOther *) m_pData)->m_nMountIntApt = 0;
	((SDataPlayerOther *) m_pData)->m_nMountConApt = 0;
	((SDataPlayerOther *) m_pData)->m_nMountEra = 0;
	((SDataPlayerOther *) m_pData)->m_nCurSuitId = 0;
	((SDataPlayerOther *) m_pData)->m_nCurEquipSign = 0;
	((SDataPlayerOther *) m_pData)->m_nCurStarSign = 0;
	((SDataPlayerOther *) m_pData)->m_nCurSuitSign = 0;
	((SDataPlayerOther *) m_pData)->nLeftWeaponVisual = 0;
	((SDataPlayerOther *) m_pData)->nRighttWeaponVisual = 0;
	((SDataPlayerOther *) m_pData)->nShoulderVisual = 0;
	((SDataPlayerOther *) m_pData)->nHeadVisual = 0;
	((SDataPlayerOther *) m_pData)->nKillCount = 0;
	((SDataPlayerOther *) m_pData)->m_StallMoneyType = 0;
	((SDataPlayerOther *) m_pData)->m_bIsHideName = FALSE;
	((SDataPlayerOther *) m_pData)->m_uInherenceExp = 0;
	((SDataPlayerOther *) m_pData)->m_uInherenceLevel = 0;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::_Init_AsPlayerMySelf(void)
{
	((SDataPlayerMyself *) m_pData)->m_nMP = 0;
	((SDataPlayerMyself *) m_pData)->m_nExp = -1;

	for(int32 i = 0; i < PLAYER_COIN_NUM; ++i)
	{
		((SDataPlayerMyself *) m_pData)->m_nMoney[i] = -1;
	}

	((SDataPlayerMyself *) m_pData)->m_nStrikePoint = 0;
	((SDataPlayerMyself *) m_pData)->m_nVigor = 0;
	((SDataPlayerMyself *) m_pData)->m_nMaxVigor = 0;
	((SDataPlayerMyself *) m_pData)->m_nRegeneRate = 0;
	((SDataPlayerMyself *) m_pData)->m_nEnergy = 0;
	((SDataPlayerMyself *) m_pData)->m_nMaxEnergy = 0;
	((SDataPlayerMyself *) m_pData)->m_nGoodBadValue = 0;
	((SDataPlayerMyself *) m_pData)->m_guidCurrentPet.Reset();
	((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_1 = 0;
	((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_2 = 0;
	((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_3 = 0;
	((SDataPlayerMyself *) m_pData)->m_nSkillPoint = 0;
	((SDataPlayerMyself *) m_pData)->m_nSTR = 0;
	((SDataPlayerMyself *) m_pData)->m_nCON = 0;
	((SDataPlayerMyself *) m_pData)->m_nINT = 0;
	((SDataPlayerMyself *) m_pData)->m_nDEX = 0;
	((SDataPlayerMyself *) m_pData)->m_nPoint_Remain = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Near = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Near = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Far = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Far = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Magic = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Magic = 0;
	((SDataPlayerMyself *) m_pData)->m_nMaxMP = 0;
	((SDataPlayerMyself *) m_pData)->m_nHP_ReSpeed = 0;
	((SDataPlayerMyself *) m_pData)->m_nMP_ReSpeed = 0;
	((SDataPlayerMyself *) m_pData)->m_nHit = 0;
	((SDataPlayerMyself *) m_pData)->m_nMiss = 0;
	((SDataPlayerMyself *) m_pData)->m_nCritRate = 0;
	((SDataPlayerMyself *) m_pData)->m_nCritHurt = 0;
	((SDataPlayerMyself *) m_pData)->m_nAttackSpeed = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Cold = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Cold = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Fire = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Fire = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Light = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Light = 0;
	((SDataPlayerMyself *) m_pData)->m_nAtt_Posion = 0;
	((SDataPlayerMyself *) m_pData)->m_nDef_Posion = 0;
	((SDataPlayerMyself *) m_pData)->m_nNear_Reduce = 0;
	((SDataPlayerMyself *) m_pData)->m_nFar_Reduce = 0;
	((SDataPlayerMyself *) m_pData)->m_nMagic_Reduce = 0;;
	((SDataPlayerMyself *) m_pData)->m_nDread_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nComa_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nHush_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nUnarm_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nAttackSpeed_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nSkillSpeed_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nMoveReduce_Resist = 0;
	((SDataPlayerMyself *) m_pData)->m_nPerCon = 0;
	((SDataPlayerMyself *) m_pData)->m_nHonor = 0;
	((SDataPlayerMyself *) m_pData)->m_RongYu = 0;
	((SDataPlayerMyself *) m_pData)->m_ShengWang = 0;
	((SDataPlayerMyself *) m_pData)->m_WenCai = 0;
	((SDataPlayerMyself *) m_pData)->m_nHot = 0;
	((SDataPlayerMyself *) m_pData)->m_uTiredTime = 0;
	((SDataPlayerMyself *) m_pData)->m_nBattleHonour = 0;
	((SDataPlayerMyself *) m_pData)->m_PVP2V2Level = 0;
	((SDataPlayerMyself *) m_pData)->m_PVP2V2Mark = 0;
	((SDataPlayerMyself *) m_pData)->m_PVP2V2Mark_WeekTotal = 0;
	((SDataPlayerMyself *) m_pData)->m_nMerit = 0;
    
    ( ( SDataPlayerMyself *) m_pData)->m_uiDefendRemainPoints = 0;
}

/*
 =======================================================================================================================
    ;
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_RaceID(int32 nRaceID)
{
	if(!m_pData)
	{
		return;
	}

	if(!m_pObjRef)
	{
		return;
	}

	m_pData->m_nRaceID = nRaceID;
	m_pObjRef->DoDataEvent_DataID();


	/* 根据RaceID重新刷新名字 */
	Set_AIType(Get_AIType());
	Set_Name(Get_Name());

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PortraitID(int32 nPortraitID)
{
	if(nPortraitID < 0) return;

	if(m_pData->m_nPortraitID != nPortraitID)
	{
		m_pData->m_nPortraitID = nPortraitID;
	}

	/* 通知渲染层 */
	m_pObjRef->OnDataChanged_FaceImage();

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Name(LPCTSTR szName)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Country(int32 country)
{
	m_pData->m_nCountry = country;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_TargetId(int32 id)
{
	m_pData->m_nTargetId = id;

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CurTitle(LPCTSTR szTitle, int32 nType)
{
	switch(nType)
	{
	/* 国家称号 */
	case STitle::GUOJIA_TITLE:
		{
			if(0 != strcmp(szTitle, m_pData->m_strCountryTitle.c_str()))
				m_pData->m_strCountryTitle = szTitle;
			else
				return;
		}
		break;

	/* 帮派称号 */
	case STitle::BANGPAI_TITLE:
		{
			if(0 != strcmp(szTitle, m_pData->m_strGuildTitle.c_str()))
				m_pData->m_strGuildTitle = szTitle;
			else
				return;
		}
		break;

	/* 玩法称号 */
	case STitle::WANFA_TITLE:
		{
			if(0 != strcmp(szTitle, m_pData->m_strTitle.c_str()))
				m_pData->m_strTitle = szTitle;
			else
				return;
		}
		break;
	};

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
LPCTSTR KCharatcterBaseData::Get_CurTitle(int32 nType) const
{
	switch(nType)
	{
	/* 国家称号 */
	case STitle::GUOJIA_TITLE:	{ return m_pData->m_strCountryTitle.c_str(); }break;
	/* 帮派称号 */
	case STitle::BANGPAI_TITLE: { return m_pData->m_strGuildTitle.c_str(); }break;
	/* 玩法称号 */
	case STitle::WANFA_TITLE:	{ return m_pData->m_strTitle.c_str(); }break;
	};

	return "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CurTitleType(BYTE bTitleType)
{
	m_pData->m_TitleType = bTitleType;

	/*
	 * m_pObjRef->DoDataEvent_CurTitles();
	 */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HPPercent(FLOAT fPercent)
{
	if(NULL == m_pData || NULL == m_pObjRef) return;

	FLOAT	fOldHPPercent = m_pData->m_fHPPercent;

	m_pData->m_fHPPercent = fPercent;

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MPPercent(FLOAT fPercent)
{
	m_pData->m_fMPPercent = fPercent;

}





/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AIType(int32 nAIType)
{
	
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Relative(int32 nRelative)
{
	m_pData->m_nRelative = nRelative;

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_ModelID(int32 nModelID)
{
	if (m_pData->m_nModelID != nModelID)
	{
		m_pData->m_nModelID = nModelID;
		m_pObjRef->DoDataEvent_ModelID();
	}	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MountID(int32 nMountID)
{
	if(nMountID != m_pData->m_nMountID)
	{
		m_pData->m_nMountID = nMountID;

		if(INVALID_ID != m_pObjRef->GetCurrCharModelID()) 
			m_pObjRef->DoDataEvent_MountID();

	}
}

/*
 =======================================================================================================================
    坐骑力量资质
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MountStrApt(int32 val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nMountStrApt = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MountStrApt()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nMountStrApt;
}

/*
 =======================================================================================================================
    坐骑敏捷资质
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MountDexApt(int32 val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nMountDexApt = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MountDexApt()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nMountDexApt;
}

/*
 =======================================================================================================================
    坐骑智力资质
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MountIntApt(int32 val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nMountIntApt = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MountIntApt()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nMountIntApt;
}

/*
 =======================================================================================================================
    坐骑体质资质
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MountConApt(int32 val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nMountConApt = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MountConApt()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nMountConApt;
}

/*
 =======================================================================================================================
    坐骑代数
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MountEra(int32 val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nMountEra = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MountEra()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nMountEra;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PerGuildCon(int32 nPerCon)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) (m_pData))->m_nPerCon = nPerCon;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_PerGuildCon()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_nPerCon;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PKValue(int32 value)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_PKValue()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nPKValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttachMemberID(int32 nIndex, int32 nObjID)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttachMemberID(int32 nIndex)
{
	if(nIndex >= 0 && nIndex < DEF_BUS_MAX_PASSENGER_COUNT)
	{
		return((SDataNPC *) m_pData)->m_nAttachMemberID[nIndex];
	}

	return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttachID(int32 nID)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttachID()
{
	if(m_pData)
	{
		return m_pData->m_nAttachID;
	}

	return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_VisibleState(BOOL bVisible)
{
	
}


BOOL KCharatcterBaseData::Get_VisibleState()
{
	if(m_pData)
	{
		return m_pData->m_bVisibleState;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Dir(FLOAT fDir)
{
	if(m_pData)
	{
		m_pData->m_fDir = fDir;
	}

	if(m_pObjRef)
	{
		m_pObjRef->DoDataEvent_Dir();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT KCharatcterBaseData::Get_Dir()
{
	if(m_pData)
	{
		return m_pData->m_fDir;
	}

	return 0.f;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_ControlState(int32 nState)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_ControlState()
{
	if(m_pData && m_pObjRef)
	{
		return m_pData->m_nControlState;
	}

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Honor()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) (m_pData))->m_nHonor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Honor(int32 nHonor)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) (m_pData))->m_nHonor = nHonor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Level(int32 nLevel)
{
	KYLIN_TRY


	if(m_pData) m_pData->m_nLevel = nLevel;

	KYLIN_CATCH("Data Set_Level 1")

	KYLIN_TRY
	m_pObjRef->DoDataEvent_Level();
	KYLIN_CATCH("Data Set_Level 2")

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_StealthLevel(int32 nStealthLevel)
{
	if(m_pData && m_pData->m_nStealthLevel != nStealthLevel)
	{
		m_pData->m_nStealthLevel = nStealthLevel;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MoveSpeed(FLOAT fSpeed)
{
	if(!m_pData) return;

	const FLOAT fBaseMoveSpeed = 3.5f;
	BOOL		bChanged = abs(fSpeed - m_pData->m_fMoveSpeed) > 0.2f ? TRUE : FALSE;

	if(bChanged)
	{	/* 速度有了明显的变化，需要改变其频率 */
	}

	m_pData->m_fMoveSpeed = fSpeed;
	m_pData->m_fSpeedRate = fSpeed / fBaseMoveSpeed;
	m_pObjRef->DoDataEvent_MoveSpeed();

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MoveLogicMode(int32 nMoveMode)
{
	if(m_pData)
	{
		m_pData->m_nMoveLogicMode = nMoveMode;
	}
}

void KCharatcterBaseData::Set_MoveActionMode(int32 nMoveMode)
{
	if(m_pData)
	{
		m_pData->m_nMoveActionMode = nMoveMode;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT KCharatcterBaseData::Get_SpeedRate(void) const
{
	if(m_pData) return m_pData->m_fSpeedRate;

	return 0.0f;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Sit(BOOL bSit)
{
	if(m_pData && m_pData->m_bSit != bSit)
	{
		m_pData->m_bSit = bSit;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::GetProfession(void) const
{
	if(m_pObjRef->GetCharacterType() == CHAR_BASE_TYPE_NPC) return INVALID_ID;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nProfession;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::SetProfession(int32 nProfession)
{
	if(CHAR_BASE_TYPE_NPC == m_pObjRef->GetCharacterType()) return;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	BOOL	bReset = (((SDataPlayerOther *) m_pData)->m_nProfession != nProfession);

	
	((SDataPlayerOther *) m_pData)->m_nProfession = nProfession;

}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Guild(void) const
{
	return m_pData->m_nGuild;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Guild(int32 nGuild, BOOL bMySelf)
{
	m_pData->m_nGuild = nGuild;
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *KCharatcterBaseData::Get_GuildName() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_strGuildName.c_str();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_GuildName(const char *pName)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_strGuildName = pName;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *KCharatcterBaseData::Get_FamilyName() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_strFamilyName.c_str();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_FamilyName(const char *pName)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_strFamilyName = pName;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *KCharatcterBaseData::Get_ConsortName() const
{
	return m_pData->m_strConsortName.c_str();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_ConsortName(const char *pName)
{
	m_pData->m_strConsortName = pName;
}

/*
 =======================================================================================================================
    帮会职位
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_GuildPosition(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerMyself *) m_pData)->m_nGuildPosition;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_GuildPosition(int32 nGuildPosition)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerMyself *) m_pData)->m_nGuildPosition = nGuildPosition;
}

/*
 =======================================================================================================================
    帮会家族id
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Family(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_nFamily;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Family(int32 nFamily, BOOL bMySelf)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nFamily = nFamily;

	
}

/*
 =======================================================================================================================
    玩家特殊时候名字颜色
 =======================================================================================================================
 */
BYTE KCharatcterBaseData::GetNameColor() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_NameColor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::SetNameColor(BYTE color)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_NameColor = color;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_TeamID(void) const
{
	return m_pData->m_nTeamID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_TeamID(int32 nTeamID)
{
	m_pData->m_nTeamID = nTeamID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_HairMesh(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_nHairMeshID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HairMesh(int32 nHairMesh)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	if(((SDataPlayerOther *) m_pData)->m_nHairMeshID != nHairMesh)
	{
		((SDataPlayerOther *) m_pData)->m_nHairMeshID = nHairMesh;
		m_pObjRef->OnDataChanged_HairMesh();
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 KCharatcterBaseData::Get_HairColor(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_uHairColor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HairColor(uint32 uHairColor)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_FaceMesh(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_nFaceMeshID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_FaceMesh(int32 nFaceMesh)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	if(((SDataPlayerOther *) m_pData)->m_nFaceMeshID != nFaceMesh)
	{
		((SDataPlayerOther *) m_pData)->m_nFaceMeshID = nFaceMesh;
		m_pObjRef->OnDataChanged_FaceMesh();
	}

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_EquipVer(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_nEquipVer;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipVer(int32 nEquipVer)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	BOOL	bNeedUpdate = ((SDataPlayerOther *) m_pData)->m_nEquipVer != nEquipVer;
	((SDataPlayerOther *) m_pData)->m_nEquipVer = nEquipVer;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Equip(PLAYER_EQUIP point) const
{
	if(NULL == m_pData)
		return INVALID_ID;

	if (point >= 0 && point < HEQUIP_NUMBER)
	{
		return ((SDataPlayerOther *) m_pData)->m_nEquipmentID[point];
	}
	return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Equip(PLAYER_EQUIP point, int32 nID, BOOL bUpdateShow)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	KLAssert(point >= 0 && point < HEQUIP_NUMBER);

	if(!m_pData || !m_pObjRef) return;

	/* 判断当前装备是否和要设置的一样 */
	if((((SDataPlayerOther *) m_pData)->m_nEquipmentID[point] != nID) || bUpdateShow)
	{
		((SDataPlayerOther *) m_pData)->m_nEquipmentID[point] = nID;

		KYLIN_TRY

		/* 通知角色层，更改外表 */
		if(HEQUIP_HEAD != point) 
			m_pObjRef->DoDataEvent_Equip(point);

		KYLIN_CATCH("Set_Equip *") char szTmp[32] = { 0 };

		_snprintf(szTmp, 32, "Set_Equip %d=%d", (int32) point, nID);

		
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_SUIT_SETTING &KCharatcterBaseData::Get_EquipSuit(int32 suitIdx) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	KLAssert(suitIdx >= 0 && suitIdx < MAX_EQUIP_SUIT_NUM);

	return((SDataPlayerOther *) m_pData)->m_oChangeSuit[suitIdx];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipSuit(int32 suitIdx, _SUIT_SETTING &pSuit)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	KLAssert(suitIdx >= 0 && suitIdx < MAX_EQUIP_SUIT_NUM);

	memcpy((void *) &((SDataPlayerOther *) m_pData)->m_oChangeSuit[suitIdx], (void *) &pSuit, sizeof(_SUIT_SETTING));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_EquipSuitId() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nCurSuitId;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipSuitId(int32 suitIdx)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_nCurSuitId = suitIdx;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_EquipSignId() const
{
	if(NULL == m_pData) return INVALID_ID;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nCurEquipSign;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipSignId(int32 signId, BOOL bUpdate)
{
	if(NULL == m_pData || NULL == m_pObjRef) return;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	if((((SDataPlayerOther *) m_pData)->m_nCurEquipSign != signId) || bUpdate)
	{
		((SDataPlayerOther *) m_pData)->m_nCurEquipSign = signId;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_EquipStarId() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nCurStarSign;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipStarId(int32 signId, BOOL bUpdate)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	if((((SDataPlayerOther *) m_pData)->m_nCurStarSign != signId) || bUpdate)
	{
		((SDataPlayerOther *) m_pData)->m_nCurStarSign = signId;

	}
}

/*
 =======================================================================================================================
    套装特效
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_EquipSuitEffect() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nCurSuitSign;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipSuitEffect(int32 signId, BOOL bUpdate)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	if((((SDataPlayerOther *) m_pData)->m_nCurSuitSign != signId) || bUpdate)
	{
		((SDataPlayerOther *) m_pData)->m_nCurSuitSign = signId;
	}
}

/*
 =======================================================================================================================
    时装外形表示
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_LeftWeaponVisual() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->nLeftWeaponVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_LeftWeaponVisual(int32 nVisual)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->nLeftWeaponVisual = nVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_RightWeaponVisual() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->nRighttWeaponVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_RightWeaponVisual(int32 nVisual)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->nRighttWeaponVisual = nVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_ShouderVisual() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->nShoulderVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_ShouderVisual(int32 nVisual)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->nShoulderVisual = nVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_HeadVisual() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->nHeadVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HeadVisual(int32 nVisual)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->nHeadVisual = nVisual;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MonstWeapon(void) const
{
	/* 如果是怪 */
	if(CHAR_BASE_TYPE_NPC == m_pObjRef->GetCharacterType())
	{
		return((SDataNPC *) m_pData)->m_nWeaponID;
	}

	return INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MonstWeapon(int32 nID)
{
	/* 先判断是否为怪 */
	if(CHAR_BASE_TYPE_NPC == m_pObjRef->GetCharacterType())
	{
		if(nID != ((SDataNPC *) m_pData)->m_nWeaponID) ((SDataNPC *) m_pData)->m_nWeaponID = nID;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_EquipGem(PLAYER_EQUIP point) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	KLAssert(point >= 0 && point < HEQUIP_NUMBER);

	/* 如果是玩家自己，存储物品实例 */
	return((SDataPlayerOther *) m_pData)->m_nEquipmentGemID[point];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_EquipGem(PLAYER_EQUIP point, int32 nID, BOOL bUpdateShow)
{
	if(NULL == m_pData || NULL == m_pObjRef) return;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	KLAssert(point >= 0 && point < HEQUIP_NUMBER);

	if(((SDataPlayerOther *) m_pData)->m_nEquipmentGemID[point] != nID || bUpdateShow)
	{
		((SDataPlayerOther *) m_pData)->m_nEquipmentGemID[point] = nID;

		/* 通知角色层，更改外表 */
		m_pObjRef->DoDataEvent_Equip(point);

		
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_KillCount(void)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->nKillCount;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_KillCount(int32 val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->nKillCount = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::Get_BusState()
{
	return m_pData->m_bBusState;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_BusState(BOOL bEnable)
{
	if( NULL == m_pData )
		return ;

	m_pData->m_bBusState = bEnable;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_CurTitleIndex() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_nCurTitleIndex;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CurTitleIndex(int32 index)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	KLAssert(index >= 0 && index < MAX_TITLE_SIZE);
	((SDataPlayerOther *) m_pData)->m_nCurTitleIndex = index;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::Get_FashionIsShow() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_bShowFashion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_FashionShow(BOOL bShow, BOOL bUIUpdate)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	if(((SDataPlayerOther *) m_pData)->m_bShowFashion != bShow)
	{
		((SDataPlayerOther *) m_pData)->m_bShowFashion = bShow;
		
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_HP(void) const
{
	return m_pData->m_nHP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HP(int32 nHP)
{
	if(m_pData && m_pObjRef)
	{
		m_pData->m_nHP = nHP;
	}

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MP(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MP(int32 nMP)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMP = nMP;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int64 KCharatcterBaseData::Get_Exp(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nExp;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Exp(int64 nExp)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	int32 nLevel = Get_Level();

	if(((SDataPlayerMyself *) m_pData)->m_nExp != -1)
	{
		/* 经验值头顶冒字 */

		/*计算增加的经验
		  按照此计算方法，当使用gm命令直接进行升级后，第一次增加经验时将会
		  把相差级别的经验值进行累加。
		*/
		int64 iAddExp = nExp - ((SDataPlayerMyself *) m_pData)->m_nExp;
		int32 iLastLevelExp = nLevel;

		

		
	}

	/* 判断是否要给出手动升级提示 */

	/* 等级要大于10 */
	if(nLevel >= 10)
	{
		CheckLevelUpExp(nExp, nLevel);
	}
	((SDataPlayerMyself *) m_pData)->m_nExp = nExp;


}

/*
 =======================================================================================================================
    判断该级升级经验
 =======================================================================================================================
 */
void KCharatcterBaseData::CheckLevelUpExp(int64 nExp, int32 nLevel)
{
	BOOL	isUiShow = FALSE;

	/* 判断该级升级经验 */
	int64		nMaxExp = Get_MaxExp(nLevel);

	/* 检测当前级别 */
	isUiShow = (nExp > nMaxExp) && (((SDataPlayerMyself *) m_pData)->m_nExp < nMaxExp);
	if(!isUiShow && ((SDataPlayerMyself *) m_pData)->m_nExp > nMaxExp)
	{
		/* 判断设置的经验 > 当前经验值 + 每级升级经验 */
		int64 nMaxExp1 = Get_MaxExp(nLevel + 1);
		int64 nMaxExp2 = Get_MaxExp(nLevel + 2);
		int64 nMaxExp3 = Get_MaxExp(nLevel + 3);
		int64 nMaxExp4 = Get_MaxExp(nLevel + 4);

		/* 1 */
		isUiShow = (nExp - nMaxExp > nMaxExp1) && (((SDataPlayerMyself *) m_pData)->m_nExp < nMaxExp + nMaxExp1);

		/* 2 */
		if(!isUiShow)
		{
			isUiShow = (nExp - nMaxExp - nMaxExp1 > nMaxExp2)
		&&	(((SDataPlayerMyself *) m_pData)->m_nExp < nMaxExp + nMaxExp1 + nMaxExp2);
		}

		/* 3 */
		if(!isUiShow)
		{
			isUiShow = (nExp - nMaxExp - nMaxExp1 - nMaxExp2 > nMaxExp3)
		&&	(((SDataPlayerMyself *) m_pData)->m_nExp < nMaxExp + nMaxExp2 + nMaxExp3);
		}

		/* 4 */
		if(!isUiShow)
		{
			isUiShow = (nExp - nMaxExp - nMaxExp1 - nMaxExp2 - nMaxExp3 > nMaxExp4)
		&&	(((SDataPlayerMyself *) m_pData)->m_nExp < nMaxExp + nMaxExp2 + nMaxExp3 + nMaxExp4);
		}
	}

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int64 KCharatcterBaseData::Get_MaxExp(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int64 KCharatcterBaseData::Get_MaxExp(int32 nLevel) const
{
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int64 KCharatcterBaseData::Get_Money(int32 T) const
{
	if(T < CU_SILLER || T > CU_BINDGOLD) return 0;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMoney[T];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Money(int64 nMoney, int32 T)
{
	if(NULL == m_pData) return;
	if(T < CU_SILLER || T > CU_BINDGOLD) return;

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	int64	nPreMoney = Get_Money(T);	// 获取当前拥有的数量
	int64	nAddtoMoney = nMoney;

	if(nPreMoney >= 0) nAddtoMoney = nMoney - nPreMoney;
	((SDataPlayerMyself *) m_pData)->m_nMoney[T] = nMoney;

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int64 KCharatcterBaseData::Get_SliverMoney() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	SDataPlayerMyself *p = ((SDataPlayerMyself *) m_pData);

	if(p)
	{
		return p->m_nMoney[CU_SILLER] + p->m_nMoney[CU_BINDSILLER];
	}

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int64 KCharatcterBaseData::Get_GoldMoney() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	SDataPlayerMyself *p = ((SDataPlayerMyself *) m_pData);

	if(p)
	{
		return p->m_nMoney[CU_GOLD] + p->m_nMoney[CU_BINDGOLD];
	}

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Silver_Model(SILLER_MODE m)
{
	if(m < SILLER_CARD || m > SILLER_CASH)
	{
		return;
	}

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Gold_Model(GOLD_MODE m)
{
	if(m < GOLD_CARD || m > GOLD_CASH)
	{
		return;
	}

	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

}





/*
 =======================================================================================================================
 =======================================================================================================================
 */
const SHorseGuid&KCharatcterBaseData::Get_CurrentPetGUID(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_guidCurrentPet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CurrentPetGUID(SHorseGuid guid)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Rage(void) const
{
	return m_pData->m_nRage;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Rage(int32 nRage)
{
	if(m_pData)
	{
		m_pData->m_nRage = nRage;
	}

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MaxRage(void) const
{
	return m_pData->m_nMaxRage;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MaxRage(int32 nMaxRage)
{
	if(m_pData)
	{
		m_pData->m_nMaxRage = nMaxRage;
	}

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_RageRespeed(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nRage_Respeed;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_RageRespeed(int32 nRageRespeed)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nRage_Respeed = nRageRespeed;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_NearReduce(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nNear_Reduce;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_NearReduce(int32 nNearReduce)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nNear_Reduce = nNearReduce;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_FarReduce(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nFar_Reduce;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_FarReduce(int32 nFarReduce)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nFar_Reduce = nFarReduce;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MagicReduce(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMagic_Reduce;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MagicReduce(int32 nMagicReduce)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMagic_Reduce = nMagicReduce;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DreadResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDread_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DreadResist(int32 nDreadResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDread_Resist = nDreadResist;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_ComaResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nComa_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_ComaResist(int32 nComaResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nComa_Resist = nComaResist;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_HushResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nHush_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HushResist(int32 nHushResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nHush_Resist = nHushResist;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_UnarmResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nUnarm_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_UnarmResist(int32 nUnarmResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nUnarm_Resist = nUnarmResist;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttackSpeedResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAttackSpeed_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttackSpeedResist(int32 nAttackSpeedResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAttackSpeed_Resist = nAttackSpeedResist;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_SkillSpeedResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nSkillSpeed_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_SkillSpeedResist(int32 nSkillSpeedResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nSkillSpeed_Resist = nSkillSpeedResist;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MoveReduceResist(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMoveReduce_Resist;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MoveReduceResist(int32 nMoveReduceResist)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMoveReduce_Resist = nMoveReduceResist;

}

/*
 =======================================================================================================================
    魅力
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Hot(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nHot;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Hot(int32 nHot)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nHot = nHot;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_StrikePoint(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nStrikePoint;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_StrikePoint(int32 nStrikePoint)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nStrikePoint = nStrikePoint;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Vigor(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nVigor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Vigor(int32 nVigor)
{
	}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MaxVigor(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMaxVigor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MaxVigor(int32 nMaxVigor)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMaxVigor = nMaxVigor;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_RegeneRate(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nRegeneRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_RegeneRate(int32 regeneRate)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nRegeneRate = regeneRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Energy(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nEnergy;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Energy(int32 nEnergy)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MaxEnergy(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMaxEnergy;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MaxEnergy(int32 nMaxEnergy)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMaxEnergy = nMaxEnergy;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_GoodBadValue(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nGoodBadValue;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_GoodBadValue(int32 nValue)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nGoodBadValue = nValue;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_STR(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nSTR;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_STR(int32 nSTR)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nSTR = nSTR;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UNIT_STR, "player" );
	 */
}

/*
 =======================================================================================================================
    int32 KCharatcterBaseData::Get_SPR(void) const { MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    return ((SDataPlayerMyself*)m_pData)->m_nSPR;
    } ;
    void KCharatcterBaseData::Set_SPR(int32 nSPR) { MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ((SDataPlayerMyself*)m_pData)->m_nSPR = nSPR;
    COMMAND_SYS_PTR->AddCommand( GCD_UNIT_SPR, "player" );
    }
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_CON(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nCON;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CON(int32 nCON)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nCON = nCON;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_INT(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nINT;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_INT(int32 nINT)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nINT = nINT;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UNIT_INT, "player" );
	 */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DEX(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDEX;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DEX(int32 nDEX)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDEX = nDEX;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UNIT_DEX, "player" );
	 */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_PointRemain(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nPoint_Remain;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PointRemain(int32 nPoint)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nPoint_Remain = nPoint;
}

/*
 =======================================================================================================================
    int32 KCharatcterBaseData::Get_AttPhysics(void) const { MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    return ((SDataPlayerMyself*)m_pData)->m_nAtt_Physics;
    } void KCharatcterBaseData::Set_AttPhysics(int32 nAttPhysics) { MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ((SDataPlayerMyself*)m_pData)->m_nAtt_Physics = nAttPhysics;
    COMMAND_SYS_PTR->AddCommand( GCD_UNIT_ATT_PHYSICS, "player" );
    }
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttMagic(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Magic;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttMagic(int32 nAttMagic)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Magic = nAttMagic;
}

/*
 =======================================================================================================================
    近攻
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttNear(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Near;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttNear(int32 nAtt)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Near = nAtt;


}

/*
 =======================================================================================================================
    近防
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefNear(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Near;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefNear(int32 nDef)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Near = nDef;


}

/*
 =======================================================================================================================
    远攻
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttFar(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Far;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttFar(int32 nAtt)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Far = nAtt;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UNIT_ATT_FAR, "player" );
	 */
}

/*
 =======================================================================================================================
    远防
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefFar(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Far;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefFar(int32 nDef)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Far = nDef;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UNIT_DEF_FAR, "player" );
	 */
}

/*
 =======================================================================================================================
    int32 KCharatcterBaseData::Get_DefPhysics(void) const { MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    return ((SDataPlayerMyself*)m_pData)->m_nDef_Physics;
    } void KCharatcterBaseData::Set_DefPhysics(int32 nDefPhysics) { MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ((SDataPlayerMyself*)m_pData)->m_nDef_Physics = nDefPhysics;
    COMMAND_SYS_PTR->AddCommand( GCD_UNIT_DEF_PHYSICS, "player" );
    }
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefMagic(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Magic;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefMagic(int32 nDefMagic)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Magic = nDefMagic;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UNIT_DEF_MAGIC, "player" );
	 */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MaxHP(void) const
{
	return m_pData->m_nMaxHP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MaxHP(int32 nMaxHP)
{
	if(m_pData)
	{
		m_pData->m_nMaxHP = nMaxHP;
	}

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MaxMP(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMaxMP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MaxMP(int32 nMaxMP)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMaxMP = nMaxMP;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_HPRespeed(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nHP_ReSpeed;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_HPRespeed(int32 nHPRespeed)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nHP_ReSpeed = nHPRespeed;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_MPRespeed(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMP_ReSpeed;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_MPRespeed(int32 nMPRespeed)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMP_ReSpeed = nMPRespeed;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Toughness(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nToughness;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Toughness(int32 nToughness)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nToughness = nToughness;


}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Hit(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nHit;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Hit(int32 nHit)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nHit = nHit;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_Miss(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nMiss;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Miss(int32 nMiss)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nMiss = nMiss;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_CritRate(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nCritRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CritRate(int32 nCritRate)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nCritRate = nCritRate;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_CritHurt(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nCritHurt;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CritHurt(int32 nCritHurt)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nCritHurt = nCritHurt;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttackSpeed(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAttackSpeed;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttackSpeed(int32 nSpeed)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAttackSpeed = nSpeed;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttCold(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Cold;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttCold(int32 nAttCold)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Cold = nAttCold;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefCold(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Cold;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefCold(int32 nDefCold)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Cold = nDefCold;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttFire(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Fire;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttFire(int32 nAttFire)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Fire = nAttFire;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefFire(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Fire;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefFire(int32 nDefFire)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Fire = nDefFire;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttLight(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Light;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_RongYu(int32 chaotingShengWang)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_RongYu = chaotingShengWang;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_RongYu()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_RongYu;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_WenCai(int32 WenCai)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_WenCai = WenCai;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_WenCai()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_WenCai;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_ShengWang(int32 jiangHuShengWang)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_ShengWang = jiangHuShengWang;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_ShengWang()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_ShengWang;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttLight(int32 nAttLight)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Light = nAttLight;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefLight(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Light;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefLight(int32 nDefLight)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Light = nDefLight;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_AttPosion(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nAtt_Posion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_AttPosion(int32 nAttPosion)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nAtt_Posion = nAttPosion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_DefPosion(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return((SDataPlayerMyself *) m_pData)->m_nDef_Posion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_DefPosion(int32 nDefPosion)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nDef_Posion = nDefPosion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::IsLimitMove(void) const
{
	if(m_pData->m_bLimitMove)
	{
		return TRUE;
	}

	if(m_pData->m_bLimitMove_2)
	{
		return TRUE;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::SetLimitMove(BOOL bSet)
{
	m_pData->m_bLimitMove = bSet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::SetLimitMove2(BOOL bSet)
{
	m_pData->m_bLimitMove_2 = bSet;
}

/*
 =======================================================================================================================
    ;
    BOOL KCharatcterBaseData::IsLimitUseSkill(void) const ;
    { ;
    MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ;
    return ((SDataPlayerMyself*)m_pData)->m_bLimitUseSkill;
    } ;
    void KCharatcterBaseData::SetLimitUseSkill(BOOL bSet) ;
    { ;
    MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ;
    ((SDataPlayerMyself*)m_pData)->m_bLimitUseSkill = bSet;
    } ;
    BOOL KCharatcterBaseData::IsLimitHandle(void) const ;
    { ;
    MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ;
    return ((SDataPlayerMyself*)m_pData)->m_bLimitHandle;
    } ;
    void KCharatcterBaseData::SetLimitHandle(BOOL bSet) ;
    { ;
    MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
    ;
    ((SDataPlayerMyself*)m_pData)->m_bLimitHandle = bSet;
    }
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::IsHaveCanActionFlag1(void) const
{
	return m_pData->m_bCanActionFlag1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::SetCanActionFlag1(BOOL bSet)
{
	m_pData->m_bCanActionFlag1 = bSet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::IsHaveCanActionFlag2(void) const
{
	return m_pData->m_bCanActionFlag2;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::SetCanActionFlag2(BOOL bSet)
{
	m_pData->m_bCanActionFlag2 = bSet;
}

/*
 =======================================================================================================================
    是否已设置二级密码
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::Get_IsMinorPwdSetup(BOOL bOpenDlg) const
{
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_SetMinorPwdSetup(BOOL bSet)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

}

/*
 =======================================================================================================================
    是否已经解锁二级密码
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::Get_IsMinorPwdUnlocked(BOOL bOpenDlg) const
{
	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_SetMinorPwdUnlocked(BOOL bSet)
{
	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::Get_IsMaxErrorCount(BOOL bOpenDlg) const
{
	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_SetMaxErrorCount(BOOL bSet)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_SeriesPoint(int32 nSeriesID)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	int32 point = 0;

	switch(nSeriesID)
	{
	case COMMON_S1: point = (((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_1); break;
	case COMMON_S2: point = (((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_2); break;
	case COMMON_S3: point = (((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_3); break;
	default:		break;
	}

	return point;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_SeriesPoint(int32 nSeriesID, int32 nSeriesPoint)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	switch(nSeriesID)
	{
	case COMMON_S1:
		((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_1 = nSeriesPoint;

		/*
		 * COMMAND_SYS_PTR->AddCommand( GCD_UINT_SERIES_1, "player" );
		 */
		break;

	case COMMON_S2:
		((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_2 = nSeriesPoint;

		/*
		 * COMMAND_SYS_PTR->AddCommand( GCD_UINT_SERIES_2, "player" );
		 */
		break;

	case COMMON_S3:
		((SDataPlayerMyself *) m_pData)->m_nSeriesPoint_3 = nSeriesPoint;

		/*
		 * COMMAND_SYS_PTR->AddCommand( GCD_UINT_SERIES_3, "player" );
		 */
		break;

	default:
		break;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_CurrentSkillPoint()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);

	return(((SDataPlayerMyself *) m_pData)->m_nSkillPoint);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_CurrentSkillPoint(int32 nPoint)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nSkillPoint = nPoint;

	/*
	 * COMMAND_SYS_PTR->AddCommand( GCD_UINT_SKILLPOINT, "player" );
	 */
}





/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_TiredTime(uint32 value)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) (m_pData))->m_uTiredTime = value;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 KCharatcterBaseData::Get_TiredTime()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_uTiredTime;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_BankPetValidCt(BYTE val)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_byBankPetValidCt = val;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BYTE KCharatcterBaseData::Get_BankPetValidCt()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_byBankPetValidCt;
}


void KCharatcterBaseData::Set_BattleHonour(uint32 nHonour)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_nBattleHonour = nHonour;

}

uint32 KCharatcterBaseData::Get_BattleHonour()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_nBattleHonour;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PVP2V2Level(USHORT nLevel)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_PVP2V2Level = nLevel;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
USHORT KCharatcterBaseData::Get_PVP2V2Level()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_PVP2V2Level;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PVP2V2Mark(USHORT nMark)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_PVP2V2Mark = nMark;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
USHORT KCharatcterBaseData::Get_PVP2V2Mark()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_PVP2V2Mark;
}

/*
 更新节日积分
 */
void KCharatcterBaseData::Set_FeastScore( uint32 dwScore)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_dwFeastScore = dwScore;

}

/*
 获得节日积分
 */
uint32 KCharatcterBaseData::Get_FeastScore()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_dwFeastScore;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_PVP2V2Mark_WeekTotal(int32 nMark)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	((SDataPlayerMyself *) m_pData)->m_PVP2V2Mark_WeekTotal = nMark;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 KCharatcterBaseData::Get_PVP2V2Mark_WeekTotal()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	MUST_NOT_CHECK(CHAR_BASE_TYPE_OHTER);
	return((SDataPlayerMyself *) m_pData)->m_PVP2V2Mark_WeekTotal;
}

/*
 =======================================================================================================================
    获得当前摊位
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::Get_IsInStall(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_bIsInStall;
}

/*
 =======================================================================================================================
    设置摊位
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_IsInStall(BOOL bIsInStall)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_bIsInStall = bIsInStall;
}

/*
 =======================================================================================================================
    获得摊位名
 =======================================================================================================================
 */
LPCTSTR KCharatcterBaseData::Get_StallName(void) const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_strStallName.c_str();
}

/*
 =======================================================================================================================
    设置摊位名
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_StallName(LPCTSTR szName)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_strStallName = szName+1;
	
	char szTmp[2] = {0};
	szTmp[0] = szName[0];
	((SDataPlayerOther *) m_pData)->m_StallMoneyType = atoi(szTmp);
}

/*
 =======================================================================================================================
    设置摊位金钱模式
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_StallMoneyType(uchar nType)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_StallMoneyType = nType;
}

/*
 =======================================================================================================================
    获得摊位金钱模式
 =======================================================================================================================
 */
uchar KCharatcterBaseData::Get_StallMoneyType() const
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_StallMoneyType;
}

/*
 =======================================================================================================================
    天赋
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_InherenceExp(uint32 value)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	((SDataPlayerOther *) (m_pData))->m_uInherenceExp = value;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 KCharatcterBaseData::Get_InherenceExp(void)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_uInherenceExp;
}

void KCharatcterBaseData::Set_InherenceLevel(uint32 value)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	if (((SDataPlayerOther *) (m_pData))->m_uInherenceLevel != value)
	{
		((SDataPlayerOther *) (m_pData))->m_uInherenceLevel = value;
		
	}
}

uint32 KCharatcterBaseData::Get_InherenceLevel(void)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);

	return((SDataPlayerOther *) m_pData)->m_uInherenceLevel;
}

/*
 =======================================================================================================================
    战场积分 ;
    竞技场积分 ;
    竞技场等级
 =======================================================================================================================
 */
BOOL KCharatcterBaseData::IsDie(void) const
{
	BOOL	bDie = (Get_HPPercent() <= 0.f);

	/*
	 * if( bDie ) ;
	 * { ;
	 * // 清掉选择的主目标 ;
	 * if( m_pObjRef && m_pObjRef == OBJECT_MANAGER_PTR->GetMainTarget() ) ;
	 * { ;
	 * GAME_OPERATE_PTR->Object_SelectAsMainTarget(INVALID_ID, 0);
	 * } ;
	 * }
	 */
	return bDie;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
STRING KCharatcterBaseData::Get_Province()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_strProvince;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
STRING KCharatcterBaseData::Get_Zone()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return((SDataPlayerOther *) m_pData)->m_strZone;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Province(STRING province)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_strProvince = province;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void KCharatcterBaseData::Set_Zone(STRING Zone)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerOther *) m_pData)->m_strZone = Zone;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
String getCountryName(int32 nCountry)
{
	

	return "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
String getProfessionName(int32 nProfession)
{

	return "";
}

/*
=======================================================================================================================
设置蒙面模式
=======================================================================================================================
*/
void KCharatcterBaseData::SetHideName(BOOL isHide)
{
	//MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	if (m_pObjRef->GetCharacterType() == CHAR_BASE_TYPE_NPC)
	{
		return;
	}
	((SDataPlayerOther *) m_pData)->m_bIsHideName = isHide;
}

/*
=======================================================================================================================
获得蒙面模式
=======================================================================================================================
*/
BOOL KCharatcterBaseData::IsHideName() const
{
	if (m_pObjRef->GetCharacterType() == CHAR_BASE_TYPE_NPC)
	{
		return FALSE;
	}
	return((SDataPlayerOther *) m_pData)->m_bIsHideName;
}


/*
=======================================================================================================================
设置帮会功德值
=======================================================================================================================
*/
void KCharatcterBaseData::SetMerit(int32 nMerit)
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	((SDataPlayerMyself *) (m_pData))->m_nMerit = nMerit;
}

/*
=======================================================================================================================
获得帮会功德值
=======================================================================================================================
*/
int32 KCharatcterBaseData::GetMerit()
{
	MUST_NOT_CHECK(CHAR_BASE_TYPE_NPC);
	return ((SDataPlayerMyself *) (m_pData))->m_nMerit;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void KCharatcterBaseData::Set_CharScale(FLOAT fValue)
{
	if (NULL == m_pData || NULL == m_pObjRef)
		return;

	m_pData->m_fCharScale = fValue;
}

FLOAT KCharatcterBaseData::Get_CharScale()
{
	if (m_pData)
	{
		return m_pData->m_fCharScale;
	}
	return 1.f;	
}


int32 KCharatcterBaseData::Get_GetDefaultSkill()
{
	if (m_pData)
	{
		return m_pData->m_nDefaultSkill;
	}
	return INVALID_ID;	
}




void KCharatcterBaseData::Set_AttrGift(int32 nGiftId, int32 nlevel)
{
	
}



void KCharatcterBaseData::Set_BalanceGift(int32 nGiftId, int32 nlevel)
{
	
}



void KCharatcterBaseData::Set_SpecialBalanceGift(int32 nGiftId, int32 nLevel)
{
		
}

void KCharatcterBaseData::Set_DefendRemainPoints( uint32 uiPoints)
{
    MUST_NOT_CHECK( CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK( CHAR_BASE_TYPE_OHTER);

    ( ( SDataPlayerMyself *) m_pData)->m_uiDefendRemainPoints = uiPoints;
}

uint32 KCharatcterBaseData::Get_DefendRemainPoints()
{
    MUST_NOT_CHECK( CHAR_BASE_TYPE_NPC);
    MUST_NOT_CHECK( CHAR_BASE_TYPE_OHTER);

    return ( ( SDataPlayerMyself *) m_pData)->m_uiDefendRemainPoints;
}


