/*$T Common/StructMonitor.h GC 1.140 10/10/07 10:06:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _GAMESTRUCT_MONITOR_H_
#define _GAMESTRUCT_MONITOR_H_

#include "TypeDefine.h"

enum MonitorOpType { MW_OP_KEYWORDLIST = 0, MW_OP_DELETE, WM_OP_KEYWORDLIST, WM_OP_DELETE, WM_OP_ERROR, };

#define MONITOR_KEYWORD_LIST_MAX_SIZE	10
#define FILTER_KEY_WORD_LEN		32
struct MWM_KeywordList
{
	uchar	m_nTotalCount;
	char	m_keywordTable[MONITOR_KEYWORD_LIST_MAX_SIZE][FILTER_KEY_WORD_LEN];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_nTotalCount = 0;
		memset(m_keywordTable, 0, sizeof(m_keywordTable));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(uchar) + m_nTotalCount * sizeof(char) * FILTER_KEY_WORD_LEN;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Read(RecieveStream &iStream)
	{
		iStream.Reci((char *) (&m_nTotalCount), sizeof(m_nTotalCount));
		for(int32 i = 0; i < m_nTotalCount; ++i)
		{
			iStream.Reci((char *) (m_keywordTable[i]), FILTER_KEY_WORD_LEN);
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Write(SendStream &oStream) const
	{
		oStream.Send((char *) (&m_nTotalCount), sizeof(m_nTotalCount));
		for(int32 i = 0; i < m_nTotalCount; ++i)
		{
			oStream.Send((char *) (m_keywordTable[i]), FILTER_KEY_WORD_LEN);
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL AddData(const char *str)
	{
		if(m_nTotalCount >= MONITOR_KEYWORD_LIST_MAX_SIZE) return FALSE;
		strncpy(m_keywordTable[m_nTotalCount], str, FILTER_KEY_WORD_LEN - 1);
		m_nTotalCount++;
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetData(int32 nIndex)
	{
		KCheck(nIndex >= 0 && nIndex < MONITOR_KEYWORD_LIST_MAX_SIZE);
		return m_keywordTable[nIndex];
	}
};

struct MW_DELETE
{
	enum
	{
		TYPE_INVALID		= -1,
		TYPE_REPORT_LIST,
		TYPE_SUSPECT_LIST,
		TYPE_WATCH_LIST,
		TYPE_FBCHAT_LIST,
		TYPE_CLEAR_FBCHAT_LIST,
	};

	uchar m_Type;
	int32 m_nCount;
	GUID_t m_guids[128];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_Type = TYPE_INVALID;
		m_nCount = 0;
		memset(m_guids, INVALID_GUID, sizeof(GUID_t) * 128);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(uchar) + sizeof(int32) + sizeof(GUID_t) * m_nCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetCount()
	{
		return m_nCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL AddGuid(int32 guid)
	{
		if(m_nCount >= 128) return FALSE;
		m_guids[m_nCount] = guid;
		m_nCount++;
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GUID_t GetGuid(int32 nIndex)
	{
		KCheck(nIndex >= 0 && nIndex < m_nCount);
		return m_guids[nIndex];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Read(RecieveStream &iStream)
	{
		iStream.Reci((char *) (&m_Type), sizeof(m_Type));
		iStream.Reci((char *) (&m_nCount), sizeof(m_nCount));
		KCheck(m_nCount >= 0 && m_nCount <= 128);
		for(int32 i = 0; i < m_nCount; ++i)
		{
			iStream.Reci((char *) (&m_guids[i]), sizeof(GUID_t));
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Write(SendStream &oStream) const
	{
		oStream.Send((char *) (&m_Type), sizeof(m_Type));
		oStream.Send((char *) (&m_nCount), sizeof(m_nCount));
		KCheck(m_nCount >= 0 && m_nCount <= 128);
		for(int32 i = 0; i < m_nCount; ++i)
		{
			oStream.Send((char *) (&m_guids[i]), sizeof(GUID_t));
		}
	}
};

struct WM_DELETE
{
	enum { TYPE_INVALID = -1, TYPE_REPORT_LIST, TYPE_SUSPECT_LIST, TYPE_WATCH_LIST, TYPE_FBCHAT_LIST, };

	uchar m_Type;
	GUID_t m_guid;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_Type = TYPE_INVALID;
		m_guid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(uchar) + sizeof(GUID_t);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Read(RecieveStream &iStream)
	{
		iStream.Reci((char *) (&m_Type), sizeof(m_Type));
		iStream.Reci((char *) (&m_guid), sizeof(GUID_t));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Write(SendStream &oStream) const
	{
		oStream.Send((char *) (&m_Type), sizeof(m_Type));
		oStream.Send((char *) (&m_guid), sizeof(GUID_t));
	}
};

class WM_ERROR
{
public:
	enum
	{
		ERROR_INVALID			= -1,
		ERROR_FBCHAT_SUCCESS,
		ERROR_FBCHAT_USER_OFFLINE,
		ERROR_FBCHAT_LIST_FULL,
		ERROR_FBCHAT_SERVER_ERROR,
		ERROR_UNFBCHAT_SUCCESS,
		ERROR_UNFBCHAT_USER_OFFLINE,
		ERROR_UNFBCHAT_SERVER_ERROR,
	};

	uchar m_ErrorType;
	int32 m_nParam;
	uchar m_szParam_Size;
	char m_szParam[128];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_ErrorType = ERROR_INVALID;
		m_nParam = 0;
		m_szParam_Size = 0;
		memset(m_szParam, 0, 128);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(uchar) + sizeof(int32) + sizeof(uchar) + m_szParam_Size;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Read(RecieveStream &iStream)
	{
		iStream.Reci((char *) (&m_ErrorType), sizeof(m_ErrorType));
		iStream.Reci((char *) (&m_nParam), sizeof(m_nParam));
		iStream.Reci((char *) (&m_szParam_Size), sizeof(m_szParam_Size));
		iStream.Reci((char *) (m_szParam), m_szParam_Size);
		m_szParam[m_szParam_Size] = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Write(SendStream &oStream) const
	{
		oStream.Send((char *) (&m_ErrorType), sizeof(m_ErrorType));
		oStream.Send((char *) (&m_nParam), sizeof(m_nParam));
		oStream.Send((char *) (&m_szParam_Size), sizeof(m_szParam_Size));
		oStream.Send((char *) (m_szParam), m_szParam_Size);
	}
};
#endif
