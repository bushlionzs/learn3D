--·ÏÆú

x550003_g_ScriptId 					= 550003
x550003_g_MissionName				= "Õæ¡ï´«ËÍ"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550003_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550003_g_ScriptId, x550003_g_MissionName);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550003_ProcEventEntry(sceneId, selfId, targetId)
		DispatchTransferType(sceneId, selfId, targetId, 3, -1)
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550003_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550003_ProcAccept(sceneId, selfId, targetId)

end