--功能：国家发动国战
--NPC：中军将军

--MisDescBegin
x211006_g_ScriptId = 211006

x211006_g_MissionName = "发动国战"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211006_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y发动国战")
		AddQuestText(sceneId, "对于敌人，我们坚决不能示弱。保持国人的战斗热情，我国才能在战争中抢得先机。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211006_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211006_g_ScriptId, x211006_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211006_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211006_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211006_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211006_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211006_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211006_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211006_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211006_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end