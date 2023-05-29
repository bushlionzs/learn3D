/*$T Common/Array_Base.h GC 1.140 10/10/07 10:06:26 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef Array_Base_h__
#define Array_Base_h__

#include "TypeDefine.h"
#include <malloc.h>

template<class T>
class Array_Base
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Array_Base(int32 iSize = 0, void* pAlloc = NULL)
	{
		m_pArray = 0;
		if (iSize > 0)
		{
			if (pAlloc)
			{
				m_pArray = (T*)pAlloc;
				for (int32 i = 0; i < iSize; ++i)
				{
					new(&m_pArray[i]) T;
				}
				m_pAlloc = pAlloc;
			}
			else
			{
				m_pArray = new T[iSize];
				m_pAlloc = NULL;
			}
		}
		m_iCurSize = 0;
		m_iMaxSize = iSize;
	}

	~Array_Base()
	{
		if (m_pAlloc)
		{
			for (int32 i = 0; i < m_iMaxSize; ++i)
			{
				if (&m_pArray[i])
				{
					(&m_pArray[i])->~T();
				}
			}

			m_pAlloc = NULL;
		}
		else
		{
			KSafeDelete_ARRAY(m_pArray);
		}
	}

	void			Reserve(int32 iSize, void* pAlloc = NULL)
	{
		m_pArray = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (iSize > 0)
		{
			if (pAlloc)
			{
				m_pArray = (T*)pAlloc;
				for (int32 i = 0; i < iSize; ++i)
				{
					new(&m_pArray[i]) T;
				}

				m_pAlloc = pAlloc;
			}
			else
			{
				m_pArray = new T[iSize];
				m_pAlloc = NULL;
			}
		}

		m_iCurSize = 0;
		m_iMaxSize = iSize;
	}

	int32			GetSize() const
	{
		return m_iCurSize;
	}

	int32			GetMaxSize() const
	{
		return m_iMaxSize;
	}

	void			RemoveAll()
	{
		m_iCurSize = 0;
	}

	void			Remove(int32 iIndex)
	{
		KCheck(iIndex >= 0 && iIndex < m_iCurSize);
		m_pArray[iIndex] = m_pArray[m_iCurSize - 1];
		--m_iCurSize;
	}

	BOOL			Add(const T& value)
	{
		if (m_iCurSize >= m_iMaxSize) return FALSE;
		m_pArray[m_iCurSize++] = value;
		return TRUE;
	}

	const T& Get(int32 iIndex) const
	{
		KCheck(iIndex >= 0 && iIndex < m_iCurSize);
		return m_pArray[iIndex];
	}
	T& Get(int32 iIndex)
	{
		KCheck(iIndex >= 0 && iIndex < m_iCurSize);
		return m_pArray[iIndex];
	}
	T& operator		[](int32 iIndex)
	{
		KCheck(iIndex >= 0 && iIndex < m_iCurSize);
		return m_pArray[iIndex];
	}
	const T& operator	[](int32 iIndex) const
	{
		KCheck(iIndex >= 0 && iIndex < m_iCurSize);
		return m_pArray[iIndex];
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Array_Base<T> &operator=(const Array_Base<T> &value)
	{
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	Array_Base(const Array_Base<T> &value)
	{
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	T	*m_pArray;
	void	*m_pAlloc;
	int32	m_iMaxSize;
	int32	m_iCurSize;
};

#include "Array_Base.cpp"
#endif
