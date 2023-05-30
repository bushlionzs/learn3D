#include "stdafx.h"
#include "LuaFunction.h"
#include "LuaFunction_Quest.h"
#include "LuaFunction_General.h"
#include "basetool.h"
#include "LuaSystem.h"
#include "LuaMacro.h"
#include "StructCommandScript.h"
#include "net/messages/SCQueryEventResult.h"
#include "net/net_message_manager.h"
int32_t LuaFunction_GetCurrentTime(Lua_State* L)
{
	lua_pushnumber(L, GET_TIME().GetCTime());
	return 1;
}


void LuaSystem::RegFunction()
{
	m_LuaState->GetGlobals().Register("GetCurrentTime", LuaFunction_GetCurrentTime);
	//general
	m_LuaState->GetGlobals().Register("GetMonsterDataID", LuaFunction_GetMonsterDataID);
	m_LuaState->GetGlobals().Register("Msg2Player", LuaFunction_Msg2Player);
	//quest
	m_LuaState->GetGlobals().Register("BeginQuestEvent", LuaFunction_BeginQuestEvent);
	m_LuaState->GetGlobals().Register("EndQuestEvent", LuaFunction_EndQuestEvent);
	m_LuaState->GetGlobals().Register("DispatchQuestEventList", LuaFunction_DispatchQuestEventList);
	m_LuaState->GetGlobals().Register("GetFrontQuestIdNM", LuaFunction_GetFrontQuestIdNM);
	m_LuaState->GetGlobals().Register("IsQuestHaveDoneNM", LuaFunction_IsQuestHaveDoneNM);
	m_LuaState->GetGlobals().Register("OnNPCClickedQuestNM", LuaFunction_OnNPCClickedQuest);
	m_LuaState->GetGlobals().Register("AddQuestText", LuaFunction_AddQuestText);
	m_LuaState->GetGlobals().Register("QuestCheckAcceptNM", LuaFunction_QuestCheckAcceptNM);
	m_LuaState->GetGlobals().Register("AddQuestTextNM", LuaFunction_AddQuestTextNM);
	m_LuaState->GetGlobals().Register("IsHaveQuestNM", LuaFunction_IsHaveQuestNM);
	m_LuaState->GetGlobals().Register("ShowNpcQuestEventList", LuaFunction_ShowNpcQuestEventList);
	m_LuaState->GetGlobals().Register("GetQuestStateNM", LuaFunction_GetQuestStateNM);
	m_LuaState->GetGlobals().Register("BeginUICommand", LuaFunction_BeginUICommand);
	m_LuaState->GetGlobals().Register("EndUICommand", LuaFunction_EndUICommand);
	m_LuaState->GetGlobals().Register("UICommand_AddInt", LuaFunction_UICommand_AddInt);
	m_LuaState->GetGlobals().Register("DispatchUICommand", LuaFunction_DispatchUICommand);
	m_LuaState->GetGlobals().Register("IsHaveQuest", LuaFunction_IsHaveQuest);
	m_LuaState->GetGlobals().Register("IsQuestHaveDone", LuaFunction_IsQuestHaveDone);
	m_LuaState->GetGlobals().Register("AddQuestExpBonus", LuaFunction_AddQuestExpBonus);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus", LuaFunction_AddQuestMoneyBonus);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus1", LuaFunction_AddQuestMoneyBonus1);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus2", LuaFunction_AddQuestMoneyBonus2);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus3", LuaFunction_AddQuestMoneyBonus3);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus4", LuaFunction_AddQuestMoneyBonus4);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus5", LuaFunction_AddQuestMoneyBonus5);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus6", LuaFunction_AddQuestMoneyBonus6);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus7", LuaFunction_AddQuestMoneyBonus7);
	m_LuaState->GetGlobals().Register("AddQuestMoneyBonus8", LuaFunction_AddQuestMoneyBonus8);
	m_LuaState->GetGlobals().Register("DispatchQuestContinueInfoNM", LuaFunction_DispatchQuestContinueInfoNM);
	m_LuaState->GetGlobals().Register("AddQuestItemBonus", LuaFunction_AddQuestItemBonus);
	m_LuaState->GetGlobals().Register("AddQuestRadioItemBonus", LuaFunction_AddQuestRadioItemBonus);
	m_LuaState->GetGlobals().Register("GetQuestIndexByID", LuaFunction_GetQuestIndexByID);
	m_LuaState->GetGlobals().Register("GetQuestParam", LuaFunction_GetQuestParam);
	m_LuaState->GetGlobals().Register("SetQuestParam", LuaFunction_SetQuestParam);
	m_LuaState->GetGlobals().Register("AddQuestNumText", LuaFunction_AddQuestNumText);
	m_LuaState->GetGlobals().Register("SetQuestByIndex", LuaFunction_SetQuestByIndex);
	m_LuaState->GetGlobals().Register("DispatchQuestInfoNM", LuaFunction_DispatchQuestInfoNM);
	m_LuaState->GetGlobals().Register("IsQuestFullNM", LuaFunction_IsQuestFullNM);
	m_LuaState->GetGlobals().Register("AddQuest", LuaFunction_AddQuest);
	m_LuaState->GetGlobals().Register("BeginAddItem", LuaFunction_BeginAddItem);
	m_LuaState->GetGlobals().Register("AddItem", LuaFunction_AddItem);
	m_LuaState->GetGlobals().Register("AddBindItem", LuaFunction_AddBindItem);
	m_LuaState->GetGlobals().Register("EndAddItem", LuaFunction_EndAddItem);
	m_LuaState->GetGlobals().Register("DelQuest", LuaFunction_DelQuest);
	m_LuaState->GetGlobals().Register("QuestCom", LuaFunction_QuestCom);
	m_LuaState->GetGlobals().Register("DispatchQuestTips", LuaFunction_DispatchQuestTips);
	m_LuaState->GetGlobals().Register("AddItemListToPlayer", LuaFunction_AddItemListToPlayer);
	m_LuaState->GetGlobals().Register("GetNeedItemNumNM", LuaFunction_GetNeedItemNumNM);
	m_LuaState->GetGlobals().Register("QuestComplateNM", LuaFunction_QuestComplateNM);
	m_LuaState->GetGlobals().Register("PushAfterQuestNM", LuaFunction_PushAfterQuestNM);
	m_LuaState->GetGlobals().Register("IsNpcHaveQuestNM", LuaFunction_IsNpcHaveQuestNM);
	m_LuaState->GetGlobals().Register("AddDispatchQuestInfoNM", LuaFunction_AddDispatchQuestInfoNM);
	m_LuaState->GetGlobals().Register("SetQuestEvent", LuaFunction_SetQuestEvent);
	m_LuaState->GetGlobals().Register("GetMonsterOwnerCount", LuaFunction_GetMonsterOwnerCount);
	m_LuaState->GetGlobals().Register("GetMonsterOwnerID", LuaFunction_GetMonsterOwnerID);
	m_LuaState->GetGlobals().Register("GetItemIdInItemBoxNM", LuaFunction_GetItemIdInItemBoxNM);
	//attr
	m_LuaState->GetGlobals().Register("GetLevel", LuaFunction_GetLevel);
	m_LuaState->GetGlobals().Register("SetLevel", LuaFunction_SetLevel);
	m_LuaState->GetGlobals().Register("CanLevelUp", LuaFunction_CanLevelUp);
	m_LuaState->GetGlobals().Register("GetItemTableIndexByIndex", LuaFunction_GetItemTableIndexByIndex);
	m_LuaState->GetGlobals().Register("GetZhiye", LuaFunction_GetZhiye);
	m_LuaState->GetGlobals().Register("AddExp", LuaFunction_AddExp);
	m_LuaState->GetGlobals().Register("AddMoney", LuaFunction_AddMoney);
	m_LuaState->GetGlobals().Register("GetRongYu", LuaFunction_GetRongYu);
	m_LuaState->GetGlobals().Register("SetRongYu", LuaFunction_SetRongYu);
	m_LuaState->GetGlobals().Register("GetShengWang", LuaFunction_GetShengWang);
	m_LuaState->GetGlobals().Register("SetShengWang", LuaFunction_SetShengWang);
	m_LuaState->GetGlobals().Register("GetItemCount", LuaFunction_GetItemCount);
	m_LuaState->GetGlobals().Register("HaveItem", LuaFunction_HaveItem);
	m_LuaState->GetGlobals().Register("AddSkill", LuaFunction_AddSkill);
	m_LuaState->GetGlobals().Register("DelSkill", LuaFunction_DelSkill);
	m_LuaState->GetGlobals().Register("HaveSkill", LuaFunction_HaveSkill);
	m_LuaState->GetGlobals().Register("UseSkill", LuaFunction_UseSkill);
	m_LuaState->GetGlobals().Register("DelItem", LuaFunction_DelItem);
	//horse
	m_LuaState->GetGlobals().Register("GetHorseCount", LuaFunction_GetHorseCount);
	m_LuaState->GetGlobals().Register("GetHorseLevel", LuaFunction_GetHorseLevel);
	m_LuaState->GetGlobals().Register("GetHorseTakeLevel", LuaFunction_GetHorseTakeLevel);
	m_LuaState->GetGlobals().Register("GetBeastieItem", LuaFunction_GetBeastieItem);
	m_LuaState->GetGlobals().Register("IsHaveHorse", LuaFunction_IsHaveHorse);
	m_LuaState->GetGlobals().Register("IsHaveMount", LuaFunction_IsHaveMount);
	m_LuaState->GetGlobals().Register("CreateHorseToPlayer", LuaFunction_CreateHorseToPlayer);
	//skill
	m_LuaState->GetGlobals().Register("AddSkillToPlayer", LuaFunction_AddSkillToPlayer);
	m_LuaState->GetGlobals().Register("HumanSkillLevelUp", LuaFunction_HumanSkillLevelUp);
	m_LuaState->GetGlobals().Register("GetHumanSkillLevel", LuaFunction_GetHumanSkillLevel);
	m_LuaState->GetGlobals().Register("OpenSkillStudyUI", LuaFunction_OpenSkillStudyUI);
	m_LuaState->GetGlobals().Register("SetImmuneAbsForLater", LuaFunction_SetImmuneAbsForLater);
	m_LuaState->GetGlobals().Register("DispelSpecificImpact", LuaFunction_DispelSpecificImpact);
	m_LuaState->GetGlobals().Register("GetImpactListCount", LuaFunction_GetImpactListCount);
	m_LuaState->GetGlobals().Register("GetImpactDataIndex", LuaFunction_GetImpactDataIndex);
	m_LuaState->GetGlobals().Register("SetImpactContinuanceByDataIndex", LuaFunction_SetImpactContinuanceByDataIndex);
	m_LuaState->GetGlobals().Register("GetImpactContinuanceElapsed", LuaFunction_GetImpactContinuanceElapsed);
	m_LuaState->GetGlobals().Register("ResetImpactContinuanceElapsed", LuaFunction_ResetImpactContinuanceElapsed);
	m_LuaState->GetGlobals().Register("GetItemDurOnDieRefix", LuaFunction_GetItemDurOnDieRefix);
	m_LuaState->GetGlobals().Register("GetPlayerMaxHP", LuaFunction_GetPlayerMaxHP);
	m_LuaState->GetGlobals().Register("RefreshImpactByDataIndex", LuaFunction_RefreshImpactByDataIndex);
	m_LuaState->GetGlobals().Register("AddInherenceZhuanGongExp", LuaFunction_AddInherenceZhuanGongExp);
	m_LuaState->GetGlobals().Register("SetInherenceZhuanFangExp", LuaFunction_SetInherenceZhuanFangExp);
	m_LuaState->GetGlobals().Register("ReallocateInherenceZhuanFangPoint", LuaFunction_ReallocateInherenceZhuanFangPoint);
	//ability
	m_LuaState->GetGlobals().Register("ItemBoxEnterScene", LuaFunction_ItemBoxEnterScene);
	//other
	m_LuaState->GetGlobals().Register("CallScriptFunction", LuaFunction_CallScriptFunction);
}
