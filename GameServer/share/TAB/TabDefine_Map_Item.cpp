/*$T MapServer/Server/Item/ItemTemplateTable.cpp GC 1.140 10/10/07 10:07:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "item/Item_Helper.h"
#include "TabDefine_Map_Item.h"
#include "TAB.h"
#include "BaseTool.h"
#include "item/ItemBox.h"
#include "item/Item_Manager.h"
#include "FileDef.h"
#include "SplitStringLevelOne.h"
#include "SplitStringLevelTwo.h"
#include "item/Item_Ruler.h"

ItemTemplateTable	g_ItemTab;

using namespace TAB;

#define KSafeValue(x)	((x > 0) && (x != -1)) ? x : 0

/*
 =======================================================================================================================
 =======================================================================================================================
 */

int32 Compare_MonsterDropTab(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ MONSTER_DROP_TB	*pTB1 = (MONSTER_DROP_TB *) pArg1;
	MONSTER_DROP_TB			*pTB2 = (MONSTER_DROP_TB *) pArg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pTB1->m_DropId > pTB2->m_DropId)
		return 1;
	else if(pTB1->m_DropId < pTB2->m_DropId)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareEquipTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((SEquipTab *) pArg1)->m_IndexID;
	guid2 = ((SEquipTab *) pArg2)->m_IndexID;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Compare_DropAttTab(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iDelta1, iDelta2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	iDelta1 = ((SDropAttrTab *) pArg1)->m_DeltaLevel;
	iDelta2 = ((SDropAttrTab *) pArg2)->m_DeltaLevel;

	if(iDelta1 > iDelta2)
		return 1;
	else if(iDelta1 < iDelta2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Compare_GemInfoTabByTI(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 TableIndex1, TableIndex2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	TableIndex1 = ((SGemInfoTab *) pArg1)->m_nTableIndex;
	TableIndex2 = ((SGemInfoTab *) pArg2)->m_nTableIndex;

	if(TableIndex1 > TableIndex2)
		return 1;
	else if(TableIndex1 < TableIndex2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Compare_EquipSetTab(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 Serial1, Serial2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Serial1 = ((SEquipSetTab *) pArg1)->m_nEquipSetSerial;
	Serial2 = ((SEquipSetTab *) pArg2)->m_nEquipSetSerial;

	if(Serial1 > Serial2)
		return 1;
	else if(Serial1 < Serial2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareExtraBagInfoTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EXTRABAG_INFO_TB *) pArg1)->m_nTableIndex;
	guid2 = ((EXTRABAG_INFO_TB *) pArg2)->m_nTableIndex;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareChangePaiInfoTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((CHANGEPAI_INFO_TB *) pArg1)->m_nTableIndex;
	guid2 = ((CHANGEPAI_INFO_TB *) pArg2)->m_nTableIndex;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Compare_CommItemInfoTab(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((SMiscItemInfoTab *) pArg1)->m_nTableIndex;
	guid2 = ((SMiscItemInfoTab *) pArg2)->m_nTableIndex;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareSpecialRepairInfoTBByTI(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 TableIndex1, TableIndex2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	TableIndex1 = ((EQUIP_SPECIALREPAIR_TB *) pArg1)->m_UseItemID;
	TableIndex2 = ((EQUIP_SPECIALREPAIR_TB *) pArg2)->m_UseItemID;

	if(TableIndex1 > TableIndex2)
		return 1;
	else if(TableIndex1 < TableIndex2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareProductInfoTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	Serial1, Serial2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Serial1 = ((ITEM_PRODUCT_INFO_TB *) pArg1)->m_ProductID;
	Serial2 = ((ITEM_PRODUCT_INFO_TB *) pArg2)->m_ProductID;

	if(Serial1 > Serial2)
		return 1;
	else if(Serial1 < Serial2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareTaskItemInfoTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((TASKITEM_INFO_TB *) pArg1)->m_nTableIndex;
	guid2 = ((TASKITEM_INFO_TB *) pArg2)->m_nTableIndex;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareEquipColorChangeTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_COLORCHANGE_TB *) pArg1)->m_YellowItem;
	guid2 = ((EQUIP_COLORCHANGE_TB *) pArg2)->m_YellowItem;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 CompareEquipCopyTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_COPY_TB *) pArg1)->m_ItemId;
	guid2 = ((EQUIP_COPY_TB *) pArg2)->m_ItemId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareEquipRecallTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_RECALL_TB *) pArg1)->m_ItemId;
	guid2 = ((EQUIP_RECALL_TB *) pArg2)->m_ItemId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareTransItemPosTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((TRANSITEM_POS_TB *) pArg1)->m_MapId;
	guid2 = ((TRANSITEM_POS_TB *) pArg2)->m_MapId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareSuckBallTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((ATTR_SUCK_BALL_TB *) pArg1)->m_ItemId;
	guid2 = ((ATTR_SUCK_BALL_TB *) pArg2)->m_ItemId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareSuckAmuletTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((SERVER_ATTR_SUCK_AMULET_TB*) pArg1)->m_ItemId;
	guid2 = ((SERVER_ATTR_SUCK_AMULET_TB*) pArg2)->m_ItemId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareSuckBallSynTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((ATTR_SUCK_BALL_SYB_TB *) pArg1)->m_Level;
	guid2 = ((ATTR_SUCK_BALL_SYB_TB *) pArg2)->m_Level;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}
/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareEquipProduceTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_PRODUCE_TB *) pArg1)->m_EquipId;
	guid2 = ((EQUIP_PRODUCE_TB *) pArg2)->m_EquipId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareEquipBlueAttrTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_BLUEATTR_TB *) pArg1)->m_AttrIdx;
	guid2 = ((EQUIP_BLUEATTR_TB *) pArg2)->m_AttrIdx;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareEquipBlueIntensifyAttrTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_BLUE_INTENSIFY_TB *) pArg1)->m_AttrId;
	guid2 = ((EQUIP_BLUE_INTENSIFY_TB *) pArg2)->m_AttrId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
int32 CompareEquipSwitchTB(const void *pArg1, const void *pArg2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ GUID_t	guid1, guid2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	guid1 = ((EQUIP_SWITCH_TB *) pArg1)->m_EquipSourceId;
	guid2 = ((EQUIP_SWITCH_TB *) pArg2)->m_EquipSourceId;

	if(guid1 > guid2)
		return 1;
	else if(guid1 < guid2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareNewEquipBlueAttrTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ int32	nKey1, nKey2;

	nKey1 = ((NEW_EQUIP_BLUEATTR_TB *) pArg1)->m_AttrIdx;
	nKey2 = ((NEW_EQUIP_BLUEATTR_TB *) pArg2)->m_AttrIdx;

	if(nKey1 > nKey2)
		return 1;
	else if(nKey1 < nKey2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareNewEquipProduceTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ int32	nKey1, nKey2;

	nKey1 = ((NEW_EQUIP_PRODUCE_TB *) pArg1)->m_nEquipId;
	nKey2 = ((NEW_EQUIP_PRODUCE_TB *) pArg2)->m_nEquipId;

	if(nKey1 > nKey2)
		return 1;
	else if(nKey1 < nKey2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareConstAttrTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ int32	nKey1, nKey2;

	nKey1 = ((EQUIP_CONST_ATTR_TB *) pArg1)->m_AttrIndex;
	nKey2 = ((EQUIP_CONST_ATTR_TB *) pArg2)->m_AttrIndex;

	if(nKey1 > nKey2)
		return 1;
	else if(nKey1 < nKey2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}
/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareConstInfoTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ int32	nKey1, nKey2;

	nKey1 = ((EQUIP_CONST_INFO_TB *) pArg1)->m_ConstId;
	nKey2 = ((EQUIP_CONST_INFO_TB *) pArg2)->m_ConstId;

	if(nKey1 > nKey2)
		return 1;
	else if(nKey1 < nKey2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}
/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareConstActivePointTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ int32	nKey1, nKey2;

	nKey1 = ((EQUIP_CONST_ACTIVE_POINT_TB *) pArg1)->m_EquipPoint;
	nKey2 = ((EQUIP_CONST_ACTIVE_POINT_TB *) pArg2)->m_EquipPoint;

	if(nKey1 > nKey2)
		return 1;
	else if(nKey1 < nKey2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/ 
int32 CompareConstBindTB(const void *pArg1, const void *pArg2)
{
	__GUARD__ int32	nKey1, nKey2;

	nKey1 = ((EQUIP_CONST_BIND_TB *) pArg1)->m_NeedItemId;
	nKey2 = ((EQUIP_CONST_BIND_TB *) pArg2)->m_NeedItemId;

	if(nKey1 > nKey2)
		return 1;
	else if(nKey1 < nKey2)
		return -1;
	else
		return 0;
	__UNGUARD__ return 0;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SetEquipType(const char *pSplitString, uint32 nIntLength, uint32 *pInt)
{
	KCheck(nIntLength == EQUIP_TYPE_NUM);
	KCheck(pSplitString);
	KCheck(pInt);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne	pSplitL1;
	SplitStringLevelTwo	pSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pSplitL1.Reset();
	pSplitL2.Reset();
	pSplitL1.Init('|', &pSplitL2);
	pSplitL2.Init('~', NULL);
	pSplitL1.DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2.GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iLineCount < EQUIP_TYPE_NUM);
	for(int32 iLine = 0; iLine < iLineCount; ++iLine)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nPos = atoi(pSplitL2.GetResultLine(iLine));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch(nPos)
		{
		case EQUIP_MDAO:
		case EQUIP_MJIAN:
		case EQUIP_MGONG:
		case EQUIP_MHUOQIANG:
		case EQUIP_MCHUI:
		case EQUIP_MZHANG:
		case EQUIP_SDUN:
		case EQUIP_SJIAN:
		case EQUIP_SJIANZHI:
		case EQUIP_SZIDAN:
		case EQUIP_SGU:
		case EQUIP_SHAOJIAO:
		case EQUIP_CAP:
		case EQUIP_NECKLACE:
		case EQUIP_SHOULDER:
		case EQUIP_ARMOR:
		case EQUIP_CUFF:
		case EQUIP_HAND:
		case EQUIP_SASH:
		case EQUIP_BOOT:
		case EQUIP_RING:
		case EQUIP_ADORN:
		case EQUIP_CRUSADE_MASTER_HAND:		//十字军主手
		case EQUIP_FIRE_ENVOY_MASTER_HAND:	//圣火使主手
		case EQUIP_ASSASSIN_MASTER_HAND:	//刺客主手
		case EQUIP_GUARDS_MASTER_HAND:		//近卫军主手
		case EQUIP_FRIAR_MASTER_HAND:		//隐修士主手
		case EQUIP_LAMA_MASTER_HAND:		//喇嘛主手
		case EQUIP_CRUSADE_ASSIST_HAND:		//十字军副手
		case EQUIP_FIRE_ENVOY_ASSIST_HAND:	//圣火使副手
		case EQUIP_ASSASSIN_ASSIST_HAND:	//刺客副手
		case EQUIP_GUARDS_ASSIST_HAND:		//近卫军副手
		case EQUIP_FRIAR_ASSIST_HAND:		//隐修士副手
		case EQUIP_LAMA_ASSIST_HAND:		//喇嘛副手
			{
				pInt[nPos] = 1;
			}
			break;

		default:
			KCheck(0);
			break;
		}
	}
}

void SetNewItem(const char *pSplitString, uint32 *pInt)
{
	KCheck(pSplitString);
	KCheck(pInt);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne	pSplitL1;
	SplitStringLevelTwo	pSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pSplitL1.Reset();
	pSplitL2.Reset();
	pSplitL1.Init('|', &pSplitL2);
	pSplitL2.Init('~', NULL);
	pSplitL1.DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2.GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iLineCount == HEQUIP_SUIT);
	uint32 uPointCount =0;
	for(int32 iLine = 0; iLine < iLineCount; ++iLine)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nItemId = atoi(pSplitL2.GetResultLine(iLine));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/		
		pInt[uPointCount++] = nItemId;
	}
}

void SetEquipPoint(const char *pSplitString, uint32 nIntLength, uint32 *pInt)
{
	KCheck(nIntLength == HEQUIP_NUMBER);
	KCheck(pSplitString);
	KCheck(pInt);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne	pSplitL1;
	SplitStringLevelTwo	pSplitL2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	pSplitL1.Reset();
	pSplitL2.Reset();
	pSplitL1.Init('|', &pSplitL2);
	pSplitL2.Init('~', NULL);
	pSplitL1.DoSplit(pSplitString);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iLineCount = pSplitL2.GetResultLineCount();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iLineCount < HEQUIP_NUMBER);
	uint32 uPointCount =0;
	for(int32 iLine = 0; iLine < iLineCount; ++iLine)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nPos = atoi(pSplitL2.GetResultLine(iLine));
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		if (nPos>=HEQUIP_MAINHAND && nPos<=HEQUIP_AMULET)
		{
			pInt[uPointCount++] = nPos;
		}
		else
		{
			KCheck(0);
		}
	}
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemTemplateTable::ItemTemplateTable()
{
	m_pEquipTableData = NULL;
	m_pAttLevelTableData = NULL;
	m_pEquipAttSetTableData = NULL;

	m_pTaskItemInfoData = NULL;

	m_pDropBoxTableData = NULL;
	m_pMonsterDropTableData = NULL;
	m_pGemInfoData = NULL;
	m_EquipHoleInfoData = NULL;

	m_EquipBindInfoData = NULL;
	m_pProductInfoData = NULL;
	m_EquipSpecialRepairData = NULL;
	m_MaterialLevelInfoData = NULL;
	m_EquipExtraInfoData = NULL;
	m_pExtraBagInfoData = NULL;
	m_EquipChainInfoData = NULL;
	m_EquipSoulInfoData = NULL;
	m_pChangePaiInfoData = NULL;

	m_pCommItemInfoData = NULL;
	m_pDropAttData = NULL;
	m_pDropPosData = NULL;

	m_pEquipSetData = NULL;
	m_pItemRulerData = NULL;

	m_pMarryEffectData = NULL;
	m_pFriendEffectData = NULL;
	m_pEquipActivationData = NULL;
	m_pEquipColorChangeData = NULL;
	m_pEquipPurpleReworkData = NULL;
	m_pEquipPurpleAttrData = NULL;
	m_pGemReworkData = NULL;
	m_pEquipCopyData = NULL;
	m_pTransItemPosData = NULL;
	m_pAttrSuckBallData = NULL;
	m_pAttrSuckAmuletData = NULL;

	memset(m_nEquipPointInfo, 0, sizeof(uint32) * HEQUIP_NUMBER);
	memset(m_nPaiInfo, 0, sizeof(PAI_INFO) * EQUIP_PAI_NUM);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ItemTemplateTable::~ItemTemplateTable()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::Clear()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete_ARRAY(m_pEquipTableData);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KSafeDelete_ARRAY(m_pAttLevelTableData);
	KSafeDelete_ARRAY(m_pEquipAttSetTableData);
	KSafeDelete_ARRAY(m_pTaskItemInfoData);
	KSafeDelete_ARRAY(m_pDropBoxTableData);
	KSafeDelete_ARRAY(m_pMonsterDropTableData);
	KSafeDelete_ARRAY(m_pGemInfoData);
	KSafeDelete_ARRAY(m_EquipHoleInfoData);

	KSafeDelete_ARRAY(m_EquipBindInfoData);
	KSafeDelete_ARRAY(m_EquipSpecialRepairData);
	KSafeDelete_ARRAY(m_pProductInfoData);
	KSafeDelete_ARRAY(m_MaterialLevelInfoData);
	KSafeDelete_ARRAY(m_EquipExtraInfoData);
	KSafeDelete_ARRAY(m_pExtraBagInfoData);
	KSafeDelete_ARRAY(m_EquipChainInfoData);
	KSafeDelete_ARRAY(m_EquipSoulInfoData);
	KSafeDelete_ARRAY(m_pChangePaiInfoData);

	KSafeDelete_ARRAY(m_pCommItemInfoData);
	KSafeDelete_ARRAY(m_pDropAttData);
	KSafeDelete_ARRAY(m_pDropPosData);
	KSafeDelete_ARRAY(m_pEquipSetData);
	KSafeDelete_ARRAY(m_pItemRulerData);
	KSafeDelete_ARRAY(m_pEquipActivationData);
	KSafeDelete_ARRAY(m_pEquipColorChangeData);
	KSafeDelete_ARRAY(m_pEquipPurpleReworkData);
	KSafeDelete_ARRAY(m_pEquipPurpleAttrData);
	KSafeDelete_ARRAY(m_pGemReworkData);
	KSafeDelete_ARRAY(m_pEquipCopyData);
	KSafeDelete_ARRAY(m_pAttrSuckBallData);
	KSafeDelete_ARRAY(m_pAttrSuckAmuletData);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ItemTemplateTable::Init()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	m_nHashOffSet = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nAttLevelCount = 0;
	m_nEquipAttSetCount = 0;
	m_nEquipCount = 0;
	m_nTaskItemCount = 0;

	m_nDropBoxCount = 0;
	m_nMonsterDropCount = 0;

	m_nEquipBindInfoCount = 0;
	m_nSpecialRepairCount = 0;
	m_nProductCount = 0;
	m_nMaterialLevelInfoCount = 0;
	m_nEquipExtraInfoCount = 0;
	m_nExtraBagInfoCount = 0;
	m_nEquipChainInfoCount = 0;
	m_nEquipSoulInfoCount = 0;
	m_nChangePaiInfoCount = 0;

	m_nGemCount = 0;
	m_nGemCount = 0;

	m_nCommItemCount = 0;

	m_nDropAttCount = 0;
	m_nDropPosCount = 0;
	m_nEquipSetCount = 0;

	m_nItemRulerCount = 0;

	m_nMarryEffectCount = 0;
	m_nFriendEffectCount = 0;
	m_nEquipActivationCount = 0;
	m_nEquipColorChangeCount = 0;
	m_nEquipPurpleReworkCount = 0;
	m_nEquipPurpleAttrCount = 0;
	m_nEquipPurpleAttrRateCount = 0;
	m_uGemReworkCount = 0;
	m_uTransItemPosCount = 0;
	m_uAttrSuckAmuletCount = 0;
	m_uAttrSuckBallCount = 0;
	m_uEquipProduceCount = 0;
	m_uEquipBlueAttrCount = 0;
	m_uEquipBlueIntensifyCount = 0;

	m_nEquipConstAttrCount = 0;
	memset(m_nEquipConstAttrMaxSed,0,sizeof(m_nEquipConstAttrMaxSed));
	memset(m_nEquipConstAttrTypeCount,0,sizeof(m_nEquipConstAttrTypeCount));
	m_nEquipConstInfoCount = 0;
	m_nEquipConstMaxSed = 0;
	m_nEquipConstActivePointCount = 0;
	m_nEquipConstBindCount = 0;

	InitEquipTable();
	InitEquipHoleInfoTable();
	InitEquipLevelupInfoTable();
	InitEquipBindInfoTable();
	InitSpecialRepairInfoTable();
	InitAttLevelTable();
	InitEquipATTSetTable();
	InitProductInfoTable();
	InitMaterialLevelInfoTable();
	InitEquipExtraInfoTable();
	InitEquipPointInfoTable();
	InitChangePaiInfoTable();
	InitPaiInfoTable();
	InitEquipChainInfoTable();
	InitEquipSoulInfoTable();
	InitExtraBagInfoTable();

	InitMonsterDropTable();
	InitGemInfoTable();

	InitCommItemInfoTable();
	InitTaskItemInfoTable();

	InitDropAttTable();
	InitItemDropPos();
	InitEquipSetAttrTable();
	InitEffectMarryTable();
	InitEffectFriend();

	InitItemRulerTable();

	InitFriendGiftTable();
	InitEquipActivationTable();
	InitEquipColorChangeTable();
	InitEquipPurpleReworkTable();
	InitEquipPurpleAttrTable();
	InitGemReworkTable();
	InitEquipCopyTable();
	InitEquipRecallTable();
	InitTransItemPosTable();
	InitAttrSuckBallTable();
	InitAttrSuckAmuletTable();
	InitAttrSuckBallSynTable();
	InitEquipProduceTable();
	InitEquipBlueAttrTable();
	InitEquipBlueIntensifyTable();
	InitEquipSwitchTable();
	InitChangeAppearanceTable();
	InitNewEquipBlueAttrTable();
	InitNewEquipProduceTable();

	//星座铭刻
	InitEquipConstAttrTable();
	InitEquipConstInfoTable();
	InitEquipConstActivePointTable();
	InitEquipConstBindTable();

	//特殊道具
	m_nItemSpecialCount =0;
	m_pItemSpecialData = NULL;
	InitItemSpecialTable();

	//荣誉铭刻
	m_nEquipHonorBindCount = 0;
	m_pEquipHonorBindData = NULL;
	InitEquipHonorBindTable();

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipATTSetTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ATTSetTBData { TBIndex = 0, TBName = 1, TBProbability = 2, TBReqLevel, TBAttBegin, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_BLUE_ATTR_SET);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipAttSetCount = iTableCount;
	m_pEquipAttSetTableData = new EQUIP_ATT_SET_TB[m_nEquipAttSetCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	SumRate = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nSetID = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(nSetID != i);

		m_pEquipAttSetTableData[i].m_IndexID = nSetID;
		m_pEquipAttSetTableData[i].m_AttSetRate = ThirdFile.Search_Posistion(i, TBProbability)->iValue;
		m_pEquipAttSetTableData[i].m_ReqLevel = ThirdFile.Search_Posistion(i, TBReqLevel)->iValue;
		SumRate += m_pEquipAttSetTableData[i].m_AttSetRate;
		m_pEquipAttSetTableData[i].m_SumRate = SumRate;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iATTID = -1;
		int32	iColumn = TBAttBegin;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 nAtt = 0; nAtt < MAX_EQUIP_EXT_ATTR; ++nAtt)
		{
			iATTID = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			if(iATTID >= 0)
			{
				m_pEquipAttSetTableData[i].m_AttrInfo[m_pEquipAttSetTableData[i].m_AttCount].m_Attr = (ITEM_PROPERTY) iATTID;

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				const char	*pSplitString = ThirdFile.Search_Posistion(i, ++iColumn)->pString;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				SetEquipType
				(
					pSplitString,
					EQUIP_TYPE_NUM,
					m_pEquipAttSetTableData[i].m_AttrInfo[m_pEquipAttSetTableData[i].
						m_AttCount].m_nValidEquipType
				);
				++m_pEquipAttSetTableData[i].m_AttCount;
			}
			else
			{
				break;
			}

			++iColumn;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitAttLevelTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ATTAttLevelData { TBIndex = 0, TBAttBegin = 2, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_BLUE_ATTR_LEVEL);
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nAttLevelCount = iTableCount;
	m_pAttLevelTableData = new EQUIP_ATT_LEVEL_TB[MAX_ATT_COUNT];

	for(int32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~*/
		int32	iATTID = -1;
		/*~~~~~~~~~~~~~~~~*/

		iATTID = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pAttLevelTableData[iATTID].m_AttID = (ITEM_PROPERTY) iATTID;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iATTValue = 0;
		int32	iColumn = TBAttBegin;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 nAtt = 1; nAtt <= MAX_EQUIP_LEVEL; ++nAtt)
		{
			iATTValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			if(iATTValue > 0)
			{
				m_pAttLevelTableData[iATTID].m_Attr[nAtt] = iATTValue;
			}

			iColumn = iColumn + 1;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ItemTBData
	{
		TBIndex			= 0,
		TBClass,
		TBType,
		TBItemIndex,
		TBColor,
		TBEquipPoint,
		TBRulerID,
		TBSet,
		TBReqLevel,
		TBReqInherenceLevel,	// rj 2010-8-23 天赋及个人等级字段索引枚举
		TBReqPersonLevel,
		TBBasePrice,
		TBMaxDur,
		TBTermHour,
		TBLevel,
		TBBaseGem,
		TBMaxGem,
		TBReqJob,
		TBPaiType,
		TBScore,
		TBBaseNearAtt,
		TBBaseFarAtt,
		TBBaseMgicAtt,
		TBBaseNearDefence,
		TBBaseFarDefence,
		TBBaseMagicDecence,
		TBAttBegin,
		TBAFFSkillBegin		= TBAttBegin + 2 * MAX_EQUIP_EXT_ATTR,
		TBEffSkillBegin		= TBAFFSkillBegin + 2 * MAX_EQUIP_AFFIX_SKILL,
		TBScriptID		= TBEffSkillBegin + 2 * MAX_EQUIP_EFFECT_SKILL,
		TBParamType,
		TBParamValue,
		TBConsumeValue,
		TBMinPickLevel,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_BASE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipCount = iTableCount;
	m_pEquipTableData = new SEquipTab[iTableCount];

	for(int32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~*/
		int32	iValue = 0;
		int32	iColumn = 0;
		/*~~~~~~~~~~~~~~~~*/

		m_pEquipTableData[i].m_IndexID = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pEquipTableData[i].m_ItemType.m_Class = ThirdFile.Search_Posistion(i, TBClass)->iValue;
		m_pEquipTableData[i].m_ItemType.m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
		m_pEquipTableData[i].m_ItemType.m_Index = ThirdFile.Search_Posistion(i, TBItemIndex)->iValue;
		m_pEquipTableData[i].m_Color = ThirdFile.Search_Posistion(i, TBColor)->iValue;
		m_pEquipTableData[i].m_EquipPoint = ThirdFile.Search_Posistion(i, TBEquipPoint)->iValue;
		m_pEquipTableData[i].m_RulerID = ThirdFile.Search_Posistion(i, TBRulerID)->iValue;
		m_pEquipTableData[i].m_EquipSetNum = ThirdFile.Search_Posistion(i, TBSet)->iValue;

		m_pEquipTableData[i].m_BasePrice = ThirdFile.Search_Posistion(i, TBBasePrice)->iValue;
		m_pEquipTableData[i].m_MaxDur = ThirdFile.Search_Posistion(i, TBMaxDur)->iValue;
		m_pEquipTableData[i].m_iTermHour = ThirdFile.Search_Posistion(i, TBTermHour)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char		*pSplitString = ThirdFile.Search_Posistion(i, TBLevel)->pString;
		SplitStringLevelOne	pSplitL1;
		SplitStringLevelTwo	pSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitL1.Reset();
		pSplitL2.Reset();
		pSplitL1.Init('|', &pSplitL2);
		pSplitL2.Init('~', NULL);
		pSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLevelCount = pSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 nID = 0; nID < iLevelCount; ++nID)
		{
			m_pEquipTableData[i].m_Level[nID] = atoi(pSplitL2.GetResultLine(nID));
			KCheck(m_pEquipTableData[i].m_Level[nID] <= MAX_EQUIP_LEVELUP_NUM);
			++m_pEquipTableData[i].m_LevelCount;
		}

		KCheck(m_pEquipTableData[i].m_LevelCount > 0);

		m_pEquipTableData[i].m_BaseGemHole = ThirdFile.Search_Posistion(i, TBBaseGem)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iMaxGem = ThirdFile.Search_Posistion(i, TBMaxGem)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_pEquipTableData[i].m_MAXGemHole = KSafeValue(iMaxGem);
		m_pEquipTableData[i].m_PrefessionReq = ThirdFile.Search_Posistion(i, TBReqJob)->iValue;

		if(ThirdFile.Search_Posistion(i, TBPaiType)->iValue > 0)
		{
			m_pEquipTableData[i].m_PaiType = ThirdFile.Search_Posistion(i, TBPaiType)->iValue;
		}

		m_pEquipTableData[i].m_EquipScore = ThirdFile.Search_Posistion(i, TBScore)->iValue;
		m_pEquipTableData[i].m_NearAttack = ThirdFile.Search_Posistion(i, TBBaseNearAtt)->iValue;
		m_pEquipTableData[i].m_FarAttack = ThirdFile.Search_Posistion(i, TBBaseFarAtt)->iValue;
		m_pEquipTableData[i].m_MagicAttack = ThirdFile.Search_Posistion(i, TBBaseMgicAtt)->iValue;
		m_pEquipTableData[i].m_NearDefence = ThirdFile.Search_Posistion(i, TBBaseNearDefence)->iValue;
		m_pEquipTableData[i].m_FarDefence = ThirdFile.Search_Posistion(i, TBBaseFarDefence)->iValue;
		m_pEquipTableData[i].m_MagicDefense = ThirdFile.Search_Posistion(i, TBBaseMagicDecence)->iValue;

		pSplitString = ThirdFile.Search_Posistion(i, TBReqLevel)->pString;

		pSplitL1.Reset();
		pSplitL2.Reset();
		pSplitL1.Init('|', &pSplitL2);
		pSplitL2.Init('~', NULL);
		pSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = pSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int32 nID = 0; nID < iLineCount; ++nID)
		{
			m_pEquipTableData[i].m_ReqLevel[nID] = atoi(pSplitL2.GetResultLine(nID));
			KCheck(m_pEquipTableData[i].m_ReqLevel[nID] <= MAX_EQUIP_LEVEL);
			++m_pEquipTableData[i].m_ReqLevelCount;
		}

		KCheck(m_pEquipTableData[i].m_ReqLevelCount > 0);

		// rj 2010-8-23 天赋及个人等级初始化表值
		m_pEquipTableData[i].m_iReqInherenceLevel = ThirdFile.Search_Posistion(i, TBReqInherenceLevel)->iValue;
		m_pEquipTableData[i].m_iReqPersonLevel = ThirdFile.Search_Posistion(i, TBReqPersonLevel)->iValue;

		/*~~~~~~~~~~~~~~~~~~~*/
		int32	iATTID = -1;
		int32	iATTValue = -1;
		/*~~~~~~~~~~~~~~~~~~~*/

		iColumn = TBAttBegin;
		for(int32 nAtt = 0; nAtt < MAX_EQUIP_EXT_ATTR; ++nAtt)
		{
			iATTID = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			++iColumn;
			iATTValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			if((iATTID >= 0) && (iATTValue > 0))
			{
				m_pEquipTableData[i].m_Attr[m_pEquipTableData[i].m_AttCount].m_AttrType = (ITEM_PROPERTY) iATTID;
				m_pEquipTableData[i].m_Attr[m_pEquipTableData[i].m_AttCount].m_Value.m_Value = iATTValue;
				++m_pEquipTableData[i].m_AttCount;
			}

			++iColumn;
		}

		/*~~~~~~~~~~~~~~~~~~~~*/
		int32	iSkillID = -1;
		int32	nSkillLevel = 0;
		/*~~~~~~~~~~~~~~~~~~~~*/

		iColumn = TBAFFSkillBegin;
		for(int32 nSkill = 0; nSkill < MAX_EQUIP_AFFIX_SKILL; ++nSkill)
		{
			iSkillID = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			iColumn = iColumn + 1;
			nSkillLevel = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			if((nSkillLevel > 0) && (iSkillID > 0))
			{
				m_pEquipTableData[i].m_AffixSkill[m_pEquipTableData[i].m_AffSkillCount].m_nSkillID = iSkillID;
				m_pEquipTableData[i].m_AffixSkill[m_pEquipTableData[i].m_AffSkillCount].m_nLevel = nSkillLevel;
				++m_pEquipTableData[i].m_AffSkillCount;
			}

			iColumn = iColumn + 1;
		}

		iSkillID = -1;
		nSkillLevel = 0;
		iColumn = TBAFFSkillBegin;
		for(int32 nSkill = 0; nSkill < MAX_EQUIP_EFFECT_SKILL; ++nSkill)
		{
			iSkillID = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			iColumn = iColumn + 1;
			nSkillLevel = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			if((nSkillLevel > 0) && (iSkillID > 0))
			{
				m_pEquipTableData[i].m_EffectSkill[m_pEquipTableData[i].m_EffSkillCount].m_nSkillID = iSkillID;
				m_pEquipTableData[i].m_EffectSkill[m_pEquipTableData[i].m_EffSkillCount].m_nLevel = nSkillLevel;
				++m_pEquipTableData[i].m_EffSkillCount;
			}

			iColumn = iColumn + 1;
		}

		m_pEquipTableData[i].m_nScriptID = ThirdFile.Search_Posistion(i, TBScriptID)->iValue;
		KCheck(m_pEquipTableData[i].m_nScriptID <= 0 || m_pEquipTableData[i].m_nScriptID >= 100000);
		m_pEquipTableData[i].m_ParamType = ThirdFile.Search_Posistion(i, TBParamType)->iValue;
		m_pEquipTableData[i].m_ParamValue = ThirdFile.Search_Posistion(i, TBParamValue)->iValue;
		m_pEquipTableData[i].m_ConsumeValue = ThirdFile.Search_Posistion(i, TBConsumeValue)->iValue;
		m_pEquipTableData[i].m_minPickLevel = ThirdFile.Search_Posistion(i, TBMinPickLevel)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitGemInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum GemInfoTBData
	{
		TBTableIndex		= 0,
		TBClass,
		TBType,
		TBIndex,
		TBResID,
		TBRulerID,
		TBEquipType,
		TBName,
		TBDesc,
		TBPrice,
		TBSellPrice,
		TBUsePrice,
		TBReqEquipLevel,
		TBBroadCast,
		TBEffectBegin,
		TBGemReqBegin		= TBEffectBegin + MAX_GEM_ATT * 2,
		TBShowLevel		= 27,
		TBParamType,
		TBParamValue,
		TBConsumeValue,
		TBGemReworkIndex	= 41,
		TBGemUninst_IsBind	= 42,
		TBMinPickLevel,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GEM_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nGemCount = iTableCount;
	m_pGemInfoData = new SGemInfoTab[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_nGemCount; i++)
	{
		m_pGemInfoData[i].m_nTableIndex = ThirdFile.Search_Posistion(i, TBTableIndex)->iValue;
		m_pGemInfoData[i].m_ItemType.m_Class = ThirdFile.Search_Posistion(i, TBClass)->iValue;
		m_pGemInfoData[i].m_ItemType.m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
		m_pGemInfoData[i].m_ItemType.m_Index = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pGemInfoData[i].m_nRulerID = ThirdFile.Search_Posistion(i, TBRulerID)->iValue;
		m_pGemInfoData[i].m_nPrice = ThirdFile.Search_Posistion(i, TBPrice)->iValue;
		m_pGemInfoData[i].m_nSellPrice = ThirdFile.Search_Posistion(i, TBSellPrice)->iValue;
		m_pGemInfoData[i].m_nUsePrice = ThirdFile.Search_Posistion(i, TBUsePrice)->iValue;
		m_pGemInfoData[i].m_nReqEquipLevel = ThirdFile.Search_Posistion(i, TBReqEquipLevel)->iValue;
		m_pGemInfoData[i].m_bBroadCast = ThirdFile.Search_Posistion(i, TBBroadCast)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char		*pSplitString = ThirdFile.Search_Posistion(i, TBEquipType)->pString;
		SplitStringLevelOne	pSplitL1;
		SplitStringLevelTwo	pSplitL2;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitL1.Reset();
		pSplitL2.Reset();
		pSplitL1.Init('|', &pSplitL2);
		pSplitL2.Init('~', NULL);
		pSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = pSplitL2.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(iLineCount < MAX_BASE_EQUIP_COUNT);
		for(int32 iLine = 0; iLine < iLineCount; ++iLine)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	nPos = atoi(pSplitL2.GetResultLine(iLine));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			switch(nPos)
			{
			case EQUIP_MDAO:
			case EQUIP_MJIAN:
			case EQUIP_MGONG:
			case EQUIP_MHUOQIANG:
			case EQUIP_MCHUI:
			case EQUIP_MZHANG:
			case EQUIP_SDUN:
			case EQUIP_SJIAN:
			case EQUIP_SJIANZHI:
			case EQUIP_SZIDAN:
			case EQUIP_SGU:
			case EQUIP_SHAOJIAO:
			case EQUIP_CAP:
			case EQUIP_NECKLACE:
			case EQUIP_SHOULDER:
			case EQUIP_ARMOR:
			case EQUIP_CUFF:
			case EQUIP_HAND:
			case EQUIP_SASH:
			case EQUIP_BOOT:
			case EQUIP_RING:
			case EQUIP_ADORN:
			case EQUIP_CRUSADE_MASTER_HAND:		//十字军主手
			case EQUIP_FIRE_ENVOY_MASTER_HAND:	//圣火使主手
			case EQUIP_ASSASSIN_MASTER_HAND:	//刺客主手
			case EQUIP_GUARDS_MASTER_HAND:		//近卫军主手
			case EQUIP_FRIAR_MASTER_HAND:		//隐修士主手
			case EQUIP_LAMA_MASTER_HAND:		//喇嘛主手
			case EQUIP_CRUSADE_ASSIST_HAND:		//十字军副手
			case EQUIP_FIRE_ENVOY_ASSIST_HAND:	//圣火使副手
			case EQUIP_ASSASSIN_ASSIST_HAND:	//刺客副手
			case EQUIP_GUARDS_ASSIST_HAND:		//近卫军副手
			case EQUIP_FRIAR_ASSIST_HAND:		//隐修士副手
			case EQUIP_LAMA_ASSIST_HAND:		//喇嘛副手
				{
					m_pGemInfoData[i].m_EquipType[nPos] = 1;
				}
				break;

			default:
				KCheck(0);
				break;
			}
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iColumn = TBEffectBegin;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(uint32 j = 0; j < MAX_GEM_ATT; j++)
		{
			KCheck(iColumn < iTableColumn);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(iValue >= 0)
			{
				m_pGemInfoData[i].m_GenAttr[j].m_AttrType = (ITEM_PROPERTY) ThirdFile.Search_Posistion
					(
						i,
						iColumn++
					)->iValue;
				m_pGemInfoData[i].m_GenAttr[j].m_Value.m_Value = ThirdFile.Search_Posistion
					(
						i,
						iColumn++
					)->iValue;
				++m_pGemInfoData[i].m_AttCount;
			}
			else
				break;
		}

		iColumn = TBGemReqBegin;
		for(uint32 j = 0; j < MAX_GEM_REQ; j++)
		{
			KCheck(iColumn < iTableColumn);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(iValue >= 0)
			{
				m_pGemInfoData[i].m_GemReqAttr[j].m_GemType = (ITEM_PROPERTY) ThirdFile.Search_Posistion(i, iColumn++)->iValue;
				m_pGemInfoData[i].m_GemReqAttr[j].m_Value.m_Value = ThirdFile.Search_Posistion
					(
						i,
						iColumn++
					)->iValue;
				++m_pGemInfoData[i].m_GemReqCount;
			}
			else
				break;
		}

		m_pGemInfoData[i].m_ShowLevel = ThirdFile.Search_Posistion(i, TBShowLevel)->iValue;
		m_pGemInfoData[i].m_ParamType = ThirdFile.Search_Posistion(i, TBParamType)->iValue;
		m_pGemInfoData[i].m_ParamValue = ThirdFile.Search_Posistion(i, TBParamValue)->iValue;
		m_pGemInfoData[i].m_ConsumeValue = ThirdFile.Search_Posistion(i, TBConsumeValue)->iValue;
		m_pGemInfoData[i].m_GemReworkIndex = ThirdFile.Search_Posistion(i, TBGemReworkIndex)->iValue;
		m_pGemInfoData[i].m_UninstalledIsBind = ThirdFile.Search_Posistion(i, TBGemUninst_IsBind)->iValue;
		m_pGemInfoData[i].m_minPickLevel = ThirdFile.Search_Posistion(i, TBMinPickLevel)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipHoleInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipHoleInfoTBData
	{
		TBHoleNum		= 0,
		TBReqItem,
		TBReqItemNum	= 47,
		TBReqMoney,
		TBRate,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EUIPHOLE_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipHoleInfoCount = iTableCount;
	KCheck(m_nEquipHoleInfoCount == MAX_ITEM_GEM);

	m_EquipHoleInfoData = new EQUIPHOLE_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_nEquipHoleInfoCount; i++)
	{
		KCheck(i == (ThirdFile.Search_Posistion(i, TBHoleNum)->iValue - 1));
		m_EquipHoleInfoData[i].m_ReqItemNum = ThirdFile.Search_Posistion(i, TBReqItemNum)->iValue;
		for(uint32 m = EQUIP_MDAO; m < EQUIP_TYPE_NUM; ++m)
		{
			m_EquipHoleInfoData[i].m_ReqItem[m] = ThirdFile.Search_Posistion
				(
					i,
					TBReqItem + m - EQUIP_MDAO
				)->iValue;
		}

		m_EquipHoleInfoData[i].m_ReqMoney = ThirdFile.Search_Posistion(i, TBReqMoney)->iValue;
		m_EquipHoleInfoData[i].m_Rate = ThirdFile.Search_Posistion(i, TBRate)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipLevelupInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipLevelupInfoTBData
	{
		TBLevel				= 1,
		TBEquipPoint,
		TBEquipLevelReqGemID,
		TBItemNum			= TBEquipLevelReqGemID + MAX_LEVELUP_GEMREQ_NUM,
		TBPunishment		= TBItemNum + MAX_LEVELUP_GEMREQ_NUM,
		TBReqMoney,
		TBEffectRate		= TBReqMoney + MAX_LEVELUP_GEMREQ_NUM,
		TBEffectAttrType,
		TBReqLevel,
		TBLevelType,
		TBEquipLevelReq,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EUIPLEVEUP_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	int32 interval = TBEquipLevelReq + MAX_LEVELUP_GEMREQ_NUM - TBEquipLevelReqGemID;

	for(uint32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	equipPoint = ThirdFile.Search_Posistion(i, TBEquipPoint)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(equipPoint >= 0);
		KCheck(equipPoint < HEQUIP_NUMBER);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nLevel = ThirdFile.Search_Posistion(i, TBLevel)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(nLevel <= MAX_EQUIP_LEVELUP_NUM);

		for ( int32 type = EQUIPLEVEL_TYPE0; type < EQUIPLEVEL_TYPENUM; type++ )
		{
			for(uint32 j = 0; j < MAX_LEVELUP_GEMREQ_NUM; ++j)
			{
				m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_EquipLevelReqGemID[j] = ThirdFile.Search_Posistion(i, j + TBEquipLevelReqGemID + interval * type)->iValue;
				m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_SuccessRate[j] = ThirdFile.Search_Posistion(i, j + TBItemNum + interval * type)->iValue;
				m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_ReqMoney[j] = ThirdFile.Search_Posistion(i, j + TBReqMoney + interval * type)->iValue;
				m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_EquipLevelReq[j] = ThirdFile.Search_Posistion(i, j + TBEquipLevelReq + interval * type)->iValue;
			}

			m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_Punishment = ThirdFile.Search_Posistion(i, TBPunishment + interval * type)->iValue;
			m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_EffectRate = ThirdFile.Search_Posistion(i, TBEffectRate + interval * type)->iValue;
			m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_EffectAttrType = ThirdFile.Search_Posistion(i, TBEffectAttrType + interval * type)->iValue;
			m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_ReqLevel = ThirdFile.Search_Posistion(i, TBReqLevel + interval * type)->iValue;
			m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[nLevel - 1][type].m_LevelType = ThirdFile.Search_Posistion(i, TBLevelType + interval * type)->iValue;
		}

	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipBindInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipLevelupInfoTBData 
	{ 
		TBBindLevel = 0,
		TBEffectRate,
		TBReqItem,
		TBNeedMoney = TBReqItem + MAX_BIND_GEMREQ_NUM, 
		TBNeedLevel = TBNeedMoney + MAX_BIND_GEMREQ_NUM,
	};
	
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EUIPBIND_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipBindInfoCount = iTableCount;
	KCheck(m_nEquipBindInfoCount == MAX_EQUIP_BIND_LEVEL);

	m_EquipBindInfoData = new EQUIP_BIND_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_nEquipBindInfoCount; i++)
	{
		KCheck(i == (ThirdFile.Search_Posistion(i, TBBindLevel)->iValue - 1));

		m_EquipBindInfoData[i].m_EffectRate = ThirdFile.Search_Posistion(i, TBEffectRate)->iValue;

		for(uint32 j = 0; j < MAX_BIND_GEMREQ_NUM; ++j)
		{
			m_EquipBindInfoData[i].m_GemID[j] = ThirdFile.Search_Posistion(i, TBReqItem + j)->iValue;
			m_EquipBindInfoData[i].m_nReqMoney[j] = ThirdFile.Search_Posistion(i, TBNeedMoney +j)->iValue;
			m_EquipBindInfoData[i].m_EquipLevelReq[j] = ThirdFile.Search_Posistion(i, TBNeedLevel +j)->iValue;
		}

	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitSpecialRepairInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum SpecialRepairInfoTBData { TBDestItem = 0, TBReqItem, TBReqItemCount, TBNeedMoney, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_SPECIALREPAIR_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nSpecialRepairCount = iTableCount;

	m_EquipSpecialRepairData = new EQUIP_SPECIALREPAIR_TB[iTableCount];
	for(uint32 i = 0; i < m_nSpecialRepairCount; i++)
	{
		m_EquipSpecialRepairData[i].m_RepairItemID = ThirdFile.Search_Posistion(i, TBDestItem)->iValue;
		m_EquipSpecialRepairData[i].m_UseItemID = ThirdFile.Search_Posistion(i, TBReqItem)->iValue;
		m_EquipSpecialRepairData[i].m_UseItemCount = ThirdFile.Search_Posistion(i, TBReqItemCount)->iValue;
		m_EquipSpecialRepairData[i].m_nReqMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitProductInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ProductCreateInfo { TBMaterialType = 0, TBMaterialNum, TBCreateNeedLevel, TBSplitRate, TBCreatInfoNum, };
	enum ProductRemouldInfo { TBRemouldMaterialType = 0, TBRemouldMaterialNum, TBRemouldNeedLevel, TBRemouldInfoNum, };
	enum ProductInfoTBData
	{
		TBPrescriptionID		= 0,
		TBProductID,
		TBPrescriptionName,
		TBProductNum,
		TBCreateInfo,
		TBRemouldInfo			= TBCreateInfo + TBCreatInfoNum * MAX_CREATE_MATERIAL_NUM,
		TBOperateTime			= TBRemouldInfo + TBRemouldInfoNum * MAX_REMOULD_MATERIAL_NUM,
		TBScriptID,
		TBCreateMoney,
		TBRemouldMoney,
		TBLevel,
		TBEquipType,
		TBAtt,
		TBNPC,
		TBFixed,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_PRODUCT_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nProductCount = iTableCount;
	m_pProductInfoData = new ITEM_PRODUCT_INFO_TB[iTableCount];

	for(uint32 i = 0; i < m_nProductCount; i++)
	{
		m_pProductInfoData[i].m_ProductID = ThirdFile.Search_Posistion(i, TBProductID)->iValue;
		m_pProductInfoData[i].m_PrescriptionID = ThirdFile.Search_Posistion(i, TBPrescriptionID)->iValue;
		m_pProductInfoData[i].m_ProductNum = ThirdFile.Search_Posistion(i, TBProductNum)->iValue;

		for(int32 j = 0; j < MAX_CREATE_MATERIAL_NUM; ++j)
		{
			if
			(
				ThirdFile.Search_Posistion
					(
						i,
						TBCreateInfo + TBMaterialType + j * TBCreatInfoNum
					)->iValue != -1
			)
			{
				m_pProductInfoData[i].m_CreateInfo[j].m_MaterialType = ThirdFile.Search_Posistion
					(
						i,
						TBCreateInfo + TBMaterialType + j * TBCreatInfoNum
					)->iValue;
				m_pProductInfoData[i].m_CreateInfo[j].m_MaterialNum = ThirdFile.Search_Posistion
					(
						i,
						TBCreateInfo + TBMaterialNum + j * TBCreatInfoNum
					)->iValue;;
				m_pProductInfoData[i].m_CreateInfo[j].m_NeedLevel = ThirdFile.Search_Posistion
					(
						i,
						TBCreateInfo + TBCreateNeedLevel + j * TBCreatInfoNum
					)->iValue;;
				m_pProductInfoData[i].m_CreateInfo[j].m_SplitRate = ThirdFile.Search_Posistion
					(
						i,
						TBCreateInfo + TBSplitRate + j * TBCreatInfoNum
					)->iValue;;

				++m_pProductInfoData[i].m_nCreateInfoCount;
			}
			else
				break;
		}

		for(int32 j = 0; j < MAX_REMOULD_MATERIAL_NUM; ++j)
		{
			if
			(
				ThirdFile.Search_Posistion
					(
						i,
						TBRemouldInfo + TBRemouldMaterialType + j * TBRemouldInfoNum
					)->iValue != -1
			)
			{
				m_pProductInfoData[i].m_RemouldInfo[j].m_MaterialType = ThirdFile.Search_Posistion
					(
						i,
						TBRemouldInfo + TBRemouldMaterialType + j * TBRemouldInfoNum
					)->iValue;
				m_pProductInfoData[i].m_RemouldInfo[j].m_MaterialNum = ThirdFile.Search_Posistion
					(
						i,
						TBRemouldInfo + TBRemouldMaterialNum + j * TBRemouldInfoNum
					)->iValue;
				m_pProductInfoData[i].m_RemouldInfo[j].m_NeedLevel = ThirdFile.Search_Posistion
					(
						i,
						TBRemouldInfo + TBRemouldNeedLevel + j * TBRemouldInfoNum
					)->iValue;

				++m_pProductInfoData[i].m_nRemouldInfoCount;
			}
		}

		m_pProductInfoData[i].m_OperateTime = ThirdFile.Search_Posistion(i, TBOperateTime)->iValue;
		m_pProductInfoData[i].m_ScriptID = ThirdFile.Search_Posistion(i, TBScriptID)->iValue;
		KCheck(m_pProductInfoData[i].m_ScriptID <= 0 || m_pProductInfoData[i].m_ScriptID >= 100000);
		m_pProductInfoData[i].m_CreateMoney = ThirdFile.Search_Posistion(i, TBCreateMoney)->iValue;
		m_pProductInfoData[i].m_RemouldMoney = ThirdFile.Search_Posistion(i, TBRemouldMoney)->iValue;
		m_pProductInfoData[i].m_IsFixed = ThirdFile.Search_Posistion(i, TBFixed)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitMaterialLevelInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum MaterialLevelInfoTBData { TBBindLevel = 0, TBVaule, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_MATERIALLEVEL_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nMaterialLevelInfoCount = iTableCount;
	KCheck(m_nMaterialLevelInfoCount == MAX_VALIDMATERIAL_LEVEL);

	m_MaterialLevelInfoData = new MATERIAL_LEVEL_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_nMaterialLevelInfoCount; i++)
	{
		KCheck(i == (ThirdFile.Search_Posistion(i, TBBindLevel)->iValue - 1));
		m_MaterialLevelInfoData[i].m_MaterialValue = ThirdFile.Search_Posistion(i, TBVaule)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipExtraInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum GemInfoTBData { TBEquipScore = 2, TBExtraAttSetBegin, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIPEXTRAATT_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipExtraInfoCount = iTableCount;
	m_EquipExtraInfoData = new EQUIPEXTRATT_TB[iTableCount];
	KCheck(iTableCount == HEQUIP_ADORN1 * MAX_VALIDMATERIAL_LEVEL);

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_EquipExtraInfoData[i].m_nEquipScore = ThirdFile.Search_Posistion(i, TBEquipScore)->iValue;

		for(uint32 m = 0; m < MAX_JOB_SUM; ++m)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SplitStringLevelOne	pSplitL1;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for(uint32 j = 0; j < MAX_ITEM_NATUREATTR; ++j)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				const char		*pSplitString = ThirdFile.Search_Posistion
					(
						i,
						TBExtraAttSetBegin + m * MAX_ITEM_NATUREATTR + j
					)->pString;
				SplitStringLevelOne	pSplitL1;
				SplitStringLevelTwo	pSplitL2;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				pSplitL1.Reset();
				pSplitL2.Reset();
				pSplitL1.Init('|', &pSplitL2);
				pSplitL2.Init('~', NULL);
				pSplitL1.DoSplit(pSplitString);

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	iLineCount = pSplitL2.GetResultLineCount();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				KCheck(iLineCount < 20);

				/*~~~~~~~~~~~~~~~~~~~*/
				BOOL	bValid = FALSE;
				/*~~~~~~~~~~~~~~~~~~~*/

				for(int32 iLine = 0; iLine < iLineCount; ++iLine)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					int32	nAtt = atoi(pSplitL2.GetResultLine(iLine));
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if(nAtt <= -1)
					{
						break;
					}

					m_EquipExtraInfoData[i].m_EquipExtrAtt[m].m_GenAttr[m_EquipExtraInfoData[i].m_EquipExtrAtt[m].m_ValidCount].m_Attr[iLine] = nAtt;
					++m_EquipExtraInfoData[i].m_EquipExtrAtt[m].m_GenAttr[m_EquipExtraInfoData[i].m_EquipExtrAtt[m].m_ValidCount].m_AttrCount;
					bValid = TRUE;
				}

				if(bValid)
				{
					++m_EquipExtraInfoData[i].m_EquipExtrAtt[m].m_ValidCount;
				}
			}
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipPointInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipPointInfoTBData { TBEquipPoint = 0, TBVaule = 2, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIPPOINT_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount < HEQUIP_NUMBER);

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	EquipPoint = ThirdFile.Search_Posistion(i, TBEquipPoint)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(EquipPoint < HEQUIP_NUMBER);
		m_nEquipPointInfo[EquipPoint] = ThirdFile.Search_Posistion(i, TBVaule)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitExtraBagInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ExtraBagTBData
	{
		TBItemIndex			= 0,
		TBClass,
		TBType,
		TBIndex,
		TBResID,
		TBName,
		TBDesc,
		TBRulerID,
		TBBasePrice,
		TBSellPrice,
		TBTime,
		TBVaule,
		TBParamType,
		TBParamValue,
		TBConsumeValue,
		TBMinPickLevel = TBConsumeValue + 7,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EXTRABAG_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nExtraBagInfoCount = iTableCount;
	m_pExtraBagInfoData = new EXTRABAG_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pExtraBagInfoData[i].m_nTableIndex = ThirdFile.Search_Posistion(i, TBItemIndex)->iValue;
		m_pExtraBagInfoData[i].m_ItemType.m_Class = ThirdFile.Search_Posistion(i, TBClass)->iValue;
		m_pExtraBagInfoData[i].m_ItemType.m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
		m_pExtraBagInfoData[i].m_ItemType.m_Index = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pExtraBagInfoData[i].m_nRulerID = ThirdFile.Search_Posistion(i, TBRulerID)->iValue;
		m_pExtraBagInfoData[i].m_nBasePrice = ThirdFile.Search_Posistion(i, TBBasePrice)->iValue;
		m_pExtraBagInfoData[i].m_nSellPrice = ThirdFile.Search_Posistion(i, TBSellPrice)->iValue;
		m_pExtraBagInfoData[i].m_nValidTime = ThirdFile.Search_Posistion(i, TBTime)->iValue;
		KCheck(ThirdFile.Search_Posistion(i, TBVaule)->iValue <= MAX_SINGLEBAG_SIZE);
		m_pExtraBagInfoData[i].m_nSize = ThirdFile.Search_Posistion(i, TBVaule)->iValue;
		m_pExtraBagInfoData[i].m_ParamType = ThirdFile.Search_Posistion(i, TBParamType)->iValue;
		m_pExtraBagInfoData[i].m_ParamValue = ThirdFile.Search_Posistion(i, TBParamValue)->iValue;
		m_pExtraBagInfoData[i].m_ConsumeValue = ThirdFile.Search_Posistion(i, TBConsumeValue)->iValue;
		m_pExtraBagInfoData[i].m_minPickLevel = ThirdFile.Search_Posistion(i, TBMinPickLevel)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipChainInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipChainTBData { TBID = 0, TBName, TBReqPai1, TBReqPai2, TBReqPai3, TBAttID, TBAttValue, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_CHAIN_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipChainInfoCount = iTableCount;
	m_EquipChainInfoData = new EQUIPCHAIN_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	int32	nValue = -1;
	BOOL	bTrue = TRUE;
	/*~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		nValue = ThirdFile.Search_Posistion(i, TBID)->iValue;
		if(nValue != -1)
		{
			m_EquipChainInfoData[i].m_ChainID = ThirdFile.Search_Posistion(i, TBID)->iValue;
		}

		nValue = ThirdFile.Search_Posistion(i, TBReqPai1)->iValue;
		if(nValue != -1)
		{
			m_EquipChainInfoData[i].m_ReqPai1 = ThirdFile.Search_Posistion(i, TBReqPai1)->iValue;
			m_EquipChainInfoData[i].m_Flat.UpdateBits(m_EquipChainInfoData[i].m_ReqPai1, bTrue);
		}

		nValue = ThirdFile.Search_Posistion(i, TBReqPai2)->iValue;
		if(nValue != -1)
		{
			m_EquipChainInfoData[i].m_ReqPai2 = ThirdFile.Search_Posistion(i, TBReqPai2)->iValue;
			m_EquipChainInfoData[i].m_Flat.UpdateBits(m_EquipChainInfoData[i].m_ReqPai2, bTrue);
		}

		nValue = ThirdFile.Search_Posistion(i, TBReqPai3)->iValue;
		if(nValue != -1)
		{
			m_EquipChainInfoData[i].m_ReqPai3 = ThirdFile.Search_Posistion(i, TBReqPai3)->iValue;
			m_EquipChainInfoData[i].m_Flat.UpdateBits(m_EquipChainInfoData[i].m_ReqPai3, bTrue);
		}

		m_EquipChainInfoData[i].m_Att.m_AttrType = ThirdFile.Search_Posistion(i, TBAttID)->iValue;
		m_EquipChainInfoData[i].m_Att.m_Value.m_Value = ThirdFile.Search_Posistion(i, TBAttValue)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipSoulInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipSoulTBData
	{
		TBID				= 0,
		TBName,
		TBSoulType,
		TBReqChain1,
		TBReqChain2,
		TBReqChain3,
		TBReqChain4,
		TBReqChain5,
		TBAttID,
		TBAttValue,
		TBReqItem			= 16,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_SOUL_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipSoulInfoCount = iTableCount;
	m_EquipSoulInfoData = new EQUIPSOUL_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	int32	nValue = -1;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		nValue = ThirdFile.Search_Posistion(i, TBID)->iValue;
		if(nValue != -1)
		{
			m_EquipSoulInfoData[i].m_SoulID = ThirdFile.Search_Posistion(i, TBID)->iValue;
		}

		m_EquipSoulInfoData[i].m_SoulType = ThirdFile.Search_Posistion(i, TBSoulType)->iValue;

		for(int32 m = TBReqChain1; m <= TBReqChain4; ++m)
		{
			nValue = ThirdFile.Search_Posistion(i, m)->iValue;
			if(nValue != -1)
			{
				/*~~~~~~~~~~~~~~~~~~~*/
				BOOL	bAlive = FALSE;
				/*~~~~~~~~~~~~~~~~~~~*/

				for(int32 j = 0; j < MAX_CHAIN_NUM; ++j)
				{
					if(m_EquipSoulInfoData[i].m_ChainID[j] == nValue)
					{
						++m_EquipSoulInfoData[i].m_ChainIDNum[j];
						bAlive = TRUE;
					}
				}

				if(!bAlive)
				{
					m_EquipSoulInfoData[i].m_ChainID[m_EquipSoulInfoData[i].ValidSoulNum] = nValue;
					m_EquipSoulInfoData[i].m_ChainIDNum[m_EquipSoulInfoData[i].ValidSoulNum] = 1;
					++m_EquipSoulInfoData[i].ValidSoulNum;
				}
			}
		}

		nValue = ThirdFile.Search_Posistion(i, TBReqChain5)->iValue;
		if(nValue != -1)
		{
			m_EquipSoulInfoData[i].m_ChainID5 = ThirdFile.Search_Posistion(i, TBReqChain5)->iValue;
		}

		iColumn = TBAttID;
		for(uint32 j = 0; j < MAX_SOUL_EFFECTATT; ++j)
		{
			if(ThirdFile.Search_Posistion(i, iColumn)->iValue == -1)
			{
				break;
			}

			m_EquipSoulInfoData[i].m_Att[j].m_AttrType = ThirdFile.Search_Posistion(i, iColumn)->iValue;
			++iColumn;
			m_EquipSoulInfoData[i].m_Att[j].m_Value.m_Value = ThirdFile.Search_Posistion
				(
					i,
					iColumn
				)->iValue;
			++iColumn;
			++m_EquipSoulInfoData[i].m_EffectAttCount;
		}

		m_EquipSoulInfoData[i].m_ReqItem = ThirdFile.Search_Posistion(i, TBReqItem)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitChangePaiInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ChangePaiTBData { TBItemIndex = 0, TBDesc, TBPaiType, TBNeedMoney, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_CHANGEPAI_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nChangePaiInfoCount = iTableCount;
	m_pChangePaiInfoData = new CHANGEPAI_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pChangePaiInfoData[i].m_nTableIndex = ThirdFile.Search_Posistion(i, TBItemIndex)->iValue;
		m_pChangePaiInfoData[i].m_DestPaiType = ThirdFile.Search_Posistion(i, TBPaiType)->iValue;
		m_pChangePaiInfoData[i].m_nReqMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitPaiInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum PaiInfoTBData { TBID = 0, TBDesc, TBAttID, TBAttValue, TBRate,TBItem,TBIDSet };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_PAI_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount < EQUIP_PAI_NUM);

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/
	SplitStringLevelOne* pSplitL1 =	NULL;
	SplitStringLevelTwo* pSplitL2 =	NULL;

	if( iTableCount > 0 )
	{
		pSplitL1 = new SplitStringLevelOne;
		pSplitL2 = new SplitStringLevelTwo;
	}

	for(int32 i = 0; i < iTableCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nType = ThirdFile.Search_Posistion(i, TBID)->iValue;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(nType != -1);
		KCheck(nType < EQUIP_PAI_NUM);
		m_nPaiInfo[nType].m_nPaiID = ThirdFile.Search_Posistion(i, TBID)->iValue;

		m_nPaiInfo[nType].m_Att.m_AttrType = ThirdFile.Search_Posistion(i, TBAttID)->iValue;
		m_nPaiInfo[nType].m_Att.m_Value.m_Value = ThirdFile.Search_Posistion(i, TBAttValue)->iValue;
		m_nPaiInfo[nType].m_nRate = ThirdFile.Search_Posistion(i, TBRate)->iValue;
		
		if((m_nPaiInfo[nType].m_nPaiID >= EQUIPPAI_ANY) && (m_nPaiInfo[nType].m_nPaiID <= EQUIPPAI_ANY_END))
		{
			const char *pSplitString = ThirdFile.Search_Posistion(i, TBIDSet)->pString;

			pSplitL1->Reset();
			pSplitL2->Reset();
			pSplitL1->Init('|', pSplitL2);
			pSplitL2->Init('~', NULL);
			pSplitL1->DoSplit(pSplitString);

			int32	iSplitCount = pSplitL2->GetResultLineCount();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			KCheck(iSplitCount < EQUIP_PAI_NUM);

			for (int32 i = 0; i < iSplitCount; ++i)
			{
				m_nPaiInfo[nType].m_nPaiIDSet[i] = atoi(pSplitL2->GetResultLine(i));
				++m_nPaiInfo[nType].m_nPaiIDSetCount;
			}
		}
	}
	KSafeDelete(pSplitL1);
	KSafeDelete(pSplitL2);
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitCommItemInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum CommonItemInfoTBData
	{
		TBIndex				= 0,
		TBClass				= 1,
		TBType,
		TBMedicIndex,
		TBResourceID,
		TBName,
		TBDesc,
		TBLevel,
		TBReqInherenceLevel,		// rj 2010-8-23 天赋及个人等级字段索引枚举
		TBReqPersonLevel,
		TBJob,
		TBBasePrice,
		TBSellPrice,
		TBRulerID,
		TBTileNumber,
		TBScriptID,
		TBSkillID,
		TBReqSkill,
		TBReqSkillLevel,
		TBHoldNumber,
		TBTargetType,
		TBbBroadcast,
		TBParamType,
		TBParamValue,
		TBConsumeValue,
		TBImpactID			= 32,
		TBIsMultTimes,
		TBMultTimes,
		TBIndexOfGemRework		= 36,
		TBMinPickLevel,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_MISCELL_ITEM);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nCommItemCount = iTableCount;
	m_pCommItemInfoData = new SMiscItemInfoTab[iTableCount];

	SplitStringLevelOne* pSplitL1 = new SplitStringLevelOne;
	SplitStringLevelTwo* pSplitL2 =  new SplitStringLevelTwo;

	for(uint32 i = 0; i < m_nCommItemCount; i++)
	{
		m_pCommItemInfoData[i].m_nTableIndex = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pCommItemInfoData[i].m_ItemType.m_Class = ThirdFile.Search_Posistion(i, TBClass)->iValue;
		m_pCommItemInfoData[i].m_ItemType.m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
		m_pCommItemInfoData[i].m_ItemType.m_Index = ThirdFile.Search_Posistion(i, TBMedicIndex)->iValue;
		m_pCommItemInfoData[i].m_nLevel = ThirdFile.Search_Posistion(i, TBLevel)->iValue;
		
		// rj 2010-8-23 天赋及个人等级初始化表值
		m_pCommItemInfoData[i].m_iReqInherenceLevel = ThirdFile.Search_Posistion(i, TBReqInherenceLevel)->iValue;
		m_pCommItemInfoData[i].m_iReqPersonLevel = ThirdFile.Search_Posistion(i, TBReqPersonLevel)->iValue;

		const char *pSplitString = ThirdFile.Search_Posistion(i, TBJob)->pString;

		pSplitL1->Reset();
		pSplitL2->Reset();
		pSplitL1->Init('|', pSplitL2);
		pSplitL2->Init('~', NULL);
		pSplitL1->DoSplit(pSplitString);

		int32	iSplitCount = pSplitL2->GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		KCheck(iSplitCount <= PROFESSION_NUMBER);
		
		int32 nJobId = -1;
		bool bSelectedOneJobs = false;
		bool bSelectedAllJobs = false;

		for(int32 nID = 0; nID < iSplitCount; ++nID)
		{
			nJobId =  atoi(pSplitL2->GetResultLine(nID));

			if(nJobId >= 0 && nJobId < PROFESSION_NUMBER)
			{
				m_pCommItemInfoData[i].m_nJob |= (1 << nJobId);
				bSelectedOneJobs = true;
			}
			else if (nJobId == -1 || nJobId == PROFESSION_NONE  )
			{
				bSelectedAllJobs = true;
			}

		}

		if (bSelectedAllJobs)
		{
			//放开职业限制
			m_pCommItemInfoData[i].m_nJob |= (~ALL_JOB_MASK);
		}
		else if (bSelectedOneJobs)
		{
			//限制职业
			m_pCommItemInfoData[i].m_nJob &= ALL_JOB_MASK;
		}


		m_pCommItemInfoData[i].m_nBasePrice = ThirdFile.Search_Posistion(i, TBBasePrice)->iValue;
		m_pCommItemInfoData[i].m_nSellPrice = ThirdFile.Search_Posistion(i, TBSellPrice)->iValue;
		m_pCommItemInfoData[i].m_nRulerID = ThirdFile.Search_Posistion(i, TBRulerID)->iValue;
		m_pCommItemInfoData[i].m_nLayedNum = ThirdFile.Search_Posistion(i, TBTileNumber)->iValue;
		m_pCommItemInfoData[i].m_nScriptID = ThirdFile.Search_Posistion(i, TBScriptID)->iValue;
		KCheck(m_pCommItemInfoData[i].m_nScriptID <= 0 || m_pCommItemInfoData[i].m_nScriptID >= 100000);
		m_pCommItemInfoData[i].m_nSkillID = ThirdFile.Search_Posistion(i, TBSkillID)->iValue;

		m_pCommItemInfoData[i].m_nReqSkill = ThirdFile.Search_Posistion(i, TBReqSkill)->iValue;
		m_pCommItemInfoData[i].m_nReqSkillLevel = ThirdFile.Search_Posistion(i, TBReqSkillLevel)->iValue;
		m_pCommItemInfoData[i].m_HoldNum = ThirdFile.Search_Posistion(i, TBHoldNumber)->iValue;
		m_pCommItemInfoData[i].m_TargetType = ThirdFile.Search_Posistion(i, TBTargetType)->iValue;

		if(ThirdFile.Search_Posistion(i, TBbBroadcast)->iValue == 1)
			m_pCommItemInfoData[i].m_bBroadcast = TRUE;

		m_pCommItemInfoData[i].m_ParamType = ThirdFile.Search_Posistion(i, TBParamType)->iValue;
		m_pCommItemInfoData[i].m_ParamValue = ThirdFile.Search_Posistion(i, TBParamValue)->iValue;
		m_pCommItemInfoData[i].m_ConsumeValue = ThirdFile.Search_Posistion(i, TBConsumeValue)->iValue;
		m_pCommItemInfoData[i].m_nImpactID = ThirdFile.Search_Posistion(i, TBImpactID)->iValue;
		m_pCommItemInfoData[i].m_bMultTimes = ThirdFile.Search_Posistion(i, TBIsMultTimes)->iValue;
		m_pCommItemInfoData[i].m_iMultTimes = ThirdFile.Search_Posistion(i, TBMultTimes)->iValue;
		m_pCommItemInfoData[i].m_nIndexOfGemRework = ThirdFile.Search_Posistion(i, TBIndexOfGemRework)->iValue;
		m_pCommItemInfoData[i].m_minPickLevel = ThirdFile.Search_Posistion(i, TBMinPickLevel)->iValue;
	}

	KSafeDelete(pSplitL1);
	KSafeDelete(pSplitL2);
 
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitTaskItemInfoTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum TaskItemInfoTBData
	{
		TBIndex				= 0,
		TBClass				= 1,
		TBType,
		TBResourceID,
		TBMedicIndex,
		TBName,
		TBDesc,
		TBLevel,
		TBBasePrice,
		TBSellPrice,
		TBRulerID,
		TBTileNumber,
		TBScriptID,
		TBSkillID,
		TBReqSkill,
		TBReqSkillLevel,
		TBHoldNumber,
		TBTargetType,
		TBbBroadcast,
		TBParamType,
		TBParamValue,
		TBConsumeValue,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_QUEST_ITEM);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nTaskItemCount = iTableCount;
	m_pTaskItemInfoData = new TASKITEM_INFO_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	KCheck(TBTargetType < iTableColumn);
	for(uint32 i = 0; i < m_nTaskItemCount; i++)
	{
		m_pTaskItemInfoData[i].m_nTableIndex = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pTaskItemInfoData[i].m_ItemType.m_Class = ThirdFile.Search_Posistion(i, TBClass)->iValue;
		m_pTaskItemInfoData[i].m_ItemType.m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
		m_pTaskItemInfoData[i].m_ItemType.m_Index = ThirdFile.Search_Posistion(i, TBMedicIndex)->iValue;

		m_pTaskItemInfoData[i].m_nLevel = ThirdFile.Search_Posistion(i, TBLevel)->iValue;
		m_pTaskItemInfoData[i].m_nBasePrice = ThirdFile.Search_Posistion(i, TBBasePrice)->iValue;
		m_pTaskItemInfoData[i].m_nSellPrice = ThirdFile.Search_Posistion(i, TBSellPrice)->iValue;
		m_pTaskItemInfoData[i].m_nRulerID = ThirdFile.Search_Posistion(i, TBRulerID)->iValue;
		m_pTaskItemInfoData[i].m_nLayedNum = ThirdFile.Search_Posistion(i, TBTileNumber)->iValue;
		m_pTaskItemInfoData[i].m_nScriptID = ThirdFile.Search_Posistion(i, TBScriptID)->iValue;
		KCheck(m_pTaskItemInfoData[i].m_nScriptID <= 0 || m_pTaskItemInfoData[i].m_nScriptID >= 100000);
		m_pTaskItemInfoData[i].m_nSkillID = ThirdFile.Search_Posistion(i, TBSkillID)->iValue;

		m_pTaskItemInfoData[i].m_nReqSkill = ThirdFile.Search_Posistion(i, TBReqSkill)->iValue;
		m_pTaskItemInfoData[i].m_nReqSkillLevel = ThirdFile.Search_Posistion(i, TBReqSkillLevel)->iValue;
		m_pTaskItemInfoData[i].m_HoldNum = ThirdFile.Search_Posistion(i, TBHoldNumber)->iValue;
		m_pTaskItemInfoData[i].m_TargetType = ThirdFile.Search_Posistion(i, TBTargetType)->iValue;

		if(ThirdFile.Search_Posistion(i, TBbBroadcast)->iValue == 1)
			m_pTaskItemInfoData[i].m_bBroadcast = TRUE;
		m_pTaskItemInfoData[i].m_ParamType = ThirdFile.Search_Posistion(i, TBParamType)->iValue;
		m_pTaskItemInfoData[i].m_ParamValue = ThirdFile.Search_Posistion(i, TBParamValue)->iValue;
		m_pTaskItemInfoData[i].m_ConsumeValue = ThirdFile.Search_Posistion(i, TBConsumeValue)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitItemRulerTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum ItemRulerTBData
	{
		TBRulerIndex			= 0,
		TBTile				= 2,
		TBDiscard,
		TBShortCut,
		TBSell,
		TBExchange,
		TBUse,
		TBPickBind,
		TBEquipBind,
		TBUnique,
		TBIdent,
		TBDummyItem,
		TBBank,
		TBConsume,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ITEM_RULE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nItemRulerCount = iTableCount;
	m_pItemRulerData = new SItemRulerTab[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	KCheck(TBUnique < iTableColumn);

	for(uint32 i = 0; i < m_nItemRulerCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		static BOOL	bInit = FALSE;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_pItemRulerData[i].m_RulerIndex = ThirdFile.Search_Posistion(i, TBRulerIndex)->iValue;

		if(!bInit)
		{
			m_nHashOffSet = m_pItemRulerData[i].m_RulerIndex - i;
		}

		KCheck(m_pItemRulerData[i].m_RulerIndex == i + m_nHashOffSet);

		m_pItemRulerData[i].m_Discard = ThirdFile.Search_Posistion(i, TBDiscard)->iValue == 1;
		m_pItemRulerData[i].m_Tile = ThirdFile.Search_Posistion(i, TBTile)->iValue == 1;
		m_pItemRulerData[i].m_ShortCut = ThirdFile.Search_Posistion(i, TBShortCut)->iValue == 1;
		m_pItemRulerData[i].m_CanSell = ThirdFile.Search_Posistion(i, TBSell)->iValue == 1;
		m_pItemRulerData[i].m_CanExchange = ThirdFile.Search_Posistion(i, TBExchange)->iValue == 1;
		m_pItemRulerData[i].m_CanUse = ThirdFile.Search_Posistion(i, TBUse)->iValue == 1;
		m_pItemRulerData[i].m_PickBind = ThirdFile.Search_Posistion(i, TBPickBind)->iValue == 1;
		m_pItemRulerData[i].m_EquipBind = ThirdFile.Search_Posistion(i, TBEquipBind)->iValue == 1;
		m_pItemRulerData[i].m_Unique = ThirdFile.Search_Posistion(i, TBUnique)->iValue == 1;

		m_pItemRulerData[i].m_Ident = ThirdFile.Search_Posistion(i, TBIdent)->iValue == 1;
		m_pItemRulerData[i].m_DummyItem = ThirdFile.Search_Posistion(i, TBDummyItem)->iValue == 1;
		m_pItemRulerData[i].m_Bank = ThirdFile.Search_Posistion(i, TBBank)->iValue == 1;
		m_pItemRulerData[i].m_Consume = ThirdFile.Search_Posistion(i, TBConsume)->iValue == 1;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SItemRulerTab *ItemTemplateTable::GetRuleValueByID(int32 &iIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 iOffSet = iIndex - m_nHashOffSet;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((iOffSet >= 0) && (iOffSet < (int32) m_nItemRulerCount))
	{
		return &m_pItemRulerData[iOffSet];
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	char	szExp[128] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tsnprintf_s(szExp, 128, "RulerID=%d is invalid!", iIndex);
	KCheckEx(0, szExp);

	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitMonsterDropTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum MonsterDropTBData { TBDropSetID = 0, TBMonsterDropContent = 1 };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_MONSTER_DROP_CONTENT);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount > 0);

	m_nMonsterDropCount = iTableCount;
	m_pMonsterDropTableData = new MONSTER_DROP_TB[iTableCount];

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pMonsterDropTableData[i].m_DropId = ThirdFile.Search_Posistion(i, TBDropSetID)->iValue;

		iColumn = TBMonsterDropContent;
		for(int32 j = 0; j < MAX_MONSTER_DROPBOX; j++)
		{
			m_pMonsterDropTableData[i].m_Drops[j].m_nItemValue = ThirdFile.Search_Posistion
				(
					i,
					iColumn++
				)->iValue;
			if(m_pMonsterDropTableData[i].m_Drops[j].m_nItemValue == -1) break;

			m_pMonsterDropTableData[i].m_Drops[j].m_nCycle = ThirdFile.Search_Posistion
				(
					i,
					iColumn++
				)->iValue;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const char		*pSplitString = ThirdFile.Search_Posistion(i, iColumn++)->pString;
			SplitStringLevelOne	pSplitL1;
			SplitStringLevelTwo	pSplitL2;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pSplitL1.Reset();
			pSplitL2.Reset();
			pSplitL1.Init('|', &pSplitL2);
			pSplitL2.Init('~', NULL);
			pSplitL1.DoSplit(pSplitString);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iLineCount = pSplitL2.GetResultLineCount();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			m_pMonsterDropTableData[i].m_Drops[j].m_pDropContent = new int32[iLineCount];

			for(int32 nID = 0; nID < iLineCount; ++nID)
			{
				m_pMonsterDropTableData[i].m_Drops[j].m_pDropContent[nID] = atoi(pSplitL2.GetResultLine(nID));
			}

			m_pMonsterDropTableData[i].m_Drops[j].m_nItemCount = iLineCount;
			++m_pMonsterDropTableData[i].m_ValidCount;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitDropAttTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum DropAttTBData
	{
		TBDeltaLevel			= 0,
		TBRate				= 1,
		TBExpRate			= 2,
		TBTeamRate			= 3,
		TBTeamExpRate			= 4,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_DROP_ATTENUATION);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nDropAttCount = iTableCount;
	m_pDropAttData = new SDropAttrTab[iTableCount];

	KCheck(iTableColumn > TBRate);
	KCheck(m_pDropAttData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pDropAttData[i].m_DeltaLevel = ThirdFile.Search_Posistion(i, TBDeltaLevel)->iValue;
		m_pDropAttData[i].m_AttValue = ThirdFile.Search_Posistion(i, TBRate)->fValue;
		m_pDropAttData[i].m_ExpValue = ThirdFile.Search_Posistion(i, TBExpRate)->fValue;
		m_pDropAttData[i].m_TeamAttValue = ThirdFile.Search_Posistion(i, TBTeamRate)->fValue;
		m_pDropAttData[i].m_TeamExpValue = ThirdFile.Search_Posistion(i, TBTeamExpRate)->fValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitItemDropPos()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum DropPosTBData { TBDropX = 1, TBDropY = 2, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_DROP_POS);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nDropPosCount = iTableCount;
	m_pDropPosData = new DROP_POS_TB[iTableCount];

	KCheck(iTableColumn > TBDropY);
	KCheck(m_pDropPosData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pDropPosData[i].m_DropX = ThirdFile.Search_Posistion(i, TBDropX)->fValue;
		m_pDropPosData[i].m_DropZ = ThirdFile.Search_Posistion(i, TBDropY)->fValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipSetAttrTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum EquipSetAttr
	{
		TBEquipSetSerial		= 0,
		TBDes,
		TBSetCount,
		TBSetDes,
		TBEquipSetCount,
		TBEquipSetAttr,
		TBEquipSetAttrValue,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_SET_ATTR);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipSetCount = iTableCount;

	m_pEquipSetData = new SEquipSetTab[iTableCount];

	KCheck(iTableColumn > TBEquipSetCount);
	KCheck(m_pEquipSetData);

	/*~~~~~~~~~~~~~~~~*/
	int32	iColumn = 0;
	int32	iValue = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_nEquipSetCount; i++)
	{
		m_pEquipSetData[i].m_nEquipSetSerial = ThirdFile.Search_Posistion(i, TBEquipSetSerial)->iValue;
		m_pEquipSetData[i].m_nEquipSetCount = ThirdFile.Search_Posistion(i, TBSetCount)->iValue;
		for(int32 j = 0; j < MAX_ITEM_SET_ATTR; j++)
		{
			iValue = ThirdFile.Search_Posistion
				(
					i,
					TBEquipSetCount + j * (TBEquipSetAttrValue - TBSetDes)
				)->iValue;
			if(iValue >= 0)
			{
				KCheck(iValue <= m_pEquipSetData[i].m_nEquipSetCount);
				m_pEquipSetData[i].m_EquipSetInfo[j].m_nEquipSetNum = iValue;
				m_pEquipSetData[i].m_EquipSetInfo[j].m_ItemAttr.m_AttrType =
					(ITEM_PROPERTY) ThirdFile.Search_Posistion
						(
							i,
							TBEquipSetAttr + j * (TBEquipSetAttrValue - TBSetDes)
						)->iValue;
				m_pEquipSetData[i].m_EquipSetInfo[j].m_ItemAttr.m_Value.m_Value = ThirdFile.
					Search_Posistion
					(
						i,
						TBEquipSetAttrValue + j * (TBEquipSetAttrValue - TBSetDes)
					)->iValue;
				++m_pEquipSetData[i].m_nValidEquipSetNum;
			}
			else
				break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitFriendGiftTable()
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum FriendGiftTBData { TBItemIndex, TBBuffID, TBFriendPoint, TBFreendScript, TBBroadcastFlag, TBDescription, };
	/*~~~~~~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_FRIEND_GIFT);
	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nFriendGiftCount = iTableCount;

	m_pFriendGiftData = new FRIEND_GIFT_TB[m_nFriendGiftCount];

	KCheck(iTableColumn > TBFriendPoint);
	KCheck(m_pFriendGiftData);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	strTemp[MAX_GIFT_DESC_LENGTH] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pFriendGiftData[i].m_nItemTableIndex = ThirdFile.Search_Posistion(i, TBItemIndex)->iValue;
		m_pFriendGiftData[i].m_nBuffID = ThirdFile.Search_Posistion(i, TBBuffID)->iValue;
		m_pFriendGiftData[i].m_nFriendPoint = ThirdFile.Search_Posistion(i, TBFriendPoint)->iValue;
		m_pFriendGiftData[i].m_nScriptID = ThirdFile.Search_Posistion(i, TBFreendScript)->iValue;
		KCheck(m_pFriendGiftData[i].m_nScriptID <= 0 || m_pFriendGiftData[i].m_nScriptID >= 100000);
		m_pFriendGiftData[i].m_nBroadcast = ThirdFile.Search_Posistion(i, TBBroadcastFlag)->iValue;
		m_pFriendGiftData[i].m_nDescription = 0;
		strncpy(strTemp, ThirdFile.Search_Posistion(i, TBDescription)->pString, MAX_GIFT_DESC_LENGTH);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		uint32	uiLength = (uint32)strlen(strTemp);
		int32	iPos = 0;
		char	strDescription[MAX_GIFT_DESC_LENGTH] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(uint32 j = 0; j < uiLength; ++j)
		{
			if(strTemp[j] != '|')
			{
				/*
				 * m_pFriendGiftData[ i].m_strDescription1[ iCount][ iPos] = strTemp[ j];
				 */
				strDescription[iPos++] = strTemp[j];
				if(iPos >= MAX_GIFT_DESC_LENGTH / MAX_GIFT_DESC_COUNT)
				{
					KCheckEx(FALSE, "读取好友道具表错误! ");
				}	/* if */
			}		/* if */
			else
			{
				strDescription[iPos] = '\0';
				strncpy
				(
					m_pFriendGiftData[i].m_strDescription[m_pFriendGiftData[i].m_nDescription++],
					strDescription,
					MAX_GIFT_DESC_LENGTH / MAX_GIFT_DESC_COUNT
				);
				memset(strDescription, 0, sizeof(strDescription));
				iPos = 0;
			}		/* else */
		}			/* for */

		if(iPos > 0 && iPos < MAX_GIFT_DESC_LENGTH / MAX_GIFT_DESC_COUNT)
		{
			strDescription[iPos] = '\0';
			strncpy
			(
				m_pFriendGiftData[i].m_strDescription[m_pFriendGiftData[i].m_nDescription++],
				strDescription,
				MAX_GIFT_DESC_LENGTH / MAX_GIFT_DESC_COUNT
			);
		}			/* if */
	}	/* for */

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipActivationTable()
{
	/*~~~~~~~*/
	__GUARD__ enum { TBIndex, TBType = 2, TBCountMin, TBCountMax, TBLevelNeed, TBPRI, TBAttBegin, };
	/*~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_EQUIP_ACTIVATION_TB);
	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipActivationCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipActivationData = new EQUIP_ACTIVATION_TB[m_nEquipActivationCount];

	KCheck(m_pEquipActivationData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipActivationData[i].m_Index = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pEquipActivationData[i].m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
		m_pEquipActivationData[i].m_NeedCountMin = ThirdFile.Search_Posistion(i, TBCountMin)->iValue;
		m_pEquipActivationData[i].m_NeedCountMax = ThirdFile.Search_Posistion(i, TBCountMax)->iValue;
		m_pEquipActivationData[i].m_NeedLevel = ThirdFile.Search_Posistion(i, TBLevelNeed)->iValue;
		m_pEquipActivationData[i].m_PRI = ThirdFile.Search_Posistion(i, TBPRI)->iValue;
		for(int32 j = 0; j < EQUIP_ACTIVATION_ATT_NUM; ++j)
		{
			m_pEquipActivationData[i].m_AttId[j] = ThirdFile.Search_Posistion
				(
					i,
					TBAttBegin + j * EQUIP_ACTIVATION_ATT_NUM
				)->iValue;
			m_pEquipActivationData[i].m_AttValue[j] = ThirdFile.Search_Posistion
				(
					i,
					TBAttBegin + j * EQUIP_ACTIVATION_ATT_NUM + 1
				)->iValue;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipColorChangeTable()
{
	/*~~~~~~~*/
	__GUARD__ enum { TBYellow, TBNeedItem, TBNeedMoney, TBNeedLevel, TBPurple, };
	/*~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_EQUIP_COLORCHANGE_TB);
	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipColorChangeCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipColorChangeData = new EQUIP_COLORCHANGE_TB[m_nEquipColorChangeCount];

	KCheck(m_pEquipColorChangeData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipColorChangeData[i].m_YellowItem = ThirdFile.Search_Posistion(i, TBYellow)->iValue;
		m_pEquipColorChangeData[i].m_NeedItem = ThirdFile.Search_Posistion(i, TBNeedItem)->iValue;
		m_pEquipColorChangeData[i].m_NeedMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
		m_pEquipColorChangeData[i].m_NeedLevel = ThirdFile.Search_Posistion(i, TBNeedLevel)->iValue;
		m_pEquipColorChangeData[i].m_PurpleItem = ThirdFile.Search_Posistion(i, TBPurple)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipPurpleReworkTable()
{
	/*~~~~~~~*/
	__GUARD__ enum { TBIndex, TBNeedItem, TBNeedMoney, };
	/*~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_EQUIP_PURPLEREWORK_TB);
	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipPurpleReworkCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipPurpleReworkData = new EQUIP_PURPLE_REWORK_TB[m_nEquipPurpleReworkCount];

	KCheck(m_pEquipPurpleReworkData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipPurpleReworkData[i].m_Index = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pEquipPurpleReworkData[i].m_NeedItem = ThirdFile.Search_Posistion(i, TBNeedItem)->iValue;
		m_pEquipPurpleReworkData[i].m_NeedMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipPurpleAttrTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { TBAttrIndex = 2, TBFLOATMIN, TBFLOATMAX, TBMIN, TBMAX, TBPOSITION, TBRATE, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_PURPLEATTR_TB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipPurpleAttrCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipPurpleAttrData = new EQUIP_PURPLEATTR_TB[m_nEquipPurpleAttrCount];

	KCheck(m_pEquipPurpleAttrData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipPurpleAttrData[i].m_AttId = ThirdFile.Search_Posistion(i, TBAttrIndex)->iValue;
		m_pEquipPurpleAttrData[i].m_fMin = ThirdFile.Search_Posistion(i, TBFLOATMIN)->fValue;
		m_pEquipPurpleAttrData[i].m_fMax = ThirdFile.Search_Posistion(i, TBFLOATMAX)->fValue;
		m_pEquipPurpleAttrData[i].m_Min = ThirdFile.Search_Posistion(i, TBMIN)->iValue;
		m_pEquipPurpleAttrData[i].m_Max = ThirdFile.Search_Posistion(i, TBMAX)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iATTID = m_pEquipPurpleAttrData[i].m_AttId;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iATTID >= 0)
		{
			m_pEquipPurpleAttrData[i].m_AttrInfo.m_Attr = (ITEM_PROPERTY) iATTID;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const char	*pSplitString = ThirdFile.Search_Posistion(i, TBPOSITION)->pString;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			SetEquipType
			(
				pSplitString,
				EQUIP_TYPE_NUM,
				m_pEquipPurpleAttrData[i].m_AttrInfo.m_nValidEquipType
			);
		}

		m_pEquipPurpleAttrData[i].m_Rate = ThirdFile.Search_Posistion(i, TBRATE)->iValue;
		m_nEquipPurpleAttrRateCount += m_pEquipPurpleAttrData[i].m_Rate;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitGemReworkTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum
	{
		TBIndex				= 0,
		TBNeedNum,
		TBOtherNeedItem,
		TBOtherNeedNum,
		TBNeedMoney,
		TBNewItem,
		TBNewNum,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_GEM_REWORK_TB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uGemReworkCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pGemReworkData = new GEM_REWORK_TB[m_uGemReworkCount];

	KCheck(m_pGemReworkData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pGemReworkData[i].m_Index = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pGemReworkData[i].m_NeedNum = ThirdFile.Search_Posistion(i, TBNeedNum)->iValue;
		m_pGemReworkData[i].m_OtherNeedItem = ThirdFile.Search_Posistion(i, TBOtherNeedItem)->iValue;
		m_pGemReworkData[i].m_OtherNeedNum = ThirdFile.Search_Posistion(i, TBOtherNeedNum)->iValue;
		m_pGemReworkData[i].m_NeedMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
		m_pGemReworkData[i].m_NewItem = ThirdFile.Search_Posistion(i, TBNewItem)->iValue;
		m_pGemReworkData[i].m_NewItemNum = ThirdFile.Search_Posistion(i, TBNewNum)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEquipCopyTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { TBIndex = 0, TBType, };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_COPY_TB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uEquipCopyCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipCopyData = new EQUIP_COPY_TB[m_uEquipCopyCount];

	KCheck(m_pEquipCopyData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipCopyData[i].m_ItemId = ThirdFile.Search_Posistion(i, TBIndex)->iValue;
		m_pEquipCopyData[i].m_Type = ThirdFile.Search_Posistion(i, TBType)->iValue;
	}

	__UNGUARD__
}

void ItemTemplateTable::InitEquipRecallTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { TBItemId = 0, TBRecalType, TBRecallValue };

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_RECALL_TB);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	KCheck(ret);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	m_uEquipRecallCount= iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipRecallData = new EQUIP_RECALL_TB[m_uEquipRecallCount];

	KCheck(m_pEquipRecallData );

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipRecallData[i].m_ItemId = ThirdFile.Search_Posistion(i, TBItemId)->iValue;
		m_pEquipRecallData[i].m_RecallType= ThirdFile.Search_Posistion(i, TBRecalType)->iValue;
		m_pEquipRecallData[i].m_RecallValue = ThirdFile.Search_Posistion(i, TBRecallValue)->iValue;
	}

	__UNGUARD__
}

void ItemTemplateTable::InitTransItemPosTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { TBMapId = 0, TBCountryLimit};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_TRANSITEM_POS);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	KCheck(ret);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	m_uTransItemPosCount= iTableCount;
	KCheck(iTableCount > 0);

	m_pTransItemPosData = new TRANSITEM_POS_TB[m_uTransItemPosCount];

	KCheck(m_pTransItemPosData );

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pTransItemPosData[i].m_MapId = ThirdFile.Search_Posistion(i, TBMapId)->iValue;
		m_pTransItemPosData[i].m_CountryLimit= ThirdFile.Search_Posistion(i, TBCountryLimit)->iValue;
	}

	__UNGUARD__

}

void ItemTemplateTable::InitAttrSuckBallTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { TBItemId = 0, TBRate, TBItem};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_WANFA_ENERGYBALL);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	KCheck(ret);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	m_uAttrSuckBallCount= iTableCount;
	KCheck(iTableCount > 0);

	m_pAttrSuckBallData = new ATTR_SUCK_BALL_TB[m_uAttrSuckBallCount];

	KCheck(m_pAttrSuckBallData );

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pAttrSuckBallData[i].m_ItemId = ThirdFile.Search_Posistion(i, TBItemId)->iValue;
		m_pAttrSuckBallData[i].m_Rate= ThirdFile.Search_Posistion(i, TBRate)->iValue;
		const char	*pSplitString = ThirdFile.Search_Posistion(i, TBItem)->pString;
		SetNewItem(pSplitString, m_pAttrSuckBallData[i].m_nNewItem);
	}

	__UNGUARD__

}

void ItemTemplateTable::InitAttrSuckAmuletTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
	enum 
	{ TBItemId = 0, 
	  TBCost,
	  TBHole1, 
	  TBPart1,
	  TBHole2, 
	  TBPart2,
	  TBHole3,
	  TBPart3,
	  TBHole4, 
	  TBPart4,
	  TBHole5, 
	  TBPart5,
	  TBHole6,
	  TBPart6,
	  TBNumber
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_WANFA_AMULET);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uAttrSuckAmuletCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pAttrSuckAmuletData = new SERVER_ATTR_SUCK_AMULET_TB[m_uAttrSuckAmuletCount];

	KCheck(m_pAttrSuckAmuletData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pAttrSuckAmuletData[i].m_ItemId = ThirdFile.Search_Posistion(i, TBItemId)->iValue;
		m_pAttrSuckAmuletData[i].m_Cost	  = ThirdFile.Search_Posistion(i, TBCost)->iValue;
		
		for (int32 j=TBHole1;j<TBNumber; ++j)
		{
			if ((j%2) != 0)
				continue;
			
			int32 bHole = ThirdFile.Search_Posistion(i, j)->iValue;
			if (bHole>0)
			{
				m_pAttrSuckAmuletData[i].m_PointInfo[j/2-1].m_IsValid = bHole;
				const char	*pSplitString = ThirdFile.Search_Posistion(i, j+1)->pString;
				SetEquipPoint
					(
					pSplitString,
					HEQUIP_NUMBER,
					(uint32_t*)&m_pAttrSuckAmuletData[i].m_PointInfo[j/2-1].m_nEquipPoint[0]
					);

			}

		}
	
	}

	__UNGUARD__
}

void ItemTemplateTable::InitAttrSuckBallSynTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ enum { TBLevel =0,TBRate,TBItemId, TBItemCount};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_WANFA_ENERGYBALLSYN);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	KCheck(ret);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	m_uAttrSuckBallSynCount= iTableCount;
	KCheck(iTableCount > 0);

	m_pAttrSuckBallSynData = new ATTR_SUCK_BALL_SYB_TB[m_uAttrSuckBallSynCount];

	KCheck(m_pAttrSuckBallSynData );

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pAttrSuckBallSynData[i].m_Level = ThirdFile.Search_Posistion(i,TBLevel)->iValue;
		m_pAttrSuckBallSynData[i].m_Rate= ThirdFile.Search_Posistion(i, TBRate)->iValue;
		m_pAttrSuckBallSynData[i].m_ItemId = ThirdFile.Search_Posistion(i, TBItemId)->iValue;
		m_pAttrSuckBallSynData[i].m_ItemCount = ThirdFile.Search_Posistion(i, TBItemCount)->iValue;
	}

	__UNGUARD__

}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
void	ItemTemplateTable::InitEquipBlueAttrTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
		enum 
	{ TBEquipBlueAttrIdx = 0, 
	TBEquipBlueAttrName,
	TBEquipBlueAttrId,
	TBFloatMin,
	TBFloatMax,
	TBIntMin,
	TBIntMax,
	TBEquipBlueAttrLevels,
	TBRandSeed,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_BLUEATTR);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uEquipBlueAttrCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipBlueAttrData = new EQUIP_BLUEATTR_TB[m_uEquipBlueAttrCount];

	KCheck(m_pEquipBlueAttrData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipBlueAttrData[i].m_AttrIdx = ThirdFile.Search_Posistion(i, TBEquipBlueAttrIdx)->iValue;
		m_pEquipBlueAttrData[i].m_AttrId = ThirdFile.Search_Posistion(i, TBEquipBlueAttrId)->iValue;
		m_pEquipBlueAttrData[i].m_fMinEff = ThirdFile.Search_Posistion(i, TBFloatMin)->fValue;
		m_pEquipBlueAttrData[i].m_fMaxEff = ThirdFile.Search_Posistion(i, TBFloatMax)->fValue;
		m_pEquipBlueAttrData[i].m_nMinEff = ThirdFile.Search_Posistion(i, TBIntMin)->iValue;
		m_pEquipBlueAttrData[i].m_nMaxEff = ThirdFile.Search_Posistion(i, TBIntMax)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iATTID = m_pEquipBlueAttrData[i].m_AttrId;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iATTID >= 0)
		{
			m_pEquipBlueAttrData[i].m_AttrInfo.m_Attr = (ITEM_PROPERTY) iATTID;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const char	*pSplitString = ThirdFile.Search_Posistion(i, TBEquipBlueAttrLevels)->pString;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			SetEquipType
				(
				pSplitString,
				EQUIP_TYPE_NUM,
				m_pEquipBlueAttrData[i].m_AttrInfo.m_nValidEquipType
				);
		}

		m_pEquipBlueAttrData[i].m_nSeed = ThirdFile.Search_Posistion(i, TBRandSeed)->iValue;
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipBlueAttrTable()  Ok!");

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitEquipBlueIntensifyTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
		
	enum 
	{ 
		TBEquipAttrId,
		TBEquipAttrValueBegin = TBEquipAttrId + 2, 
		TBEquipReqIntensifyCount = TBEquipAttrValueBegin + BLUE_INTENSIFY_MAX_ENCHASE,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_BLUE_INTENSIFY);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uEquipBlueIntensifyCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipBlueIntensifyData = new EQUIP_BLUE_INTENSIFY_TB[m_uEquipBlueIntensifyCount];

	KCheck(m_pEquipBlueIntensifyData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipBlueIntensifyData[i].m_AttrId = ThirdFile.Search_Posistion(i, TBEquipAttrId)->iValue;

		for ( int32 valueId = 0; valueId < BLUE_INTENSIFY_MAX_ENCHASE; valueId++ )
		{
			m_pEquipBlueIntensifyData[i].m_AttrValue[valueId] = ThirdFile.Search_Posistion(i, TBEquipAttrValueBegin+valueId)->iValue;
		}

		m_pEquipBlueIntensifyData[i].m_ReqIntensifyCount = ThirdFile.Search_Posistion(i, TBEquipReqIntensifyCount)->iValue;

	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipBlueIntensifyTable()  Ok!");

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void	ItemTemplateTable::InitEquipProduceTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
		enum 
	{ TBEquipId = 0, 
	TBEquipSetId,
	TBMatId1,
	TBMatCount1,
	TBMatId2,
	TBMatCount2,
	TBMatId3,
	TBMatCount3,
	TBMatId4,
	TBMatCount4,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_PRODUCE);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_uEquipProduceCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipProduceData = new EQUIP_PRODUCE_TB[m_uEquipProduceCount];

	KCheck(m_pEquipProduceData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipProduceData[i].m_EquipId = ThirdFile.Search_Posistion(i, TBEquipId)->iValue;
		m_pEquipProduceData[i].m_EquipSetId = ThirdFile.Search_Posistion(i, TBEquipSetId)->iValue;
		m_pEquipProduceData[i].m_MatId1 = ThirdFile.Search_Posistion(i, TBMatId1)->iValue;
		m_pEquipProduceData[i].m_MatCount1 = ThirdFile.Search_Posistion(i, TBMatCount1)->iValue;
		m_pEquipProduceData[i].m_MatId2 = ThirdFile.Search_Posistion(i, TBMatId2)->iValue;
		m_pEquipProduceData[i].m_MatCount2 = ThirdFile.Search_Posistion(i, TBMatCount2)->iValue;
		m_pEquipProduceData[i].m_MatId3 = ThirdFile.Search_Posistion(i, TBMatId3)->iValue;
		m_pEquipProduceData[i].m_MatCount3 = ThirdFile.Search_Posistion(i, TBMatCount3)->iValue;
		m_pEquipProduceData[i].m_MatId4 = ThirdFile.Search_Posistion(i, TBMatId4)->iValue;
		m_pEquipProduceData[i].m_MatCount4 = ThirdFile.Search_Posistion(i, TBMatCount4)->iValue;

	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipProduceTable()  Ok!");

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void	ItemTemplateTable::InitEquipSwitchTable()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
		enum 
	{ TBEquipSourceId = 0, 
	TBEquipDestId,
	TBEquipCost,
	TBMaterial,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_SWITCH);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nEquipSwitchCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipSwitchData = new EQUIP_SWITCH_TB[m_nEquipSwitchCount];

	KCheck(m_pEquipSwitchData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipSwitchData[i].m_EquipSourceId = ThirdFile.Search_Posistion(i, TBEquipSourceId)->iValue;
		m_pEquipSwitchData[i].m_EquipDestId = ThirdFile.Search_Posistion(i, TBEquipDestId)->iValue;
		m_pEquipSwitchData[i].m_Cost = ThirdFile.Search_Posistion(i, TBEquipCost)->iValue;
		m_pEquipSwitchData[i].m_MaterialId = ThirdFile.Search_Posistion(i, TBMaterial)->iValue;

	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipSwitchTable()  Ok!");

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ItemTemplateTable::InitChangeAppearanceTable()
{
	__GUARD__
		enum 
	{ TBItemId = 0,};
	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_CHANGE_APPEARANCE_TABLE_NAME);

	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nChangeAppearanceCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pChangeAppearanceData = new CHANGE_APPEARANCE_TB[m_nChangeAppearanceCount];

	KCheck(m_pChangeAppearanceData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pChangeAppearanceData[i].m_ItemId = ThirdFile.Search_Posistion(i, TBItemId)->iValue;

	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitChangeAppearanceTable()  Ok!");

	__UNGUARD__
}


/*
=======================================================================================================================
=======================================================================================================================
*/
void ItemTemplateTable::InitNewEquipBlueAttrTable()
{
	__GUARD__
	enum 
	{	TBNewEquipBlueAttrIdx = 0, 
		TBNewEquipBlueAttrName,
		TBNewEquipBlueAttrId,
		TBNewEquipBlueAttrRate,
		TBNewEquipBlueAttrTypes,
		TBNewEquipBlueAttrRandSeed,
		TBNewEquipBlueAttrFloatMin,
		TBNewEquipBlueAttrFloatMax,
		TBNewEquipBlueAttrBlueValueBegin,
		TBNewEquipBlueAttrBlueValueEnd = TBNewEquipBlueAttrBlueValueBegin + MAX_EQUIP_LEVEL - ORANGE_EQUIP_BLUEATTR_MIN_LEVEL,
	};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_NEW_EQUIP_BLUEATTR);

	KCheck(ret);


	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();


	m_nNewEquipBlueAttrCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pNewEquipBlueAttrData = new NEW_EQUIP_BLUEATTR_TB[m_nNewEquipBlueAttrCount];

	KCheck(m_pNewEquipBlueAttrData);

	m_nNewEquipBlueAttrMaxSed = 0;

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pNewEquipBlueAttrData[i].m_AttrIdx = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrIdx)->iValue;
		m_pNewEquipBlueAttrData[i].m_AttrId = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrId)->iValue;
		m_pNewEquipBlueAttrData[i].m_fRate = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrRate)->fValue;

		m_pNewEquipBlueAttrData[i].m_nSeed = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrRandSeed)->iValue;
		m_nNewEquipBlueAttrMaxSed += m_pNewEquipBlueAttrData[i].m_nSeed;

		m_pNewEquipBlueAttrData[i].m_fMinEff = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrFloatMin)->fValue;
		m_pNewEquipBlueAttrData[i].m_fMaxEff = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrFloatMax)->fValue;


		int32	iATTID = m_pNewEquipBlueAttrData[i].m_AttrId;

		if(iATTID >= 0)
		{
			m_pNewEquipBlueAttrData[i].m_AttrInfo.m_Attr = (ITEM_PROPERTY) iATTID;


			const char	*pSplitString = ThirdFile.Search_Posistion(i, TBNewEquipBlueAttrTypes)->pString;


			SetEquipType
				(
				pSplitString,
				EQUIP_TYPE_NUM,
				m_pNewEquipBlueAttrData[i].m_AttrInfo.m_nValidEquipType
				);
		}

		int32 iColumn = TBNewEquipBlueAttrBlueValueBegin;
		int32 iIndex  =  0;
		int32 iATTValue =0;

		for(;iColumn <= TBNewEquipBlueAttrBlueValueEnd;++iColumn)
		{
			iATTValue = ThirdFile.Search_Posistion(i, iColumn)->iValue;

			if(iATTValue > 0)
			{
				m_pNewEquipBlueAttrData[i].m_Attr[iIndex + ORANGE_EQUIP_BLUEATTR_MIN_LEVEL -1] = iATTValue;
			}

			++iIndex;
		}
	}



	__UNGUARD__	
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void ItemTemplateTable::InitNewEquipProduceTable()
{
	__GUARD__
	enum {	TBEquipId = 0,
			TBNeedMoney,
			TBNeedItem1,
			TBNeedItem1Count,
			TBNeedItem2,
			TBNeedItem2Count,
			TBNeedItem3,
			TBNeedItem3Count,
			TBRate1Begin,
			TBRate1End = TBRate1Begin + EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER -1,
			TBNeedItem4,
			TBNeedItem4Count,
			TBRate2Begin,
			TBRate2End = TBRate2Begin + EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER -1,
		};


	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_PRODUCE_NEW);

	KCheck(ret);


	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();


	m_nNewEquipProduceCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pNewEquipProduceData = new NEW_EQUIP_PRODUCE_TB[m_nNewEquipProduceCount];

	KCheck(m_pNewEquipProduceData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pNewEquipProduceData[i].m_nEquipId = ThirdFile.Search_Posistion(i, TBEquipId)->iValue;
		m_pNewEquipProduceData[i].m_nNeedMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem1 = ThirdFile.Search_Posistion(i, TBNeedItem1)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem1Count = ThirdFile.Search_Posistion(i, TBNeedItem1Count)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem2 = ThirdFile.Search_Posistion(i, TBNeedItem2)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem2Count = ThirdFile.Search_Posistion(i, TBNeedItem2Count)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem3 = ThirdFile.Search_Posistion(i, TBNeedItem3)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem3Count = ThirdFile.Search_Posistion(i, TBNeedItem3Count)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem4 = ThirdFile.Search_Posistion(i, TBNeedItem4)->iValue;
		m_pNewEquipProduceData[i].m_nNeedItem4Count = ThirdFile.Search_Posistion(i, TBNeedItem4Count)->iValue;

		for (int32 j =0;j < EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER; ++j)
		{
			m_pNewEquipProduceData[i].m_nRate1[j] = ThirdFile.Search_Posistion(i, TBRate1Begin +j)->iValue;
			m_pNewEquipProduceData[i].m_nRate2[j] = ThirdFile.Search_Posistion(i, TBRate2Begin +j)->iValue;
		}
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitNewEquipProduceTable()  Ok!");

	__UNGUARD__
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitEquipConstAttrTable()
{
	__GUARD__
		enum {	TBAttrIndex = 0,
		TBAttrType = 2,
		TBAttrId,
		TBAttrValue,
		TBValidEquipType,
		TBRate,
		};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_CONST_ATTR);

	KCheck(ret);


	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();


	m_nEquipConstAttrCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipConstAttrData = new EQUIP_CONST_ATTR_TB[m_nEquipConstAttrCount];

	KCheck(m_pEquipConstAttrData);

	for (int32 i = 0;i < CONST_ATTR_TYPE_NUMBER;++i)
	{
		m_nEquipConstAttrMaxSed[i] = 0;
		m_nEquipConstAttrTypeCount[i] = 0;
	}

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipConstAttrData[i].m_AttrIndex = ThirdFile.Search_Posistion(i, TBAttrIndex)->iValue;
		m_pEquipConstAttrData[i].m_AttrType = ThirdFile.Search_Posistion(i, TBAttrType)->iValue;
		m_pEquipConstAttrData[i].m_AttrId = ThirdFile.Search_Posistion(i, TBAttrId)->iValue;
		m_pEquipConstAttrData[i].m_AttrValue = ThirdFile.Search_Posistion(i, TBAttrValue)->iValue;
		m_pEquipConstAttrData[i].m_Rate = ThirdFile.Search_Posistion(i, TBRate)->iValue;

		KCheck(m_pEquipConstAttrData[i].m_AttrType >= 0 && m_pEquipConstAttrData[i].m_AttrType < CONST_ATTR_TYPE_NUMBER);
		m_nEquipConstAttrMaxSed[m_pEquipConstAttrData[i].m_AttrType] += m_pEquipConstAttrData[i].m_Rate;

		m_nEquipConstAttrTypeCount[m_pEquipConstAttrData[i].m_AttrType]++;

		KCheck( m_pEquipConstAttrData[i].m_AttrId >= 0 &&  m_pEquipConstAttrData[i].m_AttrId < IPROPERTY_NUMBER);

		const char	*pSplitString = ThirdFile.Search_Posistion(i, TBValidEquipType)->pString;
		SetEquipType
			(
				pSplitString,
				EQUIP_TYPE_NUM,
				m_pEquipConstAttrData[i].m_nValidEquipType
			);

	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipConstAttrTable()  Ok!");

	__UNGUARD__	
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitEquipConstInfoTable()
{
	__GUARD__
		enum {	TBConstId = 0,
				TBActConstIdBegin = 2,
				TBActConstIdNameBegin,									
				TBARate = TBActConstIdBegin + 2 * MAX_EQUIP_CONST_ACTIVE_NEED,
		};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_CONST_INFO);

	KCheck(ret);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();

	m_nEquipConstInfoCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipConstInfoData = new EQUIP_CONST_INFO_TB[m_nEquipConstInfoCount];

	KCheck(m_pEquipConstInfoData);
	m_nEquipConstMaxSed = 0;
	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipConstInfoData[i].m_ConstId = ThirdFile.Search_Posistion(i, TBConstId)->iValue;
		int32 nIdIndex =0;
		for (int32 j = 0;j < 2 * MAX_EQUIP_CONST_ACTIVE_NEED && nIdIndex < MAX_EQUIP_CONST_ACTIVE_NEED;j += 2)
		{
			m_pEquipConstInfoData[i].m_ActConstId[nIdIndex] = ThirdFile.Search_Posistion(i, TBActConstIdBegin + j)->iValue;
			++nIdIndex;			
		}

		m_pEquipConstInfoData[i].m_Rate = ThirdFile.Search_Posistion(i, TBARate)->iValue;

		m_nEquipConstMaxSed += m_pEquipConstInfoData[i].m_Rate;


	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipConstInfoTable()  Ok!");

	__UNGUARD__	
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitEquipConstActivePointTable()
{
	__GUARD__
		enum {	TBEquipPoint = 0,
				TBActEquipPoint = 1,
		};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_CONST_ACTIVE_POINT);

	KCheck(ret);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();

	m_nEquipConstActivePointCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipConstActivePointData = new EQUIP_CONST_ACTIVE_POINT_TB[m_nEquipConstActivePointCount];

	KCheck(m_pEquipConstActivePointData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipConstActivePointData[i].m_EquipPoint = ThirdFile.Search_Posistion(i, TBEquipPoint)->iValue;
		m_pEquipConstActivePointData[i].m_ActEquipPoint = ThirdFile.Search_Posistion(i, TBActEquipPoint)->iValue;
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipConstActivePointTable()  Ok!");

	__UNGUARD__	
}
/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitEquipConstBindTable()
{
	__GUARD__
		enum {	TBNeedItemId = 0,
				TBNeedMoney,
				TBAddConstCount,
				TBRate = TBAddConstCount + MAX_EQUIP_CONST_ATTR,
		};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_CONST_BIND);

	KCheck(ret);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();

	m_nEquipConstBindCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipConstBindData = new EQUIP_CONST_BIND_TB[m_nEquipConstBindCount];

	KCheck(m_pEquipConstBindData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipConstBindData[i].m_NeedItemId = ThirdFile.Search_Posistion(i, TBNeedItemId)->iValue;
		m_pEquipConstBindData[i].m_NeedMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;

		for (int32 j = 0; j < MAX_EQUIP_CONST_ATTR; ++j)
		{
			m_pEquipConstBindData[i].m_AddConstCount[j] = ThirdFile.Search_Posistion(i, TBAddConstCount + j)->iValue;
			m_pEquipConstBindData[i].m_Rate[j] = ThirdFile.Search_Posistion(i, TBRate + j)->iValue;
		}
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipConstBindTable()  Ok!");

	__UNGUARD__	
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitItemSpecialTable()
{
	__GUARD__
		enum {	TBItemId = 1,
				TBUseType,
		};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_ITEM_SPECIAL);

	KCheck(ret);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();

	m_nItemSpecialCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pItemSpecialData = new ITEM_SPECAIL_TB[m_nItemSpecialCount];

	KCheck(m_pItemSpecialData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pItemSpecialData[i].m_nItemId = ThirdFile.Search_Posistion(i, TBItemId)->iValue;
		m_pItemSpecialData[i].m_nUseType = ThirdFile.Search_Posistion(i, TBUseType)->iValue;
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitItemSpecialTable()  Ok!");

	__UNGUARD__	
}

/*
=======================================================================================================================
=======================================================================================================================
*/
void	ItemTemplateTable::InitEquipHonorBindTable()
{
	__GUARD__
		enum {	TBBindLevel = 0,
		TBNeedGem,
		TBRate = TBNeedGem + MAX_EQUIP_HONOR_BIND_COND,
		TBPunish = TBRate + MAX_EQUIP_HONOR_BIND_COND,
		TBNeedMoney = TBPunish + MAX_EQUIP_HONOR_BIND_COND ,
		TBIntensify,
		};

	TABFile ThirdFile(0);
	BOOL	ret = ThirdFile.OpenFromTXT(FILE_EQUIP_HONOR_BIND);

	KCheck(ret);

	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();

	m_nEquipHonorBindCount = iTableCount;
	KCheck(iTableCount > 0);

	m_pEquipHonorBindData = new EQUIP_HONOR_BIND_TB[m_nEquipHonorBindCount];

	KCheck(m_pEquipHonorBindData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pEquipHonorBindData[i].m_BindLevel = ThirdFile.Search_Posistion(i, TBBindLevel)->iValue;
		m_pEquipHonorBindData[i].m_NeedMoney = ThirdFile.Search_Posistion(i, TBNeedMoney)->iValue;
		m_pEquipHonorBindData[i].m_Intensify = ThirdFile.Search_Posistion(i, TBIntensify)->iValue;

		for (int32 j =0;j < MAX_EQUIP_HONOR_BIND_COND;++j)
		{
			m_pEquipHonorBindData[i].m_NeedGem[j] = ThirdFile.Search_Posistion(i, TBNeedGem +j)->iValue;
			m_pEquipHonorBindData[i].m_Rate[j] = ThirdFile.Search_Posistion(i, TBRate +j)->iValue;
			m_pEquipHonorBindData[i].m_Punish[j] = ThirdFile.Search_Posistion(i, TBPunish +j)->iValue;
		}
	}

	QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "InitEquipHonorBindTable()  Ok!");

	__UNGUARD__	
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEffectMarryTable()
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum EffectMarryTBData
	{
		TBIndex,
		TBFeMaleStr,
		TBFeMaleCon,
		TBFeMaleInt,
		TBFeMaleDex,
		TBMaleStr,
		TBMaleCon,
		TBMaleInt,
		TBMaleDex,
		TBExp,
		TBDay,
	};
	/*~~~~~~~~~~~~*/


	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_EFFECT_MARRY);
	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount == MARRYRELEATION_NUMS);
	m_nMarryEffectCount = iTableCount;

	m_pMarryEffectData = new MARRYEFFECT_TB[m_nMarryEffectCount];

	KCheck(m_pMarryEffectData);

	for(int32 i = 0; i < m_nMarryEffectCount; i++)
	{
		m_pMarryEffectData[i].m_EffectRate[SEX_FEMALE].m_EffectRate[CPROPERTY_LEVEL1_STR] = ThirdFile.Search_Posistion(i, TBFeMaleStr)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_FEMALE].m_EffectRate[CPROPERTY_LEVEL1_CON] = ThirdFile.Search_Posistion(i, TBFeMaleCon)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_FEMALE].m_EffectRate[CPROPERTY_LEVEL1_INT] = ThirdFile.Search_Posistion(i, TBFeMaleInt)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_FEMALE].m_EffectRate[CPROPERTY_LEVEL1_DEX] = ThirdFile.Search_Posistion(i, TBFeMaleDex)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_MALE].m_EffectRate[CPROPERTY_LEVEL1_STR] = ThirdFile.Search_Posistion
			(
				i,
				TBMaleStr
			)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_MALE].m_EffectRate[CPROPERTY_LEVEL1_CON] = ThirdFile.Search_Posistion
			(
				i,
				TBMaleCon
			)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_MALE].m_EffectRate[CPROPERTY_LEVEL1_INT] = ThirdFile.Search_Posistion
			(
				i,
				TBMaleInt
			)->iValue;
		m_pMarryEffectData[i].m_EffectRate[SEX_MALE].m_EffectRate[CPROPERTY_LEVEL1_DEX] = ThirdFile.Search_Posistion
			(
				i,
				TBMaleDex
			)->iValue;
		m_pMarryEffectData[i].m_nExpRate = ThirdFile.Search_Posistion(i, TBExp)->iValue;
		m_pMarryEffectData[i].m_nDay = ThirdFile.Search_Posistion(i, TBDay)->iValue;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ItemTemplateTable::InitEffectFriend()
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum EffectFriendTBData { TBIndex, TBDefenceRate, TBFriendPoint, TBDay, TBDesc, };
	/*~~~~~~~~~~~~*/

	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(FILE_EFFECT_FRIEND);
	KCheck(ret);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	int32	iTableColumn = ThirdFile.GetFieldsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount == FRIENDRELEATION_NUMS);
	m_nFriendEffectCount = iTableCount;

	m_pFriendEffectData = new FRIENDEFFECT_TB[m_nFriendEffectCount];

	KCheck(m_pFriendEffectData);

	for(int32 i = 0; i < iTableCount; i++)
	{
		m_pFriendEffectData[i].m_nEffectRate = ThirdFile.Search_Posistion(i, TBDefenceRate)->iValue;
		m_pFriendEffectData[i].m_nFriendPoint = ThirdFile.Search_Posistion(i, TBFriendPoint)->iValue;
		m_pFriendEffectData[i].m_nFriendDay = ThirdFile.Search_Posistion(i, TBDay)->iValue;
		m_pFriendEffectData[i].m_nEffectRate = ThirdFile.Search_Posistion(i, TBDefenceRate)->iValue;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		const char	*pszDesc = ThirdFile.Search_Posistion(i, TBDesc)->pString;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		tsnprintf_s(m_pFriendEffectData[i].m_szDesc, sizeof(m_pFriendEffectData[i].m_szDesc), "%s", pszDesc);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
MONSTER_DROP_TB *ItemTemplateTable::GetMonsterDropTB(int32 iDropId)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ MONSTER_DROP_TB	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_DropId = iDropId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MONSTER_DROP_TB *pResult = (MONSTER_DROP_TB *) bsearch
		(
			&tb,
			m_pMonsterDropTableData,
			m_nMonsterDropCount,
			sizeof(MONSTER_DROP_TB),
			(int32(*) (const void *, const void *)) Compare_MonsterDropTab
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search Obj_Monster Drop iDropId:%d Get Errors", iDropId);
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
DROP_POS_TB *ItemTemplateTable::GetDropPosTB(int32 nDropPoint)
{
	__GUARD__ if((uint32) nDropPoint < m_nDropPosCount)
	{
		return &m_pDropPosData[nDropPoint];
	}

	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ItemTemplateTable::GetEquipPointValue(PLAYER_EQUIP equipPoint)
{
	KCheck(equipPoint < HEQUIP_NUMBER);
	return m_nEquipPointInfo[equipPoint];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
PAI_INFO *ItemTemplateTable::GetPaiInfo(uint32 nType)
{
	if(nType > EQUIP_PAI_NUM)
	{
		return NULL;
	}

	return &m_nPaiInfo[nType];
}

int32  ItemTemplateTable::GetPaiIDByPaiType(int32 nType)
{
	if (nType < EQUIPPAI_ANY || nType >= EQUIP_PAI_NUM)
	{
		return INVALID_PAI_TYPE;
	}

	if(nType >= EQUIPPAI_ANY && nType <= EQUIPPAI_ANY_END)
	{
		if (m_nPaiInfo[nType].m_nPaiIDSetCount > 0)
		{
			int32 nRand = RandGenerator::GetRand(0, m_nPaiInfo[nType].m_nPaiIDSetCount - 1);
			return m_nPaiInfo[nType].m_nPaiIDSet[nRand];
		}
		else
		{
			return INVALID_PAI_TYPE;
		}
			
	}
	else
	{
		return nType;
	}
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
SEquipTab *ItemTemplateTable::GetEquipTB(uint32 itemSerial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SEquipTab	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_IndexID = itemSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SEquipTab	*pResult = (SEquipTab *) bsearch
		(
			&tb,
			m_pEquipTableData,
			m_nEquipCount,
			sizeof(SEquipTab),
			(int32(*) (const void *, const void *)) CompareEquipTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search Equip ItemSerial:%d  Get Errors", itemSerial);
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIP_ATT_LEVEL_TB *ItemTemplateTable::GetAttLevelValue(ITEM_PROPERTY iAtt)
{
	__GUARD__ if((iAtt >= 0) && (iAtt < (int32) MAX_ATT_COUNT))
	{
		return &m_pAttLevelTableData[iAtt];
	}

	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIP_ATT_SET_TB *ItemTemplateTable::GetAttSetTB(int32 nSetID)
{
	__GUARD__ if((nSetID > 0) && (nSetID < (int32) m_nEquipSetCount))
	{
		return &m_pEquipAttSetTableData[nSetID];
	}

	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIP_ATT_SET_TB *ItemTemplateTable::GetAttSetTBByRate(int32 nRate)
{
	__GUARD__
#define MAX_EQUIP_QUALITY_RAND	10000

	int32 SumInt = 0;

	for(uint32 i = 0; i < m_nEquipAttSetCount; ++i)
	{
		if(m_pEquipAttSetTableData[i].m_AttSetRate > 0)
		{
			if(SumInt + m_pEquipAttSetTableData[i].m_AttSetRate >= nRate)
				return &m_pEquipAttSetTableData[i];
			else
				SumInt += m_pEquipAttSetTableData[i].m_AttSetRate;
		}
		else
			continue;
	}

	return NULL;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ItemTemplateTable::GetSumRateByReqLevel(int32 nLevel)
{
	__GUARD__ for(int32 i = m_nEquipAttSetCount - 1; i >= 0; --i)
	{
		if(nLevel > m_pEquipAttSetTableData[i].m_ReqLevel)
		{
			return m_pEquipAttSetTableData[i].m_SumRate;
		}
	}

	KCheck(0);

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SDropAttrTab *ItemTemplateTable::GetDropAttTB(int32 iDeltaLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SDropAttrTab	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_DeltaLevel = iDeltaLevel;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SDropAttrTab	*pResult = (SDropAttrTab *) bsearch
		(
			&tb,
			m_pDropAttData,
			m_nDropAttCount,
			sizeof(SDropAttrTab),
			(int32(*) (const void *, const void *)) Compare_DropAttTab
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search DropAttTB Delta Level: %d Get Errors", iDeltaLevel);
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SGemInfoTab *ItemTemplateTable::GetGemInfoTB(uint32 TableIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SGemInfoTab	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nTableIndex = TableIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SGemInfoTab	*pResult = (SGemInfoTab *) bsearch
		(
			&tb,
			m_pGemInfoData,
			m_nGemCount,
			sizeof(SGemInfoTab),
			(int32(*) (const void *, const void *)) Compare_GemInfoTabByTI
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search GemInfoTB Index:%d  Get Errors", TableIndex);
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIPHOLE_INFO_TB *ItemTemplateTable::GetEquipHoleInfoTB(uint32 nHoleNum)
{
	__GUARD__ if((nHoleNum <= MAX_ITEM_GEM) && (nHoleNum != 0))
	{
		return &m_EquipHoleInfoData[--nHoleNum];
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIPCHAIN_INFO_TB *ItemTemplateTable::GetEquipChainInfoTB(uint32 nIndex)
{
	__GUARD__ if(nIndex < m_nEquipChainInfoCount)
	{
		return &m_EquipChainInfoData[nIndex];
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIPCHAIN_INFO_TB *ItemTemplateTable::GetEquipChainInfoTBByID(uint32 chainID)
{
	__GUARD__ for(int32 i = 0; i < m_nEquipChainInfoCount; ++i)
	{
		if(m_EquipChainInfoData[i].m_ChainID == chainID)
		{
			return &m_EquipChainInfoData[i];
		}
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIPSOUL_INFO_TB *ItemTemplateTable::GetEquipSoulInfoTB(uint32 nIndex)
{
	__GUARD__ if(nIndex < m_nEquipSoulInfoCount)
	{
		return &m_EquipSoulInfoData[nIndex];
	}

	return NULL;
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIPLEVELUP_INFO *ItemTemplateTable::GetEquipLeveupTB(EQUIP_LEVEL_TYPE nType, PLAYER_EQUIP equipPoint, uint32 nLevel)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(nType < EQUIPLEVEL_TYPENUM);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((nLevel <= MAX_EQUIP_LEVELUP_NUM) && (nLevel != 0))
	{
		return &m_EquipLeveupInfoData[equipPoint].m_EquipLevelupInfo[--nLevel][nType];
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIP_BIND_TB *ItemTemplateTable::GetEquipBindTB(uint32 nLevel)
{
	__GUARD__ if((nLevel <= MAX_EQUIP_BIND_LEVEL) && (nLevel != 0))
	{
		return &m_EquipBindInfoData[--nLevel];
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIP_SPECIALREPAIR_TB *ItemTemplateTable::GetSpecialRepairTB(uint32 itemSerial)
{
	__GUARD__ for(int32 i = 0; i < m_nSpecialRepairCount; i++)
	{
		if(m_EquipSpecialRepairData[i].m_RepairItemID == itemSerial) return &m_EquipSpecialRepairData[i];
	}

	return NULL;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ITEM_PRODUCT_INFO_TB *ItemTemplateTable::GetItemProductInfoTB(uint32 nProductID)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ITEM_PRODUCT_INFO_TB	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_ProductID = nProductID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ITEM_PRODUCT_INFO_TB	*pResult = (ITEM_PRODUCT_INFO_TB *) bsearch
		(
			&tb,
			m_pProductInfoData,
			m_nProductCount,
			sizeof(ITEM_PRODUCT_INFO_TB),
			(int32(*) (const void *, const void *)) CompareProductInfoTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search CompareProductInfoTB nProductID:%d ", nProductID);
		return 0;
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
MATERIAL_LEVEL_INFO_TB *ItemTemplateTable::GetMaterialInfoTB(uint32 nLevel)
{
	__GUARD__ if((nLevel <= MAX_VALIDMATERIAL_LEVEL) && (nLevel != 0))
	{
		return &m_MaterialLevelInfoData[--nLevel];
	}

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EQUIPEXTRATT_TB *ItemTemplateTable::GetEquipExtraAttInfoTB(PLAYER_EQUIP equipPoint, uint32 nScore)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIPEXTRATT_TB	*pTb = NULL;
	int32				beginPos = -1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(equipPoint)
	{
	case HEQUIP_MAINHAND:
	case HEQUIP_ASSIHAND:
	case HEQUIP_HEAD:
	case HEQUIP_NECK:
	case HEQUIP_SHOULDER:
	case HEQUIP_BACK:
	case HEQUIP_WRIST:
	case HEQUIP_HAND:
	case HEQUIP_WAIST:
	case HEQUIP_FEET:
	case HEQUIP_RING1:
		{
			beginPos = equipPoint;
		}
		break;

	case HEQUIP_RING2:
		{
			beginPos = HEQUIP_RING1;
		}
		break;

	case HEQUIP_ADORN1:
	case HEQUIP_ADORN2:
		{
			beginPos = HEQUIP_RING2;
		}
		break;
	}

	if(beginPos == -1)
	{
		KCheck(0);
	}

	KCheck(beginPos <= (m_nEquipExtraInfoCount - HEQUIP_RING2));
	for(int32 i = 0; i < MAX_VALIDMATERIAL_LEVEL; ++i)
	{
		if(nScore >= m_EquipExtraInfoData[i + MAX_VALIDMATERIAL_LEVEL * beginPos].m_nEquipScore)
		{
			pTb = &m_EquipExtraInfoData[i + MAX_VALIDMATERIAL_LEVEL * beginPos];
		}
		else
		{
			break;
		}
	}

	return pTb;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
EXTRABAG_INFO_TB *ItemTemplateTable::GetExtraBagInfoTB(uint32 itemSerial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EXTRABAG_INFO_TB	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nTableIndex = itemSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXTRABAG_INFO_TB	*pResult = (EXTRABAG_INFO_TB *) bsearch
		(
			&tb,
			m_pExtraBagInfoData,
			m_nExtraBagInfoCount,
			sizeof(EXTRABAG_INFO_TB),
			(int32(*) (const void *, const void *)) CompareExtraBagInfoTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search GetExtraBagInfoTB itemSerial:%d  Get Errors", itemSerial);
		return 0;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CHANGEPAI_INFO_TB *ItemTemplateTable::GetChangePaiInfoTB(uint32 itemSerial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ CHANGEPAI_INFO_TB	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nTableIndex = itemSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	CHANGEPAI_INFO_TB	*pResult = (CHANGEPAI_INFO_TB *) bsearch
		(
			&tb,
			m_pChangePaiInfoData,
			m_nChangePaiInfoCount,
			sizeof(CHANGEPAI_INFO_TB),
			(int32(*) (const void *, const void *)) CompareChangePaiInfoTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"Search GetChangePaiInfoTB itemSerial:%d  Get Errors",
				itemSerial
			);
		return 0;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CHANGEPAI_INFO_TB *ItemTemplateTable::GetExchangeChangePaiInfoTB()
{
	__GUARD__ if(m_pChangePaiInfoData)
	{
		return &m_pChangePaiInfoData[0];
	}

	return NULL;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SMiscItemInfoTab *ItemTemplateTable::GetCommItemInfoTB(uint32 itemSerial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SMiscItemInfoTab	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nTableIndex = itemSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SMiscItemInfoTab	*pResult = (SMiscItemInfoTab *) bsearch
		(
			&tb,
			m_pCommItemInfoData,
			m_nCommItemCount,
			sizeof(SMiscItemInfoTab),
			(int32(*) (const void *, const void *)) Compare_CommItemInfoTab
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search CommItemInfoTB itemSerial:%d  Get Errors", itemSerial);
		return 0;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TASKITEM_INFO_TB *ItemTemplateTable::GetTaskItemInfoTB(uint32 itemSerial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TASKITEM_INFO_TB	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nTableIndex = itemSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TASKITEM_INFO_TB	*pResult = (TASKITEM_INFO_TB *) bsearch
		(
			&tb,
			m_pTaskItemInfoData,
			m_nTaskItemCount,
			sizeof(TASKITEM_INFO_TB),
			(int32(*) (const void *, const void *)) CompareTaskItemInfoTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"Search TaskItemInfoTB itemSerial:%d  Type:%d Get Errors",
				itemSerial
			);
		return 0;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SEquipSetTab *ItemTemplateTable::GetEquipSetTB(int32 EquipSetSerial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SEquipSetTab	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nEquipSetSerial = EquipSetSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SEquipSetTab	*pResult = (SEquipSetTab *) bsearch
		(
			&tb,
			m_pEquipSetData,
			m_nEquipSetCount,
			sizeof(SEquipSetTab),
			(int32(*) (const void *, const void *)) Compare_EquipSetTab
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search EquipSetTB Serial:%d Get Errors", EquipSetSerial);
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
MARRYEFFECT_TB *ItemTemplateTable::GetMarryEffectTB(int32 MarryLevel)
{
	__GUARD__ if((MarryLevel > m_nMarryEffectCount) || (MarryLevel < 0))
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search GetMarryEffectTB MarryLevel:%d Get Errors", MarryLevel);
		return NULL;
	}

	return &m_pMarryEffectData[MarryLevel];

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemTemplateTable::GetMarryEffectTBCount()
{
	__GUARD__ return m_nMarryEffectCount;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FRIENDEFFECT_TB *ItemTemplateTable::GetFriendEffectTB(int32 FriendLevel)
{
	__GUARD__ if((FriendLevel > m_nFriendEffectCount) || (FriendLevel < 0))
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"Search GetFriendEffectTB FriendLevel:%d Get Errors",
				FriendLevel
			);
		return NULL;
	}

	return &m_pFriendEffectData[FriendLevel];

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 ItemTemplateTable::GetFriendEffectTBCount()
{
	__GUARD__ return m_nFriendEffectCount;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const FRIEND_GIFT_TB *ItemTemplateTable::GetFriendGiftData(int32 nItemTableIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pFriendGiftData);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < m_nFriendGiftCount; ++i)
	{
		if(m_pFriendGiftData[i].m_nItemTableIndex == nItemTableIndex)
		{
			return &m_pFriendGiftData[i];
		}
	}

	return NULL;

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_ACTIVATION_TB *ItemTemplateTable::GetEquipActivationTB(int32 index) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pEquipActivationData);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(index >= 0 && index < m_nEquipActivationCount);
	return &m_pEquipActivationData[index];
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_PURPLE_REWORK_TB *ItemTemplateTable::GetEquipPurpleReworkTB(int32 index) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(m_pEquipPurpleReworkData);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(index >= 0 && index < m_nEquipPurpleReworkCount);
	return &m_pEquipPurpleReworkData[index];

	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_COLORCHANGE_TB *ItemTemplateTable::GetEquipColorChangeTB(uint32 itemSerial) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_COLORCHANGE_TB	tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_YellowItem = itemSerial;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EQUIP_COLORCHANGE_TB	*pResult = (EQUIP_COLORCHANGE_TB *) bsearch
		(
			&tb,
			m_pEquipColorChangeData,
			m_nEquipColorChangeCount,
			sizeof(EQUIP_COLORCHANGE_TB),
			(int32(*) (const void *, const void *)) CompareEquipColorChangeTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG
			(
				SLOW_LOG_SERVER,
				"Search EQUIP_COLORCHANGE_TB ItemSerial:%d  Get Errors",
				itemSerial
			);
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_PURPLEATTR_TB *ItemTemplateTable::GetEquipPurpleAttrTB(int32 index) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(index >= 0 && index < m_nEquipPurpleAttrCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return &m_pEquipPurpleAttrData[index];
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const GEM_REWORK_TB *ItemTemplateTable::GetGemReworkTB(uint32 index) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(index >= 0 && index < m_uGemReworkCount);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return &m_pGemReworkData[index];
	__UNGUARD__ return NULL;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_COPY_TB *ItemTemplateTable::GetEquipCopyTB(uint32 itemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_COPY_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_ItemId = itemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EQUIP_COPY_TB	*pResult = (EQUIP_COPY_TB *) bsearch
		(
			&tb,
			m_pEquipCopyData,
			m_uEquipCopyCount,
			sizeof(EQUIP_COPY_TB),
			(int32(*) (const void *, const void *)) CompareEquipCopyTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search GetEquipCopyTB itemId:%d  Get Errors", itemId);
	}

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const EQUIP_RECALL_TB *ItemTemplateTable::GetEquipRecallTB(uint32 itemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_RECALL_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_ItemId = itemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EQUIP_RECALL_TB	*pResult = (EQUIP_RECALL_TB *) bsearch
		(
		&tb,
		m_pEquipRecallData,
		m_uEquipRecallCount,
		sizeof(EQUIP_RECALL_TB),
		(int32(*) (const void *, const void *)) CompareEquipRecallTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
	{
		QLogSystem::SLOW_LOG(SLOW_LOG_SERVER, "Search GetEquipRecallTB itemId:%d  Get Errors", itemId);
	}

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const TRANSITEM_POS_TB *ItemTemplateTable::GetTransItemPosTB(uint32 mapId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ TRANSITEM_POS_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_MapId = mapId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TRANSITEM_POS_TB	*pResult = (TRANSITEM_POS_TB *) bsearch
		(
		&tb,
		m_pTransItemPosData,
		m_uTransItemPosCount,
		sizeof(TRANSITEM_POS_TB),
		(int32(*) (const void *, const void *)) CompareTransItemPosTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;
	
	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const  ATTR_SUCK_BALL_TB*ItemTemplateTable::GetAttrSuckBallTB(uint32 itemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ATTR_SUCK_BALL_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_ItemId = itemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ATTR_SUCK_BALL_TB	*pResult = (ATTR_SUCK_BALL_TB *) bsearch
		(
		&tb,
		m_pAttrSuckBallData,
		m_uAttrSuckBallCount,
		sizeof(ATTR_SUCK_BALL_TB),
		(int32(*) (const void *, const void *)) CompareSuckBallTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const  SERVER_ATTR_SUCK_AMULET_TB*ItemTemplateTable::GetAttrSuckAmuletTB(uint32 itemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ SERVER_ATTR_SUCK_AMULET_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_ItemId = itemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SERVER_ATTR_SUCK_AMULET_TB*pResult = (SERVER_ATTR_SUCK_AMULET_TB*) bsearch
		(
		&tb,
		m_pAttrSuckAmuletData,
		m_uAttrSuckAmuletCount,
		sizeof(SERVER_ATTR_SUCK_AMULET_TB),
		(int32(*) (const void *, const void *)) CompareSuckAmuletTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const  ATTR_SUCK_BALL_SYB_TB*ItemTemplateTable::GetAttrSuckBallSynTB(uchar cLevel) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ ATTR_SUCK_BALL_SYB_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_Level = cLevel;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	ATTR_SUCK_BALL_SYB_TB*pResult = (ATTR_SUCK_BALL_SYB_TB *) bsearch
		(
		&tb,
		m_pAttrSuckBallSynData,
		m_uAttrSuckBallSynCount,
		sizeof(ATTR_SUCK_BALL_SYB_TB),
		(int32(*) (const void *, const void *)) CompareSuckBallSynTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_PRODUCE_TB* ItemTemplateTable::GetEquipProduceTB(uint32 itemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_PRODUCE_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_EquipId = itemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EQUIP_PRODUCE_TB	*pResult = (EQUIP_PRODUCE_TB *) bsearch
		(
		&tb,
		m_pEquipProduceData,
		m_uEquipProduceCount,
		sizeof(EQUIP_PRODUCE_TB),
		(int32(*) (const void *, const void *)) CompareEquipProduceTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_BLUEATTR_TB* ItemTemplateTable::GetEquipBlueAttrTB(uint32 itemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_BLUEATTR_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_AttrIdx = itemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EQUIP_BLUEATTR_TB	*pResult = (EQUIP_BLUEATTR_TB *) bsearch
		(
		&tb,
		m_pEquipBlueAttrData,
		m_uEquipBlueAttrCount,
		sizeof(EQUIP_BLUEATTR_TB),
		(int32(*) (const void *, const void *)) CompareEquipBlueAttrTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_BLUE_INTENSIFY_TB* ItemTemplateTable::GetEquipBlueIntensifyTB(uint32 tabAttrId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_BLUE_INTENSIFY_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_AttrId = tabAttrId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EQUIP_BLUE_INTENSIFY_TB	*pResult = (EQUIP_BLUE_INTENSIFY_TB *) bsearch
		(
		&tb,
		m_pEquipBlueIntensifyData,
		m_uEquipBlueIntensifyCount,
		sizeof(EQUIP_BLUE_INTENSIFY_TB),
		(int32(*) (const void *, const void *)) CompareEquipBlueIntensifyAttrTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const EQUIP_SWITCH_TB* ItemTemplateTable::GetEquipSwitchTB(uint32 itemSerial) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ EQUIP_SWITCH_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_EquipSourceId = itemSerial;

	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//EQUIP_SWITCH_TB	*pResult = (EQUIP_SWITCH_TB *) bsearch
	//	(
	//	&tb,
	//	m_pEquipSwitchData,
	//	m_nEquipSwitchCount,
	//	sizeof(EQUIP_SWITCH_TB),
	//	(int32(*) (const void *, const void *)) CompareEquipSwitchTB
	//	);
	///*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//if(pResult)
	//	return pResult;
	//else
	//	return 0;

	for(int i=0; i<m_nEquipSwitchCount; ++i)
	{
		if (m_pEquipSwitchData[i].m_EquipSourceId == itemSerial)
		{
			return m_pEquipSwitchData + i;
		}
	}

	return 0;

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const CHANGE_APPEARANCE_TB* ItemTemplateTable::GetChangeAppearanceTB(uint32 itemSerial) const
{
	__GUARD__

	for(int i=0; i < m_nChangeAppearanceCount;++i)
	{
		if (m_pChangeAppearanceData[i].m_ItemId == itemSerial)
		{
			return m_pChangeAppearanceData + i;
		}
	}

	return 0;

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const NEW_EQUIP_BLUEATTR_TB* ItemTemplateTable::GetNewEquipBlueAttrTB(uint32 nTableIndex) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ NEW_EQUIP_BLUEATTR_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_AttrIdx = nTableIndex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	NEW_EQUIP_BLUEATTR_TB	*pResult = (NEW_EQUIP_BLUEATTR_TB *) bsearch
		(
		&tb,
		m_pNewEquipBlueAttrData,
		m_nNewEquipBlueAttrCount,
		sizeof(NEW_EQUIP_BLUEATTR_TB),
		(int32(*) (const void *, const void *)) CompareNewEquipBlueAttrTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
const NEW_EQUIP_PRODUCE_TB* ItemTemplateTable::GetNewEquipProduceTB(uint32 nEquipItemId) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ NEW_EQUIP_PRODUCE_TB tb;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	tb.m_nEquipId = nEquipItemId;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	NEW_EQUIP_PRODUCE_TB	*pResult = (NEW_EQUIP_PRODUCE_TB *) bsearch
		(
		&tb,
		m_pNewEquipProduceData,
		m_nNewEquipProduceCount,
		sizeof(NEW_EQUIP_PRODUCE_TB),
		(int32(*) (const void *, const void *)) CompareNewEquipProduceTB
		);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

const EQUIP_CONST_ATTR_TB* ItemTemplateTable::GetEquipConstAttrTB(uint32 nAttrIndex) const
{
	__GUARD__ EQUIP_CONST_ATTR_TB tb;

	tb.m_AttrIndex = nAttrIndex;

	EQUIP_CONST_ATTR_TB	*pResult = (EQUIP_CONST_ATTR_TB *) bsearch
		(
		&tb,
		m_pEquipConstAttrData,
		m_nEquipConstAttrCount,
		sizeof(EQUIP_CONST_ATTR_TB),
		(int32(*) (const void *, const void *)) CompareConstAttrTB
		);

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

const EQUIP_CONST_INFO_TB* ItemTemplateTable::GetEquipConstInfoTB(int32 nConstId) const
{
	__GUARD__ EQUIP_CONST_INFO_TB tb;

	tb.m_ConstId = nConstId;

	EQUIP_CONST_INFO_TB	*pResult = (EQUIP_CONST_INFO_TB *) bsearch
		(
		&tb,
		m_pEquipConstInfoData,
		m_nEquipConstInfoCount,
		sizeof(EQUIP_CONST_INFO_TB),
		(int32(*) (const void *, const void *)) CompareConstInfoTB
		);

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

const EQUIP_CONST_ACTIVE_POINT_TB* ItemTemplateTable::GetEquipConstActivePointTB(int32 nEquipPoint) const
{
	__GUARD__ EQUIP_CONST_ACTIVE_POINT_TB tb;

	tb.m_EquipPoint = nEquipPoint;

	EQUIP_CONST_ACTIVE_POINT_TB	*pResult = (EQUIP_CONST_ACTIVE_POINT_TB *) bsearch
		(
		&tb,
		m_pEquipConstActivePointData,
		m_nEquipConstActivePointCount,
		sizeof(EQUIP_CONST_ACTIVE_POINT_TB),
		(int32(*) (const void *, const void *)) CompareConstActivePointTB
		);

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

const EQUIP_CONST_BIND_TB* ItemTemplateTable::GetEquipConstBindTB(uint32 nItemId) const
{
	__GUARD__ EQUIP_CONST_BIND_TB tb;

	tb.m_NeedItemId = nItemId;

	EQUIP_CONST_BIND_TB	*pResult = (EQUIP_CONST_BIND_TB *) bsearch
		(
		&tb,
		m_pEquipConstBindData,
		m_nEquipConstBindCount,
		sizeof(EQUIP_CONST_BIND_TB),
		(int32(*) (const void *, const void *)) CompareConstBindTB
		);

	if(pResult)
		return pResult;
	else
		return 0;

	__UNGUARD__ return 0;
}

const ITEM_SPECAIL_TB* ItemTemplateTable::GetItemSpecialTB(const uint32 nItemId,const int32 nUseType) const
{
	__GUARD__ 

	if (NULL == m_pItemSpecialData)
	{
		return NULL;
	}

	for(int i=0; i < m_nItemSpecialCount;++i)
	{
		if (nUseType == m_pItemSpecialData[i].m_nUseType 
			&& nItemId == m_pItemSpecialData[i].m_nItemId)
		{
			return m_pItemSpecialData + i;
		}
	}

	return NULL;

	__UNGUARD__ return NULL;
}

const EQUIP_HONOR_BIND_TB* ItemTemplateTable::GetEquipHonorBindTB(const int32 nBindLevel) const
{
	__GUARD__ 

	if (NULL == m_pEquipHonorBindData)
	{
		return NULL;
	}

	for(int i=0; i < m_nEquipHonorBindCount;++i)
	{
		if (nBindLevel == m_pEquipHonorBindData[i].m_BindLevel)
		{
			return m_pEquipHonorBindData + i;
		}
	}

	return NULL;

	__UNGUARD__ return NULL;
}
/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar GetMaxItemTile(SItemType &it)
{
	__GUARD__ if(it.m_Class == ICLASS_EQUIP)
	{
		return 1;
	}
	else if(it.m_Class == ICLASS_GEM)
	{
		return 1;
	}
	else if(it.m_Class == ICLASS_EXTRABAG)
	{
		return 1;
	}
	else if(it.m_Class == ICLASS_COMITEM)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(it.ToSerial());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pGET)
		{
			if(!CheckItemRuler::CheckRuler(IRL_TILE, GetItemRuler(it.ToSerial())))
			{
				KCheck(pGET->m_nLayedNum == 1);
			}

			return pGET->m_nLayedNum;
		}
		else
		{
			KCheck(FALSE);
			return 0;
		}
	}
	else if(it.m_Class == ICLASS_MATERIAL)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(it.ToSerial());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pGET)
		{
			if(!CheckItemRuler::CheckRuler(IRL_TILE, GetItemRuler(it.ToSerial())))
			{
				KCheck(pGET->m_nLayedNum == 1);
			}

			return pGET->m_nLayedNum;
		}
		else
		{
			KCheck(FALSE);
			return 0;
		}
	}
	else if(it.m_Class == ICLASS_TASKITEM)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(it.ToSerial());
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pGET)
		{
			if(!CheckItemRuler::CheckRuler(IRL_TILE, GetItemRuler(it.ToSerial())))
			{
				KCheck(pGET->m_nLayedNum == 1);
			}

			return pGET->m_nLayedNum;
		}
		else
		{
			KCheck(FALSE);
			return 0;
		}
	}
	else
	{
		KCheckEx(FALSE, "Not Implement Type in GetMaxItemTile()");
		return 0;
	}

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 GetItemMaxLayedNum(uint32 Serial)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uchar bClass = GetClassBySerial(Serial);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(bClass)
	{
	case ICLASS_EQUIP:
		{
			return 1;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pComTable = g_ItemTab.GetCommItemInfoTB(Serial);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pComTable)
			{
				return pComTable->m_nLayedNum;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pTaskTable = g_ItemTab.GetTaskItemInfoTB(Serial);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pTaskTable)
			{
				return pTaskTable->m_nLayedNum;
			}

			KCheck(FALSE);
		}
		break;

	case ICLASS_GEM:
		{
			return 1;
		}
		break;

	case ICLASS_EXTRABAG:
		{
			return 1;
		}

	default:
		KCheck(FALSE);
		break;
	}

	return 0;
	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uchar GetItemRuler(uint32 itemIndex)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	nType = GetClassBySerial(itemIndex);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(nType)
	{
	case ICLASS_EQUIP:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SEquipTab	*pGET = g_ItemTab.GetEquipTB(itemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_RulerID;
		}
		break;

	case ICLASS_MATERIAL:
	case ICLASS_COMITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SMiscItemInfoTab	*pGET = g_ItemTab.GetCommItemInfoTB(itemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	case ICLASS_TASKITEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			TASKITEM_INFO_TB	*pGET = g_ItemTab.GetTaskItemInfoTB(itemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	case ICLASS_GEM:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			SGemInfoTab	*pGET = g_ItemTab.GetGemInfoTB(itemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	case ICLASS_EXTRABAG:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			EXTRABAG_INFO_TB	*pGET = g_ItemTab.GetExtraBagInfoTB(itemIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			KCheck(pGET);
			return pGET->m_nRulerID;
		}
		break;

	default:
		{
			KCheck(0);
		}
	}

	__UNGUARD__ return -1;
}
