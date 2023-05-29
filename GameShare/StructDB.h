/*$T Common/StructDB.h GC 1.140 10/10/07 10:06:55 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __DBSTRUCT_H__
#define __DBSTRUCT_H__

#include "TypeDefine.h"
#include "Define.h"
#include "Enum.h"
#include "DefineAttr.h"
#include "DefineCountry.h"
#include "StructEffect.h"
#include "StructSpell.h"
#include "StructCountry.h"
#include "StructGuild.h"
#include "StructTopList.h"
#include "Util.h"
#include "StructWorldShop.h"
#include "HumanStateMutexDefine.h"

#pragma pack(push, 1)
class							PlayerArchive;

typedef CDList<MAX_COOLDOWN_LIST_SIZE_FOR_HUMAN>	CooldownListForHuman_T;
typedef CooldownListForHuman_T				SArchiveLoader_CoolDown;
typedef CDList<MAX_COOLDOWN_LIST_SIZE_FOR_PET>		CooldownListForPet_T;
typedef CooldownListForPet_T				_COOLDOWN_DB_LOAD_FOR_PET;
typedef CDList<MAX_COOLDOWN_LIST_SIZE_FOR_MONSTER>	CooldownListForMonster_T;

struct TeamMember_ForChangeScene
{
	GUID_t	m_GUID;
	ObjID_t m_ObjID;
	MapID_t m_SceneID;

	TeamMember_ForChangeScene()
	{
		Clear();
	}
	void Clear()
	{
		m_GUID		= INVALID_ID;
		m_ObjID		= INVALID_ID;
		m_SceneID	= INVALID_ID;
	}
};

struct TeamInfo_ForChangeScene
{
	TeamID_t					m_TeamID;
	int32						m_MemberCount;
	GUID_t						m_MyGUID;
	TeamMember_ForChangeScene	m_aMember[MAX_TEAM_MEMBER];

	TeamInfo_ForChangeScene()
	{
		Clear();
	}

	void Clear()
	{
		m_TeamID		= INVALID_ID;
		m_MemberCount	= 0;
		m_MyGUID		= INVALID_GUID;
		for(int32 i = 0; i < MAX_TEAM_MEMBER; ++i)
		{
			m_aMember[i].Clear();
		}
	}
};

struct POSTCODE
{
	int32	m_PostCode;
	POSTCODE()
	{
		m_PostCode = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetPostCode() const
	{
		return m_PostCode;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetProvinceCode() const
	{
		return(uchar) ((m_PostCode & 0x00FF0000) >> 16);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetCityCode() const
	{
		return(uchar) ((m_PostCode & 0x0000FF00) >> 8);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uchar GetSectionCode() const
	{
		return(uchar) ((m_PostCode & 0x000000FF));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Assign(uchar byProvinceCode, uchar byCityCode, uchar bySectionCode)
	{
		m_PostCode = (int32) ((byProvinceCode << 16) | (byCityCode << 8) | bySectionCode);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	POSTCODE &operator=(const POSTCODE &value)
	{
		this->m_PostCode = value.m_PostCode;
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	POSTCODE &operator=(const int32 &value)
	{
		this->m_PostCode = value;
		return *this;
	}
};
struct SHorseGuid
{
	SHorseGuid()
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SHorseGuid&operator=(const SHorseGuid&val)
	{
		m_uHighSection = val.m_uHighSection;
		m_uLowSection = val.m_uLowSection;
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(const SHorseGuid&val) const
	{
		if(m_uHighSection == val.m_uHighSection && m_uLowSection == val.m_uLowSection)
		{
			return TRUE;
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator!=(const SHorseGuid&val) const
	{
		if(m_uHighSection != val.m_uHighSection || m_uLowSection != val.m_uLowSection)
		{
			return TRUE;
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsNull(void) const
	{
		if(!m_uHighSection && !m_uLowSection)
		{
			return TRUE;
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(const GUID_t &GUID, uint32 CurTime)
	{
		m_uHighSection = GUID;
		m_uLowSection = CurTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Reset(void)
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetHighSection(void) const
	{
		return m_uHighSection;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetLowSection(void) const
	{
		return m_uLowSection;
	}

	static uint32 GetSize()
	{
		return sizeof(uint32) + sizeof(uint32);
	}

	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream) const;

	uint32	m_uHighSection;
	uint32	m_uLowSection;
};

#define DUEL_APPLY_PERSIST_TIME 60000
struct _DUEL_DATA
{
public:
	ObjID_t nOpponentId;
	GUID_t	OpponentGUID;
	int32	nDuelAreaId;
	MapID_t nSceneId;
	uint32	nStartTime;
	int32	nOpLevel;

	_DUEL_DATA()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		nOpponentId = INVALID_ID;
		OpponentGUID = INVALID_GUID;
		nDuelAreaId = -1;
		nStartTime = 0;
		nSceneId = INVALID_ID;
		nOpLevel = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_DUEL_DATA &operator=(const _DUEL_DATA &in)
	{
		nOpponentId = in.nOpponentId;
		OpponentGUID = in.OpponentGUID;
		nDuelAreaId = in.nDuelAreaId;
		nStartTime = in.nStartTime;
		nSceneId = in.nSceneId;
		nOpLevel = in.nOpLevel;
		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(const _DUEL_DATA &in)
	{
		if
		(
			OpponentGUID != in.OpponentGUID
		&&	nOpponentId != in.nOpponentId
		&&	nDuelAreaId != in.nDuelAreaId
		&&	nSceneId != in.nSceneId
		) return FALSE;
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator!=(const _DUEL_DATA &in)
	{
		return !(*this == in);
	}

	uint32 GetSize() const
	{
		return sizeof(nOpponentId)+
			sizeof(OpponentGUID) + 
			sizeof(nDuelAreaId) + 
			sizeof(nSceneId) + 
			sizeof(nStartTime)+
			sizeof(nOpLevel);
	}


};

struct SCampData
{
	enum { struct_size = sizeof (CampID_t) *2 +sizeof (int32) *2 };

	CampID_t m_nCampID;
	CampID_t m_uPKMode;
	int32 m_nReserve1;
	int32 m_nReserve2;

	SCampData (void)
	{
		m_nCampID = -1;
		m_uPKMode = 0;
		m_nReserve1 = -1;
		m_nReserve2 = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		m_nCampID = -1;
		m_uPKMode = 0;
		m_nReserve1 = -1;
		m_nReserve2 = -1;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CampID_t GetCampID() const
	{
		return m_nCampID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetPKMode() const
	{
		return m_uPKMode;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPKMode(int32 nMode)
	{
		m_uPKMode = nMode;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator==(const SCampData &in)
	{
		if(m_nCampID != in.m_nCampID || m_uPKMode != in.m_uPKMode)
		{
			return FALSE;
		}

		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL operator!=(const SCampData &in)
	{
		if(m_nCampID != in.m_nCampID || m_uPKMode != in.m_uPKMode)
		{
			return TRUE;
		}

		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SCampData &operator=(const SCampData &in)
	{
		if(&in != this)
		{
			m_nCampID = in.m_nCampID;
			m_uPKMode = in.m_uPKMode;
		}

		return *this;
	}

	uint32	GetSize() const
	{
		return sizeof(m_nCampID) + sizeof(m_uPKMode) + sizeof(m_nReserve1) + sizeof(m_nReserve2);
	}

};

struct _HUMAN_CAMP_DATA :
	public SCampData
{
public:
	ObjID_t		nObjId;
	int32		nLevel;
	ScriptID_t	nSceneID;
	int32		nSceneSafeLevel;
	int32		nSceneRestrictiveMode;
	GuildID_t	nGuildID;
	TeamID_t	nTeamID;
	char		nSafeArea;
	CampID_t	nSafeArea_CampID;
	_DUEL_DATA	m_duelData;

	_HUMAN_CAMP_DATA (void)
	:
	SCampData()
	{
		Clear();
	}
	_HUMAN_CAMP_DATA (const SCampData *in)
	{
		if(in)
		{
			m_nCampID = in->m_nCampID;
			m_uPKMode = in->m_uPKMode;
		}
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		nObjId = INVALID_ID;
		nLevel = INVALID_ID;
		nSceneID = INVALID_ID;
		nSceneSafeLevel = INVALID_ID;
		nSceneRestrictiveMode = INVALID_ID;
		nGuildID = INVALID_ID;
		nTeamID = INVALID_ID;
		nSafeArea = INVALID_ID;
		nSafeArea_CampID = INVALID_CAMP;
		m_duelData.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_HUMAN_CAMP_DATA &operator=(const SCampData *in)
	{
		if(in)
		{
			m_nCampID = in->m_nCampID;
			m_uPKMode = in->m_uPKMode;
			Clear();
		}

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_HUMAN_CAMP_DATA &operator=(const _HUMAN_CAMP_DATA &in)
	{
		nObjId = in.nObjId;
		m_nCampID = in.m_nCampID;
		m_uPKMode = in.m_uPKMode;
		nLevel = in.nLevel;
		nSceneID = in.nSceneID;
		nSceneSafeLevel = in.nSceneSafeLevel;
		nGuildID = in.nGuildID;
		nTeamID = in.nTeamID;
		m_duelData = in.m_duelData;
		return *this;
	}
};

#define MAX_RESERVE	10

struct GUID_TYPE
{
	GUID_TYPE()
	{
		Clear();
	}
	GUID_t	m_nGuid;
	int32	m_nType;
	void	Clear()
	{
		m_nGuid = INVALID_GUID;
		m_nType = RELATION_TYPE_STRANGER;
	}

};

struct SArchiveLoader_Player
{
	BOOL		m_bFirstEnterScence;
	int32		m_PortraitID;
	char		m_Name[MAX_CHARACTER_NAME];
	char		m_Title[MAX_CHARACTER_TITLE];
	GUID_t		m_GUID;
	uchar		m_Sex;
	uint32		m_CreateDate;
	STitle		m_Titles;
	int32		m_Level;
	int32		m_Vigor;
	int32		m_MaxVigor;
	int32		m_VigorRegeneRate;
	int32		m_Energy;
	int32		m_MaxEnergy;
	int32		m_EnergyRegeneRate;
	uint64		m_Exp;
	int32		m_Siller;
	int32		m_Gold;
	int32		m_BindSiller;
	int32		m_BindGold;
	uchar		m_MoneyMode;
	int32		m_nGoodBadValue;
	char		m_Passwd[MAX_PWD];
	uchar		m_uPwdFlag;
	uint32		m_uPwdDelTime;
	uchar		m_cLastProtectTime;
	uchar		m_cProtectTime;
	uint32		m_uProtectDelTime;
	uint32		m_HairColor;
	uchar		m_FaceColor;
	uchar		m_HairModel;
	uchar		m_FaceModel;
	int32		m_SoulID;
	uint32		m_GemAff;
	uint32		m_SetSuit;
	uint32		m_LevelAff;

	MapID_t		m_StartScene;
	MapID_t		m_BakScene;
	MapID_t		m_NextScene;
	GuildID_t	m_GuildID;
	int32		m_FamilyID;
	int32		m_nGuildOfficial;
	int32		m_nGP;
	int32		m_nMerit;	//帮会功德
	int32		m_nHonor;
	uint32_t		m_nInherenceExp;
	uint16_t		m_nInherenceLevel;
	TeamID_t	m_TeamID;
	GLPos	m_Position;
	GLPos	m_BakPosition;
	GLPos	m_NextPosition;
	uint32_t		m_OnlineTime;
	uint32_t		m_OnlineTimeToday;
	uint32_t		m_LastLoginTime;
	uint32_t		m_LastLogoutTime;
	uint32_t		m_LeftDieTime;
	uint32_t		m_DBVersion;
	uint32_t		m_LeaveGuildTime;
	BusID_t		m_BusID;

	uint16_t		m_nWenCai;
	int32		m_nRongYu;
	int32		m_nShengWang;
	int32		m_nHotValue;
	uint16_t		m_nKillCountToday;
	uint16_t		m_nPVP2V2_Level;
	uint16_t		m_nPVP2V2_Mark;
	int32		m_nPVP2V2_Day;
	int32		m_nPVP2V2_Mark_WeekTotal;

	SCampData	m_CampData;
	int32		m_nCountry;
	int32		m_nProfession;
	int32		m_HP;
	int32		m_MP;
	int32		m_StrikePoint;
	int32		m_Rage;
	int32		m_nPKValue;
	SHorseGuid	m_guidCurrentPet;
	_PROPERTY_LEVEL1	m_BaseAttrLevel1;
	int32		m_Level1Points;
	int32		m_RemainSkillPoints;
	int32		m_S_SkillPoints[COMMON_S_NUMBER];

	int32		m_nCountryOfficial;

	int32		m_LastForbidChatTime;
	int32		m_LastEnjailTime;

	uchar		m_cGuildBuild_Count;
	int32		m_nGuildBuild_Day;

	int32		m_nLastChgPKModeTime;

	int32		m_Reserve[MAX_RESERVE];
	BOOL		m_IsDelChar;
	int32		m_nWallowOnlineTime;
	int32		m_nWallowOfflineTime;
	int32		m_nTotalOnlineTime;
	int32		m_nTotalOfflineTime;
	int32		m_nIsNeedRename;
	char		m_szNewName[MAX_CHARACTER_NAME];
	uint32		m_TiredTime;
	int32		m_nDuelMark;
	uint32		m_uDBFlag;
	int32		m_nExploit;		//功勋
	int16		m_nExploitDay;
	ID_t		m_nPlayerWorldID;
	int32		m_MountModelID;

	SArchiveLoader_Player()
	{
		Clear();
	};
	void	Clear();

	int32	FillCrcData(char *buffer);
};

struct SArchiveLoader_Bank
{
	SItem	m_pItem[MAX_BANK_SIZE];
	int32	m_Count;
	uchar	m_CurEndIndex;
	int32	m_Money;
	SArchiveLoader_Bank()
	{
		Clear();
	};
	void	Clear();

	int32	FillCrcData(char *buffer);
};

struct SArchiveLoader_Bag
{
	friend class	PlayerArchive;

	SItem		m_pItem[MAX_BAG_SIZE];

	int32		m_BaseBagSize;

	int32		m_Count;

	SArchiveLoader_Bag()
	{
		Clear();
	};
	void	Clear();

	int32	FillCrcData(char *buffer);
private:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const SItem *GetBagDB(uint32 iBagIndex) const
	{
		KCheck(iBagIndex < MAX_BAG_SIZE);
		return &m_pItem[iBagIndex];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void PutBagDB(const SItem *pItem, uint32 iBagIndex)
	{
		KCheck(iBagIndex < MAX_BAG_SIZE);
		KCheck(pItem);

		memcpy(&m_pItem[iBagIndex], pItem, sizeof(SItem));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SwapBagDB(uint32 iAIndex, uint32 iBIndex)
	{
		KCheck(iAIndex < MAX_BAG_SIZE);
		KCheck(iBIndex < MAX_BAG_SIZE);

		SwapItem(&m_pItem[iAIndex], &m_pItem[iBIndex]);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IncCount(uint32 iBagIndex)
	{
		return m_pItem[iBagIndex].IncCount();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL DecCount(uint32 iBagIndex)
	{
		return m_pItem[iBagIndex].DecCount();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetItemBind(uint32 iBagIndex, BOOL bBind)
	{
		m_pItem[iBagIndex].SetItemBindType(bBind);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetItemDurability(uint32 BagIndex, int32 Dur)
	{
		m_pItem[BagIndex].GetEquipData()->m_CurDurPoint = Dur;
	}
};

struct SArchiveLoader_Equip
{
	SItem	m_pItem[HEQUIP_NUMBER];

	uint16	m_Flags;

	SArchiveLoader_Equip()
	{
		Clear();
	};
	void	Clear();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BOOL IsSet(PLAYER_EQUIP eEquip) const
	{
		return(m_Flags & (1 << (int32) eEquip)) ? (TRUE) : (FALSE);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Set(PLAYER_EQUIP eEquip, uchar bMark)
	{
		if(bMark)
			m_Flags |= (1 << (int32) eEquip);
		else
			m_Flags &= (~(1 << (int32) eEquip));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	const SItem *GetEquipDB(PLAYER_EQUIP EquipPoint)
	{
		return &m_pItem[EquipPoint];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetEquipDur(PLAYER_EQUIP EquipPoint, int32 Dur)
	{
		m_pItem[EquipPoint].GetEquipData()->m_CurDurPoint = Dur;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void PutEquipDB(const SItem *pItem, PLAYER_EQUIP EquipPoint)
	{
		KCheck(pItem);

		if(m_pItem[EquipPoint].IsNullType())
			memcpy(&m_pItem[EquipPoint], pItem, sizeof(SItem));
		else
		{
			KCheck(FALSE);
		}
	}

	int32	FillCrcData(char *buffer);
};

struct SArchiveLoader_Skill
{
	char		m_aPrescr[MAX_CHAR_PRESCRIPTION_BYTE];
	_PLAYER_ABILITY	m_aABility[MAX_CHAR_ABILITY_NUM];

	SArchiveLoader_Skill()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_PLAYER_ABILITY &Get_Ability(SpellID_t id)
	{
		int32	idx;
		idx = (int32) id;
		KCheck(idx > -1 && idx < MAX_CHAR_ABILITY_NUM);
		return m_aABility[idx];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_PLAYER_ABILITY Get_Ability(SpellID_t id) const
	{
		int32	idx;
		idx = (int32) id;
		KCheck(idx > -1 && idx < MAX_CHAR_ABILITY_NUM);
		return m_aABility[idx];
	}

	void	Clear();
};
typedef struct SArchiveLoader_Skill	_ABILITY_LIST;

struct SArchiveLoader_Spell
{
	uchar		m_Count;
	_PLAYER_SPELL	m_aSkill[MAX_CHAR_SKILL_NUM];

	SArchiveLoader_Spell()
	{
		Clear();
	}
	void	Clear();

	int32	FillCrcData(char *buffer);
};
typedef struct SArchiveLoader_Spell	_SPELL_LIST;

struct _Monster_Pet_DB
{
	_Monster_Pet_DB_Struct	m_aMonsterPet[MAX_MONSTER_PET_TAKE];
	_Monster_Pet_DB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, -1, sizeof(_Monster_Pet_DB));
	}
};
typedef struct _Monster_Pet_DB	SArchiveLoader_MonsterPet;

typedef struct SArchiveLoader_Effect
{
	uchar		m_Count;
	_OWN_EFFECT_DB	m_aImpacts[MAX_IMPACT_NUM];

	SArchiveLoader_Effect()
	{
		Clear();
	};
	void	Clear();
} _IMPACT_LIST_DB;

typedef struct _IMPACT_LOAD
{
	uchar		m_Count;
	uchar		m_VisableType[MAX_IMPACT_NUM];
	_OWN_EFFECT	m_aImpacts[MAX_IMPACT_NUM];

	_IMPACT_LOAD()
	{
		Clear();
	};
	void	Clear();
} _EFFECT_LIST;

#define PET_MAX_SKILL_COUNT	12
#define PET_MAX_APPER_COUNT	6

struct SHorseSkill
{
	SpellID_t	m_nSkillID;
	BOOL		m_bCanUse;

	SHorseSkill (void)
	{
		m_nSkillID = INVALID_ID;
		m_bCanUse = FALSE;
	}
	void	Clear(void);
};

struct _HORSE_DB_LOAD
{
	enum PET_TYPE { PET_TYPE_INVALID = -1, PET_TYPE_BABY = 0, PET_TYPE_VARIANCE, PET_TYPE_WILENESS, };
	enum PET_STATUS { PET_STATUS_INVALID = -1, PET_STATUS_NULL = 0, PET_STATUS_MOUNT, PET_STATUS_MATING, PET_STATUS_COMPOSE, };

	enum PET_AI_TYPE
	{
		PET_AI_INVALID		= -1,
		PET_AI_COWARDICE	= 0,
		PET_AI_WARINESS,
		PET_AI_LOYALISM,
		PET_AI_CANNINESS,
		PET_AI_VALOUR,
	};

	SHorseGuid	m_GUID;

	int32		m_nDataID;
	char		m_szName[MAX_CHARACTER_NAME];
	char		m_szNick[MAX_NICK_NAME];
	int32		m_nLevel;
	int32		m_nTakeLevel;
	int32		m_nAttackType;
	int32		m_AIType;
	SCampData	m_CampData;

	uchar		m_byGeneration;
	uchar		m_byHappiness;

	float		m_fGrowRate;

	int32		m_iStrengthPerception;
	int32		m_iSmartnessPerception;
	int32		m_iMindPerception;
	int32		m_iConstitutionPerception;

	int32		m_iStrengthPoint;
	int32		m_iSmartnessPoint;
	int32		m_iMindPoint;
	int32		m_iConstitutionPoint;

	int32		m_nRemainPoint;
	uint32		m_nExp;
	int32		m_iModelID;
	_PROPERTY_LEVEL1	m_BaseAttrLevel1;

	SHorseSkill	m_SkillList[PET_MAX_SKILL_COUNT];

	int32		m_iStatus;
	uint32		m_uHappinessLeftTime;
	int32		m_iStallOrder;

	uchar		m_byLock;
	uint32		m_UnLockTime;

	_HORSE_DB_LOAD()
	{
		Clear();
	}
	void	Clear(void);
};

typedef _HORSE_DB_LOAD	_HORSE_DB;

#define PLAYER_PET_MAX_COUNT	(6)
#define PLAYER_BANKPET_MAX_COUNT (5)

enum
{
	PET_INDEX_INVALID	= -1,
	PET_INDEX_SELF_BEGIN,
	PET_INDEX_SELF_2,
	PET_INDEX_SELF_3,
	PET_INDEX_SELF_4,
	PET_INDEX_SELF_5,
	PET_INDEX_SELF_6,
	PET_INDEX_SELF_NUMBERS,
	TARGETPET_INDEX		= 100,
};

struct _HORSE_DB_LIST_LOAD
{
	_HORSE_DB_LOAD	m_aPetDB[PLAYER_PET_MAX_COUNT];

	void		Clear(void);

	int32		FillCrcData(char *buffer);
};
typedef _HORSE_DB_LIST_LOAD	_HORSE_DB_LIST;

struct _BANKPET_DB_LIST_LOAD
{
	_BANKPET_DB_LIST_LOAD()
	{
		Clear();
	}
	_HORSE_DB_LOAD	m_aPetDB[PLAYER_BANKPET_MAX_COUNT];
	uint32		m_uValidCount;

	void		Clear(void);
};

#define MAX_QUEST_PARAM_NUM	(8)
struct OWN_QUEST
{
	QuestID_t	m_idQuest;
	ScriptID_t	m_idScript;

	uchar		m_yFlags;
	union
	{
		uint32	m_aParam[MAX_QUEST_PARAM_NUM];
		float	m_afParam[MAX_QUEST_PARAM_NUM];
		int32	m_anParam[MAX_QUEST_PARAM_NUM];
		BOOL	m_abParam[MAX_QUEST_PARAM_NUM];
	};

	OWN_QUEST( void )
	{
		Clear(); 
	}


	uint32 GetMsgSize( void )const
	{
		return sizeof(QuestID_t) + sizeof(ScriptID_t) + sizeof(uchar) + sizeof(uint32)*MAX_QUEST_PARAM_NUM;
	}

	void operator = ( const OWN_QUEST & ownquest )
	{
		this->m_idQuest = ownquest.m_idQuest;
		this->m_idScript = ownquest.m_idScript;
		this->m_yFlags = ownquest.m_yFlags;
		memcpy(this->m_aParam, ownquest.m_aParam,sizeof(uint32)*MAX_QUEST_PARAM_NUM);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		m_idScript = INVALID_ID;
		m_idQuest = INVALID_ID;
		m_yFlags = 0;
		memset(m_aParam, 0, sizeof(m_aParam));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsActiveQuest() const
	{
		if(m_idQuest != INVALID_ID && m_idScript != INVALID_ID)
			return TRUE;
		else
			return FALSE;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetFlags_KillObject(BOOL bSet)
	{
		(bSet) ? (m_yFlags |= 0x00000001) : (m_yFlags &= ~0x00000001);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsFlags_KillObject(void) const
	{
		return(m_yFlags & 0x00000001) != 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFlags_EnterArea(BOOL bSet)
	{
		(bSet) ? (m_yFlags |= (0x00000001 << 1)) : (m_yFlags &= ~(0x00000001 << 1));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsFlags_EnterArea(void) const
	{
		return(m_yFlags & (0x00000001 << 1)) != 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFlags_ItemChanged(BOOL bSet)
	{
		(bSet) ? (m_yFlags |= (0x00000001 << 2)) : (m_yFlags &= ~(0x00000001 << 2));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsFlags_ItemChanged(void) const
	{
		return(m_yFlags & (0x00000001 << 2)) != 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFlags_PetChanged(BOOL bSet)
	{
		(bSet) ? (m_yFlags |= (0x00000001 << 3)) : (m_yFlags &= ~(0x00000001 << 3));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsFlags_PetChanged(void) const
	{
		return(m_yFlags & (0x00000001 << 3)) != 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetFlags_ClickNPC(BOOL bSet)
	{
		(bSet) ? (m_yFlags |= (0x00000001 << 4)) : (m_yFlags &= ~(0x00000001 << 4));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsFlags_ClickNPC(void) const
	{
		return(m_yFlags & (0x00000001 << 4)) != 0;
	}
};

struct SArchiveLoader_Quest
{
	SArchiveLoader_Quest()
	{
		Clear();
	}
	void		Clear();

	uchar		m_Count;
	OWN_QUEST	m_aQuest[MAX_CHAR_QUEST_NUM];
	uint32		m_aQuestHaveDoneFlags[MAX_CHAR_QUEST_FLAG_LEN];
	int32		m_aQuestData[MAX_CHAR_QUEST_DATA_NUM];
};
typedef struct SArchiveLoader_Quest	QUEST_LIST;

struct OWN_QUEST_REFRESH
{
	union
	{
		uint32	m_aParam[MAX_QUEST_PARAM_NUM];
		float	m_afParam[MAX_QUEST_PARAM_NUM];
		int32	m_anParam[MAX_QUEST_PARAM_NUM];
		BOOL	m_abParam[MAX_QUEST_PARAM_NUM];
		void	*m_apParam[MAX_QUEST_PARAM_NUM];
	};
};
struct QUEST_LIST_REFRESH
{
	OWN_QUEST_REFRESH	m_aQuestRefresh[MAX_CHAR_QUEST_NUM];		/* 角色所接的任务信息 */
	int32			m_aQuestData[MAX_CHAR_QUEST_DATA_NUM];		/* 角色身上的任务自定义数据 */
	uint32			m_aQuestHaveDoneFlags[MAX_CHAR_QUEST_FLAG_LEN]; /* 角色的任务完成标志 */
public:
	QUEST_LIST_REFRESH (void)
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		memset(this, 0, sizeof(QUEST_LIST_REFRESH));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void InitQuest(const SArchiveLoader_Quest *pQuest)
	{
		if(!pQuest)
		{
			KCheckEx(FALSE, "Invalid pointer!");
			return;
		}

		for(uint32 i = 0; i < MAX_CHAR_QUEST_NUM; ++i)
			memcpy(m_aQuestRefresh[i].m_anParam, pQuest->m_aQuest->m_anParam, sizeof(OWN_QUEST_REFRESH));

		memcpy(m_aQuestData, pQuest->m_aQuestData, sizeof(m_aQuestData));
		memcpy(m_aQuestHaveDoneFlags, pQuest->m_aQuestHaveDoneFlags, sizeof(m_aQuestHaveDoneFlags));
	}
};

struct SArchiveLoader_Relationship
{
	struct OTHER_RELATION
	{
		SMarriageInfo	m_MarriageInfo;
		SPrenticeInfo	m_PrenticeInfo;
		SMasterInfo	m_MasterInfo;
		Time_t		m_SendGiftTime;
		uchar		m_SendTimes;
		int32		m_nPatrolID;
		int32		m_nCurrentPathNode;

		OTHER_RELATION()
		{
			Clear();
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void Clear()
		{
			m_MarriageInfo.Clear();
			m_PrenticeInfo.Clear();
			m_MasterInfo.Clear();
			m_SendGiftTime = 0;
			m_SendTimes = 0;
			m_nPatrolID = 0;
			m_nCurrentPathNode = 0;
		}
	};

	OTHER_RELATION	m_otherRelation;
	SArchiveLoader_Relationship()
	{
		Clear();
	};
	void	Clear();
};

#define HONOR_RECORD_MAX	10
struct SArchiveLoader_Honor
{
	struct _HONOR_RECORD
	{
		_HONOR_RECORD()
		{
			Clear();
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void Clear(void)
		{
			m_nPlayerGuid = INVALID_GUID;
			m_nFirstKillTime = 0;
			m_nTimes = 0;
		}

		/*
		 =======================================================================================================
		 =======================================================================================================
		 */
		void Init(const _HONOR_RECORD *pSrc)
		{
			m_nPlayerGuid = pSrc->m_nPlayerGuid;
			m_nFirstKillTime = pSrc->m_nFirstKillTime;
			m_nTimes = pSrc->m_nTimes;
		}

		GUID_t	m_nPlayerGuid;
		Time_t	m_nFirstKillTime;
		uchar	m_nTimes;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear(void)
	{
		for(int32 i = 0; i < HONOR_RECORD_MAX; ++i)
		{
			m_anHonor[i].Clear();
		}

		m_nHonorDay = 0;
		m_nHonorNum = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(const SArchiveLoader_Honor *pSrc)
	{
		KCheck(pSrc);
		for(int32 i = 0; i < HONOR_RECORD_MAX; ++i)
		{
			m_anHonor[i].Init(&pSrc->m_anHonor[i]);
		}

		m_nHonorDay = pSrc->m_nHonorDay;
		m_nHonorNum = pSrc->m_nHonorNum;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_HONOR_RECORD *GetRecord(int32 nIndex)
	{
		if(nIndex >= 0 && nIndex < HONOR_RECORD_MAX)
		{
			return &m_anHonor[nIndex];
		}

		return NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL AddRecord(const _HONOR_RECORD *pRecord)
	{
		if(IsFull()) return FALSE;
		for(int32 i = 0; i < HONOR_RECORD_MAX; ++i)
		{
			if(m_anHonor[i].m_nPlayerGuid == INVALID_GUID)
			{
				m_anHonor[i].Init(pRecord);
				break;
			}
		}

		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsFull(void) const
	{
		for(int32 i = 0; i < HONOR_RECORD_MAX; ++i)
		{
			if(m_anHonor[i].m_nPlayerGuid == INVALID_GUID)
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	_HONOR_RECORD	m_anHonor[HONOR_RECORD_MAX];
	int32		m_nHonorDay;
	int32		m_nHonorNum;
};

#define MAX_SETTING_DATA	68

struct _PLAYER_SETTING
{
	uchar	m_SettingType;
	int32	m_SettingData;

	_PLAYER_SETTING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_SettingType = 0;
		m_SettingData = 0;
	}


    static int32 GetSize()
    {
        return ( sizeof( uchar) + sizeof( int32) );
    }

};

#define MAX_SUIT_SETTING	10
#define MAX_SUIT_NAME_SIZE	12
struct _SUIT_SETTING
{
	char		m_SuitName[MAX_SUIT_NAME_SIZE];
	SItemGuid	m_EquipData[HEQUIP_NUMBER];

	_SUIT_SETTING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(m_SuitName, 0, sizeof(char) * MAX_SUIT_NAME_SIZE);
		memset(m_EquipData, 0, SItemGuid::GetSize() * HEQUIP_NUMBER);
	}


	static uint32 GetSize()
	{
		return sizeof(char) * MAX_SUIT_NAME_SIZE + SItemGuid::GetSize() * HEQUIP_NUMBER;
	}

	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream) const;
};

struct _SUBTRAIN_SETTING
{
	BOOL	m_bSubTrainOpen;
	int32	m_SubTrainMode;
	uint32	m_SubTrainBeginTime;
	uint32	m_SubTrainMoney;
	uint32	m_SubTrainExper;
	uint32	m_SubTrainExpRate;
	uint32	m_SubTrainMoneyRate;
	_SUBTRAIN_SETTING()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_bSubTrainOpen = FALSE;
		m_SubTrainMode = SUBTRAIN_MODE1;
		m_SubTrainBeginTime = 0;
		m_SubTrainMoney = 0;
		m_SubTrainExper = 0;
		m_SubTrainExpRate = 0;
		m_SubTrainMoneyRate = 0;
	}

	static uint32 GetSize()
	{
		return 
			sizeof(BOOL) +
			sizeof(int32) +
			sizeof(uint32) * 5;
	}

	void Send(SendStream &oStream) const;
	void Reci(RecieveStream &iStream);
};

struct SArchiveLoader_Setting
{
    //! 客户端快捷栏和扩展快捷栏配置
	_PLAYER_SETTING		m_aSetting[MAX_SETTING_DATA];
    //! 套装(一键换装)配置
	_SUIT_SETTING		m_SuitSetting[MAX_SUIT_SETTING];
	_SUBTRAIN_SETTING	m_SubTrainSetting;
	uint32			m_FlagGameSetting;
	SArchiveLoader_Setting()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		for(int32 i = 0; i < MAX_SETTING_DATA; i++)
		{
			m_aSetting[i].Clear();
		}

		for(int32 i = 0; i < MAX_SUIT_SETTING; ++i)
		{
			m_SuitSetting[i].Clear();
		}

		m_SubTrainSetting.Clear();
		m_FlagGameSetting = 0xffffffff;
	}
};

typedef struct SArchiveLoader_Setting _SETTING_LIST;

struct SArchiveLoader_PrivateInfo
{
	uchar	m_InfoType;
	uint32	m_CharGUID;
	uchar	m_Age;
	uchar	m_Sex;
	char	m_JobInfo[MAX_JOBINFO_LENGTH];
	char	m_SchoolInfo[MAX_SCHOOLINFO_LENGTH];
	uchar	m_BloodType;
	uchar	m_YearAnimal;
	uchar	m_Consella;
	int32	m_PostCode;
	char	m_EmailInfo[MAX_EMAIL_LENGTH];
	char	m_LuckWord[MAX_LUCKWORD_LENGTH];
	uchar	m_Birth_Month;
	uchar	m_Birth_Day;
	char	m_HomePage[MAX_HOME_PAGE_LENGTH];
	char	m_QQ[MAX_QQ_LENGTH];
	char	m_MSN[MAX_MSN_LENGTH];
	SArchiveLoader_PrivateInfo()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
		m_CharGUID = INVALID_ID;
		m_PostCode = INVALID_ID;
		m_Age = INVALID_ID;
	}
};

struct PLAYER_DB_ATTR_FLAG
{
	PLAYER_DB_ATTR_FLAG()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsUpdated(int32 BitOffSet)
	{
		if(m_Flags[BitOffSet / 8] & (1 << (BitOffSet % 8))) return TRUE;
		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetBitFlag(int32 BitOffSet, BOOL bValue)
	{
		if(bValue)
			m_Flags[BitOffSet / 8] |= (1 << (BitOffSet % 8));
		else
			m_Flags[BitOffSet / 8] &= (~(1 << (BitOffSet % 8)));
	}

	char	m_Flags[HUMAN_DB_ATTR_FLAG_LENGTH];
};

struct PLAYER_DB_ATTR_REG
{
	PLAYER_DB_ATTR_REG()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}

	void	*m_AttrPtr[CPROPERTY_ARCHIVE_NUMBER];
	int32	m_AttrSize[CPROPERTY_ARCHIVE_NUMBER];
};

struct _SOLDITEM_DB_LOAD
{
	uint32	m_SoldPrice;
	uchar	m_SoldPriceType;
	SItem	m_ItemHasBeenSold;
};

struct SArchiveLoader_SoldList
{
	_SOLDITEM_DB_LOAD	m_list[MAX_BOOTH_SOLD_NUMBER];
	SArchiveLoader_SoldList()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		for(int32 i = 0; i < MAX_BOOTH_SOLD_NUMBER; ++i)
		{
			m_list[i].m_SoldPrice = 0;
			m_list[i].m_SoldPriceType = 0;
			m_list[i].m_ItemHasBeenSold.Clear();
		}
	}
};

struct SArchiveLoader_Player_ExtendInfo
{
	SPlayerShopFolder m_ShopItemFavorite;
	SPlayerShopFolder m_ShopItemBuyHistory;
	SPlayerInherenceBalance m_InherenceBalance;
	SPlayerInherenceZhanJing m_InherenceZhanJing;
	uint32 m_nBattleHonour;

	SArchiveLoader_Player_ExtendInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_ShopItemFavorite.Clear();
		m_ShopItemBuyHistory.Clear();
		m_InherenceBalance.Clear();
		m_InherenceZhanJing.Clear();
		m_nBattleHonour = 0;
	}
};

struct CHARDBNODE
{
	CHARDBNODE()
	{
		Clear();
	}
	SArchiveLoader_Player			m_Human;
	SArchiveLoader_Bank			m_Bank;
	SArchiveLoader_Bag			m_Bag;
	SArchiveLoader_Equip			m_Equip;
	SArchiveLoader_Spell			m_Skill;
	SArchiveLoader_CoolDown	m_CoolDownDB;
	SArchiveLoader_Effect			m_Impact;
	SArchiveLoader_Skill			m_Ability;
	SArchiveLoader_Quest			m_QuestDB;
	SArchiveLoader_Setting		m_Setting;
	_HORSE_DB_LIST_LOAD		m_PetList;
	SArchiveLoader_Relationship		m_Relation;
	SArchiveLoader_Honor		m_HonorRecord;
	SArchiveLoader_PrivateInfo		m_PrivateInfo;
	SArchiveLoader_SoldList		m_SoldList;
	_BANKPET_DB_LIST_LOAD		m_BankPetList;
	SArchiveLoader_Player_ExtendInfo m_PlayerExtendInfo;


	BOOL				m_bIsPasswdUnlock;
	BOOL				m_bIsLoginProtectUnlock;
	BOOL				m_bChangeScence;
	uint32				m_LoginProtectTime;
	SArchiveLoader_MonsterPet			m_dbMonsterPet;
	SHorseGuid			m_guidCurrentHorse;
	SHorseGuid			m_guidLastHorse;
	int32				m_RuntimeData[MAX_RUNTIME_DATA];

	uchar				m_OnlinePasswdErrorCount;
	uint32				m_AccountGold;
	FightInfo			m_aFightInfo[FIGHT_INFO_NUM];
	int32				m_nWallowNotifyFlag;
	_DUEL_DATA			m_DuelData;
	uint32				m_nChatReport_LastTime;

	uint32				m_uCrc;
	uchar				m_LoginAnswer;
	uint32				m_VipLevel;
	BOOL				m_IsBindPWCard;
	BOOL				m_IsBindPhone;

	char				m_szGuildName[MAX_GUILD_NAME_SIZE];
	char				m_szFamilyName[MAX_GUILD_FAMILY_NAME_SIZE];

	GUID_TYPE	m_anHaveSendDetailInfo[MAX_RELATION_SIZE];
	BOOL		m_bActiveDetailRelationInfoHeartBeat;

	BOOL				m_IsEnableStockAccount;		//是否有效的股票账户

	BOOL		m_aMutexState[MS_NumOfMutexState];

	TeamInfo_ForChangeScene	m_TeamInfo;

	uint8				m_nMoveMode;
	uint32				m_nElapsedVigorRecoverTick;
	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_Human.Clear();
		m_Equip.Clear();
		m_Bag.Clear();
		m_Bank.Clear();
		m_Skill.Clear();
		m_CoolDownDB.Clear();
		m_Impact.Clear();
		m_Ability.Clear();
		m_QuestDB.Clear();
		m_Setting.Clear();
		m_PetList.Clear();
		m_Relation.Clear();
		m_HonorRecord.Clear();
		m_PrivateInfo.Clear();
		m_PlayerExtendInfo.Clear();
		m_dbMonsterPet.Clear();
		m_BankPetList.Clear();
		m_guidCurrentHorse.Reset();
		m_guidLastHorse.Reset();
		m_bChangeScence = FALSE;
		m_bIsPasswdUnlock = FALSE;
		m_LoginProtectTime = 0;
		m_bIsLoginProtectUnlock = FALSE;
		memset(m_RuntimeData, 0, sizeof(int32) * MAX_RUNTIME_DATA);
		m_OnlinePasswdErrorCount = 0;
		m_AccountGold = 0;
		m_LoginAnswer = LOGIN_ENCODE_SUCCESS;
		m_VipLevel = 0;
		for(int32 i = 0; i < FIGHT_INFO_NUM; ++i)
		{
			m_aFightInfo[i].Clear();
		}

		m_nWallowNotifyFlag = 0;
		m_nChatReport_LastTime = 0;
		m_uCrc = 0;
		m_IsBindPWCard = FALSE;
		m_IsBindPhone = FALSE;

		memset( m_szGuildName, 0, MAX_GUILD_NAME_SIZE );
		memset( m_szFamilyName, 0, MAX_GUILD_FAMILY_NAME_SIZE );

		for(int32 i = 0; i < MAX_RELATION_SIZE; ++i)
		{
			m_anHaveSendDetailInfo[i].Clear();
		}
		m_bActiveDetailRelationInfoHeartBeat = FALSE;
		m_IsEnableStockAccount = FALSE;
		memset(m_aMutexState, 0, sizeof(m_aMutexState));
		m_TeamInfo.Clear();
		m_nMoveMode = MOVE_MODE_RUN;
		m_nElapsedVigorRecoverTick = 0;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	SItem *GetItem(uint32 uDBPos)
	{
		KCheck(uDBPos <= DB_BANK_POS_END);

		if(uDBPos >= DB_BANK_POS_START)
		{
			return &m_Bank.m_pItem[uDBPos - DB_BANK_POS_START];
		}
		else if(uDBPos >= DB_EQUIP_POS_START)
		{
			return &m_Equip.m_pItem[uDBPos - DB_EQUIP_POS_START];
		}
		else if(uDBPos >= DB_BAG_POS_START)
		{
			return &m_Bag.m_pItem[uDBPos - DB_BAG_POS_START];
		}

		return NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_HORSE_DB_LOAD *GetPet(uint32 uDBPos)
	{
		__GUARD__;
		KCheck(uDBPos < PLAYER_PET_MAX_COUNT);
		return &m_PetList.m_aPetDB[uDBPos];
		__UNGUARD__;
		return NULL;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 FillCrcData(char *buffer)
	{
		int32	nStart = 0;

		nStart += m_Human.FillCrcData(buffer + nStart);
		nStart += m_Bank.FillCrcData(buffer + nStart);
		nStart += m_Bag.FillCrcData(buffer + nStart);
		nStart += m_Equip.FillCrcData(buffer + nStart);
		nStart += m_Skill.FillCrcData(buffer + nStart);
		nStart += m_PetList.FillCrcData(buffer + nStart);

		return nStart;
	}
};

#define SM_USE_FREE		0
#define SM_USE_READYFREE	1
#define SM_USE_FREEED		2
#define SM_USE_HOLDDATA		3
#define SM_USE_SENDFREE		4

struct MKHead
{
	uint32		PoolId;
	MKID_t		MKid;
	int32		UseStatus;
	atword		flag;
	ConnectorID_t	PID;
	uint32		SaveTime;

	MKHead()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		PoolId = -1;
		MKid = 0;
		PID = -1;
		UseStatus = SM_USE_FREE;
		initword(flag, SM_FREE);
		SaveTime = 0;
	}
};

struct PlayerMK
{
	MKHead				m_MKHead;
	PLAYER_DB_ATTR_FLAG		m_AttrFlag;
	SArchiveLoader_Player			m_PlayerSM;
	SArchiveLoader_Bank			m_BankSM;
	SArchiveLoader_Spell			m_SkillSM;
	SArchiveLoader_CoolDown	m_CoolDownDBShareMemory;
	SArchiveLoader_Effect			m_ImpactSM;
	SArchiveLoader_Skill			m_AbilitySM;
	SArchiveLoader_Quest			m_QuestDBShareMemory;
	SArchiveLoader_Setting		m_SettingSM;
	_HORSE_DB_LIST_LOAD		m_PetListSM;
	SArchiveLoader_Bag			m_BagSM;
	SArchiveLoader_Equip			m_EquipSM;
	SArchiveLoader_Relationship		m_RelationSM;
	SArchiveLoader_PrivateInfo		m_PrivateInfoSM;
	SArchiveLoader_SoldList		m_SoldList;
	SArchiveLoader_Honor		m_HonorRecordSM;
	_BANKPET_DB_LIST_LOAD		m_BankPetListSM;
	SArchiveLoader_Player_ExtendInfo	m_PlayerExtendInfoSM;

public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_MKHead.Clear();
		m_AttrFlag.Clear();
		m_PlayerSM.Clear();
		m_BankSM.Clear();
		m_SkillSM.Clear();
		m_CoolDownDBShareMemory.Clear();
		m_ImpactSM.Clear();
		m_AbilitySM.Clear();
		m_QuestDBShareMemory.Clear();
		m_SettingSM.Clear();
		m_PetListSM.Clear();
		m_BagSM.Clear();
		m_EquipSM.Clear();
		m_RelationSM.Clear();
		m_PrivateInfoSM.Clear();
		m_SoldList.Clear();
		m_HonorRecordSM.Clear();
		m_BankPetListSM.Clear();
		m_PlayerExtendInfoSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 SingleUseStatus()
	{
		return m_MKHead.UseStatus;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPlayerID(char Type, ConnectorID_t nID)
	{
		Lock(Type);
		m_MKHead.PID = nID;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ConnectorID_t GetPlayerID(char Type)
	{
		ConnectorID_t	id;
		Lock(Type);
		id = m_MKHead.PID;
		UnLock(Type);
		return id;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Copy2CharDBNode(char Type, CHARDBNODE *pData)
	{
		Lock(Type);

		KCheck(pData);
		memcpy(&pData->m_Ability, &m_AbilitySM, sizeof(m_AbilitySM));
		memcpy(&pData->m_Bag, &m_BagSM, sizeof(m_BagSM));
		memcpy(&pData->m_Bank, &m_BankSM, sizeof(m_BankSM));
		memcpy(&pData->m_CoolDownDB, &m_CoolDownDBShareMemory, sizeof(m_CoolDownDBShareMemory));
		memcpy(&pData->m_Equip, &m_EquipSM, sizeof(m_EquipSM));
		memcpy(&pData->m_Human, &m_PlayerSM, sizeof(m_PlayerSM));
		memcpy(&pData->m_Impact, &m_ImpactSM, sizeof(m_ImpactSM));
		memcpy(&pData->m_QuestDB, &m_QuestDBShareMemory, sizeof(m_QuestDBShareMemory));
		memcpy(&pData->m_Setting, &m_SettingSM, sizeof(m_SettingSM));
		memcpy(&pData->m_PetList, &m_PetListSM, sizeof(m_PetListSM));
		memcpy(&pData->m_Relation, &m_RelationSM, sizeof(m_RelationSM));
		memcpy(&pData->m_Skill, &m_SkillSM, sizeof(m_SkillSM));
		memcpy(&pData->m_PrivateInfo, &m_PrivateInfoSM, sizeof(m_PrivateInfoSM));
		memcpy(&pData->m_SoldList, &m_SoldList, sizeof(m_SoldList));
		memcpy(&pData->m_HonorRecord, &m_HonorRecordSM, sizeof(m_HonorRecordSM));
		memcpy(&pData->m_BankPetList, &m_BankPetListSM, sizeof(m_BankPetListSM));
		memcpy(&pData->m_PlayerExtendInfo, &m_PlayerExtendInfoSM, sizeof(m_PlayerExtendInfoSM));
		UnLock(Type);
	}
};

struct SMHead
{
	MK_VALUE	m_Key;
	uint32		m_Size;
	uint32		m_HeadVer;
	SMHead()
	{
		m_Key = 0;
		m_Size = 0;
		m_HeadVer = 0;
	}
};

struct SGuildSkillDB
{
	int32 m_iSkillID;
	int32 m_iSkillLevel;
	int32 m_iSkillLayer;

	SGuildSkillDB()
	{
		Clear();
	}

	void Clear()
	{
		m_iSkillID = INVALID_ID;
		m_iSkillLevel = 0;
		m_iSkillLayer = 0;
	}
};

struct SGuildUserDB
{
	GUID_t		m_UserGUID;
	char		m_szUserName[MAX_CHARACTER_NAME];
	eGUILD_POSITION_TYPE	m_Position;

	uint32		m_uLastLoginTime;
	uint32		m_uLevel;
	uchar		m_bProfessionID;
	int32		m_iCurContribute;
	int32		m_iMaxContribute;
	int32		m_iJoinTime;
	int32		m_iFamilyID;
	uchar		m_cSex;
	int32		m_nGP;
	char		m_szTitleName[MAX_CHARACTER_TITLE];
	int32		m_nMerit;

	int32		m_nActivity;							//活跃度
	int32		m_nLastActivity;						//上周活跃度

	SGuildUserDB()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_UserGUID = INVALID_ID;
		memset(m_szUserName, 0, sizeof(char) * MAX_CHARACTER_NAME);
		memset(m_szTitleName, 0, sizeof(char) * MAX_CHARACTER_TITLE);
		m_Position = GUILD_POSITION_TRAINEE;

		m_uLastLoginTime = 0;
		m_uLevel = 0;
		m_bProfessionID = INVALID_JOB;
		m_iCurContribute = 0;
		m_iMaxContribute = 0;
		m_iJoinTime = 0;
		m_iFamilyID = INVALID_ID;
		m_cSex = 3;
		m_nGP = 0;
		m_nMerit = 0;
		m_nActivity = 0;
		m_nLastActivity = 0;
	}
};

struct FAMILYUSER_DB
{
	int32	m_aFamilyLeader[GUILD_FAMILY_SIZE];
	int32	m_aFamilyUser[GUILD_FAMILY_SIZE][USER_FAMILY_SIZE];
	char	m_aFamilyName[GUILD_FAMILY_SIZE][MAX_GUILD_FAMILY_NAME_SIZE];
	char	m_aFamilyDesc[GUILD_FAMILY_SIZE][MAX_GUILD_FAMILY_DESC_SIZE];
	int32	m_aFamilyMemberCount[GUILD_FAMILY_SIZE];

	FAMILYUSER_DB()
	{
		Clear();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		for(int32 i = 0; i < GUILD_FAMILY_SIZE; ++i)
		{
			for(int32 j = 0; j < USER_FAMILY_SIZE; ++j)
			{
				m_aFamilyUser[i][j] = INVALID_ID;
			}

			m_aFamilyMemberCount[i] = 0;
			m_aFamilyLeader[i] = INVALID_ID;
		}

		memset(m_aFamilyName, 0, GUILD_FAMILY_SIZE * MAX_GUILD_FAMILY_NAME_SIZE);
		memset(m_aFamilyDesc, 0, GUILD_FAMILY_SIZE * MAX_GUILD_FAMILY_DESC_SIZE);
	}
};

struct SGuildDB
{
	GuildID_t	m_GuildID;
	char		m_GuildName[MAX_GUILD_NAME_SIZE];
	char		m_GuildDesc[MAX_GUILD_DESC_SIZE];
	char		m_GuildChiefName[MAX_CHARACTER_NAME];
	char		m_GuildAssChiefName[MAX_CHARACTER_NAME];
	char		m_GuildCreatorName[MAX_CHARACTER_NAME];
	uchar		m_GuildLevel;
	eGUILD_STATUS_CODE	m_Status;
	GUID_t		m_ChieftainGUID;
	GUID_t		m_AssChieftainGUID;
	int32		m_nMemberCount;
	int32		m_GuildPoint;
	uint32		m_uFamilyCount;
	int32		m_GuildMoney;
	SGuildUserDB	m_aGuildMember[USER_ARRAY_SIZE];
	CityID_t	m_CityID;
	int32		m_TotalGuildExp;
	int32		m_nFoundTime;
	int32		m_Longevity;
	int32		m_Contribute;
	int32		m_Honor;
	FAMILYUSER_DB	m_Familys;
	GuildConvoyList m_ConvoyList;
	int32		m_nLastModifyDescTime;
	int32		m_nLastModifyTitleTime;
	int32		m_nLastModifyFamilyNameTime;
	int32		m_aFreeParam[MAX_FREEPARAM_NUM];
	int32		m_nDestroyCountDown;
	int32		m_nCountryID;
	int32		m_nExpBuild_Count;
	int32		m_nExpBuild_Day;
	int32		m_nIsNeedRename;
	char		m_szNewGuildName[MAX_GUILD_NAME_SIZE];
	int32		m_nShiMing;											//帮会使命点
	uint32		m_uCrc;
	SGuildSkillDB	m_GuildSkill[MAX_GUILDSKILL_COUNT];					//帮会天赋修行技能
	int32		m_GuildSkillCount;


	SGuildDB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_GuildID = INVALID_ID;
		memset(m_GuildName, 0, MAX_GUILD_NAME_SIZE * sizeof(char));
		memset(m_GuildDesc, 0, MAX_GUILD_DESC_SIZE * sizeof(char));
		memset(m_GuildChiefName, 0, MAX_CHARACTER_NAME * sizeof(char));
		memset(m_GuildAssChiefName, 0, MAX_CHARACTER_NAME * sizeof(char));
		memset(m_GuildCreatorName, 0, MAX_CHARACTER_NAME * sizeof(char));

		m_ChieftainGUID = INVALID_ID;
		m_AssChieftainGUID = INVALID_ID;
		m_nMemberCount = 0;
		m_GuildPoint = 0;
		m_uFamilyCount = 0;
		m_TotalGuildExp = 0;
		m_GuildMoney = 0;
		m_Familys.Clear();

		/*~~~~~~*/
		int32	i;
		/*~~~~~~*/

		for(i = 0; i < USER_ARRAY_SIZE; i++)
		{
			m_aGuildMember[i].Clear();
		}

		m_CityID = INVALID_ID;
		m_nFoundTime = 0;
		m_Longevity = 0;
		m_Contribute = 0;
		m_Honor = 0;

		m_ConvoyList.Clear();
		m_GuildLevel = 0;
		m_nLastModifyDescTime = 0;
		m_nLastModifyTitleTime = 0;
		m_nDestroyCountDown = INVALID_ID;
		m_nCountryID = INVALID_ID;
		m_nExpBuild_Count = 0;
		m_nExpBuild_Day = 0;

		for(i = 0; i < MAX_FREEPARAM_NUM; ++i)
		{
			m_aFreeParam[i] = INVALID_ID;
		}

		m_nIsNeedRename = 0;
		memset(m_szNewGuildName, 0, sizeof(m_szNewGuildName));
		m_uCrc = 0;
		m_nShiMing = 0;
		
		for(i = 0; i < MAX_GUILDSKILL_COUNT; i++)
		{
			m_GuildSkill[i].Clear();
		}

		m_GuildSkillCount = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 FillCrcData(char *buffer)
	{
		int32	nStart = 0;

		memcpy(buffer + nStart, &m_GuildLevel, sizeof(m_GuildLevel));
		nStart += sizeof(m_GuildLevel);

		memcpy(buffer + nStart, &m_ChieftainGUID, sizeof(m_ChieftainGUID));
		nStart += sizeof(m_ChieftainGUID);

		memcpy(buffer + nStart, &m_AssChieftainGUID, sizeof(m_AssChieftainGUID));
		nStart += sizeof(m_AssChieftainGUID);

		memcpy(buffer + nStart, &m_GuildPoint, sizeof(m_GuildPoint));
		nStart += sizeof(m_GuildPoint);

		memcpy(buffer + nStart, &m_GuildMoney, sizeof(m_GuildMoney));
		nStart += sizeof(m_GuildMoney);

		memcpy(buffer + nStart, &m_TotalGuildExp, sizeof(m_TotalGuildExp));
		nStart += sizeof(m_TotalGuildExp);

		memcpy(buffer + nStart, &m_Longevity, sizeof(m_Longevity));
		nStart += sizeof(m_Longevity);

		memcpy(buffer + nStart, &m_Contribute, sizeof(m_Contribute));
		nStart += sizeof(m_Contribute);

		memcpy(buffer + nStart, &m_Honor, sizeof(m_Honor));
		nStart += sizeof(m_Honor);

		memcpy(buffer + nStart, &m_nCountryID, sizeof(m_nCountryID));
		nStart += sizeof(m_nCountryID);

		return nStart;
	}
};

enum GUILD_USE_STATS { GUILD_ADDNEW = 0, GUILD_DELETE, GUILD_SAVED, };

struct GuildMK
{
	MKHead		m_MKHead;
	SGuildDB	m_GuildSM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_GuildSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_GuildSM.Clear();
	}
};
enum eMAIL_USE_STATS { MAIL_ADDNEW = 0, MAIL_DELETE, MAIL_SAVED, };

struct MailMK
{
	MKHead m_MKHead;
	SMail	m_MailSM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_MailSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_MailSM.Clear();
	}
};

struct ItemSerialKeyMK
{
	MKHead m_MKHead;
	uint32	m_ItemSerial;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSerial(char Type)
	{
		uint32	Serial;
		Lock(Type);
		Serial = m_ItemSerial;
		UnLock(Type);

		return Serial;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSerial(char Type, uint32 Serial)
	{
		Lock(Type);
		m_ItemSerial = Serial;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_ItemSerial = 0;
	}
};

struct TopDataDB
{
	int32	m_TopListID;
	GUID_t	m_Guid;
	int32	m_Level;
	int32	m_Country;
	char	m_Name[MAX_CHARACTER_NAME];
	int16	m_Profession;
	char	m_GuildName[MAX_GUILD_NAME_SIZE];
	int32	m_iKeyValue;
	uint32	m_EnterDate;
	int32	m_Type;
	uint32	m_Place;    // 排名，从0开始
	char	m_TypeName[TOP_LIST_TYPENAME_LEN];

	TopDataDB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_TopListID = -1;
		m_Guid = INVALID_GUID;
		m_Level = 0;
		m_Country = -1;
		memset(m_Name, 0, sizeof(m_Name));
		m_Profession = -1;
		memset(m_GuildName, 0, sizeof(m_GuildName));
		m_iKeyValue = 0;
		m_EnterDate = 0;
		m_Type = -1;
		m_Place = 0;
		memset(m_TypeName, 0, sizeof(m_TypeName));
	}
};

enum TOP_USE_STATS { TOP_ADDNEW = 0, TOP_DELETE, TOP_SAVED, };

struct TopDataMK
{
	MKHead		m_MKHead;
	TopDataDB	m_TopDataSM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_TopDataSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_TopDataSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyFrom(_TOP_DATA &TopData)
	{
		TopData.m_Guid = m_TopDataSM.m_Guid;
		TopData.m_Country = m_TopDataSM.m_Country;
		TopData.m_iKeyValue = m_TopDataSM.m_iKeyValue;
		TopData.m_Level = m_TopDataSM.m_Level;
		TopData.m_Profession = m_TopDataSM.m_Profession;
		strncpy(TopData.m_Name, m_TopDataSM.m_Name, sizeof(TopData.m_Name));
		strncpy(TopData.m_GuildName, m_TopDataSM.m_GuildName, sizeof(TopData.m_GuildName));
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyTo(const _TOP_DATA &TopData)
	{
		m_TopDataSM.m_Guid = TopData.m_Guid;
		m_TopDataSM.m_Country = TopData.m_Country;
		m_TopDataSM.m_iKeyValue = TopData.m_iKeyValue;
		m_TopDataSM.m_Level = TopData.m_Level;
		m_TopDataSM.m_Profession = TopData.m_Profession;

		strncpy(m_TopDataSM.m_Name, TopData.m_Name, sizeof(m_TopDataSM.m_Name));
		strncpy(m_TopDataSM.m_GuildName, TopData.m_GuildName, sizeof(m_TopDataSM.m_GuildName));
	}
};

#define COUNTRY_MAX_OFFICERS_COUNT		6
#define COUNTRY_MAX_INTERVALCONTROLS_COUNT	26

struct Country_DB
{
	_COUNTRY_OFFICER	*m_pOfficers[COUNTRY_MAX_OFFICERS_COUNT];
	_IntervalControl::dbstruct * m_pIntervalControls[COUNTRY_MAX_INTERVALCONTROLS_COUNT];

	uchar				m_cCountryID;
	GUID_t				m_King;
	GUID_t				m_Challenger;
	char				m_szKing[MAX_CHARACTER_NAME];
	char				m_szChallenger[MAX_CHARACTER_NAME];
	char				m_szNotice[MAX_NOTICE_SIZE];
	int32				m_aFreeParam[MAX_FREEPARAM_NUM];
	GuildID_t			m_KingGuildID;
	GuildID_t			m_ChallengerGuildID;

	//add by wangzhiping for 青龙，朱雀国家帮
	GUID_t			m_arrCountryBangzhu[COUNTRY_GUILD_COUNT]; //国家帮会帮主guid
	char			m_arrCountryBangzhuName[COUNTRY_GUILD_COUNT][MAX_CHARACTER_NAME]; //国家帮会帮主名称
	GuildID_t		m_arrCountryGuild[COUNTRY_GUILD_COUNT]; //国家帮会list

	GUID_t			m_arrCountryBangzhu_Challenger[COUNTRY_GUILD_COUNT]; //国家帮会挑战帮主guid
	char			m_arrCountryBangzhuName_Challenger[COUNTRY_GUILD_COUNT][MAX_CHARACTER_NAME]; //国家帮会挑战帮主名称
	GuildID_t		m_arrCountryGuild_Challenger[COUNTRY_GUILD_COUNT]; //国家挑战帮会list
	//add end

	int32				m_nResource[COUNTRY_RESOURCE_COUNT];

	char				m_kingly_QiCheng_stat;
	char				m_kingly_Suit_stat;

	_COUNTRY_OFFICER		m_officer_Queen;
	_COUNTRY_OFFICER		m_officer_LMinister;
	_COUNTRY_OFFICER		m_officer_RMinister;
	_COUNTRY_OFFICER		m_officer_General;
	_COUNTRY_OFFICER		m_officer_LGuard;
	_COUNTRY_OFFICER		m_officer_RGuard;

	_IntervalControl::dbstruct	m_ctl_Fortune_db[COUNTRY_FORTUNE_COUNT];

	_IntervalControl::dbstruct	m_ctl_Assign_General_db;
	_IntervalControl::dbstruct	m_ctl_Assign_LMinister_db;
	_IntervalControl::dbstruct	m_ctl_Assign_RMinister_db;
	_IntervalControl::dbstruct	m_ctl_Assign_LGuard_db;
	_IntervalControl::dbstruct	m_ctl_Assign_RGuard_db;
	_IntervalControl::dbstruct	m_ctl_Cancel_General_db;
	_IntervalControl::dbstruct	m_ctl_Cancel_LMinister_db;
	_IntervalControl::dbstruct	m_ctl_Cancel_RMinister_db;
	_IntervalControl::dbstruct	m_ctl_Cancel_LGuard_db;
	_IntervalControl::dbstruct	m_ctl_Cancel_RGuard_db;

	_IntervalControl::dbstruct	m_ctl_ModifyNotice_db;
	_IntervalControl::dbstruct	m_ctl_Collect_db;
	_IntervalControl::dbstruct	m_ctl_ForbidChat_db;
	_IntervalControl::dbstruct	m_ctl_Enjail_db;
	_IntervalControl::dbstruct	m_ctl_Assoil_db;

	_IntervalControl::dbstruct	m_ctl_bonus_king_db;
	_IntervalControl::dbstruct	m_ctl_bonus_queen_db;
	_IntervalControl::dbstruct	m_ctl_bonus_general_db;
	_IntervalControl::dbstruct	m_ctl_bonus_lminister_db;
	_IntervalControl::dbstruct	m_ctl_bonus_rminister_db;
	_IntervalControl::dbstruct	m_ctl_bonus_lguard_db;
	_IntervalControl::dbstruct	m_ctl_bonus_rguard_db;

	uint32				m_uCrc;

	Country_DB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_King = INVALID_GUID;
		m_KingGuildID = INVALID_GUILD_ID;
		m_ChallengerGuildID = INVALID_GUILD_ID;
		m_Challenger = INVALID_GUID;
		m_cCountryID = 0;
		memset(m_szKing, 0, MAX_CHARACTER_NAME);
		memset(m_szNotice, 0, MAX_NOTICE_SIZE);
		memset(m_szChallenger, 0, MAX_CHARACTER_NAME);

		int32 i=0;
		for(i = 0; i < MAX_FREEPARAM_NUM; ++i)
		{
			m_aFreeParam[i] = INVALID_ID;
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

		memset(m_nResource, 0, sizeof(int32) * COUNTRY_RESOURCE_COUNT);

		m_kingly_QiCheng_stat = 0;
		m_kingly_Suit_stat = 0;

		m_officer_Queen.m_UserGUID = INVALID_GUID;
		m_officer_Queen.m_szUserName[0] = 0;
		m_officer_LMinister.m_UserGUID = INVALID_GUID;
		m_officer_LMinister.m_szUserName[0] = 0;
		m_officer_RMinister.m_UserGUID = INVALID_GUID;
		m_officer_RMinister.m_szUserName[0] = 0;
		m_officer_General.m_UserGUID = INVALID_GUID;
		m_officer_General.m_szUserName[0] = 0;
		m_officer_LGuard.m_UserGUID = INVALID_GUID;
		m_officer_LGuard.m_szUserName[0] = 0;
		m_officer_RGuard.m_UserGUID = INVALID_GUID;
		m_officer_RGuard.m_szUserName[0] = 0;

		m_pOfficers[0] = &m_officer_Queen;
		m_pOfficers[1] = &m_officer_LMinister;
		m_pOfficers[2] = &m_officer_RMinister;
		m_pOfficers[3] = &m_officer_General;
		m_pOfficers[4] = &m_officer_LGuard;
		m_pOfficers[5] = &m_officer_RGuard;

		m_pIntervalControls[0] = &m_ctl_Fortune_db[0];
		m_pIntervalControls[1] = &m_ctl_Fortune_db[1];
		m_pIntervalControls[2] = &m_ctl_Fortune_db[2];
		m_pIntervalControls[3] = &m_ctl_Fortune_db[3];
		m_pIntervalControls[4] = &m_ctl_Assign_General_db;
		m_pIntervalControls[5] = &m_ctl_Assign_LMinister_db;
		m_pIntervalControls[6] = &m_ctl_Assign_RMinister_db;
		m_pIntervalControls[7] = &m_ctl_Assign_LGuard_db;
		m_pIntervalControls[8] = &m_ctl_Assign_RGuard_db;
		m_pIntervalControls[9] = &m_ctl_Cancel_General_db;
		m_pIntervalControls[10] = &m_ctl_Cancel_LMinister_db;
		m_pIntervalControls[11] = &m_ctl_Cancel_RMinister_db;
		m_pIntervalControls[12] = &m_ctl_Cancel_LGuard_db;
		m_pIntervalControls[13] = &m_ctl_Cancel_RGuard_db;
		m_pIntervalControls[14] = &m_ctl_ModifyNotice_db;
		m_pIntervalControls[15] = &m_ctl_Collect_db;
		m_pIntervalControls[16] = &m_ctl_ForbidChat_db;
		m_pIntervalControls[17] = &m_ctl_Enjail_db;
		m_pIntervalControls[18] = &m_ctl_Assoil_db;
		m_pIntervalControls[19] = &m_ctl_bonus_king_db;
		m_pIntervalControls[20] = &m_ctl_bonus_queen_db;
		m_pIntervalControls[21] = &m_ctl_bonus_general_db;
		m_pIntervalControls[22] = &m_ctl_bonus_lminister_db;
		m_pIntervalControls[23] = &m_ctl_bonus_rminister_db;
		m_pIntervalControls[24] = &m_ctl_bonus_lguard_db;
		m_pIntervalControls[25] = &m_ctl_bonus_rguard_db;

		m_uCrc = 0;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 FillCrcData(char *buffer)
	{
		int32	nStart = 0;

		return nStart;
	}
};

enum COUNTRY_USE_STATS { COUNTRY_ADDNEW = 0, COUNTRY_DELETE, COUNTRY_SAVED, };

struct CountryMK
{
	MKHead		m_MKHead;
	Country_DB	m_CountrySM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_CountrySM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_CountrySM.Clear();
	}
};

struct SceneVar_DB
{
	int32	mVar[MAX_SCENE_VARIABLE];

	SceneVar_DB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct Iterface_SceneVarDB
{
	Iterface_SceneVarDB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		mSceneVar.Clear();
		mDirty = FALSE;
	}

	SceneVar_DB	mSceneVar;
	BOOL		mDirty;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	int32 GetVar(int32 index)
	{
		KCheck(index >= 0);
		KCheck(index < MAX_SCENE_VARIABLE);
		return mSceneVar.mVar[index];
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetVar(int32 index, int32 Var)
	{
		KCheck(index >= 0);
		KCheck(index < MAX_SCENE_VARIABLE);
		mSceneVar.mVar[index] = Var;
	}
};

struct SceneVarMK
{
	MKHead		m_MKHead;
	SceneVar_DB	m_SceneVar;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_SceneVar.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}
};

struct ShopDataDB
{
	uint32	m_SerialId;
	uchar	m_ShopId;
	GUID_t	m_UserGUID;
	char	m_CharName[MAX_CHARACTER_NAME + 1];
	int32	m_Gold;
	int32	m_Charge;
	int32	m_Price;
	uint32	m_CreateTime;
	uint32	m_DeleteTime;
	GUID_t	m_BuyerGUID;

	ShopDataDB()
	{
		m_SerialId = -1;
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(uint32 id)
	{
		m_SerialId = id;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ShopDataDB &operator=(const ShopDataDB &other)
	{
		__GUARD__ if(&other != this)
		{
			m_SerialId = other.m_SerialId;
			m_ShopId = other.m_ShopId;
			m_UserGUID = other.m_UserGUID;
			m_Gold = other.m_Gold;
			m_Charge = other.m_Charge;
			m_Price = other.m_Price;
			m_CreateTime = other.m_CreateTime;
			m_DeleteTime = other.m_DeleteTime;
			m_BuyerGUID = other.m_BuyerGUID;
			strncpy(m_CharName, other.m_CharName, MAX_CHARACTER_NAME);
			m_CharName[MAX_CHARACTER_NAME] = '\0';
		}

		return *this;
		__UNGUARD__ return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_ShopId = -1;
		m_UserGUID = INVALID_GUID;
		m_Gold = 0;
		m_Charge = 0;
		m_Price = 0;
		m_CreateTime = -1;
		m_DeleteTime = -1;
		m_BuyerGUID = INVALID_GUID;
		memset(m_CharName, 0, sizeof(char) * (MAX_CHARACTER_NAME + 1));
	}
};

enum WORLD_SHOP_STATS { WORLD_SHOP_ADDNEW = 0, WORLD_SHOP_DELETE, WORLD_SHOP_SAVED, };

struct ShopDataMK
{
	MKHead		m_MKHead;
	ShopDataDB	m_ShopDataSM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_ShopDataSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_ShopDataSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyFrom(ShopDataDB &ShopData)
	{
		__GUARD__	ShopData = m_ShopDataSM;

		__UNGUARD__
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyTo(const ShopDataDB &ShopData)
	{
		__GUARD__	m_ShopDataSM = ShopData;

		__UNGUARD__
	}
};

struct BankDataDB
{
	uint32	m_SerialId;
	uchar	m_ShopId;
	GUID_t	m_UserGUID;
	int32	m_Gold;
	int32	m_Siller;
	int32	m_Charge;
	uint32	m_CreateTime;
	uint32	m_DeleteTime;
	GUID_t	m_BuyerGUID;

	BankDataDB()
	{
		m_SerialId = -1;
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init(uint32 id)
	{
		m_SerialId = id;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	BankDataDB &operator=(const BankDataDB &other)
	{
		__GUARD__ if(&other != this)
		{
			m_SerialId = other.m_SerialId;
			m_ShopId = other.m_ShopId;
			m_UserGUID = other.m_UserGUID;
			m_Gold = other.m_Gold;
			m_Siller = other.m_Siller;
			m_Charge = other.m_Charge;
			m_CreateTime = other.m_CreateTime;
			m_DeleteTime = other.m_DeleteTime;
			m_BuyerGUID = other.m_BuyerGUID;
		}

		return *this;
		__UNGUARD__ return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear()
	{
		m_ShopId = -1;
		m_UserGUID = INVALID_GUID;
		m_Gold = 0;
		m_Siller = 0;
		m_Charge = 0;
		m_CreateTime = -1;
		m_DeleteTime = -1;
		m_BuyerGUID = INVALID_GUID;
	}
};

enum WORLD_BANK_STATS { WORLD_BANK_ADDNEW = 0, WORLD_BANK_DELETE, WORLD_BANK_SAVED, };

struct BankDataMK
{
	MKHead		m_MKHead;
	BankDataDB	m_BankDataSM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_BankDataSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_BankDataSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyFrom(BankDataDB &BankData)
	{
		__GUARD__	BankData = m_BankDataSM;

		__UNGUARD__
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyTo(const BankDataDB &BankData)
	{
		__GUARD__	m_BankDataSM = BankData;

		__UNGUARD__
	}
};

struct CandidateDB
{
	GUID_t	m_nUserGuid;
	char	m_szUserName[MAX_CHARACTER_NAME];

	CandidateDB()
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	CandidateDB &operator=(const CandidateDB &other)
	{
		if(this != &other)
		{
			m_nUserGuid = other.m_nUserGuid;
			tsnprintf_s(m_szUserName, sizeof(m_szUserName), "%s", other.m_szUserName);
		}

		return *this;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		m_nUserGuid = INVALID_GUID;
		memset(m_szUserName, 0, sizeof(m_szUserName));
	}
};

enum CANDIDATE_STATS { CANDIDATE_ADDNEW = 0, CANDIDATE_DELETE, CANDIDATE_SAVED, };

struct CandidateMK
{
	MKHead		m_MKHead;
	CandidateDB	m_CandidateSM;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void Clear()
	{
		m_MKHead.Clear();
		m_CandidateSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_CandidateSM.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyTo(CandidateDB &data)
	{
		__GUARD__	data = m_CandidateSM;

		__UNGUARD__
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void CopyFrom(const CandidateDB &data)
	{
		__GUARD__	m_CandidateSM = data;

		__UNGUARD__
	}
};

struct MasterCandidateMK :
	public CandidateMK
{
};

struct PrenticeCandidateMK :
	public CandidateMK
{
};

struct StockDataDB
{
	uint32	m_SerialId;
	GUID_t	m_UserGUID;
	char	m_CharName[MAX_CHARACTER_NAME + 1];
	int32	m_Price;		//交易单手的价格
	uint32	m_Gold;			//交易现金
	int32	m_Charge;
	uchar   m_TradeType;
	uint32	m_CreateTime;
	uint32	m_DeleteTime;

	StockDataDB()
	{
		Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	StockDataDB &operator=(const StockDataDB &other)
	{
		__GUARD__ if(&other != this)
		{
			m_SerialId = other.m_SerialId;
			m_UserGUID = other.m_UserGUID;
			m_Price = other.m_Price;
			m_Gold = other.m_Gold;
			m_Charge = other.m_Charge;
			m_TradeType = other.m_TradeType;
			m_CreateTime = other.m_CreateTime;
			m_DeleteTime = other.m_DeleteTime;
			strncpy(m_CharName, other.m_CharName, MAX_CHARACTER_NAME);
			m_CharName[MAX_CHARACTER_NAME] = '\0';
		}

		return *this;
		__UNGUARD__ return *this;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Clear()
	{
		m_SerialId = -1;
		m_UserGUID = INVALID_GUID;
		m_Price = 0;
		m_Gold = 0;
		m_Charge = 0;
		m_CreateTime = -1;
		m_DeleteTime = -1;
		memset(m_CharName, 0, sizeof(char) * (MAX_CHARACTER_NAME + 1));
	}
};

enum WORLD_STOCK_STATS { WORLD_STOCK_NORMAL = 0,WORLD_STOCK_ADDNEW, WORLD_STOCK_DELETE, WORLD_STOCK_SAVED, };

struct StockDataSMU
{
	MKHead		m_SMUHead;
	StockDataDB	m_StockDataSM;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	void Clear()
	{
		m_SMUHead.Clear();
		m_StockDataSM.Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Lock(char Type)
	{
		shm_lock(&m_SMUHead.flag, Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void UnLock(char Type)
	{
		shm_unlock(&m_SMUHead.flag, Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetPoolID(uint32 poolID)
	{
		m_SMUHead.PoolId = poolID;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetPoolID()
	{
		return m_SMUHead.PoolId;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_SMUHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_SMUHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_SMUHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_SMUHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Init()
	{
		m_StockDataSM.Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void CopyFrom(StockDataDB &StockData)
	{
		__GUARD__	StockData = m_StockDataSM;

		__UNGUARD__
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void CopyTo(const StockDataDB &StockData)
	{
		__GUARD__	m_StockDataSM = StockData;

		__UNGUARD__
	}
};

struct StockRecordDataDB
{
	uint32	m_SerialId;
	GUID_t	m_UserGUID;		//主人GUID
	uint32	m_TradeTime;
	uchar	m_TradeType;
	uint32	m_TradeGold;
	int32	m_TradePrice;

	enum { struct_size = sizeof(uint32) * 3 + sizeof(uchar) + sizeof(GUID_t) + sizeof(int32)};

	StockRecordDataDB()
	{
		m_SerialId = -1;
		Clear();
	}

	void Init(uint32 id)
	{
		m_SerialId = id;
	};

	StockRecordDataDB &operator=(const StockRecordDataDB &other)
	{
		__GUARD__ if(&other != this)
		{
			m_SerialId = other.m_SerialId;
			m_UserGUID = other.m_UserGUID;
			m_TradeTime = other.m_TradeTime;
			m_TradeType = other.m_TradeType;
			m_TradeGold = other.m_TradeGold;
			m_TradePrice = other.m_TradePrice;
		}

		return *this;
		__UNGUARD__ return *this;
	}

	uint32 GetSize() const
	{
		uint32 size = sizeof(m_SerialId) + 
					sizeof(m_UserGUID) + 
					sizeof(m_TradeTime) +
					sizeof(m_TradeType) + 
					sizeof(m_TradeGold) + 
					sizeof(m_TradePrice);
		return size;
	}


	void Clear()
	{
		m_UserGUID = INVALID_GUID;
		m_TradeTime = -1;
		m_TradeType = 0;
		m_TradeGold = 0;
		m_TradePrice = 0;
	}
};

enum WORLD_STOCK_RECORD_STATS { WORLD_STOCK_RECORD_ADDNEW = 0, WORLD_STOCK_RECORD_DELETE, WORLD_STOCK_RECORD_SAVED, };

struct StockRecordDataSMU
{
	MKHead		m_SMUHead;
	StockRecordDataDB	m_StockRecordDataSM;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	void Clear()
	{
		m_SMUHead.Clear();
		m_StockRecordDataSM.Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Lock(char Type)
	{
		shm_lock(&m_SMUHead.flag, Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void UnLock(char Type)
	{
		shm_unlock(&m_SMUHead.flag, Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetPoolID(uint32 poolID)
	{
		m_SMUHead.PoolId = poolID;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetPoolID()
	{
		return m_SMUHead.PoolId;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_SMUHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_SMUHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_SMUHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_SMUHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Init()
	{
		m_StockRecordDataSM.Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void CopyFrom(StockRecordDataDB &StockRecordData)
	{
		__GUARD__	StockRecordData = m_StockRecordDataSM;

		__UNGUARD__
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void CopyTo(const StockRecordDataDB &StockRecordData)
	{
		__GUARD__	m_StockRecordDataSM = StockRecordData;

		__UNGUARD__
	}
};

// 动态价格商店

struct DynamicShop_DB
{
	uint8					m_nShopID;								// dynamic_shop_tab.tab中的商店id		
	uint8					m_nItemIndexInShop;						// 物品在商店中的位置
	uint8					m_nItemCount;							// 物品剩余数
	int32					m_nItemPrice;							// 当前价格
	int32					m_nTick;								// 当前时间

	DynamicShop_DB()
	{
		Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Clear()
	{
		m_nShopID = 0;			
		m_nItemIndexInShop = 0;
		m_nItemCount = 0;		
		m_nItemPrice = 0;		
		m_nTick = 0;
	}
};

enum DYNAMIC_SHOP_USE_STATS { DYNAMIC_SHOP_ADDNEW = 0, DYNAMIC_SHOP_DELETE, DYNAMIC_SHOP_SAVED, };

#define MAX_DYNAMIC_SHOP_NUM 2048

struct DynamicShopMK
{
	MKHead		m_MKHead;
	DynamicShop_DB	m_DynamicShopSM;

	/*
	===============================================================================================================
	===============================================================================================================
	*/

	void Clear()
	{
		m_MKHead.Clear();
		m_DynamicShopSM.Clear();
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Lock(char Type)
	{
		shm_lock(&m_MKHead.flag, Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void UnLock(char Type)
	{
		shm_unlock(&m_MKHead.flag, Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetPoolID(uint32 poolID)
	{
		m_MKHead.PoolId = poolID;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetPoolID()
	{
		return m_MKHead.PoolId;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	BOOL SetUseStatus(int32 Use, char Type)
	{
		Lock(Type);
		m_MKHead.UseStatus = Use;
		UnLock(Type);
		return TRUE;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	int32 GetUseStatus(char Type)
	{
		int32	iRet;
		Lock(Type);
		iRet = m_MKHead.UseStatus;
		UnLock(Type);
		return iRet;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	uint32 GetTime2Save(char Type)
	{
		uint32	uTime;
		Lock(Type);
		uTime = m_MKHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void SetTime2Save(uint32 uTime, char Type)
	{
		Lock(Type);
		m_MKHead.SaveTime = uTime;
		UnLock(Type);
	}

	/*
	===============================================================================================================
	===============================================================================================================
	*/
	void Init()
	{
		m_DynamicShopSM.Clear();
	}
};

#pragma pack(pop)
#endif
