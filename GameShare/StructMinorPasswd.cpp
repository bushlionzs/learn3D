#include "stdafx.h"
#include "StructMinorPasswd.h"

#include "StructDB.h"

/*
 =======================================================================================================================
        输入一个密码
 =======================================================================================================================
 */
void SMinorPasswd::Clear()
{
	m_uPasswdSize = 0;
	memset((void *) m_Passwd, 0, sizeof(m_Passwd));
	m_rsaVlongPacket.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SMinorPasswd::GetSize() const
{
	return sizeof(m_uPasswdSize) + sizeof(char) * m_uPasswdSize + m_rsaVlongPacket.GetSize();
}



/*
 =======================================================================================================================
        MREQT_MODIFYPASSWD
 =======================================================================================================================
 */
void SRequestMinorPasswdModify::Clear()
{
	m_uOldPasswdSize = 0;
	memset((void *) m_OldPasswd, 0, sizeof(m_OldPasswd));
	m_uNewPasswdSize = 0;
	memset((void *) m_NewPasswd, 0, sizeof(m_NewPasswd));
	m_rsaVlongPacket.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SRequestMinorPasswdModify::GetSize() const
{
	return sizeof(m_uOldPasswdSize) +
		sizeof(char) *
		m_uOldPasswdSize +
		sizeof(m_uNewPasswdSize) +
		sizeof(char) *
		m_uNewPasswdSize+
		m_rsaVlongPacket.GetSize();
}



/*
 =======================================================================================================================
        客户端向服务器发送的联系人相关结构数据
 =======================================================================================================================
 */
void CX_MINORPASSWD::Clear()
{
	m_Type = MREQT_NONE;
	m_nFlag = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 CX_MINORPASSWD::GetSize() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uSize = sizeof(m_Type);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(m_Type)
	{
	/* 无参数部分 */
	case MREQT_PASSWDSETUP:
		break;

	case MREQT_DELETEPASSWD:
	case MREQT_SETPASSWD:
	case MREQT_UNLOCKPASSWD:
		uSize += m_OnePasswd.GetSize();
		break;

	case MREQT_MODIFYPASSWD:
		uSize += m_ModifyPasswd.GetSize();
		break;

	case MREQT_SETPROTECTTYPE:
		uSize += sizeof(m_nFlag);
		break;

	case MREQT_SETPROTECTTIME:
		uSize += sizeof(m_cTime);
		break;

	default:
		KCheck(FALSE);
		return 0;
	}

	return uSize;
}



/*
 =======================================================================================================================
        MRETT_PASSWDSETUP
 =======================================================================================================================
 */
void SReturnMinorPasswdSetup::Clear()
{
	m_uPwdFlag = 0;
	m_cLastProtectTime = 0;
	m_cProtectTime = 0;
	m_uPwdDelRemainTime = 0;
	m_uProtectDelRemainTime = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SReturnMinorPasswdSetup::GetSize() const
{
	return sizeof(m_uPwdFlag) +
		sizeof(m_cLastProtectTime) +
		sizeof(m_cProtectTime) +
		sizeof(m_uPwdDelRemainTime) +
		sizeof(m_uProtectDelRemainTime);
}



/*
 =======================================================================================================================
        MRETT_DELETEPASSWDTIME
 =======================================================================================================================
 */
void SReturnDeleteMinorpasswdTime::Clear()
{
	m_uTime = UINT_MAX;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SReturnDeleteMinorpasswdTime::GetSize() const
{
	return sizeof(m_uTime) + sizeof(m_uSetTime);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void XC_MINORPASSWD::Clear()
{
	m_Type = MRETT_NONE;

	m_uServerCurrentTime = 0;	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 XC_MINORPASSWD::GetSize() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uSize = sizeof(m_Type);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(m_Type)
	{
	case MRETT_SETPASSWDSUCC:
	case MRETT_MODIFYPASSWDSUCC:
	case MRETT_UNLOCKPASSWDSUCC:
	case MRETT_DELETEPASSWDCANCEL:
	case MRETT_DELETEPASSWDSUCC:
	case MRETT_ERR_SETPASSWDFAIL:
	case MRETT_ERR_MODIFYPASSWDFAIL:
	case MRETT_ERR_UNLOCKPASSWDFAIL:
	case MRETT_ERR_DELETEPASSWDFAIL:
	case MRETT_ERR_PASSWD:
	case MERTT_ERR_LOGINPROTECTTIME:
		break;

	case MRETT_PASSWDSETUP:
	case MRETT_SETPASSWDPROTECT:
		uSize += m_ReturnSetup.GetSize();
		break;

	case MRETT_DELETEPASSWDTIME:
	case MRETT_SETPROTECTTIMESUCC:
		uSize += m_ReturnDeleteTime.GetSize();
		break;

	default:
		KCheck(FALSE);
		return 0;
	};

	switch(m_Type)  //这三种类型Client需要MapServer的时间
	{
	case MRETT_PASSWDSETUP:
	case MRETT_DELETEPASSWDTIME:
	case MRETT_SETPROTECTTIMESUCC:
		uSize += sizeof(m_uServerCurrentTime);
		break;
	};

	return uSize;
}


