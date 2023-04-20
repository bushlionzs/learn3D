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
    字段数据类型 ;
    enum TABLE_FIELD_TYPE ;
    { ;
    T_INT = 0, // 整数 ;
    T_FLOAT = 1, // 浮点数 ;
    T_STRING = 2, // 字符串 ;
    };
    ;
    数据段 ;
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

	/* 数据获取 */
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
	/* 记录ID */
	int32		GetID(void) const;

	/* 记录列数 */
	uint32	GetFieldsNum(void) const;

	/* 记录条数 */
	uint32	GetRecordsNum(void) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 打开文件 */
	static BOOL		OpenTableMemory(LPCTSTR szFileName, TAB::TABFile * pDBCFile, BOOL bPackRes);
	static BOOL		OpenTableText(LPCTSTR szFileName, TAB::TABFile * pDBCFile);

	/*
	 * 切割字符串，将用“|”分割的字符串顺序拆分出来，并输出需求的字符。
	 * 参数：(需要解析的字符串， 第几块数据， 输出的字符串
	 */
	static String	GetSplitData(LPCTSTR szData, uint32 nCount);

	/*
	* 切割字符串，将用“|”分割的字符串顺序拆分出来，并输出需求的字符。
	* 参数：(需要解析的字符串， 输出结果，分隔符1，分隔符2
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
	/* 文本数据 */
	BOOL		OpenFromTXT(LPCTSTR szFileName, BOOL bSpecial, BOOL bPackRes);

	/* 查找字符串中 指定字符的 第某个位置, 返回为字符串下标 */
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
    定义数据库快捷方式
 =======================================================================================================================
 */
#define TABLE_DEFINEHANDLE(nameDBC, idDBC) \
	const static CGameTable	 *nameDBC = NULL; \
	if(NULL == GAME_TABLE_MANAGER_PTR) \
		nameDBC = NULL; \
	else \
		nameDBC = GAME_TABLE_MANAGER_PTR->GetTable(idDBC);
#endif /* _GAME_TABLE_H_ */
