#pragma once

int32 LuaFunction_GetCurrentTime(Lua_State* L);

//attr
int32_t LuaFunction_GetLevel(Lua_State* L);
int32_t LuaFunction_SetLevel(Lua_State* L);
int32_t LuaFunction_CanLevelUp(Lua_State* L);
int32_t LuaFunction_GetItemTableIndexByIndex(Lua_State* L);
int32_t LuaFunction_GetZhiye(Lua_State* L);
int32_t LuaFunction_AddExp(Lua_State* L);
int32_t LuaFunction_AddMoney(Lua_State* L);
int32_t LuaFunction_GetRongYu(Lua_State* L);
int32_t LuaFunction_SetRongYu(Lua_State* L);
int32_t LuaFunction_GetShengWang(Lua_State* L);
int32_t LuaFunction_SetShengWang(Lua_State* L);
int32_t LuaFunction_GetItemCount(Lua_State* L);
int32_t LuaFunction_HaveItem(Lua_State* L);
int32 LuaFunction_AddSkill(Lua_State* L);
int32 LuaFunction_DelSkill(Lua_State* L);
int32 LuaFunction_HaveSkill(Lua_State* L);
int32 LuaFunction_UseSkill(Lua_State* L);
int32_t LuaFunction_DelItem(Lua_State* L);
//horse
int32_t LuaFunction_GetHorseCount(Lua_State* L);
int32_t LuaFunction_GetHorseLevel(Lua_State* L);
int32_t LuaFunction_GetHorseTakeLevel(Lua_State* L);
int32_t LuaFunction_GetBeastieItem(Lua_State* L);
int32 LuaFunction_IsHaveHorse(Lua_State* L);
int32_t LuaFunction_IsHaveMount(Lua_State* L);
int32_t LuaFunction_CreateHorseToPlayer(Lua_State* L);
//skill
int32_t LuaFunction_AddSkillToPlayer(Lua_State* L);
int32_t LuaFunction_HumanSkillLevelUp(Lua_State* L);
int32_t LuaFunction_GetHumanSkillLevel(Lua_State* L);
int32_t LuaFunction_OpenSkillStudyUI(Lua_State* L);
int32_t LuaFunction_SetImmuneAbsForLater(Lua_State* L);
int32_t LuaFunction_DispelSpecificImpact(Lua_State* L);
int32_t LuaFunction_GetImpactListCount(Lua_State* L);
int32_t LuaFunction_GetImpactDataIndex(Lua_State* L);
int32_t LuaFunction_SetImpactContinuanceByDataIndex(Lua_State* L);
int32_t LuaFunction_GetImpactContinuanceElapsed(Lua_State* L);
int32_t LuaFunction_ResetImpactContinuanceElapsed(Lua_State* L);
int32_t LuaFunction_GetItemDurOnDieRefix(Lua_State* L);
int32_t LuaFunction_GetPlayerMaxHP(Lua_State* L);
int32_t LuaFunction_RefreshImpactByDataIndex(Lua_State* L);
int32_t LuaFunction_AddInherenceZhuanGongExp(Lua_State* L);
int32_t LuaFunction_SetInherenceZhuanFangExp(Lua_State* L);
int32_t LuaFunction_ReallocateInherenceZhuanFangPoint(Lua_State* L);

//ability
int32 LuaFunction_ItemBoxEnterScene(Lua_State* L);