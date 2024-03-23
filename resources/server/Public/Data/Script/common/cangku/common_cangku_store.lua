--功能：仓库
--NPC：新月汗国 仓库老板，仓库伙计

x561000_g_ScriptId = 561000
x561000_g_MissionName="仓库"

--**********************************

--任务入口函数

--**********************************

function x561000_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BankBegin(sceneId, selfId,targetId)
end



--**********************************

--列举事件

--**********************************

function x561000_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x561000_g_ScriptId, x561000_g_MissionName,12)
end



--**********************************

--检测接受条件

--**********************************

function x561000_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x561000_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x561000_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x561000_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x561000_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x561000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x561000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x561000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end