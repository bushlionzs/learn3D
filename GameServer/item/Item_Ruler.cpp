/*$T MapServer/Server/Item/ItemRuler.cpp GC 1.140 10/10/07 10:07:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "Item_Ruler.h"
#include "TabDefine_Map_Item.h"
#include "Enum.h"
#include "BaseTool.h"
#include "Item_Helper.h"
#include "TabDefine.h"
#include "gameobject/Player.h"
#include "gameobject/Monster.h"
#include "server_settting.h"
#include "map/game_map.h"
#include "map/MapScanerOperators.h"
#include "ItemInstanceManager.h"
#include "ItemInstance.h"
#include "Item_Interface.h"
#include "Item_Manager.h"
#include "data/data_manager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateEquipProperty
(
	SItemType	itemType,
	int32		iPlayerJob,
	SItem		&it,
	int32		iMonsterLvl,
	int32		iMonsterType
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SEquipTab	*pGET = g_ItemTab.GetEquipTB(itemType.ToSerial());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGET)
	{
		it.m_ItemIndex = pGET->m_IndexID;
		it.GetEquipData()->m_CurDamagePoint = 0;

		/*~~~~~~~~~~~~~~~~~~*/
		int32	nAttCount = 0;
		/*~~~~~~~~~~~~~~~~~~*/

		it.GetEquipData()->m_PaiType = pGET->m_PaiType;
		it.GetEquipData()->m_CurDurPoint = pGET->m_MaxDur;
		it.GetEquipData()->m_CurMaxDur = pGET->m_MaxDur;
		it.GetEquipData()->m_CurGemHole = pGET->m_BaseGemHole;
		it.GetEquipData()->m_AttrCount = nAttCount;

		if(pGET->m_iTermHour <= 0)
		{
			it.m_TermEndTime = 0;
		}
		else
		{
			it.m_TermEndTime = GET_TIME().GetCTime() + 3600 * pGET->m_iTermHour;
		}

		if(pGET->m_ParamType > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			eITEM_PARAM_VALUE	ipv = IPV_INT;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			it.SetItemFreeParam(0, ipv, pGET->m_ParamValue);
		}

		KCheck(pGET->m_ReqLevelCount > 0);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nNeedLevel = pGET->m_ReqLevel[0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pGET->m_ReqLevelCount > 1)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nRand = RandGenerator::GetRand(0, pGET->m_ReqLevelCount - 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nNeedLevel = pGET->m_ReqLevel[nRand];
		}

		it.GetEquipData()->m_NeedLevel = nNeedLevel;

		KCheck(pGET->m_LevelCount > 0);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nLevel = pGET->m_Level[0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pGET->m_LevelCount > 1)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nRand = RandGenerator::GetRand(0, pGET->m_LevelCount - 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			nLevel = pGET->m_Level[nRand];
		}

		it.GetEquipData()->m_Level = nLevel;

		if((PLAYER_EQUIP) pGET->m_EquipPoint == HEQUIP_SUIT)
		{
			memcpy
			(
				&it.GetEquipData()->m_pAttr[nAttCount],
				&pGET->m_Attr,
				sizeof(_ITEM_PROPERTY) * pGET->m_AttCount
			);
			it.GetEquipData()->m_AttrCount += pGET->m_AttCount;
			return TRUE;
		}

		if((PLAYER_EQUIP) pGET->m_EquipPoint == HEQUIP_SIGN)
		{
			memcpy
			(
				&it.GetEquipData()->m_pAttr[nAttCount],
				&pGET->m_Attr,
				sizeof(_ITEM_PROPERTY) * pGET->m_AttCount
			);
			it.GetEquipData()->m_AttrCount += pGET->m_AttCount;
			return TRUE;
		}

		if((PLAYER_EQUIP) pGET->m_EquipPoint == HEQUIP_SPECAIL || (PLAYER_EQUIP) pGET->m_EquipPoint == HEQUIP_AMULET)
		{
			memcpy
			(
				&it.GetEquipData()->m_pAttr[nAttCount],
				&pGET->m_Attr,
				sizeof(_ITEM_PROPERTY) * pGET->m_AttCount
			);
			it.GetEquipData()->m_AttrCount += pGET->m_AttCount;
			return TRUE;
		}

		if(it.GetEquipData()->m_EquipType == ITEM_DROP)
		{
			return CaculateDropEquipEffectProperty(it, iPlayerJob, iMonsterLvl, iMonsterType);
		}
		else if(it.GetEquipData()->m_EquipType == ITEM_CREATE)
		{
			return CaculateCreateEquipEffectProperty(it, iPlayerJob);
		}

		return CaculateEquipEffectProperty(it, iPlayerJob);
	}

	KCheck(FALSE);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateGemProperty(SItemType itemType, SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(itemType.ToSerial());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGET)
	{
		it.m_ItemIndex = pGET->m_nTableIndex;
		if(pGET->m_ParamType > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			eITEM_PARAM_VALUE	ipv = IPV_INT;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			it.SetItemFreeParam(0, ipv, pGET->m_ParamValue);
		}

		return TRUE;
	}
	else
	{
		QLogSystem::QUICK_LOG
			(
				QUICK_LOG_DEBUG,
				"ItemCreateRuler::CreateEquipAttrib can't find SGemInfoTab GemObjID =%d",
				itemType.ToSerial()
			);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateGemProperty(uint32 TableIndex, SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(TableIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGET)
	{
		it.m_ItemIndex = pGET->m_nTableIndex;
		if(pGET->m_ParamType > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			eITEM_PARAM_VALUE	ipv = IPV_INT;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			it.SetItemFreeParam(0, ipv, pGET->m_ParamValue);
		}

		return TRUE;
	}
	else
	{
		QLogSystem::QUICK_LOG
			(
				QUICK_LOG_DEBUG,
				"ItemCreateRuler::CreateGemAttrib can't find SGemInfoTab GemObjID =%d",
				TableIndex
			);
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateMaterialProperty(SItemType itemType, SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(FALSE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateMedicProperty(SItemType itemType, SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(itemType.ToSerial());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGET)
	{
		it.m_ItemIndex = pGET->m_nTableIndex;
		it.GetMedicData()->m_nCount = 1;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		eITEM_PARAM_VALUE	ipv = IPV_INT;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pGET->m_ParamType > 0)
		{
			it.SetItemFreeParam(0, ipv, pGET->m_ParamValue);
		}

		if(pGET->m_bMultTimes)
		{
			it.SetItemFreeParam(4, ipv, pGET->m_iMultTimes);
		}

		return TRUE;
	}
	else
		KCheck(FALSE);
	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateTaskItemProperty(SItemType itemType, SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(itemType.ToSerial());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGET)
	{
		it.m_ItemIndex = pGET->m_nTableIndex;
		it.GetMedicData()->m_nCount = 1;
		if(pGET->m_ParamType > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			eITEM_PARAM_VALUE	ipv = IPV_INT;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			it.SetItemFreeParam(0, ipv, pGET->m_ParamValue);
		}

		return TRUE;
	}
	else
		KCheck(FALSE);
	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateExtraBagProperty(SItemType itemType, SItem &it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(itemType.ToSerial());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pGET)
	{
		it.m_ItemIndex = pGET->m_nTableIndex;
		it.GetExtraBagData()->m_nBeginTime = INVALID_TIME;
		if(pGET->m_ParamType > 0)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			eITEM_PARAM_VALUE	ipv = IPV_INT;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			it.SetItemFreeParam(0, ipv, pGET->m_ParamValue);
		}

		return TRUE;
	}
	else
		KCheck(FALSE);
	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CreateQuestItemProperty(SItemType itemType, SItem &it)
{
	__GUARD__ return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CaculateDropEquipEffectProperty(SItem &it, int32 iPlayerJob, int32 iMonsterLvl, int32 iMonsterType)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	
	KCheck(it.GetEquipData()->m_EquipType == ITEM_DROP);

	return CaculateEquipProperty(it);
	
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CaculateEquipEffectProperty(SItem &it, int32 iPlayerLvl)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	
	KCheck(it.GetEquipData()->m_EquipType != ITEM_DROP);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(it.GetEquipData()->m_EquipType != ITEM_CREATE);

	return CaculateEquipProperty(it);

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CaculateEquipProperty(SItem& it)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	

	SEquipTab	*pGET = g_ItemTab.GetEquipTB(it.m_ItemIndex);
	KCheck(pGET);

	int32	nItemType = it.ItemType();
	KCheck(nItemType < EQUIP_TYPE_NUM);

	if(ISCommonEquip(it.m_ItemIndex))
	{
		if (EQUIP_CT_ORANGE != pGET->m_Color)
		{
			CaculateEquipPropertyStrategy_1(it);
		}
		else
		{
			CaculateEquipPropertyStrategy_2(it);
		}
	}
	else
	{
		uint32 nAttCount = it.GetEquipData()->m_AttrCount;
		KCheck(nAttCount <= MAX_EQUIP_EXT_ATTR && (nAttCount + pGET->m_AttCount) <= MAX_EQUIP_EXT_ATTR);

		memcpy(&it.GetEquipData()->m_pAttr[nAttCount], &pGET->m_Attr, sizeof(_ITEM_PROPERTY) * pGET->m_AttCount);
		it.GetEquipData()->m_AttrCount = nAttCount + pGET->m_AttCount;
	}

	it.GetEquipData()->m_EquipScore = pGET->m_EquipScore;
	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CreateItemRuler::CaculateEquipPropertyStrategy_1(SItem& it)
{
	__GUARD__

	SEquipTab	*pGET = g_ItemTab.GetEquipTB(it.m_ItemIndex);
	KCheck(pGET);

	int32	nItemType = it.ItemType();
	KCheck(nItemType < EQUIP_TYPE_NUM);

	//从EquipPoint_Value.tab中取此装备部位的权重值M
	uint32	nPointValue = g_ItemTab.GetEquipPointValue((PLAYER_EQUIP) pGET->m_EquipPoint);
	KCheck(nPointValue != 0);

	// 装备中当前的属性数
	uint32 nAttCount = it.GetEquipData()->m_AttrCount;
	KCheck(nAttCount <= MAX_EQUIP_EXT_ATTR);

	// 从attribute_set.tab中按照几率随机抽取一条作为蓝装属性条目
	uint32			nSumRate = g_ItemTab.GetSumRateByReqLevel(it.GetEquipData()->m_NeedLevel);
	int32			nSetCount = g_ItemTab.GetAttSetCount();
	//看随机出来的属性是否符合这个装备，不符合的话，在50次内重新随机

	BOOL	bAlive = FALSE;
	EQUIP_ATT_SET_TB	*pSetTB = NULL;
	for (uint32 i = 0; i < 50 && !bAlive; ++i)
	{
		// 按几率抽取
		int32			nRand = RandGenerator::GetRand(0, nSumRate);
		pSetTB = g_ItemTab.GetAttSetTBByRate(nRand);

		if(pSetTB)
		{
			for(int nTEquipAttCount = 0; nTEquipAttCount < pSetTB->m_AttCount; ++nTEquipAttCount)
			{
				if(pSetTB->m_AttrInfo[nTEquipAttCount].m_nValidEquipType[nItemType])
				{
					bAlive = TRUE;
					break;
				}
			}
		}

		if (bAlive)
			break;
	}

	// 没有随机到合适的属性，使用所有部件都可用的属性
	if(!bAlive)
	{
		pSetTB = g_ItemTab.GetAttSetTB(MAX_SOUL_EFFECTATT - 1);
	}

	if(pSetTB)
	{
		for(int nEquipAttCount = 0; nEquipAttCount < pSetTB->m_AttCount; ++nEquipAttCount)
		{
			if(pSetTB->m_AttrInfo[nEquipAttCount].m_nValidEquipType[nItemType])
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				//在attribute_level.tab中找到蓝装各属性对应Y的值N
				EQUIP_ATT_LEVEL_TB	*pLevelTB = g_ItemTab.GetAttLevelValue((ITEM_PROPERTY) pSetTB->m_AttrInfo[nEquipAttCount].m_Attr);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pLevelTB)
				{
					it.GetEquipData()->m_pAttr[nAttCount].m_AttrType = pSetTB->m_AttrInfo[nEquipAttCount].m_Attr;

					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					//生成的蓝装属性计算公式为：(N/100)*M 上下浮动20%
					float fValue = ((float) pLevelTB->m_Attr[it.GetEquipData()->m_NeedLevel] / 100.f) * nPointValue;
					float fRange = (RandGenerator::GetRand(0, 400) - 200.f) / 1000.f;
					int nValue = (int)(fValue + (fRange * fValue) + 0.5);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					it.GetEquipData()->m_pAttr[nAttCount].m_Value.m_Value = (nValue <= 0 ? 1 : nValue);
					++nAttCount;
				}
				else
				{
					QLogSystem::QUICK_LOG
						(
						QUICK_LOG_DEBUG,
						"ItemCreateRuler::CaculateEquipPropertyStrategy_1 can't find EQUIP_ATT_LEVEL_TB"
						);
					KCheck(0);
				}
			}
		}

		it.GetEquipData()->m_AttrCount = it.GetEquipData()->m_AttrCount + nAttCount;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CreateItemRuler::CaculateEquipPropertyStrategy_2(SItem& it)
{
	__GUARD__

	NEW_EQUIP_PRODUCE_TB tmpProduceTab;

	const NEW_EQUIP_PRODUCE_TB* pProduceTab = g_ItemTab.GetNewEquipProduceTB(it.m_ItemIndex);

	if (NULL != pProduceTab)
	{
		memcpy(&tmpProduceTab,pProduceTab,sizeof(NEW_EQUIP_PRODUCE_TB));
	}
	else
	{
		tmpProduceTab.m_nEquipId = it.m_ItemIndex;
		tmpProduceTab.m_nRate1[0] = 20;
		tmpProduceTab.m_nRate1[1] = 70;
		tmpProduceTab.m_nRate1[2] = 10;

		tmpProduceTab.m_nRate1[0] = 0;
		tmpProduceTab.m_nRate1[1] = 80;
		tmpProduceTab.m_nRate1[2] = 20;
	}
	sItemInterface.Equip_NewEquipBlueAttrRand(it,&tmpProduceTab,FALSE);

	return TRUE;

	__UNGUARD__ return FALSE;

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CreateItemRuler::CaculateCreateEquipEffectProperty(SItem &it, int32 iPlayerJob)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(it.GetEquipData()->m_EquipType == ITEM_CREATE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(it.GetEquipData()->m_EquipScore > 0);
	KCheck(iPlayerJob >= 0);
	KCheck(iPlayerJob < MAX_JOB_SUM);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SEquipTab	*pGET = g_ItemTab.GetEquipTB(it.m_ItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pGET);

	if (EQUIP_CT_ORANGE == pGET->m_Color)
	{
		return CaculateEquipProperty(it);
	}
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	nPointValue = g_ItemTab.GetEquipPointValue((PLAYER_EQUIP) pGET->m_EquipPoint);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(nPointValue != 0);

	if(it.GetEquipData()->m_EquipScore > (uint32) g_Config.m_ConfigInfo.m_nMinPaiScore)
	{
		if(it.GetEquipData()->m_EquipScore < (uint32) g_Config.m_ConfigInfo.m_nMinZiPaiScore)
		{
			it.GetEquipData()->m_PaiType = g_ItemTab.GetPaiIDByPaiType(EQUIPPAI_ANYFEIZI);
		}
		else
		{
			it.GetEquipData()->m_PaiType = g_ItemTab.GetPaiIDByPaiType(EQUIPPAI_ANYZI);
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	nAttCount = it.GetEquipData()->m_AttrCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ISCommonEquip(it.m_ItemIndex))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		EQUIPEXTRATT_TB *pEquipExtraAtt = g_ItemTab.GetEquipExtraAttInfoTB
			(
				(PLAYER_EQUIP) pGET->m_EquipPoint,
				it.GetEquipData()->m_EquipScore
			);
		EQUIPEXTRATT	equipExtraAtt = pEquipExtraAtt->m_EquipExtrAtt[iPlayerJob];
		int32		nMaxValidNum = equipExtraAtt.m_ValidCount - 1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(nMaxValidNum >= 0);
		for(uint32 i = 0; i < equipExtraAtt.m_ValidCount; ++i)
		{

			uint32			nAtt = RandGenerator::GetRand(0, equipExtraAtt.m_GenAttr[i].m_AttrCount - 1);
			EQUIP_ATT_LEVEL_TB	*pAttTB = g_ItemTab.GetAttLevelValue((ITEM_PROPERTY) equipExtraAtt.m_GenAttr[i].m_Attr[nAtt]);


			KCheck(pAttTB);

			uint32	nValue = pAttTB->m_Attr[it.GetEquipData()->m_NeedLevel];
			float64 nLogScore = log((float64) it.GetEquipData()->m_EquipScore);
			float64 nDValue = (float64) nValue * nPointValue * nLogScore / (float64) 100;

			nValue = (uint32) nDValue;
			if(nValue == 0)
			{
				nValue = 1;
			}

			it.GetEquipData()->m_pAttr[nAttCount].m_AttrType = equipExtraAtt.m_GenAttr[i].m_Attr[nAtt];
			it.GetEquipData()->m_pAttr[nAttCount].m_Value.m_Value = nValue;
			++nAttCount;
		}

		it.GetEquipData()->m_AttrCount = nAttCount;
	}
	else
	{
		for(uint32 i = 0; i < pGET->m_AttCount; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int16	nValue = pGET->m_Attr[i].m_Value.m_Value;
			float64 nLogScore = log((float64) it.GetEquipData()->m_EquipScore);
			float	fValue = (float) nValue * (float) nLogScore;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(fValue == 0)
			{
				fValue = 1;
			}

			it.GetEquipData()->m_pAttr[nAttCount].m_AttrType = pGET->m_Attr[i].m_AttrType;
			it.GetEquipData()->m_pAttr[nAttCount].m_Value.m_Value = nValue;
			++nAttCount;
		}

		it.GetEquipData()->m_AttrCount = nAttCount;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 CaculateMonsterExpRuler::CaculateBaseExp
(
	int32	iMonsterLevel,
	int32	iKillerLevel,
	uint32	MonsterBaseExp,
	int32	TeamCount
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SDropAttrTab	*pDropAttTB = g_ItemTab.GetDropAttTB(iMonsterLevel - iKillerLevel);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pDropAttTB);

	/*~~~~~~~~~~~~~*/
	uint32	nExp = 0;
	/*~~~~~~~~~~~~~*/

	if(TeamCount > 0)
	{
		switch(TeamCount)
		{
		case 1:
			{
				nExp = (uint32)
					(
						(float) MonsterBaseExp *
						pDropAttTB->m_ExpValue *
						(float) g_Config.m_ConfigInfo.m_TeamCount1Rate
					) / 100;
				if(nExp == 0)
				{
					nExp = 1;
				}
			}
			break;

		case 2:
			{
				nExp = (uint32)
					(
						(float) MonsterBaseExp *
						pDropAttTB->m_ExpValue *
						(float) g_Config.m_ConfigInfo.m_TeamCount2Rate
					) / 100;
				if(nExp == 0)
				{
					nExp = 1;
				}
			}
			break;

		case 3:
			{
				nExp = (uint32)
					(
						(float) MonsterBaseExp *
						pDropAttTB->m_ExpValue *
						(float) g_Config.m_ConfigInfo.m_TeamCount3Rate
					) / 100;
				if(nExp == 0)
				{
					nExp = 1;
				}
			}
			break;

		case 4:
			{
				nExp = (uint32)
					(
						(float) MonsterBaseExp *
						pDropAttTB->m_ExpValue *
						(float) g_Config.m_ConfigInfo.m_TeamCount4Rate
					) / 100;
				if(nExp == 0)
				{
					nExp = 1;
				}
			}
			break;

		case 5:
			{
				nExp = (uint32)
					(
						(float) MonsterBaseExp *
						pDropAttTB->m_ExpValue *
						(float) g_Config.m_ConfigInfo.m_TeamCount5Rate
					) / 100;
				if(nExp == 0)
				{
					nExp = 1;
				}
			}
			break;

		case 6:
			{
				nExp = (uint32)
					(
						(float) MonsterBaseExp *
						pDropAttTB->m_ExpValue *
						(float) g_Config.m_ConfigInfo.m_TeamCount6Rate
					) / 100;
				if(nExp == 0)
				{
					nExp = 1;
				}
			}
			break;

		default:
			{
				return 0;
			}
		}
	}
	else
	{
		nExp = (uint32) (MonsterBaseExp * pDropAttTB->m_ExpValue);
		if(nExp == 0)
		{
			nExp = 1;
		}
	}

	return nExp;

	__UNGUARD__ return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
eBOX_DISTRIBUTE_RULER CaculateMonsterDropRuler::GetMonsterDropRuler(Monster *pMonster)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__		KCheck(pMonster);
	int32			iDataID = pMonster->GetDataID();
	MonsterProperty*pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(iDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pAttr)
	{
		return(eBOX_DISTRIBUTE_RULER) pAttr->m_BossFlag;
	}

	return BDR_UNKNOW;

	__UNGUARD__ return BDR_UNKNOW;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CaculateMonsterDropRuler::CaculateCommOwnerList(Monster *pMonster)
{
	__GUARD__ if(!pMonster)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap	*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap)
	{
		return FALSE;
	}
	SDamageMemList DamageMemList = pMonster->GetKillerRec();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (DamageMemList.m_uCount > 0)
	{
		for (uint32 i = 0; i < DamageMemList.m_uCount; ++i)
		{
			pMonster->GetOwnerList().AddOwner
			(
				DamageMemList.m_DamageRec[i].m_Killer,
				DamageMemList.m_DamageRec[i].m_KillerObjID
			);
		}
	}


	return TRUE;

	__UNGUARD__ return FALSE;
}

#define MD_PICK_RANGE	(100.0f)

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CaculateMonsterDropRuler::CaculateCommDropRuler(Monster *pMonster, eBOX_DISTRIBUTE_RULER DropRuler)
{
	__GUARD__ if(!pMonster)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstanceManager	*pIBManager = pMap->GetItemInstanceManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pIBManager);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32			iMonsterLevel = pMonster->GetLevel();
	uint32			iKillerLevel = pMonster->GetOccupantLevel();
	int32			iDataID = pMonster->GetDataID();
	float			fSearchLength = g_Config.m_ConfigInfo.m_nTeamRage;
	int32			nValidMemberCount = 0;
	BOOL			bTeam = FALSE;
	int32			iFadeoutType = Obj_ItemRuler::FADE_OUT_PERSION;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster->GetOccupantTeamID() != INVALID_ID)
	{
		bTeam = TRUE;
		iFadeoutType = Obj_ItemRuler::FADE_OUT_TEAM;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Obj_ItemContaner	IBContaner = pIBManager->CaculateItemDropFromMonster
		(
			iKillerLevel,
			iDataID,
			pMonster->GetControlValue(),
			iFadeoutType
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(IBContaner.m_nCount <= 0)
	{
		return FALSE;
	}

	if(IBContaner.m_nCount > 8)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos		dropPos;

	

	for (int32 m = 0; m < IBContaner.m_nCount; ++m)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		BOOL	aLive = FALSE;
		/*~~~~~~~~~~~~~~~~~~*/

		if (!pMonster->GetNearCanDropPos(dropPos))
		{
			return TRUE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ItemInstance* pItem = pIBManager->CreateMonsterDropObj_Item
		(
			&dropPos,
			&IBContaner.m_Item[m]
		);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pItem);

		pItem->SetDropObjID(pMonster->GetID());
		pItem->SetActiveFlag(TRUE);

	}


	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CaculateMonsterDropRuler::CaculateBossDropRuler(Monster *pMonster, eBOX_DISTRIBUTE_RULER DropRuler)
{
	__GUARD__ if(!pMonster)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstanceManager	*pIBManager = pMap->GetItemInstanceManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pIBManager);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32			iMonsterLevel = pMonster->GetLevel();
	uint32			iKillerLevel = pMonster->GetOccupantLevel();
	int32			iDataID = pMonster->GetDataID();
	float			fSearchLength = g_Config.m_ConfigInfo.m_nTeamRage;
	int32			nValidMemberCount = 0;
	BOOL			bTeam = FALSE;
	int32			iFadeoutType = Obj_ItemRuler::FADE_OUT_PERSION;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster->GetOccupantTeamID() != INVALID_ID)
	{
		bTeam = TRUE;
		iFadeoutType = Obj_ItemRuler::FADE_OUT_TEAM;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Obj_ItemContaner	IBContaner = pIBManager->CaculateItemDropFromMonster
		(
			iKillerLevel,
			iDataID,
			pMonster->GetControlValue(),
			iFadeoutType
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(IBContaner.m_nCount <= 0)
	{
		return FALSE;
	}

	if(IBContaner.m_nCount > 100)
	{
		return FALSE;
	}


	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CaculateMonsterDropRuler::CaculateHuoDongBossDropRuler(Monster *pMonster, eBOX_DISTRIBUTE_RULER DropRuler)
{
	__GUARD__ if(!pMonster)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstanceManager	*pIBManager = pMap->GetItemInstanceManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pIBManager);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32			iMonsterLevel = pMonster->GetLevel();
	uint32			iKillerLevel = pMonster->GetOccupantLevel();
	int32			iDataID = pMonster->GetDataID();
	float			fSearchLength = g_Config.m_ConfigInfo.m_nTeamRage;
	int32			nValidMemberCount = 0;
	BOOL			bTeam = FALSE;
	int32			iFadeoutType = Obj_ItemRuler::FADE_OUT_NOFADE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pMonster->GetOccupantTeamID() != INVALID_ID)
	{
		bTeam = TRUE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Obj_ItemContaner	IBContaner = pIBManager->CaculateItemDropFromMonster
		(
			iKillerLevel,
			iDataID,
			pMonster->GetControlValue(),
			iFadeoutType
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(IBContaner.m_nCount <= 0)
	{
		return FALSE;
	}

	if(IBContaner.m_nCount > 100)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos		dropPos;

	if(DropRuler == BDR_BLUE)
	{
		for(int32 m = 0; m < IBContaner.m_nCount; ++m)
		{
			/*~~~~~~~~~~~~~~~~~~*/
			BOOL	aLive = FALSE;
			/*~~~~~~~~~~~~~~~~~~*/

			if(!pMonster->GetNearCanDropPos(dropPos))
			{
				return TRUE;
			}

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ItemInstance	*pItem = pIBManager->CreateMonsterDropObj_Item(&dropPos, &IBContaner.m_Item[m]);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pItem);

			pItem->SetPickOwnerTime(0);
			pItem->EnablePickOwnerTime();
			pItem->SetDropObjID(pMonster->GetID());
			pItem->SetActiveFlag(TRUE);
		}
	}
	else if(DropRuler == BDR_GOLD)
	{
		
	}


	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CaculateMonsterDropRuler::DropItemToTeam(Monster *pMonster, Obj_ItemContaner *pObjItemContainer)
{
	__GUARD__ if(!pMonster)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GameMap*pMap = pMonster->GetMap();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(!pMap)
	{
		return FALSE;
	}

	if(pMonster->GetOccupantTeamID() == INVALID_ID)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ItemInstanceManager	*pIBManager = pMap->GetItemInstanceManager();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pIBManager);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32			iDataID = pMonster->GetDataID();
	uchar			nDistribMode = pMonster->GetDistribMode();
	GUID_t			nTeamLeaderGuid = pMonster->GetOwnTeamLeader();
	float			fSearchLength = g_Config.m_ConfigInfo.m_nTeamRage;
	int32			nValidMemberCount = 0;
	Player			*pOccupantHuman = NULL;
	Player			*pLeaderHuman = NULL;
	Player			*apValidMember[MAX_TEAM_MEMBER];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(apValidMember, 0, sizeof(apValidMember));
	if((nDistribMode == ITEM_INTURNS_DISTRIB) || (nDistribMode == ITEM_TEAMLEADER_DISTRIB))
	{
		/*~~~~~~~~~~~~~~~~~~~~*/
		Player	*pPlayer = NULL;
		/*~~~~~~~~~~~~~~~~~~~~*/

		
	}

	if(pObjItemContainer->m_nCount <= 0)
	{
		return FALSE;
	}

	if(pObjItemContainer->m_nCount > 100)
	{
		return FALSE;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	GLPos		dropPos;

	

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CheckItemRuler::CheckTypeRuler(eITEM_RULER_LIST ruler, const uint32 uItemIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(uItemIndex != 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(uItemIndex != INVALID_ID);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	uClass = GetClassBySerial(uItemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(uClass)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(uItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pGET)
			{
				/*~~~~~~~~~~~~~~*/
				char	Buff[255];
				/*~~~~~~~~~~~~~~*/

				memset(Buff, 0, 255);
				sprintf(Buff, "找不到对应物品的表格定义，请确定装备资源正确 ItemType=%d", uItemIndex);
				KCheckEx(pGET, Buff);
			}

			return CheckRuler(ruler, pGET->m_RulerID);
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(uItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pGET)
			{
				/*~~~~~~~~~~~~~~*/
				char	Buff[255];
				/*~~~~~~~~~~~~~~*/

				memset(Buff, 0, 255);
				sprintf
				(
					Buff,
					"找不到对应物品的表格定义，请确定CommonItem资源正确 ItemType=%d",
					uItemIndex
				);
				KCheckEx(pGET, Buff);
			}

			return CheckRuler(ruler, pGET->m_nRulerID);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(uItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pGET)
			{
				/*~~~~~~~~~~~~~~*/
				char	Buff[255];
				/*~~~~~~~~~~~~~~*/

				memset(Buff, 0, 255);
				sprintf
				(
					Buff,
					"找不到对应物品的表格定义，请确定TaskItem资源正确 ItemType=%d",
					uItemIndex
				);
				KCheckEx(pGET, Buff);
			}

			return CheckRuler(ruler, pGET->m_nRulerID);
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(uItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pGET)
			{
				/*~~~~~~~~~~~~~~*/
				char	Buff[255];
				/*~~~~~~~~~~~~~~*/

				memset(Buff, 0, 255);
				sprintf(Buff, "找不到对应物品的表格定义，请确定Gem资源正确 ItemType=%d", uItemIndex);
				KCheckEx(pGET, Buff);
			}

			return CheckRuler(ruler, pGET->m_nRulerID);
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(uItemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(!pGET)
			{
				/*~~~~~~~~~~~~~~*/
				char	Buff[255];
				/*~~~~~~~~~~~~~~*/

				memset(Buff, 0, 255);
				sprintf(Buff, "找不到对应物品的表格定义，请确定藏宝图资源正确 ItemType=%d", uItemIndex);
				KCheckEx(pGET, Buff);
			}

			return CheckRuler(ruler, pGET->m_nRulerID);
		}
		break;

	default:
		KCheck(FALSE);
		break;
	}

	KCheck(FALSE);
	return FALSE;
	__UNGUARD__ return FALSE;
}

BOOL CheckItemRuler::CheckRuler( eITEM_RULER_LIST ruler, const char &iRuler )
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iRulerID = iRuler;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(ruler)
	{
	case IRL_DISCARD:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->CanDiscard(); }break;
	case IRL_TILE:		{ return g_ItemTab.GetRuleValueByID(iRulerID)->CanTile(); }break;
	case IRL_SHORTCUT:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->CanShortCut(); }break;
	case IRL_CANSELL:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->CanSell(); }break;
	case IRL_CANEXCHANGE:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->CanExchange(); }break;
	case IRL_CANUSE:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->CanUse(); }break;
	case IRL_PICKBIND:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->isPickBind(); }break;
	case IRL_EQUIPBIND:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->isEquipBind(); }break;
	case IRL_UNIQUE:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->isUnique(); }break;
	case IRL_IDENT:		{ return g_ItemTab.GetRuleValueByID(iRulerID)->isIdent(); }break;
	case IRL_DUMMYITEM:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->isDummyItem(); }break;
	case IRL_BANK:		{ return g_ItemTab.GetRuleValueByID(iRulerID)->isBack(); }break;
	case IRL_CONSUME:	{ return g_ItemTab.GetRuleValueByID(iRulerID)->isConsume(); }break;
	default:		{ KCheck(FALSE); }break;
	}

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/

void Obj_ItemRuler::CreateItemFromMonsterDrop
(
 int32			iMonsterID,
 int32			iPlayerLvl,
 int32			iFadeoutType,
 float			fControlValue,
 Obj_ItemContaner	&OutContaner
 )
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	dBaseDropRate;
	float64			dDeltaDropRate = 1.0;
	uint32			dCurrentRate;
	MonsterProperty*pAttr = DataManager::GetSingletonPtr()->getMonsterProperty(iMonsterID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(pAttr != NULL);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iMonsterType = pAttr->m_BossFlag;
	int32	iMonsterLvl = pAttr->m_Level;
	uint32	nMonsterDropRate = (uint32) ((float) pAttr->m_nMonsterDropRate * fControlValue);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(nMonsterDropRate <= 100);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	nTotalRand = RandGenerator::GetRand(0, 10000);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(nTotalRand > (nMonsterDropRate * 100))
	{
		return;
	}

	for(int32 m = 0; m < pAttr->m_MonsterDropSetCount; ++m)
	{
		if(pAttr->m_MonsterDropItemSetID[m] < 0)
		{
			return;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		MONSTER_DROP_TB *pTb = g_ItemTab.GetMonsterDropTB(pAttr->m_MonsterDropItemSetID[m]);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if ( NULL == pTb )
		{
			continue ;
		}

		if ( 0 == pTb->m_ValidCount )
		{
			continue;
		}

		if(iFadeoutType == FADE_OUT_PERSION || iFadeoutType == FADE_OUT_TEAM)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SDropAttrTab	*pDropAtt = g_ItemTab.GetDropAttTB(iMonsterLvl - iPlayerLvl);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pDropAtt)
			{
				if(iFadeoutType == FADE_OUT_PERSION)
				{
					dDeltaDropRate = pDropAtt->m_AttValue;
				}
				else if(iFadeoutType == FADE_OUT_TEAM)
				{
					dDeltaDropRate = pDropAtt->m_TeamAttValue;
				}
			}
			else
				return;
		}

		if((dDeltaDropRate == 0) || (g_Config.m_ConfigInfo.m_DropParam == 0)) 
			return;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		MONSTER_DROPCONTENT	*pTbContent = pTb->m_Drops;
		SItem			it;
		int32			quality = 0;


		/*~~~~~~~~~~~~~~~~~~~~~~~~*/
		SItemType	itemType;
		BOOL		Ret = FALSE;
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(uint32 j = 0; j < pTb->m_ValidCount; ++j)
		{
			if(pTb->m_Drops[j].m_nItemCount > 0)
			{
				dBaseDropRate = (uint32)
					(
					(float64) pTb->m_Drops[j].m_nItemValue * dDeltaDropRate *
					(float64) g_Config.m_ConfigInfo.m_DropParam
					);

				for(int32 nNum = 0; nNum < pTb->m_Drops[j].m_nCycle; ++nNum)
				{
					dCurrentRate = RandGenerator::GetRand(0, MAX_MONSTER_VALUE);
					if(dCurrentRate > dBaseDropRate)
					{
						continue;
					}

					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					int	nPos = RandGenerator::GetRand(0,pTb->m_Drops[j].m_nItemCount - 1);
					uint32	uItemIndex = pTb->m_Drops[j].m_pDropContent[nPos];
					uchar	uClass = GetClassBySerial(uItemIndex);
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					it.Clear();
					switch(uClass)
					{
					case ICLASS_EQUIP:
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							SEquipTab	*pGET = g_ItemTab.GetEquipTB(uItemIndex);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(!pGET)
							{
								QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的表格定义，请确定EQUIP资源正确 ItemType=%d",uItemIndex);
								OutContaner.Clear();
								return;
							}

							itemType = Serial2ItemType(uItemIndex);
							it.GetEquipData()->m_EquipType = ITEM_DROP;
							Ret = CreateItemRuler::CreateEquipProperty(itemType,0,it,iMonsterLvl,iMonsterType);
							if(Ret)
							{
								if ( g_pItemMgr->GenItemGuid(it.m_ItemGUID) )
								{
									OutContaner.AddItem(it);
								}
							}
						}
						break;

					case ICLASS_MATERIAL:
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(uItemIndex);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(!pGET)
							{
								QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的表格定义，请确定CommonItem资源正确 ItemType=%d",uItemIndex);
								OutContaner.Clear();
								return;
							}

							itemType = Serial2ItemType(uItemIndex);
							Ret = CreateItemRuler::CreateMedicProperty(itemType,it);
							if(Ret)
							{
								if ( g_pItemMgr->GenItemGuid(it.m_ItemGUID)	)
								{
									OutContaner.AddItem(it);
								}
							}
						}
						break;

					case ICLASS_COMITEM:
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(uItemIndex);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(!pGET)
							{
								QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的表格定义，请确定CommonItem资源正确 ItemType=%d",uItemIndex);
								OutContaner.Clear();
								return;
							}

							itemType = Serial2ItemType(uItemIndex);
							Ret = CreateItemRuler::CreateMedicProperty(itemType,it);
							if(Ret)
							{
								if ( g_pItemMgr->GenItemGuid(it.m_ItemGUID) )
								{
									OutContaner.AddItem(it);
								}
							}
						}
						break;

					case ICLASS_GEM:
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(uItemIndex);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(!pGET)
							{
								QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的表格定义，请确定Gem资源正确 ItemType=%d",uItemIndex);
								OutContaner.Clear();
								return;
							}

							itemType = Serial2ItemType(uItemIndex);
							Ret = CreateItemRuler::CreateGemProperty(itemType,it);
							if(Ret)
							{
								if ( g_pItemMgr->GenItemGuid(it.m_ItemGUID) )
								{
									OutContaner.AddItem(it);
								}
							}
						}
						break;

					case ICLASS_TASKITEM:
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(uItemIndex);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(!pGET)
							{
								QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的表格定义，请确定Task资源正确 ItemType=%d",uItemIndex);
								OutContaner.Clear();
								return;
							}

							itemType = Serial2ItemType(uItemIndex);
							Ret = CreateItemRuler::CreateTaskItemProperty(itemType,it	);
							if(Ret)
							{
								if (	g_pItemMgr->GenItemGuid(it.m_ItemGUID) )
								{
									OutContaner.AddItem(it);
								}
							}
						}
						break;

					case ICLASS_EXTRABAG:
						{
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
							EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(uItemIndex);
							/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

							if(!pGET)
							{
								QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的表格定义，请确定ExtraBag资源正确 ItemType=%d",uItemIndex);
								OutContaner.Clear();
								return;
							}

							itemType = Serial2ItemType(uItemIndex);
							Ret = CreateItemRuler::CreateExtraBagProperty(itemType,it);
							if(Ret)
							{
								if ( g_pItemMgr->GenItemGuid(it.m_ItemGUID) )
								{
									OutContaner.AddItem(it);
								}
							}
						}
						break;

					default:
						QLogSystem::QUICK_LOG(QUICK_LOG_DEBUG,"找不到对应物品的类型 uClass=%d",uClass);
						OutContaner.Clear();
						return;
					}
				}
			}
		}
	}

	__UNGUARD__
}

