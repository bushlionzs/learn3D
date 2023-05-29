/*$T Common/StructMinorPasswd.h GC 1.140 10/10/07 10:06:56 */

/* ������Ϣ�ṹ */
#ifndef __GAMESTRUCT_MINORPASSWD_H__
#define __GAMESTRUCT_MINORPASSWD_H__

#include "TypeDefine.h"

class	RecieveStream;
class	SendStream;
enum eMINORPASSWD_REQUEST_CODE
{
	MREQT_NONE		= 0,
	MREQT_PASSWDSETUP,			/* ѯ�����뱣�� */
	MREQT_SETPASSWD,			/* ���ö������� */
	MREQT_MODIFYPASSWD,			/* �޸Ķ������� */
	MREQT_UNLOCKPASSWD,			/* ����������� */
	MREQT_DELETEPASSWD,			/* ǿ�ƽ���ܱ� */
	MREQT_SETPROTECTTYPE,			/* ���ö������뱣������ */
	MREQT_SETPROTECTTIME,			/* �������߱���ʱ�� */
};

enum eMINORPASSWD_RETURN_CODE
{
	MRETT_NONE			= 0,
	MRETT_PASSWDSETUP,			/* ���뱣�� */
	MRETT_SETPASSWDSUCC,			/* �����������óɹ� */
	MRETT_MODIFYPASSWDSUCC,			/* ���������޸ĳɹ� */
	MRETT_UNLOCKPASSWDSUCC,			/* ������������ɹ� */
	MRETT_DELETEPASSWDCANCEL,		/* ǿ�ƽ����������ʧЧ */
	MRETT_DELETEPASSWDSUCC,			/* ��������ǿ�ƽ���ɹ� */
	MRETT_SETPASSWDPROTECT,			/* ���ñ������ͳɹ� */
	MRETT_SETPROTECTTIMESUCC,		/* �������߱���ʱ��ɹ� */

	MRETT_DELETEPASSWDTIME,			/* ǿ�ƽ�������ܱ� */
	MRETT_ERR_START,
	MRETT_ERR_SETPASSWDFAIL,		/* ������������ʧ�� */
	MRETT_ERR_MODIFYPASSWDFAIL,		/* ���������޸�ʧ�� */
	MRETT_ERR_UNLOCKPASSWDFAIL,		/* �����������ʧ�� */
	MRETT_ERR_DELETEPASSWDFAIL,		/* ��������ǿ�ƽ��ʧ�� */
	MRETT_ERR_SETPROTECTTIMEFAIL,		/* �������߱���ʱ��ʧ�� */
	MRETT_ERR_PASSWD,			/* У������ʧ�� */
	MERTT_ERR_LOGINPROTECTTIME,		/* �ڵ�½����ʱ���� */
};

enum PROTECT_TYPE
{
	PROTECT_EQUIP			= 0,	/* �Ѿ��󶨵�װ�� */
	PROTECT_BANK			= 1,	/* �ֿ� */
	PROTECT_GOLD			= 2,	/* ���ʹ�� */
	PROTECT_SILLER			= 3,	/* ����ʹ�� */
	PROTECT_HORSE			= 4,	/* ��ƥ */
	PROTECT_ABILITY			= 5,	/*�����ɾ��*/
	PROTECT_COUNTRY			= 6,    /* ����������*/	
	PROTECT_VALID			= 7,	/* ��Ǳ�����Ч */
};

struct SMinorPasswd
{
	/* ���� */
	uchar	m_uPasswdSize;
	char	m_Passwd[MAX_PWD];		/* �������� */
	RSA_VLOLG_PACKET m_rsaVlongPacket;

	/* �����ӿ� */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

    static uint32 GetPacketMaxSize()
    {
        return MAX_PWD + sizeof( uchar) + RSA_VLOLG_PACKET::struct_size;
    }

	/*
	 ===============================================================================================================
	        ����Ӧ�ýӿ�
	 ===============================================================================================================
	 */
	uchar GetPasswdSize()
	{
		return m_uPasswdSize;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetPasswd()
	{
		return m_Passwd;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPasswd(const char *szPasswd)
	{
		KCheck(szPasswd);
		strncpy(m_Passwd, szPasswd, sizeof(m_Passwd) - 1);
		m_uPasswdSize = (uchar) strlen(m_Passwd);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	RSA_VLOLG_PACKET *GetRsaVlongInfo()
	{
		return &m_rsaVlongPacket;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
        MREQT_MODIFYPASSWD
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SRequestMinorPasswdModify
{
	/* ���� */
	uchar	m_uOldPasswdSize;
	char	m_OldPasswd[MAX_PWD];	/* �ɶ������� */
	uchar	m_uNewPasswdSize;
	char	m_NewPasswd[MAX_PWD];	/* �¶������� */
	RSA_VLOLG_PACKET m_rsaVlongPacket;

	/* �����ӿ� */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	        ����Ӧ�ýӿ�
	 ===============================================================================================================
	 */
	uchar GetOldPasswdSize()
	{
		return m_uOldPasswdSize;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetOldPasswd()
	{
		return m_OldPasswd;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOldPasswd(const char *szPasswd)
	{
		KCheck(m_OldPasswd);
		strncpy(m_OldPasswd, szPasswd, sizeof(m_OldPasswd) - 1);
		m_uOldPasswdSize = (uchar) strlen(m_OldPasswd);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetPasswdSize()
	{
		return m_uNewPasswdSize;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const char *GetNewPasswd()
	{
		return m_NewPasswd;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetNewPasswd(const char *szPasswd)
	{
		KCheck(m_NewPasswd);
		strncpy(m_NewPasswd, szPasswd, sizeof(m_NewPasswd) - 1);
		m_uNewPasswdSize = (uchar) strlen(m_NewPasswd);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	RSA_VLOLG_PACKET *GetRsaVlongInfo()
	{
		return &m_rsaVlongPacket;
	}
};

struct CX_MINORPASSWD
{
	uchar	m_Type; /* enum eMINORPASSWD_REQUEST_CODE */

	union
	{
		SMinorPasswd			m_OnePasswd;
		SRequestMinorPasswdModify	m_ModifyPasswd;
		int32				m_nFlag;	/* �������� */
		int32				m_cTime;	/* ���߱���ʱ�� */
	};

	void	Clear();
	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
    static  uint32 GetPacketMaxSize()
    {
        return ( sizeof( int32) + sizeof( int32) + SMinorPasswd::GetPacketMaxSize() );
    }
};
struct SReturnMinorPasswdSetup
{
	uchar	m_uPwdFlag;			/* �����ܱ��������� */
	uchar	m_cProtectTime;			/* ��¼����ʱ�� */
	uchar	m_cLastProtectTime;		/* ��һ�ε�½����ʱ�� */
	uint32	m_uPwdDelRemainTime;		/* ��������ʣ��ʱ�� */
	uint32	m_uProtectDelRemainTime;	/* �����½����ʣ��ʱ�� */

	/* �����ӿ� */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	        ����Ӧ�ýӿ�
	 ===============================================================================================================
	 */
	uchar GetSetupFlag()
	{
		return m_uPwdFlag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSetupFlag(uchar uFlag)
	{
		m_uPwdFlag = uFlag;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetProtectTime()
	{
		return m_cProtectTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetProtectTime(uchar uTime)
	{
		m_cProtectTime = uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetLastProtectTime()
	{
		return m_cLastProtectTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetLastProtectTime(uchar uTime)
	{
		m_cLastProtectTime = uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPwdDelTime()
	{
		return m_uPwdDelRemainTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPwdDelTime(uint32 uTime)
	{
		m_uPwdDelRemainTime = uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetProtectDelTime()
	{
		return m_uProtectDelRemainTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetProtectDelTime(uint32 uTime)
	{
		m_uProtectDelRemainTime = uTime;
	}

};

/*
 -----------------------------------------------------------------------------------------------------------------------
        MRETT_DELETEPASSWDTIME
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SReturnDeleteMinorpasswdTime
{
	uint32	m_uTime;	/* �����ʱ�� */
	uint32	m_uSetTime;

	/* �����ӿ� */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	        ����Ӧ�ýӿ�
	 ===============================================================================================================
	 */
	uint32 GetDeleteTime()
	{
		return m_uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetDeleteTime(uint32 uTime)
	{
		m_uTime = uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSetTime()
	{
		return m_uSetTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSetTime(uint32 uTime)
	{
		m_uSetTime = uTime;
	}
};

struct XC_MINORPASSWD
{
	uchar	m_Type; /* enum eMINORPASSWD_RETURN_CODE */

	union
	{
		SReturnMinorPasswdSetup	m_ReturnSetup;
		SReturnDeleteMinorpasswdTime	m_ReturnDeleteTime;
	};

	uint32	m_uServerCurrentTime;		/* ��������ǰʱ�� add by wangzhiping in Nov-12-2009*/

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
#endif /* __GAMESTRUCT_MINORPASSWD_H__ */
