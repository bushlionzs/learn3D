--野外回王城
--废弃

x550004_g_ScriptId 					= 550004
x550004_g_MissionName				= "记忆之门"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550004_g_ScriptId, x550004_g_MissionName);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550004_ProcEventEntry(sceneId, selfId, targetId)
		DispatchTransferType(sceneId, selfId, targetId, 5, -1)
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550004_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550004_ProcAccept(sceneId, selfId, targetId)

end