
#ifndef GAMESTRUCT_TEAM_H
#define GAMESTRUCT_TEAM_H

#include "StructDB.h"

#define IS_CAN_ADD_GOODBAD_VALUE	"IsCanAddGoodbadValue"

#define IS_CAN_ADD_MULT_EXP	"IsCanAddMultExp"

#define ONCE_RECRUIT_LIST_LEN	50

enum RECRUIT_TYPE { LEADER_RECRUIT = 0, MEMBER_RECRUIT, };

enum TEAME_TARGET { EXERCISE_LEVEL = 0, DO_QUEST, BOUT, KILL_BOSS, KILL_ENEMY, HANG, TARGET_NUMBER, };

struct LEADER_RECRUIT_ATTRIB
{
	LEADER_RECRUIT_ATTRIB()
	{
		m_MinLevel = 0;
		m_MaxLevel = MAX_PLAYER_EXP_LEVEL;
		memset(m_IsInCountry, 0, sizeof(m_IsInCountry));
		memset(m_IsTarget, 0, sizeof(m_IsTarget));
		memset(m_IsProfessionID, 0, sizeof(m_IsProfessionID));
		memset(m_szTeamEnounce, 0, TEAM_ENOUNCE_LEN);
	}
	int32	m_MinLevel;
	int32	m_MaxLevel;

	BOOL	m_IsInCountry[COUATTRIBUTE_NUMBER];

	BOOL	m_IsTarget[TARGET_NUMBER];

	BOOL	m_IsProfessionID[PROFESSION_NUMBER];

	char	m_szTeamEnounce[TEAM_ENOUNCE_LEN];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetSize() const
	{
		uint32	size = sizeof(int32) *
			2 +
			sizeof(m_IsInCountry) +
			sizeof(m_IsTarget) +
			sizeof(m_IsProfessionID) +
			sizeof(m_szTeamEnounce);
		return size;
	}

	static uint32 GetMaxSize()
	{
		uint32 size = sizeof(int32)*2 + sizeof(BOOL)*COUATTRIBUTE_NUMBER + sizeof(BOOL)*TARGET_NUMBER + sizeof(BOOL)*PROFESSION_NUMBER + sizeof(char)*TEAM_ENOUNCE_LEN;
		return size;
	}

	
};

struct MEMBER_RECRUIT_ATTRIB
{
	MEMBER_RECRUIT_ATTRIB()
	{
		m_MinLevel = 0;
		m_MaxLevel = MAX_PLAYER_EXP_LEVEL;
		memset(m_IsInCountry, 0, sizeof(m_IsInCountry));
		memset(m_IsTarget, 0, sizeof(m_IsTarget));
		memset(m_szTeamEnounce, 0, TEAM_ENOUNCE_LEN);
	}
	int32	m_MinLevel;
	int32	m_MaxLevel;

	BOOL	m_IsInCountry[COUATTRIBUTE_NUMBER];

	BOOL	m_IsTarget[TARGET_NUMBER];

	char	m_szTeamEnounce[TEAM_ENOUNCE_LEN];

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	uint32 GetSize() const
	{
		return sizeof(int32) + sizeof(int32) + sizeof(m_IsInCountry) + sizeof(m_IsTarget) + sizeof(m_szTeamEnounce);
	}

	static uint32 GetMaxSize()
	{
		return sizeof(int32) + sizeof(int32) + sizeof(BOOL)*COUATTRIBUTE_NUMBER + sizeof(BOOL)*TARGET_NUMBER + sizeof(char)*TEAM_ENOUNCE_LEN;
	}

	
};

struct RECRUIT_OWNER_INFO
{
	RECRUIT_OWNER_INFO()
	{
		m_NameLen = 0;
		memset(m_szUserName, 0, MAX_CHARACTER_NAME);
		m_Level = INVALID_ID;
		m_ManPai = INVALID_ID;
		m_Country = INVALID_ID;
	}
	uchar	m_NameLen;
	char	m_szUserName[MAX_CHARACTER_NAME];
	int32	m_Level;
	uchar	m_ManPai;
	uchar	m_Country;
};

enum NODE_STATE { NODE_NULL = 0, NODE_USING, STATE_NUM, };

struct LEADER_INFO_NODE
{
	LEADER_INFO_NODE()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(&m_OwnerInfo, 0, sizeof(RECRUIT_OWNER_INFO));
		memset(&m_LeaderRecruit, 0, sizeof(LEADER_RECRUIT_ATTRIB));
		m_NodeState = NODE_NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOwnerData(RECRUIT_OWNER_INFO &Data)
	{
		memcpy(&m_OwnerInfo, &Data, sizeof(RECRUIT_OWNER_INFO));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetRecruitData(LEADER_RECRUIT_ATTRIB &Data)
	{
		memcpy(&m_LeaderRecruit, &Data, sizeof(LEADER_RECRUIT_ATTRIB));
	}

	uchar			m_NodeState;
	RECRUIT_OWNER_INFO	m_OwnerInfo;
	LEADER_RECRUIT_ATTRIB	m_LeaderRecruit;
};

struct MEMBER_INFO_NODE
{
	MEMBER_INFO_NODE()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(&m_OwnerInfo, 0, sizeof(RECRUIT_OWNER_INFO));
		memset(&m_MemberRecruit, 0, sizeof(MEMBER_RECRUIT_ATTRIB));
		m_NodeState = NODE_NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetOwnerData(RECRUIT_OWNER_INFO &Data)
	{
		memcpy(&m_OwnerInfo, &Data, sizeof(RECRUIT_OWNER_INFO));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetRecruitData(MEMBER_RECRUIT_ATTRIB &Data)
	{
		memcpy(&m_MemberRecruit, &Data, sizeof(MEMBER_RECRUIT_ATTRIB));
	}

	uchar			m_NodeState;
	RECRUIT_OWNER_INFO	m_OwnerInfo;
	MEMBER_RECRUIT_ATTRIB	m_MemberRecruit;
};

struct RETURN_RECRUIT_INFO
{
	RETURN_RECRUIT_INFO()
	{
		m_Level = INVALID_ID;
		m_ManPai = INVALID_ID;
		m_Country = INVALID_ID;
		m_NameLen = 0;
		memset(m_TeamTarget, 0, TARGET_NUMBER);
		memset(m_szTeamEnounce, 0, TEAM_ENOUNCE_LEN);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSize() const
	{
		uint32	size = sizeof(m_Level) + sizeof(m_ManPai) + sizeof(m_Country) + sizeof(m_TeamTarget) + sizeof
			(m_NameLen) + m_NameLen * sizeof(char) + sizeof(m_szTeamEnounce);
		return size;
	}


	uchar	m_NameLen;
	char	m_szUserName[MAX_CHARACTER_NAME];
	int32	m_Level;
	uchar	m_ManPai;
	uchar	m_Country;
	BOOL	m_TeamTarget[TARGET_NUMBER];

	char	m_szTeamEnounce[TEAM_ENOUNCE_LEN];
};

class	SimpleEffectList
{
	int32		m_nNumOfImpacts;
	EffectID_t	m_aBuffID[MAX_IMPACT_NUM];

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SimpleEffectList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_nNumOfImpacts = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetImpactsCount()
	{
		return m_nNumOfImpacts;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void AddImpact(EffectID_t impact)
	{
		KCheck(m_nNumOfImpacts <= MAX_IMPACT_NUM);
		m_aBuffID[m_nNumOfImpacts++] = impact;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void RemoveImpact(EffectID_t impact)
	{
		KCheck(m_nNumOfImpacts > 0);
		for(int32 i = 0; i < m_nNumOfImpacts; ++i)
		{
			if(m_aBuffID[i] == impact)
			{
				--m_nNumOfImpacts;

				for(int32 j = i; j < m_nNumOfImpacts; ++j)
				{
					m_aBuffID[j] = m_aBuffID[j + 1];
				}

				return;
			}
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	EffectID_t GetImpactsByIndex(int32 index)
	{
		if(index >= m_nNumOfImpacts) return INVALID_ID;
		return m_aBuffID[index];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetImpactList(const SimpleEffectList *pSimpleImpactList)
	{
		memcpy(this, pSimpleImpactList, sizeof(*this));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetImpactList(const _EFFECT_LIST *pEffectList)
	{
		m_nNumOfImpacts = pEffectList->m_Count;
		for(int32 i = 0; i < m_nNumOfImpacts; ++i)
		{
			m_aBuffID[i] = pEffectList->m_aImpacts[i].GetImpactID();
		}
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(const _EFFECT_LIST &ImpactList) const
	{
		if(m_nNumOfImpacts != ImpactList.m_Count)
		{
			return FALSE;
		}

		for(int32 i = 0; i < ImpactList.m_Count; ++i)
		{
			/*~~~~~~*/
			int32	j;
			/*~~~~~~*/

			for(j = 0; j < m_nNumOfImpacts; ++j)
			{
				if(ImpactList.m_aImpacts[i].GetImpactID() == m_aBuffID[j])
				{
					break;
				}
			}

			if(j >= m_nNumOfImpacts)
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator!=(const _EFFECT_LIST &ImpactList) const
	{
		return(*this == ImpactList) == FALSE;
	}
};

typedef struct call_up
{
	MapID_t m_nMapId;
	uint16	m_nPosX;
	uint16	m_nPosZ;
	uint8	m_nNeedLevel;

	void	Clear();
	uint32	GetSize() const;
	void	Read(RecieveStream &iStream);
	void	Write(SendStream &oStream) const;
}CALL_UP_INVITE, CALL_UP_ACCEPT;

enum XG_CALL_UP_TEAMMEMBER
{
	E_CALL_UP_INVITE = 1,
	E_CALL_UP_ACCEPT,
	E_CALL_UP_ACTIVE_NOW,
};

struct XG_TEAM
{
	uint8	m_nOpType;
	GUID_t	m_GUID;
	union
	{
		GUID_t			m_nAcceptWho;
		CALL_UP_INVITE	m_Invite;
	};

	void	Clear();
	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

struct GX_TEAM
{
	uint8		m_nOpType;
	ConnectorID_t	m_nPlayerID;

	union
	{
		GUID_t			m_nInviter;
		CALL_UP_ACCEPT	m_Accept;
	};

	void	Clear();
	uint32	GetSize() const;
	void	Reci(RecieveStream &iStream);
	void	Send(SendStream &oStream) const;
};

#define IS_CAN_GOTO_TEAMMEMBER_POSITION	"IsCanGotoTeamMemberPosition"

#endif
