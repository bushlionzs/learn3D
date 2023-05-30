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

BOOL FlagTool::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (m_uFlags), sizeof(m_uFlags));

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL FlagTool::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (m_uFlags), sizeof(m_uFlags));

	return TRUE;

	__UNGUARD__ return FALSE;
}

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
BOOL SScriptString::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_Size), sizeof(int16));
	if(m_Size > 0)
	{
		iStream.Reci(m_szString, m_Size * sizeof(char));
		m_szString[m_Size] = 0;
	}
	else
	{
		m_Size = 0;
		m_szString[0] = 0;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SScriptString::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_Size), sizeof(int16));
	if(m_Size > 0)
	{
		oStream.Send(m_szString, m_Size * sizeof(char));
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL SScriptEventItem::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_nType), sizeof(m_nType));
	switch(m_nType)
	{
	case EVENT_ITEM_TYPE_TEXT:
	case EVENT_ITEM_TYPE_SECTION:
		m_strString.Read(iStream);
		break;

	case EVENT_ITEM_TYPE_SCRIPT_ID:
		iStream.Reci((char *) (&m_index), sizeof(m_index));
		iStream.Reci((char *) (&m_state), sizeof(m_state));
		iStream.Reci((char *) (&m_idScript), sizeof(m_idScript));
		m_strString.Read(iStream);
		break;

	default:
		break;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SScriptEventItem::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_nType), sizeof(m_nType));
	switch(m_nType)
	{
	case EVENT_ITEM_TYPE_TEXT:
	case EVENT_ITEM_TYPE_SECTION:
		m_strString.Write(oStream);
		break;

	case EVENT_ITEM_TYPE_SCRIPT_ID:
		oStream.Send((char *) (&m_index), sizeof(m_index));
		oStream.Send((char *) (&m_state), sizeof(m_state));
		oStream.Send((char *) (&m_idScript), sizeof(m_idScript));
		m_strString.Write(oStream);
		break;

	default:
		break;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL SScriptParamEventList::Read(RecieveStream &iStream)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	iStream.Reci((char *) (&m_idNPC), sizeof(m_idNPC));
	iStream.Reci((char *) (&m_yItemCount), sizeof(m_yItemCount));
	for(i = 0; i < m_yItemCount; i++)
	{
		m_seiItem[i].Read(iStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SScriptParamEventList::Write(SendStream &oStream) const
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	oStream.Send((char *) (&m_idNPC), sizeof(m_idNPC));
	oStream.Send((char *) (&m_yItemCount), sizeof(m_yItemCount));
	for(i = 0; i < m_yItemCount; i++)
	{
		m_seiItem[i].Write(oStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL SQuestBonusItem::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_yCount), sizeof(m_yCount));
	iStream.Reci((char *) (&m_uItemID), sizeof(m_uItemID));

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SQuestBonusItem::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_yCount), sizeof(m_yCount));
	oStream.Send((char *) (&m_uItemID), sizeof(m_uItemID));

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL SQuestDemandKill::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_yCount), sizeof(m_yCount));
	iStream.Reci((char *) (&m_uNPCID), sizeof(m_uNPCID));

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SQuestDemandKill::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_yCount), sizeof(m_yCount));
	oStream.Send((char *) (&m_uNPCID), sizeof(m_uNPCID));

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL SQuestBonus::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_nType), sizeof(m_nType));
	switch(m_nType)
	{
	case QUEST_BONUS_TYPE_MONEY:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY1:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY2:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY3:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY4:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY5:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY6:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY7:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY8:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY9:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_EXP:		iStream.Reci((char *) (&m_uExp), sizeof(m_uExp)); break;
	case QUEST_BONUS_TYPE_ITEM:		m_ItemBonus.Read(iStream); break;
	case QUEST_BONUS_TYPE_ITEM_RAND:	break;
	case QUEST_BONUS_TYPE_ITEM_RADIO:	m_ItemBonus.Read(iStream); break;
	case QUEST_BONUS_TYPE_VIGOR:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_CHARM:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_GENIUS:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_GUILD_EXP:	iStream.Reci((char *) (&m_uExp), sizeof(m_uExp)); break;
	case QUEST_BONUS_TYPE_COUNTRY_FOOD:	iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_COUNTRY_MONEY:	iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_COUNTRY_WOOD:	iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_COUNTRY_METAL:	iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_WEIWANG:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_INHERENCE_EXP:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_GUILD_MONEY:		iStream.Reci((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	default:				break;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SQuestBonus::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_nType), sizeof(m_nType));
	switch(m_nType)
	{
	case QUEST_BONUS_TYPE_MONEY:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY1:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY2:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY3:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY4:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY5:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY6:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY7:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY8:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_MONEY9:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_EXP:		oStream.Send((char *) (&m_uExp), sizeof(m_uExp)); break;
	case QUEST_BONUS_TYPE_ITEM:		m_ItemBonus.Write(oStream); break;
	case QUEST_BONUS_TYPE_ITEM_RAND:	break;
	case QUEST_BONUS_TYPE_ITEM_RADIO:	m_ItemBonus.Write(oStream); break;
	case QUEST_BONUS_TYPE_VIGOR:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_CHARM:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_GENIUS:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_GUILD_EXP:	oStream.Send((char *) (&m_uExp), sizeof(m_uExp)); break;
	case QUEST_BONUS_TYPE_COUNTRY_FOOD:	oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_COUNTRY_MONEY:	oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_COUNTRY_WOOD:	oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_COUNTRY_METAL:	oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_WEIWANG:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_INHERENCE_EXP:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	case QUEST_BONUS_TYPE_GUILD_MONEY:		oStream.Send((char *) (&m_uMoney), sizeof(m_uMoney)); break;
	default:				break;
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL ScriptParam_QuestInfo::Read(RecieveStream &iStream)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	iStream.Reci((char *) (&m_idNPC), sizeof(m_idNPC));
	iStream.Reci((char *) (&m_idScript), sizeof(m_idScript));
	iStream.Reci((char *) (&m_idQuest), sizeof(m_idQuest));
	iStream.Reci((char *) (&m_yTextCount), sizeof(m_yTextCount));
	iStream.Reci((char *) (&m_yFlags), sizeof(m_yFlags));
	for(i = 0; i < m_yTextCount; i++)
	{
		m_aText[i].Read(iStream);
	}

	iStream.Reci((char *) (&m_yBonusCount), sizeof(m_yBonusCount));
	for(i = 0; i < m_yBonusCount; i++)
	{
		m_aBonus[i].Read(iStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestInfo::Write(SendStream &oStream) const
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	oStream.Send((char *) (&m_idNPC), sizeof(m_idNPC));
	oStream.Send((char *) (&m_idScript), sizeof(m_idScript));
	oStream.Send((char *) (&m_idQuest), sizeof(m_idQuest));
	oStream.Send((char *) (&m_yTextCount), sizeof(m_yTextCount));
	oStream.Send((char *) (&m_yFlags), sizeof(m_yFlags));
	for(i = 0; i < m_yTextCount; i++)
	{
		m_aText[i].Write(oStream);
	}

	oStream.Send((char *) (&m_yBonusCount), sizeof(m_yBonusCount));
	for(i = 0; i < m_yBonusCount; i++)
	{
		m_aBonus[i].Write(oStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL ScriptParam_QuestDemandInfo::Read(RecieveStream &iStream)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	iStream.Reci((char *) (&m_idNPC), sizeof(m_idNPC));
	iStream.Reci((char *) (&m_idScript), sizeof(m_idScript));
	iStream.Reci((char *) (&m_idQuest), sizeof(m_idQuest));
	iStream.Reci((char *) (&m_bDone), sizeof(m_bDone));
	iStream.Reci((char *) (&m_yTextCount), sizeof(m_yTextCount));
	for(i = 0; i < m_yTextCount; i++)
	{
		m_aText[i].Read(iStream);
	}

	iStream.Reci((char *) (&m_yDemandCount), sizeof(m_yDemandCount));
	for(i = 0; i < m_yDemandCount; i++)
	{
		m_aDemandItem[i].Read(iStream);
	}

	iStream.Reci((char *) (&m_yBonusCount), sizeof(m_yBonusCount));
	for(i = 0; i < m_yBonusCount; i++)
	{
		m_aBonus[i].Read(iStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestDemandInfo::Write(SendStream &oStream) const
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	oStream.Send((char *) (&m_idNPC), sizeof(m_idNPC));
	oStream.Send((char *) (&m_idScript), sizeof(m_idScript));
	oStream.Send((char *) (&m_idQuest), sizeof(m_idQuest));
	oStream.Send((char *) (&m_bDone), sizeof(m_bDone));
	oStream.Send((char *) (&m_yTextCount), sizeof(m_yTextCount));
	for(i = 0; i < m_yTextCount; i++)
	{
		m_aText[i].Write(oStream);
	}

	oStream.Send((char *) (&m_yDemandCount), sizeof(m_yDemandCount));
	for(i = 0; i < m_yDemandCount; i++)
	{
		m_aDemandItem[i].Write(oStream);
	}

	oStream.Send((char *) (&m_yBonusCount), sizeof(m_yBonusCount));
	for(i = 0; i < m_yBonusCount; i++)
	{
		m_aBonus[i].Write(oStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL ScriptParam_QuestContinueInfo::Read(RecieveStream &iStream)
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	iStream.Reci((char *) (&m_idNPC), sizeof(m_idNPC));
	iStream.Reci((char *) (&m_idScript), sizeof(m_idScript));
	iStream.Reci((char *) (&m_idQuest), sizeof(m_idQuest));
	iStream.Reci((char *) (&m_yTextCount), sizeof(m_yTextCount));
	for(i = 0; i < m_yTextCount; i++)
	{
		m_aText[i].Read(iStream);
	}

	iStream.Reci((char *) (&m_yBonusCount), sizeof(m_yBonusCount));
	for(i = 0; i < m_yBonusCount; i++)
	{
		m_aBonus[i].Read(iStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestContinueInfo::Write(SendStream &oStream) const
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ uchar i;
	/*~~~~~~~~~~~~~~*/

	oStream.Send((char *) (&m_idNPC), sizeof(m_idNPC));
	oStream.Send((char *) (&m_idScript), sizeof(m_idScript));
	oStream.Send((char *) (&m_idQuest), sizeof(m_idQuest));
	oStream.Send((char *) (&m_yTextCount), sizeof(m_yTextCount));
	for(i = 0; i < m_yTextCount; i++)
	{
		m_aText[i].Write(oStream);
	}

	oStream.Send((char *) (&m_yBonusCount), sizeof(m_yBonusCount));
	for(i = 0; i < m_yBonusCount; i++)
	{
		m_aBonus[i].Write(oStream);
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL STradeUnit::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_uDataID), sizeof(m_uDataID));
	iStream.Reci((char *) (&m_typeItem), sizeof(m_typeItem));
	iStream.Reci((char *) (&m_yCount), sizeof(m_yCount));
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL STradeUnit::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_uDataID), sizeof(m_uDataID));
	oStream.Send((char *) (&m_typeItem), sizeof(m_typeItem));
	oStream.Send((char *) (&m_yCount), sizeof(m_yCount));
	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL SScriptParamTrade::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_yItemCount), sizeof(m_yItemCount));

	/*~~~~~~*/
	uchar	i;
	/*~~~~~~*/

	for(i = 0; i < m_yItemCount; i++)
	{
		m_aTradeItem[i].Read(iStream);
	}

	iStream.Reci((char *) (&m_bRepair), sizeof(m_bRepair));
	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SScriptParamTrade::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_yItemCount), sizeof(m_yItemCount));

	/*~~~~~~*/
	uchar	i;
	/*~~~~~~*/

	for(i = 0; i < m_yItemCount; i++)
	{
		m_aTradeItem[i].Write(oStream);
	}

	oStream.Send((char *) (&m_bRepair), sizeof(m_bRepair));
	return TRUE;

	__UNGUARD__ return FALSE;
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
BOOL ScriptParam_QuestUpdate::Read(RecieveStream &iStream)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Reset();
	/*~~~~~~~~~~~~~~~~~~~~*/

	iStream.Reci((char *) (&m_QuestId), sizeof(m_QuestId));

	m_flag.Read(iStream);
	if(m_flag.IsSetBit(0)) m_strQuestTitle.Read(iStream);
	if(m_flag.IsSetBit(1)) m_strQuestName.Read(iStream);
	if(m_flag.IsSetBit(2)) m_strQuestTarget.Read(iStream);
	if(m_flag.IsSetBit(3)) m_strQuestSubmitNPC.Read(iStream);
	if(m_flag.IsSetBit(4)) m_strQuestManual.Read(iStream);
	if(m_flag.IsSetBit(5)) m_strQuestInfo.Read(iStream);
	if(m_flag.IsSetBit(6)) m_strQuestHelp.Read(iStream);
	if(m_flag.IsSetBit(7))
	{
		iStream.Reci((char *) (&m_yBonusCount), sizeof(m_yBonusCount));

		/*~~~~~~*/
		uchar	i;
		/*~~~~~~*/

		for(i = 0; i < m_yBonusCount; ++i)
		{
			m_aBonus[i].Read(iStream);
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestUpdate::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_QuestId), sizeof(m_QuestId));

	m_flag.Write(oStream);
	if(m_flag.IsSetBit(0)) m_strQuestTitle.Write(oStream);
	if(m_flag.IsSetBit(1)) m_strQuestName.Write(oStream);
	if(m_flag.IsSetBit(2)) m_strQuestTarget.Write(oStream);
	if(m_flag.IsSetBit(3)) m_strQuestSubmitNPC.Write(oStream);
	if(m_flag.IsSetBit(4)) m_strQuestManual.Write(oStream);
	if(m_flag.IsSetBit(5)) m_strQuestInfo.Write(oStream);
	if(m_flag.IsSetBit(6)) m_strQuestHelp.Write(oStream);
	if(m_flag.IsSetBit(7))
	{
		oStream.Send((char *) (&m_yBonusCount), sizeof(m_yBonusCount));

		/*~~~~~~*/
		uchar	i;
		/*~~~~~~*/

		for(i = 0; i < m_yBonusCount; ++i)
		{
			m_aBonus[i].Write(oStream);
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
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

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestDengmi::Read(RecieveStream &iStream)
{
	__GUARD__ iStream.Reci((char *) (&m_nQuestionIndex), sizeof(m_nQuestionIndex));
	iStream.Reci((char *) (&m_nAnswerTimer), sizeof(m_nAnswerTimer));
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ScriptParam_QuestDengmi::Write(SendStream &oStream) const
{
	__GUARD__ oStream.Send((char *) (&m_nQuestionIndex), sizeof(m_nQuestionIndex));
	oStream.Send((char *) (&m_nAnswerTimer), sizeof(m_nAnswerTimer));
	return TRUE;
	__UNGUARD__ return FALSE;
}
