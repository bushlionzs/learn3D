--功能：国家筹集军粮
--NPC：后军将军

--MisDescBegin
x211007_g_ScriptId = 211007

x211007_g_MissionName = "筹集军粮"
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211007_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y筹集军粮")
		AddQuestText(sceneId, "前线的战士们正在浴血奋战，我们做后勤的一定不能掉链子，做好他们的大后方。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211007_g_ScriptId, x211007_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211007_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--接受

--**********************************

function x211007_ProcAccept(sceneId, selfId)
    
end



--**********************************

--放弃

--**********************************

function x211007_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211007_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211007_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211007_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211007_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211007_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end