/*$T Common/StructPet.cpp GC 1.140 10/10/07 10:06:56 */

/* StructPet.cpp */
#include "stdafx.h"
#include "StructPet.h"

/*
 =======================================================================================================================
        _PET_DETAIL_PROPERTY ≥ËŒÔ Ù–‘
 =======================================================================================================================
 */
_PET_DETAIL_PROPERTY::_PET_DETAIL_PROPERTY(void)
{
	/*
	 * m_GUID.Reset();
	 */
	m_ObjID = INVALID_ID;
	m_nDataID = INVALID_ID;
	memset(m_szName, 0, sizeof(m_szName));
	m_nAIType = -1;

	/*
	 * m_SpouseGUID.Reset();
	 */
	m_nLevel = -1;
	m_nExp = -1;
	m_nHP = -1;
	m_nHPMax = -1;

	m_nLife = -1;
	m_byGeneration = 0;
	m_byHappiness = 0;

	m_nAtt_Near = -1;
	m_nDef_Near = -1;
	m_nAtt_Far = -1;
	m_nDef_Far = -1;

	/*
	 * m_nAtt_Physics = -1;
	 */
	m_nAtt_Magic = -1;

	/*
	 * m_nDef_Physics = -1;
	 */
	m_nDef_Magic = -1;

	m_nHit = -1;
	m_nMiss = -1;
	m_nCritical = -1;

	m_nModelID = -1;
	m_nMountID = -1;

	m_iStrengthPerception = -1;
	m_iSmartnessPerception = -1;
	m_iMindPerception = -1;

	/*
	 * m_SprPerception = -1;
	 */
	m_iConstitutionPerception = -1;

	m_Str = -1;
	m_Con = -1;
	m_Dex = -1;

	/*
	 * m_Spr = -1;
	 */
	m_Int = -1;
	m_GenGu = -1;

	m_nRemainPoint = -1;

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for(i = 0; i < MAX_PET_SKILL_COUNT; i++)
	{
		m_aSkill[i].m_nSkillID = INVALID_ID;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL _PET_DETAIL_PROPERTY::Init
(
	const _HORSE_DB			*pPetDB,
	ObjID_t				idObj,
	int32				nAtt_Near,
	int32				nDef_Near,
	int32				nAtt_Far,
	int32				nDef_Far,
	/* int32 nAtt_Physics, */int32	nAtt_Magic,
	/* int32 nDef_Physics, */int32	nDef_Magic,
	int32				nHit,
	int32				nMiss,
	int32				nCritical,
	int32				nModelID,
	int32				nMountID
)
{
	KCheck(pPetDB != NULL && "_PET_DETAIL_PROPERTY::InitFormDB");
	if(pPetDB == NULL) return FALSE;

	m_GUID = pPetDB->m_GUID;

	m_ObjID = idObj;
	m_nDataID = pPetDB->m_nDataID;
	strncpy(m_szName, pPetDB->m_szName, sizeof(m_szName) - 1);
	m_nAIType = pPetDB->m_AIType;
	m_nLevel = pPetDB->m_nLevel;
	m_nExp = pPetDB->m_nExp;
	m_byGeneration = pPetDB->m_byGeneration;
	m_byHappiness = pPetDB->m_byHappiness;

	m_nAtt_Near = nAtt_Near;
	m_nDef_Near = nDef_Near;
	m_nAtt_Far = nAtt_Far;
	m_nDef_Far = nDef_Far;

	m_nAtt_Magic = nAtt_Magic;
	m_nDef_Magic = nDef_Magic;

	m_nHit = nHit;
	m_nMiss = nMiss;
	m_nCritical = nCritical;

	m_nModelID = nModelID;
	m_nMountID = nMountID;

	m_iStrengthPerception = pPetDB->m_iStrengthPerception;
	m_iSmartnessPerception = pPetDB->m_iSmartnessPerception;
	m_iMindPerception = pPetDB->m_iMindPerception;
	m_iConstitutionPerception = pPetDB->m_iConstitutionPerception;

	m_Str = pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR];
	m_Con = pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON];
	m_Dex = pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX];
	m_Int = pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT];

	m_nRemainPoint = pPetDB->m_nRemainPoint;

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for(i = 0; i < MAX_PET_SKILL_COUNT; i++)
	{
		m_aSkill[i].m_nSkillID = pPetDB->m_SkillList[i].m_nSkillID;
	}

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _PET_DETAIL_PROPERTY::Clear(void)
{
	m_GUID.Reset();

	m_ObjID = INVALID_ID;
	m_nDataID = INVALID_ID;
	memset(m_szName, 0, sizeof(m_szName));
	m_nAIType = -1;
	m_SpouseGUID.Reset();
	m_nLevel = -1;
	m_nExp = -1;
	m_nHP = -1;
	m_nHPMax = -1;

	m_nLife = -1;
	m_byGeneration = 0;
	m_byHappiness = 0;

	m_nAtt_Near = -1;
	m_nDef_Near = -1;
	m_nAtt_Far = -1;
	m_nDef_Far = -1;

	/*
	 * m_nAtt_Physics = -1;
	 */
	m_nAtt_Magic = -1;

	/*
	 * m_nDef_Physics = -1;
	 */
	m_nDef_Magic = -1;

	m_nHit = -1;
	m_nMiss = -1;
	m_nCritical = -1;

	m_nModelID = -1;
	m_nMountID = -1;

	m_iStrengthPerception = -1;
	m_iSmartnessPerception = -1;
	m_iMindPerception = -1;
	m_iConstitutionPerception = -1;

	m_Str = -1;
	m_Con = -1;
	m_Dex = -1;

	/*
	 * m_Spr = -1;
	 */
	m_Int = -1;
	m_GenGu = -1;

	m_nRemainPoint = -1;

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for(i = 0; i < MAX_PET_SKILL_COUNT; i++)
	{
		m_aSkill[i].m_nSkillID = INVALID_ID;
	}
}

