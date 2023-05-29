/*$T Common/SkillDataMgr.cpp GC 1.140 10/10/09 10:06:54 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"

#include "SpellDataMgr.h"
#include <map>
#include <assert.h>

CSpellDataMgr *CSpellDataMgr::	s_pSkillDataMgr = NULL;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CSpellDataMgr::CSpellDataMgr(void)
{
	m_pDBCFileLoad = NULL;
	m_pDataBase = NULL;
	s_pSkillDataMgr = this;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CSpellDataMgr::~CSpellDataMgr(void)
{
	s_pSkillDataMgr = NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CSpellDataMgr::Init(const char *lpszPathName)
{
	/*~~~~~~~~~~~~*/
	BOOL	bResutl;
	/*~~~~~~~~~~~~*/

	m_pDBCFileLoad = new TAB::TABFile(UINT_MAX);
	bResutl = m_pDBCFileLoad->OpenFromTXT(lpszPathName);
	if(!bResutl) return FALSE;

	m_pDataBase = m_pDBCFileLoad;

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CSpellDataMgr::Init(const TAB::TABFile *pDataBase)
{
	m_pDBCFileLoad = NULL;
	m_pDataBase = pDataBase;
	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CSpellDataMgr::Term(void)
{
	m_pDataBase = NULL;
	if(m_pDBCFileLoad != NULL)
	{
		delete m_pDBCFileLoad;
		m_pDBCFileLoad = NULL;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SSkillData *CSpellDataMgr::GetSkillData(uint32 dwID)
{
	/*~~~~~~~~~~~~~~~~~~*/
	SSkillData	*pSet;
	/*~~~~~~~~~~~~~~~~~~*/

	pSet = (SSkillData *) (m_pDataBase->Search_Index_EQU(dwID));
	return pSet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const SSkillData *CSpellDataMgr::GetConstSkillData(uint32 dwID) const
{
	return const_cast<CSpellDataMgr *>(this)->GetSkillData(dwID);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CSpellDataMgr::GetRandAnim(uint32 dwSkillID, int32 nActionIndex /* = -1 */, BOOL bSendAnim /* = TRUE */ ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const std::vector<int32>	*pvTheAnimID = GetAnimList(dwSkillID, bSendAnim);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pvTheAnimID == NULL)
	{
		return 0;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const std::vector<int32>	&vTheAnimID = *pvTheAnimID;
	int32 nSize = (int32) vTheAnimID.size();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nSize <= 0) return 0;

	/*~~~~~~~~~~~~~*/
	int32 nRandIndex;
	/*~~~~~~~~~~~~~*/

	if(nActionIndex <= 0)
		nRandIndex = 0;
	else
		nRandIndex = nActionIndex % (int32) nSize;

	return vTheAnimID[nRandIndex];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CSpellDataMgr::GetAnimCount(uint32 dwSkillID, BOOL bSendAnim /* = TRUE */ ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const std::vector<int32>	*pvTheAnimID = GetAnimList(dwSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pvTheAnimID == NULL)
	{
		return 0;
	}

	return(int32) (pvTheAnimID->size());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const std::vector<int32> *CSpellDataMgr::GetAnimList(uint32 uSkillID, BOOL bSendAnim /* = TRUE */ ) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	typedef std::map<uint32, std::vector<int32> >	MAP_SKILLANIM;
	static MAP_SKILLANIM s_mapSkillLeadAnim, s_mapSkillSendAnim;
	MAP_SKILLANIM *pSkillAnimMap;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(bSendAnim)
	{
		pSkillAnimMap = &s_mapSkillSendAnim;
	}
	else
	{
		pSkillAnimMap = &s_mapSkillLeadAnim;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MAP_SKILLANIM::const_iterator	it = pSkillAnimMap->find(uSkillID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(it == pSkillAnimMap->end())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		static std::vector<int32>	s_vEmpty;
		const SSkillData		*pSet = (const SSkillData *) (m_pDataBase->Search_Index_EQU(uSkillID));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(!pSet)
		{
			assert(false && "CSpellDataMgr::GetAnimList Invalid skill id");
			return NULL;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		std::vector<std::string>	vAnim;
		int32 nNumber;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(bSendAnim)
		{
			nNumber = TAB::TABFile::_ConvertStringToVector
				(
					pSet->m_lpszSendActionSetID,
					vAnim,
					";",
					TRUE,
					TRUE
				);
		}
		else
		{
			nNumber = TAB::TABFile::_ConvertStringToVector
				(
					pSet->m_lpszGatherLeadActionSetID,
					vAnim,
					";",
					TRUE,
					TRUE
				);
		}

		if(0 == nNumber)
		{
			assert(false && "CSpellDataMgr::GetAnimList Invalid skill anim set");
			return NULL;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		std::vector<int32>	vAnimID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 i = 0; i < (int32) vAnim.size(); i++)
		{
			vAnimID.push_back(atoi(vAnim[i].c_str()));
		}
		(*pSkillAnimMap)[uSkillID] = vAnimID;
		it = pSkillAnimMap->find(uSkillID);
	}

	if(it == pSkillAnimMap->end()) return NULL;

	return &(it->second);
}
