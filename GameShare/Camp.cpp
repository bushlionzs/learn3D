/*$T Common/Combat/CampAndStand.cpp GC 1.140 10/10/07 10:06:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Camp.h"
#include "Util.h"
#include "StructDB.h"
#include "TAB/TAB.h"

/*
 * void logInfo( const char* cpchString, ... ) ;
 * { ;
 * FILE* pFile = ::fopen( "Debug.log", "a" );
 * char szTemp[ 1024] = { 0 };
 * ;
 * if( pFile != 0) ;
 * { ;
 * va_list marker;
 * va_start( marker, cpchString);
 * ::_vsnprintf( (char*)szTemp, 1024, cpchString, marker);
 * va_end( marker);
 * ::fprintf( pFile, "%s\n", szTemp);
 * ::fclose( pFile);
 * }// if ;
 * }
 */
using namespace TAB;

/*
 =======================================================================================================================
        class CampStandRecord_T
 =======================================================================================================================
 */
CampStandRecord::CampStandRecord() :
	m_bInited(FALSE)
{
	memset((void *) m_aStands, (int32) FALSE, sizeof(m_aStands));
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CampStandRecord::InitFromDB(const TABFile *pDB, int32 const nRow)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(pDB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(0 <= nRow);

	/*~~~~~~~~~~~~~~~*/
	int32	column = 1;
	/*~~~~~~~~~~~~~~~*/

	for(int32 nIdx = 0; MAX_ID >= nIdx; ++nIdx)
	{
		m_aStands[nIdx] = pDB->Search_Posistion(nRow, column++)->iValue != 0;
	}

	m_bInited = TRUE;
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CampStandRecord::StandByCampID(CampID_t const nCampID) const
{
	__GUARD__ if(0 <= nCampID && MAX_ID >= nCampID)
	{
		return m_aStands[nCampID];
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eRELATION Calc_RelationType
(
	const _HUMAN_CAMP_DATA		*pCampData_A,
	const _HUMAN_CAMP_DATA		*pCampData_B,
	BOOL				bUsePKMode,
	const CampAndStandDataMgr	*pCampMgr
)
{
	__GUARD__ 
	if(pCampData_A == NULL || pCampData_B == NULL) return RELATION_FRIEND;

	if(bUsePKMode)
	{
		/* 1. 新手保护 */
		if(pCampData_A->nLevel != INVALID_ID && pCampData_B->nLevel != INVALID_ID)
		{
			/* 等级小于20就不可攻击，及被攻击 */
			if(pCampData_A->nLevel <= PROTECT_HUMANLEVEL || pCampData_B->nLevel <= PROTECT_HUMANLEVEL)
			{
				return RELATION_FRIEND;
			}
		}

		/*
		 * 1.5 安全区域判断 ;
		 * 1.5.1 绝对安全区内，不可被攻击，也不可攻击任何人
		 */
		if
		(
			(pCampData_A->nSafeArea == 1 && pCampData_A->nSafeArea_CampID == INVALID_CAMP)
		||	(pCampData_B->nSafeArea == 1 && pCampData_B->nSafeArea_CampID == INVALID_CAMP)
		)
		{
			return RELATION_FRIEND;
		}

		/* 1.5.2 相对安全区内，不可被攻击 */
		if(pCampData_B->nSafeArea == 1) return RELATION_FRIEND;

		/* 1.5.3 相对安全区内，不可攻击与安全区同阵营的人，可以攻击与安全区不同阵营的人 */
		if(pCampData_A->nSafeArea == 1)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const CampStandRecord	*pCampAndStand;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pCampAndStand = pCampMgr->GetInstanceByID(pCampData_A->nSafeArea_CampID);
			if(pCampAndStand != NULL)
			{
				if(pCampAndStand->StandByCampID(pCampData_B->m_nCampID))
				{
					return RELATION_ENEMY;
				}
				else
				{
					return RELATION_FRIEND;
				}
			}
			else
			{
				return RELATION_FRIEND;
			}
		}

		/* 2. 决斗判断 */
		if
		(
			pCampData_A->m_duelData.nOpponentId != INVALID_ID
		&&	pCampData_A->m_duelData.nOpponentId == pCampData_B->nObjId
		)
		{
			/* 这里需要区分服务器客户端 */
#ifdef GAME_CLIENT
			return RELATION_ENEMY;
#else
			if
			(
				pCampData_B->m_duelData.nOpponentId != INVALID_ID
			&&	pCampData_B->m_duelData.nOpponentId == pCampData_A->nObjId
			) return RELATION_ENEMY;
#endif
		}

		/* 2. 安全场景判断 */
		if(pCampData_A->nSceneSafeLevel == 0)	/* 不可PK */
		{
			return RELATION_FRIEND;
		}

		/* 3. 场景模式限制 */
		if(pCampData_A->nSceneRestrictiveMode >= 0)
		{
			if(pCampData_A->nSceneRestrictiveMode == PK_MODE_PUTONG)
			{	/* 锁定国家模式 */
				if(pCampData_A->m_nCampID == pCampData_B->m_nCampID)
				{
					return RELATION_FRIEND;
				}
				else
				{
					return RELATION_ENEMY;
				}
			}
			else if(pCampData_A->nSceneRestrictiveMode == PK_MODE_HUNZHAN)
			{	/* 锁定混战模式 */
				return RELATION_ENEMY;
			}
		}

		/* 4. 基本阵营判断 */
		if(pCampData_A->m_nCampID != pCampData_B->m_nCampID)
		{
			return RELATION_ENEMY;
		}

		/* 5. 是否队友 */
		if(pCampData_A->nTeamID != INVALID_ID && pCampData_A->nTeamID == pCampData_B->nTeamID)
		{
			return RELATION_FRIEND;
		}

		/* 6. 狂暴模式判断：除了本队成员、本队成员镖车和自己的镖车外都可攻击 */
		if(pCampData_A->m_uPKMode == PK_MODE_HUNZHAN)
		{
			return RELATION_ENEMY;
		}
		else if
		(
			pCampData_A->m_uPKMode == PK_MODE_PK
		&&	(pCampData_B->m_uPKMode == PK_MODE_PK || pCampData_B->m_uPKMode == PK_MODE_HUNZHAN)
		)
		{
			return RELATION_ENEMY;
		}
		else if(pCampData_A->m_uPKMode == PK_MODE_PUTONG && pCampData_B->m_uPKMode == PK_MODE_HUNZHAN)
		{
			return RELATION_ENEMY;
		}

		/* 7. 查表 */
		else
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const CampStandRecord	*pCampAndStand;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pCampAndStand = pCampMgr->GetInstanceByID(pCampData_A->m_nCampID);
			if(pCampAndStand != NULL)
			{
				if(pCampAndStand->StandByCampID(pCampData_B->m_nCampID))
				{
					return RELATION_ENEMY;
				}
				else
				{
					return RELATION_FRIEND;
				}
			}
			else
			{
				return RELATION_FRIEND;
			}
		}
	}
	else
	{
		/* 新手保护 */
		if(pCampData_A->nLevel != INVALID_ID && pCampData_B->nLevel != INVALID_ID)
		{
			/* 等级小于20就不可攻击，及被攻击 */
			if(pCampData_A->nLevel <= PROTECT_HUMANLEVEL || pCampData_B->nLevel <= PROTECT_HUMANLEVEL)
			{
				return RELATION_FRIEND;
			}
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		/* 查表 */
		const CampStandRecord	*pCampAndStand;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pCampAndStand = pCampMgr->GetInstanceByID(pCampData_A->m_nCampID);
		if(pCampAndStand != NULL)
		{
			if(pCampAndStand->StandByCampID(pCampData_B->m_nCampID))
			{
				return RELATION_ENEMY;
			}
			else
			{
				return RELATION_FRIEND;
			}
		}
		else
		{
			return RELATION_FRIEND;
		}
	}

	__UNGUARD__ return RELATION_FRIEND;
}

/*
 =======================================================================================================================
        判断场景与玩家的阵营关系
 =======================================================================================================================
 */
eRELATION Calc_RelationType(CampID_t CampA, CampID_t CampB, const CampAndStandDataMgr *pCampMgr)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const CampStandRecord	*pCampAndStand;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pCampAndStand = pCampMgr->GetInstanceByID(CampA);
	if(pCampAndStand != NULL)
	{
		if(pCampAndStand->StandByCampID(CampB))
		{
			return RELATION_ENEMY;
		}
		else
		{
			return RELATION_FRIEND;
		}
	}
	else
	{
		return RELATION_FRIEND;
	}
}
