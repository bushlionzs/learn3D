#include "OgreHeader.h"
#include "GameTableDefine.h"
#include "GameTableManager.h"
#include "KTable.h"
#include "OgreResourceManager.h"
#include "platform_log.h"

template<>
CGameTableManager * GameSingleton<CGameTableManager>::m_sSingleton = NULL;

CGameTableManager::CGameTableManager(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CGameTableManager::~CGameTableManager(void)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
KHAN_RETURN_RESULT CGameTableManager::Initialize(void)
{
	OpenAllTable();

	return KRR_SUCCEED;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CGameTableManager::Release(void)
{
	CloseAllTable();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const CGameTable *CGameTableManager::GetTable(int32 nTable) const
{
	std::map<int32, CGameTable *>::const_iterator iter = m_TableMap.find(nTable);

	if(iter != m_TableMap.end()) return (const CGameTable *) (iter->second);

	return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CGameTableManager::OpenAllTable(void)
{
	String strFileName;
	String strFinalName;

	/* 打开所有数据库 */
	int32 nNum = sizeof(g_TableFileLoad) / sizeof(TABLE_FILE_LOAD_DEFINE);
	int32 nTableEnum = INVALID_ID;

	for(int32 index = 0; index < nNum; ++index)
	{
		nTableEnum = g_TableFileLoad[index].nTableEnum;

		CGameTable	*pTable = new CGameTable(nTableEnum);

		if(NULL == pTable)
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Create Table Error!");
		}
		strFileName = g_TableFileLoad[index].szTableFile;

		transform(strFileName.begin(), strFileName.end(), strFileName.begin(), ::tolower);

		strFinalName = strFileName + ".tab";

		if (!ResourceManager::getSingleton().hasResource(strFinalName, BLANKSTRING))
		{
			WARNING_LOG("resource %s is not exist", strFinalName.c_str());
			continue;
		}

		if (FALSE == pTable->OpenFromTXT(strFinalName.c_str(), FALSE, FALSE))
		{
			assert(false);
		}
		m_TableMap.insert(std::make_pair(nTableEnum, pTable));
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CGameTableManager::CloseAllTable(void)
{
	std::map<int32, CGameTable *>::iterator	it;

	for(it = m_TableMap.begin(); it != m_TableMap.end(); it++)
	{
		delete(CGameTable *) (it->second);
		it->second = NULL;
	}

	m_TableMap.clear();
}
