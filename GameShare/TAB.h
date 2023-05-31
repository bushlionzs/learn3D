
#ifndef _TAB_H_
#define _TAB_H_

#include "Define.h"

typedef int64_t table_int_t;
typedef double  table_float_t;
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
		uint32_t	m_Identify;
		int32_t		m_nFieldsNum;
		int32_t		m_nRecordsNum;
		int32_t		m_nStringBlockSize;
	};

	enum FIELD_TYPE { T_INT = 0, T_FLOAT = 1, T_STRING = 2, };

	typedef std::vector<FIELD_TYPE>	FILEDS_TYPE;

	union FIELD
	{
		table_float_t		fValue;
		table_int_t		iValue;
		const char	*pString;

		FIELD()
		{
		}
		FIELD(table_int_t value)
		{
			iValue = value;
		}
		FIELD (table_float_t value)
		{
			fValue = value;
		}
		FIELD (const char *value)
		{
			pString = value;
		}
	};

	typedef std::vector<FIELD>	DATA_BUF;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	TABFile() {}
	// ���ļ��д�
	bool	OpenFromTXT(const char *szFileName);
	// ���ڴ��д�
	bool	OpenFromMemory(const char *pMemory, const char *pDeadEnd, const char *szFileName = 0);

	void   SaveToTXT(const char* szFileName);
protected:
	bool	OpenFromMemoryImpl_Text(const char *pMemory, const char *pDeadEnd, const char *szFileName = 0);

	bool	OpenFromMemoryImpl_Binary(const char *pMemory, const char *pDeadEnd, const char *szFileName = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	// ������������nValue��ֵ�� û���ҵ�����0
	virtual const FIELD	*Search_Index_EQU(int32_t nValue) const;
	// ����ֵ nRecordLine �У�ColumNum ��
	virtual const FIELD	*Search_Posistion(int32_t nRecordLine, int32_t nColumNum) const;
	// ����nColumnNum�е�һ������value��ֵ�� û���ҵ�����0
	virtual const FIELD	*Search_First_Column_Equ(int32_t nColumnNum, const FIELD &value) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	// û���õ�
	uint32_t GetID(void) const
	{
		return m_ID;
	}

	// ��
	int32_t GetFieldsNum(void) const
	{
		return m_nFieldsNum;
	}

	// ��Ч����
	int32_t GetRecordsNum(void) const
	{
		return m_nRecordsNum;
	}

	// ��ĳһ�д���hash������������ҡ�Ĭ���ǰѵ�һ�д���Ϊ����
	void	CreateIndex(int32_t nColum = 0, const char *szFileName = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	typedef std::unordered_map<int32_t, FIELD*>	FIELD_HASHMAP;
	uint32_t m_ID;

	FILEDS_TYPE m_theType;

	int32_t m_nRecordsNum;

	int32_t m_nFieldsNum;

	DATA_BUF m_vDataBuf;

	char *m_pStringBuf;

	int32_t m_nStringBufSize;

	FIELD_HASHMAP m_hashIndex;

	int32_t m_nIndexColum;

	char m_szFileName[MAX_FILE_PATH];

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	static int32_t		_ConvertStringToVector
				(
					const char		*strStrINTgSource,
					std::vector<std::string>	&vRet,
					const char		*szKey,
					bool bOneOfKey,
					bool bIgnoreEmpty
				);

	static const char	*_GetLineFromMemory
				(
					char	*pStringBuf,
					int32_t nBufSize,
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
	TABFile(uint32_t id);
	virtual ~TABFile();
};
}
#endif
