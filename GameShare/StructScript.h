/*$T Common/StructScript.h GC 1.140 10/10/07 10:06:56 */

/*
 * // 文件名： StructScript.h // 全路径： d:\Prj\Common\StructScript.h // 创建人：
 * // 创建时间： 2006 年 1 月 9 日 // // 功能说明： // 修改记录：
 */
#ifndef __GAMESTRUCT_SCRIPT_H__
#define __GAMESTRUCT_SCRIPT_H__

#include "TypeDefine.h"

class	RecieveStream;
class	SendStream;

/*
 * m_IntCount=1 ;
 * m_aIntValue=[1989] ;
 * m_StrCount=3 ;
 * m_aStrOffset=[5][16][23] ;
 * m_aStrValue: ;
 * hello\0come herer\0gogogo\0 ;
 */
#define MAX_PARAM_SZIE	16
#define MAX_STR_SIZE	512
struct SXParam
{
	uchar	m_IntCount;			/* 整型参数数量 */
	uchar	m_StrCount;			/* 字符型参数数量 */
	int32	m_aIntValue[MAX_PARAM_SZIE];	/* 整形数据 */
	int16	m_aStrOffset[MAX_PARAM_SZIE];	/* 字符型参数间隔（\0）在字符缓存中的偏移位置 */
	char	m_aStrValue[MAX_STR_SIZE];	/* 字符缓存 */
public:
	SXParam();
	~SXParam();

	void	Clear();

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;

	int32	GetSize() const;		/* 取得SXParam的有效内存大小 */

	int32	GetIntCount();			/* 取得SXParam中的整数型参数数量 */
	int32	GetIntValue(int32 nIndex);	/* 取得第nIndex个SXParam中的整数型参数 */
	int32	SetIntValue(int32 nIndex, int32 nValue);	/* 修改SXParam中的第nIndex个整形参数 */
	int32	AppendIntValue(int32 nValue);			/* 向SXParam中添加一个整型参数 */

	int32	GetStrCount();			/* 取得SXParam中的字符串参数个数 */
	char	*GetStrValue(int32 nIndex);	/* 取得SXParam中的第nIndex个字符串参数 */
	int32	AppendStrValue(const char *szIn);	/* 向SXParam中添加一个字符串型参数 */
	/*
	 * 返回值为此参数的序号 ;
	 * int32 SetStrValue( int32 nIndex, char* szIn ) ;
	 * //修改SXParam中的第nIndex个字符串型参?
	 */
};

#define MAX_FUNC_NAME_SIZE	64

/* define MAX_STRING_PARAM_SIZE 256 */
#define MAX_INT_PARAM_COUNT	6
struct SXScript
{
	ScriptID_t	m_ScriptID;
	uchar		m_uFunNameSize;
	char		m_szFunName[MAX_FUNC_NAME_SIZE];

	/*
	 * uchar m_uStrParamSize ;
	 * char m_szStrParam[MAX_STRING_PARAM_SIZE] ;
	 */
	uchar		m_uParamCount;
	int32		m_aParam[MAX_INT_PARAM_COUNT];
public:
	SXScript();
	~SXScript();

	void	Clear();

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;

	int32	GetSize() const;			/* 取得SXScript的有效内存大小 */

    static int32 GetMaxSize()
    {
        return ( sizeof( ScriptID_t) + MAX_FUNC_NAME_SIZE + sizeof( uchar) + sizeof( int32) * MAX_INT_PARAM_COUNT + sizeof( uchar) );
    }

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetScriptID(ScriptID_t sid)
	{
		m_ScriptID = sid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ScriptID_t GetScriptID()
	{
		return m_ScriptID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFunName(char *szfunname)
	{
		strncpy(m_szFunName, szfunname, MAX_FUNC_NAME_SIZE - 1);
		m_uFunNameSize = (uchar) strlen(m_szFunName);
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	char *GetFunName()
	{
		return m_szFunName;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetFunNameSize()
	{
		return m_uFunNameSize;
	}

	/*
	 ===============================================================================================================
	        void SetStrParam( char* szstrparam ) ;
	        { ;
	        strncpy( m_szStrParam, szstrparam, MAX_STRING_PARAM_SIZE-1 ) ;
	        m_uStrParamSize = (uchar)strlen(m_szStrParam) ;
	        };
	        char* GetStrParam( ){ return m_szStrParam ;
	        } ;
	        int32 GetStrParamSize( ){ return m_uStrParamSize ;
	        }
	 ===============================================================================================================
	 */
	void SetParamCount(uchar count)
	{
		m_uParamCount = count;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetParamCount()
	{
		return m_uParamCount;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetParam(uchar uIndex, int32 param)
	{
		if(uIndex >= MAX_INT_PARAM_COUNT) return;
		m_aParam[uIndex] = param;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetParam(uchar uIndex)
	{
		if(uIndex >= MAX_INT_PARAM_COUNT) return 0;
		return m_aParam[uIndex];
	}
};
#endif
