/*$T Common/TAB/TAB.h GC 1.140 10/10/07 10:06:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _TAB_H_
#define _TAB_H_

#include <vector>
#include <unordered_map>
#include "TypeDefine.h"

namespace	TAB
{
class	TABFile
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	struct FILE_HEAD
	{
		uint32	m_Identify;
		int32	m_nFieldsNum;
		int32	m_nRecordsNum;
		int32	m_nStringBlockSize;
	};

	enum FIELD_TYPE { T_INT = 0, T_FLOAT = 1, T_STRING = 2, };

	typedef vector<FIELD_TYPE>	FILEDS_TYPE;

	union FIELD
	{
		float		fValue;
		int32		iValue;
		const char	*pString;

		FIELD()
		{
		}
		FIELD(int32 value)
		{
			iValue = value;
		}
		FIELD (float value)
		{
			fValue = value;
		}
		FIELD (const char *value)
		{
			pString = value;
		}
	};

	typedef vector<FIELD>	DATA_BUF;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	// ���ļ��д�
	BOOL	OpenFromTXT(const char *szFileName);
	// ���ڴ��д�
	BOOL	OpenFromMemory(const char *pMemory, const char *pDeadEnd, const char *szFileName = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	OpenFromMemoryImpl_Text(const char *pMemory, const char *pDeadEnd, const char *szFileName = 0);

	BOOL	OpenFromMemoryImpl_Binary(const char *pMemory, const char *pDeadEnd, const char *szFileName = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	// ������������nValue��ֵ�� û���ҵ�����0
	virtual const FIELD	*Search_Index_EQU(int32 nValue) const;
	// ����ֵ nRecordLine �У�ColumNum ��
	virtual const FIELD	*Search_Posistion(int32 nRecordLine, int32 nColumNum) const;
	// ����nColumnNum�е�һ������value��ֵ�� û���ҵ�����0
	virtual const FIELD	*Search_First_Column_Equ(int32 nColumnNum, const FIELD &value) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	// û���õ�
	uint32 GetID(void) const
	{
		return m_ID;
	}

	// ��
	int32 GetFieldsNum(void) const
	{
		return m_nFieldsNum;
	}

	// ��Ч����
	int32 GetRecordsNum(void) const
	{
		return m_nRecordsNum;
	}

	// ��ĳһ�д���hash������������ҡ�Ĭ���ǰѵ�һ�д���Ϊ����
	void	CreateIndex(int32 nColum = 0, const char *szFileName = 0);

	void   SaveToTXT(const char* szFileName);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	typedef std::unordered_map<int32, FIELD *>	FIELD_HASHMAP;
	uint32 m_ID;

	FILEDS_TYPE m_theType;

	int32 m_nRecordsNum;

	int32 m_nFieldsNum;

	DATA_BUF m_vDataBuf;

	char *m_pStringBuf;

	int32 m_nStringBufSize;

	FIELD_HASHMAP m_hashIndex;

	int32 m_nIndexColum;

	char m_szFileName[MAX_FILE_PATH];

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static int32		_ConvertStringToVector
				(
					const char		*strStrINTgSource,
					vector<std::string>	&vRet,
					const char		*szKey,
					BOOL bOneOfKey,
					BOOL bIgnoreEmpty
				);

	static const char	*_GetLineFromMemory
				(
					char	*pStringBuf,
					int32 nBufSize,
					const char *pMemory,
					const char *pDeadEnd
				);

	template<FIELD_TYPE T>
	static bool _FieldEqu(const FIELD & a, const FIELD & b);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	TABFile(uint32 id);
	virtual ~TABFile();
};
}
#endif
