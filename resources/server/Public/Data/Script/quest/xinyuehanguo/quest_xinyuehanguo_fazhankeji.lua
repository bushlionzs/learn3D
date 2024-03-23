--功能：国家发展科技任务
--NPC：大司徒

--MisDescBegin
x211002_g_ScriptId = 211002

x211002_g_MissionName = "发展科技"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211002_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y发展科技")
		AddQuestText(sceneId, "国家要发展强大，需要科技的不断提升。国强则民强，国弱则民弱，为国奉献，义不容辞。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211002_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211002_g_ScriptId, x211002_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211002_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211002_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211002_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211002_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211002_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end