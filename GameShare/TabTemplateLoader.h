/*$T Common/Combat/TabTemplateLoader.h GC 1.140 10/10/07 10:06:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/* TabTemplateLoader.h 功能说明：技能相关数据管理器的模板 */
#ifndef _TEMPLATE_MANAGER_H_
#define _TEMPLATE_MANAGER_H_

#include "TypeDefine.h"
#include "TAB.h"

namespace	TAB
{
class	TABFile;
} using namespace	TAB;
template<typename U>
class TemplateManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { MAXSIZE = U::MAX_ID +1, };

	TemplateManager();
	~TemplateManager();
	BOOL InitFromDB(char const *szFile);
	BOOL InitFromDBMemory(const TABFile *pDB);
	U const *const GetInstanceByID(int32 const nID) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 Size(void) const
	{
		return m_nSize;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	m_bReady;
	int32	m_nSize;
	U	m_vTemplateList[MAXSIZE];
	TABFile *m_pDB;
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<typename U>
inline TemplateManager<U>::TemplateManager() :
	m_bReady(FALSE),
	m_nSize(0),
	m_pDB(NULL)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<typename U>
inline TemplateManager<U>::~TemplateManager()
{
	KSafeDelete(m_pDB);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<typename U>
inline BOOL TemplateManager<U>::InitFromDBMemory(const TABFile *pDB)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_nSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_bReady = FALSE;

	if(NULL == pDB)
	{
		return FALSE;
	}

	m_nSize = pDB->GetRecordsNum();

	/*
	 * init List ;
	 * read data
	 */
	for(int32 i = 0; m_nSize > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nID = pDB->Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 > nID || MAXSIZE < nID)
		{
			KCheckEx(FALSE, "[TemplateManager_T<U>::InitFromDB: nID out of range!!abort input.");
			continue;
		}

		m_vTemplateList[nID].InitFromDB(pDB, i);
	}

	m_bReady = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<typename U>
inline BOOL TemplateManager<U>::InitFromDB(char const *szFile)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_nSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_bReady = FALSE;

	if(NULL == szFile)
	{
		return FALSE;
	}

	if(NULL != m_pDB)
	{
		KSafeDelete(m_pDB);
	}

	m_pDB = new TABFile(0);
	if(NULL == m_pDB)
	{
		return FALSE;
	}

	if(FALSE == m_pDB->OpenFromTXT(szFile))
	{
		return FALSE;
	}

	m_nSize = m_pDB->GetRecordsNum();

	/*
	 * init List ;
	 * read data
	 */
	for(int32 i = 0; m_nSize > i; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nID = m_pDB->Search_Posistion(i, 0)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(0 > nID || MAXSIZE <= nID)
		{
			KCheckEx(FALSE, "[TemplateManager_T<U>::InitFromDB: nID out of range!!abort input.");
			continue;
		}

		m_vTemplateList[nID].InitFromDB(m_pDB, i);
	}

	m_bReady = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<typename U>
inline U const *const TemplateManager<U>::GetInstanceByID(int32 const nID) const
{
	__GUARD__ if(0 > nID || MAXSIZE <= nID)
	{
		return NULL;
	}

	if(0 == m_nSize)
	{
		return NULL;
	}

	if(FALSE == m_bReady)
	{
		return NULL;
	}

	if(FALSE == m_vTemplateList[nID].IsInited())
	{
		return NULL;
	}

	return &m_vTemplateList[nID];
	__UNGUARD__ return NULL;
}
#endif /* _TEMPLATE_MANAGER_H_ */
