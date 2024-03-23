--功能：饰品商店

x560150_g_ScriptId = 560150
x560150_g_MissionName="金币商店"

--**********************************

--任务入口函数

--**********************************

function x560150_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	CallScriptFunction(560888, "OnDispatchGoldShopItem", sceneId, selfId, 0,0)

end



--**********************************

--列举事件

--**********************************

function x560150_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560150_g_ScriptId, x560150_g_MissionName,10)
end



--**********************************

--检测接受条件

--**********************************

function x560150_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560150_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560150_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560150_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560150_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560150_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560150_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560150_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end