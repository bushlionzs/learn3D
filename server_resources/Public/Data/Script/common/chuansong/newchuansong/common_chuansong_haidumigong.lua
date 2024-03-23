--进入地窖

--MisDescBegin
x550202_g_ScriptId = 550202
x550202_g_MissionName = "进入古老的祭坛"
x550202_g_MissionInfo=" 我可以送你入山谷，请点确定"  --任务描述
x550202_g_MissionInfo2=""
x550202_g_MissionQuestID	=	2723
x550202_g_MissionComplete="  "					--完成任务npc说话的话
x550202_g_ContinueInfo="    "
x550202_g_TransPos1 = "xinshoumigong2loulanin"
x550202_g_TransPos2 = "xinshoumigong2laiyinin"
x550202_g_TransPos3 = "xinshoumigong2kunlunin"
x550202_g_TransPos4 = "xinshoumigong2dunhuangin"
--任务奖励
x550202_g_MoneyBonus = 10000
--固定物品奖励，最多8种
x550202_g_ItemBonus={}

--可选物品奖励，最多8种
x550202_g_RadioItemBonus={}

--MisDescEnd
x550202_g_ExpBonus = 1000
--**********************************

--任务入口函数

--**********************************

function x550202_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local country = GetCurCountry(sceneId,selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos1)
	elseif country ==1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos2)
	elseif country ==2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos3)
	elseif country ==3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos4)
	end	
		
		
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId, x550202_g_MissionInfo)
--		EndQuestEvent()
--		DispatchQuestInfo(sceneId, selfId, targetId, x550202_g_ScriptId, x550202_g_MissionName)

	
end



--**********************************

--列举事件

--**********************************

function x550202_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	--if IsHaveQuest(sceneId, selfId,x550202_g_MissionQuestID) > 0 then

		AddQuestNumText(sceneId, x550202_g_ScriptId, x550202_g_MissionName,16)

	--else 
		--return
	--end
			
end



--**********************************

--检测接受条件

--**********************************

function x550202_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--检测查看条件

--**********************************

function x550202_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--接受

--**********************************

function x550202_ProcAccept(sceneId, selfId)
		
		
--	  BeginQuestEvent(sceneId)
--					NewWorld(sceneId,selfId,163,65,64, 550202)
--		EndQuestEvent()
    
end



--**********************************

--放弃

--**********************************

function x550202_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--检测是否可以提交

--**********************************

function x550202_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--提交

--**********************************

function x550202_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--进入区域事件

--**********************************

function x550202_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x550202_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

