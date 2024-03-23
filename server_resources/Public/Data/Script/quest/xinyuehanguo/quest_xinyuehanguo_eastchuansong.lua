--功能：东门传送
--NPC：东门传送使者

x211028_g_ScriptId = 211028
x211028_g_MissionName="汗国广场"
--**********************************

--任务入口函数

--**********************************

function x211028_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	SetPos(sceneId, selfId,108,258)
end



--**********************************

--列举事件

--**********************************

function x211028_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211028_g_ScriptId, x211028_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211028_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211028_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211028_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211028_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211028_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211028_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211028_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211028_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end