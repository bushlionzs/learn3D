/*$T MapServer/Server/Base/StringHashMap.h GC 1.140 10/10/07 10:07:21 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __STRTABLE_H__
#define __STRTABLE_H__

#include "TypeDefine.h"

struct STableItemStr
{
	char	*m_pString;
	void	*m_pPtr;
	uint32	m_Status;

	STableItemStr()
	{
		m_pString = NULL;
		m_pPtr = NULL;
		m_Status = 0;
	}
	~STableItemStr()
	{
		KSafeDelete_ARRAY(m_pString);
		m_pPtr = NULL;
		m_Status = 0;
	}
};

class	StringHashMap
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	StringHashMap();
	~	StringHashMap();

	void	InitTable(uint32 uMaxItem, uint32 uSize);

	BOOL	Add(const char *szString, void *pPtr);

	void	*Get(const char *szString);

	void	Remove(const char *szString);

	void	Clear();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { STRTS_EMPTY = 0, STRTS_SET = 1, STRTS_USE = 2, };

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	STableItemStr	*m_pTable;
	uint32		m_Count;
	uint32		m_StringSize;
};
#endif
