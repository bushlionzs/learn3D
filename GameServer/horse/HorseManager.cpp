#include "stdafx.h"
#include "BaseTool.h"
#include "TabDefine.h"
#include "map/game_map.h"
#include "Horse.h"
#include "gameobject/ObjectManager.h"
#include "HorseManager.h"
#include "item/Item_Interface.h"
#include "gameobject/PlayerManager.h"
#include "server_settting.h"
#include "gameobject/Player.h"
#include "data/data_manager.h"

#define SECSIZE 64

/*
 =======================================================================================================================
 =======================================================================================================================
 */

HorseManager::HorseManager(void)
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
HorseManager::~HorseManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Horse *HorseManager::GetHorse(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Horse	*pHorse = (Horse *) (GetMap()->GetObjManager()->GetObj(idObj));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pHorse == NULL)
	{
		return NULL;
	}

	if(pHorse->GetObjType() != Object::OBJECT_CLASS_HORSE)
	{
		KCheck((pHorse->GetObjType() == Object::OBJECT_CLASS_HORSE) && "HorseManager::GetHorse");
		return NULL;
	}

	return pHorse;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::RemoveAllHorse(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ 
	GameMap	*pMap;
	Horse		*pHorse;
	uint32		i, uCount, uMaxCount, uLength;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMap = GetMap();
	uCount = 0;
	uMaxCount = GetCount();
	uLength = GetLength();

	for(i = 0; i < uLength; i++)
	{
		pHorse = (Horse *) (GetObjByIndex(0));
		if(pHorse != NULL)
		{
			pHorse->SetActiveFlag(FALSE);
			pHorse->Clear();
			pMap->DeleteObject(pHorse);
			uCount++;
			if(uCount >= uMaxCount) break;
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::RemoveHorse(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMap)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pHorse = pMap->GetHorseManager()->GetHorse(idObj);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pHorse->GetObjType() == Object::OBJECT_CLASS_HORSE && "HorseManager::RemoveHorse ObjType error");
		if(pHorse && pHorse->GetObjType() == Object::OBJECT_CLASS_HORSE)
		{
			pHorse->SetActiveFlag(FALSE);
			pHorse->Clear();
			pMap->DeleteObject(pHorse);
		}
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::CreateHorse(int32 nDataID, GLPos *pPos, ObjID_t &rPetID, GUID_t *pGUIDOwner, uint32 nOwnerCount)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GameMap	*pMap = GetMap();
	Horse		*pHorse = (Horse *) (pMap->NewObject(Object::OBJECT_CLASS_HORSE));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pHorse)
	{
		return FALSE;
	}

	rPetID = pHorse->GetID();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_ATTR	*pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(nDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPetAttr) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~*/
	_OBJ_HORSE_INIT initPet;
	/*~~~~~~~~~~~~~~~~~~~~*/

	initPet.m_Pos = *pPos;
	initPet.m_Dir = 0.f;
	initPet.m_eLogic = CHARACTER_LOGIC_IDLE;
	if(nOwnerCount > 0 && pGUIDOwner != NULL)
	{
		if(nOwnerCount > MAX_TEAM_MEMBER) nOwnerCount = MAX_TEAM_MEMBER;
		initPet.m_nOwnerCount = nOwnerCount;
		memcpy(initPet.m_aOwnerGUID, pGUIDOwner, sizeof(GUID_t) * nOwnerCount);
	}

	if(!InitHorseDB(&initPet.m_PetDB, nDataID)) return FALSE;

	initPet.m_GUID = INVALID_GUID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bResult = pHorse->Init(&initPet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult)
	{
		return FALSE;
	}

	pHorse->SetActiveFlag(TRUE);

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::CreateGUIDOfHorse(_HORSE_DB *pPetDB, ObjID_t idHuman, ObjID_t idPet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(idHuman != INVALID_ID && idPet != INVALID_ID && "HorseManager::CreateGUIDOfPet");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(idHuman == INVALID_ID || idPet == INVALID_ID)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~*/
	Player	*pPlayer;
	Horse	*pHorse;
	/*~~~~~~~~~~~~~*/

	pPlayer = GetMap()->GetPlayerManager()->GetPlayer(idHuman);
	pHorse = GetHorse(idPet);

	KCheck(pPlayer != NULL && pHorse != NULL && "HorseManager::CreateGUIDOfPet");
	if(pPlayer == NULL || pHorse == NULL)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_ATTR	*pHorseAttr = DataManager::GetSingletonPtr()->getHorseAttr(pHorse->GetDataID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == pHorseAttr) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	SHorseGuid	guidHorse;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	InitHorseGUID(guidHorse, pPlayer);

	pPetDB->m_GUID = guidHorse;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::MakeCapturePetAttrib(_HORSE_DB *pPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	CreateBHVClassOfHorse(*pPetDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::InitHorseDB(_HORSE_DB *pPetDB, int32 nDataID, BOOL bInitNewSkill)
{
	__GUARD__ if(pPetDB == NULL) return FALSE;

	pPetDB->Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_HORSE_ATTR	*pPetAttr = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDataID > 0)
	{
		pPetAttr = DataManager::GetSingletonPtr()->getHorseAttr(nDataID);
	}

	if(NULL == pPetAttr)
	{
		return FALSE;
	}

	if(nDataID != pPetAttr->m_nDataID)
	{
		return FALSE;
	}

	pPetDB->m_nDataID = pPetAttr->m_nDataID;
	strncpy(pPetDB->m_szName, pPetAttr->m_sName, sizeof(pPetAttr->m_sName) - 1);
	strncpy(pPetDB->m_szNick, pPetAttr->m_sName, sizeof(pPetAttr->m_sName) - 1);
	pPetDB->m_nLevel = pPetAttr->m_iLevel;
	pPetDB->m_nTakeLevel = pPetAttr->m_iTakeLevel;
	pPetDB->m_nAttackType = -1;
	pPetDB->m_AIType = 0;
	pPetDB->m_CampData.Clear();

	pPetDB->m_byGeneration = pPetAttr->m_byGeneration;

	pPetDB->m_byHappiness = 100;
	pPetDB->m_iStrengthPerception = GetRand(pPetAttr->m_iStrengthMinPer, pPetAttr->m_iStrengthMaxPer);
	pPetDB->m_iSmartnessPerception = GetRand(pPetAttr->m_iSmartnessMinPer, pPetAttr->m_iSmartnessMaxPer);
	pPetDB->m_iMindPerception = GetRand(pPetAttr->m_iMindMinPer, pPetAttr->m_iMindMaxPer);
	pPetDB->m_iConstitutionPerception = GetRand(pPetAttr->m_iConstitutionMinPer, pPetAttr->m_iConstitutionMaxPer);

	pPetDB->m_fGrowRate = (float) GetRand(pPetAttr->m_iPullulationRateMin, pPetAttr->m_iPullulationRateMax);
	pPetDB->m_nRemainPoint = 0;
	pPetDB->m_nExp = 0;

	pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_STR] = GetRand
		(
			pPetAttr->m_iStrengthMin,
			pPetAttr->m_iStrengthMax
		);
	pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_DEX] = GetRand
		(
			pPetAttr->m_iSmartnessMin,
			pPetAttr->m_iSmartnessMax
		);
	pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_INT] = GetRand(pPetAttr->m_iMindMin, pPetAttr->m_iMindMax);
	pPetDB->m_BaseAttrLevel1.m_pAttr[CPROPERTY_LEVEL1_CON] = GetRand
		(
			pPetAttr->m_iConstitutionMin,
			pPetAttr->m_iConstitutionMax
		);

	if(bInitNewSkill)
	{
		InitHorseSkills(pPetDB, pPetAttr);
	}

	pPetDB->m_iModelID = pPetAttr->m_iMountID;
	pPetDB->m_uHappinessLeftTime = g_Config.m_ConfigInfo.m_PetHappinessInterval * 1000;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::CreateBHVClassOfHorse(_HORSE_DB &rPetDB)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 idData = rPetDB.m_nDataID;
	int32		&rAIType = rPetDB.m_AIType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	rAIType = RandGenerator::GetRand(0, 4);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::CreateClassOfHorse(_HORSE_DB &rPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::CreateRemainPointOfHorse(_HORSE_DB &rPetDB)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::CreateSpellOfHorse(_HORSE_DB &rPetDB)
{
//	__GUARD__
//#define MAX_RANG_VALUE	(1000000)
//#define RAND_COUNT	(5)
//	int32 idData = rPetDB.m_nDataID;
//
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	SHorseSkill	*paSkillList = rPetDB.m_SkillList;
//	int32		nIndex = 0;
//	int32		n;
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	for(n = 0; n < PET_MAX_NUM; ++n)
//	{
//		if(g_HorseSpellDistrTab[n].m_PetID == idData)
//		{
//			nIndex = n;
//			break;
//		}
//	}
//
//	if(n == PET_MAX_NUM)
//	{
//		KCheck(FALSE && "idData ... not found!");
//		return;
//	}
//
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//	int32	nRangeA = g_HorseSpellDistrTab[nIndex].m_Table[0].m_nSkillRange;
//	int32	nRangeB = nRangeA + g_HorseSpellDistrTab[nIndex].m_Table[1].m_nSkillRange;
//	int32	nRangeC = nRangeB + g_HorseSpellDistrTab[nIndex].m_Table[2].m_nSkillRange;
//	int32	nRangeD = nRangeC + g_HorseSpellDistrTab[nIndex].m_Table[3].m_nSkillRange;
//	int32	nRangeE = nRangeD + g_HorseSpellDistrTab[nIndex].m_Table[4].m_nSkillRange;
//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//	for(int32 i = 0; i < RAND_COUNT; ++i)
//	{
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//		int32	nRet = RandGenerator::GetRand(0, MAX_RANG_VALUE);
//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//		if(nRet <= nRangeA)
//		{
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[0].m_nSkillIndex;
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//			AddHorseSpell(paSkillList, nSkillIndex);
//		}
//		else if(nRet <= nRangeB)
//		{
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[1].m_nSkillIndex;
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//			AddHorseSpell(paSkillList, nSkillIndex);
//		}
//		else if(nRet <= nRangeC)
//		{
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[2].m_nSkillIndex;
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//			AddHorseSpell(paSkillList, nSkillIndex);
//		}
//		else if(nRet <= nRangeD)
//		{
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[3].m_nSkillIndex;
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//			AddHorseSpell(paSkillList, nSkillIndex);
//		}
//		else if(nRet <= nRangeE)
//		{
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[4].m_nSkillIndex;
//			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//
//			AddHorseSpell(paSkillList, nSkillIndex);
//		}
//		else
//		{
//		}
//	}
//
//	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::CreateGrowRateOfHorse(_HORSE_DB &rPetDB)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::CreatePerceptionOfHorse(_HORSE_DB &rPetDB)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::AddHorseSpell(SHorseSkill *paSkillList, int32 &rSkillIndex)
{
	//__GUARD__ if(rSkillIndex > PET_SKILL_NUM)
	//{
	//	KCheck(FALSE && "rSkillIndex > PET_SKILL_NUM");
	//	return;
	//}

	///*~~~~~~~~~~~~~~~~~~~~*/
	//int32	nSkillID = -1;
	//int32	nSkillType = -1;
	///*~~~~~~~~~~~~~~~~~~~~*/

	//for(int32 i = 0; i < PET_SKILL_NUM; ++i)
	//{
	//	if(g_HorseSpellIndexTab[i].m_nIndex == rSkillIndex)
	//	{
	//		nSkillID = g_HorseSpellIndexTab[i].m_nSkillID;

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		SpellTemplateData const *pSkillTemplateData = g_SpellTemplateDataMgr.GetInstanceByID(nSkillID);
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(!pSkillTemplateData)
	//		{
	//			return;
	//		}

	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//		ID_t	OperateModeOfPetSkill = pSkillTemplateData->GetOperateModeForPetSkill();
	//		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//		if(PET_SKILL_OPERATE_NEEDOWNER == OperateModeOfPetSkill)
	//		{
	//			paSkillList[PET_SKILL_INDEX_CONTROL_BY_PLAYER].m_nSkillID = nSkillID;
	//			return;
	//		}
	//		break;
	//	}
	//}

	//for(int32 j = PET_SKILL_INDEX_CONTROL_BY_AI0; j < PET_MAX_SKILL_COUNT; ++j)
	//{
	//	if(paSkillList[j].m_nSkillID == nSkillID)
	//	{
	//		return;
	//	}

	//	if(paSkillList[j].m_nSkillID == INVALID_ID)
	//	{
	//		paSkillList[j].m_nSkillID = nSkillID;
	//		break;
	//	}
	//}

	//__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!m_LogicTimer.CountingTimer(uTime)) return TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MAX_REMOVE_SIZE 256
	int32	aNeedRemovePet[MAX_REMOVE_SIZE];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ClearRemoveArray(aNeedRemovePet);

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRemoveCount = 0;
	int32	i;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < (int32) m_uCount; i++)
	{
		if(m_papObjs[i] != NULL)
		{
			_NET_TRY
			{
				if(m_papObjs[i]->IsActiveObj())
				{
					m_papObjs[i]->HeartBeat(uTime);
				}
				else
				{
					aNeedRemovePet[nRemoveCount++] = i;
					if(nRemoveCount >= MAX_REMOVE_SIZE - 1)
					{
						DeleteDeadHorse(nRemoveCount, aNeedRemovePet);
						nRemoveCount = 0;
						ClearRemoveArray(aNeedRemovePet);
					}
				}
			}

			_NET_CATCH
			{
				QLOGGER_CODEHOLDER();
			}
		}
	}

	DeleteDeadHorse(nRemoveCount, aNeedRemovePet);

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::DeleteDeadHorse(int32 nRemoveCount, int32 *aNeedRemovePet)
{
	__GUARD__ for(int32 i = nRemoveCount - 1; i >= 0; i--)
	{
		_NET_TRY
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Horse	*pHorse = (Horse *) (m_papObjs[aNeedRemovePet[i]]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pHorse != NULL)
			{
				pHorse->SetActiveFlag(FALSE);
				pHorse->Clear();
				GetMap()->DeleteObject(pHorse);
			}
		}

		_NET_CATCH
		{
			QLOGGER_CODEHOLDER();
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 HorseManager::GetRand(int32 iMin, int32 iMax)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fRand = ((float) (m_pMap->GetRand100()) / 100.0f);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return(int32) (iMin + ((float) (iMax - iMin) * fRand + 0.5f));

	__UNGUARD__ return iMin;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::ClearRemoveArray(int32 *aNeedRemovePet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(aNeedRemovePet, 0, sizeof(int32) * MAX_REMOVE_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::Clear()
{
	m_pMap = NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void HorseManager::InitHorseGUID(SHorseGuid&guidPet, Player *pPlayer)
{
	__GUARD__ guidPet.Init(pPlayer->GetGUID(), GET_TIME().TickCount());
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 HorseManager::GetPerceptionLimit(int32 iGeneration)
{
	/*__GUARD__ if(iGeneration < 1)
	{
		iGeneration = 1;
	}

	if(iGeneration > g_HorsePerLimit.m_iCount)
	{
		iGeneration = g_HorsePerLimit.m_iCount;
	}

	return g_HorsePerLimit.m_aLimit[iGeneration - 1];
	__UNGUARD__*/
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL HorseManager::InitHorseSkills(_HORSE_DB *pPetDB, _HORSE_ATTR *pPetAttr)
{
	//__GUARD__ if(NULL == pPetDB) return FALSE;

	//if(NULL == pPetAttr) return FALSE;

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//int32	iSoltPassive = 0;
	//int32	iSoltActive = PET_MAX_APPER_COUNT;
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//for(int32 iSkillGroup = 0; iSkillGroup < PET_MAX_SKILL_COUNT; ++iSkillGroup)
	//{
	//	if(pPetAttr->m_oSkillSlot[iSkillGroup].m_iSkillCount == 0)
	//	{
	//		continue;
	//	}

	//	if(pPetAttr->m_oSkillSlot[iSkillGroup].m_iSkillCount > MaxSlotSkillNum)
	//	{
	//		KCheck(FALSE && "骑乘初始技能ID填的太多了");
	//		continue;
	//	}

	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	int32	randvalue = RandGenerator::GetRand(0, pPetAttr->m_iInitSkillRandSum);
	//	int32	iSkill = 0;
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	for(; iSkill < pPetAttr->m_oSillRandRate[iSkillGroup].m_iSkillCount; iSkill++)
	//	{
	//		if(randvalue <= pPetAttr->m_oSillRandRate[iSkillGroup].m_aSkillRandRate[iSkill])
	//		{
	//			break;
	//		}
	//		else
	//			randvalue -= pPetAttr->m_oSillRandRate[iSkillGroup].m_aSkillRandRate[iSkill];
	//	}

	//	if(iSkill >= pPetAttr->m_oSillRandRate[iSkillGroup].m_iSkillCount)
	//	{
	//		continue;
	//	}

	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//	int32			iSkillID = pPetAttr->m_oSkillSlot[iSkillGroup].m_aSkillSlot[iSkill];
	//	const SpellTemplateData *pTemplate = GetSpellTemplateByID(iSkillID);
	//	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//	if(NULL == pTemplate)
	//	{
	//		continue;
	//	}

	//	if(pTemplate->GetPassiveFlag() <= 0)
	//	{
	//		if(iSoltActive >= PET_MAX_SKILL_COUNT) continue;
	//		pPetDB->m_SkillList[iSoltActive].m_nSkillID = iSkillID;
	//		pPetDB->m_SkillList[iSoltActive].m_bCanUse = TRUE;
	//		iSoltActive++;
	//	}
	//	else
	//	{
	//		if(iSoltPassive >= PET_MAX_APPER_COUNT) continue;
	//		pPetDB->m_SkillList[iSoltPassive].m_nSkillID = iSkillID;
	//		pPetDB->m_SkillList[iSoltPassive].m_bCanUse = TRUE;
	//		iSoltPassive++;
	//	}
	//}

	//return TRUE;

	//__UNGUARD__ return FALSE;
	return TRUE;
}
