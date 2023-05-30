#ifndef _AI_MONSTER_DEF_H_
#define _AI_MONSTER_DEF_H_

//////////////////////////////////////////////////////////////////////////
// 坐骑相关常量
//////////////////////////////////////////////////////////////////////////

#define HORSE_REFOLLOW_DISTSQR_A		9.f
#define HORSE_REFOLLOW_DISTSQR_B		64.f
#define HORSE_REFOLLOW_DISTSQR_C		225.f
#define HORSE_MAX_ATTACK_DIST			8.f
#define HORSE_SCAN_IMPACTOFOWNER_INTERVAL	(5000)

enum BHV_HORSE_STATE { BHV_HORSE_STATE_INVALID = -1, BHV_HORSE_IDLE = 0, };

//////////////////////////////////////////////////////////////////////////
// 怪物相关常量
//////////////////////////////////////////////////////////////////////////

enum eMONSTER_BHV_CHAR_STATUS { MONSTER_BHV_CHAR_IDLE = 0, MONSTER_BHV_CHAR_MOVE, MONSTER_BHV_CHAR_USESPELL, MONSTER_BHV_CHAR_NUMBER, };
enum eMONSTER_BHV_FLEE_TYPE { MONSTER_BHV_FLEE_RANDOM = 0, MONSTER_BHV_FLEE_NEARESTFRIEND, MONSTER_BHV_FLEE_NEARESTPOINT, };
enum eMONSTER_BHV_ARRIVE_TYPE { MONSTER_BHV_ARRIVE_ATTACK = 0, MONSTER_BHV_ARRIVE_PICKUP, MONSTER_BHV_ARRIVE_FOLLOW, MONSTER_BHV_ARRIVE_NUMBER, };
enum eMONSTER_BHV_SUMMON_TYPE { MONSTER_BHV_SUMMON_REGION = 0, MONSTER_BHV_SUMMON_TEAM, MONSTER_BHV_SUMMON_NUMBER, };

#define GET_MONSTER_MAP(TYPEOFRETURN) \
	Monster *pMonster = GetCharacter(); \
	if(!pMonster) \
{ \
	KCheck(false); \
	return TYPEOFRETURN; \
} \
	if(false == pMonster->IsAlive()) \
{ \
	return TYPEOFRETURN; \
} \
	GameMap	*pMap = pMonster->GetMap(); \
	if(!pMap) \
{ \
	KCheck(false); \
	return TYPEOFRETURN; \
} \


#define BHV_ZERO_VALUE		(0.0001f)
#define BHV_MIN_DIST		(1.0f)
#define BHV_NORMAL_ATTACK		(0)
#define BHV_MAGIC_ATTACK		(1)
#define BHVPARAM_ARRIVE_DIST	(1.0f)
#define BHVPARAM_ARRIVE_DIST_MIN (0.8f)
#define BHV_MODIFYSPEED_STEP	(0.2f)
#define BHV_CHANGE_ENEMY_RATE	(20)
#define BHV_MAX_TEAMMATE_COUNT	(10)
#define BHV_MAX_ENEMY_COUNT		(5)
#define BHV_MAX_RAND_TIMES		(10)
#define BHV_MAX_FLEE_LENGTH		(10)
#define BHV_REFUSEPAOPAO_TIME	(10000)
#define BHV_FX_DELTA		(0.5f)
#define BHV_FZ_DELTA		(0.5f)
#define BHV_CHECKJAMCOUNT		1
#define BHV_AVOIDOVERLAPNUM		8
#define BHV_SERVICETIME		5000

//////////////////////////////////////////////////////////////////////////
// 宠物相关常量
//////////////////////////////////////////////////////////////////////////

#define BHV_REFOLLOW_DISTSQR_A		9.f
#define BHV_REFOLLOW_DISTSQR_B		64.f
#define BHV_REFOLLOW_DISTSQR_C		225.f
#define BHV_MAX_ATTACK_DIST			8.f
#define BHV_SCAN_IMPACTOFOWNER_INTERVAL	(5000)

enum BHPetState
{
	BHV_PET_STATE_INVALID	= -1,
	BHV_PET_IDLE		= 0,
	BHV_PET_FOLLOW		= 1,
	BHV_PET_ATTACK		= 2,
	BHV_PET_ONBESPELL	= 3,
	BHV_PET_DEAD		= 4,
};

enum PET_TYPE_BHVSPELL
{
	PET_TYPE_BHVSPELL_INVALID	= -1,
	PET_TYPE_BHVSPELL_PHYSICATTACK	= 0,
	PET_TYPE_BHVSPELL_MAGICATTACK	= 1,
	PET_TYPE_BHVSPELL_PROTECTEOWNER	= 2,
	PET_TYPE_BHVSPELL_DEFENCE	= 3,
	PET_TYPE_BHVSPELL_REVENGE	= 4,
};

#endif
