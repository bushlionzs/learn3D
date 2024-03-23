--猜谜玩法头顶叹号 空任务

--MisDescBegin
x300102_g_ScriptId = 300102
x300102_g_LevelLess	= 	40

--MisDescEnd
--**********************************

function x300102_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local level = GetLevel(sceneId, selfId)
	
	if level < 160 then 
		return 
	else
		AddQuestText(sceneId," ")
	end
		
	
	
end

function x300102_DispatchMissionInfo( sceneId, selfId, NPCId )
	
end
--**********************************

function x300102_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本

	
end
--**********************************

function x300102_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x300102_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x300102_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	                                                 
	     
end
--**********************************

function x300102_ProcQuestAbandon(sceneId, selfId, MissionId)

end
--**********************************
function x300102_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	
end
--**********************************
function x300102_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end


function x300102_OnScneneTimer(sceneId)

end


--**********************************
--关闭计时器
--**********************************
function x300102_CloseTimer( sceneId, TimerIndex )

end


function x300102_GetBonus( sceneId, selfId,NpcID)

end

function x300102_Msg2toplayer( sceneId, selfId,type)

end

function x300102_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x300102_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x300102_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x300102_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x300102_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x300102_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x300102_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x300102_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x300102_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x300102_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x300102_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x300102_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end