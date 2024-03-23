--离开比武场

--MisDescBegin
x300314_g_ScriptId = 300314
--x300314_g_Name	="比武传送"

x300314_g_MissionName = "离开比武场"
x300314_g_MissionInfo=" 你确定要离开比武场吗？"  --任务描述
x300314_g_MissionInfo2=""
x300314_g_MissionTarget="    "
x300314_g_MissionComplete="  "					--完成任务npc说话的话
x300314_g_ContinueInfo="    "
x300314_g_TransPos1 = "biwu2loulan"
x300314_g_TransPos2 = "biwu2laiyin"
x300314_g_TransPos3 = "biwu2kunlun"
x300314_g_TransPos4 = "biwu2dunhuang"
--任务奖励
x300314_g_MoneyBonus = 10000
--固定物品奖励，最多8种
x300314_g_ItemBonus={}

--可选物品奖励，最多8种
x300314_g_RadioItemBonus={}

--MisDescEnd
x300314_g_ExpBonus = 1000
--**********************************

--任务入口函数

--**********************************

function x300314_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x300314_g_MissionInfo)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x300314_g_ScriptId, x300314_g_MissionName)

end



--**********************************

--列举事件

--**********************************

function x300314_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

--	BeginQuestEvent(sceneId)
		AddQuestNumText(sceneId, x300314_g_ScriptId, x300314_g_MissionName)
--	EndQuestEvent()
--	DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--检测接受条件

--**********************************

function x300314_ProcAcceptCheck(sceneId, selfId, targetId)
return 1
end


--**********************************

--检测查看条件

--**********************************

function x300314_CheckPushList(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x300314_ProcAccept(sceneId, selfId)
	local country = GetCurCountry(sceneId, selfId)

    CallScriptFunction(700005,"RestorePlayerCamp", sceneId,selfId)
    SetPlayerMutexState( sceneId,selfId,PLAYER_STATE_DIE,0) --####

	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos1)
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos2)
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos3)
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos4)
	end

end



--**********************************

--放弃

--**********************************

function x300314_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--检测是否可以提交

--**********************************

function x300314_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--提交

--**********************************

function x300314_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)


end


--进入区域事件

--**********************************

function x300314_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x300314_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

