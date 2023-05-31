/*$T Common/ScriptCommandStruct.cpp GC 1.140 10/10/07 10:06:54 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "TypeDefine.h"
#include "StructCommandScript.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SScriptString::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize = sizeof(int16) + m_Size * sizeof(char);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return uSize;

	__UNGUARD__ return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SScriptEventItem::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_nType);
	switch(m_nType)
	{
	case EVENT_ITEM_TYPE_TEXT:
	case EVENT_ITEM_TYPE_SECTION:
		uSize += m_strString.GetBufSize();
		break;

	case EVENT_ITEM_TYPE_SCRIPT_ID:
		uSize += m_strString.GetBufSize();
		uSize += sizeof(m_idScript);
		uSize += sizeof(m_state);
		uSize += sizeof(m_index);
		break;

	default:
		break;
	}

	return uSize;

	__UNGUARD__ return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SScriptParamEventList::GetBufSize(void) const
{
	/*~~~~~~~~~~*/
	uint32	uSize;
	uchar	i;
	/*~~~~~~~~~~*/

	uSize = sizeof(m_idNPC);
	uSize += sizeof(m_yItemCount);
	for(i = 0; i < m_yItemCount; i++)
	{
		uSize += m_seiItem[i].GetBufSize();
	}

	return uSize;
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SQuestBonusItem::GetBufSize(void) const
{
	__GUARD__ return sizeof(m_yCount) + sizeof(m_uItemID);

	__UNGUARD__
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SQuestDemandKill::GetBufSize(void) const
{
	__GUARD__ return sizeof(m_yCount) + sizeof(m_uNPCID);

	__UNGUARD__
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SQuestBonus::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_nType);
	switch(m_nType)
	{
	case QUEST_BONUS_TYPE_MONEY:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY1:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY2:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY3:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY4:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY5:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY6:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY7:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY8:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_MONEY9:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_EXP:		uSize += sizeof(m_uExp); break;
	case QUEST_BONUS_TYPE_ITEM:		uSize += m_ItemBonus.GetBufSize(); break;
	case QUEST_BONUS_TYPE_ITEM_RAND:	break;
	case QUEST_BONUS_TYPE_ITEM_RADIO:	uSize += m_ItemBonus.GetBufSize(); break;
	case QUEST_BONUS_TYPE_GUILD_EXP:	uSize += sizeof(m_uExp); break;
	case QUEST_BONUS_TYPE_VIGOR:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_CHARM:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_GENIUS:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_COUNTRY_FOOD:	uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_COUNTRY_MONEY:	uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_COUNTRY_WOOD:	uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_COUNTRY_METAL:	uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_WEIWANG:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_INHERENCE_EXP:		uSize += sizeof(m_uMoney); break;
	case QUEST_BONUS_TYPE_GUILD_MONEY:		uSize += sizeof(m_uMoney); break;
	default:				break;
	}

	return uSize;

	__UNGUARD__ return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScriptParam_QuestInfo::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	uchar			i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_idNPC);
	uSize += sizeof(m_idScript);
	uSize += sizeof(m_idQuest);
	uSize += sizeof(m_yTextCount);
	uSize += sizeof(m_yFlags);
	for(i = 0; i < m_yTextCount; i++)
	{
		uSize += m_aText[i].GetBufSize();
	}

	uSize += sizeof(m_yBonusCount);
	for(i = 0; i < m_yBonusCount; i++)
	{
		uSize += m_aBonus[i].GetBufSize();
	}

	return uSize;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ScriptParam_QuestInfo::SetFlag(int32 nIndex)
{
	__GUARD__ if(nIndex < 0 || nIndex > 7) return;
	switch(nIndex)
	{
	case 0:		m_yFlags |= 0x00000001; break;
	case 1:		m_yFlags |= 0x00000010; break;
	case 2:		m_yFlags |= 0x00000100; break;
	case 3:		m_yFlags |= 0x00001000; break;
	case 4:		m_yFlags |= 0x00010000; break;
	case 5:		m_yFlags |= 0x00100000; break;
	case 6:		m_yFlags |= 0x01000000; break;
	case 7:		m_yFlags |= 0x10000000; break;
	default:	break;
	}

	__UNGUARD__
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScriptParam_QuestDemandInfo::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	uchar			i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_idNPC);
	uSize += sizeof(m_idScript);
	uSize += sizeof(m_idQuest);
	uSize += sizeof(m_bDone);

	uSize += sizeof(m_yTextCount);
	for(i = 0; i < m_yTextCount; i++)
	{
		uSize += m_aText[i].GetBufSize();
	}

	uSize += sizeof(m_yDemandCount);
	for(i = 0; i < m_yDemandCount; i++)
	{
		uSize += m_aDemandItem[i].GetBufSize();
	}

	uSize += sizeof(m_yBonusCount);
	for(i = 0; i < m_yBonusCount; i++)
	{
		uSize += m_aBonus[i].GetBufSize();
	}

	return uSize;

	__UNGUARD__ return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScriptParam_QuestContinueInfo::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	uchar			i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_idNPC);
	uSize += sizeof(m_idScript);
	uSize += sizeof(m_idQuest);
	uSize += sizeof(m_yTextCount);
	for(i = 0; i < m_yTextCount; i++)
	{
		uSize += m_aText[i].GetBufSize();
	}

	uSize += sizeof(m_yBonusCount);
	for(i = 0; i < m_yBonusCount; i++)
	{
		uSize += m_aBonus[i].GetBufSize();
	}

	return uSize;

	__UNGUARD__ return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScriptParam_QuestTips::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = m_strText.GetBufSize();
	return uSize;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestTips::Read(RecieveStream &iStream)
{
	__GUARD__ m_strText.Read(iStream);
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestTips::Write(SendStream &oStream) const
{
	__GUARD__ m_strText.Write(oStream);
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 STradeUnit::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_uDataID) + sizeof(m_typeItem) + sizeof(m_yCount);
	return uSize;

	__UNGUARD__ return 0;
}



/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 SScriptParamTrade::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_yItemCount);

	/*~~~~~~*/
	uchar	i;
	/*~~~~~~*/

	for(i = 0; i < m_yItemCount; i++)
	{
		m_aTradeItem[i].GetBufSize();
	}

	uSize += sizeof(m_bRepair);
	return uSize;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScriptParam_QuestUpdate::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	uSize;
	uchar			i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uSize = sizeof(m_QuestId);
	uSize += sizeof(m_flag);

	if(m_flag.IsSetBit(0)) uSize += m_strQuestTitle.GetBufSize();
	if(m_flag.IsSetBit(1)) uSize += m_strQuestName.GetBufSize();
	if(m_flag.IsSetBit(2)) uSize += m_strQuestTarget.GetBufSize();
	if(m_flag.IsSetBit(3)) uSize += m_strQuestSubmitNPC.GetBufSize();
	if(m_flag.IsSetBit(4)) uSize += m_strQuestManual.GetBufSize();
	if(m_flag.IsSetBit(5)) uSize += m_strQuestInfo.GetBufSize();
	if(m_flag.IsSetBit(6)) uSize += m_strQuestHelp.GetBufSize();
	if(m_flag.IsSetBit(7))
	{
		uSize += sizeof(m_yBonusCount);
		for(i = 0; i < m_yBonusCount; i++)
		{
			uSize += m_aBonus[i].GetBufSize();
		}
	}

	return uSize;

	__UNGUARD__ return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
uint32 ScriptParam_QuestDengmi::GetBufSize(void) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	nSize = sizeof(int32) + sizeof(int32);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	return nSize;
}


