/*$T Common/StructCountry.cpp GC 1.140 10/10/07 10:06:55 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "StructCountry.h"
#include "StructDB.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

_COUNTRY::_COUNTRY()
{
	m_King = INVALID_GUID;
	m_Challenger = INVALID_GUID;
	m_nCurUser = 0;
	m_nAP = 0;
	m_cCountryID = 0;
	m_KingGuildID = INVALID_GUILD_ID;
	m_ChallengerGuildID = INVALID_GUILD_ID;

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for(i = 0; i < MAX_WORLD_PLAYER; ++i)
	{
		m_aUser[i] = INVALID_GUID;
	}

	//add by wangzhiping for 青龙，朱雀国家帮
	for(i = 0; i < COUNTRY_GUILD_COUNT; i++)
	{
		m_arrCountryBangzhu[i] = INVALID_GUID;
		memset(m_arrCountryBangzhuName[i], 0, MAX_CHARACTER_NAME);
		m_arrCountryGuild[i] = INVALID_GUILD_ID;

		m_arrCountryBangzhu_Challenger[i] = INVALID_GUID;
		memset(m_arrCountryBangzhuName_Challenger[i], 0, MAX_CHARACTER_NAME);
		m_arrCountryGuild_Challenger[i] = INVALID_GUILD_ID;
	}
	//add end

	memset(m_szKing, 0, MAX_CHARACTER_NAME);
	memset(m_szChallenger, 0, MAX_CHARACTER_NAME);
	memset(m_szNotice, 0, MAX_NOTICE_SIZE);
	memset(m_nResource, 0, sizeof(int32) * COUNTRY_RESOURCE_COUNT);

	for(i = 0; i < MAX_FREEPARAM_NUM; ++i)
	{
		m_aFreeParam[i] = INVALID_ID;
	}

	m_kingly_QiCheng_stat = 0;
	m_kingly_Suit_stat = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _COUNTRY::Save2DB(struct Country_DB &db)
{
	/*~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 i = 0;
	/*~~~~~~~~~~~~~~~~~~*/

	db.m_King = m_King;
	db.m_KingGuildID = m_KingGuildID;
	db.m_Challenger = m_Challenger;
	db.m_ChallengerGuildID = m_ChallengerGuildID;
	db.m_cCountryID = m_cCountryID;
	db.m_officer_Queen = m_officer_Queen;
	db.m_officer_General = m_officer_General;
	db.m_officer_LMinister = m_officer_LMinister;
	db.m_officer_RMinister = m_officer_RMinister;
	db.m_officer_LGuard = m_officer_LGuard;
	db.m_officer_RGuard = m_officer_RGuard;
	tsnprintf_s(db.m_szNotice, sizeof(db.m_szNotice), "%s", m_szNotice);
	tsnprintf_s(db.m_szKing, sizeof(db.m_szKing), "%s", m_szKing);
	tsnprintf_s(db.m_szChallenger, sizeof(db.m_szChallenger), "%s", m_szChallenger);

	for(i = 0; i < COUNTRY_RESOURCE_COUNT; ++i)
	{
		db.m_nResource[i] = m_nResource[i];
	}

	//add by wangzhiping for 青龙，朱雀国家帮
	for(i = 0; i < COUNTRY_GUILD_COUNT; i++)
	{
		db.m_arrCountryBangzhu[i] = m_arrCountryBangzhu[i];
		tsnprintf_s(db.m_arrCountryBangzhuName[i], sizeof(db.m_arrCountryBangzhuName[i]), "%s", m_arrCountryBangzhuName[i]);
		db.m_arrCountryGuild[i] = m_arrCountryGuild[i];

		db.m_arrCountryBangzhu_Challenger[i] = m_arrCountryBangzhu_Challenger[i];
		tsnprintf_s(db.m_arrCountryBangzhuName_Challenger[i], sizeof(db.m_arrCountryBangzhuName_Challenger[i]), "%s", m_arrCountryBangzhuName_Challenger[i]);
		db.m_arrCountryGuild_Challenger[i] = m_arrCountryGuild_Challenger[i];
	}
	//add end

	db.m_kingly_QiCheng_stat = m_kingly_QiCheng_stat;
	db.m_kingly_Suit_stat = m_kingly_Suit_stat;

	memcpy(db.m_aFreeParam, m_aFreeParam, sizeof(m_aFreeParam));

	for(i = 0; i < COUNTRY_FORTUNE_COUNT; ++i)
	{
		db.m_ctl_Fortune_db[i] = m_ctl_Fortune[i].m_dbdata;
	}

	db.m_ctl_Assign_General_db = m_ctl_Assign_General.m_dbdata;
	db.m_ctl_Assign_LMinister_db = m_ctl_Assign_LMinister.m_dbdata;
	db.m_ctl_Assign_RMinister_db = m_ctl_Assign_RMinister.m_dbdata;
	db.m_ctl_Assign_LGuard_db = m_ctl_Assign_LGuard.m_dbdata;
	db.m_ctl_Assign_RGuard_db = m_ctl_Assign_RGuard.m_dbdata;
	db.m_ctl_Cancel_General_db = m_ctl_Cancel_General.m_dbdata;
	db.m_ctl_Cancel_LMinister_db = m_ctl_Cancel_LMinister.m_dbdata;
	db.m_ctl_Cancel_RMinister_db = m_ctl_Cancel_RMinister.m_dbdata;
	db.m_ctl_Cancel_LGuard_db = m_ctl_Cancel_LGuard.m_dbdata;
	db.m_ctl_Cancel_RGuard_db = m_ctl_Cancel_RGuard.m_dbdata;

	db.m_ctl_ModifyNotice_db = m_ctl_ModifyNotice.m_dbdata;
	db.m_ctl_Collect_db = m_ctl_Collect.m_dbdata;
	db.m_ctl_ForbidChat_db = m_ctl_ForbidChat.m_dbdata;
	db.m_ctl_Enjail_db = m_ctl_Enjail.m_dbdata;
	db.m_ctl_Assoil_db = m_ctl_Assoil.m_dbdata;

	db.m_ctl_bonus_king_db = m_ctl_bonus_king.m_dbdata;
	db.m_ctl_bonus_queen_db = m_ctl_bonus_queen.m_dbdata;
	db.m_ctl_bonus_general_db = m_ctl_bonus_general.m_dbdata;
	db.m_ctl_bonus_lminister_db = m_ctl_bonus_lminister.m_dbdata;
	db.m_ctl_bonus_rminister_db = m_ctl_bonus_rminister.m_dbdata;
	db.m_ctl_bonus_lguard_db = m_ctl_bonus_lguard.m_dbdata;
	db.m_ctl_bonus_rguard_db = m_ctl_bonus_rguard.m_dbdata;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _COUNTRY::InitFromDB(struct Country_DB &db)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_King = db.m_King;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_KingGuildID = db.m_KingGuildID;
	m_Challenger = db.m_Challenger;
	m_ChallengerGuildID = db.m_ChallengerGuildID;
	m_cCountryID = db.m_cCountryID;
	m_officer_Queen = db.m_officer_Queen;
	m_officer_General = db.m_officer_General;
	m_officer_LMinister = db.m_officer_LMinister;
	m_officer_RMinister = db.m_officer_RMinister;
	m_officer_LGuard = db.m_officer_LGuard;
	m_officer_RGuard = db.m_officer_RGuard;
	tsnprintf_s(m_szNotice, sizeof(m_szNotice), "%s", db.m_szNotice);
	tsnprintf_s(m_szKing, sizeof(m_szKing), "%s", db.m_szKing);
	tsnprintf_s(m_szChallenger, sizeof(m_szChallenger), "%s", db.m_szChallenger);

	/*~~~~~~*/
	int32	i;
	/*~~~~~~*/

	for(i = 0; i < COUNTRY_RESOURCE_COUNT; ++i)
	{
		m_nResource[i] = db.m_nResource[i];
	}

	//add by wangzhiping for 青龙，朱雀国家帮
	for(i = 0; i < COUNTRY_GUILD_COUNT; i++)
	{
		m_arrCountryBangzhu[i] = db.m_arrCountryBangzhu[i];
		tsnprintf_s(m_arrCountryBangzhuName[i], sizeof(m_arrCountryBangzhuName[i]), "%s", db.m_arrCountryBangzhuName[i]);
		m_arrCountryGuild[i] = db.m_arrCountryGuild[i];

		m_arrCountryBangzhu_Challenger[i] = db.m_arrCountryBangzhu_Challenger[i];
		tsnprintf_s(m_arrCountryBangzhuName_Challenger[i], sizeof(m_arrCountryBangzhuName_Challenger[i]), "%s", db.m_arrCountryBangzhuName_Challenger[i]);
		m_arrCountryGuild_Challenger[i] = db.m_arrCountryGuild_Challenger[i];
	}
	//add end

	m_kingly_QiCheng_stat = db.m_kingly_QiCheng_stat;
	m_kingly_Suit_stat = db.m_kingly_Suit_stat;

	memcpy(m_aFreeParam, db.m_aFreeParam, sizeof(db.m_aFreeParam));

	for(i = 0; i < COUNTRY_FORTUNE_COUNT; ++i)
	{
		m_ctl_Fortune[i].InitFromDB(db.m_ctl_Fortune_db[i]);
	}

	m_ctl_Assign_General.InitFromDB(db.m_ctl_Assign_General_db);
	m_ctl_Assign_LMinister.InitFromDB(db.m_ctl_Assign_LMinister_db);
	m_ctl_Assign_RMinister.InitFromDB(db.m_ctl_Assign_RMinister_db);
	m_ctl_Assign_LGuard.InitFromDB(db.m_ctl_Assign_LGuard_db);
	m_ctl_Assign_RGuard.InitFromDB(db.m_ctl_Assign_RGuard_db);
	m_ctl_Cancel_General.InitFromDB(db.m_ctl_Cancel_General_db);
	m_ctl_Cancel_LMinister.InitFromDB(db.m_ctl_Cancel_LMinister_db);
	m_ctl_Cancel_RMinister.InitFromDB(db.m_ctl_Cancel_RMinister_db);
	m_ctl_Cancel_LGuard.InitFromDB(db.m_ctl_Cancel_LGuard_db);
	m_ctl_Cancel_RGuard.InitFromDB(db.m_ctl_Cancel_RGuard_db);

	m_ctl_ModifyNotice.InitFromDB(db.m_ctl_ModifyNotice_db);
	m_ctl_Collect.InitFromDB(db.m_ctl_Collect_db);
	m_ctl_ForbidChat.InitFromDB(db.m_ctl_ForbidChat_db);
	m_ctl_Enjail.InitFromDB(db.m_ctl_Enjail_db);
	m_ctl_Assoil.InitFromDB(db.m_ctl_Assoil_db);

	m_ctl_bonus_king.InitFromDB(db.m_ctl_bonus_king_db);
	m_ctl_bonus_queen.InitFromDB(db.m_ctl_bonus_queen_db);
	m_ctl_bonus_general.InitFromDB(db.m_ctl_bonus_general_db);
	m_ctl_bonus_lminister.InitFromDB(db.m_ctl_bonus_lminister_db);
	m_ctl_bonus_rminister.InitFromDB(db.m_ctl_bonus_rminister_db);
	m_ctl_bonus_lguard.InitFromDB(db.m_ctl_bonus_lguard_db);
	m_ctl_bonus_rguard.InitFromDB(db.m_ctl_bonus_rguard_db);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _COUNTRY::AddUser(GUID_t guid)
{
	__GUARD__ for(int32 i = 0; i < MAX_WORLD_PLAYER; ++i)
	{
		if(m_aUser[i] == INVALID_GUID)
		{
			m_aUser[i] = guid;
			++m_nCurUser;
			break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _COUNTRY::RemoveUser(GUID_t guid)
{
	__GUARD__ for(int32 i = 0; i < MAX_WORLD_PLAYER; ++i)
	{
		if(m_aUser[i] == guid)
		{
			m_aUser[i] = INVALID_GUID;
			--m_nCurUser;
			break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 _COUNTRY::AddResource(int32 nIndex, int32 nDelta)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nIndex >= 0 && nIndex < COUNTRY_RESOURCE_COUNT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDelta > 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nTotal = m_nResource[nIndex] + nDelta;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nTotal > MAXCOUNT_COUNTRY_RESOURCE)
		{
			nDelta = MAXCOUNT_COUNTRY_RESOURCE - m_nResource[nIndex];
			m_nResource[nIndex] = MAXCOUNT_COUNTRY_RESOURCE;
		}
		else
		{
			m_nResource[nIndex] += nDelta;
		}
	}

	return nDelta;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 _COUNTRY::SubResource(int32 nIndex, int32 nDelta)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nIndex >= 0 && nIndex < COUNTRY_RESOURCE_COUNT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nDelta > 0)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRes = m_nResource[nIndex] - nDelta;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nRes < 0)
		{
			nDelta = m_nResource[nIndex];
			m_nResource[nIndex] = 0;
		}
		else
		{
			m_nResource[nIndex] -= nDelta;
		}
	}

	return nDelta;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 _COUNTRY::GetResource(int32 nIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nIndex >= 0 && nIndex < COUNTRY_RESOURCE_COUNT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return m_nResource[nIndex];

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_IntervalControl::_IntervalControl()
{
	m_dbdata.tm_last = 0;
	m_dbdata.tm_checkpoint = 0;
	m_dbdata.count = 0;
	m_nInterval = 0;
	m_nMaxCount = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL _IntervalControl::Request(int32 tmNow, int32 dateNow)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 delta = dateNow - m_dbdata.tm_checkpoint;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(delta >= m_nInterval || delta < 0)
	{
		m_dbdata.tm_last = tmNow;
		m_dbdata.tm_checkpoint = dateNow;
		m_dbdata.count = 1;
		return TRUE;
	}
	else
	{
		if(m_dbdata.count < m_nMaxCount)
		{
			m_dbdata.tm_last = tmNow;
			m_dbdata.count++;
			return TRUE;
		}
		else
			return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL _IntervalControl::TestRequest(int32 tmNow, int32 dateNow)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 delta = dateNow - m_dbdata.tm_checkpoint;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(delta >= m_nInterval || delta < 0)
	{
		return TRUE;
	}
	else
	{
		if(m_dbdata.count < m_nMaxCount)
		{
			return TRUE;
		}
		else
			return FALSE;
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL _IntervalControl::IsDuration(int32 tmNow, int32 nDuration)
{
	__GUARD__ if(tmNow < GetLastTime()) return FALSE;

	if(tmNow - GetLastTime() < nDuration) return TRUE;

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _IntervalControl::InitFromDB(dbstruct &db)
{
	m_dbdata.tm_last = db.tm_last;
	m_dbdata.tm_checkpoint = db.tm_checkpoint;
	m_dbdata.count = db.count;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void _IntervalControl::Init(int32 interval, int32 maxcnt)
{
	m_nInterval = interval;
	m_nMaxCount = maxcnt;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 _IntervalControl::GetLastTime()
{
	return m_dbdata.tm_last;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 _IntervalControl::GetCheckPoint()
{
	return m_dbdata.tm_checkpoint;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
_IntervalControl::dbstruct::dbstruct()
{
	tm_last = 0;
	tm_checkpoint = 0;
	count = 0;
}

_IntervalControl::dbstruct & _IntervalControl::dbstruct::operator =(_IntervalControl::dbstruct & rhs)
{
	tm_last = rhs.tm_last;
	tm_checkpoint = rhs.tm_checkpoint;
	count = rhs.count;
	return *this;
}
