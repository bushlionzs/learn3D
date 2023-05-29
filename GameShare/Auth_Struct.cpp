/*$T Common/Auth_Struct.cpp GC 1.140 10/10/07 10:06:26 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Auth_Struct.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

void AUTH_SYSBOARD::Clear()
{
	m_WorldID = INVALID_ID;
	m_nSize = 0;
	memset(m_szContex, 0, sizeof(char) * MAX_CHATCONT_SIZE);
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_SYSBOARD::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_nSize) + sizeof(char) * m_nSize + sizeof(m_NameSize) + m_NameSize * sizeof(char);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_PLAYERCOUNT::Clear()
{
	m_WorldID = INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_PLAYERCOUNT::GetSize() const
{
	return sizeof(m_WorldID);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_RETPLAYERCOUNT::Clear()
{
	m_WorldID = INVALID_ID;
	m_PlayerCount = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_RETPLAYERCOUNT::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_PlayerCount);
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_KICKPLAYER::Clear()
{
	m_WorldID = INVALID_ID;
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_KICKPLAYER::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_NameSize) + m_NameSize * sizeof(char);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_RETKICKPLAYER::Clear()
{
	m_WorldID = INVALID_ID;
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
	m_Result = INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_RETKICKPLAYER::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_NameSize) + m_NameSize * sizeof(char) + sizeof(m_Result);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_PLAYERINFO::Clear()
{
	m_WorldID = INVALID_ID;
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
	m_ClientAccSize = 0;
	memset(m_ClientAccName, 0, MAX_ACC_SIZE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_PLAYERINFO::GetSize() const
{
	return sizeof(m_WorldID) +
		sizeof(m_NameSize) +
		m_NameSize *
		sizeof(char) +
		sizeof(m_ClientAccSize) +
		m_ClientAccSize *
		sizeof(char);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_RETPLAYERBASEINFO::Clear()
{
	m_WorldID = INVALID_ID;
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
	m_AccSize = 0;
	memset(m_Accname, 0, MAX_ACC_SIZE);

	m_ClientAccSize = 0;
	memset(m_ClientAccName, 0, MAX_ACC_SIZE);

	m_GUID = INVALID_ID;
	m_SceneID = INVALID_ID;
	m_TeamID = INVALID_ID;
	m_uCountry = -1;
	m_nLevel = 0;
	m_uSex = 0;
	m_titleSize = 0;
	memset(m_szTitle, 0, MAX_CHARTITLE_SIZE);
	m_GuildID = INVALID_ID;
	m_guildSize = 0;
	memset(m_szGuildName, 0, MAX_GUILDNAME_SIZE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_RETPLAYERBASEINFO::GetSize() const
{
	return sizeof(m_WorldID) +
		sizeof(m_NameSize) +
		m_NameSize *
		sizeof(char) +
		sizeof(m_AccSize) +
		m_AccSize *
		sizeof(char) +
		sizeof(m_ClientAccSize) +
		m_ClientAccSize *
		sizeof(char) +
		sizeof(GUID_t) +
		sizeof(MapID_t) +
		sizeof(TeamID_t) +
		sizeof(uint32) +
		sizeof(int32) +
		sizeof(uint16) +
		sizeof(m_titleSize) +
		m_titleSize *
		sizeof(char) +
		sizeof(GuildID_t) +
		sizeof(m_guildSize) +
		m_guildSize *
		sizeof(char);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_CHATSTAT::Clear()
{
	m_WorldID = INVALID_ID;
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
	m_ChatStat = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_CHATSTAT::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_NameSize) + m_NameSize * sizeof(char) + sizeof(int32);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_SERVERSTATUS::Clear()
{
	m_WorldID = INVALID_ID;
	m_MapID = INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_SERVERSTATUS::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_MapID);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_RETSERVERSTATUS::Clear()
{
	m_WorldID = INVALID_ID;
	for(int32 i = 0; i < MAX_RET_SERVER; i++)
	{
		m_aMapID[i] = INVALID_ID;
		m_aStatus[i] = 0;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_RETSERVERSTATUS::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(ID_t) * MAX_RET_SERVER + sizeof(int32) * MAX_RET_SERVER;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_SHUTDOWN::Clear()
{
	m_Minute = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_SHUTDOWN::GetSize() const
{
	return sizeof(m_Minute);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_MODIFYSET::Clear()
{
	m_WorldID = INVALID_ID;
	m_MST_Type = MST_TV;
	m_MapID = INVALID_ID;
	m_Rate = 1.0f;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_MODIFYSET::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_MST_Type) + sizeof(m_Rate) + sizeof(m_MapID);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_MODIFYMAXPLAYER::Clear()
{
	m_WorldID = INVALID_ID;
	m_MaxPlayer = 5000;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_MODIFYMAXPLAYER::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_MaxPlayer);
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_RETCRCERROR::Clear()
{
	m_WorldID = INVALID_ID;
	m_NameSize = 0;
	memset(m_CharName, 0, MAX_CHARNAME_SIZE);
	m_AccSize = 0;
	memset(m_Accname, 0, MAX_ACC_SIZE);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_RETCRCERROR::GetSize() const
{
	return sizeof(m_WorldID) +
		sizeof(m_NameSize) +
		m_NameSize *
		sizeof(char) +
		sizeof(m_AccSize) +
		m_AccSize *
		sizeof(char);
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_WORLDSHOP::Clear()
{
	m_WorldID = INVALID_ID;
	m_OperType = OP_TYPE_NONE;
	m_ShopId = INVALID_ID;
	m_BuyCallIndex = INVALID_ID;
	m_Parameter = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_WORLDSHOP::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_OperType) + sizeof(m_ShopId) + sizeof(m_BuyCallIndex) + sizeof(m_Parameter);
}



/*
=======================================================================================================================
=======================================================================================================================
*/
void AUTH_WORLDSTOCK::Clear()
{
	m_WorldID = INVALID_ID;
	m_OperType = OP_TYPE_NONE;
	m_Id = INVALID_ID;
	m_BuyCallIndex = INVALID_ID;
	m_Parameter = 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 AUTH_WORLDSTOCK::GetSize() const
{
	return sizeof(m_WorldID) + sizeof(m_OperType) + sizeof(m_Id) + sizeof(m_BuyCallIndex) + sizeof(m_Parameter);
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
void AUTH_STRUCT::Clear()
{
	m_AT = AT_NONE;
	m_authid = INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 AUTH_STRUCT::GetSize() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uSize = sizeof(m_AT) + sizeof(m_authid);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(m_AT)
	{
	case AT_SYSBOARD:		uSize += m_SysBoard.GetSize(); break;
	case AT_PLAYERCOUNT:		uSize += m_PlayerCount.GetSize(); break;
	case AT_RETPLAYERCOUNT:		uSize += m_RetPlayerCount.GetSize(); break;
	case AT_KICKPLAYER:		uSize += m_KickPlayer.GetSize(); break;
	case AT_RETKICKPLAYER:		uSize += m_RetKickPlayer.GetSize(); break;
	case AT_PLAYERINFO:		uSize += m_PlayerInfo.GetSize(); break;
	case AT_RETPLAYERINFO:		uSize += m_RetPlayerInfo.GetSize(); break;
	case AT_CHATSTAT:		uSize += m_ChatStat.GetSize(); break;
	case AT_SERVERSTAT:		uSize += m_ServerStatus.GetSize(); break;
	case AT_RETSERVERSTAT:		uSize += m_RetServerStatus.GetSize(); break;
	case AT_UPDATEAUTHINFO:		break;
	case AT_BESHUTDOWN:		uSize += m_ShutDown.GetSize(); break;
	case AT_MODIFYSET:		uSize += m_ModifySet.GetSize(); break;
	case AT_MODIFYMAXPLAYER:	uSize += m_ModifyMaxPlayer.GetSize(); break;
	case AT_RETCRCERROR:		uSize += m_RetCRCError.GetSize(); break;
	case AT_WORLDSHOPCONFIG:	uSize += m_WorldShop.GetSize(); break;
	case AT_WORLDSTOCKCONFIG:	uSize += m_WorldStock.GetSize(); break;
	default:			break;
	}

	return uSize;
}


