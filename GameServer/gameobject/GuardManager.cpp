/*$T MapServer/Server/Obj/GuardManager.cpp GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "BaseTool.h"
#include "BaseTool.h"
#include "TabDefine.h"
#include "Map.h"
#include "Pet.h"
#include "ObjectManager.h"
#include "GuardManager.h"
#include "Item_Interface.h"
#include "BaseTool.h"
#define SECSIZE 64

/*
 =======================================================================================================================
 =======================================================================================================================
 */

GuardManager::GuardManager(void)
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
GuardManager::~GuardManager(void)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::Clear()
{
	memset(&m_oInit, 0, sizeof(m_oInit));
	m_pMap = NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Pet *GuardManager::GetPet(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Pet	*pPet = (Pet *) (GetMap()->GetObjManager()->GetObj(idObj));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pPet == NULL)
	{
		return NULL;
	}

	if(pPet->GetObjType() != Object::OBJECT_CLASS_PET)
	{
		KCheck((pPet->GetObjType() == Object::OBJECT_CLASS_PET) && "GuardManager::GetPet");
		return NULL;
	}

	return pPet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::SetInitData(_MONSTER_PET_ATTR &oInit)
{
	m_oInit = oInit;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const _MONSTER_PET_ATTR &GuardManager::GetInitData()
{
	return m_oInit;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GuardManager::RemoveAllPet(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Map	*pMap;
	Pet		*pPet;
	uint32		i, uCount, uMaxCount, uLength;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMap = GetMap();
	uCount = 0;
	uMaxCount = GetCount();
	uLength = GetLength();

	for(i = 0; i < uLength; i++)
	{
		pPet = (Pet *) (GetObjByIndex(0));
		if(pPet != NULL)
		{
			pPet->SetActiveFlag(FALSE);
			pPet->Clear();
			pMap->DeleteObject(pPet);
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
BOOL GuardManager::RemovePet(ObjID_t idObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Map	*pMap = GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMap)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Object	*pPet = pMap->GetGuardManager()->GetPet(idObj);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pPet && pPet->GetObjType() == Object::OBJECT_CLASS_PET)
		{
			pPet->SetActiveFlag(FALSE);
			pPet->Clear();
			pMap->DeleteObject(pPet);
		}
	}

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GuardManager::CreatePet(int32 nDataID, GLPos *pPos, ObjID_t &rPetID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Pet	*pPet = (Pet *) (GetMap()->NewObject(Object::OBJECT_CLASS_PET));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPet)
	{
		return FALSE;
	}

	rPetID = pPet->GetID();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SMonsterExtAttr	*pMonsterExtAttr = g_MonsterPropertyExTab.GetExtAttr(nDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonsterExtAttr) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~*/
	_INIT_PET_OBJECT	initPet;
	/*~~~~~~~~~~~~~~~~~~~~*/

	initPet.m_Pos = *pPos;
	initPet.m_Dir = 0.f;
	initPet.m_eLogic = CHARACTER_LOGIC_IDLE;
	initPet.m_CreatorID = INVALID_ID;

	InitPetDB(&initPet.m_PetDB, nDataID);
	initPet.m_GUID = INVALID_GUID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL	bResult = pPet->Init(&initPet);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!bResult)
	{
		return FALSE;
	}

	pPet->SetActiveFlag(TRUE);

	return TRUE;
	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GuardManager::CreateGUIDOfPet(_HORSE_DB *pPetDB, ObjID_t idHuman, ObjID_t idPet)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(idHuman != INVALID_ID && idPet != INVALID_ID && "GuardManager::CreateGUIDOfPet");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(idHuman == INVALID_ID || idPet == INVALID_ID)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~*/
	Player	*pPlayer;
	Pet	*pPet;
	/*~~~~~~~~~~~~~*/

	pPlayer = GetMap()->GetPlayerManager()->GetPlayer(idHuman);
	pPet = GetPet(idPet);

	KCheck(pPlayer != NULL && pPet != NULL && "GuardManager::CreateGUIDOfPet");
	if(pPlayer == NULL || pPet == NULL)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	PET_PROPERTY	*pPetAttr = g_HorsePropertyTab.GetAttr(pPet->GetDataID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pPetAttr) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SHorseGiud	guidPet, guidSpouse;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guidPet.Init(pPlayer->GetGUID(), GET_TIME().TickCount());
	guidSpouse.Reset();

	pPetDB->m_GUID = guidPet;

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GuardManager::MakeCapturePetAttrib(_HORSE_DB *pPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	CreateAITypeOfPet(*pPetDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GuardManager::InitPetDB(_HORSE_DB *pPetDB, int32 nDataID)
{
	__GUARD__ if(pPetDB == NULL) return FALSE;

	pPetDB->Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SMonsterExtAttr	*pPetAttr = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDataID != INVALID_ID)
	{
		pPetAttr = g_MonsterPropertyExTab.GetExtAttr(nDataID);
	}

	if(pPetAttr != NULL)
	{
		pPetDB->m_nDataID = nDataID;
		strncpy(pPetDB->m_szNick, "", sizeof(pPetDB->m_szNick) - 1);

		pPetDB->m_nAttackType = -1;
		pPetDB->m_AIType = 0;
		pPetDB->m_CampData.Clear();

		pPetDB->m_CampData.m_nCampID = pPetAttr->m_Camp;

		pPetDB->m_byGeneration = 0;

		pPetDB->m_byHappiness = 100;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::CreateAITypeOfPet(_HORSE_DB &rPetDB)
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
void GuardManager::CreateTypeOfPet(_HORSE_DB &rPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::CreateRemainPointOfHorse(_HORSE_DB &rPetDB)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::CreateSkillOfPet(_HORSE_DB &rPetDB)
{
	__GUARD__
#define MAX_RANG_VALUE	(1000000)
#define RAND_COUNT	(5)
	int32 idData = rPetDB.m_nDataID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SHorseSkill	*paSkillList = rPetDB.m_SkillList;
	int32		nIndex = 0;
	int32		n;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(n = 0; n < PET_MAX_NUM; ++n)
	{
		if(g_HorseSpellDistrTab[n].m_PetID == idData)
		{
			nIndex = n;
			break;
		}
	}

	if(n == PET_MAX_NUM)
	{
		KCheck(FALSE && "idData ... not found!");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nRangeA = g_HorseSpellDistrTab[nIndex].m_Table[0].m_nSkillRange;
	int32	nRangeB = nRangeA + g_HorseSpellDistrTab[nIndex].m_Table[1].m_nSkillRange;
	int32	nRangeC = nRangeB + g_HorseSpellDistrTab[nIndex].m_Table[2].m_nSkillRange;
	int32	nRangeD = nRangeC + g_HorseSpellDistrTab[nIndex].m_Table[3].m_nSkillRange;
	int32	nRangeE = nRangeD + g_HorseSpellDistrTab[nIndex].m_Table[4].m_nSkillRange;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < RAND_COUNT; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRet = RandGenerator::GetRand(0, MAX_RANG_VALUE);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRet <= nRangeA)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[0].m_nSkillIndex;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if(nRet <= nRangeB)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[1].m_nSkillIndex;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if(nRet <= nRangeC)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[2].m_nSkillIndex;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if(nRet <= nRangeD)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[3].m_nSkillIndex;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if(nRet <= nRangeE)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nSkillIndex = g_HorseSpellDistrTab[nIndex].m_Table[4].m_nSkillIndex;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			AddPetSkill(paSkillList, nSkillIndex);
		}
		else
		{
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::CreateGrowRateOfPet(_HORSE_DB &rPetDB)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::CreatePerceptionOfPet(_HORSE_DB &rPetDB)
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GuardManager::AddPetSkill(SHorseSkill *paSkillList, int32 &rSkillIndex)
{
	__GUARD__ if(rSkillIndex > PET_SKILL_NUM)
	{
		KCheck(FALSE && "rSkillIndex > PET_SKILL_NUM");
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~*/
	int32	nSkillID = -1;
	int32	nSkillType = -1;
	/*~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < PET_SKILL_NUM; ++i)
	{
		if(g_HorseSpellIndexTab[i].m_nIndex == rSkillIndex)
		{
			nSkillID = g_HorseSpellIndexTab[i].m_nSkillID;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SpellTemplateData const *pSkillTemplateData = g_SpellTemplateDataMgr.GetInstanceByID(nSkillID);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pSkillTemplateData)
			{
				return;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ID_t	OperateModeOfPetSkill = pSkillTemplateData->GetOperateModeForPetSkill();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(PET_SKILL_OPERATE_NEEDOWNER == OperateModeOfPetSkill)
			{
				paSkillList[PET_SKILL_INDEX_CONTROL_BY_PLAYER].m_nSkillID = nSkillID;
				return;
			}
			break;
		}
	}

	for(int32 j = PET_SKILL_INDEX_CONTROL_BY_AI0; j < PET_MAX_SKILL_COUNT; ++j)
	{
		if(paSkillList[j].m_nSkillID == nSkillID)
		{
			return;
		}

		if(paSkillList[j].m_nSkillID == INVALID_ID)
		{
			paSkillList[j].m_nSkillID = nSkillID;
			break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL GuardManager::HeartBeat(uint32 uTime)
{
	__GUARD__ if(!m_LogicTimer.CountingTimer(uTime)) return TRUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define MAX_REMOVE_SIZE 256
	int32	aNeedRemovePet[MAX_REMOVE_SIZE];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(aNeedRemovePet, 0, sizeof(int32) * MAX_REMOVE_SIZE);

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
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					BOOL	bRet = m_papObjs[i]->HeartBeat_OutMap(uTime);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(bRet == FALSE)
					{
						aNeedRemovePet[nRemoveCount++] = i;
					}
				}
			}

			_NET_CATCH
			{
				QLOGGER_CODEHOLDER();
			}
		}
	}

	for(i = nRemoveCount - 1; i >= 0; i--)
	{
		_NET_TRY
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Pet	*pPet = (Pet *) (m_papObjs[aNeedRemovePet[i]]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pPet != NULL)
			{
				pPet->SetActiveFlag(FALSE);
				pPet->Clear();
				GetMap()->DeleteObject(pPet);
			}
		}

		_NET_CATCH
		{
			QLOGGER_CODEHOLDER();
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GuardManager::GetRand(int32 iMin, int32 iMax)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fRand = ((float) (m_pMap->GetRand100()) / 100.0f);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return(int32) (iMin + ((float) (iMax - iMin) * fRand + 0.5f));
}
