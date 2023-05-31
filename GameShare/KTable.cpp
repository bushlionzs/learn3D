#include "OgreHeader.h"
#include "KTable.h"
#include "OgreResourceManager.h"
#include "ku.h"
extern ku::CKU gUtil;
extern int	g_nProcess;
SplitStringLevelOne CGameTable::m_SplitL1;
SplitStringLevelTwo CGameTable::m_SplitL2;
/*
 =======================================================================================================================
 =======================================================================================================================
 */
CGameTable::CGameTable(int32 id)
{
	m_pTableFile = new TAB::TABFile(id);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CGameTable::~CGameTable()
{
	if(m_pTableFile)
	{
		delete m_pTableFile;
		m_pTableFile = NULL;
	}
}

const TAB::TABFile * CGameTable::GetTableFile (void) const
{
	return m_pTableFile;
}
const TAB::TABFile::FIELD * CGameTable::GetFieldDataByIndex(int32 iIndexValue) const
{
	return(TAB::TABFile::FIELD *) m_pTableFile->Search_Index_EQU(iIndexValue);
}
const TAB::TABFile::FIELD * CGameTable::GetFieldDataByLine(int32 nLine, int32 nColum) const
{
	return(TAB::TABFile::FIELD *) m_pTableFile->Search_Posistion(nLine, nColum);
}
const TAB::TABFile::FIELD *
	CGameTable::GetFieldDataByFirstColumn(int32 nColumnNum, const TAB::TABFile::FIELD & value) const
	{
		return(TAB::TABFile::FIELD *) m_pTableFile->Search_First_Column_Equ(nColumnNum, value.iValue);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CGameTable::GetID(void) const
{
	return m_pTableFile->GetID();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 CGameTable::GetFieldsNum(void) const
{
	return m_pTableFile->GetFieldsNum();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 CGameTable::GetRecordsNum(void) const
{
	return m_pTableFile->GetRecordsNum();
}

/*
 =======================================================================================================================
    打开文件
 =======================================================================================================================
 */
BOOL CGameTable::OpenTableMemory(LPCTSTR szFileName, TAB::TABFile * pDBCFile, BOOL bPackRes)
{
	TCHAR	szTmp[MAX_PATH] = { 0 };

	snprintf(szTmp, MAX_PATH, "10003 %s", szFileName);

	std::shared_ptr<DataStream> stream = 
		ResourceManager::getSingleton().openResource(szFileName);
	DWORD	dwSize = stream->getStreamLength();

	if(dwSize <= 0) return FALSE;

	BOOL	bRet = FALSE;

	const char* lpAddress = stream->getStreamData();

	if (FALSE == bPackRes)
	{
		bRet = pDBCFile->OpenFromMemory(lpAddress, lpAddress + dwSize + 1, szFileName );
	}
	else
	{
		DWORD	dwBufSize = dwSize;
		char	*bufTarget = new char[dwBufSize + 1];
		memset(bufTarget, 0, dwBufSize + 1);

		gUtil.FileConversion( lpAddress, bufTarget, dwBufSize, false, g_nProcess + 3 );	// 8
		bufTarget[dwBufSize] = 0;

		bRet = pDBCFile->OpenFromMemory(bufTarget, bufTarget + dwBufSize + 1);
	}

	return bRet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CGameTable::OpenTableText(LPCTSTR szFileName, TAB::TABFile *pDBCFile)
{
	BOOL	bRet = pDBCFile->OpenFromTXT(szFileName);

	return bRet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CGameTable::OpenFromTXT(LPCTSTR szFileName, BOOL bSpecial, BOOL bPackRes)
{
	if(bSpecial) return OpenTableText(szFileName, m_pTableFile);

	return OpenTableMemory(szFileName, m_pTableFile, bPackRes);
}

/*
 =======================================================================================================================
    nCount 从1开始
 =======================================================================================================================
 */
String CGameTable::GetSplitData(LPCTSTR szData, uint32 nCount)
{
	if (NULL == szData)
	{
		return std::string();
	}

	/* 起始位置 */
	int32 off1 = 0;

	if(nCount > 1)
	{
		off1 = GetCharOff(szData, '|', nCount - 1);
		if(0 != off1) ++off1;
	}

	/* 结束位置 */
	int32 off2 = GetCharOff(szData, '|', nCount);

	if(off2 <= off1)
	{
		off2 = (int32) strlen(szData);
	}

	/* 拷贝之间的字符串 */
	int32 copySize = off2 - off1;

	if(0 < copySize)
	{
		String	str(szData);

		return str.substr(off1, copySize);
	}

	return "";
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void CGameTable::SplitData(LPCTSTR szSrcData,
					  std::vector<String>& vecStrResult,
					  const CHAR cSpliter1,
					  const CHAR cSpliter2)
{
	const char* pSplitString = szSrcData;

	vecStrResult.clear();

	if (NULL != pSplitString)
	{
		m_SplitL1.Reset();
		m_SplitL2.Reset();
		m_SplitL1.Init(cSpliter1,&m_SplitL2);
		m_SplitL2.Init(cSpliter2,NULL);

		m_SplitL1.DoSplit(pSplitString);
		
		int32 iSplitCount = m_SplitL2.GetResultLineCount();
		
		if (iSplitCount>0)
		{
			vecStrResult.resize(iSplitCount);

			for(int32 i = 0; i < iSplitCount;++i)
			{
				vecStrResult[i]= m_SplitL2.GetResultLine(i);			
			}			
		}
	}

}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CGameTable::GetCharOff(const char *szStr, const char ch, uint32 uCount)
{
	if(NULL == szStr) return -1;

	uint32	uNum = 0, uIndex = 0, uSize = (uint32) strlen(szStr);

	for(uint32 i = 0; i < uSize; ++i)
	{
		if(ch == szStr[i])
		{
			++uNum;
			uIndex = i;

			/* 找到第uCount个ch，返回位置 */
			if(uNum >= uCount) return i;
		}
	}

	/* 返回最后一个ch的位置 */
	return uIndex;
}
