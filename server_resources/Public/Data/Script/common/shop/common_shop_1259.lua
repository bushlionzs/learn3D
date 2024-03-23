--功能：骑乘炼化金币商店

x561259_g_ScriptId = 561259
x561259_g_MissionName="骑乘炼化金币商店"
x561259_g_ShopList={1259}
--**********************************

--任务入口函数

--**********************************

function x561259_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x561259_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x561259_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 85 then
		AddQuestNumText(sceneId, x561259_g_ScriptId, x561259_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x561259_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561259_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561259_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561259_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561259_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561259_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561259_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561259_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end