--功能：补偿领取
--NPC：新月汗国 礼戒

x211015_g_ScriptId = 211015
x211015_g_MissionName="补偿领取"

--**********************************

--任务入口函数

--**********************************

function x211015_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y补偿领取")
		AddQuestText(sceneId, "不少国民为国家的发展，无私的奉献了自己，汗国是不会忘记大家对国家的服出的。奉大王旨意，我这里负责对符合要求的国民给予一定的补偿。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x211015_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211015_g_ScriptId, x211015_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211015_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211015_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211015_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211015_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211015_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211015_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211015_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211015_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end