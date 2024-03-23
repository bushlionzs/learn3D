--功能：骑乘商店
--NPC：骑乘店老板

--MisDescBegin
x211025_g_ScriptId = 211025

x211025_g_MissionName = "骑乘商店"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211025_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, 950 )
end



--**********************************

--列举事件

--**********************************

function x211025_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211025_g_ScriptId, x211025_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211025_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211025_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211025_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211025_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211025_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211025_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211025_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211025_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end