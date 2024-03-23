--功能：国家建设工程
--NPC：大司空

--MisDescBegin
x211004_g_ScriptId = 211004

x211004_g_MissionName = "建设工程"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211004_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y建设工程")
		AddQuestText(sceneId, "国家基础建设跟上了，国民的生活质量才有提高。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211004_g_ScriptId, x211004_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211004_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211004_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211004_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211004_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211004_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end