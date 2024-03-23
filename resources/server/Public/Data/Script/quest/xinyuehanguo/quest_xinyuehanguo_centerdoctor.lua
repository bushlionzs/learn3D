--功能：中心医生
--NPC：中心医生

x211023_g_ScriptId = 211023
x211023_g_MissionName="免费治疗"
--**********************************

--任务入口函数

--**********************************

function x211023_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y免费治疗")
		AddQuestText(sceneId, "\t目前国家正处于不断发展阶段，我这里可以为你免费治疗。现在你已经恢复了健康，去做你该做的事吧。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local	strText = "你恢复了健康"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
end



--**********************************

--列举事件

--**********************************

function x211023_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211023_g_ScriptId, x211023_g_MissionName , 3 )
end



--**********************************

--检测接受条件

--**********************************

function x211023_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211023_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211023_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211023_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211023_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211023_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211023_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211023_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end