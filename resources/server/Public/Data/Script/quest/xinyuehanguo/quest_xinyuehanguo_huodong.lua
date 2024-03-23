--功能：庆祝活动
--NPC：新月汗国 礼仪

x211014_g_ScriptId = 211014
x211014_g_MissionName="庆祝活动"

--**********************************

--任务入口函数

--**********************************

function x211014_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y庆祝活动")
		AddQuestText(sceneId, "每逢节日到来，国家都会有很多的庆祝活动。当然有的时候，国王心情一好，每天都有可能是节日，这个好处自然是……呵呵，不用我明说了吧。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211014_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211014_g_ScriptId, x211014_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211014_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211014_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211014_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211014_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211014_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211014_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211014_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211014_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end