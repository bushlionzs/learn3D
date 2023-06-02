/*$T Common/ScriptCacheMgr.cpp GC 1.140 10/10/07 10:06:30 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "ScriptCacheMgr.h"

#include "TAB.h"

using namespace TAB;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ScriptCache::ScriptCache(void)
{
	m_uID = INVALID_ID;
	memset(m_szFileName, 0, sizeof(m_szFileName));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScriptCache::~ScriptCache(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptCache::Init(uint32 uID, const char *pszFileName, FILE *fp)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pszFileName != NULL);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(strlen(pszFileName) < FILE_DATA_NAME_LEN);
	m_uID = uID;
	strncpy(m_szFileName, pszFileName, FILE_DATA_NAME_LEN - 1);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptCache::Term(void)
{
	m_uID = INVALID_ID;
	memset(m_szFileName, 0, sizeof(m_szFileName));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScriptCacheMgr::ScriptCacheMgr(void)
{
	m_bInit = FALSE;
	m_uCount = 0;
	m_apFileData = NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScriptCacheMgr::~ScriptCacheMgr(void)
{
	Term();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptCacheMgr::Term(void)
{
	m_bInit = FALSE;
	m_uCount = 0;
	if(m_apFileData)
	{
		delete[] m_apFileData;
		m_apFileData = NULL;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ScriptCacheMgr::CompareOfFileDataID(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 Serial1, Serial2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Serial1 = ((ScriptCache *) pArg1)->GetID();
	Serial2 = ((ScriptCache *) pArg2)->GetID();

	if(Serial1 > Serial2)
	{
		return 1;
	}
	else if(Serial1 < Serial2)
	{
		return -1;
	}
	else
	{
		return 0;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScriptCache *ScriptCacheMgr::GetFileData(uint32 uID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ScriptCache	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.Init(uID, "for bsearch", NULL);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ScriptCache	*pResult = (ScriptCache *) bsearch
		(
			&tb,
			m_apFileData,
			m_uCount,
			sizeof(ScriptCache),
			(int32(*) (const void *, const void *)) CompareOfFileDataID
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return pResult;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const ScriptCache *ScriptCacheMgr::GetConstFileData(uint32 uID) const
{
	return const_cast<ScriptCacheMgr *>(this)->GetFileData(uID);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScriptCache *ScriptCacheMgr::GetFileDataByIndex(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nIndex >= 0 && nIndex < m_uCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return &m_apFileData[nIndex];
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptCacheMgr::Init(const char *pszPathFileName, BOOL bForceArrayMode)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { FileData_Index = 0, FileData_Name };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(pszPathFileName);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ret != TRUE)
	{
		KCheck(FALSE && "ScriptCacheMgr::Init error, when open file");
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!ReadTabSizeCheck(iTableCount))
	{
		return FALSE;
	}

	m_uCount = iTableCount;

	m_apFileData = new ScriptCache[m_uCount];
	KCheck(m_apFileData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		char szName[_MAX_PATH]={0};
		int32		iID = ThirdFile.Search_Posistion(i, FileData_Index)->iValue;
		const char	*pName = ThirdFile.Search_Posistion(i, FileData_Name)->pString;
		sprintf( szName, "../Public/Data/Script%s", pName );
		FILE* fp = fopen(szName,"r");
		if( fp == NULL )
		{
			char szKCheck[256]={0};
			sprintf(szKCheck,"Error ! Script File [%d:%s] Not Exist!",iID,pName);
			
		//	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, szKCheck); //zhousha
		////	KCheckEx(FALSE,szKCheck);
		}
		else
			fclose(fp);

		m_apFileData[i].Init(iID, const_cast<char *>(pName), NULL);
	}

	SortFileDataArray();

	m_bInit = TRUE;

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptCacheMgr::ReadTabSizeCheck(int32 iTableCount)
{
	__GUARD__ if(iTableCount <= 0)
	{
		KCheck(FALSE && "ScriptCacheMgr::Init error, TableCount <= 0");
		return FALSE;
	}

	if(iTableCount > AUTO_ARRAY_MODE_MAX_LEN)
	{
		KCheck(FALSE && "ScriptCacheMgr::Init error, iTableCount > AUTO_ARRAY_MODE_MAX_LEN");
		return FALSE;
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptCacheMgr::SortFileDataArray()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	qsort
			(
				m_apFileData,
				m_uCount,
				sizeof(ScriptCache),
				(int32(*) (const void *, const void *)) CompareOfFileDataID
			);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}
