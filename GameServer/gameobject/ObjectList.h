/*$T MapServer/Server/Obj/ObjectList.h GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __OBJLIST_H__
#define __OBJLIST_H__

#include "TypeDefine.h"

class	Object;

struct _INIT_LIST_NODE
{
	Object		*m_pNode;
	_INIT_LIST_NODE	*m_pNext;
	_INIT_LIST_NODE	*m_pPrev;

	_INIT_LIST_NODE()
	{
		m_pNode = NULL;
		m_pNext = NULL;
		m_pPrev = NULL;
	}
	_INIT_LIST_NODE(Object * pNode)
	{
		m_pNode = pNode;
		m_pNext = NULL;
		m_pPrev = NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_pNode = NULL;
		m_pNext = NULL;
		m_pPrev = NULL;
	};
};

struct ObjectList
{
public:
	_INIT_LIST_NODE	m_Head;
	_INIT_LIST_NODE	m_Tail;
	int32		m_nSize;
public:
	ObjectList()
	{
		m_nSize = 0;

		m_Head.m_pNext = &m_Tail;
		m_Head.m_pPrev = &m_Head;
		m_Tail.m_pNext = &m_Tail;
		m_Tail.m_pPrev = &m_Head;
	}
	~ObjectList()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Head.Clear();
		m_Tail.Clear();
		m_nSize = 0;
		m_Head.m_pNext = &m_Tail;
		m_Head.m_pPrev = &m_Head;
		m_Tail.m_pNext = &m_Tail;
		m_Tail.m_pPrev = &m_Head;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL AddNode(_INIT_LIST_NODE *pNode)
	{
		__GUARD__	
		KCheck(pNode);	
		KCheck(pNode->m_pPrev == NULL);
		KCheck(pNode->m_pNext == NULL);

		pNode->m_pNext = &m_Tail;
		pNode->m_pPrev = m_Tail.m_pPrev;
		m_Tail.m_pPrev->m_pNext = pNode;
		m_Tail.m_pPrev = pNode;

		m_nSize++;

		__UNGUARD__ return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL DeleteNode(_INIT_LIST_NODE *pNode)
	{
		__GUARD__

		char Msg[32] = {0};
		sprintf(Msg, "pNode=%p,size=%d", pNode, m_nSize);

		KCheckEx(pNode, Msg);
		KCheckEx(pNode->m_pPrev != NULL, Msg);
		KCheckEx(pNode->m_pNext != NULL, Msg);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_INIT_LIST_NODE	*pPoint = m_Head.m_pNext;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheckEx(pPoint, Msg);

		while(pPoint != &m_Tail)
		{
			if(pPoint == pNode)
			{
				pPoint->m_pPrev->m_pNext = pPoint->m_pNext;
				pPoint->m_pNext->m_pPrev = pPoint->m_pPrev;
				pPoint->m_pNext = NULL;
				pPoint->m_pPrev = NULL;

				m_nSize--;
				return TRUE;
			}
			else
			{
				pPoint = pPoint->m_pNext;
				KCheckEx(pPoint,Msg);
			}
		}

		KCheckEx(FALSE,Msg);

		__UNGUARD__ return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetSize()
	{
		return m_nSize;
	}
};
#endif
