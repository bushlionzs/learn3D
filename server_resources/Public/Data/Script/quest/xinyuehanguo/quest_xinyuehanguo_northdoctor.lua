--功能：中心医生
--NPC：中心医生

x211031_g_ScriptId = 211031
x211031_g_MissionName="免费治疗"
--**********************************

--任务入口函数

--**********************************

function x211031_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y免费治疗")
		AddQuestText(sceneId, "目前国家正处于不断发展阶段，我这里也响应号召，为大家免费治疗。现在你已经恢复健康了，去做你该做的事吧，不要荒废了光阴。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "你全身恢复了健康"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	RestoreHp(sceneId, selfId,100)
	RestoreRage(sceneId, selfId,100)
end



--**********************************

--列举事件

--**********************************

function x211031_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211031_g_ScriptId, x211031_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211031_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211031_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211031_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211031_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211031_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211031_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211031_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211031_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end