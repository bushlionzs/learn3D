#include "StdAfx.h"
#include "GameDataStructPet.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

LPCSTR GetMountStateText(int32 nState)
{
	switch(nState)
	{
	case MOUNT_STATE_MOUNTING:	/* 出战中 */
		{
//			strTmp = UI_SYSTEM_PTR->ParserString_NoColor_VarParam(GetORTText(OR_MOUNT_MOUNTING) ).c_str();
			return ACTION_SYS_PTR->GetOperateResult( OR_MOUNT_MOUNTING );
		}
		break;

	case MOUNT_STATE_EXCHANGE:	/* 交易中 */
		{
			return ACTION_SYS_PTR->GetOperateResult( OR_MOUNT_EXCHANGE );
		}
		break;

	case MOUNT_STATE_STALL:		/* 摆摊中 */
		{
			return ACTION_SYS_PTR->GetOperateResult( OR_MOUNT_STALL );
		}
		break;

	case MOUNT_STATE_MATING:	/* 交配中 */
		{
			return ACTION_SYS_PTR->GetOperateResult( OR_MOUNT_MATING );
		}
		break;

	case MOUNT_STATE_FRIEND:	/* 征友中 */
		{
			return ACTION_SYS_PTR->GetOperateResult( OR_MOUNT_FRIEND );
		}
		break;

	default:
		break;
	}

	return "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 GetMountResult(int32 iPara1, FLOAT fPara2, int32 iPara3, int32 iPara4, int32 iRate)
{
	FLOAT	fRate = iRate * 0.01f;

	return(int32) (iPara3 * iPara4 * 0.01f * fRate + 0.5f);
}

/*
 =======================================================================================================================
    获取坐骑属性修正值
 =======================================================================================================================
 */
int32 GetMountRefixResult(int32 nSkillID, int32 nImpactParamIndex, const SDataPet *pPet)
{
	if(NULL == pPet /* || pPet->m_GUID.IsNull() */ )	/* huangjin 坐骑超链接测试屏蔽 */
		return 0;
	if(nImpactParamIndex <= 0 || nImpactParamIndex > 5) return 0;

	TABLE_DEFINEHANDLE(s_MountBaseDBC, TABLE_MOUNT_BASE_DATA);

	const _TABLE_MOUNT_BASE_DATA	*pMountBaseData = (const _TABLE_MOUNT_BASE_DATA *) s_MountBaseDBC->GetFieldDataByIndex(pPet->m_nBaseID);

	if(NULL == pMountBaseData) return 0;

	/* 技能有效 */
	TABLE_DEFINEHANDLE(s_pSkillDBC, TABLE_SKILL_DATA);

	const _DBC_SPELL_DATA	*pSkillData = (const _DBC_SPELL_DATA *) s_pSkillDBC->GetFieldDataByIndex(nSkillID);

	if(NULL == pSkillData) return 0;

	STRING	strOut = CGameTable::GetSplitData(pSkillData->m_lpszImpactParameter_1, 1);
	int32		nImpactID = atoi(strOut.c_str());

	/* impact有效 */
	TABLE_DEFINEHANDLE(s_pEquip_Impact, TABLE_EQUIP_IMPACT);

	const _TABLE_EQUIP_IMPACT *pImpact = (const _TABLE_EQUIP_IMPACT *) s_pEquip_Impact->GetFieldDataByIndex(nImpactID);

	if(NULL == pImpact) return 0;

	int32		nTypeIndex = (nImpactParamIndex - 1) * 6 + 3;
	int32		nParamIndex = (nImpactParamIndex - 1) * 6 + 5;
	LPCSTR	szType = "-1";

	if(nTypeIndex > 0 && nTypeIndex < IMPACT_PARAM_MAX_NUM * 2)
	{
		szType = pImpact->m_szParamDes[nTypeIndex];
	}

	LPCSTR	szParam = "0";

	if(nParamIndex > 0 && nParamIndex < IMPACT_PARAM_MAX_NUM * 2)
	{
		szParam = pImpact->m_szParamDes[nParamIndex];
	}

	int32 nType = atoi(szType);
	int32 nParam = atoi(szParam);
	int32 nLevelParam = pPet->m_nLevel - pMountBaseData->nLevel;
	int32 nResult = 0;

	switch(nType)
	{
	case 0: /* 力量 */
		{
			nResult = GetMountResult
				(
					pPet->m_nLevel,
					pPet->m_nUpRate,
					pPet->m_nAttrStrApt,
					pPet->m_nAttrStr + nLevelParam + pPet->m_nAttrStrAdd,
					nParam
				);
		}
		break;

	case 1: /* 敏捷 */
		{
			nResult = GetMountResult
				(
					pPet->m_nLevel,
					pPet->m_nUpRate,
					pPet->m_nAttrDexApt,
					pPet->m_nAttrDex + nLevelParam + pPet->m_nAttrDexAdd,
					nParam
				);
		}
		break;

	case 2: /* 智力 */
		{
			nResult = GetMountResult
				(
					pPet->m_nLevel,
					pPet->m_nUpRate,
					pPet->m_nAttrIntApt,
					pPet->m_nAttrInt + nLevelParam + pPet->m_nAttrIntAdd,
					nParam
				);
		}
		break;

	case 3: /* 体质 */
		{
			nResult = GetMountResult
				(
					pPet->m_nLevel,
					pPet->m_nUpRate,
					pPet->m_nAttrConApt,
					pPet->m_nAttrCon + nLevelParam + pPet->m_nAttrConAdd,
					nParam
				);
		}
		break;

	default:
		break;
	}

	return nResult;
}

/*
 =======================================================================================================================
    获取附带坐骑修正值的说明文字
 =======================================================================================================================
 */
LPCSTR GetMountTipDesc(int32 nSkillID, LPCSTR szStr, const SDataPet *pPet)
{
	if(INVALID_ID == nSkillID) return szStr;
	if(NULL == pPet) return szStr;

	/*
	 * huangjin 坐骑超链接测试屏蔽 ;
	 * if (pPet->m_GUID.IsNull()) ;
	 * return szStr;
	 */
	if(NULL == szStr) return "";

	static const uint32	ulength = 512;
	static char			szDesc[ulength] = { 0 };

	memset(szDesc, NULL, sizeof(char) * ulength);

	uint32	num = (uint32) strlen(szStr);

	num = (num < ulength - 2) ? (num) : (ulength - 2);

	memcpy(szDesc, szStr, sizeof(char) * num);

	int32		nParm[10] = { 0 };	/* 最多支持10个输出参数 */
	uint32	uParmNum = 0;

	for(int32 i = 0; i < num; ++i)
	{
		if(uParmNum >= 10) break;

		if('$' == szDesc[i] && i + 1 < num)
		{
			int32 nIndex = szDesc[i + 1] - 'a' + 1;	/* 取值1~5， 对应 buff_logic.tab 的数据索引 */

			if(nIndex > 0 && nIndex <= 5)
			{
				nParm[uParmNum] = GetMountRefixResult(nSkillID, nIndex, pPet);

				szDesc[i] = '%';
				szDesc[i + 1] = 'd';
				++uParmNum;
			}
		}
	}

	if(0 == uParmNum) return szStr;

	static char szOutData[ulength] = { 0 };

	sprintf
	(
		szOutData,
		szDesc,
		nParm[0],
		nParm[1],
		nParm[2],
		nParm[3],
		nParm[4],
		nParm[5],
		nParm[6],
		nParm[7],
		nParm[8],
		nParm[9]
	);

	return szOutData;
}

/*
 =======================================================================================================================
    宠物数据结构 ;
 =======================================================================================================================
 */
void SDataPet::Clear(void)
{
	m_pModelData = NULL;
	m_nBaseID = -1;
	m_nState = MOUNT_STATE_IDLE;
	m_nGender = 0;
	m_szName = "";
	m_szNickname = "";
	m_nLevel = 0;
	m_nExp = 0;
	m_nEraCount = 0;
	m_nHappiness = 0;
	m_nSkillGrid = 0;

	m_nAttrStr = 0;
	m_nAttrDex = 0;
	m_nAttrInt = 0;
	m_nAttrCon = 0;

	m_nAttrStrAdd = 0;
	m_nAttrDexAdd = 0;
	m_nAttrIntAdd = 0;
	m_nAttrConAdd = 0;

	m_nUpRate = 0;
	m_nPotential = 0;
	m_nBasic = 0;
	m_nSavvy = 0;

	m_nAttrStrApt = 0;
	m_nAttrDexApt = 0;
	m_nAttrIntApt = 0;
	m_nAttrConApt = 0;

	m_nAttrMaxStrApt = 0;
	m_nAttrMaxDexApt = 0;
	m_nAttrMaxIntApt = 0;
	m_nAttrMaxConApt = 0;

	m_GUID.Reset();
	m_SpouseGUID.Reset();
	m_nServerIndex = INVALID_ID;
	for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		m_Skill[i].Clear();
	}

	m_byLock = PET_UNLOCK;
	m_UnLockTime = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SDataPet &SDataPet::operator=(const SDataPet &val)
{
	m_pModelData = val.m_pModelData;
	m_nBaseID = val.m_nBaseID;
	m_nState = val.m_nState;
	m_nGender = val.m_nGender;
	m_szName = val.m_szName;
	m_szNickname = val.m_szNickname;
	m_nLevel = val.m_nLevel;
	m_nExp = val.m_nExp;
	m_nEraCount = val.m_nEraCount;
	m_nHappiness = val.m_nHappiness;
	m_nSkillGrid = val.m_nSkillGrid;

	m_nAttrStr = val.m_nAttrStr;
	m_nAttrDex = val.m_nAttrDex;
	m_nAttrInt = val.m_nAttrInt;
	m_nAttrCon = val.m_nAttrCon;

	m_nAttrStrAdd = val.m_nAttrStrAdd;
	m_nAttrDexAdd = val.m_nAttrDexAdd;
	m_nAttrIntAdd = val.m_nAttrIntAdd;
	m_nAttrConAdd = val.m_nAttrConAdd;

	m_nUpRate = val.m_nUpRate;
	m_nPotential = val.m_nPotential;
	m_nBasic = val.m_nBasic;
	m_nSavvy = val.m_nSavvy;

	m_nAttrStrApt = val.m_nAttrStrApt;
	m_nAttrDexApt = val.m_nAttrDexApt;
	m_nAttrIntApt = val.m_nAttrIntApt;
	m_nAttrConApt = val.m_nAttrConApt;

	m_nAttrMaxStrApt = val.m_nAttrMaxStrApt;
	m_nAttrMaxDexApt = val.m_nAttrMaxDexApt;
	m_nAttrMaxIntApt = val.m_nAttrMaxIntApt;
	m_nAttrMaxConApt = val.m_nAttrMaxConApt;

	m_GUID = val.m_GUID;
	m_SpouseGUID = val.m_SpouseGUID;
	m_nServerIndex = val.m_nServerIndex;

	m_byLock = val.m_byLock;
	m_UnLockTime = val.m_UnLockTime;

	for(int32 i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		m_Skill[i].Clear();
		m_Skill[i] = val.m_Skill[i];
	}

	return *this;
}
