/*$T Common/StructScript.h GC 1.140 10/10/07 10:06:56 */

/*
 * // �ļ����� StructScript.h // ȫ·���� d:\Prj\Common\StructScript.h // �����ˣ�
 * // ����ʱ�䣺 2006 �� 1 �� 9 �� // // ����˵���� // �޸ļ�¼��
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
	uchar	m_IntCount;			/* ���Ͳ������� */
	uchar	m_StrCount;			/* �ַ��Ͳ������� */
	int32	m_aIntValue[MAX_PARAM_SZIE];	/* �������� */
	int16	m_aStrOffset[MAX_PARAM_SZIE];	/* �ַ��Ͳ��������\0�����ַ������е�ƫ��λ�� */
	char	m_aStrValue[MAX_STR_SIZE];	/* �ַ����� */
public:
	SXParam();
	~SXParam();

	void	Clear();

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;

	int32	GetSize() const;		/* ȡ��SXParam����Ч�ڴ��С */

	int32	GetIntCount();			/* ȡ��SXParam�е������Ͳ������� */
	int32	GetIntValue(int32 nIndex);	/* ȡ�õ�nIndex��SXParam�е������Ͳ��� */
	int32	SetIntValue(int32 nIndex, int32 nValue);	/* �޸�SXParam�еĵ�nIndex�����β��� */
	int32	AppendIntValue(int32 nValue);			/* ��SXParam�����һ�����Ͳ��� */

	int32	GetStrCount();			/* ȡ��SXParam�е��ַ����������� */
	char	*GetStrValue(int32 nIndex);	/* ȡ��SXParam�еĵ�nIndex���ַ������� */
	int32	AppendStrValue(const char *szIn);	/* ��SXParam�����һ���ַ����Ͳ��� */
	/*
	 * ����ֵΪ�˲�������� ;
	 * int32 SetStrValue( int32 nIndex, char* szIn ) ;
	 * //�޸�SXParam�еĵ�nIndex���ַ����Ͳ�?
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

	int32	GetSize() const;			/* ȡ��SXScript����Ч�ڴ��С */

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
