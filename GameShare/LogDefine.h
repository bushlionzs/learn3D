/*$T MapServer/Server/Base/LogDefine.h GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __RECORD_GAMEWAY_H_
#define __RECORD_GAMEWAY_H_

#include "TypeDefine.h"
#include "StructDB.h"
#include "record_format.h"
#include "record_struct.h"
#include "BaseTool.h"
#include "Setting.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

template<typename PARAM>
inline void WRITE_GAMESYSTEM_LOG(const PARAM &Param)
{
}

template<typename PARAM>
inline void WRITE_GAMESYSTEM_LOG(const PARAM &Param0, const PARAM &Param1, MapID_t, int32)
{
}

template<typename PARAM>
inline void WRITE_GAMESYSTEM_LOG(int opType,const PARAM &Param0, const PARAM &Param1, MapID_t, int32)
{
}


/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const ItemLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_ITEMCHANGE,
			csRECORD_FORMAT_Item,
			GET_TIME().GetCTime(),
			Param.CharGUID,
			Param.Name,
			Param.IP,
			Param.MapID,
			Param.OpType,
			Param.OpDesc,
			Param.ItemType,
			Param.ItemGuid.m_World,
			Param.ItemGuid.m_Server,
			Param.ItemGuid.m_Serial,
			Param.Count,
			Param.TargetGUID,
			Param.SecOpType,
			Param.ContainerPos,
			Param.DestContainerPos,
			Param.NpcType,
			Param.XPos,
			Param.ZPos,
			Param.ShopGUID,
			Param.GemMax,
			Param.ScriptID,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const EquipLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_EQUIP,
			csRECORD_FORMAT_Equip,
			GET_TIME().GetCTime(),
			Param.CharGUID,
			Param.Name,
			Param.IP,
			Param.ItemType,
			Param.ItemGuid.m_World,
			Param.ItemGuid.m_Server,
			Param.ItemGuid.m_Serial,
			Param.OpType,
			Param.Level,
			Param.MaJiang,
			Param.AttContent[0].m_AttrType,
			Param.AttContent[0].m_Value.m_Value,
			Param.AttContent[1].m_AttrType,
			Param.AttContent[1].m_Value.m_Value,
			Param.AttContent[2].m_AttrType,
			Param.AttContent[2].m_Value.m_Value,
			Param.AttContent[3].m_AttrType,
			Param.AttContent[3].m_Value.m_Value,
			Param.AttContent[4].m_AttrType,
			Param.AttContent[4].m_Value.m_Value,
			Param.AttContent[5].m_AttrType,
			Param.AttContent[5].m_Value.m_Value,
			Param.AttContent[6].m_AttrType,
			Param.AttContent[6].m_Value.m_Value,
			Param.AttContent[7].m_AttrType,
			Param.AttContent[7].m_Value.m_Value,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);	

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const CurrencyLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_MONEYCHANGE,
			csRECORD_FORMAT_Money,
			GET_TIME().GetCTime(),
			Param.CharGUID,
			Param.Name,
			Param.MapID,
			Param.OPType,
			Param.MoneyType,
			Param.Count,
			Param.RemainCount,
			Param.XPos,
			Param.ZPos,
			Param.TargetGUID,
			Param.ItemIndex,
			Param.ItemCount,
			Param.PetGUID.m_uHighSection,
			Param.PetGUID.m_uLowSection,
			Param.ScriptId,
			Param.nExt,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);	

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const PetLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_PET,
			csRECORD_FORMAT_Pet,
			Param.CharGUID,
			Param.TargetGUID,
			Param.OPType,
			Param.MapID,
			Param.XPos,
			Param.ZPos,
			Param.PetGUID.m_uHighSection,
			Param.PetGUID.m_uLowSection,
			Param.DataID,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);	

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const SkillLogRecordInfo &Param)
{
	__GUARD__;
#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG_DB
		(
			SLOW_LOG_SKILL,
			csRECORD_FORMAT_Skill,
			Param.CharGUID,
			Param.OPType,
			Param.MapID,
			Param.XPos,
			Param.ZPos,
			Param.SkillID,
			Param.Level,
			Param.Count,
			Param.MapID,
			Param.WorldID
		);
#else
	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_SKILL,
			csRECORD_FORMAT_Skill,
			Param.CharGUID,
			Param.OPType,
			Param.MapID,
			Param.XPos,
			Param.ZPos,
			Param.SkillID,
			Param.Level,
			Param.Count,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);
#endif
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const AbilityLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_ABILITY,
			csRECORD_FORMAT_Ability,
			Param.CharGUID,
			Param.OPType,
			Param.MapID,
			Param.XPos,
			Param.ZPos,
			Param.AbilityID,
			Param.Level,
			Param.Count,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const QuestLogRecordInfo &Param)
{
	__GUARD__;

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const GameWayLogRecoreInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_GAMEWAY,
			csRECORD_FORMAT_GameWay,
			Param.CharGUID,
			Param.Name,
			Param.MapID,
			Param.GameID,
			Param.HaveTeam,
			Param.member_cnt,
			Param.member[0].Level,
			Param.member[0].Job,
			Param.member[1].Level,
			Param.member[1].Job,
			Param.member[2].Level,
			Param.member[2].Job,
			Param.member[3].Level,
			Param.member[3].Job,
			Param.member[4].Level,
			Param.member[4].Job,
			Param.member[5].Level,
			Param.member[5].Job,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);	

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const EnterSceneLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_CSIE,
			csRECORD_FORMAT_IllegalEnter,
			Param.CharGUID,
			Param.Name,
			Param.MapID,
			Param.GameID,
			Param.DayCount,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const GoldCardLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_IB,
			csRECORD_FORMAT_IB,
			GET_TIME().GetCTime(),
			Param.guidChar,
			Param.Name,
			Param.mapId,
			Param.iChangeType,
			Param.iCostTypeId,
			Param.uPayment,
			Param.uItemTypeID,
			Param.iItemCount,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const TradeLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_TRADE,
			csRECORD_FORMAT_Trade,
			Param.m_anTradeParam[0].m_nCharGuid,
			Param.m_anTradeParam[0].m_szCharName,
			Param.m_anTradeParam[0].m_nSceneId,
			Param.m_anTradeParam[0].m_nTradeType,
			Param.m_anTradeParam[0].m_nPreGold,
			Param.m_anTradeParam[0].m_nAftGold,
			Param.m_anTradeParam[0].m_anItem[0].m_nItemId,
			Param.m_anTradeParam[0].m_anItem[0].m_nItemGuid.m_World,
			Param.m_anTradeParam[0].m_anItem[0].m_nItemGuid.m_Server,
			Param.m_anTradeParam[0].m_anItem[0].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[0].m_anItem[0].m_nCount,
			Param.m_anTradeParam[0].m_anItem[1].m_nItemId,
			Param.m_anTradeParam[0].m_anItem[1].m_nItemGuid.m_World,
			Param.m_anTradeParam[0].m_anItem[1].m_nItemGuid.m_Server,
			Param.m_anTradeParam[0].m_anItem[1].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[0].m_anItem[1].m_nCount,
			Param.m_anTradeParam[0].m_anItem[2].m_nItemId,
			Param.m_anTradeParam[0].m_anItem[2].m_nItemGuid.m_World,
			Param.m_anTradeParam[0].m_anItem[2].m_nItemGuid.m_Server,
			Param.m_anTradeParam[0].m_anItem[2].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[0].m_anItem[2].m_nCount,
			Param.m_anTradeParam[0].m_anItem[3].m_nItemId,
			Param.m_anTradeParam[0].m_anItem[3].m_nItemGuid.m_World,
			Param.m_anTradeParam[0].m_anItem[3].m_nItemGuid.m_Server,
			Param.m_anTradeParam[0].m_anItem[3].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[0].m_anItem[3].m_nCount,
			Param.m_anTradeParam[0].m_anItem[4].m_nItemId,
			Param.m_anTradeParam[0].m_anItem[4].m_nItemGuid.m_World,
			Param.m_anTradeParam[0].m_anItem[4].m_nItemGuid.m_Server,
			Param.m_anTradeParam[0].m_anItem[4].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[0].m_anItem[4].m_nCount,
			Param.m_anTradeParam[0].m_nPetId,
			Param.m_anTradeParam[0].m_nPetGuid.m_uHighSection,
			Param.m_anTradeParam[0].m_nPetGuid.m_uLowSection,
			Param.m_anTradeParam[1].m_nCharGuid,
			Param.m_anTradeParam[1].m_szCharName,
			Param.m_anTradeParam[1].m_nSceneId,
			Param.m_anTradeParam[1].m_nTradeType,
			Param.m_anTradeParam[1].m_nPreGold,
			Param.m_anTradeParam[1].m_nAftGold,
			Param.m_anTradeParam[1].m_anItem[0].m_nItemId,
			Param.m_anTradeParam[1].m_anItem[0].m_nItemGuid.m_World,
			Param.m_anTradeParam[1].m_anItem[0].m_nItemGuid.m_Server,
			Param.m_anTradeParam[1].m_anItem[0].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[1].m_anItem[0].m_nCount,
			Param.m_anTradeParam[1].m_anItem[1].m_nItemId,
			Param.m_anTradeParam[1].m_anItem[1].m_nItemGuid.m_World,
			Param.m_anTradeParam[1].m_anItem[1].m_nItemGuid.m_Server,
			Param.m_anTradeParam[1].m_anItem[1].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[1].m_anItem[1].m_nCount,
			Param.m_anTradeParam[1].m_anItem[2].m_nItemId,
			Param.m_anTradeParam[1].m_anItem[2].m_nItemGuid.m_World,
			Param.m_anTradeParam[1].m_anItem[2].m_nItemGuid.m_Server,
			Param.m_anTradeParam[1].m_anItem[2].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[1].m_anItem[2].m_nCount,
			Param.m_anTradeParam[1].m_anItem[3].m_nItemId,
			Param.m_anTradeParam[1].m_anItem[3].m_nItemGuid.m_World,
			Param.m_anTradeParam[1].m_anItem[3].m_nItemGuid.m_Server,
			Param.m_anTradeParam[1].m_anItem[3].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[1].m_anItem[3].m_nCount,
			Param.m_anTradeParam[1].m_anItem[4].m_nItemId,
			Param.m_anTradeParam[1].m_anItem[4].m_nItemGuid.m_World,
			Param.m_anTradeParam[1].m_anItem[4].m_nItemGuid.m_Server,
			Param.m_anTradeParam[1].m_anItem[4].m_nItemGuid.m_Serial,
			Param.m_anTradeParam[1].m_anItem[4].m_nCount,
			Param.m_anTradeParam[1].m_nPetId,
			Param.m_anTradeParam[1].m_nPetGuid.m_uHighSection,
			Param.m_anTradeParam[1].m_nPetGuid.m_uLowSection,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.m_WorldID
		);	

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const GLGoldShopLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::SLOW_LOG_DB
		(
			SLOW_LOG_GL_WORLD_SHOP,
			csRECORD_FORMAT_WorlShop,
			Param.OwnerGUID,
			Param.BuyerGUID,
			Param.OPType,
			Param.ShopId,
			Param.SerialId,
			Param.SellGold,
			Param.GoldNum,
			Param.Price,
			Param.SillerNum,
			Param.Charge,
			Param.CreateTime,
			Param.DeleteTime,
			2,
			g_Config.m_WorldInfo.m_WorldID
		);
	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const WorldShopLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_MAPWORLDSHOP,
			csRECORD_FORMAT_WorlShop,
			Param.OwnerGUID,
			Param.BuyerGUID,
			Param.OPType,
			Param.ShopId,
			Param.SerialId,
			Param.SellGold,
			Param.GoldNum,
			Param.Price,
			Param.SillerNum,
			Param.Charge,
			Param.CreateTime,
			Param.DeleteTime,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);	

	__UNGUARD__;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
template<>
inline void WRITE_GAMESYSTEM_LOG(const CheatActLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
			QUICK_LOG_MAPLAWLESSOP,
			csRECORD_FORMAT_Cheat,
			Param.CharName,
			Param.OwnerGUID,
			Param.OPType,
			Param.MapID,
			Param.Offset,
			Param.PosX,
			Param.PosZ,
			Param.Param,
			g_Config.m_ConfigInfo.m_ServerID,
			Param.WorldID
		);
	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(int nOpType,const ReturnToChildLogRecordInfo &Param0, const ReturnToChildLogRecordInfo &Param1, MapID_t MapID, int32 WorldID)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
		QUICK_LOG_PET_RETURN,
		csRECORD_FORMAT_ReturnToChild,
		nOpType,
		Param0.m_uHighSection,Param0.m_uLowSection,
		Param0.m_nBaseStr,Param0.m_nBaseCon,Param0.m_nBaseDex,Param0.m_nBaseInt,
		Param0.m_nExtStr,Param0.m_nExtCon,Param0.m_nExtDex,Param0.m_nExtInt,
		Param0.m_nSkill[0],Param0.m_nSkill[1],Param0.m_nSkill[2],Param0.m_nSkill[3],Param0.m_nSkill[4],Param0.m_nSkill[5],
		Param0.m_nSkill[6],Param0.m_nSkill[7],Param0.m_nSkill[8],Param0.m_nSkill[9],Param0.m_nSkill[10],Param0.m_nSkill[11],
		Param1.m_uHighSection,Param1.m_uLowSection,
		Param1.m_nBaseStr,Param1.m_nBaseCon,Param1.m_nBaseDex,Param1.m_nBaseInt,
		Param1.m_nExtStr,Param1.m_nExtCon,Param1.m_nExtDex,Param1.m_nExtInt,
		Param1.m_nSkill[0],Param1.m_nSkill[1],Param1.m_nSkill[2],Param1.m_nSkill[3],Param1.m_nSkill[4],Param1.m_nSkill[5],
		Param1.m_nSkill[6],Param1.m_nSkill[7],Param1.m_nSkill[8],Param1.m_nSkill[9],Param1.m_nSkill[10],Param1.m_nSkill[11],
		g_Config.m_ConfigInfo.m_ServerID,
		WorldID
		);
	__UNGUARD__;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const PetSkillLogRecordInfo &Param0, const PetSkillLogRecordInfo &Param1, MapID_t MapID, int32 WorldID)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
		QUICK_LOG_PET_SKILL,
		csRECORD_FORMAT_PetSkillChange,
		Param0.m_uHighSection,Param0.m_uLowSection,
		Param0.m_nBaseStr,Param0.m_nBaseCon,Param0.m_nBaseDex,Param0.m_nBaseInt,
		Param0.m_nExtStr,Param0.m_nExtCon,Param0.m_nExtDex,Param0.m_nExtInt,
		Param0.m_nSkill[0],Param0.m_nSkill[1],Param0.m_nSkill[2],Param0.m_nSkill[3],Param0.m_nSkill[4],Param0.m_nSkill[5],
		Param0.m_nSkill[6],Param0.m_nSkill[7],Param0.m_nSkill[8],Param0.m_nSkill[9],Param0.m_nSkill[10],Param0.m_nSkill[11],
		Param1.m_uHighSection,Param1.m_uLowSection,
		Param1.m_nBaseStr,Param1.m_nBaseCon,Param1.m_nBaseDex,Param1.m_nBaseInt,
		Param1.m_nExtStr,Param1.m_nExtCon,Param1.m_nExtDex,Param1.m_nExtInt,
		Param1.m_nSkill[0],Param1.m_nSkill[1],Param1.m_nSkill[2],Param1.m_nSkill[3],Param1.m_nSkill[4],Param1.m_nSkill[5],
		Param1.m_nSkill[6],Param1.m_nSkill[7],Param1.m_nSkill[8],Param1.m_nSkill[9],Param1.m_nSkill[10],Param1.m_nSkill[11],
		g_Config.m_ConfigInfo.m_ServerID,
		WorldID
		);
	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const IBInItemLogRecordInfo &Param)
{
	__GUARD__;

#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG_DB
		(
		SLOW_LOG_GL_IBMONEY,
		csRECORD_FORMAT_IBMoney,
		Param.CharGUID,
		Param.Name,
		Param.OpType,
		Param.ItemType,
		Param.ItemGuid.m_World,
		Param.ItemGuid.m_Server,
		Param.ItemGuid.m_Serial,
		Param.Count,
		Param.GoldCash,
		Param.TermTime,
		2,
		g_Config.m_WorldInfo.m_WorldID
		);
#else
	QLogSystem::QUICK_LOG_DB
		(
		QUICK_LOG_IBMONEY,
		csRECORD_FORMAT_IBMoney,
		Param.CharGUID,
		Param.Name,
		Param.OpType,
		Param.ItemType,
		Param.ItemGuid.m_World,
		Param.ItemGuid.m_Server,
		Param.ItemGuid.m_Serial,
		Param.Count,
		Param.GoldCash,
		Param.TermTime,
		g_Config.m_ConfigInfo.m_ServerID,
		Param.WorldID
		);	
#endif

	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const IBOutItemLogRecordInfo &Param)
{
	__GUARD__;

#ifdef __GLSERVER__
	QLogSystem::SLOW_LOG_DB
		(
		SLOW_LOG_GL_IBCOST,
		csRECORD_FORMAT_IBCost,
		Param.CharGUID,
		Param.Name,
		Param.OpType,
		Param.ItemType,
		Param.ItemGuid.m_World,
		Param.ItemGuid.m_Server,
		Param.ItemGuid.m_Serial,
		Param.Count,
		Param.GoldCash,
		2,
		g_Config.m_WorldInfo.m_WorldID
		);
#else
	QLogSystem::QUICK_LOG_DB
		(
		QUICK_LOG_IBCOST,
		csRECORD_FORMAT_IBCost,
		Param.CharGUID,
		Param.Name,
		Param.OpType,
		Param.ItemType,
		Param.ItemGuid.m_World,
		Param.ItemGuid.m_Server,
		Param.ItemGuid.m_Serial,
		Param.Count,
		Param.GoldCash,
		g_Config.m_ConfigInfo.m_ServerID,
		Param.WorldID
		);	
#endif

	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const GLStockTradeLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::SLOW_LOG_DB
		(
		SLOW_LOG_GL_STOCK_TRADE,
		csRECORD_FORMAT_StockTrade,
		Param.OwnerGUID,
		Param.OtherGUID,
		Param.OPType,
		Param.TradeType,
		Param.OwnerPrice,
		Param.OtherPrice,
		Param.Gold,
		Param.CreateTime,
		Param.DeleteTime,
		2,
		g_Config.m_WorldInfo.m_WorldID
		);
	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const MapStockAccLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::QUICK_LOG_DB
		(
		QUICK_LOG_MAPSTOCKACC,
		csRECORD_FORMAT_StockAcc,
		Param.OwnerGUID,
		Param.OPType,
		Param.TransGold,
		Param.TransSiller,
		Param.StockGold,
		Param.StockSiller,
		g_Config.m_ConfigInfo.m_ServerID,
		Param.WorldID
		);

	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const GLStockAccLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::SLOW_LOG_DB
		(
		SLOW_LOG_GL_STOCK_ACC,
		csRECORD_FORMAT_StockAcc,
		Param.OwnerGUID,
		Param.OPType,
		Param.TransGold,
		Param.TransSiller,
		Param.StockGold,
		Param.StockSiller,
		2,
		g_Config.m_WorldInfo.m_WorldID
		);
	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const GLGuildLogRecordInfo &Param)
{
	__GUARD__;
	QLogSystem::SLOW_LOG_DB
		(
		SLOW_LOG_GL_GUILD,
		csRECORD_FORMAT_Guild,
		Param.m_GuildId,
		Param.m_szGuildName,
		Param.m_OpType,
		Param.m_nCount,
		Param.m_nRemainCount,
		Param.m_nParam,
		Param.m_nScriptId,
		2,
		g_Config.m_WorldInfo.m_WorldID
		);

	__UNGUARD__;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
template<>
inline void WRITE_GAMESYSTEM_LOG(const ZhuanJingLogRecordInfo &Param)
{
	__GUARD__;

	QLogSystem::QUICK_LOG_DB
		(
		QUICK_LOG_ZHUANJING,
		csRECORD_FORMAT_ZhuanJing,
		Param.CharGUID,
		Param.OPType,
		Param.MapID,
		Param.XPos,
		Param.ZPos,
		Param.TotalPoint,
		Param.Profession[PROFESSION_WUSHI],
		Param.Profession[PROFESSION_JIANXIA],
		Param.Profession[PROFESSION_QISHE],
		Param.Profession[PROFESSION_HUOQIANG],
		Param.Profession[PROFESSION_XIANZHI],
		Param.Profession[PROFESSION_SAMAN],
		Param.Profession[PROFESSION_SHIZIJUN],
		Param.Profession[PROFESSION_SHENGHUOSHI],
		Param.Profession[PROFESSION_CIKE],
		Param.Profession[PROFESSION_JINWEIJUN],
		Param.Profession[PROFESSION_YINXIUSHI],
		Param.Profession[PROFESSION_LAMA],
		Param.Reserve_param0,
		Param.Reserve_param1,
		g_Config.m_ConfigInfo.m_ServerID,
		Param.WorldID
		);	

	__UNGUARD__;
}

#endif
