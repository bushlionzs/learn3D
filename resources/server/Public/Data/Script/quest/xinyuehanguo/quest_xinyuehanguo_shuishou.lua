--功能：国家税收任务
--NPC：大司马

--MisDescBegin
x211003_g_ScriptId = 211003

x211003_g_MissionName = "税收"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211003_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y税收")
		AddQuestText(sceneId, "有了充足的税收，国家就可以发展科技，建设工程。但是过重的税收也会导致民怨，所以慎之慎之啊！")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211003_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211003_g_ScriptId, x211003_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211003_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211003_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211003_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211003_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211003_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211003_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211003_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211003_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end