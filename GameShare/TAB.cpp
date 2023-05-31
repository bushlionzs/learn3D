#include "OgreHeader.h"
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
int32_t TABFile::_ConvertStringToVector
(
	const char		*strStrINTgSource,
	std::vector<std::string>	&vRet,
	const char		*szKey,
	bool			bOneOfKey,
	bool			bIgnoreEmpty
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

	while(true)
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

	return(int32_t) vRet.size();
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
TABFile::TABFile(uint32_t id)
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
	if(m_pStringBuf) delete m_pStringBuf;
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
const char *TABFile::_GetLineFromMemory(char *pStringBuf, int32_t nBufSize, const char *pMemory, const char *pDeadEnd)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const char	*pMem = pMemory;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMem >= pDeadEnd || *pMem == 0) return 0;

	while(pMem < pDeadEnd && pMem - pMemory + 1 < nBufSize && *pMem != 0 && *pMem != '\r' && *pMem != '\n')
		*(pStringBuf++) = *(pMem++);

	*pStringBuf = 0;

	while(pMem < pDeadEnd && *pMem != 0 && (*pMem == '\r' || *pMem == '\n')) pMem++;

	return pMem;
}


bool TABFile::OpenFromMemory(const char *pMemory, const char *pDeadEnd, const char *szFileName)
{
	assert(pMemory && pDeadEnd);

	if(pDeadEnd - pMemory >= sizeof(FILE_HEAD) && *((uint32_t *) pMemory) == 0XDDBBCC00)
	{
		return OpenFromMemoryImpl_Binary(pMemory, pDeadEnd, szFileName);
	}
	else
	{
		return OpenFromMemoryImpl_Text(pMemory, pDeadEnd, szFileName);
	}
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

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t Decrypt(const char *cSrc, char *cDest)
{
	if(0 == strcmp(cSrc, "")) return 1;

	/*~~~~~~~~~~*/
	int32_t	h, l;
	int32_t	m, n;
	int32_t	j = 0;
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


bool TABFile::OpenFromMemoryImpl_Binary(const char *pMemory, const char *pDeadEnd, const char *szFileName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	register const char	*pMem = pMemory;
	FILE_HEAD		theHead;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memcpy(&theHead, pMem, sizeof(FILE_HEAD));
	if(theHead.m_Identify != 0XDDBBCC00)
	{
		return false;
	}


	uint32_t offset = sizeof(FILE_HEAD) +
		sizeof(uint32_t) *
		theHead.m_nFieldsNum +
		sizeof(int32_t) *
		theHead.m_nRecordsNum *
		theHead.m_nFieldsNum +
		theHead.m_nStringBlockSize;
	if(offset > (uint32_t) (pDeadEnd - pMemory))
	{
		return false;
	}

	pMem += sizeof(FILE_HEAD);

	m_nRecordsNum = theHead.m_nRecordsNum;
	m_nFieldsNum = theHead.m_nFieldsNum;
	m_nStringBufSize = theHead.m_nStringBlockSize;

	m_pStringBuf = new char[theHead.m_nStringBlockSize];

	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	std::vector<uint32_t>	vFieldType;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	vFieldType.resize(theHead.m_nFieldsNum);
	memcpy(&(vFieldType[0]), pMem, sizeof(uint32_t) * theHead.m_nFieldsNum);
	pMem += sizeof(uint32_t) * theHead.m_nFieldsNum;

	m_theType.resize(theHead.m_nFieldsNum);
	for(int32_t i = 0; i < (int32_t) theHead.m_nFieldsNum; i++)
	{
		switch(vFieldType[i])
		{
		case T_INT:
		case T_FLOAT:
			m_theType[i] = (FIELD_TYPE) vFieldType[i];
			break;
		case T_STRING:
			m_theType[i] = (FIELD_TYPE)vFieldType[i];
			break;
		default:
			delete m_pStringBuf;
			return false;
		}
	}


	m_vDataBuf.resize(std::max(theHead.m_nRecordsNum * theHead.m_nFieldsNum, 1));

	int32_t size = theHead.m_nRecordsNum * theHead.m_nFieldsNum;


	for (int32_t i = 0; i < size; i++)
	{
		m_vDataBuf[i].iValue = *(int32_t*)pMem;
		pMem += sizeof(int32_t);
	}

	//pMem += sizeof(int32_t) * theHead.m_nRecordsNum * theHead.m_nFieldsNum;

	memcpy(m_pStringBuf, pMem, m_nStringBufSize);
	m_pStringBuf[m_nStringBufSize - 1] = 0;

	for(int32_t j = 0; j < (int32_t) theHead.m_nFieldsNum; j++)
	{
		if(vFieldType[j] != T_STRING) continue;

		/*~~~~~~~~~~~~~~~*/
		std::string	str;
		int32_t	nFieldsNum;
		/*~~~~~~~~~~~~~~~*/

		for(int32_t i = 0; i < (int32_t) theHead.m_nRecordsNum; i++)
		{
			nFieldsNum = GetFieldsNum();

			char* current = m_pStringBuf + m_vDataBuf[i * nFieldsNum + j].iValue;
			m_vDataBuf[i * nFieldsNum + j].pString = current;
		}
	}

	CreateIndex(0, szFileName);

	return true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
bool TABFile::OpenFromMemoryImpl_Text(const char *pMemory, const char *pDeadEnd, const char *szFileName)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char			szLine[1024 * 10] = { 0 };
	register const char	*pMem = pMemory;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMem = _GetLineFromMemory(szLine, 1024 * 10, pMem, pDeadEnd);
	if(!pMem) return false;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	std::vector<std::string>	vRet;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	_ConvertStringToVector(szLine, vRet, "\t", TRUE, TRUE);
	if(vRet.empty()) return false;

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	FILEDS_TYPE	vFieldsType;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	vFieldsType.resize(vRet.size());

	for(int32_t i = 0; i < (int32_t) vRet.size(); i++)
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
			return false;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32_t					nRecordsNum = 0;
	int32_t					nFieldsNum = (int32_t) vFieldsType.size();
	std::vector<std::pair<std::string, int32_t> >	vStringBuf;
	std::map<std::string, int32_t>		mapStringBuf;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pMem = _GetLineFromMemory(szLine, 1024 * 10, pMem, pDeadEnd);
	if(!pMem) return false;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32_t nStringBufSize = 0;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	do
	{
		pMem = _GetLineFromMemory(szLine, 1024 * 10, pMem, pDeadEnd);
		if(!pMem) break;;

		if(szLine[0] == '#') continue;

		_ConvertStringToVector(szLine, vRet, "\t", true, false);

		if(vRet.empty()) continue;
		if(vRet.size() != nFieldsNum)
		{
			if((int32_t) vRet.size() < nFieldsNum)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32_t nSubNum = nFieldsNum - (int32_t) vRet.size();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				for(int32_t i = 0; i < nSubNum; i++)
				{
					vRet.push_back("");
				}
			}
		}

		if(vRet[0].empty()) continue;

		for(register int32_t i = 0; i < nFieldsNum; i++)
		{
			FIELD newField;

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
					std::map<std::string, int32_t>::iterator	it = mapStringBuf.find(vRet[i]);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(it == mapStringBuf.end())
					{
						vStringBuf.push_back(std::make_pair(vRet[i], nStringBufSize));
						mapStringBuf.insert(std::make_pair(vRet[i], (int32_t) vStringBuf.size() - 1));
						newField.iValue = nStringBufSize + 1;

						nStringBufSize += (int32_t) strlen(vRet[i].c_str()) + 1;
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
	} while(true);

	m_nRecordsNum = nRecordsNum;
	m_nFieldsNum = nFieldsNum;
	m_nStringBufSize = nStringBufSize + 1;

	m_pStringBuf = new char[m_nStringBufSize];

	m_theType = vFieldsType;


	m_pStringBuf[0] = '\0';

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	register char	*p = m_pStringBuf + 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32_t i = 0; i < (int32_t) vStringBuf.size(); i++)
	{
		memcpy(p, vStringBuf[i].first.c_str(), vStringBuf[i].first.size());
		p += vStringBuf[i].first.size();

		*(p++) = '\0';
	}

	for(register int32_t i = 0; i < nFieldsNum; i++)
	{
		if(vFieldsType[i] != T_STRING) continue;

		for(register int32_t j = 0; j < nRecordsNum; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			FIELD	&theField = m_vDataBuf[j * nFieldsNum + i];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			theField.pString = m_pStringBuf + theField.iValue;
		}
	}

	CreateIndex(0, szFileName);

	return true;
}


bool TABFile::OpenFromTXT(const char *szFileName)
{
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
		return false;
	}

	fseek(fp, 0, SEEK_END);

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32_t nFileSize = ftell(fp);
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
	bool bRet = OpenFromMemory(pMemory, pMemory + nFileSize + 1, szFileName);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	delete [] pMemory;
	pMemory = 0;
	return bRet;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void TABFile::CreateIndex(int32_t nColum, const char *szFileName)
{
	if(nColum < 0 || nColum >= m_nFieldsNum || m_nIndexColum == nColum) return;

	m_hashIndex.clear();

	for(int32_t i = 0; i < (int32_t) m_nRecordsNum; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		FIELD			*p = &(m_vDataBuf[i * m_nFieldsNum]);
		FIELD_HASHMAP::iterator itFind = m_hashIndex.find(p->iValue);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(itFind != m_hashIndex.end())
		{
			/*~~~~~~~~~~~~~*/
			char szTemp[MAX_FILE_PATH];
			/*~~~~~~~~~~~~~*/

			snprintf
			(
				szTemp,
				MAX_FILE_PATH,
				"[%s]Multi index at line %d(SAME:value=%d)",
				szFileName,
				i + 1,
				p->iValue
			);

			return;
		}

		m_hashIndex.insert(std::make_pair(p->iValue, p));
	}
}

const TABFile::FIELD * TABFile::Search_Index_EQU(int32_t iIndex) const
{
	FIELD_HASHMAP::const_iterator	itFind = m_hashIndex.find(iIndex);
	if(itFind == m_hashIndex.end()) return NULL;

	return itFind->second;
}
const TABFile::FIELD * TABFile::Search_Posistion(int32_t nRecordLine, int32_t nColumNum) const
{
	int32_t nPosition = nRecordLine *
	GetFieldsNum()
	+ nColumNum;

	if(nPosition < 0 || nPosition >= (int32_t) m_vDataBuf.size())
	{
		char szTemp[MAX_FILE_PATH];
		snprintf(szTemp, MAX_FILE_PATH, "[TAB] Invalid Key! file=%s,line=%d,col=%d]", m_szFileName, nRecordLine, nColumNum);

		return NULL;
	}
	return &(m_vDataBuf[nPosition]);
}
const TABFile::FIELD * TABFile::Search_First_Column_Equ(int32_t nColumnNum, const FIELD & value) const
{
	if(nColumnNum < 0 || nColumnNum >= m_nFieldsNum) return 0;
	FIELD_TYPE type = m_theType[nColumnNum];

	for(register int32_t i = 0; i < m_nRecordsNum; i++)
	{
		const FIELD	&theField = m_vDataBuf[m_nFieldsNum * i + nColumnNum];

		bool bRet;
		if(T_INT == type)
			bRet = _FieldEqu<T_INT> (theField, value);
		else if(T_FLOAT == type)
			bRet = _FieldEqu<T_FLOAT> (theField, value);
		else
			bRet = _FieldEqu<T_STRING> (theField, value);

		if (bRet)
		{
			const TABFile::FIELD* field = &(m_vDataBuf[m_nFieldsNum * i]);
			return field;
		}
			
	}
	return nullptr;
}
}
