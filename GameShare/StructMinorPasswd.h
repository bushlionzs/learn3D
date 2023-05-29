/*$T Common/StructMinorPasswd.h GC 1.140 10/10/07 10:06:56 */

/* 好友消息结构 */
#ifndef __GAMESTRUCT_MINORPASSWD_H__
#define __GAMESTRUCT_MINORPASSWD_H__

#include "TypeDefine.h"

class	RecieveStream;
class	SendStream;
enum eMINORPASSWD_REQUEST_CODE
{
	MREQT_NONE		= 0,
	MREQT_PASSWDSETUP,			/* 询问密码保护 */
	MREQT_SETPASSWD,			/* 设置二级密码 */
	MREQT_MODIFYPASSWD,			/* 修改二级密码 */
	MREQT_UNLOCKPASSWD,			/* 二级密码解锁 */
	MREQT_DELETEPASSWD,			/* 强制解除密保 */
	MREQT_SETPROTECTTYPE,			/* 设置二级密码保护类型 */
	MREQT_SETPROTECTTIME,			/* 设置上线保护时间 */
};

enum eMINORPASSWD_RETURN_CODE
{
	MRETT_NONE			= 0,
	MRETT_PASSWDSETUP,			/* 密码保护 */
	MRETT_SETPASSWDSUCC,			/* 二级密码设置成功 */
	MRETT_MODIFYPASSWDSUCC,			/* 二级密码修改成功 */
	MRETT_UNLOCKPASSWDSUCC,			/* 二级密码解锁成功 */
	MRETT_DELETEPASSWDCANCEL,		/* 强制解除二级密码失效 */
	MRETT_DELETEPASSWDSUCC,			/* 二级密码强制解除成功 */
	MRETT_SETPASSWDPROTECT,			/* 设置保护类型成功 */
	MRETT_SETPROTECTTIMESUCC,		/* 设置上线保护时间成功 */

	MRETT_DELETEPASSWDTIME,			/* 强制解除二级密保 */
	MRETT_ERR_START,
	MRETT_ERR_SETPASSWDFAIL,		/* 二级密码设置失败 */
	MRETT_ERR_MODIFYPASSWDFAIL,		/* 二级密码修改失败 */
	MRETT_ERR_UNLOCKPASSWDFAIL,		/* 二级密码解锁失败 */
	MRETT_ERR_DELETEPASSWDFAIL,		/* 二级密码强制解除失败 */
	MRETT_ERR_SETPROTECTTIMEFAIL,		/* 设置上线保护时间失败 */
	MRETT_ERR_PASSWD,			/* 校验密码失败 */
	MERTT_ERR_LOGINPROTECTTIME,		/* 在登陆保护时间内 */
};

enum PROTECT_TYPE
{
	PROTECT_EQUIP			= 0,	/* 已经绑定的装备 */
	PROTECT_BANK			= 1,	/* 仓库 */
	PROTECT_GOLD			= 2,	/* 金币使用 */
	PROTECT_SILLER			= 3,	/* 银币使用 */
	PROTECT_HORSE			= 4,	/* 马匹 */
	PROTECT_ABILITY			= 5,	/*生活技能删除*/
	PROTECT_COUNTRY			= 6,    /* 帮会国家设置*/	
	PROTECT_VALID			= 7,	/* 标记保护有效 */
};

struct SMinorPasswd
{
	/* 数据 */
	uchar	m_uPasswdSize;
	char	m_Passwd[MAX_PWD];		/* 二级密码 */
	RSA_VLOLG_PACKET m_rsaVlongPacket;

	/* 基本接口 */
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
	        数据应用接口
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
	/* 数据 */
	uchar	m_uOldPasswdSize;
	char	m_OldPasswd[MAX_PWD];	/* 旧二级密码 */
	uchar	m_uNewPasswdSize;
	char	m_NewPasswd[MAX_PWD];	/* 新二级密码 */
	RSA_VLOLG_PACKET m_rsaVlongPacket;

	/* 基本接口 */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	        数据应用接口
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
		int32				m_nFlag;	/* 保护类型 */
		int32				m_cTime;	/* 上线保护时间 */
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
	uchar	m_uPwdFlag;			/* 二级密保保护类型 */
	uchar	m_cProtectTime;			/* 登录保护时间 */
	uchar	m_cLastProtectTime;		/* 上一次登陆保护时间 */
	uint32	m_uPwdDelRemainTime;		/* 解除密码的剩余时间 */
	uint32	m_uProtectDelRemainTime;	/* 解除登陆保护剩余时间 */

	/* 基本接口 */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	        数据应用接口
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
	uint32	m_uTime;	/* 解除的时间 */
	uint32	m_uSetTime;

	/* 基本接口 */
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	        数据应用接口
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

	uint32	m_uServerCurrentTime;		/* 服务器当前时间 add by wangzhiping in Nov-12-2009*/

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
#endif /* __GAMESTRUCT_MINORPASSWD_H__ */
