--功能：怪兽总动员
--NPC：新月汗国 哈伦

x211013_g_ScriptId = 211013
x211013_g_MissionName="怪兽总动员"

--**********************************

--任务入口函数

--**********************************

function x211013_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y怪兽总动员")
		AddQuestText(sceneId, "最近国内豪门流行招揽门客，我手底下也有不少来自各地的人才，你可敢与他们较量较量，我也正好看看他们是不是有真本事。文斗武斗，你来选。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211013_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211013_g_ScriptId, x211013_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211013_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211013_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211013_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211013_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211013_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211013_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211013_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211013_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end