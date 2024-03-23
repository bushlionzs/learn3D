--功能：国家收集情报
--NPC：先锋将军

--MisDescBegin
x211005_g_ScriptId = 211005

x211005_g_MissionName = "收集情报"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211005_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y收集情报")
		AddQuestText(sceneId, "两国交战，情报的收集工作尤为重要。情报人员虽然不在战场上冲锋陷阵杀敌，但是一条重要的情报，往往杀人无数于无形中。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211005_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211005_g_ScriptId, x211005_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211005_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211005_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211005_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211005_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211005_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211005_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211005_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211005_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end