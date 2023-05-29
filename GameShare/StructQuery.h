/*$T Common/StructQuery.h GC 1.140 10/10/07 10:06:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _GAMESTRUCT_HORSEFINDMATE_H_
#define _GAMESTRUCT_HORSEFINDMATE_H_

#include "TypeDefine.h"
#include "StructDB.h"

enum HorseStateChangeType { ST_TRADE = 0, ST_MATING = 1, ST_FREE = 2, ST_RETURNTOCHILD = 3, ST_COUNT };

struct HorseFindMateInfo
{
	SHorseGuid	m_HorseGuid;
	int32		m_iHorseDataId;
	uint32		m_uIssueTime;
	char		m_szHorseName[MAX_CHARACTER_NAME];
	char		m_szOwnerName[MAX_CHARACTER_NAME];
	char		m_szLeaveWords[MAX_BBS_MESSAGE_LENGTH];
	int32		m_iHorseLevel;
	int32		m_iSex;
	int32		m_iGrowRate;
	int32		m_iMatchPoint;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	HorseFindMateInfo &operator=(const HorseFindMateInfo &value)
	{
		m_HorseGuid = value.m_HorseGuid;
		m_iHorseDataId = value.m_iHorseDataId;
		m_uIssueTime = value.m_uIssueTime;
		tsnprintf_s(m_szHorseName, MAX_CHARACTER_NAME, "%s", value.m_szHorseName);
		tsnprintf_s(m_szOwnerName, MAX_CHARACTER_NAME, "%s", value.m_szOwnerName);
		tsnprintf_s(m_szLeaveWords, MAX_BBS_MESSAGE_LENGTH, "%s", value.m_szLeaveWords);
		m_iHorseLevel = value.m_iHorseLevel;
		m_iSex = value.m_iSex;
		m_iGrowRate = value.m_iGrowRate;
		m_iMatchPoint = value.m_iMatchPoint;

		return *this;
	}

	HorseFindMateInfo()
	{
		m_iHorseLevel = INVALID_ID;
		m_iSex = INVALID_SEX;
		m_iGrowRate = INVALID_ID;
		m_iGrowRate = INVALID_ID;
		m_iMatchPoint = INVALID_ID;
		m_uIssueTime = 0;
		tsnprintf_s(m_szHorseName, MAX_CHARACTER_NAME, "%s", "");
		tsnprintf_s(m_szOwnerName, MAX_CHARACTER_NAME, "%s", "");
		tsnprintf_s(m_szLeaveWords, MAX_BBS_MESSAGE_LENGTH, "%s", "");
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(m_HorseGuid) +
			sizeof(m_iHorseDataId) +
			sizeof(m_uIssueTime) +
			sizeof(m_szHorseName) +
			sizeof(m_szOwnerName) +
			sizeof(m_szLeaveWords) +
			sizeof(m_iHorseLevel) +
			sizeof(m_iSex) +
			sizeof(m_iGrowRate) +
			sizeof(m_iMatchPoint);
	}

	
};

struct HorseFindMateInfoPerPage
{
	enum { MAX_COUNT_PER_PAGE = 6 };

	int32 m_iCount;
	HorseFindMateInfo m_aList[MAX_COUNT_PER_PAGE];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	HorseFindMateInfoPerPage &operator=(const HorseFindMateInfoPerPage &value)
	{
		m_iCount = value.m_iCount;
		for(int32 i = 0; i < MAX_COUNT_PER_PAGE; ++i) m_aList[i] = value.m_aList[i];

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(m_iCount) + m_aList[0].GetSize() * MAX_COUNT_PER_PAGE;
	}

	
};

struct OnlineUser_SameCity
{
	GUID_t		m_PlayerGUID;
	char		m_szName[MAX_CHARACTER_NAME];
	char		m_szGuildName[MAX_GUILD_NAME_SIZE];
	int32		m_iLevel;
	int32		m_iCountry;
	int32		m_iProfession;
	POSTCODE	m_PostCode;
	int32		m_nGuildId;
	int32		m_nGuildPos;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	OnlineUser_SameCity &operator=(const OnlineUser_SameCity &value)
	{
		m_PlayerGUID = value.m_PlayerGUID;
		tsnprintf_s(m_szName, MAX_CHARACTER_NAME, "%s", value.m_szName);
		tsnprintf_s(m_szGuildName, MAX_CHARACTER_NAME, "%s", value.m_szGuildName);
		m_iLevel = value.m_iLevel;
		m_iCountry = value.m_iCountry;
		m_iProfession = value.m_iProfession;
		m_PostCode = value.m_PostCode;
		m_nGuildId = value.m_nGuildId;
		m_nGuildPos = value.m_nGuildPos;

		return *this;
	}

	OnlineUser_SameCity()
	{
		m_PlayerGUID = INVALID_GUID;
		m_iLevel = INVALID_ID;
		m_iCountry = INVALID_ID;
		m_iProfession = INVALID_ID;
		m_PostCode = INVALID_ID;
		m_nGuildId = INVALID_ID;
		m_nGuildPos = INVALID_ID;
		tsnprintf_s(m_szName, MAX_CHARACTER_NAME, "%s", "");
		tsnprintf_s(m_szGuildName, MAX_CHARACTER_NAME, "%s", "");
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(m_PlayerGUID) + sizeof(m_szName) + sizeof(m_szGuildName) + sizeof(m_iLevel) + sizeof(m_iCountry) + sizeof(m_iProfession) + sizeof(m_PostCode) + sizeof(m_nGuildId) + sizeof(m_nGuildPos);
	}

	
};

struct OnlineUser_SameCity_PerPage
{
	enum { MAX_ONLINEUSER_NUMBER = 20 };

	int32 m_iCount;
	OnlineUser_SameCity m_aList[MAX_ONLINEUSER_NUMBER];

	OnlineUser_SameCity_PerPage()
	{
		m_iCount = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	OnlineUser_SameCity_PerPage &operator=(const OnlineUser_SameCity_PerPage &value)
	{
		m_iCount = value.m_iCount;
		for(int32 i = 0; i < MAX_ONLINEUSER_NUMBER; ++i) m_aList[i] = value.m_aList[i];

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		return sizeof(m_iCount) + m_aList[0].GetSize() * m_iCount;
	}

	
};
#endif
