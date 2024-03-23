#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "Util.h"
#include "BaseTool.h"

Configer::Configer()
{
	m_pBuf = NULL;
	m_pCurSection = NULL;
	m_nBufLen = 0;
	m_nBufMaxLen = 0;
	memset( m_szFileName, 0, MAX_FILE_PATH );
}

Configer::Configer(const char* filename)
{
	m_pBuf = NULL;
	m_pCurSection = NULL;
	m_nBufLen = 0;
	m_nBufMaxLen = 0;
	memset( m_szFileName, 0, MAX_FILE_PATH );

	Open(filename);
}

Configer::~Configer()
{
	Close();
}

BOOL Configer::Open(const char* filename)
{
	m_pBuf = new char[CONFIGER_BUF_SIZE];
	m_nBufMaxLen += CONFIGER_BUF_SIZE; 

#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_WORLD, "[Config] Begin Load %s ... ", filename);
#elif defined __MAPSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "[Config] Begin Load %s ... ", filename);
#endif

	strncpy( m_szFileName, filename, MAX_FILE_PATH - 1 );

	m_ifile.open( filename, std::ios_base::in );
	if( !m_ifile )
	{
		char szMsg[128] = {0};
		tsnprintf_s(szMsg, 128, "[Config] Open File Failed! file=%s", filename);
		KCheckEx(FALSE, szMsg);
	}

	char buf[512] = {0};
	while( m_ifile.getline(buf, 512) )
	{
		_TrimString(buf);

		char* sSection;
		if( _ParseSection(buf,&sSection) )
		{
			m_pCurSection = new ConfigerValueHashMap;
			m_SectionData.insert( std::make_pair(std::string(sSection), m_pCurSection) );
			continue;
		}

		char* sKey, *sValue;
		if( _ParseKey(buf,&sKey,&sValue) )
		{
			if( m_pCurSection == NULL )
			{
				char szMsg[128] = {0};
				tsnprintf_s(szMsg, 128, "[Config] Format Invalid! file=%s,key=%s", filename,sKey);
				KCheck(FALSE);
			}

			int nPos = _AddBufString(sValue);
			m_pCurSection->insert( std::make_pair(std::string(sKey), nPos ));
			continue;
		}
	}

	return TRUE;
}

void Configer::Close()
{
	__GUARD__

	if( m_ifile )
		m_ifile.close();

	if( m_pBuf != NULL )
	{
		delete[] m_pBuf;
		m_pBuf = NULL;
	}


	ConfigerSectionHashMap::iterator iter = m_SectionData.begin();
	for( ; iter != m_SectionData.end(); iter++ )
	{
		ConfigerValueHashMap* pSection = iter->second;
		if( pSection != NULL )
			delete pSection;
	}
	m_SectionData.clear();

	m_nBufLen = 0;
	m_nBufMaxLen = 0;

#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_WORLD, "[Config] End   Load %s ! ", m_szFileName);
#elif defined __MAPSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "[Config] End   Load %s ! ", m_szFileName);
#endif

	memset( m_szFileName, 0, MAX_FILE_PATH );

	__UNGUARD__
}

int32 Configer::Get_Property_Int(const char *section, const char *key, int32 nDefault )
{
	__GUARD__

	int32 nResult;
	if( _GetInt(section,key,nResult) )
		return nResult;

	char szMsg[128] = {0};
	tsnprintf_s(szMsg, 128, "[Config] Invalid Key! file=%s,section=%s,key=%s", m_szFileName,section,key);
	KCheckEx(FALSE,szMsg);
	return nDefault;
	__UNGUARD__
	return nDefault;
}

BOOL Configer::GetIntIfExist(const char *section, const char *key, int32& nResult )
{
	__GUARD__

	return _GetInt(section,key,nResult);

	__UNGUARD__
	return FALSE;	
}

float Configer::GetFloat(const char *section, const char *key, float fDefault )
{
	__GUARD__

	float fResult;
	if( _GetFloat(section,key,fResult) )
		return fResult;	

	char szMsg[128] = {0};
	tsnprintf_s(szMsg, 128, "[Config] Invalid Key! file=%s,section=%s,key=%s", m_szFileName,section,key);
	KCheckEx(FALSE,szMsg);
	return fDefault;
	__UNGUARD__
	return fDefault;
}

BOOL Configer::GetFloatIfExist(const char *section, const char *key, float& fResult )
{
	__GUARD__

	return _GetFloat(section,key,fResult);

	__UNGUARD__
	return FALSE;
}

BOOL Configer::GetText(const char *section, const char *key, char *str, int32 size, const char* strDefault )
{
	__GUARD__

	if( _GetText(section,key,str,size) )
		return TRUE;

	strncpy( str, strDefault, size );
	int32 nSize = strlen(strDefault) > size-1 ? size-1 : ( int32)strlen(strDefault);
	str[nSize] = 0;

	char szMsg[128] = {0};
	tsnprintf_s(szMsg, 128, "[Config] Invalid Key! file=%s,section=%s,key=%s", m_szFileName,section,key);
	KCheckEx(FALSE,szMsg);
	return FALSE;
	__UNGUARD__
	return FALSE;
}

BOOL Configer::GetTextIfExist(const char *section, const char *key, char *str, int32 size )
{
	__GUARD__

	return _GetText(section,key,str,size);

	__UNGUARD__
	return FALSE;
}


BOOL Configer::_GetInt(const char *section, const char *key, int32& nResult )
{
	__GUARD__

	ConfigerSectionHashMap::iterator it = m_SectionData.find(section);
	if( it == m_SectionData.end() )
		return FALSE;

	ConfigerValueHashMap* pSection = it->second;
	if( pSection != NULL )
	{
		ConfigerValueHashMap::iterator it2 = pSection->find(std::string(key));
		if( it2 == pSection->end() )
			return FALSE;

		int nPos = it2->second;
		char* sValue = _GetBufString(nPos);
		nResult = atoi(sValue);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__
	return FALSE;
}

BOOL Configer::_GetFloat(const char *section, const char *key, float& fResult )
{
	__GUARD__

	ConfigerSectionHashMap::iterator it = m_SectionData.find(section);
	if( it == m_SectionData.end() )
		return FALSE;

	ConfigerValueHashMap* pSection = it->second;
	if( pSection != NULL )
	{
		ConfigerValueHashMap::iterator it2 = pSection->find(std::string(key));
		if( it2 == pSection->end() )
			return FALSE;

		int nPos = it2->second;
		char* sValue = _GetBufString(nPos);
		fResult = (float)atof(sValue);
		return TRUE;
	}

	return FALSE;
	__UNGUARD__
	return FALSE;
}

BOOL Configer::_GetText(const char *section, const char *key, char *str, int32 size )
{
	__GUARD__

	ConfigerSectionHashMap::iterator it = m_SectionData.find(section);
	if( it == m_SectionData.end() )
		return FALSE;

	ConfigerValueHashMap* pSection = it->second;
	if( pSection != NULL )
	{
		ConfigerValueHashMap::iterator it2 = pSection->find(std::string(key));
		if( it2 == pSection->end() )
			return FALSE;

		int nPos = it2->second;
		char* sValue = _GetBufString(nPos);
		size_t nValueLen = strlen(sValue);
		strncpy( str, sValue, nValueLen );
		size_t nSize = nValueLen > size-1 ? size-1 : nValueLen;
		str[nSize] = 0;

		return TRUE;
	}

	return FALSE;
	__UNGUARD__
	return FALSE;
}

void Configer::_TrimString( char* buf )
{
	__GUARD__

	if( buf[strlen(buf)-1] == '\r' )
	{
		buf[strlen(buf)-1] = 0;
	}

	size_t i;
	for( i=0; i<strlen(buf); i++ )
	{
		if( buf[i] == CONFIGER_NOTE )
		{
			buf[i] = '\0';
			break;
		}
	}

	for( i=strlen(buf)-1; i>=0; i-- )
	{
		if( buf[i]==' ' || buf[i]=='\t' )
		{
			buf[i] = 0;
		}
		else
			break;
	}

	__UNGUARD__
}

BOOL Configer::_ParseSection( char* buf, char** pSection )
{
	__GUARD__

	if( buf[0] != '[' )
		return FALSE;

	char* pFind = strchr( buf, ']' );
	if( pFind != NULL )
	{
		pFind[0] = 0;
		*pSection = buf+1;
		return TRUE;
	}

	return FALSE;
	__UNGUARD__
	return FALSE;
}

BOOL Configer::_ParseKey( char* buf, char** sKey, char** sValue )
{
	__GUARD__

	char* pFind = strchr( buf, '=' );
	if( pFind != NULL )
	{
		pFind[0] = 0;
		*sKey = buf;
		*sValue = pFind + 1;
		return TRUE;
	}

	return FALSE;
	__UNGUARD__
	return FALSE;
}

void Configer::_ResizeBuf()
{
	__GUARD__
	m_nBufMaxLen *= 2;
	m_pBuf = (char*)realloc(m_pBuf,m_nBufMaxLen);
	if( m_pBuf == NULL )
		KCheck(FALSE);
	__UNGUARD__
}

char* Configer::_GetBufString(int32 nPos)
{
	__GUARD__
	return m_pBuf+nPos;
	__UNGUARD__
}

int32 Configer::_AddBufString(char* str)
{
	__GUARD__

	int32 nPos;
	size_t nSize = strlen(str);
	if( m_nBufLen+nSize+1 >= m_nBufMaxLen )
		_ResizeBuf();

	memcpy( m_pBuf+m_nBufLen, str, nSize+1 );
	nPos = m_nBufLen;
    m_nBufLen += ( int32)nSize + 1;
	return nPos;

	__UNGUARD__
	return 0;
}
