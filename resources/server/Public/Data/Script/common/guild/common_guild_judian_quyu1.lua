--�ݵ�ս����A�¼�����

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300923_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	return CallScriptFunction(300918,"ProcAreaEnteredA",sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--�뿪�����¼�
----------------------------------------------------------------------------------------------
function x300923_ProcAreaLeaved(sceneId,selfId,zoneId,MissionId)
	return CallScriptFunction(300918,"ProcAreaLeavedA",sceneId, selfId, zoneId, MissionId)
end