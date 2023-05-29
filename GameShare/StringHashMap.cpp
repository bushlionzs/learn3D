/*$T MapServer/Server/Base/StringHashMap.cpp GC 1.140 10/10/07 10:07:21 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "StringHashMap.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

StringHashMap::StringHashMap()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_pTable = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;
	m_StringSize = 0;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
StringHashMap::~StringHashMap()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete_ARRAY(m_pTable);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_Count = 0;
	m_StringSize = 0;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void StringHashMap::InitTable(uint32 uMaxItem, uint32 uSize)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_Count = uMaxItem;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_StringSize = uSize;
	KSafeDelete_ARRAY(m_pTable);
	m_pTable = new STableItemStr[m_Count];
	KCheck(m_pTable);

	for(uint32 i = 0; i < m_Count; i++)
	{
		m_pTable[i].m_pString = new char[m_StringSize];
		memset(m_pTable[i].m_pString, 0, sizeof(char) * m_StringSize);

		m_pTable[i].m_pPtr = NULL;
		m_pTable[i].m_Status = STRTS_EMPTY;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL StringHashMap::Add(const char *szString, void *pPtr)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	id = KLCRC(szString);
	uint32			c = (id / 4) % m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_Count; i++)
	{
		if(m_pTable[c].m_Status == STRTS_SET)
		{
			c++;
			if(c >= m_Count) c = 0;

			continue;
		}

		if(m_pTable[c].m_pString == NULL)
		{
			m_pTable[c].m_pString = new char[m_StringSize];
		}

		memset(m_pTable[c].m_pString, 0, sizeof(char) * m_StringSize);
		strncpy(m_pTable[c].m_pString, szString, m_StringSize - 1);

		m_pTable[c].m_pPtr = pPtr;
		m_pTable[c].m_Status = STRTS_SET;

		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void *StringHashMap::Get(const char *szString)
{
	__GUARD__ if(szString == NULL || szString[0] == 0)
	{
		return NULL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	id = KLCRC(szString);
	uint32	c = (id / 4) % m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_Count; i++)
	{
		if(m_pTable[c].m_Status == STRTS_EMPTY)
		{
			return NULL;
		}
		else if(m_pTable[c].m_Status == STRTS_USE)
		{
			c++;
			if(c >= m_Count) c = 0;
			continue;
		}

		if(strcmp(m_pTable[c].m_pString, szString) == 0)
		{
			return m_pTable[c].m_pPtr;
		}

		c++;
		if(c >= m_Count) c = 0;
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void StringHashMap::Remove(const char *szString)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	id = KLCRC(szString);
	uint32			c = (id / 4) % m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_Count; i++)
	{
		if(m_pTable[c].m_Status == STRTS_EMPTY)
		{
			return;
		}
		else if(m_pTable[c].m_Status == STRTS_USE)
		{
			c++;
			if(c >= m_Count) c = 0;
			continue;
		}

		if(strcmp(m_pTable[c].m_pString, szString) == 0)
		{
			memset(m_pTable[c].m_pString, 0, sizeof(char) * m_StringSize);
			m_pTable[c].m_pPtr = NULL;
			m_pTable[c].m_Status = STRTS_USE;

			return;
		}

		c++;
		if(c >= m_Count) c = 0;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void StringHashMap::Clear()
{
	__GUARD__ if(m_pTable == NULL) return;

	for(uint32 i = 0; i < m_Count; i++)
	{
		memset(m_pTable[i].m_pString, 0, sizeof(char) * m_StringSize);
		m_pTable[i].m_pPtr = NULL;
		m_pTable[i].m_Status = STRTS_EMPTY;
	}

	__UNGUARD__
}
