/*$T Common/List.h GC 1.140 10/10/07 10:06:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __LIST_H__
#define __LIST_H__

#include "TypeDefine.h"

class	CListHeader;
class	CListItem
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CListHeader	*m_pHead;
	CListItem	*m_pNext;
	CListItem	*m_pPrevious;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CListItem();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual~CListItem()
	{ ;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPrevious(CListItem *pItem)
	{
		m_pPrevious = pItem;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetNext(CListItem *pItem)
	{
		m_pNext = pItem;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetHeader(CListHeader *pHeader)
	{
		m_pHead = pHeader;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListHeader *GetHeader()
	{
		return m_pHead;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *GetNext()
	{
		return m_pNext;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *GetPrevious()
	{
		return m_pPrevious;
	}

	void	DisConnect();
};

class CListHeader :
	public CListItem
{
	friend class	CListItem;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	uint32		m_uNum;
	CListItem	*m_pEnd;
	CListItem	*m_pHead;
	CListItem	*m_pCurrent;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CListHeader();
	virtual		~CListHeader();

	CListItem	*MoveTo(int32 i);
	BOOL		Add(CListItem *pItem);
	BOOL		Insert(CListItem *pItem);
	BOOL		InsertBeforeCurrent(CListItem *pItem);
	BOOL		InsertAfterCurrent(CListItem *pItem);
	CListItem	*Remove();
	CListItem	*OutChain();
	BOOL		RemoveAll();
	BOOL		OutAll();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetNum()
	{
		return m_uNum;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetNum(uint32 uNum)
	{
		m_uNum = uNum;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *First()
	{
		m_pCurrent = m_pHead;
		return m_pCurrent;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *Next()
	{
		if(!m_pCurrent) return NULL;
		m_pCurrent = m_pCurrent->GetNext();
		return m_pCurrent;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *NextCycle()
	{
		if(!m_pCurrent)
			m_pCurrent = m_pHead;
		else if(m_pCurrent == m_pEnd)
			m_pCurrent = m_pHead;
		else
			m_pCurrent = m_pCurrent->GetNext();

		return m_pCurrent;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *ViewFirst()
	{
		return m_pHead;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *ViewNext()
	{
		if(!m_pCurrent) return NULL;
		return m_pCurrent->GetNext();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CListItem *Last()
	{
		m_pCurrent = m_pEnd;
		return m_pCurrent;
	}

	CListItem	*Previous();
	CListItem	*PreviousCycle();
	CListItem	*ViewPrevious();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	CListItem *Current()
	{
		return m_pCurrent;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetCurrent(CListItem *pItem)
	{
		m_pCurrent = pItem;
	}

	int32	Get(CListItem *pItem);
};
#endif