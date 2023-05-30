/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	MapScanOperators.cpp 
			file path:	F:\khan2\src\MapServer\Server\Map
			file base:
			file ext:	cpp
author:		
modified:	wujianping
purpose:	Scanor是所有搜索周围obj操作的基类
			以下的各个类 是根据具体的条件进行搜索的
			SCANOR_INIT 为搜索条件
**********************************************************************************************/


#include "stdafx.h"


#include "gameobject/Monster.h"

//#include "server/gameobject/Bus.h"
#include "gameobject/Trap.h"
#include "skill/Spell_Interface.h"
#include "skill/Spell_Logic_Base.h"
#include "gameobject/Behavior_Monster.h"

#include "map/game_map.h"

#include "gameobject/Behavior_Helper.h"
#include "MapScanerOperators.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Scanor_ActiveTeammates::Scanor_ActiveTeammates()
{
	m_nActiveTeammateCount = 0;
	for(int32 i = 0; i < MAX_TEAM_MEMBER; i++)
	{
		m_aActiveTeammate[i] = NULL;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_ActiveTeammates::~Scanor_ActiveTeammates()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_ActiveTeammates::Init(SCANOR_ACTIVETEAMMATES_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_Position = pInit->m_Position;
	m_TeamID = pInit->m_TeamID;
	m_MemberGUID = pInit->m_MemberGUID;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_ActiveTeammates::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	if(pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = (Player *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_AEImpact::Scanor_AEImpact() :
	m_pTargets(NULL),
	m_fRadius(0.0f),
	m_nCount(0),
	m_pLogic(NULL),
	m_pMe(NULL),
	m_bReady(FALSE)
{
	m_CentrePoint.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_AEImpact::~Scanor_AEImpact()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_AEImpact::Init(SCANOR_AEIMPACT_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheckEx(FALSE, "[Scanor_AEImpact::Init]: NULL init struct pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pTargets)
	{
		KCheckEx(FALSE, "[Scanor_AEImpact::Init]: NULL OBJLIST pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pMe)
	{
		KCheckEx(FALSE, "[Scanor_AEImpact::Init]: NULL init Me pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pLogic)
	{
		KCheckEx(FALSE, "[Scanor_AEImpact::Init]: NULL Skill logic pointer found!!");
		return FALSE;
	}

	pInit->InitBase();
	m_pTargets = pInit->m_pTargets;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_Impact = pInit->m_Impact;
	m_pLogic = pInit->m_pLogic;
	m_pMe = pInit->m_pMe;
	m_CentrePoint.m_fX = pInit->m_CentrePoint.m_fX;
	m_CentrePoint.m_fZ = pInit->m_CentrePoint.m_fZ;
	if(TRUE == Scanor::Init(pInit))
	{
		m_bReady = TRUE;
		return TRUE;
	}

	m_bReady = FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_AEImpact::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(FALSE == m_bReady)
	{
		KCheckEx(FALSE, "[Scanor_AEImpact::OnEvent_FindObj]:Init first, use second! please~!!");
		return SCANRETURN_RETURN;
	}

	if(pObj == NULL)
	{
		KCheckEx(FALSE, "[Scanor_AEImpact::OnEvent_FindObj]: NULL Object Pointer Found!!");
		return SCANRETURN_RETURN;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistSq = KLLengthSq(&m_CentrePoint, pObj->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSq > (m_fRadius * m_fRadius))
	{
		return SCANRETURN_CONTINUE;
	}

	if(FALSE == m_pLogic->IsScanedTargetValid(m_Impact, *m_pMe, (Character &) (*pObj)))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	&rCount = m_pTargets->m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rCount < m_nCount && OBJLIST::MAX_OBJ_LIST_SIZE > rCount)
	{
		m_pTargets->m_aObj[rCount] = pObj;
		++rCount;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_AESkill::Scanor_AESkill() :
	m_pTargets(NULL),
	m_fRadius(0.0f),
	m_nCount(0),
	m_pSkillInfo(NULL),
	m_pMe(NULL),
	m_bReady(FALSE)
{
	m_CentrePoint.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_AESkill::~Scanor_AESkill()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_AESkill::Init(SCANOR_AESPELL_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL init struct pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pTargets)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL OBJLIST pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pMe)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL init Me pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pSkillInfo)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL Skill Info pointer found!!");
		return FALSE;
	}

	pInit->InitBase();
	m_pTargets = pInit->m_pTargets;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_pSkillInfo = pInit->m_pSkillInfo;
	m_pMe = pInit->m_pMe;
	m_CentrePoint.m_fX = pInit->m_CentrePoint.m_fX;
	m_CentrePoint.m_fZ = pInit->m_CentrePoint.m_fZ;
	if(TRUE == Scanor::Init(pInit))
	{
		m_bReady = TRUE;
		return TRUE;
	}

	m_bReady = FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_AESkill::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(FALSE == m_bReady)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::OnEvent_FindObj]:Init first, use second! please~!!");
		return SCANRETURN_RETURN;
	}

	if(pObj == NULL)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::OnEvent_FindObj]: NULL Object Pointer Found!!");
		return SCANRETURN_RETURN;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistSq = KLLengthSq(&m_CentrePoint, pObj->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSq > (m_fRadius * m_fRadius))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BaseSpellLogic const	*pSkillLogic = Spell_GetLogic(*m_pSkillInfo);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(FALSE == pSkillLogic->IsWantedTarget(*m_pMe, (Character &) (*pObj), *m_pSkillInfo))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	&rCount = m_pTargets->m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rCount < m_nCount && OBJLIST::MAX_OBJ_LIST_SIZE > rCount)
	{
		m_pTargets->m_aObj[rCount] = pObj;
		++rCount;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Chat::Scanor_Chat()
{
	m_pPacket = NULL;
	m_nChatType = 0;
	m_GuildID = INVALID_ID;
	m_JiaZuID = INVALID_ID;
	m_CountryID = INVALID_ID;
	m_WorldID = INVALID_ID;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Chat::~Scanor_Chat()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_Chat::Init(SCANOR_CHAT_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_pPacket = pInit->m_pPacket;
	m_nChatType = pInit->m_nChatType;
	m_GuildID = pInit->m_GuildID;
	m_JiaZuID = pInit->m_JiaZuID;
	m_CountryID = pInit->m_CountryID;
	m_WorldID = pInit->m_WorldID;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_Chat::OnEvent_BeforeScan()
{
	__GUARD__ if(m_GridID != INVALID_ID)
	{
		return TRUE;
	}

	

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_Chat::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	if(!pObj->IsActiveObj() || pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_CountryMember::Scanor_CountryMember()
{
	m_nMemberCount = 0;
	for(int32 i = 0; i < MAX_HUMAN_LIST_SIZE; i++)
	{
		m_aMember[i] = NULL;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_CountryMember::~Scanor_CountryMember()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_CountryMember::Init(SCANOR_COUNTRY_MEMBER_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_Position = pInit->m_Position;
	m_CountryID = pInit->m_CountryID;
	m_MemberGUID = pInit->m_MemberGUID;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_CountryMember::OnEvent_FindObj(Object *pObj)
{
	return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BUS_Scanor_Enemy::BUS_Scanor_Enemy()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BUS_Scanor_Enemy::~BUS_Scanor_Enemy()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL BUS_Scanor_Enemy::Init(BUS_SCANOR_ENEMY_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_pBus = pInit->m_pBus;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 BUS_Scanor_Enemy::OnEvent_FindObj(Object *pObj)
{
	 return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Enemy::Scanor_Enemy()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Enemy::~Scanor_Enemy()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_Enemy::Init(SCANOR_ENEMY_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_pMonster = pInit->m_pMonster;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_Enemy::OnEvent_FindObj(Object *pObj)
{
	 return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_GuildMember::Scanor_GuildMember()
{
	m_nMemberCount = 0;
	for(int32 i = 0; i < MAX_HUMAN_LIST_SIZE; i++)
	{
		m_aMember[i] = NULL;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_GuildMember::~Scanor_GuildMember()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_GuildMember::Init(SCANOR_GUILD_MEMBER_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_Position = pInit->m_Position;
	m_GuildID = pInit->m_GuildID;
	m_MemberGUID = pInit->m_MemberGUID;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_GuildMember::OnEvent_FindObj(Object *pObj)
{
	 return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Human::Scanor_Human()
{
	m_nMemberCount = 0;
	for(int32 i = 0; i < MAX_PLAYER; i++)
	{
		m_aMember[i] = NULL;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Human::~Scanor_Human()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_Human::Init(SCANOR_HUMAN_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_Position = pInit->m_Position;
	m_GUID = pInit->m_GUID;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_Human::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	if(pObj->GetObjType() != Object::OBJECT_CLASS_PLAYER)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Player	*pPlayer = (Player *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pPlayer);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(&m_Position, pPlayer->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDist < m_fRadius && m_nMemberCount < MAX_PLAYER)
	{
		m_aMember[m_nMemberCount] = pPlayer;
		m_nMemberCount++;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}
/*
=======================================================================================================================
===搜索周围的MONSTER====================
=======================================================================================================================
*/
//Added by HuangQinqi.  2010.03.24
Scanor_Monster::Scanor_Monster()
{
	m_nMonsterCount = 0;
	for(int32 i = 0; i < MAX_PLAYER; i++)
	{
		m_aMonster[i] = NULL;
	}
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Scanor_Monster::~Scanor_Monster()
{
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL Scanor_Monster::Init(SCANOR_MONSTER_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}
	
	m_Position = pInit->m_Position;
	m_GUID = pInit->m_GUID;
	m_fRadius = pInit->m_fRadius;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 Scanor_Monster::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	if(pObj->GetObjType() != Object::OBJECT_CLASS_MONSTER)
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster	*pMonster = (Monster *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pMonster);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(&m_Position, pMonster->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDist < m_fRadius && m_nMonsterCount < MAX_PLAYER)
	{
		m_aMonster[m_nMonsterCount] = pMonster;
		m_nMonsterCount++;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}
//Add end. HuangQinqi. 2010.03.24


const float	FLOAT_PRECISION = 0.000001f;
const float	SCAN_PI = 3.14159265359f;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Scanor_SectorSkill::Scanor_SectorSkill() :
	m_pTargets(NULL),
	m_fRadius(0.0f),
	m_nCount(0),
	m_pSkillInfo(NULL),
	m_pMe(NULL),
	m_bReady(FALSE),
	m_fSpellUserDir(0.f)
{
	Clear();
	m_CentrePoint.Clear();
	m_RectPoint.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_SectorSkill::~Scanor_SectorSkill()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_SectorSkill::Init(SCANOR_SECTORSKILL_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL init struct pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pTargets)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL OBJLIST pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pMe)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL init Me pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pSkillInfo)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::Init]: NULL Skill Info pointer found!!");
		return FALSE;
	}

	pInit->InitBase();
	m_pTargets = pInit->m_pTargets;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_pSkillInfo = pInit->m_pSkillInfo;
	m_pMe = pInit->m_pMe;
	m_CentrePoint.m_fX = pInit->m_CentrePoint.m_fX;
	m_CentrePoint.m_fZ = pInit->m_CentrePoint.m_fZ;
	m_fSpellUserDir = pInit->m_fDir;
	if(TRUE == Scanor::Init(pInit))
	{
		m_bReady = TRUE;
		//add by wujianping
		InitRectanglePoint();
		return TRUE;
	}

	m_bReady = FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_SectorSkill::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(m_nCount <= 0) return SCANRETURN_RETURN;

	if(FALSE == m_bReady)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::OnEvent_FindObj]:Init first, use second! please~!!");
		return SCANRETURN_RETURN;
	}

	if(pObj == NULL)
	{
		KCheckEx(FALSE, "[Scanor_AESkill::OnEvent_FindObj]: NULL Object Pointer Found!!");
		return SCANRETURN_RETURN;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistance = 9999999.0f;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(GetRectangleWidth() > 0.f )
	{
		if( !IsInSector(pObj) )
		{
			return SCANRETURN_CONTINUE;
		}
		fDistance = KLLengthSq(&m_CentrePoint, pObj->GetGLPos());
	}
	else
	{	
		if(!IsInSector(GetAngle(), pObj, fDistance))
		{
			return SCANRETURN_CONTINUE;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	BaseSpellLogic const	*pSkillLogic = Spell_GetLogic(*m_pSkillInfo);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pSkillLogic);
	if(FALSE == pSkillLogic->IsWantedTarget(*m_pMe, (Character &) (*pObj), *m_pSkillInfo))
	{
		return SCANRETURN_CONTINUE;
	}

	return InsterObjToTagList(fDistance, pObj);

	__UNGUARD__ return SCANRETURN_CONTINUE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Scanor_SectorSkill::GetAngle()
{
	__GUARD__ return m_pSkillInfo->GetAngle();

	__UNGUARD__ return 0;
}

float Scanor_SectorSkill::GetRectangleWidth()
{
	__GUARD__ return m_pSkillInfo->GetRectangleWidth();

	__UNGUARD__ return 0.f;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_SectorSkill::IsInSector(float fAngle, Object *pObj, float &fDistance)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SpellTargetingAndDepletingParams	&rParams = m_pMe->GetTargetingAndDepletingParams();
	const GLPos					*pTagPos = pObj->GetGLPos();
	float						fDir = rParams.GetTargetDirection();
	float						fDistSq = KLLengthSq(&m_CentrePoint, pTagPos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fDistance = fDistSq;

	if(fDistSq > (m_fRadius * m_fRadius))
	{
		return FALSE;
	}

	if(fDir < -0.00000001)
	{
		return TRUE;
	}
	else if(6.28f <= fAngle)
	{
		return TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	GLPos	tmpPos;
	/*~~~~~~~~~~~~~~~~~~~*/

	tmpPos.m_fX = pTagPos->m_fX - m_CentrePoint.m_fX;
	tmpPos.m_fZ = pTagPos->m_fZ - m_CentrePoint.m_fZ;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fHalfAngle = fAngle * 0.5f;
	float	fTagAngle = GetFineAngle(tmpPos.m_fZ, tmpPos.m_fX);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	fTagAngle = fabs(fTagAngle - fDir);

	fTagAngle = (fTagAngle > SCAN_PI) ? (2 * SCAN_PI - fTagAngle) : fTagAngle;

	if(fTagAngle < fHalfAngle)
	{
		return TRUE;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

//add by wujianping
BOOL Scanor_SectorSkill::IsInSector(Object *pObj)
{
	__GUARD__
	/*
			m_RectPoint 
			   |	
			   |
			 __.__	    ___
			|	  |    |._.| -----pTagPos
			|	  |	   /   \
			|__.__|	    | |	
			   |  
			   |   
			playerpos(m_CentrePoint)
	*/
	const GLPos					*pTagPos = pObj->GetGLPos();
	//先用距离剔除一些点
	float fMaxDist = m_fRadius * m_fRadius + GetRectangleWidth() * GetRectangleWidth();
	float fTarget2MeDist = (pTagPos->m_fX - m_CentrePoint.m_fX) * (pTagPos->m_fX - m_CentrePoint.m_fX) + 
							(pTagPos->m_fZ - m_CentrePoint.m_fZ) * (pTagPos->m_fZ - m_CentrePoint.m_fZ);
	if( fTarget2MeDist > fMaxDist )
	{
		return FALSE;
	}
	//用点的差乘求面积
	float fMultiply = (m_CentrePoint.m_fX - m_RectPoint.m_fX) * (pTagPos->m_fZ - m_RectPoint.m_fZ) - 
		(pTagPos->m_fX - m_RectPoint.m_fX) * (m_CentrePoint.m_fZ - m_RectPoint.m_fZ);
	float fDistance = sqrtf(
			(m_CentrePoint.m_fX - m_RectPoint.m_fX) * (m_CentrePoint.m_fX - m_RectPoint.m_fX) + 
			(m_CentrePoint.m_fZ - m_RectPoint.m_fZ) * (m_CentrePoint.m_fZ - m_RectPoint.m_fZ)
		);

	//三角形的高度 = 矩形面积 / 底边长度 / 2
	float fHight = (fabs(fMultiply) / fDistance) * 0.5f;

	if( fHight > GetRectangleWidth() )
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~*/
	GLPos	tmpPos;
	/*~~~~~~~~~~~~~~~~~~~*/

	tmpPos.m_fX = pTagPos->m_fX - m_CentrePoint.m_fX;
	tmpPos.m_fZ = pTagPos->m_fZ - m_CentrePoint.m_fZ;

	SpellTargetingAndDepletingParams	&rParams = m_pMe->GetTargetingAndDepletingParams();
	float	fDir = rParams.GetTargetDirection();
	float	fTagAngle = GetFineAngle(tmpPos.m_fZ, tmpPos.m_fX);

	fTagAngle = fabs(fTagAngle - fDir);

	fTagAngle = (fTagAngle > SCAN_PI) ? (2 * SCAN_PI - fTagAngle) : fTagAngle;

	if(fTagAngle * 2 > SCAN_PI)
	{
		return FALSE;
	}
	return TRUE;

	__UNGUARD__ return FALSE;
}

//add by wujianping
BOOL Scanor_SectorSkill::InitRectanglePoint()
{
	
	/*
	m_fSpellUserDir 是Z轴逆时针旋转后的角度
	          m_RectPoint 
				   |	
			       |
				 __.__	  
				|	  |
				|	  |
				|__.__|
			       |  
			       |   
				playerpos(m_CentrePoint)
	*/
	__GUARD__
	if( m_fSpellUserDir < 0.f )
	{
		m_fSpellUserDir += 2*__PI;
	}
	if( m_fSpellUserDir > 2*__PI )
	{
		m_fSpellUserDir -= 2*__PI;
	}
	m_RectPoint.m_fX = m_CentrePoint.m_fX + (MathSinCos::Sin(m_fSpellUserDir) * m_fRadius);
	m_RectPoint.m_fZ = m_CentrePoint.m_fZ + (MathSinCos::Cos(m_fSpellUserDir) * m_fRadius);

	
	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
float Scanor_SectorSkill::GetFineAngle(float fX, float fY)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float fAngle = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fY < FLOAT_PRECISION && fY > -FLOAT_PRECISION)
	{
		if(fX >= 0)
			return 0;
		else
			return SCAN_PI;
	}
	else if(fX < FLOAT_PRECISION && fX > -FLOAT_PRECISION)
	{
		if(fY >= 0)
			return SCAN_PI * 0.5f;
		else
			return SCAN_PI * 1.5f;
	}

	fAngle = atanf(fabs(fY / fX));

	if(fX < 0 && fY > 0)
	{
		fAngle = atanf(fabs(fX / fY));
		fAngle += SCAN_PI * 0.5f;
	}
	else if(fX < 0 && fY < 0)
		fAngle += SCAN_PI;
	else if(fX > 0 && fY < 0)
	{
		fAngle = atanf(fabs(fX / fY));
		fAngle += SCAN_PI * 1.5f;
	}

	return fAngle;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Scanor_SectorSkill::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_aDistance, 0, sizeof(float) * _OBJLIST::MAX_OBJ_LIST_SIZE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Scanor_SectorSkill::InsterObjToTagList(float fDistance, Object *pObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uchar &rCount = m_pTargets->m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OBJLIST::MAX_OBJ_LIST_SIZE <= rCount) return SCANRETURN_RETURN;

	if(rCount < m_nCount)
	{
		if(rCount == 0)
		{
			m_pTargets->m_aObj[rCount] = pObj;
			m_aDistance[rCount] = fDistance;
			++rCount;
			return SCANRETURN_CONTINUE;
		}

		for(int32 i = 0; i < rCount; ++i)
		{
			if(fDistance < m_aDistance[i])
			{
				memmove
				(
					&m_pTargets->m_aObj[i + 1],
					&m_pTargets->m_aObj[i],
					sizeof(Object *) * (rCount - i)
				);
				memmove(&m_aDistance[i + 1], &m_aDistance[i], sizeof(Object *) * (rCount - i));
				m_pTargets->m_aObj[i] = pObj;
				m_aDistance[i] = fDistance;
				++rCount;
				return SCANRETURN_CONTINUE;
			}
		}

		m_pTargets->m_aObj[rCount] = pObj;
		m_aDistance[rCount] = fDistance;
		++rCount;
	}
	else
	{
		for(int32 i = 0; i < rCount; ++i)
		{
			if(fDistance < m_aDistance[i])
			{
				m_pTargets->m_aObj[i] = pObj;
				m_aDistance[i] = fDistance;
				break;
			}
		}
	}

	return SCANRETURN_CONTINUE;
	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Teammate::Scanor_Teammate()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Scanor_Teammate::~Scanor_Teammate()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Scanor_Teammate::Init(SCANOR_TEAMMATE_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_pMonster = pInit->m_pMonster;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_bOnlyNoEnemy = pInit->m_bOnlyNoEnemy;
	m_bScanAllMonster = pInit->m_bScanAllMonster;
	m_Pos = pInit->m_Pos;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 Scanor_Teammate::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	if(Object::OBJECT_CLASS_MONSTER != pObj->GetObjType())
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = (Monster *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonster->IsAlive()) return SCANRETURN_CONTINUE;
	if(m_pMonster->IsEnemy(pMonster)) return SCANRETURN_CONTINUE;
	if
	(
		!(ESTATE_IDLE == pMonster->GetMonsterAI()->GetBehavior_State()->GetStateID()
		||	ESTATE_PATROL == pMonster->GetMonsterAI()->GetBehavior_State()->GetStateID()
		)
	) return SCANRETURN_CONTINUE;
	if(pMonster->GetMonsterAI()->GetNextTarget() != NULL) return SCANRETURN_CONTINUE;

	if(!m_bScanAllMonster)
	{
		if(pMonster->GetMonsterAI()->BHVParam(BHVPARAM_SCANTIME) < 0)
		{
			return SCANRETURN_CONTINUE;
		}
	}

	if(pMonster->GetObjType() != Object::OBJECT_CLASS_MONSTER) return SCANRETURN_CONTINUE;
	if(m_pMonster->GetID() == pMonster->GetID()) return SCANRETURN_CONTINUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(pMonster->GetGLPos(), &m_Pos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDist < m_fRadius)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nCount = m_pMonster->GetMonsterAI()->GetTeammateCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(nCount >= m_nCount) return SCANRETURN_RETURN;

		m_pMonster->GetMonsterAI()->AddTeammate(pMonster->GetID());
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScanOpt_SObj_ScanPlayer::ScanOpt_SObj_ScanPlayer() :
	m_pTargets(NULL),
	m_fRadius(0.0f),
	m_nCount(0),
	m_pLogic(NULL),
	m_pMe(NULL),
	m_bReady(FALSE)
{
	m_CentrePoint.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScanOpt_SObj_ScanPlayer::~ScanOpt_SObj_ScanPlayer()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScanOpt_SObj_ScanPlayer::Init(SCANOPT_SOBJ_SCANPLAYER_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheckEx(FALSE, "[ScanOpt_SObj_ScanPlayer::Init]: NULL init struct pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pTargets)
	{
		KCheckEx(FALSE, "[ScanOpt_SObj_ScanPlayer::Init]: NULL Target LIST pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pMe)
	{
		KCheckEx(FALSE, "[ScanOpt_SObj_ScanPlayer::Init]: NULL me pointer found!!");
		return FALSE;
	}

	pInit->InitBase();
	m_pTargets = pInit->m_pTargets;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_pMe = pInit->m_pMe;
	m_pLogic = ObjSpecial_GetLogic(*m_pMe);
	if(NULL == m_pLogic)
	{
		KCheckEx(FALSE, "[ScanOpt_SObj_ScanPlayer::Init]: Can not find the logic for this special obj!!");
		return FALSE;
	}

	m_CentrePoint.m_fX = pInit->m_CentrePoint.m_fX;
	m_CentrePoint.m_fZ = pInit->m_CentrePoint.m_fZ;
	if(TRUE == Scanor::Init(pInit))
	{
		m_bReady = TRUE;
		return TRUE;
	}

	m_bReady = FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScanOpt_SObj_ScanPlayer::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(FALSE == m_bReady)
	{
		KCheckEx(FALSE, "[ScanOpt_SObj_ScanPlayer::OnEvent_FindObj]:Init first, use second! please~!!");
		return SCANRETURN_RETURN;
	}

	if(pObj == NULL)
	{
		KCheckEx(FALSE, "[ScanOpt_SObj_ScanPlayer::OnEvent_FindObj]: NULL Object Pointer Found!!");
		return SCANRETURN_RETURN;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistSq = KLLengthSq(&m_CentrePoint, pObj->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSq > (m_fRadius * m_fRadius))
	{
		return SCANRETURN_CONTINUE;
	}

	if(FALSE == m_pLogic->IsScanedTargetValid(*m_pMe, (Character &) (*pObj)))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	&rCount = m_pTargets->m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rCount < m_nCount && m_pTargets->MAX_OBJ_LIST_SIZE > rCount)
	{
		m_pTargets->m_aObj[rCount] = pObj;
		++rCount;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScanOptSObjScanTrap::ScanOptSObjScanTrap() :
	m_pTargets(NULL),
	m_fRadius(0.0f),
	m_nCount(0),
	m_pLogic(NULL),
	m_pMe(NULL),
	m_bReady(FALSE)
{
	m_CentrePoint.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ScanOptSObjScanTrap::~ScanOptSObjScanTrap()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScanOptSObjScanTrap::Init(SScanoptsObjScanTrapInit *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheckEx(FALSE, "[ScanOptSObjScanTrap::Init]: NULL init struct pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pTargets)
	{
		KCheckEx(FALSE, "[ScanOptSObjScanTrap::Init]: NULL Target LIST pointer found!!");
		return FALSE;
	}

	if(NULL == pInit->m_pMe)
	{
		KCheckEx(FALSE, "[ScanOptSObjScanTrap::Init]: NULL me pointer found!!");
		return FALSE;
	}

	pInit->InitBase();
	m_pTargets = pInit->m_pTargets;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_pMe = pInit->m_pMe;
	m_pLogic = ObjSpecial_GetLogic(*m_pMe);
	if(NULL == m_pLogic)
	{
		KCheckEx(FALSE, "[ScanOptSObjScanTrap::Init]: Can not find the logic for this special obj!!");
		return FALSE;
	}

	m_CentrePoint.m_fX = pInit->m_CentrePoint.m_fX;
	m_CentrePoint.m_fZ = pInit->m_CentrePoint.m_fZ;
	if(TRUE == Scanor::Init(pInit))
	{
		m_bReady = TRUE;
		return TRUE;
	}

	m_bReady = FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScanOptSObjScanTrap::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(FALSE == m_bReady)
	{
		KCheckEx(FALSE, "[ScanOptSObjScanTrap::OnEvent_FindObj]:Init first, use second! please~!!");
		return SCANRETURN_RETURN;
	}

	if(pObj == NULL)
	{
		KCheckEx(FALSE, "[ScanOptSObjScanTrap::OnEvent_FindObj]: NULL Object Pointer Found!!");
		return SCANRETURN_RETURN;
	}

	if(!IsObjSpecial(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDistSq = KLLengthSq(&m_CentrePoint, pObj->GetGLPos());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDistSq > (m_fRadius * m_fRadius))
	{
		return SCANRETURN_CONTINUE;
	}

	if(FALSE == m_pLogic->IsScanedTargetValid(*m_pMe, (SpecialCreature &) (*pObj)))
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	&rCount = m_pTargets->m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(rCount < m_nCount && m_pTargets->MAX_OBJ_LIST_SIZE > rCount)
	{
		m_pTargets->m_aObj[rCount] = (SpecialCreature *) pObj;
		++rCount;
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
Scanor_NearestMonster::Scanor_NearestMonster()
{
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Scanor_NearestMonster::~Scanor_NearestMonster()
{
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL Scanor_NearestMonster::Init(SCANOR_NEARESTMONSTER_INIT *pInit)
{
	__GUARD__ if(pInit == NULL)
	{
		KCheck(FALSE);
		return FALSE;
	}

	m_pMonster = pInit->m_pMonster;
	m_pTargets = pInit->m_pTargets;
	m_fRadius = pInit->m_fRadius;
	m_nCount = pInit->m_nCount;
	m_Pos = pInit->m_Pos;

	return Scanor::Init(pInit);

	__UNGUARD__ return TRUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
uint32 Scanor_NearestMonster::OnEvent_FindObj(Object *pObj)
{
	__GUARD__ if(pObj == NULL)
	{
		KCheck(FALSE);
		return SCANRETURN_RETURN;
	}

	if(!IsObjCharacter(pObj->GetObjType()))
	{
		return SCANRETURN_CONTINUE;
	}

	if(Object::OBJECT_CLASS_MONSTER != pObj->GetObjType())
	{
		return SCANRETURN_CONTINUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Monster *pMonster = (Monster *) pObj;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMonster->IsAlive()) return SCANRETURN_CONTINUE;
	if(m_pMonster->IsEnemy(pMonster)) return SCANRETURN_CONTINUE;
	if(m_pMonster->GetID() == pMonster->GetID()) return SCANRETURN_CONTINUE;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fDist = KLSqrt(pMonster->GetGLPos(), &m_Pos);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(fDist < m_fRadius)
	{
		return InsterObjToTagList(fDist, pMonster);
	}

	__UNGUARD__ return SCANRETURN_CONTINUE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 Scanor_NearestMonster::InsterObjToTagList(float fDistance, Object *pObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uchar &rCount = m_pTargets->m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(OBJLIST::MAX_OBJ_LIST_SIZE <= rCount) return SCANRETURN_RETURN;

	if(rCount < m_nCount)
	{
		if(rCount == 0)
		{
			m_pTargets->m_aObj[rCount] = pObj;
			m_aDistance[rCount] = fDistance;
			++rCount;
			return SCANRETURN_CONTINUE;
		}

		for(int32 i = 0; i < rCount; ++i)
		{
			if(fDistance < m_aDistance[i])
			{
				memmove
					(
					&m_pTargets->m_aObj[i + 1],
					&m_pTargets->m_aObj[i],
					sizeof(Object *) * (rCount - i)
					);
				memmove(&m_aDistance[i + 1], &m_aDistance[i], sizeof(Object *) * (rCount - i));
				m_pTargets->m_aObj[i] = pObj;
				m_aDistance[i] = fDistance;
				++rCount;
				return SCANRETURN_CONTINUE;
			}
		}

		m_pTargets->m_aObj[rCount] = pObj;
		m_aDistance[rCount] = fDistance;
		++rCount;
	}
	else
	{
		for(int32 i = 0; i < rCount; ++i)
		{
			if(fDistance < m_aDistance[i])
			{
				m_pTargets->m_aObj[i] = pObj;
				m_aDistance[i] = fDistance;
				break;
			}
		}
	}

	return SCANRETURN_CONTINUE;
	__UNGUARD__ return SCANRETURN_CONTINUE;
}

