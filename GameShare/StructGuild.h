/*$T Common/StructGuild.h GC 1.140 10/10/07 10:06:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __GAMESTRUCT_GUILD_H__
#define __GAMESTRUCT_GUILD_H__

#include "TypeDefine.h"
#include "DefineGuild.h"

class	RecieveStream;
class	SendStream;

struct ConvoyMember
{
	ConvoyMember()
	{
		Clear();
	}
	enum { struct_size = sizeof (GUID_t) +sizeof (BOOL) +sizeof (uchar) +sizeof (char) *MAX_CHARACTER_NAME };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_GUID = INVALID_GUILD_ID;
		m_IsInDist = TRUE;
		m_NameSize = 0;
		memset(m_szName, 0, MAX_CHARACTER_NAME);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ConvoyMember &operator=(const ConvoyMember &entry)
	{
		m_GUID = entry.m_GUID;
		m_IsInDist = entry.m_IsInDist;
		m_NameSize = entry.m_NameSize;
		strncpy(m_szName, entry.m_szName, sizeof(m_szName) - 1);
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetName(const char *pName)
	{
		strncpy(m_szName, pName, MAX_CHARACTER_NAME - 1);
		m_NameSize = (uchar) strlen(m_szName);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetSize() const
	{
		return sizeof(m_GUID) + sizeof(m_IsInDist) + sizeof(m_NameSize) + sizeof(char) * m_NameSize;
	}

	GUID_t	m_GUID;
	BOOL	m_IsInDist;
	uchar	m_NameSize;
	char	m_szName[MAX_CHARACTER_NAME];
};

struct GUILD_QUEST_DATA
{
	int32	m_aQuestData[MAX_GUILD_QUEST_NUM];

	GUILD_QUEST_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		for(int32 i = 0; i < MAX_GUILD_QUEST_NUM; i++) m_aQuestData[i] = -1;
	}
};

struct GuildConvoyList
{
	GuildConvoyList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		for(int32 i = 0; i < MAX_USER_IN_GUILD; i++)
		{
			m_Member[i].Clear();
		}

		m_iMemberCount = 0;
		m_BusObjID = INVALID_ID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL Add(ConvoyMember &member)
	{
		if(m_iMemberCount >= MAX_USER_IN_GUILD)
		{
			return FALSE;
		}

		for(int32 i = 0; i < m_iMemberCount; i++)
		{
			if(m_Member[i].m_GUID == member.m_GUID)
			{
				return FALSE;
			}
		}

		m_Member[m_iMemberCount] = member;
		m_iMemberCount++;
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL Delete(GUID_t id)
	{
		BOOL	bFind = FALSE;
		int32	i;

		for(i = 0; i < m_iMemberCount; i++)
		{
			if(m_Member[i].m_GUID == id)
			{
				bFind = TRUE;
				break;
			}
		}

		if(bFind)
		{
			for(; i < m_iMemberCount - 1; i++)
			{
				m_Member[i] = m_Member[i + 1];
			}

			m_iMemberCount--;
			KCheck(m_iMemberCount >= 0);

			return TRUE;
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ConvoyMember *GetMemberByIndex(int32 index)
	{
		KCheckEx(index >= 0 && index < m_iMemberCount, "获取帮派护送成员时下标越界");
		return &m_Member[index];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ConvoyMember *GetMemberByGUID(GUID_t id)
	{
		for(int32 i = 0; i < m_iMemberCount; i++)
		{
			if(m_Member[i].m_GUID == id)
			{
				return &m_Member[i];
			}
		}

		return NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetMemberCount()
	{
		return m_iMemberCount;
	}

	ConvoyMember	m_Member[MAX_USER_IN_GUILD];
	int32		m_iMemberCount;
	ObjID_t		m_BusObjID;
};

struct SGuildPacket
{
	virtual uint32 GetPacketSize () const = 0;
	virtual void Read(RecieveStream & iStream) = 0;
	virtual void Write (SendStream & oStream) const = 0;
};

struct GUILD_CXG_ASKLIST :
	public SGuildPacket
{
	uchar	m_SortType;
	uint16	m_uStart;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_SortType) + sizeof(m_uStart);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

/*
struct SMail
{
	GUID_t	m_GUID;								// 邮件发送者GUID
	uchar	m_SourSize;							// 邮件发送者名字长度
	char	m_szSourName[MAX_CHARACTER_NAME];	// 邮件发送者名字

	int32	m_nPortrait;						// 发送者头像ID

	uchar	m_DestSize;							// 邮件接收者名字长度
	char	m_szDestName[MAX_CHARACTER_NAME];	// 邮件接收者名字

	uint16	m_ContexSize;						// 邮件内容长度
	char	m_szContex[MAX_MAIL_CONTEX];		// 邮件内容

	uint32	m_uFlag;							// 邮件类型
	uint32	m_uCreateTime;						// 邮件创建时间，GetCTime类型

	uint32	m_uParam0;							// 附加参数，脚本邮件使用
	uint32	m_uParam1;
	uint32	m_uParam2;
	uint32	m_uParam3;

    static int32 GetSize()
    {
        return ( sizeof( GUID_t) + sizeof( uchar) * 2 + sizeof( int32) + sizeof(uint32) + sizeof( uint16) + sizeof( uint32) * 5 + MAX_CHARACTER_NAME * 2 + MAX_MAIL_CONTEX);
    }

	SMail()
	{
		Clear();
	};
*/
struct GUILD_CXG_SEND_MAIL:
	public SGuildPacket
{
		// 邮件内容长度
		int32   m_CxtSize  ;
		char	m_szContex[MAX_MAIL_CONTEX];		// 邮件内容
		
		GUILD_CXG_SEND_MAIL()
		{
			Clear();
		}

		void Clear()
		{
			m_CxtSize = 0;
			memset(m_szContex, 0, sizeof(char) * MAX_MAIL_CONTEX);
		}
		
		virtual uint32 GetPacketSize () const
		{
			return sizeof(m_CxtSize) + m_CxtSize;
			
		}
};

struct GUILD_CXG_CREATE :
	public SGuildPacket
{
	uchar	m_NameSize;
	char	m_szGuildName[MAX_GUILD_NAME_SIZE];

	uchar	m_DescSize;
	char	m_szGuildDesc[MAX_GUILD_DESC_SIZE];

	GUILD_CXG_CREATE()
	{
		m_NameSize = 0;
		memset((void *) m_szGuildName, 0, MAX_GUILD_NAME_SIZE);

		m_DescSize = 0;
		memset((void *) m_szGuildDesc, 0, MAX_GUILD_DESC_SIZE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_NameSize) + m_NameSize + sizeof(m_DescSize) + m_DescSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};
struct GUILD_CXG_MOVE_MEMBER :
	public SGuildPacket
{
	char	m_cSrcFamilyIndex;
	char	m_cDestFamilyIndex;
	int32	m_iGuildIndex;
	GUID_t	m_TargetGuid;

	GUILD_CXG_MOVE_MEMBER()
	{
		m_cSrcFamilyIndex = INVALID_ID;
		m_cDestFamilyIndex = INVALID_ID;
		m_iGuildIndex = INVALID_ID;
		m_TargetGuid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_cSrcFamilyIndex) + sizeof(m_cDestFamilyIndex) + sizeof(m_iGuildIndex) + sizeof(m_TargetGuid);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_APPOINT_POS :
	public SGuildPacket
{
	GUID_t	m_TargetGuid;
	int32	m_nPos;

	GUILD_CXG_APPOINT_POS()
	{
		m_nPos = INVALID_ID;
		m_TargetGuid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nPos) + sizeof(m_TargetGuid);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_CANCEL_POS :
	public SGuildPacket
{
	GUID_t	m_TargetGuid;
	int32	m_nPos;

	GUILD_CXG_CANCEL_POS()
	{
		m_nPos = INVALID_ID;
		m_TargetGuid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nPos) + sizeof(m_TargetGuid);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};
struct GUILD_CXG_MODIFY_ACTIVITY_PARAM :
	public SGuildPacket
{
	int32 m_arrParam[GUILD_ACTIVITY_PARAM_COUNT];

	GUILD_CXG_MODIFY_ACTIVITY_PARAM()
	{
		for(int32 i=0; i<GUILD_ACTIVITY_PARAM_COUNT; i++)
		{
			m_arrParam[i] = 0;
		}
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual uint32 GetPacketSize() const
	{
		return sizeof(int32)*GUILD_ACTIVITY_PARAM_COUNT;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_MODIFY_DESC :
	public SGuildPacket
{
	uchar	m_DescSize;
	char	m_szGuildDesc[MAX_GUILD_DESC_SIZE];

	GUILD_CXG_MODIFY_DESC()
	{
		m_DescSize = 0;
		memset((void *) m_szGuildDesc, 0, MAX_GUILD_DESC_SIZE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_DescSize) + m_DescSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_MODIFY_TITLE_NAME :
	public SGuildPacket
{
	uchar	m_NameSize;
	char	m_szTitleName[MAX_CHARACTER_TITLE];
	GUID_t	m_TargetGuid;

	GUILD_CXG_MODIFY_TITLE_NAME()
	{
		m_NameSize = 0;
		memset((void *) m_szTitleName, 0, MAX_CHARACTER_TITLE);
		m_TargetGuid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_NameSize) + m_NameSize + sizeof(m_TargetGuid);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_JOIN :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	GUID_t		m_TargetGuid;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_TargetGuid);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_INVITE :
	public SGuildPacket
{
	uchar	m_NameSize;
	char	m_szTargetName[MAX_CHARACTER_NAME];

	GUILD_CXG_INVITE()
	{
		m_NameSize = 0;
		memset((void *) m_szTargetName, 0, MAX_CHARACTER_NAME);
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(uchar) + m_NameSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_CREATE_FAMILY :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	uchar		m_cDescSize;
	uchar		m_cNameSize;
	char		m_szFamilyDesc[MAX_GUILD_FAMILY_DESC_SIZE];
	char		m_szFamilyName[MAX_GUILD_FAMILY_NAME_SIZE];
	char		m_szFamilyBossName[MAX_CHARACTER_NAME];

	GUILD_CXG_CREATE_FAMILY()
	{
		m_GuildGUID = INVALID_GUILD_ID;
		m_cDescSize = 0;
		m_cNameSize = 0;
		memset((void *) m_szFamilyDesc, 0, MAX_GUILD_FAMILY_DESC_SIZE);
		memset((void *) m_szFamilyName, 0, MAX_GUILD_FAMILY_NAME_SIZE);
		memset((void *) m_szFamilyBossName, 0, MAX_CHARACTER_NAME);
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(uchar) * 2 + m_cDescSize + m_cNameSize + sizeof(m_szFamilyBossName);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ADD_FAMILY_USER :
	public SGuildPacket
{
	char	m_cFamilyIndex;
	int32	m_iGuildIndex;
	GUID_t	m_TargetGuid;

	GUILD_CXG_ADD_FAMILY_USER()
	{
		m_cFamilyIndex = INVALID_ID;
		m_iGuildIndex = INVALID_ID;
		m_TargetGuid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(char) + sizeof(int32) + sizeof(GUID_t);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_REMOVE_FAMILY_USER :
	public SGuildPacket
{
	char	m_cFamilyIndex;
	int32	m_iGuildIndex;
	GUID_t	m_TargetGuid;

	GUILD_CXG_REMOVE_FAMILY_USER()
	{
		m_cFamilyIndex = INVALID_ID;
		m_iGuildIndex = INVALID_ID;
		m_TargetGuid = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(char) + sizeof(int32) + sizeof(GUID_t);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_FAMILY_DISMISS :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	int32		m_nFamilyID;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ASKINFO :
	public SGuildPacket
{
	enum 
	{ 
		GUILD_MEMBER_INFO_ONLINE = 0, 
		GUILD_MEMBER_INFO_OFFLINE, 
		GUILD_MEMBER_INFO_ALL, 
		GUILD_INFO_LOGIN,
		GUILD_INFO, 
		GUILD_APPOINT_POS, 
		GUILD_SELF_INFO,
		GUILD_ACTIVITY_SETTING,
		GUILD_SKILL_INFO,
	};

	GUILD_CXG_ASKINFO()
	{
		m_GuildGUID = INVALID_GUILD_ID;
		m_Type = INVALID_ID;
		m_cPwdSize = 0;
		memset(m_Password, 0, MAX_PWD);
	}
	GuildID_t	m_GuildGUID;
	uchar		m_Type;

	uchar		m_cPwdSize;
	char		m_Password[MAX_PWD];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(uchar) + m_cPwdSize + sizeof(m_cPwdSize);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_APPOINT :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	GUID_t		m_CandidateGUID;
	uchar		m_NewPosition;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_CandidateGUID) + sizeof(m_NewPosition);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ADJUSTAUTH :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	GUID_t		m_CandidateGUID;
	uchar		m_NewAuthority;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_CandidateGUID) + sizeof(m_NewAuthority);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_LEVELUP :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	GUID_t		m_ChiefGUID;
	uchar		m_GuildLevel;
	int32		m_GP;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_ChiefGUID) + sizeof(m_GuildLevel) + sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_SKILLLEVELUP :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	int32	m_nSkillID;
	uchar	m_nType;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_nSkillID) + sizeof(m_nType);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_LEVELDOWN:
	public SGuildPacket
{
	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return 0;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


struct GUILD_CXG_GEXP :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	int32		m_GExp;
	char		m_szGuildName[MAX_GUILD_NAME_SIZE];
	
	// log 相关
	int32		m_OpType;
	int32		m_nParam;
	int32		m_nScriptId;

	GUILD_CXG_GEXP()
	{
		m_GuildGUID = -1;
		m_GExp = 0;
		memset(m_szGuildName,0,MAX_GUILD_NAME_SIZE);
		m_OpType = 0;
		m_nParam = 0;
		m_nScriptId = -1;
	}

	void SetGuildName(const char * szName)
	{
		memset( m_szGuildName, 0, MAX_GUILD_NAME_SIZE );
		strncpy( m_szGuildName, szName, MAX_GUILD_NAME_SIZE );
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_GExp) + MAX_GUILD_NAME_SIZE + sizeof(int32) + sizeof(int32) + sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_GP :
	public SGuildPacket
{
	GuildID_t	m_GuildGUID;
	GUID_t		m_TargetGUID;
	int32		m_GP;
	uchar		m_bDelta;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildGUID) + sizeof(m_GP) + sizeof(m_TargetGUID) + sizeof(m_bDelta);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ADD_MERIT :
	public SGuildPacket
{
	int32		m_nDelta;

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nDelta);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

enum GUILD_CXG_ADD_MEMBER_VALUE_TYPE
{
	GUILD_CXG_ADD_MEMBER_INVAID = -1,
	GUILD_CXG_ADD_MEMBER_ACTIVITY = 0,
};
struct GUILD_CXG_ADD_MEMBER_VALUE :
	public SGuildPacket
{
	int32		m_nValue;
	int16		m_nType;

	GUILD_CXG_ADD_MEMBER_VALUE()
	{
		Clear();
	}

	virtual void Clear()
	{
		m_nValue =0;
		m_nType = GUILD_CXG_ADD_MEMBER_INVAID;
	}

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nValue)+sizeof(m_nType);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ADD_MONEY :
	public SGuildPacket
{
	int32		m_nDelta;

	int32		m_OpType;
	int32		m_nParam;
	int32		m_nScriptId;

	GUILD_CXG_ADD_MONEY()
	{
		m_nDelta = 0;
		m_OpType = 0;
		m_nParam = 0;
		m_nScriptId = -1;
	}

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nDelta) + sizeof(int32) + sizeof(int32) + sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_SET_MULTIMISSION :
	public SGuildPacket
{
	uchar		m_OpType;
	uchar		m_MissionType;
	uchar		m_Enable;

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_OpType) + sizeof(m_MissionType) + sizeof(m_Enable);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ASK_LAIRDDATA :
	public SGuildPacket
{
	uchar	  m_byVersion;

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_byVersion) ;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_LEVELINFO :
	public SGuildPacket
{
	int32	m_nMaxMemberCount;
	int32	m_nMaxFamilyCount;
	int32	m_nMaxGoldFamilyUserCount;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(int32) * 3;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_RECRUIT :
	public SGuildPacket
{
	GUID_t	m_ProposerGUID;
	BOOL	m_bAgree;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_ProposerGUID) + sizeof(m_bAgree);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_EXPEL :
	public SGuildPacket
{
	GUID_t	m_GuildUserGUID;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildUserGUID);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_WITHDRAW :
	public SGuildPacket
{
	uint32	m_MoneyAmount;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_MoneyAmount);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_DEPOSIT :
	public SGuildPacket
{
	uint32	m_MoneyAmount;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_MoneyAmount);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_DEMISE :
	public SGuildPacket
{
	GUID_t	m_DestGUID;

	GUILD_CXG_DEMISE()
	{
		m_DestGUID = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_DestGUID);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_LEAVE :
	public SGuildPacket
{

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Read(RecieveStream &iStream)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Write(SendStream &oStream) const
	{
	}
};

struct GUILD_CXG_CHANG_DESC :
	public SGuildPacket
{
	char	m_GuildDesc[MAX_GUILD_DESC_SIZE];
	uchar	m_GuildDescLength;

	GUILD_CXG_CHANG_DESC()
	{
		memset(m_GuildDesc, 0, MAX_GUILD_DESC_SIZE);
		m_GuildDescLength = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(uchar) + m_GuildDescLength;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_INVITE_CONFIRM :
	public SGuildPacket
{
	GuildID_t	m_GuildId;
	BOOL		m_AgreeInvite;
	uchar		m_InvitorNameSize;
	char		m_InvitorName[MAX_CHARACTER_NAME];

	GUILD_CXG_INVITE_CONFIRM()
	{
		m_GuildId = INVALID_ID;
		m_AgreeInvite = TRUE;
		m_InvitorNameSize = 0;
		memset(&m_InvitorName[0], 0, MAX_CHARACTER_NAME);
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(GuildID_t) + sizeof(BOOL) + m_InvitorNameSize + sizeof(m_InvitorNameSize);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_APPOINT_INFO :
	public SGuildPacket
{
	struct s
	{
		char	m_PosName[MAX_GUILD_POS_NAME_SIZE];
		uchar	m_PosID;
		s()
		{
			memset(m_PosName, 0, MAX_GUILD_POS_NAME_SIZE);
			m_PosID = 0;
		}
	}
	m_PosList[GUILD_POSITION_SIZE];
	int32	iPosNum;

	GUILD_GXC_APPOINT_INFO()
	{
		iPosNum = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(iPosNum) + sizeof(s) * iPosNum;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


/*
==============================================================================================================
==============================================================================================================
*/
struct GUILD_GXC_GUILD_INFO :
	public SGuildPacket
{
	GuildID_t	m_GuildID;
	int32		m_nFamilyID;
	uchar		m_GuildNameSize;
	char		m_GuildName[MAX_GUILD_NAME_SIZE];
	uchar		m_GuildChairManSize;
	char		m_GuildChairMan[MAX_CHARACTER_NAME];
	uchar		m_FamilyNameSize;
	char		m_FamilyName[MAX_GUILD_FAMILY_NAME_SIZE];
	uchar		m_GuildNoticeSize;
	char		m_GuildNotice[MAX_GUILD_DESC_SIZE];
	GUID_t		m_ChiefGUID;
	uchar		m_nLevel;
	int32		m_nPortSceneID;
	int32		m_MemNum;
	int32		m_nGuildExp;
	int32		m_FoundedMoney;
	int32		m_GuildMerchStatus[MAX_GUILDMERCH_USEINT];
	uchar		m_bSynchronizeInfo;
	int32		m_nBattleMark;
	uchar		m_bNewMemberFlag;
	int16		m_nShiMing;
	int32		m_nMultiMission_HuShou;
	int32		m_nMultiMission_HeiMu;
	int32		m_nMultiMission_AnZhan;
	int32		m_nMultiMission_ChuYao;
	int32		m_nMultiMission_MuJi;
	
	//活跃度参数
	int32		m_arrActivityParam[GUILD_ACTIVITY_PARAM_COUNT];
	// 帮会BUS技能
	int32		m_aBusSkillID[MAX_GUILD_BUS_SKILL_NUM];

	int32		m_nChiefMultiMissionDay;
	int32		m_nAssChiefMultiMissionDay;

	//据点战经验
	int32		m_nLairdExp;

	//帮会上月的消费金额
	int32 		m_nLastMonth_Guild_Member_Money;
	//帮会本月的消费金额
	int32 		m_nCurMonth_Guild_Member_Money;

	int32       m_nLastMonth;
	int32       m_nCurMonth;

	

	GUILD_GXC_GUILD_INFO()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_GuildID = INVALID_GUILD_ID;
		m_nFamilyID = INVALID_ID;

		m_GuildNameSize = 0;
		m_GuildChairManSize = 0;
		m_FamilyNameSize = 0;
		m_GuildNoticeSize = 0;
		memset(m_GuildName, 0, MAX_GUILD_NAME_SIZE);
		memset(m_GuildChairMan, 0, MAX_CHARACTER_NAME);
		memset(m_FamilyName, 0, MAX_GUILD_FAMILY_NAME_SIZE);
		memset(m_GuildNotice, 0, MAX_GUILD_DESC_SIZE);

		m_ChiefGUID = INVALID_GUID;
		m_nLevel = 0;
		m_nPortSceneID = 0;
		m_MemNum = 0;
		m_nGuildExp = 0;
		m_FoundedMoney = 0;
		memset(m_GuildMerchStatus, 0, sizeof(int32) * MAX_GUILDMERCH_USEINT);
		m_bSynchronizeInfo = 0;
		m_nBattleMark = 0;
		m_bNewMemberFlag = 0;
		m_nShiMing = 0;

		m_nMultiMission_HuShou = -1;
		m_nMultiMission_HeiMu = -1;
		m_nMultiMission_AnZhan = -1;
		m_nMultiMission_ChuYao = -1;
		m_nMultiMission_MuJi = -1;

		m_nChiefMultiMissionDay = -1;
		m_nAssChiefMultiMissionDay = -1;

		int32 i=0;
		for(i=0; i<GUILD_ACTIVITY_PARAM_COUNT; i++)
		{
			m_arrActivityParam[i] =0;
		}

		for(i=0; i<MAX_GUILD_BUS_SKILL_NUM; i++)
		{
			m_aBusSkillID[i] = 0;
		}

		m_nLairdExp = 0;
		m_nLastMonth_Guild_Member_Money = 0;
		m_nCurMonth_Guild_Member_Money  = 0;
		m_nLastMonth = 0;
		m_nCurMonth  = 0;
		
		
	}

	void SetGuildName(const char* szGuildName)
	{
		memset( m_GuildName, 0, MAX_GUILD_NAME_SIZE );
		m_GuildNameSize = (uchar)strlen(szGuildName);
		if( m_GuildNameSize >= MAX_GUILD_NAME_SIZE)
			m_GuildNameSize = MAX_GUILD_NAME_SIZE - 1;
		memcpy( m_GuildName, szGuildName, m_GuildNameSize );
	}

	void SetGuildChairMan(const char* szChairMan)
	{
		memset( m_GuildChairMan, 0, MAX_CHARACTER_NAME );
		m_GuildChairManSize = (uchar)strlen(szChairMan);
		if( m_GuildChairManSize >= MAX_CHARACTER_NAME)
			m_GuildChairManSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_GuildChairMan, szChairMan, m_GuildChairManSize );		
	}

	void SetFamilyName(const char* szFamilyName)
	{
		memset( m_FamilyName, 0, MAX_GUILD_FAMILY_NAME_SIZE );
		m_FamilyNameSize = (uchar)strlen(szFamilyName);
		if( m_FamilyNameSize >= MAX_GUILD_FAMILY_NAME_SIZE)
			m_FamilyNameSize = MAX_GUILD_FAMILY_NAME_SIZE - 1;
		memcpy( m_FamilyName, szFamilyName, m_FamilyNameSize );		
	}

	void SetGuildNotice(const char* szNotice)
	{
		memset( m_GuildNotice, 0, MAX_GUILD_DESC_SIZE );
		uint32 uTmp = (uint32)strlen(szNotice);
		if( uTmp >= MAX_GUILD_DESC_SIZE )
			uTmp = MAX_GUILD_DESC_SIZE - 1;
		m_GuildNoticeSize = (uchar)uTmp;
		if( m_GuildNoticeSize >= MAX_GUILD_DESC_SIZE)
			m_GuildNoticeSize = MAX_GUILD_DESC_SIZE - 1;
		memcpy( m_GuildNotice, szNotice, m_GuildNoticeSize );				
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual uint32 GetPacketSize() const
	{
		uint32 uSize = 0;
		uSize += sizeof(m_GuildID) + sizeof(m_nFamilyID) + sizeof(m_nLevel) + sizeof(m_nPortSceneID) + sizeof(m_MemNum) + sizeof(m_ChiefGUID) +
			sizeof(m_nGuildExp) +
			sizeof(m_FoundedMoney) +
			sizeof(m_bSynchronizeInfo) +
			sizeof(m_GuildNameSize) + m_GuildNameSize +
			sizeof(m_GuildChairManSize) + m_GuildChairManSize +
			sizeof(m_FamilyNameSize) + m_FamilyNameSize +
			sizeof(m_GuildNoticeSize) + m_GuildNoticeSize +
			sizeof(int32) * MAX_GUILDMERCH_USEINT +
			sizeof(m_nBattleMark)+
			sizeof(m_bNewMemberFlag) +
			sizeof(m_nShiMing) +
			sizeof(m_nMultiMission_HuShou) +
			sizeof(m_nMultiMission_HeiMu) +
			sizeof(m_nMultiMission_AnZhan) +
			sizeof(m_nMultiMission_ChuYao) +
			sizeof(m_nMultiMission_MuJi)+
			sizeof(int32)*GUILD_ACTIVITY_PARAM_COUNT + 
			sizeof(m_nLairdExp) + 
			sizeof(m_nLastMonth_Guild_Member_Money) +
			sizeof(m_nCurMonth_Guild_Member_Money)  +
			sizeof(m_nLastMonth) +
			sizeof(m_nCurMonth) +
			sizeof(int32) * MAX_GUILD_BUS_SKILL_NUM;

		if( m_bSynchronizeInfo == 1 )
		{
			uSize += sizeof(m_nChiefMultiMissionDay) + sizeof(m_nAssChiefMultiMissionDay);
		}

		return uSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


/*
===============================================================================================================
===============================================================================================================
 */
struct GUILD_GXC_MEMBER_LIST :
	public SGuildPacket
{
	struct _Member
	{
		enum
		{
			SPECIAL_TITLE_1 = 34,
			SPECIAL_TITLE_2,
			SPECIAL_TITLE_3,
			SPECIAL_TITLE_4
		};

		struct _Member_Bits
		{
			uchar	m_bIsOnline			: 1;
			uchar	m_iSex				: 1;
			uchar	m_bPosition			: 3;
			uchar	m_iFamilyID			: 3;
			_Member_Bits()
			{
				m_bIsOnline = 0;
				m_iSex = 0;
				m_bPosition = 0;
				m_iFamilyID = 7;	// 转换为-1
			}
		};

		uchar			m_uIndex;
		uchar			m_nNameSize;
		uchar			m_nTitleNameSize;
		char			m_szName[MAX_CHARACTER_NAME];
		char			m_szTitleName[MAX_CHARACTER_TITLE];

		GUID_t			m_Guid;
		uchar			m_bLevel;
		uchar			m_bProfessionID;
		int32			m_iCurContribute;
		int32			m_nActivity;							//活跃度
		int32			m_nLastActivity;						//上周活跃度
		int32			m_nMerit;
		_Member_Bits	m_Bits;

		_Member()
		{
			m_uIndex = 0;
			m_nNameSize = 0;
			m_nTitleNameSize = 0;
			memset(m_szName, 0, MAX_CHARACTER_NAME);
			memset(m_szTitleName, 0, MAX_CHARACTER_TITLE);
			m_Guid = INVALID_GUID;
			m_bLevel = 0;
			m_bProfessionID = PROFESSION_NONE;
			m_iCurContribute = 0;
			m_nActivity = 0;
			m_nLastActivity = 0;
			m_nMerit = 0;
		}

		void SetName(const char* szName)
		{
			memset( m_szName, 0, MAX_CHARACTER_NAME );
			m_nNameSize = (uchar)strlen(szName);
			if( m_nNameSize >= MAX_CHARACTER_NAME )
				m_nNameSize = MAX_CHARACTER_NAME - 1;
			memcpy( m_szName, szName, m_nNameSize );
		}

		void SetTitleName(const char* szTitleName)
		{
			memset( m_szTitleName, 0, MAX_CHARACTER_TITLE );
			m_nTitleNameSize = (uchar)strlen(szTitleName);
			if( m_nTitleNameSize >= MAX_CHARACTER_TITLE )
				m_nTitleNameSize = MAX_CHARACTER_TITLE - 1;
			memcpy( m_szTitleName, szTitleName, m_nTitleNameSize );					
		}

		void SetSpecialTitleName(char nSpecialType)
		{
			m_nTitleNameSize = nSpecialType;
		}

		BOOL IsSpecialTitleName() const
		{
			if( m_nTitleNameSize == SPECIAL_TITLE_1
				|| m_nTitleNameSize == SPECIAL_TITLE_2
				|| m_nTitleNameSize == SPECIAL_TITLE_3
				|| m_nTitleNameSize == SPECIAL_TITLE_4 )
				return TRUE;
			return FALSE;
		}

		uint32 GetSize() const
		{
			uchar uTitleSize;
			if( IsSpecialTitleName() )
				uTitleSize = 0;
			else
				uTitleSize = m_nTitleNameSize;
			return sizeof(m_uIndex) + sizeof(m_nNameSize) + m_nNameSize +
					sizeof(m_nTitleNameSize) + uTitleSize +
					sizeof(m_Guid) +
					sizeof(m_bLevel) +
					sizeof(m_bProfessionID) +
					sizeof(m_iCurContribute) +
					sizeof(m_nActivity) +
					sizeof(m_nLastActivity) +
					sizeof(m_nMerit) +
					sizeof(m_Bits);
					
		}

		
	};
	

	struct _Family
	{
		char	m_iFamilyID;
		uchar	m_nFamilyNameSize;
		char	m_szFamilyName[MAX_GUILD_FAMILY_NAME_SIZE];

		_Family()
		{
			m_nFamilyNameSize = 0;
			memset(m_szFamilyName, 0, MAX_GUILD_FAMILY_NAME_SIZE);
			m_iFamilyID = INVALID_ID;
		}

		void SetFamilyName(const char* szFamilyName)
		{
			memset( m_szFamilyName, 0, MAX_GUILD_FAMILY_NAME_SIZE );
			m_nFamilyNameSize = (uchar)strlen(szFamilyName);
			if( m_nFamilyNameSize >= MAX_GUILD_FAMILY_NAME_SIZE )
				m_nFamilyNameSize = MAX_GUILD_FAMILY_NAME_SIZE - 1;
			memcpy( m_szFamilyName, szFamilyName, m_nFamilyNameSize );
		}

		uint32 GetSize() const 
		{
			return sizeof(m_iFamilyID) + sizeof(m_nFamilyNameSize) + m_nFamilyNameSize;
		}

	};


	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar	m_uMemberCount;
	uchar	m_uSendCount;
	uchar	m_uFamilyCount;
	uchar	m_bPosition;
	uchar	m_bAccess;
	uchar	m_bOnlineFlag;
	_Member	m_GuildMemberData[USER_ARRAY_SIZE];
	_Family	m_GuildFamilyData[GUILD_FAMILY_SIZE];
	

	GUILD_GXC_MEMBER_LIST()
	{
		m_uMemberCount = 0;
		m_bPosition = 0;
		m_bAccess = 0;
		m_uFamilyCount = 0;
		m_uSendCount = 0;
		m_bOnlineFlag = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		uchar i;
		uint32 uBaseSize = 0;
		uint32 uMemberSize = 0;
		uint32 uFamilySize = 0;

		uBaseSize = sizeof(m_uMemberCount) + 
					sizeof(m_uSendCount) +
					sizeof(m_uFamilyCount) +
					sizeof(m_bPosition) +
					sizeof(m_bAccess) +
					sizeof(m_bOnlineFlag);
		
		for( i=0; i<m_uMemberCount; ++i )
		{
			uMemberSize +=m_GuildMemberData[i].GetSize();
		}

		for( i=0; i<m_uFamilyCount; ++i )
		{
			uFamilySize += m_GuildFamilyData[i].GetSize();
		}

		return uBaseSize + uMemberSize + uFamilySize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

enum GUILD_GXC_REFRESH_MEMBER_INFO_MODE
{
	GUILD_GXC_REFRESH_MEMBER_INFO_UPDATE =0,
	GUILD_GXC_REFRESH_MEMBER_INFO_DELETE =1,
};

struct GUILD_GXC_REFRESH_MEMBER_INFO :
	public SGuildPacket
{
	GuildID_t   m_GuildID;
	GUID_t		m_GUID;
	int32		m_nMemberIndex;

	int32		m_nActivity;							//活跃度
	int32		m_nLastActivity;						//上周活跃度
	uchar		m_nMode;								//操作模式	

	GUILD_GXC_REFRESH_MEMBER_INFO()
	{
		Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Clear()
	{
		m_GuildID = INVALID_GUILD_ID;
		m_GUID = INVALID_GUID;
		m_nMemberIndex = INVALID_ID;

		m_nActivity = 0;
		m_nLastActivity = 0;

		m_nMode = GUILD_GXC_REFRESH_MEMBER_INFO_UPDATE;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildID)+sizeof(m_GUID)+sizeof(m_nMemberIndex)+sizeof(m_nActivity)+sizeof(m_nLastActivity)+sizeof(m_nMode);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


struct GUILD_GXC_REFRESH_ALL_MEMBER_INFO :
	public SGuildPacket
{
	

	uchar	m_uMemberCount;
	uchar	m_uSendCount;
	GuildID_t m_GuildId;
	GUILD_GXC_REFRESH_MEMBER_INFO	m_GuildMemberData[USER_ARRAY_SIZE];
	

	GUILD_GXC_REFRESH_ALL_MEMBER_INFO()
	{
		m_uMemberCount = 0;
		m_uSendCount = 0;
		m_GuildId = INVALID_GUILD_ID;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual uint32 GetPacketSize() const
	{
		uchar i;
		uint32 uBaseSize = 0;
		uint32 uMemberSize = 0;

		uBaseSize = sizeof(m_uMemberCount) + 
			sizeof(m_uSendCount)+
			sizeof(m_GuildId);

		for( i=0; i<m_uMemberCount; ++i )
		{
			uMemberSize +=m_GuildMemberData[i].GetPacketSize();
		}

		
		return uBaseSize + uMemberSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_LIST :
	public SGuildPacket
{
	uint16	m_uStartIndex;
	uint16	m_uGuildCount;
	uchar	m_uGuildListCount;

	struct s
	{
		s()
		{
			m_GuildID = INVALID_ID;
			memset((void *) m_GuildName, 0, sizeof(m_GuildName));
			memset((void *) m_GuildDesc, 0, sizeof(m_GuildDesc));
			memset((void *) m_CityName, 0, sizeof(m_CityName));
			memset((void *) m_ChiefName, 0, sizeof(m_ChiefName));
			m_uGuildStatus = 0;
			m_uGuildUserCount = 0;
			m_bGuildLevel = 0;
			m_PortSceneID = -1;
			m_nFoundedTime = 0;
		}
		GuildID_t	m_GuildID;
		char		m_ChiefName[MAX_CHARACTER_NAME];
		char		m_GuildName[MAX_GUILD_NAME_SIZE];
		char		m_GuildDesc[MAX_GUILD_DESC_SIZE];
		char		m_CityName[MAX_CITY_NAME_SIZE];
		int32		m_PortSceneID;
		uchar		m_uGuildStatus;
		uchar		m_uGuildUserCount;
		uchar		m_bGuildLevel;
		int32		m_nFoundedTime;
	} m_uGuild[MAX_GUILD_LIST_COUNT];

	GUILD_GXC_LIST()
	{
		m_uStartIndex = 0;
		m_uGuildCount = 0;
		m_uGuildListCount = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_uStartIndex) +
			sizeof(m_uGuildCount) +
			sizeof(m_uGuildListCount) +
			m_uGuildListCount *
			sizeof(s);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_MODIFY_TITLE_NAME :
	public SGuildPacket
{
	GUID_t	m_Guid;
	uchar	m_uTitleNameSize;
	char	m_szTitleName[MAX_CHARACTER_TITLE];

	GUILD_GXC_MODIFY_TITLE_NAME()
	{
		m_Guid = INVALID_GUID;
		m_uTitleNameSize = 0;
		memset(m_szTitleName, 0, MAX_CHARACTER_TITLE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(GUID_t) + sizeof(uchar) + m_uTitleNameSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_INVITE :
	public SGuildPacket
{
	GuildID_t	m_GuildId;
	uchar		m_GuildNameSize;
	char		m_GuildName[MAX_GUILD_NAME_SIZE];
	uchar		m_InvitorNameSize;
	char		m_InvitorName[MAX_CHARACTER_NAME];

	GUILD_GXC_INVITE()
	{
		m_GuildId = INVALID_ID;
		m_GuildNameSize = 0;
		m_InvitorNameSize = 0;
		memset((void *) m_GuildName, 0, sizeof(m_GuildName));
		memset((void *) m_InvitorName, 0, sizeof(m_InvitorName));
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(GuildID_t) + sizeof(uchar) * 2 + m_GuildNameSize + m_InvitorNameSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_ABDICATE :
	public SGuildPacket
{
	GUILD_CXG_ABDICATE()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Read(RecieveStream &iStream)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Write(SendStream &oStream) const
	{
	}
};

struct GUILD_CXG_MODIFYFAMILYNAME :
	public SGuildPacket
{
	int32	m_nFamilyID;
	char	m_szFamilyName[MAX_GUILD_FAMILY_NAME_SIZE];

	GUILD_CXG_MODIFYFAMILYNAME()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nFamilyID) + sizeof(m_szFamilyName);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_SELF_GUILD_INFO :
	public SGuildPacket
{
	uchar	m_Position;
	int32	m_nGP;

	GUILD_GXC_SELF_GUILD_INFO()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_Position = 0;
		m_nGP = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(uchar) + sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_INVITE_INFO :
	public SGuildPacket
{
	GuildID_t	m_GuildId;
	GUID_t		m_TargetGuid;
	uchar		m_TargetNameSize;
	char		m_TargetName[MAX_CHARACTER_NAME];

	GUILD_GXC_INVITE_INFO()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_TargetName, 0, MAX_CHARACTER_NAME);
		m_GuildId = INVALID_ID;
		m_TargetGuid = INVALID_GUID;
		m_TargetNameSize = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(uchar) + sizeof(m_GuildId) + sizeof(m_TargetGuid) + m_TargetNameSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_SCRIPT_CALLBACK :
	public SGuildPacket
{
#define FuncNameLen	32
	enum { GUILD_SCRIPT_CALLBACK_INVALID = 0, GUILD_SCRIPT_CALLBACK_EXPBUILD = 1, };

	GuildID_t m_GuildId;
	ScriptID_t m_ScriptID;
	uchar m_cType;
	char m_szFuncName[FuncNameLen];
	int32 m_param1;
	int32 m_param2;
	int32 m_param3;
	int32 m_param4;

	GUILD_GXC_SCRIPT_CALLBACK()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_GuildId = INVALID_GUILD_ID;
		m_ScriptID = 0;
		m_cType = (uchar) GUILD_SCRIPT_CALLBACK_INVALID;
		memset(m_szFuncName, 0, FuncNameLen);
		m_param1 = 0;
		m_param2 = 0;
		m_param3 = 0;
		m_param4 = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildId) + sizeof(m_ScriptID) + sizeof(m_cType) + sizeof(m_szFuncName) + sizeof(m_param1) + sizeof(m_param2) + sizeof(m_param3) + sizeof(m_param4);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_SET_FREEPARAM :
	public SGuildPacket
{
	char	m_szGuildName[MAX_GUILD_NAME_SIZE];
	int32	m_nIndex;
	int32	m_nValue;

	GUILD_GXC_SET_FREEPARAM()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nIndex = -1;
		m_nValue = -1;
		memset(m_szGuildName, 0, MAX_GUILD_NAME_SIZE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_szGuildName) + sizeof(m_nIndex) + sizeof(m_nValue);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_GUILD_STRENGTH :
	public SGuildPacket
{
	GuildID_t	m_guildID;
	int32		m_nStrength;

	GUILD_CXG_GUILD_STRENGTH()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_guildID = -1;
		m_nStrength = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_guildID) + sizeof(m_nStrength);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_CONVOKE :
	public SGuildPacket
{
	MapID_t m_sceneId;
	float	m_PosX;
	float	m_PosZ;

	GUILD_CXG_CONVOKE()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(MapID_t) + sizeof(float) + sizeof(float);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_CONVOKE_CONFIRM :
	public SGuildPacket
{
	GUILD_CXG_CONVOKE_CONFIRM()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return 0;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_MEMBER_JOINTIME :
	public SGuildPacket
{
	int32	m_scriptid;

	GUILD_CXG_MEMBER_JOINTIME()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_scriptid = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_MEMBER_JOINTIME :
	public SGuildPacket
{
	int32	m_scriptid;
	uint32	m_uTime;

	GUILD_GXC_MEMBER_JOINTIME()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_scriptid = 0;
		m_uTime = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(int32) + sizeof(uint32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_DELATE_BROADCAST :
	public SGuildPacket
{
	ID_t		m_WorldID;
	GuildID_t	m_guildId;
	GUID_t		m_guidReqUser;
	char		m_szReqUser[MAX_CHARACTER_NAME];
	MapID_t		m_nSceneId;

	GUILD_GXC_DELATE_BROADCAST()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_WorldID = INVALID_ID;
		m_guildId = INVALID_GUILD_ID;
		m_guidReqUser = INVALID_GUID;
		memset(m_szReqUser, 0, sizeof(m_szReqUser));
		m_nSceneId = INVALID_ID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(ID_t) + sizeof(m_guildId) + sizeof(m_guidReqUser) + sizeof(m_szReqUser) + sizeof(m_nSceneId);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_CXG_DELATE_VOTE :
	public SGuildPacket
{
	GUID_t	m_nWhoIVote;

	GUILD_CXG_DELATE_VOTE()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nWhoIVote = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(GUID_t);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


struct GUILD_CXG_SHIMING :
	public SGuildPacket
{
	int32		m_nValue;

	int32		m_OpType;
	int32		m_nParam;
	int32		m_nScriptId;

	GUILD_CXG_SHIMING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nValue = 0;
		m_OpType = 0;
		m_nParam = 0;
		m_nScriptId = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(int32) + sizeof(int32) + sizeof(int32) + sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


struct GUILD_GXC_CONVOKE :
	public SGuildPacket
{
	enum { SUCCESS = 0, ALREADY_CONVOKE, };

	int32 m_nFlag;

	GUILD_GXC_CONVOKE()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nFlag = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(int32);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_CONVOKE_SUCCESS :
	public SGuildPacket
{
	MapID_t m_sceneId;
	float	m_PosX;
	float	m_PosZ;

	GUILD_GXC_CONVOKE_SUCCESS()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(MapID_t) + sizeof(float) + sizeof(float);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_SET_MEMBER_GP :
	public SGuildPacket
{
	int32	m_nGP;

	GUILD_GXC_SET_MEMBER_GP()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nGP = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nGP);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_SET_MEMBER_MERIT :
	public SGuildPacket
{
	int32	m_nMerit;

	GUILD_GXC_SET_MEMBER_MERIT()
	{
		Clear();
	}

	void Clear()
	{
		m_nMerit = 0;
	}

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nMerit);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_SET_MULTIMISSION :
	public SGuildPacket
{
	uchar	m_nCount;
	uchar	m_nMissionType[5];
	uint32	m_uIssueTime[5];

	GUILD_GXC_SET_MULTIMISSION()
	{
		Clear();
	}

	void Clear()
	{
		m_nCount = 0;
		memset( m_nMissionType, 0, sizeof(m_nMissionType) );
		memset( m_uIssueTime, 0, sizeof(m_uIssueTime) );
	}

	void AddIssue(uchar type,uint32 uTime)
	{
		if( m_nCount >=5 )
			return;

		m_nMissionType[m_nCount] = type;
		m_uIssueTime[m_nCount] = uTime;
		m_nCount++;
	}

	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_nCount) + (sizeof(uchar) + sizeof(uint32))*m_nCount;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


struct GUILD_GXC_SYNC_LAIRDINFO :
	public SGuildPacket
{
	uchar  m_byBroadcastToPlayer;
	MapID_t m_nMapID;
	uchar  m_byLairdInfoVersion;
	uchar  m_bySendNameFlag;

	MapID_t	m_aMapIdLaird0[MAX_GUILDLAIRD_NUM];
	MapID_t	m_aMapIdLaird1[MAX_GUILDLAIRD_NUM];
	MapID_t	m_aMapIdLaird2[MAX_GUILDLAIRD_NUM];
	GuildID_t m_aGuildLaird[MAX_GUILDLAIRD_NUM];
	int32 m_aLairdDate[MAX_GUILDLAIRD_NUM];
	CountryID_t m_aLairdCountry[MAX_GUILDLAIRD_NUM];
	uchar m_aLairdLevel[MAX_GUILDLAIRD_NUM];

	char m_aGuildName[MAX_GUILDLAIRD_NUM][MAX_GUILD_NAME_SIZE+1];
	uchar m_aGuildNameLen[MAX_GUILDLAIRD_NUM];

	char m_aChiefName[MAX_GUILDLAIRD_NUM][MAX_CHARACTER_NAME+1];
	uchar m_aChiefNameLen[MAX_GUILDLAIRD_NUM];
	
	GUILD_GXC_SYNC_LAIRDINFO()
	{
		Clear();
	}

	void Clear()
	{
		m_byBroadcastToPlayer = 0;
		m_nMapID = INVALID_ID;
		m_byLairdInfoVersion = 0;
		m_bySendNameFlag = 0;
		memset(m_aMapIdLaird0,INVALID_ID,sizeof(m_aMapIdLaird0));
		memset(m_aMapIdLaird1,INVALID_ID,sizeof(m_aMapIdLaird1));
		memset(m_aMapIdLaird2,INVALID_ID,sizeof(m_aMapIdLaird2));
		memset(m_aGuildLaird, INVALID_ID,sizeof(m_aGuildLaird) );
		memset(m_aLairdDate, INVALID_ID,sizeof(m_aLairdDate) );
		memset(m_aLairdCountry, INVALID_ID,sizeof(m_aLairdCountry) );
		memset(m_aLairdLevel,0,sizeof(m_aLairdLevel));

		memset(m_aGuildName,0,sizeof(m_aGuildName));
		memset(m_aGuildNameLen,0,sizeof(m_aGuildNameLen));

		memset(m_aChiefName,0,sizeof(m_aChiefName));
		memset(m_aChiefNameLen,0,sizeof(m_aChiefNameLen));
	}

	void FillData(int nIndex,MapID_t nMapId0,MapID_t nMapId1,MapID_t nMapId2,GuildID_t nGuildId,int32 nDate,CountryID_t nCountry,uchar nLevel )
	{
		if( nIndex < 0 || nIndex >= MAX_GUILDLAIRD_NUM )
			return;

		m_aMapIdLaird0[nIndex] = nMapId0;
		m_aMapIdLaird1[nIndex] = nMapId1;
		m_aMapIdLaird2[nIndex] = nMapId2;
		m_aGuildLaird[nIndex] = nGuildId;
		m_aLairdDate[nIndex] = nDate;
		m_aLairdCountry[nIndex] = nCountry;
		m_aLairdLevel[nIndex] = nLevel;
	}

	void SetGuildName(int nIndex,const char* strGuildName )
	{
		if( strGuildName == NULL )
			return;

		if( nIndex < 0 || nIndex >= MAX_GUILDLAIRD_NUM )
			return;

		strncpy(m_aGuildName[nIndex],strGuildName,MAX_GUILD_NAME_SIZE);
		m_aGuildName[nIndex][MAX_GUILD_NAME_SIZE] = 0;
		m_aGuildNameLen[nIndex] = (uchar)strlen(m_aGuildName[nIndex]);
		m_bySendNameFlag = 1;
	}

	void SetChiefName(int nIndex,const char* strChiefName )
	{
		if( strChiefName == NULL )
			return;

		if( nIndex < 0 || nIndex >= MAX_GUILDLAIRD_NUM )
			return;

		strncpy(m_aChiefName[nIndex],strChiefName,MAX_CHARACTER_NAME);
		m_aChiefName[nIndex][MAX_CHARACTER_NAME] = 0;
		m_aChiefNameLen[nIndex] = (uchar)strlen(m_aChiefName[nIndex]);
		m_bySendNameFlag = 1;
	}

	virtual uint32 GetPacketSize() const
	{
		uint32 uSize = sizeof(m_byBroadcastToPlayer) + sizeof(m_byLairdInfoVersion);
		if( m_byBroadcastToPlayer == 0 )
		{
			uSize += sizeof(m_aMapIdLaird0) + 
				     sizeof(m_aMapIdLaird1) + 
					 sizeof(m_aMapIdLaird2) + 
					 sizeof(m_aGuildLaird) + 
					 sizeof(m_aLairdDate) + 
					 sizeof(m_aLairdCountry) + 
					 sizeof(m_aLairdLevel);
		}
		else
		{
			uSize += sizeof(m_nMapID);
		}

		//名字传输,只有客户端会用
		uSize += sizeof(m_bySendNameFlag);
		if( m_bySendNameFlag  == 1 )
		{
			uSize += sizeof(m_aGuildNameLen);
			for( int i = 0; i<MAX_GUILDLAIRD_NUM; ++i )
			{
				uSize += m_aGuildNameLen[i] * sizeof(char);
			}

			uSize += sizeof(m_aChiefNameLen);
			for( int i = 0; i<MAX_GUILDLAIRD_NUM; ++i )
			{
				uSize += m_aChiefNameLen[i] * sizeof(char);
			}
		}

		return uSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct GUILD_GXC_REFRESH_SKILL_INFO :
	public SGuildPacket
{
	GuildID_t   m_GuildID;
	int32		m_nSkillID;
	int32		m_nSkillLevel;
	int32		m_nSkillIndex;

	GUILD_GXC_REFRESH_SKILL_INFO()
	{
		Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Clear()
	{
		m_GuildID = INVALID_GUILD_ID;
		m_nSkillID = INVALID_ID;
		m_nSkillLevel = 0;
		m_nSkillIndex = INVALID_ID;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual uint32 GetPacketSize() const
	{
		return sizeof(m_GuildID)+sizeof(m_nSkillID)+sizeof(m_nSkillLevel) + sizeof(m_nSkillIndex);
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};


struct GUILD_GXC_REFRESH_ALL_SKILL_INFO :
	public SGuildPacket
{


	uchar	m_uSkillCount;
	GuildID_t m_GuildId;
	GUILD_GXC_REFRESH_SKILL_INFO	m_GuildSkill[MAX_GUILDSKILL_COUNT];


	GUILD_GXC_REFRESH_ALL_SKILL_INFO()
	{
		m_uSkillCount = 0;
		m_GuildId = INVALID_GUILD_ID;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	virtual uint32 GetPacketSize() const
	{
		uchar i;
		uint32 uBaseSize = 0;
		uint32 uMemberSize = 0;

		uBaseSize = sizeof(m_uSkillCount) + 
			sizeof(m_GuildId);

		for( i=0; i<m_uSkillCount; ++i )
		{
			uMemberSize +=m_GuildSkill[i].GetPacketSize();
		}


		return uBaseSize + uMemberSize;
	}

	virtual void	Read(RecieveStream &iStream);
	virtual void	Write(SendStream &oStream) const;
};

struct SGuildExtPacket
{
	uchar			m_uPacketType;
	virtual SGuildPacket	*GetPacket(int32 nPacketType) const = 0;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		SGuildPacket	*pGuildPacket;

		pGuildPacket = GetPacket(m_uPacketType);
		if(pGuildPacket == NULL)
		{
			KCheck(FALSE);
			return 0;
		}

		return(sizeof(m_uPacketType) + pGuildPacket->GetPacketSize());
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct _GUILD_CXG_PACKET :
	public SGuildExtPacket
{
	GUILD_CXG_ASKLIST		m_PacketAskList;
	GUILD_CXG_CREATE		m_PacketCreate;
	GUILD_CXG_JOIN			m_PacketJoin;
	GUILD_CXG_ASKINFO		m_PacketAskInfo;
	GUILD_CXG_APPOINT		m_PacketAppoint;
	GUILD_CXG_ADJUSTAUTH		m_PacketJustAuthority;
	GUILD_CXG_LEVELUP		m_PacketLevelUp;
	GUILD_CXG_LEVELDOWN		m_PacketLevelDown;
	GUILD_CXG_GEXP			m_PacketGEXP;
	GUILD_CXG_LEVELINFO		m_PacketLevelInfo;
	GUILD_CXG_RECRUIT		m_PacketRecruit;
	GUILD_CXG_EXPEL			m_PacketExpel;
	GUILD_CXG_WITHDRAW		m_PacketWithdraw;
	GUILD_CXG_DEPOSIT		m_PacketDeposit;
	GUILD_CXG_LEAVE			m_PacketLeave;
	GUILD_CXG_DEMISE		m_PacketDemise;
	GUILD_CXG_CHANG_DESC		m_PacketChangeDesc;
	GUILD_CXG_INVITE		m_PacketInvite;
	GUILD_CXG_INVITE_CONFIRM	m_PacketInviteConfirm;
	GUILD_CXG_CREATE_FAMILY		m_PacketCreateFamily;
	GUILD_CXG_ADD_FAMILY_USER	m_PacketAddFamilyUser;
	GUILD_CXG_REMOVE_FAMILY_USER	m_PacketRemoveFamilyUser;
	GUILD_CXG_MODIFY_DESC		m_PacketModifyDesc;
	GUILD_CXG_MODIFY_TITLE_NAME	m_PacketModifyTitleName;
	GUILD_CXG_FAMILY_DISMISS	m_PacketFamilyDismiss;
	GUILD_CXG_MOVE_MEMBER		m_PacketMoveMember;
	GUILD_CXG_APPOINT_POS		m_PacketAppointPos;
	GUILD_CXG_CANCEL_POS		m_PacketCancelPos;
	GUILD_CXG_ABDICATE		m_PacketAbdicate;
	GUILD_CXG_GP			m_PacketGP;
	GUILD_CXG_MODIFYFAMILYNAME	m_PacketModifyFamilyName;
	GUILD_GXC_SCRIPT_CALLBACK	m_PacketScriptCallback;
	GUILD_GXC_SET_FREEPARAM		m_PacketSetFreeParam;
	GUILD_CXG_GUILD_STRENGTH	m_PacketGuildStrength;
	GUILD_CXG_CONVOKE		m_PacketConvoke;
	GUILD_CXG_CONVOKE_CONFIRM	m_PacketConvokeConfirm;
	GUILD_CXG_MEMBER_JOINTIME	m_PacketMemberJoinTime;
	GUILD_CXG_DELATE_VOTE		m_PacketDelateVote;
	GUILD_CXG_SHIMING			m_PacketShiMing;
	GUILD_CXG_ADD_MERIT			m_PacketAddMerit;
	GUILD_CXG_ADD_MEMBER_VALUE	m_PacketAddMemberValue;
	GUILD_CXG_ADD_MONEY			m_PacketAddMoney;
	GUILD_CXG_SET_MULTIMISSION	m_PacketSetMultiMission;
	GUILD_CXG_ASK_LAIRDDATA		m_PacketAskLairdData;
	GUILD_CXG_MODIFY_ACTIVITY_PARAM m_PacketModifyActivityParam;
	GUILD_CXG_SKILLLEVELUP m_PacketGuildSkillLevelUp;

	union u
	{
		char	u_AskListSize[sizeof(GUILD_CXG_ASKLIST)];
		char	u_CreateSize[sizeof(GUILD_CXG_CREATE)];
		char	u_JoinSize[sizeof(GUILD_CXG_JOIN)];
		char	u_AskInfoSize[sizeof(GUILD_CXG_ASKINFO)];
		char	u_AppointSize[sizeof(GUILD_CXG_APPOINT)];
		char	u_JustAuthoritySize[sizeof(GUILD_CXG_ADJUSTAUTH)];
		char	u_LevelUp[sizeof(GUILD_CXG_LEVELUP)];
		char	u_LevelDown[sizeof(GUILD_CXG_LEVELDOWN)];
		char	u_GEXP[sizeof(GUILD_CXG_GEXP)];
		char	u_LevelInfo[sizeof(GUILD_CXG_LEVELINFO)];
		char	u_RecruitSize[sizeof(GUILD_CXG_RECRUIT)];
		char	u_ExpelSize[sizeof(GUILD_CXG_EXPEL)];
		char	u_WithdrawSize[sizeof(GUILD_CXG_WITHDRAW)];
		char	u_DepositSize[sizeof(GUILD_CXG_DEPOSIT)];
		char	u_LeaveSize[sizeof(GUILD_CXG_LEAVE)];
		char	u_DemiseSize[sizeof(GUILD_CXG_DEMISE)];
		char	u_ChangeDescSize[sizeof(GUILD_CXG_CHANG_DESC)];
		char	u_InviteSize[sizeof(GUILD_CXG_INVITE)];
		char	u_InviteConfirmSize[sizeof(GUILD_CXG_INVITE_CONFIRM)];
		char	u_CreateFamilySize[sizeof(GUILD_CXG_CREATE_FAMILY)];
		char	u_AddFamilyUserSize[sizeof(GUILD_CXG_ADD_FAMILY_USER)];
		char	u_RemoveFamilyUserSize[sizeof(GUILD_CXG_REMOVE_FAMILY_USER)];
		char	u_ModifyDescSize[sizeof(GUILD_CXG_MODIFY_DESC)];
		char	u_ModifyTitleNameSize[sizeof(GUILD_CXG_MODIFY_TITLE_NAME)];
		char	u_FamilyDismiss[sizeof(GUILD_CXG_FAMILY_DISMISS)];
		char	u_MoveMember[sizeof(GUILD_CXG_MOVE_MEMBER)];
		char	u_AppointPos[sizeof(GUILD_CXG_APPOINT_POS)];
		char	u_CancelPos[sizeof(GUILD_CXG_CANCEL_POS)];
		char	u_Abdicate[sizeof(GUILD_CXG_ABDICATE)];
		char	u_GuildPoint[sizeof(GUILD_CXG_GP)];
		char	u_ModifyFamilyName[sizeof(GUILD_CXG_MODIFYFAMILYNAME)];
		char	u_ScriptCallback[sizeof(GUILD_GXC_SCRIPT_CALLBACK)];
		char	u_SetFreeParam[sizeof(GUILD_GXC_SET_FREEPARAM)];
		char	u_GuildStrength[sizeof(GUILD_CXG_GUILD_STRENGTH)];
		char	u_Convoke[sizeof(GUILD_CXG_CONVOKE)];
		char	u_ConvokeConfirm[sizeof(GUILD_CXG_CONVOKE_CONFIRM)];
		char	u_MemberJoinTime[sizeof(GUILD_CXG_MEMBER_JOINTIME)];
		char	u_DelateVote[sizeof(GUILD_CXG_DELATE_VOTE)];
		char	u_ShiMing[sizeof(GUILD_CXG_SHIMING)];
		char	u_AddMerit[sizeof(GUILD_CXG_ADD_MERIT)];
		char	u_AddMemberValue[sizeof(GUILD_CXG_ADD_MEMBER_VALUE)];
		char	u_AddMoney[sizeof(GUILD_CXG_ADD_MONEY)];
		char	u_SetMultiMission[sizeof(GUILD_CXG_SET_MULTIMISSION)];
		char	u_AskLairdData[sizeof(GUILD_CXG_ASK_LAIRDDATA)];
		char	u_ModifyActivityParam[sizeof(GUILD_CXG_MODIFY_ACTIVITY_PARAM)];
		char	u_GuildSkillLevelUp[sizeof(GUILD_CXG_SKILLLEVELUP)];
		char    u_GuildSENDMAIL[sizeof(GUILD_CXG_SEND_MAIL)];

	};

	_GUILD_CXG_PACKET()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual SGuildPacket *GetPacket(int32 nPacketType) const
	{
		SGuildPacket	*pGuildPacket;

		switch(nPacketType)
		{
		case GUILD_PACKET_CX_ASKLIST:
		case GUILD_PACKET_XG_ASKLIST:
			pGuildPacket = (SGuildPacket *) &m_PacketAskList;
			break;

		case GUILD_PACKET_CX_CREATE:
		case GUILD_PACKET_XG_CREATE:
			pGuildPacket = (SGuildPacket *) &m_PacketCreate;
			break;

		case GUILD_PACKET_CX_JOIN:
		case GUILD_PACKET_XG_JOIN:
			pGuildPacket = (SGuildPacket *) &m_PacketJoin;
			break;

		case GUILD_PACKET_CX_ASKINFO:
		case GUILD_PACKET_XG_ASKINFO:
			pGuildPacket = (SGuildPacket *) &m_PacketAskInfo;
			break;

		case GUILD_PACKET_CX_APPOINT:
		case GUILD_PACKET_XG_APPOINT:
			pGuildPacket = (SGuildPacket *) &m_PacketAppoint;
			break;

		case GUILD_PACKET_CX_ADJUSTAUTHORITY:
		case GUILD_PACKET_XG_ADJUSTAUTHORITY:
			pGuildPacket = (SGuildPacket *) &m_PacketJustAuthority;
			break;

		case GUILD_PACKET_CX_RECRUIT:
		case GUILD_PACKET_XG_RECRUIT:
			pGuildPacket = (SGuildPacket *) &m_PacketRecruit;
			break;

		case GUILD_PACKET_CX_EXPEL:
		case GUILD_PACKET_XG_EXPEL:
			pGuildPacket = (SGuildPacket *) &m_PacketExpel;
			break;

		case GUILD_PACKET_CX_WITHDRAW:
		case GUILD_PACKET_XG_WITHDRAW:
			pGuildPacket = (SGuildPacket *) &m_PacketWithdraw;
			break;

		case GUILD_PACKET_CX_DEPOSIT:
		case GUILD_PACKET_XG_DEPOSIT:
			pGuildPacket = (SGuildPacket *) &m_PacketDeposit;
			break;

		case GUILD_PACKET_CX_LEAVE:
		case GUILD_PACKET_XG_LEAVE:
			pGuildPacket = (SGuildPacket *) &m_PacketLeave;
			break;

		case GUILD_PACKET_CX_DISMISS:
		case GUILD_PACKET_XG_DISMISS:
			pGuildPacket = (SGuildPacket *) &m_PacketLeave;
			break;

		case GUILD_PACKET_CX_DEMISE:
		case GUILD_PACKET_XG_DEMISE:
			pGuildPacket = (SGuildPacket *) &m_PacketDemise;
			break;

		case GUILD_PACKET_CX_CHANGEDESC:
		case GUILD_PACKET_XG_CHANGEDESC:
			pGuildPacket = (SGuildPacket *) &m_PacketChangeDesc;
			break;

		case GUILD_PACKET_CX_INVITE:
		case GUILD_PACKET_XG_INVITE:
			pGuildPacket = (SGuildPacket *) &m_PacketInvite;
			break;

		case GUILD_PACKET_CX_INVITE_CONFIRM:
		case GUILD_PACKET_XG_INVITE_CONFIRM:
			pGuildPacket = (SGuildPacket *) &m_PacketInviteConfirm;
			break;

		case GUILD_PACKET_CX_CREATE_FAMILY:
		case GUILD_PACKET_XG_CREATE_FAMILY:
			pGuildPacket = (SGuildPacket *) &m_PacketCreateFamily;
			break;

		case GUILD_PACKET_CX_ADD_FAMILY_USER:
		case GUILD_PACKET_XG_ADD_FAMILY_USER:
			pGuildPacket = (SGuildPacket *) &m_PacketAddFamilyUser;
			break;

		case GUILD_PACKET_CX_REMOVE_FAMILY_USER:
		case GUILD_PACKET_XG_REMOVE_FAMILY_USER:
			pGuildPacket = (SGuildPacket *) &m_PacketRemoveFamilyUser;
			break;

		case GUILD_PACKET_XG_MODIFY_DESC:
		case GUILD_PACKET_CX_MODIFY_DESC:
			pGuildPacket = (SGuildPacket *) &m_PacketModifyDesc;
			break;

		case GUILD_PACKET_XG_MODIFY_TITLE_NAME:
			pGuildPacket = (SGuildPacket *) &m_PacketModifyTitleName;
			break;

		case GUILD_PACKET_XG_FAMILY_DISMISS:
		case GUILD_PACKET_CX_FAMILY_DISMISS:
			pGuildPacket = (SGuildPacket *) &m_PacketFamilyDismiss;
			break;

		case GUILD_PACKET_CX_LEVELUP:
		case GUILD_PACKET_XG_LEVELUP:
			pGuildPacket = (SGuildPacket *) &m_PacketLevelUp;
			break;

		case GUILD_PACKET_XG_LEVELDOWN:
			pGuildPacket = (SGuildPacket *) &m_PacketLevelDown;
			break;

		case GUILD_PACKET_XG_SET_SHIMING:
			pGuildPacket = (SGuildPacket *) &m_PacketShiMing;
			break;

		case GUILD_PACKET_XG_ADD_GEXP:
		case GUILD_PACKET_XG_SUB_GEXP:
			pGuildPacket = (SGuildPacket *) &m_PacketGEXP;
			break;

		case GUILD_PACKET_XG_LEVEL_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketLevelInfo;
			break;

		case GUILD_PACKET_CX_MOVE_MEMBER:
		case GUILD_PACKET_XG_MOVE_MEMBER:
			pGuildPacket = (SGuildPacket *) &m_PacketMoveMember;
			break;

		case GUILD_PACKET_CX_APPOINT_POS:
		case GUILD_PACKET_XG_APPOINT_POS:
			pGuildPacket = (SGuildPacket *) &m_PacketAppointPos;
			break;

		case GUILD_PACKET_CX_CANCEL_POS:
		case GUILD_PACKET_XG_CANCEL_POS:
			pGuildPacket = (SGuildPacket *) &m_PacketCancelPos;
			break;

		case GUILD_PACKET_CX_ABDICATE:
		case GUILD_PACKET_XG_ABDICATE:
			pGuildPacket = (SGuildPacket *) &m_PacketAbdicate;
			break;

		case GUILD_PACKET_CX_SET_GP:
		case GUILD_PACKET_XG_SET_GP:
			pGuildPacket = (SGuildPacket *) &m_PacketGP;
			break;

		case GUILD_PACKET_CX_MODIFYFAMILYNAME:
		case GUILD_PACKET_XG_MODIFYFAMILYNAME:
			pGuildPacket = (SGuildPacket *) &m_PacketModifyFamilyName;
			break;

		case GUILD_PACKET_XG_SCRIPT_CALLBACK:
			pGuildPacket = (SGuildPacket *) &m_PacketScriptCallback;
			break;

		case GUILD_PACKET_XG_SETFREEPARAM:
			pGuildPacket = (SGuildPacket *) &m_PacketSetFreeParam;
			break;

		case GUILD_PACKET_CX_GUILDSTRENGTH:
		case GUILD_PACKET_XG_GUILDSTRENGTH:
			pGuildPacket = (SGuildPacket *) &m_PacketGuildStrength;
			break;

		case GUILD_PACKET_CX_CONVOKE_CONFIRM:
		case GUILD_PACKET_XG_CONVOKE_CONFIRM:
			pGuildPacket = (SGuildPacket *) &m_PacketConvokeConfirm;
			break;

		case GUILD_PACKET_XG_CONVOKE:
			pGuildPacket = (SGuildPacket *) &m_PacketConvoke;
			break;

		case GUILD_PACKET_XG_MEMBER_JOINTIME:
			pGuildPacket = (SGuildPacket *) &m_PacketMemberJoinTime;
			break;

		case GUILD_PACKET_CX_DELATE_VOTE:
		case GUILD_PACKET_XG_DELATE_VOTE:
			pGuildPacket = (SGuildPacket *) &m_PacketDelateVote;
			break;

		case GUILD_PACKET_XG_ADD_MERIT:
			pGuildPacket = (SGuildPacket *) &m_PacketAddMerit;
			break;
		case GUILD_PACKET_XG_ADD_MEMBER_VALUE:
			pGuildPacket = (SGuildPacket *) &m_PacketAddMemberValue;
			break;

		case GUILD_PACKET_XG_ADD_MONEY:
			pGuildPacket = (SGuildPacket *) &m_PacketAddMoney;
			break;

		case GUILD_PACKET_XG_SET_MULTIMISSION:
			pGuildPacket = (SGuildPacket *) &m_PacketSetMultiMission;
			break;

		case GUILD_PACKET_CX_ASKLAIRDDATA:
			pGuildPacket = (SGuildPacket *) &m_PacketAskLairdData;
			break;

        case GUILD_PACKET_XG_CHANGEPROFESSION:
            pGuildPacket = (SGuildPacket *) &m_PacketJoin;
            break;

		case GUILD_PACKET_CX_MODIFY_ACTIVITY_PARAM:
		case GUILD_PACKET_XG_MODIFY_ACTIVITY_PARAM:
			pGuildPacket = (SGuildPacket *) &m_PacketModifyActivityParam;
			break;

		case GUILD_PACKET_CX_UPDATESKILLLEVEL:
		case GUILD_PACKET_XG_UPDATESKILLLEVEL:
		case GUILD_PACKET_CX_BUS_SKILLUP:
		case GUILD_PACKET_XG_BUS_UPDATESKILL:
			pGuildPacket = (SGuildPacket *) &m_PacketGuildSkillLevelUp;
			break;
		
		
		default:
			KCheck(FALSE);
			pGuildPacket = NULL;
		}

		return pGuildPacket;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	static uint32 GetPacketMaxSize()
	{
		return(sizeof(uchar) + sizeof(u) - sizeof(SGuildPacket));
	}
};

struct _GUILD_GXC_PACKET :
	public SGuildExtPacket
{
	GUILD_GXC_LIST			m_PacketList;
	GUILD_GXC_MEMBER_LIST		m_PacketMemberList;
	GUILD_GXC_GUILD_INFO		m_PacketGuildInfo;
	GUILD_GXC_APPOINT_INFO		m_PacketAppointList;
	GUILD_GXC_SELF_GUILD_INFO	m_PacketSelfGuildInfo;
	GUILD_GXC_INVITE		m_PacketInvite;
	GUILD_GXC_MODIFY_TITLE_NAME	m_PacketTitleName;
	GUILD_GXC_SCRIPT_CALLBACK	m_PacketScriptCallback;
	GUILD_GXC_SET_MEMBER_GP		m_PacketSetMemberGP;
	GUILD_GXC_REFRESH_MEMBER_INFO		m_PacketRefreshMemberInfo;
	GUILD_GXC_REFRESH_ALL_MEMBER_INFO	m_PacketRefreshAllMemberInfo;
	GUILD_CXG_GUILD_STRENGTH	m_PacketGuildStrength;
	GUILD_GXC_CONVOKE		m_PacketConvoke;
	GUILD_GXC_CONVOKE_SUCCESS	m_PacketConvokeSuccess;
	GUILD_GXC_MEMBER_JOINTIME	m_PacketMemberJoinTime;
	GUILD_GXC_DELATE_BROADCAST	m_PacketDelateBroadcast;
	GUILD_GXC_SET_MEMBER_MERIT	m_PacketSetMemberMerit;
	GUILD_GXC_SET_MULTIMISSION	m_PacketSetMultiMission;
	GUILD_GXC_SYNC_LAIRDINFO	m_PacketSyncLairdInfo;
	GUILD_GXC_REFRESH_SKILL_INFO	m_PacketRefreshSkillInfo;
	GUILD_GXC_REFRESH_ALL_SKILL_INFO	m_PacketRefreshAllSkillInfo;

	union u
	{
		char	u_ListSize[sizeof(GUILD_GXC_LIST)];
		char	u_MemberListSize[sizeof(GUILD_GXC_MEMBER_LIST)];
		char	u_GuildInfoSize[sizeof(GUILD_GXC_GUILD_INFO)];
		char	u_AppointInfoSize[sizeof(GUILD_GXC_APPOINT_INFO)];
		char	u_SelfGuildInfoSize[sizeof(GUILD_GXC_SELF_GUILD_INFO)];
		char	u_InviteSize[sizeof(GUILD_GXC_INVITE)];
		char	u_TitleNameSize[sizeof(GUILD_GXC_MODIFY_TITLE_NAME)];
		char	u_ScriptCallback[sizeof(GUILD_GXC_SCRIPT_CALLBACK)];
		char	u_SetMemberGP[sizeof(GUILD_GXC_SET_MEMBER_GP)];
		char	u_RefreshMemberInfo[sizeof(GUILD_GXC_REFRESH_MEMBER_INFO)];
		char	u_RefreshAllMemberInfo[sizeof(GUILD_GXC_REFRESH_ALL_MEMBER_INFO)];
		char	u_GuildStrength[sizeof(GUILD_CXG_GUILD_STRENGTH)];
		char	u_Convoke[sizeof(GUILD_GXC_CONVOKE)];
		char	u_ConvokeSuccess[sizeof(GUILD_GXC_CONVOKE_SUCCESS)];
		char	u_MemberJoinTime[sizeof(GUILD_GXC_MEMBER_JOINTIME)];
		char	u_DelateBroadcast[sizeof(GUILD_GXC_DELATE_BROADCAST)];
		char	u_SetMemberMerit[sizeof(GUILD_GXC_SET_MEMBER_MERIT)];
		char	u_SetMultiMission[sizeof(GUILD_GXC_SET_MULTIMISSION)];
		char	u_SyncLairdInfo[sizeof(GUILD_GXC_SYNC_LAIRDINFO)];
		char	u_RefreshSkillInfo[sizeof(GUILD_GXC_REFRESH_SKILL_INFO)];
		char	u_RefreshAllSkillInfo[sizeof(GUILD_GXC_REFRESH_ALL_SKILL_INFO)];
	};

	_GUILD_GXC_PACKET()
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual SGuildPacket *GetPacket(int32 nPacketType) const
	{
		SGuildPacket	*pGuildPacket;

		switch(nPacketType)
		{
		case GUILD_PACKET_GX_LIST:
		case GUILD_PACKET_XC_LIST:
			pGuildPacket = (SGuildPacket *) &m_PacketList;
			break;

		case GUILD_PACKET_GX_MEMBER_LIST:
		case GUILD_PACKET_XC_MEMBER_LIST:
			pGuildPacket = (SGuildPacket *) &m_PacketMemberList;
			break;

		case GUILD_PACKET_GX_GUILD_INFO:
		case GUILD_PACKET_XC_GUILD_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketGuildInfo;
			break;

		case GUILD_PACKET_GX_APPOINT_INFO:
		case GUILD_PACKET_XC_APPOINT_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketAppointList;
			break;

		case GUILD_PACKET_GX_SELF_GUILD_INFO:
		case GUILD_PACKET_XC_SELF_GUILD_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketSelfGuildInfo;
			break;

		case GUILD_PACKET_GX_CONFIRM_GUILD_INVITE:
		case GUILD_PACKET_XC_CONFIRM_GUILD_INVITE:
			pGuildPacket = (SGuildPacket *) &m_PacketInvite;
			break;

		case GUILD_PACKET_GX_MODIFY_TITLE_NAME:
		case GUILD_PACKET_XC_MODIFY_TITLE_NAME:
			pGuildPacket = (SGuildPacket *) &m_PacketTitleName;
			break;

		case GUILD_PACKET_GX_SCRIPT_CALLBACK:
			pGuildPacket = (SGuildPacket *) &m_PacketScriptCallback;
			break;

		case GUILD_PACKET_GX_SET_MEMBER_GP:
			pGuildPacket = (SGuildPacket *) &m_PacketSetMemberGP;
			break;

		case GUILD_PACKET_GX_REFRESH_MEMBER_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketRefreshMemberInfo;
			break;
		case GUILD_PACKET_GX_REFRESH_ALL_MEMBER_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketRefreshAllMemberInfo;
			break;

		case GUILD_PACKET_GX_GUILDSTRENGTH:
		case GUILD_PACKET_XC_GUILDSTRENGTH:
			pGuildPacket = (SGuildPacket *) &m_PacketGuildStrength;
			break;

		case GUILD_PACKET_GX_CONVOKE:
		case GUILD_PACKET_XC_CONVOKE:
			pGuildPacket = (SGuildPacket *) &m_PacketConvoke;
			break;

		case GUILD_PACKET_GX_CONVOKE_SUCCESS:
			pGuildPacket = (SGuildPacket *) &m_PacketConvokeSuccess;
			break;

		case GUILD_PACKET_GX_MEMBER_JOINTIME:
			pGuildPacket = (SGuildPacket *) &m_PacketMemberJoinTime;
			break;

		case GUILD_PACKET_GX_DELATE_BROADCAST:
		case GUILD_PACKET_XC_DELATE_BROADCAST:
			pGuildPacket = (SGuildPacket *) &m_PacketDelateBroadcast;
			break;

		case GUILD_PACKET_GX_SET_MEMBER_MERIT:
			pGuildPacket = (SGuildPacket *) &m_PacketSetMemberMerit;
			break;

		case GUILD_PACKET_GX_SET_MULTIMISSION:
		case GUILD_PACKET_XC_SET_MULTIMISSION:
			pGuildPacket = (SGuildPacket *) &m_PacketSetMultiMission;
			break;

		case GUILD_PACKET_GX_SYNC_LAIRDINFO:
		case GUILD_PACKET_XC_SYNC_LAIRDINFO:
			pGuildPacket = (SGuildPacket *) &m_PacketSyncLairdInfo;
			break;

		case GUILD_PACKET_GX_SKILL_ALL:
		case GUILD_PACKET_GX_SYNC_SKILL_INFO:
		case GUILD_PACKET_XC_SYNC_SKILL_INFO:
			pGuildPacket = (SGuildPacket *) &m_PacketRefreshAllSkillInfo;
			break;

		case GUILD_PACKET_GX_SKILL:
			pGuildPacket = (SGuildPacket *) &m_PacketRefreshSkillInfo;
			break;

		default:
			KCheck(FALSE);
			pGuildPacket = NULL;
		}

		return pGuildPacket;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	static uint32 GetPacketMaxSize()
	{
		return(sizeof(uchar) + sizeof(u) - sizeof(SGuildPacket));
	}
};

struct SGuildReturn
{
	char		m_ReturnType;
	GuildID_t	m_GuildID;
	GUID_t		m_GUID;
	GUID_t		m_GUIDChanged;
	uchar		m_PosID;
	uchar		m_SourNameSize;
	char		m_SourName[MAX_CHARACTER_NAME];
	uchar		m_DestNameSize;
	char		m_DestName[MAX_CHARACTER_NAME];
	uchar		m_GuildNameSize;
	char		m_GuildName[MAX_GUILD_NAME_SIZE];
	uchar		m_PositionNameSize;
	char		m_PositionName[MAX_GUILD_POS_NAME_SIZE];
	uchar		m_ChangedPositionNameSize;
	char		m_ChangedPositionName[MAX_GUILD_POS_NAME_SIZE];
	char		m_cFamilyID;
	uchar		m_FamilyNameSize;
	char		m_FamilyName[MAX_GUILD_FAMILY_NAME_SIZE];
	uchar		m_FamilyDescSize;
	char		m_FamilyDesc[MAX_GUILD_FAMILY_DESC_SIZE];
	uchar		m_GuildLevel;
	BOOL		m_bScuess;
	uint32		m_SkillID;

	SGuildReturn()
	{
		m_ReturnType = GUILD_RETURN_INVALID;
		m_GuildID = INVALID_ID;
		m_GUID = INVALID_ID;
		m_GUIDChanged = INVALID_ID;
		m_PosID = 0;
		m_SourNameSize = 0;
		m_cFamilyID = INVALID_ID;
		m_FamilyNameSize = 0;
		m_FamilyDescSize = 0;
		m_GuildLevel = 0;
		m_bScuess = FALSE;
		m_SkillID = INVALID_ID;

		memset((void *) m_SourName, 0, sizeof(m_SourName));
		m_DestNameSize = 0;
		memset((void *) m_DestName, 0, sizeof(m_DestName));
		m_GuildNameSize = 0;
		memset((void *) m_GuildName, 0, sizeof(m_GuildName));
		m_PositionNameSize = 0;
		memset((void *) m_PositionName, 0, sizeof(m_PositionName));
		m_ChangedPositionNameSize = 0;
		memset((void *) m_ChangedPositionName, 0, sizeof(m_ChangedPositionName));
		memset((void *) m_FamilyName, 0, sizeof(m_FamilyName));
		memset((void *) m_FamilyDesc, 0, sizeof(m_FamilyDesc));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		uint32	uSize = sizeof(m_ReturnType);

		switch(m_ReturnType)
		{
		case GUILD_RETURN_POSITION_CHANGED:
			{
				uSize += sizeof(m_GUID) + sizeof(m_PosID);
			}
			break;

		case GUILD_RETURN_INVIT:
			{
				uSize += sizeof(m_GuildID) + sizeof(m_GUID) + sizeof(m_GuildNameSize) + m_GuildNameSize;
			}
			break;

		case GUILD_RETURN_CREATE:
			{
				uSize += sizeof(m_GuildID) + sizeof(m_GuildNameSize) + m_GuildNameSize;
			}
			break;

		case GUILD_RETURN_JOIN:
			{
				uSize += sizeof(m_GuildID) + sizeof(m_GuildNameSize) + m_GuildNameSize + sizeof(m_SourNameSize) + m_SourNameSize + sizeof(m_GUID);
			}
			break;

		case GUILD_RETURN_RESPONSE:
			{
				uSize += sizeof(m_GuildID) + sizeof(m_GUID) + sizeof(m_SourNameSize) + m_SourNameSize;
			}
			break;

		case GUILD_RETURN_EXPEL:
			{
				uSize += sizeof(m_SourNameSize) +
					m_SourNameSize +
					sizeof(m_DestNameSize) +
					m_DestNameSize +
					sizeof(m_GUID);
			}
			break;

		case GUILD_RETURN_REJECT:
			{
				uSize += sizeof(m_GuildNameSize) +
					m_GuildNameSize +
					sizeof(m_DestNameSize) +
					m_DestNameSize +
					sizeof(m_GUID);
			}
			break;

		case GUILD_RETURN_RECRUIT:
			{
				uSize += sizeof(m_GuildID) +
					sizeof(m_GUIDChanged) +
					sizeof(m_SourNameSize) +
					m_SourNameSize +
					sizeof(m_DestNameSize) +
					m_DestNameSize +
					sizeof(m_GuildNameSize) +
					m_GuildNameSize +
					sizeof(m_PositionNameSize) +
					m_PositionNameSize +
					sizeof(m_GUID);
			}
			break;

		case GUILD_RETURN_LEAVE:
			{
				uSize += sizeof(m_GUID) + sizeof(m_GuildNameSize) + m_GuildNameSize + sizeof(m_DestNameSize) + m_DestNameSize;
			}
			break;

		case GUILD_RETURN_FOUND:
			{
			}
			break;

		case GUILD_RETURN_DISMISS:
			{
			}
			break;

		case GUILD_RETURN_ALREADY_IN:
			{
			}
			break;

		case GUILD_RETURN_ERASE_ITEM_FAIL:
			{
			}
			break;

		case GUILD_RETURN_PROMOTE:
			{
				uSize += sizeof(m_SourNameSize) +
					m_SourNameSize +
					sizeof(m_DestNameSize) +
					m_DestNameSize +
					sizeof(m_PositionNameSize) +
					m_PositionNameSize +
					sizeof(m_GuildNameSize) +
					m_GuildNameSize +
					sizeof(m_PosID) +
					sizeof(m_GUID) +
					sizeof(m_GuildID);
			}
			break;

		case GUILD_RETURN_DEMOTE:
			{
				uSize += sizeof(m_SourNameSize) +
					m_SourNameSize +
					sizeof(m_DestNameSize) +
					m_DestNameSize +
					sizeof(m_PositionNameSize) +
					m_PositionNameSize +
					sizeof(m_GuildNameSize) +
					m_GuildNameSize +
					sizeof(m_PosID) +
					sizeof(m_GUID) +
					sizeof(m_GuildID);
			}
			break;

		case GUILD_RETURN_AUTHORIZE:
		case GUILD_RETURN_DEPRIVE_AUTHORITY:
			{
			}
			break;

		case GUILD_RETURN_DEMISE:
			{
				uSize += sizeof(m_GuildID) + sizeof(m_GUID) + sizeof(m_GUIDChanged) + sizeof
					(m_SourNameSize) + m_SourNameSize + sizeof(m_DestNameSize) + m_DestNameSize + sizeof
					(m_GuildNameSize) + m_GuildNameSize + sizeof(m_PositionNameSize) + m_PositionNameSize + sizeof
					(m_ChangedPositionNameSize) + m_ChangedPositionNameSize;
			}
			break;

		case GUILD_RETURN_NAME:
			{
			}
			break;

		case GUILD_RETURN_WITHDRAW:
		case GUILD_RETURN_DEPOSIT:
		case GUILD_RETURN_CREATE_FAILED:
			{
			}
			break;

		case GUILD_RETURN_CREATE_FAMILY:
			{
				uSize += sizeof(m_cFamilyID) + m_FamilyNameSize + m_FamilyDescSize + sizeof(m_FamilyNameSize) + sizeof(m_FamilyDescSize);
			}
			break;

		case GUILD_RETURN_FAMILY_DISMISS:
			{
				uSize += sizeof(m_cFamilyID);
			}
			break;

		case GUILD_RETURN_ADD_FAMILY_USER:
			{
				uSize += sizeof(m_cFamilyID) + m_SourNameSize + sizeof(m_SourNameSize);
			}
			break;

		case GUILD_RETURN_LEVEL_UP:
			{
				uSize += sizeof(m_GuildLevel) + sizeof(m_bScuess);
			}
			break;

		case GUILD_RETURN_SKILL_LEVEL_UP:
		case GUILD_RETURN_BUS_SKILL_LEVEL_UP:
			{
				uSize += sizeof(m_GuildID) + sizeof(m_bScuess) + sizeof(m_SkillID);
			}
			break;


		case GUILD_RETURN_BEADD_FAMILY:
			{
				uSize += sizeof(m_cFamilyID);
			}
			break;

		case GUILD_RETURN_REMOVE_FAMILY_USER:
			{
				uSize += sizeof(m_cFamilyID) + m_SourNameSize + sizeof(m_SourNameSize);
			}
			break;

		case GUILD_RETURN_MODIFY_DESC:
			{
				uSize += m_FamilyDescSize + sizeof(m_FamilyDescSize);
			}
			break;

		default:
			KCheck(FALSE);
			return 0;
		}

		return uSize;
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct SGuildPos
{
	uchar	NumPos;
	uchar	MaxNumPos;
	char	szPosName[MAX_GUILD_POS_NAME_SIZE];
	int32	Posidx[MAX_NUM_PER_POSITION];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		NumPos = 0;
		MaxNumPos = 0;
		memset(szPosName, 0, MAX_GUILD_POS_NAME_SIZE);
		for(int32 i = 0; i < MAX_NUM_PER_POSITION; i++)
		{
			Posidx[i] = -1;
		}
	}
};

struct SGuildAdmin
{
	enum ORESULT { RET_SUCCESS = 0, RET_NOT_EXIST, RET_POS_FULL, RET_NO_USER, RET_UNKOWN, };
	enum
	{
		POS_LEVEL0_BEGIN		= 0,
		POS_CHAIR_MAN,
		POS_ASS_CHAIR_MAN,
		POS_NORMAL_FAMILY_BOSS,
		POS_ELITE_MEMBER,
		POS_MEMBER,
		POS_LEVEL_END,
	};

	SGuildPos m_PosList[POS_LEVEL_END];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	SGuildPos *Get(int32 iPos)
	{
		return &m_PosList[iPos];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ORESULT Remove(int32 iPos, int32 iIndex)
	{
		SGuildPos	*pGuildPos = Get(iPos);

		for(int32 i = 0; i < pGuildPos->MaxNumPos; i++)
		{
			if(pGuildPos->Posidx[i] == iIndex)
			{
				pGuildPos->Posidx[i] = pGuildPos->Posidx[pGuildPos->NumPos - 1];
				pGuildPos->Posidx[pGuildPos->NumPos - 1] = -1;
				pGuildPos->NumPos--;
				return RET_SUCCESS;
			}
		}

		return RET_NOT_EXIST;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ORESULT Add(int32 iPos, int32 iIndex)
	{
		SGuildPos	*pGuildPos = Get(iPos);
		if(pGuildPos->NumPos == pGuildPos->MaxNumPos) return RET_POS_FULL;
		pGuildPos->Posidx[pGuildPos->NumPos] = iIndex;
		pGuildPos->NumPos++;
		return RET_SUCCESS;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(int32 iLevelBegin = POS_LEVEL0_BEGIN)
	{
		for(int32 i = iLevelBegin; i < POS_LEVEL_END; i++)
		{
			m_PosList[i].Clear();
		}
	}
};

#endif
