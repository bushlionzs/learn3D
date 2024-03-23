--据点战区域A事件处理

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300923_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	return CallScriptFunction(300918,"ProcAreaEnteredA",sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--离开区域事件
----------------------------------------------------------------------------------------------
function x300923_ProcAreaLeaved(sceneId,selfId,zoneId,MissionId)
	return CallScriptFunction(300918,"ProcAreaLeavedA",sceneId, selfId, zoneId, MissionId)
end