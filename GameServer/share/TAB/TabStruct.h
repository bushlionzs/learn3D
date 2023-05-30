#ifndef __TAB_STRUCT_H__
#define __TAB_STRUCT_H__

#include "TypeDefine.h"

// 表格模板类，目前只有TabDefine_Share用到
template <class TYPE,int32 MAXSIZE>
class TabTemplate
{
public:
	TabTemplate()
	{
		memset( m_TableExt, 0, sizeof(m_TableExt) );
		m_Count = 0;
	}

	~TabTemplate() {}

	int32	GetSize()
	{
		return m_Count;
	}

	void	SetSize(int32 nSize)
	{
		m_Count = nSize;
	}

	int32	GetMaxSize()
	{
		return MAXSIZE;
	}

	TYPE*	GetData()
	{
		return m_TableExt;
	}

	TYPE*	GetData(int32 nIndex)
	{
		KCheck( nIndex>=0 && nIndex<m_Count );
		return &(m_TableExt[nIndex]);
	}

public:
	TYPE	m_TableExt[MAXSIZE];
	int32	m_Count;
};


/*
 =======================================================================================================================
 =======================================================================================================================
 */
class SplitStringLevelOne;
class SplitStringLevelTwo;
int32	CommonStringSplit
	(
		SplitStringLevelOne	*pSplitL1,
		SplitStringLevelTwo	*pSplitL2,
		const char		*pSplitString,
		int32 iMaxNum,
		int32 *pArry
	);

#endif