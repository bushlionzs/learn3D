--据点战区域B事件处理

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300924_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	return CallScriptFunction(300918,"ProcAreaEnteredB",sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--离开区域事件
----------------------------------------------------------------------------------------------
function x300924_ProcAreaLeaved(sceneId,selfId,zoneId,MissionId)
	return CallScriptFunction(300918,"ProcAreaLeavedB",sceneId, selfId, zoneId, MissionId)
end