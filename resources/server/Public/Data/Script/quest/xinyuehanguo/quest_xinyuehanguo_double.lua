--功能：领双相关
--NPC：御林军统领

--MisDescBegin
x211034_g_ScriptId = 211034

--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211034_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	--BeginQuestEvent(sceneId)
	--	AddQuestText(sceneId, "你领取了#G一小时#W的双倍经验时间，快去历练吧，提高自己，超越自己！")
	--EndQuestEvent(sceneId)
	--DispatchQuestEventList(sceneId,selfId,targetId)
	--
	--BeginQuestEvent(sceneId)
	--	AddQuestText(sceneId, "你领取了一小时双倍经验时间")
	--EndQuestEvent(sceneId)
	--DispatchQuestTips(sceneId,selfId)
end



--**********************************

--列举事件

--**********************************

function x211034_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, 211034, "一小时")
end

--**********************************

--检测接受条件

--**********************************

function x211034_ProcAcceptCheck(sceneId, selfId, targetId)
end


--**********************************

--接受

--**********************************

function x211034_ProcAccept(sceneId, selfId)
end



--**********************************

--放弃

--**********************************

function x211034_ProcQuestAbandon(sceneId, selfId, MissionId)
end



--**********************************

--检测是否可以提交

--**********************************

function x211034_CheckSubmit( sceneId, selfId, targetId)
end



--**********************************

--提交

--**********************************

function x211034_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211034_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



--**********************************

--进入区域事件

--**********************************

function x211034_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
end



--**********************************

--道具改变

--**********************************

function x211034_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end