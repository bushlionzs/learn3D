--皇城边境马车夫

x550002_g_ScriptId 					= 550002
x550002_g_MissionName				= "马车夫"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550002_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550002_g_ScriptId, x550002_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550002_ProcEventEntry(sceneId, selfId, targetId)
	local country = GetCurCountry(sceneId,selfId)
	if country == 0 then
		DispatchTransferType(sceneId, selfId, targetId, 8, -1)
	elseif country == 1 then
		DispatchTransferType(sceneId, selfId, targetId, 11, -1)
	elseif country == 2 then	
		DispatchTransferType(sceneId, selfId, targetId, 14, -1)
	elseif country == 3 then
		DispatchTransferType(sceneId, selfId, targetId, 17, -1)
	end	
		
		
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550002_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550002_ProcAccept(sceneId, selfId, targetId)

end