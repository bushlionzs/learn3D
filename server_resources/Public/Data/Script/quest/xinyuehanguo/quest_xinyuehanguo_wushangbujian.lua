--功能：南门传送
--NPC：南门传送使者

x211051_g_ScriptId = 211051
x211051_g_MissionName="汗国广场"
--**********************************

--任务入口函数

--**********************************

function x211051_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	SetPos(sceneId, selfId,108,258)
end



--**********************************

--列举事件

--**********************************

function x211051_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211051_g_ScriptId, x211051_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211051_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211051_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211051_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211051_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211051_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211051_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211051_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211051_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end