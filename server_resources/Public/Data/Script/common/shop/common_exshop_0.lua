--功能：骑乘炼化金币商店

x561500_g_ScriptId = 561500
x561500_g_MissionName="神秘商店"
x561500_g_EXShopList={0}
--**********************************

--任务入口函数

--**********************************

function x561500_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	local curTime = GetMinOfDay()

	if GetWeek() ~= 0 and GetWeek() ~= 6 or curTime < 540 or curTime >= 1320 then
		Msg2Player(sceneId,selfId,"很抱歉，此商店只在周末12点到22点之间开放",8,3)
    	return
	else
		DispatchDynamicShopItem(sceneId, selfId, targetId, x561500_g_EXShopList[1])
	end
end



--**********************************

--列举事件

--**********************************

function x561500_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 85 then
		AddQuestNumText(sceneId, x561500_g_ScriptId, x561500_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561500_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561500_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561500_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561500_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561500_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561500_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561500_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561500_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end