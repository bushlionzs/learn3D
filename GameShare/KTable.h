#ifndef _GAME_TABLE_H_
#define _GAME_TABLE_H_

#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "tab.h"

/*
 =======================================================================================================================
    enum eOPTRESULT;
 =======================================================================================================================
 */
class	CGameTable
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	friend class	CGameTableManager;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
/*
 -----------------------------------------------------------------------------------------------------------------------
    �ֶ��������� ;
    enum TABLE_FIELD_TYPE ;
    { ;
    T_INT = 0, // ���� ;
    T_FLOAT = 1, // ������ ;
    T_STRING = 2, // �ַ��� ;
    };
    ;
    ���ݶ� ;
    union TABLE_FIELD_DATA ;
    { ;
    FLOAT fValue;
    int32 iValue;
    const char* pString;
    // Just for runtime! ;
    // Construct ;
    TABLE_FIELD_DATA( void ) {} ;
    TABLE_FIELD_DATA( int32 value ) { iValue = value;
    } ;
    TABLE_FIELD_DATA( FLOAT value ) { fValue = value;
    } ;
    TABLE_FIELD_DATA( const char* value ) { pString = value;
    } ;
    };
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CGameTable(int32 nId);
	~	CGameTable(void);

	/* ���ݻ�ȡ */
	const TAB::TABFile *
	GetTableFile (void)
	const;

	const TAB::TABFile::FIELD *
	GetFieldDataByIndex(int32 iIndexValue)
	const;
	const TAB::TABFile::FIELD *
	GetFieldDataByLine(int32 nLine, int32 nColum = 0)
	const;
	const TAB::TABFile::FIELD *
	GetFieldDataByFirstColumn(int32 nColumnNum, const TAB::TABFile::FIELD & value)
	const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* ��¼ID */
	int32		GetID(void) const;

	/* ��¼���� */
	uint32	GetFieldsNum(void) const;

	/* ��¼���� */
	uint32	GetRecordsNum(void) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* ���ļ� */
	static BOOL		OpenTableMemory(LPCTSTR szFileName, TAB::TABFile * pDBCFile, BOOL bPackRes);
	static BOOL		OpenTableText(LPCTSTR szFileName, TAB::TABFile * pDBCFile);

	/*
	 * �и��ַ��������á�|���ָ���ַ���˳���ֳ����������������ַ���
	 * ������(��Ҫ�������ַ����� �ڼ������ݣ� ������ַ���
	 */
	static String	GetSplitData(LPCTSTR szData, uint32 nCount);

	/*
	* �и��ַ��������á�|���ָ���ַ���˳���ֳ����������������ַ���
	* ������(��Ҫ�������ַ����� ���������ָ���1���ָ���2
	*/
	static void	SplitData(LPCTSTR szSrcData,
		std::vector<String>& vecStrResult,
		const char cSpliter1='|',
		const char cSpliter2 = '~');

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* �ı����� */
	BOOL		OpenFromTXT(LPCTSTR szFileName, BOOL bSpecial, BOOL bPackRes);

	/* �����ַ����� ָ���ַ��� ��ĳ��λ��, ����Ϊ�ַ����±� */
	static int32	GetCharOff(const char *szStr, const char ch, uint32 nCount);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	TAB::TABFile * m_pTableFile;
private:
	static SplitStringLevelOne m_SplitL1;
	static SplitStringLevelTwo m_SplitL2;
};

/*
 =======================================================================================================================
    class ;
    �������ݿ��ݷ�ʽ
 =======================================================================================================================
 */
#define TABLE_DEFINEHANDLE(nameDBC, idDBC) \
	const static CGameTable	 *nameDBC = NULL; \
	if(NULL == GAME_TABLE_MANAGER_PTR) \
		nameDBC = NULL; \
	else \
		nameDBC = GAME_TABLE_MANAGER_PTR->GetTable(idDBC);
#endif /* _GAME_TABLE_H_ */
