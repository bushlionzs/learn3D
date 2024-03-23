--离开新手村

--MisDescBegin
x550201_g_ScriptId = 550201
x550201_g_MissionName = "返回村里"
x550201_g_MissionInfo=" 我可以把你送回村子。"  --任务描述
x550201_g_MissionInfo2=""
--x550201_g_MissionQuestID	=	2553
x550201_g_MissionComplete="  "					--完成任务npc说话的话
x550201_g_ContinueInfo="    "
x550201_g_TransPos1 = "xinshoumigong1loulan"
x550201_g_TransPos2 = "xinshoumigong1laiyin"
x550201_g_TransPos3 = "xinshoumigong1kunlun"
x550201_g_TransPos4 = "xinshoumigong1dunhuang"
--任务奖励
x550201_g_MoneyBonus = 10000
--固定物品奖励，最多8种
x550201_g_ItemBonus={}

--可选物品奖励，最多8种
x550201_g_RadioItemBonus={}

--MisDescEnd
x550201_g_ExpBonus = 1000
--**********************************

--任务入口函数

--**********************************

function x550201_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	local country = GetCurCountry(sceneId,selfId)
		if country == 0 then		
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos1)
    elseif country ==1 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos2)
		elseif country ==2 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos3)
		elseif country ==3 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos4)
	end



--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId, x550201_g_MissionInfo)
--		EndQuestEvent()
--		DispatchQuestInfo(sceneId, selfId, targetId, x550201_g_ScriptId, x550201_g_MissionName)

	
end



--**********************************

--列举事件

--**********************************

function x550201_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x550201_g_ScriptId, x550201_g_MissionName,15)

			
end



--**********************************

--检测接受条件

--**********************************

function x550201_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--检测查看条件

--**********************************

function x550201_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--接受

--**********************************

function x550201_ProcAccept(sceneId, selfId)
		--PrintNum(111)

	
end



--**********************************

--放弃

--**********************************

function x550201_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--检测是否可以提交

--**********************************

function x550201_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--提交

--**********************************

function x550201_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--进入区域事件

--**********************************

function x550201_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x550201_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

