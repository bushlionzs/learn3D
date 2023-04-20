#include "OgreHeader.h"
#include "ActionSetManager.h"
#include "KTable.h"


#pragma warning(disable:4996)



CDBActionSet *CDBActionSet::m_pManagerActionSet	= NULL;


CDBActionSet::CDBActionSet( void )
{
	m_pManagerActionSet	= this;
}

CDBActionSet::~CDBActionSet( void )
{
	m_pManagerActionSet = NULL;
}


KHAN_RETURN_RESULT CDBActionSet::Initialize(String strResPath)
{
	m_strResPath = strResPath;

	return KRR_SUCCEED;
}

void CDBActionSet::Clear( void )
{
	CActionSetMap::iterator itCur, itEnd;
	itEnd = m_mapActionSet.end();
	for ( itCur = m_mapActionSet.begin(); itCur != itEnd; itCur++ )
	{
		delete (itCur->second);
	}
	m_mapActionSet.erase( m_mapActionSet.begin(), m_mapActionSet.end() );
}

const _TABLE_CHARACTER_ACTION_SET *CDBActionSet::GetActionSet( std::string strFileName, uint32 dwID )
{
	CActionSetMap::const_iterator itFind;
	itFind = m_mapActionSet.find( strFileName );
	if ( itFind == m_mapActionSet.end() )
	{
		TAB::TABFile* pDBCFile = new TAB::TABFile( -1 );
		String strPathName = m_strResPath + strFileName;
		const char *pszPathName = strPathName.c_str();
		BOOL bResult = CGameTable::OpenTableMemory( pszPathName, pDBCFile, g_bDebugPackRes );
		if ( bResult )
		{
			itFind = m_mapActionSet.insert( m_mapActionSet.end(), CActionSetMap::value_type( strFileName, pDBCFile ) );
		}
		else
		{
			delete pDBCFile;
			pDBCFile = NULL;
		}
	}

	if ( itFind == m_mapActionSet.end() )
		return NULL;

	const TAB::TABFile *pDBCFile = itFind->second;
	const _TABLE_CHARACTER_ACTION_SET *pActionSet = (const _TABLE_CHARACTER_ACTION_SET*)( pDBCFile->Search_Index_EQU( dwID ) );
	
	return pActionSet;
}

const TAB::TABFile *CDBActionSet::GetActionSetFile(std::string strFileName)
{
	CActionSetMap::const_iterator itFind;
	itFind = m_mapActionSet.find( strFileName );
	if ( itFind == m_mapActionSet.end() )
	{
		TAB::TABFile *pDBCFile = new TAB::TABFile( -1 );
		String strPathName;
		g_bDebugPackRes = 1;
		if (FALSE == g_bDebugPackRes)
		{
			strPathName = m_strResPath + strFileName;
		}
		else
		{
			strPathName = strFileName;
		}
		const char *pszPathName = strPathName.c_str();
		BOOL bResult = CGameTable::OpenTableMemory( pszPathName, pDBCFile, g_bDebugPackRes );
		if ( bResult )
		{
			itFind = m_mapActionSet.insert( m_mapActionSet.end(), CActionSetMap::value_type( strFileName, pDBCFile ) );
		}
		else
		{
			delete pDBCFile;
			pDBCFile = NULL;
		}
	}

	if ( itFind == m_mapActionSet.end() )
		return NULL;

	return itFind->second;
}
