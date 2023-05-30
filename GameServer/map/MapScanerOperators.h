/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	MapScanerOperators.h 
file path:	F:\khan2\src\MapServer\Server\Map
file base:
file ext:	h
author:		
modified:	wujianping
purpose:	Scanor是所有搜索周围obj操作的基类
			以下的各个类 是根据具体的条件进行搜索的
			SCANOR_INIT 为搜索条件
**********************************************************************************************/


#ifndef __MAPSCANOPERATORS_H__
#define __MAPSCANOPERATORS_H__

#include "TypeDefine.h"
#include "ScanerOperator.h"
#include "skill/Spell_EffectLogic_Base.h"
#include "gameobject/Character.h"
#include "gameobject/Player.h"
#include "map/game_map.h"
#include "gameobject/Behavior_Const.h"
#include "skill/Spell_Helper.h"
#include "gameobject/Trap.h"
#include "skill/Spell_TrapObjLogic.h"
#include "server_settting.h"


class	Bus;
class	Monster;
class	Player;
class	IMessage;

struct SCANOR_ACTIVETEAMMATES_INIT :
	public SCANOR_INIT
{
	GLPos	m_Position;
	TeamID_t	m_TeamID;
	GUID_t		m_MemberGUID;
	float		m_fRadius;

	SCANOR_ACTIVETEAMMATES_INIT()
	{
		m_TeamID = INVALID_ID;
		m_MemberGUID = INVALID_ID;
		m_fRadius = 0.0f;
	}
};

struct SCANOR_AEIMPACT_INIT :
	public SCANOR_INIT
{
	OBJLIST			*m_pTargets;
	float			m_fRadius;
	int32			m_nCount;
	UNIT_EFFECT		m_Impact;
	EffectLogic const	*m_pLogic;
	Character		*m_pMe;
	GLPos		m_CentrePoint;
	SCANOR_AEIMPACT_INIT()
	{
		m_pTargets = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_Impact.Clear();
		m_pLogic = NULL;
		m_pMe = NULL;
		m_CentrePoint.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void InitBase(void)
	{
		int32	&rZoneSize = g_Config.m_ConfigInfo.m_ZoneSize;
		if(0 != rZoneSize)
		{
			m_nZoneRadius = int32(m_fRadius / rZoneSize) + 1;
		}
		else
		{
			m_nZoneRadius = 0;
		}

		if(NULL == m_pMap)
		{
			KCheckEx
			(
				FALSE,
				"[SCANOR_AEIMPACT_INIT::InitBase]:Scene point is NULL!!please initialize it."
			);
			return;
		}

		m_GridID = m_pMap->CalcGridID(&m_CentrePoint);
	}
};

struct SCANOR_AESPELL_INIT :
	public SCANOR_INIT
{
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	SpellInfo const *m_pSkillInfo;
	Character	*m_pMe;
	GLPos	m_CentrePoint;
	SCANOR_AESPELL_INIT()
	{
		m_pTargets = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_pSkillInfo = NULL;
		m_pMe = NULL;
		m_CentrePoint.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void InitBase(void)
	{
		int32	&rZoneSize = g_Config.m_ConfigInfo.m_ZoneSize;
		if(0 != rZoneSize)
		{
			m_nZoneRadius = int32(m_fRadius / rZoneSize) + 1;
		}
		else
		{
			m_nZoneRadius = 0;
		}

		if(NULL == m_pMap)
		{
			KCheckEx
			(
				FALSE,
				"[SCANOR_AESPELL_INIT::InitBase]:Scene point is NULL!!please initialize it."
			);
			return;
		}

		m_GridID = m_pMap->CalcGridID(&m_CentrePoint);
	}
};

struct SCANOR_CHAT_INIT :
	public SCANOR_INIT
{
	IMessage	*m_pPacket;
	int32		m_nChatType;
	GuildID_t	m_GuildID;

	JiaZuID_t	m_JiaZuID;

	CountryID_t	m_CountryID;
	ID_t		m_WorldID;

	SCANOR_CHAT_INIT()
	{
		m_pPacket = NULL;
		m_nChatType = 0;
		m_GuildID = INVALID_ID;
		m_JiaZuID = INVALID_ID;
		m_CountryID = INVALID_ID;
		m_WorldID = INVALID_ID;
	};
};

struct SCANOR_COUNTRY_MEMBER_INIT :
	public SCANOR_INIT
{
	GLPos	m_Position;
	CountryID_t	m_CountryID;
	GUID_t		m_MemberGUID;
	float		m_fRadius;

	SCANOR_COUNTRY_MEMBER_INIT()
	{
		m_CountryID = INVALID_ID;
		m_MemberGUID = INVALID_ID;
		m_fRadius = 0.0f;
	}
};

struct BUS_SCANOR_ENEMY_INIT :
	public SCANOR_INIT
{
	Bus	*m_pBus;
	float	m_fRadius;

	BUS_SCANOR_ENEMY_INIT()
	{
		m_pBus = NULL;
		m_fRadius = 0.0f;
	}
};

struct SCANOR_ENEMY_INIT :
	public SCANOR_INIT
{
	Monster *m_pMonster;
	float	m_fRadius;

	SCANOR_ENEMY_INIT()
	{
		m_pMonster = NULL;
		m_fRadius = 0.0f;
	}
};

struct SCANOR_GUILD_MEMBER_INIT :
	public SCANOR_INIT
{
	GLPos	m_Position;
	GuildID_t	m_GuildID;
	GUID_t		m_MemberGUID;
	float		m_fRadius;

	SCANOR_GUILD_MEMBER_INIT()
	{
		m_GuildID = INVALID_ID;
		m_MemberGUID = INVALID_ID;
		m_fRadius = 0.0f;
	}
};

struct SCANOR_HUMAN_INIT :
	public SCANOR_INIT
{
	GLPos	m_Position;
	GUID_t		m_GUID;
	float		m_fRadius;

	SCANOR_HUMAN_INIT()
	{
		m_GUID = INVALID_ID;
		m_fRadius = 0.0f;
	}
};

//Add by HuangQinqi. 
struct SCANOR_MONSTER_INIT :
	public SCANOR_INIT
{
	GLPos	m_Position;
	GUID_t		m_GUID;
	float		m_fRadius;

	SCANOR_MONSTER_INIT()
	{
		m_GUID	 = INVALID_ID;
		m_fRadius = 0.0f;
	}
};
//Add end.

struct SCANOR_SECTORSKILL_INIT :
	public SCANOR_INIT
{
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	SpellInfo const *m_pSkillInfo;
	Character	*m_pMe;
	GLPos	m_CentrePoint;
	float		m_fDir;
	SCANOR_SECTORSKILL_INIT()
	{
		m_pTargets = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_pSkillInfo = NULL;
		m_pMe = NULL;

		m_CentrePoint.Clear();
		m_fDir = 0.f;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void InitBase(void)
	{
		int32	&rZoneSize = g_Config.m_ConfigInfo.m_ZoneSize;
		if(0 != rZoneSize)
		{
			m_nZoneRadius = int32(m_fRadius / rZoneSize) + 1;
		}
		else
		{
			m_nZoneRadius = 0;
		}

		if(NULL == m_pMap)
		{
			KCheckEx
			(
				FALSE,
				"[SCANOR_AESPELL_INIT::InitBase]:Scene point is NULL!!please initialize it."
			);
			return;
		}

		m_GridID = m_pMap->CalcGridID(&m_CentrePoint);
	}
};

struct SCANOR_TEAMMATE_INIT :
	public SCANOR_INIT
{
	Monster		*m_pMonster;
	float		m_fRadius;
	int32		m_nCount;
	int32		m_Type;
	BOOL		m_bOnlyNoEnemy;
	BOOL		m_bScanAllMonster;
	GLPos	m_Pos;

	SCANOR_TEAMMATE_INIT()
	{
		m_pMonster = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_Type = MONSTER_BHV_SUMMON_REGION;
		m_bOnlyNoEnemy = TRUE;
		m_bScanAllMonster = FALSE;
	}
};

struct SCANOPT_SOBJ_SCANPLAYER_INIT :
	public SCANOR_INIT
{
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	SpecialCreature *m_pMe;
	GLPos	m_CentrePoint;
	SCANOPT_SOBJ_SCANPLAYER_INIT()
	{
		m_pTargets = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_pMe = NULL;
		m_CentrePoint.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void InitBase(void)
	{
		int32	&rZoneSize = g_Config.m_ConfigInfo.m_ZoneSize;
		if(0 != rZoneSize)
		{
			m_nZoneRadius = int32(m_fRadius / rZoneSize) + 1;
		}
		else
		{
			m_nZoneRadius = 0;
		}

		if(NULL == m_pMap)
		{
			KCheckEx
			(
				FALSE,
				"[SScanoptsObjScanTrapInit::InitBase]:Scene point is NULL!!please initialize it."
			);
			return;
		}

		m_GridID = m_pMap->CalcGridID(&m_CentrePoint);
	}
};

struct SScanoptsObjScanTrapInit :
	public SCANOR_INIT
{
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	SpecialCreature *m_pMe;
	GLPos	m_CentrePoint;
	SScanoptsObjScanTrapInit()
	{
		m_pTargets = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_pMe = NULL;
		m_CentrePoint.Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void InitBase(void)
	{
		int32	&rZoneSize = g_Config.m_ConfigInfo.m_ZoneSize;
		if(0 != rZoneSize)
		{
			m_nZoneRadius = int32(m_fRadius / rZoneSize) + 1;
		}
		else
		{
			m_nZoneRadius = 0;
		}

		if(NULL == m_pMap)
		{
			KCheckEx
			(
				FALSE,
				"[SScanoptsObjScanTrapInit::InitBase]:Scene point is NULL!!please initialize it."
			);
			return;
		}

		m_GridID = m_pMap->CalcGridID(&m_CentrePoint);
	}
};

struct SCANOR_NEARESTMONSTER_INIT :
	public SCANOR_INIT
{
	Monster		*m_pMonster;
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	int32		m_Type;
	GLPos	m_Pos;

	SCANOR_NEARESTMONSTER_INIT()
	{
		m_pMonster = NULL;
		m_pTargets = NULL;
		m_fRadius = 0.0f;
		m_nCount = 0;
		m_Type = MONSTER_BHV_SUMMON_REGION;
	}
};

class Scanor_ActiveTeammates :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_ActiveTeammates();
	virtual		~Scanor_ActiveTeammates();

	virtual BOOL	Init(SCANOR_ACTIVETEAMMATES_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	GLPos	m_Position;
	TeamID_t	m_TeamID;
	GUID_t		m_MemberGUID;
	float		m_fRadius;

	Player		*m_aActiveTeammate[MAX_TEAM_MEMBER];
	int32		m_nActiveTeammateCount;
};

class Scanor_AEImpact :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_AEImpact();
	virtual		~Scanor_AEImpact();

	virtual BOOL	Init(SCANOR_AEIMPACT_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	OBJLIST			*m_pTargets;
	float			m_fRadius;
	int32			m_nCount;
	UNIT_EFFECT		m_Impact;
	EffectLogic const	*m_pLogic;
	Character		*m_pMe;
	GLPos		m_CentrePoint;
	BOOL			m_bReady;
};

class Scanor_AESkill :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_AESkill();
	virtual		~Scanor_AESkill();

	virtual BOOL	Init(SCANOR_AESPELL_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	SpellInfo const *m_pSkillInfo;
	Character	*m_pMe;
	GLPos	m_CentrePoint;
	BOOL		m_bReady;
};

class Scanor_Chat :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_Chat();
	virtual		~Scanor_Chat();

	virtual BOOL	Init(SCANOR_CHAT_INIT *pInit);
	virtual BOOL	OnEvent_BeforeScan();
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	IMessage	*m_pPacket;
	int32		m_nChatType;
	GuildID_t	m_GuildID;

	JiaZuID_t	m_JiaZuID;

	CountryID_t	m_CountryID;
	ID_t		m_WorldID;
};

class Scanor_CountryMember :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_CountryMember();
	virtual		~Scanor_CountryMember();

	virtual BOOL	Init(SCANOR_COUNTRY_MEMBER_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	GLPos	m_Position;
	CountryID_t	m_CountryID;
	GUID_t		m_MemberGUID;
	float		m_fRadius;

	Player		*m_aMember[MAX_HUMAN_LIST_SIZE];
	int32		m_nMemberCount;
};

class BUS_Scanor_Enemy :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BUS_Scanor_Enemy();
	virtual		~BUS_Scanor_Enemy();

	virtual BOOL	Init(BUS_SCANOR_ENEMY_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Bus	*m_pBus;
	float	m_fRadius;
};

class Scanor_Enemy :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_Enemy();
	virtual		~Scanor_Enemy();

	virtual BOOL	Init(SCANOR_ENEMY_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Monster *m_pMonster;
	float	m_fRadius;
};

class Scanor_GuildMember :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_GuildMember();
	virtual		~Scanor_GuildMember();

	virtual BOOL	Init(SCANOR_GUILD_MEMBER_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	GLPos	m_Position;
	GuildID_t	m_GuildID;
	GUID_t		m_MemberGUID;
	float		m_fRadius;

	Player		*m_aMember[MAX_HUMAN_LIST_SIZE];
	int32		m_nMemberCount;
};

class Scanor_Human :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_Human();
	virtual		~Scanor_Human();

	virtual BOOL	Init(SCANOR_HUMAN_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	GLPos	m_Position;
	GUID_t		m_GUID;
	float		m_fRadius;

	Player		*m_aMember[MAX_PLAYER];
	int32		m_nMemberCount;
};

//Added by Jerry Huang.
class Scanor_Monster :
	public Scanor
{
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	Scanor_Monster();
	virtual		~Scanor_Monster();

	virtual BOOL	Init(SCANOR_MONSTER_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	GLPos	m_Position;
	GUID_t		m_GUID;
	float		m_fRadius;

	Monster		*m_aMonster[MAX_PLAYER];
	int32		m_nMonsterCount;
};

class Scanor_SectorSkill :
	public Scanor
{
	float	m_aDistance[_OBJLIST::MAX_OBJ_LIST_SIZE];

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_SectorSkill();
	virtual		~Scanor_SectorSkill();

	virtual BOOL	Init(SCANOR_SECTORSKILL_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	OBJLIST		*m_pTargets;
	float		m_fRadius;
	int32		m_nCount;
	SpellInfo const *m_pSkillInfo;
	Character	*m_pMe;
	GLPos	m_CentrePoint;
	GLPos	m_RectPoint;
	float		m_fSpellUserDir;
	BOOL		m_bReady;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:

	float	GetAngle();
	float	GetRectangleWidth();
	BOOL	InitRectanglePoint();
	BOOL	IsInSector(float fAngle, Object *pObj, float &fDistance);
	BOOL	IsInSector(Object *pObj);
	float	GetFineAngle(float fX, float fY);
	int32	InsterObjToTagList(float fDistance, Object *pObj);
	void	Clear();
};

class Scanor_Teammate :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Scanor_Teammate();
	virtual		~Scanor_Teammate();

	virtual BOOL	Init(SCANOR_TEAMMATE_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Monster		*m_pMonster;
	float		m_fRadius;
	int32		m_nCount;
	int32		m_Type;
	BOOL		m_bOnlyNoEnemy;
	BOOL		m_bScanAllMonster;
	GLPos	m_Pos;
};

class ScanOpt_SObj_ScanPlayer :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ScanOpt_SObj_ScanPlayer();
	virtual		~ScanOpt_SObj_ScanPlayer();

	virtual BOOL	Init(SCANOPT_SOBJ_SCANPLAYER_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	OBJLIST			*m_pTargets;
	float			m_fRadius;
	int32			m_nCount;
	SpecialObjectLogic const *m_pLogic;
	SpecialCreature		*m_pMe;
	GLPos		m_CentrePoint;
	BOOL			m_bReady;
};

class ScanOptSObjScanTrap :
	public Scanor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ScanOptSObjScanTrap();
	virtual		~ScanOptSObjScanTrap();

	virtual BOOL	Init(SScanoptsObjScanTrapInit *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	OBJLIST			*m_pTargets;
	float			m_fRadius;
	int32			m_nCount;
	SpecialObjectLogic const *m_pLogic;
	SpecialCreature		*m_pMe;
	GLPos		m_CentrePoint;
	BOOL			m_bReady;
};
class Scanor_NearestMonster :
	public Scanor
{
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	Scanor_NearestMonster();
	virtual		~Scanor_NearestMonster();

	virtual BOOL	Init(SCANOR_NEARESTMONSTER_INIT *pInit);
	virtual uint32	OnEvent_FindObj(Object *pObj);
	int32	InsterObjToTagList(float fDistance, Object *pObj);
	/*
	-----------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------
	*/
public:
	Monster		*m_pMonster;
	OBJLIST		*m_pTargets;
	float	m_aDistance[_OBJLIST::MAX_OBJ_LIST_SIZE];
	float		m_fRadius;
	int32		m_nCount;
	int32		m_Type;
	GLPos	m_Pos;
};
#endif
