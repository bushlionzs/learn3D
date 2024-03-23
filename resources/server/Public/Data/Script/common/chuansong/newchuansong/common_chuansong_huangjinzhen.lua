--王城边境马车夫

x550001_g_ScriptId 					= 550001
x550001_g_MissionName				= "马车夫"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550001_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550001_g_ScriptId, x550001_g_MissionName,15);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550001_ProcEventEntry(sceneId, selfId, targetId)
	local country = GetCurCountry(sceneId,selfId)
	if country == 0 then
		DispatchTransferType(sceneId, selfId, targetId, 7, -1)
	elseif country == 1 then
		DispatchTransferType(sceneId, selfId, targetId, 10, -1)
	elseif country == 2 then	
		DispatchTransferType(sceneId, selfId, targetId, 13, -1)
	elseif country == 3 then
		DispatchTransferType(sceneId, selfId, targetId, 16, -1)
	end	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550001_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550001_ProcAccept(sceneId, selfId, targetId)

end