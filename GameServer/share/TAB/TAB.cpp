/*$T Common/TAB/TAB.cpp GC 1.140 10/10/07 10:06:57 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include <string>
#include <map>
#include <assert.h>
#include "TAB.h"
#include <exception>

namespace	TAB
{

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 TABFile::_ConvertStringToVector
(
	const char		*strStrINTgSource,
	vector<std::string>	&vRet,
	const char		*szKey,
	BOOL			bOneOfKey,
	BOOL			bIgnoreEmpty
)
{
	vRet.clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	std::string	strSrc = strStrINTgSource;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(strSrc.empty())
	{
		return 0;
	}

	std::string::size_type nLeft = 0;
	std::string::size_type nRight;
	if(bOneOfKey)
	{
		nRight = strSrc.find_first_of(szKey);
	}
	else
	{
		nRight = strSrc.find(szKey);
	}

	if(nRight == std::string::npos)
	{
		nRight = strSrc.length();
	}

	while(TRUE)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		std::string	strItem = strSrc.substr(nLeft, nRight - nLeft);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(strItem.length() > 0 || !bIgnoreEmpty)
		{
			vRet.push_back(strItem);
		}

		if(nRight == strSrc.length())
		{
			break;
		}

		nLeft = nRight + (bOneOfKey ? 1 : strlen(szKey));

		if(bOneOfKey)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			std::string	strTemp = strSrc.substr(nLeft);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nRight = strTemp.find_first_of(szKey);
			if(nRight != std::string::npos) nRight += nLeft;
		}
		else
		{
			nRight = strSrc.find(szKey, nLeft);
		}

		if(nRight == std::string::npos)
		{
			nRight = strSrc.length();
		}
	}

	return(int32) vRet.size();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<TABFile::FIELD_TYPE T>
bool TABFile::_FieldEqu(const FIELD &a, const FIELD &b)
{
	if(T == T_INT)
	{
		return a.iValue == b.iValue;
	}
	else if(T == T_FLOAT)
	{
		return a.fValue == b.fValue;
	}
	else
	{
		try
		{
			return(strcmp(a.pString, b.pString) == 0);
		}
		catch(...)
		{
			return false;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TABFile::TABFile(uint32 id)
{
	m_ID = id;
	m_pStringBuf = NULL;
	m_nIndexColum = -1;
	memset( m_szFileName, 0, MAX_FILE_PATH );
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TABFile::~TABFile()
{
	if(m_pStringBuf) KSafeDelete_ARRAY(m_pStringBuf);
	m_pStringBuf = NULL;

#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_WORLD, "[TAB] End   Load %s ! ", m_szFileName);
#elif defined __MAPSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "[TAB] End   Load %s ! ", m_szFileName);
#endif
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const char *TABFile::_GetLineFromMemory(char *pStringBuf, int32 nBufSize, const char *pMemory, const char *pDeadEnd)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	register const char	*pMem = pMemory;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMem >= pDeadEnd || *pMem == 0) return 0;

	while(pMem < pDeadEnd && pMem - pMemory + 1 < nBufSize && *pMem != 0 && *pMem != '\r' && *pMem != '\n')
		*(pStringBuf++) = *(pMem++);

	*pStringBuf = 0;

	while(pMem < pDeadEnd && *pMem != 0 && (*pMem == '\r' || *pMem == '\n')) pMem++;

	return pMem;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TABFile::OpenFromMemory(const char *pMemory, const char *pDeadEnd, const char *szFileName)
{
	assert(pMemory && pDeadEnd);

	if(pDeadEnd - pMemory >= sizeof(FILE_HEAD) && *((uint32 *) pMemory) == 0XDDBBCC00)
	{
		return OpenFromMemoryImpl_Binary(pMemory, pDeadEnd, szFileName);
	}
	else
	{
		return OpenFromMemoryImpl_Text(pMemory, pDeadEnd, szFileName);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Decrypt(const char *cSrc, char *cDest)
{
	if(0 == strcmp(cSrc, "")) return 1;

	/*~~~~~~~~~~*/
	int32	h, l;
	int32	m, n;
	int32	j = 0;
	/*~~~~~~~~~~*/

	for(size_t i = 0; i < strlen(cSrc); i = i + 2)
	{
		h = (cSrc[i] - 'x');
		l = (cSrc[i + 1] - 'z');

		m = (h << 4);
		n = (l & 0xf);

		cDest[j] = m + n;

		j++;
	}

	cDest[j] = '\0';

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TABFile::OpenFromMemoryImpl_Binary(const char *pMemory, const char *pDeadEnd, const char *szFileName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	register const char	*pMem = pMemory;
	FILE_HEAD		theHead;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(&theHead, pMem, sizeof(FILE_HEAD));
	if(theHead.m_Identify != 0XDDBBCC00)
	{
		return FALSE;
	}

	if
	(
		sizeof(FILE_HEAD) +
			sizeof(uint32) *
			theHead.m_nFieldsNum +
			sizeof(FIELD) *
			theHead.m_nRecordsNum *
			theHead.m_nFieldsNum +
			theHead.m_nStringBlockSize > (uint32) (pDeadEnd - pMemory)
	)
	{
		return FALSE;
	}

	pMem += sizeof(FILE_HEAD);

	m_nRecordsNum = theHead.m_nRecordsNum;
	m_nFieldsNum = theHead.m_nFieldsNum;
	m_nStringBufSize = theHead.m_nStringBlockSize;

	m_pStringBuf = new char[theHead.m_nStringBlockSize];
	if(!m_pStringBuf) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	vector<uint32>	vFieldType;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	vFieldType.resize(theHead.m_nFieldsNum);
	memcpy(&(vFieldType[0]), pMem, sizeof(uint32) * theHead.m_nFieldsNum);
	pMem += sizeof(uint32) * theHead.m_nFieldsNum;

	m_theType.resize(theHead.m_nFieldsNum);
	for(int32 i = 0; i < (int32) theHead.m_nFieldsNum; i++)
	{
		switch(vFieldType[i])
		{
		case T_INT:
		case T_FLOAT:
		case T_STRING:
			m_theType[i] = (FIELD_TYPE) vFieldType[i];
			break;

		default:
			KSafeDelete_ARRAY(m_pStringBuf);
			return FALSE;
		}
	}

	// ...: if theHead.m_nRecordsNum = 0, m_vDataBuf will be resized to 0,
	// and then &(m_vDataBuf[0]) will throw exception...
	// Using max to resize at least to 1
	m_vDataBuf.resize(max(theHead.m_nRecordsNum * theHead.m_nFieldsNum, 1));
	memcpy(&(m_vDataBuf[0]), pMem, sizeof(FIELD) * theHead.m_nRecordsNum * theHead.m_nFieldsNum);
	pMem += sizeof(FIELD) * theHead.m_nRecordsNum * theHead.m_nFieldsNum;

	memcpy(m_pStringBuf, pMem, m_nStringBufSize);	
	m_pStringBuf[m_nStringBufSize - 1] = 0;

	for(int32 j = 0; j < (int32) theHead.m_nFieldsNum; j++)
	{
		if(vFieldType[j] != T_STRING) continue;

		/*~~~~~~~~~~~~~~~*/
		string	str;
		int32	nFieldsNum;
		/*~~~~~~~~~~~~~~~*/

		for(int32 i = 0; i < (int32) theHead.m_nRecordsNum; i++)
		{
			nFieldsNum = GetFieldsNum();

			m_vDataBuf[i * nFieldsNum + j].pString += reinterpret_cast<uint64> (m_pStringBuf);
		}
	}

	CreateIndex(0, szFileName);

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TABFile::OpenFromMemoryImpl_Text(const char *pMemory, const char *pDeadEnd, const char *szFileName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char			szLine[1024 * 10] = { 0 };
	register const char	*pMem = pMemory;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMem = _GetLineFromMemory(szLine, 1024 * 10, pMem, pDeadEnd);
	if(!pMem) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	vector<std::string>	vRet;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	_ConvertStringToVector(szLine, vRet, "\t", TRUE, TRUE);
	if(vRet.empty()) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	FILEDS_TYPE	vFieldsType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	vFieldsType.resize(vRet.size());

	for(int32 i = 0; i < (int32) vRet.size(); i++)
	{
		if(vRet[i] == "INT" || vRet[i] == "NUM" /* ...: Support new tab file */)
			vFieldsType[i] = T_INT;
		else if(vRet[i] == "FLOAT")
			vFieldsType[i] = T_FLOAT;
		else if(vRet[i] == "STRING" || vRet[i] == "TEXT" /* ...: Support new tab file */)
			vFieldsType[i] = T_STRING;
		else if(vRet[i] == "CNC")
			vFieldsType[i] = T_STRING;
		else
		{
			return FALSE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32					nRecordsNum = 0;
	int32					nFieldsNum = (int32) vFieldsType.size();
	vector<std::pair<std::string, int32> >	vStringBuf;
	std::map<std::string, int32>		mapStringBuf;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMem = _GetLineFromMemory(szLine, 1024 * 10, pMem, pDeadEnd);
	if(!pMem) return FALSE;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32 nStringBufSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	do
	{
		pMem = _GetLineFromMemory(szLine, 1024 * 10, pMem, pDeadEnd);
		if(!pMem) break;;

		if(szLine[0] == '#') continue;

		_ConvertStringToVector(szLine, vRet, "\t", TRUE, FALSE);

		if(vRet.empty()) continue;
		if(vRet.size() != nFieldsNum)
		{
			if((int32) vRet.size() < nFieldsNum)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32 nSubNum = nFieldsNum - (int32) vRet.size();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				for(int32 i = 0; i < nSubNum; i++)
				{
					vRet.push_back("");
				}
			}
		}

		if(vRet[0].empty()) continue;

		for(register int32 i = 0; i < nFieldsNum; i++)
		{
			/*~~~~~~~~~~~*/
			FIELD newField;
			/*~~~~~~~~~~~*/

			switch(vFieldsType[i])
			{
			case T_INT:
				newField.iValue = atoi(vRet[i].c_str());
				m_vDataBuf.push_back(newField);
				break;

			case T_FLOAT:
				newField.fValue = (float) atof(vRet[i].c_str());
				m_vDataBuf.push_back(newField);
				break;

			case T_STRING:
				if(vRet[i].empty())
				{
					newField.iValue = 0;
				}
				else
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					const char				*p = vRet[i].c_str();
					std::map<std::string, int32>::iterator	it = mapStringBuf.find(vRet[i]);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(it == mapStringBuf.end())
					{
						vStringBuf.push_back(std::make_pair(vRet[i], nStringBufSize));
						mapStringBuf.insert(std::make_pair(vRet[i], (int32) vStringBuf.size() - 1));
						newField.iValue = nStringBufSize + 1;

						nStringBufSize += (int32) strlen(vRet[i].c_str()) + 1;
					}
					else
					{
						newField.iValue = vStringBuf[it->second].second + 1;
					}
				}

				m_vDataBuf.push_back(newField);
				break;
			}
		}

		nRecordsNum++;
	} while(TRUE);

	m_nRecordsNum = nRecordsNum;
	m_nFieldsNum = nFieldsNum;
	m_nStringBufSize = nStringBufSize + 1;

	m_pStringBuf = new char[m_nStringBufSize];
	if(!m_pStringBuf) return FALSE;

	m_theType = vFieldsType;

	/*~~~~~~~~~~~~~~~~~*/
	uchar byBlank = '\0';
	/*~~~~~~~~~~~~~~~~~*/

	m_pStringBuf[0] = '\0';

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	register char	*p = m_pStringBuf + 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < (int32) vStringBuf.size(); i++)
	{
		memcpy(p, vStringBuf[i].first.c_str(), vStringBuf[i].first.size());
		p += vStringBuf[i].first.size();

		*(p++) = '\0';
	}

	for(register int32 i = 0; i < nFieldsNum; i++)
	{
		if(vFieldsType[i] != T_STRING) continue;

		for(register int32 j = 0; j < nRecordsNum; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			FIELD	&theField = m_vDataBuf[j * nFieldsNum + i];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			theField.pString = m_pStringBuf + theField.iValue;
		}
	}

	CreateIndex(0, szFileName);

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL TABFile::OpenFromTXT(const char *szFileName)
{
	__GUARD__

	assert(szFileName);

#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_WORLD, "[TAB] Begin Load %s ... ", szFileName);
#elif defined __MAPSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "[TAB] Begin Load %s ... ", szFileName);
#endif

	strncpy( m_szFileName, szFileName, MAX_FILE_PATH - 1 );

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	FILE	*fp = fopen(szFileName, "rb");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == fp)
	{
#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_WORLD, "[Tab] Open File Failed! file=%s", szFileName);
#elif defined __MAPSERVER__
	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "[Tab] Open File Failed! file=%s", szFileName);
#endif
	return FALSE;
	}

	fseek(fp, 0, SEEK_END);

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32 nFileSize = ftell(fp);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	fseek(fp, 0, SEEK_SET);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	*pMemory = new char[nFileSize + 1];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fread(pMemory, 1, nFileSize, fp);
	fclose(fp);
	fp = 0;
	pMemory[nFileSize] = 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BOOL bRet = OpenFromMemory(pMemory, pMemory + nFileSize + 1, szFileName);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KSafeDelete_ARRAY(pMemory);
	pMemory = 0;
	return bRet;

	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TABFile::CreateIndex(int32 nColum, const char *szFileName)
{
	if(nColum < 0 || nColum >= m_nFieldsNum || m_nIndexColum == nColum) return;

	m_hashIndex.clear();

	for(int32 i = 0; i < (int32) m_nRecordsNum; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FIELD			*p = &(m_vDataBuf[i * m_nFieldsNum]);
		FIELD_HASHMAP::iterator itFind = m_hashIndex.find(p->iValue);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(itFind != m_hashIndex.end())
		{
			/*~~~~~~~~~~~~~*/
			char szTemp[260];
			/*~~~~~~~~~~~~~*/

			tsnprintf
			(
				szTemp,
				260,
				"[%s]Multi index at line %d(SAME:value=%d)",
				szFileName,
				i + 1,
				p->iValue
			);
#ifdef GAME_CLIENT
			throw std::exception(szTemp);
#else
			KCheckEx(FALSE, szTemp);
#endif
			return;
		}

		m_hashIndex.insert(std::make_pair(p->iValue, p));
	}
}

const TABFile::FIELD * TABFile::Search_Index_EQU(int32 iIndex) const
{
	FIELD_HASHMAP::const_iterator	itFind = m_hashIndex.find(iIndex);
	if(itFind == m_hashIndex.end()) return NULL;

	return itFind->second;
}
const TABFile::FIELD * TABFile::Search_Posistion(int32 nRecordLine, int32 nColumNum) const
{
	int32 nPosition = nRecordLine *
	GetFieldsNum()
	+ nColumNum;

	if(nPosition < 0 || nPosition >= (int32) m_vDataBuf.size())
	{
		char szTemp[260];
		tsnprintf(szTemp, MAX_FILE_PATH, "[TAB] Invalid Key! file=%s,line=%d,col=%d]", m_szFileName, nRecordLine, nColumNum);
#ifdef GAME_CLIENT
		//throw std::exception(szTemp);
#else
		KCheckEx(FALSE, szTemp);
#endif
		return NULL;
	}
	return &(m_vDataBuf[nPosition]);
}
const TABFile::FIELD * TABFile::Search_First_Column_Equ(int32 nColumnNum, const FIELD & value) const
{
	if(nColumnNum < 0 || nColumnNum >= m_nFieldsNum) return 0;
	FIELD_TYPE type = m_theType[nColumnNum];

	for(register int32 i = 0; i < m_nRecordsNum; i++)
	{
		const FIELD	&theField = m_vDataBuf[m_nFieldsNum * i + nColumnNum];

		bool bRet;
		if(T_INT == type)
			bRet = _FieldEqu<T_INT> (theField, value);
		else if(T_FLOAT == type)
			bRet = _FieldEqu<T_FLOAT> (theField, value);
		else
			bRet = _FieldEqu<T_STRING> (theField, value);

		if(bRet) return &(m_vDataBuf[m_nFieldsNum * i]);
	}
	return 0;
}

void   TABFile::SaveToTXT(const char* szFileName)
{
	std::ostringstream ostream;

	for (auto cur : m_theType)
	{
		if (cur == T_INT)
		{
			ostream << "int\t";
		}
		else if (cur == T_FLOAT)
		{
			ostream << "float\t";
		}
		else if (cur == T_STRING)
		{
			ostream << "string\t";
		}
	}
	ostream << "\n";

	for (int32_t i = 0; i < m_nRecordsNum; i++)
	{
		for (int32_t j = 0; j < m_nFieldsNum; j++)
		{
			int32_t index = i * m_nFieldsNum + j;
			if (m_theType[j] == T_INT)
			{
				ostream << m_vDataBuf[index].iValue << "\t";
			}
			else if (m_theType[j] == T_FLOAT)
			{
				ostream << m_vDataBuf[index].fValue << "\t";
			}
			else if (m_theType[j] == T_STRING)
			{
				ostream << m_vDataBuf[index].pString << "\t";
			}
		}

		ostream << "\n";
	}

	std::string content = ostream.str();

	FILE* fp = fopen(szFileName, "wb");
	if (fp)
	{
		fwrite(content.c_str(), 1, content.size(), fp);
		fclose(fp);
	}
}

}
