/*$T Common/Auth_Struct.h GC 1.140 10/10/07 10:06:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _AUTH_STRUCT_H_
#define _AUTH_STRUCT_H_
#include "TypeDefine.h"
//本文件是AWCommand消息所用
#define MAX_CHATCONT_SIZE	257
#define MAX_CHARNAME_SIZE	30
#define MAX_CHARTITLE_SIZE	34
#define MAX_GUILDNAME_SIZE	30
#define MAX_RET_SERVER		10
#define MAX_ACC_SIZE		50

class	RecieveStream;
class	SendStream;
enum AUTH_TYPE
{
	AT_NONE			= 0,
	AT_SYSBOARD		= 1,
	AT_PLAYERCOUNT		= 2,
	AT_RETPLAYERCOUNT	= 3,
	AT_KICKPLAYER		= 4,
	AT_RETKICKPLAYER	= 5,
	AT_PLAYERINFO		= 6,
	AT_RETPLAYERINFO	= 7,
	AT_CHATSTAT		= 8,
	AT_SERVERSTAT		= 9,
	AT_RETSERVERSTAT	= 10,
	AT_UPDATEAUTHINFO	= 11,
	AT_BESHUTDOWN		= 12,
	AT_MODIFYSET		= 13,
	AT_MODIFYMAXPLAYER	= 14,
	AT_RETCRCERROR		= 15,
	AT_WORLDSHOPCONFIG	= 16,
	AT_WORLDSTOCKCONFIG	= 17,
};

#pragma pack(push, 1)
struct AUTH_SYSBOARD
{
	ID_t	m_WorldID;
	int32	m_nSize;
	char	m_szContex[MAX_CHATCONT_SIZE];
	char	m_NameSize;
	char	m_CharName[MAX_CHARNAME_SIZE];
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_PLAYERCOUNT
{
	ID_t	m_WorldID;
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_RETPLAYERCOUNT
{
	ID_t	m_WorldID;
	int32	m_PlayerCount;
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_KICKPLAYER
{
	ID_t	m_WorldID;
	char	m_NameSize;
	char	m_CharName[MAX_CHARNAME_SIZE];

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_RETKICKPLAYER
{
	ID_t	m_WorldID;
	char	m_NameSize;
	char	m_CharName[MAX_CHARNAME_SIZE];
	int32	m_Result;

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_PLAYERINFO
{
	ID_t	m_WorldID;
	char	m_NameSize;
	char	m_CharName[MAX_CHARNAME_SIZE];
	char	m_ClientAccSize;
	char	m_ClientAccName[MAX_ACC_SIZE];

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_RETPLAYERBASEINFO
{
	ID_t		m_WorldID;
	char		m_NameSize;
	char		m_CharName[MAX_CHARNAME_SIZE];
	char		m_AccSize;
	char		m_Accname[MAX_ACC_SIZE];
	char		m_ClientAccSize;
	char		m_ClientAccName[MAX_ACC_SIZE];
	GUID_t		m_GUID;
	MapID_t		m_SceneID;
	TeamID_t	m_TeamID;
	uint32		m_uCountry;
	int32		m_nLevel;
	uint16		m_uSex;
	char		m_titleSize;
	char		m_szTitle[MAX_CHARTITLE_SIZE];
	GuildID_t	m_GuildID;
	char		m_guildSize;
	char		m_szGuildName[MAX_GUILDNAME_SIZE];
	void		Clear();
	uint32		GetSize() const;
	void		Read(RecieveStream &iStream);
	void		Write(SendStream &oStream) const;
};

struct AUTH_CHATSTAT
{
	ID_t	m_WorldID;
	char	m_NameSize;
	char	m_CharName[MAX_CHARNAME_SIZE];
	int32	m_ChatStat;
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct AUTH_SERVERSTATUS
{
	ID_t	m_WorldID;
	ID_t	m_MapID;
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
struct AUTH_RETSERVERSTATUS
{
	ID_t	m_WorldID;
	ID_t	m_aMapID[MAX_RET_SERVER];

	int32	m_aStatus[MAX_RET_SERVER];
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct AUTH_SHUTDOWN
{
	int16	m_Minute;
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

enum MOD_SET_TYPE { MST_TV = -1, MST_T0 = 0, MST_T1 = 1, };
struct AUTH_MODIFYSET
{
	ID_t	m_WorldID;
	int32	m_MST_Type;
	float	m_Rate;
	int32	m_MapID;

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct AUTH_MODIFYMAXPLAYER
{
	ID_t	m_WorldID;
	int32	m_MaxPlayer;
	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct AUTH_RETCRCERROR
{
	ID_t	m_WorldID;
	GUID_t	m_GUID;
	char	m_NameSize;
	char	m_CharName[MAX_CHARNAME_SIZE];
	char	m_AccSize;
	char	m_Accname[MAX_ACC_SIZE];

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

enum WORLD_SHOP_OPER_TYPE
{
	OP_TYPE_NONE			= 0,
	OP_TYPE_AUTO_BUY_CALL,
	OP_TYPE_MIN_BUY_BACK_PRICE,
	OP_TYPE_MAX_BUY_BACK_PRICE,
	OP_TYPE_MAX_BUY_BACK_COUNT,
	OP_TYPE_MIN_BUY_BACK_TIME,
	OP_TYPE_MAX_BUY_BACK_TIME,
};

struct AUTH_WORLDSHOP
{
	ID_t	m_WorldID;
	uchar	m_OperType;
	uint32	m_ShopId;
	uint32	m_BuyCallIndex;

	uint32	m_Parameter;

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

enum WORLD_STOCK_OPER_TYPE
{
	OP_STOCK_TYPE_NONE			= 0,
	OP_STOCK_TYPE_AUTO_BUY_CALL,
	OP_STOCK_TYPE_MIN_BUY_BACK_PRICE,
	OP_STOCK_TYPE_MAX_BUY_BACK_PRICE,
	OP_STOCK_TYPE_MAX_BUY_BACK_COUNT,
	OP_STOCK_TYPE_MIN_BUY_BACK_TIME,
	OP_STOCK_TYPE_MAX_BUY_BACK_TIME,
};

struct AUTH_WORLDSTOCK
{
	ID_t	m_WorldID;
	uchar	m_OperType;
	uint32	m_Id;
	uint32	m_BuyCallIndex;

	uint32	m_Parameter;

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};

struct AUTH_STRUCT
{
	AUTH_TYPE	m_AT;
	uint32		m_authid;
	union
	{
		AUTH_SYSBOARD		m_SysBoard;
		AUTH_PLAYERCOUNT	m_PlayerCount;
		AUTH_RETPLAYERCOUNT	m_RetPlayerCount;
		AUTH_KICKPLAYER		m_KickPlayer;
		AUTH_RETKICKPLAYER	m_RetKickPlayer;
		AUTH_PLAYERINFO		m_PlayerInfo;
		AUTH_RETPLAYERBASEINFO	m_RetPlayerInfo;
		AUTH_CHATSTAT		m_ChatStat;
		AUTH_SERVERSTATUS	m_ServerStatus;
		AUTH_RETSERVERSTATUS	m_RetServerStatus;
		AUTH_SHUTDOWN		m_ShutDown;
		AUTH_MODIFYSET		m_ModifySet;
		AUTH_MODIFYMAXPLAYER	m_ModifyMaxPlayer;
		AUTH_RETCRCERROR	m_RetCRCError;
		AUTH_WORLDSHOP		m_WorldShop;
		AUTH_WORLDSTOCK		m_WorldStock;
	};

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
};
#pragma pack(pop)
#endif
