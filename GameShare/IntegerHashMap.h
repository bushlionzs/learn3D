/*$T MapServer/Server/Base/IntegerHashMap.h GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __IDTABLE_H__
#define __IDTABLE_H__

#include "TypeDefine.h"

#include <unordered_map>
struct STableItem
{
	uint32	m_ID;
	void	*m_pPtr;
	uint32	m_Status;
};

class	IntegerHashMap
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	typedef std::unordered_map<uint32, void *>	IDTableHashMap;

	typedef IDTableHashMap::iterator		IDTableIterator;
	IntegerHashMap();
	~						IntegerHashMap();

	void						InitTable(uint32 MaxItem);

	BOOL						Add(uint32 id, void *pPtr);

	void						*Get(uint32 id);

	BOOL						Remove(uint32 id);

	void						Clear();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetCount()
	{
		return(uint32) m_IDTableHashMap.size();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetMaxCount()
	{
		return m_MaxCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	IDTableIterator Begin()
	{
		m_CurrentIterator = m_IDTableHashMap.begin();
		return m_CurrentIterator;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	IDTableIterator End()
	{
		return m_IDTableHashMap.end();
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	IDTableHashMap m_IDTableHashMap;
	IDTableIterator m_CurrentIterator;
	uint32 m_MaxCount;
};
#endif