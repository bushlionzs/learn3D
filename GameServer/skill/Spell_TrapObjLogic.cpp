/*$T MapServer/Server/Spell/SpecialObjLogic/SpecialObjLogic.cpp GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Spell_TrapObjLogic.h"
#include "Spell_EffectLogicManager.h"
#include "data/data_manager.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

SpecialObjectLogic const *ObjSpecial_GetLogic(SpecialCreature &rObj)
{
	__GUARD__ if(INVALID_ID == rObj.GetDataID())
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpecialObjData_T const	*pData = rObj.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ID_t	nLogicID = pData->GetLogicID();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(INVALID_ID == nLogicID)
	{
		return NULL;
	}

	return DataManager::GetSingletonPtr()->getSpecialObjectLogicById(nLogicID);
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 SpecialObjectLogic::GetDescriptorValueByIndex(SpecialCreature &rThis, int32 nIdx) const
{
	__GUARD__ if(INVALID_ID == rThis.GetDataID())
	{
		KCheckEx
		(
			FALSE,
			"[SpecialObjLogic_T::GetDescriptorValueByIndex]: Can't find the specific data for this obj."
		);
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SpecialObjData_T const	*pData = rThis.GetDataRecord();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pData)
	{
		KCheckEx
		(
			FALSE,
			"[SpecialObjLogic_T::GetDescriptorValueByIndex]: Can't find the specific data for this obj."
		);
		return 0;
	}

	if(0 > nIdx || DESCRIPTOR_NUMBER <= nIdx)
	{
		KCheckEx(FALSE, "[SpecialObjLogic_T::GetDescriptorValueByIndex]: Illegal Index Found.");
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Descriptor const	*pDescriptor = pData->GetDescriptorByIndex(nIdx);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pDescriptor)
	{
		KCheckEx(FALSE, "[SpecialObjLogic_T::GetDescriptorValueByIndex]: Illegal Index Found.");
		return 0;
	}

	return pDescriptor->GetValueBySkillLevel(0);
	__UNGUARD__ return 0;
}
