--�ݵ�ս����B�¼�����

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300924_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	return CallScriptFunction(300918,"ProcAreaEnteredB",sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--�뿪�����¼�
----------------------------------------------------------------------------------------------
function x300924_ProcAreaLeaved(sceneId,selfId,zoneId,MissionId)
	return CallScriptFunction(300918,"ProcAreaLeavedB",sceneId, selfId, zoneId, MissionId)
end