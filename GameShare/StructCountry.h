/*$T Common/StructCountry.h GC 1.140 10/10/07 10:06:55 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __GAMESTRUCT_COUNTRY_H__
#define __GAMESTRUCT_COUNTRY_H__

#include "TypeDefine.h"
#include "DefineCountry.h"

#define DEFAULT_AP		1000
#define MAX_VOTE_USER		1000
#define MAX_GUILD_MASTER_VOTE	100

struct PK_INFO
{
	int32	m_nID;
	int32	m_nMin;
	int32	m_nMax;
	int32	m_nValue;

	PK_INFO()
	{
		m_nID = 0;
		m_nMin = 0;
		m_nMax = 0;
		m_nValue = 0;
	}
};

struct VOTE_INFO
{
	BOOL	m_bResult;
	GUID_t	m_Guid;

	VOTE_INFO()
	{
		m_bResult = FALSE;
		m_Guid = INVALID_GUID;
	}
};

enum CAMP_ENUM
{
	CAMP_A		= 0,
	CAMP_B,
	CAMP_C,
	CAMP_D,
	CAMP_4,
	CAMP_5,
	CAMP_6,
	CAMP_7,
	CAMP_8,
	CAMP_9,
	CAMP_10,
	CAMP_11,
	CAMP_12,
	CAMP_13,
	CAMP_14,
	CAMP_15,
	CAMP_PLAYER_END,
	CAMP_17		= 17,
	CAMP_18,
	CAMP_19,
	CAMP_20,
	CAMP_21,
	CAMP_22,
	CAMP_23,
	CAMP_24,
	CAMP_25,
	CAMP_26,
	CAMP_27,
	CAMP_28,
	CAMP_29,
	CAMP_30,
	CAMP_31,
	CAMP_32,
	CAMP_NPC_END,
	CAMP_UNKNOWN,
};

enum PK_MODE { PK_MODE_PUTONG, PK_MODE_PK, PK_MODE_HUNZHAN, };

struct _COUNTRY_OFFICER
{
	_COUNTRY_OFFICER()
	{
		m_UserGUID = INVALID_GUID;
		memset(m_szUserName, 0, MAX_CHARACTER_NAME);
	}
	GUID_t	m_UserGUID;
	char	m_szUserName[MAX_CHARACTER_NAME];
};

struct _IntervalControl
{
	struct dbstruct
	{
		int32	tm_last;
		int32	tm_checkpoint;
		int32	count;
		dbstruct();
		dbstruct &operator	=(dbstruct &rhs);
	};

	dbstruct	m_dbdata;
	int32		m_nInterval;
	int32		m_nMaxCount;
public:
	_IntervalControl();
	void	InitFromDB(dbstruct &db);
	void	Init(int32 interval, int32 maxcnt);
	int32	GetLastTime();
	int32	GetCheckPoint();
	BOOL	Request(int32 tmNow, int32 dateNow);
	BOOL	TestRequest(int32 tmNow, int32 dateNow);
	BOOL	IsDuration(int32 tmNow, int32 nDuration);
};

enum COUNTRY_RESOURCE_ENUM
{
	COUNTRY_RESOURCE_WOOD	= 0,
	COUNTRY_RESOURCE_MEAT	= 1,
	COUNTRY_RESOURCE_GOLD	= 2,
	COUNTRY_RESOURCE_STONE	= 3,
	COUNTRY_RESOURCE_COUNT,
};

enum COUNTRY_FORTUNE_ENUM
{
	COUNTRY_FORTUNE_YULONG	= 0,
	COUNTRY_FORTUNE_HUWEI	= 1,
	COUNTRY_FORTUNE_TIANGE1 = 2,
	COUNTRY_FORTUNE_TIANGE2 = 3,
	COUNTRY_FORTUNE_TIANGE3 = 4,
	COUNTRY_FORTUNE_TIANXING= 5,
	COUNTRY_FORTUNE_COUNT,
};

enum COUNTRY_RANK { COUNTRY_RANK_STRONG = 0, COUNTRY_RANK_NORMAL1, COUNTRY_RANK_NORMAL2, COUNTRY_RANK_WEAK, };

#define MAXCOUNT_COUNTRY_RESOURCE	999999999

struct _COUNTRY
{
public:
	uchar			m_cCountryID;
	GUID_t			m_aUser[MAX_WORLD_PLAYER];
	int32			m_nCurUser;
	int32			m_nAP;

	GUID_t			m_King;
	GUID_t			m_Challenger;
	char			m_szKing[MAX_CHARACTER_NAME];
	char			m_szChallenger[MAX_CHARACTER_NAME];
	GuildID_t		m_KingGuildID;
	GuildID_t		m_ChallengerGuildID;
	
	//add by wangzhiping for 青龙，朱雀国家帮
	GUID_t			m_arrCountryBangzhu[COUNTRY_GUILD_COUNT]; //国家帮会帮主guid
	char			m_arrCountryBangzhuName[COUNTRY_GUILD_COUNT][MAX_CHARACTER_NAME]; //国家帮会帮主名称
	GuildID_t		m_arrCountryGuild[COUNTRY_GUILD_COUNT]; //国家帮会list

	GUID_t			m_arrCountryBangzhu_Challenger[COUNTRY_GUILD_COUNT]; //国家帮会挑战帮主guid
	char			m_arrCountryBangzhuName_Challenger[COUNTRY_GUILD_COUNT][MAX_CHARACTER_NAME]; //国家帮会挑战帮主名称
	GuildID_t		m_arrCountryGuild_Challenger[COUNTRY_GUILD_COUNT]; //国家挑战帮会list
	//add end

	char			m_szNotice[MAX_NOTICE_SIZE];
	int32			m_aFreeParam[MAX_FREEPARAM_NUM];

	int32			m_nResource[COUNTRY_RESOURCE_COUNT];

	char			m_kingly_QiCheng_stat;
	char			m_kingly_Suit_stat;

	_COUNTRY_OFFICER	m_officer_Queen;
	_COUNTRY_OFFICER	m_officer_LMinister;
	_COUNTRY_OFFICER	m_officer_RMinister;
	_COUNTRY_OFFICER	m_officer_General;
	_COUNTRY_OFFICER	m_officer_LGuard;
	_COUNTRY_OFFICER	m_officer_RGuard;

	_IntervalControl	m_ctl_Fortune[COUNTRY_FORTUNE_COUNT];

	_IntervalControl	m_ctl_Assign_General;
	_IntervalControl	m_ctl_Assign_LMinister;
	_IntervalControl	m_ctl_Assign_RMinister;
	_IntervalControl	m_ctl_Assign_LGuard;
	_IntervalControl	m_ctl_Assign_RGuard;
	_IntervalControl	m_ctl_Cancel_General;
	_IntervalControl	m_ctl_Cancel_LMinister;
	_IntervalControl	m_ctl_Cancel_RMinister;
	_IntervalControl	m_ctl_Cancel_LGuard;
	_IntervalControl	m_ctl_Cancel_RGuard;

	_IntervalControl	m_ctl_ModifyNotice;
	_IntervalControl	m_ctl_Collect;
	_IntervalControl	m_ctl_ForbidChat;
	_IntervalControl	m_ctl_Enjail;
	_IntervalControl	m_ctl_Assoil;

	_IntervalControl	m_ctl_bonus_king;
	_IntervalControl	m_ctl_bonus_queen;
	_IntervalControl	m_ctl_bonus_general;
	_IntervalControl	m_ctl_bonus_lminister;
	_IntervalControl	m_ctl_bonus_rminister;
	_IntervalControl	m_ctl_bonus_lguard;
	_IntervalControl	m_ctl_bonus_rguard;
public:
	_COUNTRY();

	void	Save2DB(struct Country_DB &db);

	void	InitFromDB(struct Country_DB &db);

	int32	AddResource(int32 nIndex, int32 nDelta);
	int32	SubResource(int32 nIndex, int32 nDelta);
	int32	GetResource(int32 nIndex);

	void	AddUser(GUID_t guid);

	void	RemoveUser(GUID_t guid);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	int32 GetCurUserNum()
	{
		return m_nCurUser;
	}
};

struct COUNTRY_CXG_KINDOM_REQUEST
{
	GUID_t		m_Guid;

	virtual void	Reci(RecieveStream &iStream);
	virtual void	Send(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		return sizeof(GUID_t);
	}
};

struct COUNTRY_CXG_COUNTRY_APPOINT
{
	GUID_t	m_KindomGuid;
	char	m_cNameSize;
	char	m_szTargetName[MAX_CHARACTER_NAME];
	int32	m_nOfficialPosition;

	COUNTRY_CXG_COUNTRY_APPOINT()
	{
		memset(m_szTargetName, 0, MAX_CHARACTER_NAME);
	}
	virtual void	Reci(RecieveStream &iStream);
	virtual void	Send(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		return sizeof(GUID_t) + sizeof(int32) + sizeof(char) + m_cNameSize;
	}
};

struct COUNTRY_CXG_COUNTRY_REMOVE
{
	GUID_t	m_KindomGuid;
	int32	m_nOfficialPosition;
	char	m_cNameSize;
	char	m_szTargetName[MAX_CHARACTER_NAME];

	COUNTRY_CXG_COUNTRY_REMOVE()
	{
		memset(m_szTargetName, 0, MAX_CHARACTER_NAME);
	}
	virtual void	Reci(RecieveStream &iStream);
	virtual void	Send(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		return sizeof(GUID_t) + sizeof(char) + m_cNameSize + sizeof(int32);
	}

    static uint32 GetSize()
    {
        return sizeof(GUID_t) + sizeof(char) + MAX_CHARACTER_NAME + sizeof(int32);
    }
};

struct COUNTRY_CXG_COUNTRY_COLLECT
{
	GUID_t	m_Guid;
	int32	m_nCountryID;
	int32	m_nGold;
	uchar	m_cKindomSize;
	uchar	m_cDescSize;
	char	m_szKindom[MAX_CHARACTER_NAME];
	char	m_szDesc[MAX_COUNTRY_COLLECT_DESC];

	COUNTRY_CXG_COUNTRY_COLLECT()
	{
		m_Guid = INVALID_GUID;
		m_nCountryID = INVALID_ID;
		m_nGold = 0;
		m_cKindomSize = 0;
		m_cDescSize = 0;

		memset(m_szKindom, 0, MAX_CHARACTER_NAME);
		memset(m_szDesc, 0, MAX_COUNTRY_COLLECT_DESC);
	}
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		return sizeof(m_Guid) + sizeof(int32)*2 + sizeof(uchar)*2 + m_cKindomSize + m_cDescSize;
	}
};

struct COUNTRY_CXG_COUNTRY_INFO
{
	int32		m_CountryID;
	_COUNTRY	m_CountryInfo;

	COUNTRY_CXG_COUNTRY_INFO()
	{
		memset(&m_CountryInfo, 0, sizeof(_COUNTRY));
	}
	virtual void	Reci(RecieveStream &iStream);
	virtual void	Send(SendStream &oStream) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		return sizeof(int32) + sizeof(_COUNTRY);
	}
};

enum COUNTRY_RETURN_TYPE
{
	COUNTRY_RETURN_INVALID			= -1,
	COUNTRY_RETURN_REQUEST_KINDOM		= 0,
	COUNTRY_RETURN_APPOINT,
	COUNTRY_RETURN_REMOVE,
	COUNTRY_RETURN_DELATE,
	COUNTRY_RETURN_DELATE_SCUESS,
	COUNTRY_RETURN_REQUEST_KINDOM_FAIL,
	COUNTRY_ERROR_COUNTRY_ID		= 30,
	COUNTRY_ERROR_USER_NOT_FIND,
	COUNTRY_RETURN_SIZE,
};

struct _COUNTRY_RETURN
{
	char	m_ReturnType;
	char	m_cPosition;
	char	m_cCountry;
	char	m_szName[MAX_CHARACTER_NAME];

	_COUNTRY_RETURN()
	{
		m_ReturnType = COUNTRY_RETURN_INVALID;
		memset(m_szName, 0, MAX_CHARACTER_NAME);
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
		case COUNTRY_RETURN_REQUEST_KINDOM:
			{
			}
			break;

		case COUNTRY_RETURN_APPOINT:
			{
				uSize += sizeof(m_cPosition) + sizeof(m_cCountry) + MAX_CHARACTER_NAME;
			}
			break;

		case COUNTRY_RETURN_REMOVE:
			{
				uSize += sizeof(m_cPosition) + sizeof(m_cCountry);
			}
			break;

		case COUNTRY_ERROR_COUNTRY_ID:
			{
			}
			break;

		case COUNTRY_ERROR_USER_NOT_FIND:
			{
			}
			break;

		case COUNTRY_RETURN_DELATE_SCUESS:
			break;

		case COUNTRY_RETURN_DELATE:
			break;

		case COUNTRY_RETURN_REQUEST_KINDOM_FAIL:
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

enum CountryOpType
{
	OP_FORBIDCHAT				= 0,
	OP_ENJAIL,
	OP_MODIFYNOTICE,
	OP_COLLECT,
	OP_APPLYKING,
	OP_APPLYKING_GM,
	OP_DONATE,
	OP_ASKINFO,
	OP_RETURNINFO,
	OP_COUNTRYBASEINFO,
	OP_WITHDRAW,
	OP_CANCELKING,
	OP_APPOINT,
	OP_DISMISE,
	OP_ASSOIL,
	OP_STATEFORTUNE,
	OP_DRAWBONUS,
	OP_MODIFYRESOURCE,
	OP_FEEDBACK,
	OP_BETRAY,
	OP_RETBETRAY,
	OP_FORBIDCHAT_GM,
	OP_SETFREEPARAM,
	OP_ADDCOUNTRYSTRENGTH,
	OP_COUNTRY_ORDER,
	OP_DELATE_TO_GUILD_CHIEFTAIN,
	OP_CHIEFTAIN_VOTE,
	OP_DELATE_TO_ALL_COUNTRY_MEMBER,
	OP_MEMBER_VOTE,
	OP_KING_ZHAOJI,
	OP_COUNTRYDATA,
    OP_PRECONTRACT,                     // 国务预约
    OP_REQUSET_COUNTRY_COLLEAGE_TO_ACQUIRE, //请求国家结盟,需要对方国王确认
    OP_REQUEST_COUNTRY_COLLEAGUE,		//请求国家结盟,对方国王点击确认后的事件
    OP_DISAGREE_COUNTRY_COLLEAGUE_C2S,	//拒绝了结盟,用户点击确认
    OP_DISAGREE_COUNTRY_COLLEAGUE_S2C,	//服务端把拒绝的消息发到客户端
};

enum CountryOpType_FeedBack { FB_EnjailResult = 0, FB_AssoilResult = 1, };

struct ForbidChat
{
	GUID_t	m_UserGUID;
	char	m_szName[MAX_CHARACTER_NAME];
	char	m_szReason[MAX_REASON_SIZE];
	int32	m_nTime;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		memset((void *) m_szName, 0, sizeof(m_szName));
		memset((void *) m_szReason, 0, sizeof(m_szReason));
		m_nTime = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_szName) + sizeof(m_szReason) + sizeof(m_nTime);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Enjail
{
	GUID_t	m_UserGUID;
	char	m_szName[MAX_CHARACTER_NAME];
	char	m_szReason[MAX_REASON_SIZE];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		memset((void *) m_szName, 0, sizeof(m_szName));
		memset((void *) m_szReason, 0, sizeof(m_szReason));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_szName) + sizeof(m_szReason);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Assoil
{
	GUID_t	m_UserGUID;
	char	m_szName[MAX_CHARACTER_NAME];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		memset((void *) m_szName, 0, sizeof(m_szName));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_szName);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct StateFortune
{
	GUID_t	m_UserGUID;
	int32	m_nCountryID;
	char	m_cAuth;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nCountryID = INVALID_ID;
		m_cAuth = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nCountryID) + sizeof(m_cAuth);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct ChieftainVote
{
	GUID_t	m_nVoter;
	char	m_szWhoIVote[MAX_CHARACTER_NAME];
	GUID_t	m_nWhoIVote;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_nVoter = INVALID_GUID;
		memset(m_szWhoIVote, 0, sizeof(m_szWhoIVote));
		m_nWhoIVote = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_nVoter) + sizeof(m_szWhoIVote) + sizeof(m_nWhoIVote);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};
struct DrawBonus
{
	GUID_t	m_UserGUID;
	int32	m_nPosition;
	int32	m_nType;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nPosition = COUNTRY_POSITION_INVALID;
		m_nType = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nPosition) + sizeof(m_nType);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct ModifyNotice
{
	GUID_t	m_UserGUID;
	char	m_szNotice[MAX_NOTICE_SIZE];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		memset((void *) m_szNotice, 0, sizeof(m_szNotice));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_szNotice);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Collect
{
	ID_t	m_WorldID;
	GUID_t	m_UserGUID;
	int32	m_nCountryID;
	MapID_t m_nSceneId;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_WorldID = INVALID_ID;
		m_UserGUID = INVALID_GUID;
		m_nCountryID = INVALID_ID;
		m_nSceneId = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(ID_t) + sizeof(m_UserGUID) + sizeof(m_nCountryID) + sizeof(m_nSceneId);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct ApplyKing
{
	GUID_t	m_UserGUID;
	int16	m_nIndex;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nIndex = COUNTRY_GUILD_KING;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID)+sizeof(m_nIndex);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct CancelKing
{
	GUID_t	m_UserGUID;
	CountryID_t	m_KingCountryID;
	int16	m_nIndex;
	int16	m_nCountryOfficial;
	int16	m_nCountrySpecialOfficial;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_KingCountryID = INVALID_COUNTRY;
		m_nIndex = COUNTRY_GUILD_KING;
		m_nCountryOfficial = COUNTRY_POSITION_INVALID;
		m_nCountrySpecialOfficial =  COUNTRY_GUILD_INVAILD;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID)+sizeof(m_KingCountryID)+sizeof(m_nIndex) + sizeof(m_nCountryOfficial) + sizeof(m_nCountrySpecialOfficial);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Appoint
{
	GUID_t	m_UserGUID;
	int32	m_pos;
	char	m_szName[MAX_CHARACTER_NAME];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_pos = COUNTRY_POSITION_INVALID;
		memset((void *) m_szName, 0, MAX_CHARACTER_NAME);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_pos) + sizeof(m_szName);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Dismise
{
	GUID_t	m_UserGUID;
	int32	m_pos;
	char	m_szName[MAX_CHARACTER_NAME];
	int16	m_nMode;
	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_pos = COUNTRY_POSITION_INVALID;
		memset((void *) m_szName, 0, MAX_CHARACTER_NAME);
		m_nMode = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_pos) + sizeof(m_szName)+sizeof(m_nMode);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Donate
{
	GUID_t	m_UserGUID;
	int32	m_nDonate;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nDonate = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nDonate);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct AskCountryInfo
{
	GUID_t	m_UserGUID;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct ModifyResource
{
	GUID_t	m_UserGUID;
	int32	m_nCountryID;
	int32	m_nDelta;
	int32	m_nIndex;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nDelta = 0;
		m_nCountryID = -1;
		m_nIndex = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nDelta) + sizeof(m_nCountryID) + sizeof(m_nIndex);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct FeedBack
{
	GUID_t	m_UserGUID;
	int32	m_nType;
	int32	m_nResult;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nType = -1;
		m_nResult = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nType) + sizeof(m_nResult);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct SetFreeParam
{
	GUID_t	m_UserGUID;
	int32	m_nIndex;
	int32	m_nValue;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nValue = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nIndex) + sizeof(m_nValue);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct AddCountryStrength
{
	GUID_t	m_UserGUID;
	int32	m_nAdd;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nAdd = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nAdd);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct CountryBetray
{
	GUID_t		m_UserGUID;
	uchar		m_oldCountryId;
	uchar		m_newCountryId;
	ScriptID_t	m_scriptId;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_oldCountryId = -1;
		m_newCountryId = -1;
		m_scriptId = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_oldCountryId) + sizeof(m_newCountryId) + sizeof(m_scriptId);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct RetCountryBetray
{
	GUID_t		m_UserGUID;
	BOOL		m_nResult;
	ScriptID_t	m_scriptId;
	uchar		m_newCountryId;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_UserGUID = INVALID_GUID;
		m_nResult = 0;
		m_scriptId = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGUID) + sizeof(m_nResult) + sizeof(m_scriptId) + sizeof(m_newCountryId);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct CountryOrder
{
	ID_t	m_WorldID;
	uchar	m_nCountryId;
	uchar	m_nIndex;
	int32	m_nLeftTime;
	MapID_t m_nSceneId;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_nCountryId = 0;
		m_nIndex = -1;
		m_nLeftTime = 0;
		m_nSceneId = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(ID_t) + sizeof(m_nCountryId) + sizeof(m_nIndex) + sizeof(m_nLeftTime) + sizeof(MapID_t);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct DelateToGuildChieftain
{
	char	m_szDelateReqName[MAX_CHARACTER_NAME];
	GUID_t	m_nDelateReq;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		memset(m_szDelateReqName, 0, sizeof(m_szDelateReqName));
		m_nDelateReq = INVALID_GUID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(m_szDelateReqName) + sizeof(m_nDelateReq);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct DelateToAllCountryMember
{
	ID_t m_WorldID;
	char m_szDelateReqName[MAX_CHARACTER_NAME];
	GUID_t m_nDelateReq;
	MapID_t m_nMapId;
	CountryID_t m_nCountryId;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_WorldID = INVALID_ID;
		memset(m_szDelateReqName, 0, sizeof(m_szDelateReqName));
		m_nDelateReq = INVALID_GUID;
		m_nMapId = INVALID_ID;
		m_nCountryId = INVALID_ID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		return sizeof(ID_t) + sizeof(m_szDelateReqName) + sizeof(m_nDelateReq) + sizeof(m_nMapId) + sizeof(m_nCountryId);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

enum
{
    PRECONTRACT_GUOYUN,         // 国运
    PRECONTRACT_CHUGUO,         // 出国
    PRECONTRACT_MUJI,           // 募集
    PRECONTRACT_COUNT,

    PRECONTRACT_MAX     = 15,
};
static int32 g_saPrecontractType[] = { CD_PRECONTRACT_GUOYUN, CD_PRECONTRACT_CHUGUO, CD_PRECONTRACT_MUJI };

struct RetAllCountryData
{
	GUID_t	m_nKingGUID[MAX_COUNTRY_NUM];
	uchar	m_nKingNameSize[MAX_COUNTRY_NUM];
	char	m_szKingName[MAX_COUNTRY_NUM][MAX_CHARACTER_NAME];

	GUID_t	m_nZhuQueGUID[MAX_COUNTRY_NUM];
	uchar	m_nZhuQueNameSize[MAX_COUNTRY_NUM];
	char	m_szZhuQueName[MAX_COUNTRY_NUM][MAX_CHARACTER_NAME];

	GUID_t	m_nQingLongGUID[MAX_COUNTRY_NUM];
	uchar	m_nQingLongNameSize[MAX_COUNTRY_NUM];
	char	m_szQingLongName[MAX_COUNTRY_NUM][MAX_CHARACTER_NAME];

	uchar   m_rank[MAX_COUNTRY_NUM];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		for( int i = 0; i<MAX_COUNTRY_NUM; ++i )
		{
			m_nKingGUID[i] = INVALID_GUID;
			m_nKingNameSize[i] = 0;
			memset(m_szKingName[i],0,sizeof(m_szKingName[i]));

			m_nZhuQueGUID[i] = INVALID_GUID;
			m_nZhuQueNameSize[i] = 0;
			memset(m_szZhuQueName[i],0,sizeof(m_szZhuQueName[i]));

			m_nQingLongGUID[i] = INVALID_GUID;
			m_nQingLongNameSize[i] = 0;
			memset(m_szQingLongName[i],0,sizeof(m_szQingLongName[i]));

			m_rank[i] = COUNTRY_RANK_NORMAL1;
		}
	}

	void SetKingInfo(CountryID_t nCountry,GUID_t nGUID,const char* strName );
	void SetZhuQueInfo(CountryID_t nCountry,GUID_t nGUID,const char* strName );
	void SetQingLongInfo(CountryID_t nCountry,GUID_t nGUID,const char* strName );
	void SetCountryRankInfo(CountryID_t nCountry,uchar nRank );

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32  GetPacketSize() const;

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

/*
===============================================================================================================
===============================================================================================================
*/
struct ReturnCountryInfo
{
	GUID_t	m_KingGUID;
	GUID_t	m_QueenGUID;
	GUID_t	m_GeneralGUID;
	GUID_t	m_LMinisterGUID;
	GUID_t	m_RMinisterGUID;
	GUID_t	m_LGuardGUID;
	GUID_t	m_RGuardGUID;

	GUID_t	m_KingGuildGUID;

	uchar	m_KingNameSize;
	char	m_szKingName[MAX_CHARACTER_NAME];
	
	uchar	m_QueenNameSize;
	char	m_szQueenName[MAX_CHARACTER_NAME];
	
	uchar	m_GeneralNameSize;
	char	m_szGeneralName[MAX_CHARACTER_NAME];
	
	uchar	m_LMinisterNameSize;
	char	m_szLMinisterName[MAX_CHARACTER_NAME];
	
	uchar	m_RMinisterNameSize;
	char	m_szRMinisterName[MAX_CHARACTER_NAME];
	
	uchar	m_LGuardNameSize;
	char	m_szLGuardName[MAX_CHARACTER_NAME];
	
	uchar	m_RGuardNameSize;
	char	m_szRGuardName[MAX_CHARACTER_NAME];

	uchar	m_NoticeSize;
	char	m_szNotice[MAX_NOTICE_SIZE];

	int32	m_nFortuneTime[COUNTRY_FORTUNE_COUNT];
	int32	m_nResource[COUNTRY_RESOURCE_COUNT];

	//--青龙，朱雀start
	GUID_t			m_arrCountryBangzhu[COUNTRY_GUILD_COUNT]; //国家帮会帮主guid
	char			m_arrCountryBangzhuName[COUNTRY_GUILD_COUNT][MAX_CHARACTER_NAME]; //国家帮会帮主名称
	uchar			m_arrCountryBangzhuNameSize[COUNTRY_GUILD_COUNT];
	GuildID_t		m_arrCountryGuild[COUNTRY_GUILD_COUNT]; //国家帮会list
	//--青龙，朱雀end

    //! 国务预约信息
    int32   m_iPrecontracts[ PRECONTRACT_COUNT];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Init()
	{
		m_KingGUID = INVALID_GUID;
		m_QueenGUID = INVALID_GUID;
		m_GeneralGUID = INVALID_GUID;
		m_LMinisterGUID = INVALID_GUID;
		m_RMinisterGUID = INVALID_GUID;
		m_LGuardGUID = INVALID_GUID;
		m_RGuardGUID = INVALID_GUID;

		m_KingGuildGUID = INVALID_GUID;

		memset((void *) m_nResource, 0, sizeof(m_nResource));
		memset((void *) m_nFortuneTime, 0, sizeof(m_nFortuneTime));

		m_KingNameSize = 0;
		m_QueenNameSize = 0;
		m_GeneralNameSize = 0;
		m_LMinisterNameSize = 0;
		m_RMinisterNameSize = 0;
		m_LGuardNameSize = 0;
		m_RGuardNameSize = 0;
		m_NoticeSize = 0;

		memset((void *) m_szKingName, 0, sizeof(m_szKingName));
		memset((void *) m_szQueenName, 0, sizeof(m_szQueenName));
		memset((void *) m_szGeneralName, 0, sizeof(m_szGeneralName));
		memset((void *) m_szLMinisterName, 0, sizeof(m_szLMinisterName));
		memset((void *) m_szRMinisterName, 0, sizeof(m_szRMinisterName));
		memset((void *) m_szLGuardName, 0, sizeof(m_szLGuardName));
		memset((void *) m_szRGuardName, 0, sizeof(m_szRGuardName));
		memset((void *) m_szNotice, 0, sizeof(m_szNotice));

        memset( m_iPrecontracts, 0, sizeof(m_iPrecontracts) );
		
		//--青龙，朱雀start
		for(int16 i = 0; i < COUNTRY_GUILD_COUNT; i++)
		{
			m_arrCountryBangzhu[i] = INVALID_GUID;
			m_arrCountryBangzhuNameSize[i] = 0;
			memset(m_arrCountryBangzhuName[i], 0, MAX_CHARACTER_NAME);
			m_arrCountryGuild[i] = INVALID_GUILD_ID;

		}
		//--青龙，朱雀end
	}

	void SetCountryBangzhuName(const char* szName, int16 nIndex)
	{
		if(nIndex<=COUNTRY_GUILD_KING || nIndex>=COUNTRY_GUILD_COUNT)
		{
			return;
		}
		memset( m_arrCountryBangzhuName[nIndex], 0, MAX_CHARACTER_NAME );
		m_arrCountryBangzhuNameSize[nIndex] = (uchar)strlen(szName);
		if( m_arrCountryBangzhuNameSize[nIndex] >= MAX_CHARACTER_NAME )
			m_arrCountryBangzhuNameSize[nIndex] = MAX_CHARACTER_NAME - 1;
		memcpy(  m_arrCountryBangzhuName[nIndex], szName, m_arrCountryBangzhuNameSize[nIndex] );
	}

	void SetKingName(const char* szName)
	{
		memset( m_szKingName, 0, MAX_CHARACTER_NAME );
		m_KingNameSize = (uchar)strlen(szName);
		if( m_KingNameSize >= MAX_CHARACTER_NAME )
			m_KingNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szKingName, szName, m_KingNameSize );
	}

	void SetQueenName(const char* szName)
	{
		memset( m_szQueenName, 0, MAX_CHARACTER_NAME );
		m_QueenNameSize = (uchar)strlen(szName);
		if( m_QueenNameSize >= MAX_CHARACTER_NAME )
			m_QueenNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szQueenName, szName, m_QueenNameSize );
	}

	void SetGeneralName(const char* szName)
	{
		memset( m_szGeneralName, 0, MAX_CHARACTER_NAME );
		m_GeneralNameSize = (uchar)strlen(szName);
		if( m_GeneralNameSize >= MAX_CHARACTER_NAME )
			m_GeneralNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szGeneralName, szName, m_GeneralNameSize );
	}

	void SetLMinisterName(const char* szName)
	{
		memset( m_szLMinisterName, 0, MAX_CHARACTER_NAME );
		m_LMinisterNameSize = (uchar)strlen(szName);
		if( m_LMinisterNameSize >= MAX_CHARACTER_NAME )
			m_LMinisterNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szLMinisterName, szName, m_LMinisterNameSize );
	}

	void SetRMinisterName(const char* szName)
	{
		memset( m_szRMinisterName, 0, MAX_CHARACTER_NAME );
		m_RMinisterNameSize = (uchar)strlen(szName);
		if( m_RMinisterNameSize >= MAX_CHARACTER_NAME )
			m_RMinisterNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szRMinisterName, szName, m_RMinisterNameSize );
	}

	void SetLGuardName(const char* szName)
	{
		memset( m_szLGuardName, 0, MAX_CHARACTER_NAME );
		m_LGuardNameSize = (uchar)strlen(szName);
		if( m_LGuardNameSize >= MAX_CHARACTER_NAME )
			m_LGuardNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szLGuardName, szName, m_LGuardNameSize );
	}

	void SetRGuardName(const char* szName)
	{
		memset( m_szRGuardName, 0, MAX_CHARACTER_NAME );
		m_RGuardNameSize = (uchar)strlen(szName);
		if( m_RGuardNameSize >= MAX_CHARACTER_NAME )
			m_RGuardNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szRGuardName, szName, m_RGuardNameSize );
	}

	void SetNotice(const char* szName)
	{
		memset( m_szNotice, 0, MAX_NOTICE_SIZE );
		m_NoticeSize = (uchar)strlen(szName);
		if( m_NoticeSize >= MAX_NOTICE_SIZE )
			m_NoticeSize = MAX_NOTICE_SIZE - 1;
		memcpy( m_szNotice, szName, m_NoticeSize );
	}

    void SetCountryPrecontract( int32 iCD, int32 iPrecontract)
    {
        m_iPrecontracts[ iCD] = iPrecontract;
    }

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPacketSize() const
	{
		int nSize = 0;
		//--青龙，朱雀start
		for(int16 i = 0; i < COUNTRY_GUILD_COUNT; i++)
		{
			nSize += sizeof(m_arrCountryBangzhu[i]);
			nSize += sizeof(m_arrCountryBangzhuNameSize[i]);
			nSize += m_arrCountryBangzhuNameSize[i];
			nSize += sizeof(m_arrCountryGuild[i]);

		}
		//--青龙，朱雀end

		return nSize+sizeof(m_KingGUID) + sizeof(m_QueenGUID) + sizeof(m_GeneralGUID) + sizeof(m_LMinisterGUID) + sizeof(m_RMinisterGUID) + sizeof(m_LGuardGUID) + sizeof(m_RGuardGUID) +
				sizeof(m_KingGuildGUID) + sizeof(m_nResource) + sizeof(m_nFortuneTime) +
				sizeof(m_KingNameSize) + m_KingNameSize +
				sizeof(m_QueenNameSize) + m_QueenNameSize +
				sizeof(m_GeneralNameSize) + m_GeneralNameSize +
				sizeof(m_LMinisterNameSize) + m_LMinisterNameSize +
				sizeof(m_RMinisterNameSize) + m_RMinisterNameSize +
				sizeof(m_LGuardNameSize) + m_LGuardNameSize +
				sizeof(m_RGuardNameSize) + m_RGuardNameSize +
				sizeof(m_NoticeSize) + m_NoticeSize + sizeof( m_iPrecontracts);
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct CountryBaseInfo
{
	GUID_t		m_KingGUID;
	GUID_t		m_QueenGUID;
	GUID_t		m_GeneralGUID;
	GUID_t		m_LMinisterGUID;
	GUID_t		m_RMinisterGUID;
	GUID_t		m_LGuardGUID;
	GUID_t		m_RGuardGUID;

	GuildID_t	m_nGuildIDOfKing;
	int32		m_nCountryID;
	int32		m_nResource[COUNTRY_RESOURCE_COUNT];
	int32		m_nFortuneTime[COUNTRY_FORTUNE_COUNT];
	int32		m_nFortuneLastTime[COUNTRY_FORTUNE_COUNT];

	int32		m_nBonusTime_King;
	int32		m_nBonusTime_Queen;
	int32		m_nBonusTime_General;
	int32		m_nBonusTime_LMinister;
	int32		m_nBonusTime_RMinister;
	int32		m_nBonusTime_LGuard;
	int32		m_nBonusTime_RGuard;

	char		m_kingly_QiCheng_stat;
	char		m_kingly_Suit_stat;
	uchar		m_rank;

	uchar		m_KingNameSize;
	uchar		m_QueenNameSize;
	uchar		m_GeneralNameSize;
	uchar		m_LMinisterNameSize;
	uchar		m_RMinisterNameSize;
	uchar		m_LGuardNameSize;
	uchar		m_RGuardNameSize;

	char		m_szKingName[MAX_CHARACTER_NAME];
	char		m_szQueenName[MAX_CHARACTER_NAME];
	char		m_szGeneralName[MAX_CHARACTER_NAME];
	char		m_szLMinisterName[MAX_CHARACTER_NAME];
	char		m_szRMinisterName[MAX_CHARACTER_NAME];
	char		m_szLGuardName[MAX_CHARACTER_NAME];
	char		m_szRGuardName[MAX_CHARACTER_NAME];

	//--青龙，朱雀start
	GUID_t			m_arrCountryBangzhu[COUNTRY_GUILD_COUNT]; //国家帮会帮主guid
	char			m_arrCountryBangzhuName[COUNTRY_GUILD_COUNT][MAX_CHARACTER_NAME]; //国家帮会帮主名称
	uchar			m_arrCountryBangzhuNameSize[COUNTRY_GUILD_COUNT];
	GuildID_t		m_arrCountryGuild[COUNTRY_GUILD_COUNT]; //国家帮会list
	//--青龙，朱雀end
	
	int32		m_aFreeParam[CD_INDEX_DEFINE_COUNT];

	void Init()
	{
		m_KingGUID = INVALID_GUID;
		m_QueenGUID = INVALID_GUID;
		m_GeneralGUID = INVALID_GUID;
		m_LMinisterGUID = INVALID_GUID;
		m_RMinisterGUID = INVALID_GUID;
		m_LGuardGUID = INVALID_GUID;
		m_RGuardGUID = INVALID_GUID;

		m_nGuildIDOfKing = INVALID_GUILD_ID;
		m_nCountryID = -1;
		memset( m_nResource, 0, sizeof(m_nResource) );
		memset( m_nFortuneTime, 0, sizeof(m_nFortuneTime) );
		memset( m_nFortuneLastTime, 0, sizeof(m_nFortuneLastTime) );

		m_nBonusTime_King = 0;
		m_nBonusTime_Queen = 0;
		m_nBonusTime_General = 0;
		m_nBonusTime_LMinister = 0;
		m_nBonusTime_RMinister = 0;
		m_nBonusTime_LGuard = 0;
		m_nBonusTime_RGuard = 0;

		m_kingly_QiCheng_stat = 0;
		m_kingly_Suit_stat = 0;
		m_rank = 0;

		m_KingNameSize = 0;
		m_QueenNameSize = 0;
		m_GeneralNameSize = 0;
		m_LMinisterNameSize = 0;
		m_RMinisterNameSize = 0;
		m_LGuardNameSize = 0;
		m_RGuardNameSize = 0;

		memset( m_szKingName, 0, MAX_CHARACTER_NAME );
		memset( m_szQueenName, 0, MAX_CHARACTER_NAME );
		memset( m_szGeneralName, 0, MAX_CHARACTER_NAME );
		memset( m_szLMinisterName, 0, MAX_CHARACTER_NAME );
		memset( m_szRMinisterName, 0, MAX_CHARACTER_NAME );
		memset( m_szLGuardName, 0, MAX_CHARACTER_NAME );
		memset( m_szRGuardName, 0, MAX_CHARACTER_NAME );

		//--青龙，朱雀start
		int16 i;
		for(i = 0; i < COUNTRY_GUILD_COUNT; i++)
		{
			m_arrCountryBangzhu[i] = INVALID_GUID;
			m_arrCountryBangzhuNameSize[i] = 0;
			memset(m_arrCountryBangzhuName[i], 0, MAX_CHARACTER_NAME);
			m_arrCountryGuild[i] = INVALID_GUILD_ID;

		}
		//--青龙，朱雀end

		
		for(i = 0; i < CD_INDEX_DEFINE_COUNT; i++)
		{
			m_aFreeParam[i] = 0;

		}
		
	}

	void SetCountryBangzhuName(const char* szName, int16 nIndex)
	{
		if(nIndex<=COUNTRY_GUILD_KING || nIndex>=COUNTRY_GUILD_COUNT)
		{
			return;
		}
		memset( m_arrCountryBangzhuName[nIndex], 0, MAX_CHARACTER_NAME );
		m_arrCountryBangzhuNameSize[nIndex] = (uchar)strlen(szName);
		if( m_arrCountryBangzhuNameSize[nIndex] >= MAX_CHARACTER_NAME )
			m_arrCountryBangzhuNameSize[nIndex] = MAX_CHARACTER_NAME - 1;
		memcpy(  m_arrCountryBangzhuName[nIndex], szName, m_arrCountryBangzhuNameSize[nIndex] );
	}

	void SetKingName(const char* szName)
	{
		memset( m_szKingName, 0, MAX_CHARACTER_NAME );
		m_KingNameSize = (uchar)strlen(szName);
		if( m_KingNameSize >= MAX_CHARACTER_NAME )
			m_KingNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szKingName, szName, m_KingNameSize );
	}

	void SetQueenName(const char* szName)
	{
		memset( m_szQueenName, 0, MAX_CHARACTER_NAME );
		m_QueenNameSize = (uchar)strlen(szName);
		if( m_QueenNameSize >= MAX_CHARACTER_NAME )
			m_QueenNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szQueenName, szName, m_QueenNameSize );
	}

	void SetGeneralName(const char* szName)
	{
		memset( m_szGeneralName, 0, MAX_CHARACTER_NAME );
		m_GeneralNameSize = (uchar)strlen(szName);
		if( m_GeneralNameSize >= MAX_CHARACTER_NAME )
			m_GeneralNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szGeneralName, szName, m_GeneralNameSize );
	}

	void SetLMinisterName(const char* szName)
	{
		memset( m_szLMinisterName, 0, MAX_CHARACTER_NAME );
		m_LMinisterNameSize = (uchar)strlen(szName);
		if( m_LMinisterNameSize >= MAX_CHARACTER_NAME )
			m_LMinisterNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szLMinisterName, szName, m_LMinisterNameSize );
	}

	void SetRMinisterName(const char* szName)
	{
		memset( m_szRMinisterName, 0, MAX_CHARACTER_NAME );
		m_RMinisterNameSize = (uchar)strlen(szName);
		if( m_RMinisterNameSize >= MAX_CHARACTER_NAME )
			m_RMinisterNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szRMinisterName, szName, m_RMinisterNameSize );
	}

	void SetLGuardName(const char* szName)
	{
		memset( m_szLGuardName, 0, MAX_CHARACTER_NAME );
		m_LGuardNameSize = (uchar)strlen(szName);
		if( m_LGuardNameSize >= MAX_CHARACTER_NAME )
			m_LGuardNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szLGuardName, szName, m_LGuardNameSize );
	}

	void SetRGuardName(const char* szName)
	{
		memset( m_szRGuardName, 0, MAX_CHARACTER_NAME );
		m_RGuardNameSize = (uchar)strlen(szName);
		if( m_RGuardNameSize >= MAX_CHARACTER_NAME )
			m_RGuardNameSize = MAX_CHARACTER_NAME - 1;
		memcpy( m_szRGuardName, szName, m_RGuardNameSize );
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		int nSize = 0;
		//--青龙，朱雀start
		for(int16 i = 0; i < COUNTRY_GUILD_COUNT; i++)
		{
			nSize += sizeof(m_arrCountryBangzhu[i]);
			nSize += sizeof(m_arrCountryBangzhuNameSize[i]);
			nSize += m_arrCountryBangzhuNameSize[i];
			nSize += sizeof(m_arrCountryGuild[i]);

		}
		//--青龙，朱雀end

		nSize += sizeof(int32)*CD_INDEX_DEFINE_COUNT;


		return nSize + sizeof(GUID_t)*7
				+ sizeof(m_nGuildIDOfKing) + sizeof(m_nCountryID) + sizeof(m_nResource) + sizeof(m_nFortuneTime) + sizeof(m_nFortuneLastTime) 
				+ sizeof(int32) * 7
				+ sizeof(char) + sizeof(char) + sizeof(uchar)
				+ sizeof(uchar) * 7
				+ m_KingNameSize
				+ m_QueenNameSize
				+ m_GeneralNameSize
				+ m_LMinisterNameSize
				+ m_RMinisterNameSize
				+ m_LGuardNameSize
				+ m_RGuardNameSize;

	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct Withdraw
{
	GUID_t	m_KingGUID;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetPacketSize() const
	{
		return sizeof(m_KingGUID);
	}

	void Init()
	{
		m_KingGUID = INVALID_GUID;
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct KingZhaoJi
{
	GUID_t	m_UserGuid;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	uint32 GetPacketSize() const
	{
		return sizeof(m_UserGuid);
	}

	void Init()
	{
		m_UserGuid = INVALID_GUID;
	}

	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

enum Precontract_Bit_Define     // 预约信息占国家变量的Bit数
{
    pb_hour   = 5,              // 预约时间：小时
    pb_minute = 6,              // 预约时间：分钟
    pb_type   = 4,              // 预约类型
    pb_flag   = 1,              // 是否预约标记
    pb_date   = 9,              // 上次国务预约日期
    pb_times  = 5,              // 每日预约次数统计

    pb_max    = 32, 
};
#define MAX_VALUE_IN32( BitCount) ( MAX_UINT32_VALUE >> ( pb_max - BitCount) )
#define GET_BITS_VALUE( sValue, iValue, Bits) ( sValue & ( iValue << Bits) ) >> Bits

struct Precontract
{
    GUID_t  m_Guid;

    int32   m_iPrecontract;

    int32   GetPacketSize() const
    {
        return ( sizeof( m_Guid) + sizeof( m_iPrecontract) );
    }

    void    Init()
    {
        m_Guid = INVALID_GUID;
        m_iPrecontract = 0;
    }

    void	Reci( RecieveStream &iStream);
    void	Send( SendStream &oStream) const;

};

struct RequestCountryColleague
{
	CountryID_t m_nCountryID; //申请结盟者所在的国家
	CountryID_t m_nTargetCountryID; //对方的国家
	
    int32   GetPacketSize() const
    {
        return ( sizeof (m_nCountryID)   + sizeof (m_nTargetCountryID) ) ;
    }

    void    Init()
    {
        m_nCountryID = INVALID_ID;
		m_nTargetCountryID = INVALID_ID;
		
    }

    void	Reci( RecieveStream &iStream);
    void	Send( SendStream &oStream) const;

};


#endif
