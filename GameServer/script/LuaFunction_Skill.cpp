/*$T MapServer/Server/Script/LuaFunction_Skill.cpp GC 1.140 10/10/07 10:07:51 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "LuaFunction.h"
#include "LuaMacro.h"
#include "gameobject/Player.h"
#include "Archive/PlayerDB.h"
#include "map/game_map.h"
#include "map/map_manager.h"
#include "gameobject/HumanSkillUpgrad.h"
#include "net/messages/SCScriptCommand.h"
#include "net/messages/SCDetailBuff.h"
#include "net/messages/SCRetSkillSetting.h"
#include "net/messages/SCAddSkillToSkillList.h"
#include "net_message_manager.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_AddSkillToPlayer(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[5].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	SkillID_t	iSkillID = Lua_ValueToNumber(L, 3);
	int32		iSkillLevel = Lua_ValueToNumber(L, 4);
	int32		iSkillBarIndex = Lua_ValueToNumber(L, 5);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	_PLAYER_SETTING	oOwnSetting;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	oOwnSetting.m_SettingType = AOT_SKILL;
	oOwnSetting.m_SettingData = iSkillID;

	if(SETTING_TYPE_K0 > iSkillBarIndex || SETTING_TYPE_EK23 < iSkillBarIndex)
	{
		LUA_RETURNERROR_1;
	}

	pPlayer->SetSettingData(iSkillBarIndex, &oOwnSetting);

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	_PLAYER_SPELL	oOwnSkill;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	oOwnSkill.m_eState = _PLAYER_SPELL::OWN_SKILL_CAN_USE;
	oOwnSkill.m_nLevel = iSkillLevel;
	oOwnSkill.m_nSkillID = iSkillID;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const _PLAYER_SPELL	*pOwnSkill = pPlayer->GetSpell(iSkillID);
	int32			iIndex = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL != pOwnSkill)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		_SPELL_LIST const	&rList = pPlayer->GetSpellList();
		uchar const		&rCount = rList.m_Count;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(MAX_CHAR_SKILL_NUM < rCount)
		{
			KCheck(!"LuaFunction_AddSkillToPlayer");
			LUA_RETURNERROR_1;
		}

		for(int32 i = 0; rCount > i; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_PLAYER_SPELL const	&rSkill = rList.m_aSkill[i];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(iSkillID == rSkill.m_nSkillID)
			{
				iIndex = i;
				break;
			}
		}
	}
	else
	{
		iIndex = pPlayer->GetDB()->GetSkillCount();
		if(MAX_CHAR_SKILL_NUM > iIndex)
		{
			++iIndex;
			pPlayer->GetDB()->SetSkillCount(iIndex);
		}

		--iIndex;
	}

	pPlayer->GetDB()->SetSkillID(oOwnSkill, iIndex);

	SCRetSkillSetting* packet = new SCRetSkillSetting;

	packet->setPlayerSetting(oOwnSetting);
	packet->setIndex(iSkillBarIndex);
	NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);


	SCAddSkillToSkillList* packet2 = new SCAddSkillToSkillList;
	packet2->setObjectId(selfId);
	packet2->setSpell(oOwnSkill);
	NetMessageManager::GetSingletonPtr()->sendNetMessage(packet2);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_HumanSkillLevelUp(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	SpellID_t	SkillId = Lua_ValueToNumber(L, 3);
	int32		iLevel = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	PlayerSkillUpgrade	oSkillUpgrade;
	BOOL			bOk = oSkillUpgrade.HumanSkillLevelUpNoCheck(pPlayer, SkillId, iLevel);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, bOk);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetHumanSkillLevel(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t		mapId = Lua_ValueToNumber(L, 1);
	ObjID_t		selfId = Lua_ValueToNumber(L, 2);
	SpellID_t	SkillId = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	PlayerSkillUpgrade	oSkillUpgrade;
	int32			iLevel = oSkillUpgrade.GetHumanSkillLevel(pPlayer, SkillId);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, iLevel);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_OpenSkillStudyUI(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	assert(false);
	/*~~~~~~~~~~~~~~~~*/
	SCScriptCommand* packet = new SCScriptCommand;
	/*~~~~~~~~~~~~~~~~*/

	packet->setCmdId(SCRIPT_COMMAND_SKILL_STUDY);

	NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);

	Lua_PushNumber(L, TRUE);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_SetImmuneAbsForLater(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	immuneAbs = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}
	pPlayer->SetImmuneAbsForLater(immuneAbs > 0 ? TRUE : FALSE);
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_DispelSpecificImpact(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	dataIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// 2010-9-13 by rj 增加强制删除接口
	BOOL bForceDispel = FALSE;

	if(Lua_GetTopIndex(L) < 4)
	{
		bForceDispel = FALSE;
	}
	else
	{
		if (!args[4].IsString())
		{
			LUA_ASSERT(false);
			LUA_RETURNERROR_1;
		}

		bForceDispel = Lua_ValueToNumber(L, 4) > 0 ? TRUE : 0;
	}

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}
	//pPlayer->Effect_DispelSpecificEffectByDataIndex(dataIndex, 1, bForceDispel);
	assert(false);
	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetImpactListCount(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Lua_PushNumber(L, rCount);
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetImpactDataIndex(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	index = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(index >= 0 && index < rCount)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[index];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Lua_PushNumber(L, rImp.GetDataIndex());
		return 1;
	}

	LUA_RETURNERROR_1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_SetImpactContinuanceByDataIndex(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[4].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	dataIndex = Lua_ValueToNumber(L, 3);
	int32	value = Lua_ValueToNumber(L, 4);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uchar i = 0; i < rCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(rImp.GetDataIndex() == dataIndex)
		{
			rImp.SetContinuance(value);
			return 0;
		}
	}

	LUA_RETURNERROR_1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetImpactContinuanceByDataIndex(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	dataIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uchar i = 0; i < rCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(rImp.GetDataIndex() == dataIndex)
		{
			Lua_PushNumber(L, rImp.GetContinuance());
			return 1;
		}
	}

	LUA_RETURNERROR_1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetImpactContinuanceElapsed(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	dataIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uchar i = 0; i < rCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(rImp.GetDataIndex() == dataIndex)
		{
			Lua_PushNumber(L, rImp.GetContinuanceElapsed());
			return 1;
		}
	}

	LUA_RETURNERROR_1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_ResetImpactContinuanceElapsed(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	dataIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uchar i = 0; i < rCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(rImp.GetDataIndex() == dataIndex)
		{
			rImp.SetContinuanceElapsed(0);
			break;
		}
	}

	return 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_GetItemDurOnDieRefix(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	Lua_PushNumber(L, pPlayer->GetIntAttrRefix_EX(CharIntAttrRefixs::REFIX_ITEM_DUR_ON_DIE));
	return 1;
}

/*
 =======================================================================================================================
 取得玩家最大HP值
 =======================================================================================================================
 */
int32_t LuaFunction_GetPlayerMaxHP(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}
	Lua_PushNumber(L, pPlayer->GetMaxHP());
	return 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32_t LuaFunction_RefreshImpactByDataIndex(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32	dataIndex = Lua_ValueToNumber(L, 3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = pPlayer->Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uchar i = 0; i < rCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(rImp.GetDataIndex() == dataIndex)
		{
			SCDetailBuff* packet = new SCDetailBuff;

			packet->setReceiverId(selfId);
			packet->setSenderId(rImp.GetCasterObjID());
			packet->setEnable(TRUE);
			packet->setSkillId(rImp.GetSkillID());
			packet->setSN(rImp.GetSN());
			packet->setBuffId(dataIndex);
			packet->setContinuance(rImp.GetContinuance());
			packet->setDelayTime(0);
			packet->setSenderLogicCount(rImp.GetCasterLogicCount());

			NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);
			

			return 0;
		}
	}

	LUA_RETURNERROR_1;
}

/*
=======================================================================================================================
添加专攻经验
=======================================================================================================================
*/
int32_t LuaFunction_AddInherenceZhuanGongExp(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}
	int32 aAddExp[PROFESSION_NUMBER];
	memset(aAddExp, 0, sizeof(aAddExp));

	assert(false);
	
	char msg[1024] = { 0 };
	const char* txt[PROFESSION_NUMBER] = {
	"获得武士专攻点数#G",
	"获得剑侠专攻点数#G",
	"获得骑射专攻点数#G",
	"获得火枪专攻点数#G",
	"获得先知专攻点数#G",
	"获得萨满专攻点数#G",
	"获得十字军专攻点数#G",
	"获得圣火使专攻点数#G",
	"获得刺客专攻点数#G",
	"获得近卫军专攻点数#G",
	"获得隐修士专攻点数#G",
	"获得僧侣专攻点数#G"
	};
    for (int32 i = 0; i < PROFESSION_NUMBER; i++)
	{
		if (aAddExp[i] > 0)
		{
			switch (i)
			{
			case PROFESSION_WUSHI:
				 strncat(msg, txt[PROFESSION_WUSHI], strlen(txt[PROFESSION_WUSHI]) ) ;
				break;
			case PROFESSION_JIANXIA:
				strncat(msg, txt[PROFESSION_JIANXIA], strlen(txt[PROFESSION_JIANXIA]) ) ;
				break;
			case PROFESSION_QISHE:
				strncat(msg, txt[PROFESSION_QISHE], strlen(txt[PROFESSION_QISHE]) ) ;
				break;
			case PROFESSION_HUOQIANG:
				strncat(msg, txt[PROFESSION_HUOQIANG], strlen(txt[PROFESSION_HUOQIANG]) ) ;
				break;
			case PROFESSION_XIANZHI:
				strncat(msg, txt[PROFESSION_XIANZHI], strlen(txt[PROFESSION_XIANZHI]) ) ;
				break;
			case PROFESSION_SAMAN:
				strncat(msg, txt[PROFESSION_SAMAN], strlen(txt[PROFESSION_SAMAN]) ) ;
				break;
			case PROFESSION_SHIZIJUN:
				strncat(msg, txt[PROFESSION_SHIZIJUN], strlen(txt[PROFESSION_SHIZIJUN]) ) ;
				break;
			case PROFESSION_SHENGHUOSHI:
				strncat(msg, txt[PROFESSION_SHENGHUOSHI], strlen(txt[PROFESSION_SHENGHUOSHI]) ) ;
				break;
			case PROFESSION_CIKE:
				strncat(msg, txt[PROFESSION_CIKE], strlen(txt[PROFESSION_CIKE]) ) ;
				break;
			case PROFESSION_JINWEIJUN:
				strncat(msg, txt[PROFESSION_JINWEIJUN], strlen(txt[PROFESSION_JINWEIJUN]) ) ;
				break;
			case PROFESSION_YINXIUSHI:
				strncat(msg, txt[PROFESSION_YINXIUSHI], strlen(txt[PROFESSION_YINXIUSHI]) ) ;
				break;
			case PROFESSION_LAMA:
				strncat(msg, txt[PROFESSION_LAMA], strlen(txt[PROFESSION_LAMA]) ) ;
				break;
			default:
				break;
			}

			char buff[255] = { 0 };
			sprintf(buff,"%d", aAddExp[i]);
			strncat(msg, buff, strlen(buff) ) ;
			const char *tmp = "#o点\n";
			strncat(msg, tmp, strlen(tmp) ) ;
		}
	}

	Lua_PushLString(L, msg, strlen(msg));
	return 1;
}

/*
=======================================================================================================================
添加专防经验
=======================================================================================================================
*/
int32_t LuaFunction_SetInherenceZhuanFangExp(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[3].IsString())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);
	int32 point = Lua_ValueToNumber(L, 3);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}

	assert(false);
	Lua_PushNumber(L, 1);
	return 1;
}

/*
=======================================================================================================================
专防洗点
=======================================================================================================================
*/
int32_t LuaFunction_ReallocateInherenceZhuanFangPoint(Lua_State *L)
{
	LuaStack args(L);

	if (!args[1].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	if (!args[2].IsNumber())
	{
		LUA_ASSERT(false);
		LUA_RETURNERROR_1;
	}

	MapID_t mapId = Lua_ValueToNumber(L, 1);
	ObjID_t selfId = Lua_ValueToNumber(L, 2);

	GameMap* pMap = MapManager::GetSingletonPtr()->getMap(mapId);
	Player* pPlayer = pMap->getPlayer(selfId);
	if (pPlayer == nullptr)
	{
		LUA_RETURNERROR_1;
	}
	assert(false);
	Lua_PushNumber(L, FALSE);
	return 1;
}

