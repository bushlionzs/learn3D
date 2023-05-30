#include "stdafx.h"
#include "HorseStruct.h"

_HORSE_ATTR_BACKUP::_HORSE_ATTR_BACKUP(void)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _HORSE_ATTR_BACKUP::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_bNameModified = FALSE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_bTitleModified = FALSE;
	m_CampData.Clear();
	m_nOwnerID = INVALID_ID;
	m_nAIType = -1;
	m_Level = -1;

	m_nDataID = INVALID_ID;
	m_nModelID = INVALID_ID;
	m_nMountID = INVALID_ID;

	m_GUID.Reset();
	m_byGeneration = 0;
	m_byHappiness = 0;

	m_nAtt_Near = -1;
	m_nAtt_Far = -1;

	m_nAtt_Magic = -1;
	m_nDef_Near = -1;
	m_nDef_Far = -1;

	m_nDef_Magic = -1;
	m_nHit = -1;
	m_nMiss = -1;

	m_nExp = -1;

	m_iStrengthPerception = -1;
	m_iSmartnessPerception = -1;
	m_iMindPerception = -1;
	m_iConstitutionPerception = -1;
	m_iPullulationRate = 0;

	m_iStrength = 0;
	m_iSmartness = 0;
	m_iMind = 0;
	m_iConstitution = 0;

	m_nRemainPoint = -1;
	__UNGUARD__
}
