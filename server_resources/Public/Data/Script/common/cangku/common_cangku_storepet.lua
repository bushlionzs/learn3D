--功能：仓库
--NPC：新月汗国 仓库老板，仓库伙计

x561004_g_ScriptId = 561004
x561004_g_MissionName="骑乘仓库"

--**********************************

--任务入口函数

--**********************************

function x561004_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
end



--**********************************

--列举事件

--**********************************

function x561004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x561004_g_ScriptId, x561004_g_MissionName,12)
end



--**********************************

--检测接受条件

--**********************************

function x561004_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--**********************************

--接受

--**********************************

function x561004_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561004_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561004_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561004_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end