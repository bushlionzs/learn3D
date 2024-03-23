--功能：推广员
--NPC：新月汗国 推广员

x211016_g_ScriptId = 211016
x211016_g_MissionName="推广员系统"

--**********************************

--任务入口函数

--**********************************

function x211016_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y推广员系统")
		AddQuestText(sceneId, "只要你能邀请更多的人加入到游戏里来，国家都将给予你相当的奖励。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211016_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211016_g_ScriptId, x211016_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211016_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211016_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211016_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211016_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211016_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211016_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211016_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211016_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end